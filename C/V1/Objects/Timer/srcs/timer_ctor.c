/**
* \file				timer_ctor.c
* \author			Sébastien Le Maire
* \version			1.0
* \date				27 Février 2017
*/

#include "timer.h"

t_bool				timer_ctor(t_timer *this,
					   uint32_t const frequency)
{
  this->_frequency = (frequency) ? frequency : 1;
  this->_ticks = (1000000000L / this->_frequency);
  this->_oldFrequency = this->_frequency;
  this->_countTicks = 0;
  this->_outTicks = 0;
  this->_change = 0;
  return (CAST_BOOL(clock_gettime(CLOCK_MONOTONIC, &this->_old) != -1));
}
