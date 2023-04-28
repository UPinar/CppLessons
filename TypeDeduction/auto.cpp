#include <iostream>

/*	
	=======================
	| auto type deduction |
	=======================	
*/

/*
	type deduction is not happening for the variable,
	type deduction is happening for auto keyword.

	auto x = expr;
	if auto deduce to int -> x is int

	const auto x =  expr;
	if auto deduce to int -> x is const int

	auto* x = expr;
	if auto deduce to int  -> x is int* (a pointer to int)	
	if auto deduce to int* -> x is int** 
*/

/*
	auto x;
	// default initialization is NOT VALID
*/

/*
	auto x = expr;
	// copy initialization

	auto x(expr);
	// direct initialization

	auto x{ expr };
	// value initialization
*/

/*
	------------------
	| auto x = expr; |
	------------------
*/

/*
	auto x = 10;
	// int

	auto x = 'A';
	// char

	auto x = 'A' + 'A';
	// int (integral promotion)
*/

/*
	char c = 12;
	auto x = +c;
	// int (integral promotion)
*/

/*
	int a = 5;
	int b = 6;
	double dval = 3.4;
	auto x = a > 2 ? b : dval;
	// type conversion rules applied between 2nd and 3rd operands of ternary operator.
	// "int + double" expressions type is double
	// x deduce to double
*/

/*
	int a = 5;
	int b = 6;
	auto x = a > b;
	// bool in C++
	// int  in C
*/

/*
	int arr[]{ 3, 6, 9 };
	auto x = arr;
	// array decay to pointer -> int*
*/

/*
	char str[] = "hello";
	auto x = str;
	// array decay to pointer -> char*
*/

/*
	const int a[] = { 3, 1, 8, 2 };
	auto b = a;
	// array decay to pointer -> const int*
*/

/*
	auto x = "hello"; // const char[6]
	// array decay to pointer -> const char*
*/

/*
	const int x = 20;
	auto b = x;
	// we have an int variable(x) and it is const.
	// carrying the value from its address to another variable.
	// to carry that value from x(const int) we need to create a space for int.
	// we don't need any const keyword for new variable.
	// x(const) gave a promise to not change its value but the new variable 
	// did not need to gave the same promise.
	// b's type is int
	// CONST WILL DROP
*/

/*
	int a = 10;
	int* const p = &a;
	auto x = p;

	// p is a const pointer to int 
	// x's type will be a pointer to int (int*)
	// TOP-LEVEL CONST WILL DROP

	const int* b = &a;
	auto y = b;
	// b is a pointer to const int.
	// y's type will be a pointer to a const int (const int*)
	// LOW-LEVEL CONSTNESS WILL NOT DROP

	const int* const c = &a;
	auto z = c;
	// c is a const pointer to const int
	// z's type will be a pointer to a const int (const int*)
	// TOP-LEVEL CONST WILL DROP
	// LOW-LEVEL CONST WILL NOT DROP
*/

/*
	int x = 10;
	int& r = x;
	auto y = r;
	// y's type will be int.

	const int& cr = x;
	auto z = cr;
	// z's type will be int
	// CONST WILL DROP
*/

/*
	int&& r = 10;
	// r variables data type is int&&
	r;
	// r expressions type is int and it is an L value expression.
*/

/*
	int foo(int);
	// foo functions type is -> int(int)
	// foo's address type is -> int(*)(int)

	int (*p)(int) = foo;	// implicit function to pointer conversion
	int (*p)(int) = &foo;
	// These 2 lines are same

	auto fp = foo;		// implicit function to pointer conversion
	// fp is not function type 
	// fp is function pointer type 
	// int (*fp)(int)
*/

/*
	int x = 10;
	int* ptr = &x;

	const auto p = ptr;
	// const [const auto p = ptr;] in expression make p TOP-LEVEL const
	// p type is int*, the statement is const ptr (constant pointer to int)
*/

/*
	-------------------
	| auto &y = expr; |
	-------------------	
*/

/*
	// const WILL NOT drop.
	// no array to pointer conversion(no array decay)
	// no function to function pointer conversion(no function decay)
*/

/*
	int x = 10;
	auto& y = x;
	// y's type is int&
*/

/*
	int x = 10;
	auto& y = x + 5; // syntax error
	// initializing L value reference with an R value expression 
	// is not legal.
*/

/*
	const int x = 10;
	auto& y = x;
	// auto's type is cont int
	// y's type is const int&
	// y is a reference to constant int
*/

/*
	int x = 10;
	int* const p = &x; // TOP-LEVEL CONST
	auto& y = p;
	// auto's type is int* const
	// y's type is int* const&
	// y is a reference to constant pointer to integer
*/

