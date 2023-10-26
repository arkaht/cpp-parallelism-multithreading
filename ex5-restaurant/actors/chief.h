#pragma once

#include "macros.hpp"
#include "thread_state_machine.hpp"
#include "restaurant.hpp"

namespace vkr
{
	class chief : public thread_state_machine<chief>
	{
	public:
		chief( restaurant& restaurant )
			: _restaurant( restaurant )
		{}

		DEFINE_TALK_METHOD( Chief );
		
		void thread_run();

	private:
		void state_wait();
		void state_mix();

		void dispatch_ingredients();

		//  states data
		struct 
		{
			customer* customer;
			std::vector<ingredient> recipe;
			physical_meal meal;
			physical_ingredient ingredient;
		} _mix_data;

		restaurant& _restaurant;
	};

}