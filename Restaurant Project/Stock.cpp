#include "Stock.h"
#include "File_Helper.h"
#include <fstream>
#include <sstream>

Stock::Stock()
{}

Stock::Stock(const std::vector<std::shared_ptr<RecipeItem>>& items)
{
	Set_items(items);
	Push_all_data_to_file();
	Push_readable_data_to_file();
}

void Stock::Set_items(const std::vector<std::shared_ptr<RecipeItem>>& items)
{
	this->items = items;
}

std::vector<std::shared_ptr<RecipeItem>>& Stock::Get_items()
{
	return items;
}

void Stock::Add_item(const std::shared_ptr<RecipeItem>& added_item)
{
	int index = Is_item_name_exists(added_item->Get_ingredient()->Get_name());

	if(index < 0)
		Get_items().emplace_back(added_item);
	else
	{
		Get_items()[index]->Set_amount(Get_items()[index]->Get_amount() + added_item->Get_amount());
	}
}

void Stock::Delete_item(const int& id)
{
	int index = Is_item_id_exist(id);

	if (index >= 0)
		Get_items()[index]->Set_amount(0U);
}

void Stock::Delete_all_items()
{
	size_t length = Get_items().size();
	for (size_t i = 0ui64; i < length; i++)
		Get_items()[i]->Set_amount(0U);
}

void Stock::Increase_ingredient_amount(const std::shared_ptr<RecipeItem>& item, const short& amount)
{
	item->Set_amount(item->Get_amount() + amount);
}

void Stock::Decrease_ingredient_amount(const std::shared_ptr<RecipeItem>& item, const short& amount)
{
	item->Set_amount(item->Get_amount() - amount);
}

int Stock::Is_item_id_exist(const int& id)
{
	size_t length = Get_items().size();
	for (size_t i = 0U; i < length; i++)
		if (id == Get_items().at(i)->Get_ingredient()->Get_id())
			return i;

	return INVALID_ID;
}

bool Stock::Is_item_amount_exist(const int& index,const short& amount)
{
	return amount <= Get_items()[index]->Get_amount();
}

int Stock::Is_item_name_exists(const std::string& ingredient_name)
{
	size_t length = Get_items().size();
	for (size_t i = 0ui64; i < length; i++)
		if (ingredient_name == Get_items()[i]->Get_ingredient()->Get_name())
			return i;

	return INVALID_ID;
}

void Stock::Push_all_data_to_file()
{
	std::stringstream ss;
	size_t length = Get_items().size();
	for (size_t i = 0ui64; i < length; i++)
		ss << Get_items()[i]->Push_all_data_to_file() << "\n=======================\n\n";

	FileHelper::Write_file_in_text_format(FileHelper::show_stock, ss.str());
}

void Stock::Push_readable_data_to_file()
{
	std::stringstream ss;
	size_t length = Get_items().size();
	for (size_t i = 0ui64; i < length; i++)
		ss << Get_items()[i]->Push_readable_data_to_file() << '\n';

	FileHelper::Write_file_in_text_format(FileHelper::read_stock, ss.str());
}

void Stock::Show()
{

	std::cout << "Stock Recipe Items\n\n";
	size_t length = Get_items().size();

	std::ifstream fin(FileHelper::read_stock, std::ios_base::in);

	while (length != 0)
	{

		unsigned int id{};
		std::string name{};
		float fat{};
		unsigned short kcal{};
		float protein{};
		float carbohydrat{};
		float price{};
		unsigned short amount{};

		fin >> id;
		std::getline(fin, name);
		std::getline(fin, name);
		fin >> fat;
		fin >> kcal;
		fin >> protein;
		fin >> carbohydrat;
		fin >> price;
		fin >> amount;


		std::cout << "Ingredient ID: " << id << '\n';
		std::cout << "Ingredient Name: " << name << '\n';
		std::cout << "Ingredient Fat: " << fat << " gr\n";
		std::cout << "Ingredient Kcal: " << kcal << " kcal\n";
		std::cout << "Ingredient Protein: " << protein << " gr\n";
		std::cout << "Ingredient Carbohydrat: " << carbohydrat << " gr\n";
		std::cout << "Ingredient Price: " << price << " $\n";
		std::cout << "Ingredient Amount: " << amount << "\n\n";
		--length;
	}

	fin.close();
}