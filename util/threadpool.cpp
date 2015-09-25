
#include "util/threadpool.h"

namespace uos {

Pthread::Pthread(ThreadPool *pool):Thread(false)
{
	_Pool = pool;
}
Pthread::~Pthread()
{

}

void Pthread::run()
{
	_Pool->poolThreadRun();
}

ThreadPool::ThreadPool()
:_MaxPoolSize(DEFAULT_POOL_SIZE)
{

}

ThreadPool::ThreadPool(int size)
:_MaxPoolSize(size)
{

}

ThreadPool::~ThreadPool()
{
	if(_PoolState == START){
		this->poolStop();
	}
}

void ThreadPool::addThreadTask(ThreadTask task)
{
	_Task_Queue_Mutex.lock();
	_Thread_Task.push(task);
	_Task_Queue_Mutex.unlock();
	_Thread_Cond.signal();

}

void ThreadPool::poolStart()
{
	_PoolState = START;
	fprintf(stdout, "%d\n", _MaxPoolSize);
	for (int i=0;i<_MaxPoolSize;i++)
	{	
		Pthread pthread = Pthread(this);
		_Thread_List.push_back(pthread);
		_Thread_List.back().create(0);
		
	}
}

void ThreadPool::poolStop()
{
	_Task_Queue_Mutex.lock();
	_PoolState = STOP;
	_Task_Queue_Mutex.unlock();
	_Thread_Cond.broadcast();

	for(_Iter=_Thread_List.begin();_Iter!=_Thread_List.end();_Iter++){
		(*_Iter).join();
		_Thread_Cond.broadcast();
	}

	fprintf(stdout, "main pool thread exit:%lu\n", pthread_self());
}

void ThreadPool::poolThreadRun()
{
	while(true){

		fprintf(stdout, "thread run :%lu\n", pthread_self());
		_Task_Queue_Mutex.lock();

		if((_PoolState == START)&&(_Thread_Task.empty())) {
			int oret = _Thread_Cond.wait(_Task_Queue_Mutex);
		}

		if(_PoolState == STOP){

			_Task_Queue_Mutex.unlock();
			pthread_exit(NULL);
			fprintf(stdout, "thread exit: %lu\n", pthread_self());
		}
		fprintf(stdout, "thread get a task:%lu\n", pthread_self());
		ThreadTask task(_Thread_Task.front());
		_Thread_Task.pop();
		_Task_Queue_Mutex.unlock();

		task.TaskRun();

	}
}

}
