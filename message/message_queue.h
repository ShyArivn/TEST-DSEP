
#ifndef _MESSAGE_QUEUE_H_
#define _MESSAGE_QUEUE_H_

#include "message/message.h"
#include "message/message_thread.h"
#include "util/linklist.h"
#include "message/message_role.h"

namespace message {

class MessageQueue : public MessageThread, public util::LinkList
{

public:
	MessageQueue();
	virtual ~MessageQueue();

	virtual void OnMessage();
	virtual void Post(Message *message);
	virtual void BroadCast(Message *message);

	void run();

protected:
	virtual void _Push(Message *message);
	virtual Message* _Pop();

private:
	MessageRoleMap _Group;
	MessageRoleMap _Topic;
};

}


#endif