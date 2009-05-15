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

#ifndef _TICKETY_UI_H
#define	_TICKETY_UI_H

#include <gtk/gtk.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include "tickety_common.h"
#include "tickety_task.h"

#define GTK_STOCK_MEDIA_STOP_IMAGE gtk_image_new_from_stock(GTK_STOCK_MEDIA_STOP, GTK_ICON_SIZE_BUTTON)
#define GTK_STOCK_MEDIA_PLAY_IMAGE gtk_image_new_from_stock(GTK_STOCK_MEDIA_PLAY, GTK_ICON_SIZE_BUTTON)

struct _tickety_ui {
    tickety_task *current_task;
    GtkWidget *message;
    GtkEntryCompletion *task_completion;
    GtkWidget *task_entry;
    GtkWidget *task_frame;
    GtkListStore *task_model;
    GtkWidget *timer_table;
    GtkWidget *timer_button;
    GtkWidget *root;
    GtkWidget *main_window;
};

typedef struct _tickety_ui tickety_ui;

void
tickety_ui_current_task_new(tickety_ui *self);

void
tickety_ui_current_task_start(tickety_ui *self);

void
tickety_ui_current_task_start_callback(GtkWidget *widget, gpointer data);

void
tickety_ui_current_task_stop(tickety_ui *self);

void
tickety_ui_format_elapsed_time(gchar *elapsed, time_t start_time);

void 
tickety_ui_main_window_destroy(GtkWidget *widget, gpointer data);

void 
tickety_ui_main_window_new(tickety_ui *self);

void 
tickety_ui_message_label_new(tickety_ui *self);

gboolean 
tickety_ui_message_update_elapsed_time(gpointer data);

void
tickety_ui_task_model_add_task(void *data, char *task_name);

void 
tickety_ui_timer_button_click(GtkWidget *widget, gpointer data);

void 
tickety_ui_timer_button_new(tickety_ui *self);

tickety_ui 
*tickety_ui_new();

#endif	/* _TICKETY_UI_H */
