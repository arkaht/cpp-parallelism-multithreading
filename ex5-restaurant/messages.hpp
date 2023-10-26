#pragma once

#include <vector>

#include "message_box.hpp"
#include "meal.hpp"

namespace vkr
{
	class customer;

	struct meal_chosen_message : public message
	{
		customer* customer;
		std::vector<ingredient> ingredients;
	};
	struct meal_ready_message : public message 
	{
		customer* customer;
		physical_meal meal;
	};

	struct ingredient_chosen_message : public message
	{
		physical_ingredient ingredient;
	};
	struct ingredient_cooked_message : public message
	{
		physical_ingredient ingredient;
	};
};