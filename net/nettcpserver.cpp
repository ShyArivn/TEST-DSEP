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

NetTcpServer::NetTcpServer ( )
{
/*#ifdef _EPOLL
	//NetEpollEvent *_Event = NetEpollEvent();
#else
	//_Event = NetSelectEvent()
#endif*/
	_Event = new NetEpollEvent();
}

NetTcpServer::~NetTcpServer ( )
{
	_Acceptor->Close();
}

void NetTcpServer::start ( )
{
	assert( _Event != NULL );

	struct ComEvent IoEvent[MAX_EVENTS];

	_Event->wait(&IoEvent[0], _TimeOut);
}

bool NetTcpServer::addIoServer ( const char *addr, const int port )
{

	NetSocket *serversocket = new NetServerSocket();

	serversocket->NetSetAddress(addr, port);

	_Acceptor = new NetAcpIoCom(serversocket ,this);

	_Acceptor->SetIoEvent(_Event);

	_Acceptor->EventIoCom(_Event, NET_READABLE);

	_Acceptor->start();

	return true;

}

void NetTcpServer::CloseServer()
{
	delete this;
}

}
