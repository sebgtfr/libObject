/**
* \file				String.hpp
* \author			Sébastien Le Maire
* \version			1.0
* \date				25 Avril 2018
*/

#ifndef OBJECTS_STRING_HPP_
# define OBJECTS_STRING_HPP_

# include <cstdint>
# include <cstdlib>
# include <cstring>
# include <cstdarg>
# include <type_traits>
# include <limits>

/*

TODO

line 500

- Replace C format to C++ format (using std::enable_if and variadic template)

*/

# include "Objects/Exception.hpp"
# include "Objects/Char.hpp"

namespace						Objects
{
	namespace					Unicode
	{
		namespace				String
		{
			class				Iterator
			{
			private:
				char const	*_current;

			public:
				Iterator(char const * const str)
					: _current(const_cast<char *>(str)) {};

				Iterator(Objects::Unicode::String::Iterator const &copy)
					: _current(const_cast<char *>(copy._current)) {};

				inline Objects::Unicode::String::Iterator	&operator=(Objects::Unicode::String::Iterator const &copy)
					{
						this->_current = copy._current;
						return *this;
					}

				inline bool									operator==(Objects::Unicode::String::Iterator const &it) const
					{
						return (this->_current == it._current);
					}

				inline bool									operator!=(Objects::Unicode::String::Iterator const &it) const
					{
						return (this->_current != it._current);
					}

				inline Objects::Unicode::String::Iterator	&operator++(void)
					{
						this->_current += Objects::Unicode::Char::size(*this->_current);
						return *this;
					}
				inline Objects::Unicode::String::Iterator	&operator--(void)
					{
						while (*(--this->_current) & 0x80 &&
							   Objects::Unicode::Char::size(*this->_current) == 1);
						return *this;
					}
				Objects::Unicode::String::Iterator			operator++(int)
					{
						Objects::Unicode::String::Iterator	it(this->_current);

						this->_current += Objects::Unicode::Char::size(*this->_current);
						return it;
					}
				Objects::Unicode::String::Iterator	  		operator--(int)
					{
						Objects::Unicode::String::Iterator	it(this->_current);

						while (*(--this->_current) & 0x80 &&
							   Objects::Unicode::Char::size(*this->_current) == 1);
						return it;
					}
				inline Objects::Unicode::Char				operator*(void) const
					{
						if (!this->_current)
							throw Objects::Exception(Objects::Exception::READ_NULLPTR);
						return Objects::Unicode::Char(this->_current);
					}
			};
		}
	}

	class						String
	{
	private:
		/* Private Attributes */
		char					*_data;
		uint32_t				_size;
		uint32_t				_unicodeSize;
		uint32_t				_capacity;

		/* Private Static Attributes */
		static uint64_t			_precision;

		/* Private Methods */
		void					lenUnicode(char const * const str); // len + unicode Len
		void					dup(char const * const str,
									uint32_t const size);
		void					copy(char const * const str,
									 uint32_t const size,
									 uint32_t const begin = 0);

		/* Private Static Methods */
		static char				*copy(char *dst, size_t nb);
		static char				*copy(char *dst, ssize_t nb);
		static char				*fcopy(char *dst, float const nb,
									   uint64_t const decPrecision,
									   uint8_t const zero);
		static char				*fcopy(char *dst, double const nb,
									   uint64_t const decPrecision,
									   uint8_t const zero);
		/*static uint32_t			lenFormat(char const *fmt, va_list *originalAp);
		static void				format(char const *fmt,
									   Objects::String &ret,
									   va_list *ap);*/

	public:
		/* Iterator */
		class					Iterator
		{
		private:
			char				*_current;

		public:
			Iterator(char const * const str)
				: _current(const_cast<char *>(str)) {};

			Iterator(Objects::String::Iterator const &copy)
				: _current(const_cast<char *>(copy._current)) {};

			inline Objects::String::Iterator	&operator=(Objects::String::Iterator const &copy)
				{
					this->_current = copy._current;
					return *this;
				}

