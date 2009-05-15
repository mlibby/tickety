#ifndef _TICKETY_TASK_H
#define _TICKETY_TASK_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tickety_common.h"

#define TICKETY_TASK_NAME_MAX_CHARS 255

/*
* This library is here to help keep "model" data out of the view. It
* is still a to-do item to encapsulate task switching and other task
* management functions in this library.
*/

struct _tickety_task {
    char name[TICKETY_TASK_NAME_MAX_CHARS];
    time_t start;
};
typedef struct _tickety_task tickety_task;

int
tickety_task_destroy(tickety_task *self);

tickety_task 
*tickety_task_new(char *name, time_t start);

#endif /* _TICKETY_TASK_H */
