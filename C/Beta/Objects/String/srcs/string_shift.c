/**
* \file			        string_shift.c
* \author			Sébastien Le Maire
* \version			1.0
* \date				03 Mars 2017
*/

#include <string.h>
#include "mystring.h"

/**
* \brief		        Décale le debut de la chaîne de caractère.
* \details		        Décale la position du début de la chaîne de caractère
*				contenu dans {this} de {shift} caractères.
* \param this			Référence sur l'objet de chaîne de caractère.
* \param shift		        Position du nouveau debut de la chaîne de caratère.
*
*/
void				string_shift(t_string *this, uint64_t const shift)
{
  if (shift && this->_data)
    {
      if (shift < this->_length)
	{
	  (void)memmove(this->_data, (void *)this->_data + shift,
			this->_length - shift);
	  this->_length -= shift;
	  this->_data[this->_length] = '\0';
	}
      else
	string_reset(this);
    }
}
