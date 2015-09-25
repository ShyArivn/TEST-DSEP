
#ifndef _COND_H_
#define _COND_H_

#include <pthread.h>
#include <assert.h>
#include "uos/mutex.h"

namespace uos {

class Cond
{

public:
	Cond();
	~Cond();

	bool wait(const Mutex& mutex);
	void signal();
	void broadcast();

private:
	pthread_cond_t _Cond;
};
}

#endif
