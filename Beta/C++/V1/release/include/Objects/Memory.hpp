
#ifndef OBJECTS_MEMORY_HPP_
# define OBJECTS_MEMORY_HPP_

# include <cstdlib>
# include "Objects/System.hpp"

namespace								Objects
{
	namespace							Memory
	{
		inline wordsize					align(wordsize const size)
		{
# if SYSTEM_ENV == 64
			return ((((size - 1) >> 3) << 3) + 8);
# else
			return ((((size - 1) >> 2) << 2) + 4);
# endif /* !SYSTEM ENV */
		}

		void							*alloc(wordsize const size);
		void							*realloc(void *,
												 wordsize const size);
		inline void						free(void *&ptr)
		{
			::free(ptr);
			ptr = NULL;
		}
	}
}

#endif /* !OBJECTS_MEMORY_HPP_ */
