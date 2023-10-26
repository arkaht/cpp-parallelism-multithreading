#pragma once

#include "message_box.hpp"

namespace vkr
{
	class customer;

	struct meal_chosen_message : public message
	{
		customer* customer;
		//  std::array<ingredient, 3> ingredients;
	};
	struct meal_ready_message : public message 
	{
		customer* customer;
	};

	struct ingredient_chosen_message : public message
	{
		//  ingredient ingredient;
	};
	struct ingredient_cooked_message : public message
	{
		//  ingredient ingredient;
	};
};