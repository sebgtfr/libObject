
#ifndef OBJECTS_NUMBER_HPP_
# define OBJECTS_NUMBER_HPP_

# include <type_traits>
# include <limits>
# include <cstdint>
# include "Objects/Memory.hpp"

namespace                       Objects
{
    class                       Number
    {
        /* Attributes */

        uint8_t                 *_data;
        uint32_t        		_capacity;
        uint8_t             	_sign;

        /* Private Methods */

        void                    capacity(uint32_t const capacity);

        /* Static Private Methods */

        static uint32_t         realMemSize(uint8_t const *data,
                                            uint32_t const size);
        static int8_t           compare(uint8_t const *left,
                                        uint8_t const *right,
                                        uint32_t const size);

        /* Private Inline Methods */

        inline uint32_t         realMemSize(void) const
            {
                return Objects::Number::realMemSize(this->_data, this->_capacity);
            }
        inline int8_t           compare(uint8_t const *right,
                                        uint32_t const size) const
            {
                return Number::compare(this->_data, right, size);
            }
        inline void             copy(uint8_t const *data, uint32_t const size)
            {
                Objects::Memory::copy<uint8_t>(this->_data, data, size);
            }

        inline void             initNotUsed(uint32_t const shift)
            {
                Objects::Memory::fill<uint8_t>(this->_data + shift, 0,
                                               this->_capacity - shift);
            }

        /* Template Private Inline Methods */

        template<typename _TypeInt, typename = typename std::enable_if<std::numeric_limits<_TypeInt>::is_integer, _TypeInt>::type>
        inline void             copy(_TypeInt const data, uint32_t const size)
            {
                this->copy(reinterpret_cast<uint8_t const *>(&data), size);
            }

        /* Template Private Methods and inline use generate code for integers */

        template<typename _TypeUInt>
        void                    init(typename std::enable_if<std::numeric_limits<_TypeUInt>::is_integer && std::is_unsigned<_TypeUInt>::value, _TypeUInt>::type const type)
            {
                this->capacity(Objects::Number::realMemSize<_TypeUInt>(type));
                this->copy(reinterpret_cast<uint8_t const *>(&type), this->_capacity);
            }

        template<typename _TypeUInt>
        void                    assign(typename std::enable_if<std::numeric_limits<_TypeUInt>::is_integer && std::is_unsigned<_TypeUInt>::value, _TypeUInt>::type const type)
            {
                uint8_t         capacity = Objects::Number::realMemSize<_TypeUInt>(type);

                if (this->_capacity < capacity)
                    this->capacity(capacity);
                this->copy(reinterpret_cast<uint8_t const *>(&type), capacity);
                this->initNotUsed(capacity);
                this->_sign = 0;
            }

        template<typename _TypeInt>
        void                    assign(typename std::enable_if<std::numeric_limits<_TypeInt>::is_integer && std::is_signed<_TypeInt>::value, _TypeInt>::type const type)
            {
                this->assign<typename std::make_unsigned<_TypeInt>::type>(Objects::Number::abs<_TypeInt>(type));
                if (type < 0)
                    this->_sign = 1;
            }

        template<typename _TypeUInt>
        bool                    isEqual(typename std::enable_if<std::numeric_limits<_TypeUInt>::is_integer && std::is_unsigned<_TypeUInt>::value, _TypeUInt>::type const type)
            {
                uint32_t        realSize = this->realMemSize();

                return (!this->_sign && realSize == Objects::Number::realMemSize<_TypeUInt>(type)
                        && !this->compare(reinterpret_cast<uint8_t const *>(&type), realSize));
            }

        template<typename _TypeInt>
        bool                    isEqual(typename std::enable_if<std::numeric_limits<_TypeInt>::is_integer && std::is_signed<_TypeInt>::value, _TypeInt>::type const type)
            {
                uint32_t        realSize = this->realMemSize();
                auto            uType = Objects::Number::abs<_TypeInt>(type);

                return (this->_sign == ((type < 0) ? 1 : 0) && realSize == Objects::Number::realMemSize<typename std::make_unsigned<_TypeInt>::type>(uType)
                        && !this->compare(reinterpret_cast<uint8_t const *>(&uType), realSize));
            }

        /* Template Static Private Inline Methods */

