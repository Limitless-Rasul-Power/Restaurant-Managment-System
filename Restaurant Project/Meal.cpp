#include "Meal.h"
#include "Exception.h"
#include "File_Helper.h"
#include <fstream>
#include <sstream>

#define INVALID_ID -1;

Meal::Meal() :items(NULL), name(""), category(""), rating(0.0f), rating_count(1U)
{}

Meal::Meal(const std::vector<std::shared_ptr<RecipeItem>>& items, const std::string& name, const std::string& category,
	const float& rating)
	: Base(++meal_id), rating_count(1U)
{
	Set_items(items);
	Set_name(name);
	Set_rating(rating);
	Set_category(category);
}

void Meal::Set_items(const std::vector<std::shared_ptr<RecipeItem>>& items)
{
	this->items = items;
}

std::vector<std::shared_ptr<RecipeItem>>& Meal::Get_items()
{
	return items;
}

void Meal::Add_item(const std::shared_ptr<RecipeItem>& added_item, const short& amount)
{
	int index = Is_item_name_exists(added_item->Get_ingredient()->Get_name());

	if (index < 0)
	{
		Get_items().emplace_back(added_item);
		Get_items()[Get_items().size() - 1]->Set_amount(amount);
	}
	else
		Get_items()[index]->Set_amount(Get_items()[index]->Get_amount() + amount);
}

void Meal::Set_name(const std::string& name)
{
	if (name.empty())
		throw InvalidArgumentException("Name is Empty!", __LINE__, __FILE__);

	this->name = name;
}

std::string  Meal::Get_name() const
{
	return name;
}

void Meal::Set_category(const std::string& category)
{
	if (category.empty())
		throw InvalidArgumentException("Category is Empty!", __LINE__, __FILE__);

	this->category = category;
}

std::string Meal::Get_category() const
{
	return category;
}

void Meal::Set_rating(const float& rating)
{
	if (rating < 0.0f || rating > 5.0f)
		throw InvalidArgumentException("Rating must be between 0 - 5!", __LINE__, __FILE__);

	this->rating_count = 1U;
	this->rating = rating;
}

float Meal::Get_rating() const
{
	return rating;
}

void Meal::Increase_rating(const float& increase)
{
	++this->rating_count;
	this->rating += increase;
}

unsigned short Meal::Get_rating_count() const
{
	return rating_count;
}


float Meal::Get_max_fat()
{
	float max_fat{ 0.0f };
	size_t length = Get_items().size();

	for (size_t i = 0ui64; i < length; i++)
		max_fat += Get_items()[i]->Get_ingredient()->Get_fat();

	return max_fat;
}

float Meal::Get_max_protein()
{
	float max_protein{ 0.0f };
	size_t length = Get_items().size();

	for (size_t i = 0ui64; i < length; i++)
		max_protein += Get_items()[i]->Get_ingredient()->Get_protein();

	return max_protein;
}

float Meal::Get_max_carbohydrat()
{
	float max_carbonhydrat{ 0.0f };
	size_t length = Get_items().size();

	for (size_t i = 0ui64; i < length; i++)
		max_carbonhydrat += Get_items()[i]->Get_ingredient()->Get_carbonhydrat();

	return max_carbonhydrat;
}

unsigned short Meal::Get_max_kcal()
{
	unsigned short max_kcal{ 0U };
	size_t length = Get_items().size();

	for (size_t i = 0ui64; i < length; i++)
		max_kcal += Get_items()[i]->Get_ingredient()->Get_kcal();

	return max_kcal;
}

unsigned short Meal::Get_max_amount()
{
	unsigned short max_amount{ 0U };

	size_t length = Get_items().size();

	for (size_t i = 0ui64; i < length; i++)
		max_amount += Get_items()[i]->Get_amount();

	return max_amount;
}

