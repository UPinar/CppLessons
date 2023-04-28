#include <iostream>

/*
	=====================================
	| decltype specifier type deduction |
	=====================================
*/

/*
	------------------------
	| decltype(identifier) |
	------------------------
*/

/* 
	decltype(x)
	decltype(a.m_x)
	decltype(ptr->val)
*/

/*
	int x = 10;
	decltype(x); // decltype(x)'s type is int
	// if x is int, decltype(x) is int

	decltype(x) intVar;

	struct Data {
		decltype(x) y;
		int y;
		// These 2 are same lines
	};

	double y = 3.4;
	decltype(x) foo(decltype(y));
	int foo(double);
	// These 2 are same lines
*/

/*
	const int x = 13;
	decltype(x) y = 15; 
	// decltype(x)'s type is const int 

	decltype(x) z; // syntax error
	// const objects can not be default initialized
*/

/*
	const int x = 13;
	const int* const ptr = &x;
	decltype(ptr) p = &x; 
	// decltype(ptr)'s type is const int* const
*/

/*
	int a[5]{};

	decltype(a) b; // b's type is int a[5]
	int b[5]; 
	// These 2 lines are same
	// no array decay happens
*/

/*
	int x = 10;
	int y = 456;
	
	int& r = x;
	decltype(r) t = y;
	// t's type is int&
	// decltype(r)'s type is int&
*/

/*
	int&& r = 10;
	decltype(r) x = 5; 
	// x's type is int&&
	// decltype(r)'s type is int&&
*/

/*
	int x = 5;
	int y = 10;
	
	decltype(x)& r = y;
	// decltype(x)'s type is int
	// r's type is int&
*/

/*
	int x = 5;
	const auto a = x; 
	// auto's type is int 
	// a's type is const int

	int x = 5;
	const decltype(x); // syntax error
	// we can not use const, volatile, static 
*/

/*
	class Myclass {
	public:
		int a, b;
		double dval;
	};
	
	int main()
	{
		Myclass mx;
		decltype(mx.a) ival = 5;
		// decltype(mx.a)'s type is int

		Myclass* mp{ &mx };
		decltype(mp->dval) dx = 3.4;
		// decltype(mp->dval)'s type is double
	}
*/

/*
	------------------------
	| decltype(expression) |
	------------------------
*/

/*
	decltype((x))
	decltype(+x)
*/

/*
	// type of decltype(expr), depends on the operand's "value category"
	
	PR Value        T
	L  Value	T&
	X  Value	T&&
*/

/*
	int x = 10;
	decltype(x + 4); 
	// (x+4) ->  PR value expression
	// type of decltype(x + 4) is an int
*/

/*
	int x = 10;
	int* ptr = &x;

	decltype(*ptr);
	// (*ptr) -> L value expression
	// decltype(*ptr)'s type is int&

	decltype(*ptr) b; // sythax error 
	// int& val; can not be default initialized
	// L value reference needs a value to initialized
*/

/*
	int x = 10;
	int a[3]{};
	
	decltype(a[2]);
	// (a[2]) is an L value expression 
	// decltype(a[2])'s type is int&
*/

/*
	int x = 10;
	decltype(+x)
	// (+x) is -> PR Value
	// decltype(+x) type is int
*/

/*
	int x = 10;
	
	decltype(x) y ; 
	// x is identifier, decltype(x)'s type is int

	decltype((x)) z; 
	// (x) is an L value expression, decltype((x))'s type is int&
*/

/*
	int foo();   	// function return type is int
	int& bar();	// function return type is int&[L value reference]
	int&& baz(); 	// function return type is int&&[R value reference]

	foo(); 		// calling foo function's value category PR Value
	bar(); 		// calling bar function's value category L  Value
	baz(); 		// calling baz function's value category X  Value

	decltype(foo());
	// foo() -> foo() is PR value expression
	// decltype(foo())'s type is int

	decltype(bar());
	// bar() -> bar() is an L value expression
	// decltype(bar())'s type is int&

	decltype(baz());
	// baz() -> baz() is X value expression
	// decltype(baz())'s type is int&&
*/

/*
	int x = 10;

	decltype(x++);
	// (x++) is PR value expression
	// decltype(x++)'s type is int

	decltype(++x);
	// (++x) is L value expression
	// decltype(x++)'s type is int&
*/
