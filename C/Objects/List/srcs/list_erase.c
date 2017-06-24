/**
* \file				list_erase.c
* \author			Sébastien Le Maire
* \version			1.0
* \date				04 Décembre 2016
*/

#include "list.h"

/**
* \brief		        Détruit un maillon de la liste.
* \details			Détruit le maillon {item} de la liste {this}. Utilse le callback {clear}
*				pour détruire l'objet contenu dans le maillon.
*				ATTENTION: La méthode ne vérifie pas l'existance du maillon {item} dans
*				la liste {this}. Utilisé la mauvaise liste peut produire des erreurs.
* \param this			Référence sur la liste
* \param item			Référence vers le maillon à détruire.
* \param clear			Callback permettant un destruction de l'objet contenu dans chaques
*				maillons de la liste.
* \return			none
*
*/
void			list_erase(t_list *this, t_item *item,
				   t_fct_clear clear)
{
  if (this->_length && item)
    {
      t_item		*next = item->_prev;
      t_item		*prev = item->_next;

      prev = item->_prev;
      next = item->_next;
      if (this->_begin == item)
	this->_begin = this->_begin->_next;
      if (this->_end == item)
	this->_end = this->_end->_prev;
      if (clear)
	clear(item->_data);
      free(item);
      if (prev)
	prev->_next = next;
      if (next)
	next->_prev = prev;
      --(this->_length);
    }
}
