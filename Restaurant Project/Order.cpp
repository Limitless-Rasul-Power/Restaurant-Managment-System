#include "Order.h"
#include "Exception.h"

Order::Order() :table_no(""), meal(nullptr), amount(0U)
{}

Order::Order(const std::shared_ptr<Meal>& meal, const short& amount)
	:Base(++order_id)
{
	Set_meal(meal);
	Set_amount(amount);
}

void Order::Set_table_no(const std::string& table_no)
{
	if (table_no.empty())
		throw InvalidArgumentException("Table No is Empty!", __LINE__, __FILE__);

	this->table_no = table_no;
}

std::string Order::Get_table_no() const
{
	return table_no;
}

void Order::Set_meal(const std::shared_ptr<Meal>& meal)
{
	if (meal == nullptr)
		throw InvalidArgumentException("Meal is nullptr!", __LINE__, __FILE__);

	this->meal = meal;
}

std::shared_ptr<Meal>& Order::Get_meal()
{
	return meal;
}

void Order::Set_amount(const short& amount)
{
	if (amount <= 0U)
		throw InvalidArgumentException("Amount must be more than 0!", __LINE__, __FILE__);

	this->amount = amount;
}

unsigned short Order::Get_amount() const
{
	return amount;
}

void Order::Show()
{
	if (!Get_table_no().empty())
	{
		std::cout << "Table No_" << Get_table_no() << '\n';
		std::cout << "Order ID: " << Get_id() << '\n';
		std::cout << "Ordered Meal Information\n\n";
		std::cout << "Ordered Meal Amount: " << Get_amount() << '\n';
		Get_meal()->Show();
	}
}