/**
* \file			        buffer_resize.c
* \author			Sébastien Le Maire
* \version			1.0
* \date				07 Mars 2017
*/

#include <stdlib.h>
#include "buffer.h"

t_bool				buffer_resize(t_buffer *this,
					      uint64_t const capacity)
{
  if (!capacity)
    buffer_dtor(this);
  else if (this->_capacity != capacity)
    {
      if (!(this->_data = realloc(this->_data, (capacity + 1))))
	{
	  this->_capacity = 0;
	  this->_length = 0;
	  return (false);
	}
      this->_capacity = capacity;
      if (this->_length > this->_capacity)
	this->_length = this->_capacity;
      ((uint8_t *)this->_data)[this->_length] = 0;
    }
  return (true);
}
