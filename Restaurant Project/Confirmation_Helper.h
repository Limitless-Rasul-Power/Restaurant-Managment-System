#pragma once
#include <iostream>
#include <string>
#include <sstream>
class Helper
{
public:
	static void Check_choice(char& choice, const char& max_limit);

	static bool Chech_meal_rating(float& meal_rating);

	static void Check_is_empty(std::string& text);


	template<typename T>
	static void Check_is_input_number_and_not_equal_to_zero(T& number)
	{
		while (!(std::cin >> number) || number <= static_cast<T>(0))
		{
			std::cout << "Enter Postive Number: ";
			std::cin.clear();
			std::cin.ignore();
		}
	}

	template<typename T>
	static void Check_is_input_number(T& number)
	{
		while (!(std::cin >> number))
		{
			std::cout << "Enter Number: ";
			std::cin.clear();
			std::cin.ignore();
		}
	}

	template<typename T>
	static void Chech_lesser_than_zero_input(T& number)
	{
		while (number <= static_cast<T>(0))
		{
			std::cout << "Number must be more than 0!\nEnter again: ";
			std::cin >> number;
		}
	}

};