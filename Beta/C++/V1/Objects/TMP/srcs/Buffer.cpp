
#include <new>
#include <stdexcept>
#include "Buffer.hpp"

/*

Faire Fast copy (Buffer, size)
Finir Dynamic buffer

*/

namespace                       Object
{
    namespace                   Static
    {
		ABuffer::ABuffer(uint64_t const capacity)
			: _capacity(0), _data(nullptr)
		{
			if (capacity)
				this->alloc(capacity);
		}

		ABuffer::ABuffer(uint8_t const *data, size_t const size)
			: _capacity(0), _data(nullptr)
		{
			if (data && size)
            {
                this->alloc(size);
				Object::Static::ABuffer::copy(this->_data, data, size);
            }
		}

		ABuffer::ABuffer(Object::Static::ABuffer const &copy)
			: _capacity(copy._capacity), _data(nullptr)
		{
			this->alloc(copy._capacity);
			this->copy(copy);
		}

		Object::Static::ABuffer &ABuffer::operator=(Object::Static::ABuffer const &other)
		{
			if (&other != this)
			{
				if (this->_data)
					::free(this->_data);
				this->alloc(other._capacity);
				this->copy(other);
			}
			return *this;
		}

		ABuffer::~ABuffer(void)
		{
			if (this->_data)
				::free(this->_data);
		}

		/* Protected Methods */

		void                        ABuffer::copy(Object::Static::ABuffer const &copy)
		{
			size_t                  len =
				(Object::Static::ABuffer::align((this->_capacity < copy.size()) ?
												this->_capacity : copy.size()) /
				 sizeof(size_t));

			for (size_t i = 0; i < len; ++i)
				reinterpret_cast<size_t *>(this->_data)[i] =
					reinterpret_cast<size_t *>(copy._data)[i];
		}

		void                        ABuffer::copy(Object::Static::ABuffer const &copy,
												  size_t begin)
		{
			size_t					capacity = this->_capacity - begin;
			size_t                  len = Object::Static::ABuffer::align((capacity < copy.size()) ?
																		 capacity : copy.size()) / sizeof(size_t);
			size_t					lowCopy = begin % sizeof(size_t);

			if (lowCopy)
			{
				--len;
				lowCopy = sizeof(size_t) - lowCopy;
			}
			for (size_t i = 0; i < len; ++i)
				reinterpret_cast<size_t *>(this->_data + begin)[i] =
					reinterpret_cast<size_t *>(copy._data)[i];
			len *= sizeof(size_t);
			begin += len;
			for (size_t i = 0; i < lowCopy; ++i)
				this->_data[begin + i] = copy._data[len + i];
		}

		/**

		   0000 0000 | 0000 0111 | 1111 1111 | 1111 1000

		   1111 1111 | 1111 1111 | 1111 1111 | 1111 1111

		                           ^

		   32 && 32 && 13
		   cap = 19
		   len = 3
		   low = 5

		   len = 2
		   low = 3

		   while 0 < 2

		   len = 16
		   begin = 29


		 */

		/* Protected methods */

		void                        ABuffer::alloc(size_t size)
		{
			size = Object::Static::ABuffer::align(size);
			if (!(this->_data = static_cast<uint8_t *>(::malloc(size + 1))))
				throw std::bad_alloc();
			this->_data[size] = 0;
			this->_capacity = size;
		}

		/* BUFFER */

        Buffer::Buffer(size_t const capacity)
            : Object::Static::ABuffer(capacity), _currentCursor(0), _size(0)
        {
        }

        Buffer::Buffer(uint8_t const *data, size_t const size)
            : Object::Static::ABuffer(data, size), _currentCursor(0), _size(0)
        {
        }

        Buffer::Buffer(Buffer const &copy)
            : Object::Static::ABuffer(copy),
			_currentCursor(copy._currentCursor),
            _size(copy._size)
        {
        }

		Object::Static::Buffer  &Buffer::operator=(Object::Static::Buffer const &other)
        {
            if (&other != this)
                {
                    Object::Static::ABuffer::operator=(other);
                    this->_currentCursor = other._currentCursor;
                    this->_size = other._size;
                }
            return *this;
        }


        /* Public methods */

        uint8_t                 &Buffer::at(size_t idx)
        {
			idx = (idx > this->_capacity) ? this->_capacity : idx;
			if (idx > this->_size)
				this->_size = idx + ((idx != this->_capacity) ? 1 : 0);
			this->_currentCursor = idx + ((idx != this->_capacity) ? 1 : 0);
			return this->_data[idx];
        }

        size_t                  Buffer::write(uint8_t const *data,
                                              size_t const size)
        {
            size_t              freeSpace = (this->_capacity -
                                             this->_currentCursor);
            size_t              sizeWrite = ((size < freeSpace) ?
                                             size : freeSpace);

            if (sizeWrite)
			{
				Object::Static::ABuffer::copy(this->_data + this->_currentCursor,
											  data, sizeWrite);
				this->_currentCursor += sizeWrite;
				if (this->_currentCursor > this->_size)
					this->_size = this->_currentCursor;
			}
            return sizeWrite;
        }

		size_t					Buffer::write(Object::Static::Buffer const &buffer)
		{
			size_t              freeSpace = (this->_capacity -
                                             this->_currentCursor);
            size_t              sizeWrite = ((size < freeSpace) ?
                                             size : freeSpace);

			if (sizeWrite)
			{

			}
		}
    }

	namespace					Dynamic
	{

		/* ABUFFER */

		/* Public methods */

		void					ABuffer::capacity(size_t size)
		{
			if (size)
				this->realloc(size);
			else
			{
				::free(this->_data);
				this->_capacity = 0;
			}
		}

		/* Protected methods */

		void                    ABuffer::realloc(size_t size)
		{
			size = Object::Static::ABuffer::align(size);
			if (this->_capacity != size)
			{
				if (!(this->_data =
					  static_cast<uint8_t *>(::realloc(this->_data, size + 1))))
					throw std::bad_alloc();
				this->_data[size] = 0;
				this->_capacity = size;
			}
		}

		/* BUFFER */

		uint8_t                 &Buffer::at(size_t idx)
        {
			if (++idx > this->_capacity)
				this->realloc(idx);
			if (idx > this->_size)
				this->_size = idx;
			this->_currentCursor = idx;
			return this->_data[--idx];
        }

        size_t                  Buffer::write(uint8_t const *data,
                                              size_t const size)
        {
            size_t              freeSpace = (this->_capacity -
                                             this->_currentCursor);

			if (size > freeSpace)
				this->addPageMemory(size - freeSpace);
			Object::Static::ABuffer::copy(this->_data + this->_currentCursor,
										  data, size);
			this->_currentCursor += size;
			if (this->_currentCursor > this->_size)
				this->_size = this->_currentCursor;
			return size;
		}
	}
}
