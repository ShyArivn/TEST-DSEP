/*
* shyarivn.
*
*
* Version: 1.0
*
* Authors:
*	shyarivn - shyarivn@gmail.com
*/

#ifndef SH_NET_SOKET_H
#define SH_NET_SOKET_H

namespace netlib {

class NetSocket {

public:
	NetSocket();

	NetSocket(int fd);

	virtual ~NetSocket() {};

	bool NetConnect();

	bool NetClose();

	ssize_t NetWrite(Sstr &data);

	ssize_t NetRead(Sstr &data);

	bool NetSetKeepAlive(bool on);

	bool NetSetReusePort(bool on);

	bool NetSetReuseAddress(bool on);

	bool NetSetBlock(bool on);

	bool NetSetTimeOption(bool on);

	void NetSetIoCom(NetIoCom *iocom);

	int NetSocketfd();

	NetIoCom* NetSocketIoCom();

	void NetSetSocketfd(int fd);

	void NetSetSockAddr(struct sockaddr_in *sa);

	bool NetSetAddress(const char *addr, const int port);


protected:

	struct sockaddr_in _Addr;

	NetIoCom *_Iocom;

	int _Socketfd;

};

}

#endif
