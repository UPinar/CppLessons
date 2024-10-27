#include <iostream>

/*
                  ------------------------
                  | range based for loop |
                  ------------------------
*/

/*
  class AClass {
  public:
    AClass();
    AClass(AClass&&);   // user declared move ctor
    void foo();
  };

  int main()
  {
    AClass arr[100];

    // ------------------------------------------------

    for (auto elem_a : arr)  // syntax error
      elem_a.foo();

    // error: use of deleted function 
    // 'constexpr AClass::AClass(const AClass&)'
    // aclass_arr elements will be copy constructed 

    // because of AClass's move ctor is user declared
    // compiler will delete copy members (implicitly declared deleted)

    // ------------------------------------------------

    AClass arr2[100]{};
    AClass a2 = arr2[0]; // syntax error
    // error: use of deleted function 
    // 'constexpr AClass::AClass(const AClass&)'

    // ------------------------------------------------
  }
*/

/*
                    -----------------------
                    | pointer to an array |
                    -----------------------
*/

/*
  #include <cstdio>  // std::putchar

  int g_arr[5] = { 1, 2, 3, 4, 5 };

  int(*foo_1())[5]
  {
    return &g_arr;
  }

  typedef int(*INTARR5_PTR)[5];     // typedef declaration
  using INTARR5_PTR2 = int(*)[5];   // using declaration

  INTARR5_PTR foo_2()
  {
    return &g_arr;
  }

  INTARR5_PTR2 foo_3()
  {
    return &g_arr;
  }

  auto foo_4()
  {
    return &g_arr;
  }

  // foo_1, foo_2, foo_3, foo_4 are equivalent.

  int main()
  {
    int* p1 = g_arr;  // g_arr will decay to pointer &g_arr[0]
    int(*p2)[5] = &g_arr; 

    // *p1 -> pointing to the first element of the array
    // *p2 -> pointing to the whole array

    auto f1 = foo_1();
    auto f2 = foo_2();
    auto f3 = foo_3();
    auto f4 = foo_4();

    for (size_t i = 0; i < 5; i++)
    {
      std::cout << (*f1)[i] << " ";
      std::cout << (*f2)[i] << " ";
      std::cout << (*f3)[i] << " ";
      std::cout << (*f4)[i] << " ";
      std::putchar('\n');
    }

    // output -> 
    //  1 1 1 1
    //  2 2 2 2
    //  3 3 3 3
    //  4 4 4 4
    //  5 5 5 5                    
  }
*/

/*
                    -------------------------------
                    | if with initializer (C++17) |
                    -------------------------------
*/

/*
  - solves scope leakage problem
*/

/*
  #include <vector>     // std::begin, std::end 
  #include <algorithm>  // std::find

  int main()
  {
    using namespace std;

    vector<int> ivec{ 1, 2, 3, 4, 78, 5, 6, 7, 8, 9 };

    // ------------------------------------------------

    // using nested scope to solve scope leakage problem

    {
      auto iter = find(begin(ivec), end(ivec), 78);

      if (iter != end(ivec))
        std::cout << iter - begin(ivec) << '\n';
      // output -> 4
    }

    // ------------------------------------------------

    // using if with initializer (C++17) for scope leakage problem

    if (auto iter = find(begin(ivec), end(ivec), 78); iter != end(ivec))
      std::cout << iter - begin(ivec) << '\n';
    // output -> 4
    
    // ------------------------------------------------
  }
*/

/*
  int foo() { return 12; }

  int main()
  {
    // if with initializer (C++17)
    if (int ival = foo(); ival > 10)
      std::cout << "(ival > 10) ival = " << ival << '\n';
    else
      std::cout << "(ival <= 10) ival = " << ival << '\n';
    // output -> (ival > 10) ival = 12
    

    ival = 99; // syntax error
    // error: 'ival' was not declared in this scope;
  }
*/