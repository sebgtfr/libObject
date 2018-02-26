/**
* \file				vector_push.c
* \author			Sébastien Le Maire
* \version			1.0
* \date				09 Décembre 2016
*/

#include <stdlib.h>
#include <string.h>
#include "vector.h"

/**
* \brief		        Ajoute les éléments d'un tableau à la fin d'un autre.
* \details		        Ajoute les éléments contenu dans le tableau {vector}
*				à la fin du tableau this.
* \param this			Référence sur le tableau
* \param vector			Référence sur le tableau à ajouté.
* \return			true en cas de succès.
* \return			false en cas d'echec (allocation mémoire).
*
*/
t_bool				vector_push(t_vector *this, t_vector const *vector)
{
  if (this->_size_item == vector->_size_item)
    {
      uint64_t			size = this->_length + vector->_length;
      uint64_t			capacity =  (size > this->_capacity) ? (size - this->_capacity) : 0;

      if (capacity && (!VECTOR_ADD_BLOCK(this, capacity)))
	return (false);
      (void)memcpy(this->_data + (this->_length * this->_size_item), vector->_data,
		   vector->_size_item * vector->_length);
      this->_length = size;
    }
  return (true);
}

/**
* \brief		        Ajoute un élément à la fin du tableau.
* \details		        Ajoute l'éléments {content} à la fin
*			        du tableau {this}.
* \param this			Référence sur le tableau
* \param content       		Référence sur l'élément à ajouté.
* \return			true en cas de succès.
* \return			false en cas d'echec (allocation mémoire).
*
*/
t_bool				vector_push_back(t_vector *this, void const *content)
{
  if (content)
    {
      void			*elem;

      if ((this->_length >= this->_capacity))
	{
	  ++this->_capacity;
	  if (!(this->_data = realloc(this->_data,
					this->_size_item * this->_capacity)))
	    return (false);
	}
      elem = this->_data + VECTOR_INDEX(this, this->_length);
      ++this->_length;
      (void)memcpy(elem, content, this->_size_item);
    }
  return (true);
}
