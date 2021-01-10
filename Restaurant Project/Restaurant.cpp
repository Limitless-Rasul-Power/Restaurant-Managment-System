#include <iostream>
#include "Restaurant.h"
#include "Exception.h"

#define INVALID_CREDENTIAL -1

Restaurant::Restaurant() :name(""), address(""), city(""), budget(0U)
{}

Restaurant::Restaurant(const std::string& name)
{
	Set_name(name);
}

Restaurant::Restaurant(const std::string& name, const std::string& address)
		    :Restaurant(name)
{
	Set_address(address);
}

Restaurant::Restaurant(const std::string& name, const std::string& address, const std::string& city)
	        :Restaurant(name, address)
{
	Set_city(city);
}

Restaurant::Restaurant(const std::string& name, const std::string& address, const std::string& city, const
	std::vector<std::shared_ptr<Admin>>& admins)
	:Restaurant(name, address, city)
{
	Set_admins(admins);
}

Restaurant::Restaurant(const std::string& name, const std::string& address, const std::string& city, const
	std::vector<std::shared_ptr<Admin>>& admins, const std::vector<std::shared_ptr<Table>>& tables)
	:Restaurant(name, address, city, admins)
{
	Set_tables(tables);
}

void Restaurant::Set_name(const std::string& name)
{
	if (name.empty())
		throw InvalidArgumentException("Name is Empty!", __LINE__, __FILE__);

	this->name = name;
}

std::string Restaurant::Get_name() const
{
	return name;
}

void Restaurant::Set_address(const std::string& address)
{
	if(address.empty())
		throw InvalidArgumentException("Address is Empty!", __LINE__, __FILE__);

	this->address = address;
}

std::string Restaurant::Get_address() const
{
	return address;
}

void Restaurant::Set_city(const std::string& city)
{
	if(city.empty())
		throw InvalidArgumentException("City is Empty!", __LINE__, __FILE__);

	this->city = city;
}

std::string Restaurant::Get_city() const
{
	return city;
}

void Restaurant::Set_budget(const float& budget)
{
	if(budget < 0.0f)
		throw InvalidArgumentException("Budget must be more than 0!", __LINE__, __FILE__);

	this->budget += budget;
}
float Restaurant::Get_budget() const
{
	return budget;
}

void Restaurant::Set_tables(const std::vector<std::shared_ptr<Table>>& tables)
{
	this->tables = tables;
}

std::vector<std::shared_ptr<Table>>& Restaurant::Get_tables()
{
	return tables;
}

void Restaurant::Delete_all_orders_from_tables()
{
	size_t length = Get_tables().size();
	for (size_t i = 0Ui64; i < length; i++)
		Get_tables()[i]->Get_orders().erase(Get_tables()[i]->Get_orders().begin(), Get_tables()[i]->Get_orders().end());
}

void Restaurant::Delete_all_orders_from_one_table(const std::shared_ptr<Table>& table)
{
	table->Get_orders().erase(table->Get_orders().begin(), table->Get_orders().end());
}

void Restaurant::Set_order_in_the_table(const std::shared_ptr<Table>& table, const std::shared_ptr<Order>& order)
{
		table->Get_orders().emplace_back(order);
}

int Restaurant::Is_ordered_meal_name_exist_in_the_table(const std::shared_ptr<Table>& table, const std::string& ordered_meal_name)
{
	size_t length = table->Get_orders().size();
	for (size_t i = 0Ui64; i < length; i++)
		if (table->Get_orders()[i]->Get_meal()->Get_name() == ordered_meal_name)
			return i;

	return INVALID_CREDENTIAL;
}

void Restaurant::Set_admins(const std::vector<std::shared_ptr<Admin>>& admins)
{
	this->admins = admins;
}

std::vector<std::shared_ptr<Admin>>& Restaurant::Get_admins()
{
	return admins;
}

void Restaurant::Show_all_table_names()
{
	size_t length = Get_tables().size();
	std::cout << "Table Names: ";
	for (size_t i = 0ui64; i < length - 1; i++)
		std::cout << Get_tables()[i]->Get_table_no() << ",   ";

	std::cout << Get_tables()[length - 1]->Get_table_no() << "\n\n";
}

void Restaurant::Show()
{
	std::cout << "Restaurant Name: " << Get_name() << '\n';
	std::cout << "Restaurant Address: " << Get_address() << '\n';
	std::cout << "Restaurant City: " << Get_city() << '\n';
	std::cout << "Restaurant Budget: " << Get_budget() << " $\n";

	std::cout << "\nRestaurant Tables Inforamtions\n\n";

	size_t length = Get_tables().size();

	for (size_t i = 0Ui64; i < length; i++)
		Get_tables()[i]->Show();

	length = Get_admins().size();

	std::cout << "\n\nRestaurant Admins Inforamtions\n\n";
	for (size_t i = 0ui64; i < length; i++)
		Get_admins()[i]->Show();

}