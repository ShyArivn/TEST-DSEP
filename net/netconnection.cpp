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

NetConnection::NetConnection(NetSocket *socket, NetIoCom *iocom)
:_Socket(socket),_Iocom(iocom)
{
}

NetConnection::~NetConnection()
{
	SetConnState(NET_CON_DISCONN);
	_Socket->NetClose();
}

int NetConnection::GetConnState ()
{
	return _State;
}

void NetConnection::SetConnState(int state)
{
	_State = state;
}

NetSocket *NetConnection::GetConnSock() 
{
	return _Socket;
}

NetIoCom *NetConnection::GetIoCom()
{
	return _Iocom;
}

void NetConnection::Close()
{
	delete this;
}

}
