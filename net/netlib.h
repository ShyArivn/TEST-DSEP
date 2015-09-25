/*
* (C) 2015
*
*
* Version: 1.0
* Authors:
* 	shyarivn-shyarivn@gmail.com
*/

#ifndef _NET_LIB_H_
#define _NET_LIB_H_

#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/time.h>
#include <pthread.h>
#include <errno.h>
#include <signal.h>
#include <assert.h>

#include "common/common.h"
#include "types/sstr.h"
#include "util/log.h"
#include "netcommon.h"

namespace netlib {
class NetBuffer;
class NetDoubleBuffer;
class NetHandleBuffer;
class NetAcpIoCom;
class NetPacket;
class NetConnection;
class NetConnectSocket;
class NetEpollEvent;
class NetEvent;
class NetHttpServer;
class NetHttpStream;
class NetIo;
class NetIoCom;
class NetIoStream;
class NetProcPacket;
class NetSelectEvent;
class NetServer;
class NetSocket;
class NetServerSocket;
class NetStream;
class netTcpConnection;
class NetTcpIoCom;
class NetTcpServer;
class NetTimeNode;
class NetTimeOut;
}

#include "nettypes.h"
#include "netiocom.h"
#include "netpacket.h"
#include "netbuffer.h"
#include "netdoublebuffer.h"
#include "netsocket.h"
#include "netevent.h"
#include "netconnection.h"
#include "netstream.h"
#include "nettimeout.h"
#include "netserver.h"
#include "netconnectsocket.h"
#include "netepollevent.h"
#include "nethttpserver.h"
#include "nethttpstream.h"
#include "netiostream.h"
#include "netacpiocom.h"
#include "netselectevent.h"
#include "netserversocket.h"
#include "nettcpconnection.h"
#include "nettcpiocom.h"
#include "nettcpserver.h"
#include "nethandlebuffer.h"

#endif
