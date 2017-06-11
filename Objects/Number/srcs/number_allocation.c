/**
* \file			        number_allocation.c
* \author			Sébastien Le Maire
* \version			1.0
* \date				23 Mars 2017
*/

#include <stdlib.h>
#include "number.h"

t_number			*number_new(void)
{
  t_number			*new;

  if ((new = malloc(sizeof(*new))))
    *new = _NUMBER_INIT_;
  return (new);
}

void				number_delete(t_number *this)
{
  number_dtor(this);
  free(this);
}

t_bool				number_resize(t_number *this, uint64_t const size)
{
  if (size && (this->_capacity != (size)) &&
      (this->_data = realloc(this->_data, sizeof(char) * (size + 2))))
    {
      this->_capacity = size;
      this->_data[0] = '-';
      this->_data[this->_capacity] = '\0';
      return (true);
    }
  return (CAST_BOOL(this->_data));
}
