#pragma once

#include <random>

namespace vkr
{
	class random
	{
	public:
		static int generate( int min, int max )
		{
			static std::mt19937 _generator( (unsigned int)std::time( nullptr ) );
			std::uniform_int_distribution<> dist( min, max );
			return dist( _generator );
		}

		static float generate( float min, float max )
		{
			static std::mt19937 _generator( (unsigned int)std::time( nullptr ) );
			std::uniform_real_distribution<> dist( (double)min, (double)max );
			return (float)dist( _generator );
		}

		template <typename T>
		static const T& generate( const std::vector<T>& list )
		{
			return list[generate( 0, (int)list.size() - 1 )];
		}

	};
}