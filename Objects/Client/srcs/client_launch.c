/**
* \file				client_launch.c
* \author			Sébastien Le Maire
* \version			1.0
* \date				03/03/2017
*/

#include <signal.h>
#include "client.h"

t_bool				lg_continu = true;

static void                     client_sigquit(__attribute__((unused))int sig)
{
  lg_continu = false;
}

static void    			client_init_fdset(t_client *this,
						  fd_set fdSet[FD_SET_LAST])
{
  t_type_fd_set		typeFdSet = FD_SET_READ;

  while (typeFdSet < FD_SET_LAST)
    FD_ZERO(fdSet + (typeFdSet++));
  if (this->_events._stdin)
    FD_SET(STDIN_FILENO, fdSet + FD_SET_READ);
  if (!BUFFER_EMPTY(&this->_output))
    FD_SET(STDOUT_FILENO, fdSet + FD_SET_WRITE);
  FD_SET(this->_socket._fd, fdSet + FD_SET_READ);
  if (!BUFFER_EMPTY(&this->_socket._output))
    FD_SET(this->_socket._fd, fdSet + FD_SET_WRITE);
}

void				client_action(t_client *this,
					      fd_set fdSet[FD_SET_LAST])
{
  if (FD_ISSET(this->_socket._fd, fdSet + FD_SET_READ))
    {
      if ((lg_continu = socket_recv(&this->_socket)) &&
	  (this->_events._recvData))
	this->_events._recvData(this);
    }
  if (lg_continu && FD_ISSET(this->_socket._fd, fdSet + FD_SET_WRITE))
    lg_continu = socket_send(&this->_socket);
  if (lg_continu)
    {
      if (FD_ISSET(STDOUT_FILENO, fdSet + FD_SET_WRITE))
	{
	  buffer_print(&this->_output, STDOUT_FILENO);
	  buffer_reset(&this->_output);
	}
      if ((this->_events._stdin) &&
	  FD_ISSET(STDIN_FILENO, fdSet + FD_SET_READ))
	this->_events._stdin(this);
      if (this->_events._action)
	this->_events._action(this);
    }
}

t_bool				client_launch(t_client *this)
{
  if (signal(SIGINT, &client_sigquit) != SIG_ERR)
    {
      struct timeval		tv = {0, 0};
      fd_set			fdSet[FD_SET_LAST];

      while (lg_continu)
	{
	  client_init_fdset(this, fdSet);
	  if (select(this->_socket._fd + 1, fdSet + FD_SET_READ,
		     fdSet + FD_SET_WRITE, fdSet + FD_SET_EXCEPT, &tv) == -1)
	    lg_continu = false;
	  else
	    client_action(this, fdSet);
	}
      return (true);
    }
  return (false);
}
