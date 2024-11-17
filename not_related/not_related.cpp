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

    if (auto it = find(begin(ivec), end(ivec), 78); it != end(ivec))
      std::cout << it - begin(ivec) << '\n';
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

    for (auto it = init_list.begin(); it != init_list.end(); ++it)
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

/*
                    ----------------------------
                    | std::pair class template |
                    ----------------------------
*/

/*
  // std::pair is an aggregate class

  #include <utility>    // std::pair
  #include <string>

  template <typename T, typename U>
  struct Pair {
    T m_first{};
    U m_second{};
  };

  std::pair<int, std::string> foo();
  // 2 different type can be return with std::pair

  int main()
  {
    std::pair<int, double> p1;
    std::cout << p1.first << '\n';    // output -> 0
    std::cout << p1.second << '\n';   // output -> 0.0
    // default ctor is value initializing data members

    std::pair <int, std::string> p2;
    std::cout << p.first << '\n';           // output -> 0
    std::cout << p.second.size() << '\n';   // output -> 0

    // in std::pair's default initialization
    // std::string's default ctor will be called
  }
*/

/*
  #include <utility>    // std::pair
  #include <string>

  int main()
  {
    // ---------------------------------------------------

    std::pair<int, double> p1{ 1, 2.5 };
    // pair(const T& x, const U& y) constructor is being called.

    std::cout << p1.first << '\n';    // output -> 1
    std::cout << p1.second << '\n';   // output -> 2.5

    // ---------------------------------------------------

    std::pair <std::string, double> p2{ "hello", 2.3 };
    std::cout << p2.first << '\n';    // output -> hello
    std::cout << p2.second << '\n';   // output -> 2.3

    // ---------------------------------------------------
  }
*/

/*
  #include <utility>    // std::pair
  #include <string>

  int main()
  {
    std::pair p3{ 4, 5.5 }; 
    std::pair<int, double> p4{ 4, 5.5 };
    // Those 2 lines are equivalent.
    // CTAD (Class Template Argument Deduction)
    // ---------------------------------------------------
  }
*/

/*
  #include <utility>    // std::pair
  #include <string>

  template <typename T, typename U>
  struct Pair {
  public:
    T m_first{};
    U m_second{};

    Pair() = default;
    Pair(const T& first, const U& second) 
      : m_first(first), m_second(second) {}

    // member template constructor function
    template <typename A, typename B>
    Pair(const Pair<A, B>& other) 
      : m_first(other.m_first), m_second(other.m_second) {}

    // member template copy assignment operator
    template <typename A, typename B>
    Pair& operator=(const Pair<A, B>& other)
    {
      m_first = other.m_first;
      m_second = other.m_second;
      return *this;
    }
  };

  int main()
  {
    // ---------------------------------------------------

    std::pair<double, double> p1{ 3.14, 6.28 };
    std::pair<int, int> p2{ 11, 22 };

    p2 = p1;  // VALID
    p1 = p2;  // VALID

    // ---------------------------------------------------

    std::pair<std::string, double> p3;
    std::pair<const char*, int> p4{ "hello", 22 };
    p3 = p4;  // VALID

    // conversion from const char* to std::string is allowed

    // ---------------------------------------------------
  }
*/

/*
  template <typename T, typename U>
  struct Pair {
    T m_first{};
    U m_second{};

    Pair() = default;
    Pair(const T& first, const U& second) 
      : m_first(first), m_second(second) {}

    // conversion constructor (member template)
    template <typename A, typename B>
    Pair(const Pair<A, B>& other) 
      : m_first(other.m_first), m_second(other.m_second) {}
  };

  int main()
  {
    Pair<double, double> p1{ 2.2, 4.4 };
    Pair<int, int> p2{ 11, 22 };

    p1 = p2;
  }
*/

/*
  #include <utility>  // std::pair, std::make_pair

  template <typename T, typename U>
  std::pair<T, U> Make_Pair(const T& first, const U& second)
  {
    return std::pair<T, U>(first, second);
  }

  int main()
  {
    auto p1 = Make_Pair(12, 4.5);
    // "Make_Pair(12, 4.5)" is a PRValue expression(R)
  }
*/

/*
  #include <utility>  // std::pair, std::make_pair
  #include <string>

  // inserter operator overload for std::pair
  template <typename T, typename U>
  std::ostream& operator<<( std::ostream& os, 
                            const std::pair<T, U>& p)
  {
    return os << '[' << p.first << ", " << p.second << ']';
  }

  int main()
  {
    std::pair<int, double> p1{ 2, 4.4 };
    std::cout << p1 << '\n';  // output -> [2, 4.4]

    std::cout << std::make_pair(12, 5.5) << '\n';
    // output -> [12, 5.5]

    std::string str{ "hello" };
    std::cout << std::make_pair(std::make_pair(11, 3.3), 
                                std::make_pair( str, 44L)) << '\n';
    // output -> [[11, 3.3], [hello, 44]]
  }
*/

