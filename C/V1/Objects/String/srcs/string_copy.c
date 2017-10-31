/**
* \file			        string_copy.c
* \author			Sébastien Le Maire
* \version			1.0
* \date				22 Décembre 2016
*/

#include <stdlib.h>
#include <string.h>
#include "mystring.h"

/**
* \brief			Construteur par copie de l'objet t_string
* \details			Initialise un objet t_string ({this}) pouvant contenir
*			        la chaîne de caractère de l'objet {cpy}.
* \param this			Référence sur l'objet de chaîne de caractère.
* \param cpy			Référence vers un objet string de chaîne de caractère.
* \return false			Echec de l'allocation mémoire.
* \return true			Création de la chaîne de caractère avec succès.
*
*/
t_bool				string_copy(t_string *this, t_string const *cpy)
{
  if (this != cpy)
    {
      if (cpy && cpy->_data)
	{
	  if (!(this->_data = realloc(this->_data, sizeof(char) * cpy->_capacity)))
	    {
	      this->_capacity = 0;
	      this->_length = 0;
	      return (false);
	    }
	  this->_length = cpy->_length;
	  this->_capacity = cpy->_capacity;
	  (void)strcpy(this->_data, cpy->_data);
	}
      else
	*this = _INIT_STRING_;
    }
  return (true);
}
