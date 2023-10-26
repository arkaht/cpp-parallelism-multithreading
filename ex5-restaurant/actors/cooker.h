#pragma once

#include "macros.hpp"
#include "thread_state_machine.hpp"
#include "restaurant.hpp"

namespace vkr
{
	class cooker : public thread_state_machine<cooker>
	{
	public:
		cooker( restaurant& restaurant )
			: _restaurant( restaurant )
		{}

		DEFINE_TALK_METHOD( Cooker );
		
		void thread_run();

	private:
		void state_wait();
		void state_cook();

		//  states data
		struct 
		{
			physical_ingredient ingredient;
		} _cook_data;

		restaurant& _restaurant;
	};
}
