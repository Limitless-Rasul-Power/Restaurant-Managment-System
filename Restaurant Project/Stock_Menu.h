#pragma once
#include "Database.h"
#include "Exception.h"
#include <windows.h>
#include "Confirmation_Helper.h"
#include "Admin_Menu_Enums.h"
#include "File_Helper.h"

namespace Stock_of_ingredients
{
	void Menu(const std::shared_ptr<DataBase>& db)
	{
		std::string restaurant_name = "Restaurant: " + db->Get_restaurant()->Get_name();
		std::wstring w_restaurant_name = std::wstring(restaurant_name.begin(), restaurant_name.end());
		LPCWSTR caption = w_restaurant_name.c_str();

		char choice{};
		int result{};

		while (true)
		{
			system("CLS");
			std::cout << "\n1)Show All Ingredients\n2)Add Ingredient\n3)Delete Ingredient\n4)Increase Ingredient Amount with ID\n\
5)Decrease Ingredient Amount with ID\n6)Back\nEnter: ";

			std::cin >> choice;

			Helper::Check_choice(choice, Sixth);

			system("CLS");

			if (choice == Admin_Menu::Stock::Back)
				break;

			if (choice > Zero && choice < Admin_Menu::Stock::Back && choice != Admin_Menu::Stock::Add_Ingredient &&
				db->Get_stock()->Get_items().size() == 0ui64)
			{
				std::cout << "There is no Ingredient in the Stock!\n";
				Sleep(1000);
			}
			else
			{
				switch (choice)
				{
				case Admin_Menu::Stock::Show_All_Ingredients:
				{
					db->Get_stock()->Show();
					system("pause");
				}
				break;

				case Admin_Menu::Stock::Add_Ingredient:
				{
					std::cin.ignore(1, '\n');
					while (true)
					{
						std::string name{};
						std::cout << "Ingredient Name: ";
						std::getline(std::cin, name);

						Helper::Check_is_empty(name);

						int index = db->Get_stock()->Is_item_name_exists(name);

						if (index >= 0)
						{
							short amount{};
							std::cout << "How many amount do you want to add\nEnter: ";
							Helper::Check_is_input_number_and_not_equal_to_zero(amount);

							db->Get_stock()->Get_items()[index]->Set_amount(db->Get_stock()->Get_items()[index]->Get_amount() + amount);
							db->Get_stock()->Push_all_data_to_file();
							db->Get_stock()->Push_readable_data_to_file();
							break;
						}
						else
						{
							while (true)
							{								
								float fat{};
								std::cout << "Ingredient Fat: ";
								Helper::Check_is_input_number_and_not_equal_to_zero(fat);

								float protein{};
								std::cout << "Ingredient Protein: ";
								Helper::Check_is_input_number_and_not_equal_to_zero(protein);

								float carbonhydrat{};
								std::cout << "Ingredient Carbohydrat: ";
								Helper::Check_is_input_number_and_not_equal_to_zero(carbonhydrat);

								short kcal{};
								std::cout << "Ingredient Kcal: ";
								Helper::Check_is_input_number_and_not_equal_to_zero(kcal);

								float price{};
								std::cout << "Ingredient Price: ";
								Helper::Check_is_input_number_and_not_equal_to_zero(price);

								try
								{
									std::shared_ptr<Ingredient> ingredient(new Ingredient(name, fat, protein, carbonhydrat, kcal, price));

									short amount{};
									std::cout << "Ingredient Amount: ";
									Helper::Check_is_input_number_and_not_equal_to_zero(amount);

									std::shared_ptr<RecipeItem> added_recipe_item(new RecipeItem(ingredient, amount));

									db->Get_stock()->Add_item(added_recipe_item);

									FileHelper::Append_file_in_text_format(FileHelper::show_stock, added_recipe_item->Push_all_data_to_file());
									FileHelper::Append_file_in_text_format(FileHelper::read_stock, added_recipe_item->Push_readable_data_to_file());
									db->Push_useful_ingredient_numbers_to_file();
									break;
								}
								catch (const Exception& ex)
								{
									--Ingredient::ingredient_id;
									system("CLS");
									std::cout << ex << '\n';									
									FileHelper::Append_file_in_text_format(FileHelper::exception_file_name, ex.Get_data());
									Sleep(1000);
									system("CLS");
								}
							}
							break;
						}
					}
				}
				break;

				case Admin_Menu::Stock::Delete_Ingredient:
				{
					std::string question = "Do you want to delete all Ingredients ?\nIF you choose NO you jump to DELETE ingredient with Id page";
					std::wstring w_question = std::wstring(question.begin(), question.end());
					LPCWSTR text = w_question.c_str();

					result = MessageBox(NULL, text, caption, MB_YESNO | MB_ICONQUESTION);

					if (result == IDYES)
					{
						db->Get_stock()->Delete_all_items();

						db->Get_stock()->Push_all_data_to_file();
						db->Get_stock()->Push_readable_data_to_file();
						db->Push_useful_ingredient_numbers_to_file();
						std::cout << "All ingredients deleted successfully !!!\n";
					}
					else
					{
						short ingre_id{};
						int index{};

						while (true)
						{
							db->Get_stock()->Show();

							std::cout << "\nWhich Ingredient ID do you want to delete, IF you choose 0 nothing deleted in the stock!\nEnter: ";
							Helper::Check_is_input_number(ingre_id);

							index = db->Get_stock()->Is_item_id_exist(ingre_id);

							if (ingre_id == 0)
								break;

							try
							{
								if (index < 0)
									throw InvalidArgumentException("There is no [" + std::to_string(ingre_id) + "] ID in the Stock!", __LINE__, __FILE__);
								else
									break;
							}
							catch (const Exception& ex)
							{
								system("CLS");
								std::cout << ex << '\n';
								FileHelper::Append_file_in_text_format(FileHelper::exception_file_name, ex.Get_data());
								Sleep(1000);
								system("CLS");
							}


						}

						system("CLS");
						if (ingre_id != 0)
						{
							db->Get_stock()->Delete_item(ingre_id);

							db->Get_stock()->Push_all_data_to_file();
							db->Get_stock()->Push_readable_data_to_file();
							db->Push_useful_ingredient_numbers_to_file();
							std::cout << "Ingredient Deleted Successfully !!!\n";
						}
						else
							std::cout << "Ingredient didn't deleted !!!\n";

					}
					Sleep(1000);
				}
				break;

				case Admin_Menu::Stock::Increase_Ingredient_Amount_with_ID:
				{
					short ingre_id{};
					int index{};

					while (true)
					{
						db->Get_stock()->Show();

						std::cout << "\nWhich Ingredient ID do you want to increase amount\nEnter: ";
						Helper::Check_is_input_number(ingre_id);

						index = db->Get_stock()->Is_item_id_exist(ingre_id);

						try
						{
							if (index < 0)
								throw InvalidArgumentException("There is no [" + std::to_string(ingre_id) + "] ID in the Stock!", __LINE__, __FILE__);
							else
								break;
						}
						catch (const Exception& ex)
						{

							system("CLS");
							std::cout << ex << '\n';
							FileHelper::Append_file_in_text_format(FileHelper::exception_file_name, ex.Get_data());
							Sleep(1000);
							system("ClS");
						}
					}


					short amount{};
					std::cout << "How many amounts do you want to increase\nEnter: ";
					Helper::Check_is_input_number_and_not_equal_to_zero(amount);

					db->Get_stock()->Get_items()[index]->Set_amount(db->Get_stock()->Get_items()[index]->Get_amount() + amount);
					db->Get_stock()->Push_all_data_to_file();
					db->Get_stock()->Push_readable_data_to_file();

				}
				break;

				case Admin_Menu::Stock::Decrease_Ingredient_Amount_with_ID:
				{
					short ingre_id{};
					int index{};

					while (true)
					{
						db->Get_stock()->Show();

						std::cout << "\nWhich Ingredient ID do you want to decrease amount\nEnter: ";
						Helper::Check_is_input_number(ingre_id);

						index = db->Get_stock()->Is_item_id_exist(ingre_id);

						try
						{
							if (index < 0)
								throw InvalidArgumentException("There is no [" + std::to_string(ingre_id) + "] ID in the Stock!", __LINE__, __FILE__);
							else
								break;
						}
						catch (const Exception& ex)
						{

							system("CLS");
							std::cout << ex << '\n';
							FileHelper::Append_file_in_text_format(FileHelper::exception_file_name, ex.Get_data());
							Sleep(1000);
							system("CLS");
						}

					}

					short amount{};
					std::cout << "How many amounts do you want to decrease\nEnter: ";
					Helper::Check_is_input_number_and_not_equal_to_zero(amount);


					short final_amount = static_cast<short>(db->Get_stock()->Get_items()[index]->Get_amount()) - static_cast<short>(amount);
					if (final_amount < 0)
						final_amount = 0;
		
					db->Get_stock()->Get_items()[index]->Set_amount(static_cast<unsigned short>(final_amount));
					db->Get_stock()->Push_all_data_to_file();
					db->Get_stock()->Push_readable_data_to_file();
				}
				break;

				}
			}
		}
	}
}