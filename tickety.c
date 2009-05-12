#include "tickety.h"

void
tickety_current_task_new(tickety *self)
{
    GtkWidget *task_box;

    self->task_frame = gtk_frame_new("I'm working on:");
    gtk_frame_set_label_align(GTK_FRAME(self->task_frame), 0.5, 0.5);
    self->task_entry = gtk_entry_new_with_max_length(TICKETY_TASK_NAME_MAX_CHARS);

    task_box = gtk_hbox_new(FALSE, 0);
    gtk_container_set_border_width(GTK_CONTAINER(task_box), 10);

    g_signal_connect(G_OBJECT(self->task_entry), "activate", G_CALLBACK(tickety_current_task_start_callback), self);
    
    gtk_box_pack_start(GTK_BOX(task_box), self->task_entry, TRUE, TRUE, 5);
    gtk_container_add(GTK_CONTAINER(self->task_frame), task_box);
}

void
tickety_current_task_start(tickety *self)
{
    time(&(self->start_time));
    gtk_button_set_label(GTK_BUTTON(self->timer_button), "Stop");
    gtk_button_set_image(GTK_BUTTON(self->timer_button), GTK_STOCK_MEDIA_STOP_IMAGE);
    gtk_label_set_text(GTK_LABEL(self->message), "Timer started");
}

void 
tickety_current_task_start_callback(GtkWidget *widget, gpointer data)
{
    tickety *self;
    self = (tickety *)data;
    tickety_current_task_start(self);
}

void
tickety_current_task_stop(tickety *self)
{
    gchar elapsed[25];
    tickety_format_elapsed_time(elapsed, self->start_time);
    printf("task '%s' completed in %s\n",
	   gtk_entry_get_text(GTK_ENTRY(self->task_entry)),
	   elapsed);
    
    self->start_time = TIME_ZERO;
    gtk_button_set_label(GTK_BUTTON(self->timer_button), "Start");
    gtk_button_set_image(GTK_BUTTON(self->timer_button), GTK_STOCK_MEDIA_PLAY_IMAGE);
    gtk_label_set_text(GTK_LABEL(self->message), "Timer stopped");
}

void
tickety_format_elapsed_time(gchar *elapsed, time_t start_time)
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
tickety_main_window_destroy(GtkWidget *widget, gpointer data)
{
    gtk_main_quit();
}

void 
tickety_main_window_new(tickety *self)
{
    self->window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    g_signal_connect(G_OBJECT(self->window), "destroy", G_CALLBACK(tickety_main_window_destroy), NULL);
    gtk_container_set_border_width(GTK_CONTAINER(self->window), 10);

    self->root = gtk_vbox_new(FALSE, 0);
    gtk_container_add(GTK_CONTAINER(self->window), self->root);
}

void 
tickety_message_label_new(tickety *self)
{
    self->message = gtk_label_new("Let's get to work!");
}

gboolean 
tickety_message_update_elapsed_time(gpointer data)
{
    gchar elapsed[25];
    gchar msg[255];
    tickety *self;
    self = (tickety *)data;

    if(TIME_ZERO < self->start_time)
    {
	tickety_format_elapsed_time(elapsed, self->start_time);
	sprintf(msg, "Elapsed: %s", elapsed);
	gtk_label_set_text(GTK_LABEL(self->message), msg);
    }

    return TRUE;
}

void 
tickety_timer_button_click(GtkWidget *widget, gpointer data)
{
    tickety *self;
    self = (tickety *)data;
    if(TIME_ZERO == self->start_time)
    {
	tickety_current_task_start(self);
    }
    else
    {
	tickety_current_task_stop(self);
    }
}

void 
tickety_timer_button_new(tickety *self)
{
    self->timer_table = gtk_table_new(1, 3, TRUE);
    self->timer_button = gtk_button_new_with_label("Start");
    gtk_table_attach_defaults(GTK_TABLE(self->timer_table), self->timer_button, 1, 2, 0, 1);
    gtk_button_set_image(GTK_BUTTON(self->timer_button), GTK_STOCK_MEDIA_PLAY_IMAGE);
    g_signal_connect(G_OBJECT(self->timer_button), "clicked", G_CALLBACK(tickety_timer_button_click), self);
}

int 
main(int argc, char *argv[])
{
    tickety self;
    
    self.start_time = TIME_ZERO;
    gtk_init(&argc, &argv);

    tickety_main_window_new(&self);
    tickety_current_task_new(&self);
    tickety_message_label_new(&self);
    tickety_timer_button_new(&self);

    gtk_box_pack_start(GTK_BOX(self.root), self.task_frame, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(self.root), self.timer_table, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(self.root), self.message, TRUE, TRUE, 5);

    g_timeout_add(1000, (GSourceFunc)tickety_message_update_elapsed_time, &self);

    gtk_widget_show_all(self.window);
    gtk_main();
    return 0;
}
