#pragma once

#include <queue>
#include <thread>
#include <mutex>

namespace vkr
{
	template <typename T>
	class threasafe_queue
	{
	public:
		void push( const T& element )
		{
			std::lock_guard lock( _mutex );
			_queue.push( element );
			_cond_var.notify_all();
		}

		T wait_n_pop()
		{
			std::unique_lock<std::mutex> lock( _mutex );
			_cond_var.wait( lock, [&]() { return !_queue.empty(); } );

			auto element = _queue.front();
			_queue.pop();

			return element;
		}

	private:
		std::mutex _mutex;
		std::queue<T> _queue;
		std::condition_variable _cond_var;
	};
}