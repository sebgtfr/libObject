/**
* \file			        number.h
* \author			Sébastien Le Maire
* \version			1.0
* \date				07 Mars 2017
*/

#ifndef NUMBER_H_
# define NUMBER_H_

# include "bool.h"

# ifndef NULL
#  define NULL			(void *)0
# endif

typedef enum			e_number_type
  {
				NUMBER_INT,
				NUMBER_STRING,
				NUMBER_OBJ_NUMBER,
				NUMBER_UNDEFINED
  }				t_number_type;

typedef struct			s_number
{
  t_bool			_sign; /* false = '-'; true = '+' */
  uint64_t			_capacity;
  uint64_t			_length;
  char				*_data;
}				t_number;

/*
** Macros
*/
# define NUMBER_INIT(s,c,l,d)	(t_number){s, c, l, d}
# define _NUMBER_INIT_		NUMBER_INIT(false, 0, 0, NULL)
# define _NUMBER_INIT_NULL_	NUMBER_INIT(true, 0, 1, "0\0")
# define _NUMBER_MAXLENGHT_INT_	18 /* Lenght secure of int 64 for conversion */
# define IS_NUMBER(n)		((n) >= '0' && (n) <= '9')
# define NUMBER_TO_CHAR(n)	((n) + '0')
# define NUMBER_TO_INT(n)	((n) - '0')
# define NUMBER_ABS(n)		(((n) < 0) ? (-(n)) : (n))
# define NUMBER_CHANGE_ABS(n)	(n)->_sign = true;
# define NUMBER_NUM_ABS(n)      ((n)->_data + CAST_BOOL((n)->_data[0] == '-'))
# define NUMBER_ISNEG(n)        (!(n)->_sign)
# define NUMBER_DATA(n)		((n)->_data + (n)->_sign)
# define NUMBER_UNIT(n)		((n)->_data + (n)->_length - CAST_BOOL((n)->_data[0] != '-'))
# define NUMBER_ISZERO(n)	(((n)->_length == 1) && ((n)->_data[CAST_BOOL((n)->_data[0] == '-')] == '0'))

/*
** Macros functions
*/
# define number_reverseSign(n)	if (n) (n)->_sign = !(n)->_sign

/*
** Number's functions
*/
t_bool				number_ctor(t_number *this,
					    t_number_type const type,
					    uint64_t number);
void				number_dtor(t_number *this);
t_bool				number_copy(t_number *this,
					    t_number const *number);

/*
** Allocation
*/
t_number			*number_new(void);
void				number_delete(t_number *this);
t_bool				number_resize(t_number *this, uint64_t const size);

/*
** Operator
*/
t_bool				number_equal(t_number const *this,
					     t_number const *num);
t_bool				number_great(t_number const *this,
					     t_number const *num);
t_bool				number_low(t_number const *this,
					   t_number const *num);

/*
** Methods
*/
t_number			*number_assign(t_number *this,
					       t_number_type const type,
					       uint64_t number);
t_number			*number_assign_string(t_number *this,
						      char const *number);
t_number			*number_assign_int(t_number *this,
						   int64_t number);
t_number			*number_change(t_number *this,
					       t_number_type const type,
					       uint64_t number);
t_number			*number_change_string(t_number *this,
						      char const *number);
t_number			*number_change_int(t_number *this,
						   int64_t number);
void				number_print(t_number *this, int const fd);
void				number_delUselessZero(t_number *this);
int64_t				number_integer(t_number const *this);

/* Operations */
t_number			*number_addition(t_number const *a,
						 t_number const *b,
						 t_number *res);
t_number			*number_subtraction(t_number const *a,
						    t_number *b,
						    t_number *res);
t_number			*number_multiplication(t_number const *a,
						       t_number const *b,
						       t_number *res);


#endif /* !NUMBER_H_ */
