#include "tickety_ui.h"

typedef struct _completion
{
    char *task_name;
} completion;

static completion completions[] = {
    { "stuff" },
    { "programming" },
    { "goofing off" },
    { "fixing bugs" },
    { "sitting idle" }
};

void
tickety_ui_current_task_completion_new(tickety_ui *self)
{
    completion *c;
    GtkTreeIter iter;

    self->task_completion = gtk_entry_completion_new();
    self->task_model = gtk_list_store_new(1, G_TYPE_STRING);

    for(c = completions; c && c->task_name; c++)
    {
	gtk_list_store_append(self->task_model, &iter);
	gtk_list_store_set(self->task_model, &iter, 0, c->task_name, -1);
    }

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

    g_signal_connect(G_OBJECT(self->task_entry), "activate", G_CALLBACK(tickety_ui_current_task_start_callback), self);

    gtk_box_pack_start(GTK_BOX(task_box), self->task_entry, TRUE, TRUE, 5);
    gtk_container_add(GTK_CONTAINER(self->task_frame), task_box);
}

void
tickety_ui_current_task_start(tickety_ui *self)
{
    time(&(self->start_time));
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
    gchar elapsed[25];
    tickety_ui_format_elapsed_time(elapsed, self->start_time);
    printf("task '%s' completed in %s\n",
	   gtk_entry_get_text(GTK_ENTRY(self->task_entry)),
	   elapsed);
    
    self->start_time = TIME_ZERO;
    gtk_button_set_label(GTK_BUTTON(self->timer_button), "Start");
    gtk_button_set_image(GTK_BUTTON(self->timer_button), GTK_STOCK_MEDIA_PLAY_IMAGE);
    gtk_label_set_text(GTK_LABEL(self->message), "Timer stopped");
    gtk_widget_grab_focus(self->task_entry);
}

void
tickety_ui_format_elapsed_time(gchar *elapsed, time_t start_time)
{
    time_t now;
    int time_diff;
    int hours;
    int minutes;
    int seconds;
    time_diff = (int)(time(&now) - start_time);
    hours = time_diff / 3600;
    minutes = (time_diff - hours * 3600) / 60;
    seconds = time_diff - hours * 3600 - minutes * 60;
    sprintf(elapsed, "%02d:%02d:%02d", hours, minutes, seconds);
}

void 
tickety_ui_main_window_destroy(GtkWidget *widget, gpointer data)
{
    gtk_main_quit();
}

void 
tickety_ui_main_window_new(tickety_ui *self)
{
    self->main_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    g_signal_connect(G_OBJECT(self->main_window), "destroy", G_CALLBACK(tickety_ui_main_window_destroy), NULL);
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
    gchar elapsed[25];
    gchar msg[255];
    tickety_ui *self;
    self = (tickety_ui *)data;

    if(TIME_ZERO < self->start_time)
    {
	tickety_ui_format_elapsed_time(elapsed, self->start_time);
	sprintf(msg, "Elapsed: %s", elapsed);
	gtk_label_set_text(GTK_LABEL(self->message), msg);
    }

    return TRUE;
}

void 
tickety_ui_timer_button_click(GtkWidget *widget, gpointer data)
{
    tickety_ui *self;
    self = (tickety_ui *)data;
    if(TIME_ZERO == self->start_time)
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
    g_signal_connect(G_OBJECT(self->timer_button), "clicked", G_CALLBACK(tickety_ui_timer_button_click), self);
}

tickety_ui 
*tickety_ui_new() 
{
    tickety_ui *self;
    self = (tickety_ui *)malloc(sizeof(tickety_ui));
   
    self->start_time = TIME_ZERO;

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