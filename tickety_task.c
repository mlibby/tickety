int
tickety_task_destroy(tickety_task *self);
{
    free(self);
}

tickety_task 
*tickety_task_new(char *name, time_t start);
{
    tickety_task *self;

    self = (tickety_task *)malloc(sizeof(tickety_task));
    if(NULL != self)
    {
	strcpy(self->name, name);
	self->start = start;
	return self;
    }
    return NULL;
}

