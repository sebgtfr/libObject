/**
* \file			        string_reset.c
* \author			Sébastien Le Maire
* \version			1.0
* \date				22 Décembre 2016
*/

#include "mystring.h"

/**
* \brief		        Vide la chaine de caractère.
* \details		        Vide la chaine de caractère sans la détruire en mémoire. le premier caractère devient un '\0'.
* \param this			Référence sur l'objet de chaîne de caractère.
* \return			none
*
*/
void				string_reset(t_string *this)
{
  if (this->_data)
    {
      this->_data[0] = '\0';
      this->_length = 0;
    }
}
