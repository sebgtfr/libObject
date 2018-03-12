
#include "Objects/String.hpp"

int								main(void)
{
	char const * const			name = "Sébastien";
	Objects::String				strName(name);
	Objects::String				copyName(strName);
	Objects::String				copy2Name;
	Objects::String				copy3Name(nullptr);
	Objects::String				copy4Name(nullptr);

	copy3Name = copy2Name = strName.rawData();
	copy4Name += strName += ", J'ai 15 € !";

	size_t						e = copy4Name.find("é");
	size_t						euro = copy4Name.find("€");

	return 0;
}
