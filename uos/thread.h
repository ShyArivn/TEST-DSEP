
#ifndef _THREAD_H_
#define _THREAD_H_

#include <pthread.h>

#include "util/log.h"


namespace uos {

class Thread
{
public:
	Thread();
	Thread(bool joinable);
	virtual ~Thread() {};
	int join();
	int detach();
	bool create(int stacksize);
	bool setState(int state);
	pthread_t threadId();

	virtual void run(){};

private:

	int _Thread_State;
	pthread_t _Thread_Id;

public:
	static const int JOIN = 1;
	static const int DETACH = 2;
	static const int RUN = 4;
	static const int STOP = 8;
};

}

#endif
