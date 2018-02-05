/**
* \file			        string_concat.c
* \author			Sébastien Le Maire
* \version			1.0
* \date				22 Décembre 2016
*/

#include <stdlib.h>
#include <string.h>
#include "mystring.h"

/**
* \brief		        Concatène une chaîne de caratère à un objet string.
* \details		        Concatène la chaîne de caratère {data} à la fin
*				de la chaîne de caractère de l'objet string {this}.
* \param this			Référence sur l'objet de chaîne de caractère.
* \param data			Référence vers une chaîne de caractère.
* \return false			Echec de l'allocation mémoire.
* \return true			Création de la chaîne de caractère avec succès.
*
*/
t_bool				string_concat(t_string *this, char const *data,
                                  uint64_t const n)
{
    if (data)
        {
            uint64_t			dataLength = strlen(data);
            uint64_t			nsize = (((!n) || (n > dataLength)) ?
                                         dataLength : n);
            uint64_t			size = this->_length + nsize;
            uint64_t			capacity = this->_capacity - this->_length;

            if ((capacity = (capacity < size) ? (size - capacity) : 0))
                if (!(string_add_page_memory(this, capacity)))
                    return (false);
            (void)strncpy(this->_data + this->_length, data, nsize);
            this->_length = size;
            this->_data[this->_length] = g_nullchar;
        }
    return (true);
}

/**
* \brief		        Concatène un objet string  à un autre objet string.
* \details		        Concatène la chaîne de caratère de l'objet {str}
*				à la fin de la chaîne de caractère de
*				l'objet string {this}.
* \param this			Référence sur l'objet de chaîne de caractère.
* \param data			Référence vers un objet de chaîne de caractère.
* \return false			Echec de l'allocation mémoire.
* \return true			Création de la chaîne de caractère avec succès.
*
*/
t_bool				string_str_concat(t_string *this,
                                      t_string const *str,
                                      uint64_t const n)
{
    if (str && str->_data)
        {
            uint64_t			nsize = (((!n) || (n > str->_length)) ?
                                         str->_length : n);
            uint64_t			size = this->_length + nsize;
            uint64_t			capacity;

            if ((capacity = (size <= this->_capacity) ? 0 :
                 (size - this->_capacity)))
                if (!(string_add_page_memory(this, capacity)))
                    return (false);
            (void)strncpy(this->_data + this->_length, str->_data, nsize);
            this->_length = size;
            this->_data[this->_length] = g_nullchar;
        }
    return (true);
}
