/*
* (C) 2015
*
*
* Version: 1.0
* Authors:
* 	shyarivn-shyarivn@gmail.com
*/

#ifndef _NET_TCP_SERVER_H_
#define _NET_TCP_SERVER_H_
#include "nettimeout.h"

namespace netlib {

class NetTcpServer : public NetServer
{

public:
	NetTcpServer();
	~NetTcpServer();
	
	bool addIoServer(const char *addr, const int port );
	void start();

	void CloseServer();

private:

	NetEvent *_Event;
	NetAcpIoCom *_Acceptor;

};

}

#endif