			inline bool							operator==(Objects::String::Iterator const &it) const
				{
					return (this->_current == it._current);
				}

			inline bool							operator!=(Objects::String::Iterator const &it) const
				{
					return (this->_current != it._current);
				}

			inline Objects::String::Iterator	&operator++(void)
				{
					++this->_current;
					return *this;
				}
			inline Objects::String::Iterator	&operator--(void)
				{
					--this->_current;
					return *this;
				}
			Objects::String::Iterator		   	operator++(int)
				{
					Objects::String::Iterator	it(this->_current);

					++this->_current;
					return it;
				}
			Objects::String::Iterator		   	operator--(int)
				{
					Objects::String::Iterator	it(this->_current);

					--this->_current;
					return it;
				}
			inline char			&operator*(void) const
				{
					if (!this->_current)
						throw Objects::Exception(Objects::Exception::READ_NULLPTR);
					return *this->_current;
				}
		};


		/* ctor & dtor on canonics form */
		String(char const c);
		String(Objects::Unicode::Char const c);
		String(char const * const str = nullptr);
		String(ssize_t const nb);
		String(size_t const nb);
		String(float const nb);
		String(double const nb);
		String(Objects::String const &copy);
		Objects::String			&operator=(Objects::String const &other);
		~String(void);

		inline String(short const nb) : Objects::String(static_cast<ssize_t>(nb))
			{}

		inline String(int const nb) : Objects::String(static_cast<ssize_t>(nb))
			{}

		inline String(unsigned short const nb) : Objects::String(static_cast<size_t>(nb))
			{}

		inline String(unsigned int const nb) : Objects::String(static_cast<size_t>(nb))
			{}

		/* Getters */
		inline uint32_t			capacity(void) const
			{
				return this->_capacity;
			}
		inline uint32_t			size(void) const
			{
				return this->_size;
			}
		inline uint32_t			unicodeSize(void) const
			{
				return this->_unicodeSize;
			}
		inline char				*rawData(void) const
			{
				return this->_data;
			}
		char					&at(uint32_t const i);
		inline char const		&at(uint32_t const i) const
			{
				return this->_data[(i > this->_capacity) ? this->_capacity : i];
			}
		inline Objects::Unicode::Char	unicodeAt(uint32_t const i) const
			{
				return Objects::Unicode::Char(this->_data +
											  ((i > this->_capacity) ?
											  this->_capacity : i));
			}
		inline bool				empty(void) const
			{
				return !this->_size;
			}

		/* Setters */
		void					capacity(uint32_t const capacity);
		void					resize(uint32_t const size);
		void					clear(void);

		/* Operators */
		inline char				*operator*(void) const
			{
				return this->_data;
			}
		inline char				&operator[](uint32_t const i)
			{
				return this->at(i);
			}
		inline char				operator[](uint32_t const i) const
			{
				return this->at(i);
			}

		Objects::String			&operator=(char const c);
		Objects::String			&operator=(Objects::Unicode::Char const c);
		Objects::String			&operator=(char const * const str);
		Objects::String			&operator=(ssize_t const nb);
		Objects::String			&operator=(size_t const nb);
		Objects::String			&operator=(float const nb);
		Objects::String			&operator=(double const nb);

		inline Objects::String	&operator=(short const nb)
			{
				return operator=(static_cast<ssize_t>(nb));
			}
		Objects::String			&operator=(int const nb)
			{
				return operator=(static_cast<ssize_t>(nb));
			}
		Objects::String			&operator=(unsigned short const nb)
			{
				return operator=(static_cast<size_t>(nb));
			}
		Objects::String			&operator=(unsigned int const nb)
			{
				return operator=(static_cast<size_t>(nb));
			}

