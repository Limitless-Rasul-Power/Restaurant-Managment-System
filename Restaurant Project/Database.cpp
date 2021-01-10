#include <iostream>
#include <windows.h>
#include "Database.h"
#include "Exception.h"
#include "Notification_Menu_Enums.h"
#include "Encrypt.h"
#include "File_Helper.h"
#include <fstream>
#include <sstream>
#include <algorithm>

#define INVALID_CREDENTIAL -1;


DataBase::DataBase(const std::shared_ptr<Restaurant>& restaurant, const std::shared_ptr<Stock>& stock,
	const std::vector<std::shared_ptr<Meal>>& meals)
{
	Set_restaurant(restaurant);
	Set_stock(stock);
	Set_meals(meals);

	Push_all_meal_data_to_file();
	Push_more_info_about_meal_to_file();
	Push_less_info_about_meal_to_file();
	Push_useful_meal_numbers_to_file();
	Push_useful_ingredient_numbers_to_file();
}

void DataBase::Set_restaurant(const std::shared_ptr<Restaurant>& restaurant)
{
	if (restaurant == nullptr)
		throw InvalidArgumentException("Restaurant is nullptr!", __LINE__, __FILE__);

	this->restaurant = restaurant;
}

std::shared_ptr<Restaurant>& DataBase::Get_restaurant()
{
	return restaurant;
}

void DataBase::Set_stock(const std::shared_ptr<Stock>& stock)
{
	this->stock = stock;
}

std::shared_ptr<Stock>& DataBase::Get_stock()
{
	return stock;
}

void DataBase::Set_meals(const std::vector<std::shared_ptr<Meal>>& meals)
{
	this->meals = meals;
}

std::vector<std::shared_ptr<Meal>>& DataBase::Get_meals()
{
	return meals;
}

void DataBase::Show_all_meals()
{
	std::ifstream fin(FileHelper::read_more_info_about_meals, std::ios_base::in);

	if (fin.is_open())
	{
		size_t length = Get_meals().size();
		for (size_t i = 0ui64; i < length; i++)
		{
			size_t ingredient_length = Get_meals()[i]->Get_items().size();
			for (size_t j = 0ui64; j < ingredient_length; j++)
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
			}

			float max_fat{};
			unsigned short max_kcal{};
			float max_protein{};
			float max_carbohydrat{};
			float max_price{};
			unsigned short max_amount{};

			fin >> max_protein;
			fin >> max_fat;
			fin >> max_carbohydrat;
			fin >> max_kcal;
			fin >> max_amount;
			fin >> max_price;

			std::cout << "All Meal Protein: " << max_protein << " gr\n";
			std::cout << "All Meal Fat: " << max_fat << " gr\n";
			std::cout << "All Meal Carbohydrat: " << max_carbohydrat << " gr\n";
			std::cout << "All Meal Kcal: " << max_kcal << " kcal\n";
			std::cout << "All Ingredient Amount: " << max_amount << " gr\n";
			std::cout << "All Meal Ingredient Price: " << max_price << " $\n\n";

			unsigned int id{};
			std::string name{};
			std::string category{};
			float rating{};

			fin >> id;
			std::getline(fin, name);
			std::getline(fin, name);
			std::getline(fin, category);
			fin >> rating;

			std::cout << "Meal ID: " << id << '\n';
			std::cout << "Meal Name: " << name << '\n';
			std::cout << "Meal Category: " << category << '\n';
			std::cout << "Meal Rating: " << rating << "\n\n=======================\n\n";
		}

		fin.close();
	}
}

void DataBase::Add_meal(const std::shared_ptr<Meal>& added_meal)
{
	Get_meals().emplace_back(added_meal);
}

bool DataBase::Delete_meal_with_id(const int& id)
{
	int index = Is_meal_id_exist(id);

	if (index >= 0)
	{
		Get_meals().erase(Get_meals().begin() + index);
		return true;
	}
	return false;
}

