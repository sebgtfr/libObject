/**
* \file				server_connect.c
* \author			Sébastien Le Maire
* \version			1.0
* \date				03/03/2017
*/

#include "server.h"

t_bool				server_connect(t_server *this,
					       uint8_t backlog)
{
  return (CAST_BOOL((bind(this->_socket._fd,
			  this->_socket._sockaddr,
			  this->_socket._socklen) >= 0) &&
		    (listen(this->_socket._fd, backlog) >= 0)));
}
