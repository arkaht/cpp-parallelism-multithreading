#pragma once

#include "macros.hpp"
#include "thread_state_machine.hpp"

namespace vkr
{
	class cooker : public thread_state_machine<cooker>
	{
	public:
		DEFINE_TALK_METHOD( Cooker );
		
		void thread_run();

	private:
		void state_wait();
		void state_cook();
	};
}
