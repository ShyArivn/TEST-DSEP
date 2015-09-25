
#include "testlog.h"

int main(int argc, char **agrv)
{
	char *filename = "/.macro/util/test/testlog.log";
	log_open(filename, Logger::LEVEL_DEBUG, false, 0);
	int incr;

	for(incr=0;incr<100;incr++)
	{
		log_debug("debug test");
		log_info("info test %d", incr);
	}
}
