/*
* shyarivn.
*
*
* Version: 1.0
*
* Authors:
*	shyarivn - shyarivn@gmail.com
*/

#ifndef SH_NET_SERVERSOKET_H_
#define SH_NET_SERVERSOKET_H_

namespace netlib {

class NetServerSocket : public NetSocket {

public:
	NetServerSocket();

	NetServerSocket(const int backlog);

	~NetServerSocket();

	bool AddSockets(const char &addr, const int port);

	NetSocket *NetAccept();

	int NetListen();

	int NetBind();
	
	bool NetStart();

private:
	
	int _Backlog;

};

}

#endif
