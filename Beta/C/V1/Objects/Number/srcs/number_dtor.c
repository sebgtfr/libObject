/**
* \file			        number_dtor.c
* \author			Sébastien Le Maire
* \version			1.0
* \date				10 Mars 2017
*/

#include <stdlib.h>
#include "number.h"

void				number_dtor(t_number *this)
{
  if (this->_data)
    free(this->_data);
  *this = _NUMBER_INIT_;
}
