#include <iostream>

/*
	=======================
	| reference semantics |
	=======================
*/

/*
	There are 3 categories of references
	1. L value references
	2. R vaalue references
	3. forwarding reference (universal reference)
*/

/*
	primary value categories 
	1. L value
	2. PR value (pure R value)
	3. X value (eXpiring value)

	// compiler understands the value category of the expression in compile time.
*/

/*
	int foo();
	int& func();
	int&& bar();
	
	int main()
	{
		10;		// PR Value expression
	
		int x = 10;
		x;		// L Value expression
	
		+x;		// PR Value expression
		++x;		// L value expression
		x++;		// R value expression
		&x;		// L value expression
	
		nullptr;	// PR value expression
	
		foo();		// PR value expression
		func();		// L value expression
		bar();		// X value expression
	}
*/

/*
				C		C++
	------------------------------------------
	++x			R		L
	--x			R		L
	a = b			R		L
	x, y			R		L	[if right operand is L value]
	x > y ? a : b		R		L

	// For more information about comma operator
	// https://necatiergin2019.medium.com/cde-virg%C3%BCl-operat%C3%B6r%C3%BC-comma-operator-in-c-177a0193deac
*/

/*
	combined value categories
	1. GL value		-> L value or X value
	2. R value		-> PR value or X value

	For more information
	// https://www.youtube.com/watch?v=XS2JddPq7GQ&list=PLX-5eF57P5eEHJCMYVIOL9u9ZQtKas8Ut&index=12
	// Back to Basics: Understanding Value Categories - Ben Saks - CppCon 2019 
*/

/*
	----------------------
	| L value references |
	----------------------
*/

/*
	int main()
	{
		int& ref; // syntax error
		// references can not be default initialize
	
		int x = 34;
		int& r = x; // r binds to x
	
		++r;		// ++x;
		r = 888;	// x = 888
	
		int y = 5;
		r = y;		// x = 5
		// references can not bind to another object once they bind to an object.
	}
*/

/*
	int main()
	{
		int x = 34;
		int y = 5;
		int z = 3;
	
		int& r = x;
		std::cout << "x = " << x << '\n'; // output -> x = 34
	
		r = y; // x = y
		std::cout << "x = " << x << '\n'; // output -> x = 5
	
		r = z; // x = z
		std::cout << "x = " << x << '\n'; // output -> x = 3
	}
*/

/*
	// L value references needs to be initialize with L value expression

	int main()
	{
		int& r = 10; // 10 is an R value expression[PR value expression]
		// E0461 initial value of reference to non - const must be an lvalue
	}
*/

/*
	int main()
	{
		int x = 10;
		int* p{ &x };
	
		int& r = *p;
		r = 999; // x = 999
		std::cout << "x = " << x << '\n'; // output -> x = 999
	}
*/

/*
	int main()
	{
		int x = 7;
		int& r1 = x;	// r1 = x
		int& r2 = r1;	// r2 = x
		int& r3 = r2;	// r3 = x
	
		++r1; // ++x
		++r2; // ++x
		++r3; // ++x
	
		std::cout << "x = " << x << '\n'; // output -> x = 10
	}
*/

/*
	int main()
	{
		int x = 9;
		int* p{ &x };	// p is a pointer to x
		int*& r = p;	// r is a reference to p (r = p)
	
		++* r; // *r = *p = x  ------> ++x
	
		// references can bind to pointers too.
	}
*/

/*
	int main()
	{
		int* p = nullptr;
	
		int*& r = p; // r = p
		int x = 10;
		r = &x;		// r = &x -> p = &x
		*r = 99;	// *r = *p = x ---> x = 99
	}
*/

/*
	int main()
	{
		int x = 5;
		int* p = &x;
		int** ptr = &p;
	
		int**& r = ptr; // r = ptr
	
		**r = 99; // **r = **ptr = x ---> x = 99
		std::cout << "x = " << x << '\n'; // output -> x = 99
	}
*/

/*
	int main()
	{
		int* p = nullptr;
		// * is a declerator
	
		int x = 10;
		int* ptr = &x;
		// * is a declerator, & is an operator
	
		*p = 45; 
		// * is an operator
	
		int& r = x;
		// & is a declerator
	
		++* ptr;
		// ++ and * are operator
	}
*/

/*
	int main()
	{
		int x = 10;
		double dval{};
	
		int& r = dval; // syntax error
		// E0434 a reference of type "int &" (not const - qualified) cannot be initialized with
		// a value of type "double"
	
		double& rr = dval;
	}
*/

