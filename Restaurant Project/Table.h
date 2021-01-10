#pragma once
#include "Order.h"

class Table : public Base
{

private:
	std::string table_no;
	std::vector<std::shared_ptr<Order>> orders;
	std::string message_from_kitchen;

public:

	static unsigned int table_id;

	Table();

	Table(const std::string& table_no);

	void Set_table_no(const std::string& table_no);
	std::string Get_table_no() const;

	std::vector<std::shared_ptr<Order>>& Get_orders();
	void Delete_order_with_meal_name_and_amount(const std::string& meal_name, const int& amount);
	int Is_correct_order_credential(const std::string meal_name, const int& amount);

	void Set_message_from_kitchen(const std::string& message_from_kitchen);
	std::string Get_message_from_kitchen() const;

	void Show();

};