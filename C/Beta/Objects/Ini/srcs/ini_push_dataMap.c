/**
* \file				ini_push_dataMap.c
* \author			Sébastien Le Maire
* \version			1.0
* \date			        14 Février 2017
*/

#include "ini.h"

t_bool				ini_push_dataMap(t_ini *this,
						 char const *sectionName,
						 t_iniDataMap const *dataMap)
{
  t_iniSection			*section = ini_get_section(this, sectionName);
  t_iniDataMap			*data = ini_get_dataMap(section, dataMap->_key);

  if (data)
    {
      free(data->_key);
      if (data->_value)
	free(data->_value);
      *data = *dataMap;
      return (true);
    }
  return (INI_PUSH_DATAMAP_ON_SECTION(section, dataMap));
}
