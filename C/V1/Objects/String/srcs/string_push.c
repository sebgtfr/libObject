/**
* \file			        string_push.c
* \author			Sébastien Le Maire
* \version			1.0
* \date				22 Décembre 2016
*/

#include <stdlib.h>
#include <string.h>
#include "mystring.h"

/**
* \brief		        Concatène un caratère à un objet string.
* \details		        Concatène le caractère {c} à la fin
*				de la chaîne de caractère de l'objet string {this}.
* \param this			Référence sur l'objet de chaîne de caractère.
* \param c		        Caractère à ajouter.
* \return false			Echec de l'allocation mémoire.
* \return true			Création de la chaîne de caractère avec succès.
*
*/
t_bool				string_push_back(t_string *this, char const c)
{
  if (c)
    {
      uint64_t			capacity = (this->_capacity - this->_length);

      if (!capacity)
	if (!(string_add_page_memory(this, 1)))
	  return (false);
      this->_data[this->_length++] = c;
      this->_data[this->_length] = '\0';
    }
  return (true);
}
