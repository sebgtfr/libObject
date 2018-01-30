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
* \param clear			Callback permettant un destruction de l'objet contenu dans chaques
*				maillons de la liste.
* \return			none
*
*/
void				list_dtor(t_list *this, t_fct_clear clear)
{
  list_clear(this, clear);
  *this = _LIST_CTOR_(0);
}
