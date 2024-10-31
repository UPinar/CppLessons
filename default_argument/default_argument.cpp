#include <iostream>

/*
                    =====================
                    | default arguments |
                    =====================
*/

/*
  void func(int x, int y);  // formal parameters
  func(12, x + 5);          // arguments
*/

/*
  int printf(const char*, ...); (print format function)


  void func(int, int, ...); // variadic parameter

  // ... -> ellipsis token

  // variadic parameter needs to be the last parameter.
  // only 1 variadic parameter is valid.

  int main()
  {
    func(2);            // syntax error
    func(2, 2);         // legal
    func(2, 2, 2);      // legal
    func(2, 2, 2, 2);   // legal
  }
*/

/*
  - no runtime cost.
  - compile time tool.
*/

/*
  void func(int, int, int, int);    // function declaration
  // in function declarations,
  // we do not need to use names(identifiers) in parameters.

  void func(int x, int y, int z, int k){
    // function definition
  }
*/

/*
  int g{};

  void func(int a, int b = g, int c = 10);
  // default argument does not need to be
  // a constant expression (int b = g)
*/

/*
  void func(int a, int b = 10, int c);  // syntax error.
  // error: default argument missing for parameter 3 of
  // 'void func(int, int, int)'

  // if 2nd argument is default argument,
  // next arguments needs to be default arguments too.

  int main()
  {
    func(10, , 20); // syntax error
  }
*/

/*
  void func(int x, int y = x + 10); // syntax error
  // error: parameter 'x' may not appear in this context
  // using one of parameters name(identifier) in other parameter's
  // default argument is not valid.
*/

/*
  void func(int = 10, int = 20, int = 30);
  // function declaration

  void func(int x = 10, int y = 20, int z = 30){
    // function definition
  }
  // syntax error ->
  // error: default argument given for parameter 1 of
  // 'void func(int, int, int
  // error: default argument given for parameter 2 of
  // 'void func(int, int, int
  // error: default argument given for parameter 3 of
  // 'void func(int, int, int

  // When we declare default arguments in function declaration
  // we can not redeclare them in function definition.


  // general scenerio :
  //  default arguments will be in function declaration,
  //  not in function definition
*/

/*
  //  function.h
  //  -----------------
  void func(int = 10, int = 20, int = 30);

  //  function.cpp
  //  -----------------
  void func(int a, int b, int c)
  {
    std::cout << "a = " << a << ' ';
    std::cout << "b = " << b << ' ';
    std::cout << "c = " << c << '\n';
  }

  int main()
  {
    func(1, 2, 3);  // output -> a = 1 b = 2 c = 3
    func(1, 2);     // output -> a = 1 b = 2 c = 30
    func(1);        // output -> a = 1 b = 20 c = 30
    func();         // output -> a = 10 b = 20 c = 30
  }
*/

/*
  void func(int* p = nullptr);
  void func(const char* p_err = "error");
  void print(int x, std::ostream& os = std::cout);

  // pointers and reference parameters can have default arguments.
*/

/*
                        -----------------
                        | maximal munch |
                        -----------------
*/

/*
  int main()
  {
    int x = 20;
    int y = 30;

    int z = x+++y;
    // int z = x++ + y;
    // Those 2 lines are equivalent.

    std::cout << "x = " << x << '\n';   // output -> x = 21
    std::cout << "y = " << y << '\n';   // output -> y = 30
    std::cout << "z = " << z << '\n';   // output -> z = 50
  }
*/

/*
  sum>>++x (tokens)
  -----------------
  1. sum
  2. >>=
  3. ++
  4. x
*/

/*
  int main()
  {
    int n = 5;
    while (n --> 0){ // (n-- > 0)
      std::cout << n << ' ';
    }
    // output -> 4 3 2 1 0
  }
*/

/*
  void func(int, const char *= "hello");  // syntax error
  // because of maximal munch "*=" is an operator.

  void func(int, const char* = "hello");  // VALID
*/

/*
  //  function.h
  //  -----------------
  int foo(int, int, int);

  // foo() function will be used in client.cpp a lot of times.
  // It will always be called with the same 3rd argument.
  // function can be redeclared with a default argument.

  //  client.cpp
  //  -----------------
  #include "function.h"
  int foo(int, int, int = 0); // redeclaration
*/

/*
  //  function.h
  //  -----------------
  int func(int x, int y, int z = 10);

  //  client.cpp
  //  -----------------
  #include "function.h"
  int func(int x, int y = 20, int z); // VALID
  // in redeclaration default argument used for the 2nd parameter
  // but in func() functions redeclaration
  // we can not use default argument in 3rd parameter again


  int func(int x, int y, int z = 30); // syntax error
  // error: default argument given for parameter 3 of
  // 'int func(int, int, int '
*/

/*
  int x = 10;

  void func(int a = ++x)
  {
    std::cout << "a = " << a << '\n';
  }
  // every time func() has been called
  // ++x will be applied as a side effect.

  int main()
  {
    func(); // output -> a = 11
    func(); // output -> a = 12
    func(); // output -> a = 13

    // func() and func(++x) call's are equivalent.
  }
*/

/*
  // Question : Can we send same argument for the 2nd parameter
  // from client code? (default argument for 2nd parameter)

  //  someheader.h
  //  ------------
  void func(int x, int y, int z); // function declaration

  //  client.cpp
  //  ------------
  void func_wrapper(int x, int z, int y = 0)
  {
    func(x, y, z);
  }
  // writing a wrapper function with a default argument
  // that default argument will be sent to the 2nd parameter
  // of the func() function.
*/

/*
  // How to control if an argument is sent to a function or not?
  void process_date(int mday = -1, int month = -1, int year = -1)
  {
    if (year == -1){
      // controlling the 3rd argument has been sent or not.
    }
  }
*/

/*
  #include <ctime> // std::time_t, std::time, std::localtime

  void process_date(int mday = -1, int month = -1, int year = -1)
  {
    if (year == -1)
    {
      std::time_t timer{};
      std::time(&timer);
      auto tp = std::localtime(&timer);
      year = tp->tm_year + 1900;

      if (month == -1)
      {
        month = tp->tm_mon + 1;

        if (mday == -1)
          mday = tp->tm_mday;
      }
    }
    std::cout << mday << '-' << month << '-' << year << '\n';
  }

  int main()
  {
    process_date(12, 5, 1993); // output -> 12-5-1993
    process_date(12, 5);       // output -> 12-5-2023
    process_date(12);          // output -> 12-4-2023
    process_date();            // output -> 28-4-2023
  }
*/
