#pragma once

#include "messages.hpp"
#include "meal.hpp"

namespace vkr
{
	using menu = std::vector<recipe>;

	class restaurant
	{
	public:
		restaurant( const menu& menu )
			: _menu( menu ) {}

		physical_ingredient create_physical_ingredient( ingredient obj )
		{
			auto physical = std::make_shared<ingredient>( obj );
			
			physical_ingredients.push_back( physical );
			return physical;
		}
		physical_meal create_physical_meal( meal obj )
		{
			auto physical = std::make_shared<meal>( obj );

			physical_meals.push_back( physical );
			return physical;
		}

		void talk( const std::string& text )
		{
			std::lock_guard lock( _cout_mutex );
			std::cout << text;
		}

		const menu& get_menu() { return _menu; }

		message_box& get_waiters_box() { return _waiters_box; }
		message_box& get_cookers_box() { return _cookers_box; }
		message_box& get_chiefs_box() { return _chiefs_box; }

	private:
		std::mutex _cout_mutex;

		std::vector<physical_ingredient> physical_ingredients;
		std::vector<physical_meal> physical_meals;

		menu _menu;

		message_box _waiters_box;
		message_box _cookers_box;
		message_box _chiefs_box;
	};
}