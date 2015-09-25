/*
* (C) 2015
*
*
* Version: 1.0
* Authors:
* 	shyarivn-shyarivn@gmail.com
*/


#ifndef _NET_PACKET_H_
#define _NET_PACKET_H_

namespace netlib {
// packetid|packettype|packetlen|data|crc32
struct NetPacketHeader
{
	int32_t _PacketId;
	int32_t _PacketType;
	int32_t _PacketDataLength;

	int32_t GetPacketId(){ return _PacketId; }
	int32_t GetPacketType(){ return _PacketType; }
	int32_t GetPacketDataLength(){ return _PacketDataLength;}
	void SetPacketId(int32_t packetid){ _PacketId = packetid; }
	void SetPacketType(int32_t packettype) {_PacketType = packettype;}
	void SetPacketLen(int32_t packetlen) { _PacketDataLength = packetlen; }
};

struct NetPacketTailer
{
int32_t _Crc32;

};

class NetPacket
{
public:
	NetPacket();
	virtual ~NetPacket() {};

	virtual Sstr& Encode(Sstr &sstr);
	virtual Sstr& Decode(Sstr &sstr);

	bool ParsePacketHeader(Sstr &packet);
	int GetPacketDataLength();

	int GetBufferDataLength(Sstr &buffer);
	int GetPacketHeaderSize();
	NetPacketHeader &GetPacketHeader();
	void UnParsePacketHeader(Sstr &packet);
	bool RemovePacketHeader(Sstr &packet);
	void SetPacketHeader(int32_t packetid, int32_t packettype, int32_t packetlen);
private:
	NetPacketHeader _PacketHeader;
	NetPacketTailer _PacketTailer;
};

}

#endif
