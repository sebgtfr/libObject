/**
* \file				client.h
* \author			Sébastien Le Maire
* \version			1.0
* \date				07/03/2017
*/

#ifndef CLIENT_H_
# define CLIENT_H_

# include "socket.h"

typedef struct s_client		t_client;

typedef void			(*t_client_event_client)(t_client *);

typedef enum			e_client_event_type
  {
				CLIENT_EVENT_STDIN = 0,
				CLIENT_EVENT_ACTION,
				CLIENT_EVENT_RECV_DATA,
				CLIENT_EVENT_LAST
  }				t_client_event_type;

typedef struct			s_client_event
{
  t_client_event_client		_stdin;
  t_client_event_client		_action;
  t_client_event_client		_recvData;
}				t_client_event;

struct				s_client
{
  t_socket			_socket;
  t_client_event		_events;
  t_buffer			_output;
  void				*_globals;
};

# define CLIENT_STDOUT(t, m, s)	buffer_concat(&(t)->_output, m, s)
# define CLIENT_SEND(t, m, s)	SOCKET_WRITE(&(t)->_socket, m, s)
# define CLIENT_CLEAR_INPUT(t)	buffer_reset(&(t)->_socket._input)

/*
** Client's functions
*/
t_bool				client_ctor(t_client *this,
					    t_typeSocket const type,
					    socklen_t socklen);
void				client_dtor(t_client *this);

/*
** Accessor
*/
void				client_setEvent(t_client *this,
						t_client_event_type type,
						void *functionsEvent);

/*
** Methods
*/
t_bool				client_connect(t_client *this);
t_bool				client_launch(t_client *this);

/*
** Protocols
*/
t_bool				clientTCP_ctor(t_client *this,
					       char const *addressHost,
					       uint16_t const port);
t_bool				clientUDP_ctor(t_client *this,
					       char const *addressHost,
					       uint16_t const port);
# if defined (linux)
/*
** UNIX Protocol
*/
t_bool				clientUNIX_ctor(t_client *this,
						char const *path);
# endif /* !define linux */

#endif /* !CLIENT_H_ */
