/**
* \file				vector_ctor.c
* \author			Sébastien Le Maire
* \version			1.0
* \date				04 Décembre 2016
*/

#include <stdlib.h>
#include "vector.h"

/**
* \brief			Construteur de l'objet t_vector
* \details			Initialise un objet t_vector ({this}) pouvant contenir des éléments
*				de taille {size_item} en mémoire (cf #t_vector)
* \param this			Référence sur le tableau
* \param size_item		Taille en mémoire de l'objet contenu une case du tableau.
* \return			none
*
*/
t_bool				vector_ctor(t_vector *this,
					    uint64_t const size_item,
					    uint64_t const capacity)
{
  if (capacity)
    {
      this->_length = 0;
      this->_capacity = capacity;
      this->_size_item = size_item;
      if (!(this->_data = calloc(size_item, capacity)))
	{
	  this->_capacity = 0;
	  return (false);
	}
    }
  else
    {
      *this = _VECTOR_CTOR_(size_item);
    }
  return (true);
}
