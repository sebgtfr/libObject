/**
* \file				list_ctor.c
* \author			Sébastien Le Maire
* \version			1.0
* \date				04 Décembre 2016
*/

#include "list.h"


/**
* \brief			Construteur de l'objet t_list
* \details			Initialise un objet t_list ({this}) pouvant contenir des éléments
*				de taille {size_item} en mémoire (cf #t_list)
* \param this			Référence sur la liste
* \param size_item		Taille en mémoire de l'objet contenu un maillon de la liste.
* \return			none
*
*/
void				list_ctor(t_list *this,
					  uint64_t const size_item)
{
  *this = _LIST_CTOR_(size_item);
}
