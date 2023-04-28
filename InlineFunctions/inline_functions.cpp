#include <iostream>

/*
	====================
	| inline functions |
	====================
*/

/*
	---------------------------------
	| inline expansion optimization |
	---------------------------------
*/

/*
	Normally if you declare a function in a file. 
	Compiler will generate functions input&output assembly code
	e.g,. changing stack pointers location, arguments to registers move codes,
	return value to register move code...
	Then Linker will link the compiler code and the function call() inside cpp file.
	
	Inline expansion optimization
	-------------------------------
	If compiler saw the function decleration.
	It can compile the code when it sees the function call() in (.cpp) file.
	-> Cost will decrease

	-> functions that have small codes(inline expansion will eleminate input&output codes),
		One Liner funtions, Classes GET, SET functions will be a great candidate to be inline functions.
*/

/*
	// If foo() function will be used in a lot of (.cpp) files. 
	// It must be define in header(.h) file.

	int foo(int x, int y)
	{
		return x * x * y * y + 1;
	}
	
	int main()
	{
		int a = 46;
		int b = 345;
	
		auto x = foo(a, b);
		// compiler can change the code(inline expansion) 
		// and calculate the return value in compile time.

		auto y = a * a * b * b + 1;
		// foo() functions return value will calculate like this line.
		// seems like foo() functions is not invoking.
	}
*/

/*
	if you make a function `inline`, compiler might not make
	inline expansion optimization for that function.
	
	if you did not make a function inline, compiler can apply inline expansion 
	optimization for that function too.

	if you want inline expansion optimization apply to a function by the compiler,
	and you want to use that function in many .cpp files, 
	you need to put that function in header(.h) file and
	make it inline for not violating the One Definition Rule (ODR)
	then include that header(.h) file in .cpp files.
*/

/*
	----------------------------
	| One Definition Rule(ODR) |
	----------------------------
*/

/*
	If a functions definition count is greater than 1, that will make the program ill-formed.
	It is violating One Definition Rule.
*/

/*
	int g = 10;
	int g = 10;
	// violating ODR, syntax error.


	void func(int x)
	{
		++x;
	}

	void func(int x)
	{
		++x;
	}
	// violating ODR, syntax error.
*/

/*
	one.cpp
		void func(int x) {}
	two.cpp
	three.cpp
	four.cpp
		void func(int x) {}
	five.cpp

	ODR VIOLATION!!
	Compiler could't found out if there same functions in different .cpp files.
	Because compiler checks only 1 cpp file each time.
	[Ill formed, but no diagnostic required]
*/

/*
	some.h
		int func(int x,int y) {return x * x - y;}

	one.cpp
		#include "some.h"
	two.cpp
	three.cpp
		#include "some.h"
	four.cpp
	five.cpp

	ODR VIOLATION!!
*/

/*
	some.h
		int globalVariable = 12;

	one.cpp
	two.cpp
		#include "some.h"
	three.cpp
		#include "some.h"
	four.cpp
	five.cpp

	ODR VIOLATION!!
*/

/*
	some.h
		extern int x;			// global variable decleration
		int func(int x, int y);		// function decleration

	one.cpp
	two.cpp
		#include "some.h"
	three.cpp
		#include "some.h"
	four.cpp
	five.cpp

	There is NO ODR Violation.
*/

/*
	one.cpp
	two.cpp
		inline int func(int x,int y) {return x * x - y;}
	three.cpp
		inline int func(int x,int y) {return x * x + y;}	
	four.cpp
	five.cpp

	Inline functions definitions are not token by token same.
	One of them returns [x * x - y] other one returns [x * x + y]
	ODR VIOLATION!!
*/

/*
	one.cpp
	two.cpp
		inline int func(int x,int y) {return x * x + y;}
	three.cpp
		inline int func(int x,int y) {return x * x + y;}
	four.cpp
	five.cpp

	NO ODR Violation.
	Both inline functions definitions in the same project are token by token same.
*/

/*
	some.h
		inline int func(int x,int y) {return x * x - y;}		// inline function

	one.cpp
	two.cpp
		#include "some.h"
	three.cpp
		#include "some.h"
	four.cpp
	five.cpp

	There is NO ODR Violation.
	Inline function in .header file guarantees that, every .cpp file that include "some.h"
	will have the same inline function definition token by token.
*/

/*
	some.h
		static int foo(int x) {return x * x - 6;}
		inline int func(int x) {return x * x * x + 2;}

	one.cpp
		#include "some.h"
	two.cpp
		#include "some.h"
	three.cpp
	four.cpp
		#include "some.h"
	five.cpp

	// static keyword make the function have an internal linkage.

	// static is also act like inline,
	// different .cpp files can include and use foo() functions
	// without violating ODR rules.

	// The difference is, for inline function
	// every .cpp file that include and use that inline function
	// will get the same function and the same function address.
	// but for static function, every .cpp file will get the same function
	// but their addresses will be different.
*/

/*
	constexpr func(int x, int y);
	// constexpr functions are implicitly inline functions.
	// putting constexpr functions in header(.h) file will not violate ODR.

	
	class Myclass {
	public:
		// non-static member function
		void foo(int x, int y);
	};
	// non-static member functions are implicitly inline functions.
	
	// static member functions are implicitly inline
	// friend functions are implicitly inline
	// function templates are implicitly inline
*/

/*
	=============================
	| inline variables// C++ 17 |
	=============================
*/

/*
	Before C++17 global variables and classes static data members 
	can not be used in header files, they caused program to be ill-formed. 
*/

/*
	inline int& oldschool_global_inline_variable()
	{
		static int x{ 30 };
		return x;
	}
*/

/*
	some.h 
		inline int x = 10;	// inline global variable.

	one.cpp
		#include "some.h"
	two.cpp
		#include "some.h"
	three.cpp
	four.cpp
*/
