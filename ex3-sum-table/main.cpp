#include <iostream>
#include <vector>
#include <thread>

int sum( const std::vector<int>& list, int start_id = 0, int last_id = -1 )
{
	int count = 0;

	if ( last_id == -1 )
	{
		last_id = (int)list.size() - 1;
	}

	for ( int i = start_id; i <= last_id; i++ )
	{
		count += list[i];
	}

	return count;
}

int sum_threaded( const std::vector<int>& list, int subdivisions )
{
	int count = 0;

	//  setup subdivisions
	int size = list.size();
	subdivisions = std::min( subdivisions, size );
	int space = ceilf( (float)size / subdivisions );
	//printf( "size: %d | subdivs: %d | space: %d\n", size, subdivisions, space );

	std::vector<std::thread> threads;

	int start_id = 0;
	int last_id = space;
	for ( int subdiv = 0; subdiv < subdivisions; subdiv++ )
	{
		//  sum up
		threads.emplace_back( [&count, &list, start_id, last_id]() {
			count += sum(
				list,
				start_id,
				last_id
			);
		} );
		//printf( "%d | %d - %d\n", subdiv, start_id, last_id );

		//  count next indexes
		start_id = last_id + 1;
		last_id = std::min( size - 1, last_id + space );
	}

	//  wait threads
	for ( auto& thread : threads )
	{
		thread.join();
	}

	return count;
}

int main()
{
	std::vector<int> list0 { 1, 5, 3, -3, 4, 7, 2, 6, 5 };

	std::cout << "sum: " << sum( list0 ) << std::endl;
	std::cout << "sum_threaded: " << sum_threaded( list0, 5 ) << std::endl;
}