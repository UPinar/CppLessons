#include <iostream>

/*
                        ==================
                        | Type Deduction |
                        ==================
  -> Compile Time (no runtime cost) 

  -> If the type includes a lot of tokens, 
    type deduction makes it easier.
  std::vector<std::pair<std::list<std::vector::iterator>, 
                        std::list<std::vector::iterator>>>
  
*/

/*
                      =======================
                      | auto type deduction |
                      =======================
*/

/*
  - type deduction is not happening for the variable,
    type deduction is happening for `auto` keyword.

  auto x = expr;
  if auto deduce to int   -> x's data type is int

  const auto x =  expr;
  if auto deduce to int   -> x's data type is const int

  auto* x = expr;
  if auto deduce to int   -> x's data type is int* (a pointer to int)
  if auto deduce to int*  -> x's data type is int**
*/

/*
  auto x; // syntax error -> default initialization is NOT VALID
  // error: declaration of 'auto x' has no initializer
*/

/*
  auto x = expr;  // copy initialization

  auto x(expr);   // direct initialization

  auto x{ expr }; // value initialization
*/

/*
                        ------------------
                        | auto x = expr; |
                        ------------------
*/

/*
  auto x = 10;  // x's data type is int

  auto x = 'A'; // x's data type is char

  auto x = 'A' + 'A'; // x's data type is int(integral promotion)
*/

/*
  char c = 12;
  auto x = +c;  // x's data type is int (integral promotion)
*/

/*
  int a = 5;
  int b = 6;
  double dval = 3.4;
  auto x = a > 2 ? b : dval;
  // type conversion rules applied between 2nd and 3rd operands 
  // of ternary operator.
  // "int + double" expression's type is double
  // x deduce to double
*/

/*
  int a = 5;
  int b = 6;
  auto x = a > b; // x's data type is bool in C++, int in C
*/

/*
  int arr[]{ 3, 6, 9 };
  auto x = arr; // x's data type is int* (array to pointer conversion)
*/

/*
  char str[] = "hello";
  auto x = str; // x's data type is char* (array decay)
*/

/*
  const int a[] = { 3, 1, 8, 2 };
  auto x = a; // x's data type is const int* (array decay)
*/

/*
  auto x = "hello";  // x's data type is const char* (array decay)
  // "hello" expression's data type is const char[6]
*/

/*
  const int x = 20;
  auto b = x;
  // we have a const int variable (x)
  // to copy const int variable to new variable 
  // we need to create a space for int.
  // const int variable is giving a promise 
  // that its value will not change
  // but b variable is not need to give the same promise
  // b's data type is int (CONST WILL DROP)
*/

/*
  // -----------------------------------------------------------
  int a = 10;
  int* const p = &a;
  auto x = p;

  // p's data type is a const pointer to int  (TOP LEVEL CONST)
  // x's data type is pointer to int (int*)
  // TOP-LEVEL CONST WILL DROP

  // -----------------------------------------------------------
  const int* b = &a;
  auto y = b;

  // b's data type is a pointer to const int. (LOW-LEVEL CONST)
  // y's data type is a pointer to a const int (const int*)
  // LOW-LEVEL CONST WILL NOT DROP

  // -----------------------------------------------------------
  const int* const c = &a;
  auto z = c;
  // c's data type is a const pointer to const int (TOP-LOW-LEVEL CONST)
  // z's data type is a pointer to a const int (const int*)
  // TOP-LEVEL CONST WILL DROP
  // LOW-LEVEL CONST WILL NOT DROP

  // -----------------------------------------------------------
*/

/*
  int x = 10;
  int& r = x;
  auto y = r;
  // y's data type is int.

  const int& cr = x;
  auto z = cr;
  // z's data type is int
  // CONST WILL DROP
*/

/*
  int&& r = 10; 
  // r's declaration type is int&&

  r;
  // "r" expressions data type is int 
  // it is an LValue expression.
*/

/*
  int foo(int);
  // foo functions data type is           -> int(int)
  // foo function addresses data type is  -> int(*)(int)

  int (*p)(int) = foo;  // implicit function to pointer conversion
  int (*p)(int) = &foo;
  // These 2 lines are equivalent

  auto fp = foo;        // implicit function to pointer conversion
  // fp's data type is not a function type
  // fp's data type is a function pointer type
  // fp's data type is int (*fp)(int)
*/

