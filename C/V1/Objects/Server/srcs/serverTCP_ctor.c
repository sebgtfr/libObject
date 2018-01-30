/**
* \file				serverTCP_ctor.c
* \author			Sébastien Le Maire
* \version			1.0
* \date				03/03/2017
*/

#include "server.h"

static void			serverTCP_configSockaddr(SOCKADDR_IN *sockaddr,
							 uint16_t const port)
{
  sockaddr->sin_port = htons(port);
  sockaddr->sin_addr.s_addr = htonl(INADDR_ANY);
  sockaddr->sin_family = AF_INET;
}

t_bool				serverTCP_ctor(t_server *this,
                                   uint16_t const port)
{
    if (server_ctor(this, SOCKET_TCP, sizeof(SOCKADDR_IN)))
        {
            serverTCP_configSockaddr((SOCKADDR_IN *)this->_socket._sockaddr,
                                     port);
            return (true);
        }
    return (false);
}
