
#include "Objects/Memory.hpp"
#include "Objects/Exception.hpp"

namespace							Objects
{
	namespace						Memory
	{
		void						*alloc(wordsize const size)
		{
			void					*ptr = ::malloc(size);

			if (!ptr)
				throw Objects::Exception(Objects::Exception::BAD_ALLOC);
			return ptr;
		}

		void						*realloc(void *ptr, wordsize const size)
		{
			ptr = ::realloc(ptr, size);
			if (!ptr)
				throw Objects::Exception(Objects::Exception::BAD_ALLOC);
			return ptr;
		}
	}
}
