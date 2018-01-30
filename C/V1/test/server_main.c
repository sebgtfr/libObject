#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "server.h"

t_server_client		*newClient(__attribute__((unused))t_server *this)
{
    (void)printf("Naissance d'un nouveau client !\n");
    return malloc(sizeof(t_server_client));
}

void				disconnection(__attribute__((unused))t_server *this,
                                  t_server_client *client)
{
    (void)printf("Le client %d est mort !\n", client->_socket._fd);
}

void				recvDataEvent(t_server *this,
					      t_server_client *client)
{
  SERVER_STDOUT(this, client->_socket._input._data, client->_socket._input._length);
  SERVER_CLEAR_INPUT(client);
}

static int          g_ticks = 0;

void				action()
{
  (void)printf("\r=> %03d secondes", g_ticks++);
  fflush(stdout);
}

int				main(int ac, char **av)
{
    t_server			server;

    if (ac != 2)
        return (EXIT_FAILURE);
    if (!socket_start())
        return (EXIT_FAILURE);
    if (serverTCP_ctor(&server, atoi(av[1])))
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
