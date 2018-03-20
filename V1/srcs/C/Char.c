/**
* \file				Char.c
* \author			Sébastien Le Maire
* \version			1.0
* \date				23 Février 2018
*/

#include "Objects/Char.h"

UnicodeChar						UnicodeChar_ctor(char const *str)
{
	return Objects::Unicode::Char(str);
}

uint8_t							UnicodeCharSize(char const c)
{
	return Objects::Unicode::Char::size(c);
}

uint8_t							UnicodeChar_size(UnicodeChar const unicode)
{
	return Objects::Unicode::Char(unicode).size();
}

void							UnicodeChar_print(UnicodeChar const unicode)
{
	std::cout << Objects::Unicode::Char(unicode);
}

uint8_t							UnicodeChar_toString(UnicodeChar const unicode,
													 char *dest)
{
	Objects::Unicode::CharInt	ci = Objects::Unicode::Char(unicode).toString();
	char const					*i = (char const *)ci._char;

	while ((*dest = *i++))
		++dest;
	return (uint8_t)(i - (char const *)ci._char);
}
