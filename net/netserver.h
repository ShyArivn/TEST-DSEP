

#ifndef _NET_SERVER_H_
#define _NET_SERVER_H_

namespace netlib {

class NetServer
{
public:
	NetServer();
	virtual ~NetServer() {};
	NetTimeOut *GetTimeOut();
	NetHandleBuffer *_GetProcessHandler();
	void _AddProcessHandler(NetHandleBuffer *processhandler);

protected:
	NetHandleBuffer *_ProcessHandler;
	NetTimeOut _TimeOut;
};

}

#endif
