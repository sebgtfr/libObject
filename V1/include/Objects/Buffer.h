/**
* \file				Buffer.h
* \author			Sébastien Le Maire
* \version			1.0
* \date				25 Février 2018
*/

#ifndef OBJECTS_BUFFER_H_
# define OBJECTS_BUFFER_H_

# include "Objects/Buffer.hpp"

# ifndef __cplusplus

typedef struct					Buffer
{
	uint8_t						__private[__SIZEOF_BUFFER__];
}								Buffer;

# define _OBJECTS_BUFFER_		Buffer

# else

# define _OBJECTS_BUFFER_		Objects::Buffer

extern "C" {

# endif /* !CPLUSPLUS */

	/* Prototype Methods */

	/* Ctor & Dtor */
	extern _OBJECTS_BUFFER_		Buffer_ctor(size_t const capacity);
	extern _OBJECTS_BUFFER_		Buffer_ctorCopy(_OBJECTS_BUFFER_ const *copy);
	extern void					Buffer_eq(_OBJECTS_BUFFER_ *self,
										  _OBJECTS_BUFFER_ const *oth);
	extern void					Buffer_dtor(_OBJECTS_BUFFER_ *self);

	/* Getters */
	extern size_t				Buffer_getCapacity(_OBJECTS_BUFFER_ const *self);
	extern size_t				Buffer_size(_OBJECTS_BUFFER_ const *self);
	extern uint8_t				*Buffer_rawData(_OBJECTS_BUFFER_ const *self);
# define Buffer_at				*Buffer_at
	extern uint8_t				Buffer_at(_OBJECTS_BUFFER_ *self,
										   size_t const i);
	extern uint8_t				Buffer_atConst(_OBJECTS_BUFFER_ const *self,
											   size_t const i);
	extern bool					Buffer_empty(_OBJECTS_BUFFER_ const *self);

	/* Setters */
	extern void					Buffer_setCapacity(_OBJECTS_BUFFER_ *self,
												   size_t const capacity);
	extern void					Buffer_resize(_OBJECTS_BUFFER_ *self,
											  size_t const size);
	extern void					Buffer_clear(_OBJECTS_BUFFER_ *self);

	/* Methods */
	extern void					Buffer_write(_OBJECTS_BUFFER_ *self,
											 uint8_t const *data,
											 size_t const size);
	extern void					Buffer_concat(_OBJECTS_BUFFER_ *self,
											  _OBJECTS_BUFFER_ const *buffer);
	extern void					Buffer_shift(_OBJECTS_BUFFER_ *self,
											 size_t const nbLeftBytes);

# ifdef __cplusplus

}

# endif /* !CPLUSPLUS */

#endif /* !OBJECTS_BUFFER_HPP_ */
