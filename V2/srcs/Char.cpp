/**
* \file				Char.cpp
* \author			Sébastien Le Maire
* \version			1.0
* \date				23 Février 2018
*/

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

		Objects::Unicode::CharInt		Char::toString(void) const
		{
			Objects::Unicode::CharInt	strUnicode;
			uint8_t						si = 0;

			for (int8_t i = (this->size() - 1) * 8; i >= 0; i -= 8)
				strUnicode._char[si++] = static_cast<uint8_t>((this->_value >> i) & 0xFF);
			return strUnicode;
		}
	}
}
