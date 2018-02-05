/**
* \file			        number_sum.c
* \author			Sébastien Le Maire
* \version			1.0
* \date				18 Mars 2017
*/

#include <string.h>
#include "number.h"

char				*number_init_res(t_number *res, uint64_t const size,
						 t_bool const sign);

static void	       		number_sumGetResSign(t_number const *a,
						     t_number const *b,
						     t_number const *greater[2])
{
  t_bool			aIsGreater;

  if ((a->_length) == (b->_length))
    {
      int			res = strcmp(number_num_abs(a),
					     number_num_abs(b));

      aIsGreater = ((a->_sign != b->_sign) && (!res)) ? a->_sign : CAST_BOOL(res >= 0);
    }
  else
    aIsGreater = CAST_BOOL(a->_length > b->_length);
  if (aIsGreater)
    {
      greater[0] = a;
      greater[1] = b;
    }
  else
    {
      greater[0] = b;
      greater[1] = a;
    }
}

static t_number			*number_add(t_number const *a, t_number const *b,
					    t_number *res)
{
  char const			*numA = number_unit(a);
  char const			*numB = number_unit(b);
  char				*numRes;
  uint64_t			len = 0;
  uint8_t			retenu = 0;

  if (!(numRes = number_init_res(res, ((a->_length > b->_length) ?
				       (a->_length + 1)
				       : (b->_length + 1)), a->_sign)))
    return (NULL);
  while (len < res->_length)
    {
      uint8_t			addRes = retenu;

      if (len < a->_length)
	addRes += NUMBER_TO_INT(*(numA--));
      if (len < b->_length)
	addRes += NUMBER_TO_INT(*(numB--));
      retenu = addRes / 10;
      *numRes = NUMBER_TO_CHAR(addRes % 10);
      --numRes;
      ++len;
    }
  number_delUselessZero(res);
  return (res);
}

t_number			*number_sub(t_number const *a, t_number const *b,
					    t_number *res)
{
  char const			*numA = number_unit(a);
  char const			*numB = number_unit(b);
  char				*numRes;
  uint64_t			len = 0;
  uint8_t			retenu = 0;

  if (!(numRes = number_init_res(res, ((a->_length > b->_length) ?
				       (a->_length + 1)
				       : (b->_length + 1)), a->_sign)))
    return (NULL);
  while (len < res->_length)
    {
      int8_t			digitA = -retenu;
      int8_t			digitB = 0;

      if (len < a->_length)
	digitA += NUMBER_TO_INT(*(numA--));
      if (len < b->_length)
	digitB += NUMBER_TO_INT(*(numB--));
      retenu = (digitA < digitB) ? 1 : 0;
      *numRes = NUMBER_TO_CHAR((digitA + 10 * retenu) - digitB);
      --numRes;
      ++len;
    }
  number_delUselessZero(res);
  return (res);
}

t_number			*number_addition(t_number const *a,
						 t_number const *b,
						 t_number *res)
{
  t_number const		*greater[2];

  if (a && b && res)
    {
      number_sumGetResSign(a, b, greater);
      return (((a->_sign == b->_sign) ? number_add(greater[0], greater[1], res) :
	       number_sub(greater[0], greater[1], res)));
    }
  return (NULL);
}

t_number       			*number_subtraction(t_number const *a,
						    t_number *b,
						    t_number *res)
{
  t_number			*ret;

  number_reverseSign(b);
  ret = number_addition(a, b, res);
  number_reverseSign(b);
  return (ret);
}
