/*
 * Copyright (c) 2010 Ryan Flannery <ryan.flannery@gmail.com>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#ifndef VITUNES_H
#define VITUNES_H

#include <sys/time.h>

#include <getopt.h>
#include <locale.h>
#include <pwd.h>
#include <signal.h>
#include <util.h>
#include <unistd.h>

#include "debug.h"
#include "enums.h"
#include "input_handlers.h"
#include "medialib.h"
#include "player.h"
#include "uinterface.h"
#include "e_commands.h"

/* record keeping  */
extern playlist   *viewing_playlist;
extern playlist   *playing_playlist;

/* signal flags (references elsewhere) */
extern volatile sig_atomic_t VSIG_QUIT;
extern volatile sig_atomic_t VSIG_RESIZE;
extern volatile sig_atomic_t VSIG_PLAYER_MONITOR;
extern volatile sig_atomic_t VSIG_PLAYER_RESTART;

void load_config();
void process_signals(bool);

#endif
