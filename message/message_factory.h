
#ifndef _MESSAGE_FACTORY_H_
#define _MESSAGE_FACTORY_H_

#include "message/message.h"

class MessageFactory
{
public:
	MessageFactory(){}
	~MessageFactory(){}

	Message *CreateMessage(MessageType type, MessageQueueID mqid, bool reply, Sstr &data)
	{
		swith(type){
			case ON_PING_MESSAGE:
				return new PingMessage(mqid, reply, data);
			case ON_DATA_MESSAGE:
				return new DataMessage(mqid, reply, data);
		}
	}
};

#endif