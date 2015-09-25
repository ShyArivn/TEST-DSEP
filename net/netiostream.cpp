/*
* shyarivn.
*
*
* Version: 1.0
*
* Authors:
*	shyarivn - shyarivn@gmail.com
*/

#include "netlib.h"

namespace netlib {

NetIoStream::NetIoStream ( NetConnection *connection ):NetStream(connection)
{
}

NetIoStream::~NetIoStream ()
{

}

bool NetIoStream::ReadStream ()
{
	
	if (IsState(_Connection->GetConnState() ,NET_CON_CONNECT )) 
	{
		NetSocket *sock = _Connection->GetConnSock();

		NetBuffer* inputbuffer = _DoubleBuffer.GetInputBuffer();
		NetBuffer* outputbuffer = _DoubleBuffer.GetOutputBuffer();

		NetPacket* packet = inputbuffer->GetBufferPacket();

		int bytes = sock->NetRead(inputbuffer->GetBufferData());
		if ( bytes > 0 ) 
		{
			if(IsState(GetStreamState(), NET_ORIGIN))
			{
				SetStreamState(NET_READING_HEADER);
			}

			if(IsState(GetStreamState(), NET_READING_HEADER))
			{
				bool header = packet->ParsePacketHeader(inputbuffer->GetBufferData());

				if(!header)
				{	
					SetStreamState(NET_READING_HEADER);
					return true;
				}
				SetStreamState(NET_FINISH_HEADER);

			}

			if(IsState(GetStreamState(), NET_FINISH_HEADER)){

				int DataLen = packet->GetPacketDataLength();
				if (packet->GetBufferDataLength(inputbuffer->GetBufferData()) >= DataLen )
				{
					SetStreamState(NET_FINISH_DATA);
					inputbuffer->GetHandleBuffer()->ProcessBuffer(inputbuffer,outputbuffer);
					return true;
				}
			}
		}else if( bytes == 0 ){
			if(IsState(GetStreamState(), NET_FINISH_WRITE)){
				log_info("finish data:%s\n","ok");
				return false;
			}
		}else if( bytes == -1 ){
			_Connection->SetConnState(NET_CON_DISCONN);
			SetStreamState(NET_ORIGIN);
			return false;
		}
	}
	return false;
}

bool NetIoStream::WriteStream ()
{
	if (IsState(_Connection->GetConnState(), NET_CON_CONNECT))
	{
		NetBuffer* inputbuffer = _DoubleBuffer.GetInputBuffer();
		NetBuffer* outputbuffer = _DoubleBuffer.GetOutputBuffer();

		NetSocket *sock = _Connection->GetConnSock();
		int sstate = GetStreamState();

		int datalen = outputbuffer->GetBufferDataLen();
		if (IsState(sstate,NET_WRITE_READY))
		{
			int ret;
			do{
				ret = sock->NetWrite(outputbuffer->GetBufferData());
				if (ret > 0){
					ret = datalen-ret;
					if(ret == 0){
						SetStreamState(NET_FINISH_WRITE);
						NetEvent* event = _Connection->GetIoCom()->GetEvent();
						event->modIoEvent(_Connection->GetConnSock(), true, false);
						return true;
					}
				}else{
					if(ret == -1){
						_Connection->SetConnState(NET_CON_DISCONN);
						SetStreamState(NET_ORIGIN);
						return false;
					}
				}
			}while( ret > 0 );

		}
	}
	return false;
}

void NetIoStream::CloseStream()
{
	delete this;
}

}

