#include <iostream>

/*
                    ========================
                    | Function Overloading |
                    ========================
*/

/*
  function OVERLOADING  -> compile time  -> static(early) binding
  function OVERRIDING   -> run time      -> dynamic(late) binding
*/

/*
  for function overloading : 
    1. functions names(identifiers) should be same.
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
    - gloabal variables
    - global functions
    - global type definitions
  -> class scope
  -> block scope
    - local variables
    - variables inside functions
  -> function prototype scope
    - function parameters
  -> function scope
    - labels
*/

/*
  void foo(int);        //namespace scope

  int main()
  {
    void foo(double);   //block scope
  }
  // function identifiers are same      [+]
  // functiom signatures are different  [+]
  // function scopes are same           [-]
  // NO function overloading
*/

/*
  class Myclass {
    void foo(int);    // class scope
  };

  int main()
  {
    void foo(double); // block scope
  }

  // function identifiers are same      [+]
  // functiom signatures are different  [+]
  // function scopes are same           [-]
  // NO function overloading
*/

/*
  namespace first {
    void foo(int);    // namespace scope
  }

  namespace second {
    void foo(double); // namespace scope
  }
  // function identifiers are same      [+]
  // functiom signatures are different  [+]
  // function scopes are same           [-]
  // NO function overloading (different namespace scopes)
*/

/*
                      ----------------------
                      | function signature |
                      ----------------------
*/

/*
  // for function signature only function parameters are important.

  int foo(int, int);
  double bar(int, int);

  // foo and bar functions have same function signature.
  // foo and bar functions have different return types.

*/

/*
  int func(int);
  double func(int); // syntax error
  //  error: ambiguating new declaration of 'double func(int)'

  int foo(int);
  int foo(int);     // VALID
  // function redeclaration (not overloading)
*/

/*
  int func(int);
  double func(int, int);
  double func(double, int);
  // function identifiers are same      [+]
  // functiom signatures are different  [+]
  // function scopes are same           [+]
  // We have 3 overloads(function overloads)
*/

/*
  - If a parameter is not a reference or a pointer type
    declaring two functions, one have a const parameter and 
    the other one have a non-const parameter
    is not function overloading.

  int func(int);
  int func(const int);
  
  // function identifiers are same      [+]
  // functiom signatures are different  [-]
  // function scopes are same           [+]
  // NO overloading, function redecelaration
*/

/*
  void func(int*);        // pointer to int
  void func(int* const);  // const pointer to int (top-level const)
  // NO overloading, function redecelaration

  void foo(int*);         // pointer to int
  void foo(const int*);   // pointer to const int (low-level const)
  // Because of parameters are pointers
  // We have 2 overloads(const overloads)
*/

/*
  void foo(int&);         // reference to int
  void foo(const int&);   // reference to const int (low-level const)
  // Because of parameters are references
  // We have 2 overloads(const overloads)
*/  

/*
  void func(char);		      // implementation-defined
  void func(signed char);
  void func(unsigned char);
  // char, signed char and unsigned char are distinct types

  // function identifiers are same      [+]
  // functiom signatures are different  [+]
  // function scopes are same           [+]
  // We have 3 overloads(function overloads)
*/
  

/*
  typedef unsigned char BYTE; // type alias

  void func(unsigned char);
  void func(BYTE);
  // function identifiers are same      [+]
  // functiom signatures are different  [-]
  // function scopes are same           [+]
  // NO overloading, function redecelaration
*/

/*
  #include <cstdint>

  // int32_t is a type alias (optional sythax)
  void func(int x);
  void func(int32_t x);

  // depending on the system, int and int32_t can be same type
  // if they are same type, we have function redeclaration
  // if they are different types, we have function overloading
*/

/*
  // In C and C++ languages, parameter variables 
  // can not be an array type.
  // When a parameter variable declared as an array,
  // compiler will decay that array to a poiner. (array decay)

  void func(int* p);
  void func(int p[]);
  void func(int p[10]);
  // 1 overload here, all are function redeclarations.
*/

/*
  void func(int p[10]);   // void func(int* p);

  int main()
  {
    int x{ 98 };
    func(&x);   // VALID

    // func functions parameter variable's type is int* (array decay)

    // even if function's signature is expressing that 
    // it wants an array as a parameter
    // it will accept an address of an integer.
    // because of array decay, int p[10] will decay to int* p
  }
*/

