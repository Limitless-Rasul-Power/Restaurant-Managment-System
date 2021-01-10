#pragma once
#include "Base.h"
#include <string>
#include <vector>
class Admin : public Base
{

private:
	std::string user_name;
	size_t password;

public:

	static unsigned int admin_id;

	Admin();

	Admin(const std::string& user_name, const std::string& password);

	void Set_user_name(const std::string& user_name);	
	std::string Get_user_name() const;

	void Set_password(const std::string& password);
	size_t Get_password() const;


	static unsigned int Get_current_id();

	void Show() const;
};