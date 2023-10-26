#pragma once

#include "utils.hpp"
#include "thread_state_machine.hpp"
#include "restaurant.hpp"

namespace vkr 
{
	class customer : 
		public thread_state_machine<customer>, 
		public messager
	{
	public:
		customer( restaurant& restaurant )
			: _restaurant( restaurant )
		{}

		DEFINE_TALK_METHOD( Customer );

		void thread_run();

	private:
		void state_order();
		void state_wait();
		void state_eat();
		void state_exit();

		//  states data
		struct 
		{
			physical_meal meal;
		} _eat_data;

		restaurant& _restaurant;
	};
}

