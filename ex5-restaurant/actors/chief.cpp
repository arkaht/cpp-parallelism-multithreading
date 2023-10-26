#include "chief.h"

using namespace vkr;

void chief::thread_run()
{
	_state = &chief::state_wait;
	run_loop( this );
}

void chief::state_wait() 
{
	auto incoming = _restaurant.get_chiefs_box().read();

	//  called when a waiter took an order from a customer
	incoming->handle<meal_chosen_message>( 
		[&]( auto msg )
		{
			_meal_customer = msg.customer;
			talk( "received an order, dispatching ingredients to cookers" );

			//  TODO: do ingredients
			auto& box = _restaurant.get_cookers_box();
			box.send( ingredient_chosen_message {} );
		}
	);

	//  called when a cooker finished an ingredient
	incoming->handle<ingredient_cooked_message>( 
		[&]( auto msg )
		{
			//  transit to mix state
			_state = &chief::state_mix;
		}
	);
}

void chief::state_mix() 
{
	talk( "is composing a meal with ingredients" );
	sleep_ms( 1500 );

	//  prepare order
	meal_ready_message msg {};
	msg.customer = _meal_customer;

	//  send meal to waiters
	_restaurant.get_waiters_box().send( msg );

	talk( "finished mixing the meal" );

	//  transit to wait state
	_state = &chief::state_wait;
}
