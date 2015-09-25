
#include "netlib.h"

namespace netlib {

NetServer::NetServer()
{	
	
}

void NetServer::_AddProcessHandler(NetHandleBuffer *processhandler)
{
	_ProcessHandler = processhandler;
}

NetHandleBuffer *NetServer::_GetProcessHandler()
{
	return _ProcessHandler;
}

NetTimeOut *NetServer::GetTimeOut()
{
	return &_TimeOut;
}

}
