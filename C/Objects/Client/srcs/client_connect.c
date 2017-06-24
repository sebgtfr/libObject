/**
* \file			        client_connect.c
* \author			Sébastien Le Maire
* \version			1.0
* \date				07/03/2017
*/

#include "client.h"

t_bool				client_connect(t_client *this)
{
  return (CAST_BOOL(connect(this->_socket._fd, this->_socket._sockaddr,
			    this->_socket._socklen) >= 0));
}
