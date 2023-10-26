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

	auto& menu = _restaurant.get_menu();

	//  prepare order
	meal_chosen_message msg {};
	msg.customer = this;
	msg.recipe = random::generate( menu );

	//  send order
	_restaurant.get_waiters_box().send( msg );
	talk( "chose his meal: '" + msg.recipe.name + "' (" + ingredient::concat_as_text( msg.recipe.ingredients ) + ")" );

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
			_eat_data.meal = msg.meal;
			talk( "received his meal" );

			//  transit to eat state
			_state = &customer::state_eat;
		}
	);
}

void customer::state_eat() 
{
	//  eating
	while ( _eat_data.meal->get_proportion() > 0.0f )
	{
		sleep_ms( 500 );
		_eat_data.meal->eat( random::generate( 0.15f, 0.45f ) );
		
		//  show progress
		float progress = ( 1.0f - _eat_data.meal->get_proportion() ) * 100.0f;
		talk( 
			"is eating.. (" 
		  + std::format( "{:.0f}", progress ) + "%)" 
		);
	}

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