/*
  int x = 10;
  int* ptr = &x;

  const auto p = ptr;
  // const [const auto p = ptr;] in declaration statement 
  // make p variable as TOP-LEVEL const
  // p's data type is int*

  // "const auto p = ptr;" declaration statement's 
  // data type is int* const (constant pointer to int)
*/

/*
                      -------------------
                      | auto &y = expr; |
                      -------------------
*/

/*
    const WILL NOT drop.
    no array to pointer conversion(array decay)
    no function to function pointer conversion(function decay)
*/

/*
  int x = 10;
  auto& y = x;  // y's data type is int&
*/

/*
  int x = 10;
  auto& y = x + 5; // syntax error
  // error: cannot bind non-const lvalue reference of type 'int&' 
  // to an rvalue of type 'int'

  // "x + 5" expression is an RValue expression
  // initializing L value reference 
  // with an RValue expression is NOT VALID.
*/

/*
  const int x = 10;
  auto& y = x;
  // auto's data type will be deduced to const int
  // y's data type is const int& (reference to constant int)
*/

/*
  int x = 10;
  int* const p = &x; // TOP-LEVEL CONST (constant pointer to int)
  auto& y = p;
  // auto's data type will be deduce to 
  // int* const (constant pointer to int)

  // y's data type is int* const& 
  // (reference to constant pointer to int)
*/

/*
  int a[5] = { 1, 2, 3, 4, 5 };
  auto& x = a;
  // auto's data type is deduced to int[5]
  // x's data type is int(&)[5] (reference to int[5])

  auto& k = a; 
  // k's data type is int(&)[5] (reference to int[5])
  int(&m)[5] = a; 
  // m's data type is int(&)[5] (reference to int[5])

  using ar = int[5];
  ar& n = a;
  // n's data type is int(&)[5] (reference to int[5])

  // Those 3 lines are equivalent.
*/

/*
  auto& x = "hello";
  // auto's data type is const char[6]
  // x's data type is const char(&)[6] (reference to const char[6])

  const char(&y)[6] = "hello";
  // y's data type is const char(&)[6] (reference to const char[6])

  using constCharArray = const char[6];
  constCharArray& z = "hello";
  // z's data type is const char(&)[6] (reference to const char[6])
  
  // Those 3 lines are equivalent.
*/

/*
  int foo(int);

  //------------------------------------------------------------
  using FUNCTION  = int(int);
  using FPTR      = int(*)(int);

  FUNCTION* fp1 = foo; 	
  // function to function pointer conversion (function decay)
  FUNCTION* fp1_2 = &foo;
  // Those 2 lines are equivalent.

  //------------------------------------------------------------
  FPTR fp2 = foo;		
  // function to function pointer conversion (function decay)
  FPTR fp2_2 = &foo;
  // Those 2 lines are equivalent.

  //------------------------------------------------------------
  auto fp3 = foo;		
  // function to function pointer conversion (function decay)
  auto fp3_2 = &foo;
  // Those 2 lines are equivalent.

  //------------------------------------------------------------
  FUNCTION* fp_a = foo;
  FPTR fp_b = foo;
  auto fp_c = foo;
  // Those 3 lines are equivalent.

  //------------------------------------------------------------
  auto& f1 = foo;    
  // function decay is NOT HAPPENING in `auto&` deduction
  // auto's data type will be deduce to int(int)
  // f1's data type is int(&)(int) (reference to function)

  //------------------------------------------------------------
  auto& f_a = foo;
  int(&f_b)(int) = foo;
  FUNCTION& f_c = foo;
  // Those 3 lines are equivalent.

  //------------------------------------------------------------
*/

/*
              --------------------------------------------
              | auto && z = expr; (forwarding reference) |
              --------------------------------------------
*/

/*
                    ------------------------
                    | reference collapsing |
                    ------------------------
*/

/*
  1.  T&    &     -> T&
  2.  T&    &&    -> T&
  3.  T&&   &     -> T&
  4.  T&&   &&    -> T&&
*/

/*
  using IREF = int&;

  int a = 34;

  IREF&   x = a;    // int&  &  -> int& (x's data type is int&)
  int&    y = a;
  // Those 2 lines are equivalent.

  int b = 35;

  IREF&&  k = b;    // int&  && -> int& (k's data type is int&)
  int&    l = b;
  // Those 2 lines are equivalent.
*/

/*
  using IREFREF = int&&;

  int a = 36;

  IREFREF&  x = a;    // int&& &  -> int& (x's data type is int&)
  int&      y = a;  
  // Those 2 lines are equivalent.

  IREFREF&&   k = 12; // int&& && -> int&& (k's data type is int&&)
  int&&       l = 12;
  // Those 2 lines are equivalent.
*/

