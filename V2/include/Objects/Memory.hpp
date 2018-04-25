/**
* \file				Memory.hpp
* \author			Sébastien Le Maire
* \version			1.0
* \date				23 Février 2018
*/

#ifndef OBJECTS_MEMORY_HPP_
# define OBJECTS_MEMORY_HPP_

# include <cstdlib>
# include <cstring>

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

		template<typename _Type>
		inline _Type					*alloc(size_t const size)
		{
			return reinterpret_cast<_Type *>(Objects::Memory::alloc(size * sizeof(_Type)));
		}

		template<typename _Type>
		inline _Type					*realloc(_Type *ptr, size_t const size)
		{
			return reinterpret_cast<_Type *>(Objects::Memory::realloc(static_cast<void *>(ptr),
																	  size * sizeof(_Type)));
		}

		template<typename _Type>
		inline void						free(_Type *&ptr)
		{
			Objects::Memory::free(reinterpret_cast<void *&>(ptr));
		}

		template<typename _Type1, typename _Type2 = _Type1>
		inline void						copy(_Type1 *dst, _Type2 const *src,
											 size_t const size)
		{
			Objects::Memory::copy(reinterpret_cast<void *>(dst),
								  reinterpret_cast<void const *>(src),
								  size);
		}

		template<typename _Type1, typename _Type2 = _Type1>
		inline void						move(_Type1 *dst, _Type2 const *src,
											 size_t const size)
		{
			Objects::Memory::move(reinterpret_cast<void *>(dst),
								  reinterpret_cast<void const *>(src),
								  size);
		}
	}
}

#endif /* !OBJECTS_MEMORY_HPP_ */
