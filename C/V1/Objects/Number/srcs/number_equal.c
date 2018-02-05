/**
* \file			        number_equal.c
* \author			Sébastien Le Maire
* \version			1.0
* \date				18 Mars 2017
*/

#include <string.h>
#include "number.h"

t_bool				number_equal(t_number const *this,
					     t_number const *num)
{
  return ((this->_sign == num->_sign) ?
	  (CAST_BOOL(!strcmp(number_data(this), number_data(num)))) :
	  (false));
}
