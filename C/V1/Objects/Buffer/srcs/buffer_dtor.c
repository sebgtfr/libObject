/**
* \file			        buffer_dtor.c
* \author			Sébastien Le Maire
* \version			1.0
* \date				07 Mars 2017
*/

#include <stdlib.h>
#include "buffer.h"

void				buffer_dtor(t_buffer *this)
{
  if (this->_data)
    free(this->_data);
  *this = _INIT_BUFFER_;
}
