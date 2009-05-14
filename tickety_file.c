#include "tickety_file.h"

int
tickety_file_read_task_file(void (*callback)(void*, char*), void *data)
{
    FILE *task_file;
    char task_line[TICKETY_TASK_NAME_MAX_CHARS];
    char task_file_name[64];
    int line_length;

    strcpy(task_file_name, "task_data.txt");
    task_file = fopen(task_file_name, "r");
    if(NULL == task_file)
    {
	fprintf(stderr, "Error opening task file '%s'\n", task_file_name);
	return TICKETY_FILE_ERROR_READING_TASK_FILE;
    }

    while(NULL != fgets(task_line, sizeof(task_line), task_file))
    {
	line_length = strlen(task_line);
	if(0 < line_length && line_length <= TICKETY_TASK_NAME_MAX_CHARS)
	{
	    task_line[line_length - 2] = '\0';
	    (*callback)(data, task_line);
	}
    }

    return TICKETY_FILE_SUCCESS_READING_TASK_FILE;
}
