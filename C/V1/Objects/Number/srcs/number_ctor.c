/**
* \file			        number_ctor.c
* \author			Sébastien Le Maire
* \version			1.0
* \date				07 Mars 2017
*/

#include "number.h"

t_bool				number_ctor(t_number *this,
					    t_number_type const type,
					    uint64_t number)
{
  *this = _NUMBER_INIT_;
  return (CAST_BOOL(number_assign(this, type, number)));
}
