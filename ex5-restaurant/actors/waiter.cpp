#include "waiter.h"

using namespace vkr;

void waiter::thread_run()
{
	_state = &waiter::state_wait;
	run_loop( this );
}

void waiter::state_wait() {}

void waiter::state_take_order() {}

void waiter::state_bring_meal() {}
