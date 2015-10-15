

#ifndef _MESSAGE_H_
#define _MESSAGE_H_

#include <iostream.h>
#include "types/sstr.h"

namespace message {

typedef unsigned short MessageQueueID;
typedef unsigned long MessageID;
typedef unsigned int MessageLen;

enum MessageType
{
	ON_PING_MESSAGE = 0,
	ON_REGISTER_MESSAGE,
	ON_DATA_MESSAGE,
}

class Message
{

protected:
	typedef struct MessageHeader{
		MessageQueueID _MqID;
		MessageID _MessageID;
		MessageType _MessageType;
		bool _IsReply;
	} _MessageHeader;

public:
	Message();
	Message(const char *str);
	Message(const string& str);
	Message(const Message &message);
	Message(const Sstr &str);
	virtual ~Message();

	// 判断是发送or接收
	bool IsReply();
	// message填充数据
	void SetMessageData(Sstr &str);
	// 设置发送or接收
	void SetIsReply(bool reply);
	// 获取消息长度
	MessageLen GetMessageLen();
	// 获取消息id
	MessageID GetMessageID();
	// 设置消息类型
	void SetMessageType(MessageType type);
	// 设置消息队列ID
	void SetMessageQueueID(MessageQueueID mqid);

private:
	MessageID _GenerateMessageId();
	Sstr _MessageData;
	MessageOper *_MessageOper;
	
};

class PingMessage : public Message
{

public:
	PingMessage(MessageQueueID mqid, bool reply, Sstr &data)
	{
		SetMessageQueueID(mqid);
		SetIsReply(reply);
		SetMessageType(ON_PING_MESSAGE);
	}
	~PingMessage()
	{

	}
};

class DataMessage : public Message
{
public:
	DataMessage(MessageQueueID mqid, bool reply, Sstr &data)
	{
		SetMessageQueueID(mqid);
		SetIsReply(reply);
		SetMessageType(ON_DATA_MESSAGE);
	}
	~DataMessage()
	{

	}
};


}

#endif
