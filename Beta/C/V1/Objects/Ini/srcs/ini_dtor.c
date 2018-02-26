/**
* \file				ini_ctor.c
* \author			Sébastien Le Maire
* \version			1.0
* \date				24 Janvier 2017
*/

#include <stdlib.h>
#include "ini.h"

static void			dtor_each_dataMap(void *data)
{
  free(((t_iniDataMap *)data)->_key);
  if (((t_iniDataMap *)data)->_value)
    free(((t_iniDataMap *)data)->_value);
}

static void			dtor_each_sections(void *data)
{
  if ((*(char **)data))
    free(*(char **)data);
  vector_dtor(&((t_iniSection *)data)->_values, dtor_each_dataMap);
}

/**
* \brief			Construteur de l'objet t_ini
* \details			Initialise un objet t_ini ({this})
* \param this			Référence sur l'objet ini
* \return			none
*/
void				ini_dtor(t_ini *this)
{
  this->_name = NULL;
  vector_dtor(&this->_sections, dtor_each_sections);
}