/*
	int a[5] = { 1, 2, 3, 4, 5 };
	auto& x = a;
	// auto's type is int[5]
	int(&y)[5] = a;
	// x's type is a reference to int[5]

	using ar = int[5];
	auto& x = a; || int(&x)[5] = a; || ar& x = a;
	// those 3 lines are same 
	// no array decay happens.
*/

/*
	using charArray = const char[6];

	auto& x = "hello";
	const char(&y)[6] = "hello";
	charArray& z = "hello";
	// These 3 lines are same.
*/

/*
	int foo(int);

	using FUNCTION = int(int);
	using FPTR = int(*)(int);

	FUNCTION* fp1 = foo; 	// function to function pointer conversion (decay)
	FUNCTION* fp1 = &foo;
	// These 2 lines are same 

	FPTR fp2 = foo;		// function to function pointer conversion (decay)
	FPTR fp2 = &foo;
	// These 2 lines are same 

	auto fp3 = foo;		// function to function pointer conversion (decay)
	auto fp3 = &foo;
	// These 2 lines are same

	FUNCTION* fp1 = foo;
	FPTR fp2 = foo;
	auto fp3 = foo;
	// These 3 lines are same
	
	auto& f1 = foo;    // DECAY IS NOT HAPPENING [NO FUNCTION TO FUNCTION POINTER CONVERSION]
	// type of auto is  int(int)		-> is a function
	// type of f1   is  int(&f1)(int)	-> is a reference to function

	auto& f1 = foo;
	int(&f2)(int) = foo;
	FUNCTION& f3 = foo;
	// These 3 lines are same
*/

/*
	-----------------------------------------------
	| auto && z = expr; | -> forwarding reference |
	-----------------------------------------------
*/

/*
	------------------------
	| reference collapsing |
	------------------------
*/

/*
	// 1. T&    &    -> T&
	// 2. T&    &&   -> T&
	// 3. T&&   &    -> T&
	// 4. T&&   &&   -> T&&
*/

/*
	using REF = int&;

	int y = 34;

	REF& x = y;
	int& x = y;
	// These 2 lines are same
	// 1. T&    &    -> T&
	// x's type is int&

	int y = 35;

	REF&& x = y;
	int& x = y; 
	// These 2 lines are same
	// 2. T&    &&   -> T&
	// x's type is int&
*/

/*
	using REF = int&&;

	int y = 36;

	REF& x = y;
	int& x = y; 
	// These 2 lines are same
	// 3. T&&   &    -> T&
	// x's type is int&

	REF&& x = 10; 
	int&& x = 10; 
	// These 2 lines are same
	// 4. T&&   &&    -> T&&
	// x's type is int&&
*/
	
/*
	// auto&& r = expr;
	// if expr is L value ==> auto type is T&
	// if expr is R value ==> auto type is T
*/

/*
	int x = 10;
	auto&& y = x;
	// x is L value expression , auto's type is int&(T&)
	// int& && is reference collapsing
	// y's type will be int&
	// 2. T&    &&   -> T&

	auto&& y = x;
	int& y = x; 
	// These 2 line are same.
*/

/*
	auto&& y = 10;
	// 10(expression) is R value, auto type is int(T);
	// auto's type will be int
	// y's type is int&&

	auto&& y = 10;
	int&& y = 10;
	// These 2 lines are same.
*/

/*
	const int x = 190;
	auto&& r = x;
	// x is an L value expression, auto's type is const int&
	// const will not dropped.
	// 2. T&    &&   -> T&

	auto&& r = x;
	const int& r = x; 
	// These 2 lines are same
*/

/*
	int x = 10;
	int* ptr = &x;
	
	auto&& a = *ptr;
	// (*ptr) is L value expression [dereference of int pointer is an int], auto type is T&(int&)
	// 2. T&    &&   -> T&

	auto&& a = *ptr;
	int& a = *ptr;
	// These 2 lines are same.
*/

/*
	--------------------------------------
	| some other usage of "auto" keyword |
	--------------------------------------
*/

/*
	------------------------
	| trailing return type |
	------------------------
*/

/*
	auto func()-> int
	{
		// code here
		// func() is a function, its return type is int
	}
*/

/*
	// declaring a fuction that have a return type of int (*)(int)
	int bar(int);
	
	int(*foo())(int) {
		return &bar;
	}

	// declaring the same function with trailing return type
	
	auto foo() -> int(*)(int)
	{
		return &bar;
	}
*/

/*
	int a[10]{};
	
	auto foo() -> int(*)[10]
	{
		return &a;
	}
	// foo()'s return type is address of 10 elem int array
*/

/*
	--------------------
	| auto return type |
	--------------------
*/

/*
	int bar(double);
	
	auto foo()
	{
		return &bar;
	}
	// auto's type is int(*)(double)
*/
