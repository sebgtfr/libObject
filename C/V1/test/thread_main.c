
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "thread.h"
#include "mutex.h"

void            *set42(void *a)
{
    mutex_lockByID(0);
    *(int *)a = 42;
    mutex_unlockByID(0);
    return NULL;
}

int				main(void)
{
    t_thread    *tInt42 = thread_newObject(sizeof(int), &set42);
    int         *int42;
    t_mutex     mutex;

    mutex_init(1);
    mutex_ctor(&mutex);
    mutex_lock(&mutex);
    thread_run(tInt42, NULL);
    thread_join(tInt42);
    mutex_unlock(&mutex);
    int42 = thread_getObject(tInt42);
    printf("int42 = %d\n", *int42);
    free(tInt42);
    mutex_quit();
    return (EXIT_SUCCESS);
}
