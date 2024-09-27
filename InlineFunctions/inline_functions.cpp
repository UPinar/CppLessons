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
  - When a function declared in header file, compiler will generate
    that functions input&output assembly code.
    i.e : 
          -> changing stack pointers location
          -> arguments to registers move codes
          -> return value to register move code

    then linker will link the function call inside source file 
    with the input&output code that compiler generated.

  Inline expansion optimization
  -----------------------------
  - If compiler saw the function definition
    it can compile the code directly where function was called 
    without generating input&output assembly code. (cost will decrease)

  - functions that have small codes are great candidates for 
    inline functions.
      -> one liner functions
      -> classes GET and SET functions
*/


/*
	// if foo() function will be used in lots of source files(.cpp),
  // it must be defined in the header(.h) file
  // for compiler to apply inline expansion optimization.

	int foo(int x, int y)
	{
		return x * x * y * y + 1;
	}
  // compiler already know foo function's definition here

	int main()
	{
		int a = 46;
		int b = 345;
	
		auto x = foo(a, b);
		// compiler can change this function call(inline expansion) 
    // and directly calculate the return value in compile time.
    // without generating foo functions input&output assembly code.

		auto y = a * a * b * b + 1;
    // foo(a, b); function call will be replaced with this line
    // by the compiler. (inline expansion optimization)
	}
*/

/*
  - making functions `inline`, will not guarantee that 
    compiler will apply inline expansion optimization for that function.  
    it might or it might not.

  - if a function wanted to be inline expanded by the compiler,
    it must be defined in the header(.h) file and should be made
    `inline` for not violating the One Definition Rule (ODR)
    for different source files(.cpp) that include that header file.
*/

/*
                    ----------------------------
                    | One Definition Rule(ODR) |
                    ----------------------------
*/

/*
  - If any function's DEFINITION count is greater than 1,
    program will become ill-formed.
    It will violate the One Definition Rule(ODR).
*/

/*
	int g_x = 10;
	int g_x = 10; // syntax error (violation of ODR)
  // error: redefinition of 'int g_x' 

	void func(int x){
		++x;
	}

	void func(int x){
		++x;
	}
  // syntax error (violation of ODR)
  // error: redefinition of 'void func(int)'
*/

/*
	//  one.cpp
  //  ------------
	void func(int x) {}

  //  two.cpp
  //  ------------

  //  three.cpp
  //  ------------

  //  four.cpp
  //  ------------
	void func(int x) {}

  //  five.cpp
  //  ------------

  // ODR violation.
  // compiler will not give any error or warning
  // because compiler is checking only one .cpp file at a time.
  // In the linking phase, linker will give an error.
  // linker error : multiple definition of `func(int)'
*/

/*
	// some.h
  // ------------
	int func(int x, int y) { return x * x - y; }

	// one.cpp
  // ------------
	#include "some.h"

  // two.cpp
  // ------------
	#include "some.h"

	// ODR violation 
  // linker error : multiple definition of `func(int, int)'
*/

/*
	// some.h
  // ------------
	int global_var = 12;

	// one.cpp
  // ------------
	#include "some.h"
  
  // two.cpp
  // ------------
	#include "some.h"

	// ODR violation 
  // linker error : multiple definition of `global_var'
*/

/*
	// some.h
  // ------------

	extern int x;             // global variable declaration
	int func(int x, int y);	  // function declaration

	// one.cpp
  // ------------
	#include "some.h"
  
  // two.cpp
  // ------------
	#include "some.h"

	// NO ODR violation
*/


/*
	// one.cpp
  // ------------
	// inline int foo(int x, int y) { return x * x - y; }

  // two.cpp
  // ------------
	// inline int foo(int x, int y) { return x * x + y; }	

	// `inline` foo function's definitions are not token by token same.
	// ODR violation.
*/

/*
	// one.cpp
  // ------------
	inline int func(int x, int y) { return x * x + y; }
  
  // two.cpp
  // ------------
	inline int func(int x, int y) { return x * x + y; }

  // `inline` foo function's definitions are token by token same.
  // NO ODR violation.
*/
  
/*
	// some.h
  // ------------
	inline int foo(int x, int y) { return x * x - y; }		

	// one.cpp
  // ------------
  #include "some.h"
	
  // two.cpp
  // ------------
	#include "some.h"

  // `inline` function definition in an header(.h) file 
  // guarantees that, every source(.cpp) file that includes 
  // the header file, will have the same function definition
  // token by token.
	// NO ODR Violation.
*/


/*
	// some.h
  // ------------
	static int foo(int x) { return x * x - 6; }
	inline int func(int x) { return x * x * x + 2; }

	// one.cpp
  // ------------
  #include "some.h"
	
  // two.cpp
  // ------------
	#include "some.h"

  // -----------------------------------------------------------

	// `static` keyword makes function's linkage internal.

	// `static` function will also act like an `inline` function.
  // every source(.cpp) file that includes the header file 
  // can use the `static` function without violating ODR.
	// NO ODR Violation.

  // -----------------------------------------------------------

  // for `inline` function,
  // every source(.cpp) file that includes the header file
  // will have the same `inline` function definition token by token 
  // and will have the same function addresses.

  // -----------------------------------------------------------

  // for `static` function,
  // every source(.cpp) file that includes the header file
  // will have the same `static` function definition token by token
  // but will have different function addresses.

  // -----------------------------------------------------------
*/

/*
  // some.h
  // ------------
	constexpr int foo(int x, int y) { return x * x - y; }

  // one.cpp
  // ------------
  #include "some.h"
	
  // two.cpp
  // ------------
	#include "some.h"

	// constexpr functions are IMPLICITLY INLINE functions.
	// constexpr function definition in header(.h) file
  // will not violate ODR.
*/

/*
	class AClass {
	public:
		void foo(int x, int y);
	};

	// non-static member functions  -> IMPLICITLY INLINE functions.
	// static member functions      -> IMPLICITLY INLINE functions.
	// friend functions             -> IMPLICITLY INLINE functions.
	// function templates           -> IMPLICITLY INLINE functions.
*/
	
/*
                ----------------------------
                | inline variables (C++17) |
                ----------------------------
*/

/*
  - Before C++17,  
    -> global variables
    -> classes static data members
  can not be defined in header files because of ODR violation. 
  It was causing program to be ill-formed.

*/

/*
  // before C++17 global inline variables can be used with this method

  // some.h
  // ------------
	inline int& get_global_inline_variable()
	{
		static int x{ 30 };
		return x;
	}

  // one.cpp
  // ------------
  #include "some.h"
  int main()
  {
    int& ref = get_global_inline_variable();
    ref = 50;
  }

  // two.cpp
  // ------------
  #include "some.h"
  void some_function()
  {
    int& ref = get_global_inline_variable();
    std::cout << ref << '\n';  // output -> 50
  }
*/

/*
  // After C++17, `inline` global variables can be defined 
  // in header(.h) files without violating ODR.

	// some.h
  // ------------ 
	inline int x = 10;	// `inline` global variable.

  // one.cpp
  // ------------
  #include "some.h"

  // two.cpp
  // ------------
	#include "some.h"

  // NO ODR violation.
*/