/*
  auto&& r = expr;
  -> if expr is LValue expression ==> auto type deduce to T&
  -> if expr is RValue expression ==> auto type deduce to T
*/

/*
  int x = 10;
  auto&& y = x;   
  // "x" is an LValue expression, its data type is int
  // auto's data type will be deduced to int&(T&)
  // int& && -> int& (y's data type is int&)

  auto&&  k = x;
  int&    l = x;
  // Those 2 lines are equivalent.
*/

/*
  auto&& y = 10;
  // "10" is an RValue expression, its data type is int
  // auto's data type will be deduced to int(T)
  // y's data type is int&& (no reference collapsing)

  auto&&  k = 10;
  int&&   l = 10;
  // Those 2 lines are equivalent.
*/
  
/*
  const int x = 190;
  auto&& r = x;
  // "x" is an LValue expression, its data type is const int
  // auto's data type will be deduced to const int&(T&)
  // const int&   && -> const int&  (reference collapsing)
  // r's data type is const int&

  auto&&      k = x;
  const int&  l = x;
  // Those 2 lines are equivalent.
*/

/*
  int x = 10;
  int* ptr = &x;

  auto&& a = *ptr;
  // "*ptr" is an LValue expression, its data type is int
  // auto's data type will be deduced to is int&(T&)
  // int& && -> int& (a's data type is int&)

  auto&&  k = *ptr;
  int&    l = *ptr;
  // Those 2 lines are equivalent.
*/

/*
                    ------------------------
                    | trailing return type |
                    ------------------------
*/

/*
  auto func()-> int
  {
    // func() is a function and its return type is int
  }
*/

/*
  int foo(int);
  // declaring a fuction have a return type of int (*)(int)

  int(*bar())(int) 
  {
    return &foo;
  }
  // bar()'s return type is int(*)(int)

  auto baz() -> int(*)(int)
  {
    return &foo;
  }
  // baz()'s return type is int(*)(int)

  // bar and baz functions are equivalent
*/

/*
  int a[10]{};

  auto foo() -> int(*)[10]
  {
    return &a;
  }
  // foo()'s return type is int(*)[10] (address of 10 element int array)
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
  // auto's type will be deduced to int(*)(double)
*/


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
  Type deduction when decltype specifier's operand is an identifier.
    - decltype(x)
    - decltype(a.m_x)
    - decltype(ptr->val)
*/

/*
	int x = 10;
	decltype(x); // decltype(x)'s data type is int
	// if x's data type is int
  // decltype(x)'s data type is int

	decltype(x) intVar;

	struct Data {
		decltype(x) y;
		int y;
		// Those 2 lines are equivalent.
	};

	double y = 3.4;

	decltype(x) foo(decltype(y));
	int foo(double);
	// Those 2 lines are equivalent.
*/

/*
	const int x = 13;
	decltype(x) y = 15; 
  // x's data type is const int
	// decltype(x)'s type is const int 

	decltype(x) z; // syntax error
  // error: uninitialized 'const z' 
	// const objects can not be default initialized
*/

/*
	const int x = 13;
	const int* const ptr = &x;

	decltype(ptr) p = &x; 
	// decltype(ptr)'s data type is const int* const
  // (constant pointer to a constant int)
*/

/*
	int a[5]{};

	decltype(a) b;  // (no array to pointer conversion)
  // b's data type is int a[5]
	int c[5]; 
	// Those 2 lines are equivalent. 
*/

/*
	int x = 10;
	int y = 456;
	
	int& r = x;
	decltype(r) t = y;
	// decltype(r)'s data type is int&, t's data type is int&
*/

/*
	int&& r = 10;
	decltype(r) x = 5; 
	// decltype(r)'s data type is int&&, x's data type is int&&
*/

/*
	int x = 5;
	int y = 10;
	
	decltype(x)& r = y;
	// decltype(x)'s data type is int, r's data type is int&
*/

/*
	int x = 5;
	const auto a = x; 
	// auto's data type will be deduced to int 
	// a's data type is const int

	int y = 5;
	const decltype(y) b; // syntax error
  // error: uninitialized 'const b'
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
		// decltype(mx.a)'s data type is int

		Myclass* mp{ &mx };
		decltype(mp->dval) dx = 3.4;
		// decltype(mp->dval)'s data type is double
	}
*/

/*
                      ------------------------
                      | decltype(expression) |
                      ------------------------
*/

