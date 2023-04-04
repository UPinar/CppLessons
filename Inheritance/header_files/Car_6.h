#pragma once

#include <iostream>

class Car {
public:
	virtual Car* clone() = 0; 

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
};

class Volvo : public Car {
public:
	Car* clone()override
	{
		return new Volvo(*this); 
	}

	void start()override
	{
		std::cout << "Volvo has just started\n";
	}
	void run()override
	{
		std::cout << "Volvo is running\n";
	}
	void stop()override
	{
		std::cout << "Volvo has just stopped\n";
	}
};

class Audi : public Car {
public:

	Car* clone()override
	{
		return new Audi(*this); 
	}
	void start()override
	{
		std::cout << "Audi has just started\n";
	}
	void run()override
	{
		std::cout << "Audi is running\n";
	}
	void stop()override
	{
		std::cout << "Audi has just stopped\n";
	}
};


