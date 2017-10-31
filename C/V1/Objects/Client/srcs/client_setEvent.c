/**
* \file				client_setEvent.c
* \author			Sébastien Le Maire
* \version			1.0
* \date				07/03/2017
*/

#include "client.h"

void				client_setEvent(t_client *this,
						t_client_event_type type,
						void *functionsEvent)
{
  if (type >= 0 && type < CLIENT_EVENT_LAST)
    ((void **)&this->_events)[type] = functionsEvent;
}
