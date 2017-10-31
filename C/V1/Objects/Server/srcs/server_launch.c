/**
* \file				server_launch.c
* \author			Sébastien Le Maire
* \version			1.0
* \date				03/03/2017
*/

#include <signal.h>
#include <time.h>
#include "server.h"

t_bool				lg_continu = true;

static void                     server_sigquit(__attribute__((unused))int sig)
{
  lg_continu = false;
}

static t_item			*server_disconnectClient(t_server *this,
							 t_server_client *client,
							 t_item *it)
{
  t_item		*node = it;

  if (this->_events._disconnection)
    this->_events._disconnection(this, client);
  socket_dtor(&client->_socket);
  it = it->_next;
  list_erase(&this->_clients, node, this->_events._deleteClient);
  return (it);
}

static void			server_action(t_server *this, t_server_client *client,
					      t_bool execTimerFunction,
					      fd_set fdSet[2][FD_SET_LAST],
					      uint8_t const currentFdSet)
{
  if (FD_ISSET(client->_socket._fd, fdSet[!currentFdSet] + FD_SET_WRITE))
    client->_connect = socket_send(&client->_socket);
  if (client->_connect &&
      FD_ISSET(client->_socket._fd, fdSet[!currentFdSet] + FD_SET_READ))
    {
      if ((client->_connect = socket_recv(&client->_socket)) &&
	  (this->_events._recvData))
	{
	  this->_events._recvData(this, client);
	}
    }
  if (client->_connect)
    {
      if (execTimerFunction && this->_events._actionClient)
	this->_events._actionClient(this, client);
      if (client->_connect)
	{
	  FD_SET(client->_socket._fd, fdSet[currentFdSet] + FD_SET_READ);
	  if (!BUFFER_EMPTY(&client->_socket._output))
	    FD_SET(client->_socket._fd, fdSet[currentFdSet] + FD_SET_WRITE);
	}
    }
}

static int			server_app(t_server *this, t_bool execTimerFunction,
					   fd_set fdSet[2][FD_SET_LAST],
					   uint8_t const currentFdSet)
{
  t_item			*it = this->_clients._begin;
  int				maxFd = this->_socket._fd;

  if (execTimerFunction && this->_events._action)
    this->_events._action(this);
  if ((this->_events._stdin) &&
      FD_ISSET(STDIN_FILENO, fdSet[!currentFdSet] + FD_SET_READ))
    this->_events._stdin(this);
  if (FD_ISSET(STDOUT_FILENO, fdSet[!currentFdSet] + FD_SET_WRITE))
    {
      buffer_print(&this->_output, STDOUT_FILENO);
      buffer_reset(&this->_output);
    }
  while (it)
    {
      t_server_client		*client = (t_server_client *)it->_data;

      if (!client->_connect)
	it = server_disconnectClient(this, client, it);
      else
	{
	  server_action(this, client, execTimerFunction, fdSet, currentFdSet);
	  if (client->_connect)
	    {
	      if (maxFd < client->_socket._fd)
		maxFd = client->_socket._fd;
	      it = it->_next;
	    }
	  else
	    it = server_disconnectClient(this, client, it);
	}
    }
  return (maxFd);
}

static t_bool	       		server_newClient(t_server *this)
{
  int				fd = SOCKET_ERROR;
  SOCKADDR			*sockaddr = malloc(this->_socket._socklen);

  if ((sockaddr) &&
      ((fd = accept(this->_socket._fd, this->_socket._sockaddr,
		    &this->_socket._socklen)) != SOCKET_ERROR) &&
      (list_push_back(&this->_clients, NULL)))
    {
      t_server_client		*client = (t_server_client *)this->_clients._end->_data;

      client->_socket._fd = fd;
      socket_init(&client->_socket, sockaddr, this->_socket._socklen);
      client->_connect = true;
      if (this->_events._newClient)
	this->_events._newClient(this, client);
      return (true);
    }
  else
    {
      if (sockaddr)
	free(sockaddr);
      if (fd != SOCKET_ERROR)
	closesocket(fd);
    }
  return (false);
}

static void			server_init_fdset(fd_set fdSet[2][FD_SET_LAST],
						  uint8_t const currentFdSet)
{
  t_type_fd_set		typeFdSet = FD_SET_READ;

  while (typeFdSet < FD_SET_LAST)
    FD_ZERO(fdSet[currentFdSet] + (typeFdSet++));
}

t_bool				server_launch(t_server *this,
					      uint32_t const secFrequency,
					      uint32_t const usecFrequency)
{
  if ((signal(SIGINT, &server_sigquit) != SIG_ERR))
    {
      struct timeval		tv = {secFrequency, usecFrequency};
      t_bool			execTimerFunction = true;
      uint8_t			currentFdSet = 0;
      int			maxFd;
      fd_set			fdSet[2][FD_SET_LAST];
      struct timespec		now;
      struct timespec		old;
      t_bool			stateGetOldTime;
      t_bool			stateGetNowTime;

      this->_timer = tv;
      server_init_fdset(fdSet, !currentFdSet);
      while (lg_continu)
	{
	  stateGetOldTime = CAST_BOOL(clock_gettime(CLOCK_MONOTONIC, &old) != -1);
	  server_init_fdset(fdSet, currentFdSet);
	  if (this->_events._stdin)
	    FD_SET(STDIN_FILENO, fdSet[currentFdSet] + FD_SET_READ);
	  FD_SET(this->_socket._fd, fdSet[currentFdSet] + FD_SET_READ);
	  maxFd = server_app(this, execTimerFunction, fdSet, currentFdSet);
	  if (!BUFFER_EMPTY(&this->_output))
	    FD_SET(STDOUT_FILENO, fdSet[currentFdSet] + FD_SET_WRITE);
	  stateGetNowTime = CAST_BOOL(clock_gettime(CLOCK_MONOTONIC, &now) != -1);
	  if (stateGetNowTime && stateGetOldTime)
	    {
	      uint32_t		sec = now.tv_sec - old.tv_sec;
	      uint32_t		usec = (now.tv_nsec - old.tv_nsec) / 1000;


	      if (usec > tv.tv_usec)
		{
		  if (tv.tv_sec > 0)
		    {
		      --tv.tv_sec;
		      tv.tv_usec = tv.tv_usec + 1000000 - usec;
		    }
		  else
		    tv.tv_usec = 0;
		}
	      else
		tv.tv_usec -= usec;
	      tv.tv_sec = (sec >= tv.tv_sec) ? 0 : (tv.tv_sec - sec);
	    }
	  if (select(maxFd + 1, fdSet[currentFdSet] + FD_SET_READ,
		     fdSet[currentFdSet] + FD_SET_WRITE,
		     fdSet[currentFdSet] + FD_SET_EXCEPT, &tv) == -1)
	    lg_continu = false;
	  else if (FD_ISSET(this->_socket._fd, fdSet[currentFdSet] + FD_SET_READ))
	    server_newClient(this);
	  if ((execTimerFunction = (tv.tv_sec == 0 && tv.tv_usec == 0)))
	    tv = this->_timer;
	  currentFdSet = !currentFdSet;
	}
      return (true);
    }
  return (false);
}
