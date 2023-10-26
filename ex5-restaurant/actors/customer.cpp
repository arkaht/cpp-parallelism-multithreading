#include "customer.h"

using namespace vkr;

void customer::thread_run()
{
	talk( "is taking a seat" );
	_state = &customer::state_order;

	run_loop( this );
}

void customer::state_order()
{
	sleep_ms( 500 );

	//  prepare order
	meal_chosen_message order {};
	order.customer = this;
	order.ingredients = std::vector( {
		ingredient( "Carrot" ),
		ingredient( "Potato" ),
		ingredient( "Steak" ),
	} );

	//  send order
	_restaurant.get_waiters_box().send( order );
	talk( "chose his meal" );

	//  transit to wait state
	_state = &customer::state_wait;
}

void customer::state_wait() 
{
	auto incoming = _message_box.read();
	
	//  wait for meal
	incoming->handle<meal_ready_message>(
		[&]( auto msg )
		{
			talk( "received his meal" );

			//  transit to eat state
			_state = &customer::state_eat;
		}
	);
}

void customer::state_eat() 
{
	talk( "is eating" );

	sleep_ms( 1500 );

	talk( "finished his meal" );

	//  transit to exit state
	_state = &customer::state_exit;
}

void customer::state_exit() 
{
	talk( "left the restaurant" );
	
	//  stop thread
	_is_running = false;
}
