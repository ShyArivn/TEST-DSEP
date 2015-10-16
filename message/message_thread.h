

#ifndef _MESSAGE_THREAD_H_
#define _MESSAGE_THREAD_H_

#include "uos/thread.h"
#include "uos/cond.h"
#include "uos/mutex.h"

#include "message/message_queue.h"


namespace message {

class MessageThread : public uos::Thread
{

public:
	MessageThread();
	~MessageThread();

	void LockAndWait();
	void UnLockAndRun();

protected:
	uos::Cond _MessageThreadCond;
	uos::Mutex _MessageThreadMutex;
};

}



#endif