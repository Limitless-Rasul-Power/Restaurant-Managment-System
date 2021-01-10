#pragma once
#include <string>
#include "Base.h"

#define SizeOfCreateTime 26

class Notification : public Base
{

private:
	std::string text;
	std::string table_name;
	bool is_read;
	char create_time[SizeOfCreateTime];

public:

	static unsigned int note_id;

	Notification(const std::string& text, const std::string& table_name);

	void Set_text(const std::string& text);
	std::string Get_text() const;

	void Set_table_name(const std::string& table_name);
	std::string Get_table_name() const;

	void Set_is_read(const bool& is_read);
	bool Is_read() const;

	static unsigned int Get_current_id();

	const char* Get_create_time() const;

	void Show() const;

};