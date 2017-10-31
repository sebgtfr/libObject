/**
* \file				list_clear.c
* \author			Sébastien Le Maire
* \version			1.0
* \date				04 Décembre 2016
*/

#include <stdlib.h>
#include "list.h"

/**
* \brief			Construteur de l'objet t_list
* \details			Utilise le callback {clear} sur l'objet contenu dans
*				chaques maillons de la liste pour appliquer une dernière action à cette objet et/ou détruire de la
*				memoire des attributs de celui-ci.
* \param this			Référence sur la liste
* \param clear			Callback permettant un destruction de l'objet contenu dans chaques
*				maillons de la liste.
* \return			none
*
*/
void				list_clear(t_list *this, t_fct_clear clear)
{
  t_item			*elem;

  while (this->_begin)
    {
      elem = this->_begin;
      this->_begin = this->_begin->_next;
      if (clear)
	clear((void *)elem->_data);
      free(elem);
    }
  this->_length = 0;
  this->_end = NULL;
}
