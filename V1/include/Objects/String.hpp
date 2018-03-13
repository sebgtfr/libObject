/**
* \file				String.hpp
* \author			Sébastien Le Maire
* \version			1.0
* \date				12 Mars 2018
*/

#ifndef OBJECTS_STRING_HPP_
# define OBJECTS_STRING_HPP_

# include <stdint.h>
# include <stdlib.h>
# include "Objects/Char.h"
# include "Objects/Bool.h"

# ifdef __cplusplus

# include "Objects/Exception.hpp"

namespace						Objects
{
# endif /* !CPLUSPLUS */

	struct						PrivateString
	{
		char					*_data;
		size_t					_size;
		size_t					_unicodeSize;
		size_t					_capacity;

# ifdef __cplusplus

		PrivateString(char const * const str);
		PrivateString(Objects::PrivateString const &str);

	protected:
		void					len(char const * const str);
		void					dup(char const * const str,
									size_t const size);
		void					copy(char const * const str,
									 size_t const size,
									 size_t const begin = 0);

#  define __SIZEOF_STRING__		sizeof(Objects::PrivateString)

# else

#  define __SIZEOF_STRING__		sizeof(struct PrivateString)

# endif /* !CPLUSPLUS*/
	};

	struct						PrivateStringIterator
	{
		char					*_current;

# ifdef __cplusplus

		PrivateStringIterator(char const * const str)
			: _current(const_cast<char *>(str)) {};

		inline PrivateStringIterator	&operator=(Objects::PrivateStringIterator const &copy)
			{
				this->_current = copy._current;
				return *this;
			}

		inline bool			operator==(Objects::PrivateStringIterator const &it)
			{
				return (this->_current == it._current);
			}
		inline bool			operator!=(Objects::PrivateStringIterator const &it)
			{
				return (this->_current != it._current);
			}

#  define __SIZEOF_STRING_ITERATOR__		sizeof(Objects::PrivateStringIterator)

# else

#  define __SIZEOF_STRING_ITERATOR__		sizeof(struct PrivateStringIterator)

# endif /* !CPLUSPLUS*/
	};


# ifdef __cplusplus
	namespace				Unicode
	{
		namespace			String
		{
			class			Iterator : public Objects::PrivateStringIterator
			{
			public:
				Iterator(char const * const str)
					: Objects::PrivateStringIterator(str) {};

				inline Objects::Unicode::String::Iterator	&operator++(void)
					{
						this->_current += Objects::Unicode::Char::size(*this->_current);
						return *this;
					}
				inline Objects::Unicode::String::Iterator	&operator--(void)
					{
						int8_t								i = -1;

						while (this->_current[i] & 0x80 &&
							   Objects::Unicode::Char::size(this->_current[i]) == 1)
							--i;
						this->_current += i;
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
						int8_t								i = -1;

						while (this->_current[i] & 0x80 &&
							   Objects::Unicode::Char::size(this->_current[i]) == 1)
							--i;
						this->_current += i;
						return it;
					}
				inline Objects::Unicode::Char				operator*(void)
					{
						if (!this->_current)
							throw Objects::Exception(Objects::Exception::READ_NULLPTR);
						return Objects::Unicode::Char(this->_current);
					}
			};
		}
	}

	class						String : private Objects::PrivateString
	{
	public:
		/* Iterator */
		class					Iterator : public Objects::PrivateStringIterator
		{
		public:
			Iterator(char const * const str)
				: Objects::PrivateStringIterator(str) {};

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
			inline char			&operator*(void)
				{
					if (!this->_current)
						throw Objects::Exception(Objects::Exception::READ_NULLPTR);
					return *this->_current;
				}
		};


		/* ctor & dtor on canonics form */
		String(char const * const str = nullptr);
		String(Objects::String const &copy);
		Objects::String			&operator=(Objects::String const &other);
		~String(void);

		/* Getters */
		inline size_t			capacity(void) const
			{
				return this->_capacity;
			}
		inline size_t			size(void) const
			{
				return this->_size;
			}
		inline size_t			unicodeSize(void) const
			{
				return this->_unicodeSize;
			}
		inline char			*rawData(void) const
			{
				return this->_data;
			}
		char					&at(size_t const i);
		inline char const		&at(size_t const i) const
			{
				return this->_data[(i > this->_capacity) ? this->_capacity : i];
			}
		inline Objects::Unicode::Char	unicodeAt(size_t const i) const
			{
				return Objects::Unicode::Char(this->_data +
											  ((i > this->_capacity) ?
											  this->_capacity : i));
			}
		bool					empty(void) const
			{
				return !this->_size;
			}

		/* Setters */
		void					capacity(size_t const capacity);
		void					resize(size_t const size);

		/* Operator */
		inline char				*operator*(void) const
			{
				return this->_data;
			}
		inline char				&operator[](size_t const i)
			{
				return this->at(i);
			}
		inline char				operator[](size_t const i) const
			{
				return this->at(i);
			}
		Objects::String			&operator=(char const * const str);
		Objects::String			&operator+=(char const * const str);
		Objects::String			&operator+=(Objects::String const &str);
		Objects::String			operator+(char const * const str);
		Objects::String			operator+(Objects::String const &str);
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
		size_t					find(Objects::Unicode::Char const c) const;
		int						compare(char const * const str,
										size_t const n = 0,
										size_t const begin = 0) const;
		inline int				compare(Objects::String const &str,
										size_t const n = 0,
										size_t const begin = 0) const
			{
				return this->compare(str._data, n, begin);
			}
		Objects::String			uppercase(void) const;
		Objects::String			lowercase(void) const;
		Objects::String			reverse(void) const;
		Objects::String			substr(size_t const begin,
									   size_t size) const;
	};
}

# include <iostream>

inline std::ostream				&operator<<(std::ostream &os,
											Objects::String const &str)
{
	os << ((str.empty()) ? "NULL" : *str);
	return os;
}

# endif /* !CPLUSPLUS */


#endif /* !OBJECTS_STRING_HPP_ */
