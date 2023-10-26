#pragma once

#include "messages.hpp"

namespace vkr
{
	class restaurant
	{
	public:
		message_box& get_waiters_box() { return _waiters_box; }
		message_box& get_cookers_box() { return _cookers_box; }
		message_box& get_chiefs_box() { return _chiefs_box; }

	private:
		message_box _waiters_box;
		message_box _cookers_box;
		message_box _chiefs_box;
	};
}