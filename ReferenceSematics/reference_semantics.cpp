#include <iostream>

/*
                      =======================
                      | reference semantics |
                      =======================
*/

/*
  There are 3 categories of references
    1. L value references
    2. R value references
    3. forwarding(universal) reference
*/

/*
  Primary Value Categories
  ------------------------
    1. L value
    2. PR value (pure R value)
    3. X value (eXpiring value)

  - compiler understands value category of the expression in compile time.
*/

/*
  int foo();
  int& func();
  int&& bar();

  int main()
  {
    10;         // PRValue expression

    int x = 10;
    x;          // LValue expression

    +x;         // PRValue expression
    ++x;        // LValue expression
    x++;        // RValue expression
    &x;         // LValue expression

    nullptr;    // PRValue expression

    foo();      // PRValue expression
    func();     // LValue expression
    bar();      // XValue expression
  }
*/

/*
                    C     C++
  ------------------------------------------
  ++x               R     L
  --x               R     L
  a = b             R     L
  x, y              R     L [if right operand is L value]
  x > y ? a : b     R     L
*/

/*
  Combined Value Categories
  -------------------------
  1. GL value		-> L value  or X value
  2. R value		-> PR value or X value
/*

/*
                      ----------------------
                      | L value references |
                      ----------------------
*/

/*
  int main()
  {
    int& ref; // syntax error -> references can not be default initialize
    // error: 'ref' declared as reference but not initialized
  }
*/

/*
  int main()
  {
    int x = 34;
    int& r = x;   // r binds to x

    std::cout << "x = " << x << '\n'; // output -> x = 34

    ++r;
    std::cout << "x = " << x << '\n'; // output -> x = 35

    r = 888;
    std::cout << "x = " << x << '\n'; // output -> x = 888

    int y = 5;
    r = y;
    std::cout << "x = " << x << '\n'; // output -> x = 5

    // references can not bind to another object
    // once they bind to an object.
  }
*/

/*
  int main()
  {
    int x = 33;
    int y = 66;
    int z = 99;

    int& r = x;
    std::cout << "x = " << x << '\n'; // output -> x = 33

    r = y; // x = y
    std::cout << "x = " << x << '\n'; // output -> x = 66

    r = z; // x = z
    std::cout << "x = " << x << '\n'; // output -> x = 99
  }
*/

/*
  // L Value references needs to be initialize with LValue expression

  int main()
  {
    int& r = 10;
    // "10" is an PRValue expression
    // error: cannot bind non-const lvalue reference of type 'int&'
    // to an rvalue of type 'int'
  }
*/

/*
  int main()
  {
    int x = 111;
    int* p{ &x };
    std::cout << "x = " << x << '\n'; // output -> x = 111

    int& r = *p;  // r binds to x

    r = 999;
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
    std::cout << "x = " << x << '\n'; // output -> x = 8

    ++r2; // ++x
    std::cout << "x = " << x << '\n'; // output -> x = 9

    ++r3; // ++x
    std::cout << "x = " << x << '\n'; // output -> x = 10
  }
*/

/*
  // references can bind to pointers.
  int main()
  {
    int x = 9;
    int* p{ &x };	// p is a pointer to x
    int*& r = p;	// r is a reference to p (r = p)

    ++*r; 	// *r ===> *p ===> x
    std::cout << "x = " << x << '\n'; // output -> x = 10
  }
*/

/*
  int main()
  {
    int* p = nullptr;

    int*& r = p;    // r = p
    int x = 10;
    r = &x;         // r = &x ===> p = &x
    *r = 99;        // *r ===> *p ===> x

    std::cout << "x = " << x << '\n'; // output -> x = 99
  }
*/

/*
  int main()
  {
    int 	x 	= 5;
    int* 	p 	= &x;
    int** ptr = &p;

    int**& r = ptr;   // r = ptr
    **r = 99;         // **r ===> **ptr ===> x

    std::cout << "x = " << x << '\n'; // output -> x = 99
  }
*/

/*
  int main()
  {
    //-------------------------------------------------
    int* p = nullptr;
    // "int* p = nullptr;" is a declaration statement
    // "*" token is a declerator

    //-------------------------------------------------
    int x = 10;
    int* ptr = &x;
    // "int* ptr = &x;" is a declaration statement
    // "*" token is a declerator

    // "&x" is an expression
    // "&" token is an operator

    //-------------------------------------------------
    *p = 45;
    // "*p" is an expression, "*" token is an operator

    //-------------------------------------------------
    int& r = x;
    // "int& r = x;" is a declaration statement
    // "&" token is a declerator

    //-------------------------------------------------
    ++*ptr;
    // "++*ptr" is an expression
    // "++" and "*" tokens are operators

    //-------------------------------------------------
  }
*/

