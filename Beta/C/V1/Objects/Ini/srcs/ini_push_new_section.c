/**
* \file				ini_push_new_section.c
* \author			Sébastien Le Maire
* \version			1.0
* \date			        03 Février 2017
*/

#include <string.h>
#include "ini.h"

t_bool				ini_push_new_section(t_ini *this,
						     char const *sectionName)
{
  t_iniSection			section = _INIT_INI_SECTION_;

  if (!ini_get_section(this, sectionName))
    {
      if (sectionName)
	if (!(section._name = strdup(sectionName)))
	  return (false);
      return (vector_push_back(&this->_sections, &section));
    }
  return (false);
}
