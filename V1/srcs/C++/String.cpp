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
		this->_data = static_cast<char *>(
			Objects::Memory::alloc(sizeof(char)
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

	/* String */
	String::String(char const * const str)
		: PrivateString(str)
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
			Objects::Memory::free(reinterpret_cast<void *&>(this->_data));
			this->_size = other._size;
			this->_unicodeSize = other._unicodeSize;
			this->_capacity = other._capacity;
			if (other._data)
				this->dup(reinterpret_cast<char const *>(other._data),
						  this->_capacity);
		}
		return *this;
	}

	String::~String(void)
	{
		Objects::Memory::free(reinterpret_cast<void *&>(this->_data));
	}

	/* Setters */

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

	char						&String::at(size_t const i)
	{
		if (i > this->_capacity)
			this->capacity(i);
		return this->_data[i];
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

	Objects::String				&String::operator+=(char const * const str)
	{
		Objects::String			tmp;
		size_t					freeSpace = this->_capacity - this->_size;

		tmp.len(str);
		if (tmp._capacity > freeSpace)
			this->capacity(this->_capacity + (tmp._capacity - freeSpace));
		this->copy(str, tmp._capacity, this->_size);
		this->_size += tmp._size;
		this->_unicodeSize += tmp._unicodeSize;
		return *this;
	}

	Objects::String				&String::operator+=(Objects::String const &str)
	{
		size_t					freeSpace = this->_capacity - this->_size;

		if (str._capacity > freeSpace)
			this->capacity(this->_capacity + (str._capacity - freeSpace));
		this->copy(reinterpret_cast<char const * const>(str._data),
				   str._capacity, this->_size);
		this->_size += str._size;
		this->_unicodeSize += str._unicodeSize;
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

	size_t						String::find(Objects::Unicode::Char c) const
	{
		size_t					f = 0;

		for (Objects::Unicode::String::Iterator it = this->unicodeBegin();
			 it != this->unicodeEnd() && !(*it == c); ++it)
			f += (*it).size();
		return f;
	}

	int							String::compare(char const * const str,
												size_t n,
												size_t const begin) const
	{
		Objects::String			tmp;
		int						ret;

		tmp.len(str);
		tmp._data = const_cast<char *>(str);
		ret = this->compare(tmp, n, begin);
		tmp._data = nullptr;
		return ret;
	}

	int							String::compare(Objects::String const &str,
												size_t n,
												size_t const begin) const
	{
		int						ret = (str._data) ? -1 : 1;

		if (this->_data && begin < this->_capacity)
			ret = (!n) ? strcmp(this->_data + begin, str._data) :
				strncmp(this->_data + begin, str._data, n);
		return (this->_data == str._data) ? 0 : ret;
	}
}