        template<typename _TypeUInt>
        static inline uint32_t	realMemSize(typename std::enable_if<std::numeric_limits<_TypeUInt>::is_integer && std::is_unsigned<_TypeUInt>::value, _TypeUInt>::type const data)
            {
                return Objects::Number::realMemSize(reinterpret_cast<uint8_t const *>(&data), sizeof(_TypeUInt));
            }

	public:
        /* ctor & dtor on canonics form */

        inline Number(uint8_t const type = 0) : _data(nullptr), _capacity(0), _sign(0)
            {
                this->init<uint8_t>(type);
            };
        inline Number(uint16_t const type) : _data(nullptr), _capacity(0), _sign(0)
            {
                this->init<uint16_t>(type);
            };
        inline Number(uint32_t const type) : _data(nullptr), _capacity(0), _sign(0)
            {
                this->init<uint32_t>(type);
            };
        inline Number(uint64_t const type) : _data(nullptr), _capacity(0), _sign(0)
            {
                this->init<uint64_t>(type);
            };
        inline Number(int8_t const type) : _data(nullptr), _capacity(0), _sign((type < 0) ? 1 : 0)
            {
                this->init<uint8_t>(Objects::Number::abs<int8_t>(type));
            };
        inline Number(int16_t const type) : _data(nullptr), _capacity(0), _sign((type < 0) ? 1 : 0)
            {
                this->init<uint16_t>(Objects::Number::abs<int16_t>(type));
            };
        inline Number(int32_t const type) : _data(nullptr), _capacity(0), _sign((type < 0) ? 1 : 0)
            {
                this->init<uint32_t>(Objects::Number::abs<int32_t>(type));
            };
        inline Number(int64_t const type) : _data(nullptr), _capacity(0), _sign((type < 0) ? 1 : 0)
            {
                this->init<uint64_t>(Objects::Number::abs<int64_t>(type));
            };

        Number(Number const &copy);
        Number                  &operator=(Number const &other);
        ~Number(void);

        /* Operator assignment */
        inline Number           &operator=(uint8_t const type)
            {
                this->assign<uint8_t>(type);
                return *this;
            };

        inline Number           &operator=(uint16_t const type)
            {
                this->assign<uint16_t>(type);
                return *this;
            };

        inline Number           &operator=(uint32_t const type)
            {
                this->assign<uint32_t>(type);
                return *this;
            };

        inline Number           &operator=(uint64_t const type)
            {
                this->assign<uint64_t>(type);
                return *this;
            };

        inline Number           &operator=(int8_t const type)
            {
                this->assign<int8_t>(type);
                return *this;
            };

        inline Number           &operator=(int16_t const type)
            {
                this->assign<int16_t>(type);
                return *this;
            };

        inline Number           &operator=(int32_t const type)
            {
                this->assign<int32_t>(type);
                return *this;
            };

        inline Number           &operator=(int64_t const type)
            {
                this->assign<int64_t>(type);
                return *this;
            };

        /* Operator convert */

        /* Operator comparaison */

        inline bool              operator==(Objects::Number const &other) const
            {
                uint32_t        realSize = this->realMemSize();

                return (this->_sign == other._sign && realSize == other.realMemSize()
                        && !this->compare(other._data, realSize));
            }

        inline bool              operator==(uint8_t const type)
            {
                return this->isEqual<uint8_t>(type);
            };

        inline bool              operator==(uint16_t const type)
            {
                return this->isEqual<uint16_t>(type);
            };

        inline bool              operator==(uint32_t const type)
            {
                return this->isEqual<uint32_t>(type);
            };

        inline bool              operator==(uint64_t const type)
            {
                return this->isEqual<uint64_t>(type);
            };

        inline bool              operator==(int8_t const type)
            {
                return this->isEqual<int8_t>(type);
            };

        inline bool              operator==(int16_t const type)
            {
                return this->isEqual<int16_t>(type);
            };

        inline bool              operator==(int32_t const type)
            {
                return this->isEqual<int32_t>(type);
            };

        inline bool              operator==(int64_t const type)
            {
                return this->isEqual<int64_t>(type);
            };


        /* Public static inline Methods */
        template<typename _TypeInt, typename = typename std::enable_if<std::is_signed<_TypeInt>::value && std::numeric_limits<_TypeInt>::is_integer, _TypeInt>::type>
        inline static typename std::make_unsigned<_TypeInt>::type   abs(_TypeInt const type)
            {
                return (type < 0) ? -type : type;
            }
    };
}

#endif /* !OBJECTS_NUMBER_HPP_ */
