/**
* \file				Char.c
* \author			Sébastien Le Maire
* \version			1.0
* \date				23 Février 2018
*/

#include "Objects/Char.h"

UnicodeChar						UnicodeChar_ctor(char const *str)
{
	Objects::Unicode::Char		c(str);

	return *c;
}

uint8_t							UnicodeCharSize(char const c)
{
	return Objects::Unicode::Char(c);
}

uint8_t							UnicodeChar_size(UnicodeChar const unicode)
{
	Objects::Unicode::Char		c(unicode);

	return c.size();
}

void							UnicodeChar_print(UnicodeChar const unicode)
{
	Objects::Unicode::Char		c(unicode);

	std::cout << c;
}
