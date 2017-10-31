/**
* \file				socket_send.h
* \author			Sébastien Le Maire
* \version			1.0
* \date				03/03/2017
*/

#include <errno.h>
#include <unistd.h>
#include "socket.h"

t_bool				socket_send(t_socket *this)
{
  ssize_t			ret;

  errno = 0;
  if (((ret = sendto(this->_fd, this->_output._data, this->_output._length,
		     MSG_NOSIGNAL | MSG_DONTWAIT, this->_sockaddr,
		     this->_socklen)) <= 0)
      && (errno != EAGAIN && errno != EWOULDBLOCK))
    return (false);
  buffer_shift(&this->_output, ret);
  return (true);
}
