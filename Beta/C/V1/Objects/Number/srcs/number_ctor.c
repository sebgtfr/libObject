/**
0;115;0c* \file			        number_ctor.c
* \author			Sébastien Le Maire
* \version			1.0
* \date				07 Mars 2017
*/

#include "number.h"

#ifdef __NUMBER_NULLPTR_DEFINE__

void const * const      g_nullptr = (void *)0;

#endif /* !__NUMBER_NULLPTR_DEFINE__ */

t_number const          g_defaultNumber = _NUMBER_INIT_;
t_number const          g_nullNumber = NUMBER_INIT(TRUE, 0, 1, "0\0");
uint8_t const           g_numberMaxLenghtInt = 18;

t_bool				number_ctor(t_number *this,
                                t_number_type const type,
                                uint64_t number)
{
    *this = g_defaultNumber;
    return (CAST_BOOL(number_assign(this, type, number)));
}
