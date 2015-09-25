/*
* shyarivn.
*
*
* Version: 1.0
*
* Authors:
*	shyarivn - shyarivn@gmail.com
*/

#ifndef SH_NET_CONNECTSOCKET_H_
#define SH_NET_CONNECTSOCKET_H_

namespace netlib {

class NetConnectSocket : public NetSocket {

public:
	NetConnectSocket(int fd);
	~NetConnectSocket();
};

}

#endif

