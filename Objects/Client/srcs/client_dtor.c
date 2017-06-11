/**
* \file				client_dtor.c
* \author			Sébastien Le Maire
* \version			1.0
* \date				07/03/2017
*/

#include "client.h"

void				client_dtor(t_client *this)
{
  socket_dtor(&this->_socket);
  buffer_dtor(&this->_output);
}
