#pragma once
#include <string>
class FileHelper
{
public:

	static const std::string exception_file_name;
	static const std::string is_program_run;

	static const std::string show_more_info_about_meals;
	static const std::string show_stock;

	static const std::string read_more_info_about_meals;
	static const std::string read_less_info_about_meals;
	static const std::string read_stock;

	static const std::string useful_number_for_ingredients;
	static const std::string useful_number_for_meals;

	static const std::string restaurant_budget;

	static void Append_file_in_text_format(const std::string& file_name, const std::string& text);
	static void Append_file_in_binary_format(const std::string& file_name, const std::string& text);
	static void Append_file_in_binary_format(const std::string& file_name, const size_t& text);

	static void Write_file_in_text_format(const std::string& file_name, const std::string& text);

	static void Write_file_in_binary_format(const std::string& file_name, const std::string& text);
	static void Write_file_in_binary_format(const std::string& file_name, const size_t& text);
};