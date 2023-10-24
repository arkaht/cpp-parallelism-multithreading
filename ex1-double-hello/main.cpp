#include <iostream>
#include <thread>

void thread_hello_world()
{
    std::cout << "Hello World!\n";
}

void thread_hello_my_friend()
{
    std::cout << "Hello My Frieend!\n";
}

int main()
{
    std::thread thread0( thread_hello_world );
    std::thread thread1( thread_hello_my_friend );

    thread0.join();
    thread1.join();
}