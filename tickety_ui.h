#ifndef _TICKETY_UI_H
#define	_TICKETY_UI_H

#include <gtk/gtk.h>
#include <time.h>
#include <stdlib.h>

#define TIME_ZERO 0
#define TICKETY_TASK_NAME_MAX_CHARS 255
#define GTK_STOCK_MEDIA_STOP_IMAGE gtk_image_new_from_stock(GTK_STOCK_MEDIA_STOP, GTK_ICON_SIZE_BUTTON)
#define GTK_STOCK_MEDIA_PLAY_IMAGE gtk_image_new_from_stock(GTK_STOCK_MEDIA_PLAY, GTK_ICON_SIZE_BUTTON)

struct _tickety_ui {
    GtkWidget *message;
    time_t start_time;
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
tickety_ui_timer_button_click(GtkWidget *widget, gpointer data);

void 
tickety_ui_timer_button_new(tickety_ui *self);

tickety_ui 
*tickety_ui_new();

#endif	/* _TICKETY_UI_H */