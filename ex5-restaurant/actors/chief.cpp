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
			_mix_data.meal = _restaurant.create_physical_meal( meal() );
			_mix_data.customer = msg.customer;
			_mix_data.recipe = std::move( msg.ingredients );
			talk( "received an order, dispatching ingredients to cookers" );

			dispatch_ingredients();
		}
	);

	//  called when a cooker finished an ingredient
	incoming->handle<ingredient_cooked_message>( 
		[&]( auto msg )
		{
			_mix_data.ingredient = msg.ingredient;

			//  transit to mix state
			_state = &chief::state_mix;
		}
	);
}

void chief::state_mix() 
{
	auto& meal = _mix_data.meal;
	auto& ingredient = _mix_data.ingredient;

	talk( "is mixing.." );

	//  work
	sleep_ms( 500 );
	meal->add_ingredient( ingredient );
	talk( 
		"mixed " + ingredient->get_name() + " (" 
		+ std::to_string( meal->get_ingredients_count() ) + "/" 
		+ std::to_string( (int)_mix_data.recipe.size() ) + ")"
	);

	//  is meal finally prepared?
	if ( meal->get_ingredients_count() == _mix_data.recipe.size() )
	{
		//  prepare order
		meal_ready_message msg {};
		msg.customer = _mix_data.customer;
		msg.meal = meal;

		//  send meal to waiters
		_restaurant.get_waiters_box().send( msg );

		talk( "finished mixing the meal" );
	}

	//  transit to wait state
	_state = &chief::state_wait;
}

void chief::dispatch_ingredients()
{
	auto& box = _restaurant.get_cookers_box();
	for ( auto& ingredient : _mix_data.recipe )
	{
		talk( "orders cookers to cook " + ingredient.get_name() );
		
		ingredient_chosen_message msg {};
		msg.ingredient = _restaurant.create_physical_ingredient( ingredient );
		box.send( msg );
	}
}
