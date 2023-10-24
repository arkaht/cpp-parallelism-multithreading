#include <iostream>
#include <vector>
#include <thread>
#include <mutex>

//  1st version: classic sum
int sum( const std::vector<int>& list, int start_id = 0, int last_id = -1 )
{
	//  auto-fill last id
	if ( last_id == -1 )
	{
		last_id = (int)list.size() - 1;
	}

	//  sum
	int count = 0;
	for ( int i = start_id; i <= last_id; i++ )
	{
		count += list[i];
	}

	return count;
}

//  2nd version: divided into subtables w/ a thread per subtable
int sum_threaded( const std::vector<int>& list, int subdivisions )
{
	int count = 0;
	std::vector<std::thread> threads;

	//  setup subdivisions
	int size = list.size();
	subdivisions = std::min( subdivisions, size );
	int space = ceilf( (float)size / subdivisions );
	//printf( "size: %d | subdivs: %d | space: %d\n", size, subdivisions, space );

	int start_id = 0;
	int last_id = space;
	for ( int subdiv = 0; subdiv < subdivisions; subdiv++ )
	{
		//  sum up
		threads.emplace_back( 
			[&count, &list, start_id, last_id]() {
				count += sum(
					list,
					start_id,
					last_id
				);
			}
		);
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

//  3rd version: derived from 2nd w/ global sum variable & mutex
int global_sum = 0;
void sum_global_threaded( const std::vector<int>& list, int subdivisions )
{
	std::vector<std::thread> threads;
	std::mutex mutex;

	//  setup subdivisions
	int size = list.size();
	subdivisions = std::min( subdivisions, size );
	int space = ceilf( (float)size / subdivisions );
	//printf( "size: %d | subdivs: %d | space: %d\n", size, subdivisions, space );

	int start_id = 0;
	int last_id = space;
	for ( int subdiv = 0; subdiv < subdivisions; subdiv++ )
	{
		//  sum up
		threads.emplace_back( 
			[&mutex, &list, start_id, last_id]() {
				int _sum = sum(
					list,
					start_id,
					last_id
				);

				std::lock_guard lock( mutex );
				global_sum += _sum;
			}
		);
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
}

int main()
{
	std::vector<int> list0 { 1, 5, 3, -3, 4, 7, 2, 6, 5 };

	std::cout << "sum: " << sum( list0 ) << std::endl;
	std::cout << "sum_threaded: " << sum_threaded( list0, 3 ) << std::endl;

	sum_global_threaded( list0, 3 );
	std::cout << "sum_global_threaded: " << global_sum << std::endl;
}