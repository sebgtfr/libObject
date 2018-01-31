/**
* \file				mutex.c
* \author			Sébastien Le Maire
* \version			1.0
* \date				30 Janvier 2018
*/

#include "mutex.h"

t_vector                        g_mutexes = _VECTOR_CTOR_(sizeof(t_mutex));

extern void                     mutex_ctor(t_mutex *mutex);
extern t_bool                   mutex_lock(t_mutex *mutex);
extern t_bool                   mutex_unlock(t_mutex *mutex);

static inline void              mutex_init_foreach(void *mutex)
{
    mutex_ctor((t_mutex *)mutex);
}

void                            mutex_init(uint64_t const nb_mutexes)
{
    vector_resize(&g_mutexes, nb_mutexes, NULL);
    vector_foreach(&g_mutexes, &mutex_init_foreach);
}

extern void                     mutex_quit(void);
extern t_bool                   mutex_lockByID(uint64_t const id);
extern t_bool                   mutex_unlockByID(uint64_t const id);
