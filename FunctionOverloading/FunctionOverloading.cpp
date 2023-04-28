#include <iostream>

/*
	========================
	| Function Overloading |
	========================
*/

/*
	function OVERLOADING > compile time > static(early) binding
	function OVERRIDING  > run time     > dynamic(late) binding
*/

/*
	For function overloading
	-----------------------

	1. funtions names should be same.
	2. functions scopes should be same.
	3. functions signatures should be different
*/

/*
	C scope categories
	-------------------------
	-> file scope
	-> block scope
	-> function prototype scope
	-> function scope

	C++ scope categories
	-------------------------
	-> namespace scope
		(gloabal variables, global functions, global type definitions)
	-> class scope
	-> block scope
		(variables inside functions, local variables)
	-> function prototype scope
		(function parameters)
	-> function scope
		(labels[goto])
*/

/*
	void foo(int); //namespace scope
	int main()
	{
		void foo(double); //block scope
	}
	// no function overloading, different scopes
*/

/*
	int main()
	{
		class Myclass {
			void foo(int); // class scope
		};
		void foo(double); // block scope
		// no function overloading, different scopes
	}
*/

/*
	namespace first {
		void foo(int);
	}

	namespace second {
		void foo(double);
	}
	// no function overloading , different namespace scopes
*/

/*
	----------------------
	| function signature |
	----------------------
*/

/*
	int     foo(int,int);
	double func(int,int);
	// these functions have same function signature but different return types.
	// we do not check function return types, we only check function parameters
	// for function signatures.
*/

/*
	int func(int);
	double func(int);
	// sythax error.

	int foo(int);
	int foo(int);
	// function redecleration , no sythax error.
*/

/*
	int func(int);
	double func(int, int);
	double func(double, int);
	// we have 3 overloads(function overloads)
*/

/*
	If a parameter is not a reference or a pointer!!
	Declaring two functions, one of them has const do not create overloads.

	int func(int);
	int func(const int);
	// Function redecleration, not overloads
*/

/*
	void func(int*);
	void func(int* const);
	// This is not overloading (Top-level const)

	void foo(int*);
	void foo(const int*);
	// const overloading, 2 overloads here
*/

/*
	void foo(int&);
	void foo(const int&);
	//const overloading
*/

/*
	void func(char);		// implementation defined.
	void func(signed char);
	void func(unsigned char);

	// char, signed char and unsigned char are distinct types
	// There are 3 overload functions
*/

/*
	typedef unsigned char BYTE; // type alias

	void func(unsigned char);
	void func(BYTE);
	// function redecleration, no overloading
*/

/*
#include <cstdint>

	// int32_t is a type alias (optional sythax)
	void func(int);
	void func(int32_t);

	// int32_t needs to be exactly 32 bit
	// size of int depends on systems int byte size, can be 4 can be 2
*/

/*
	// In C and C++ languages, parameter variables can not be an array!
	// if you declare parameter variable as an array,
	// compiler will decay that array to a poiner.

	void func(int* p);
	void func(int p[]);
	void func(int p[10]);
	// 1 overload here, all function redeclerations.
*/

/*
	void func(int p[10]);

	int main()
	{
		int x{ 98 };
		func(&x);	// VALID, NO SYNTAX ERROR

		// func(int* p); func functions actual parameter variable is int* (array decay)
		// sending address of int is valid.
		// even if our purpose is sending an int array[10]
	}
*/

/*
	// functions parameter variable can not be a function type!
	// if you declare parameter variable as a function type,
	// compiler will decay that function type to function pointer type

	// int(int)    -> function type
	// int(*)(int) -> function pointer type


	void foo(int(int));  // int(int) will decay to int(*)(int)
	void foo(int(*)(int));
	// function redecleration, 1 overload here.
*/

/*
	// 1 overload in here. They are all redecleration
	using Function = int(int);	// function type
	using FPTR = int(*)(int);	// function pointer type

	void foo(Function*);
	void foo(FPTR);
	void foo(int(int));
	void foo(int(*)(int));
	// 1 overload here, all function redeclerations.
*/