/*
  // Functions parameter variable can not be a function type
  // When a parameter variable declared as a function type
  // compiler will decay that function 
  // to a function pointer. (function decay)

  // int(int)    -> function type
  // int(*)(int) -> function pointer type


  void foo(int(int));     // func(int(*)(int));
  void foo(int(*)(int));
  // NO overloading, function redecelaration
*/

/*
  // 1 overload in here. They are all redeclaration
  using Function = int(int);  // function type
  using FPTR = int(*)(int);   // function pointer type

  void foo(Function);
  void foo(int(int));
  void foo(Function*);
  void foo(int(*)(int));
  void foo(FPTR);
  // 1 overload here, all are function redeclarations.
*/

/*
  void func(int(*)[10]);
  void func(int[][10]);
  // NO overloading, function redecelaration
*/

/*
  void func(int(*)[10]);
  // func can be called with an address of int[10]

  int main()
  {
    // -----------------------------------------------------

    int a[10]{};
    func(&a);     // VALID
    func(a);      // syntax error (a ==> int*)
    // error: cannot convert 'int*' to 'int (*)[10]'
    func(&a[0]);  // syntax error (&a[0] ==> int*)
    // error: cannot convert 'int*' to 'int (*)[10]'

    // -----------------------------------------------------

    int x = 12;
    int* p = &x;
    func(&x);		// syntax error (&x ==> int*)
    // error: cannot convert 'int*' to 'int (*)[10]'
    func(p);		// syntax error (p ==> int*)
    // error: cannot convert 'int*' to 'int (*)[10]'
    func(&p);		// syntax error (&p ==> int**)
    // error: cannot convert 'int**' to 'int (*)[10]'

    // -----------------------------------------------------

    int b[16]{};
    func(&b);		// syntax error (&b ==> int(*)[16])
    // error: cannot convert 'int (*)[16]' to 'int (*)[10]'

    // -----------------------------------------------------
  }
*/

/*
  void func(int(&)[10]);
  // func can be called int[10]

  int main()
  {
    int a[10]{};
    func(a);  // VALID
  }
*/

/*
  void func(int(*)[5]);
  void func(int(*)[10]);
  void func(int(*)[15]);
  // function identifiers are same      [+]
  // functiom signatures are different  [+]
  // function scopes are same           [+]
  // We have 3 overloads(function overloads)


  void foo(int(&r)[5]);
  void foo(int(&r)[10]);
  void foo(int(&r)[15]);
  // function identifiers are same      [+]
  // functiom signatures are different  [+]
  // function scopes are same           [+]
  // We have 3 overloads(function overloads)
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

  // Those 3 functions are equivalent.
*/

/*
  int g_arr[10]{};

  int(*foo())[10]
  {
    return &g_arr;
  }

  using inta10 = int[10];
  inta10* bar()
  {
    return &g_arr;
  }

  using inta10_ptr = int(*)[10];
  inta10_ptr baz()
  {
    return &g_arr;
  }

  // Those 3 functions are equivalent.
*/

/*
  void func(int, int = 0);  // func(int, int) [2 parameters]
  void func(int);           // func(int)
  // function identifiers are same      [+]
  // functiom signatures are different  [+]
  // function scopes are same           [+]
  // We have 2 overloads(function overloads)
*/

/*
  void func(int, int);
  void func(int, int = 0);
  // function identifiers are same      [+]
  // functiom signatures are different  [-]
  // function scopes are same           [+]
  // NO overloading, function redecelaration
*/

/*
  void func(int, int, int);
  void func(int, int, int = 0);
  void func(int, int = 0, int);
  // function identifiers are same      [+]
  // functiom signatures are different  [-]
  // function scopes are same           [+]
  // NO overloading, function redecelaration(cumuative decleration)
*/

/*
  void foo(int&);
  void foo(int*);
  void foo(int);
  // function identifiers are same      [+]
  // functiom signatures are different  [+]
  // function scopes are same           [+]
  // We have 3 overloads(function overloads)
*/

/*
  class Myclass {};

  void func(const Myclass&);
  void func(Myclass&);
  void func(Myclass&&);
  // function identifiers are same      [+]
  // functiom signatures are different  [+]
  // function scopes are same           [+]
  // We have 3 overloads(function overloads)
*/