/*
  Type deduction when decltype specifier's operand is an expression.
    - decltype((x))
    - decltype(+x)
*/

/*
	data type of decltype(expr) depends on the operand's "Value Category"
	
	- PRValue expression  -->   T
	- LValue expression   -->   T&
	- XValue expression   -->   T&&
*/

/*
	int x = 10;
	decltype(x + 4); 
	// "x + 4" is a PRValue expression(T), its data type is int
	// decltype(x + 4)'s data type is int
*/

/*
	int x = 10;
	int* ptr = &x;

	decltype(*ptr);
	// "*ptr" is  LValue expression(T&), its data type is int
	// decltype(*ptr)'s data type is int&

	decltype(*ptr) b; // sythax error 
  // error: 'b' declared as reference but not initialized
  // L Value reference must be initialized
*/

/*
	int x = 10;
	int a[3]{};
	
	decltype(a[2]);
	// "a[2]" is LValue expression(T&), its data type is int
	// decltype(a[2])'s data type is int&
*/

/*
	int x = 10;
	decltype(+x)
	// "+x" is PRValue expression, its data type is int
	// decltype(+x)'s data type is int
*/

/*
	int x = 10;
	
	decltype(x) y ; 
	// "x" is an identifier, decltype(x)'s data type is int

	decltype((x)) z; 
	// "(x)" is an LValue expression(T&), its data type is int
  // decltype((x))'s data type is int&
*/

/*
	int foo();    // foo function's return type is int
	int& bar();   // bar function's return type is int&(L value reference)
	int&& baz(); 	// baz function's return type is int&&(R value reference) 

	decltype(foo());
	// "foo()" is a PRValue expression(T), its data type is int
	// decltype(foo())'s data type is int

	decltype(bar());
  // "bar()" is an LValue expression(T&), its data type is int&
  // decltype(bar())'s data type is int&

	decltype(baz());
  // "baz()" is an XValue expression(T&&), its data type is int&&
  // decltype(baz())'s data type is int&&
*/

/*
	int x = 10;

	decltype(x++);
	// "x++" is a PRValue expression(T), its data type is int
	// decltype(x++)'s data type is int

	decltype(++x);
  // "++x" is an LValue expression(T&), its data type is int
  // decltype(++x)'s data type is int&
*/


/*
        =======================================================
        | unevaluated context (İşlem kodu üretilmeyen bağlam) | 
        =======================================================          
*/

/*
  #include <cstddef>  // std::size_t

  int main()
  {
    int x = 10;
    std::cout << "x = " << x << '\n';
    // output -> x = 10

    size_t sz = sizeof(x++);
    std::cout << "x = " << x << '\n';
    // output -> x = 10
  }
*/

/*
	sizeof(x++);     -> value of x is not going to increase
	sizeof(foo());   -> foo() function will not call

	- NO SIDE EFFECT WILL HAPPEN
*/

/*
  int main()
  {
    int* p = nullptr;
    int a[5]{};
    int x = 356;

    auto t = a[67]; 
    // undefined behavior.(array bound overflow)

    *p = 4;
    // undefined behavior.(null pointer dereferencing)

    x << 45;
    // undefined behavior.

    sizeof(*p) + sizeof(a[67]) + sizeof(x << 8765);
    // no undefined behaviour because of unevaluated context
  }
*/


/*
	// C code example

  #include <cstdlib>  // std::malloc

	typedef struct {
		int x, y;
		double dval;
	}*MyclassPtr;
	
	int main()
	{
		MyclassPtr p;
		// type does not have a name, only a pointer to it
		// but we can create a dynamic storage duration object
	
		MyclassPtr px = (MyclassPtr)malloc(sizeof(*px));
	
		// if *px evaluated it will cause undefined behaviour
		// but we use it inside unevaluated context to find the structs size.
	}
*/

/*
	In C++ there are more unevaluated operators,
	  - sizeof
	  - decltype
	  - typeid
	  - noexcept 

  In C, unevaluated context is only happens in `sizeof()` operator.
*/

/*
	int main()
	{
		int x = 10;
    std::cout << "x = " << x << '\n'; // output -> x = 10

		decltype(x++) y = 6;
    std::cout << "x = " << x << '\n'; // output -> x = 10
    // x's value is not changed because decltype operators
    // operand is an unevaluated context.

		int a[10]{};
		decltype(a[20]) y = x;
    // "a[20]" expression is undefined behavior
    // but we use it inside unevaluated context
    // so no undefined behavior will happen.
	}
*/