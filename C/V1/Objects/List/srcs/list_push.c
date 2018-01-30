/**
* \file				list_push.c
* \author			Sébastien Le Maire
* \version			1.0
* \date				04 Décembre 2016
*/

#include <stdlib.h>
#include <string.h>
#include "list.h"

/**
* \brief		        Crée un nouveau maillon en mémoire.
* \details		        Crée un nouveau maillon pour une liste de taille {size} et contenant l'objet {content}.
* \param content		Référence vers l'objet à ajouter.
* \param size			Taille en mémoire de l'objet {content}.
* \return		        Référence vers un maillon (cf #t_item) en cas de succès.
* \return			NULL en cas d'echec.
*
*/
static t_item			*list_new_item(void const *content,
					       size_t const size)
{
  t_item			*elem;

  if ((elem = malloc(sizeof(*elem) + size)))
    {
      if (content)
          (void)memcpy((void *)elem->_data, content, size);
      elem->_prev = NULL;
      elem->_next = NULL;
    }
  return (elem);
}

/**
* \brief		        Ajoute un nouveau élément dans la liste.
* \details		        Ajoute à la fin de la liste {this} un nouveau maillon contenant l'objet {content}
* \param this			Référence sur la liste
* \param content		Référence vers l'objet à ajouter.
* \return		        true en cas de succès
* \return			false en cas d'echec.
*
*/
t_bool				list_push_back(t_list *this,
					       void const *content)
{
  t_item			*elem;

  if ((elem = list_new_item(content, this->_size_item)))
    {
      if (!this->_begin)
	this->_begin = elem;
      else
	{
	  this->_end->_next = elem;
	  elem->_prev = this->_end;
	}
      this->_end = elem;
      ++this->_length;
      return (true);
    }
  return (false);
}

/**
* \brief		        Ajoute un nouveau élément dans la liste.
* \details		        Ajoute au début de la liste {this} un nouveau maillon contenant l'objet {content}
* \param this			Référence sur la liste
* \param content		Référence vers l'objet à ajouter.
* \return		        true en cas de succès
* \return			false en cas d'echec.
*
*/
t_bool				list_push_front(t_list *this,
						void const *content)
{
  t_item			*elem;

  if (content && (elem = list_new_item(content, this->_size_item)))
    {
      if (!this->_end)
        this->_end = elem;
      elem->_next = this->_begin;
      if (this->_begin)
        this->_begin->_prev = elem;
      this->_begin = elem;
      ++this->_length;
      return (true);
    }
  return (false);
}

/**
* \brief		        Ajoute un nouveau élément dans la liste.
* \details		        Ajoute à la fin de la liste {this} une copie des maillons de la liste {list}.
* \param this			Référence sur la liste
* \param list		        Référence vers une liste.
* \return		        true en cas de succès
* \return			false en cas d'echec.
*
*/
t_bool				list_push(t_list *this, t_list const *list)
{
  if (this->_size_item == list->_size_item)
    {
      t_item			*node = list->_begin;

      while (node)
	{
	  if (!list_push_back(this, (void *)node->_data))
	    return (false);
	  node = node->_next;
	}
      return (true);
    }
  return (false);
}

/**
* \brief		        Ajoute un nouveau élément dans la liste.
* \details		        Ajoute à la position {offset} de la liste {this} un nouveau maillon contenant l'objet {content}.
*				Si la position {offset} indiqué est plus grande que la taille de la liste, ajoute l'élément
*				à la fin de celle-ci.
* \param this			Référence sur la liste
* \param content		Référence vers l'objet à ajouter.
* \param offset			Position du nouveau maillon dans la liste.
* \return		        true en cas de succès
* \return			false en cas d'echec.
*
*/
t_bool				list_insert(t_list *this,
					    void const *content,
					    uint64_t const offset)
{
  t_item			*elem;

  if (!offset)
    return (list_push_front(this, content));
  else if ((this->_length - 1) >= offset)
    return (list_push_back(this, content));
  else if (content && (elem = list_new_item(content, this->_size_item)))
    {
      t_item			*current = LIST_DATA_TO_ITEM(list_item(this, offset));

      if (current)
	{
	  ++(this->_length);
	  elem->_next = current;
	  elem->_prev = current->_prev;
	  current->_prev->_next = elem;
	  current->_prev = elem;
	  return (true);
	}
    }
  return (false);
}
