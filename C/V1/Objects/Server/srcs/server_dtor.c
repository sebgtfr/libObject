/**
* \file				server_dtor.c
* \author			Sébastien Le Maire
* \version			1.0
* \date				02/03/2017
*/

#include "server.h"

static void	       		server_dtorClients(t_list *clients,
                                           t_fct_clear clear)
{
    while (clients->_begin)
        {
            t_item			*elem = clients->_begin;
            t_server_client *client = *(t_server_client **)elem->_data;

            clients->_begin = clients->_begin->_next;
            socket_dtor((t_socket *)client);
            if (clear)
                clear((void *)client);
            free((void *)client);
            free(elem);
        }
    clients->_length = 0;
    clients->_end = NULL;
}

void				server_dtor(t_server *this)
{
  socket_dtor(&this->_socket);
  buffer_dtor(&this->_output);
  server_dtorClients(&this->_clients, this->_events._deleteClient);
}
