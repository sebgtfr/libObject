/**
* \file				list_to_vector.c
* \author			Sébastien Le Maire
* \version			1.0
* \date				04 Décembre 2016
*/

#include <string.h>
#include "vector.h"
#include "list.h"

/**
* \brief		        Convertie une liste en tableau.
* \details		        Génére un tableau (cf #t_vector) à partir d'une liste (cf #t_list).
				Penser à free le vector après l'avoir détruit.
* \param this			Référence vers la liste à convertir.
* \return		        Référence vers un tableau (cf #t_vector) en cas de succès.
* \return			NULL en cas d'echec.
*
*/
t_vector			*list_to_vector(t_list *this)
{
  t_vector			*vector = malloc(sizeof(*vector));

  if (vector && vector_ctor(vector, this->_size_item, this->_length))
    {
      t_item			*node = this->_begin;
      void			*iterator = vector->_data;

      while (node && vector->_length < this->_length)
	{
	  (void)memcpy(iterator, (void *)node->_data, vector->_size_item);
	  ++vector->_length;
	  iterator += vector->_size_item;
	  node = node->_next;
	}
      return (vector);
    }
  return (NULL);
}
