
#include "Objects/String.hpp"
#include <iostream>

int								main(void)
{
	Objects::String				str("Hello World !");
	Objects::String				str2(str);
	Objects::String				name("Sébastien");
	Objects::String				str3("28€");
	Objects::String				str4;
	Objects::Unicode::String::Iterator	it(const_cast<char *>(name.getRawData()));
	Objects::String::Iterator			itBytes(const_cast<char *>(name.getRawData()));

	str = name;
	str4 = str3;
	while (*it)
	{
		std::cout << *it;
		++it;
	}
	std::cout << std::endl;
	while (*itBytes)
	{
		std::cout << *itBytes;
		++itBytes;
	}
	std::cout << std::endl;
	std::cout << Objects::Unicode::Char('é') << std::endl;
	std::cout << Objects::Unicode::Char('€') << std::endl;
	return 0;
}
