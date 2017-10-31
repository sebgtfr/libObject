/**
* \file				list_pop.c
* \author			Sébastien Le Maire
* \version			1.0
* \date				04 Décembre 2016
*/

#include <stdlib.h>
#include "list.h"

/**
* \brief		        Détruit le premier maillon de la liste.
* \details			Supprime le maillon au début de la liste {this} en appelant le callback {clear}
*				pour détruire l'objet contenu dans le maillon.
* \param this			Référence sur la liste
* \param clear			Callback permettant un destruction de l'objet contenu dans chaques
*				maillons de la liste.
* \return			none
*
*/
void			list_pop_front(t_list *this, t_fct_clear clear)
{
  if (this->_begin)
    {
      t_item		*node = this->_begin;

      if ((this->_begin = this->_begin->_next))
	this->_begin->_prev = NULL;
      else
	this->_end = NULL;
      if (clear)
	clear(node->_data);
      free(node);
      --(this->_length);
    }
}

/**
* \brief			Détruit le dernier maillon de la liste.
* \details			Supprime le maillon à la fin de la liste {this} en appelant le callback {clear}
*				pour détruire l'objet contenu dans le maillon.
* \param this			Référence sur la liste
* \param clear			Callback permettant un destruction de l'objet contenu dans chaques
*				maillons de la liste.
* \return			none
*
*/
void			list_pop_back(t_list *this, t_fct_clear clear)
{
  if (this->_end)
    {
      t_item		*node = this->_end;

      if ((this->_end = this->_end->_prev))
	this->_end->_next = NULL;
      else
	this->_begin = NULL;
      if (clear)
	clear(node->_data);
      free(node);
      --(this->_length);
    }
}
