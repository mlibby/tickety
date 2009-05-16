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

#include "tickety.h"

int 
main(int argc, char *argv[])
{
    tickety_ui *tui;
    int result;

    gtk_init(&argc, &argv);

    tui = tickety_ui_new();
    result = tickety_data_read_task_names(&tickety_ui_task_model_add_task, tui);

    if(TICKETY_DATA_SUCCESS_READING_TASK_FILE == result)
    {
	gtk_widget_show_all(tui->main_window);
	gtk_main();
    }

    return 0;
}
