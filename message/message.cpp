

#include "message/message.h"

namespace message {

Message::Message()
{
	SetMessageID(_GenerateMessageID());
}

Message::Message(const char *str)
{
	_MessageData(str, sizeof(str));
}

Message::Message(const string &str)
{
	_MessageData(str.c_str(), str.len());
}

Message::Message(const Sstr &sstr)
{
	_MessageData(sstr);
}

bool Message::IsReply()
{
	return _MessageHeader._IsReply;
}
void Message::SetMessageData(Sstr &str)
{
	_MessageData(sstr);
}
void Message::SetIsReply(bool reply)
{
	_MessageHeader._IsReply = reply;
}

MessageLen Message::GetMessageLen()
{
	return _MessageData.size();
}
MessageID Message::GetMessageID()
{
	return _MessageHeader.__MessageID;
}

}


