/*
 * SNOOPY LOGGER
 *
 * File: snoopy/filter/exclude_comm.h
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
 *
 * changelog:
 *   add exclude_comm filter
 * arstercz
 * 2020-10-26
 */



/*
 * SNOOPY FILTER: exclude_comm
 */
int snoopy_filter_exclude_comm (const char *filename, char *msg, char const * const arg);
