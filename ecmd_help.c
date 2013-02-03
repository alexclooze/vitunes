/*
 * Copyright (c) 2010, 2011, 2012 Ryan Flannery <ryan.flannery@gmail.com>
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

#include <err.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "ecmd.h"
#include "vitunes.h"

static void
ecmd_help_exec(UNUSED int argc, char **argv)
{
   char *man_args[3];

   /* no help requested for a specific command, give a list of all e-cmds */
   if (argc == 0) {
      printf("\
The following is a list of e-commands supported by vitunes.\n\
Each command is executed by doing:\n\
   $ vitunes -e COMMAND [args ...]\n\
The complete manual for each can be obtained by doing:\n\
   $ vitunes -e help COMMAND\n\
The list of available commands are:\n\n\
   Command     Description\n\
   -------     ------------------------------------------------------------\n\
   init        Create the initial database used by vitunes.\n\
   update      Scan all files in the database and update their records.\n\
   add         Add files to the vitunes database.\n\
   addurl      Add non-files/URLs to the vitunes database.\n\
   check       Scan files for meta-info and if they are in the database.\n\
   rm          Remove files/URLs from the database.\n\
   rmfile      Alias for \"rm\".\n\
   tag         Add or modify meta-information tags in raw files.\n\
   flush       Output the records of all files in the database.\n\
   help        This command.\n\
");
      return;
   }

   /* if reach here, help fora specific command was requested */
   if (strcmp(argv[0], "help") == 0) {
      printf("You're a damn fool if you need help with help.\n");
      return;
   }

   man_args[0] = "man";
   if (asprintf(&man_args[1], "vitunes-%s", argv[0]) == -1)
      err(1, "ecmd_help: asprintf failed");
   man_args[2] = NULL;

   execvp("man", man_args);
   err(1, "ecmd_help: execvp failed");
}

const struct ecmd ecmd_help = {
   "help", NULL,
   "[command]",
   0, 1,
   NULL,
   NULL,
   ecmd_help_exec
};
