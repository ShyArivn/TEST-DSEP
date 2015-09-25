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

NetEpollEvent::NetEpollEvent()
{
	_Epfd = epoll_create(Maxevents);
}

NetEpollEvent::~NetEpollEvent()
{

}

int NetEpollEvent::eventWait ( ComEvent *events, int timeout)
{
	struct epoll_event epollevents[Maxevents];
	int retval, numevents = 0;
	retval = epoll_wait(_Epfd, epollevents, Maxevents, timeout);
    if (retval > 0) {
        int j;
        numevents = retval;
        for (j = 0; j < numevents; j++) {
            events[j].iocom = (NetIoCom *)epollevents[j].data.ptr;
            events[j].iocom->ReSetComDataState();
            if (epollevents[j].events & EP_ERROR){
            	events[j].iocom->SetComDataState(NET_IOCOMM_ERROR); 
            }	 
            if (epollevents[j].events & EP_READ){
            	events[j].iocom->SetComDataState(NET_IOCOMM_READ);
            } 	
            if(epollevents[j].events & EP_WRITE){
            	events[j].iocom->SetComDataState(NET_IOCOMM_WRITE);
            }
        }
    }
    return numevents;	
}

int NetEpollEvent::addIoEvent ( NetSocket *socket , int op )
{
	struct epoll_event ee;
	memset(&ee, 0, sizeof(ee));
	ee.data.fd = socket->NetSocketfd();
	ee.data.ptr = socket->NetSocketIoCom();
	if ( op & NET_READABLE ) 
	{
		ee.events |= EP_READ|EPOLLET;
	}

	if ( op & NET_WRITABLE )
	{
		ee.events |= EP_WRITE|EPOLLET;
	}
	if ( epoll_ctl( _Epfd, EPOLL_CTL_ADD, socket->NetSocketfd(), &ee) == NET_ERR )
	{
		return NET_ERR;
	}
	return NET_OK;
}

int NetEpollEvent::modIoEvent ( NetSocket *socket, bool read, bool write)
{
	struct epoll_event ee;
	memset(&ee, 0, sizeof(ee));
	ee.data.fd = socket->NetSocketfd();
	ee.data.ptr = socket->NetSocketIoCom();
	if ( read ) 
	{
		ee.events |= EP_READ|EPOLLET;
	}
	if ( write )
	{
		ee.events |= EP_WRITE|EPOLLET;	
	}
	if ( epoll_ctl( _Epfd, EPOLL_CTL_MOD, socket->NetSocketfd(), &ee) == NET_ERR )
	{
		return NET_ERR;
	}

	return NET_OK;
}

int NetEpollEvent::delIoEvent ( NetSocket *socket )
{
	struct epoll_event ee;
	memset(&ee, 0, sizeof(ee));
	ee.data.ptr = socket->NetSocketIoCom();

	if ( epoll_ctl( _Epfd, EPOLL_CTL_DEL, socket->NetSocketfd(), &ee) == NET_ERR )
	{
		return NET_ERR;
	}
	return NET_OK;
	
}

}
