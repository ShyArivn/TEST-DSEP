/*
* (C) 2015
*
*
* Version: 1.0
* Authors:
* 	shyarivn-shyarivn@gmail.com
*/

#include "netlib.h"

namespace netlib {

NetIoCom::NetIoCom(NetSocket *socket,NetServer *server)
{
	_Socket = socket;
	_Server = server;
	_Time = NULL;
	_DataState = 0;
}

NetIoCom::~NetIoCom()
{
	_Connection->Close();
	_Server->GetTimeOut()->DelTimeOut(_Time);
} 

bool NetIoCom::SetConnection ( NetConnection* connection )
{
	_Connection = connection;
	return true;
}

bool NetIoCom::EventIoCom ( NetEvent *event, int op )
{
	_Event = event;
	_Socket->NetSetIoCom ( this );
	_Event->addIoEvent ( _Socket, op );
	return true;
}

bool NetIoCom::SetIoEvent (NetEvent *event )
{
	_Event = event;
	return true;
}

bool NetIoCom::SetComDataState(int datastate)
{
	_DataState |= datastate;
	return true;
}

NetSocket *NetIoCom::GetComSocket() const
{
	return _Socket;
}

int NetIoCom::GetComDataState(){
	return _DataState;
}

void NetIoCom::Destroy()
{
	delete this;
}

NetEvent *NetIoCom::GetEvent()
{
	return _Event;
}

NetSocket *NetIoCom::GetSocket()
{
	return _Socket;
}

NetServer *NetIoCom::GetServer()
{
	return _Server;
}

void NetIoCom::SetTimeOut(NetTimeNode *node)
 {
 	_Time = node;
 }

 NetTimeNode *NetIoCom::GetTimeOut()
 {
 	return _Time;
 }

 NetConnection *NetIoCom::GetConnection()
 {
 	return _Connection;
 }

 void NetIoCom::ReSetComDataState()
 {
 	_DataState = 0;
 }

}
