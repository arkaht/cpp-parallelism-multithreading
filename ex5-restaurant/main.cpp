#include <iostream>
#include <thread>
#include <chrono>

#include "actors/customer.h"
#include "actors/waiter.h"
#include "actors/cooker.h"
#include "actors/chief.h"

int main()
{
	//  init actors
	vkr::customer customer {};
	vkr::waiter waiter {};
	vkr::cooker cooker {};
	vkr::chief chief {};

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