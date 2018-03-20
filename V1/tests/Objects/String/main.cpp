
#include "Objects/String.hpp"

int								main(void)
{
	char const * const			name = "Sébastien";
	char const * const			john = "John";
	Objects::String				strName(name);
	Objects::String				copyName(strName);
	Objects::String				copy2Name;
	Objects::String				copy3Name(nullptr);
	Objects::String				copy4Name(nullptr);

	copy3Name = copy2Name = strName.rawData();
	copy4Name += strName += ", J'ai 15 € !";

	size_t						e = copy4Name.find("é");
	size_t						euro = copy4Name.find("€");

	std::cout << "Dans la phrase : \"" << copy4Name << "\" "
			  << "le caractère '" << copy4Name.unicodeAt(e)
			  << "' commence en mémoire en position "
			  << e << " et le caratère '" << copy4Name.unicodeAt(euro)
			  << "' commence en mémoire en position " << euro << std::endl;
	std::cout << "\"" << strName << "\" == \"" << copy4Name << "\" est '"
			  << (strName == copy4Name) << '\'' << std::endl;
	std::cout << "\"" << copy3Name << "\" == \"" << name << "\" est '"
			  << (copy3Name == name) << '\'' << std::endl;
	std::cout << "\"" << copy3Name << "\" <= \"" << name << "\" est '"
			  << (copy3Name <= name) << '\'' << std::endl;
	std::cout << "\"" << copy3Name << "\" >= \"" << name << "\" est '"
			  << (copy3Name >= name) << '\'' << std::endl;
	std::cout << "\"" << copy3Name << "\" != \"" << name << "\" est '"
			  << (copy3Name != name) << '\'' << std::endl;
	std::cout << "\"" << copy3Name << "\" == \"" << copy4Name << "\" est '"
			  << (copy3Name == copy4Name) << '\'' << std::endl;
	std::cout << "\"" << copy3Name << "\" < \"" << copy4Name << "\" est '"
			  << (copy3Name < copy4Name) << '\'' << std::endl;
	std::cout << "\"" << copy3Name << "\" > \"" << copy4Name << "\" est '"
			  << (copy3Name > copy4Name) << '\'' << std::endl;
	std::cout << "\"" << copy3Name << "\" > \"" << NULL << "\" est '"
			  << (copy3Name > NULL) << '\'' << std::endl;
	std::cout << "\"" << copy3Name << "\" < \"" << NULL << "\" est '"
			  << (copy3Name < NULL) << '\'' << std::endl;
	std::cout << "\"" << copy3Name << "\" == \"" << NULL << "\" est '"
			  << (copy3Name == NULL) << '\'' << std::endl;
	copy3Name = NULL;
	std::cout << "\"" << copy3Name << "\" == \"" << NULL << "\" est '"
			  << (copy3Name == NULL) << '\'' << std::endl;
	strName = john;

	Objects::String				johnlc = strName.lowercase();
	Objects::String				johnuc = strName.uppercase();

	copy4Name = copy4Name.substr(0, "n").reverse();

	std::cout << "reverse : " << copy4Name << std::endl;

	Objects::Unicode::String::Iterator revIt = copy4Name.unicodeEnd();
	while (--revIt != copy4Name.unicodeBegin())
		std::cout << *revIt;
	std::cout << *revIt << std::endl;
	return 0;
}
