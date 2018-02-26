/**
* \file				thread.c
* \author			Sébastien Le Maire
* \version			1.0
* \date				30 Janvier 2018
*/

#include <stdlib.h>
#include "thread.h"

/**
* \brief			Construteur de l'objet t_thread
* \details			Initialise un objet t_thread
* \param this       Référence sur le thread
* \param routine    Routine exécuté par le thread.
* \return			none
*
*/
void                            thread_ctor(t_thread *this,
                                            t_thread_routine routine)
{
    this->_routine = routine;
    this->_return = NULL;
}

t_thread                        *thread_newObject(uint64_t const sizeObject,
                                                  t_thread_routine routine)
{
    t_thread                    *new = malloc(sizeof(t_thread) + sizeObject);

    if (new)
        thread_ctor(new, routine);
    return new;
}

t_bool                          thread_run(t_thread *this,
                                           t_thread_routine routine)
{
    if (routine)
        this->_routine = routine;
    return CAST_BOOL(pthread_create(&this->_thread, NULL,
                                    this->_routine, &this->_data));
}
