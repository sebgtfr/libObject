/**
* \file			        number_delUselessZero.c
* \author			Sébastien Le Maire
* \version			1.0
* \date				20 Mars 2017
*/

#include <string.h>
#include "number.h"

void				number_delUselessZero(t_number *this)
{
  if (this->_data)
    {
      uint64_t			shift = 0;

      while ((shift < this->_length) && (this->_data[shift + 1] == '0'))
	++shift;
      if (shift < this->_length)
	{
	  (void)memmove(this->_data + 1, (void *)this->_data + 1 + shift,
			this->_length - shift);
	  this->_length -= shift;
	}
      else
	number_change_string(this, "0\0");
      this->_data[this->_length + 1] = '\0';
    }
}
