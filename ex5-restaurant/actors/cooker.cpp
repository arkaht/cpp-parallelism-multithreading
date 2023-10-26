#include "cooker.h"

using namespace vkr;

void cooker::thread_run()
{
	state = &cooker::state_wait;
	run_loop( this );
}

void cooker::state_wait() {}

void cooker::state_cook() {}