/*
  int x{};

  void func(int);
  void func(decltype(x));   // void func(int);
  // "x" is identifier, decltype(x)'s data type is int
  // function identifiers are same      [+]
  // functiom signatures are different  [-]
  // function scopes are same           [+]
  // NO overloading, function redecelaration

  void foo(int);
  void foo(decltype((x)));  // void foo(int&);
  // "(x)" is an LValue expression, decltype((x))'s data type is int&
  // function identifiers are same      [+]
  // functiom signatures are different  [+]
  // function scopes are same           [+]
  // We have 2 overloads(function overloads)
*/

/*
                  --------------------------------
                  | Function Overload Resolution |
                  --------------------------------
*/

/*
  1. find all overloads and make them candidate functions.
  2. check their signatures and 
    find which ones can be called (viable functions)
  3. if no viable function -> NO MATCH ERROR.
  4. if more than 1 viable functions, 
    find the best match and call it.
  5. if no best match -> AMBIGUITY ERROR
*/

/*
  Question: Implicit conversion is possible ?

  scoped enum     -->   int         [NO]
  unscoped enum   -->   int         [YES]
  double          -->   char        [YES]
  int*            -->   void*       [YES]
  void*           -->   int*        [NO]
  int*            -->   bool        [YES]
  bool            -->   int*        [NO]
  nullptr_t       -->   int*        [YES]
  int*            -->   nullptr_t   [NO]
  nullptr_t       -->   bool        [NO]	[YES - in logic context]
*/

/*
  void func(unsigned int);
  void func(char);

  int main()
  {
    func(12); // syntax error
    // error: call of overloaded 'func(int)' is ambiguous
  }
*/

/*
  Qualities of conversion levels
  -----------------------------
  Level 0 -> variadic conversion        [WORST]
  Level 1 -> user-defined conversion
  Level 2 -> standart conversion        [BEST]
*/

/*
  void func(int, ...);
  void func(int, int, ...);
  void func(...); // is not possible in C but possible in C++
*/

/*
  // variadic conversion - LEVEL 0  (WORST quality conversion)

  void func(...) { std::cout << "func(...)\n"; }
  void func(double) { std::cout << "func(double)\n"; }

  int main()
  {
    func(123);  // output -> func(double)
    // [standart conversion > variadic conversion]
  }
*/

/*
  // user-defined conversion - LEVEL 1

  class Myclass {
  public:
    Myclass() = default;
    Myclass(int x) : m_x{ x } {}

    operator int() const { return m_x; }
  private: 
    int m_x = 10;
  };

  int main()
  {
    Myclass x; 
    x = 22;       // user-defined conversion (int -> Myclass)

    Myclass y;
    int ival{};
    ival = y;     // user-defined conversion (Myclass -> int)
  }
*/

/*
  // standart conversion - LEVEL 2

  void func(unsigned int);
  void func(float);
  void func(double);

  int main()
  {
    func(10 > 5); // syntax error
    // error: call of overloaded 'func(bool)' is ambiguous

    // bool type can implicitly convert to 
    // unsigned int, float and double

    // 3 overloads are both standart conversion
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
    - standart conversion other than 
      exact match and promotion are conversions.
    - if there are more than 1 overloads, 
      there will be an AMBIGUITY ERROR.
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

    func(a);      // exact match (array decay)
    func(&a[0]);  // exact match (array decay)
    // Those 2 lines are equivalent.
  }
*/

/*
  void func(const int*);  // (const int*) pointer to const int

  int main()
  {
    const int x = 10;
    func(&x);   // exact match

    int y = 12;
    func(&y);   // exact match (const conversion)
    // conversion from int* to const int*
  }
*/

/*
  void func(int(*)(int));
  // func's parameter variable is a function pointer
  // func can be called with an address of a int(int) function 

  int foo(int);

  int main()
  {
    func(&foo);   // exact match
    func(foo);    // exact match (function to pointer conversion)
    // conversion from int(int) -> int(*)(int)
  }
*/

/*
  void func(int);
  void func(double);
  void func(long);

  int main()
  {
    func(12u);  // syntax error (all overloads are conversion)
    //  error: call of overloaded 'func(unsigned int)' is ambiguous
  }
*/

/*
  void func(long double);
  void func(char);

  int main()
  {
    func(3.4);  // syntax error (all overloads are conversion)
    //  error: call of overloaded 'func(double)' is ambiguous
  }
*/

