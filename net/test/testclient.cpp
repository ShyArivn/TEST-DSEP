
#include "net/netlib.h"
#include "common/varint.h"
#include <unistd.h>

using namespace netlib;

int main(int argc, char **argv)
{
	char *host = "10.10.126.72";
	int port = 12345;
	
	struct sockaddr_in sa;
	sa.sin_family = AF_INET;
	sa.sin_port = htons(port);
	sa.sin_addr.s_addr = inet_addr(host);

	int fd = socket(AF_INET, SOCK_STREAM, 0);
	connect(fd, (struct sockaddr *)&sa, sizeof(sa));
	char *message = "testdatatestdatatestdata";
	fprintf(stdout, "send message:%s\n", message);
	fprintf(stdout, "send message len:%d\n", sizeof(message));
	NetPacketHeader _packetheader;
	_packetheader._PacketId = 12;
	_packetheader._PacketType = 1;
	_packetheader._PacketDataLength = 24;
	char mm[50];
	char tmp[12];
	PutVarInt32(tmp, &_packetheader._PacketId);
	PutVarInt32(tmp+4, &_packetheader._PacketType);
	PutVarInt32(tmp+8, &_packetheader._PacketDataLength);
	memcpy(mm, tmp, 12);
	memcpy(mm+12, message, 24);
	write(fd, mm, 36);
	memset(mm, 0 ,50);
	read(fd, mm, 50);
	fprintf(stdout, "read data from fd:%s\n", mm);
	close(fd);


}
