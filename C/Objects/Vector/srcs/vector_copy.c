/**
* \file				vector_copy.c
* \author			Sébastien Le Maire
* \version			1.0
* \date				09 Décembre 2016
*/

#include <stdlib.h>
#include <string.h>
#include "vector.h"

/**
 * \brief		        Créé une copie du tableau {cpy} dans le tableau {this}
* \details		        Initialise un tableau {this} avec le contenu du tableau {cpy}
*				de taille {size_item} en mémoire (cf #t_vector)
* \param this			Référence sur le tableau
* \param cpy			Référence sur le tableau à copié.
* \return		        true en cas de succès.
* \return			false en cas d'echec (Allocation mémoire).
*
*/
t_bool				vector_copy(t_vector *this, t_vector const *cpy)
{
  if (this != cpy)
    {
      uint64_t			size = cpy->_size_item * cpy->_capacity;

      this->_length = cpy->_length;
      this->_capacity = cpy->_capacity;
      this->_size_item = cpy->_size_item;
      if (!(this->_data = realloc(this->_data, size)))
	{
	  this->_length = 0;
	  this->_capacity = 0;
	  this->_size_item = 0;
	  return (false);
	}
      (void)memcpy(this->_data, cpy->_data, size);
    }
  return (true);
}