/*
	void func(int(*)[10]);
	void func(int[][10]);
	// Function redecleration.
*/

/*
	void func(int(*)[10]);
	// func() can be called with an address of int[10]

	int main()
	{
		int a[10]{};
		func(&a);		// legal [sending int(*)[16]]
		func(a);		// syntax error [sending int*]
		func(&a[0]);		// syntax error [sending int*]

		int x = 12;
		int* p = &x;
		func(&x);		// syntax error [sending int*]
		func(p);		// syntax error [sending int*]
		func(&p);		// syntax error [sending int**]

		int b[16]{};
		func(&b);		// syntax error [sending int(*)[16]]
	}
*/

/*

	void func(int(&)[10]);
	// this function can called with int[10]

	int main()
	{
		int a[10]{};
		func(a);
	}
*/

/*

	void func(int(*)[5]);
	void func(int(*)[10]);
	void func(int(*)[15]);
	// There are 3 overload functions

	void foo(int(&r)[5]);
	void foo(int(&r)[10]);
	void foo(int(&r)[15]);
	// There are 3 overload functions
*/

/*
	void foo(int(*p)[10]);
	void bar(int p[][10]);

	using inta10 = int[10];
	void baz(inta10* p);

	int main()
	{
		int a[10]{};

		foo(&a);
		bar(&a);
		baz(&a);
	}
*/

/*
	int a[10]{};
	
	int(*foo())[10]
	{
		return &a;
	}
	
	using inta10 = int[10];
	inta10* bar()
	{
		return &a;
	}
	
	using inta10_ptr = int(*)[10];
	
	inta10_ptr baz()
	{
		return &a;
	}
*/

/*

	void func(int, int = 0);	// 2 parameters
	void func(int);			// 1 parameter
	// 2 overloads
*/

/*
	void func(int, int);
	void func(int, int = 0);
	// function redecleration
*/

/*

	void func(int, int, int);
	void func(int, int, int = 0);
	void func(int, int = 0, int);
	// 1 overloads, cumulative decleration
*/

/*

	void foo(int&);
	void foo(int*);
	void foo(int);
	// There are 3 overloads here
*/

/*
	class Myclass {};

	void func(const Myclass&);
	void func(Myclass&);
	void func(Myclass&&);
	// There are 3 overloads here. 
*/

/*
	int x{};
	
	void func(int);
	void func(decltype(x)); // decltype(x) int type, x is PR value expression
	// function redecleration, no overload

	void foo(int);
	void foo(decltype((x)));  // decltype((x)) int& type, (x) is L value expression
	// function overloading, 2 overloads
*/

/*
	--------------------------------
	| Function Overload Resolution |
	--------------------------------
*/

/*
	1. find all overloads and make them (candidate functions)
	2. check their signatures and find which you can call (viable functions)
	3. if no viable function -> NO MATCH ERROR.
	4. if more than 1 viable functions, find best vaible function(best match)
	5. if no best match -> AMBIGUITY ERROR
*/

/*
	Q. Implicit conversion is possible ?

	scoped enum		--> int			[NO]
	unscoped enum		--> int			[YES]
	double			--> char		[YES]
	int*			--> void*		[YES]
	void*			--> int*		[NO]
	int*			--> bool		[YES]
	bool			--> int*		[NO]
	nullptr_t		--> int*		[YES]
	int*			--> nullptr_t		[NO]
	nullptr_t		--> bool		[NO]	// In logic context Yes
*/

/*
	void func(unsigned int);
	void func(char);

	int main()
	{
		func(12);
		// ambiguity(belirsizlik) error 
	}
*/

/*
	Qualities of conversion levels
	-----------------------------
	Level 0 -> variadic conversion			[WORST]
	Level 1 -> user-defined conversion
	Level 2 -> standart conversion			[BEST]
*/

