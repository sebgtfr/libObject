/**
* \file			        number_assign.c
* \author			Sébastien Le Maire
* \version			1.0
* \date				10 Mars 2017
*/

#include <string.h>
#include "number.h"

void				number_set_int(char *this, int64_t number);
uint64_t			number_length_int(int64_t number);

t_number			*number_assign_int(t_number *this,
						   int64_t number)
{
  uint64_t			i = number_length_int(number);

  this->_sign = CAST_BOOL(number >= 0);
  if (number_resize(this, i))
    {
      this->_length = i;
      number_set_int(NUMBER_UNIT(this), number);
      this->_data[this->_length + 1] = '\0';
      return (this);
    }
  return (NULL);
}

t_number			*number_assign_string(t_number *this,
						      char const *number)
{
  uint64_t			i;

  this->_sign = CAST_BOOL(number[0] != '-');
  number += NUMBER_ISNEG(this);
  for (i = 0;(number[i] && IS_NUMBER(number[i])); ++i);
  if (number_resize(this, i))
    {
      this->_length = i;
      (void)strncpy(this->_data + 1, number, i);
      this->_data[this->_length + 1] = '\0';
      return (this);
    }
  return (NULL);
}

t_number			*number_assign(t_number *this,
					       t_number_type const type,
					       uint64_t number)
{
  switch (type)
    {
    case NUMBER_INT:
      return (number_assign_int(this, (int64_t)number));
      break;
    case NUMBER_STRING:
      return (number_assign_string(this, (char const *)number));
      break;
    case NUMBER_UNDEFINED:
    default:
      *this = _NUMBER_INIT_;
      break;
    }
  return (false);
}
