/*
* (C) 2015
*
*
* Version: 1.0
* Authors:
* 	shyarivn-shyarivn@gmail.com
*/

#ifndef _NET_IOCOM_H_
#define _NET_IOCOM_H_

namespace netlib {

class NetIoCom
{

public:

	NetIoCom( NetSocket *socket, NetServer *server );

	virtual ~NetIoCom();
	virtual void ProcIoRead() {};
	virtual void ProcIoWrite() {};
	virtual void ProcIoTimeOut() {};
	virtual void Destroy();

	bool SetConnection(NetConnection* connection);
	NetConnection* GetConnection();
	bool SetIoEvent( NetEvent *event );
	bool EventIoCom( NetEvent *event, int op );
	NetSocket *GetComSocket() const;
	bool SetComDataState(int datastate);
	int GetComDataState();
	NetServer *GetServer();
	NetEvent *GetEvent();
	NetSocket *GetSocket();
	void SetTimeOut(NetTimeNode *node);
	NetTimeNode *GetTimeOut();
	void ReSetComDataState();

protected:

	NetEvent *_Event;
	NetSocket *_Socket;
	NetConnection *_Connection;
	NetServer *_Server;
	NetTimeNode *_Time;
	int _DataState;
};

}

#endif
