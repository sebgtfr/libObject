
#include <iostream>
#include "Objects/String.hpp"
#include "Objects/Vector.hpp"

int											main(void)
{
	Objects::String const					name("Sébastien");
	Objects::Vector<int>					toto;
	Objects::Vector<Objects::Unicode::Char>	vname(name.unicodeSize());
	Objects::Vector<Objects::Unicode::Char>	vnameCopyOP(name.unicodeSize());
	Objects::Vector<Objects::String>		vstr;

	toto.push_back(42);
	vstr.push_back(name);
	for (Objects::Unicode::String::Iterator it = name.unicodeBegin();
		 it != name.unicodeEnd(); ++it)
	{
		vname.push_back(*it);
		vnameCopyOP.push_back(*it);
	}
	for (Objects::Vector<Objects::Unicode::Char>::Iterator it = vname.begin();
		 it != vname.end(); ++it)
		std::cout << *it;
	std::cout << std::endl;

	Objects::Vector<Objects::Unicode::Char>	vnameCopy(vname);

	vnameCopy.insert('€', 1);
	vnameCopyOP = vnameCopy;

	vnameCopyOP.erase(2, 8);
	vnameCopyOP.push_back('b');

	for (Objects::Vector<Objects::Unicode::Char>::Iterator it = vnameCopyOP.begin();
		 it != vnameCopyOP.end(); ++it)
		std::cout << *it;
	std::cout << std::endl;

	return 0;
}
