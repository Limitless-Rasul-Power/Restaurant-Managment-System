#pragma once
#include "Kitchen_Menu.h"
#include "Stock_Menu.h"

namespace DataBaseAdmin
{
	void Menu(const std::shared_ptr<DataBase>& db)
	{
		system("CLS");
		std::string user_name{};
		std::cout << "Enter User Name: ";
		std::getline(std::cin, user_name);

		std::string password{};
		std::cout << "Enter Password: ";
		std::getline(std::cin, password);

		if (db->Is_correct_admin_credentials(user_name, password) == false)
		{
			system("CLS");
			throw DataBaseException("Wrong Admin Credentials!", __LINE__, __FILE__);
		}		

		while (true)
		{
			system("CLS");				
			char choice{};
			size_t length = db->Get_notes().size();

			std::cout << "\n1)Kitchen\n2)Stock\n3)Exit\n";
			if (length == 0ui64)
				std::cout << "You don't have any notifications!\n";
			else if (db->Get_read_note_count() == length)
				std::cout << "You don't have any unread notifications!\n";
			else
			std::cout << db->Get_read_note_count() << " out of " << db->Get_notes().size() << " notifications has been read!\n";

			std::cout << "Enter: ";
			std::cin >> choice;
			Helper::Check_choice(choice, Third);

			if (choice == Third)
				return;

			else if (choice == First)
				Kitchen::Menu(db, user_name);
			else
				Stock_of_ingredients::Menu(db);
		}
	}
}