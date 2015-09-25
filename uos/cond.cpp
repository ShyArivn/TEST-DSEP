
#include "uos/cond.h"

namespace uos {

Cond::Cond()
{
	int ret = pthread_cond_init(&_Cond, NULL);
	assert(ret==0);
}

Cond::~Cond()
{
	int ret = pthread_cond_destroy(&_Cond);
	assert(ret==0);
}

bool Cond::wait(const Mutex &mutex)
{
	int ret = pthread_cond_wait(&_Cond, mutex.getMutexPtr());
	if (!ret) {
		return 1;
	}
	return 0;
}

void Cond::signal()
{
	pthread_cond_signal(&_Cond);
}

void Cond::broadcast()
{
	pthread_cond_broadcast(&_Cond);
}

}
