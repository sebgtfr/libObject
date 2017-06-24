/**
* \file				string_trim.c
* \author			Sébastien Le Maire
* \version			1.0
* \date				02 Février 2017
*/

#include "mystring.h"

t_bool				string_trim(t_string *this)
{
  uint64_t			trimBegin = 0;
  uint64_t			trimEnd = this->_length - 1;

  while ((this->_data[trimBegin]) && ((this->_data[trimBegin] == ' ') ||
				      (this->_data[trimBegin] == '\t')))
    ++trimBegin;
  while ((trimEnd > 0) && ((this->_data[trimEnd] == ' ') ||
			   (this->_data[trimEnd] == '\t')))
    --trimEnd;
  ++trimEnd;
  this->_data[trimEnd] = '\0';
  this->_length = trimEnd;
  if (trimBegin)
    string_shift(this, trimBegin);
  return (true);
}
