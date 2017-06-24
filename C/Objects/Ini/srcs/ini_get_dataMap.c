/**
* \file				ini_get_dataMap.c
* \author			Sébastien Le Maire
* \version			1.0
* \date			        03 Février 2017
*/

#include <string.h>
#include "ini.h"

t_bool				ini_cmp_search_dataMap(void *content,
						       void const *data)
{
  char const			*dataArray = *(char const **)content;
  char const			*dataString = (char const *)data;

  return (((!dataString) || (!dataArray)) ? (CAST_BOOL(dataString == dataArray)) :
	  (CAST_BOOL(strcmp(dataString, dataArray))));

}

t_iniDataMap			*ini_get_dataMap(t_iniSection *this,
						 char const *key)
{
  return ((t_iniDataMap *)vector_compare(&this->_values, ini_cmp_search_dataMap,
					 key));
}
