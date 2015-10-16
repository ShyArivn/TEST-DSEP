

#ifndef _ROLE_REGISTER_H_
#define _ROLE_REGISTER_H_

namespace message {

class RoleRegister
{
public:
	RoleRegister();
	~RoleRegister();

	void RegisterRole(MessageRole *role);	

private:
	std::hash_map<Sstr , MessageRole *> _MessageRoles;
};

static RoleRegister SRoleRegister;

static RoleRegister& GetRoleRegister()
{
	return SRoleRegister;
}

}


#endif
