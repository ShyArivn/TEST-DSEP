
#include "thread.h"

namespace uos {

extern "C"
{
void *hook(void *arg)
{
	Thread *threadptr = (Thread*)(arg);
	threadptr->run();
	threadptr->setState(Thread::STOP);
}
}

Thread::Thread()
{
	_Thread_State = JOIN|STOP;
	_Thread_Id = 0UL;
}

Thread::Thread(bool joinable){
	if(joinable){
		_Thread_State = JOIN|STOP;
	}else{
		_Thread_State = DETACH|STOP;
	}
	_Thread_Id = 0UL;
}

pthread_t Thread::threadId()
{
	return _Thread_Id;
}

bool Thread::create(int stacksize)
{
	if(_Thread_State&STOP)
	{
		if(stacksize>0){
			pthread_attr_t attr;
			int ret;
			ret = pthread_attr_init(&attr);
			if (ret != 0){
				log_error("thread attribute init error:%s", strerror(errno));
				return 0;
			}

			ret = pthread_attr_setstacksize(&attr, stacksize);
			if (ret != 0){
				log_error("thread setstacksize fail:%s", strerror(errno));
				return 0;
			}

			ret = pthread_create(&_Thread_Id, &attr, hook, this);
			if (ret != 0){
				log_error("thread create fail:%s", strerror(errno));
				return 0;
			}
		}else{

			int ret;
			ret = pthread_create(&_Thread_Id, 0, hook, this);
			if (ret != 0){
				log_error("thread create fail:%s", strerror(errno));
				return 0;
			}
		}
		
		if(_Thread_State&DETACH){
			this->detach();
		}else{
			this->join();
		}
		this->setState(RUN);
		return 1;
	}
}

int Thread::join()
{

	int ret = pthread_join(_Thread_Id, NULL);
	if (ret != 0){
		log_error("pthread join error:%s", strerror(errno));
		return 0;
	}
	_Thread_State &= ~DETACH;
	_Thread_State &= JOIN;
	return 1;
}

int Thread::detach()
{

	int ret = pthread_detach(_Thread_Id);
	if(ret != 0){
		log_error("pthread join error:%s", strerror(errno));
		return 0;
	}
	_Thread_State &= ~JOIN;
	_Thread_State &= DETACH;
	return 1;
}

bool Thread::setState(int state)
{
	_Thread_State = _Thread_State&state;
}

}