/*
  void func(double); // exact match
  void func(float);  // conversion

  int main()
  {
    func(3.5);  // exact match
    // func(double) will be called.
  }
*/

/*
  void func(int);           // integral promotion
  void func(double);        // conversion
  void func(long double);   // conversion


  int main()
  {
    func('A');
    // conversion from char -> int (integral promotion)
    // func(int) will be called.
  }
*/

/*
  void func(int);           // integral promotion
  void func(double);	      // conversion
  void func(long double);   // conversion

  int main()
  {
    bool flag{};
    func(flag);
    // conversion from bool -> int (integral promotion)
    // func(int) will be called.
  }
*/

/*
  void func(unsigned long);   // conversion
  void func(long);            // conversion

  int main()
  {
    int ival{ 32 };
    func(ival); // syntax error 
    // error: call of overloaded 'func(int&)' is ambiguous
  }
*/

/*
  void func(int*);
  void func(const int*);
  // const overloads

  int main()
  {
    const int x = 12;
    func(&x);
    // void func(int*);       -> NOT VIABLE
    // void func(const int*); -> VIABLE
    // func(const int*) will be called.

    int y = 10;
    func(&y);
    // void func(int*);       -> VIABLE (exact match) --> CHOOSEN
    // void func(const int*); -> VIABLE (exact match)
    // func(int*) will be called.
  }
*/

/*
  void func(const int&){
    std::cout << "func (const int&)\n";
  }

  void func(int&){
    std::cout << "func (int&)\n";
  }
  // const overloads

  int main()
  {
    const int x = 12;
    func(x);
    // void func(const int&); -> VIABLE
    // void func(int&);       -> NOT VIABLE
    // func(const int&) will be called.

    int y = 10;
    func(y);
    // void func(const int&); -> VIABLE (exact match)
    // void func(int&);       -> VIABLE (exact match) --> CHOOSEN
    // func(int&) will be called.
  }
*/

/*
  void func(int x, int y = 0);
  void func(int x);

  int main()
  {
    func(24); // syntax error
    // void func(int x, int y = 0); -> VIABLE (exact match)
    // void func(int x);            -> VIABLE (exact match)
    // error: call of overloaded 'func(int)' is ambiguous

    func(1, 5);
    // void func(int x, int y = 0); -> VIABLE (exact match)
    // void func(int x);            -> NOT VIABLE
    // func(int x, int y = 0) will be called.
  }
*/

/*
  void func(int);   // call by value
  void func(int&);  // call by reference

  int main()
  {
    int x{};
    func(x); // syntax error 
    // void func(int);   -> VIABLE (exact match)
    // void func(int&);  -> VIABLE (exact match)
    // error: call of overloaded 'func(int&)' is ambiguous
  }
*/

/*
  void func(int);   // call by value
  void func(int&);  // call by reference

  int main()
  {
    func(10); 
    // "10" is PR value expression, 
    // L value reference can not bind with PR value expression

    // void func(int);   -> VIABLE (exact match)
    // void func(int&);  -> NOT VIABLE
    // func(int) will be called.
  }
*/

/*
  void func(int);
  void func(const int&); 

  int main()
  {
    func(4); // syntax error 
    // "4" is PR value expression, 
    // const L value reference can bind with PR value expression

    // void func(int);          -> VIABLE (exact match)
    // void func(const int&);   -> VIABLE (exact match)
    // error: call of overloaded 'func(int)' is ambiguous
  }
*/

/*
  void func(int*);
  void func(int);

  int main()
  {
    func(0);
    // void func(int*);         -> VIABLE (null pointer conversion)
    // void func(int);          -> VIABLE (exact match)
    // func(int) will be called.

    func(nullptr);
    // void func(int*);         -> VIABLE 
    // void func(int);          -> NOT VIABLE
    // conversion from nullptr_t to int in not VALID
    // func(int*) will be called.
  }
*/

/*
  void func(int*);
  void func(double);

  int main()
  {
    func(0); // syntax error 
    // void func(int*);    	  -> VIABLE (null pointer conversion)
    // void func(double);	    -> VIABLE (conversion)
    // error: call of overloaded 'func(int)' is ambiguous
  }
*/

