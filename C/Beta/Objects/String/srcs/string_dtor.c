/**
* \file			        string_dtor.c
* \author			Sébastien Le Maire
* \version			1.0
* \date				22 Décembre 2016
*/

#include <stdlib.h>
#include "mystring.h"

/**
* \brief		        Destruteur de l'objet t_string.
* \details			Détruit l'objet t_string ({this})
* \param this			Référence sur l'objet de chaîne de caractère.
* \return			none
*
*/
void				string_dtor(t_string *this)
{
  if (this->_data)
    free(this->_data);
  *this = _INIT_STRING_;
}
