/**
* \file				socket.h
* \author			Sébastien Le Maire
* \version			1.0
* \date				28/02/2017
*/

#ifndef SOCKET_H_
# define SOCKET_H_

# include "bool.h"
# include "buffer.h"

# ifdef WIN32

#  include <winsock2.h>

#  define __START_SOCKET__							\
    WSADATA			wsa;						\
    if (WSAStartup(MAKEWORD(2, 2), &wsa) < 0)					\
      return (false);								\
  }										\

#  define __CLEAN_SOCKET__							\
  WSACleanup();									\

typedef int			socklen_t;

# elif defined (linux)

#  include <sys/types.h>
#  include <sys/socket.h>
#  include <netinet/in.h>
#  include <arpa/inet.h>
#  include <unistd.h> /* close */
#  include <netdb.h> /* gethostbyname */

#  define __START_SOCKET__	//
#  define __CLEAN_SOCKET__	//
#  define INVALID_SOCKET       	-1
#  define SOCKET_ERROR		-1
#  define closesocket(s)       	close(s)

typedef int			SOCKET;
typedef struct sockaddr		SOCKADDR;
typedef struct sockaddr_in	SOCKADDR_IN;
typedef struct protoent		PROTOENT;

# endif /* !PLATFORM_COMPATIBILITY */

typedef enum			e_type_fd_set
  {
			        FD_SET_READ = 0,
				FD_SET_WRITE,
			        FD_SET_EXCEPT,
			        FD_SET_LAST,
  }				t_type_fd_set;

typedef enum			s_typeSocket
  {
    _SOCKET_ERROR_ = SOCKET_ERROR,
    SOCKET_TCP,
    SOCKET_UDP,
    SOCKET_LAST_PROTOCOL,
    SOCKET_UNIX,
    SOCKET_UNDEFINED
  }				t_typeSocket;

typedef struct			s_dataSocket
{
  char const * const		_protoName;
  int const			_type;
}				t_dataSocket;

typedef struct			s_socket
{
  SOCKET			_fd;
  SOCKADDR			*_sockaddr;
  socklen_t			_socklen;
  t_buffer			_input;
  t_buffer			_output;
}				t_socket;

# ifndef _SOCKET_INPUT_SIZE_
#  define _SOCKET_INPUT_SIZE_	(1024)
# endif /* !_SOCKET_INPUT_SIZE_ */

# ifndef _SOCKET_OUTPUT_SIZE_
#  define _SOCKET_OUTPUT_SIZE_	(1024)
# endif /* !_SOCKET_OUTPUT_SIZE_ */

/*
** Socket *this, void *message, size_t size
*/
# define SOCKET_WRITE(t, m, s)	buffer_concat(&(t)->_output, m, s)

/*
** Socket *this
*/
# define SOCKET_GET_INPUT(t)	(t)->_input

/*
** Socket session's functions
*/
t_bool				socket_start(void);
void				socket_end(void);

/*
** Socket's functions
*/
t_bool				socket_ctor(t_socket *this,
					    t_typeSocket const type,
					    SOCKADDR *sockaddr,
					    socklen_t socklen);
t_bool				socket_init(t_socket *this, SOCKADDR *sockaddr,
					    socklen_t socklen);
void				socket_dtor(t_socket *this);

/*
** Methods
*/
t_bool				socket_recv(t_socket *this);
t_bool				socket_send(t_socket *this);

#endif /* !SOCKET_H_ */