/*
  #include <utility>  // std::make_pair

  template <typename T, typename U>
  bool operator<( const std::pair<T, U>& lhs, 
                  const std::pair<T, U>& rhs)
  {
    return (lhs.first < rhs.first || !(rhs.first < lhs.first)) && 
            lhs.second < rhs.second;
  }

  int main()
  {
    std::cout << std::boolalpha;

    auto p1 = std::make_pair(1, 11);
    auto p2 = std::make_pair(2, 22);

    std::cout <<  (p1 < p2) << '\n';  // output -> true
  }
*/

/*
  #include <utility>  // std::make_pair
  #include <string> 

  int main()
  {
    using namespace std::literals;

    auto p1 = std::make_pair("hello", 11);
    // p1.first data member's type is const char*

    auto p2 = std::make_pair("world"s, 12);
    auto p3 = std::make_pair(operator""s("world", 6), 12);
    // Those 2 lines are equivalent.
    // p2.first data member's type is std::string
  }
*/

/*
  #include <utility>  // std::pair
  #include <string>

  int main()
  {
    int x{ 10 };
    std::string str{ "hello" };

    // ---------------------------------------------------

    std::pair<int, std::string> p1{ x, str };
    p1.first *= 11;
    p1.second += " world";

    std::cout << p1.first << ' ' << p1.second << '\n';
    // output -> 110 hello world

    std::cout << "x = " << x << '\n';       
    // output -> x = 10
    std::cout << "str = " << str << '\n';
    // output -> str = hello


    // ---------------------------------------------------

    std::pair<int&, std::string&> p2{ x, str };
    p2.first *= 22;
    p2.second += " galaxy";

    std::cout << p2.first << ' ' << p2.second << '\n';
    // output -> 220 hello galaxy

    std::cout << "x = " << x << '\n';       
    // output -> x = 220
    std::cout << "str = " << str << '\n';
    // output -> str = hello galaxy

    // ---------------------------------------------------
  }
*/

/*
                      ----------------------
                      | perfect forwarding |
                      ----------------------
*/

/*
  #include <utility>  // std::move

  class Myclass{};

  void foo(Myclass&)
  {
    std::cout << "foo(Myclass&)" << '\n';
  }

  void foo(const Myclass&)
  {
    std::cout << "foo(const Myclass&)" << '\n';
  }

  void foo(Myclass&&)
  {
    std::cout << "foo(Myclass&&)" << '\n';
  }

  void foo(const Myclass&&)
  {
    std::cout << "foo(const Myclass&&)" << '\n';
  }

  void call_foo(Myclass& r)
  {
    foo(r);
  }

  void call_foo(const Myclass& r)
  {
    foo(r);
  }

  void call_foo(Myclass&& r)
  {
    foo(std::move(r));
  }

  void call_foo(const Myclass&& r)
  {
    foo(std::move(r));
  }

  // if "foo" function have 2 parameters 
  // 16(4^2) "call_foo" overloads need to be written

  // if "foo" function have n parameters
  // 4^n "call_foo" overloads need to be written

  int main()
  {
    Myclass mx;
    const Myclass cx;

    foo(mx);                  // output -> foo(Myclass&)
    call_foo(mx);             // output -> foo(Myclass&)

    foo(cx);                  // output -> foo(const Myclass&)
    call_foo(cx);             // output -> foo(const Myclass&)

    foo(Myclass{});           // output -> foo(Myclass&&)
    call_foo(Myclass{});      // output -> foo(Myclass&&)

    foo(std::move(cx));       // output -> foo(const Myclass&&)
    call_foo(std::move(cx));  // output -> foo(const Myclass&&)
  }
*/

/*
  #include <utility>  // std::forward, std::move

  class Myclass{};

  void foo(Myclass&)
  {
    std::cout << "foo(Myclass&)" << '\n';
  }

  void foo(const Myclass&)
  {
    std::cout << "foo(const Myclass&)" << '\n';
  }

  void foo(Myclass&&)
  {
    std::cout << "foo(Myclass&&)" << '\n';
  }

  void foo(const Myclass&&)
  {
    std::cout << "foo(const Myclass&&)" << '\n';
  }

  template <typename T>
  void forward_foo(T&& r) // universal reference parameter
  {
    foo(std::forward<T>(r));
  }

  int main()
  {
    Myclass mx;
    const Myclass cx;

    forward_foo(mx);                // output -> foo(Myclass&)
    forward_foo(cx);                // output -> foo(const Myclass&)
    forward_foo(Myclass{});         // output -> foo(Myclass&&)
    forward_foo(std::move(cx));     // output -> foo(const Myclass&&)
  }
*/

