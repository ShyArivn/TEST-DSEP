

#ifndef _MESSAGE_OPER_H_
#define _MESSAGE_OPER_H_

#include "message/message_role.h"
#include "net/netlib.h"

namespace message {

class MessageOper
{
public:
	virtual void PostMessage(Message *message)=0;
	virtual Message *RecvMessage()=0;
};

class MessageDefaultOper : public MessageOper
{
public:
	virtual void PostMessage(MessageRole *role, Message *message)
	{

	}

	virtual Message *RecvMessage()
	{

	}

};

class MessageNetOper : public MessageOper, public netlib::NetHandleBuffer
{

public:
	virtual void PostMessage(MessageRole *role, Message *message)
	{

	}

	virtual Message *RecvMessage()
	{

	}

};



class MessageOperFactory
{
public:
	MessageOperFactory(){}
	~MessageOperFactory(){}
	void CreateMessageOper(){
		return new MessageDefaultOper();
	}
};

}


#endif