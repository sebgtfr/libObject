/**
* \file				timer_checkTicks.c
* \author			Sébastien Le Maire
* \version			1.0
* \date				27 Février 2017
*/

#include "timer.h"

static uint64_t			timer_diff_time(t_timer *this)
{
  return ((clock_gettime(CLOCK_MONOTONIC, &this->_now) == -1) ? 0 :
	  (1000000000L * (this->_now.tv_sec - this->_old.tv_sec) +
	   (this->_now.tv_nsec - this->_old.tv_nsec)));
}

t_bool				timer_checkTicks(t_timer *this)
{
  uint32_t			ticks;
  uint64_t			diff;

  ticks = (this->_ticks <= this->_outTicks) ? 0 : (this->_ticks - this->_outTicks);
  if ((diff = timer_diff_time(this)) > ticks)
    {
      this->_countTicks = (this->_countTicks + 1) % this->_oldFrequency;
      if ((this->_change) && (!this->_countTicks))
	{
	  this->_change = false;
	  this->_ticks = (1000000000L / this->_frequency);
	  this->_outTicks = 0;
	  this->_oldFrequency = this->_frequency;
	}
      else
	this->_outTicks = diff - ticks;
      this->_old = this->_now;
      return (true);
    }
  return (false);
}
