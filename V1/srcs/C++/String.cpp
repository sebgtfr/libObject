/**
* \file				String.cpp
* \author			Sébastien Le Maire
* \version			1.0
* \date				25 Février 2018
*/

#include "Objects/Memory.hpp"
#include "Objects/String.hpp"

namespace						Objects
{
	/* Private String */
	PrivateString::PrivateString(char const c)
		: _data(nullptr), _size(1), _unicodeSize(1), _capacity(1)
	{
		this->_data = static_cast<char *>(Objects::Memory::alloc(sizeof(char)
																 * 2));
		this->_data[0] = c;
		this->_data[1] = '\0';
	}

	PrivateString::PrivateString(ssize_t const nb)
		: _data(nullptr), _size(0), _unicodeSize(0),
		  _capacity(Objects::PrivateString::len(nb))
	{
		this->_data = static_cast<char *>(Objects::Memory::alloc(sizeof(char)
																 * (this->_capacity + 1)));
		this->_size = this->_unicodeSize = this->_capacity;
		Objects::PrivateString::copy(this->_data, nb);
		this->_data[this->_size] = '\0';
	}

	PrivateString::PrivateString(size_t const nb)
		: _data(nullptr), _size(0), _unicodeSize(0),
		  _capacity(Objects::PrivateString::len(nb))
	{
		this->_data = static_cast<char *>(Objects::Memory::alloc(sizeof(char)
																 * (this->_capacity + 1)));
		this->_size = this->_unicodeSize = this->_capacity;
		Objects::PrivateString::copy(this->_data, nb);
		this->_data[this->_size] = '\0';
	}

	PrivateString::PrivateString(float const nb)
		: _data(nullptr), _size(0), _unicodeSize(0),
		  _capacity(Objects::PrivateString::len(nb))
	{
		this->_data = static_cast<char *>(Objects::Memory::alloc(sizeof(char)
																 * (this->_capacity + 1)));
		this->_size = this->_unicodeSize = this->_capacity;
		Objects::PrivateString::copy(this->_data, nb);
		this->_data[this->_size] = '\0';
	}

	PrivateString::PrivateString(double const nb)
		: _data(nullptr), _size(0), _unicodeSize(0),
		  _capacity(Objects::PrivateString::len(nb))
	{
		this->_data = static_cast<char *>(Objects::Memory::alloc(sizeof(char)
																 * (this->_capacity + 1)));
		this->_size = this->_unicodeSize = this->_capacity;
		Objects::PrivateString::copy(this->_data, nb);
		this->_data[this->_size] = '\0';
	}

	PrivateString::PrivateString(char const * const str)
		: _data(nullptr), _size(0), _unicodeSize(0), _capacity(0)
	{
		if (str)
		{
			this->len(str);
			this->dup(str, this->_capacity);
		}
	}

	PrivateString::PrivateString(Objects::PrivateString const &copy)
		: _data(nullptr), _size(copy._size), _unicodeSize(copy._unicodeSize),
		  _capacity(copy._capacity)
	{
		if (copy._data)
			this->dup(reinterpret_cast<char const *>(copy._data), this->_capacity);
	}

	/* Methods */

	void						PrivateString::len(char const * const str)
	{
		int8_t					unicodeSize = 0;

		for (char const *tmp = str; *tmp; tmp += unicodeSize)
		{
			unicodeSize = Objects::Unicode::Char::size(*tmp);
			this->_size += unicodeSize;
			++this->_unicodeSize;
		}
		this->_capacity = this->_size;
	}

	void						PrivateString::dup(char const * const str,
												   size_t const size)
	{
		this->_data = static_cast<char *>(Objects::Memory::alloc(sizeof(char)
																 * (size + 1)));
		this->copy(str, size);
	}

	void						PrivateString::copy(char const * const str,
													size_t const size,
													size_t const begin)
	{
		Objects::Memory::copy(reinterpret_cast<void *>(this->_data + begin),
							  reinterpret_cast<void const *>(str),
							  size);
		this->_data[size + begin] = '\0';
	}

