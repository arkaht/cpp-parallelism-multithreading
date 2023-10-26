#include "cooker.h"

using namespace vkr;

void cooker::thread_run()
{
	_state = &cooker::state_wait;
	run_loop( this );
}

void cooker::state_wait() 
{
	auto incoming = _restaurant.get_cookers_box().read();

	incoming->handle<ingredient_chosen_message>( 
		[&]( auto msg )
		{
			talk( "received an order" );

			//  transit to cook state
			_state = &cooker::state_cook;
		}
	);
}

void cooker::state_cook() 
{
	talk( "is cooking" );

	sleep_ms( 500 );

	talk( "cooked an ingredient" );

	//  send work to chiefs
	ingredient_cooked_message msg {};
	_restaurant.get_chiefs_box().send( msg );

	//  transit to wait
	_state = &cooker::state_wait;
}
