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

NetConnectSocket::NetConnectSocket(int fd):NetSocket(fd)
{	

	NetSetBlock(false);
}

NetConnectSocket::~NetConnectSocket ()
{

}

}
