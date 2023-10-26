#pragma once

#include "macros.hpp"
#include "thread_state_machine.hpp"

namespace vkr
{
	class waiter : public vkr::thread_state_machine<waiter>
	{
	public:
		DEFINE_TALK_METHOD( Waiter );
		
		void thread_run();

	private:
		void state_wait();
		void state_take_order();
		void state_bring_meal();
	};
}
