#include "waiter.h"

#include "customer.h"

using namespace vkr;

void waiter::thread_run()
{
	_state = &waiter::state_wait;
	run_loop( this );
}

void waiter::state_wait() 
{
	auto incoming = _restaurant.get_waiters_box().read();

	//  called when a customer has chosen his meal
	incoming->handle<meal_chosen_message>( 
		[&]( auto msg ) {
			talk( "is passing the order of a customer to kitchens" );

			//  gives the order to kitchens
			auto& box = _restaurant.get_chiefs_box();
			box.send( msg );
		} 
	);

	//  called when kitchens have finished to prepare the meal
	incoming->handle<meal_ready_message>(
		[&]( auto msg )
		{
			talk( "is delivering a meal to a customer" );
			sleep_ms( 500 );

			//  serving meal
			auto& box = msg.customer->get_message_box();
			box.send( msg );
			talk( "has served the customer's meal" );
		}
	);
}

void waiter::state_take_order() {}

void waiter::state_bring_meal() {}
