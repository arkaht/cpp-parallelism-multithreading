#include "chief.h"

using namespace vkr;

void chief::thread_run()

{
	_state = &chief::state_wait;
	run_loop( this );
}

void chief::state_wait() {}

void chief::state_mix() {}
