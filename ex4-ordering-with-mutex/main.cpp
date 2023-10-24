#include <iostream>
#include <thread>
#include <mutex>

std::mutex mutex;
const int MAX_N = 100;

void thread_print_odd_numbers()
{
	for ( int i = 0; i <= MAX_N; i++ )
	{
		if ( i % 2 == 0 ) 
		{
			std::lock_guard guard( mutex );
			continue;
		}

		std::cout << i << std::endl;
	}
}

void thread_print_even_numbers()
{
	for ( int i = 0; i <= MAX_N; i++ )
	{
		if ( i % 2 != 0 )
		{
			std::lock_guard guard( mutex );
			continue;
		}

		std::cout << i << std::endl;
	}
}

int main()
{
	std::thread thread0( thread_print_odd_numbers );
	std::thread thread1( thread_print_even_numbers );

	thread0.join();
	thread1.join();
}
