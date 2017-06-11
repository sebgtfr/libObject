/**
* \file			        buffer_assign.c
* \author			Sébastien Le Maire
* \version			1.0
* \date				07 Mars 2017
*/

#include <string.h>
#include "buffer.h"

t_bool				buffer_assign(t_buffer *this, void const *data,
					      uint64_t const size)
{
  if (data)
    {
      if (!buffer_resize(this, size))
	return (false);
      (void)memcpy(this->_data, data, size);
      this->_length = size;
      ((uint8_t *)this->_data)[this->_length] = 0;
    }
  else
    buffer_dtor(this);
  return (true);
}
