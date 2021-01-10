#pragma once
#include "Database.h"
#include "File_Helper.h"

unsigned int Notification::note_id = 0U;
unsigned int Ingredient::ingredient_id = 0U;
unsigned int Meal::meal_id = 0U;
unsigned int Order::order_id = 0U;
unsigned int Table::table_id = 0U;
unsigned int Admin::admin_id = 0U;

const std::string FileHelper::exception_file_name = "Error Log.txt";
const std::string FileHelper::is_program_run = "Is Program Run Before.bin";

const std::string FileHelper::show_more_info_about_meals = "More Info About Meals.txt";
const std::string FileHelper::show_stock = "Show Stock.txt";

const std::string FileHelper::read_more_info_about_meals = "Read More Info About Meals.txt";
const std::string FileHelper::read_less_info_about_meals = "Read Less Info About Meals.txt";

const std::string FileHelper::useful_number_for_ingredients = "Useful Numbers for Ingredients.txt";
const std::string FileHelper::useful_number_for_meals = "Useful Numbers for Meals.txt";

const std::string FileHelper::read_stock = "Read Stock.txt";

const std::string FileHelper::restaurant_budget = "Restaurant Budget.bin";