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
	uint64_t					Objects::String::_precision = 10000;

	/* Private Methods */

	void						String::lenUnicode(char const * const str)
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

	void						String::dup(char const * const str,
											uint32_t const size)
	{
		this->_data = Objects::Memory::alloc<char>(size + 1);
		this->copy(str, size);
	}

	void						String::copy(char const * const str,
											 uint32_t const size,
											 uint32_t const begin)
	{
		Objects::Memory::copy<char>(this->_data + begin, str, size);
		this->_data[size + begin] = '\0';
	}

	/* Private Static Methods */

	char						*String::copy(char *dst, size_t nb)
	{
		if (nb > 10)
			dst = Objects::String::copy(dst, nb / 10);
		*(dst++) = nb % 10 + '0';
		return dst;
	}

	char						*String::copy(char *dst, ssize_t nb)
	{
		if (nb < 0)
		{
			*dst = '-';
			return Objects::String::copy(++dst, static_cast<size_t>(-nb));
		}
		return Objects::String::copy(dst, static_cast<size_t>(nb));
	}

	char						*String::fcopy(char *dst, float const nb,
											   uint64_t const decPrecision,
											   uint8_t const zero)
	{
		ssize_t const			castNb = static_cast<ssize_t>(nb);
		uint64_t				decNb = (nb * decPrecision -
										 castNb * decPrecision);

		dst = Objects::String::copy(dst, castNb);
		*(dst++) = '.';
		for (char const *end = dst + zero; dst < end; ++dst)
			*dst = '0';
		dst = Objects::String::copy(dst, decNb);
		return (dst);
	}

	char						*String::fcopy(char *dst, double const nb,
											   uint64_t const decPrecision,
											   uint8_t const zero)
	{
		ssize_t const			castNb = static_cast<ssize_t>(nb);
		uint64_t				decNb = (nb * decPrecision -
										 castNb * decPrecision);

		dst = Objects::String::copy(dst, castNb);
		*(dst++) = '.';
		for (char const *end = dst + zero; dst < end; ++dst)
			*dst = '0';
		dst = Objects::String::copy(dst, decNb);
		return (dst);
	}

	/* Format */
