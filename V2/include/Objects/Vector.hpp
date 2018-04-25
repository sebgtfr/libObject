/**
* \file				Vector.hpp
* \author			Sébastien Le Maire
* \version			1.0
* \date				14 Mars 2018
*/

#ifndef OBJECTS_VECTOR_HPP_
# define OBJECTS_VECTOR_HPP_

# include "Objects/Memory.hpp"
# include "Objects/Exception.hpp"

namespace						Objects
{
	template <typename _Type>
	class						Vector
	{
		_Type					*_data;
		size_t					_size;
		size_t					_capacity;

	public:
		class					Iterator
		{
		private:
			_Type				*_current;

		public:
			Iterator(_Type *ptr)
				: _current(ptr) {};

			Iterator(Objects::Vector<_Type>::Iterator const &copy)
				: _current(copy._current) {};

			Objects::Vector<_Type>::Iterator &operator=(Objects::Vector<_Type>::Iterator const &other)
				{
					this->_current = other._current;
					return *this;
				}

			inline Objects::Vector<_Type>::Iterator &operator++(void)
				{
					++this->_current;
					return *this;
				}

			inline Objects::Vector<_Type>::Iterator &operator--(void)
				{
					--this->_current;
					return *this;
				}

			inline Objects::Vector<_Type>::Iterator operator++(int)
				{
					Objects::Vector<_Type>::Iterator it(*this);

					++this->_current;
					return it;
				}

			inline Objects::Vector<_Type>::Iterator operator--(int)
				{
					Objects::Vector<_Type>::Iterator it(*this);

					--this->_current;
					return it;
				}

			inline _Type		&operator*(void) const
				{
					if (!this->_current)
						throw Objects::Exception(Objects::Exception::READ_NULLPTR);
					return *this->_current;
				}

			_Type				*operator->(void) const
				{
					return this->_current;
				}

			inline bool			operator==(Objects::Vector<_Type>::Iterator const &it) const
				{
					return (this->_current == it._current);
				}

			inline bool				operator!=(Objects::Vector<_Type>::Iterator const &it) const
				{
					return (this->_current != it._current);
				}

		};

		/* ctor & dtor on canonics form */
		Vector(size_t const capacity = 0)
			: _data(nullptr), _size(0), _capacity(capacity)
			{
				if (this->_capacity)
					this->_data = Objects::Memory::alloc<_Type>(this->_capacity);
			}

		Vector(Objects::Vector<_Type> const &copy)
			: _data(nullptr), _size(copy._size), _capacity(copy._capacity)
			{
				if (this->_capacity)
				{
					this->_data = Objects::Memory::alloc<_Type>(this->_capacity);
					for (Objects::Vector<_Type>::Iterator itCopy = copy.begin(),
							 itThis = this->begin(); itCopy != copy.end();
						 ++itCopy, ++itThis)
						new(&(*itThis)) _Type(*itCopy);
				}
			}

		Objects::Vector<_Type>	&operator=(Objects::Vector<_Type> const &other)
			{
				if (this != &other)
				{
					this->clear();
					this->_size = other._size;
					if (this->_capacity != other._capacity)
					{
						this->_capacity = other._capacity;
						Objects::Memory::free<_Type>(this->_data);
						this->_data = Objects::Memory::alloc<_Type>(this->_capacity);
					}
					for (Objects::Vector<_Type>::Iterator itOther = other.begin(),
							 itThis = this->begin();
						 itOther != other.end(); ++itOther, ++itThis)
						new(&(*itThis)) _Type(*itOther);
				}
				return *this;
			}

		~Vector(void)
			{
				this->clear();
				Objects::Memory::free<_Type>(this->_data);
			}

		/* Getters */
		inline size_t								size(void) const
			{
				return this->_size;
			}

		inline size_t								capacity(void) const
			{
				return this->_capacity;
			}

		inline _Type								&at(size_t const i)
			{
				if (this->_size >= i)
					throw Objects::Exception(Objects::Exception::OUT_OF_RANGE);
				return reinterpret_cast<_Type *>(this->_data)[i];
			}

		inline _Type const							&at(size_t const i) const
			{
				return this->at(i);
			}

		inline _Type								*getData(void) const
			{
				return this->_data;
			}

		inline bool									empty(void) const
			{
				return !this->_size;
			}

		inline _Type								&operator[](size_t const i)
			{
				return this->at(i);
			}

		inline _Type const							&operator[](size_t const i) const
			{
				return this->at(i);
			}

