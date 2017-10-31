/**
* \file				list.h
* \author			Sébastien Le Maire
* \version			1.0
* \date				04 Décembre 2016
*/

#ifndef LIST_H_
# define LIST_H_

# include <stdlib.h>
# include "bool.h"

/**
* \brief		        Maillon d'un objet #t_list
* \details		        Maillon de la liste chaînée contenu dans l'objet #t_list.
*/
struct				s_item
{
  struct s_item			*_prev; /*!< Référence vers le maillon précedent de la liste. */
  struct s_item			*_next; /*!< Référence vers le maillon suivant de la liste. */
  char			        _data[0]; /*!< Position du premier octet de l'objet contenu dans le maillon. */
}				__attribute__((packed));

typedef struct s_item  		t_item;

/**
* \brief		        Gestionnaire de liste chaînée.
* \details		        S'occupe de la gestion d'une liste chaînée.
*/
typedef struct			s_list
{
  t_item			*_begin; /*!< Référence vers le premier maillon de la liste. */
  t_item			*_end; /*!< Référence vers le dernier maillon de la liste. */
  uint64_t			_length; /*!< Nombre de maillon(s) contenu dans la liste. */
  uint64_t			_size_item; /*!< Taille de l'objet contenu dans les maillons de la liste. */
}				t_list;

/**
* \brief		        Initialise une liste.
* \details		        Initialise une liste vide pouvant contenir des objets de taille {size_item}
* \param size_item		Taille en mémoire d'un objet contenu dans un maillon de la liste.
* \return			Un objet #t_list.
*/
# define _LIST_CTOR_(size_item)	(t_list){NULL, NULL, 0, size_item}

/**
* \brief		        Initialise une liste.
* \details		        Initialise une liste vide pouvant contenir des objets de type (item)
* \param item			Nom de l'objet pouvant être contenu dans un maillon de la liste.
* \return			Un objet #t_list.
*/
# define _LIST_INIT_(item)	_LIST_CTOR_(sizeof(item))

/**
* \brief		        Contrôler de la boucle.
* \datails		        Contrôle les actions de la boucle des fonctions foreach_ctrl.
*/
typedef enum			e_ctrl_list
  {
				LIST_CONTINU = 1, /*!< Continue la boucle normalement. */
				LIST_DELETE = 2, /*!< Supprime le maillon courrant de la liste */
				LIST_STOP = 4, /*!< Arrête la boucle. */
  }				t_ctrl_list;

/*
** list ptr
*/
/**
* \brief		        Callback sur un évènement.
* \details		        Callback sur un évènement foreach avec controller. Il s'agit du parsing d'un conteneur.
*				Le prototype du callback est :  t_ctrl_list foreach(void *content);
* \param content       	        Référence vers l'objet courrant du parsing.
* \return			#t_ctrl_list pour contrôler l'avancement du parsing de la liste.
*/
typedef t_ctrl_list     (*t_fct_foreach_ctrl)(void *content);

/**
* \brief		        Callback sur un évènement.
* \details		        Callback sur un évènement foreach avec donnée unique et controller. Il s'agit du parsing d'un conteneur.
*				Le prototype du callback est :  t_ctrl_list foreach(void *content, void *data);
* \param content       	        Référence vers l'objet courrant du parsing.
* \param data			Référence vers un objet quelconque.
* \return			#t_ctrl_list pour contrôler l'avancement du parsing de la liste.
*/
typedef t_ctrl_list     (*t_fct_foreach_ctrl_data)(void *content, void *data);

/**
* \brief		        Callback sur un évènement.
* \details		        Callback sur un évènement foreach avec données variatiques et controller. Il s'agit du parsing d'un conteneur.
*				Le prototype du callback est :  t_ctrl_list foreach(void *content, void **datas);
* \param content       	        Référence vers l'objet courrant du parsing.
* \param datas			Tableau de références vers des objets quelconques.
* \return			#t_ctrl_list pour contrôler l'avancement du parsing de la liste.
*/
typedef t_ctrl_list     (*t_fct_foreach_ctrl_ap)(void *content, void **datas);

# include "container_type.h"

/**
* \brief		        Vérifie si la liste est vide.
* \details		        Vérifie si la liste est vide ou si elle contient des maillons.
* \param list			Objet #t_list à vérifier.
* \return			true si la liste est vide.
* \return			false si la liste n'est pas vide.
*/
# define LIST_EMPTY(list)	(!list->_length)

/**
* \brief		        Récupère le maillon d'une liste.
* \details		        Récupère le maillon d'une liste à partir de l'objet quel contient.
*				Cette macro ne vérifie pas l'appartenant de l'objet à un maillon.
* \param d		        Donnée issus d'un maillon d'une liste.
* \return			true si la liste est vide.
*/
# define LIST_DATA_TO_ITEM(d)	((t_item *)((void *)(d) - sizeof(t_item *) * 2))

/*
** List's functions
** canonical form
*/
void				list_ctor(t_list *this,
					  uint64_t const size_item);
t_bool				list_copy(t_list *this, t_list const *cpy);
void				list_dtor(t_list *list, t_fct_clear clear);
t_bool				list_push(t_list *this, t_list const *list);

/*
** Insert's functions :
*/
t_bool				list_push_back(t_list *list,
					       void const *content);
t_bool				list_push_front(t_list *list,
						void const *content);
t_bool				list_insert(t_list *this,
					    void const *content,
					    uint64_t const offset);

/*
** Get information to list.
*/
void				*list_item(t_list *this, uint64_t const offset);
void				list_foreach(t_list const *list,
					     t_fct_foreach foreach);
void				list_foreach_data(t_list const *list,
						  t_fct_foreach_data foreach,
						  void *data);
void                            list_foreach_ap(t_list const *this,
						t_fct_foreach_ap foreach,
						uint64_t const argc, ...);
void				list_foreach_ctrl(t_list *list,
						  t_fct_foreach_ctrl foreach,
						  t_fct_clear clear);
void				list_foreach_ctrl_data(t_list *, void *,
						       t_fct_foreach_ctrl_data,
						       t_fct_clear);
void                            list_foreach_ctrl_ap(t_list *this,
						     t_fct_foreach_ctrl_ap foreach,
						     t_fct_clear clear,
						     uint64_t const argc, ...);
void				*list_compare(t_list const *list,
					      t_fct_compare cmp,
					      void const *data);

/*
** Delete list's functions.
*/
void				list_pop_front(t_list *list,
					       t_fct_clear clear);
void				list_pop_back(t_list *list,
					      t_fct_clear clear);
void				list_clear(t_list *list,
					   t_fct_clear clear);
void				list_erase(t_list *list, t_item *item,
					   t_fct_clear clear);

# ifdef VECTOR_H_

t_vector			*list_to_vector(t_list *this);

# endif /* !VECTOR_H_ */

#endif /* !LIST_H_ */
