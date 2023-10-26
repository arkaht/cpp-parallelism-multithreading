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
	struct meal_served_message : public message {};
	struct meal_ready_message : public message {};
};