
#include "Objects/Number.hpp"

namespace                       Objects
{
    /* Private Methods */

    void                        Number::capacity(uint32_t const capacity)
    {
        this->_data = Objects::Memory::realloc<uint8_t>(this->_data, capacity);
        this->_capacity = capacity;
    }

    /* Static Private Methods */
    uint32_t                    Number::realMemSize(uint8_t const *data,
                                                    uint32_t const size)
    {
        uint8_t const			*it = data + (size - 1);
        uint32_t				extraSize = 0;

        while (it > data && !(*it))
        {
            --it;
            ++extraSize;
        }
        return size - extraSize;
    }

    int8_t                      Number::compare(uint8_t const *left,
                                                uint8_t const *right,
                                                uint32_t const size)
    {
        static uint8_t const	wordSize = sizeof(size_t);
        uint8_t const			*end = left - 1;
        uint8_t const			*itLeft = left + size - 1;
        uint8_t const			*itRight = right + size - 1;

        while (itLeft > (end + wordSize))
        {
            size_t				valLeft = *reinterpret_cast<size_t const *>(itLeft);
            size_t				valRight = *reinterpret_cast<size_t const *>(itRight);

            if (valLeft != valRight)
                return ((valLeft < valRight) ? -1 : 1);
            itLeft -= wordSize;
            itRight -= wordSize;
        }
        while (itLeft > end)
        {
            if (*itLeft != *itRight)
                return ((*itLeft < *itRight) ? -1 : 1);
            --itLeft;
            --itRight;
        }
        return 0;
    }

    /* ctor & dtor on canonics form */

    Number::Number(Number const &copy)
        : _data(nullptr), _capacity(0), _sign(copy._sign)
    {
        this->capacity(copy.realMemSize());
        this->copy(copy._data, this->_capacity);
    }

    Number                      &Number::operator=(Number const &other)
    {
        if (&other != this)
        {
            uint32_t            capacity = other.realMemSize();

            if (this->_capacity < capacity)
                this->capacity(capacity);
            this->copy(other._data, capacity);
            this->initNotUsed(capacity);
            this->_sign = other._sign;
        }
        return *this;
    }

    Number::~Number(void)
    {
        Objects::Memory::free<uint8_t>(this->_data);
    }

}
