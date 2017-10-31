/**
* \file				list_foreach.c
* \author			Sébastien Le Maire
* \version			1.0
* \date				04 Décembre 2016
*/

#include <stdlib.h>
#include <stdarg.h>
#include "list.h"


/**
* \brief		        Applique une fonctionnalité sur l'ensemble des éléments de la liste.
* \details		        Parse l'intégralité des maillons de la liste en éxécutant le callback {foreach} pour chaques objets.
* \param this			Référence sur la liste.
* \param foreach		Callback appelé pour chaques maillons de la liste afin d'éxécuté
*				une fonctionnalité sur chaques objets de la liste.
* \return			none
*
*/
void				list_foreach(t_list const *this,
					     t_fct_foreach foreach)
{
  if (foreach)
    {
      t_item			*iterator = this->_begin;

      while (iterator)
	{
	  foreach((void *)iterator->_data);
	  iterator = iterator->_next;
	}
    }
}

/**
* \brief		        Applique une fonctionnalité sur l'ensemble des éléments de la liste.
* \details		        Parse l'intégralité des maillons de la liste en éxécutant le callback {foreach} pour chaques objets
*				en ajoutant en second paramètre du callback, la référence {data} fourni en paramètre.
* \param this			Référence sur la liste.
* \param foreach		Callback appelé pour chaques maillons de la liste afin d'éxécuté
* \param data			Référence vers un objet
*				une fonctionnalité sur chaques objets de la liste.
* \return			none
*
*/
void				list_foreach_data(t_list const *this,
						  t_fct_foreach_data foreach,
						  void *data)
{
  if (foreach)
    {
      t_item			*iterator = this->_begin;

      while (iterator)
	{
	  foreach((void *)iterator->_data, data);
	  iterator = iterator->_next;
	}
    }
}

/**
* \brief		        Applique une fonctionnalité sur l'ensemble des éléments de la liste.
* \details		        Parse l'intégralité des maillons de la liste en éxécutant le callback {foreach} pour chaques objets
*				en ajoutant en second paramètre du callback, un tableau de taille {argc} dont chaques case correspond
*				à une référence vers un objets fourni en paramètre via les varargs.
* \param this			Référence sur la liste.
* \param foreach		Callback appelé pour chaques maillons de la liste afin d'éxécuté
*				une fonctionnalité sur chaques objets de la liste.
* \param argc			Nombre de référence à récupérer via les varargs.
* \param ...		        Varargs: attend {argc} référence(s).
* \return			none
*
*/
void				list_foreach_ap(t_list const *this,
						t_fct_foreach_ap foreach,
						uint64_t const argc, ...)
{
  if (foreach)
    {
      void			**argv = NULL;
      t_item			*iterator = this->_begin;

      if (argc && (argv = malloc(sizeof(*argv) * argc)))
	{
	  va_list		ap;
	  uint64_t		i = 0;

	  va_start(ap, argc);
	  while (i < argc)
	    {
	      argv[i] = va_arg(ap, void *);
	      ++i;
	    }
	  va_end(ap);
	}
      while (iterator)
	{
	  foreach((void *)iterator->_data, argv);
	  iterator = iterator->_next;
	}
      if (argv)
	free(argv);
    }
}

/**
* \brief		        Applique une fonctionnalité sur l'ensemble des éléments de la liste.
* \details		        Parse l'intégralité des maillons de la liste en éxécutant le callback {foreach} pour chaques objets.
*				Vous posséder également la possibilité de contrôler la boucle en utilisant le retour de votre callback {foreach}.
*				Vous pouvez arrêté la boucle ou bien supprimer l'élément courant de la boucle.
*				L'élément supprimé fera appelle au callback {clear} pour détruire l'objet.
* \param this			Référence sur la liste.
* \param foreach		Callback appelé pour chaques maillons de la liste afin d'éxécuté
*				une fonctionnalité sur chaques objets de la liste.
* \param clear			Callback permettant un destruction de l'objet contenu dans chaques
*				maillons de la liste.
* \return			none
*
*/
void			list_foreach_ctrl(t_list *this,
					  t_fct_foreach_ctrl foreach,
					  t_fct_clear clear)
{
  if (foreach)
    {
      t_item		*iterator = this->_begin;
      t_ctrl_list	ctrl = LIST_CONTINU;

      while ((iterator) && (!(ctrl & LIST_STOP)))
	{
	  ctrl = foreach((void *)iterator->_data);
	  if (ctrl & LIST_DELETE)
	    {
	      t_item	*node = iterator;

	      iterator = iterator->_next;
	      list_erase(this, node, clear);
	    }
	  else
	    iterator = iterator->_next;
	}
    }
}