		/* Setters */
		void										capacity(size_t const capacity)
			{
				if (capacity != this->_capacity)
				{
					if ((this->_capacity = capacity) > 0)
						this->_data = Objects::Memory::realloc<_Type>(this->_data,
																	  this->_capacity);
					else
						Objects::Memory::free<_Type>(this->_data);
					if (this->_capacity < this->_size)
						this->_size = this->_capacity;
				}
			}

		void										resize(size_t const size)
			{
				if (this->_size != size)
				{
					if (size > this->_capacity)
						this->capacity(size);
					this->_size = size;
				}
			}

		void										clear(void)
			{
				for (Objects::Vector<_Type>::Iterator it = this->begin();
					 it != this->end(); ++it)
					it->~_Type();
				this->_size = 0;
			}

		void										shrink_to_fit(void)
			{
				if (this->_capacity > this->_size)
				{
					this->_capacity = this->_size;
					if (this->_capacity)
						this->_data = Objects::Memory::realloc<_Type>(this->_data,
																	  this->_capacity);
					else
						Objects::Memory::free<_Type>(this->_data);
				}
			}

		/* Iterators */
		inline Objects::Vector<_Type>::Iterator		begin(void) const
			{
				return Objects::Vector<_Type>::Iterator(this->_data);
			}

		inline Objects::Vector<_Type>::Iterator		end(void) const
			{
				return Objects::Vector<_Type>::Iterator((this->_data) ?
														(this->_data + this->_size) : nullptr);
			}

		/* Methods */
		void										push_back(_Type const &value)
			{
				if (this->_size >= this->_capacity)
					this->capacity(this->_capacity + 1);
				new(this->_data + this->_size++) _Type(value);
			}

		inline void									pop_back(void)
			{
				if (this->_size)
					this->_data[this->_size--].~_Type();
			}

		void											insert(_Type const &value,
															   size_t const pos)
			{
				if (pos < this->_size)
				{
					size_t								i = 0;
					_Type								*data;
					_Type								*itData;
					Objects::Vector<_Type>::Iterator	it = this->begin();
					Objects::Vector<_Type>::Iterator	itEnd = this->end();

					if (++this->_size >= this->_capacity)
						this->_capacity = this->_size;
					itData = data = Objects::Memory::alloc<_Type>(this->_capacity);
					while (it != itEnd)
					{
						if (i++ == pos)
							new (itData) _Type(value);
						else
							Objects::Memory::copy<_Type>(itData, &(*it++), sizeof(_Type));
						++itData;
					}
					Objects::Memory::free<_Type>(this->_data);
					this->_data = data;
				}
				else
					this->push_back(value);
			}

		void											erase(size_t const begin,
															  size_t const nb = 1)
			{
				if (begin < this->_size && nb > 0)
				{
					size_t								end = begin + ((nb + begin > this->_size) ? (this->_size - begin) : nb);
					size_t								i = 0;
					Objects::Vector<_Type>::Iterator	itEnd = this->end();

					for (Objects::Vector<_Type>::Iterator it = this->begin(), rewrite = it;
						 it != itEnd; ++it, ++i)
					{
						if (i >= begin && i < end)
							it->~_Type();
						else if (&(*rewrite++) != &(*it))
							Objects::Memory::move<_Type>(&(*rewrite), &(*it), sizeof(_Type));
					}
					this->_size -= (end - begin);
				}
			}

		void											erase(Objects::Vector<_Type>::Iterator const &pos)
			{
				void									*data = reinterpret_cast<void *>(&(*pos));

				if (data >= this->_data && data < (this->_data + this->_size * sizeof(_Type)))
					this->erase(static_cast<size_t>(data) - static_cast<size_t>(this->_data) / sizeof(_Type));
			}

		void											erase(Objects::Vector<_Type>::Iterator const &begin,
															  Objects::Vector<_Type>::Iterator const &end)
			{
				void									*dataBegin = reinterpret_cast<void *>(&(*begin));
				void									*dataEnd = reinterpret_cast<void *>(&(*end));
				void									*endThis = this->_data + this->_size * sizeof(_Type);

				if (dataBegin >= this->_data && dataBegin < endThis)
				{
					if (dataBegin == dataEnd)
						this->erase(static_cast<size_t>(dataBegin) - static_cast<size_t>(this->_data) / sizeof(_Type));
					else if (dataEnd > dataBegin && dataEnd <= endThis)
						this->erase(static_cast<size_t>(dataBegin) - static_cast<size_t>(this->_data) / sizeof(_Type),
									(static_cast<size_t>(dataEnd) - static_cast<size_t>(dataBegin)) / sizeof(_Type));
				}
			}
	};
}

#endif /* !OBJECTS_VECTOR_HPP_ */
