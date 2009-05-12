#ifndef _TICKETY_H
#define	_TICKETY_H

#include <gtk/gtk.h>
#include <time.h>

#define TIME_ZERO 0
#define TICKETY_TASK_NAME_MAX_CHARS 255
#define GTK_STOCK_MEDIA_STOP_IMAGE gtk_image_new_from_stock(GTK_STOCK_MEDIA_STOP, GTK_ICON_SIZE_BUTTON)
#define GTK_STOCK_MEDIA_PLAY_IMAGE gtk_image_new_from_stock(GTK_STOCK_MEDIA_PLAY, GTK_ICON_SIZE_BUTTON)

struct _tickety {
    time_t start_time;
    GtkWidget *window;
    GtkWidget *root;
    GtkWidget *task_box;
    GtkWidget *task_entry;
    GtkWidget *timer;
    GtkWidget *message;
};
typedef struct _tickety tickety;

#endif	/* _TICKETY_H */