void DataBase::Show_summary_of_the_meals()
{
	std::ifstream fin(FileHelper::read_less_info_about_meals, std::ios_base::in);
	if (fin.is_open())
	{
		size_t length = Get_meals().size();
		
		for (size_t i = 0ui64; i < length; i++)
		{
			unsigned int id{};
			std::string name{};
			std::string category{};
			float rating{};
			float price{};

			fin >> id;
			std::getline(fin, name);
			std::getline(fin, name);
			std::getline(fin, category);
			fin >> rating;
			fin >> price;

			std::cout << "Meal ID: " << id << ", Name: " << name << ", Category: "\
				<< category << ", Rating: " << rating << ", Price: " << price << " $\n\n";
		}

		fin.close();
	}
}

#include <algorithm>

bool DataBase::Search_meal(const std::string& meal_name)
{
	size_t length = Get_meals().size();
	bool flag_for_finding = false;
	std::string meal_name_copy = meal_name;

	for (size_t i = 0ui64; i < length; i++)
	{

		std::transform(meal_name_copy.begin(), meal_name_copy.end(), meal_name_copy.begin(), std::tolower);
		size_t finding_index = Get_meals()[i]->Get_name().find(meal_name_copy);

		if (finding_index < Get_meals()[i]->Get_name().size() && finding_index >= 0)
		{
			Get_meals()[i]->Show_summary_of_the_meal();
			flag_for_finding = true;
		}

		std::transform(meal_name_copy.begin(), meal_name_copy.end(), meal_name_copy.begin(), std::toupper);
		finding_index = Get_meals()[i]->Get_name().find(meal_name_copy);

		if (finding_index < Get_meals()[i]->Get_name().size() && finding_index >= 0)
		{
			Get_meals()[i]->Show_summary_of_the_meal();
			flag_for_finding = true;
		}
	}

	return flag_for_finding;
}

void DataBase::Delete_all_meals()
{
	Get_meals().erase(Get_meals().begin(), Get_meals().end());
}

void DataBase::Set_orders(const std::vector<std::shared_ptr<Order>>& orders)
{
	this->orders = orders;
}

std::vector <std::shared_ptr<Order>>& DataBase::Get_orders()
{
	return orders;
}

void DataBase::Show_all_orders()
{
	size_t length = Get_orders().size();
	for (size_t i = 0Ui64; i < length; i++)
		Get_orders()[i]->Show();
}

void DataBase::Show_summary_of_the_orders()
{
	size_t length = Get_orders().size();
	for (size_t i = 0Ui64; i < length; i++)
		std::cout << "Order ID: " << Get_orders()[i]->Get_id() << ", Ordered Meal Table No: " << Get_orders()[i]->Get_table_no()
		<< ", Ordered Meal Name: " << Get_orders()[i]->Get_meal()->Get_name()
		<< ", Ordered Meal Amount: " << Get_orders()[i]->Get_amount() << "\n\n";
}

void DataBase::Add_order(const std::shared_ptr<Order>& added_order)
{
	Get_orders().emplace_back(added_order);
}

void DataBase::Delete_order_with_id(const int& id)
{
	int index = Is_order_id_exist(id);

	if (index >= 0)
		Get_orders().erase(Get_orders().begin() + index);
}

void DataBase::Delete_all_orders()
{
	Get_orders().erase(Get_orders().begin(), Get_orders().end());
}

int DataBase::Is_order_id_exist(const int& id)
{
	size_t length = Get_orders().size();

	for (size_t i = 0Ui64; i < length; i++)
		if (id == Get_orders()[i]->Get_id())
			return i;

	return INVALID_ID;
}

void DataBase::Delete_orders_in_the_kitchen_with_table_no(const std::string& table_no)
{
	for (size_t i = 0ui64; i < Get_orders().size(); i++)
		if (Get_orders()[i]->Get_table_no() == table_no)
		{
			Get_orders().erase(Get_orders().begin() + i);
			--i;
		}
}

std::vector<std::shared_ptr<Notification>>& DataBase::Get_notes()
{
	return notes;
}

bool DataBase::Is_correct_admin_credentials(const std::string& user_name, const std::string& password)
{
	size_t length = Get_restaurant()->Get_admins().size();

	for (size_t i = 0ui64; i < length; i++)
	{
		if (user_name == Get_restaurant()->Get_admins().at(i)->Get_user_name())
		{
			if (Get_restaurant()->Get_admins().at(i)->Get_password() == Encrypt::Readable_text(password))
				return true;
		}
	}
	return false;
}

