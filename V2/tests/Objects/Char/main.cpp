
#include <iostream>
#include "Objects/Char.hpp"

void							printUnicode(Objects::Unicode::Char const unicode)
{
	std::cout << "size of \"" << unicode << "\" is "
			  << static_cast<int>(unicode.size())
			  << " bytes." << std::endl;
}

int								main(void)
{
	printUnicode("é");
	printUnicode("€");
	return 0;
}
