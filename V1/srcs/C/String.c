/**
* \file				String.c
* \author			Sébastien Le Maire
* \version			1.0
* \date				13 Mars 2018
*/

#include <string.h>
#include <iostream>
#include "Objects/String.h"

/* Ctor & Dtor */

_OBJECTS_STRING_				String_ctor(char const * const str)
{
	return Objects::String(str);
}

_OBJECTS_STRING_				*String_new(char const * const str)
{
	return new Objects::String(str);
}

_OBJECTS_STRING_				String_ctorCopy(_OBJECTS_STRING_ const *copy)
{
	return Objects::String(*copy);
}

_OBJECTS_STRING_				*String_newCopy(_OBJECTS_STRING_ const *copy)
{
	return new Objects::String(*copy);
}

_OBJECTS_STRING_				*String_eq(_OBJECTS_STRING_ *self,
										   _OBJECTS_STRING_ const *oth)
{
	*self = *oth;
	return self;
}

void							String_dtor(_OBJECTS_STRING_ *self)
{
	self->~String();
	static_cast<void>(::memset(reinterpret_cast<void *>(self), 0, __SIZEOF_STRING__));
}

void							String_delete(_OBJECTS_STRING_ *self)
{
	delete self;
}

/* Getters */

size_t							String_getCapacity(_OBJECTS_STRING_ const *self)
{
	return self->capacity();
}

size_t							String_size(_OBJECTS_STRING_ const *self)
{
	return self->size();
}

size_t							String_unicodeSize(_OBJECTS_STRING_ const *self)
{
	return self->unicodeSize();
}

char							*String_rawData(_OBJECTS_STRING_ const *self)
{
	return self->rawData();
}

char							String_at(_OBJECTS_STRING_ const *self,
										  size_t const i)
{
	return self->at(i);
}

UnicodeChar						String_unicodeAt(_OBJECTS_STRING_ const *self,
												 size_t const i)
{
	return self->unicodeAt(i);
}

bool							String_empty(_OBJECTS_STRING_ const *self)
{
	return self->empty();
}

/* Setters */

void							String_setCapacity(_OBJECTS_STRING_ *self,
												   size_t const capacity)
{
	self->capacity(capacity);
}

void							String_resize(_OBJECTS_STRING_ *self,
											  size_t const size)
{
	self->resize(size);
}

_OBJECTS_STRING_				*String_assign(_OBJECTS_STRING_ *self,
											   char const * const str)
{
	*self = str;
	return self;
}

void							String_clear(_OBJECTS_STRING_ *self)
{
	self->clear();
}

/* Methods */
_OBJECTS_STRING_				*String_concat(_OBJECTS_STRING_ *self,
											   char const * const str)
{
	*self += str;
	return self;
}

_OBJECTS_STRING_				*String_concatString(_OBJECTS_STRING_ *self,
													 _OBJECTS_STRING_ const *str)
{
	*self += *str;
	return self;
}

_OBJECTS_STRING_ITERATOR_		String_begin(_OBJECTS_STRING_ const *self)
{
	return self->begin();
}

_OBJECTS_STRING_ITERATOR_		String_end(_OBJECTS_STRING_ const *self)
{
	return self->end();
}

_OBJECTS_UNICODE_STRING_ITERATOR_	String_unicodeBegin(_OBJECTS_STRING_ const *self)
{
	return self->unicodeBegin();
}

_OBJECTS_UNICODE_STRING_ITERATOR_	String_unicodeEnd(_OBJECTS_STRING_ const *self)
{
	return self->unicodeEnd();
}

size_t							String_find(_OBJECTS_STRING_ const *self,
											UnicodeChar const c)
{
	return self->find(Objects::Unicode::Char(c));
}

int								String_cmp(_OBJECTS_STRING_ const *self,
										   char const * const str)
{
	return self->compare(str);
}

int								String_ncmp(_OBJECTS_STRING_ const *self,
											char const * const str,
											size_t const n,
											size_t const begin)
{
	return self->compare(str, n, begin);
}

int								String_compare(_OBJECTS_STRING_ const *self,
											   _OBJECTS_STRING_ const *str)
{
	return self->compare(*str);
}

int								String_ncompare(_OBJECTS_STRING_ const *self,
												_OBJECTS_STRING_ const *str,
												size_t const n,
												size_t const begin)
{
	return self->compare(*str, n, begin);
}

void							String_shift(_OBJECTS_STRING_ *self,
											 size_t const nbLeftBytes)
{
	self->shift(nbLeftBytes);
}

_OBJECTS_STRING_				String_uppercase(_OBJECTS_STRING_ const *self)
{
	return self->uppercase();
}

_OBJECTS_STRING_				String_lowercase(_OBJECTS_STRING_ const *self)
{
	return self->lowercase();
}

_OBJECTS_STRING_				String_reverse(_OBJECTS_STRING_ const *self)
{
	return self->reverse();
}

_OBJECTS_STRING_				String_substr(_OBJECTS_STRING_ const *self,
											  size_t const begin)
{
	return self->substr(begin);
}

_OBJECTS_STRING_				String_nsubstr(_OBJECTS_STRING_ const *self,
											   size_t const begin,
											   size_t size)
{
	return self->substr(begin, size);
}

_OBJECTS_STRING_				String_substrToUnicode(_OBJECTS_STRING_ const *self,
													   size_t const begin,
													   UnicodeChar const end)
{
	return self->substr(begin, Objects::Unicode::Char(end));
}

_OBJECTS_STRING_				String_substrUnicode(_OBJECTS_STRING_ const *self,
													 UnicodeChar const begin,
													 UnicodeChar const end)
{
	return self->substr(Objects::Unicode::Char(begin), Objects::Unicode::Char(end));
}

void							String_print(_OBJECTS_STRING_ const *self)
{
	std::cout << *self;
}

/* Iterator */

_OBJECTS_STRING_ITERATOR_		String_Iterator_next(_OBJECTS_STRING_ITERATOR_ it)
{
	return ++it;
}

_OBJECTS_STRING_ITERATOR_		String_Iterator_prev(_OBJECTS_STRING_ITERATOR_ it)
{
	return --it;
}

char							String_Iterator_content(_OBJECTS_STRING_ITERATOR_ it)
{
	return *it;
}

bool							String_Iterator_eq(_OBJECTS_STRING_ITERATOR_ self,
												   _OBJECTS_STRING_ITERATOR_ it)
{
	return self == it;
}

/* Unicode Iterator */

_OBJECTS_UNICODE_STRING_ITERATOR_	Unicode_String_Iterator_next(_OBJECTS_UNICODE_STRING_ITERATOR_ it)
{
	return ++it;
}

_OBJECTS_UNICODE_STRING_ITERATOR_	Unicode_String_Iterator_prev(_OBJECTS_UNICODE_STRING_ITERATOR_ it)
{
	return --it;
}

UnicodeChar							Unicode_String_Iterator_content(_OBJECTS_UNICODE_STRING_ITERATOR_ it)
{
	return *it;
}

bool								Unicode_String_Iterator_eq(_OBJECTS_UNICODE_STRING_ITERATOR_ self,
															   _OBJECTS_UNICODE_STRING_ITERATOR_ it)
{
	return self == it;
}
