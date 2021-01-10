#pragma once
namespace Admin_Menu
{
	namespace Kitchen
	{
		enum Choice : char
		{
			Show_All_Orders_and_Operations = '1', Show_All_Meals = '2', Show_All_Notifications = '3',
			Add_Meal = '4', Delete_Meal = '5', Update_Meal = '6',
			Delete_Notification = '7', Back = '8'
		};

		enum Meal : char
		{
			Show_More = '1', Show_Less = '2'
		};
	}

	namespace Stock
	{
		enum Choice : char
		{
			Show_All_Ingredients = '1', Add_Ingredient = '2', Delete_Ingredient = '3', Increase_Ingredient_Amount_with_ID = '4',
			Decrease_Ingredient_Amount_with_ID = '5', Back = '6'
		};
	}
}

namespace OrderOperation
{
	enum Choice : char
	{
		Reject_All = '1', Reject_With_ID = '2', Exit_and_Accept_All = '3'
	};
}