/*
  int main()
  {
    int x = 10;
    double dval{};

    int& iref = dval; 		// syntax error
    // error: cannot bind non-const lvalue reference of type 'int&'
    // to a value of type 'double'

    double& dref = dval;	// VALID
  }
*/

/*
  int main()
  {
    int a[5]{ 1, 2, 3, 4, 5 };

    //--------------------------------------------------------
    int* ptr = a;     // pointer, points to the arrays first element.
    // int* ptr = &a[0];
    // Those 2 lines are equivalent.

    std::cout << typeid(ptr).name() << '\n';
    // output -> int* __ptr64 ->
    // (pointer to an integer[array's first element])

    //--------------------------------------------------------
    int(*p)[5] = &a;  // pointer, points to the whole array.

    std::cout << typeid(p).name() << '\n';
    // output -> int (* __ptr64)[5] ->
    // (pointer to a 5 element array)

    //--------------------------------------------------------
    int(&r)[5] = a;   // reference to 5 element array

    for (int i = 0; i < 5; ++i)
      printf("%d %d\n", r[i], a[i]);
    // output ->
    // 1 1
    // 2 2
    // 3 3
    // 4 4
    // 5 5

    //--------------------------------------------------------
    typedef int intarr5_1[5];
    // 1. write the type that you want to use.
    // -	int a[5];
    // 2. add a typedef in the beginning
    // -	typedef int a[5];
    // 3. change the object name with type name
    // -	typedef int intarr5[5];

    using intarr5_2 = int[5];

    intarr5_1& r1 = a;			// reference to 5 element array
    intarr5_1* p1 = &a;			// pointer, points to the whole array.

    intarr5_2& r2 	= a;		// reference to 5 element array
    intarr5_2* p2 	= &a;		// pointer, points to the whole array.

    //--------------------------------------------------------
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
  void int_swap_ptr(int* p1, int* p2)
  {
    int temp = *p1;
    *p1 = *p2;
    *p2 = temp;
  }

  void int_swap_ref(int& r1, int& r2)
  {
    int temp = r1;
    r1 = r2;
    r2 = temp;
  }

  int main()
  {
    int a = 111, b = 222;
    std::cout << "a = " << a << " b = " << b << '\n';
    // output -> a = 111 b = 222

    int_swap_ptr(&a, &b);
    std::cout << "a = " << a << " b = " << b << '\n';
    // output -> a = 222 b = 111

    int_swap_ref(a, b);
    std::cout << "a = " << a << " b = " << b << '\n';
    // output -> a = 111 b = 222
  }
*/

/*
  int g_ival = 50;

  int* foo()
  {
    return &g_ival;
  }

  int& bar()
  {
    return g_ival;
  }

  int main()
  {
    std::cout << "g_ival = " << g_ival << '\n';
    // output -> g_ival = 50

    ++*foo();
    std::cout << "g_ival = " << g_ival << '\n';
    // output -> g_ival = 51

    *foo() = 999;
    std::cout << "g_ival = " << g_ival << '\n';
    // output -> g_ival = 999

    int* p = foo();
    *p = -1;
    std::cout << "g_ival = " << g_ival << '\n';
    // output -> g_ival = -1

    bar() = 888;
    // "bar()" is an LValue expression
    std::cout << "g_ival = " << g_ival << '\n';
    // output -> g_ival = 888

    ++bar();
    std::cout << "g_ival = " << g_ival << '\n';
    // output -> g_ival = 889
  }
*/

/*
  int* ptr_func(int* ptr)
  {
    *ptr *= 2;
    return ptr;
  }

  int& ref_func(int& ref)
  {
    ref *= 2;
    return ref;
  }

  int main()
  {
    int x = 10;

    int* p = ptr_func(&x);
    std::cout << "x = " << x << '\n';	// output -> x = 20

    ++*p;
    std::cout << "x = " << x << '\n';	// output -> x = 21

    int y = 20;

    int& r = ref_func(y);
    std::cout << "y = " << y << '\n';	// output -> y = 40

    ++r;
    std::cout << "y = " << y << '\n';	// output -> y = 41
  }
*/

