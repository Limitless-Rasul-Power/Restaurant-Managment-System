#pragma once
#include "RecipeItem.h"
#include <vector>

#define INVALID_ID -1;

class Stock
{

private:
	std::vector<std::shared_ptr<RecipeItem>> items;

public:

	Stock();

	Stock(const std::vector<std::shared_ptr<RecipeItem>>& items);

	void Set_items(const std::vector<std::shared_ptr<RecipeItem>>& items);
	std::vector<std::shared_ptr<RecipeItem>>& Get_items();


	void Add_item(const std::shared_ptr<RecipeItem>& added_item);
	void Delete_item(const int& id);
	void Delete_all_items();

	void Increase_ingredient_amount(const std::shared_ptr<RecipeItem>& item, const short& amount);
	void Decrease_ingredient_amount(const std::shared_ptr<RecipeItem>& item, const short& amount);

	int Is_item_id_exist(const int& id);
	bool Is_item_amount_exist(const int& index, const short& amount);
	int Is_item_name_exists(const std::string& item_name);

	void Push_all_data_to_file();
	void Push_readable_data_to_file();

	void Show();
};