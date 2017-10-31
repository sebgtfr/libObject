/**
* \file				server.h
* \author			Sébastien Le Maire
* \version			1.0
* \date				02/03/2017
*/

#ifndef SERVER_H_
# define SERVER_H_

# include "list.h"
# include "timer.h"
# include "socket.h"

typedef struct s_server		t_server;

typedef struct			s_server_client
{
  t_socket			_socket;
  t_bool			_connect;
}				t_server_client;

/*
** Server's events
*/
typedef void			(*t_server_event_server)(t_server *);
typedef void			(*t_server_event_client)(t_server *, t_server_client *);

typedef enum			e_server_event_type
  {
				SERVER_EVENT_DISCONNECTION = 0,
				SERVER_EVENT_NEW_CLIENT,
				SERVER_EVENT_DELETE_CLIENT,
				SERVER_EVENT_ACTION,
				SERVER_EVENT_ACTION_CLIENT,
				SERVER_EVENT_STDIN,
				SERVER_EVENT_RECV_DATA,
				SERVER_EVENT_LAST
  }				t_server_event_type;

typedef struct			s_server_event
{
  t_server_event_client		_disconnection;
  t_server_event_client		_newClient;
  t_fct_clear			_deleteClient;
  t_server_event_server		_action;
  t_server_event_client		_actionClient;
  t_server_event_server		_stdin;
  t_server_event_client		_recvData;
}				t_server_event;

/*
** Server Object
*/
struct				s_server
{
  t_socket			_socket;
  t_list			_clients;
  struct timeval		_timer;
  t_server_event		_events;
  t_buffer			_output;
  void				*_globals;
};

# define SERVER_STDOUT(t, m, s)	buffer_concat(&(t)->_output, m, s)
# define SERVER_SEND(t, m, s)	SOCKET_WRITE(&(t)->_socket, m, s)
# define SERVER_CLEAR_INPUT(t)  buffer_reset(&(t)->_socket._input)

/*
** Server's functions
*/
t_bool				server_ctor(t_server *this,
					    t_typeSocket const type,
					    uint64_t const sizeClient,
					    socklen_t socklen);
void				server_dtor(t_server *this);

/*
** Accessor
*/
void				server_setEvent(t_server *this,
						t_server_event_type type,
						void *functionsEvent);

/*
** Methods
*/
t_bool				server_connect(t_server *this, uint8_t backlog);
t_bool				server_launch(t_server *this,
					      uint32_t const secFrequency,
					      uint32_t const usecFrequency);

/*
** Protocols
*/
t_bool				serverTCP_ctor(t_server *this,
					       uint64_t const sizeClient,
					       uint16_t const port);
t_bool				serverUDP_ctor(t_server *this,
					       uint64_t const sizeClient,
					       uint16_t const port);
# if defined (linux)
/*
** UNIX Protocol
*/
t_bool				serverUNIX_ctor(t_server *this,
						uint64_t const sizeClient,
					        char const *path);
# endif /* !define linux */

#endif /* !SERVER_H_ */
