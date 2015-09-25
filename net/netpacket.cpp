
#include "netlib.h"
#include "common/varint.h"

namespace netlib {


NetPacket::NetPacket()
{

}

Sstr& NetPacket::Encode(Sstr &data)
{
	return data;
}

Sstr& NetPacket::Decode(Sstr &data)
{
	return data;
}

int NetPacket::GetPacketHeaderSize()
{
	return sizeof(_PacketHeader);
}

bool NetPacket::ParsePacketHeader(Sstr &packet)
{
	if(packet.size() < GetPacketHeaderSize()){
		return false;
	}else{
		char *curpos = packet.data();
		_PacketHeader._PacketId = ReadVarInt32(curpos);
		_PacketHeader._PacketType = ReadVarInt32(curpos+4);
		_PacketHeader._PacketDataLength	= ReadVarInt32(curpos+8);
		return true;
	}
}

void NetPacket::UnParsePacketHeader(Sstr &packet)
{
	char temp[12];
	PutVarInt32((char*)temp, &_PacketHeader._PacketId);
	PutVarInt32((char*)temp+4, &_PacketHeader._PacketType);
	PutVarInt32((char*)temp+8, &_PacketHeader._PacketDataLength);
	packet.append((char*)temp, sizeof(temp));
}

int NetPacket::GetPacketDataLength()
{
	return _PacketHeader._PacketDataLength;
}

int NetPacket::GetBufferDataLength(Sstr &packet)
{
	return packet.size()-GetPacketHeaderSize();
}

NetPacketHeader &NetPacket::GetPacketHeader()
{
	return _PacketHeader;
}

void NetPacket::SetPacketHeader(int32_t packetid, int32_t packettype, int32_t packetlen)
{
	_PacketHeader.SetPacketId(packetid);
	_PacketHeader.SetPacketType(packettype);
	_PacketHeader.SetPacketLen(packetlen);

}

}
