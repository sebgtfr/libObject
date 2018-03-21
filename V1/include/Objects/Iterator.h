/**
* \file				Iterator.h
* \author			Sébastien Le Maire
* \version			1.0
* \date				21 Mars 2018
*/

#ifndef OBJECTS_ITERATOR_H_
# define OBJECTS_ITERATOR_H_

# include <stdint.h>

typedef struct					Iterator
{
	uint8_t						__private[sizeof(size_t)];
}								Iterator;

#endif /* !OBJECTS_ITERATOR_H_ */
