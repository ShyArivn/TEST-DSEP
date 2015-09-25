/*
* (C) 2015
*
*
* Version: 1.0
* Authors:
* 	shyarivn-shyarivn@gmail.com
*/


#ifndef _NET_BUFFER_H_
#define _NET_BUFFER_H_

namespace netlib {

class NetBuffer
{

public:
	NetBuffer();
	NetBuffer(int buffersize);
	~NetBuffer();

	void ResetSpace();
	char *GetFreeSpace(int bytes);
	Sstr &GetBufferData();
	int GetBufferDataLen();
	NetPacket *GetBufferPacket();
	NetHandleBuffer *GetHandleBuffer();
	void SetHandleBuffer(NetHandleBuffer *handlebuffer, NetIoCom *iocom);

	void BufferRead(Sstr &sstr);
	void BufferWrite(Sstr &sstr);
	
private:
	int _MaxBufferSize;
	Sstr _BufferSstr;
	NetPacket _Packet;
	NetHandleBuffer *_HandleBuffer;
	NetIoCom *_Iocom;
};

}

#endif
