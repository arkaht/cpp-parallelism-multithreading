#include <iostream>
#include <thread>

template <typename T>
class ThreadStateRunner
{
public:
	virtual void thread_run() = 0;
	std::thread spawn() 
	{ 
		return std::thread( &T::thread_run, this );
	}

protected:
	void run_loop( T* self )
	{
		while ( true ) 
		{ 
			run_state( self ); 
		}
	}
	void run_state( T* self ) { (self->*state)(); }
	void (T::*state)();
};

class Customer : public ThreadStateRunner<Customer>
{
public:
	void thread_run()
	{
		state = &Customer::state_order;
		run_loop( this );
	}

private:
	void state_order() {}
	void state_eat() {}
	void state_exit() {}
};

class Waiter : public ThreadStateRunner<Waiter>
{
public:
	void thread_run()
	{
		state = &Waiter::state_wait;
		run_loop( this );
	}

private:
	void state_wait() {}
	void state_take_order() {}
	void state_bring_meal() {}

};

class Cooker : public ThreadStateRunner<Cooker>
{
public:
	void thread_run()
	{
		state = &Cooker::state_wait;
		run_loop( this );
	}

private:
	void state_wait() {}
	void state_cook() {}
};

class Chief : public ThreadStateRunner<Chief>
{
public:
	void thread_run()
	{
		state = &Chief::state_wait;
		run_loop( this );
	}

private:
	void state_wait() {}
	void state_mix() {}
};

int main()
{
	Customer customer {};
	Waiter waiter {};
	Cooker cooker {};
	Chief chief {};

	std::thread thread_customer = customer.spawn();
	//std::thread thread_customer( &Customer::thread_run, &customer );
	//std::thread thread_waiter( &Waiter::thread_run, &waiter );
	//std::thread thread_cooker( &Cooker::thread_run, &cooker );
	//std::thread thread_chief( &Chief::thread_run, &chief );

	thread_customer.join();
	//thread_waiter.join();
	//thread_cooker.join();
	//thread_chief.join();

	std::cout << "Hello World!\n";
}