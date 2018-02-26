/**
* \file				vector_resize.c
* \author			Sébastien Le Maire
* \version			1.0
* \date				09 Décembre 2016
*/

#include <stdlib.h>
#include <string.h>
#include "vector.h"

/**
* \brief		        Redimensionne le tableau
* \details		        Modifie la taille du tableau {this} en mémoire
*				par la taille {size}. Si le tableau est plus
*				petit, la méthode utilise le callback {clear} pour
*				supprimer les objets exclus du tableau.
* \param this			Référence sur le tableau
* \param vector			Référence sur le tableau à ajouté.
* \return			true en cas de succès.
* \return			false en cas d'echec (allocation mémoire).
*
*/
t_bool				vector_resize(t_vector *this,
					      uint64_t const size,
					      t_fct_clear clear)
{
  if (!size)
    {
      uint64_t			size_item = this->_size_item;

      vector_dtor(this, clear);
      vector_ctor(this, size_item, 0);
    }
  else
    {
      if (clear)
	{
	  void			*elem = this->_data + (this->_size_item * this->_length);

	  while (this->_length > size)
	    {
	      clear(elem);
	      --this->_length;
	      elem -= this->_size_item;
	    }
	}
      else
	this->_length = size;
      this->_capacity = size;
      return CAST_BOOL((this->_data = realloc(this->_data, this->_size_item * size)));
    }
  return (true);
}
