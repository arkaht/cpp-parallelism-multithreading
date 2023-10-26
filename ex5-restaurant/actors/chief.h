#pragma once

#include "macros.hpp"
#include "thread_state_machine.hpp"

namespace vkr
{
	class chief : public thread_state_machine<chief>
	{
	public:
		DEFINE_TALK_METHOD( Chief );
		
		void thread_run();

	private:
		void state_wait();
		void state_mix();
	};

}