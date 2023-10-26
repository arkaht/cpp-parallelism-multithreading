#pragma once

#include "macros.hpp"
#include "thread_state_machine.hpp"

namespace vkr 
{
	class customer : public thread_state_machine<customer>
	{
	public:
		DEFINE_TALK_METHOD( Customer );

		void thread_run();

	private:
		void state_order();
		void state_wait();
		void state_eat();
		void state_exit();
	};
}