/*	uint32_t					String::lenFormat(char const *fmt,
    va_list *originalAp)
	{
    uint32_t				len = 0;
    va_list					ap;

    va_copy(ap, *originalAp);
    while (*fmt)
    {
    if (*fmt == '%')
    {
    char const		*it = fmt + 1;
    unsigned char	intPrecision = 0;
    unsigned char	decPrecision = 0;

    while (*it >= '0' && *it <= '9')
    {
    intPrecision = intPrecision * 10 + (*it - '0');
    ++it;
    }
    if (*it == '.')
    while (*(++it) >= '0' && *it <= '9')
    decPrecision = decPrecision * 10 + (*it - '0');
    switch (*it)
    {
    case 's':
    if (!intPrecision && !decPrecision)
    {
    len += ::strlen(static_cast<char *>(va_arg(ap, char *)));
    fmt = it;
    }
    break;
    case 'd':
    if (!decPrecision)
    {
    uint32_t	lenInt = Objects::String::len(static_cast<ssize_t>(va_arg(ap, int)));

    len += (lenInt < intPrecision) ? intPrecision : lenInt;
    fmt = it;
    }
    break;
    case 'u':
    if (!decPrecision)
    {
    uint32_t	lenInt = Objects::String::len(static_cast<size_t>(va_arg(ap, unsigned int)));

    len += (lenInt < intPrecision) ? intPrecision : lenInt;
    fmt = it;
    }
    break;
    case 'f':
    Objects::String::setPrecision(decPrecision);

    double		val = static_cast<double>(va_arg(ap, double));
    uint32_t	lenVal = Objects::String::len(val);
    uint32_t	lenValCast = Objects::String::len(static_cast<ssize_t>(lenVal));

    if (lenValCast < intPrecision)
    lenVal += (intPrecision - lenValCast);
    len = lenVal;
    fmt = it;
    break;
    }
    if (*fmt == '%')
    ++len;
    }
    else
    ++len;
    ++fmt;
    }
    return len;
	}

	void						String::format(char const *fmt,
    Objects::String &ret,
    va_list *ap)
	{
    ret.capacity(Objects::String::lenFormat(fmt, ap));
    while (*fmt)
    {
    if (*fmt == '%')
    {
    char const		*it = fmt + 1;
    unsigned char	intPrecision = 0;
    unsigned char	decPrecision = 0;

    while (*it >= '0' && *it <= '9')
    {
    intPrecision = intPrecision * 10 + (*it - '0');
    ++it;
    }
    if (*it == '.')
    while (*(++it) >= '0' && *it <= '9')
    decPrecision = decPrecision * 10 + (*it - '0');
    switch (*it)
    {
    case 's':
    if (!intPrecision && !decPrecision)
    {
    ret += static_cast<char *>(va_arg(*ap, char *));
    fmt = it;
    }
    break;
    case 'd':
    if (!decPrecision)
    {
    ssize_t const	tmp = static_cast<ssize_t>(va_arg(*ap, int));
    uint32_t	lenInt = Objects::String::len(tmp);

    while (lenInt < intPrecision)
    {
    ret += '0';
    ++lenInt;
    }
    ret += tmp;
    fmt = it;
    }
    break;
    case 'u':
    if (!decPrecision)
    {
    size_t const	tmp = static_cast<size_t>(va_arg(*ap, unsigned int));
    uint32_t		lenInt = Objects::String::len(tmp);

    while (lenInt < intPrecision)
    {
    ret += '0';
    ++lenInt;
    }
    ret += tmp;
    fmt = it;
    }
    break;
    case 'f':
    Objects::String::setPrecision(decPrecision);

    double		val = static_cast<double>(va_arg(*ap, double));
    uint64_t	valDecPrecision;
    uint8_t		zero;
    uint32_t	lenVal = Objects::String::len(val, valDecPrecision, zero);
    uint32_t	lenValCast = Objects::String::len(static_cast<ssize_t>(lenVal));

    if (lenValCast < intPrecision)
    {
    ret += '0';
    ++lenValCast;
    }
    ret += val;
    fmt = it;
    break;
    }
    if (*fmt == '%')
    ret += '%';
    }
    else
    ret += *fmt;
    ++fmt;
    }
    }*/

	/* Public */

	String::String(char const c)
		: _data(nullptr), _size(1), _unicodeSize(1), _capacity(1)
	{
		this->_data = Objects::Memory::alloc<char>(2);
		this->_data[0] = c;
		this->_data[1] = '\0';
	}

	String::String(Objects::Unicode::Char const c)
		: _data(nullptr), _size(c.size()), _unicodeSize(1), _capacity(_size)
	{
		this->dup(c.toString()._char, this->_capacity);
	}

	String::String(char const * const str)
		: _data(nullptr), _size(0), _unicodeSize(0), _capacity(0)
	{
		if (str)
		{
			this->lenUnicode(str);
			this->dup(str, this->_capacity);
		}
	}

	String::String(ssize_t const nb)
		: _data(nullptr), _size(Objects::String::len(nb)),
		  _unicodeSize(_size), _capacity(_size)
	{
		this->_data = Objects::Memory::alloc<char>(this->_capacity + 1);
		Objects::String::copy(this->_data, nb);
		this->_data[this->_size] = '\0';
	}

	String::String(size_t const nb)
		: _data(nullptr), _size(Objects::String::len(nb)),
		  _unicodeSize(_size), _capacity(_size)
	{
		this->_data = Objects::Memory::alloc<char>(this->_capacity + 1);
		Objects::String::copy(this->_data, nb);
		this->_data[this->_size] = '\0';
	}

	String::String(float const nb)
		: _data(nullptr), _size(0), _unicodeSize(0), _capacity(0)
	{
		uint64_t				decPrecision;
		uint8_t					zero;

		this->_size = this->_unicodeSize = this->_capacity = Objects::String::len(nb, decPrecision, zero) + 1;
		this->_data = Objects::Memory::alloc<char>(this->_capacity + 1);
		Objects::String::fcopy(this->_data, nb, decPrecision, zero);
		this->_data[this->_size] = '\0';
	}

	String::String(double const nb)
		: _data(nullptr), _size(0), _unicodeSize(0), _capacity(0)
	{
		uint64_t				decPrecision;
		uint8_t					zero;

		this->_size = this->_unicodeSize = this->_capacity = Objects::String::len(nb, decPrecision, zero) + 1;
		this->_data = Objects::Memory::alloc<char>(this->_capacity + 1);
		Objects::String::fcopy(this->_data, nb, decPrecision, zero);
		this->_data[this->_size] = '\0';
	}

	String::String(Objects::String const &copy)
		: _data(nullptr), _size(copy._size), _unicodeSize(copy._unicodeSize),
		  _capacity(copy._capacity)
	{
		if (copy._data)
			this->dup(copy._data, this->_capacity);
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
				Objects::Memory::free<char>(this->_data);
				this->_data = Objects::Memory::alloc<char>(this->_capacity + 1);
			}
			if (other._data)
				this->copy(reinterpret_cast<char const *>(other._data),
						   this->_capacity);
		}
		return *this;
	}

	String::~String(void)
	{
		Objects::Memory::free<char>(this->_data);
	}

	/* Setters */

	char						&String::at(uint32_t const i)
	{
		if (i > this->_capacity)
			this->capacity(i);
		return this->_data[i];
	}

	void						String::capacity(uint32_t const capacity)
	{
		if (capacity != this->_capacity)
		{
			if ((this->_capacity = capacity) > 0)
			{
				this->_data = Objects::Memory::realloc<char>(this->_data,
															 this->_capacity + 1);
				this->_data[this->_capacity] = '\0';
			}
			else
				Objects::Memory::free<char>(this->_data);
			if (this->_capacity < this->_size)
			{
				this->_size = this->_unicodeSize = 0;
				this->lenUnicode(reinterpret_cast<char const * const>(this->_data));
			}
		}
	}

	void						String::resize(uint32_t const size)
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

	Objects::String				&String::operator=(char const c)
	{
		if (this->_capacity != 1)
		{
			Objects::Memory::free<char>(this->_data);
			Objects::Memory::alloc<char>(2);
		}
		this->_data[0] = c;
		this->_data[1] = '\0';
		this->_size = this->_unicodeSize = this->_capacity = 1;
		return *this;
	}

	Objects::String				&String::operator=(Objects::Unicode::Char const c)
	{
		uint8_t const			size = c.size();

		if (this->_capacity != size)
		{
			Objects::Memory::free<char>(this->_data);
			Objects::Memory::alloc<char>(size + 1);
		}
		this->copy(c.toString()._char, size, 0);
		this->_data[size] = '\0';
		this->_size = this->_capacity = size;
		this->_unicodeSize = 1;
		return *this;
	}

	Objects::String				&String::operator=(char const * const str)
	{
		if (str != reinterpret_cast<char const * const>(this->_data))
		{
			if (str)
			{
				Objects::String	tmp;

				tmp.lenUnicode(str);
				if (tmp._capacity != this->_capacity)
				{
					Objects::Memory::free<char>(this->_data);
					Objects::Memory::alloc<char>(this->_capacity + 1);
					this->_capacity = tmp._capacity;
				}
				this->copy(str, tmp._size);
				this->_size = tmp._size;
				this->_unicodeSize = tmp._unicodeSize;
			}
			else
			{
				Objects::Memory::free<char>(this->_data);
				this->_size = this->_unicodeSize = this->_capacity = 0;
			}
		}
		return *this;
	}

	Objects::String				&String::operator=(ssize_t const nb)
	{
		uint32_t const			len = Objects::String::len(nb);

		if (this->_capacity != len)
		{
			Objects::Memory::free<char>(this->_data);
			Objects::Memory::alloc<char>(len + 1);
		}
		Objects::String::copy(this->_data, nb);
		this->_data[len] = '\0';
		this->_size = this->_unicodeSize = this->_capacity = len;
		return *this;
	}

	Objects::String				&String::operator=(size_t const nb)
	{
		uint32_t const			len = Objects::String::len(nb);

		if (this->_capacity != len)
		{
			Objects::Memory::free<char>(this->_data);
			Objects::Memory::alloc<char>(len + 1);
		}
		Objects::String::copy(this->_data, nb);
		this->_data[len] = '\0';
		this->_size = this->_unicodeSize = this->_capacity = len;
		return *this;
	}

	Objects::String				&String::operator=(float const nb)
	{
		uint64_t				decPrecision;
		uint8_t					zero;
		uint32_t const			len = Objects::String::len(nb, decPrecision, zero) + 1;

		if (this->_capacity != len)
		{
			Objects::Memory::free<char>(this->_data);
			Objects::Memory::alloc<char>(len + 1);
		}
		Objects::String::fcopy(this->_data, nb, decPrecision, zero);
		this->_data[len] = '\0';
		this->_size = this->_unicodeSize = this->_capacity = len;
		return *this;
	}

	Objects::String				&String::operator=(double const nb)
	{
		uint64_t				decPrecision;
		uint8_t					zero;
		uint32_t const			len = Objects::String::len(nb, decPrecision, zero) + 1;

		if (this->_capacity != len)
		{
			Objects::Memory::free<char>(this->_data);
			Objects::Memory::alloc<char>(len + 1);
		}
		Objects::String::fcopy(this->_data, nb, decPrecision, zero);
		this->_data[len] = '\0';
		this->_size = this->_unicodeSize = this->_capacity = len;
		return *this;
	}

	Objects::String				String::operator+(char const c) const
	{
		Objects::String			ret;

		ret.capacity(this->_size + 1);
		ret.copy(reinterpret_cast<char const * const>(this->_data), this->_size);
		ret._data[this->_size] = c;
		ret._unicodeSize = this->_unicodeSize + 1;
		ret._size = ret._capacity;
		return ret;
	}

	Objects::String				String::operator+(Objects::Unicode::Char const c) const
	{
		Objects::String			ret;
		uint8_t const			size = c.size();

		ret.capacity(this->_size + size);
		ret.copy(reinterpret_cast<char const * const>(this->_data), this->_size);
		ret.copy(c.toString()._char, size, this->_size);
		ret._size = ret._capacity;
		ret._unicodeSize = this->_unicodeSize + 1;
		return ret;
	}

	Objects::String				String::operator+(char const * const str) const
	{
		Objects::String			ret;
		Objects::String			tmp;

		tmp.lenUnicode(str);
		ret.capacity(this->_size + tmp._size);
		ret.copy(reinterpret_cast<char const * const>(this->_data), this->_size);
		ret.copy(str, tmp._size, this->_size);
		ret._size = this->_size + tmp._size;
		ret._unicodeSize = this->_unicodeSize + tmp._unicodeSize;
		return ret;
	}

	Objects::String				String::operator+(Objects::String const &str) const
	{
		Objects::String			ret;

		ret.capacity(this->_capacity + str._capacity);
		ret.copy(reinterpret_cast<char const * const>(this->_data), this->_size);
		ret.copy(str._data, str._size, this->_size);
		ret._size = this->_size + str._size;
		ret._unicodeSize = this->_unicodeSize + str._unicodeSize;
		return ret;
	}

	Objects::String				String::operator+(ssize_t const nb) const
	{
		Objects::String			ret;
		uint32_t const			len = Objects::String::len(nb);

		ret.capacity(this->_size + len);
		ret.copy(reinterpret_cast<char const * const>(this->_data), this->_size);
		Objects::String::copy(ret._data + this->_size, nb);
		ret._unicodeSize = this->_unicodeSize + len;
		ret._size = ret._capacity;
		return ret;
	}

	Objects::String				String::operator+(size_t const nb) const
	{
		Objects::String			ret;
		uint32_t const			len = Objects::String::len(nb);

		ret.capacity(this->_size + len);
		ret.copy(reinterpret_cast<char const * const>(this->_data), this->_size);
		Objects::String::copy(ret._data + this->_size, nb);
		ret._unicodeSize = this->_unicodeSize + len;
		ret._size = ret._capacity;
		return ret;
	}

	Objects::String				String::operator+(float const nb) const
	{
		Objects::String			ret;
		uint64_t				decPrecision;
		uint8_t					zero;
		uint32_t const			len = Objects::String::len(nb, decPrecision, zero) + 1;

		ret.capacity(this->_size + len);
		ret.copy(reinterpret_cast<char const * const>(this->_data), this->_size);
		Objects::String::fcopy(ret._data + this->_size, nb, decPrecision, zero);
		ret._unicodeSize = this->_unicodeSize + len;
		ret._size = ret._capacity;
		return ret;
	}

	Objects::String				String::operator+(double const nb) const
	{
		Objects::String			ret;
		uint64_t				decPrecision;
		uint8_t					zero;
		uint32_t const			len = Objects::String::len(nb, decPrecision, zero) + 1;

		ret.capacity(this->_size + len);
		ret.copy(reinterpret_cast<char const * const>(this->_data), this->_size);
		Objects::String::fcopy(ret._data + this->_size, nb, decPrecision, zero);
		ret._unicodeSize = this->_unicodeSize + len;
		ret._size = ret._capacity;
		return ret;
	}

	/* Methods */

	uint32_t						String::find(Objects::Unicode::Char const c) const
	{
		uint32_t					f = 0;

		for (Objects::Unicode::String::Iterator it = this->unicodeBegin();
			 it != this->unicodeEnd() && !(*it == c); ++it)
			f += (*it).size();
		return f;
	}

	uint32_t						String::find(char const * const str) const
	{
		char const				*i = this->_data;
		char const				*istr = str;

		while (*i && *istr)
		{
			istr = (*i == *istr) ? (istr + 1) : str;
			++i;
		}
		return static_cast<uint32_t>(i - this->_data - (istr - str));
	}

	int							String::compare(char const * const str,
												uint32_t const n,
												uint32_t const begin) const
	{
		int						ret = (str) ? -1 : 1;

		if (str && this->_data && begin < this->_capacity)
			ret = (!n) ? ::strcmp(this->_data + begin, str) :
				::strncmp(this->_data + begin, str, n);
		return (this->_data == str) ? 0 : ret;
	}

	Objects::String				&String::append(char const c)
	{
		uint32_t				freeSpace = this->_capacity - this->_size;

		if (!freeSpace)
			this->capacity(this->_capacity + 1);
		this->_data[this->_size++] = c;
		++this->_unicodeSize;
		return *this;
	}

	Objects::String				&String::append(Objects::Unicode::Char const c)
	{
		uint32_t				freeSpace = this->_capacity - this->_size;
		uint8_t const			size = c.size();

		if (size > freeSpace)
			this->capacity(this->_capacity + (size - freeSpace));
		this->copy(c.toString()._char, size, this->_size);
		this->_size += size;
		++this->_unicodeSize;
		return *this;
	}

	Objects::String				&String::append(char const * const str)
	{
		Objects::String			tmp;
		uint32_t				freeSpace = this->_capacity - this->_size;

		tmp.lenUnicode(str);
		if (tmp._size > freeSpace)
			this->capacity(this->_capacity + (tmp._size - freeSpace));
		this->copy(str, tmp._size, this->_size);
		this->_size += tmp._size;
		this->_unicodeSize += tmp._unicodeSize;
		return *this;
	}

	Objects::String				&String::append(Objects::String const &str)
	{
		uint32_t				freeSpace = this->_capacity - this->_size;

		if (str._size > freeSpace)
			this->capacity(this->_capacity + (str._size - freeSpace));
		this->copy(reinterpret_cast<char const * const>(str._data),
				   str._size, this->_size);
		this->_size += str._size;
		this->_unicodeSize += str._unicodeSize;
		return *this;
	}

	Objects::String				&String::append(ssize_t const nb)
	{
		uint32_t				freeSpace = this->_capacity - this->_size;
		uint32_t const			len = Objects::String::len(nb);

		if (len > freeSpace)
			this->capacity(this->_capacity + (len - freeSpace));
		Objects::String::copy(this->_data + this->_size, nb);
		this->_size += len;
		this->_unicodeSize += len;
		this->_data[this->_size] = '\0';
		return *this;
	}

	Objects::String				&String::append(size_t const nb)
	{
		uint32_t				freeSpace = this->_capacity - this->_size;
		uint32_t const			len = Objects::String::len(nb);

		if (len > freeSpace)
			this->capacity(this->_capacity + (len - freeSpace));
		Objects::String::copy(this->_data + this->_size, nb);
		this->_size += len;
		this->_unicodeSize += len;
		this->_data[this->_size] = '\0';
		return *this;
	}

	Objects::String				&String::append(float const nb)
	{
		uint32_t				freeSpace = this->_capacity - this->_size;
		uint64_t				decPrecision;
		uint8_t					zero;
		uint32_t const			len = Objects::String::len(nb, decPrecision, zero) + 1;

		if (len > freeSpace)
			this->capacity(this->_capacity + (len - freeSpace));
		Objects::String::fcopy(this->_data + this->_size, nb, decPrecision, zero);
		this->_size += len;
		this->_unicodeSize += len;
		this->_data[this->_size] = '\0';
		return *this;
	}

	Objects::String				&String::append(double const nb)
	{
		uint32_t				freeSpace = this->_capacity - this->_size;
		uint64_t				decPrecision;
		uint8_t					zero;
		uint32_t const			len = Objects::String::len(nb, decPrecision, zero) + 1;

		if (len > freeSpace)
			this->capacity(this->_capacity + (len - freeSpace));
		Objects::String::fcopy(this->_data + this->_size, nb, decPrecision, zero);
		this->_size += len;
		this->_unicodeSize += len;
		this->_data[this->_size] = '\0';
		return *this;
	}

	void						String::shift(uint32_t const nbLeftBytes)
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
		uint32_t					i = 0;

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
		uint32_t					i = 0;

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
		uint32_t					i = this->_capacity;

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

	Objects::String				String::substr(uint32_t const begin,
											   uint32_t size) const
	{
		Objects::String			ret;

		if (size && begin < this->_size)
		{
			if ((begin + size) > this->_size)
				size = this->_size - begin;
			ret.dup(reinterpret_cast<char const *>(this->_data + begin), size);
			ret._capacity = size;
			ret.lenUnicode(ret._data);
		}
		return ret;
	}

	Objects::String				String::substr(uint32_t const begin,
											   Objects::Unicode::Char const end) const
	{
		if (begin < this->_size)
		{
			uint32_t				f = 0;

			for (Objects::Unicode::String::Iterator it = this->_data + begin;
				 it != this->unicodeEnd() && !(*it == end); ++it)
				f += (*it).size();
			return this->substr(begin, f + ((this->_data[f]) ? 1 : 0));
		}
		return Objects::String();
	}

	/* Static Methods */
