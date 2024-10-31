#include <iostream>

/*
                      =====================
                      | constexpr keyword |
                      =====================
*/

/*
  int foo(){}

  int main()
  {
    const int x = 10;
    // "x" is constant expression,
    // its value is known at compile time.

    const int y = foo();
    // "y" is not constant expression,
    // after foo() function executed,
    // its value will be known.

    int a[x] = { 0 };	// VALID
    int b[y] = { 0 };	// syntax error
    // y is not constant expression.
    // can not be used as array size.

    const int z = x + 5;
    // z is constant expression because x is constant expression.
    // its value is known at compile time.
  }
*/

/*
  int main()
  {
    int x = 5;

    const int y = x + 5;
    // y is not constexpr because x is not constant

    int a[y] = { 0 }; // syntax error
    // warning: ISO C++ forbids variable length array 'a'
  }
*/

/*
  int main()
  {
    // To check if an expression is constant expression,
    // we can use constexpr keyword.
    // Declare a constexpr variable and initialize with
    // the expression you want to check.

    const int x = 5;
    int y = 12;

    constexpr int z = x * y - 3; // syntax error
    // error: the value of 'y' is not usable in a constant expression
    // "z" is not a constant expression because "y" is not constant.
  }
*/

/*
  - constexpr variable needs to initialize with constant expression.
  - constexpr is not a type qualifier.
  - when a variable declared with constexpr keyword,
    its type will be const.
*/

/*
  int main()
  {
    constexpr int x = 30;

    x = 12; // syntax error.
    // error: assignment of read-only variable 'x'
    // "x" expression's data type is const int.
  }
*/

/*
  int main()
  {
    constexpr int a[] = { 3, 5, 6, 1 };
    // constexpr array is valid, can be used as a lookup tables.

    constexpr int x = a[2] + a[3] - 5;  // VALID
  }
*/

/*
  int g_x = 10;

  int main()
  {
    // constexpr nesnenin kendisinin const'lugunu ifade ediyor.
    constexpr const int* p1 = &g_x;
    const int* p2 = &g_x;
    // Those 2 lines are NOT equivalent.

    // constexpr makes "p1"s declaration type const
    // without constexpr keyword "p1"'s declaration type is
    //    -> const int*         (pointer to const int)
    // with constexpr keyword "p1"'s declaration type will become
    //    -> const int* const   (const pointer to const int)

    constexpr const int* p3 = &g_x;
    const int* const p4 = &g_x;
    // Those 2 lines are equivalent.
  }
*/

/*
                    -----------------------
                    | constexpr functions |
                    -----------------------
*/

/*
  - If all arguments are sent as constant expressions
    to a constexpr function,
    return value of the function will be calculated in compile time.

  - Else return value will be calculated in runtime.
*/

/*
  // constexpr function
  constexpr int factorial(int x)
  {
    return x < 2 ? 1 : x * factorial(x - 1);
  }

  int main()
  {
    constexpr auto result = factorial(10);
    // "10" is a constant expression.
    // so result variable will be calculated in compile time.

    int a[factorial(5)]{};   // VALID
    // "5" is a constant expression.
    // so array size(return value of the constexpr function)
    // will be calculated in compile time.

    const int x = 7;
    const int y = 5;
    constexpr auto val = factorial(x + y - 3);  // VALID
    // "x + y - 3" is a constant expression.
    // so val variable will be calculated in compile time.
  }
*/

/*
  [val * sqrt(sin(x) + cos(y))]

  THIS EXPRESSION WILL BE CONSTANT EXPRESSION IF ALL ARE TRUE

  1. if "x" and "y" are constant expressions
  2. if sin() and cos() are constexpr functions
  3. if sqrt() is constexpr function
  4. if val is a constant expression
*/

/*
  constexpr bool isprime(int x)
  {
    if (x < 2)
      return false;
    if (x % 2 == 0)
      return x == 2;
    if (x % 3 == 0)
      return x == 3;
    if (x % 5 == 0)
      return x == 5;

    for (int i = 7; i * i <= x; i += 2)
      if (x % i == 0)
        return false;

    return true;
  }

  int main()
  {
    constexpr auto val_1 = isprime(19001);
    // a -> true

    constexpr auto val_2 = isprime(19002);
    // b -> false

    constexpr int x = 324273;
    const int y = 123;
    const int z = 2130125;

    constexpr auto val_3 = isprime(x * y - z);
    // c -> false

    // val_1, val_2 and val_3 will be calculated in compile time.
  }
*/

/*
  - constexpr functions are implicitly inline.
  - constexpr functions are defined in header(.h) files.
*/