float Meal::Get_meal_price()
{
	float meal_price{ 0.0f };
	size_t length = Get_items().size();

	for (size_t i = 0ui64; i < length; i++)
		meal_price += (static_cast<float>(Get_items()[i]->Get_amount()) * Get_items()[i]->Get_ingredient()->Get_price());

	return meal_price;
}

void Meal::Show_all_Meal_value()
{
	std::cout << "All Meal Protein: " << Get_max_protein() << " gr\n";
	std::cout << "All Meal Fat: " << Get_max_fat() << " gr\n";
	std::cout << "All Meal Carbohydrat: " << Get_max_carbohydrat() << " gr\n";
	std::cout << "All Meal Kcal: " << Get_max_kcal() << " kcal\n";
	std::cout << "All Ingredient Amount: " << Get_max_amount() << " gr\n";
	std::cout << "All Meal Ingredient Price: " << Get_meal_price() << " $\n\n";
}

unsigned int Meal::Get_current_id()
{
	return meal_id;
}

int Meal::Is_item_name_exists(const std::string& ingredient_name)
{
	size_t length = Get_items().size();
	for (size_t i = 0ui64; i < length; i++)
		if (ingredient_name == Get_items()[i]->Get_ingredient()->Get_name())
			return i;

	return INVALID_ID;
}

std::string Meal::Push_all_data_to_file()
{
	std::stringstream ss;
	size_t length = Get_items().size();
	for (size_t i = 0; i < length; i++)
		ss << Get_items()[i]->Push_all_data_to_file() << "\n\n";

	ss << "Meal ID: " << Get_id() << '\n'
		<< "Meal Name: " << Get_name() << '\n'
		<< "Meal Category: " << Get_category() << '\n'
		<< "Meal rating: " << (Get_rating() / static_cast<float>(Get_rating_count())) << '\n';

	return ss.str();
}

std::string Meal::Push_more_data_to_file()
{
	std::stringstream ss;
	size_t length = Get_items().size();
	for (size_t i = 0; i < length; i++)
		ss << Get_items()[i]->Push_readable_data_to_file() << "\n\n";

	ss << Get_max_protein() << '\n' << Get_max_fat() << '\n' << Get_max_carbohydrat() << '\n'
		<< Get_max_kcal() << '\n' << Get_max_amount() << '\n' << Get_meal_price() << "\n\n";

	ss << Get_id() << '\n'
		<< Get_name() << '\n'
		<< Get_category() << '\n'
		<< (Get_rating() / static_cast<float>(Get_rating_count())) << '\n';

	return ss.str();
}

std::string Meal::Push_less_data_to_file()
{
	std::stringstream ss;
	ss << Get_id() << '\n'
		<< Get_name() << '\n'
		<< Get_category() << '\n'
		<< (Get_rating() / static_cast<float>(Get_rating_count())) << '\n' << Get_meal_price() << '\n';

	return ss.str();
}

bool Meal::operator > (const Meal& meal) const
{
	return (this->Get_rating() / static_cast<float>(this->Get_rating_count())) > (meal.Get_rating() / static_cast<float>(meal.Get_rating_count()));
}

void Meal::Show_summary_of_the_meal()
{
	std::cout << "Meal ID: " << Get_id() << ", Name: " << Get_name() << ", Category: "\
		<< Get_category() << ", Rating: " << Get_rating() / static_cast<float>(Get_rating_count()) << ", Price: "\
		<< Get_meal_price() << " $\n\n";
}


void Meal::Show()
{
	size_t length = Get_items().size();
	for (size_t i = 0ui64; i < length; i++)
	{
		std::cout << "#" << i + 1 << ", ";
		Get_items()[i]->Show();
	}
	Show_all_Meal_value();
	std::cout << "\n\nMeal ID: " << Get_id() << '\n';
	std::cout << "Meal Name: " << Get_name() << '\n';
	std::cout << "Meal Category: " << Get_category() << '\n';
	std::cout << "Meal Price: " << Get_meal_price() << '\n';
	std::cout << "Meal Rating: " << Get_rating() / Get_rating_count() << " of the 5 stars\n\n";
}