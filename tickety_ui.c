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

#include "tickety_ui.h"

void
tickety_ui_current_task_completion_new(tickety_ui *self)
{
    self->task_completion = gtk_entry_completion_new();
    self->task_model = gtk_list_store_new(1, G_TYPE_STRING);
    
    gtk_entry_completion_set_text_column(self->task_completion, 0);
    gtk_entry_set_completion(GTK_ENTRY(self->task_entry), self->task_completion);
    gtk_entry_completion_set_model(self->task_completion, GTK_TREE_MODEL(self->task_model));
}

void
tickety_ui_current_task_new(tickety_ui *self)
{
    GtkWidget *task_box;

    self->task_frame = gtk_frame_new("I'm working on:");
    gtk_frame_set_label_align(GTK_FRAME(self->task_frame), 0.5, 0.5);
    self->task_entry = gtk_entry_new_with_max_length(TICKETY_TASK_NAME_MAX_CHARS);

    task_box = gtk_hbox_new(FALSE, 0);
    gtk_container_set_border_width(GTK_CONTAINER(task_box), 10);

    g_signal_connect(G_OBJECT(self->task_entry), 
		     "activate", 
		     G_CALLBACK(tickety_ui_current_task_start_callback), 
		     self);

    gtk_box_pack_start(GTK_BOX(task_box), self->task_entry, TRUE, TRUE, 5);
    gtk_container_add(GTK_CONTAINER(self->task_frame), task_box);
}

void
tickety_ui_current_task_start(tickety_ui *self)
{

    if(NULL != self->current_task)
    {
	tickety_ui_current_task_stop(self);
    }

    self->current_task = tickety_task_new((char *)gtk_entry_get_text(GTK_ENTRY(self->task_entry)));
    tickety_task_start(self->current_task);

    gtk_button_set_label(GTK_BUTTON(self->timer_button), "Stop");
    gtk_button_set_image(GTK_BUTTON(self->timer_button), GTK_STOCK_MEDIA_STOP_IMAGE);

    gtk_label_set_text(GTK_LABEL(self->message), "Timer started");
    gtk_widget_grab_focus(self->timer_button);
}

void 
tickety_ui_current_task_start_callback(GtkWidget *widget, gpointer data)
{
    tickety_ui *self;
    self = (tickety_ui *)data;
    tickety_ui_current_task_start(self);
}

void
tickety_ui_current_task_stop(tickety_ui *self)
{
    tickety_task_stop(self->current_task);
    tickety_task_destroy(self->current_task);
    self->current_task = NULL;

    gtk_button_set_label(GTK_BUTTON(self->timer_button), "Start");
    gtk_button_set_image(GTK_BUTTON(self->timer_button), GTK_STOCK_MEDIA_PLAY_IMAGE);
    gtk_label_set_text(GTK_LABEL(self->message), "Timer stopped");
    gtk_widget_grab_focus(self->task_entry);
}

void 
tickety_ui_main_window_destroy(GtkWidget *widget, gpointer data)
{
    tickety_ui *self;
    self = (tickety_ui *)data;
    tickety_task_stop(self->current_task);

    gtk_main_quit();
}

void 
tickety_ui_main_window_new(tickety_ui *self)
{
    self->main_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    g_signal_connect(G_OBJECT(self->main_window), 
		     "destroy",
		     G_CALLBACK(tickety_ui_main_window_destroy),
		     self);
    gtk_container_set_border_width(GTK_CONTAINER(self->main_window), 10);

    self->root = gtk_vbox_new(FALSE, 0);
    gtk_container_add(GTK_CONTAINER(self->main_window), self->root);
}

void 
tickety_ui_message_label_new(tickety_ui *self)
{
    self->message = gtk_label_new("Let's get to work!");
}

gboolean 
tickety_ui_message_update_elapsed_time(gpointer data)
{
    char elapsed[25];
    gchar msg[255];
    time_t now;
    tickety_ui *self;

    self = (tickety_ui *)data;
    if(NULL != self->current_task)
    {
	time(&now);
	tickety_format_elapsed_time(elapsed, self->current_task->start_time, now);
	sprintf(msg, "Elapsed: %s", elapsed);
	gtk_label_set_text(GTK_LABEL(self->message), msg);
    }
 
    return TRUE;
}

void
tickety_ui_task_model_add_task(void *data, char *task_name)
{
    tickety_ui *self;
    GtkTreeIter iter;

    self = data;
    gtk_list_store_append(self->task_model, &iter);
    gtk_list_store_set(self->task_model, &iter, 0, task_name, -1);
}

void 
tickety_ui_timer_button_click(GtkWidget *widget, gpointer data)
{
    tickety_ui *self;
    self = (tickety_ui *)data;
    if(NULL == self->current_task)
    {
	tickety_ui_current_task_start(self);
    }
    else
    {
	tickety_ui_current_task_stop(self);
    }
}

void 
tickety_ui_timer_button_new(tickety_ui *self)
{
    self->timer_table = gtk_table_new(1, 3, TRUE);
    self->timer_button = gtk_button_new_with_label("Start");
    gtk_table_attach_defaults(GTK_TABLE(self->timer_table), self->timer_button, 1, 2, 0, 1);
    gtk_button_set_image(GTK_BUTTON(self->timer_button), GTK_STOCK_MEDIA_PLAY_IMAGE);
    g_signal_connect(G_OBJECT(self->timer_button),
		     "clicked", 
		     G_CALLBACK(tickety_ui_timer_button_click),
		     self);
}

tickety_ui 
*tickety_ui_new() 
{
    tickety_ui *self;
    self = (tickety_ui *)malloc(sizeof(tickety_ui));

    self->current_task = NULL;
   
    tickety_ui_main_window_new(self);
    tickety_ui_current_task_new(self);
    tickety_ui_current_task_completion_new(self);
    tickety_ui_message_label_new(self);
    tickety_ui_timer_button_new(self);

    gtk_box_pack_start(GTK_BOX(self->root), self->task_frame, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(self->root), self->timer_table, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(self->root), self->message, TRUE, TRUE, 5);

    g_timeout_add(1000, (GSourceFunc)tickety_ui_message_update_elapsed_time, self);

    return self;
}
