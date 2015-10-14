
#ifndef _MESSAGE_QUEUE_H_
#define _MESSAGE_QUEUE_H_

#include "message/message.h"
#include "message/message_thread.h"
#include "util/linklist.h"

namespace message {

class MessageQueue : public MessageThread, public util::LinkList
{
	
};

}


#endif