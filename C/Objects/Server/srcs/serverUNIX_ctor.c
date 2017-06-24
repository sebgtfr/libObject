/**
* \file				serverUNIX_ctor.c
* \author			Sébastien Le Maire
* \version			1.0
* \date				03/03/2017
*/

#include <string.h>
#include "server.h"

static void			serverUNIX_configSockaddr(struct sockaddr_un *sockaddr,
							  char const *path)
{
  sockaddr->sun_family = AF_UNIX;
  (void)strncpy(sockaddr->sun_path, path, sizeof(sockaddr->sun_path) - 1);
  if (!access(sockaddr->sun_path, F_OK))
    unlink(sockaddr->sun_path);
}

t_bool				serverUNIX_ctor(t_server *this,
						uint64_t const sizeClient,
					        char const *path)
{
  if (server_ctor(this, SOCKET_UNIX, sizeClient, sizeof(struct sockaddr_un)))
    {
      serverUNIX_configSockaddr((struct sockaddr_un *)this->_server._socket._sockaddr,
			        path);
      return (true);
    }
  return (false);
}
