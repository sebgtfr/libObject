/**
* \file				dtor_socket.c
* \author			Sébastien Le Maire
* \version			1.0
* \date				28/02/2017
*/

#include <stdlib.h>
#include "socket.h"

void				socket_dtor(t_socket *this)
{
  if (this->_fd != SOCKET_ERROR)
    {
      closesocket(this->_fd);
      this->_fd = SOCKET_ERROR;
    }
  if (this->_sockaddr)
    {
      free(this->_sockaddr);
      this->_sockaddr = NULL;
    }
  buffer_dtor(&this->_input);
  buffer_dtor(&this->_output);
}
