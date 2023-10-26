#include "customer.h"

using namespace vkr;

void customer::thread_run()
{
	talk( "I'm taking a seat." );
	_state = &customer::state_order;

	run_loop( this );
}

void customer::state_order()
{
	std::this_thread::sleep_for( std::chrono::milliseconds( 500 ) );

	talk( "I have chosen my meal!" );
	_state = &customer::state_wait;
}

void customer::state_wait() {}

void customer::state_eat() {}

void customer::state_exit() {}
