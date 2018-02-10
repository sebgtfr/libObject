/**
* \file				vector.h
* \author			Sébastien Le Maire
* \version			1.0
* \date				04 Décembre 2016
*/

#ifndef VECTOR_H_
# define VECTOR_H_

# include <stdlib.h>
# include "bool.h"
# include "container_type.h"

/**
* \brief		        Gestionnaire de tableau
* \details		        S'occupe de la gestion de tableau d'objet.
*/
typedef struct			s_vector
{
  uint64_t			_length; /*!< Nombre d'objets dans le tableau. */
  uint64_t			_capacity; /*!< Nombre d'objet pouvant être accueilli en mémoire. */
  uint64_t		        _size_item; /*!< Taille en mémoire d'un objet. */
  void				*_data; /*!< Référence vers le tableau d'objet. */
}				t_vector;

/**
* \brief		        Initialise un tableau.
* \details		        Initialise un tableau vide pouvant contenir des objets de taille {size_it}
* \param size_it		Taille en mémoire d'un objet contenu dans une case du tableau.
* \return			Un objet #t_vector.
*/
# define _VECTOR_CTOR_(size_it)	(t_vector){0, 0, size_it, NULL}

/**
* \brief		        Initialise un tableau.
* \details		        Initialise un tableau vide pouvant contenir des objets de type (item)
* \param item			Nom de l'objet pouvant être contenu dans une case du tableau.
* \return			Un objet #t_vector.
*/
# define _VECTOR_INIT_(item)	_VECTOR_CTOR_(sizeof(item))

/**
* \brief		        Vérifie si le tableau est vide.
* \details		        Vérifie si le tableau est vide ou si il contient des cases remplis.
* \param vector			Objet #t_vector à vérifier.
* \return			true si le tableau est vide.
* \return			false si le tableau n'est pas vide.
*/
# define VECTOR_EMPTY(vector)	(!(vector)->_length)

/**
* \brief		        Calcule l'index du tableau.
* \details		        Calcule la position en mémoire de la case du tableau indexé en position {idx}.
* \param vec			Objet #t_vector.
* \param idx			Index de la case du tableau à chercher.
* \return		        Le véritable index en memoire de la case du tableau.
*/
# define VECTOR_INDEX(vec, idx)	((idx) * (vec)->_size_item)

/**
* \brief		        Récupére un élément du tableau.
* \details		        Calcule la position en mémoire de la case du tableau indexé en position {idx}
*				et retourne l'addresse de la case mémoire.
* \param vec			Objet #t_vector.
* \param idx			Index de la case du tableau à chercher.
* \return		        L'addresse de la case mémoire à l'index {idx}.
*/
# define VECTOR_AT(vec, idx)	((vec)->_data + VECTOR_INDEX(vec, idx))

/**
* \brief		        Ajoute b cases mémoires au tableau
* \details		        Redimmensionne le tableau {v} en lui ajoutant {b} cases mémoires.
* \param v			Référence vers un objet #t_vector.
* \param b		        Nombre de case mémoire à ajouté.
* \return		        true en cas de succès.
* \return			false en cas d'échec (allocation mémoire).
*/
# define VECTOR_ADD_BLOCK(v, b)	vector_resize((v), (v)->_capacity + b, NULL)

/**
* \brief		        Récupére le dernier élément du tableau.
* \details		        Calcule la position en mémoire de la case du tableau indexé en position {idx}
*				et retourne l'addresse de la case mémoire.
* \param vec			Objet #t_vector.
* \return		        L'addresse de la case mémoire à du dernier élément du tableau.
*/
# define VECTOR_LAST(vec)	(VECTOR_AT(vec, (vec)->_length - 1))

/*
** Vector's functions
** canonical form
*/
t_bool				vector_ctor(t_vector *this,
					    uint64_t const size_item,
					    uint64_t const capacity);
t_bool				vector_copy(t_vector *this,
					    t_vector const *cpy);
void				vector_dtor(t_vector *this,
					    t_fct_clear clear);

/*
** Add elements vector's functions
*/
t_bool				vector_push_back(t_vector *this,
						 void const *content);
t_bool				vector_resize(t_vector *this,
					      uint64_t const size,
					      t_fct_clear clear);
t_bool				vector_push(t_vector *this,
					    t_vector const *vector);

/*
** Delete vector's functions
*/
void				vector_pop_back(t_vector *this,
						t_fct_clear clear);
void				vector_clear(t_vector *this,
					     t_fct_clear clear);

/*
** Get information to vector.
*/
void				vector_foreach(t_vector const *this,
					       t_fct_foreach foreach);
void				vector_foreach_data(t_vector const *this,
						    t_fct_foreach_data foreach,
						    void *data);
void				vector_foreach_ap(t_vector const *this,
						  t_fct_foreach_ap foreach,
						  uint64_t const argc, ...);
void				*vector_compare(t_vector const *this,
						t_fct_compare compare,
						void const *data);

#endif /* !VECTOR_H_ */
