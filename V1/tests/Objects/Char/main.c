
#include <stdio.h>
#include "Objects/Char.h"

void							printUnicode(UnicodeChar const unicode)
{
	(void)printf("size of \"");
	UnicodeChar_print(unicode);
	(void)printf("\" is %u bytes.\n", UnicodeChar_size(unicode));
}

int								main(void)
{
	printUnicode(UnicodeChar_ctor("é"));
	printUnicode(UnicodeChar_ctor("€"));
	return 0;
}
