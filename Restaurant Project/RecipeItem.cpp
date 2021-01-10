#include "RecipeItem.h"
#include "Exception.h"
#include <sstream>

RecipeItem::RecipeItem() :ingredient(nullptr), amount(0U)
{}

RecipeItem::RecipeItem(const std::shared_ptr<Ingredient>& ingredient, const short& amount)
{
	Set_ingredient(ingredient);
	Set_amount(amount);
}

void RecipeItem::Set_ingredient(const std::shared_ptr<Ingredient>& ingredient)
{
	if (ingredient == nullptr)
		throw InvalidArgumentException("Ingredient is nullptr!", __LINE__, __FILE__);

	this->ingredient = ingredient;
}

std::shared_ptr<Ingredient>& RecipeItem::Get_ingredient()
{
	return ingredient;
}

void RecipeItem::Set_amount(const short& amount)
{
	if(amount < 0)
	throw InvalidArgumentException("Amount must be more than -1!", __LINE__, __FILE__);

	this->amount = amount;
}

unsigned short RecipeItem::Get_amount() const
{
	return amount;
}

RecipeItem& RecipeItem::operator = (const RecipeItem& other)
{	
	Set_ingredient(other.ingredient);
	Set_amount(other.amount);

	return *this;
}

std::string RecipeItem::Push_all_data_to_file()
{
	std::stringstream ss;
	ss << ingredient->Push_all_data_to_file();
	ss << "Ingredient Amount: " << Get_amount() << '\n';

	return ss.str();
}

std::string RecipeItem::Push_readable_data_to_file()
{
	std::stringstream ss;
	ss << ingredient->Push_readable_data_to_file();
	ss << Get_amount() << '\n';

	return ss.str();
}

void RecipeItem::Show()
{
	std::cout << "Ingredient Information\n\n";
	Get_ingredient()->Show();
	std::cout << "Ingredient Amount: " << Get_amount() << "\n\n";
}