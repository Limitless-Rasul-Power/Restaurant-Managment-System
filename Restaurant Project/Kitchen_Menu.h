#pragma once
#include "Database.h"
#include "Exception.h"
#include <windows.h>
#include "Confirmation_Helper.h"
#include "Admin_Menu_Enums.h"
#include "File_Helper.h"

namespace Kitchen
{
	void Menu(const std::shared_ptr<DataBase>& db, const std::string& user_name)
	{
		std::string restaurant_name = "Restaurant: " + db->Get_restaurant()->Get_name();
		std::wstring w_restaurant_name = std::wstring(restaurant_name.begin(), restaurant_name.end());
		LPCWSTR caption = w_restaurant_name.c_str();

		char choice{};
		int result{};

		while (true)
		{
			system("CLS");
			std::cout << "\n1)Show All Orders and Operations\n2)Show All Meals\n3)Show All Notifications\n4)Add Meal\n5)Delete Meal\n6)Update Meal\n\
7)Delete Notification\n8)Back\nEnter: ";

			std::cin >> choice;

			Helper::Check_choice(choice, Eigth);

			if (choice == Admin_Menu::Kitchen::Back)
				break;

			system("CLS");

			switch (choice)
			{
			case Admin_Menu::Kitchen::Show_All_Orders_and_Operations:
			{
				while (true)
				{
					if (db->Get_orders().size() == 0ui64)
					{
						std::cout << "There is no Order in the Restaurant!\n";
						Sleep(1000);
						break;
					}

					db->Show_summary_of_the_orders();
					std::cout << "\n1)Reject All\n2)Reject with ID\n3)Exit and Accept All\nEnter: ";
					std::cin >> choice;

					Helper::Check_choice(choice, Third);


					if (choice == OrderOperation::Reject_All)
					{
						std::cin.ignore(1, '\n');
						system("CLS");
						std::string feedback{};
						std::cout << user_name << " leave feedback for all rejected orders\nEnter: ";
						std::getline(std::cin, feedback);

						size_t length = db->Get_restaurant()->Get_tables().size();

						for (size_t i = 0ui64; i < length; i++)
							if (db->Get_restaurant()->Get_tables()[i]->Get_orders().size() > 0ui64)
								db->Get_restaurant()->Get_tables()[i]->Set_message_from_kitchen("Restaurant apologizing for all of your ordered meals: " + feedback);


						db->Delete_all_orders();
						db->Get_restaurant()->Delete_all_orders_from_tables();
						break;
					}
					else if (choice == OrderOperation::Reject_With_ID)
					{
						int order_id{};
						int index{};

						while (true)
						{
							system("CLS");
							db->Show_summary_of_the_orders();

							std::cout << "Which ID do you want to reject\nEnter: ";
							Helper::Check_is_input_number(order_id);

							index = db->Is_order_id_exist(order_id);

							try
							{
								if (index < 0)
									throw InvalidArgumentException("There is no order [" + std::to_string(order_id) + "] ID in the restaurant!", __LINE__, __FILE__);
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

						int table_index = db->Is_table_exist(db->Get_orders()[index]->Get_table_no());

						db->Get_restaurant()->Get_tables()[table_index]->Delete_order_with_meal_name_and_amount
						(
							db->Get_orders()[index]->Get_meal()->Get_name(), db->Get_orders()[index]->Get_amount()
						);
						system("CLS");
						std::cin.ignore(1, '\n');

						std::string feedback{};
						std::cout << user_name << " leave feedback to rejected order\nEnter: ";
						std::getline(std::cin, feedback);

						db->Get_restaurant()->Get_tables()[table_index]->Set_message_from_kitchen("Meal " +
							db->Get_orders()[index]->Get_meal()->Get_name() +
							" with amount " + std::to_string(db->Get_orders()[index]->Get_amount()) + " is removed, because "
							+ feedback
						);

						db->Delete_order_with_id(order_id);

						system("CLS");
						std::cout << "Order Successfully Deleted!!!\n";
						Sleep(1000);
						system("CLS");
						if (db->Get_orders().size() == 0ui64)
							break;

					}
					else
					{
						size_t table_length = db->Get_restaurant()->Get_tables().size();

						for (size_t i = 0ui64; i < table_length; i++)
						{
							for (int j = 0U; j < db->Get_restaurant()->Get_tables()[i]->Get_orders().size(); j++)
							{
								int order_amount = db->Get_restaurant()->Get_tables()[i]->Get_orders()[j]->Get_amount();
								bool all_correct{};

								for (int k = 0U, table_ordered_meal_length = db->Get_restaurant()->Get_tables()[i]->Get_orders()[j]->Get_meal()->Get_items().size(); k < table_ordered_meal_length; k++)
								{
									all_correct = true;
									int index = db->Get_stock()->Is_item_name_exists(db->Get_restaurant()->Get_tables()[i]->Get_orders()[j]->Get_meal()->Get_items()[k]->Get_ingredient()->Get_name());
									int meal_ingredient_amount = static_cast<int>(db->Get_restaurant()->Get_tables()[i]->Get_orders()[j]->Get_meal()->Get_items()[k]->Get_amount());
									int decrease = 0;

									if (index != -1)
									{
										decrease = static_cast<int>(db->Get_stock()->Get_items()[index]->Get_amount()) - (order_amount * meal_ingredient_amount);
										if (decrease >= 0)
										{
											db->Get_stock()->Decrease_ingredient_amount(db->Get_stock()->Get_items()[index],
												order_amount * meal_ingredient_amount);
										}
									}

									if (index == -1 || decrease < 0)
									{
										all_correct = false;
										for (int r = k - 1; r >= 0; r--)
										{
											index = db->Get_stock()->Is_item_name_exists(db->Get_restaurant()->Get_tables()[i]->Get_orders()[j]->Get_meal()->Get_items()[r]->Get_ingredient()->Get_name());
											meal_ingredient_amount = db->Get_restaurant()->Get_tables()[i]->Get_orders()[j]->Get_meal()->Get_items()[r]->Get_amount();
											db->Get_stock()->Increase_ingredient_amount(db->Get_stock()->Get_items()[index], order_amount * meal_ingredient_amount);
										}
										db->Get_restaurant()->Get_tables()[i]->Set_message_from_kitchen(db->Get_restaurant()->Get_tables()[i]->Get_orders()[j]->Get_meal()->Get_name() + " didn't prepare because lack of resources");
										db->Get_restaurant()->Get_tables()[i]->Delete_order_with_meal_name_and_amount(db->Get_restaurant()->Get_tables()[i]->Get_orders()[j]->Get_meal()->Get_name(), db->Get_restaurant()->Get_tables()[i]->Get_orders()[j]->Get_amount());

										--j;
										break;
									}
								}
								if (all_correct)
								{
									db->Get_restaurant()->Set_budget(static_cast<float>(order_amount) * db->Get_restaurant()->Get_tables()[i]->Get_orders()[j]->Get_meal()->Get_meal_price());
									FileHelper::Write_file_in_binary_format(FileHelper::restaurant_budget, static_cast<float>(db->Get_restaurant()->Get_budget()));
									db->Get_restaurant()->Get_tables()[i]->Set_message_from_kitchen(db->Get_restaurant()->Get_tables()[i]->Get_orders()[j]->Get_meal()->Get_name() + " Prepared Successfully!!!");
								}
							}
						}

						system("CLS");
						std::cout << "All Orders Completed!\n";
						Sleep(1000);

						db->Get_restaurant()->Delete_all_orders_from_tables();
						db->Delete_all_orders();

						db->Get_stock()->Push_all_data_to_file();
						db->Get_stock()->Push_readable_data_to_file();
						db->Push_useful_ingredient_numbers_to_file();

						break;
					}
				}
			}
			break;

			case Admin_Menu::Kitchen::Show_All_Meals:
			{
				if (db->Get_meals().size() == 0ui64)
				{
					std::cout << "There is no Meal in the Restaurant!\n";
					Sleep(1000);
				}
				else
				{
					std::cout << "\n1)Show More Information\n2)Show Less Information\nEnter: ";
					std::cin >> choice;

					Helper::Check_choice(choice, Second);

					system("CLS");

					if (choice == Admin_Menu::Kitchen::Meal::Show_More)
						db->Show_all_meals();
					else
						db->Show_summary_of_the_meals();

					system("pause");
				}
			}
			break;

			case Admin_Menu::Kitchen::Show_All_Notifications:
			{
				if (db->Get_notes().size() == 0ui64)
				{
					std::cout << "There is no Notification in the DataBase!\n";
					Sleep(1000);
				}
				else
					db->Show_all_notification();
			}
			break;

			case Admin_Menu::Kitchen::Add_Meal:
			{
				std::cin.ignore(1, '\n');
				std::string name{};
				std::cout << "Meal Properties\n\n";
				std::cout << "Name: ";
				std::getline(std::cin, name);

				Helper::Check_is_empty(name);

				std::string category{};
				std::cout << "Category: ";
				std::getline(std::cin, category);

				Helper::Check_is_empty(category);

				float rating{};
				std::cout << "Rating: ";
				while (true)
				{
					Helper::Check_is_input_number_and_not_equal_to_zero(rating);
					if (Helper::Chech_meal_rating(rating))
						break;
				}


				std::vector<std::shared_ptr<RecipeItem>> ri_all;

				while (true)
				{
					int id{};
					int amount{};
					int item_index{};

					while (true)
					{
						system("CLS");
						db->Get_stock()->Show();

						std::cout << "\n\nWhich Ingredient ID do you want to add to meal: ";
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

					std::cout << "How many do you want to add: ";
					Helper::Check_is_input_number_and_not_equal_to_zero(amount);

					std::shared_ptr<Ingredient> ingre(new Ingredient);
					*(ingre) = *(db->Get_stock()->Get_items()[item_index]->Get_ingredient());

					std::shared_ptr<RecipeItem> recipe_item(new RecipeItem(ingre, amount));

					size_t length = ri_all.size();
					bool is_exist = false;
					for (size_t i = 0ui64; i < length; i++)
					{
						if (ri_all[i]->Get_ingredient()->Get_name() == ingre->Get_name())
						{
							ri_all[i]->Set_amount(ri_all[i]->Get_amount() + amount);
							is_exist = true;
							break;
						}
					}

					if (is_exist == false)
						ri_all.push_back(recipe_item);

					system("CLS");
					std::string question = "Do You Want to Add More Ingredient(s) ?";
					std::wstring w_question = std::wstring(question.begin(), question.end());
					LPCWSTR text = w_question.c_str();

					result = MessageBox(NULL, text, caption, MB_YESNO | MB_ICONQUESTION);

					if (result == IDNO)
						break;

					system("CLS");
				}

				std::shared_ptr<Meal> added_meal(new Meal(ri_all, name, category, rating));
				db->Add_meal(added_meal);

				db->Push_all_meal_data_to_file();
				db->Push_less_info_about_meal_to_file();
				db->Push_more_info_about_meal_to_file();
				db->Push_useful_meal_numbers_to_file();

				system("CLS");
				std::cout << "Meal added Successfully!\n\n";
				Sleep(1000);

			}
			break;

			case Admin_Menu::Kitchen::Delete_Meal:
			{
				if (db->Get_meals().size() == 0ui64)
				{
					std::cout << "There is no Meal in the Restaurant!\n";
					Sleep(1000);
				}
				else
				{
					db->Show_summary_of_the_meals();

					int id{};

					std::string question = "Do you want to delete all Meal(s) ?";
					std::wstring w_question = std::wstring(question.begin(), question.end());
					LPCWSTR text = w_question.c_str();

					result = MessageBox(NULL, text, caption, MB_YESNO | MB_ICONQUESTION);

					system("CLS");

					if (result == IDYES)
					{
						db->Delete_all_meals();

						db->Push_all_meal_data_to_file();
						db->Push_more_info_about_meal_to_file();
						db->Push_less_info_about_meal_to_file();
						db->Push_useful_meal_numbers_to_file();

						std::cout << "All Meals deleted successfully!\n";
					}
					else
					{
						while (true)
						{
							db->Show_summary_of_the_meals();

							std::cout << "\nWhich ID Meal do you want to delete, If you enter 0 nothing will be deleted in the Restaurant.\nEnter: ";
							Helper::Check_is_input_number(id);

							if (id == 0)
								break;

							if (db->Delete_meal_with_id(id) == false)
							{
								try
								{
									throw InvalidArgumentException("There is No [" + std::to_string(id) + "] ID meal exist in the Restaurant!", __LINE__, __FILE__);
								}
								catch (const Exception& ex)
								{
									system("CLS");
									std::cout << ex << '\n';
									FileHelper::Append_file_in_text_format(FileHelper::exception_file_name, ex.Get_data());
									Sleep(1000);
								}
								system("CLS");
							}
							else
								break;

							system("CLS");
						}

						system("CLS");
						if (id != 0)
						{
							std::cout << "Meal Successfully Deleted!\n";

							db->Push_all_meal_data_to_file();
							db->Push_more_info_about_meal_to_file();
							db->Push_less_info_about_meal_to_file();
							db->Push_useful_meal_numbers_to_file();
						}
						else
							std::cout << "No meal was deleted in the Restaurant!\n";
					}
					Sleep(1000);
				}

			}
			break;

			case Admin_Menu::Kitchen::Update_Meal:
			{
				size_t length = db->Get_meals().size();
				if (length == 0ui64)
				{
					std::cout << "There is no Meal in the Restaurant!\n";
					Sleep(1000);
				}
				else
				{
					int id{};
					int index{};

					while (true)
					{

						db->Show_summary_of_the_meals();

						std::cout << "\nWhich ID meal do you want to update: ";
						Helper::Check_is_input_number(id);

						index = db->Is_meal_id_exist(id);

						try
						{
							if (index < 0)
								throw InvalidArgumentException("There is no [" + std::to_string(id) + "] ID meal in the Restaurant", __LINE__, __FILE__);
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

					std::cin.ignore(1, '\n');
					system("CLS");

					while (true)
					{
						std::string name{};
						std::cout << "Update Meal Name: ";
						std::getline(std::cin, name);

						std::string category{};
						std::cout << "Update Meal Category: ";
						std::getline(std::cin, category);

						float rating{};
						std::cout << "Update Meal Rating: ";
						while (true)
						{
							Helper::Check_is_input_number_and_not_equal_to_zero(rating);
							if (Helper::Chech_meal_rating(rating))
								break;
						}



						try
						{
							db->Get_meals()[index]->Set_name(name);
							db->Get_meals()[index]->Set_category(category);
							db->Get_meals()[index]->Set_rating(rating);

							db->Push_all_meal_data_to_file();//butun data seliqeli
							db->Push_more_info_about_meal_to_file();//cox data oxumaq uchun fayldan
							db->Push_less_info_about_meal_to_file();//az data oxumaq uchun fayldan

							break;
						}
						catch (const Exception& ex)
						{
							std::cin.ignore(1, '\n');
							system("CLS");
							std::cout << ex << '\n';
							FileHelper::Append_file_in_text_format(FileHelper::exception_file_name, ex.Get_data());
							Sleep(1000);
							system("CLS");
						}
					}
				}
			}
			break;

			case Admin_Menu::Kitchen::Delete_Notification:
			{
				int id{};
				size_t length = db->Get_notes().size();

				if (length != 0ui64)
				{
					std::string question = "Do you want to delete all Notifications ?\nIF you choose NO you jump to delete Notificiation with ID page";
					std::wstring w_question = std::wstring(question.begin(), question.end());
					LPCWSTR text = w_question.c_str();

					result = MessageBox(NULL, text, caption, MB_YESNO | MB_ICONQUESTION);

					if (result == IDYES)
					{
						db->Delete_all_notifications();
						std::cout << "All Notifications are deleted!\n";
					}
					else
					{
						while (true)
						{
							db->Print_notifications_with_no_operation();
							std::cout << "\nWhich ID Notification do you want to delete( IF you choose 0 you don't delete\
 any notification in the database ! )\nEnter: ";
							Helper::Check_is_input_number(id);

							if (id == 0)
								break;

							try
							{
								if (db->Is_notification_id_exist(id) < 0)
									throw InvalidArgumentException("There is no [" + std::to_string(id) + "] ID exists in the Notification!", __LINE__, __FILE__);
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
						if (id != 0)
						{
							db->Delete_notification_with_id(id);
							std::cout << "Notification Successfully deleted!!!\n";
						}
						else
							std::cout << "Notification didn't deleted!\n";

						Sleep(1000);
					}
				}
				else
				{
					std::cout << "There is no Notification in the DataBase!\n";
					Sleep(1000);
				}
			}
			break;
			}
		}
	}
}