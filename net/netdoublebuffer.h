
#ifndef _NET_DOUBLE_BUFFER_H_
#define _NET_DOUBLE_BUFFER_H_

#include "netbuffer.h"

namespace netlib {
class NetDoubleBuffer
{
public:

	NetDoubleBuffer();
	~NetDoubleBuffer();
	NetBuffer *GetInputBuffer();
	NetBuffer *GetOutputBuffer();

private:
	
	NetBuffer _InBuffer;
	NetBuffer _OutBuffer;

};

}

#endif
