/**
* \file			        string_change.c
* \author			Sébastien Le Maire
* \version			1.0
* \date				22 Décembre 2016
*/

#include <stdlib.h>
#include <string.h>
#include "mystring.h"

/**
* \brief		        Assigne une chaîne de caractère.
* \details		        Assigne la chaîne de caratère {str} à l'objet {this}
* \param this			Référence sur l'objet de chaîne de caractère.
* \param str			Référence vers une chaîne de caractère.
* \return false			Echec de l'allocation mémoire.
* \return true			Création de la chaîne de caractère avec succès.
*
*/
t_bool				string_change(t_string *this, char const *data,
                                  uint64_t const n)
{
    if (data)
        {
            uint64_t			dataLength = strlen(data);
            uint64_t			size = (((!n) || (n > dataLength)) ?
                                        dataLength : n);
            uint64_t			capacity = this->_capacity;

            if ((capacity = (capacity < size) ? (size - capacity) : 0))
                if (!(string_add_page_memory(this, capacity)))
                    return (false);
            (void)strncpy(this->_data, data, size);
            this->_length = size;
            this->_data[this->_length] = g_nullchar;
        }
    return (true);
}
