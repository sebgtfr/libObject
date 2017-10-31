/**
* \file				clientTCP_ctor.c
* \author			Sébastien Le Maire
* \version			1.0
* \date				07/03/2017
*/

#include <string.h>
#include "client.h"

static t_bool			clientTCP_configSockaddr(SOCKADDR_IN *sockaddr,
							 char const *addressHost,
							 uint16_t const port)
{
  unsigned long int		ip;

  if ((ip = inet_addr(addressHost)) == (unsigned long int)INADDR_NONE)
    {
      struct hostent		*host = gethostbyname(addressHost);

      if (!host)
	return (false);
      sockaddr->sin_family = host->h_addrtype;
      (void)memcpy(&sockaddr->sin_addr, host->h_addr, host->h_length);
    }
  else
    {
      sockaddr->sin_addr.s_addr = ip;
      sockaddr->sin_family = AF_INET;
    }
  sockaddr->sin_port = htons(port);
  return (true);
}

t_bool				clientTCP_ctor(t_client *this,
					       char const *addressHost,
					       uint16_t const port)
{
  if (client_ctor(this, SOCKET_TCP, sizeof(SOCKADDR_IN)))
    return (clientTCP_configSockaddr((SOCKADDR_IN *)this->_socket._sockaddr,
				     addressHost, port));
  return (false);
}