/*	Objects::String				String::format(char const * const fmt, ...)
	{
    va_list					ap;
    Objects::String			ret;

    va_start(ap, fmt);
    Objects::String::format(fmt, ret, &ap);
    va_end(ap);
    return ret;
	}

	Objects::String				String::format(Objects::String const fmt, ...)
	{
    va_list					ap;
    Objects::String			ret;

    va_start(ap, fmt);
    Objects::String::format(*fmt, ret, &ap);
    va_end(ap);
    return ret;
    }*/

	void						String::setPrecision(uint8_t precision)
	{
		if (precision && precision != Objects::String::_precision)
		{
			if (precision > 18)
				precision = 18;
			Objects::String::_precision = 1;
			for (uint8_t i = 0; i < precision; ++i)
				Objects::String::_precision *= 10;
		}
	}

	/* Tools Static Methods */

    uint32_t					String::len(float const nb)
	{
		ssize_t const			castNb = static_cast<ssize_t>(nb);
		uint8_t const			ret = (castNb) ? 1 : 0;
		uint64_t				decNb = ((nb + ((ret) ? 0 : 1)) * Objects::String::_precision -
										 (castNb - ret) *
										 Objects::String::_precision);
		uint32_t				lenDec;
        uint64_t                decPrecision = Objects::String::_precision;

		while (decNb && (!(decNb % 10)))
		{
			decNb /= 10;
			decPrecision /= 10;
		}
		lenDec = Objects::String::len(decNb) - 1;
		return Objects::String::len(castNb) + lenDec;
	}

	uint32_t					String::len(float const nb,
											uint64_t &decPrecision,
											uint8_t &zero)
	{
		ssize_t const			castNb = static_cast<ssize_t>(nb);
		uint8_t const			ret = (castNb) ? 1 : 0;
		uint64_t				decNb = ((nb + ((ret) ? 0 : 1)) * Objects::String::_precision -
										 (castNb - ret) *
										 Objects::String::_precision);
		uint32_t				lenDec;

		decPrecision = Objects::String::_precision;
		while (decNb && (!(decNb % 10)))
		{
			decNb /= 10;
			decPrecision /= 10;
		}
		lenDec = Objects::String::len(decNb) - 1;
		zero = lenDec - Objects::String::len(decNb - 1 * decPrecision);
		return Objects::String::len(castNb) + lenDec;
	}

    uint32_t					String::len(double const nb)
	{
		ssize_t const			castNb = static_cast<ssize_t>(nb);
		uint8_t const			ret = (castNb) ? 1 : 0;
		uint64_t				decNb = ((nb + ((ret) ? 0 : 1)) * Objects::String::_precision -
										 (castNb - ret) *
										 Objects::String::_precision);
		uint32_t				lenDec;
        uint64_t                decPrecision = Objects::String::_precision;

		while (decNb && (!(decNb % 10)))
		{
			decNb /= 10;
			decPrecision /= 10;
		}
		lenDec = Objects::String::len(decNb) - 1;
		return Objects::String::len(castNb) + lenDec;
	}

	uint32_t					String::len(double const nb,
											uint64_t &decPrecision,
											uint8_t &zero)
	{
		ssize_t const			castNb = static_cast<ssize_t>(nb);
		uint8_t const			ret = (castNb) ? 1 : 0;
		uint64_t				decNb = ((nb + ((ret) ? 0 : 1)) * Objects::String::_precision -
										 (castNb - ret) *
										 Objects::String::_precision);
		uint32_t				lenDec;

		decPrecision = Objects::String::_precision;
		while (decNb && (!(decNb % 10)))
		{
			decNb /= 10;
			decPrecision /= 10;
		}
		lenDec = Objects::String::len(decNb) - 1;
		zero = lenDec - Objects::String::len(decNb - 1 * decPrecision);
		return Objects::String::len(castNb) + lenDec;
	}
}

