
#ifndef _MUTEX_H_
#define _MUTEX_H_

#include <pthread.h>
#include <assert.h>

namespace uos {

class Mutex
{
public:
	Mutex();
	~Mutex();

	void lock();
	void unlock();
	int trylock();

	pthread_mutex_t* getMutexPtr() const;

private:
	mutable pthread_mutex_t _Mutex;
};

}

#endif
