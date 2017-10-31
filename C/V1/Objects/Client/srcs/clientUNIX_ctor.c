/**
* \file				clientUNIX_ctor.c
* \author			Sébastien Le Maire
* \version			1.0
* \date				07/03/2017
*/

#include <string.h>
#include "client.h"

static t_bool			clientUNIX_configSockaddr(struct sockaddr_un *sockaddr,
							  char const *path)
{
  sockaddr->sun_family = AF_UNIX;
  (void)strncpy(sockaddr->sun_path, path, sizeof(sockaddr->sun_path) - 1);
  return (true);
}

t_bool				clientUNIX_ctor(t_client *this,
						char const *path)
{
  if (client_ctor(this, SOCKET_UNIX, sizeof(struct sockaddr_un)))
    return (clientUNIX_configSockaddr((struct sockaddr_un *)this->_socket._sockaddr,
				      path));
  return (false);
}
