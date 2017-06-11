
#include <unistd.h>
#include <stdlib.h>
#include "ini.h"

int		main(void)
{
  t_ini		ini;
  t_bool	lol;

  ini_ctor(&ini, "test.ini");
  if ((lol = ini_load(&ini)))
    {
      ini_save(&ini, "save.ini");
    }
  ini_dtor(&ini);
  return (EXIT_SUCCESS);
}
