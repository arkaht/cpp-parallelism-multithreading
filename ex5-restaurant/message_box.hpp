#pragma once

#include <functional>

#include "threadsafe_queue.hpp"

namespace vkr
{
	/*
	 *  Base class for a message data structure
	 */
	struct message : public std::enable_shared_from_this<message>
	{
		virtual ~message() {}

		template <typename T>
		void handle( std::function<void( const T& )> callback )
		{
			auto msg = std::dynamic_pointer_cast<T>( shared_from_this() );
			if ( !msg ) return;

			callback( *msg.get() );
		}
	};

	/*
	 *  Holding a vkr::threadsafe_queue of vkr::message.
	 *  Allows to send and read messages
	 */
	class message_box 
	{
	public:
		template <typename T>
		void send( const T& msg )
		{
			_inbox.push( std::make_shared<T>( msg ) );
		}

		std::shared_ptr<message> read()
		{
			return _inbox.wait_n_pop();
		}

	private:
		threasafe_queue<std::shared_ptr<message>> _inbox;
	};

	/*
	 *  Holding a vkr::message_box that can be publicly accessed
	 */
	class messager
	{
	public:
		message_box& get_message_box() { return _message_box; }

	protected:
		message_box _message_box;
	};
}