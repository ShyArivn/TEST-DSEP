
#include "util/rbtree.h"

using namespace util;

class TestRB
{
public:
	TestRB(int testcount, char* str){
		_testcount = testcount;
		_teststr = str;
	}
	~TestRB()
	{

	}

	friend bool operator<(const TestRB& ln, const TestRB& rn)
	{
		if(ln._testcount < rn._testcount){
			return false;
		}else{
			return true;
		}
	}
private:
	int _testcount;
	char *_teststr;
};

int main(int argc, char **argv)
{
	RbTree<TestRB> _rbtree;
	TestRB _testrb(5,"rbtree");
	_rbtree.RbTreeInsert(_testrb);
}
