/**
* \file				ini_parse.h
* \author			Sébastien Le Maire
* \version			1.0
* \date				02 Février 2017
*/

#ifndef INI_PARSE_H_
# define INI_PARSE_H_

# include "ini.h"

typedef enum			e_ini_parse_state
  {
				INI_PARSE_VOID = -2,
				INI_PARSE_COMMENT = -1,
				INI_PARSE_SECTION = 0,
				INI_PARSE_KEY,
				INI_PARSE_VALUE,
				INI_PARSE_END,
				INI_PARSE_ERROR
  }				t_ini_parse_state;

typedef struct			s_ini_parse
{
  t_ini_parse_state		_state;
  t_iniSection			*_currentSection;
  t_iniDataMap			_dataMap;
  t_bool			_quote;
  t_string			_save;
}				t_ini_parse;

typedef unsigned int		(*t_ini_parse_state_action)(t_ini *,
							    char const *,
							    t_ini_parse *);

# define INI_IS_LOWER_ALPHA(c)	(((c) >= 'a') && ((c) <= 'z'))
# define INI_IS_UPPER_ALPHA(c)	(((c) >= 'A') && ((c) <= 'Z'))
# define INI_IS_NUMERIC(c)	(((c) >= '0') && ((c) <= '9'))

# define _INI_PARSE_INIT_	(t_ini_parse){INI_PARSE_VOID, NULL, _INIT_INI_DATAMAP_, false, g_defaultString}

#endif /* !INI_PARSE_H_ */
