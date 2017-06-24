/**
* \file				vector_pop.c
* \author			Sébastien Le Maire
* \version			1.0
* \date				09 Décembre 2016
*/

#include "vector.h"

/**
* \brief		        Supprime le dernier éléments du tableau.
* \details		        Supprime le dernier élément à la fin
*			        du tableau {this}.
* \param this			Référence sur le tableau
* \param clear			Callback appellé pour détruire l'objet contenu
*				dans la case du tableau détruite.
* \return		        none.
*
*/
void				vector_pop_back(t_vector *this, t_fct_clear clear)
{
  if (this->_length)
    {
      --this->_length;
      if (this->_data && clear)
	clear(this->_data + VECTOR_INDEX(this, this->_length));
    }
}
