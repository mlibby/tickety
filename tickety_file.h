#ifndef _TICKETY_FILE_H
#define	_TICKETY_FILE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tickety_common.h"

#define TICKETY_FILE_SUCCESS_READING_TASK_FILE 0
#define TICKETY_FILE_ERROR_READING_TASK_FILE 1

int
tickety_file_read_task_file(void (*callback)(void*, char*), void *data);

#endif	/* _TICKETY_FILE_H */
