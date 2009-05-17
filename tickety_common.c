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

#include "tickety_common.h"

void
tickety_format_elapsed_time(char *elapsed, time_t start_time, time_t stop_time)
{
    int time_diff;
    int hours;
    int minutes;
    int seconds;

    time_diff = (int)(stop_time - start_time);
    hours = time_diff / 3600;
    minutes = (time_diff - hours * 3600) / 60;
    seconds = time_diff - hours * 3600 - minutes * 60;
    sprintf(elapsed, "%02d:%02d:%02d", hours, minutes, seconds);
}
