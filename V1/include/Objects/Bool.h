/**
* \file				Bool.h
* \author			Sébastien Le Maire
* \version			1.0
* \date				23 Février 2018
*/

#ifndef OBJECTS_BOOL_H_
# define OBJECTS_BOOL_H_

# include <stdint.h>

# ifndef __cplusplus

typedef uint8_t					bool;

#  define false					0
#  define true					!false


#  define CAST_BOOL(var)   		((bool)(!!(var)))

# else

extern "C" {

# endif /* !CPLUSPLUS */

	extern bool const			g_false;
	extern bool const			g_true;

# ifdef __cplusplus
}
# endif /* !CPLUSPLUS */

# define FALSE					g_false
# define TRUE					g_true

#endif /* !OBJECTS_BOOL_H_ */
