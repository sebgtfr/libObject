/**
* \file				thread.h
* \author			Sébastien Le Maire
* \version			1.0
* \date				30 Janvier 2018
*/

#ifndef THREAD_H_
# define THREAD_H_

# include <pthread.h>
# include "bool.h"

typedef void                    *(*t_thread_routine)(void *);

typedef struct                  s_thread
{
    pthread_t                   _thread;
    t_thread_routine            _routine;
    void                        *_return;
    char                        _data[0];
}                               t_thread;

void                            thread_ctor(t_thread *this,
                                            t_thread_routine routine);
t_thread                        *thread_newObject(uint64_t const sizeObject,
                                                  t_thread_routine routine);
t_bool                          thread_run(t_thread *this,
                                           t_thread_routine routine);

static inline t_bool            thread_join(t_thread *this)
{
    return CAST_BOOL(pthread_join(this->_thread, &this->_return));
};

static inline void              thread_return(void *ret)
{
    pthread_exit(ret);
};

static inline void              *thread_getReturn(t_thread const *this)
{
    return this->_return;
};

static inline void              *thread_getObject(t_thread const *this)
{
    return (void *)&this->_data;
};

#endif /* !THREAD_H_ */
