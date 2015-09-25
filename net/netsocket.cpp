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

NetSocket::NetSocket ( )
{
	_Socketfd = socket( AF_INET, SOCK_STREAM, 0 );
}

NetSocket::NetSocket ( int fd )
{
	_Socketfd = fd;
}

void NetSocket::NetSetIoCom ( NetIoCom *iocom )
{
	_Iocom = iocom;
}

NetIoCom *NetSocket::NetSocketIoCom()
{
	return _Iocom;
}
int NetSocket::NetSocketfd ()
{
	return _Socketfd;
}

bool NetSocket::NetConnect()
{
	
	if(connect(_Socketfd, (struct sockaddr *)&_Addr, sizeof(_Addr))!=0){
		return false;
	}
	return true;

}

void NetSocket::NetSetSocketfd(int fd)
{
	_Socketfd = fd;
}

bool NetSocket::NetClose()
{
	if(close(_Socketfd)!=0){
		return false;
	}
	delete this;
	return true;
}

ssize_t NetSocket::NetRead(Sstr &data)
{
	ssize_t bytes, ret=0;
	char buf[CHUNKSIZE];
	do{
		bytes = read(_Socketfd, buf, CHUNKSIZE);
		if(bytes == 0){
			return ret;
		}else if(bytes < 0){
			if(errno == EAGAIN){
				return ret;
			}else{
				return -1;
			}
		}
		data.append(buf, bytes);
		ret += bytes;
	}while(bytes > 0 || errno == EINTR);
	return ret;
}

ssize_t NetSocket::NetWrite(Sstr &data)
{
	ssize_t bytes, ret = 0;
	char *cur = data.data();
	ssize_t cursize = data.size();
	do {
		bytes = write(_Socketfd, cur, cursize);
		if(bytes<0){
			if(errno == EAGAIN){
				return ret;
			}else{
				return -1;
			}
		}
		cur += bytes;
		cursize -= bytes;
		ret += bytes;
	}while(cursize > 0 || errno == EINTR);
	return ret;
}

bool NetSocket::NetSetKeepAlive(bool on)
{
	return true;
}

bool NetSocket::NetSetBlock(bool on)
{
	long sock_flag = fcntl(_Socketfd, F_GETFL, NULL);
	if(sock_flag < 0){
		return false;
	}
	if(on) {
		sock_flag &= ~O_NONBLOCK;
	}else{
		sock_flag |= O_NONBLOCK;
	}

	int ret = fcntl(_Socketfd, F_SETFL, sock_flag);
	fprintf(stdout, "errno:%s\n", strerror(errno));
	if(ret < 0){
		return false;
	}
	return true;
}

bool NetSocket::NetSetReusePort(bool on){
	//int optval;
	/*if(on){
		if(setsockopt(_Socketfd, SOL_SOCKET, SO_REUSEPORT, (const void*)&optval,sizeof(optval))<0){
			return false;
		}
	}*/
	return true;
}

void NetSocket::NetSetSockAddr(struct sockaddr_in *sa)
{
	memcpy(&_Addr, sa, sizeof(_Addr));
}

bool NetSocket::NetSetReuseAddress(bool on){
	return true;
}

bool NetSocket::NetSetAddress(const char *addr, const int port)
{
	bzero(&_Addr, sizeof(_Addr));
	_Addr.sin_family = AF_INET;
	_Addr.sin_addr.s_addr = inet_addr(addr);
	_Addr.sin_port = htons(port);
	return true;
}

}
