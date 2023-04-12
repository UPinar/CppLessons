#include <iostream>

/*
	=====================
	| constexpr keyword |
	=====================
*/

/*
	int foo();

	int main()
	{
		const int x = 10;
		// x is constexpr, we know its value in compile time

		const int y = foo();
		// y is not constexpr, we will learn its value in run time
		// after foo() function executed.

		int a[x] = { 0 };	// legal
		int b[y] = { 0 };	// syntax error

		const int z = x + 5;
		// z is constexpr because x is a constant
	}
*/

/*
	int main()
	{
		int x = 5;
		
		const int y = x + 5;
		// y is not constexpr because x is not constant

		int a[y] = { 0 }; // syntax error
	}
*/

/*
	int main()
	{
		// To check an expression is a constant expression or not, we can use constexpr keyword.
		// Declare a constexpr variable and initialize with the expression you want to check.\

		const int x = 5;
		int y = 12;

		constexpr int z = x * y - 3; // syntax error
		// not a constant expression
	}
*/

/*
	int main() 
	{
		constexpr int x = 30;
		// constexpr variable needs to initialize with constant expression.


		decltype(x) y = 5; // y's type is const int.
		// constexpr is not a type. 
		// When we declare a variable with a constexpr keyword it's type is const int.

		x = 12; // syntax error.
		// x's type is const int.
	}
*/

/*
	int main()
	{
		constexpr int a[] = { 3, 5, 6, 1 };
		// constexpr array is possible. It can be used as a lookup tables.
	
		constexpr int x = a[2] + a[3] - 5; // legal
	}
*/

/*
	int g = 10;

	int main()
	{
		// constexpr nesnenin kendisinin const'lugunu ifade ediyor.
		constexpr const int* p1 = &g;
		const int* p2 = &g;
		// These 2 lines ARE NOT EQUAL.
		// constexpr makes (p1 expression) const and p1's type is const int* 
		// so, [const int*] (pointer to const int) will become,
		// [const int * const] (const pointer to const int)
		// TOP-LEVEL CONST

		constexpr const int* p3 = &g;
		const int* const p4 = &g;
		// These 2 lines are EQUAL
	}
*/

/*
	-----------------------
	| constexpr functions |
	-----------------------
*/

/*
	If we send all arguments as constant expressions,
	we can get the result of constexpr function in compile time.
	Return value will created in compile time.
	Else value will be created in run time.
*/

/*
	constexpr int factorial(int x)
	{
		return x < 2 ? 1 : x * factorial(x - 1);
	}
	
	int main()
	{
		constexpr auto k = factorial(10);
	
		int a[factorial(5)]{};

		const int x = 7;
		const int y = 5;
		constexpr auto val = factorial(x + y - 3);
	}
*/

/*
	[val * sqrt(sin(x) + cos(y))]

	THIS EXPRESSION WILL BE CONSTANT EXPRESSION IF ALL ARE TRUE

	1. if x and y are constant expressions 
	2. sin() and cos() are constexpr functions
	3. sqrt() is constexpr function
	4. val is a constant expression
*/

/*
	constexpr bool isprime(int x)
	{
		if (x < 2)
			return false;
		if (x % 2 == 0)
			return x == 2;
		if (x % 3 == 0)
			return x == 3;
		if (x % 5 == 0)
			return x == 5;
	
		for (int i = 7; i * i <= x; i += 2)
			if (x % i == 0)
				return false;
	
		return true;
	}
	
	int main()
	{
		constexpr auto a = isprime(19001);
		// a -> true
	
		constexpr auto b = isprime(19002);
		// b -> false
	
		constexpr int x = 324273;
		const int y = 123;
		const int z = 2130125;
	
		constexpr auto c = isprime(x * y - z);
		// c -> false
	
		// a, b and c values calculated in compile time.
	}
*/

/*
	constexpr functions are implicitly INLINE.
	-> Generally constexpr functions are in header(.h) files.
*/