		inline Objects::String	&operator+=(char const c)
			{
				return this->append(c);
			}
		inline Objects::String	&operator+=(Objects::Unicode::Char const c)
			{
				return this->append(c);
			}
		inline Objects::String	&operator+=(char const * const str)
			{
				return this->append(str);
			}
		inline Objects::String	&operator+=(Objects::String const &str)
			{
				return this->append(str);
			}
		inline Objects::String	&operator+=(short const nb)
			{
				return this->append(nb);
			}
		inline Objects::String	&operator+=(int const nb)
			{
				return this->append(nb);
			}
		inline Objects::String	&operator+=(unsigned short const nb)
			{
				return this->append(nb);
			}
		inline Objects::String	&operator+=(unsigned int const nb)
			{
				return this->append(nb);
			}
		inline Objects::String	&operator+=(ssize_t const nb)
			{
				return this->append(nb);
			}
		inline Objects::String	&operator+=(size_t const nb)
			{
				return this->append(nb);
			}
		inline Objects::String	&operator+=(float const nb)
			{
				return this->append(nb);
			}
		inline Objects::String	&operator+=(double const nb)
			{
				return this->append(nb);
			}

		Objects::String			operator+(char const c) const;
		Objects::String			operator+(Objects::Unicode::Char const c) const;
		Objects::String			operator+(char const * const str) const;
		Objects::String			operator+(Objects::String const &str) const;
		Objects::String			operator+(ssize_t const nb) const;
		Objects::String			operator+(size_t const nb) const;
		Objects::String			operator+(float const nb) const;
		Objects::String			operator+(double const nb) const;

		inline Objects::String	operator+(short const nb) const
			{
				return operator+(static_cast<ssize_t>(nb));
			}
		inline Objects::String	operator+(int const nb) const
			{
				return operator+(static_cast<ssize_t>(nb));
			}
		inline Objects::String	operator+(unsigned short const nb) const
			{
				return operator+(static_cast<size_t>(nb));
			}
		inline Objects::String	operator+(unsigned int const nb) const
			{
				return operator+(static_cast<size_t>(nb));
			}

		inline bool				operator==(char const * const str) const
			{
				return !this->compare(str);
			}
		inline bool				operator==(Objects::String const &str) const
			{
				return !this->compare(str);
			}
		inline bool				operator!=(char const * const str) const
			{
				return this->compare(str);
			}
		inline bool				operator!=(Objects::String const &str) const
			{
				return this->compare(str);
			}
		inline bool				operator>(char const * const str) const
			{
				return this->compare(str) > 0;
			}
		inline bool				operator>(Objects::String const &str) const
			{
				return this->compare(str) > 0;
			}
		inline bool				operator>=(char const * const str) const
			{
				return this->compare(str) >= 0;
			}
		inline bool				operator>=(Objects::String const &str) const
			{
				return this->compare(str) >= 0;
			}
		inline bool				operator<(char const * const str) const
			{
				return this->compare(str) < 0;
			}
		inline bool				operator<(Objects::String const &str) const
			{
				return this->compare(str) < 0;
			}
		inline bool				operator<=(char const * const str) const
			{
				return this->compare(str) <= 0;
			}
		inline bool				operator<=(Objects::String const &str) const
			{
				return this->compare(str) <= 0;
			}

		inline operator bool(void) const
			{
				return !this->empty();
			}

		/* Methods */
		inline Objects::String::Iterator	begin(void) const
			{
				return Objects::String::Iterator(this->_data);
			}
		inline Objects::String::Iterator	end(void) const
			{
				return Objects::String::Iterator((this->_data) ?
												 this->_data + this->_size :
												 nullptr);
			}
		inline Objects::Unicode::String::Iterator	unicodeBegin(void) const
			{
				return Objects::Unicode::String::Iterator(this->_data);
			}
		inline Objects::Unicode::String::Iterator	unicodeEnd(void) const
			{
				return Objects::Unicode::String::Iterator((this->_data) ?
														  this->_data +
														  this->_size :
														  nullptr);
			}
		uint32_t				find(Objects::Unicode::Char const c) const;
		uint32_t				find(char const * const str) const;
		inline uint32_t			find(Objects::String const &str) const
			{
				return this->find(str._data);
			}

