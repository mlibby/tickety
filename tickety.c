#include "tickety.h"

int 
main(int argc, char *argv[])
{
    tickety_ui *tui;

    gtk_init(&argc, &argv);

    tui = tickety_ui_new();
    gtk_widget_show_all(tui->main_window);

    gtk_main();
    return 0;
}
