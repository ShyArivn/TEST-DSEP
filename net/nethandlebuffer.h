

#ifndef _NET_HANDLEBUFFER_H_
#define _NET_HANDLEBUFFER_H_

#include "netbuffer.h"

namespace netlib {

class NetHandleBuffer
{

public:
	NetHandleBuffer(){}
	virtual ~NetHandleBuffer(){}
	virtual void ProcessBuffer(NetBuffer *ibuffer, NetBuffer *obuffer)=0;

};

}

#endif
