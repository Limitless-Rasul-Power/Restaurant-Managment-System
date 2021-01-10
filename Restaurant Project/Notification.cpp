#include <iostream>
#include "Exception.h"
#include "Notification.h"
#include "Time.h"

Notification::Notification(const std::string& text, const std::string& table_name)
	:Base(++note_id)
{
	Set_text(text);
	Set_table_name(table_name);
	Set_create_time(this->create_time);
	this->is_read = false;
}

void Notification::Set_text(const std::string& text)
{
	if (text.empty())
		throw InvalidArgumentException("Text is Empty!", __LINE__, __FILE__);

	this->text = text;
}

std::string Notification::Get_text() const
{
	return text;
}

void Notification::Set_table_name(const std::string& table_name)
{
	if (table_name.empty())
		throw InvalidArgumentException("Table name is Empty!", __LINE__, __FILE__);

	this->table_name = table_name;
}

std::string Notification::Get_table_name() const
{
	return table_name;
}

void Notification::Set_is_read(const bool& is_read)
{
	this->is_read = is_read;
}

bool Notification::Is_read() const
{
	return is_read;
}

unsigned int Notification::Get_current_id()
{
	return note_id;
}

const char* Notification::Get_create_time() const
{
	return create_time;
}

void Notification::Show() const
{
	std::cout << "Notification Text: " << Get_text() << '\n';
	std::cout << "Table Name: " << Get_table_name() << '\n';
	std::cout << "Notification Create Time: " << Get_create_time() << "\n\n";
}