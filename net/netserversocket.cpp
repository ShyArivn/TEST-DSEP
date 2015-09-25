/*
* shyarivn.
*
*
* Version: 1.0
*
* Authors:
*	shyarivn - shyarivn@gmail.com
*/

#include "netlib.h"

namespace netlib {

NetServerSocket::NetServerSocket ( )
{
	_Backlog =1024;
	NetSetBlock(false);
	//NetSetReusePort(true);
}

NetServerSocket::~NetServerSocket ( )
{

}

bool NetServerSocket::NetStart ( )
{	

	if ( NetBind ( ) == NET_ERR )
	{
		return NET_ERR;
	}

	if ( NetListen ( ) == NET_ERR )
	{
		return NET_ERR;
	}

	return NET_OK;
}

int NetServerSocket::NetListen ( )
{
	if ( listen ( NetSocketfd(), _Backlog) == NET_ERR )
	{
		return NET_ERR;
	}
	return NET_OK;
}

int NetServerSocket::NetBind ( )
{
	if ( bind ( NetSocketfd(), (struct sockaddr *)&_Addr, sizeof(_Addr) ) == NET_ERR )
	{
		return NET_ERR;
	}
	return NET_OK;
}

NetSocket *NetServerSocket::NetAccept ()
{
	int socketfd;
	struct sockaddr_in sa;
	int len = sizeof(sa);
	while ((socketfd=accept(NetSocketfd(),(struct sockaddr*)&sa,(socklen_t*)&len))==NET_ERR)
	{
		if (errno == EINTR)
		{
			continue;
		}else{
			return NULL;
		}
	}
	
	NetSocket *socket = new NetConnectSocket(socketfd);
	socket->NetSetSockAddr(&sa);
	
	return socket;

}


}
