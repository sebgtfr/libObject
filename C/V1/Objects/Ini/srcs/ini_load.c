/**
* \file				ini_ctor.c
* \author			Sébastien Le Maire
* \version			1.0
* \date				24 Janvier 2017
*/

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "mystring.h"
#include "ini_parse.h"

static unsigned int		ini_parse_section(t_ini *this, char const *buffer,
						  t_ini_parse *parse)
{
  unsigned int			i = 0;
  unsigned int			spaceBegin = 0;
  t_bool			endParse = false;

  if (string_empty(&parse->_save))
    {
      while (buffer[spaceBegin] &&
	     ((buffer[spaceBegin] == ' ') || (buffer[spaceBegin] == '\t')))
	++spaceBegin;
      buffer += spaceBegin;
    }
  while (buffer[i] && buffer[i] != ']' && buffer[i] != '\n' &&
	 buffer[i] != ';' && buffer[i] != '[')
    ++i;
  if (buffer[i] == ']')
    endParse = true;
  else if (buffer[i] == '\n' || buffer[i] == '[' || buffer[i] == ';')
    parse->_state = INI_PARSE_ERROR;
  if (i)
    if (!string_concat(&parse->_save, buffer, i))
      parse->_state = INI_PARSE_ERROR;
  if (parse->_state == INI_PARSE_ERROR)
    return (0);
  if (endParse)
    {
      string_trim(&parse->_save);
      ini_push_new_section(this, parse->_save._data);
      parse->_currentSection = VECTOR_LAST(&this->_sections);
      string_reset(&parse->_save);
      parse->_state = INI_PARSE_END;
    }
  return (i + spaceBegin + (int)endParse);
}

static unsigned int		ini_parse_key(__attribute__((unused))t_ini *this,
					      char const *buffer,
					      t_ini_parse *parse)
{
  unsigned int			i = 0;

  while ((buffer[i] && buffer[i] != '\n') &&
	 (buffer[i] != ';') && buffer[i] != '=')
    ++i;
  if (!buffer[i])
    {
      if (i)
	if (!string_concat(&parse->_save, buffer, i))
	  parse->_state = INI_PARSE_ERROR;
    }
  else if (buffer[i] == '=')
    {
      if (i)
	if (!string_concat(&parse->_save, buffer, i))
	  parse->_state = INI_PARSE_ERROR;
      if (parse->_state != INI_PARSE_ERROR)
	{
	  string_trim(&parse->_save);
	  parse->_state = ((parse->_dataMap._key = strdup(parse->_save._data))) ? INI_PARSE_VALUE : INI_PARSE_ERROR;
	  string_reset(&parse->_save);
	}
    }
  else
    parse->_state = INI_PARSE_ERROR;
  return (i);
}

static unsigned int		ini_parse_value(__attribute__((unused))t_ini *this,
						char const *buffer,
						t_ini_parse *parse)
{
  unsigned int			i = 0;
  unsigned int			spaceBegin = 0;

  if (string_empty(&parse->_save))
    {
      while (buffer[spaceBegin] &&
	     ((buffer[spaceBegin] == ' ') || (buffer[spaceBegin] == '\t')))
	++spaceBegin;
      parse->_quote = CAST_BOOL(buffer[spaceBegin] == '"');
      spaceBegin += (int)parse->_quote;
      buffer += spaceBegin;
    }
  if (parse->_quote)
    while ((buffer[i] && buffer[i] != '"'))
      ++i;
  else
    while ((buffer[i] && buffer[i] != '\n') && (buffer[i] != ';'))
      ++i;
  if (!buffer[i] && i > 0)
    {
      if (!string_concat(&parse->_save, buffer, i))
	parse->_state = INI_PARSE_ERROR;
    }
  else if (buffer[i] == '\n' || buffer[i] == ';' || buffer[i] == '"')
    {
      if (i)
	if (!string_concat(&parse->_save, buffer, i))
	  parse->_state = INI_PARSE_ERROR;
      if (parse->_state != INI_PARSE_ERROR)
	{
	  if (!parse->_quote)
	    string_trim(&parse->_save);
	  if (!string_empty(&parse->_save))
	    if(!(parse->_dataMap._value = strdup(parse->_save._data)))
	      parse->_state = INI_PARSE_ERROR;
	  if (!parse->_currentSection)
	    parse->_state = INI_PARSE_ERROR;
	  if (parse->_state != INI_PARSE_ERROR)
	    {
	      if (INI_PUSH_DATAMAP_ON_SECTION(parse->_currentSection,
					      &parse->_dataMap))
		{
		  parse->_dataMap = _INIT_INI_DATAMAP_;
		  string_reset(&parse->_save);
		  parse->_state = INI_PARSE_END;
		  i += (int)parse->_quote;
		  parse->_quote = false;
		}
	      else
		parse->_state = INI_PARSE_ERROR;
	    }
	}
    }
  return (i + spaceBegin);
}

