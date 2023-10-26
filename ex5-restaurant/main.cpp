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
	vkr::restaurant restaurant {};

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