/**
* \file			        socket_ctor.c
* \author			Sébastien Le Maire
* \version			1.0
* \date				28/02/2017
*/

#include "socket.h"

static t_dataSocket const	lg_dataSocket[SOCKET_LAST_PROTOCOL] =
  {
    { "TCP", SOCK_STREAM },
    { "UDP", SOCK_DGRAM }
  };

t_bool				socket_ctor(t_socket *this,
					    t_typeSocket const type,
					    SOCKADDR *sockaddr,
					    socklen_t socklen)
{
  if (type < SOCKET_UNDEFINED)
    {
      if (type > _SOCKET_ERROR_ && type < SOCKET_LAST_PROTOCOL)
	{
	  PROTOENT		*pe;

	  if (((pe = getprotobyname(lg_dataSocket[type]._protoName)) &&
	       ((this->_fd = socket(AF_INET, lg_dataSocket[type]._type,
				    pe->p_proto)) != SOCKET_ERROR)) ||
	      ((type == SOCKET_UNIX) &&
	       ((this->_fd = socket(AF_UNIX, SOCK_STREAM, 0)) != SOCKET_ERROR)))
	    return (socket_init(this, sockaddr, socklen));
	}
    }
  this->_fd = SOCKET_ERROR;
  return (false);
}
