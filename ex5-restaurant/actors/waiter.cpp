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

	incoming->handle<meal_chosen_message>( 
		[&]( auto msg ) {
			talk( "Ordering a meal for customer.." );

			sleep_ms( 1000 );

			auto& box = msg.customer->get_message_box();
			box.send( meal_served_message() );

			talk( "Served the customer's meal" );
		} 
	);
}

void waiter::state_take_order() {}

void waiter::state_bring_meal() {}
