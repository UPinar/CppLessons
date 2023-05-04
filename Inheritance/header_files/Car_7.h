#pragma once

#include <iostream>

class Car {
public:

	friend std::ostream& operator<<(std::ostream& os, const Car& c) 
	{
		c.print(os);
		return os;
	}

	virtual void print(std::ostream& os) const = 0;		// pure virtual function

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
	void print(std::ostream& os) const override
	{
		os << "I am a Volvo";
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
	void print(std::ostream& os) const override
	{
		os << "I am an Audi";
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
