/**
* \file				Buffer.hpp
* \author			Sébastien Le Maire
* \version			1.0
* \date				25 Février 2018
*/

#ifndef OBJECTS_BUFFER_HPP_
# define OBJECTS_BUFFER_HPP_

# include <cstdint>
# include <cstdlib>

namespace						Objects
{
	class						Buffer
	{
	private:
		uint8_t					*_data;
		size_t					_size;
		size_t					_capacity;

	public:
		/* ctor & dtor on canonics form */
		Buffer(size_t const capacity = 0);
		Buffer(Objects::Buffer const &copy);
		Objects::Buffer			&operator=(Objects::Buffer const &other);
		~Buffer(void);

		/* Getters */
		inline size_t			capacity(void) const
			{
				return this->_capacity;
			}
		inline size_t			size(void) const
			{
				return this->_size;
			}
		inline uint8_t			*rawData(void) const
			{
				return this->_data;
			}
		uint8_t					&at(size_t const i);
		inline uint8_t			at(size_t const i) const
			{
				return (i > this->_capacity) ? 0 : this->_data[i];
			}
		bool					empty(void) const
			{
				return !this->_size;
			}

		/* Setters */
		void					capacity(size_t const capacity);
		void					resize(size_t const size);
		inline void				clear(void)
			{
				this->_size = 0;
			}

		/* Operator */
		inline uint8_t			&operator[](size_t const i)
			{
				return this->at(i);
			}
		inline uint8_t			operator[](size_t const i) const
			{
				return this->at(i);
			}
		inline Objects::Buffer	&operator+=(Objects::Buffer const &buffer)
			{
				this->write(buffer);
				return *this;
			}
		inline operator bool(void) const
			{
				return !this->empty();
			}

		/* Methods */
		void					write(uint8_t const *data, size_t const size);
		inline void				write(Objects::Buffer const &buffer)
			{
				this->write(buffer.rawData(), buffer.size());
			}

		void					shift(size_t const nbLeftBytes);

	}; /* END BUFFER */

} /* END NAMESPACE OBJECTS */

#endif /* !OBJECTS_BUFFER_HPP_ */
