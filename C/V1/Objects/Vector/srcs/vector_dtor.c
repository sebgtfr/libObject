/**
* \file				vector_dtor.c
* \author			Sébastien Le Maire
* \version			1.0
* \date				09 Décembre 2016
*/

#include <stdlib.h>
#include "vector.h"

/**
* \brief		        Destructeur de l'objet t_vector
* \details		        Détruit un objet t_vector ({this}) et utilise le callback {clear} pour détruire les éléments.
*				de taille {size_item} en mémoire (cf #t_vector)
* \param this			Référence sur le tableau
* \param clear			callback vers une fonction pour détruire les objets contenu dans le tableau.
* \return			none
*
*/
void				vector_dtor(t_vector *this, t_fct_clear clear)
{
  vector_clear(this, clear);
  if (this->_data)
    {
      free(this->_data);
    }
  this->_capacity = 0;
  this->_size_item = 0;
}
