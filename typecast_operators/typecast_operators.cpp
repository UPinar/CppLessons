#include <iostream>

/*
                    ======================
                    | typecast operators |
                    ======================
*/

/*
  1. (target type) Cstyle cast
  2. static_cast
  3. const_cast
  4. reinterpret_cast
  5. dynamic_cast
*/

/*
  int main()
  {
    int i1 = 24, i2 = 11;
    double dval{};

    (double)i1 / i2;    // we want to use the double
    (long long)i1 *i2;  // we want to use values greater than MAX_INT
    char c = (char)i1;  // we want to cast to char
    
    // implicit conversion can also be happen but
    // explicit cast explains the purpose

    int x = 453223;
    const int *cptr = &x;

    int *p_1 = cptr;  // syntax error
    // error: invalid conversion from 'const int*' to 'int*' 

    int* p_2 = (int *)cptr; // we want to change the value of x
    *p_2 = 12;  // VALID
  }
*/

/*
  #include <cstring>    // std::strchr

  // C <string.h> library function
  char* strchr_implementation(const char* p, int c)
  {
    while (*p) {
      if (*p == c)
        return (char*) p;
      else
        ++p;
    }

    if (c == '\0')
      return (char*) p;

    return NULL;
  }
  // checks the char(ASCII int) in cstring
*/

/*
  int main()
  {
    const int x = 10;
    const int* cptr = &x;

    int* p = (int*)cptr;
    // DO NOT WRITE A CODE LIKE THIS.
    // x is const int, promise that its value will not change
    // but we are casting const int* to int*
    // and changing the value of x

    *p = 12;
  }
*/

/*
  int main()
  {
    double dval{ 82372.238823 };

    unsigned char* p = (unsigned char*)&dval;

    for (size_t i = 0; i < sizeof dval; ++i)
    {
      printf("%u\n", p[i]);
    }
    // output ->
    //  233
    //  16
    //  56
    //  210
    //  67
    //  28
    //  244
    //  64
  }

  // https://gregstoll.com/~gregstoll/floattohex/
  // binary representation of 82372.238823
  // 1010000'0111000'1000011'11010010'00111000'00010000'11101001
  // decimal representation of each byte : 64'244'28'67'210'56'16'233
*/


/*
  int main()
  {
    double dval{ 82373.2394 };
    int* p = (int*)&dval;

    *p;	// undefined behaviour
  }
*/

/*
  int main()
  {
    int x = 10;
    unsigned int* p = (unsigned int*)&x; // not undefined behaviour 
    [same types signed & unsigned]
  }
*/

/*
  struct Mystruct {
    int a;
    double b, c;
  };

  int main()
  {
    Mystruct ms = { 32, 2.4, 5.4 };

    int* iptr = (int*)&ms;  // not undefined behaviour
    // &ms is equal to &ms.a
    // struct's address and the address of the first member variable
    // of that structs are same
  }
*/

/*
  static cast
    -> conversion between integral and floating point types
    -> conversion between integral types
    int - double
    double - int
    int - long
    -> conversion between enumaration types and integral types
    -> conversion between pointer to integral types
    -> void* to other pointer types
  const cast
    -> const T* -> T*
    -> sometimes T* -> const T*
  reinterpret cast
  dynamic cast
    -> inheritance(RTTI) from Base object to Der object (downcasting) 
        [run time]
*/

/*
  int main()
  {
    int i1 = 19, i2{ 3 };

    double dval{ 234823.234 };
    i1 = static_cast<int>(dval);

    double dval_2 = static_cast<double>(i1) / i2;
    long long lval = static_cast<long long>(i1)* i1;
  }
*/

/*
  int main()
  {
    int x = 20;
    const int* cp = &x;

    char* p = reinterpret_cast<char*>(cp);  // syntax error
    // error: 'reinterpret_cast' from type 'const int*' 
    // to type 'char*' casts away qualifiers

    const char* p = reinterpret_cast<const char*>(cp);

    auto p = const_cast<int*>(cp);

    auto p1 = reinterpret_cast<char*>(const_cast<int*>(cp));
    auto p2 = const_cast<char*>(reinterpret_cast<const char*>(cp));
    // Those 2 lines are equivalent.

    void* vptr = &x;
    int* iptr = static_cast<int*>(vptr);
  }
*/