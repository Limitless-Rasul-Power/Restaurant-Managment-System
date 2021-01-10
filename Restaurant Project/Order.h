#pragma once
#include <iostream>
#include "Meal.h"
#include "Base.h"

class Order : public Base
{

private:
	std::string table_no;
	std::shared_ptr<Meal> meal;
	unsigned short amount;

public:

	static unsigned int order_id;

	Order();

	Order(const std::shared_ptr<Meal>& meal, const short& amount);

	void Set_table_no(const std::string& table_no);
	std::string Get_table_no() const;

	void  Set_meal(const std::shared_ptr<Meal>& meal);
	std::shared_ptr<Meal>& Get_meal();

	void Set_amount(const short& amount);
	unsigned short Get_amount() const;

	void Show();
};