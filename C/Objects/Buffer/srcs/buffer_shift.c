/**
* \file			        buffer_shift.c
* \author			Sébastien Le Maire
* \version			1.0
* \date				07 Mars 2017
*/

#include <string.h>
#include "buffer.h"

void				buffer_shift(t_buffer *this, uint64_t const shift)
{
  if (shift && this->_data)
    {
      if (shift < this->_length)
	{
	  (void)memmove(this->_data, BUFFER_AT(this, shift),
			this->_length - shift);
	  this->_length -= shift;
	  ((uint8_t *)this->_data)[this->_length] = 0;
	}
      else
        buffer_reset(this);
    }
}
