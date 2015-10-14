
#ifndef _MESSAGE_SERVER_H_
#define _MESSAGE_SERVER_H_

#include "net/nettcpserver.h"
#include "message/message_queue.h"

namespace message {

class MessageServer : public NetTcpServer, public MessageQueue
{
	
};

}

#endif