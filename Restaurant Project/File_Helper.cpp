#include "File_Helper.h"
#include <iostream>
#include <fstream>
#include <sstream>

void FileHelper::Append_file_in_text_format(const std::string& file_name, const std::string& text)
{
	std::ofstream fout(file_name, std::ios_base::app);

	if (fout.is_open())
		fout << text;
	else
		std::cout << "File could not be opened!\n";

	fout.close();
}

void FileHelper::Append_file_in_binary_format(const std::string& file_name, const std::string& text)
{
	std::ofstream fout(file_name, std::ios_base::binary | std::ios_base::app);

	if (fout.is_open())
		fout.write(text.c_str(), text.size());
	else
		std::cout << "File could not be opened!\n";

	fout.close();
}

void FileHelper::Append_file_in_binary_format(const std::string& file_name, const size_t& text)
{
	std::ofstream fout(file_name, std::ios_base::binary | std::ios_base::app);

	if (fout.is_open())
		fout.write(reinterpret_cast<const char*>(&text), sizeof(text));
	else
		std::cout << "File could not be opened!\n";

	fout.close();
}

void FileHelper::Write_file_in_text_format(const std::string& file_name, const std::string& text)
{
	std::ofstream fout(file_name);

	if (fout.is_open())
		fout << text;
	else
		std::cout << "File could not be opened!\n";

	fout.close();
}

void FileHelper::Write_file_in_binary_format(const std::string& file_name, const std::string& text)
{
	std::ofstream fout(file_name, std::ios_base::binary);

	if (fout.is_open())
		fout.write(text.c_str(), text.size());
	else
		std::cout << "File could not be opened!\n";

	fout.close();
}

void FileHelper::Write_file_in_binary_format(const std::string& file_name, const size_t& text)
{
	std::ofstream fout(file_name);

	if (fout.is_open())
		fout << text;
	else
		std::cout << "File could not be opened!\n";

	fout.close();
}