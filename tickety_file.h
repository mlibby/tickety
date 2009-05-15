/*
 *   Copyright 2009, Michael C. Libby
 *
 *   This file is part of Tickety.
 *
 *   Tickety is free software: you can redistribute it and/or modify it
 *   under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   Tickety is distributed in the hope that it will be useful, but
 *   WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *   General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with Tickety.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef _TICKETY_FILE_H
#define	_TICKETY_FILE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tickety_common.h"
#include "tickety_task.h"

#define TICKETY_FILE_SUCCESS_READING_TASK_FILE 0
#define TICKETY_FILE_ERROR_READING_TASK_FILE 1

int
tickety_file_read_task_file(void (*callback)(void*, char*), void *data);

#endif	/* _TICKETY_FILE_H */