/*
	// variadic conversion - LEVEL 0 (Lowest quality conversion)

	void func(int, ...);
	void func(int,int, ...);
	void func(...);		// is not possible in C but possible in C++
	
	void func(double);

	int main()
	{
		func(123);
		// will call func(double) -> [standart conversion > variadic conversion]
	}
*/

/*
	// user-defined conversion - LEVEL 1

	class Myclass {
	public:
		Myclass();
		Myclass(int);

		operator int()const;
	};

	int main()
	{
		Myclass x;
		x = 5;		// user-defined conversion [int -> Myclass]

		Myclass y;
		int ival{};
		ival = y;	// user-defined conversion [Myclass -> int]
	}
*/

/*
	// standart conversion - LEVEL 2

	void func(unsigned int);	
	void func(float);
	void func(double);

	int main()
	{
		func(10 > 5);
		// bool can impilictly convert to unsigned int, float and double
		// 3 functions are both standart conversion
	}
*/

/*
	Qualities of Standart conversion 
	-------------------------------------

	A. exact match	[BEST]
		array to pointer conversion (array decay)
		const conversion
		function to pointer conversion

	B. promotion
		bool, char, short ==> int (integral promotion)
		float ==> double 

	C. conversion	[WORST]
		standart conversion other than A(exact match) and B(promotion) are conversions.
		If there are more than 1 overloads, it will create AMBIGUITY ERROR.
*/

/*
	-------------------------------------
	| Standart conversion - exact match |
	-------------------------------------
*/

/*
	void func(int*);

	int main()
	{
		int a[5]{};
		func(a);	// exact match (array decay)
		func(&a[0]);	// exact match (array decay)
		// These 2 lines are same
	}
*/

/*
	void func(const int*);

	int main()
	{
		const int x = 10;
		func(&x);	// exact match

		int y = 12;
		func(&x);	// exact match
		// conversion from T* to const T*
	}
*/

/*
	void func(int(*)(int)); 
	// func's parameter variable is a function pointer
	// func can call with address of int(int) function

	int foo(int);

	int main()
	{
		func(&foo); 	// exact match

		func(foo);	// exact match
		// (foo -> foo* ) function to pointer conversion
	}
*/

/*
	void func(int);
	void func(double);
	void func(long);
	
	int main()
	{
		func(12u);	// syntax error
		// both of 3 overloads creates ambiguity error
	}
*/

/*
	void func(long double);
	void func(char);

	int main()
	{
		func(3.4);	// syntax error
		// both of 2 overloads creates ambiguity error
	}
*/

/*
	void func(double); // exact match
	void func(float);  // promotion
	
	int main()
	{
		func(3.5);
		// exact match will be called.
	}
*/

/*
	void func(int);         // integral promotion
	void func(double);	// conversion
	void func(long double); // conversion

	
	int main()
	{
		func('A');
		// promotion from char ==> int will be called.
	}
*/

/*
	void func(int);         // integral promotion
	void func(double);	// conversion
	void func(long double); // conversion

	int main()
	{
		bool flag{};
		func(flag);
		// promotion from bool ==> int will be called.
	}
*/

/*
	void func(unsigned long); 	// conversion
	void func(long);		// conversion
	
	int main()
	{
		int ival{ 32 };
		func(ival);
		// 2 overloads creates ambiguity error
	}
*/

/*
	void func(int*);        // non-const objects will come here
	void func(const int*);	// const objects will come here

	int main()
	{
		const int x = 12;
		func(&x);
		// only void func(const int*); is viable.

		int y = 10;
		func(&y);
		// both [void func(int*);] and [void func(const int*);] are viable
		// because of they are const overloads, both overloads are exact match.
		// BUT [void func(int*)] WILL BE CHOSEN !!
	}
*/

/*
	void func(const int&)
	{
		std::cout << "func (const int&)\n";
	}
	void func(int&)
	{
		std::cout << "func (int&)\n";
	}

	int main()
	{
		const int x = 12;
		func(x);
		// only void func(const int&); is viable.

		int y = 10;
		func(y);
		// both [void func(int&);] and [void func(const int&);] are viable
		// because of they are const overloads, both overloads are exact match.
		// BUT [void func(int&)] WILL BE CHOSEN !!
	}
*/

