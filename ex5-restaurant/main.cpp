#include <iostream>
#include <thread>
#include <chrono>

#include "actors/customer.h"
#include "actors/waiter.h"
#include "actors/cooker.h"
#include "actors/chief.h"
#include "restaurant.hpp"

int main()
{
	//  reset random seed
	//vkr::srand();
	
	//  init restaurant
	vkr::restaurant restaurant(
		vkr::menu {
			vkr::recipe {
				"Steak with mashed carrots and potatoes",
				std::vector( {
					vkr::ingredient( "Carrot" ),
					vkr::ingredient( "Potato" ),
					vkr::ingredient( "Steak" ),
				} )
			},
			vkr::recipe {
				"Beef Sirloin with Chips",
				std::vector( {
					vkr::ingredient( "Steak" ),
					vkr::ingredient( "Potato" ),
				} ),
			},
			vkr::recipe {
				"Cheeseburger",
				std::vector {
					vkr::ingredient( "Steak" ),
					vkr::ingredient( "Bread" ),
					vkr::ingredient( "Tomato" ),
					vkr::ingredient( "Salad" ),
					vkr::ingredient( "Cheese" ),
				}
			},
			vkr::recipe {
				"Smoked salmon with chive sauce",
				std::vector {
					vkr::ingredient( "Salmon" ),
					vkr::ingredient( "Chive" ),
					vkr::ingredient( "Bread" ),
					vkr::ingredient( "Butter" ),
				}
			},
		}
	);

	/*for ( int i = 0; i < 100; i++ )
	{
		std::cout << vkr::rand( 0, 2 ) << vkr::rand( restaurant.get_menu() ).name << std::endl;
	}*/

	//  init actors
	vkr::customer customer( restaurant );
	vkr::waiter waiter( restaurant );
	vkr::cooker cooker( restaurant );
	vkr::chief chief( restaurant );

	std::cout << "The Restaurant is opening!" << std::endl;

	//  init threads
	std::thread thread_customer( &vkr::customer::thread_run, &customer );
	std::thread thread_waiter( &vkr::waiter::thread_run, &waiter );
	std::thread thread_cooker( &vkr::cooker::thread_run, &cooker );
	std::thread thread_chief( &vkr::chief::thread_run, &chief );

	//  waiting threads
	thread_customer.join();
	thread_waiter.join();
	thread_cooker.join();
	thread_chief.join();
}