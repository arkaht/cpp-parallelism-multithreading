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
	sleep_ms( 500 );

	//  prepare order
	meal_chosen_message order {};
	order.customer = this;

	//  send order
	_restaurant.get_waiters_box().send( order );
	talk( "I have chosen my meal!" );

	//  transit to wait state
	_state = &customer::state_wait;
}

void customer::state_wait() 
{
	auto msg = _message_box.read();
	
	//  wait for meal
	if ( auto data = std::dynamic_pointer_cast<meal_served_message>( msg ) )
	{
		talk( "I have received my meal.." );

		//  transit to eat state
		_state = &customer::state_eat;
	}
}

void customer::state_eat() 
{
	talk( "let's eat!" );

	sleep_ms( 1500 );

	talk( "I have finished my meal, I leave now." );

	//  transit to exit state
	_state = &customer::state_exit;
}

void customer::state_exit() 
{
	talk( "I have left the restaurant" );
	
	//  stop thread
	_is_running = false;
}
