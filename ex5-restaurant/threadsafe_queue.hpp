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
		void push( T&& element )
		{
			std::lock_guard lock( _mutex );
			_queue.push( std::make_shared( element ) );
			_cond_var.notify_all();
		}

		std::shared_ptr<T> wait_n_pop()
		{
			std::unique_lock<std::mutex> lock( _mutex );
			_cond_var.wait( lock, [&]() { return !_queue.empty(); } );

			auto element = _queue.front();
			_queue.pop();

			return element;
		}

	private:
		std::mutex _mutex;
		std::queue<std::shared_ptr<T>> _queue;
		std::condition_variable _cond_var;
	};
}