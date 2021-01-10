#pragma once
#include <string>

#define SizeOfCreateTime 26

class Exception
{

private:
	std::string text;
	long line;
	std::string file_name;
	char create_time[SizeOfCreateTime];

public:

	Exception(const std::string& text, const long& line, const std::string& file_name);

	void Set_text(const std::string& text);
	std::string Get_text() const;

	void Set_line(const long& line);
	long Get_line() const;

	void Set_file_name(const std::string& file_name);
	std::string Get_file_name() const;

	const char* Get_create_time() const;

	std::string Get_data() const;

	friend std::ostream& operator << (std::ostream& out, const Exception& exception);

};

class DataBaseException : public Exception
{
public:

	DataBaseException(const std::string& text, const long& line, const std::string& file_name);

};

class InvalidArgumentException : public Exception
{
public:

	InvalidArgumentException(const std::string& text, const long& line, const std::string& file_name);

};