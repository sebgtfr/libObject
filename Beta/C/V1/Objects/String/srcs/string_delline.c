/**
* \file			        string_delline.c
* \author			Sébastien Le Maire
* \version			1.0
* \date				22 Décembre 2016
*/

#include <stdlib.h>
#include <string.h>
#include "mystring.h"

/**
* \brief		        Détruit la chaîne de caractère jusqu'à un caractère.
* \details		        Détruit la chaîne de caractère de l'objet {this}
*				jusqu'au caractère {lim}.
* \param this			Référence sur l'objet de chaîne de caractère.
* \param lim			Caractère limitant la ligne.
* \return false			Echec de l'allocation mémoire.
* \return true			Création de la chaîne de caractère avec succès.
*
*/
t_bool				string_delline(t_string *this, char const lim)
{
    if (this->_data)
        {
            uint64_t			i = 0;

            while ((i < this->_length) && (this->_data[i]) && (this->_data[i] != lim))
                ++i;
            if (this->_data[i] == lim)
                {
                    char			*tmp = NULL;

                    if (this->_data[i] && this->_data[i + 1])
                        if (!(tmp = strdup(this->_data + (i + 1))))
                            return (false);
                    free(this->_data);
                    this->_data = tmp;
                    this->_length -= (this->_length <= (i + 1)) ? this->_length : (i + 1);
                    this->_capacity = this->_length;
                }
        }
    return (true);
}