		int						compare(char const * const str,
										uint32_t const n = 0,
										uint32_t const begin = 0) const;
		inline int				compare(Objects::String const &str,
										uint32_t const n = 0,
										uint32_t const begin = 0) const
			{
				return this->compare(str._data, n, begin);
			}

		Objects::String			&append(char const c);
		Objects::String			&append(Objects::Unicode::Char const c);
		Objects::String			&append(char const * const str);
		Objects::String			&append(Objects::String const &str);
		Objects::String			&append(ssize_t const nb);
		Objects::String			&append(size_t const nb);
		Objects::String			&append(float const nb);
		Objects::String			&append(double const nb);

		inline Objects::String	&append(short const nb)
			{
				return this->append(static_cast<ssize_t>(nb));
			}
		inline Objects::String	&append(int const nb)
			{
				return this->append(static_cast<ssize_t>(nb));
			}
		inline Objects::String	&append(unsigned short const nb)
			{
				return this->append(static_cast<size_t>(nb));
			}
		inline Objects::String	&append(unsigned int const nb)
			{
				return this->append(static_cast<size_t>(nb));
			}

		void					shift(uint32_t const nbLeftBytes);
		Objects::String			uppercase(void) const;
		Objects::String			lowercase(void) const;
		Objects::String			reverse(void) const;
		Objects::String			substr(uint32_t const begin,
									   uint32_t size) const;
		Objects::String			substr(uint32_t const begin,
									   Objects::Unicode::Char const end) const;
		inline Objects::String	substr(uint32_t const begin) const
			{
				return this->substr(begin, this->_size - begin);
			}
		inline Objects::String	substr(Objects::Unicode::Char const begin,
									   Objects::Unicode::Char const end) const
			{
				return this->substr(static_cast<uint32_t>(this->find(begin)),
									end);
			}


        /**
         * FORMAT METHODS
         */

        template<typename Param>
        inline static uint32_t  lenFormat(typename std::enable_if<std::numeric_limits<Param>::is_integer, Param>::type const &param)
            {
                return Objects::String::len<Param>(param);
            }

        template<typename Param>
        inline static uint32_t  lenFormat(typename std::enable_if<!std::numeric_limits<Param>::is_integer, Param>::type const &param)
            {
                return Objects::String::len(param);
            }

        inline static uint32_t  lenFormat(char const *fmt)
            {
                return Objects::String::len(fmt);
            }

        template<typename Param, typename... VarArgs>
        static uint32_t         lenFormat(char const *fmt, Param const &param,
                                          VarArgs const &... args)
            {
                uint32_t        len = 0;

                while (*fmt)
                {
                    if (*fmt == '$' && *(fmt + 1) == '[')
                    {
                        char const *it = fmt + 2;

                        while (*it && *it != ']')
                            ++it;
                        if (*it == ']')
                            return len + Objects::String::lenFormat<Param>(param) + Objects::String::lenFormat(it + 1, args...);
                    }
                    ++fmt;
                    ++len;
                }
                return len;
            }

        inline static void      generateStringFormat(Objects::String &str, char const *fmt)
            {
                str += fmt;
            }

        template<typename Param, typename... VarArgs>
        static void             generateStringFormat(Objects::String &str, char const *fmt,
                                                     Param const &param, VarArgs const &... args)
            {
                while (*fmt)
                {
                    if (*fmt == '$' && *(fmt + 1) == '[')
                    {
                        char const *it = fmt + 2;

                        while (*it && *it != ']')
                            ++it;
                        if (*it == ']')
                        {
                            str += param;
                            Objects::String::generateStringFormat(str, it + 1, args...);
                            return ;
                        }

                    }
                    str += *fmt++;
                }
            }

