#pragma once
#include <iostream>
#include "Ingredient.h"

class RecipeItem
{

private:
	std::shared_ptr<Ingredient> ingredient;
	unsigned short amount;
	
public:

	RecipeItem();

	RecipeItem(const std::shared_ptr<Ingredient>& ingredient, const short& amount);

	void Set_ingredient(const std::shared_ptr<Ingredient>& ingredient);
	std::shared_ptr<Ingredient>& Get_ingredient();

	void Set_amount(const short& amount);
	unsigned short Get_amount() const;

	RecipeItem& operator = (const RecipeItem& other);

	std::string Push_all_data_to_file();
	std::string Push_readable_data_to_file();

	void Show();

};