/*
* (C) 2015
*
*
* Version: 1.0
* Authors:
* 	shyarivn-shyarivn@gmail.com
*/

#include "netlib.h"

namespace netlib {

NetTcpIoCom::NetTcpIoCom ( NetSocket *socket,NetServer *server):NetIoCom(socket,server)
{
	_Connection = new NetTcpConnection(socket,this);
	_Connection->SetConnState(NET_CON_CONNECT);
}

NetTcpIoCom::~NetTcpIoCom()
{
	
}

void NetTcpIoCom::ProcIoRead ()
{
	assert( _Connection != NULL );
	if(!_Connection->readConnData()){
		Destroy();
	}
}

void NetTcpIoCom::ProcIoWrite()
{
	assert( _Connection != NULL );
	if(!_Connection->writeConnData())
	{
		Destroy();
	}
}

void NetTcpIoCom::ProcIoTimeOut()
{
	_Server->GetTimeOut()->DelTimeOut(_Time);
}

void NetTcpIoCom::Destroy()
{
	delete this;
}

}