bool DataBase::Is_meal_name_already_exist(const std::string& meal_name)
{
	size_t length = Get_meals().size();

	for (size_t i = 0ui64; i < length; i++)
		if (meal_name == Get_meals().at(i)->Get_name())
			return true;

	return false;
}

bool DataBase::Is_ingredient_name_already_exist(const std::string& ingredient_name)
{
	size_t length = Get_stock()->Get_items().size();
	for (size_t i = 0ui64; i < length; i++)
		if (ingredient_name == Get_stock()->Get_items().at(i)->Get_ingredient()->Get_name())
			return true;

	return false;
}

int DataBase::Is_meal_id_exist(const int& id)
{
	size_t length = Get_meals().size();
	for (size_t i = 0ui64; i < length; i++)
		if (id == Get_meals()[i]->Get_id())
			return i;

	return INVALID_ID;
}

int DataBase::Is_notification_id_exist(const int& id)
{
	size_t length = Get_notes().size();
	for (size_t i = 0Ui64; i < length; i++)
		if (id == Get_notes()[i]->Get_id())
			return i;

	return INVALID_ID;
}

void DataBase::Set_feedback_for_all_tables(const std::string& feedback)
{
	size_t length = Get_restaurant()->Get_tables().size();
	for (size_t i = 0Ui64; i < length; i++)
		Get_restaurant()->Get_tables()[i]->Set_message_from_kitchen(feedback);
}

int DataBase::Is_table_exist(const std::string& table_no)
{
	size_t length = Get_restaurant()->Get_tables().size();
	for (size_t i = 0ui64; i < length; i++)
		if (table_no == Get_restaurant()->Get_tables()[i]->Get_table_no())
			return i;

	return INVALID_ID;
}

void DataBase::Add_notification(const std::shared_ptr<Notification>& note)
{
	Get_notes().emplace_back(note);
}

void DataBase::Delete_notification_with_id(const int& id)
{
	int index = Is_notification_id_exist(id);

	if (index >= 0)
		Get_notes().erase(Get_notes().begin() + index);
}

void DataBase::Show_all_notification()
{
	char choice{};
	int id{};

	size_t length = Get_notes().size();

	while (true)
	{
		std::cout << "1)Show Unread message(s)\n2)Show all message(s)\n3)Exit\nEnter: ";
		std::cin >> choice;

		Helper::Check_choice(choice, Third);
		system("CLS");

		bool is_all_read = true;
		if (choice != Notification_Menu::Exit)
			for (size_t i = 0ui64; i < length; i++)
				if (Get_notes()[i]->Is_read() == false)
				{
					is_all_read = false;
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
					std::cout << "Unread Message ID: " << Get_notes()[i]->Get_id() << "..........\n";
				}


		if (choice == Notification_Menu::Unread)
		{
			if (is_all_read)
			{
				std::cout << "You don't have Unread Notifications!\n";
				Sleep(1000);
			}
			else
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
				std::cout << "\nWhich id do you want to read: ";
				Helper::Check_is_input_number_and_not_equal_to_zero(id);

				for (size_t i = 0ui64; i < length; i++)
				{
					if (id == Get_notes()[i]->Get_id() && Get_notes()[i]->Is_read() == false)
					{
						system("CLS");
						Get_notes()[i]->Set_is_read(true);
						Get_notes()[i]->Show();
						system("pause");
						break;
					}
				}
			}

		}

		else if (choice == Notification_Menu::Read)
		{
			for (size_t i = 0ui64; i < length; i++)
				if (Get_notes()[i]->Is_read() == true)
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
					std::cout << "Read Message ID: " << Get_notes()[i]->Get_id() << '\n';
				}

			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
			std::cout << "\nWhich id do you want to read: ";
			Helper::Check_is_input_number_and_not_equal_to_zero(id);

			for (size_t i = 0ui64; i < length; i++)
			{
				if (id == Get_notes()[i]->Get_id())
				{
					if (Get_notes()[i]->Is_read() == false)
						Get_notes()[i]->Set_is_read(true);

					system("CLS");
					Get_notes()[i]->Show();
					system("pause");
					break;
				}
			}
		}

		else
			break;

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

		system("CLS");
	}

}

