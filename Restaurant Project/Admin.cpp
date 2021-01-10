#include <iostream>
#include "Admin.h"
#include "Exception.h"
#include "Encrypt.h"
#include "File_Helper.h"
#include <sstream>

Admin::Admin() :user_name(""), password(0U)
{}

Admin::Admin(const std::string& user_name, const std::string& password)
	:Base(++admin_id)
{
	Set_user_name(user_name);
	Set_password(password);
}

void Admin::Set_user_name(const std::string& user_name)
{
	if (user_name.empty())
		throw InvalidArgumentException("User Name is Empty!", __LINE__, __FILE__);

	this->user_name = user_name;
}

std::string Admin::Get_user_name() const
{
	return user_name;
}

void Admin::Set_password(const std::string& password)
{
	if (password.empty())
		throw InvalidArgumentException("Password is Empty!", __LINE__, __FILE__);

	this->password = Encrypt::Readable_text(password);
}

size_t Admin::Get_password() const
{
	return password;
}

unsigned int Admin::Get_current_id()
{
	return admin_id;
}

void Admin::Show() const
{
	std::cout << "Admin ID: " << Get_id() << '\n';
	std::cout << "Admin User Name: " << Get_user_name() << '\n';
	std::cout << "Admin Password: " << Get_password() << "\n\n";
}