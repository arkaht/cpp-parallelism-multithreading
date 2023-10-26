#pragma once

#include "utils.hpp"
#include "thread_state_machine.hpp"
#include "restaurant.hpp"

namespace vkr
{
	class waiter : public thread_state_machine<waiter>
	{
	public:
		waiter( restaurant& restaurant )
			: _restaurant( restaurant )
		{}

		DEFINE_TALK_METHOD( Waiter );
		
		void thread_run();

	private:
		void state_wait();
		void state_take_order();
		void state_bring_meal();

		restaurant& _restaurant;
	};
}
