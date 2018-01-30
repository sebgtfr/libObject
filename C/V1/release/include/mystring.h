/**
* \file				mystring.h
* \author			Sébastien Le Maire
* \version			1.0
* \date				04 Décembre 2016
*/

#ifndef MYSTRING_H_
# define MYSTRING_H_

# include "bool.h"

/**
* \brief		        Gestionnaire de chaîne de caractère.
* \details		        S'occupe de la gestion de chaîne de caractère.
*/
typedef struct			s_string
{
  uint64_t		        _length; /*!< Longueur de la chaîne de caractère. */
  uint64_t			_capacity; /*!< Capacité total en mémoire alloué de la chaîne de caractère. */
  char				*_data; /*!< Référence vers la chaîne de caractère. */
}				t_string;

# ifndef NULL
/**
* \brief		        Defini la constante NULL.
* \details		        Défini la constante NULL si elle n'a pas été défini.
*/
#  define NULL			(void *)0
# endif /* !NULL */

/**
* \brief		        Initialise une chaîne de caractère.
* \details		        Initialise une chaîne de caractère vide.
* \return			Un objet #t_string.
*/
# define _INIT_STRING_		(t_string){ 0, 0, NULL }

/**
* \brief		        Vérifie si la chaîne de caractère est vide.
* \details		        Vérifie si la chaîne de caractère est vide ou si elle contient des caractères.
* \param this			Objet #t_string à vérifier.
* \return			true si la chaîne de caractère est vide.
* \return			false si la chaîne de caractère n'est pas vide.
*/
# define STRING_EMPTY(this)	(!(this)->_length)

/**
* \brief		        Récupére un caractère de la string.
* \details		        Récupère le caractère indexé en position {idx}.
* \param this			Référence vers un objet #t_string.
* \param idx			Index du caractère dans la chaîne de caractère.
* \return		        Le caractère en position {idx}.
*/
# define STRING_AT(this, idx)	((this)->_data[idx])

/**
* \brief		        Compare deux #t_string
* \details		        Compare deux #t_string.
* \param this			Référence vers un objet #t_string.
* \param s		        Référence vers un objet #t_string.
* \return		        0 si identique, sinon la différence (man strcmp)
*/
# define STRING_COMPARE(this,s)	(strcmp((this)->_data, (s)->_data))

/**
* \brief		        Compare deux #t_string
* \details		        Compare deux #t_string.
* \param t			Référence vers un objet #t_string.
* \param s		        Référence vers un objet #t_string.
* \param n		        Nombre de caractère à comparer.
* \return		        0 si identique, sinon la différence (man strncmp)
*/
# define STRING_NCOMPARE(t,s,n)	(strncmp((t)->_data, (s)->_data, n))

# ifndef _STRING_BUFFER_SIZE_

/**
* \brief		        Taille lecture/écriture d'un flux
* \details		        Macro Déterminant la taille de lecture/ecriture d'un flux.
*				L'utilisateur peut déterminer cette en définisant cette macro
*				avant d'inclure le fichier header mystring.h.
* \return		        Taille de lecture/ecriture d'un flux.
*/
#  define _STRING_BUFFER_SIZE_	(1024)

# endif /*!_STRING_BUFFER_SIZE_ */

/*
** String's functions
** Canonical form
** string_ctor_dtor.c
*/
t_bool				string_ctor(t_string *this, char const *data);
t_bool				string_copy(t_string *this,
					    t_string const *cpy);
void				string_dtor(t_string *this);
t_bool				string_assign(t_string *this, char const *str,
					      uint64_t const n);
t_bool				string_change(t_string *this, char const *str,
					      uint64_t const n);
void				string_reset(t_string *this);

/*
** Add elements string's functions
** add_string.c
*/
t_bool				string_concat(t_string *str, char const *data,
					      uint64_t const n);
t_bool				string_str_concat(t_string *this,
						  t_string const *str,
						  uint64_t const n);
t_bool				string_push_back(t_string *str, char const c);
t_bool				string_resize(t_string *str,
					      uint64_t const capacity);
t_bool				string_add_page_memory(t_string *this,
						       uint64_t page_memory);

/*
** file descriptor
*/
t_bool				string_getline(t_string *str, int const fd);
t_bool				string_print(t_string *str, int const fd);

/*
** Others
*/
t_bool				string_delline(t_string *str, char const lim);
t_bool				string_trim(t_string *this);
void				string_shift(t_string *this, uint64_t const shift);

# ifdef VECTOR_H_

t_vector			*string_split(t_string *this,
					      char const lim);

# endif /* !VECTOR_H_ */

#endif /* !MYSTRING_H_ */
