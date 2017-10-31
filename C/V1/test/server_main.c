#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "server.h"

void				newClient(t_server *this, t_server_client *client)
{
  (void)printf("Le client %d est né !\n", client->_socket._fd);
  (void)this;
}

void				disconnection(t_server *this, t_server_client *client)
{
  (void)printf("Le client %d est mort !\n", client->_socket._fd);
  (void)this;
}

void				recvDataEvent(t_server *this,
					      t_server_client *client)
{
  SERVER_STDOUT(this, client->_socket._input._data, client->_socket._input._length);
  SERVER_CLEAR_INPUT(client);
}

int				g_ticks = 0;

void				action()
{
  (void)printf("%d secondes\n", g_ticks++);
}

int				main(int ac, char **av)
{
  t_server			server;

  if (ac != 2)
    return (EXIT_FAILURE);
  if (!socket_start())
    return (EXIT_FAILURE);
  if (serverTCP_ctor(&server, 0, atoi(av[1])))
    {
      server_setEvent(&server, SERVER_EVENT_DISCONNECTION, disconnection);
      server_setEvent(&server, SERVER_EVENT_NEW_CLIENT, newClient);
      server_setEvent(&server, SERVER_EVENT_RECV_DATA, recvDataEvent);
      server_setEvent(&server, SERVER_EVENT_ACTION, action);
      if (server_connect(&server, 5))
	{
	  server_launch(&server, 1, 0);
	}
      server_dtor(&server);
    }
  socket_end();
  return (EXIT_SUCCESS);
}
