


#ifndef _NET_TIMEOUT_H_
#define _NET_TIMEOUT_H_
#include <time.h>
#include "util/rbtree.h"

namespace netlib {


class NetTimeNode
{
public:

	NetTimeNode(NetIoCom *iocom, int timeout);
	~NetTimeNode();

	friend bool operator<(const NetTimeNode &ln, const NetTimeNode &rn){
		return ln._DeadLine < rn._DeadLine;
	}

	void SetTimeOut(int timeout);
	int GetTimeOut();
	long GetDeadLine() const;
	NetIoCom *GetIoCom() const;

private:
	NetIoCom *_Iocom;
	long _DeadLine;
	int _TimeOut;

};

class NetTimeOut
{
public:
	NetTimeOut();
	
	~NetTimeOut();

	NetTimeNode* AddTimeOut(NetTimeNode &node);

	void DelTimeOut(NetTimeNode *node);

	int ProcessTimeOut();

	NetTimeNode* GetNearestTimeOut();

private:
	util::RbTree<NetTimeNode> _TimeRbTree;
};

}



#endif
