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
		void sleep_ms( int ms ) 
		{
			std::this_thread::sleep_for( std::chrono::milliseconds( ms ) );
		}

		void run_loop( T* self )
		{
			while ( _is_running ) 
			{ 
				run_state( self ); 
			}
		}
		void run_state( T* self ) { (self->*_state)(); }
		void (T::*_state)();
		bool _is_running = true;
	};
}