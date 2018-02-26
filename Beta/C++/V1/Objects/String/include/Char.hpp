
#ifndef OBJECTS_CHAR_HPP_
# define OBJECTS_CHAR_HPP_

#include "Objects/System.hpp"
#include <iostream>

namespace								Objects
{
	namespace							Unicode
	{
		class							Char
		{
		private:
			uint32						_value;

		public:
			/* Ctor & Dtor copelian form */
			Char(uint32 const c = 0) : _value(c) {};
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
			inline uint32					operator*(void) const
				{
					return this->_value;
				}

			/* Conversion */
# define OBJECTS_UNICODE_CHAR_CONVERT(type)									\
			inline operator type(void) const								\
				{															\
					return static_cast<type>(this->_value);					\
				}															\

			OBJECTS_UNICODE_CHAR_CONVERT(bool)
			OBJECTS_UNICODE_CHAR_CONVERT(int8)
			OBJECTS_UNICODE_CHAR_CONVERT(uint8)
			OBJECTS_UNICODE_CHAR_CONVERT(int16)
			OBJECTS_UNICODE_CHAR_CONVERT(uint16)
			OBJECTS_UNICODE_CHAR_CONVERT(int32)
			OBJECTS_UNICODE_CHAR_CONVERT(uint32)


			/* Low level type C operator */
# define OBJECTS_UNICODE_CHAR_OPERATOR(type, cast)							\
			Objects::Unicode::Char	&operator=(type const c)				\
				{															\
					this->_value = c;										\
					return *this;											\
				}															\
																			\
			/* Assignment */											   	\
			Objects::Unicode::Char	&operator+=(type const c)				\
				{															\
					this->_value += c;										\
					return *this;											\
				}															\
			Objects::Unicode::Char	&operator-=(type const c)				\
				{															\
					this->_value -= c;										\
					return *this;											\
				}															\
			Objects::Unicode::Char	&operator*=(type const c)				\
				{															\
					this->_value *= c;										\
					return *this;											\
				}															\
			Objects::Unicode::Char	&operator/=(type const c)				\
				{															\
					this->_value /= c;										\
					return *this;											\
				}															\
			Objects::Unicode::Char	&operator%=(type const c)				\
				{															\
					this->_value %= c;										\
					return *this;											\
				}															\
			Objects::Unicode::Char	&operator&=(type const c)				\
				{															\
					this->_value &= c;										\
					return *this;											\
				}															\
			Objects::Unicode::Char	&operator|=(type const c)				\
				{															\
					this->_value |= c;										\
					return *this;											\
				}															\
			Objects::Unicode::Char	&operator^=(type const c)				\
				{															\
					this->_value ^= c;										\
					return *this;											\
				}															\
			Objects::Unicode::Char	&operator<<=(type const c)				\
				{															\
					this->_value <<= c;										\
					return *this;											\
				}															\
			Objects::Unicode::Char	&operator>>=(type const c)				\
				{															\
					this->_value >>= c;										\
					return *this;											\
				}															\
																			\
			/* Arithmetic */											   	\
			inline Objects::Unicode::Char	operator+(type const &c)		\
				{															\
					return Objects::Unicode::Char(this->_value + c);		\
				}															\
			inline Objects::Unicode::Char	operator-(type const &c) const 	\
				{															\
					return Objects::Unicode::Char(this->_value - c);		\
				}															\
			inline Objects::Unicode::Char	operator*(type const &c) const 	\
				{															\
					return Objects::Unicode::Char(this->_value * c);		\
				}															\
			inline Objects::Unicode::Char	operator/(type const &c) const 	\
				{															\
					return Objects::Unicode::Char(this->_value / c);		\
				}															\
			inline Objects::Unicode::Char	operator%(type const &c) const 	\
				{															\
					return Objects::Unicode::Char(this->_value % c);		\
				}															\
			inline Objects::Unicode::Char	operator&(type const &c) const 	\
				{															\
					return Objects::Unicode::Char(this->_value & c);		\
				}															\
			inline Objects::Unicode::Char	operator|(type const &c) const 	\
				{															\
					return Objects::Unicode::Char(this->_value | c);		\
				}															\
			inline Objects::Unicode::Char	operator^(type const &c) const 	\
				{															\
					return Objects::Unicode::Char(this->_value ^ c);		\
				}															\
			inline Objects::Unicode::Char	operator<<(type const &c) const	\
				{															\
					return Objects::Unicode::Char(this->_value << c);		\
				}															\
			inline Objects::Unicode::Char	operator>>(type const &c) const	\
				{															\
					return Objects::Unicode::Char(this->_value >> c);		\
				}															\
																			\
			/* Logical */												   	\
			inline bool					operator&&(type const &c) const		\
				{															\
					return this->_value && static_cast<cast>(c);			\
				}															\
			inline bool					operator||(type const &c) const		\
				{															\
					return this->_value || static_cast<cast>(c);			\
				}															\
																			\
			/* Comparaison */											   	\
			inline bool					operator==(type const &c) const		\
				{															\
					return this->_value == static_cast<cast>(c);			\
				}															\
			inline bool					operator!=(type const &c) const		\
				{															\
					return this->_value != static_cast<cast>(c);			\
				}															\
			inline bool					operator<(type const &c) const		\
				{															\
					return this->_value < static_cast<cast>(c);				\
				}															\
			inline bool					operator<=(type const &c) const		\
				{															\
					return this->_value <= static_cast<cast>(c);			\
				}															\
			inline bool					operator>(type const &c) const		\
				{															\
					return this->_value > static_cast<cast>(c);				\
				}															\
			inline bool					operator>=(type const &c) const		\
				{															\
					return this->_value >= static_cast<cast>(c);			\
				}															\

			OBJECTS_UNICODE_CHAR_OPERATOR(bool, uint8)
			OBJECTS_UNICODE_CHAR_OPERATOR(int8, uint8)
			OBJECTS_UNICODE_CHAR_OPERATOR(uint8, uint8)
			OBJECTS_UNICODE_CHAR_OPERATOR(int16, uint16)
			OBJECTS_UNICODE_CHAR_OPERATOR(uint16, uint16)
			OBJECTS_UNICODE_CHAR_OPERATOR(int32, uint32)
			OBJECTS_UNICODE_CHAR_OPERATOR(uint32, uint32)
		};
	}
}

std::ostream					&operator<<(std::ostream &os,
											Objects::Unicode::Char const &uc);

#endif /* !OBJECTS_CHAR_HPP_ */
