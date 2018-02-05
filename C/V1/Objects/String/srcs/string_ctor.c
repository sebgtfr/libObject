/**
* \file			        string_ctor.c
* \author			Sébastien Le Maire
* \version			1.0
* \date				22 Décembre 2016
*/

#include <string.h>
#include "mystring.h"

/*
** Definition of global.
*/

#ifdef __STRING_NULLPTR_DEFINE__

void const * const      g_nullptr = (void *)0;

#endif /* !__STRING_NULLPTR_DEFINE__ */

char const              g_nullchar = '\0';

t_string const          g_defaultString = _INIT_STRING_;

/**
* \brief			Construteur de l'objet t_string
* \details			Initialise un objet t_string ({this}) pouvant contenir
*			        la chaîne de caractère {data}.
* \param this			Référence sur l'objet de chaîne de caractère.
* \param data			Référence vers une chaîne de caractère.
* \return false			Echec de l'allocation mémoire.
* \return true			Création de la chaîne de caractère avec succès.
*
*/
t_bool				string_ctor(t_string *this, char const *data)
{
    if (data)
        {
            if (!(this->_data = strdup(data)))
                {
                    this->_length = 0;
                    this->_capacity = 0;
                    return (false);
                }
            this->_capacity = strlen(this->_data);
            this->_length = this->_capacity;
        }
    else
        *this = g_defaultString;
    return (true);
}
