#pragma once

#include <iostream>
class Car {
public:
	virtual void start()
	{
		std::cout << "Car has just started\n";
	}
	virtual void run()
	{
		std::cout << "Car is running\n";
	}
	virtual void stop()
	{
		std::cout << "Car has just stopped\n";
	}

	void test_car()
	{
		start();
		run();
		stop();
	}
};

class Mercedes : public Car {
public:
	void open_sunroof()
	{
		std::cout << "Mercedes sunroof opened\n";
	}
	void start()override
	{
		std::cout << "Mercedes has just started\n";
	}
	void run()override
	{
		std::cout << "Mercedes is running\n";
	}
	void stop()override
	{
		std::cout << "Mercedes has just stopped\n";
	}
};