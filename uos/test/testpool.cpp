
#include <unistd.h>
#include "uos/threadpool.h"

using namespace uos;

void* runing(void* arg);

int main(int argc, char **argv)
{
	char *filename = "/.macro/util/test/testlog.log";
	//log_open(filename, Logger::LEVEL_DEBUG, false, 0);

	ThreadPool threadpool = ThreadPool();
	threadpool.poolStart();
	int arr[9] = {0,1,2,3,4,5,6,7,8};
	for(int i=0;i<9;i++)
	{
		ThreadTask threadtask = ThreadTask(&runing,(void*)&arr[i]);
		threadpool.addThreadTask(threadtask);
	}

	sleep(1000);
}

void* runing(void* arg){
	fprintf(stdout, "task is commpleted:%d\n", *((int*)arg));
}
