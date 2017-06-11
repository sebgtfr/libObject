/**
* \file			        number_copy.c
* \author			Sébastien Le Maire
* \version			1.0
* \date				20 Mars 2017
*/

#include <string.h>
#include "number.h"

t_bool				number_copy(t_number *this,
					    t_number const *number)
{
  if (number_resize(this, number->_length))
    {
      (void)strncpy(this->_data + 1, number->_data + 1, this->_length);
      this->_length = number->_length;
      this->_data[this->_length + 1] = '\0';
      this->_sign = number->_sign;
      return (true);
    }
  return (false);
}
