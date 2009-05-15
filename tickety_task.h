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

#ifndef _TICKETY_TASK_H
#define _TICKETY_TASK_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "tickety_common.h"

#define TICKETY_TASK_NAME_MAX_CHARS 255

/*
* This library is here to help keep "model" data out of the view. It
* is still a to-do item to encapsulate task switching and other task
* management functions in this library.
*/

struct _tickety_task {
    char name[TICKETY_TASK_NAME_MAX_CHARS];
    time_t start_time;
};
typedef struct _tickety_task tickety_task;

void
tickety_task_destroy(tickety_task *self);

tickety_task 
*tickety_task_new(char *name, time_t start_time);

#endif /* _TICKETY_TASK_H */
