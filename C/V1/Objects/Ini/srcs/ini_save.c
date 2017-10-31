/**
* \file				ini_save.c
* \author			Sébastien Le Maire
* \version			1.0
* \date			        14 Février 2017
*/

#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include "ini.h"

static void  		        ini_write_dataMap(void *content,
						  void *data)
{
  t_iniDataMap const		*dataMap = (t_iniDataMap const *)content;
  int const			fd = *(int const *)data;

  (void)write(fd, dataMap->_key, strlen(dataMap->_key));
  (void)write(fd, " = \"", 4);
  if (dataMap->_value)
    (void)write(fd, dataMap->_value, strlen(dataMap->_value));
  (void)write(fd, "\"\n", 2);
}

static void  		        ini_write_section(void *content,
						  void *data)
{
  t_iniSection const		*section = (t_iniSection const *)content;
  int const			fd = *(int const *)data;

  if (section->_name)
    {
      (void)write(fd, "[", 1);
      (void)write(fd, section->_name, strlen(section->_name));
      (void)write(fd, "]\n", 2);
    }
  vector_foreach_data(&section->_values, ini_write_dataMap, data);
  (void)write(fd, "\n", 1);
}

t_bool				ini_save(t_ini *this, char const *filename)
{
  int				fd;

  if ((filename) && (!strcmp(filename + strlen(filename) - 4, ".ini")) &&
      ((fd = open(filename, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) != -1))
    {
      vector_foreach_data(&this->_sections, ini_write_section, &fd);
      (void)close(fd);
      return (true);
    }
  return (false);
}
