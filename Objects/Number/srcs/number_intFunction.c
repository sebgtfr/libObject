/**
* \file			        number_intFunction.c
* \author			Sébastien Le Maire
* \version			1.0
* \date				10 Mars 2017
*/

#include "number.h"

uint64_t			number_length_int(int64_t number)
{
  uint64_t			length = 0;

  while (number)
    {
      ++length;
      number /= 10;
    }
  return ((length) ? length : 1);
}

void				number_set_int(char *this, int64_t number)
{
  if (!number)
    *this = '0';
  while (number)
    {
      *this = NUMBER_TO_CHAR(NUMBER_ABS(number % 10));
      number /= 10;
      --this;
    }
}
