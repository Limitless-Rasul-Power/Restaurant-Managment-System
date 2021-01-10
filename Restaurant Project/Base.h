#pragma once
enum Choices : char
{
	Zero = '0', First = '1', Second = '2', Third = '3', Fourth = '4', Fifth = '5', Sixth = '6', Seventh = '7', Eigth = '8'
};

namespace Main_Menu
{
	enum Choice : char
	{
		Client = '1', Admin = '2', Exit = '3'
	};
}

class Base
{

protected:
	unsigned int id;

public:

	Base();

	explicit Base(const int& id);

	void Set_id(const int& id);
	unsigned int Get_id() const;

	virtual ~Base() = 0
	{}
};