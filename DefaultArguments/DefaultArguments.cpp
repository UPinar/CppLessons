#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

/*
	=====================
	| default arguments |
	=====================
*/

/*
	// formal parameters
	void func(int x, int y);
	
	// arguments
	func(12, x + 5);
*/

/*
	int printf(const char*, ...); [print format function]
	
	// variadic parameter
	void func(int, int, ...);
	
	// ... -> ellipsis
	
	// variadic paramter nees to be last parameter.
	// only 1 variadic parameter is valid.
	
	int main()
	{
		func(2);			// syntax error
		func(2, 2);			// legal
		func(2, 2, 2);		// legal
		func(2, 2, 2, 2);	// legal
	}
*/

/*
	no runtime cost.
	compile time tool.
*/

/*
	// decleration
	void func(int, int, int, int);
	// in function declerations we do not need to use names in parameters.
	
	// definition
	void func(int x, int y, int z, int k)
	{
		// code here
	}
*/

/*
	int g{};
	
	void func(int a, int b = g, int c = 10);
	// default argument does not need to be constant expression [int b = g]
*/

/*
	void func(int a, int b = 10, int c); // syntax error.
	// E0306 default argument not at end of parameter list
	
	// if 2nd argument is default argument next arguments needs to be default argumens too.

	func(10, , 20); // is not legal 
*/

/*
	void func(int x, int y = x + 10); // syntax error
	// using parameter name in other parameter is not valid.
*/

/*
	// decleration
	void func(int = 10, int = 20, int = 30);

	// definition
	void func(int x = 10, int y = 20, int z = 30)
	{

	}
	// syntax error
	// When we declare default arguments in function decleration
	// we will never declare that default arguments again in the function definition.

	// 'func': redefinition of default argument : parameter 1
	// 'func': redefinition of default argument : parameter 2
	// 'func': redefinition of default argument : parameter 3

	// general scenerio default argument will be in function decleration, not in function definition
*/

/*
	// function.h
	void func(int = 10, int = 20, int = 30);
	
	// function.cpp
	void func(int a, int b, int c)
	{
		std::cout << "a = " << a << ' ';
		std::cout << "b = " << b << ' ';
		std::cout << "c = " << c << '\n';
	}
	
	int main()
	{
		func(1, 2, 3);
		func(1, 2);
		func(1);
		func();
	}
*/

/*
	void func(int* p = nullptr);
	void func(const char* p_err = "error");
	void print(int x, std::ostream& os = std::cout);

	// pointers, reference parameters can take default parameters.
*/

/*
	-----------------
	| maximal munch |
	-----------------
*/

/*
	int main()
	{
		int x = 20;
		int y = 30;
	
		int z = x+++y;
		// int z = x++ + y;
		std::cout << "z = " << z << '\n'; // output -> z = 50
		std::cout << "x = " << x << '\n'; // output -> x = 21
		std::cout << "y = " << y << '\n'; // output -> y = 30
	}
*/

/*
	sum>>++x
	1. sum
	2. >>=
	3. ++
	4. x
*/

/*
	int main()
	{
		int n = 5;
	
		while (n --> 0) // (n-- > 0)
		{
	
		}
	}
*/

/*
	void func(int, const char *= "hello"); // syntax error
	// maximal munch *= is an operator.
	void func(int, const char* = "hello");
*/

/*
	// function.h
	int foo(int, int, int);
	
	// we will use foo() function in client.cpp a lot of times.
	// and we always want to sent 3rd argument the same value.
	// we can redeclare that function again in our .cpp file.
	
	// client.cpp
	// #include "function.h"
	int foo(int, int, int = 0);
*/

/*
	// function.h
	int func(int x, int y, int z = 10);
	
	// client.cpp
	int func(int x, int y = 20, int z);
	// redecleration for the second parameter
	// but in redecleration we can not use default argument of 3rd parameter again.
*/

/*
	int x = 10;
	
	void func(int a = ++x)
	{
		std::cout << "a = " << a << '\n';
	}
	// every time this function called ++x will have a side effect.
	
	int main()
	{
		func(); // output -> a = 11
		// func(++x);
		// These 2 lines are same.
		func(); // output -> a = 12
		func(); // output -> a = 13
	}
*/

/*
	// someheader.h
	void func(int x, int y, int z);
	
	// Can we send same argument for the 2nd parameter in client code?
	
	void func_(int x, int z, int y = 0)
	{
		func(x, y, z);
	}
	// wrapper function.
*/

/*
	void process_date(int mday = -1, int month = -1, int year = -1)
	{
		if (year == -1)
		{
			// controlling if an argument is sent to 3rd parameter.
		}
	}
*/

/*
	#include <ctime>
	
	void process_date(int mday = -1, int month = -1, int year = -1)
	{
		if (year == -1){
			std::time_t timer{};
			std::time(&timer);
			auto tp = localtime(&timer);
			year = tp->tm_year + 1900;
	
			if (month == -1){
				month = tp->tm_mon + 1;
	
				if (mday == -1) {
					mday = tp->tm_mday;
				}
			}
		}
		std::cout << mday << '-' << month << '-' << year << '\n';
	}
	
	int main()
	{
		process_date(12, 5, 1993);
		process_date(12, 5);
		process_date(12);
		process_date();
	}
*/