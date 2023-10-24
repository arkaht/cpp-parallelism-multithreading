#include <iostream>
#include <thread>
#include <semaphore>
#include <mutex>
#include <string>

int x = 0;
std::mutex mutex;
const int MAX_N = 1000;

void thread_odd_even( bool is_odd )
{
	while ( x < MAX_N )
	{
		std::lock_guard lock( mutex );
		if ( x % 2 == is_odd ) continue;

		std::cout << x << std::endl;
		x++;
	}
}

int main()
{
	std::thread thread0( thread_odd_even, true );
	std::thread thread1( thread_odd_even, false );

	thread0.join();
	thread1.join();
}
