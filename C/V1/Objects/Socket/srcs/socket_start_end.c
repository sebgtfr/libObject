/**
* \file				socket_start_end.c
* \author			Sébastien Le Maire
* \version			1.0
* \date				28/02/2017
*/

#include "socket.h"

t_bool				socket_start(void)
{
  __START_SOCKET__
  return (true);
}

void				socket_end(void)
{
  __CLEAN_SOCKET__
}