static t_ini_parse_state_action	g_iniActionState[INI_PARSE_END] =
  {
    ini_parse_section,
    ini_parse_key,
    ini_parse_value
  };

static void			ini_parse_set_state(t_ini *this, char const *buffer,
						    t_ini_parse *parse)
{
  switch (*buffer)
    {
    case '\n' :
      if ((parse->_state == INI_PARSE_VOID) && (parse->_currentSection) && (parse->_currentSection->_name))
	parse->_currentSection = ini_get_section(this, NULL);
      else
	parse->_state = INI_PARSE_VOID;
      break;
    case ';' :
      parse->_state = INI_PARSE_COMMENT;
    break;
    }
  if ((parse->_state == INI_PARSE_END) && (((*buffer) != ' ') && ((*buffer) != '\t')))
    parse->_state = INI_PARSE_ERROR;
  if (parse->_state != INI_PARSE_COMMENT && parse->_state != INI_PARSE_ERROR)
    {
      switch (*buffer)
	{
	case '[' :
	  parse->_state = INI_PARSE_SECTION;
	  break;
        default :
	  if (INI_IS_LOWER_ALPHA(*buffer) || INI_IS_UPPER_ALPHA(*buffer)
	      || INI_IS_NUMERIC(*buffer))
	    {
	      parse->_state = INI_PARSE_KEY;
	      if (!parse->_currentSection)
		{
		  if (!ini_push_new_section(this, NULL))
		    parse->_state = INI_PARSE_ERROR;
		  parse->_currentSection = VECTOR_LAST(&this->_sections);
		}
	    }
	break;
	}
    }
}

static void			ini_parse_file(t_ini *this, char const *buffer,
					       t_ini_parse *parse)
{
  unsigned int			i;

  while ((*buffer) && (parse->_state != INI_PARSE_ERROR))
    {
      if (parse->_state > INI_PARSE_COMMENT && parse->_state < INI_PARSE_END)
	{
	  i = g_iniActionState[parse->_state](this, buffer, parse);
	  buffer += i;
	}
      if (*buffer && parse->_state != INI_PARSE_ERROR)
	{
	  ini_parse_set_state(this, buffer, parse);
	  if (parse->_state != INI_PARSE_KEY)
	    ++buffer;
	}
    }
}

/**
* \brief			Construteur de l'objet t_ini
* \details			Initialise un objet t_ini ({this})
* \param this			Référence sur l'objet ini
* \return			none
*/
t_bool				ini_load(t_ini *this)
{
  int				fd;
  int				ret;
  char				buffer[_INI_BUFFER_SIZE_ + 1];
  t_ini_parse			parse = _INI_PARSE_INIT_;

  if ((this->_name) && (!strcmp(this->_name + strlen(this->_name) - 4, ".ini")) &&
      ((fd = open(this->_name, O_RDONLY)) != -1) &&
      (string_add_page_memory(&parse._save, _INI_BUFFER_SIZE_)))
    {
      while ((parse._state != INI_PARSE_ERROR) &&
	     ((ret = read(fd, (void *)buffer, _INI_BUFFER_SIZE_)) > 0))
	{
	  buffer[ret] = '\0';
	  ini_parse_file(this, buffer, &parse);
	}
      (void)close(fd);
      string_dtor(&parse._save);
      if ((ret < 0) || ((parse._state == INI_PARSE_ERROR)))
	{
	  ini_dtor(this);
	  return (false);
	}
      return (true);
    }
  return (false);
}
