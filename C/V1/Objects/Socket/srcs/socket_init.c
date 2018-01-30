/**
* \file				socket_init.c
* \author			Sébastien Le Maire
* \version			1.0
* \date				06/03/2017
*/

#include <string.h>
#include "socket.h"

t_bool				socket_init(t_socket *this, SOCKADDR *sockaddr,
					    socklen_t socklen)
{
  if (sockaddr)
    {
      (void)memset(sockaddr, 0, socklen);
      this->_socklen = socklen;
    }
  else
    this->_socklen = 0;
  this->_sockaddr = sockaddr;
  this->_input = _INIT_BUFFER_;
  this->_output = _INIT_BUFFER_;
  return (buffer_resize(&this->_input, _SOCKET_INPUT_SIZE_) &&
	  buffer_resize(&this->_output, _SOCKET_OUTPUT_SIZE_));
}
