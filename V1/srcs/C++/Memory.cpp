/**
* \file				Memory.cpp
* \author			Sébastien Le Maire
* \version			1.0
* \date				23 Février 2018
*/

#include "Objects/Memory.hpp"
#include "Objects/Exception.hpp"

namespace							Objects
{
	namespace						Memory
	{
		void						*alloc(size_t const size)
		{
			void					*ptr = ::malloc(size);

			if (!ptr)
				throw Objects::Exception(Objects::Exception::BAD_ALLOC);
			return ptr;
		}

		void						*realloc(void *ptr, size_t const size)
		{
			ptr = ::realloc(ptr, size);
			if (!ptr)
				throw Objects::Exception(Objects::Exception::BAD_ALLOC);
			return ptr;
		}

		void						free(void *&ptr)
		{
			if (ptr)
			{
				::free(ptr);
				ptr = nullptr;
			}
		}
	}
}
