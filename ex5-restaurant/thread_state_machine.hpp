#pragma once

//  default includes for actors
#include <iostream>
#include <chrono>
#include <thread>

namespace vkr
{
	template <typename T>
	class thread_state_machine
	{
	public:
		virtual void thread_run() = 0;

	protected:
		void run_loop( T* self )
		{
			while ( true ) 
			{ 
				run_state( self ); 
			}
		}
		void run_state( T* self ) { (self->*state)(); }
		void (T::*state)();
	};
}