#include "mystring.h"

uint64_t                        string_unicodeLen(t_string const *this)
{
    uint64_t                    unicodeLen = 0;
    uint8_t                     lenCurChar = 0;
    uint8_t                     it;

    for (uint64_t i = 0; (it = this->_data[i]); i += lenCurChar)
	{
		lenCurChar = 1;
		if ((it >> 7) & 1)
			while (lenCurChar < 4 && ((it >> (7 - lenCurChar)) & 1))
				++lenCurChar;
		++unicodeLen;
	}
    return unicodeLen;
}

int main(void)
{
    t_string                    name;
    t_string                    money;

    string_ctor(&name, "Sébastien");
    string_ctor(&money, "15€");

    uint64_t unicodeLenName = string_unicodeLen(&name);
    uint64_t unicodeLenMoney = string_unicodeLen(&money);

    string_dtor(&name);
    string_dtor(&money);
}
