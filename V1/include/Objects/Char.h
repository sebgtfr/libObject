/**
* \file				Char.h
* \author			Sébastien Le Maire
* \version			1.0
* \date				23 Février 2018
*/

#ifndef OBJECTS_CHAR_H_
# define OBJECTS_CHAR_H_

# include "Objects/Char.hpp"

# ifdef __cplusplus

extern "C" {

# endif /* !CPLUSPLUS */

	extern UnicodeChar			UnicodeChar_ctor(char const *str);
	extern uint8_t				UnicodeCharSize(char const c);
	extern uint8_t				UnicodeChar_size(UnicodeChar const unicode);
	extern void					UnicodeChar_print(UnicodeChar const unicode);

#ifdef __cplusplus

}

# endif /* !CPLUSPLUS */

#endif /* !OBJECTS_CHAR_H_ */