/*
  void func(int*);
  void func(double*);

  int main()
  {
    func(nullptr); // syntax error
    // void func(int*);    	-> VIABLE (conversion)
    // void func(double*);	-> VIABLE (conversion)
    //  error: call of overloaded 'func(std::nullptr_t)' is ambiguous
  }
*/

/*
  void func(std::nullptr_t);
  void func(int*);
  void func(double*);

  int main()
  {
    func(nullptr);
    // void func(std::nullptr_t); -> VIABLE (exact match)
    // void func(int*);           -> VIABLE (conversion)
    // void func(double*);        -> VIABLE (conversion)
    // func(std::nullptr_t) will be called.
  }
*/

/*
  void func(void*)
  {
    std::cout << "func(void*) called\n";
  }

  void func(bool)
  {
    std::cout << "func(bool) called\n";
  }

  int main()
  {
    int x = 555;
    func(&x); // output -> func(void*) called
    // void func(void*);  -> VIABLE (conversion) -----> CHOOSEN
    // void func(bool);   -> VIABLE (conversion)

    // This is a special case where void* is preferred over bool.
  }
*/

/*
  #include <utility>  // std::move

  class Myclass {};

  void func(Myclass&);
  void func(Myclass&&);

  int main()
  {
    Myclass m;

    func(m);
    // "m" is an LValue expression 
    // L value reference can bind with L value expression
    // R value reference can not bind with L value expression
    // func(Myclass&); will be called

    func(Myclass{});
    // "Myclass{}" (temporary object - geçici nesne) 
    //  is PR value expression
    // L value reference can not bind with PR value expression
    // R value reference can bind with PR value expression
    // func(Myclass&&); will be called

    func(std::move(m));
    // std::move(m) is XValue expression
    // L value reference can not bind with XValue expression
    // R value reference can bind with XValue expression
    // func(Myclass&&); will be called
  }
*/

/*
  class Myclass {};

  void func(const Myclass&)
  {
    std::cout << "const L value reference parameter\n";
  }
  void func(Myclass&&)
  {
    std::cout << "R value reference parameter\n";
  }
  // Those are move overloads

  int main()
  {
    Myclass m;

    func(m);
    // "m" is an LValue expression.
    // const L value reference can bind with L value expression.
    // R value reference can not bind with L value expression.
    // func(const Myclass&); will be called.

    func(Myclass{});
    // "Myclass{}" is a PRValue expression.
    // const L value reference can bind with PR value expression.
    // R value reference can bind with PR value expression.
    // both overloads are viable.
    // func(Myclass&&); will be called.
  }
*/

/*
  class Myclass {};

  void func(Myclass&)
  {
    std::cout << "(1) L VALUE REF PARAM\n";
  }
  void func(const Myclass&)
  {
    std::cout << "(2) CONST L VALUE REF PARAM\n";
  }
  void func(Myclass&&)
  {
    std::cout << "(3) R VALUE REF PARAM\n";
  }

  int main()
  {
    Myclass m;
    func(m);
    // "m" is an LValue expression.
    // L value reference can bind with L value expression.
    // const L value reference can bind with L value expression.
    // R value reference can not bind with L value expression.
    // (1) and (2) overloads are viable.
    // func(Myclass&); will be called.

    const Myclass cm;
    func(cm);
    // "cm" is an LValue expression.
    // L value reference can not bind with L value expression(const).
    // const L value reference can bind with L value expression(const).
    // R value reference can not bind with L value expression(const).
    // (2) overload is viable.
    // func(const Myclass&); will be called.

    func(Myclass{});
    // "Myclass{}" is a PRValue expression.
    // L value reference can not bind with PR value expression.
    // const L value reference can bind with PR value expression.
    // R value reference can bind with PR value expression.
    // (2) and (3) overloads are viable.
    // func(Myclass&&); will be called.
  }
*/

