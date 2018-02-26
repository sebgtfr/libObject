/**
* \file			        string_print.c
* \author			Sébastien Le Maire
* \version			1.0
* \date				22 Décembre 2016
*/

#include <unistd.h>
#include "mystring.h"

/**
* \brief		        Ecrit la chaîne de caratère.
* \details		        Ecrit la chaîne de caratère contenu dans l'objet
*				l'objet string {this} dans le file descriptor {fd}.
* \param this			Référence sur l'objet de chaîne de caractère.
* \param fd			File descriptor du flux auquel on ecrit les données.
* \return false			Echec de l'écriture dans le flux.
* \return true		        Ecriture dans le flux avec succès.
*
*/
t_bool				string_print(t_string *this, int const fd)
{
    if (this->_data)
        return (!(write(fd, this->_data, this->_length) < 0));
    return (true);
}
