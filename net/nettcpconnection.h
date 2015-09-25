/*
* shyarivn
*
*
* Version: 1.0
*
* Authors:
*	shyarivn - shyarivn@gmail.com
*/

#ifndef _NET_TCPCONNECTION_H_
#define _NET_TCPCONNECTION_H_

namespace netlib {

class NetTcpConnection : public NetConnection
{

public:
	NetTcpConnection(NetSocket *socket, NetIoCom *iocom);
	~NetTcpConnection();
	bool readConnData();
	bool writeConnData();
	NetIoStream *GetIoStream();
	void Close();

private:

	NetIoStream *_Iostream;
};

}

#endif
