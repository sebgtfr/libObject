/**
* \file				server_setEvent.c
* \author			Sébastien Le Maire
* \version			1.0
* \date				03/03/2017
*/

#include "server.h"

void				server_setEvent(t_server *this,
						t_server_event_type type,
						void *functionsEvent)
{
  if (type >= 0 && type < SERVER_EVENT_LAST)
    ((void **)&this->_events)[type] = functionsEvent;
}
