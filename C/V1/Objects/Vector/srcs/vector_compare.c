/**
* \file				vector_compare.c
* \author			Sébastien Le Maire
* \version			1.0
* \date				09 Décembre 2016
*/

#include "vector.h"

/**
* \brief		        Compare un élément avec ceux de le tableau.
* \details		        Parse l'intégralité des cases du tableau en éxécutant le callback {compare} pour chaques objets
*				en ajoutant en second paramètre du callback, la référence {data} fourni en paramètre.
*				Si votre callback {compare} retourne "true", alors la boucle s'arrête et la fonction retourne
*				l'objet de la case courrante.
* \param this			Référence sur le tableau
* \param compare		Callback appelé pour chaques cases du tableau afin de comparer une donnée
*				à chaques objets de le tableau.
* \param data		        Référence vers un objet quelconque.
* \return			Référence vers un objet quelconque en cas de succès.
* \return			NULL en cas d'echec
*
*/
void			*vector_compare(t_vector const *this,
					t_fct_compare compare,
					void const *data)
{
  if (compare)
    {
      void		*elem = this->_data;
      uint64_t		i = 0;

      while (i < this->_length)
	{
	  if (compare(elem, data))
	    return (elem);
	  elem += this->_size_item;
	  ++i;
	}
    }
  return (NULL);
}