	char						*PrivateString::copy(char *dst,
													size_t nb)
	{
		if (nb > 10)
			dst = Objects::PrivateString::copy(dst, nb / 10);
		*(dst++) = nb % 10 + '0';
		return dst;
	}

	char						*PrivateString::copy(char *dst,
													ssize_t nb)
	{
		if (nb < 0)
		{
			*dst = '-';
			return Objects::PrivateString::copy(++dst, static_cast<size_t>(-nb));
		}
		return Objects::PrivateString::copy(dst, static_cast<size_t>(nb));
	}

	char						*PrivateString::copy(char *dst,
													 float nb)
	{
		dst = Objects::PrivateString::copy(dst, static_cast<ssize_t>(nb));
		if ((nb - static_cast<ssize_t>(nb)) != 0.0f)
			*(dst++) = '.';
		if (nb < 0)
			nb = -nb;
		while ((nb = (nb - static_cast<ssize_t>(nb)) * 10) != 0.0f)
			*(dst++) = static_cast<ssize_t>(nb) + '0';
		return (dst);
	}

	char						*PrivateString::copy(char *dst,
													 double nb)
	{
		dst = Objects::PrivateString::copy(dst, static_cast<ssize_t>(nb));
		if ((nb - static_cast<ssize_t>(nb)) != 0.0d)
			*(dst++) = '.';
		if (nb < 0)
			nb = -nb;
		while ((nb = (nb - static_cast<ssize_t>(nb)) * 10) != 0.0d)
			*(dst++) = static_cast<ssize_t>(nb) + '0';
		return (dst);
	}

	size_t						PrivateString::len(size_t nb)
	{
		size_t					len = 1;

		while ((nb = nb / 10) > 0)
			++len;
		return len;
	}

	size_t						PrivateString::len(ssize_t nb)
	{
		if (nb < 0)
			return (1 + Objects::PrivateString::len(static_cast<size_t>(-nb)));
		return Objects::PrivateString::len(static_cast<size_t>(nb));
	}

	size_t						PrivateString::len(float nb)
	{
		size_t					len = Objects::PrivateString::len(static_cast<ssize_t>(nb));
		size_t					declen = 0;

		while ((nb = (nb - static_cast<ssize_t>(nb)) * 10) != 0.0d)
			++declen;
		if (declen)
			++declen;
		return len + declen;
	}

	size_t						PrivateString::len(double nb)
	{
		size_t					len = Objects::PrivateString::len(static_cast<ssize_t>(nb));
		size_t					declen = 0;

		while ((nb = (nb - static_cast<ssize_t>(nb)) * 10) != 0.0d)
			++declen;
		if (declen)
			++declen;
		return len + declen;
	}

	/* String */

	String::String(char const c)
		: PrivateString(c)
	{
	}

	String::String(Objects::Unicode::Char const c)
		: PrivateString(c.toString()._char)
	{
	}

	String::String(char const * const str)
		: PrivateString(str)
	{
	}

	String::String(short const nb)
		: PrivateString(static_cast<ssize_t const>(nb))
	{
	}

	String::String(int const nb)
		: PrivateString(static_cast<ssize_t const>(nb))
	{
	}

	String::String(ssize_t const nb)
		: PrivateString(nb)
	{
	}

	String::String(unsigned short const nb)
		: PrivateString(static_cast<size_t const>(nb))
	{
	}

	String::String(unsigned int const nb)
		: PrivateString(static_cast<size_t const>(nb))
	{
	}

	String::String(size_t const nb)
		: PrivateString(nb)
	{
	}

	String::String(float const nb)
		: PrivateString(nb)
	{
	}

	String::String(double const nb)
		: PrivateString(nb)
	{
	}

	String::String(Objects::String const &copy)
		: PrivateString(copy)
	{
	}

