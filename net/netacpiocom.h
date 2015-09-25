/*
* (C) 2015
*
*
* Version: 1.0
* Authors:
* 	shyarivn-shyarivn@gmail.com
*/


#ifndef _SH_NET_ACPIOCOM_H_
#define _SH_NET_ACPIOCOM_H_

namespace netlib {

class NetAcpIoCom : public NetIoCom {

public:
	NetAcpIoCom( NetSocket *socket,NetServer *server);

	~NetAcpIoCom();

	void start();

	void ProcIoRead();

	void ProcIoWrite();

	void Close();
};

}

#endif
