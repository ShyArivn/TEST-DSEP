/*
* shyarivn.
*
*
* Version: 1.0
*
* Authors:
*	shyarivn - shyarivn@gmail.com
*/

#ifndef _NET_IOSTREAM_H_
#define _NET_IOSTREAM_H_

namespace netlib {

class NetIoStream : public NetStream
{

public:
	
	NetIoStream(NetConnection *connection);
	~NetIoStream();

	bool ReadStream();
	bool WriteStream();
	void CloseStream();
};

}

#endif
