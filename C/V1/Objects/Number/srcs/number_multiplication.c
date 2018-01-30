/**
* \file			        number_multiplication.c
* \author			Sébastien Le Maire
* \version			1.0
* \date				23 Mars 2017
*/

#include <stdio.h>

#include <stdlib.h>
#include <string.h>
#include "number.h"

t_number			*number_sub(t_number const *a, t_number const *b,
					    t_number *res);

static void			number_partial_copy(t_number const *this,
						    uint64_t const size,
						    t_number *left,
						    t_number *right)
{
  uint64_t			rightSize;

  if (this->_length <= size)
    {
      *left = _NUMBER_INIT_NULL_;
      rightSize = this->_length;
    }
  else
    {
      uint64_t			leftSize = this->_length - size;

      *left = NUMBER_INIT(true, 0, leftSize, NUMBER_NUM_ABS(this));
      rightSize = size;
    }
  *right = NUMBER_INIT(false, 0, rightSize, NUMBER_UNIT(this) + 1 - rightSize);
  while ((*left->_data == '0') && (left->_length > 1))
    {
      ++left->_data;
      --left->_length;
    }
  while ((*right->_data == '0') && (right->_length > 1))
    {
      ++right->_data;
      --right->_length;
    }
}

static t_number			*number_tenPower(t_number const *this,
						 t_number *res,
						 uint64_t const power)
{
  if (NUMBER_ISZERO(this))
    return (number_assign_string(res, "0\0"));
  if (number_resize(res, this->_length + power))
    {
      char			*digit = NUMBER_NUM_ABS(res);

      res->_length = 0;
      while (res->_length < res->_capacity)
	{
	  *digit = (res->_length < this->_length) ? this->_data[res->_length + 1] : '0';
	  ++digit;
	  ++res->_length;
	}
      res->_data[res->_length + 1] = '\0';
      res->_sign = this->_sign;
      return (res);
    }
  return (NULL);
}

static void			number_karatsuba_expression(uint64_t const size,
							    t_number *ac,
							    t_number *bd,
							    t_number *abcd,
							    t_number *res)
{
  t_number			tenK = _NUMBER_INIT_;
  t_number			ten2K = _NUMBER_INIT_;
  t_number			resACBD = _NUMBER_INIT_;
  t_number			resABCD = _NUMBER_INIT_;

  number_addition(number_addition(number_tenPower(ac, &ten2K, size * 2),
				  number_tenPower(number_subtraction(number_addition(ac, bd,
										     &resACBD),
								     abcd, &resABCD),
						  &tenK, size),
				  &resABCD), bd, res);
  number_dtor(&tenK);
  number_dtor(&ten2K);
  number_dtor(&resACBD);
  number_dtor(&resABCD);
}

static void			number_setGreater(t_number const *a,
						  t_number const *b,
						  t_number const *greater[2])
{
  if (((a->_length == b->_length) ?
       CAST_BOOL(strcmp(NUMBER_NUM_ABS(a), NUMBER_NUM_ABS(b)) > 0) :
       CAST_BOOL(a->_length > b->_length)))
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

static t_number			*number_karatsuba(t_number const *numA,
						  t_number const *numB,
						  t_number *res)
{
  t_number			a;
  t_number			b;
  t_number			c;
  t_number			d;
  t_number			ac = _NUMBER_INIT_;
  t_number			bd = _NUMBER_INIT_;
  t_number			abcd = _NUMBER_INIT_;
  t_number			resAB = _NUMBER_INIT_;
  t_number			resCD = _NUMBER_INIT_;
  uint64_t			size = ((numA->_length > numB->_length) ?
					numA->_length : numB->_length);
  t_number const		*greaterAB[2];
  t_number const		*greaterCD[2];

  size = (size / 2) + (size % 2);
  number_partial_copy(numA, size, &a, &b);
  number_partial_copy(numB, size, &c, &d);
  number_setGreater(&a, &b, greaterAB);
  number_setGreater(&c, &d, greaterCD);
  if (number_multiplication(&a, &c, &ac) && number_multiplication(&b, &d, &bd) &&
      number_multiplication(number_sub(greaterAB[0], greaterAB[1], &resAB),
			    number_sub(greaterCD[0], greaterCD[1], &resCD), &abcd))
    number_karatsuba_expression(size, &ac, &bd, &abcd, res);
  number_dtor(&ac);
  number_dtor(&bd);
  number_dtor(&abcd);
  number_dtor(&resAB);
  number_dtor(&resCD);
  return (res);
}

static t_number			*number_mult(t_number const *a, t_number const *b)
{
  t_number			*res = number_new();
  t_bool			resSign = CAST_BOOL(a->_sign == b->_sign);

  if (res)
    {
      if (NUMBER_ISZERO(a) || NUMBER_ISZERO(b) ||
	  ((a->_length + b->_length) <= _NUMBER_MAXLENGHT_INT_))
	{
	  if ((res = number_assign_int(res, number_integer(a) * number_integer(b))))
	    res->_sign = resSign;
	  return (res);
	}
      return (number_karatsuba(a, b, res));
    }
  return (NULL);
}

t_number			*number_multiplication(t_number const *a,
						       t_number const *b,
						       t_number *res)
{
  t_bool			resSign = CAST_BOOL(a->_sign == b->_sign);
  t_number			*resAlgo;

  if (a && b && res)
    {
      if ((resAlgo = number_mult(a, b)))
	{
	  number_dtor(res);
	  *res = *resAlgo;
	  res->_sign = resSign;
	  free(resAlgo);
	  number_delUselessZero(res);
	  return (res);
	}
    }
  return (NULL);
}
