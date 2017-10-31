/**
* \file			        string_add_page_memory.c
* \author			Sébastien Le Maire
* \version			1.0
* \date				22 Décembre 2016
*/

#include <stdlib.h>
#include <string.h>
#include "mystring.h"

/**
* \brief		        Ajoute de la mémoire à la chaîne de caractère.
* \details		        Ajoute un bloc de {page_memory} octet en mémoire
*				à la capacité de la string {this}.
* \param this			Référence sur l'objet de chaîne de caractère.
* \param page_memory		Capacité en mémoire à ajouté à l'objet.
* \return false			Echec de l'allocation mémoire.
* \return true			Création de la chaîne de caractère avec succès.
*
*/
t_bool				string_add_page_memory(t_string *this,
						       uint64_t const page_memory)
{
  return (string_resize(this, this->_capacity + page_memory));
}