        template<typename Param>
        static Objects::String  format(char const * const fmt)
            {
                Objects::String ret;

                ret.capacity(Objects::String::lenFormat(fmt));
                Objects::String::generateStringFormat(ret, fmt);
                return ret;
            }

        template<typename Param, typename... VarArgs>
        static Objects::String  format(char const * const fmt, Param const &param,
                                       VarArgs... args)
            {
                Objects::String ret;

                ret.capacity(Objects::String::lenFormat(fmt, param, args...));
                Objects::String::generateStringFormat(ret, fmt, param, args...);
                return ret;
            }


		/* Static Methods */
/*		static Objects::String	format(char const * const fmt, ...);
		static Objects::String	format(Objects::String const fmt, ...);
		inline static Objects::String	format(char const * const fmt,
											   va_list *ap)
			{
				Objects::String			ret;

				Objects::String::format(fmt, ret, ap);
				return ret;
			}
		inline static Objects::String	format(Objects::String const fmt,
											   va_list *ap)
			{
				return Objects::String::format(*fmt, ap);
                }*/

		static void				setPrecision(uint8_t precision);

		/* Tools Static Methods */
        inline static uint32_t  len(char const * const str)
            {
                return ::strlen(str);
            }
        inline static uint32_t  len(Objects::String const &str)
            {
                return str.size();
            }

        template<typename _TypeUInt = size_t>
        static uint32_t         len(typename std::enable_if<std::numeric_limits<_TypeUInt>::is_integer && std::is_unsigned<_TypeUInt>::value, _TypeUInt>::type nb)
            {
                uint32_t        len = 1;

                while ((nb = nb / 10) > 0)
                    ++len;
                return len;
            }

        template<typename _TypeInt = ssize_t>
        static uint32_t         len(typename std::enable_if<std::numeric_limits<_TypeInt>::is_integer && std::is_signed<_TypeInt>::value, _TypeInt>::type nb)
            {
                typedef typename std::make_unsigned<_TypeInt>::type _TypeUInt;

                if (nb < 0)
                    return (1 + Objects::String::len<_TypeUInt>(static_cast<_TypeUInt>(-nb)));
                return Objects::String::len<_TypeUInt>(static_cast<_TypeUInt>(nb));
            }

        static uint32_t			len(float const nb);
		static uint32_t			len(float const nb,
									uint64_t &decPrecision,
									uint8_t &zero);
        static uint32_t			len(double const nb);
		static uint32_t			len(double const nb,
									uint64_t &decPrecision,
									uint8_t &zero);
	};
}

/* EXTRA OPERATOR + */

Objects::String					operator+(char const c,
										  Objects::String const &str);
Objects::String					operator+(Objects::Unicode::Char const c,
										  Objects::String const &str);
Objects::String					operator+(char const * const s1,
										  Objects::String const &str);
Objects::String					operator+(ssize_t const nb,
										  Objects::String const &str);
Objects::String					operator+(size_t const nb,
										  Objects::String const &str);
Objects::String					operator+(float const nb,
										  Objects::String const &str);
Objects::String					operator+(double const nb,
										  Objects::String const &str);

inline Objects::String			operator+(short const nb,
										  Objects::String const &str)
{
	return ::operator+(static_cast<ssize_t>(nb), str);
}

inline Objects::String			operator+(int const nb,
										  Objects::String const &str)
{
	return ::operator+(static_cast<ssize_t>(nb), str);
}

inline Objects::String			operator+(unsigned short const nb,
										  Objects::String const &str)
{
	return ::operator+(static_cast<size_t>(nb), str);
}

inline Objects::String			operator+(unsigned int const nb,
										  Objects::String const &str)
{
	return ::operator+(static_cast<size_t>(nb), str);
}

# include <iostream>

inline std::ostream				&operator<<(std::ostream &os,
											Objects::String const &str)
{
	os << ((str.empty()) ? "NULL" : *str);
	return os;
}

#endif /* !OBJECTS_STRING_HPP_ */
