/**
* \file				Char.cpp
* \author			Sébastien Le Maire
* \version			1.0
* \date				25 Février 2018
*/

#include "Objects/Memory.hpp"
#include "Objects/Buffer.hpp"

namespace						Objects
{
	/* Private Buffer */

	PrivateBuffer::PrivateBuffer(size_t const size, size_t const capacity)
		: _data(nullptr), _size(size), _capacity(capacity)
	{
		if (capacity)
			this->_data = static_cast<uint8_t *>(
				Objects::Memory::alloc(sizeof(uint8_t)
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
			Objects::Memory::copy(reinterpret_cast<void *>(this->_data),
								  reinterpret_cast<void const *>(copy._data),
								  this->_size);
	}

	Buffer						&Buffer::operator=(Buffer const &other)
	{
		if (&other != this)
		{
			this->_size = other._size;
			this->_capacity = other._capacity;
			Objects::Memory::free(reinterpret_cast<void *&>(this->_data));
			if (other._data)
			{
				this->_data = static_cast<uint8_t *>(
					Objects::Memory::alloc(sizeof(uint8_t)
										   * this->_capacity));
				Objects::Memory::copy(reinterpret_cast<void *>(this->_data),
									  reinterpret_cast<void const *>(other._data),
									  this->_size);
			}
		}
		return *this;
	}

	Buffer::~Buffer(void)
	{
		Objects::Memory::free(reinterpret_cast<void *&>(this->_data));
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
				this->_data = static_cast<uint8_t *>(
					Objects::Memory::realloc(reinterpret_cast<void *>(this->_data),
											 sizeof(uint8_t)
											 * this->_capacity));
			else
				Objects::Memory::free(reinterpret_cast<void *&>(this->_data));
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
			Objects::Memory::copy(reinterpret_cast<void *>(this->_data +
														   this->_size),
								  reinterpret_cast<void const *>(data),
								  size);
			this->_size += size;
		}
	}

	void						Buffer::shift(size_t nbLeftBytes)
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
			}
		}
	}
}
