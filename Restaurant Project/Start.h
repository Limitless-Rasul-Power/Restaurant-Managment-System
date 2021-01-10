#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include "Exception.h"
#include "Client_Menu.h"
#include "Admin_Menu.h"
#include "Confirmation_Helper.h"
#include "Console.h"
#include "All_Static_Variables.h"

void Start()
{	
	Console::Change_font();
	Console::Disable_cursor();
	Console::Disable_x_button();
	

	std::vector<std::shared_ptr<Table>> tables;
	tables.reserve(10);

	tables.emplace_back(new Table("T-1"));
	tables.emplace_back(new Table("T-2"));

	tables.emplace_back(new Table("T-3"));
	tables.emplace_back(new Table("T-4"));

	tables.emplace_back(new Table("T-5"));
	tables.emplace_back(new Table("T-6"));

	tables.emplace_back(new Table("T-7"));
	tables.emplace_back(new Table("T-8"));


	std::shared_ptr<Admin> admin_1(new Admin("Rasul", "admin"));
	std::shared_ptr<Admin> admin_2(new Admin("Luca", "123456"));
	std::shared_ptr<Admin> admin_3(new Admin("Dan Mil", "enjoy the moment"));

	std::vector<std::shared_ptr<Admin>> admins;
	admins.reserve(7);
	admins.emplace_back(admin_1);
	admins.emplace_back(admin_2);
	admins.emplace_back(admin_3);

	std::shared_ptr<Restaurant> restaurant(new Restaurant("ONE day all LIFE", "Rasul's Street", "America", admins, tables));


	bool is_program_run = false;

	std::ifstream fin(FileHelper::is_program_run, std::ios_base::in);

	if (fin.is_open())
	{
		fin >> is_program_run;
		fin.close();
	}

	if (is_program_run == false)
	{
		FileHelper::Write_file_in_binary_format(FileHelper::is_program_run, true);

		std::vector<std::shared_ptr<Ingredient>> ingre;
		ingre.reserve(50);

		ingre.emplace_back(new Ingredient("Tomatoe", 0.2f, 1.4f, 44.4f, 12, 3.0f));
		ingre.emplace_back(new Ingredient("Pepper", 0.2f, 0.01f, 45.4f, 10, 1.2f));
		ingre.emplace_back(new Ingredient("Parmizan", 2.2f, 1.2f, 45.4f, 40, 2.1f));
		ingre.emplace_back(new Ingredient("Beef", 54.33f, 12.2f, 50.23f, 500, 3.5f));
		ingre.emplace_back(new Ingredient("Oyster", 2.2f, 1.1f, 30.1f, 20, 0.69f));
		ingre.emplace_back(new Ingredient("Onion", 0.4f, 3.1f, 10.1f, 6, 1.1f));
		ingre.emplace_back(new Ingredient("Organic Chicken", 5.4f, 3.1f, 10.1f, 600, 5.0f));
		ingre.emplace_back(new Ingredient("Crab", 2.4f, 4.1f, 9.1f, 712, 7.0f));
		ingre.emplace_back(new Ingredient("Salmon", 1.4f, 15.1f, 2.1f, 800, 12.0f));
		ingre.emplace_back(new Ingredient("Cacao Powder", 0.5f, 5.1f, 2.3f, 16, 2.2f));
		ingre.emplace_back(new Ingredient("Sugar", 0.1f, 1.1f, 0.3f, 8, 1.1f));
		ingre.emplace_back(new Ingredient("Lettuce", 1.1f, 2.1f, 3.3f, 4, 0.5f));


		std::vector<std::shared_ptr<RecipeItem>> recipe_items;
		recipe_items.reserve(50);

		recipe_items.emplace_back(new RecipeItem(ingre.at(0), 100));
		recipe_items.emplace_back(new RecipeItem(ingre.at(1), 300));
		recipe_items.emplace_back(new RecipeItem(ingre.at(2), 300));
		recipe_items.emplace_back(new RecipeItem(ingre.at(3), 100));
		recipe_items.emplace_back(new RecipeItem(ingre.at(4), 250));
		recipe_items.emplace_back(new RecipeItem(ingre.at(5), 350));
		recipe_items.emplace_back(new RecipeItem(ingre.at(6), 100));
		recipe_items.emplace_back(new RecipeItem(ingre.at(7), 150));
		recipe_items.emplace_back(new RecipeItem(ingre.at(8), 200));
		recipe_items.emplace_back(new RecipeItem(ingre.at(9), 120));
		recipe_items.emplace_back(new RecipeItem(ingre.at(10), 130));
		recipe_items.emplace_back(new RecipeItem(ingre.at(11), 222));


		std::vector<std::shared_ptr<RecipeItem>> for_meal_pizza;
		for_meal_pizza.reserve(20);
		for_meal_pizza.emplace_back(new RecipeItem(ingre[0], 5));
		for_meal_pizza.emplace_back(new RecipeItem(ingre[1], 6));
		for_meal_pizza.emplace_back(new RecipeItem(ingre[2], 7));
		for_meal_pizza.emplace_back(new RecipeItem(ingre[5], 3));
		for_meal_pizza.emplace_back(new RecipeItem(ingre[6], 4));


		std::vector<std::shared_ptr<RecipeItem>> for_meal_caesar;
		for_meal_caesar.reserve(20);
		for_meal_caesar.emplace_back(new RecipeItem(ingre[0], 5));
		for_meal_caesar.emplace_back(new RecipeItem(ingre[1], 6));
		for_meal_caesar.emplace_back(new RecipeItem(ingre[2], 7));
		for_meal_caesar.emplace_back(new RecipeItem(ingre[8], 3));
		for_meal_caesar.emplace_back(new RecipeItem(ingre[6], 4));
		for_meal_caesar.emplace_back(new RecipeItem(ingre[11], 12));


		std::vector<std::shared_ptr<RecipeItem>> for_meal_cake;
		for_meal_cake.reserve(20);
		for_meal_cake.emplace_back(new RecipeItem(ingre[9], 5));
		for_meal_cake.emplace_back(new RecipeItem(ingre[10], 6));

		std::shared_ptr<Meal> meal_1(new Meal(for_meal_pizza, "Pizza", "Hot Meals", 5.0f));
		std::shared_ptr<Meal> meal_2(new Meal(for_meal_caesar, "Caesar", "Salad", 4.98f));
		std::shared_ptr<Meal> meal_3(new Meal(for_meal_cake, "Cake", "Sugary Meals", 4.4f));

		std::vector<std::shared_ptr<Meal>> all_meals;
		all_meals.reserve(20);
		all_meals.emplace_back(meal_1);
		all_meals.emplace_back(meal_2);
		all_meals.emplace_back(meal_3);
		
		std::shared_ptr<Stock> stock(new Stock(recipe_items));

		std::shared_ptr<DataBase> db(new DataBase(restaurant, stock, all_meals));

		while (true)
		{
			system("CLS");
			char choice{};
			std::cout << restaurant->Get_name() << " Managment System\n1)Client\n2)Admin\n3)Exit\nEnter: ";
			std::cin >> choice;

			Helper::Check_choice(choice, Third);
			std::cin.ignore(1, '\n');

			if (choice == Main_Menu::Client)
			{
				try
				{
					Client::Menu(db);
				}
				catch (const Exception& ex)
				{
					std::cout << ex << '\n';
					FileHelper::Append_file_in_text_format(FileHelper::exception_file_name, ex.Get_data());
					Sleep(1000);
				}
			}
			else if (choice == Main_Menu::Admin)
			{
				try
				{
					DataBaseAdmin::Menu(db);
				}
				catch (const Exception& ex)
				{
					std::cout << ex << '\n';
					FileHelper::Append_file_in_text_format(FileHelper::exception_file_name, ex.Get_data());
					Sleep(1000);
				}
			}
			else
			{
				std::stringstream ss;
				ss << Ingredient::ingredient_id << '\n';
				FileHelper::Append_file_in_text_format(FileHelper::useful_number_for_ingredients, ss.str());
				FileHelper::Write_file_in_binary_format(FileHelper::restaurant_budget, static_cast<size_t>(db->Get_restaurant()->Get_budget()));
				
				db->Push_all_meal_data_to_file();
				db->Push_more_info_about_meal_to_file();
				db->Push_less_info_about_meal_to_file();
				db->Push_useful_meal_numbers_to_file();
				db->Get_stock()->Push_all_data_to_file();
				db->Get_stock()->Push_readable_data_to_file();
				
				system("CLS");
				db->Get_restaurant()->Show();
				std::cout << "Bye - Bye\n";
				system("pause");
				return;
			}
		}
	}
	else
	{
		std::vector<std::shared_ptr<RecipeItem>> all_items;
		all_items.reserve(50);

		size_t ingre_size{};

		std::ifstream fin_ingre_size(FileHelper::useful_number_for_ingredients, std::ios_base::in);
		fin_ingre_size >> ingre_size;
		fin_ingre_size >> Ingredient::ingredient_id;
		fin_ingre_size.close();

		const unsigned int current_id = Ingredient::ingredient_id;

		std::ifstream fin_item(FileHelper::read_stock, std::ios_base::in);

		for (size_t i = 0; i < ingre_size; i++)
		{
			unsigned int id{};
			std::string name{};
			float fat{};
			unsigned short kcal{};
			float protein{};
			float carbohydrat{};
			float price{};
			unsigned short amount{};

			fin_item >> id;
			std::getline(fin_item, name);
			std::getline(fin_item, name);
			fin_item >> fat;
			fin_item >> kcal;
			fin_item >> protein;
			fin_item >> carbohydrat;
			fin_item >> price;
			fin_item >> amount;

			try
			{
				std::shared_ptr<Ingredient> ingre_in_the_file(new Ingredient(name, fat, protein, carbohydrat, kcal, price));
				ingre_in_the_file->Set_id(id);
				std::shared_ptr<RecipeItem> recipe_item(new RecipeItem(ingre_in_the_file, amount));
				all_items.emplace_back(recipe_item);
			}
			catch (const Exception& ex)
			{
				system("CLS");
				std::cout << ex << '\n';
				FileHelper::Append_file_in_text_format(FileHelper::exception_file_name, ex.Get_data());
				Sleep(1000);
			}
		}
		fin_item.close();

		std::shared_ptr<Stock> stock(new Stock(all_items));

		std::ifstream fin_meal_numbers(FileHelper::useful_number_for_meals, std::ios_base::in);

		size_t meal_size{};
		fin_meal_numbers >> meal_size;

		std::vector<size_t> number_of_ingredients_in_meal;
		number_of_ingredients_in_meal.reserve(50);

		for (size_t i = 0ui64; i < meal_size; i++)
		{
			size_t number{};
			fin_meal_numbers >> number;
			number_of_ingredients_in_meal.emplace_back(number);
		}
		fin_meal_numbers.close();


		std::vector<std::shared_ptr<Meal>> all_meals;
		all_meals.reserve(50);

		Meal::meal_id = 0U;

		std::ifstream fin_meals(FileHelper::read_more_info_about_meals, std::ios_base::in);

		for (size_t i = 0ui64; i < meal_size; i++)
		{
			std::vector<std::shared_ptr<RecipeItem>> ingredients_in_meal;
			ingredients_in_meal.reserve(20);

			for (size_t j = 0ui64; j < number_of_ingredients_in_meal[i]; j++)
			{
				unsigned int id{};
				std::string name{};
				float fat{};
				unsigned short kcal{};
				float protein{};
				float carbohydrat{};
				float price{};
				unsigned short amount{};

				fin_meals >> id;
				std::getline(fin_meals, name);
				std::getline(fin_meals, name);
				fin_meals >> fat;
				fin_meals >> kcal;
				fin_meals >> protein;
				fin_meals >> carbohydrat;
				fin_meals >> price;
				fin_meals >> amount;


				try
				{
					std::shared_ptr<Ingredient> ingredient(new Ingredient(name, fat, protein, carbohydrat, kcal, price));
					ingredient->Set_id(id);
					--Ingredient::ingredient_id;
					std::shared_ptr<RecipeItem> item(new RecipeItem(ingredient, amount));
					ingredients_in_meal.emplace_back(item);
				}
				catch (const Exception& ex)
				{
					system("CLS");
					std::cout << ex << '\n';
					FileHelper::Append_file_in_text_format(FileHelper::exception_file_name, ex.Get_data());					
					Sleep(1000);
				}
			}

			float max_fat{};
			unsigned short max_kcal{};
			float max_protein{};
			float max_carbohydrat{};
			float max_price{};
			unsigned short max_amount{};

			fin_meals >> max_protein;
			fin_meals >> max_fat;
			fin_meals >> max_carbohydrat;
			fin_meals >> max_kcal;
			fin_meals >> max_amount;
			fin_meals >> max_price;

			
			unsigned int id{};
			std::string meal_name{};
			std::string category{};
			float rating{};

			fin_meals >> id;
			std::getline(fin_meals, meal_name);
			std::getline(fin_meals, meal_name);
			std::getline(fin_meals, category);
			fin_meals >> rating;

			try
			{
				std::shared_ptr<Meal> meal(new Meal(ingredients_in_meal, meal_name, category, rating));
				all_meals.emplace_back(meal);
			}
			catch (const Exception& ex)
			{
				system("CLS");
				std::cout << ex << '\n';
				FileHelper::Append_file_in_text_format(FileHelper::exception_file_name, ex.Get_data());
				Sleep(1000);
			}
		}
		Ingredient::ingredient_id = current_id;
		fin_meals.close();

		std::ifstream fin_budget(FileHelper::restaurant_budget, std::ios_base::in);
		if (fin_budget.is_open())
		{
			unsigned int budget{};
			fin_budget >> budget;
			fin_budget.close();
			restaurant->Set_budget(budget);
		}

		std::shared_ptr<DataBase> db(new DataBase(restaurant, stock, all_meals));

		while (true)
		{
			system("CLS");
			char choice{};
			std::cout << restaurant->Get_name() << " Managment System\n1)Client\n2)Admin\n3)Exit\nEnter: ";
			std::cin >> choice;

			Helper::Check_choice(choice, Third);
			std::cin.ignore(1, '\n');

			if (choice == Main_Menu::Client)
			{
				try
				{
					Client::Menu(db);
				}
				catch (const Exception& ex)
				{
					std::cout << ex << '\n';
					FileHelper::Append_file_in_text_format(FileHelper::exception_file_name, ex.Get_data());
					Sleep(1000);
				}
			}
			else if (choice == Main_Menu::Admin)
			{
				try
				{
					DataBaseAdmin::Menu(db);
				}
				catch (const Exception& ex)
				{
					std::cout << ex << '\n';
					FileHelper::Append_file_in_text_format(FileHelper::exception_file_name, ex.Get_data());
					Sleep(1000);
				}
			}
			else
			{
				std::stringstream ss;
				ss << Ingredient::ingredient_id << '\n';
				FileHelper::Append_file_in_text_format(FileHelper::useful_number_for_ingredients, ss.str());

				db->Push_all_meal_data_to_file();
				db->Push_more_info_about_meal_to_file();
				db->Push_less_info_about_meal_to_file();
				db->Push_useful_meal_numbers_to_file();
				db->Get_stock()->Push_all_data_to_file();
				db->Get_stock()->Push_readable_data_to_file();
				

				system("CLS");
				db->Get_restaurant()->Show();
				std::cout << "Bye - Bye\n";
				system("pause");
				return;
			}
		}

	}

}
