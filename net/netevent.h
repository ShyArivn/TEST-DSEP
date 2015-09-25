/*
* shyarivn.
*
*
* Version: 1.0
*
* Authors:
*	shyarivn - shyarivn@gmail.com
*/

#ifndef _NET_EVENT_H_
#define _NET_EVENT_H_
#include "netcommon.h"

namespace netlib {

class NetEvent 
{
public:
	NetEvent();

	virtual ~NetEvent() {};

	void wait(ComEvent *events, NetTimeOut &timeout);

	virtual int addIoEvent( NetSocket *socket, int op )=0;

	virtual int delIoEvent( NetSocket *socket )=0;

	virtual int eventWait( ComEvent *events, int timeout )=0;

	virtual int modIoEvent ( NetSocket *socket, bool read, bool write)=0;

	virtual void CloseEvent () { delete this;}

protected:
	int Maxevents;

protected:
	int _GetWaitTime(NetTimeOut &timeout);
};

}

#endif
