#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "timer.h"

int				main(void)
{
  t_timer			time;
  uint32_t			chrono = 0;

  if (timer_ctor(&time, 0))
    {
      while (chrono < 10)
	{
	  if (timer_checkTicks(&time))
	    {
	      printf("%u\n", ++chrono);
	    }
	}
    }
  return (EXIT_SUCCESS);
}
