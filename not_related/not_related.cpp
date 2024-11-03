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

/*
            ----------------------------------------
            | std::initializer_list class template |
            ----------------------------------------
*/

/*
  initializer_list class have 2 pointer data members.
    - 1st points to the address of array's beginning.
    - 2nd points to the address of array's end.
*/

/*
  #include <initializer_list>

  void func(std::initializer_list<int> param) {}

  int main()
  {
    std::initializer_list<int> init_list = { 1, 3, 5, 7, 9 };
    
    std::cout << "sizeof(myList) = " << sizeof(init_list) << '\n';
    // output -> sizeof(myList) = 16

    func(init_list);  
    // passing 2 pointers to the function
  }
*/

/*
  #include <initializer_list>

  class Myclass {
    char m_buffer[1024]{};
  };

  int main()
  {
    std::initializer_list<Myclass> init_list{ Myclass{}, Myclass{} };

    std::cout << "sizeof(Myclass) = " 
              << sizeof(Myclass) << '\n';
    // output -> sizeof(Myclass) = 1024

    std::cout << "sizeof(init_list) = " 
              << sizeof(init_list) << '\n';
    // output -> sizeof(init_list) = 16
  }
*/

/*
  int main()
  {
    auto x = { 1, 2, 3, 4, 5 };
    // x's declaration type is initializer_list<int>

    auto y = { 1, 2, 3, 4, 5.5 }; // syntax error
    // error: unable to deduce 'std::initializer_list<auto>' 
    // from '{1, 2, 3, 4, 5.5e+0}'
    // note: deduced conflicting types for parameter 'auto' 
    // ('int' and 'double')
  }
*/

/*
  int main()
  {
    auto x{ 1 };
    // x's declaration type is int

    auto y{ 1, 2 }; // syntax error
    // error: direct-list-initialization of 'auto' requires 
    // exactly one element

    auto z = { 1 }; 
    // z's declaration type is initializer_list<int>
  }
*/

/*
  #include <initializer_list>

  void func(std::initializer_list<int> x) {}

  int main()
  {
    func({ 1, 3, 5 });  
    // passing initializer_list<int> to the function
  }
*/

/*
  #include <initializer_list>

  int main()
  {
    std::initializer_list<int> init_list{ 1, 2, 3, 4, 5 };

    std::cout << "init_list.size() = " << init_list.size() << '\n';
    // output -> init_list.size() = 5

    for (auto iter = init_list.begin(); iter != init_list.end(); ++iter)
      std::cout << *iter << " ";
    // output -> 1 2 3 4 5

    std::cout << '\n';

    // range-based for loop
    for (auto elem : init_list)
      std::cout << elem << " "; 
      // output -> 1 4 7 2 9
  }
*/


/*
  // using initializer_list in range-based for loop

  int bar(int);

  void foo(int param1, int param2, int param3, int param4)
  {
    for (auto elem : { param1, param2, param3, param4 }){
      bar(elem); 
    }
  }
*/

/*
  #include <initializer_list>

  int main()
  {
    std::initializer_list<double> x = { 1, 4, .6, 7, .3 };
    // explicit template argument declaration

    // int elements inside initializer_list<double>
    // will implicitly convert to double. (int ==> double)
  }
*/

/*
  int main()
  {
    auto init_list = { 1, 2, 3, 4, 5 };

    // ------------------------------------------------

    auto iter = init_list.begin();
    std::cout << *iter << '\n'; 
    // output -> 1 (1st element in initializer_list)

    ++iter;
    std::cout << *iter << '\n'; 
    // output -> 3 (2nd element in initializer_list)

    // ------------------------------------------------

    *iter = 10; // syntax error
    // error: assignment of read-only location '* iter'

    // begin() member function's return type is  int const* 
    // (pointer to const int)
    // so we can't change the value of the element

    // ------------------------------------------------
  }
*/

/*
  #include <initializer_list>
  #include <vector>
  #include <string>

  class Myclass {
  public:
    Myclass(std::initializer_list<int> init_list_param)
    {
      std::cout << "initializer_list<int> ctor\n";
    }
  };

  int main()
  {
    Myclass m1{ 1, 3, 5, 7 };
    // output -> initializer_list<int> ctor

    // ------------------------------------------------

    std::vector<int> ivec{ 1, 2, 3, 4, 5 }; 
    // std::vector classes initializer_list parameter constructor

    // ------------------------------------------------

    std::string str{ 'h', 'e', 'l', 'l', 'o' };
    std::cout << "str = " << str << '\n'; // output -> str = hello
    // std::string class's initializer_list<char> ctor

    // ------------------------------------------------
  }
*/

/*
  #include <initializer_list>

  class Myclass {
  public:
    // converting constructor
    Myclass(int)
    {
      std::cout << "Myclass(int)\n";
    }

    // converting constructor
    Myclass(int, int)
    {
      std::cout << "Myclass(int,int)\n";
    }

    // initializer_list parameter constructor
    Myclass(std::initializer_list<int>)
    {
      std::cout << "Myclass(std::initializer_list<int>)\n";
    }
  };

  int main()
  {
    Myclass m3(20);
    // output -> Myclass(int)

    Myclass m1(12, 24);
    // output -> Myclass(int,int)
    
    Myclass m4{ 20 };
    // output -> Myclass(std::initializer_list<int>)

    Myclass m2{ 12, 34 };
    // output -> Myclass(std::initializer_list<int>)
  }
*/