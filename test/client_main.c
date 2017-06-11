#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "client.h"

void				stdinEvent(t_client *this)
{
  char				buffer[_SOCKET_INPUT_SIZE_ + 1];
  ssize_t      			ret;

  if ((ret = read(STDIN_FILENO, (void *)buffer, _SOCKET_INPUT_SIZE_)) > 0)
    {
      buffer[ret] = '\0';
      CLIENT_SEND(this, buffer, ret);
    }
}

int				main(int ac, char **av)
{
  t_client			client;

  if (ac != 3)
    return (EXIT_FAILURE);
  if (!socket_start())
    return (EXIT_FAILURE);
  if (clientTCP_ctor(&client, av[1], atoi(av[2])))
    {
      printf("client\n");
      client_setEvent(&client, CLIENT_EVENT_STDIN, stdinEvent);
      if (client_connect(&client))
	client_launch(&client);
      client_dtor(&client);
    }
  socket_end();
  return (EXIT_SUCCESS);
}
