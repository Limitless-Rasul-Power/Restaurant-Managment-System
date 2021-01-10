#pragma once
#include <string>
#include "Base.h"

class Ingredient : public Base
{

protected:
	std::string name;
	float fat;
	float protein;
	float carbonhydrat;
	unsigned short kcal;
	float price;

public:

	static unsigned int ingredient_id;

	Ingredient();

	Ingredient(const std::string& name, const float& fat, const float& protein, const float& carbonhydrat, const short& kcal, const float& price);

	void Set_name(const std::string& name);
	std::string Get_name() const;

	void Set_fat(const float& fat);
	float Get_fat() const;

	void Set_protein(const float& protein);
	float Get_protein() const;

	void Set_carbonhydrat(const float& carbonhydrat);
	float Get_carbonhydrat() const;

	void Set_kcal(const short& kcal);
	unsigned short Get_kcal() const;

	void Set_price(const float& price);
	float Get_price() const;

	std::string Push_all_data_to_file();
	std::string Push_readable_data_to_file();

	static unsigned int Get_current_id();

	void Show() const;
};