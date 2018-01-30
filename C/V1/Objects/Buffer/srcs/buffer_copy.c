/**
* \file			        buffer_copy.c
* \author			Sébastien Le Maire
* \version			1.0
* \date				07 Mars 2017
*/

#include "buffer.h"

t_bool				buffer_copy(t_buffer *this,
					    t_buffer const *copy)
{
  if (copy && copy->_data)
    return (CAST_BOOL(buffer_resize(this, copy->_capacity) &&
		      buffer_change(this, copy->_data, copy->_length)));
  else
    *this = _INIT_BUFFER_;
  return (true);
}
