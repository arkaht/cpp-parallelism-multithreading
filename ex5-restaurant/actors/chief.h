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

		restaurant& _restaurant;
	};

}