
#ifndef BUFFER_HPP_
# define BUFFER_HPP_

# include <cstdint>
# include <cstring>

namespace                               Object
{
    namespace                           Static
    {
		class                           ABuffer
		{
		protected:
			size_t                      _capacity; /* Capacity of buffer */
			uint8_t                     *_data; /* bytes array */

		public:

			/* ctor & dtor on canonics form */
			ABuffer(size_t const capacity);
			ABuffer(uint8_t const *data, size_t const size);
			ABuffer(Object::Static::ABuffer const &copy);
			Object::Static::ABuffer     &operator=(Object::Static::ABuffer const &other);
			virtual ~ABuffer(void);

			/* Public methods */
			virtual inline uint8_t      &at(size_t const idx)
				{
					return this->_data[(idx > this->_capacity) ? this->_capacity : idx];
				}

			inline uint8_t const		&at(size_t const idx) const
				{
					return this->_data[(idx > this->_capacity) ? this->_capacity : idx];
				}

			/* Overload operator */
			inline uint8_t              &operator[](size_t const idx)
				{
					return this->at(idx);
				}

			inline uint8_t const		&operator[](size_t const idx) const
				{
					return this->at(idx);
				}

			/* Getters */
			virtual inline size_t       size(void) const = 0;

			inline size_t               capacity(void) const
				{
					return this->_capacity;
				}

			inline uint8_t              *getRawData(void) const
				{
					return this->_data;
				}

		protected:

			/* Protected methods */
			void                        copy(Object::Static::ABuffer const &copy);
			void                        copy(Object::Static::ABuffer const &copy,
											 size_t const begin);
			virtual void                alloc(size_t size);

			inline void					copy(uint8_t *dest,
											 uint8_t const *src,
											 size_t const size)
				{
					static_cast<void>(::memcpy(dest, src, size));
				}

			/* Static's methods */

			static inline size_t        align(size_t const size)
				{
# if _WIN64 || __x86_64__ || __ppc64__
					return ((((size - 1) >> 3) << 3) + 8);
# else
					return ((((size - 1) >> 2) << 2) + 4);
#endif /* SYSTEM ENV SIZE BITS */
				}
		};


        class                           Buffer
			: virtual public			Object::Static::ABuffer
        {
        protected:
            size_t                      _currentCursor; /* Current Read/Write's cursor */
            size_t                      _size; /* Cursor of the last byte written */

        public:

            /* ctor & dtor on canonics form */

            Buffer(size_t const capacity);
            Buffer(uint8_t const *data, size_t const size);
            Buffer(Buffer const &copy);
			Object::Static::Buffer      &operator=(Object::Static::Buffer const &other);

            /* Getters */

            inline void                 seek(size_t const pos)
				{
					if (pos <= this->_capacity)
						this->_currentCursor = pos;
				}

            inline size_t               getCurrentCursor(void) const
				{
					return this->_currentCursor;
				}

            inline size_t               size(void) const final
				{
					return this->_size;
				}

            inline void                 clear(void)
				{
					this->_currentCursor = this->_size = 0;
				}

            /* Public methods */

            virtual size_t              write(uint8_t const *data,
                                              size_t const size);
			virtual size_t              write(Object::Static::Buffer const &buffer);
            virtual uint8_t             &at(size_t const idx) override;

            template<typename T>
            inline size_t               write(T const &data)
				{
					return this->write(reinterpret_cast<uint8_t const *>(&data), sizeof(T));
				}

            template<typename T>
            T                           read(void)
				{
					size_t                  freeSpace = (this->_size -
														 this->_currentCursor);

					if (freeSpace >= sizeof(T))
					{
                        uint8_t         *buf = (this->_data +
                                                this->_currentCursor);

                        this->_currentCursor += sizeof(T);
                        return *reinterpret_cast<T *>(buf);
                    }
					return T();
				}
        };
    }

	namespace							Dynamic
	{
		class							ABuffer
			: virtual public			Object::Static::ABuffer
		{
		public:
			void						capacity(size_t const size);
			static void					addPageMemory(size_t const size)
				{
					this->realloc(this->_capacity + size);
				}

		protected:
			void						realloc(size_t size);
		};

		class							Buffer
			: public					Object::Static::Buffer,
			  public					Object::Dynamic::ABuffer
		{
			size_t						write(uint8_t const *data,
                                              size_t const size);
            uint8_t						&at(size_t const idx) final;
		};
	}
}

#endif /* !BUFFER_HPP_ */
