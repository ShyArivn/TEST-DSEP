

#ifndef _MESSAGE_QUEUE_PROXY_H_
#define _MESSAGE_QUEUE_PROXY_H_

#include "message/message_queue.h"

namespace message {

class MessageQueueProxy
{

public:
	MessageQueueProxy();
	~MessageQueueProxy();

	void ProxyPost(Message *message);
	void ProxyBroadcast(Message *message);

	
};

}


#endif