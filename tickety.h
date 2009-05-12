#ifndef _TICKETY_H
#define	_TICKETY_H

#include <gtk/gtk.h>
#include <time.h>

#define TIME_ZERO 0
#define TICKETY_TASK_NAME_MAX_CHARS 255
#define GTK_STOCK_MEDIA_STOP_IMAGE gtk_image_new_from_stock(GTK_STOCK_MEDIA_STOP, GTK_ICON_SIZE_BUTTON)
#define GTK_STOCK_MEDIA_PLAY_IMAGE gtk_image_new_from_stock(GTK_STOCK_MEDIA_PLAY, GTK_ICON_SIZE_BUTTON)

struct _tickety {
    GtkWidget *message;
    time_t start_time;
    GtkEntryCompletion *task_completion;
    GtkWidget *task_entry;
    GtkWidget *task_frame;
    GtkListStore *task_model;
    GtkWidget *timer_table;
    GtkWidget *timer_button;
    GtkWidget *root;
    GtkWidget *window;
};

typedef struct _tickety tickety;

void
tickety_current_task_new(tickety *self);

void
tickety_current_task_start(tickety *self);

void
tickety_current_task_start_callback(GtkWidget *widget, gpointer data);

void
tickety_current_task_stop(tickety *self);

void
tickety_format_elapsed_time(gchar *elapsed, time_t start_time);

void 
tickety_main_window_destroy(GtkWidget *widget, gpointer data);

void 
tickety_main_window_new(tickety *self);

void 
tickety_message_label_new(tickety *self);

gboolean 
tickety_message_update_elapsed_time(gpointer data);

void 
tickety_timer_button_click(GtkWidget *widget, gpointer data);

void 
tickety_timer_button_new(tickety *self);

#endif	/* _TICKETY_H */
