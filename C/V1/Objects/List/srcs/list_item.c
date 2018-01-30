/**
* \file				list_item.c
* \author			Sébastien Le Maire
* \version			1.0
* \date				04 Décembre 2016
*/

#include "list.h"

/**
* \brief		        Récupère un éléments de la liste.
* \details		        Récupère à la position {offset} de la liste {this} l'objet du maillon.
*				Si la position {offset} indiqué est plus grande que la taille de la liste, récupère l'élément
*				à la fin de celle-ci.
* \param this			Référence sur la liste
* \param offset			Position du maillon à récupérer dans la liste.
* \return			Référence vers l'objet contenu dans le maillon en position {offset} en cas de succès.
* \return			NULL en cas d'echec.
*
*/
void				*list_item(t_list *this, uint64_t const offset)
{
  t_item			*node = NULL;

  if (this->_length)
    {
      uint64_t			i;

      if (offset > (this->_length / 2))
	{
	  node = this->_end;
	  i = this->_length - 1;
	  while ((node != this->_begin) && (i != offset))
	    {
	      node = node->_prev;
	      --i;
	    }
	  if (node == this->_begin)
	    node = NULL;
	}
      else
	{
	  i = 0;
	  node = this->_begin;
	  while (node && i < offset)
	    {
	      node = node->_next;
	      ++i;
	    }
	}
    }
  return ((node) ? (void *)node->_data : NULL);
}
