/**
* \file				Buffer.c
* \author			Sébastien Le Maire
* \version			1.0
* \date				25 Février 2018
*/

#include <string.h>
#include "Objects/Buffer.h"

/* Ctor & Dtor */

_OBJECTS_BUFFER_				Buffer_ctor(size_t const capacity)
{
	return Objects::Buffer(capacity);
}

_OBJECTS_BUFFER_				Buffer_ctorCopy(_OBJECTS_BUFFER_ const *copy)
{
	return Objects::Buffer(*copy);
}

void							Buffer_eq(_OBJECTS_BUFFER_ *self,
										  _OBJECTS_BUFFER_ const *oth)
{
	*self = *oth;
}

void							Buffer_dtor(_OBJECTS_BUFFER_ *self)
{
	self->~Buffer();
	static_cast<void>(::memset(reinterpret_cast<void *>(self), 0, __SIZEOF_BUFFER__));
}

/* Getters */

size_t							Buffer_getCapacity(_OBJECTS_BUFFER_ const *self)
{
	return self->capacity();
}

size_t							Buffer_size(_OBJECTS_BUFFER_ const *self)
{
	return self->size();
}

uint8_t							*Buffer_rawData(_OBJECTS_BUFFER_ const *self)
{
	return self->rawData();
}

uint8_t							Buffer_at(_OBJECTS_BUFFER_ *self,
										  size_t const i)
{
	return &self->at(i);
}

uint8_t							Buffer_atConst(_OBJECTS_BUFFER_ const *self,
											   size_t const i)
{
	return self->at(i);
}

bool							Buffer_empty(_OBJECTS_BUFFER_ const *self)
{
	return self->empty();
}

/* Setters */

void							Buffer_setCapacity(_OBJECTS_BUFFER_ *self,
												   size_t const capacity)
{
	self->capacity(capacity);
}

void							Buffer_resize(_OBJECTS_BUFFER_ *self,
											  size_t const size)
{
	self->resize(size);
}

void							Buffer_clear(_OBJECTS_BUFFER_ *self)
{
	self->clear();
}

void							Buffer_write(_OBJECTS_BUFFER_ *self,
											 uint8_t const *data,
											 size_t const size)
{
	self->write(data, size);
}

void							Buffer_concat(_OBJECTS_BUFFER_ *self,
											  _OBJECTS_BUFFER_ const *buffer)
{
	self->write(*buffer);
}

void							Buffer_shift(_OBJECTS_BUFFER_ *self,
											 size_t const nbLeftBytes)
{
	self->shift(nbLeftBytes);
}