/* EXTRA OPERATOR */

Objects::String					operator+(char const c,
										  Objects::String const &str)
{
	Objects::String				ret;

	ret.capacity(str.size() + 1);
	ret += c;
	ret += str;
	return ret;
}

Objects::String					operator+(Objects::Unicode::Char const c,
										  Objects::String const &str)
{
	Objects::String				ret;

	ret.capacity(str.size() + c.size());
	ret += c;
	ret += str;
	return ret;
}

Objects::String					operator+(char const * const s1,
										  Objects::String const &str)
{
	Objects::String				ret;

	ret.capacity(str.size() + ::strlen(s1));
	ret += s1;
	ret += str;
	return ret;
}

Objects::String					operator+(ssize_t const nb,
										  Objects::String const &str)
{
	Objects::String				ret;

	ret.capacity(str.size() + Objects::String::len(nb));
	ret += nb;
	ret += str;
	return ret;
}

Objects::String					operator+(size_t const nb,
										  Objects::String const &str)
{
	Objects::String				ret;

	ret.capacity(str.size() + Objects::String::len(nb));
	ret += nb;
	ret += str;
	return ret;
}

Objects::String					operator+(float const nb,
										  Objects::String const &str)
{
	Objects::String				ret;

	ret.capacity(str.size() + Objects::String::len(nb));
	ret += nb;
	ret += str;
	return ret;
}

Objects::String					operator+(double const nb,
										  Objects::String const &str)
{
	Objects::String				ret;

	ret.capacity(str.size() + Objects::String::len(nb));
	ret += nb;
	ret += str;
	return ret;
}