	Objects::String				&String::operator=(Objects::String const &other)
	{
		if (&other != this)
		{

			this->_size = other._size;
			this->_unicodeSize = other._unicodeSize;
			if (this->_capacity != other._capacity)
			{
				this->_capacity = other._capacity;
				Objects::Memory::free(reinterpret_cast<void *&>(this->_data));
				this->_data = static_cast<char *>(Objects::Memory::alloc(sizeof(char)
																		 * (this->_capacity + 1)));
			}
			if (other._data)
				this->copy(reinterpret_cast<char const *>(other._data),
						   this->_capacity);
		}
		return *this;
	}

	String::~String(void)
	{
		Objects::Memory::free(reinterpret_cast<void *&>(this->_data));
	}

	/* Setters */

	char						&String::at(size_t const i)
	{
		if (i > this->_capacity)
			this->capacity(i);
		return this->_data[i];
	}

	void						String::capacity(size_t const capacity)
	{
		if (capacity != this->_capacity)
		{
			if ((this->_capacity = capacity) > 0)
			{
				this->_data = static_cast<char *>(
					Objects::Memory::realloc(reinterpret_cast<void *>(this->_data),
											 sizeof(char)
											 * (this->_capacity + 1)));
				this->_data[this->_capacity] = '\0';
			}
			else
				Objects::Memory::free(reinterpret_cast<void *&>(this->_data));
			if (this->_capacity < this->_size)
			{
				this->_size = this->_unicodeSize = 0;
				this->len(reinterpret_cast<char const * const>(this->_data));
			}
		}
	}

	void						String::resize(size_t const size)
	{
		if (this->_size != size)
		{
			if (size > this->_capacity)
				this->capacity(size);
			this->_size = size;
		}
	}

	void						String::clear(void)
	{
		if (this->_data)
		{
			this->_size = 0;
			this->_data[0] = '\0';
		}
	}

	/* Operator */

	Objects::String				&String::operator=(char const * const str)
	{
		if (str != reinterpret_cast<char const * const>(this->_data))
		{
			Objects::Memory::free(reinterpret_cast<void *&>(this->_data));
			this->_size = 0;
			this->_unicodeSize = 0;
			this->_capacity = 0;
			if (str)
			{
				this->len(str);
				this->dup(str, this->_capacity);
			}
		}
		return *this;
	}

	Objects::String				String::operator+(char const * const str)
	{
		Objects::String			ret;
		Objects::String			tmp;

		tmp.len(str);
		ret.capacity(this->_capacity + tmp._capacity);
		ret.copy(reinterpret_cast<char const * const>(this->_data),
				 this->_size);
		ret.copy(str, tmp._size, this->_size);
		ret._size = this->_size + tmp._size;
		ret._unicodeSize = this->_unicodeSize + tmp._unicodeSize;
		return ret;
	}

	Objects::String				String::operator+(Objects::String const &str)
	{
		Objects::String			ret;

		ret.capacity(this->_capacity + str._capacity);
		ret.copy(reinterpret_cast<char const * const>(this->_data),
				 this->_size);
		ret.copy(*str, str._size, this->_size);
		ret._size = this->_size + str._size;
		ret._unicodeSize = this->_unicodeSize + str._unicodeSize;
		return ret;
	}

	/* Methods */

	size_t						String::find(Objects::Unicode::Char const c) const
	{
		size_t					f = 0;

		for (Objects::Unicode::String::Iterator it = this->unicodeBegin();
			 it != this->unicodeEnd() && !(*it == c); ++it)
			f += (*it).size();
		return f;
	}

	size_t						String::find(char const * const str) const
	{
		char const				*i = this->_data;
		char const				*istr = str;

		while (*i && *istr)
		{
			istr = (*i == *istr) ? (istr + 1) : str;
			++i;
		}
		return static_cast<size_t>(i - this->_data - (istr - str));
	}

	int							String::compare(char const * const str,
												size_t const n,
												size_t const begin) const
	{
		int						ret = (str) ? -1 : 1;

		if (str && this->_data && begin < this->_capacity)
			ret = (!n) ? strcmp(this->_data + begin, str) :
				strncmp(this->_data + begin, str, n);
		return (this->_data == str) ? 0 : ret;
	}