/*
  // "bar" function does have 2 parameters
  template <typename T, typename U>
  void forward_bar(T&& t, U&& u)
  {
    bar(std::forward<T>(t), std::forward<U>(u));
  }

  // "func" function does have N parameters
  template <typename ...Args>
  void forward_func(Args&& ...args)
  {
    func(std::forward<Args>(args)...);
  }
*/

/*
  template <typename T>
  class Vector {
  public:
    void push_back(const T&);
    // const L value reference parameter

    void push_back(T&&);  
    // R value reference parameter (NOT universal reference)

    // (move overloads)
  };
*/

/*
  #include <utility>  // std::move

  template <typename T>
  class Myclass {
  public:
    void foo(T&&);
    // "foo"'s parameter is R value reference

    template <typename U>
    void func(U&&);
    // "func" parameter is universal reference
  };

  int main()
  {
    Myclass<int> mx;
    int x{};
    int y{};

    // ---------------------------------------------------

    mx.foo(x);  // syntax error
    // error: cannot bind rvalue reference of type 'int&&' 
    // to lvalue of type 'int'

    mx.foo(std::move(x));  // VALID

    // "foo" function have a R value reference parameter
    // it can not be called with L value expressions.

    // ---------------------------------------------------

    mx.func(y);               // VALID
    mx.func(std::move(y));    // VALID

    // "func" function have a universal reference parameter
    // it can be called with L value and R value expressions.

    // ---------------------------------------------------
  }
*/

/*
  template <typename T>
  void foo(T&&);          
  // forwarding(universal) reference

  template <typename T>
  void bar(const T&&); 
  // const R value reference (NOT universal reference)   
*/

/*
  template <typename T>
  class Myclass {};

  template <typename T>
  void func(Myclass<T>&&);  
  // R Value reference (NOT universal reference)

  int main()
  {
    Myclass<int> mx;

    func(mx);   // syntax error
    // error: cannot bind rvalue reference of type 'Myclass<int>&&' 
    // to lvalue of type 'Myclass<int>'
  }
*/

/*
  #include <utility>  // std::move

  int main()
  {

    int x = 11;
    const int cx = 22;

    auto&& var_1 = x;   // VALID
    auto&& var_2 = cx;  // VALID

    auto&& var_3 = 11;  // VALID
    auto&& var_4 = std::move(x);  // VALID
    auto&& var_5 = std::move(cx); // VALID
  
    // `auto&&` is a universal reference type
  }
*/

/*
                          --------------
                          | type alias |
                          --------------
*/

/*
  typedef declarations
  -------------------------------------------------------

  1. declare a variable from that type.
  2. add `typedef` keyword in front of the declaration.
  3. change the variable identifier with the alias identifier.

  1. int x;
  2. typedef int x;
  3. typedef int Word;  
  // Word is an alias for int

  1. int i_arr[10];
  2. typedef int i_arr[10];
  3. typedef int i_arr10[10]
  // i_arr10 is an alias for int[10]

  1. int(*fp)(const char*, const char*);
  2. typedef int(*fp)(const char*, const char*);
  3. typedef int(*cmp_func)(const char*, const char*);
  // cmp_func is an alias for int(*)(const char*, const char*)
*/

/*
  typedef int* IPTR;  // IPTR is an alias for int*

  int main()
  {
    int x = 10;
    int y = 12;

    // ---------------------------------------------------

    const IPTR p1 = &x;   // top level const
    int* const p2 = &x;   // top level const
    // These 2 lines are equivalent.
    // p1 and p2's data type is int* const (const pointer to int)

    // ---------------------------------------------------

    *p1 = 55;  // VALID
    p1 = &y;	 // syntax error
    // error: assignment of read-only variable 'p1'

    // ---------------------------------------------------
  }
*/

/*
  using declarations
  -------------------------------------------------------
  using cmp_func  = int(*)(const char*, const char*);
  using i_pair    = std::pair<int, int>;
  using i_arr10   = int[10];
  using Word      = int; 
*/

// ---------------------------------------------------
// ---------------------------------------------------
// ---------------------------------------------------
// ---------------------------------------------------
// ---------------------------------------------------