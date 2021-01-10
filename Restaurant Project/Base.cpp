#include "Base.h"
#include "Exception.h"

Base::Base() :id(0U)
{}

Base::Base(const int& id)
{
	Set_id(id);
}

void Base::Set_id(const int& id)
{
	if (id < 0)
		throw InvalidArgumentException("ID must be more than 0!", __LINE__, __FILE__);

	this->id = id;
}

unsigned int Base::Get_id() const
{
	return id;
}