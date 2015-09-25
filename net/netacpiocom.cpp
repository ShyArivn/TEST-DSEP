/*
* shyarivn.
*
*
* Version: 1.0
*
* Authors:
*	shyarivn - shyarivn@gmail.com
*/

#include "netlib.h"

namespace netlib {

NetAcpIoCom::NetAcpIoCom ( NetSocket *socket, NetServer *server ) : NetIoCom ( socket ,server)
{

}

NetAcpIoCom::~NetAcpIoCom()
{
	
}

void NetAcpIoCom::ProcIoRead ( )
{
	NetSocket *socket;
	if((socket = static_cast<NetServerSocket*>(_Socket)->NetAccept())!=NULL)
	{
		NetTcpIoCom *tcpiocom = new NetTcpIoCom(socket,_Server);
		tcpiocom->EventIoCom( _Event ,NET_READABLE );
		NetTimeNode node(tcpiocom, 10000);
		NetTimeNode *timen = _Server->GetTimeOut()->AddTimeOut(node);
		tcpiocom->SetTimeOut(timen);
	}

}

void NetAcpIoCom::ProcIoWrite ()
{

}

void NetAcpIoCom::start ()
{
	static_cast<NetServerSocket*>(_Socket)->NetStart();
}

void NetAcpIoCom::Close()
{
	_Socket->NetClose();
	delete this;
}

}
