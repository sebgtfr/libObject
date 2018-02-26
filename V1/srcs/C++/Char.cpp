
#include "Objects/Char.hpp"

namespace								Objects
{
	namespace							Unicode
	{
		Char::Char(char const *str)
			: _value(0)
		{
			uint8_t		sizeUnicodeChar = Objects::Unicode::Char::size(*str);

			for (uint8_t i = 0; i < sizeUnicodeChar; ++i)
				this->_value = (this->_value << 8) + (uint8_t)str[i];
		}

		Objects::Unicode::Char			&Char::operator=(Objects::Unicode::Char const &c)
		{
			this->_value = c._value;
			return *this;
		}

		Objects::Unicode::Char			&Char::operator+=(Objects::Unicode::Char const &c)
		{
			this->_value += c._value;
			return *this;
		}

		Objects::Unicode::Char			&Char::operator-=(Objects::Unicode::Char const &c)
		{
			this->_value -= c._value;
			return *this;
		}

		Objects::Unicode::Char			&Char::operator*=(Objects::Unicode::Char const &c)
		{
			this->_value *= c._value;
			return *this;
		}

		Objects::Unicode::Char			&Char::operator/=(Objects::Unicode::Char const &c)
		{
			this->_value /= c._value;
			return *this;
		}

		Objects::Unicode::Char			&Char::operator%=(Objects::Unicode::Char const &c)
		{
			this->_value %= c._value;
			return *this;
		}

		Objects::Unicode::Char			&Char::operator&=(Objects::Unicode::Char const &c)
		{
			this->_value &= c._value;
			return *this;
		}

		Objects::Unicode::Char			&Char::operator|=(Objects::Unicode::Char const &c)
		{
			this->_value |= c._value;
			return *this;
		}

		Objects::Unicode::Char			&Char::operator^=(Objects::Unicode::Char const &c)
		{
			this->_value ^= c._value;
			return *this;
		}

		Objects::Unicode::Char			&Char::operator<<=(Objects::Unicode::Char const &c)
		{
			this->_value <<= c._value;
			return *this;
		}

		Objects::Unicode::Char			&Char::operator>>=(Objects::Unicode::Char const &c)
		{
			this->_value >>= c._value;
			return *this;
		}

		Objects::Unicode::Char			&Char::operator++(void)
		{
			++this->_value;
			return *this;
		}

		Objects::Unicode::Char			&Char::operator--(void)
		{
			--this->_value;
			return *this;
		}

		Objects::Unicode::Char			Char::operator++(int)
		{
			Objects::Unicode::Char		c(*this);

			++this->_value;
			return c;
		}

		Objects::Unicode::Char			Char::operator--(int)
		{
			Objects::Unicode::Char		c(*this);

			--this->_value;
			return c;
		}

		uint8_t							Char::size(void) const
		{
			unsigned char				c = 0;

			for (int8_t i = 24; !c && i >= 0; i -= 8)
				c = (unsigned char)((this->_value >> i) & 0xFF);
			return Objects::Unicode::Char::size(c);
		}

		uint8_t							Char::size(unsigned char const c)
		{
			switch (c & 0xF0)
			{
			case 0xC0: // 1100 0000
				return 2;
			case 0xE0: // 1110 0000
				return 3;
			case 0xF0: // 1111 0000
				return 4;
			}
			return 1;
		}
	}
}

std::ostream							&operator<<(std::ostream &os,
													Objects::Unicode::Char const &uc)
{
	char								strUnicode[5] = {0};
	uint8_t								si = 0;

	for (int8_t i = 24; i >= 0; i -= 8)
	{
		uint8_t					c = (uint8_t)((*uc >> i) & 0xFF);

		if (c)
			strUnicode[si++] = c;
	}
	if (si)
		os << strUnicode;
	return os;
}
