
#include <string.h>
#include "Objects/Buffer.hpp"

namespace						Objects
{
	/* Private Buffer */

	PrivateBuffer::PrivateBuffer(size_t const size, size_t const capacity)
		: _data(nullptr), _size(size), _capacity(capacity)
	{
		if (capacity)
			this->_data = static_cast<uint8_t *>(::malloc(sizeof(uint8_t)
														  * this->_capacity));
	}

	/* Buffer */
	Buffer::Buffer(size_t const capacity)
		: Objects::PrivateBuffer(0, capacity)
	{
	}

	Buffer::Buffer(Buffer const &copy)
		: Objects::PrivateBuffer(copy._size, copy._capacity)
	{
		if (copy._data)
			(void)::memcpy(reinterpret_cast<void *>(this->_data),
						   reinterpret_cast<void *>(copy._data),
						   this->_size);
	}

	Buffer						&Buffer::operator=(Buffer const &other)
	{
		if (&other != this)
		{
			this->_size = other._size;
			this->_capacity = other._capacity;
			if (this->_data)
				::free(this->_data);
			if (other._data)
			{
				this->_data = static_cast<uint8_t *>(::malloc(sizeof(uint8_t)
															  * this->_capacity));
				(void)::memcpy(reinterpret_cast<void *>(this->_data),
							   reinterpret_cast<void *>(other._data),
							   this->_size);
			}
			else
				this->_data = nullptr;
		}
		return *this;
	}

	Buffer::~Buffer(void)
	{
		if (this->_data)
			::free(this->_data);
	}

	/* Getters */
	uint8_t						&Buffer::at(size_t const i)
	{
		this->resize(i);
		return this->_data[i];
	}

	/* Setters */
	void						Buffer::capacity(size_t const capacity)
	{
		if (capacity != this->_capacity)
		{
			if ((this->_capacity = capacity) > 0)
				this->_data = static_cast<uint8_t *>(::realloc(reinterpret_cast<void *>(this->_data),
															   sizeof(uint8_t)
															   * this->_capacity));
			else
			{
				if (this->_data)
					::free(this->_data);
				this->_data = nullptr;
			}
			if (this->_capacity < this->_size)
				this->_size = this->_capacity;
		}
	}

	void						Buffer::resize(size_t const size)
	{
		if (this->_size != size)
		{
			if (size > this->_capacity)
				this->capacity(size);
			this->_size = size;
		}
	}

	/* Methods */
	void						Buffer::write(uint8_t const *data,
											  size_t const size)
	{
		if (data && size)
		{
			if ((this->_capacity - this->_size) < size)
				this->capacity(size - (this->_capacity - this->_size));
			static_cast<void>(::memcpy(reinterpret_cast<void *>(this->_data +
																this->_size),
									   reinterpret_cast<void const *>(data),
									   size));
			this->_size += size;
		}
	}
}
