/**
* \file				list_copy.c
* \author			Sébastien Le Maire
* \version			1.0
* \date				04 Décembre 2016
*/

#include "list.h"

/**
* \brief		        Détruit un maillon de la liste.
* \details		        Initialise un objet t_list ({this}) avec le contenu de la list {list}.
* \param this			Référence sur la liste
* \param list			Référence sur la liste à copier.
* \return			none
*
*/
t_bool				list_copy(t_list *this, t_list const *list)
{
  if ((this != list))
    {
      t_item			*node = this->_begin;

      *this = _LIST_CTOR_(this->_size_item);
      while (node)
	{
	  if (!list_push_back(this, (void *)node->_data))
	    return (false);
	  node = node->_next;
	}
    }
  return (true);
}
