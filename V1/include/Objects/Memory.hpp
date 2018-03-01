/**
* \file				Memory.hpp
* \author			Sébastien Le Maire
* \version			1.0
* \date				23 Février 2018
*/

#ifndef OBJECTS_MEMORY_HPP_
# define OBJECTS_MEMORY_HPP_

# include <stdlib.h>
# include <string.h>

# ifdef __cplusplus
namespace								Objects
{
	namespace							Memory
	{
		void							*alloc(size_t const size);
		void							*realloc(void *ptr,
												 size_t const size);
		void							free(void *&ptr);
		inline void						copy(void *dst, void const *src,
											 size_t const size)
		{
			static_cast<void>(::memcpy(dst, src, size));
		}
		inline void						move(void *dst, void const *src,
											 size_t const size)
		{
			static_cast<void>(::memmove(dst, src, size));
		}
	}
}
# endif /* !CPLUSPLUS */

#endif /* !OBJECTS_MEMORY_HPP_ */
