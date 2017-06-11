/**
* \file			        buffer_read.c
* \author			Sébastien Le Maire
* \version			1.0
* \date				07 Mars 2017
*/

#include <unistd.h>
#include "buffer.h"

t_bool				buffer_print(t_buffer *this, int const fd)
{
  if (this->_data)
    return (!(write(fd, this->_data, this->_length) < 0));
  return (true);
}
