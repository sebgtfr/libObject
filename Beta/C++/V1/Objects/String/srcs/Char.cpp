
#include "Objects/Char.hpp"
#include "Objects/String.hpp"

namespace								Objects
{
	namespace							Unicode
	{
		Char::Char(char const *str)
			: _value(0)
		{
			uint8			sizeUnicodeChar = Objects::Unicode::String::sizeUnicodeChar(*str);

			for (uint8 i = 0; i < sizeUnicodeChar; ++i)
				this->_value = (this->_value << 8) + (uint8)str[i];
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
			Objects::Unicode::Char c(*this);

			++this->_value;
			return c;
		}

		Objects::Unicode::Char			Char::operator--(int)
		{
			Objects::Unicode::Char c(*this);

			--this->_value;
			return c;
		}
	}
}

std::ostream							&operator<<(std::ostream &os,
													Objects::Unicode::Char const &uc)
{
	for (int8 i = 24; i >= 0; i -= 8)
	{
		uint8							c = static_cast<uint8>((*uc >> i) & 0xFF);

		if (c)
			os << c;
	}
	return os;
}
