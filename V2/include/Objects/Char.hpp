/**
* \file				Char.hpp
* \author			Sébastien Le Maire
* \version			1.0
* \date				25 Avril 2018
*/

#ifndef OBJECTS_CHAR_HPP_
# define OBJECTS_CHAR_HPP_

# include <cstdint>

namespace								Objects
{
	namespace							Unicode
	{
		union							CharInt
		{
			char						_char[sizeof(uint32_t) + 1];
			uint32_t					_int;

			CharInt() : _char{0} {};
		};

		class							Char
		{
		private:
			uint32_t				   	_value;

		public:
			/* Ctor & Dtor copelian form */
			Char(uint32_t const c = 0) : _value(c) {};
			Char(char const *str);
			Char(Objects::Unicode::Char const &c) : _value(c._value) {};
			Objects::Unicode::Char	&operator=(Objects::Unicode::Char const &c);

			/* Assignment */
			Objects::Unicode::Char	&operator+=(Objects::Unicode::Char const &c);
			Objects::Unicode::Char	&operator-=(Objects::Unicode::Char const &c);
			Objects::Unicode::Char	&operator*=(Objects::Unicode::Char const &c);
			Objects::Unicode::Char	&operator/=(Objects::Unicode::Char const &c);
			Objects::Unicode::Char	&operator%=(Objects::Unicode::Char const &c);
			Objects::Unicode::Char	&operator&=(Objects::Unicode::Char const &c);
			Objects::Unicode::Char	&operator|=(Objects::Unicode::Char const &c);
			Objects::Unicode::Char	&operator^=(Objects::Unicode::Char const &c);
			Objects::Unicode::Char	&operator<<=(Objects::Unicode::Char const &c);
			Objects::Unicode::Char	&operator>>=(Objects::Unicode::Char const &c);

			/* (in/de)crement */
			Objects::Unicode::Char	&operator++(void);
			Objects::Unicode::Char	&operator--(void);
			Objects::Unicode::Char	operator++(int);
			Objects::Unicode::Char	operator--(int);

			/* Arithmetic */
			inline Objects::Unicode::Char	operator+(Objects::Unicode::Char const &c) const
				{
					return Objects::Unicode::Char(this->_value + c._value);
				}
			inline Objects::Unicode::Char	operator-(Objects::Unicode::Char const &c) const
				{
					return Objects::Unicode::Char(this->_value - c._value);
				}
			inline Objects::Unicode::Char	operator*(Objects::Unicode::Char const &c) const
				{
					return Objects::Unicode::Char(this->_value * c._value);
				}
			inline Objects::Unicode::Char	operator/(Objects::Unicode::Char const &c) const
				{
					return Objects::Unicode::Char(this->_value / c._value);
				}
			inline Objects::Unicode::Char	operator%(Objects::Unicode::Char const &c) const
				{
					return Objects::Unicode::Char(this->_value % c._value);
				}
			inline Objects::Unicode::Char	operator~(void) const
				{
					return Objects::Unicode::Char(~this->_value);
				}
			inline Objects::Unicode::Char	operator&(Objects::Unicode::Char const &c) const
				{
					return Objects::Unicode::Char(this->_value & c._value);
				}
			inline Objects::Unicode::Char	operator|(Objects::Unicode::Char const &c) const
				{
					return Objects::Unicode::Char(this->_value | c._value);
				}
			inline Objects::Unicode::Char	operator^(Objects::Unicode::Char const &c) const
				{
					return Objects::Unicode::Char(this->_value ^ c._value);
				}
			inline Objects::Unicode::Char	operator<<(Objects::Unicode::Char const &c) const
				{
					return Objects::Unicode::Char(this->_value << c._value);
				}
			inline Objects::Unicode::Char	operator>>(Objects::Unicode::Char const &c) const
				{
					return Objects::Unicode::Char(this->_value >> c._value);
				}

			/* Logical */
			inline bool   				operator!(void) const
				{
					return !this->_value;
				}
			inline bool   				operator&&(Objects::Unicode::Char const &c) const
				{
					return this->_value && c._value;
				}
			inline bool				operator||(Objects::Unicode::Char const &c) const
				{
					return this->_value || c._value;
				}

			/* Comparaison */
			inline bool				operator==(Objects::Unicode::Char const &c) const
				{
					return this->_value == c._value;
				}
			inline bool				operator!=(Objects::Unicode::Char const &c) const
				{
					return this->_value != c._value;
				}
			inline bool   				operator<(Objects::Unicode::Char const &c) const
				{
					return this->_value < c._value;
				}
			inline bool				operator<=(Objects::Unicode::Char const &c) const
				{
					return this->_value <= c._value;
				}
			inline bool				operator>(Objects::Unicode::Char const &c) const
				{
					return this->_value > c._value;
				}
			inline bool				operator>=(Objects::Unicode::Char const &c) const
				{
					return this->_value >= c._value;
				}

			/* Access */
			inline uint32_t					operator*(void) const
				{
					return this->_value;
				}

			/* Conversion */
# define OBJECTS_UNICODE_CHAR_CONVERT(type)					\
			inline operator type(void) const				\
				{											\
					return static_cast<type>(this->_value);	\
				}											\

