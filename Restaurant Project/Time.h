#pragma once
#include <ctime>
inline void Set_create_time(char* const& date)
{
	time_t now = time(NULL);
	ctime_s(date, 26 * sizeof(char), &now);
}