/**
* \file			        string_ctor.c
* \author			Sébastien Le Maire
* \version			1.0
* \date				22 Décembre 2016
*/

#include <string.h>
#include "mystring.h"

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
    *this = _INIT_STRING_;
  return (true);
}
