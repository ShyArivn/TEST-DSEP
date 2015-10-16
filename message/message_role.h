

#ifndef _MESSAGE_ROLE_H_
#define _MESSAGE_ROLE_H_

#include <map>
#include "types/sstr.h"
#include "message/message.h"

namespace message {


class MessageRole
{

public:
	MessageRole();
	MessageRole()
	~MessageRole();
	std::string GenerateRoleID();

private:
	Sstr _RoleID;
	Sstr _Host;
	unsigned short _Port;
};

class 

class MessageRoleMap
{
public:
	MessageRole * FindRole(std::string map, unsigned short roleId);
private:
	std::map<std::string, util::LinkList> _RoleMap;
};

static MessageRoleMap SMesssageRoleMap;

static MessageRoleMap& GetMessageRoleMap()
{
	return MessageRoleMap;
}

}


#endif