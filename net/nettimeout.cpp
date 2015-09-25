
#include "net/netlib.h"

namespace netlib {

NetTimeNode::NetTimeNode(NetIoCom *iocom, int timeout)
:_Iocom(iocom)
{	
	struct timeval _timeval;
	gettimeofday(&_timeval, NULL);
	_TimeOut = timeout;
	_DeadLine = _timeval.tv_sec*1000 + _timeval.tv_usec/1000 + _TimeOut;
}

NetTimeNode::~NetTimeNode()
{

}

void NetTimeNode::SetTimeOut(int timeout)
{
	_TimeOut = timeout;
}

long NetTimeNode::GetDeadLine() const
{
	return _DeadLine;
}

NetIoCom *NetTimeNode::GetIoCom() const
{
	return _Iocom;
}

int NetTimeNode::GetTimeOut()
{
	struct timeval _timeval;
	gettimeofday(&_timeval, NULL);
	long now = _timeval.tv_sec*1000+_timeval.tv_usec/1000;
	return GetDeadLine()-now;
}


NetTimeOut::NetTimeOut()
{

}

NetTimeOut::~NetTimeOut()
{

}

NetTimeNode* NetTimeOut::AddTimeOut(NetTimeNode &node)
{
	return _TimeRbTree.RbTreeInsert(node);
}

NetTimeNode* NetTimeOut::GetNearestTimeOut()
{
	return _TimeRbTree.getMinDataNode();
}

void NetTimeOut::DelTimeOut(NetTimeNode *node)
{
	_TimeRbTree.RbTreeDelete(node);
}

int NetTimeOut::ProcessTimeOut()
{
	int wait;
	do{
		NetTimeNode *tmptime = GetNearestTimeOut();
		if(tmptime == NULL)
		{
			return DEFAULT_WAIT_TIME;
		}
		wait = tmptime->GetTimeOut();
		log_info("get wait:%d\n", wait);
		if(wait < 0)
		{
			NetIoCom *_iocom = tmptime->GetIoCom();
			_iocom->ProcIoTimeOut();
		}
	}while(wait < 0);

	return wait;

}


}
