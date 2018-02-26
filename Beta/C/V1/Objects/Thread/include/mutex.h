/**
* \file				mutex.h
* \author			Sébastien Le Maire
* \version			1.0
* \date				30 Janvier 2018
*/

#ifndef MUTEX_H_
# define MUTEX_H_

# include <pthread.h>
# include "bool.h"
# include "vector.h"

typedef pthread_mutex_t         t_mutex;

inline void                     mutex_ctor(t_mutex *mutex)
{
    *mutex = (t_mutex)PTHREAD_MUTEX_INITIALIZER;
};

inline t_bool                   mutex_lock(t_mutex *mutex)
{
    return CAST_BOOL(!pthread_mutex_lock(mutex));
};

inline t_bool                   mutex_unlock(t_mutex *mutex)
{
    return CAST_BOOL(!pthread_mutex_unlock(mutex));
};

extern t_vector                 g_mutexes;

extern void                     mutex_init(uint64_t const nb_mutexes);

inline void                     mutex_quit(void)
{
    vector_dtor(&g_mutexes, NULL);
};

inline t_bool                   mutex_lockByID(uint64_t const id)
{
    return (g_mutexes._length > id) ?
        mutex_lock(VECTOR_AT(&g_mutexes, id)) : false;
};

inline t_bool                   mutex_unlockByID(uint64_t const id)
{
    return (g_mutexes._length > id) ?
        mutex_unlock(VECTOR_AT(&g_mutexes, id)) : true;
};

#endif /* !MUTEX_H_ */
