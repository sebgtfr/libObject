/**
* \file				list_compare.c
* \author			Sébastien Le Maire
* \version			1.0
* \date				04 Décembre 2016
*/

#include "list.h"

/**
* \brief		        Compare un élément avec ceux de la liste.
* \details		        Parse l'intégralité des maillons de la liste en éxécutant le callback {compare} pour chaques objets
*				en ajoutant en second paramètre du callback, la référence {data} fourni en paramètre.
*				Si votre callback {compare} retourne "true", alors la boucle s'arrête et la fonction retourne
*				l'objet du maillon courrant.
* \param this			Référence sur la liste
* \param compare		Callback appelé pour chaques maillons de la liste afin de comparer une donnée
*				à chaques objets de la liste.
* \param data		        Référence vers un objet quelconque.
* \return			Référence vers un objet quelconque en cas de succès.
* \return			NULL en cas d'echec
*
*/
void				*list_compare(t_list const *this,
					      t_fct_compare compare,
					      void const *data)
{
  if (compare)
    {
      t_item			*iterator = this->_begin;

      while (iterator)
	{
	  if (compare((void *)iterator->_data, data))
	    return ((void *)iterator->_data);
	  iterator = iterator->_next;
	}
    }
  return (NULL);
}
