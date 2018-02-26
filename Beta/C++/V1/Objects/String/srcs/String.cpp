
#include "Objects/Memory.hpp"
#include "Objects/Exception.hpp"
#include "Objects/String.hpp"

namespace	Objects
{
	String::String(char const *str)
		: _capacity(0), _size(0), _unicodeSize(0), _data(nullptr)
	{
		if (str)
		{
			this->_capacity = Objects::Memory::align(Objects::String::strlen(str));
			this->_data = static_cast<char *>(Objects::Memory::alloc(this->_capacity + 1));
			this->_data[this->_capacity] = '\0';
			this->copy(str);
		}
	}

	String::String(String const &copy)
		: _capacity(0), _size(0), _unicodeSize(0), _data(nullptr)
	{
		if (copy._data)
		{
			this->_capacity = copy._capacity;
			this->_data = static_cast<char *>(Objects::Memory::alloc(this->_capacity + 1));
			this->_data[this->_capacity] = '\0';
			this->copy(copy);
		}
	}

	Objects::String					&String::operator=(String const &other)
	{
		if (&other != this)
		{
			if (other._data)
			{
				if (this->_capacity != other._capacity)
				{
					this->_capacity = other._capacity;
					if (this->_data)
						Objects::Memory::free(reinterpret_cast<void *&>(this->_data));
					this->_data = static_cast<char *>(Objects::Memory::alloc(this->_capacity + 1));
				}
				this->copy(other);
			}
			else
			{
				this->_capacity = this->_size = this->_unicodeSize = 0;
				if (this->_data)
					Objects::Memory::free(reinterpret_cast<void *&>(this->_data));
			}
		}
		return *this;
	}

	String::~String(void)
	{
		if (this->_data)
			Objects::Memory::free(reinterpret_cast<void *&>(this->_data));
	}

	/* Accessor */
	void							String::resize(wordsize const size)
	{
		wordsize					oldSize = this->_size;

		this->_size = (size > this->_capacity) ? this->_capacity : size;
		this->_data[this->_size] = '\0';
		if (size < oldSize)
		{
			this->_unicodeSize = Objects::String::strUnicodeLen(this->_data);
		}
	}

	void							String::capacity(wordsize const capacity)
	{
		if (!capacity)
		{
			this->_capacity = this->_size = this->_unicodeSize = 0;
			if (this->_data)
				Objects::Memory::free(reinterpret_cast<void *&>(this->_data));
		}
		else if (this->_capacity != Objects::Memory::align(capacity))
		{
			this->_capacity = Objects::Memory::align(capacity);
			this->_data = static_cast<char *>(Objects::Memory::realloc(
												  reinterpret_cast<void *>(this->_data),
												  this->_capacity));
			if (this->_size > this->_capacity)
			{
				this->_size = this->_capacity;
				this->_data[this->_size] = '\0';
				this->_unicodeSize = Objects::String::strUnicodeLen(this->_data);
			}

		}
	}

	char							&String::operator[](wordsize const idx)
	{
		if (idx > this->_capacity)
			throw Objects::Exception(Objects::Exception::OUT_OF_RANGE);
		return this->_data[idx];
	}

	char							String::operator[](wordsize const idx) const
	{
		if (idx > this->_capacity)
			throw Objects::Exception(Objects::Exception::OUT_OF_RANGE);
		return this->_data[idx];
	}

	/* Private Methods */
	void							String::copy(char const *copy)
	{
		this->_size = 0;
		this->_unicodeSize = 0;
		while (*copy)
		{
			uint8					sizeUnicodeChar = Objects::Unicode::String::sizeUnicodeChar(*copy);

			switch (sizeUnicodeChar)
			{
			case 1:
				this->_data[this->_size] = *copy;
				break;
			case 2:
				*reinterpret_cast<uint16 *>(this->_data + this->_size) =
					*reinterpret_cast<uint16 const *>(copy);
				break;
			case 3:
			case 4:
				*reinterpret_cast<uint32 *>(this->_data + this->_size) =
					*reinterpret_cast<uint32 const *>(copy);
				break;
			}
			this->_size += sizeUnicodeChar;
			copy += sizeUnicodeChar;
			++this->_unicodeSize;
		}
	}

	void							String::copy(Objects::String const &copy)
	{
		wordsize					len = Objects::Memory::align(copy._size) / sizeof(wordsize);
		wordsize					*thisData = reinterpret_cast<wordsize *>(this->_data);
		wordsize					*copyData = reinterpret_cast<wordsize *>(copy._data);

		for (wordsize i = 0; i < len; ++i)
			*thisData++ = *copyData++;
		this->_size = copy._size;
		this->_unicodeSize = copy._unicodeSize;
	}

	void							String::copy(Objects::String const &copy,
												 wordsize begin)
	{
		wordsize					len = Objects::Memory::align(copy._size) / sizeof(wordsize);
		wordsize					*thisData = reinterpret_cast<wordsize *>(this->_data);
		wordsize					*copyData = reinterpret_cast<wordsize *>(copy._data);
		wordsize					lowCopy = begin % sizeof(wordsize);

		if (lowCopy)
		{
			--len;
			lowCopy = sizeof(wordsize) - lowCopy;
		}
		for (wordsize i = 0; i < len; ++i)
			*thisData++ = *copyData++;
		len *= sizeof(size_t);
		begin += len;
		for (wordsize i = 0; i < lowCopy; ++i)
			this->_data[begin + i] = copy._data[len + i];
		this->_size += copy._size;
		this->_unicodeSize += copy._unicodeSize;
	}

	/* Static Public Methods */
	uint8							Unicode::String::sizeUnicodeChar(char const c)
	{
		uint8						size = 1;

		if ((c >> 7) & 1)
			while (size < 4 && ((c >> (7 - size)) & 1))
				++size;
		return size;
	}

	/* Static Private Methods */
	wordsize						String::strlen(char const *str)
	{
		wordsize					len = 0;

		while (*str++)
			++len;
		return len;
	}

	wordsize						String::strUnicodeLen(char const *str)
	{
		wordsize					len = 0;

		while (*str)
		{
			str += Objects::Unicode::String::sizeUnicodeChar(*str);
			++len;
		}
		return len;
	}
}
