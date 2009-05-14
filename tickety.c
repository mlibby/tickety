#include "tickety.h"
#include "tickety_file.h"

int 
main(int argc, char *argv[])
{
    tickety_ui *tui;
    int file_result;

    gtk_init(&argc, &argv);

    tui = tickety_ui_new();
    file_result = tickety_file_read_task_file(&tickety_ui_task_model_add_task, tui);

    if(TICKETY_FILE_SUCCESS_READING_TASK_FILE == file_result)
    {
	gtk_widget_show_all(tui->main_window);
	gtk_main();
    }

    return 0;
}
