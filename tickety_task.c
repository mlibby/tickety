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

#include "tickety_task.h"

void
tickety_task_destroy(tickety_task *self)
{
    free(self);
}

tickety_task 
*tickety_task_new(char *name, time_t start_time)
{
    tickety_task *self;

    self = (tickety_task *)malloc(sizeof(tickety_task));
    if(NULL != self)
    {
	strcpy(self->name, name);
	self->start_time = start_time;
	return self;
    }
    return NULL;
}