/*
	typedef int intarr5[5];
	// 1. write the type that you want to use as a typedef.
	// int a[5];
	// 2. add a typedef in the beginning
	// typedef int a[5];
	// 3. change the object name with type name
	// typedef int intarr5[5];
	
	using inta5 = int[5];
	
	int main()
	{
		int a[5]{ 1,2,3,4,5 };
	
		int* ptr = a; // pointer, points to the first element of array
		// int* ptr = &a[0];
		// these 2 lines are same
		std::cout << typeid(ptr).name() << '\n';
		// output -> int* __ptr64 -> (pointer to an integer[first element])
	
	
		int(*p)[5] = &a; // pointer, points to the array.
		std::cout << typeid(p).name() << '\n';
		// output -> int (* __ptr64)[5] -> (pointer to 5 element array)
	
		int(&r)[5] = a; //  reference to 5 element array
	
		for (int i = 0; i < 5; ++i)
		{
			printf("%d %d\n", r[i], a[i]);
		}
		// output ->
		// 1 1
		// 2 2
		// 3 3
		// 4 4
		// 5 5
	
		intarr5& r = a;
		intarr5* p = &a;
	
		inta5& r = a;
		inta5* r = &a;
	}
*/

/*
	void func(int* ptr);
	void foo(int& r);
	
	int main()
	{
		int x = 10;
	
		func(&x);
		foo(x);
	}
*/

/*
	void iswap(int* p1, int* p2)
	{
		int temp = *p1;
		*p1 = *p2;
		*p2 = temp;
	}
	
	void iswapref(int& r1, int& r2)
	{
		int temp = r1;
		r1 = r2;
		r2 = temp;
	}
	
	int main()
	{
		int a = 67, b = 88;
	
		std::cout << "a = " << a << " b = " << b << '\n';
		iswap(&a, &b);
		std::cout << "a = " << a << " b = " << b << '\n';
	
		iswapref(a, b);
		std::cout << "a = " << a << " b = " << b << '\n';
	}
*/

/*
	int g = 50;
	
	int* foo()
	{
		return &g;
	}
	
	int& bar() // L value expression
	{
		return g;
	}
	
	int main()
	{
		std::cout << "g = " << g << '\n';
		++*foo();
		std::cout << "g = " << g << '\n';
		*foo() = 999;
		std::cout << "g = " << g << '\n';
	
		int* p = foo();
		*p = -1;
		std::cout << "g = " << g << '\n';
	
		bar() = 888;
		std::cout << "g = " << g << '\n';
		++bar();
		std::cout << "g = " << g << '\n';
	}
 */

/*
	int* fooptrfunc(int* ptr)
	{
		*ptr *= 2;
		return ptr;
	}
	
	int& fooreffunc(int& ref)
	{
		ref *= 2;
		return ref;
	}
	
	int main()
	{
		int x = 10;
		int* p = fooptrfunc(&x);
		++* p;
		std::cout << "x = " << x << '\n';
	
		int y = 10;
		int& r = fooreffunc(y);
		++r;
		std::cout << "y = " << y << '\n';
	}
*/

/*
	int main()
	{
		int x = 10;
		int& r = x; //  (r bind to x)
	
		int y = r; // y will be 10;
		y = 99;
		std::cout << "x = " << x << '\n'; // output -> x = 10
	
		int& z = r; //  r = z = x (r and z are bind to x)
		z = 99;
		std::cout << "x = " << x << '\n'; // output -> x = 99
	}
*/

/*
	using T = int;
	
	void mutator_func(T&);		// SET function
	void accessor_func(const T&);	// GET function
	
	int main()
	{
		int x = 10;
		const int& r = x; // const reference -> reading purpose
	
		++r;	// syntax error
		r = 12; // syntax error
	}
*/

/*
	using T = int;
	
	void f1(T*);
	void f1_(T&);
	
	void f2(const T*);
	void f2_(const T&);
	
	T* f3(void);
	T& f3_(void);
	
	const T* f4();
	const T& f4_();
*/

/*
	int main()
	{
		const int x = 10;
		int* p = &x; // syntax error
		// no implicit conversion from const T* to T*
	
		int& r = x; // syntax error
	
		const int* cptr = &x;	// legal
		const int& cr = x;	// legal
	}
*/

/*
	int main()
	{
		int x = 10;
	
		const int* p = &x; // legal [contractual constness]
		// implicit conversion from int* to const int* is valid.
		const int& r = x; // legal
	
		*p = 23;	// not legal
		x = 23;		// legal
	}
*/

/*
	int main()
	{
		const char (&r)[11] = "helloWorld";
	
		for (int i = 0; i < 10; ++i)
		{
			std::cout << r[i] << ' ' << (int)r[i] << '\n';
		}
		// output ->
		// h 104
		// e 101
		// l 108
		// l 108
		// o 111
		// W 87
		// o 111
		// r 114
		// l 108
		// d 100
	}
*/

/*
	pointer semantics			reference semantics
	---------------------------------------------------------------------
	- can be default initialized		- can not default initialized
	- can hold different objects addresses	- can not rebind to another object
	- array object types can be pointers	- array object types can not be reference
	- null pointer is valid			- null reference is not valid
	- pointer to pointer is valied		- reference to reference is not valid
*/

/*
	int main()
	{
		int& r = 10; // not valid
	
		const int& cr = 10; // valid
		// compiler create a temporary object and reference binds to that temp object.
	
		// int_obj = 10;
		// const int& cr = t_obj;
	
		int x = 10;
		double& dr = x;			// syntax error
		const double& cdr = x;	// legal
	
		// created implicit conversion from x(int) to double.
		// double temp_obj = static_cast<double>(x);
		// const double& cdr = temp_obj;
	}
*/
