#pragma once
#include "Table.h"
#include "Admin.h"

class Restaurant
{

private:
	std::string name;
	std::string address;
	std::string city;
	float budget{ 0.0f };
	
	std::vector<std::shared_ptr<Admin>> admins;
	std::vector<std::shared_ptr<Table>> tables;

public:

	Restaurant();

	explicit Restaurant(const std::string& name);

	Restaurant(const std::string& name, const std::string& address);

	Restaurant(const std::string& name, const std::string& address, const std::string& city);

	Restaurant(const std::string& name, const std::string& address, const std::string& city, const
		std::vector<std::shared_ptr<Admin>>& admins);

	Restaurant(const std::string& name, const std::string& address, const std::string& city, const
		std::vector<std::shared_ptr<Admin>>& admins, const std::vector<std::shared_ptr<Table>>& tables);

	void Set_name(const std::string& name);
	std::string Get_name() const;

	void Set_address(const std::string& address);
	std::string Get_address() const;

	void Set_city(const std::string& city);
	std::string Get_city() const;

	void Set_budget(const float& budget);
	float Get_budget() const;

	void Set_tables(const std::vector<std::shared_ptr<Table>>& tables);
	std::vector<std::shared_ptr<Table>>& Get_tables();

	void Set_order_in_the_table(const std::shared_ptr<Table>& table, const std::shared_ptr<Order>& order);
	int Is_ordered_meal_name_exist_in_the_table(const std::shared_ptr<Table>& table, const std::string& ordered_meal_name);
	void Delete_all_orders_from_tables();
	void Delete_all_orders_from_one_table(const std::shared_ptr<Table>& table);

	void Set_admins(const std::vector<std::shared_ptr<Admin>>& admins);
	std::vector<std::shared_ptr<Admin>>& Get_admins();

	void Show_all_table_names();
	void Show();

};