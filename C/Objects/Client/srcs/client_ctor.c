/**
* \file			        client_ctor.c
* \author			Sébastien Le Maire
* \version			1.0
* \date				07/03/2017
*/

#include <stdlib.h>
#include <string.h>
#include "client.h"

t_bool				client_ctor(t_client *this,
					    t_typeSocket const type,
					    socklen_t socklen)
{
  SOCKADDR			*sockaddr = (socklen) ? malloc(socklen) : NULL;

  if (((socklen && sockaddr) || (!socklen)) &&
      socket_ctor(&this->_socket, type, sockaddr, socklen))
    {
      (void)memset(&this->_events, 0, sizeof(this->_events));
      this->_globals = NULL;
      this->_output = _INIT_BUFFER_;
      return (buffer_resize(&this->_output, _SOCKET_OUTPUT_SIZE_));
    }
  return (false);
}
