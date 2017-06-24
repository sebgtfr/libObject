/**
* \file				ini_get_section.c
* \author			Sébastien Le Maire
* \version			1.0
* \date			        03 Février 2017
*/

#include <string.h>
#include "ini.h"

t_bool				ini_cmp_search_section(void *content,
						       void const *data)
{
  char const			*dataArray = *(char const **)content;
  char const			*dataString = (char const *)data;

  return (((!dataString) || (!dataArray)) ? (CAST_BOOL(dataString == dataArray)) :
	  (CAST_BOOL(strcmp(dataString, dataArray))));

}

t_iniSection			*ini_get_section(t_ini *this,
						 char const *sectionName)
{
  return ((t_iniSection *)vector_compare(&this->_sections, ini_cmp_search_section,
					 sectionName));
}
