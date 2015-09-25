

#include "netlib.h"

namespace netlib {

NetDoubleBuffer::NetDoubleBuffer()
{

}
NetDoubleBuffer::~NetDoubleBuffer()
{

}

NetBuffer *NetDoubleBuffer::GetInputBuffer()
{
	return &_InBuffer;
}
NetBuffer *NetDoubleBuffer::GetOutputBuffer()
{
	return &_OutBuffer;
}



}
