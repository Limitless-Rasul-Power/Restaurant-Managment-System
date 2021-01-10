#include "Confirmation_Helper.h"
#include <string>

void Helper::Check_choice(char& choice, const char& max_limit)
{
	while (choice <= '0' || choice > max_limit)
	{
		std::cout << "Enter one of this choices: ";
		std::cin >> choice;
	}
}

bool Helper::Chech_meal_rating(float& meal_rating)
{
	while (meal_rating < 0.0 || meal_rating > 5.0f)
	{
		std::cout << "Enter Number between 0 - 5: ";
		while (!(std::cin >> meal_rating)) 
		{
			std::cout << "Enter Number between 0 - 5: ";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
	}
	return true;
}

void Helper::Check_is_empty(std::string& text)
{
	while (text.empty())
	{
		std::cout << "It is empty, please fill it\nEnter: ";
		std::getline(std::cin, text);
	}
}