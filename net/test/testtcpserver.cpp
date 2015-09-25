

#include "net/netlib.h"

using namespace netlib;

class Myhandle : public NetHandleBuffer
{
public:
	void ProcessBuffer(NetBuffer *ibuffer, NetBuffer *obuffer)
	{
		Sstr mysstr;
		ibuffer->BufferRead(mysstr);
		fprintf(stdout, "ibuffer :%d\n", mysstr.size());
		obuffer->BufferWrite(mysstr);
	}
};

int main(int argc, char **argv)
{

	log_open("/opt/sysr/sysr.log");
	char addr[] = "10.10.126.72";
	int port = 12345;

	Myhandle *handle = new Myhandle();
	NetTcpServer _tcpserver;
	_tcpserver.addIoServer(addr, port);
	_tcpserver._AddProcessHandler(handle);
	_tcpserver.start();

}