			OBJECTS_UNICODE_CHAR_CONVERT(bool)
			OBJECTS_UNICODE_CHAR_CONVERT(char)
			OBJECTS_UNICODE_CHAR_CONVERT(int32_t)
			OBJECTS_UNICODE_CHAR_CONVERT(uint32_t)


			/* Low level type C operator */
# define OBJECTS_UNICODE_CHAR_OPERATOR(type, cast)						\
			Objects::Unicode::Char	&operator=(type const c)			\
				{														\
					this->_value = c;									\
					return *this;										\
				}														\
																		\
			/* Assignment */											\
			Objects::Unicode::Char	&operator+=(type const c)			\
				{														\
					this->_value += c;									\
					return *this;										\
				}														\
			Objects::Unicode::Char	&operator-=(type const c)			\
				{														\
					this->_value -= c;									\
					return *this;										\
				}														\
			Objects::Unicode::Char	&operator*=(type const c)			\
				{														\
					this->_value *= c;									\
					return *this;										\
				}														\
			Objects::Unicode::Char	&operator/=(type const c)			\
				{														\
					this->_value /= c;									\
					return *this;										\
				}														\
			Objects::Unicode::Char	&operator%=(type const c)			\
				{														\
					this->_value %= c;									\
					return *this;										\
				}														\
			Objects::Unicode::Char	&operator&=(type const c)			\
				{														\
					this->_value &= c;									\
					return *this;										\
				}														\
			Objects::Unicode::Char	&operator|=(type const c)			\
				{														\
					this->_value |= c;									\
					return *this;										\
				}														\
			Objects::Unicode::Char	&operator^=(type const c)			\
				{														\
					this->_value ^= c;									\
					return *this;										\
				}														\
			Objects::Unicode::Char	&operator<<=(type const c)			\
				{														\
					this->_value <<= c;									\
					return *this;										\
				}														\
			Objects::Unicode::Char	&operator>>=(type const c)			\
				{														\
					this->_value >>= c;									\
					return *this;										\
				}														\
																		\
			/* Arithmetic */											\
			inline Objects::Unicode::Char	operator+(type const &c)	\
				{														\
					return Objects::Unicode::Char(this->_value + c);	\
				}														\
			inline Objects::Unicode::Char	operator-(type const &c) const \
				{														\
					return Objects::Unicode::Char(this->_value - c);	\
				}														\
			inline Objects::Unicode::Char	operator*(type const &c) const \
				{														\
					return Objects::Unicode::Char(this->_value * c);	\
				}														\
			inline Objects::Unicode::Char	operator/(type const &c) const \
				{														\
					return Objects::Unicode::Char(this->_value / c);	\
				}														\
			inline Objects::Unicode::Char	operator%(type const &c) const \
				{														\
					return Objects::Unicode::Char(this->_value % c);	\
				}														\
			inline Objects::Unicode::Char	operator&(type const &c) const \
				{														\
					return Objects::Unicode::Char(this->_value & c);	\
				}														\
			inline Objects::Unicode::Char	operator|(type const &c) const \
				{														\
					return Objects::Unicode::Char(this->_value | c);	\
				}														\
			inline Objects::Unicode::Char	operator^(type const &c) const \
				{														\
					return Objects::Unicode::Char(this->_value ^ c);	\
				}														\
			inline Objects::Unicode::Char	operator<<(type const &c) const	\
				{														\
					return Objects::Unicode::Char(this->_value << c);	\
				}														\
			inline Objects::Unicode::Char	operator>>(type const &c) const	\
				{														\
					return Objects::Unicode::Char(this->_value >> c);	\
				}														\
																		\
			/* Logical */												\
			inline bool					operator&&(type const &c) const	\
				{														\
					return this->_value && static_cast<cast>(c);		\
				}														\
			inline bool					operator||(type const &c) const	\
				{														\
					return this->_value || static_cast<cast>(c);		\
				}														\
																		\
			/* Comparaison */											\
			inline bool					operator==(type const &c) const	\
				{														\
					return this->_value == static_cast<cast>(c);		\
				}														\
			inline bool					operator!=(type const &c) const	\
				{														\
					return this->_value != static_cast<cast>(c);		\
				}														\
			inline bool					operator<(type const &c) const	\
				{														\
					return this->_value < static_cast<cast>(c);			\
				}														\
			inline bool					operator<=(type const &c) const	\
				{														\
					return this->_value <= static_cast<cast>(c);		\
				}														\
			inline bool					operator>(type const &c) const	\
				{														\
					return this->_value > static_cast<cast>(c);			\
				}														\
			inline bool					operator>=(type const &c) const	\
				{														\
					return this->_value >= static_cast<cast>(c);		\
				}														\

			OBJECTS_UNICODE_CHAR_OPERATOR(char, unsigned char)
			OBJECTS_UNICODE_CHAR_OPERATOR(int32_t, uint32_t)
			OBJECTS_UNICODE_CHAR_OPERATOR(uint32_t, uint32_t)

			/* Public methods */
			uint8_t						size(void) const;
			Objects::Unicode::CharInt	toString(void) const;

			/* Static methods */
			static uint8_t				size(unsigned char const c);
		};
	}
}

# include <iostream>

inline std::ostream						&operator<<(std::ostream &os,
													Objects::Unicode::Char const &c)
{
	os << c.toString()._char;
	return os;
}

#endif /* !OBJECTS_CHAR_HPP_ */
