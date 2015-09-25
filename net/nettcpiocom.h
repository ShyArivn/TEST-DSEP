

#ifndef _NET_TCP_IOCOM_H_
#define _NET_TCP_IOCOM_H_

namespace netlib {

class NetTcpIoCom : public NetIoCom
{

public:
	NetTcpIoCom(NetSocket *socket, NetServer *server);
	~NetTcpIoCom();

	void ProcIoRead();
	void ProcIoWrite();
	void ProcIoTimeOut();
	void Destroy();
	
};

}

#endif
