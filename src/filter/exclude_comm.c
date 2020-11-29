/*
 * SNOOPY LOGGER
 *
 * File: snoopy/filter/exclude_comm.c
 *
 * Copyright (c) 2015 Datto, Inc. All rights reserved.
 * Author: Fred Mora - fmora@datto.com
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */


/*
 * Includes order: from local to global
 */
#include "exclude_comm.h"
#include "exclude_spawns_of.h"
#include "snoopy.h"
#include "inputdatastorage.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

char* extract_comm(const char *str, const char *needle);

/*
 * SNOOPY FILTER: exclude_comm
 *
 * Description:
 *     Excludes all log messages for executables that have the specified program name in their ancestors.
 *     Strategy: We parse arg to create the "list of specified programs" (LoSP).
 *     Then, we filter by filename from LoSP
 *
 * Params:
 *     logMessage: Pointer to string that contains formatted log message (may be manipulated)
 *     arg:        Comma-separated list of program comm names for the spawns of which log messages are dropped.
 *
 * Return:
 *     SNOOPY_FILTER_PASS or SNOOPY_FILTER_DROP
 */
int snoopy_filter_exclude_comm(char *msg, char const * const arg)
{
    char  *argDup;   // Must not alter arg
    char **losp; // List of specified programs derived from arg
    int is_comm_in_list = 0;
    char *comm;

#ifdef SNOOPY_CONF_THREAD_SAFETY_ENABLED
    return SNOOPY_FILTER_PASS;
#endif

    // Turn comma-separated arg into array of program name strings
    argDup = strdup(arg);
    losp = string_to_token_array(argDup);
    if (losp == NULL) {
        // If failure, we cannot filter anything, just pass the message
        return SNOOPY_FILTER_PASS;
    }

    // snoopy_inputdatastorage_data is gloabl variable
    extern snoopy_inputdatastorage_t snoopy_inputdatastorage_data;
    const char* filename = snoopy_inputdatastorage_data.filename;

    const char* delimiter = "/"; // path delimiter in Unix/Linux
    comm = extract_comm(filename, delimiter); // get command name

    // Check if one of the program names in losp is an ancestor
    is_comm_in_list = find_string_in_array(comm, losp);
    free(losp);
    free(argDup);
    return (is_comm_in_list == 1) ? SNOOPY_FILTER_DROP : SNOOPY_FILTER_PASS; // Error means pass
}

// get comm name from filename
char* extract_comm(const char *str, const char *needle)
{
    if (*needle == '\0')
         return (char *)str;

    char *result = NULL;
    for (;;)
    {
        char *p = strstr(str, needle);
        if (p == NULL)
            break;

        result = p + 1;
        str = p + 1;
    }
    return result;
}
