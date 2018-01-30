/**
* \file			        number_print.c
* \author			Sébastien Le Maire
* \version			1.0
* \date				11 Mars 2017
*/

#include <unistd.h>
#include "number.h"

void				number_print(t_number *this, int const fd)
{
  if (this->_data && this->_length)
    (void)write(fd, NUMBER_DATA(this), this->_length + NUMBER_ISNEG(this));
}
