#pragma once
#include "RecipeItem.h"
#include "Base.h"
#include <vector>

class Meal : public Base
{

protected:
	std::vector<std::shared_ptr<RecipeItem>> items;
	std::string name;
	std::string category;
	float rating;
	unsigned short rating_count;

public:

	static unsigned int meal_id;

	Meal();

	Meal(const std::vector<std::shared_ptr<RecipeItem>>& items, const std::string& name, const std::string& category, const float& rating);

	void Set_items(const std::vector<std::shared_ptr<RecipeItem>>& items);
	std::vector<std::shared_ptr<RecipeItem>>& Get_items();
	void Add_item(const std::shared_ptr<RecipeItem>& added_item, const short& amount);

	void Set_name(const std::string& name);
	std::string  Get_name() const;

	void Set_category(const std::string& category);
	std::string Get_category() const;

	void Set_rating(const float& rating);
	float Get_rating() const;

	void Increase_rating(const float& increase);
	unsigned short Get_rating_count() const;

	float Get_max_fat();
	float Get_max_protein();
	float Get_max_carbohydrat();

	unsigned short Get_max_kcal();
	unsigned short Get_max_amount();

	float Get_meal_price();

	void Show_all_Meal_value();

	static unsigned int Get_current_id();

	int Is_item_name_exists(const std::string& item_name);

	std::string Push_all_data_to_file();
	std::string Push_more_data_to_file();
	std::string Push_less_data_to_file();

	bool operator > (const Meal& meal) const;

	void Show_summary_of_the_meal();
	void Show();
};