void DataBase::Delete_all_notifications()
{
	Get_notes().erase(Get_notes().begin(), Get_notes().end());
}

size_t DataBase::Get_read_note_count()
{
	size_t count = 0ui64;
	size_t length = Get_notes().size();

	for (size_t i = 0ui64; i < length; i++)
		if (Get_notes()[i]->Is_read())
			++count;

	return count;
}

void DataBase::Print_notifications_with_no_operation()
{
	size_t length = Get_notes().size();
	for (size_t i = 0ui64; i < length; i++)
	{
		if (Get_notes()[i]->Is_read() == false)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
			std::cout << "Unread Notification ID: " << Get_notes()[i]->Get_id() << '\n';
		}		
	}

	for (size_t i = 0ui64; i < length; i++)
	{
		if (Get_notes()[i]->Is_read())
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
			std::cout << "Read Notification ID: " << Get_notes()[i]->Get_id() << '\n';
		}
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}

void DataBase::Delete_notes_in_the_kitchen_with_table_no(const std::string& table_no)
{
	for (size_t i = 0ui64; i < Get_notes().size(); i++)
		if (Get_notes()[i]->Get_table_name() == table_no)
		{
			Get_notes().erase(Get_notes().begin() + i);
			--i;
		}
}

void DataBase::Push_all_meal_data_to_file()
{
	sort(Get_meals().begin(), Get_meals().end(), greater());
	
	std::stringstream ss;
	size_t length = Get_meals().size();
	for (size_t i = 0ui64; i < length; i++)
		ss << Get_meals()[i]->Push_all_data_to_file() << "\n=======================\n\n";

	FileHelper::Write_file_in_text_format(FileHelper::show_more_info_about_meals, ss.str());
}

void DataBase::Push_more_info_about_meal_to_file()
{
	sort(Get_meals().begin(), Get_meals().end(), greater());

	std::stringstream ss;

	size_t length = Get_meals().size();
	for (size_t i = 0ui64; i < length; i++)
		ss << Get_meals()[i]->Push_more_data_to_file() << "\n\n";

	FileHelper::Write_file_in_text_format(FileHelper::read_more_info_about_meals, ss.str());
}

void DataBase::Push_less_info_about_meal_to_file()
{
	sort(Get_meals().begin(), Get_meals().end(), greater());

	std::stringstream ss;

	size_t length = Get_meals().size();
	for (size_t i = 0ui64; i < length; i++)
		ss << Get_meals()[i]->Push_less_data_to_file() << "\n\n";

	FileHelper::Write_file_in_text_format(FileHelper::read_less_info_about_meals, ss.str());
}

void DataBase::Push_useful_meal_numbers_to_file()
{
	std::stringstream ss;
	size_t length = Get_meals().size();


	ss << length << '\n';
	for (size_t i = 0ui64; i < length; i++)
		ss << Get_meals()[i]->Get_items().size() << '\n';

	FileHelper::Write_file_in_text_format(FileHelper::useful_number_for_meals, ss.str());

}

void DataBase::Push_useful_ingredient_numbers_to_file()
{
	std::stringstream ss;

	ss << Get_stock()->Get_items().size() << '\n';

	FileHelper::Write_file_in_text_format(FileHelper::useful_number_for_ingredients, ss.str());;
}

void DataBase::Show()
{
	Get_restaurant()->Show();

	if (Get_stock()->Get_items().size() == 0ui64)
		std::cout << "There are no ingredients in the Stock !\n";
	else
	{
		std::cout << "\nAll Ingredients Informations\n\n";
		Get_stock()->Show();
	}

	if (Get_meals().size() == 0ui64)
		std::cout << "There are no meals in the Restaurant !\n";
	else
	{
		std::cout << "\nAll Meals Informations\n\n";
		Show_all_meals();
	}

	std::cout << "\n\n";
}