/*
	void func(int x, int y = 0);
	void func(int x);

	int main()
	{
		func(24); // syntax error (AMBIGUITY)
		// both overloads are exact match

		func(1,5);
		// only [void func(int x, int y = 0);] is viable.
	}
*/

/*
	void func(int);		// called by value
	void func(int&);	// called by reference

	int main()
	{
		int x{};
		func(x); // syntax error (AMBIGUITY)
	}
*/

/*
	void func(int);		
	void func(int&);	

	int main()
	{
		func(10); // 10 is PR value expression
		// only [void func(int);] is viable
	}
*/

/*
	void func(int);
	void func(const int&); // const int& can bind with PR value expression

	int main()
	{
		func(4); // syntax error (AMBIGUITY)
	}
*/

/*
	void func(int*);    // from 0 to int* (null pointer conversion)
	void func(int);		// exact match

	int main()
	{
		func(0);
		// both overloads are viable.
		// void(int) will be called.

		func(nullptr);
		// only [void func(int*);] overload is viable.
		// no conversion from nullptr_t to int.
	}
*/

/*
	void func(int*);   	// from 0 to int* (null pointer conversion)
	void func(double);	// from int to double // conversion

	
	int main()
	{
		func(0); // syntax error (AMBIGUITY)
		// both overloads are conversion.
	}
*/

/*
	void func(int*);    	// from nullptr_t to int* conversion
	void func(double*);	// from nullptr_t to double* conversion

	
	int main()
	{
		func(nullptr); // syntax error (AMBIGUITY)
		// both overloads are conversion.
	}
*/

/*
	void func(std::nullptr_t);  	// exact match
	void func(int*);		// conversion
	void func(double*);		// conversion
	
	int main()
	{
		func(nullptr);
		// void(std::nullptr_t) will be called.
	}
*/

/*
	void func(void*)
	{
		std::cout << "func(void*) called\n";
		// int* to void* conversion is viable
	}
	void func(bool)
	{
		std::cout << "func(bool) called\n";
		// int* to bool conversion is viable
	}

	int main()
	{
		int x = 555;
		func(&x);
		// both overloads are conversion.
		// SPECIAL OCCASION!!!!! [void func(void*);] will be called.
	}
*/

/*
	class Myclass {};

	void func(Myclass&);  //1
	void func(Myclass&&); //2

	int main()
	{
		Myclass m;

		func(m);			
		// m object is L value expression.
		// only 1st overload is viable. 

		func(Myclass{});	
		// temporay object(gecici nesne) PR value expression.
		// only 2nd overload is viable.

		func(std::move(m));	
		// std::move(m) is PR value expression.
		only 2nd overload is viable.
	}
*/

/*
	class Myclass {

	};
	void func(const Myclass&)	//1 
	{
		std::cout << "const L value ref\n";
	}
	void func(Myclass&&)		//2
	{
		std::cout << "R value ref\n";
	}
	// This overloads are move overloads.

	int main()
	{
		Myclass m;

		func(m);
		// m object is L value expression.
		// only 1st overload is viable.

		func(Myclass{});   
		// Both overloads are viable. [const Myclass&] can also bind PR value expression.
		// But the 2nd overload [void func(Myclass&&);]  will be called.
	}
*/

/*
	class Myclass {};

	void func(Myclass&)	// 1
	{
		std::cout << "(1) L VALUE REF\n";
	}
	void func(const Myclass&) // 2
	{
		std::cout << "(2) CONST L VALUE REF\n";
	}
	void func(Myclass&&) // 3
	{
		std::cout << "(3) R VALUE REF\n";
	}

	int main()
	{
		Myclass m;
		 func(m);
		// 1st and 2nd overloads are viable, but 1st overload will be called.

		const Myclass cm;
		func(cm);		   
		// Only 2nd overload is viable so 2nd overload will be called.

		func(Myclass{});  
		// 2nd and 3rd overloads are viable, but 3rd overload will be called.
	}
*/

