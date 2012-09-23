include config.mk

# install locations -- OVERRIDEN by config.mk
PREFIX?=/usr/local
BINDIR?=$(PREFIX)/bin
MANDIR?=$(PREFIX)/man/man1

# combine all dependencies (from taglib & config.mk)
CDEPS=$(TAGLIB_CFLAGS)  $(GSTREAMER_CFLAGS)
LDEPS=$(TAGLIB_LDFLAGS) $(GSTREAMER_LDFLAGS)
ODEPS=$(GSTREAMER_OBJS)

# build variables
CC		  ?= /usr/bin/cc
CFLAGS  += -c -std=c89 -Wall -Wextra -Wno-unused-value $(CDEBUG) $(CDEPS)
LDFLAGS += -lm -lncurses -lutil $(LDEPS)

# object files
OBJS=commands.o compat.o e_commands.o \
	  keybindings.o medialib.o meta_info.o \
	  mplayer.o paint.o player.o player_utils.o \
	  playlist.o socket.o str2argv.o \
	  uinterface.o vitunes.o \
	  $(ODEPS)

# subdirectories with code (.PATH for BSD make, VPATH for GNU make)
.PATH:  players
VPATH = players


.PHONY: debug clean clean-all install uninstall

# main build targets

vitunes: $(OBJS)
	$(CC) -o $@ $(LDFLAGS) $(OBJS)

.c.o:
	$(CC) $(CFLAGS) $<

debug:
	make CDEBUG="-DDEBUG -g"

clean:
	rm -f *.o
	rm -f vitunes vitunes.core vitunes-debug.log

clean-all: clean
	rm -rf report.*

install: vitunes
	mkdir -p $(MANDIR)
	install -c -m 0555 vitunes $(BINDIR)
	install -c -m 0444 doc/vitunes*.1 $(MANDIR)

uninstall:
	rm -f $(BINDIR)/vitunes
	rm -f $(MANDIR)/vitunes*.1

# misc. targets

# this should be moved to my vitunes.org repo...
vitunes.html: vitunes.1
	man2web vitunes > vitunes.html

cscope.out: *.h *.c
	cscope -bke

### static analysis checks

.PHONY: report.mandoc
report.mandoc:
	@figlet "mandoc -Tlint"
	-mandoc -Tlint doc/vitunes*.1 2> $@
	cat $@

.PHONY: report.cppcheck
report.cppcheck:
	@figlet "cppcheck"
	make clean
	cppcheck --std=c89 -i compat --enable=all -D_GNU_SOURCE . 1> /dev/null 2> $@
	@cat $@

.PHONY: report.scan-build
report.scan-build:
	@figlet "clang analyzer"
	make clean
	scan-build -o report.scan-build make

### wrapper for static checks above
.PHONY: reports
reports: report.mandoc report.cppcheck report.scan-build
	@figlet "Static Checks Complete"
	cat report.mandoc
	cat report.cppcheck