/*
  int main()
  {
    int x = 10;
    int& r = x; 	// r binds to x

    //----------------------------------------------------
    int y = r; 		// y will be r(x) but not bind to x
    std::cout << "y = " << y << '\n'; // output -> y = 10

    y = 99;
    std::cout << "x = " << x << '\n'; // output -> x = 10
    std::cout << "y = " << y << '\n'; // output -> y = 99

    //----------------------------------------------------
    int& z = r; //  r = z ===> z = x
    std::cout << "z = " << z << '\n'; // output -> z = 10

    z = 99;
    std::cout << "x = " << x << '\n'; // output -> x = 99

    //----------------------------------------------------
  }
*/

/*
  using T = int;

  void mutator_func(T&);          // SET function
  void accessor_func(const T&);   // GET function

  int main()
  {
    int x = 10;
    const int& r = x;
    // const reference -> reading purpose

    ++r;    // syntax error
    // error: increment of read-only reference 'r'

    r = 12; // syntax error
    // error: assignment of read-only reference 'r'
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
    int* p = &x;    // syntax error
    // no implicit conversion from const T* to T*
    // error: invalid conversion from 'const int*' to 'int*'

    int& r = x;     // syntax error
    // error: binding reference of type 'int&' to 'const int'

    const int* cptr = &x;   // VALID
    const int& cref = x;    // VALID
  }
*/

/*
  int main()
  {
    int x = 10;

    const int* cptr = &x;   // VALID (contractual constness)
    // implicit conversion from int* to const int* is valid.

    const int& cref = x;    // VALID

    *cptr = 22;   // syntax error
    // error: assignment of read-only location '* cptr'

    cref = 44;    // syntax error
    // error: assignment of read-only reference 'cref'

    x = 23;   // VALID
  }
*/

/*
  int main()
  {
    const char (&r)[11] = "HelloWorld";

    for (int i = 0; i < 10; ++i)
    {
      std::cout << r[i] << ' ' << (int)r[i] << '\n';
    }
    // output ->
    // H 72
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
  ------------------------------------------------
                  pointer semantics
  ------------------------------------------------
  - can be default initialized
  - can hold different objects addresses
  - array object types can be pointers
  - null pointer is valid
  - pointer to pointer is valied


  ------------------------------------------------
                  reference semantics
  ------------------------------------------------
  - can not default initialized
  - can not rebind to another object
  - array object types can not be reference
  - null reference is not valid
  - reference to reference is not valid
*/

/*
  int main()
  {
    const int& cref = 10;   // VALID
    // compiler create a temporary object and
    // reference binds to that temp object.
  }

  // compiled with x86-64 gcc -O0 -std=c++11
  //	main:
  //	  push rbp
  //	  mov rbp, rsp
  //	  mov DWORD PTR [rbp-12], 10    // int temp_obj = 10;
  //	  lea rax, [rbp-12]             // rax = &temp_obj
  //	  mov QWORD PTR [rbp-8], rax    // int* ptr = rax(&temp_obj)
  //	  mov eax, 0
  //	  pop rbp
  //	  ret
*/

/*
  int main()
  {
    int x = 10;
    double& dr = x;   // syntax error
    // error: cannot bind non-const lvalue reference of type 'double&'
    // to a value of type 'int'
  }
*/

/*
  int main()
  {
    const double& cdref = x;  // VALID
    // compiler will create an int and double temp objects
    // it will implicitly cast int to double
    // const double& will bind to casted double temp object.
  }

  // compiled with x86-64 gcc -O0 -std=c++11
  // main:
  //	push rbp
  //	mov rbp, rsp
  //	mov DWORD PTR [rbp-4], 10           : int temp_i_obj = 10;
  //	pxor xmm0, xmm0                     : clean xmm0 register

  //	cvtsi2sd xmm0, DWORD PTR [rbp-4]    : xmm0 = (double)temp_i_obj
  //	movsd QWORD PTR [rbp-24], xmm0      : double temp_d_obj = xmm0
  //    - double temp_d_obj = (double)temp_i_obj;

  //	lea rax, [rbp-24]                   : rax = &temp_d_obj
  //	mov QWORD PTR [rbp-16], rax         : double* ptr = rax(&temp_d_obj)
  //	mov eax, 0
  //	pop rbp
  //	ret

  // CVTSI2SD — Convert Doubleword Integer to
  // Scalar Double Precision Floating-Point Value
  // F2 0F 2A /r ==> CVTSI2SD xmm1, r32/m32
*/