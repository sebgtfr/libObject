/**
* \file			        buffer_concat.c
* \author			Sébastien Le Maire
* \version			1.0
* \date				07 Mars 2017
*/

#include <string.h>
#include "buffer.h"

t_bool				buffer_concat(t_buffer *this, void const *data,
					      uint64_t const size)
{
  if (data)
    {
      uint64_t			capacity = this->_capacity - this->_length;

      if ((capacity = (capacity < size) ? (size - capacity) : 0))
	if (!(buffer_add_page_memory(this, capacity)))
	  return (false);
      (void)memcpy(BUFFER_AT(this, this->_length), data, size);
      this->_length += size;
      ((uint8_t *)this->_data)[this->_length] = 0;
    }
  return (true);
}
