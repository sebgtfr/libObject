/**
* \file				bool.h
* \author			Sébastien Le Maire
* \version			1.0
* \date				04 Décembre 2016
*/

#ifndef BOOL_H_
# define BOOL_H_

# include <stdint.h>

typedef uint8_t                 t_bool;

/**
* \brief		        Convertie une variable ou une expression en booleén.
* \details		        Utilise l'opérateur binaire not (!) pour convertir une variable
*				ou une expression en un booléen.
* \return			0 pour false.
* \return			1 pour true.
*/
# define CAST_BOOL(var)         (!(!(var)))

# ifndef FALSE
/**
* \brief		        Défini la contante false
* \details		        Défini la constante false avec la valeur 0
*				dans le cas où elle n'est pas défini.
*/
#  define FALSE                 0

extern t_bool const             false;

# endif /* !false */

# ifndef TRUE
/**
* \brief		        Défini la contante true
* \details		        Défini la constante true avec comme valeur tout sauf 0
*				dans le cas où elle n'est pas défini.
*/
#  define TRUE                  !FALSE

extern t_bool const             true;

# endif /* !true */

#endif /* !BOOL_H_ */
