#include "Table.h"
#include "Exception.h"

#define INVALID_CREDENTIAL -1;

Table::Table() :table_no(""), orders(NULL), message_from_kitchen("")
{}

Table::Table(const std::string& table_no)
	:Base(++table_id)
{
	Set_table_no(table_no);
}

void Table::Set_table_no(const std::string& table_no)
{
	if (table_no.empty())
		throw InvalidArgumentException("Table No is Empty!", __LINE__, __FILE__);

	this->table_no = table_no;
}

std::string Table::Get_table_no() const
{
	return table_no;
}

std::vector<std::shared_ptr<Order>>& Table::Get_orders()
{
	return orders;
}

void Table::Delete_order_with_meal_name_and_amount(const std::string& meal_name, const int& amount)
{
	int index = Is_correct_order_credential(meal_name, amount);

	if (index >= 0)
		Get_orders().erase(Get_orders().begin() + index);

}

int Table::Is_correct_order_credential(const std::string meal_name, const int& amount)
{
	for (size_t i = 0Ui64; i < Get_orders().size(); i++)
		if (meal_name == Get_orders()[i]->Get_meal()->Get_name() && amount == Get_orders()[i]->Get_amount())
			return i;

	return INVALID_CREDENTIAL;
}

void Table::Set_message_from_kitchen(const std::string& message_from_kitchen)
{
	if (message_from_kitchen == "")
		this->message_from_kitchen = message_from_kitchen;
	else
	this->message_from_kitchen.append('\n' + message_from_kitchen + '\n');
}

std::string Table::Get_message_from_kitchen() const
{
	return message_from_kitchen;
}

void Table::Show()
{
	std::cout << "Tabled ID: " << Get_id() << '\n';
	std::cout << "Table No: " << Get_table_no() << "\n\n";

	size_t length = Get_orders().size();
	if (length > 0ui64)
	{
		std::cout << "Table Orders Information\n\n";
		for (size_t i = 0Ui64; i < length; i++)
			Get_orders()[i]->Show();
	}

	if (!Get_message_from_kitchen().empty())
		std::cout << "Message from Kitchen: " << Get_message_from_kitchen() << "\n\n";
	else
		std::cout << "Table has no message from Kitchen!\n\n";
}