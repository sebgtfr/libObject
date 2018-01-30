/**
* \file				socket_recv.h
* \author			Sébastien Le Maire
* \version			1.0
* \date				03/03/2017
*/

#include <errno.h>
#include <unistd.h>
#include "socket.h"

t_bool				socket_recv(t_socket *this)
{
  ssize_t			ret;
  char				buffer[_SOCKET_INPUT_SIZE_ + 1];

  errno = 0;
  if (((ret = recvfrom(this->_fd, (void *)buffer, _SOCKET_INPUT_SIZE_,
		       MSG_DONTWAIT, this->_sockaddr, &this->_socklen)) <= 0)
      && (errno != EAGAIN))
    return (false);
  buffer[ret] = '\0';
  return (buffer_concat(&this->_input, (void *)buffer, ret));
}
