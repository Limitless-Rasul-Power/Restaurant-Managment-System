#pragma once
#include "Restaurant.h"
#include "Notification.h"
#include "Stock.h"
#include "Confirmation_Helper.h"

struct greater
{	
	bool operator()(const std::shared_ptr<Meal>& first, const std::shared_ptr<Meal>& second) const
	{
		return first->Get_rating() / static_cast<float>(first->Get_rating_count()) > second->Get_rating() / static_cast<float>(second->Get_rating_count());
	}

};

class DataBase
{

private:
	std::shared_ptr<Restaurant> restaurant;
	std::shared_ptr<Stock> stock;

	std::vector<std::shared_ptr<Meal>> meals;
	std::vector<std::shared_ptr<Order>> orders;
	std::vector<std::shared_ptr<Notification>> notes;

public:

	DataBase(const std::shared_ptr<Restaurant>& restaurant, const std::shared_ptr<Stock>& stock,
		const std::vector<std::shared_ptr<Meal>>& meals);

	void Set_restaurant(const std::shared_ptr<Restaurant>& restaurant);
	std::shared_ptr<Restaurant>& Get_restaurant();

	void Set_stock(const std::shared_ptr<Stock>& stock);
	std::shared_ptr<Stock>& Get_stock();

	void Set_meals(const std::vector<std::shared_ptr<Meal>>& meals);
	std::vector<std::shared_ptr<Meal>>& Get_meals();
	void Show_all_meals();
	void Add_meal(const std::shared_ptr<Meal>& added_meal);
	bool Delete_meal_with_id(const int& id);
	void Show_summary_of_the_meals();
	bool Search_meal(const std::string& meal_name);
	void Delete_all_meals();

	void Set_orders(const std::vector<std::shared_ptr<Order>>& orders);
	std::vector <std::shared_ptr<Order>>& Get_orders();
	void Show_all_orders();
	void Add_order(const std::shared_ptr<Order>& added_order);
	void Delete_order_with_id(const int& id);
	void Delete_all_orders();
	void Show_summary_of_the_orders();
	void Delete_orders_in_the_kitchen_with_table_no(const std::string& table_no);


	std::vector<std::shared_ptr<Notification>>& Get_notes();
	void Add_notification(const std::shared_ptr<Notification>& note);
	void Delete_notification_with_id(const int& id);
	void Show_all_notification();
	void Set_feedback_for_all_tables(const std::string& feedback);
	void Delete_all_notifications();
	size_t Get_read_note_count();
	void Print_notifications_with_no_operation();
	void Delete_notes_in_the_kitchen_with_table_no(const std::string& table_no);

	bool Is_correct_admin_credentials(const std::string& user_name, const std::string& password);
	bool Is_meal_name_already_exist(const std::string& meal_name);
	bool Is_ingredient_name_already_exist(const std::string& ingredient_name);

	int Is_table_exist(const std::string& table_no);
	int Is_meal_id_exist(const int& id);
	int Is_order_id_exist(const int& id);
	int Is_notification_id_exist(const int& id);

	void Push_all_meal_data_to_file();
	void Push_more_info_about_meal_to_file();
	void Push_less_info_about_meal_to_file();

	void Push_useful_meal_numbers_to_file();
	void Push_useful_ingredient_numbers_to_file();


	void Show();

};