/*
  void func(float, double, int);        // 1
  void func(int, long, unsigned);       // 2
  void func(double, unsigned, float);   // 3

  // Overload's 1 parameter needs to be better than other overloads, 
  // but other parameters can not be worse.

  // If first parameter is best in 1st overload 
  // and second parameter is best in 2nd or 3rd
  // there will be an AMBIGUITY ERROR.

  int main()
  {
    func(3.4f, 12, true);
    // func() paramaters		[float, int, bool]
    // 1st func() overload  ->    [exact match, conversion , promotion ]
    // 2nd func() overload  ->    [conversion , conversion , conversion]
    // 3rd func() overload  ->    [conversion , conversion , conversion]

    // 1st - func(float, double, int) overload will be called.

    func(3.4f, 12, 5.3f); // syntax error
    // func() paramaters    [float, int, float]
    // 1st func() overload  ->    [exact match, conversion , promotion ]
    // 2nd func() overload  ->    [conversion , conversion , conversion]
    // 3rd func() overload  ->    [conversion , conversion , exact match]

    // In 1st parameter 1st overload is the best
    // In 3rd parameter 3rd func overload is the best
    // error: call of overloaded 'func(float, int, float)' is ambiguous

    func(true, 12, 4.5);
    // func() paramaters    [bool, int, double]
    // 1st func() overload  ->    [conversion, conversion , conversion]
    // 2nd func() overload  ->    [promotion , conversion , conversion]
    // 3rd func() overload  ->    [conversion, conversion , conversion]

    // 2nd - func(int, long, unsigned) overload will be called.

    func(12, 13, 3.5);
    // func() paramaters    [int, int, double]
    // 1st func() overload  ->    [conversion , conversion , conversion]
    // 2nd func() overload  ->    [exact match, conversion , conversion]
    // 3rd func() overload  ->    [conversion , conversion , conversion]

    // 2nd - func(int, long, unsigned) overload will be called.

    func(12, 6u, 3.5);  // syntax error
    // func() paramaters    [int, unsigned int, double]
    // 1st func() overload  ->    [conversion , conversion , conversion]
    // 2nd func() overload  ->    [exact match, conversion , conversion]
    // 3rd func() overload  ->    [conversion , exact match, conversion]

    // In 1st parameter 2nd overload is the best
    // In 2nd parameter 3rd overload is the best
    // error: call of overloaded 'func(int, unsigned int, double)' 
    // is ambiguous

    func(12, 15, true); // syntax error
    // func() paramaters    [int, int, bool]
    // 1st func() overload  ->    [conversion , conversion , promotion ]
    // 2nd func() overload  ->    [exact match, conversion , conversion]
    // 3rd func() overload  ->    [conversion , conversion , conversion]

    // In 1st parameter 2nd overload is the best
    // In 3rd parameter 1st overload is the best
    // error: call of overloaded 'func(int, int, bool)' is ambiguous
  }
*/

/*
  void func(unsigned int);
  void func(long);

  int main()
  {
    bool flag{};
    func(static_cast<unsigned>(flag));
    // func(unsigned int) will be called.

    func(static_cast<long>(flag));
    // func(long) will be called.
  }
*/

/*
                  -----------------------------
                  | name decoration(mangling) |
                  -----------------------------
*/

/*
  #include "header/different.h"
  #include "header/same.h"

  int main()
  {
    int x{};

    //x = func_different(12, 34); // linker error

    // In C, because of there is no function overloading.
    // C compiler will only use the function's name 
    // in the reference that it wrote for linker.
    // (NO name mangling)

    // In C++, there is function overloading mechanism
    // C++ Compiler is using function's signatures in the reference
    // that it wrote for linker. (name decoration-mangling)

    x = func_same(12, 13);
    std::cout << "x = " << x << '\n';
  }

  // <----------------------- SCENARIO ------------------------->
  // 1. Compile different.c and same.c with C compiler
  //  - gcc -c source/different.c -o different.o
  //  - gcc -c source/same.c -o same.o
  // 2. Link different.o and same.o and client code with C++ compiler
  //  - g++ -o prog client.cpp different.o same.o -std=c++20

  // In this scenario, C++ compiler will see extern "C" block
  // inside "same.h" header file, so it will not do name mangling
  // and because of "same.c" were compiled with C compiler (same.o)
  // there won't be any link error.
  // (linking same.h function declarations with same.o object code)

  // But C++ compiler will NOT see extern "C" block inside
  // "different.h" header file, so it will do name mangling
  // and because of "different.c" were compiled with C compiler
  // (different.o) there will be a link error.

  // C++ compiler's generated reference for "func_different" 
  // function which is name decorated(mangled) with function's signature
  // will be different than C compiler's generated reference for
  // "func_different" function inside the different.o 
  // So "func_different" function's reference can not be linked with 
  // "different.o" object code.
*/