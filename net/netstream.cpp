/*
* shyarivn
*
*
* Version: 1.0
*
* Authors:
*	shyarivn - shyarivn@gmail.com
*/

#include "netlib.h"

namespace netlib {

NetStream::NetStream (NetConnection *connetion)
{
	_Connection = connetion;
}

int NetStream::GetStreamState()
{
	return _State;
}

void NetStream::SetStreamState(int state)
{
	_State = state;
}

void NetStream::SetHandleStream(NetHandleBuffer *handlebuffer)
{
	_DoubleBuffer.GetInputBuffer()->SetHandleBuffer(handlebuffer, _Connection->GetIoCom());
	_DoubleBuffer.GetOutputBuffer()->SetHandleBuffer(handlebuffer, _Connection->GetIoCom());

}

void NetStream::CloseStream()
{
	delete this;
}


}
