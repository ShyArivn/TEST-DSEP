/*
* shyarivn.
*
*
* Version: 1.0
*
* Authors:
*	shyarivn - shyarivn@gmail.com
*/

#ifndef _NET_EPOLLEVENT_H_
#define _NET_EPOLLEVENT_H_

namespace netlib {


#define _EPOLLIN 0x001
#define _EPOLLPRI 0x002
#define _EPOLLOUT 0x004
#define _EPOLLERR 0x008
#define _EPOLLHUP 0x010
#define _EPOLLRDHUP 0x2000
#define _EPOLLONESHOT (1 << 30)
#define _EPOLLET (1 << 31)

#define EP_READ _EPOLLIN
#define EP_WRITE _EPOLLOUT
#define EP_ERROR (_EPOLLERR|_EPOLLHUP)

class NetEpollEvent : public NetEvent
{

public:
	NetEpollEvent();
	
	~NetEpollEvent();

	int addIoEvent( NetSocket *socket, int op );

	int delIoEvent( NetSocket *socket );

	int eventWait( ComEvent *events, int timeout );

	int modIoEvent( NetSocket *socket, bool read, bool write);

private:
	int _Epfd;
};

}

#endif
