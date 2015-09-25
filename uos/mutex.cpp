
#include "uos/mutex.h"

namespace uos {

Mutex::Mutex()
{
	int ret = pthread_mutex_init(&_Mutex, NULL);
	assert(ret == 0);
}

Mutex::~Mutex()
{
	int ret = pthread_mutex_destroy(&_Mutex);
	assert(ret==0);
}

void Mutex::lock()
{
	pthread_mutex_lock(&_Mutex);
}

void Mutex::unlock()
{
	pthread_mutex_unlock(&_Mutex);
}

int Mutex::trylock()
{
	return pthread_mutex_trylock(&_Mutex);
}

pthread_mutex_t* Mutex::getMutexPtr() const
{
	return &_Mutex;
}

}