	Objects::String				&String::append(char const * const str)
	{
		Objects::String			tmp;
		size_t					freeSpace = this->_capacity - this->_size;

		tmp.len(str);
		if (tmp._size > freeSpace)
			this->capacity(this->_capacity + (tmp._size - freeSpace));
		this->copy(str, tmp._size, this->_size);
		this->_size += tmp._size;
		this->_unicodeSize += tmp._unicodeSize;
		return *this;
	}

	Objects::String				&String::append(Objects::String const &str)
	{
		size_t					freeSpace = this->_capacity - this->_size;

		if (str._size > freeSpace)
			this->capacity(this->_capacity + (str._size - freeSpace));
		this->copy(reinterpret_cast<char const * const>(str._data),
				   str._size, this->_size);
		this->_size += str._size;
		this->_unicodeSize += str._unicodeSize;
		return *this;
	}

	void						String::shift(size_t const nbLeftBytes)
	{
		if (this->_data)
		{
			if (nbLeftBytes >= this->_size)
				this->clear();
			else
			{
				this->_size -= nbLeftBytes;
				Objects::Memory::move(static_cast<void *>(this->_data),
									  static_cast<void const *>(this->_data
																+ nbLeftBytes),
									  this->_size);
				this->_data[this->_size] = '\0';
			}
		}
	}

	Objects::String				String::uppercase(void) const
	{
		Objects::String			ret;
		size_t					i = 0;

		ret.capacity(this->_capacity);
		ret._size = this->_size;
		ret._unicodeSize = this->_unicodeSize;
		for (Objects::String::Iterator it = this->begin();
			 it != this->end(); ++it)
		{
			char				c = *it;

			ret[i++] = ((c >= 'a' && c <= 'z') ? (c - 32) : c);
		}
		return ret;
	}

	Objects::String				String::lowercase(void) const
	{
		Objects::String			ret;
		size_t					i = 0;

		ret.capacity(this->_capacity);
		ret._size = this->_size;
		ret._unicodeSize = this->_unicodeSize;
		for (Objects::String::Iterator it = this->begin();
			 it != this->end(); ++it)
		{
			char				c = *it;

			ret[i++] = ((c >= 'A' && c <= 'Z') ? (c + 32) : c);
		}
		return ret;
	}

	Objects::String				String::reverse(void) const
	{
		Objects::String			ret;
		size_t					i = this->_capacity;

		ret.capacity(this->_capacity);
		ret._size = this->_size;
		ret._unicodeSize = this->_unicodeSize;
		for (Objects::Unicode::String::Iterator it = this->unicodeBegin();
			 it != this->unicodeEnd(); ++it)
		{
			Objects::Unicode::Char	c = *it;
			uint8_t					unicodeLen = c.size();
			uint8_t					j = 0;

			i -= unicodeLen;
			for (int8_t b = 24; j < unicodeLen && b >= 0; b -= 8)
			{
				uint8_t					uc = (uint8_t)((*c >> b) & 0xFF);

				if (uc)
					ret[i + j++] = uc;
			}
		}
		return ret;
	}

	Objects::String				String::substr(size_t const begin,
											   size_t size) const
	{
		Objects::String			ret;

		if (size && begin < this->_size)
		{
			if ((begin + size) > this->_size)
				size = this->_size - begin;
			ret.dup(reinterpret_cast<char const *>(this->_data + begin), size);
			ret._capacity = size;
			ret.len(ret._data);
		}
		return ret;
	}

	Objects::String				String::substr(size_t const begin,
											   Objects::Unicode::Char const end) const
	{
		if (begin < this->_size)
		{
			size_t				f = 0;

			for (Objects::Unicode::String::Iterator it = this->_data + begin;
				 it != this->unicodeEnd() && !(*it == end); ++it)
				f += (*it).size();
			return this->substr(begin, f + ((this->_data[f]) ? 1 : 0));
		}
		return Objects::String();
	}
}
