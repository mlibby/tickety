/*
 *   Copyright 2009, Michael C. Libby
 *
 *   This file is part of Tickety.
 *
 *   Tickety is free software: you can redistribute it and/or modify it
 *   under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   Tickety is distributed in the hope that it will be useful, but
 *   WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *   General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with Tickety.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "tickety_data.h"

struct _task_names_callback {
    void (*callback)(void*, char*);
    void *object;
};
typedef struct _task_names_callback task_names_callback;

static int
process_task_names(void *data, int column_count, char **column_values, char **column_names){
    task_names_callback *callback;
    callback = (task_names_callback *)data;
    (callback->callback)(callback->object, column_values[0]);
    return 0;
}

void
tickety_data_insert_task(tickety_task *task)
{
    sqlite3 *db;
    char sql_cmd[512];
    char *err_msg = 0;
    int rc;

    printf("insert task: '%s' (%lu-%lu)\n",
	   task->name, 
	   (unsigned long int)task->start_time, 
	   (unsigned long int)task->stop_time);

    rc = sqlite3_open(TICKETY_DATA_FILE_NAME, &db);
    if(rc){
	fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
	sqlite3_close(db);
    }

    sprintf(sql_cmd,
	    "INSERT INTO tasks VALUES (NULL, '%s', %lu, %lu)",
	    task->name,
	    (unsigned long int)task->start_time,
	    (unsigned long int)task->stop_time);

    rc = sqlite3_exec(db, sql_cmd, NULL, NULL, &err_msg);
    if(rc != SQLITE_OK){
	fprintf(stderr, "SQL error: %s\n", err_msg);
	sqlite3_free(err_msg);
    }
    sqlite3_close(db);
}


int
tickety_data_read_task_names(void (*callback)(void*, char*), void *object)
{
    sqlite3 *db;
    char *err_msg = 0;
    int rc;
    task_names_callback *names_callback;

    names_callback = malloc(sizeof(task_names_callback));
    /* TODO: check that malloc worked */

    names_callback->callback = callback;
    names_callback->object = object;

    rc = sqlite3_open(TICKETY_DATA_FILE_NAME, &db);
    if(rc){
	fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
	sqlite3_close(db);
	return TICKETY_DATA_ERROR_READING_TASK_FILE;
    }

    rc = sqlite3_exec(db, "SELECT DISTINCT name FROM tasks", process_task_names, names_callback, &err_msg);
    if(rc != SQLITE_OK){
	fprintf(stderr, "SQL error: %s\n", err_msg);
	sqlite3_free(err_msg);
	return TICKETY_DATA_ERROR_READING_TASK_FILE;
    }

    free(names_callback);
    sqlite3_close(db);
    return TICKETY_DATA_SUCCESS_READING_TASK_FILE;
}
