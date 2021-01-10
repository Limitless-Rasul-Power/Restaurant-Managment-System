#include "Ingredient.h"
#include "Exception.h"
#include <iostream>
#include <sstream>

Ingredient::Ingredient() :name(""), fat(0.0f), protein(0.0f), carbonhydrat(0.0f), kcal(0), price(0.0f)
{}

Ingredient::Ingredient(const std::string& name, const float& fat, const float& protein, const float& carbonhydrat, const short& kcal,
	const float& price)
	:Base(++ingredient_id)
{
	Set_name(name);
	Set_fat(fat);
	Set_protein(protein);
	Set_carbonhydrat(carbonhydrat);
	Set_kcal(kcal);
	Set_price(price);
}

void Ingredient::Set_name(const std::string& name)
{
	if (name.empty())
		throw InvalidArgumentException("Name is Empty", __LINE__, __FILE__);

	this->name = name;
}

std::string Ingredient::Get_name() const
{
	return name;
}

void Ingredient::Set_fat(const float& fat)
{
	if(fat < 0.0f)
	throw InvalidArgumentException("Fat must be more than or equal 0!", __LINE__, __FILE__);

	this->fat = fat;
}

float Ingredient::Get_fat() const
{
	return fat;
}

void Ingredient::Set_protein(const float& protein)
{
	if(protein < 0.0f)
	throw InvalidArgumentException("Protein must be more than or equal 0!", __LINE__, __FILE__);

	this->protein = protein;
}

float Ingredient::Get_protein() const
{
	return protein;
}

void Ingredient::Set_carbonhydrat(const float& carbonhydrat)
{
	if(carbonhydrat < 0.0f)
	throw InvalidArgumentException("Carbonhydrat must be more than or equal 0!", __LINE__, __FILE__);

	this->carbonhydrat = carbonhydrat;
}

float Ingredient::Get_carbonhydrat() const
{
	return carbonhydrat;
}

void Ingredient::Set_kcal(const short& kcal)
{
	if(kcal < 0U)
	throw InvalidArgumentException("Kcal must be more than or equal 0!", __LINE__, __FILE__);

	this->kcal = kcal;
}

unsigned short Ingredient::Get_kcal() const
{
	return kcal;
}

void  Ingredient::Set_price(const float& price)
{
	if (price <= 0.0f)
		throw InvalidArgumentException("Price must be more than 0!", __LINE__, __FILE__);

	this->price = price;
}

float Ingredient::Get_price() const
{
	return price;
}

unsigned int Ingredient::Get_current_id()
{
	return ingredient_id;
}

std::string Ingredient::Push_all_data_to_file()
{
	std::stringstream ss;

	ss << "Ingredient ID: " << Get_id() << '\n';
	ss << "Ingredient Name: " << Get_name() << '\n';
	ss << "Ingredient Fat: " << Get_fat() << "gr\n";
	ss << "Ingredient Kcal: " << Get_kcal() << " kcal\n";
	ss << "Ingredient Protein: " << Get_protein() << " gr\n";
	ss << "Ingredient Carbonhydrat: " << Get_carbonhydrat() << " gr\n";
	ss << "Ingredient Price: " << Get_price() << " $\n";

	return ss.str();
}

std::string Ingredient::Push_readable_data_to_file()
{
	std::stringstream ss;
	ss << Get_id() << '\n' << Get_name() << '\n' << Get_fat() << '\n' << Get_kcal() << '\n' << Get_protein() << '\n'
		<< Get_carbonhydrat() << '\n' << Get_price() << '\n';

	return ss.str();
}

void Ingredient::Show() const
{
	std::cout << "Ingredient ID: " << Get_id() << '\n';
	std::cout << "Ingredient Name: " << Get_name() << '\n';
	std::cout << "Ingredient Fat: " << Get_fat() << " gr\n";
	std::cout << "Ingredient Kcal: " << Get_kcal() << " kcal\n";
	std::cout << "Ingredient Protein: " << Get_protein() << " gr\n";
	std::cout << "Ingredient Carbohydrat: " << Get_carbonhydrat() << " gr\n";
	std::cout << "Ingredient Price: " << Get_price() << " $\n";
}