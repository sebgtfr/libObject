/**
* \file			        number_init_res.c
* \author			Sébastien Le Maire
* \version			1.0
* \date				23 Mars 2017
*/

#include "number.h"

char			*number_init_res(t_number *res, uint64_t const size,
					 t_bool const sign)
{
  if (number_resize(res, size))
    {
      res->_sign = sign;
      res->_length = size;
      return (number_unit(res));
    }
  return ((char *)g_nullptr);
}
