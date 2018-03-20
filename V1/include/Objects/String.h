/**
* \file				String.h
* \author			Sébastien Le Maire
* \version			1.0
* \date				25 Février 2018
*/

#ifndef OBJECTS_STRING_H_
# define OBJECTS_STRING_H_

# include "Objects/String.hpp"

# ifndef __cplusplus

typedef struct					String
{
	uint8_t						__private[__SIZEOF_STRING__];
}								String;

typedef struct					StringIterator
{
	uint8_t						__private[__SIZEOF_STRING_ITERATOR__];
}								StringIterator;

typedef StringIterator			UnicodeStringIterator;

# define _OBJECTS_STRING_					String
# define _OBJECTS_STRING_ITERATOR_			StringIterator
# define _OBJECTS_UNICODE_STRING_ITERATOR_	UnicodeStringIterator

# else

# define _OBJECTS_STRING_					Objects::String
# define _OBJECTS_STRING_ITERATOR_			Objects::String::Iterator
# define _OBJECTS_UNICODE_STRING_ITERATOR_	Objects::Unicode::String::Iterator

extern "C" {

# endif /* !CPLUSPLUS */

	/* Prototype Methods */

	/* Ctor & Dtor */
	extern _OBJECTS_STRING_		String_ctor(char const * const str);
	extern _OBJECTS_STRING_		*String_new(char const * const str);
	extern _OBJECTS_STRING_		String_ctorCopy(_OBJECTS_STRING_ const *copy);
	extern _OBJECTS_STRING_		*String_newCopy(_OBJECTS_STRING_ const *copy);
	extern _OBJECTS_STRING_		*String_eq(_OBJECTS_STRING_ *self,
										   _OBJECTS_STRING_ const *oth);
	extern void					String_dtor(_OBJECTS_STRING_ *self);
	extern void					String_delete(_OBJECTS_STRING_ *self);

	/* Getters */
	extern size_t				String_getCapacity(_OBJECTS_STRING_ const *self);
	extern size_t				String_size(_OBJECTS_STRING_ const *self);
	extern size_t				String_unicodeSize(_OBJECTS_STRING_ const *self);
	extern char					*String_rawData(_OBJECTS_STRING_ const *self);
	extern char					String_at(_OBJECTS_STRING_ const *self,
										  size_t const i);
	extern UnicodeChar	String_unicodeAt(_OBJECTS_STRING_ const *self,
													 size_t const i);
	extern bool					String_empty(_OBJECTS_STRING_ const *self);

	/* Setters */
	extern void					String_setCapacity(_OBJECTS_STRING_ *self,
												   size_t const capacity);
	extern void					String_resize(_OBJECTS_STRING_ *self,
											  size_t const size);
	extern _OBJECTS_STRING_		*String_assign(_OBJECTS_STRING_ *self,
											   char const * const oth);
	extern void					String_clear(_OBJECTS_STRING_ *self);

	/* Methods */
	extern _OBJECTS_STRING_		*String_concat(_OBJECTS_STRING_ *self,
											   char const * const str);
	extern _OBJECTS_STRING_		*String_concatString(_OBJECTS_STRING_ *self,
													 _OBJECTS_STRING_ const *string);
	extern _OBJECTS_STRING_ITERATOR_	String_begin(_OBJECTS_STRING_ const *self);
	extern _OBJECTS_STRING_ITERATOR_	String_end(_OBJECTS_STRING_ const *self);
	extern _OBJECTS_UNICODE_STRING_ITERATOR_	String_unicodeBegin(_OBJECTS_STRING_ const *self);
	extern _OBJECTS_UNICODE_STRING_ITERATOR_	String_unicodeEnd(_OBJECTS_STRING_ const *self);
	extern size_t				String_find(_OBJECTS_STRING_ const *self,
											UnicodeChar const c);
	extern int					String_cmp(_OBJECTS_STRING_ const *self,
										   char const * const str);
	extern int					String_ncmp(_OBJECTS_STRING_ const *self,
											char const * const str,
											size_t const n,
											size_t const begin);
	extern int					String_compare(_OBJECTS_STRING_ const *self,
											   _OBJECTS_STRING_ const *str);
	extern int					String_ncompare(_OBJECTS_STRING_ const *self,
												_OBJECTS_STRING_ const *str,
												size_t const n,
												size_t const begin);
	extern void					String_shift(_OBJECTS_STRING_ *self,
											  size_t const nbLeftBytes);
	extern _OBJECTS_STRING_		String_uppercase(_OBJECTS_STRING_ const *self);
	extern _OBJECTS_STRING_		String_lowercase(_OBJECTS_STRING_ const *self);
	extern _OBJECTS_STRING_		String_reverse(_OBJECTS_STRING_ const *self);
	extern _OBJECTS_STRING_		String_substr(_OBJECTS_STRING_ const *self,
											  size_t const begin);
	extern _OBJECTS_STRING_		String_nsubstr(_OBJECTS_STRING_ const *self,
											   size_t const begin,
											   size_t size);
	extern _OBJECTS_STRING_		String_substrToUnicode(_OBJECTS_STRING_ const *self,
													   size_t const begin,
													   UnicodeChar const end);
	extern _OBJECTS_STRING_		String_substrUnicode(_OBJECTS_STRING_ const *self,
													 UnicodeChar const begin,
													 UnicodeChar const end);
	extern void					String_print(_OBJECTS_STRING_ const *self);

	/* Iterator */

	extern _OBJECTS_STRING_ITERATOR_	String_Iterator_next(_OBJECTS_STRING_ITERATOR_ it);
	extern _OBJECTS_STRING_ITERATOR_	String_Iterator_prev(_OBJECTS_STRING_ITERATOR_ it);
	extern char							String_Iterator_content(_OBJECTS_STRING_ITERATOR_ it);
	extern bool							String_Iterator_eq(_OBJECTS_STRING_ITERATOR_ self,
														   _OBJECTS_STRING_ITERATOR_ it);

	/* Unicode Iterator */

	extern _OBJECTS_UNICODE_STRING_ITERATOR_	Unicode_String_Iterator_next(_OBJECTS_UNICODE_STRING_ITERATOR_ it);
	extern _OBJECTS_UNICODE_STRING_ITERATOR_	Unicode_String_Iterator_prev(_OBJECTS_UNICODE_STRING_ITERATOR_ it);
	extern UnicodeChar							Unicode_String_Iterator_content(_OBJECTS_UNICODE_STRING_ITERATOR_ it);
	extern bool									Unicode_String_Iterator_eq(_OBJECTS_UNICODE_STRING_ITERATOR_ self,
																		   _OBJECTS_UNICODE_STRING_ITERATOR_ it);

# ifdef __cplusplus

}

# endif /* !CPLUSPLUS */

#endif /* !OBJECTS_STRING_HPP_ */
