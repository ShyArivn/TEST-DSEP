

#ifndef _THEAD_POOL_H_
#define _THEAD_POOL_H_

#include <list>
#include <queue>

#include "uos/thread.h"
#include "uos/mutex.h"
#include "uos/cond.h"

namespace uos {

class ThreadTask;
class ThreadPool;

class Pthread : public Thread
{
public:
	Pthread(ThreadPool *pool);
	~Pthread();
	void run();
private:
	ThreadPool *_Pool;
};

#define DEFAULT_POOL_SIZE 1
#define START 1
#define STOP 0

class ThreadPool
{

public:
	ThreadPool();
	ThreadPool(int size);
	~ThreadPool();

	void poolStart();
	void poolStop();
	void poolThreadRun();
	void addThreadTask(ThreadTask task);

private:
	int _MaxPoolSize;
	int _FreeSize;

	int _PoolState;

	Mutex _Task_Queue_Mutex;
	Cond _Thread_Cond;

	std::list<Pthread> _Thread_List;
	std::list<Pthread>::iterator _Iter;
	std::queue<ThreadTask> _Thread_Task;

};


typedef void *(*_func_ptr)(void *);

class ThreadTask
{
public:
	ThreadTask(_func_ptr fptr, void *args)
	{
		_Fptr = fptr;
		_Args = args;
	}

	~ThreadTask()
	{

	}

	inline void TaskRun() {
		(*_Fptr)(_Args);
	}



private:
	_func_ptr _Fptr;
	void *_Args;
};

}

#endif
