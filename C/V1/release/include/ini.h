/**
* \file				ini.h
* \author			Sébastien Le Maire
* \version			1.0
* \date				21 Janvier 2017
*/

#ifndef INI_H_
# define INI_H_

# include "bool.h"
# include "vector.h"

# ifndef NULL
/**
* \brief		        Defini la constante NULL.
* \details		        Défini la constante NULL si elle n'a pas été défini.
*/
#  define NULL			(void *)0
# endif /* !NULL */

typedef struct			s_iniDataMap
{
  char				*_key;
  char				*_value;
}				t_iniDataMap;

typedef struct			s_iniSection
{
  char				*_name;
  t_vector			_values;
}				t_iniSection;

typedef struct			s_ini
{
  char const			*_name;
  t_vector			_sections;
}				t_ini;

# define _INIT_INI_DATAMAP_	(t_iniDataMap){ NULL , NULL }
# define _INIT_INI_SECTION_	(t_iniSection){ NULL, _VECTOR_INIT_(t_iniDataMap) }
# define _INIT_INI_(filename)	(t_ini){ filename, _VECTOR_INIT_(t_iniSection) }

# ifndef _INI_BUFFER_SIZE_

/**
* \brief		        Taille lecture/écriture d'un flux
* \details		        Macro Déterminant la taille de lecture/ecriture d'un flux.
*				L'utilisateur peut déterminer cette en définisant cette macro
*				avant d'inclure le fichier header ini.h.
* \return		        Taille de lecture/ecriture d'un flux.
*/
#  define _INI_BUFFER_SIZE_	(1024)

# endif /*!_INI_BUFFER_SIZE_ */

# define INI_PUSH_SECTION(i, s)	(vector_push_back(i, s))

# define INI_PUSH_DATAMAP_ON_SECTION(s, d)	(vector_push_back(&(s)->_values, d))

/*
** Caninical form
*/
void				ini_ctor(t_ini *this, char const *filename);
void				ini_dtor(t_ini *this);

t_bool				ini_load(t_ini *this);

/*
** Sections
*/
t_bool				ini_push_new_section(t_ini *this,
						     char const *sectionName);
t_iniSection			*ini_get_section(t_ini *this,
						 char const *sectionName);

/*
** DataMap
*/
t_bool				ini_push_new_dataMap(t_ini *this,
						     char const *sectionName,
						     char const *key,
						     char const *value);
t_bool				ini_push_dataMap(t_ini *this,
						 char const *sectionName,
						 t_iniDataMap const *dataMap);
t_iniDataMap			*ini_get_dataMap(t_iniSection *this,
						 char const *key);

/*
** Other
*/
t_bool				ini_save(t_ini *this, char const *filename);

#endif /* !INI_H_ */
