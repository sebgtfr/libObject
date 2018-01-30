/**
* \file				timer.h
* \author			Sébastien Le Maire
* \version			1.0
* \date				27 Février 2017
*/

#ifndef TIMER_H_
# define TIMER_H_

# include <time.h>
# include "bool.h"

typedef struct			s_timer
{
  uint32_t			_frequency;
  uint32_t			_oldFrequency;
  uint32_t			_ticks;
  uint32_t			_countTicks;
  uint32_t			_outTicks;
  t_bool			_change;
  struct timespec		_old;
  struct timespec		_now;
}				t_timer;

/*
** Timer's functions
** canonical form
*/
t_bool				timer_ctor(t_timer *this,
					   uint32_t const frequency);

/*
** Setter
*/
void				timer_setFrequency(t_timer *this,
						   uint32_t const frequency);

/*
** Methods
*/
t_bool				timer_checkTicks(t_timer *this);

#endif /* !TIMER_H_ */
