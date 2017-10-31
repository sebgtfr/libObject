/**
* \file				ini_ctor.c
* \author			Sébastien Le Maire
* \version			1.0
* \date				24 Janvier 2017
*/

#include <stdlib.h>
#include "ini.h"

/**
* \brief			Construteur de l'objet t_ini
* \details			Initialise un objet t_ini ({this})
* \param this			Référence sur l'objet ini
* \param filename	        Nom du fichier Ini.
* \return			none
*/
void				ini_ctor(t_ini *this, char const *filename)
{
  *this = _INIT_INI_(filename);
}
