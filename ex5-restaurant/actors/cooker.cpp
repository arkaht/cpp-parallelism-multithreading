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
			_cook_data.ingredient = msg.ingredient;
			talk( "received an order" );

			//  transit to cook state
			_state = &cooker::state_cook;
		}
	);
}

void cooker::state_cook() 
{
	auto& ingredient = _cook_data.ingredient;

	talk( "is cooking.." );

	//  work
	sleep_ms( 500 );
	ingredient->cook();
	talk( "cooked " + ingredient->get_name() );

	//  send work to chiefs
	ingredient_cooked_message msg {};
	msg.ingredient = ingredient;
	_restaurant.get_chiefs_box().send( msg );

	//  transit to wait
	_state = &cooker::state_wait;
}
