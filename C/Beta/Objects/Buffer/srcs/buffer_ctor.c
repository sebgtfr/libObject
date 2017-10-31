/**
* \file			        buffer_ctor.c
* \author			Sébastien Le Maire
* \version			1.0
* \date				07 Mars 2017
*/

#include "buffer.h"

t_bool				buffer_ctor(t_buffer *this,
					      uint64_t const capacity)
{
  *this = _INIT_BUFFER_;
  return ((capacity) ? buffer_resize(this, capacity) : true);
}
