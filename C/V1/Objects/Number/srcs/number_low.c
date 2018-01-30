/**
* \file			        number_low.c
* \author			Sébastien Le Maire
* \version			1.0
* \date				18 Mars 2017
*/

#include <string.h>
#include "number.h"

t_bool				number_low(t_number const *this,
					   t_number const *num)
{
  if (this->_sign == num->_sign)
    {
      t_bool			thisIsGreater;

      if (this->_length == num->_length)
	{
	  int			res = strcmp(NUMBER_DATA(this),
					     NUMBER_DATA(num));
	  if (!res)
	    return (false);
	  thisIsGreater = CAST_BOOL(res > 0);
	}
      else
	thisIsGreater = CAST_BOOL(this->_length > num->_length);

      return ((this->_sign) ? (!CAST_BOOL(thisIsGreater)) :
	      (CAST_BOOL(thisIsGreater)));
    }
  return (!this->_sign);
}
