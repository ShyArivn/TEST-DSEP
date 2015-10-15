

#ifndef _QUEUE_REGISTER_H_
#define _QUEUE_REGISTER_H_

#include <hash_map>

#include "types/sstr.h"
#include "message/message_queue.h"

namespace message {

class QueueRegister
{

public:
	QueueRegister();
	~QueueRegister();
	void RegisterIntoMQ();

private:
	std::hash_map<Sstr, MessageQueue *> _MessageQueues;
};

static QueueRegister SQueueRegister;

static QueueRegister& GetQueueRegister()
{
	return SQueueRegister;
}
}


#endif