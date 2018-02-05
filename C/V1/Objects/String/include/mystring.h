/**
* \file				mystring.h
* \author			Sébastien Le Maire
* \version			1.0
* \date				04 Décembre 2016
*/

#ifndef MYSTRING_H_
# define MYSTRING_H_

# include <string.h>
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

/* GLOBAL (define on ctor's file) */

# ifndef _NULLPTR_
#  define  _NULLPTR_
/**
* \brief		        Defini la constante NULL.
* \details		        Défini la constante NULL si elle n'a pas été défini.
*/
extern void const * const       g_nullptr;

# define __STRING_NULLPTR_DEFINE__

# endif /* !_NULLPTR_ */

/**
* \brief		        Defini la constante '\0'.
* \details		        Défini la constante '\0' représentant la fin d'une
*                       chaine de caractère.
*/
extern char const               g_nullchar;

/**
* \brief		        Initialise une chaîne de caractère.
* \details		        Initialise une chaîne de caractère vide.
* \return               Un objet #t_string.
*/
extern t_string const           g_defaultString;

# define _INIT_STRING_          (t_string){0, 0, (char *)0};

/* Methods */

/*
** String's functions
** Canonical form
** string_ctor_dtor.c
*/
extern t_bool			string_ctor(t_string *this, char const *data);
extern t_bool			string_copy(t_string *this,
                                    t_string const *cpy);
extern void				string_dtor(t_string *this);
extern t_bool			string_assign(t_string *this, char const *str,
                                      uint64_t const n);
extern t_bool			string_change(t_string *this, char const *str,
                                      uint64_t const n);
extern void				string_reset(t_string *this);

/*
** Add elements string's functions
** add_string.c
*/
extern t_bool			string_concat(t_string *str, char const *data,
                                      uint64_t const n);
extern t_bool			string_str_concat(t_string *this,
                                          t_string const *str,
                                          uint64_t const n);
extern t_bool			string_push_back(t_string *str, char const c);
extern t_bool			string_resize(t_string *str,
                                      uint64_t const capacity);

/*
** file descriptor
*/
extern t_bool			string_getline(t_string *str, int const fd);
extern t_bool			string_print(t_string *str, int const fd);

/*
** Others
*/
extern t_bool			string_delline(t_string *str, char const lim);
extern t_bool			string_trim(t_string *this);
extern void				string_shift(t_string *this, uint64_t const shift);

# ifdef VECTOR_H_

extern t_vector			*string_split(t_string *this,
                                      char const lim);

# endif /* !VECTOR_H_ */

/* INLINE */

/**
 * \brief		        Vérifie si la chaîne de caractère est vide.
 * \details		        Vérifie si la chaîne de caractère est vide ou si elle contient des caractères.
 * \param this			Objet #t_string à vérifier.
 * \return			true si la chaîne de caractère est vide.
 * \return			false si la chaîne de caractère n'est pas vide.
 */
static inline t_bool        string_empty(t_string const *this)
{
    return !this->_data;
};

/**
 * \brief		        Récupére un caractère de la string.
 * \details		        Récupère le caractère indexé en position {idx}.
 * \param this			Référence vers un objet #t_string.
 * \param idx			Index du caractère dans la chaîne de caractère.
 * \return		        Le caractère en position {idx}.
 */
static inline char              string_at(t_string const *this,
                                          uint64_t const idx)
{
    return this->_data[idx];
};

/**
* \brief		        Compare deux #t_string
* \details		        Compare deux #t_string.
* \param this			Référence vers un objet #t_string.
* \param s		        Référence vers un objet #t_string.
* \return		        0 si identique, sinon la différence (man strcmp)
*/
static inline int       string_compare(t_string const *this,
                                       t_string const *cmp)
{
    return strcmp(this->_data, cmp->_data);
};

/**
* \brief		        Compare deux #t_string
* \details		        Compare deux #t_string.
* \param t			Référence vers un objet #t_string.
* \param s		        Référence vers un objet #t_string.
* \param n		        Nombre de caractère à comparer.
* \return		        0 si identique, sinon la différence (man strncmp)
*/
static inline int       string_ncompare(t_string const *this,
                                        t_string const *cmp,
                                        size_t const n)
{
    return strncmp(this->_data, cmp->_data, n);
};

/**
* \brief		        Ajoute de la mémoire à la chaîne de caractère.
* \details		        Ajoute un bloc de {page_memory} octet en mémoire
*				à la capacité de la string {this}.
* \param this			Référence sur l'objet de chaîne de caractère.
* \param page_memory		Capacité en mémoire à ajouté à l'objet.
* \return false			Echec de l'allocation mémoire.
* \return true			Création de la chaîne de caractère avec succès.
*
*/
static inline t_bool    string_add_page_memory(t_string *this,
                                               uint64_t page_memory)
{
    return (string_resize(this, this->_capacity + page_memory));
}

#endif /* !MYSTRING_H_ */
