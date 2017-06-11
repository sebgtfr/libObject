/**
* \file				mystring.h
* \author			Sébastien Le Maire
* \version			1.0
* \date				04 Décembre 2016
*/

#ifndef BUFFER_H_
# define BUFFER_H_

# include "bool.h"

/**
* \brief		        Gestionnaire d'un buffer.
* \details		        S'occupe de la gestion de buffer.
*/
typedef struct			s_buffer
{
  uint64_t			_length;
  uint64_t			_capacity;
  void				*_data;
}				t_buffer;

# ifndef NULL
/**
* \brief		        Defini la constante NULL.
* \details		        Défini la constante NULL si elle n'a pas été défini.
*/
#  define NULL			(void *)0
# endif /* !NULL */

/**
* \brief		        Initialise un buffer.
* \details		        Initialise un buffer vide
* \return			Un objet #t_buffer.
*/
# define _INIT_BUFFER_		(t_buffer){ 0, 0, NULL }

/**
* \brief		        Vérifie si le buffer est vide.
* \details		        Vérifie si le buffer est vide ou si elle contient des caractères.
* \param this			Objet #t_buffer à vérifier.
* \return			true si le buffer est vide.
* \return			false si le buffer n'est pas vide.
*/
# define BUFFER_EMPTY(this)	(!(this)->_length)

/**
* \brief		        Récupére un emplacement mémoire du buffer.
* \details		        Récupère l'adresse en position {idx}.
* \param this			Référence vers un objet #t_buffer.
* \param idx			Index de l'adresse cible dans le buffer.
* \return		        L'adresse mémoire en position {idx}.
*/
# define BUFFER_AT(this, idx)   ((this)->_data + idx)

# ifndef _BUFFER_BUFFER_SIZE_

/**
* \brief		        Taille lecture/écriture d'un flux
* \details		        Macro Déterminant la taille de lecture/ecriture d'un flux.
*				L'utilisateur peut déterminer cette en définisant cette macro
*				avant d'inclure le fichier header buffer.h.
* \return		        Taille de lecture/ecriture d'un flux.
*/
#  define _BUFFER_BUFFER_SIZE_	(1024)

# endif /*!_BUFFER_BUFFER_SIZE_ */

# define buffer_add_page_memory(t, c)	buffer_resize(t, (t)->_capacity + c)
# define buffer_reset(this)		(this)->_length = 0

/*
** Buffer's functions
*/
t_bool				buffer_ctor(t_buffer *this,
					    uint64_t const capacity);
void				buffer_dtor(t_buffer *this);
t_bool				buffer_copy(t_buffer *this,
					    t_buffer const *copy);
t_bool				buffer_assign(t_buffer *this, void const *data,
					      uint64_t const size);

/*
** Methods
*/
t_bool				buffer_change(t_buffer *this, void const *data,
					      uint64_t const size);
t_bool				buffer_concat(t_buffer *this, void const *data,
					      uint64_t const size);
t_bool				buffer_resize(t_buffer *this,
					      uint64_t const capacity);
void				buffer_shift(t_buffer *this, uint64_t const shift);
t_bool				buffer_print(t_buffer *this, int const fd);

#endif /* !BUFFER_H_ */
