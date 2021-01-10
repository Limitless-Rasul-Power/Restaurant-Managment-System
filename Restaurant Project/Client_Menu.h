#pragma once
#include "Database.h"
#include "Exception.h"
#include <windows.h>
#include "Confirmation_Helper.h"
#include "Client_Menu_Enums.h"
#include "File_Helper.h"

namespace Client
{
	void Menu(const std::shared_ptr<DataBase>& db)
	{
		system("CLS");
		db->Get_restaurant()->Show_all_table_names();
		if (db->Get_meals().size() == 0ui64)
		{
			std::cout << "There is no meal in the Restaurant. Sorry :(\n";
			Sleep(1000);
			return;
		}
		else if (db->Get_stock()->Get_items().size() == 0ui64)
		{
			std::cout << "There is no Recipe Item in the Restaurant. Sorry, we recover soon :(\n";
			Sleep(1000);
			return;
		}

		std::string table_no{};
		std::cout << "Please Enter Table No: ";
		std::getline(std::cin, table_no);

		int table_index = db->Is_table_exist(table_no);

		if (table_index < 0)
		{
			system("CLS");
			throw InvalidArgumentException("There is no " + table_no + " table in the Restaurant", __LINE__, __FILE__);
			Sleep(1000);
		}


		system("CLS");
		std::shared_ptr<Notification> note(new Notification(table_no + " is in the Restaurant!", table_no));
		db->Add_notification(note);

		if (!db->Get_restaurant()->Get_tables()[table_index]->Get_message_from_kitchen().empty())
		{
			std::cout << table_no << " has Notification(s) in the Kitchen\n";
			std::cout << db->Get_restaurant()->Get_tables()[table_index]->Get_message_from_kitchen() << '\n';
			system("pause");
			system("CLS");
		}

		while (true)
		{
			system("CLS");
			char choice{};
			std::cout << "1)Show All Menu\n2)Search Meal\n3)Exit from Menu\n4)Exit from Restaurant\nEnter: ";			
			std::cin >> choice;

			Helper::Check_choice(choice, Fourth);

			bool choice_is_search = false;
			bool is_find = false;
			std::string search_for_meal{};

			if (choice == Client_Menu::Entry::Exit_From_Restaurant)
			{				
				system("CLS");

				int result{};
				size_t length = db->Get_restaurant()->Get_tables()[table_index]->Get_orders().size();
				if (length > 0ui64)
				{
					std::string restaurant_name = "Restaurant: " + db->Get_restaurant()->Get_name();
					std::wstring w_name = std::wstring(restaurant_name.begin(), restaurant_name.end());
					LPCWSTR caption = w_name.c_str();

					std::string question = "Do you want to exit in the Restaurant ?\n\nIf you exit in the restaurant your ORDER(s) will\
not prepare.And ordered MEAL(s) list will be removed from the Kitchen!\n";
					std::wstring w_question = std::wstring(question.begin(), question.end());

					LPCWSTR text = w_question.c_str();

					result = MessageBox(NULL, text, caption, MB_YESNO | MB_ICONQUESTION);

					if (result == IDYES)
					{
						db->Get_restaurant()->Delete_all_orders_from_one_table(db->Get_restaurant()->Get_tables()[table_index]);
						db->Delete_orders_in_the_kitchen_with_table_no(table_no);
					}
					else
					{
						std::shared_ptr<Notification> exit_from_restaurant_note(new Notification(table_no + " comes to Exit From Restaurant Page!", table_no));
						db->Add_notification(exit_from_restaurant_note);

						std::shared_ptr<Notification> table_final_note(new Notification(table_no + " comes to Exit From Restaurant Page and choose I Don't Want To Exit Restaurant!", table_no));
						db->Add_notification(table_final_note);
					}
				}
				
				if (result == IDYES || length == 0)
				{
					db->Get_restaurant()->Get_tables()[table_index]->Set_message_from_kitchen("");
					db->Delete_notes_in_the_kitchen_with_table_no(table_no);
					std::cout << "See You next Time, Good Bye :)\n";
					Sleep(1000);
					system("CLS");
					break;
				}
			}

			else if (choice == Client_Menu::Entry::Exit_From_Menu)
			{
				std::shared_ptr<Notification> note_exit(new Notification(table_no + " exits in the Menu!", table_no));
				db->Add_notification(note_exit);
				return;
			}

			else if (choice == Client_Menu::Entry::Search_Meal)
			{
				std::shared_ptr<Notification> note_2(new Notification(table_no + " wants to search meal in the Menu!", table_no));
				db->Add_notification(note_2);

				system("CLS");

				std::cin.ignore(1, '\n');
				std::cout << "Search Meal: ";
				std::getline(std::cin, search_for_meal);
				choice_is_search = true;
				system("CLS");

				is_find = (db->Search_meal(search_for_meal));
				if (is_find == false)
				{
					std::cout << "There is no " << search_for_meal << " in the Restaurant!\n";
					std::shared_ptr<Notification> note_3(new Notification(table_no + " searched meal [" + search_for_meal + "] isn't in the Menu!", table_no));
					db->Add_notification(note_3);
					Sleep(1000);
				}
				else
				{
					std::shared_ptr<Notification> note_4(new Notification(table_no + " searched meal [" + search_for_meal + "] is in the Menu!", table_no));
					db->Add_notification(note_4);
				}
			}
			else
			{
				std::shared_ptr<Notification> note_show_all(new Notification(table_no + " wants to show all meal in the Menu!", table_no));
				db->Add_notification(note_show_all);
			}

			while (true)
			{
				if (!(is_find))
				{
					system("CLS");
					db->Show_summary_of_the_meals();
				}


				std::cout << "\n1)Order\n2)Show More Information\n3)Back\nEnter: ";
				std::cin >> choice;

				Helper::Check_choice(choice, Third);

				system("CLS");

				if (choice == Client_Menu::Request::Back)
					break;
				else if (choice == Client_Menu::Request::Order)
				{
					short order_meal_id{};
					int meal_index{};
					while (true)
					{

						system("CLS");
						if (!(is_find))
							db->Show_summary_of_the_meals();

						else
							db->Search_meal(search_for_meal);

						std::cout << "Ordered Meal ID: ";
						Helper::Check_is_input_number(order_meal_id);

						meal_index = db->Is_meal_id_exist(order_meal_id);

						try
						{
							if (meal_index < 0)
								throw InvalidArgumentException("There is no [" + std::to_string(order_meal_id) + "] id exist in the Restaurant", __LINE__, __FILE__);
							else
								break;
						}
						catch (const Exception& ex)
						{
							system("CLS");
							std::cout << ex << '\n';
							FileHelper::Append_file_in_text_format(FileHelper::exception_file_name, ex.Get_data());
							Sleep(1000);
						}
					}

					std::string meal_name = db->Get_meals()[meal_index]->Get_name();				
					std::shared_ptr<Notification> note_5(new Notification(table_no + " wants to order [" + std::to_string(order_meal_id) + "] ID, this ID means " + meal_name, table_no));
					db->Add_notification(note_5);

					std::cout << "\n1)Add More Ingredient\n2)Order\n";
					std::cin >> choice;

					Helper::Check_choice(choice, Second);

					std::vector<std::shared_ptr<RecipeItem>> all_recipe_items;
					all_recipe_items.reserve(25);

					size_t length = db->Get_meals()[meal_index]->Get_items().size();

					for (size_t i = 0ui64; i < length; i++)
					{
						std::shared_ptr<RecipeItem> ro(new RecipeItem);
						*ro = *db->Get_meals()[meal_index]->Get_items()[i];
						all_recipe_items.emplace_back(ro);
					}
				
					float meal_rating = db->Get_meals()[meal_index]->Get_rating();
					unsigned short rating_count = db->Get_meals()[meal_index]->Get_rating_count();
					std::string meal_category = db->Get_meals()[meal_index]->Get_category();

					std::string restaurant_name = "Restaurant: " + db->Get_restaurant()->Get_name();
					std::wstring w_name = std::wstring(restaurant_name.begin(), restaurant_name.end());
					LPCWSTR caption = w_name.c_str();
					int result{};

					std::shared_ptr<Meal> meal(new Meal(all_recipe_items, meal_name, meal_category, meal_rating / static_cast<float>(rating_count)));
					--Meal::meal_id;

					if (choice == Client_Menu::Category::Add_More_Ingredient)
					{
						while (true)
						{
							int id{};
							int amount{};
							int item_index{};

							while (true)
							{
								system("CLS");
								db->Get_stock()->Show();

								std::cout << "\n\n";

								std::cout << "Which Ingredient ID do you want to add to meal: ";
								Helper::Check_is_input_number(id);

								item_index = db->Get_stock()->Is_item_id_exist(id);

								try
								{
									if (item_index < 0)
										throw InvalidArgumentException("There is no [" + std::to_string(id) + "] ID exist in the Stock", __LINE__, __FILE__);
									else
										break;

								}
								catch (const Exception& ex)
								{
									system("CLS");
									std::cout << ex << '\n';
									FileHelper::Append_file_in_text_format(FileHelper::exception_file_name, ex.Get_data());
									Sleep(1000);
								}

							}

							while (true)
							{

								std::cout << "How many do you want to add: ";
								Helper::Check_is_input_number_and_not_equal_to_zero(amount);

								try
								{
									if (db->Get_stock()->Is_item_amount_exist(item_index, amount) == false)
										throw InvalidArgumentException("There is no " + std::to_string(amount) + " amounts of " + db->Get_stock()->Get_items()[item_index]->Get_ingredient()->Get_name() + " exists in the stock!", __LINE__, __FILE__);
									else
										break;
								}
								catch (const Exception& ex)
								{
									system("CLS");
									std::cout << ex << '\n';
									FileHelper::Append_file_in_text_format(FileHelper::exception_file_name, ex.Get_data());
									Sleep(1000);
									db->Get_stock()->Show();
								}
							}							

							std::shared_ptr<Ingredient> ingre(new Ingredient);
							*(ingre) = *(db->Get_stock()->Get_items()[item_index]->Get_ingredient());

							std::shared_ptr<RecipeItem> recipe_item(new RecipeItem(ingre, amount));

							std::shared_ptr<Notification> note_6(new Notification(table_no + " adds extra " + std::to_string(amount) + " amounts of " + ingre->Get_name(), table_no));
							db->Add_notification(note_6);

							meal->Add_item(recipe_item, amount);

							system("CLS");

							std::string question = "Do You Want to Add More Ingredient(s) to " + meal_name + " ?";
							std::wstring w_question = std::wstring(question.begin(), question.end());

							LPCWSTR text = w_question.c_str();

							result = MessageBox(NULL, text, caption, MB_YESNO | MB_ICONQUESTION);
							
							if (result == IDNO)
								break;
						}
					}

					system("CLS");
					
					std::string order_question = "Do you want to order " + meal_name + " ?";
					std::wstring w_order_question = std::wstring(order_question.begin(), order_question.end());
					LPCWSTR order_text = w_order_question.c_str();

					result = MessageBox(NULL, order_text, caption, MB_YESNO | MB_ICONQUESTION);

					if (result == IDNO)
					{
						std::cout << "Meal didn't order!\n";
						std::shared_ptr<Notification> note_7(new Notification(table_no + " comes to [order] or [not] part, choose NO and order didn't save", table_no));
						db->Add_notification(note_7);
					}
					else
					{
						system("CLS");
						int count{};
						std::cout << "How many " << meal_name << " do you want to order?\nEnter: ";
						Helper::Check_is_input_number_and_not_equal_to_zero(count);

						std::shared_ptr<Order> order(new Order(meal, count));
						order->Set_table_no(table_no);

						std::shared_ptr<Notification> note_8(new Notification(table_no + " orders " + meal_name, table_no));
						db->Add_notification(note_8);

						system("CLS");
						std::cout << meal_name << " is ordered successfully!\n";
						Sleep(1000);
						system("CLS");

						float rating{};
						std::cout << "Please rate " << meal_name << " between 0 - 5\nEnter: ";
						while (true)
						{
							Helper::Check_is_input_number_and_not_equal_to_zero(rating);
							if (Helper::Chech_meal_rating(rating))
								break;
						}

						system("CLS");

						std::shared_ptr<Notification> note_9(new Notification(table_no + " rates " + meal_name + ' ' + std::to_string(rating) + " stars", table_no));
						db->Add_notification(note_9);

						db->Get_meals()[meal_index]->Increase_rating(rating);
						db->Get_restaurant()->Set_order_in_the_table(db->Get_restaurant()->Get_tables()[table_index], order);

						db->Push_all_meal_data_to_file();
						db->Push_more_info_about_meal_to_file();
						db->Push_less_info_about_meal_to_file();

						db->Add_order(order);
					}
				}
				else
				{
					
					int index{};
					while (true)
					{
						system("CLS");
						if (!(is_find))
							db->Show_summary_of_the_meals();
						else
							db->Search_meal(search_for_meal);

						short show_which_meal_id{};
						std::cout << "Show Meal ID: ";
						Helper::Check_is_input_number(show_which_meal_id);

						index = db->Is_meal_id_exist(show_which_meal_id);

						try
						{
							if (index < 0)
								throw InvalidArgumentException("There is no [" + std::to_string(show_which_meal_id) + "] ID meal in the Restaurant for show more information about!", __LINE__, __FILE__);
							else
								break;
						}
						catch (const Exception& ex)
						{
							system("CLS");
							std::cout << ex << '\n';
							FileHelper::Append_file_in_text_format(FileHelper::exception_file_name, ex.Get_data());
							Sleep(1000);
						}

					}			

					std::shared_ptr<Notification> note_10(new Notification(table_no + " want to see more information about " + db->Get_meals()[index]->Get_name(), table_no));
					db->Add_notification(note_10);

					system("CLS");
					db->Get_meals()[index]->Show();
					system("pause");

				}
				is_find = false;
			}
		}
	}
}