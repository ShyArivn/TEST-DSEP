/*
* shyarivn.
*
*
* Version: 1.0
*
* Authors:
*	shyarivn - shyarivn@gmail.com
*/

#ifndef _NET_STREAM_H_
#define _NET_STREAM_H_

namespace netlib {

class NetStream
{

public:
	NetStream(NetConnection *connection);

	virtual ~NetStream() {};

	virtual bool ReadStream(){return true;}

	virtual bool WriteStream(){return true;}

	virtual void CloseStream();

	int GetStreamState();

	void SetStreamState(int state);

	void SetHandleStream(NetHandleBuffer *handlebuffer);

protected:

	int _State;
	NetConnection *_Connection;
	NetDoubleBuffer _DoubleBuffer;
};

}

#endif
