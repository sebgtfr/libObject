/**
* \file				vector_clear.c
* \author			Sébastien Le Maire
* \version			1.0
* \date				09 Décembre 2016
*/

#include "vector.h"

/**
* \brief		        Supprime tous les éléments du tableau.
* \details		        Supprime tous les éléments du tableau à l'aide du
*			        callback {clear}. Cette fonction ne détruit par la
*				mémoire du tableau.
* \param this			Référence sur le tableau
* \param clear			Callback appellé pour détruire l'objet contenu
*				dans la case du tableau détruite.
* \return		        none.
*
*/
void				vector_clear(t_vector *this, t_fct_clear clear)
{
  if (clear && this->_data)
    {
      uint64_t			i = 0;
      void			*elem = this->_data;

      while (i < this->_length)
	{
	  clear(elem);
	  elem += this->_size_item;
	  ++i;
	}
    }
  this->_length = 0;
}
