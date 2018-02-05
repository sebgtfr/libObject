/**
* \file			        string_resize.c
* \author			Sébastien Le Maire
* \version			1.0
* \date				22 Décembre 2016
*/

#include <stdlib.h>
#include <string.h>
#include "mystring.h"

/**
* \brief		        Redimensionne la chaîne de caractère en mémoire.
* \details		        Redimensionne la chaîne de caractère {this} en mémoire
*				de la taille capacity. Cela ne détruit pas la sauf si
*				la capacité diminue.
* \param this			Référence sur l'objet de chaîne de caractère.
* \param capacity		Capacité en mémoire à attribué à l'objet.
* \return false			Echec de l'allocation mémoire.
* \return true			Création de la chaîne de caractère avec succès.
*
*/
t_bool				string_resize(t_string *this,
                                  uint64_t const capacity)
{
    if (!capacity)
        string_dtor(this);
    else if (this->_capacity != capacity)
        {
            if (!(this->_data = realloc(this->_data, sizeof(char) *
                                        (capacity + 1))))
                {
                    this->_capacity = 0;
                    this->_length = 0;
                    return (false);
                }
            this->_capacity = capacity;
            if (this->_length > this->_capacity)
                this->_length = this->_capacity;
            this->_data[this->_length] = g_nullchar;
        }
    return (true);
}
