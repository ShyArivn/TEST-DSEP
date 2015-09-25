#include <unistd.h>
#include "uos/thread.h"

#include <list>
using namespace std;
using namespace uos;

class mytest
{
public:
	mytest(){
		fprintf(stdout, "%s\n", "mytest constructor non init");
	}
	mytest(int count, char *str){
		_Count = count;
		_Str = str;
		fprintf(stdout, "%s\n", "mytest constructor init");
	}
	mytest(const mytest& test){
		fprintf(stdout, "%s\n", "copy constructor init");
	}
private:
	int _Count;
	char *_Str;

private:
	
};

class cthread : public Thread
{
public:
	cthread();
	cthread(bool joinable);
	~cthread();
	void run();
private:
	list<mytest> _Mytest;
};

cthread::cthread()
{
	fprintf(stdout, "%s\n", "cthread constructor non init");
}

cthread::cthread(bool joinable):Thread(joinable)
{
	fprintf(stdout, "%s\n", "cthread constructor init");
}

cthread::~cthread()
{
	fprintf(stdout, "cthread deconstuctor:%lu\n", pthread_self());
}


void cthread::run()
{
	char *str = "abc";
	mytest test = mytest(5, str);
	_Mytest.push_back(test);
	fprintf(stdout, "%s\n", "thread cache run");
}

list<cthread> mythreads;
void runspec()
{
	for(int i=0;i<3;i++){

		cthread thread = cthread(false);
		mythreads.push_back(thread);
		mythreads.back().create(0);
	}
}

int main(int argc, char **argv)
{
	char *filename = "/.macro/util/test/testlog.log";
	log_open(filename, Logger::LEVEL_DEBUG, false, 0);

	runspec();
	
	fprintf(stdout, "%s\n", "sleep ....");
	sleep(100000000);
}
