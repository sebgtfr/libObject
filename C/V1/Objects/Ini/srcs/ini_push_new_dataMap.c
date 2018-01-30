/**
* \file				ini_push_new_dataMap.c
* \author			Sébastien Le Maire
* \version			1.0
* \date			        14 Février 2017
*/

#include <string.h>
#include "ini.h"

static t_bool			ini_set_dataMap(t_iniDataMap *this,
						char const *key,
						char const *value)
{
  return (CAST_BOOL(((this->_key = strdup(key))) &&
		    ((this->_value = strdup(value)))));
}

t_bool				ini_push_new_dataMap(t_ini *this,
						     char const *sectionName,
						     char const *key,
						     char const *value)
{
  t_iniDataMap			dataMap = _INIT_INI_DATAMAP_;

  return (CAST_BOOL(ini_set_dataMap(&dataMap, key, value) &&
		    ini_push_dataMap(this, sectionName, &dataMap)));
}
