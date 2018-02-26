/**
* \file			        number_integer.c
* \author			Sébastien Le Maire
* \version			1.0
* \date				23 Mars 2017
*/

#include "number.h"

int64_t				number_integer(t_number const *this)
{
  int64_t			num = 0;

  if (this->_length <= g_numberMaxLenghtInt)
    {
      char const		*digit = (this->_data +
					  CAST_BOOL(this->_data[0] == '-'));
      uint8_t			i = 0;

      while ((i++ < this->_length))
	num = (num * 10) + NUMBER_TO_INT(*(digit++));
    }
  return ((number_isNeg(this) ? -num : num));
}
