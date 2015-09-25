/*
* shyarivn
*
*
* Version: 1.0
*
* Authors:
*	shyarivn - shyarivn@gmail.com
*/

#ifndef _NET_CONNECTION_H_
#define _NET_CONNECTION_H_

namespace netlib {

class NetConnection
{

public:

	NetConnection( NetSocket* socket, NetIoCom* iocom);

	virtual ~NetConnection();

	virtual bool readConnData()=0;

	virtual bool writeConnData()=0;

	virtual NetStream *GetIoStream()=0;

	virtual void Close();

	int GetConnState();

	void SetConnState(int state);

	NetSocket *GetConnSock();

	NetIoCom *GetIoCom();

protected:
	int _State;
	NetSocket *_Socket;
	NetIoCom *_Iocom;
};

}

#endif
