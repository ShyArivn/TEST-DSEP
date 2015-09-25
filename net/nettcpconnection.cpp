/*
* shyarivn
*
*
* Version: 1.0
*
* Authors:
*	shyarivn - shyarivn@gmail.com
*/

#include "netlib.h"

namespace netlib {

NetTcpConnection::NetTcpConnection ( NetSocket* socket, NetIoCom* iocom )
:NetConnection(socket,iocom)
{
	_Socket = socket;
	_Iocom = iocom;
	_Iostream = new NetIoStream(this);
	_Iostream->SetStreamState(NET_ORIGIN);
	_Iostream->SetHandleStream(_Iocom->GetServer()->_GetProcessHandler());
}
NetTcpConnection::~NetTcpConnection()
{
	_Iostream->CloseStream();
}

bool NetTcpConnection::readConnData ()
{
	if (IsState(GetConnState(),NET_CON_CONNECT)) 
	{
		return _Iostream->ReadStream();
	}
	return false;
}

bool NetTcpConnection::writeConnData ()
{
	if (IsState(GetConnState(),NET_CON_CONNECT))
	{
		return _Iostream->WriteStream();
	}
	return false;
}

void NetTcpConnection::Close()
{
	delete this;
}

NetIoStream *NetTcpConnection::GetIoStream()
{
	return _Iostream;
}

}



