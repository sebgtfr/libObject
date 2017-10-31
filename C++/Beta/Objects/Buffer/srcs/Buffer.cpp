/**
* \file					Buffer.cpp
* \author				Sébastien Le Maire
* \version				1.0
* \date					24/06/2017
*/
#include <cstdint>
#include "Memory.hpp"
#include "Buffer.hpp"

Buffer::Buffer(size_t const size) : m_size(0), m_capacity(0), m_data(NULL)
{
  this->resize(size);
}

Buffer::Buffer(Buffer const &copy) : m_size(copy.m_size), m_capacity(copy.m_capacity)
{
  this->m_data = Memory::getInstance().allocate(this->m_capacity);
  Memory::copy(this->m_data, copy.m_data, this->m_capacity);
}

Buffer					&Buffer::operator=(Buffer const &other)
{
  if (&other != this)
    {
      this->m_size = other.m_size;
      this->m_capacity = other.m_capacity;
      this->m_data = Memory::getInstance().allocate(this->m_capacity);
      Memory::copy(this->m_data, other.m_data, this->m_capacity);
    }
  return (*this);
}

Buffer::~Buffer(void)
{
  Memory::getInstance().deallocate(this->m_data);
}

/*
** Private's methods
*/

void					Buffer::resize(size_t const capacity)
{
  if (!capacity)
    this->clear();
  else if (this->m_capacity != capacity)
    {
      this->m_data = Memory::getInstance().reallocate(this->m_data,
								 capacity);
      this->m_capacity = capacity;
      if (this->m_size > capacity)
	this->m_size = capacity;
    }
}

/*
** Public's methods
*/

void					Buffer::reset(void)
{
  this->m_size = 0;
}

void					Buffer::clear(void)
{
  Memory::getInstance().deallocate(this->m_data);
  this->m_data = NULL;
  this->m_capacity = 0;
  this->m_size = 0;
}

size_t					Buffer::size(void) const
{
  return this->m_size;
}

void					*Buffer::getData(size_t const shift) const
{
  return static_cast<void *>(static_cast<int8_t *>(this->m_data) + shift);
}

void					Buffer::assign(void const *data,
						       size_t const size)

{
  if (data)
    {
      this->resize(size);
      Memory::copy(this->m_data, data, size);
      this->m_size = size;
    }
  else
    this->clear();
}

void					Buffer::change(void const *data,
						       size_t const size)
{
  if (data)
    {
      size_t				capacity = this->m_capacity;

      if ((capacity = (capacity < size) ? (size - capacity) : 0))
	this->resize(this->m_capacity + capacity);
      Memory::copy(this->m_data, data, size);
      this->m_size = size;
    }
}

void					Buffer::concat(void const *data,
						       size_t const size)
{
  if (data)
    {
      size_t				capacity = this->m_capacity - this->m_size;

      if ((capacity = (capacity < size) ? (size - capacity) : 0))
	this->resize(this->m_capacity + capacity);
      Memory::copy(static_cast<void *>(static_cast<uint8_t *>(this->m_data) + this->m_size),
		   data, size);
      this->m_size += size;
    }
}

void					Buffer::shift(size_t const shift)
{
  if (shift && this->m_data)
    {
      if (shift < this->m_size)
	{
	  Memory::move(this->m_data, static_cast<void *>(static_cast<uint8_t *>(this->m_data) + shift),
		       this->m_size - shift);
	  this->m_size -= shift;
	}
      else
	this->reset();
    }
}
