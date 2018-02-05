/**
* \file			        number.h
* \author			Sébastien Le Maire
* \version			1.0
* \date				07 Mars 2017
*/

#ifndef NUMBER_H_
# define NUMBER_H_

# include "bool.h"

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
# define NUMBER_INIT(s, c, l, d)    (t_number){s, c, l, (char *)d}
# define _NUMBER_INIT_              NUMBER_INIT(FALSE, 0, 0, 0)

# define IS_NUMBER(n)		((n) >= '0' && (n) <= '9')
# define NUMBER_TO_CHAR(n)	((n) + '0')
# define NUMBER_TO_INT(n)	((n) - '0')
# define NUMBER_ABS(n)		(((n) < 0) ? (-(n)) : (n))

/* Global */

# ifndef _NULLPTR_
#  define  _NULLPTR_
/**
* \brief		        Defini la constante NULL.
* \details		        Défini la constante NULL si elle n'a pas été défini.
*/
extern void const * const       g_nullptr;

# define __NUMBER_NULLPTR_DEFINE__

# endif /* !_NULLPTR_ */

extern t_number const           g_defaultNumber;
extern t_number const           g_nullNumber;
extern uint8_t const            g_numberMaxLenghtInt; /* Lenght secure of int 64 for conversion */

/*
** Number's functions
*/
extern t_bool           number_ctor(t_number *this,
                                    t_number_type const type,
                                    uint64_t number);
extern void				number_dtor(t_number *this);
extern t_bool  			number_copy(t_number *this,
                                    t_number const *number);

/*
** Allocation
*/
extern t_number			*number_new(void);
extern void				number_delete(t_number *this);
extern t_bool			number_resize(t_number *this, uint64_t const size);

/*
** Operator
*/
extern t_bool				number_equal(t_number const *this,
					     t_number const *num);
extern t_bool				number_great(t_number const *this,
					     t_number const *num);
extern t_bool				number_low(t_number const *this,
					   t_number const *num);

/*
** Methods
*/
extern t_number			*number_assign(t_number *this,
                                       t_number_type const type,
                                       uint64_t number);
extern t_number			*number_assign_string(t_number *this,
                                              char const *number);
extern t_number			*number_assign_int(t_number *this,
                                           int64_t number);
extern t_number			*number_change(t_number *this,
                                       t_number_type const type,
                                       uint64_t number);
extern t_number			*number_change_string(t_number *this,
                                              char const *number);
extern t_number			*number_change_int(t_number *this,
                                           int64_t number);
extern void				number_print(t_number *this, int const fd);
extern void				number_delUselessZero(t_number *this);
extern int64_t				number_integer(t_number const *this);

/* Operations */
extern t_number			*number_addition(t_number const *a,
                                         t_number const *b,
                                         t_number *res);
extern t_number			*number_subtraction(t_number const *a,
                                            t_number *b,
                                            t_number *res);
extern t_number			*number_multiplication(t_number const *a,
                                               t_number const *b,
                                               t_number *res);

static inline void              number_abs(t_number *this)
{
    this->_sign = true;
};

static inline char              *number_num_abs(t_number const *this)
{
    return this->_data + CAST_BOOL(this->_data[0] == '-');
};

static inline t_bool            number_isNeg(t_number const *this)
{
    return !this->_sign;
};

static inline char              *number_data(t_number const *this)
{
    return this->_data + this->_sign;
};

static inline char              *number_unit(t_number const *this)
{
    return this->_data + this->_length - CAST_BOOL(this->_data[0] != '-');
};

static inline t_bool            number_isZero(t_number const *this)
{
    return (this->_length == 1) &&
        (this->_data[CAST_BOOL(this->_data[0] == '-')] == '0');
};

static inline void              number_reverseSign(t_number *this)
{
    this->_sign = !this->_sign;
};

#endif /* !NUMBER_H_ */
