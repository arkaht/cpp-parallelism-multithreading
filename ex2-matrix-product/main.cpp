#include <iostream>
#include <assert.h>
#include <thread>
#include <vector>

class Matrix
{
public:
	static Matrix multiply( const Matrix& a, const Matrix& b )
	{
		Matrix c {};

		//  1st line
		//c[0] = a[0] * b[0] + a[1] * b[3] + a[2] * b[6];
		//c[1] = a[0] * b[1] + a[1] * b[4] + a[2] * b[7];
		//c[2] = a[0] * b[2] + a[1] * b[5] + a[2] * b[8];

		//  2nd line
		//c[3] = a[3] * b[0] + a[4] * b[3] + a[5] * b[6];
		//c[4] = a[3] * b[1] + a[4] * b[4] + a[5] * b[7];
		//c[5] = a[3] * b[2] + a[4] * b[5] + a[5] * b[8];

		//  3rd line
		//c[6] = a[6] * b[0] + a[7] * b[3] + a[8] * b[6];
		//c[7] = a[6] * b[1] + a[7] * b[4] + a[8] * b[7];
		//c[8] = a[6] * b[2] + a[7] * b[5] + a[8] * b[8];

		for ( int i = 0; i < 9; i++ )
		{
			multiply_index( a, b, c, i );
		}

		return c;
	}

	static Matrix multiply_threaded( const Matrix& a, const Matrix& b )
	{
		Matrix c {};

		//  create threads
		std::vector<std::thread> threads;
		auto c_ref = std::ref( c );
		for ( int i = 0; i < 9; i++ )
		{
			threads.emplace_back( Matrix::multiply_index, a, b, c_ref, i );
		}

		//  wait for them to finish
		for ( auto& thread : threads )
		{
			thread.join();
		}

		return c;
	}

	float& operator[]( int id )
	{
		assert( id >= 0 && id < 9 );
		return m[id];
	}
	float operator[]( int id ) const
	{
		assert( id >= 0 && id < 9 );
		return m[id];
	}

	friend std::ostream& operator<<( std::ostream& os, const Matrix &m )
	{
		os << m[0] << ", " << m[1] << ", " << m[2] << ", " << std::endl;
		os << m[3] << ", " << m[4] << ", " << m[5] << ", " << std::endl;
		os << m[6] << ", " << m[7] << ", " << m[8] << ", " << std::endl;
		return os;
	}

	float m[9];

private:
	static void multiply_index( const Matrix& a, const Matrix& b, Matrix& c, int id )
	{
		int row = id / 3 * 3;
		int column = id % 3;

		c[id] = a[row] * b[column] + a[row + 1] * b[column + 3] + a[row + 2] * b[column + 6];
		//printf( "%d; %d; %d => %f\n",id, row, column, c[id] );
		//c[0] = a[0] * b[0] + a[1] * b[3] + a[2] * b[6];
	}
};



int main()
{
	//  create matrices
	Matrix A {
		1.0f, 2.0f, -1.0f,
		3.0f, 2.0f, 0.0f,
		-4.0f, 0.0f, 2.0f
	};
	std::cout << "A:\n" << A << std::endl;
	Matrix B {
		3.0f, 4.0f, 2.0f,
		0.0f, 1.0f, 0.0f,
		-2.0f, 0.0f, 1.0f
	};
	std::cout << "B:\n" << B << std::endl;

	//  classic multiply
	Matrix C = Matrix::multiply( A, B );
	std::cout << "C = multiply( A, B ):\n" << C << std::endl;

	//  threaded multiply
	Matrix D = Matrix::multiply_threaded( A, B );
	std::cout << "D = multiply_threaded( A, B ):\n" << D << std::endl;
}