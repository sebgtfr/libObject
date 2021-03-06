/**
* \file				server_ctor.c
* \author			Sébastien Le Maire
* \version			1.0
* \date				02/03/2017
*/

#include <string.h>
#include "server.h"

t_bool				server_ctor(t_server *this,
                                t_typeSocket const type,
                                socklen_t socklen)
{
    SOCKADDR			*sockaddr = (socklen) ? malloc(socklen) : NULL;

    if (((socklen && sockaddr) || (!socklen)) &&
        socket_ctor(&this->_socket, type, sockaddr, socklen))
        {
            list_ctor(&this->_clients, sizeof(t_server_client *));
            (void)memset(&this->_events, 0, sizeof(this->_events));
            this->_globals = NULL;
            this->_output = _INIT_BUFFER_;
            return (buffer_resize(&this->_output, _SOCKET_OUTPUT_SIZE_));
        }
    return (false);
}