/*
	void func(float, double, int);			// 1
	void func(int, long, unsigned);			// 2
	void func(double, unsigned, float);		// 3

	// Overload's 1 parameter needs to be better than other overloads, but other parameters can not be worse.
	// If first parameter better in 1 and second parameter is better in 2 or 3 ambiguity error.

	int main()
	{
		func(3.4f, 12, true);
		// func() paramaters		[float, int, bool]
		// 1st func() overload 	->  	[exact match, conversion , promotion ]
		// 2nd func() overload	->	[conversion , conversion , conversion]
		// 3rd func() overload	->  	[conversion , conversion , conversion]
	
		// 1'st func overload will be called.

		func(3.4f, 12, 5.3f);
		// func() paramaters		[float, int, bool]
		// 1st func() overload 	->  	[exact match, conversion , promotion ]
		// 2nd func() overload	->	[conversion , conversion , conversion]
		// 3rd func() overload	->  	[conversion , conversion , exact match]

		// in 1st parameter 1st func overload is better 
		// in 3rd parameter 3rd func overload is better
		// AMBIGUITY ERROR 

		func(true, 12, 4.5);
		// func() paramaters		[bool, int, double]
		// 1st func() overload 	->  	[conversion, conversion , conversion]
		// 2nd func() overload	->	[promotion , conversion , conversion]
		// 3rd func() overload	->  	[conversion, conversion , conversion]

		// 2nd func overload will be called.

		func(12, 13, 3.5);
		// func() paramaters		[int, int, double]
		// 1st func() overload 	->  	[conversion , conversion , conversion]
		// 2nd func() overload	->	[exact match, conversion , conversion]
		// 3rd func() overload	->  	[conversion , conversion , conversion]

		// 2'nd func overload will be called.

		func(12, 6u, 3.5);
		// func() paramaters		[int, unsigned int, double]
		// 1st func() overload 	->  	[conversion , conversion , conversion]
		// 2nd func() overload	->	[exact match, conversion , conversion]
		// 3rd func() overload	->  	[conversion , exact match, conversion]

		// in 1st parameter 2nd func overload is better 
		// in 2nd parameter 3rd func overload is better
		// AMBIGUITY ERROR 

		func(12, 15, true);
		// func() paramaters		[int, int, bool]
		// 1st func() overload 	-> 	[conversion , conversion , promotion ]
		// 2nd func() overload	->	[exact match, conversion , conversion]
		// 3rd func() overload	->  	[conversion , conversion , conversion]

		// in 1st parameter 2nd func overload is better 
		// in 3rd parameter 1st func overload is better
		// AMBIGUITY ERROR 
	}
*/

/*
	void func(unsigned int);
	void func(long);
	
	int main()
	{
		bool flag{};
		func(static_cast<unsigned>(flag));
		func(static_cast<long>(flag));
	}
*/

/*
	-----------------------------
	| name decoration(mangling) |
	-----------------------------
*/

/*
	#include "different.h"
	#include "same.h"
	
	int main()
	{
		int x{};
	
		// x = func_difference(12, 34);
		std::cout << "x = " << x << '\n';
	
		// Linker error.
		// LNK2019	unresolved external symbol "int __cdecl func_difference(int,int)" 
		// (? func_difference@@YAHHH@Z) referenced in function main
	
		// Linker will found out the reference in main()'s object code
		// then link the caller and callee functions.
		// But Linker couldn't found the function that have been called [func_difference(int,int)]
	
		// In C because of there is no function overloading.
		// C Compiler will only use the function's name in the reference that it wrote for Linker.
		// But in C++ because of there is function overloading mechanism 
		// C++ Compiler will also use function's signature in the reference.
	
		// So in this scenerio C++ compilers reference code[caller] 
		// and C compilers reference code[callee] is not same.
	
		x = func_same(12, 13);
		std::cout << "x = " << x << '\n';
	}
*/
