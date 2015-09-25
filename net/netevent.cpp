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

NetEvent::NetEvent ( )
{
	Maxevents = MAX_EVENTS;
}

void NetEvent::wait(ComEvent *events, NetTimeOut &timeout)
{	
	while(true){

		int wait = timeout.ProcessTimeOut();
		int eventnum = eventWait(events, wait);
		if (eventnum == NET_ERR)
		{
			log_error("event wait errors accur:%s\n", strerror(errno));
		}
		for(int i=0;i<eventnum;i++)
		{
			NetIoCom* iocom = events[i].iocom;
			if ( iocom == NULL ){
				log_error("io error :%s\n", strerror(errno));
				iocom->Destroy();
			}
			if (IsState(iocom->GetComDataState(),NET_IOCOMM_ERROR)){
				log_error("io error :%s\n", strerror(errno));
				iocom->Destroy();
			}
			if (IsState(iocom->GetComDataState(),NET_IOCOMM_READ)){
				log_info("io read event ");
				iocom->ProcIoRead();
			}
			if (IsState(iocom->GetComDataState(),NET_IOCOMM_WRITE)){
				log_info("io write event ");
				iocom->ProcIoWrite();
			}
		}
		}
	}
	
}
