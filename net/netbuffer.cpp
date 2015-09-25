/*
* (C) 2015
*
*
* Version: 1.0
* Authors:
* 	shyarivn-shyarivn@gmail.com
*/

#include "netlib.h"

namespace netlib {

NetBuffer::NetBuffer ()
{
	_MaxBufferSize = 104857600;
}

NetBuffer::~NetBuffer ()
{
	
}

void NetBuffer::ResetSpace()
{
	memset(_BufferSstr.data(), 0, _BufferSstr.size());
}

Sstr &NetBuffer::GetBufferData()
{
	return _BufferSstr;
}

int NetBuffer::GetBufferDataLen()
{
	return _BufferSstr.size();
}

NetPacket *NetBuffer::GetBufferPacket()
{
	return &_Packet;
}

NetHandleBuffer *NetBuffer::GetHandleBuffer()
{
	return _HandleBuffer;
}

void NetBuffer::SetHandleBuffer(NetHandleBuffer *handlebuffer, NetIoCom *iocom)
{	
	_HandleBuffer = handlebuffer;
	_Iocom = iocom;
}

void NetBuffer::BufferRead(Sstr &sstr)
{
	int headersize = _Packet.GetPacketHeaderSize();
	sstr.append(_BufferSstr.data()+headersize, _BufferSstr.size()-headersize);
	_Packet.Decode(sstr);
}

void NetBuffer::BufferWrite(Sstr &sstr)
{
	_Packet.SetPacketHeader(0, 0, sstr.size());
	log_info("UnParsePacketHeader before\n");
	_Packet.UnParsePacketHeader(_BufferSstr);
	_Packet.Encode(sstr);
	log_info("BufferWrite before");
	_BufferSstr.append(sstr.data(), sstr.size());
	log_info("BufferWrite after");
	_Iocom->GetEvent()->modIoEvent(_Iocom->GetSocket(), true, true);
	NetStream *streamer = _Iocom->GetConnection()->GetIoStream();
	streamer->SetStreamState(NET_WRITE_READY);
	//_Iocom->GetServer()->GetTimeOut()->DelTimeOut(_Iocom->GetTimeOut());
}

}