/**
* \brief		        Applique une fonctionnalité sur l'ensemble des éléments de la liste.
* \details		        Parse l'intégralité des maillons de la liste en éxécutant le callback {foreach} pour chaques objets
*				en ajoutant en second paramètre du callback, la référence {data} fourni en paramètre.
*				Vous posséder également la possibilité de contrôler la boucle en utilisant le retour de votre callback {foreach}.
*				Vous pouvez arrêté la boucle ou bien supprimer l'élément courant de la boucle.
*				L'élément supprimé fera appelle au callback {clear} pour détruire l'objet.
* \param this			Référence sur la liste.
* \param data			Référence vers un objet
* \param foreach		Callback appelé pour chaques maillons de la liste afin d'éxécuté
*				une fonctionnalité sur chaques objets de la liste.
* \param clear			Callback permettant un destruction de l'objet contenu dans chaques
*				maillons de la liste.
* \return			none
*
*/
void			list_foreach_ctrl_data(t_list *this, void *data,
					       t_fct_foreach_ctrl_data foreach,
					       t_fct_clear clear)
{
  if (foreach)
    {
      t_item		*iterator = this->_begin;
      t_ctrl_list	ctrl = LIST_CONTINU;

      while ((iterator) && (!(ctrl & LIST_STOP)))
	{
	  ctrl = foreach((void *)iterator->_data, data);
	  if (ctrl & LIST_DELETE)
	    {
	      t_item	*node = iterator;

	      iterator = iterator->_next;
	      list_erase(this, node, clear);
	    }
	  else
	    iterator = iterator->_next;
	}
    }
}

/**
* \brief		        Applique une fonctionnalité sur l'ensemble des éléments de la liste.
* \details		        Parse l'intégralité des maillons de la liste en éxécutant le callback {foreach} pour chaques objets
*				en ajoutant en second paramètre du callback, un tableau de taille {argc} dont chaques case correspond
*				à une référence vers un objets fourni en paramètre via les varargs.
*				Vous posséder également la possibilité de contrôler la boucle en utilisant le retour de votre callback {foreach}.
*				Vous pouvez arrêté la boucle ou bien supprimer l'élément courant de la boucle.
*				L'élément supprimé fera appelle au callback {clear} pour détruire l'objet.
* \param this			Référence sur la liste.
* \param foreach		Callback appelé pour chaques maillons de la liste afin d'éxécuté
*				une fonctionnalité sur chaques objets de la liste.
* \param clear			Callback permettant un destruction de l'objet contenu dans chaques
*				maillons de la liste.
* \param argc			Nombre de référence à récupérer via les varargs.
* \param ...		        Varargs: attend {argc} référence(s).
* \return			none
*
*/
void			list_foreach_ctrl_ap(t_list *this,
					     t_fct_foreach_ctrl_ap foreach,
					     t_fct_clear clear,
					     uint64_t const argc, ...)
{
  if (foreach)
    {
      void		**argv = NULL;
      t_item		*iterator = this->_begin;
      t_ctrl_list	ctrl = LIST_CONTINU;

      if (argc && (argv = malloc(sizeof(*argv) * argc)))
	{
	  va_list	ap;
	  uint64_t	i = 0;

	  va_start(ap, argc);
	  while (i < argc)
	    {
	      argv[i] = va_arg(ap, void *);
	      ++i;
	    }
	  va_end(ap);
	}
      while ((iterator) && (!(ctrl & LIST_STOP)))
	{
	  ctrl = foreach((void *)iterator->_data, argv);
	  if (ctrl & LIST_DELETE)
	    {
	      t_item	*node = iterator;

	      iterator = iterator->_next;
	      list_erase(this, node, clear);
	    }
	  else
	    iterator = iterator->_next;
	}
      if (argv)
	free(argv);
    }
}
