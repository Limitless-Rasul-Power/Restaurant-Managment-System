#include "Exception.h"
#include "Time.h"
#include <iostream>

Exception::Exception(const std::string& text, const long& line, const std::string& file_name)
{
	Set_text(text);
	Set_line(line);
	Set_file_name(file_name);
	Set_create_time(this->create_time);
}

void Exception::Set_text(const std::string& text)
{
	this->text = text;
}

std::string Exception::Get_text() const
{
	return text;
}

void Exception::Set_line(const long& line)
{
	this->line = line;
}

long Exception::Get_line() const
{
	return line;
}

void Exception::Set_file_name(const std::string& file_name)
{
	this->file_name = file_name;
}

std::string Exception::Get_file_name() const
{
	return file_name;
}

const char* Exception::Get_create_time() const
{
	return create_time;
}

std::string Exception::Get_data() const
{
	std::string data{};
	data.append("Reason: " + Get_text() + '\n');
	data.append("File Name: " + Get_file_name() + '\n');
	data.append("Line: " + std::to_string(line) + '\n');
	data.append("Created Time: " + static_cast<std::string>(Get_create_time()) + '\n');

	return data;
}

DataBaseException::DataBaseException(const std::string& text, const long& line, const std::string& file_name)
	:Exception(text, line, file_name)
{}

InvalidArgumentException::InvalidArgumentException(const std::string& text, const long& line, const std::string& file_name)
	:Exception(text, line, file_name)
{}

std::ostream& operator << (std::ostream& out, const Exception& exception)
{
	out << "Exception Text: " << exception.Get_text() << '\n';
	out << "Exception Line: " << exception.Get_line() << '\n';
	out << "Exception File Name: " << exception.Get_file_name() << '\n';
	out << "Exception Create Time: " << exception.Get_create_time() << "\n\n";

	return out;
}