/**
* \file			        number_change.c
* \author			Sébastien Le Maire
* \version			1.0
* \date				21 Mars 2017
*/

#include <string.h>
#include "number.h"

void				number_set_int(char *this, int64_t number);
uint64_t			number_length_int(int64_t number);

t_number			*number_change_int(t_number *this,
						   int64_t number)
{
  uint64_t			i = number_length_int(number);
  uint64_t			capacity = ((this->_capacity < i) ?
					    (i - this->_capacity) : 0);

  if (capacity)
    if (!number_resize(this, this->_capacity + capacity))
      return (NULL);
  this->_sign = CAST_BOOL(number >= 0);
  this->_length = i;
  number_set_int(number_unit(this), number);
  this->_data[this->_length + 1] = '\0';
  return (this);
}

t_number			*number_change_string(t_number *this,
						      char const *number)
{
  uint64_t			i;
  uint64_t			capacity;

  this->_sign = CAST_BOOL(number[0] != '-');
  number += number_isNeg(this);
  for (i = 0;(number[i] && IS_NUMBER(number[i])); ++i);
  if ((capacity = (this->_capacity < i) ? (i - this->_capacity) : 0))
    if (!number_resize(this, this->_capacity + capacity))
      return (NULL);
  this->_length = i;
  (void)strncpy(this->_data + 1, number, i);
  this->_data[this->_length + 1] = '\0';
  return (this);
}

t_number			*number_change(t_number *this,
					       t_number_type const type,
					       uint64_t number)
{
  switch (type)
    {
    case NUMBER_INT:
      return (number_change_int(this, (int64_t)number));
      break;
    case NUMBER_STRING:
      return (number_change_string(this, (char const *)number));
      break;
    case NUMBER_UNDEFINED:
    default:
      *this = _NUMBER_INIT_;
      break;
    }
  return (NULL);
}
