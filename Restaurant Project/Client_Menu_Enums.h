#pragma once
namespace Client_Menu
{
	namespace Entry
	{
		enum Choice : char
		{
			Show_All_Menu = '1', Search_Meal = '2', Exit_From_Menu = '3', Exit_From_Restaurant = '4'
		};
	}

	namespace Request
	{
		enum Choice : char
		{
			Order = '1', Show_More_Information = '2', Back = '3'
		};
	}

	namespace Category
	{
		enum Choice : char
		{
			Add_More_Ingredient = '1', Order = '2'
		};
	}
}