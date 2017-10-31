/**
* \file				timer_setFrequency.c
* \author			Sébastien Le Maire
* \version			1.0
* \date				27 Février 2017
*/

#include "timer.h"

void				timer_setFrequency(t_timer *this,
						   uint32_t const frequency)
{
  this->_frequency = (frequency) ? frequency : 1;
  this->_change = true;
}
