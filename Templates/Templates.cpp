#include <iostream>

/*	
                            =============
                            | Templates |
                            =============
*/

/*
  Template categories
  -----------------------
    -> function template
    -> class template
    -> alias template     (C++11)
    -> variable template  (C++14)
    -> concepts           (C++20)
*/

/*
  Template parameters
  -----------------------
    -> template type parameter
    -> non-type template parameter (NTTP)
    -> template template parameter
*/

/*
  template <class T, typename U>
  // T and U are template type parameters.
*/

/*
  // non-type template parameter represents a constant

  template <int N>
  class Myclass {}; 
  // N is a non-type template parameter (NTTP)
*/

/*
  template <typename T, int N>
  class Myclass {
  private:
    T arr[N];
  };
  // first template parameter is a type parameter
  // second template parameter is a non-type template parameter (NTTP)
*/

/*
  template <typename T>
  void func(T x, T y){}
  // "func" function template have 
  //    1 template type parameter
  //    2 function parameters
*/

/*
  - explicit template argument
  - deduction
    -> before C++17, template argument deduction was only 
    valid for function templates.
    -> after C++17, class templates are also use template
    argument deduction called CTAD(Class Template Argument Deduction)
  - default template argument
*/

/*
  template <typename T>
  void foo(T x){}
  
  int main()
  {
    
    foo<int>(12); // explicit template argument
  }
*/


/*
  Template codes are implicitly INLINE, 
  so they will not violate ODR(One Definition Rule).
  They should be define in header(.h) files.
*/

/*
  template <typename T>
  void func(T x)
  {
    // ---------------------------------------------------

    foo(x);   // VALID
    x.bar();  // VALID

    // "foo" and "bar" identifiers are dependent to type `T` 
    // name lookup has been failed for "foo" and "bar" identifiers
    // but because of they are dependent to type `T`,
    // with Argument Dependent Lookup[ADL] rules, 
    // those identifiers might be found. 

    // so there won't be a compile time error
    // if identifiers will not found in run time, 
    // it will be a run time error.

    // ---------------------------------------------------

    baz();    // syntax error
    // error: there are no arguments to 'baz' 
    // that depend on a template parameter, 
    // so a declaration of 'baz' must be available

    // name lookup for "baz" identifier 
    // started from "func" function's scope   -> NOT FOUND
    // continued from global namespace scope  -> NOT FOUND
    // so it will be a syntax error.

    // --------------------------------------------------
  }
*/


/*
                  -------------------------------
                  | template argument deduction |
                  -------------------------------
*/

/*
  template <typename T>
  void func(T x){}

  int main()
  {
    func(12);     // func<int>(12)
    func(1.2);    // func<double>(1.2)
    func(29L);    // func<long>(29L)

    // template argument deduction rules applied.
  }
*/

/*
  // <---- check type_deduction/type_deduction.cpp ---->

  template <typename T>
  void func(T x) {}
  // For T type	  -> auto x = expr; rules applied.

  template <typename T>
  void foo(T& x) {}
  // For T& type  -> auto& y = expr; rules applied.

  template <typename T>
  void bar(T&& x) {}
  // For T&& type	-> auto&& z = expr; rules applied.
*/

/*
  template <typename T>
  void func(T x) {}
  // For T type	  -> auto x = expr; rules applied.

  int main()
  {
    const int c_ival = 24;
    func(c_ival); 
    // T will deduce to type `int`
    // const will drop

    int arr[10]{};
    func(arr);    
    // T will deduce to type `int*`
    // array to pointer conversion

    const int c_arr[10]{};
    func(c_arr);  
    // T will deduce to type `const int*`
  }
*/

/*
  // For T type	  -> auto x = expr; rules applied.

  template <typename>
  class TypeTeller;   // incomplete type

  template <typename T>
  void func(T)
  {
    TypeTeller<T> x;  // syntax error
    // creating an object from incomplete type
    // will be a syntax error.
    // but syntax error message will show us the type of T
  }

  int foo(int);

  int main()
  {
    // ---------------------------------------------------

    func(12);
    // error: 'TypeTeller<int> x' has incomplete type
    // T will be deduced to int

    // ---------------------------------------------------

    int arr[4]{};
    func(arr);
    // error: 'TypeTeller<int*> x' has incomplete type
    // T will be deduced to int* (array to pointer conversion)

    // ---------------------------------------------------

    const int c_arr[5]{};
    func(c_arr);
    // error: 'TypeTeller<const int*> x' has incomplete type
    // T will be deduced to const int* 

    // ---------------------------------------------------

    int ival = 10;
    int& iref = ival;
    func(iref);
    // error: 'TypeTeller<int> x' has incomplete type
    // reference will be drop.
    // T will be deduced to int

    // ---------------------------------------------------

    func("Hello");    // "Hello" is a const char[6]
    // error: 'TypeTeller<const char*> x' has incomplete type
    // T will be deduced to const char*

    // ---------------------------------------------------

    func(foo);  
    // error: 'TypeTeller<int (*)(int)> x' has incomplete type
    // T will be deduced to int(*)(int)

    // function to function pointer conversion

    // ---------------------------------------------------
  }
*/

/*
  // For T& type  -> auto& y = expr; rules applied.

  template <typename>
  class TypeTeller;  // incomplete type

  template <typename T>
  void func(T& param)
  {
    TypeTeller<T> x;
  }

  int foo(int);

  int main()
  {
    // ---------------------------------------------------

    int ival = 10;
    func(ival);
    // error: 'TypeTeller<int> x' has incomplete type
    // T will be deduced to int
    // "param" function parameter type will be int&

    // ---------------------------------------------------
    
    int arr[5]{};
    func(arr);
    // error: 'TypeTeller<int [5]> x' has incomplete type
    // T will be deduced to int[5]
    // "param" function parameter type will be int(&)[5]

    // NO array to pointer conversion

    // ---------------------------------------------------
    
    func(foo);
    // error: 'TypeTeller<int(int)> x' has incomplete type
    // T will be deduced to int(int)
    // "param" function parameter type will be int(&)(int)

    // NO function to function pointer conversion

    // ---------------------------------------------------
    
    const int c_ival = 4;
    func(c_ival);
    // error: 'TypeTeller<const int> x' has incomplete type
    // T will be deduced to const int
    // "param" function parameter type will be const int&

    // const WILL NOT drop
    
    // ---------------------------------------------------
  }
*/

/*
  template <typename>
  class TypeTeller;

  template <typename T>
  void func(T&& param)
  {
    TypeTeller<T> x;
    // "param"'s(function's parameter variable) data type
    // can only be an L value reference or R value reference
  }

  int main()
  {
    // ---------------------------------------------------

    func(123);
    // error: 'TypeTeller<int> x' has incomplete type

    // "123" is a PR value expression(R)
    // T's type is int 
    // "param"'s type is int&&

    // ---------------------------------------------------

    int y = 23;
    func(y);
    // error: 'TypeTeller<int&> x' has incomplete type

    // "y" is an L value expression
    // reference collapsing will be applied & - && -> &
    // T's type is int&
    // reference collapsing will be applied for "param" 
    // (& - && -> &) "param"'s type is int&

    // ---------------------------------------------------
  }
*/

/*
  template <typename T>
  void func(T&& param)
  {
    T x;  // syntax error
    // error: 'x' declared as reference but not initialized
    // int& variable can not be default initialized.
  }

  int main()
  {
    int y = 23;
    func(y);
    // "y" is an L value expression
    // T's type is int&
    // "param"'s type is (& - && -> &) int&
  }
*/

/*
  // The only difference between,
  // auto type deduction and template argument deduction
  // is std::initializer_list type deduction.

  #include <initializer_list>
  #include <type_traits>  // std::is_same

  template <typename T>
  void func(T);

  int main()
  {
    // ---------------------------------------------------

    auto init_list = { 1, 2, 3, 4, 5 }; // VALID

    static_assert(std::is_same_v<decltype(init_list), 
                  std::initializer_list<int>>); // HOLDS

    // {1, 2, 3, 4, 5} will be deduce to std::initializer_list<int>
    // in auto type deduction

    // ---------------------------------------------------

    func({ 1, 2, 3, 4, 5 }); // syntax error
    // error: no matching function for call to 
    // 'func(<brace-enclosed initializer list>)'

    // template argument deduction can not be done for 
    // initializer_list type

    // ---------------------------------------------------
  }
*/

/*
  template <typename T>
  T foo();

  int main()
  {
    // ---------------------------------------------------

    foo();  // syntax error
    // error: no matching function for call to 'foo()'
    // note: couldn't deduce template parameter 'T'

    // ---------------------------------------------------

    int x = foo();  // syntax error.
    // error: no matching function for call to 'foo()'
    // note: couldn't deduce template parameter 'T'

    // ---------------------------------------------------
  }
*/

/*
  template <typename T>
  void func(T, T);

  int main()
  {
    func(1, 5u);  // syntax error
    // error: no matching function for call to 
    // 'func(int, unsigned int)'
  }
*/

/*
  template <typename T>
  void func(T param_1, T&& param_2);

  int main()
  {
    // ---------------------------------------------------

    func(10, 20); // VALID
    // for first argument('10')
    // T will be deduced to int
    // "param_1"'s type will be int

    // for the second argument('20')
    // "20" is a PRValue expression(R)
    // T will be deduced to int
    // param_2's type will be int&&

    // ---------------------------------------------------

    int ival{ 11 };
    func(ival, ival); // syntax error
    //  error: no matching function for call to 'func(int&, int&)'

    // for first argument('ival') 
    // T will be deduced to int

    // for the second argument('ival') 
    // "ival" is an L value expression
    // T will be deduced to int&

    // ---------------------------------------------------
  }
*/

/*
  template <typename T>
  void func_1(T, T);

  template <typename T>
  void func_2(T&, T&);

  int main()
  {
    // ---------------------------------------------------

    func_1("hello", "world");   // VALID
    // for both arguments
    // T will be deduced to const char*

    func_1("hello", "universe"); // VALID
    // for both arguments
    // T will be deduced to const char*

    // array to pointer conversion WILL be applied

    // ---------------------------------------------------

    func_2("hello", "world");   // VALID
    // for both arguments
    // T will be deduced to const char[6]

    func_2("hello", "universe");  // syntax error
    // error: no matching function for call to 
    // 'func_2(const char [6], const char [9])'

    // for 1st argument T will be deduced to const char[6]
    // for 2nd argument T will be deduced to const char[9]

    // array to pointer conversion WILL NOT be applied

    // ---------------------------------------------------
  }
*/

/*
  template <typename T, int N>
  void func(T(&arr_ref)[N]);

  int main()
  {
    int i_arr[5]{};
    func(i_arr);

    // T wiill be deduced to int
    // N will be deduced to 5
  }
*/

/*
  template <typename T>
  void func(T* arg);

  int main()
  {
    int x{};
    int* p = &x;
    int** pp = &p;

    func(p);	
    // T will be deduced to int
    // "arg"'s type will be int*

    func(pp);
    // T will be deduced to int*
    // "arg"'s type will be int**
  }
*/

/*
  template <typename T, typename U>
  void func(T(*)(U));

  int bar(double);

  int main()
  {
    func(bar);  // function to function pointer conversion
    func(&bar);
    // Those 2 lines are equivalent.

    // T will be deduced to int
    // U will be deduced to double
  }
*/

/*
  template <typename T, std::size_t N>
  constexpr std::size_t asize(T(&)[N])
  {
    return N;
  }

  int main()
  {
    int arr[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    constexpr auto arr_size = asize(arr); // arr_size -> 9u
  }
*/

/*
  // compiler will wrote different functions(specilizations) 
  // for each template argument

  template <typename T>
  void func(T)
  {
    std::cout << typeid(T).name() << '\n';
  }

  int main()
  {
    func(12);     // output -> int
    func('A');    // output -> char
    func(true);   // output -> bool
    // template argument will be deduced for each function call

    func<int>(12);    // output -> int
    func<int>('A');   // output -> int
    func<int>(true);  // output -> int
    // explicit template argument
  }
*/

/*
  template <typename Fn>
  void func(Fn fn)
  {
    fn();
  }

  void bar()
  {
    std::cout << "bar() called\n";
  }

  void compiler_written_func_for_bar(void(*fn)())
  {
    fn(); 
    // fn is a function pointer(callable)
  }

  class Myclass {
  public:
    void operator()() const
    {
      std::cout << "Myclass::operator()() called\n";
    }
  };

  int main()
  {
    // ---------------------------------------------------
    
    func(bar);  
    // output -> bar() called

    // "bar"'s type is void(*)()
    // so Fn will be deduced to void(*)()
    // compiler written function specialization will be like 
    // "compiler_written_func_for_bar" function

    compiler_written_func_for_bar(bar);
    // output -> bar() called

    // ---------------------------------------------------

    func(Myclass{});  // output -> Myclass::operator()() called

    // ---------------------------------------------------
  }
*/

/*
  class Myclass {
  public:
    class value_type {};  // nested type
  };

  template <typename T>
  void func(T)
  {
    T::value_type x;
    // compiler thinks that "value_type"
    // is a static data member of T type.
  }

  int main()
  {
    func(Myclass{});  // syntax error
    // error: need 'typename' before 'T::value_type' 
    // because 'T' is a dependent scope

    // error: dependent-name 'T::value_type' is parsed as a non-type, 
    // but instantiation yields a type
  }
*/

/*
  class Myclass {
  public:
    class value_type {};  // nested type
  };

  template <typename T>
  void func(T)
  {
    typename T::value_type x;
    // compiler thinks that "value_type" is a nested type of T type.

    // when declaring a variable from nested type, 
    // `typename` keyword should be used.
  }

  int main()
  {
    func(Myclass{});  // VALID
  }
*/

/*
  template <typename T>
  void func_1(T t)
  {
    std::cout << "t = " << t << '\n';
  }

  template <typename T, typename U>
  void func_2(T t, U u)
  {
    std::cout << "t = " << t << ", u = " << u << '\n';
  }

  int main()
  {
    // ---------------------------------------------------

    func_1<double>(12);     // output -> t = 12
    // no template argument deduction for T, 
    // because its type is explicitly declared as double.

    // ---------------------------------------------------

    func_2(12, 45);         // output -> t = 12, u = 45
    // T will be deduced to int
    // U will be deduced to int
    // T and U's type can be same.

    // ---------------------------------------------------

    func_2(12, 3.14);       // output -> t = 12, u = 3.14
    // T will be deduced to int
    // U will be deduced to double

    // ---------------------------------------------------

    func_2<int>('A', 5.6);  // output -> t = 65, u = 5.6
    // T's type is explicitly declared as int 
    // U's type will be deduced to double

    // char('A') will be implicitly converted to int(65)

    // ---------------------------------------------------
  }
*/

/*
  // in some scenarios compiler can not understand T's type
  // if we did not declare T as an explicit template argument.

  #include <memory> // std::make_unique, std::unique_ptr
  #include <string>

  template <typename T, typename ...Args>
  std::unique_ptr<T> Make_Unique(Args&&...args);

  int main()
  {
    auto p_str = std::make_unique<std::string>(10, 'A');
    std::cout << *p_str << '\n';  // output -> AAAAAAAAAA
  }
*/

/*
                    ------------------------
                    | trailing return type |
                    ------------------------
*/

/*
  int foo(int,int);
  // function that returns the address of 
  // "foo" function, should have a return type of int(*)(int,int) 

  int(*func_1())(int, int)
  {
    return &foo;
  }

  auto func_2() -> int(*)(int, int)
  {
    return foo;
  }
  // both "func_1" and "func_2" functions are equivalent.
*/


/*
  template <typename T, typename U>
  T sum_template_argument(T x, U y)
  {
    return x + y;
  }

  template <typename TResult, typename T, typename U>
  TResult sum_explicit_template_argument(T x, U y)
  {
    return x + y;
  }

  // trailing return type
  template <typename T, typename U>
  auto sum_trailing(T x, U y)-> decltype(x + y)
  {
    return x + y;
  }

  // auto return type
  template <typename T, typename U>
  auto sum_auto(T x, U y)
  {
    return x + y;
  }

  int main()
  {
    // ---------------------------------------------------

    int res_1 = sum_template_argument(6, 4.5);
    // T will be deduced to int
    // U will be deduced to double
    // because of T's type is `int`, 
    // function's return type will be `int`

    // ---------------------------------------------------

    double res_2 = sum_explicit_template_argument<double>(6, 2.4);
    // TResult's type is explicitly declared as double,
    // function's return type will be double
    // T will be deduced to int
    // U will be deduced to double

    // ---------------------------------------------------

    auto res_3 = sum_trailing(6, 2.2);
    // T will be deduced to int
    // U will be deduced to double
    // decltype(x + y) -> double
    // function's return type will be double

    // ---------------------------------------------------

    auto res_4 = sum_auto(6, 2.2);
    // T will be deduced to int
    // U will be deduced to double
    // x + y -> double
    // function's return type will be double

    // ---------------------------------------------------
  }
*/

/*
                  ----------------------------
                  | member function template |
                  ----------------------------
*/

/*
  #include <type_traits>  // std::is_same

  class Myclass {
  public:
    template <typename T>   // member function template
    void func(T x)
    {
      if (std::is_same_v<T, int>) {
        std::cout << "int\n";
      }
      else if (std::is_same_v<T, double>) {
        std::cout << "double\n";
      }
      else if (std::is_same_v<T, char>) {
        std::cout << "char\n";
      }
      else if (std::is_same_v<T, const char*>) {
        std::cout << "const char*\n";
      }
    }
  };

  int main()
  {
    Myclass m;

    m.func(12);           // output -> int
    m.func(3.14);         // output -> double
    m.func('A');          // output -> char
    m.func("hello");      // output -> const char*
  }
*/

/*
  class Myclass {
  public:
    template<typename T>  
    Myclass(T);   
    // constructor template
  };

  int main()
  {
    Myclass m1{ 35 };       // T will be deduced to int
    Myclass m2{ 3.5 };      // T will be deduced to double
    Myclass m3{ 3.5f };     // T will be deduced to float
    Myclass m4{ 35L };      // T will be deduced to long
    Myclass m5{ 35LL };     // T will be deduced to long long
  }
*/

/*
  class Myclass {
  public:
    template<typename T>
    Myclass& operator=(const T&);   
    // copy assignment operator template
  };

  int main()
  {
    Myclass mx;

    mx = 5;           // T will be deduced to int
    mx = 5.4;         // T will be deduced to double
    mx = 5L;          // T will be deduced to long
    mx = "hello";     // T will be deduced to const char*
    mx = 'B';         // T will be deduced to char
  }
*/

/*
  class Myclass {
  public:
    template<typename T>
    T operator()(T) const;  
    // operator call(operator()()) function template
  };

  int main()
  {
    Myclass mx;

    auto r1 = mx(12);
    // T will be deduced to int
    // r1's type will be int

    auto r2 = mx("Hello");
    // T will be deduced to const char*
    // r2's type will be const char*

    auto r3 = mx(1.4);
    // T will be deduced to double
    // r3's type will be double

    auto r4 = mx('C');
    // T will be deduced to char
    // r4's type will be char
  }
*/

/*
  class Myclass {
  public:
    template<typename T>
    operator T() const    // cast operator template
    {
      return T{} + 65.5;
    }
  };

  int main()
  {
    Myclass mx;

    int ival = mx;
    std::cout << "ival = " << ival << '\n';
    // output -> ival = 65

    double dval = mx;
    std::cout << "dval = " << dval << '\n';
    // output -> dval = 65.2

    long lval = mx;
    std::cout << "lval = " << lval << '\n';
    // output -> lval = 65

    char cval = mx;
    std::cout << "cval = " << cval << '\n';
    // output -> cval = A
  }
*/

// ------------------------------------------------------
// ------------------------------------------------------
// ------------------------------------------------------
// ------------------------------------------------------
// ------------------------------------------------------

/*
  template <typename T>
  T foo(T);

  template <typename T>
  T* func(T*);

  // compiler will do a substitution for each function call
  // and will create a specialization.

  // template specialization that compiler is generated 
  // will join the "function overload resolution".
  // not the function template itself.

  int main()
  {
    int x = 10;
    int* p = &x;
    int** pp = &p;

    foo(x);  
    // int foo<int>(int); -> specialization

    func(pp);
    // int** func<int*>(int**) -> specialization
  }
*/

/*
  template <typename T>
  typename T::value_type func(T)
  {
    std::cout << "typename T::value_type func(T)\n";
    return typename T::value_type();
  }

  void func(double)
  {
    std::cout << "void func(double)\n";
  }

  class Myclass{
  public:
    class value_type {};
  };

  int main()
  {
    // ---------------------------------------------------

    func(2);  // output -> void func(double)

    // in function overload set
    // there is 2 function at first

    // typename int::value_type func(int);
    // void func(double);

    // because of int::value_type is not a valid type 
    // template substitution will fail
    // but it will not cause a syntax error
    // SFINAE(Substitution Failure Is Not An Error)
    // so compiler will remove that template specialization
    // from the function overload set.
    // only viable function left is void func(double)

    // ---------------------------------------------------

    Myclass m;
    func(m);  // output -> typename T::value_type func(T)

    // ---------------------------------------------------
  }
*/

/*
  #include <type_traits>  // std::is_same

  template <typename T>
  void foo(T x)
  {
    if (std::is_same_v<T, int>)
      std::cout << "void foo(T x), T = int\n";
    else if (std::is_same_v<T, double>) 
      std::cout << "void foo(T x), T = double\n";
    else if (std::is_same_v<T, char>) 
      std::cout << "void foo(T x), T = char\n";
    else if (std::is_same_v<T, const char*>)
      std::cout << "void foo(T x), T = const char*\n";
  }

  void foo(int)
  {
    std::cout << "void foo(int)\n";
  }

  int main()
  {
    // ---------------------------------------------------

    foo(2.3);   // output -> void foo(T x), T = double
    // T will be deduced to double

    // void foo<double>(double)   -> exact match
    // void foo(int)              -> conversion
    // 2 overloads are viable in "function overload set".

    // ---------------------------------------------------

    foo('A');   // output -> void foo(T x), T = char
    // T will be deduced to char

    // void foo<char>(char)      -> exact match
    // void foo(int)             -> promotion
    // 2 overloads are viable in "function overload set".

    // ---------------------------------------------------

    foo(12);    // output -> void foo(int)
    // T will be deduced to int

    // void foo<int>(int)       -> exact match
    // void foo(int)            -> exact match    --> choosen
    // 2 overloads are viable in Function Overload Set.
    // both are exact match overload but the real function
    // will be chosen.

    // ---------------------------------------------------
  }
*/

/*
  template <typename T>
  void func(T) = delete;

  void func(double);

  int main()
  {
    func(123);  // syntax error
    // error: use of deleted function 
    // 'void func(T) [with T = int]'

    func(1.f);  // syntax error
    // error: use of deleted function 
    // 'void func(T) [with T = float]'
    func(1u);   // syntax error

    // error: use of deleted function 
    // 'void func(T) [with T = unsigned int]'

    func(12.3); // VALID
    // "func" can only be called with double argument.
  }
*/

/*
  template <typename T>
  void func(T)
  {
    std::cout << "func(T)\n";
  }

  template <typename T>
  void func(T*)
  {
    std::cout << "func(T*)\n";
  }

  template <typename T>
  void func(T**)
  {
    std::cout << "func(T**)\n";
  }

  int main()
  {
    int x{};
    func(&x);   // output -> func(T*)
    // There are 2 viable function specializations

    int* p = &x;
    func(&p);   // output -> func(T**)
    // There are 3 viable function specializations

    // more specific will be chosen,
    // partial ordering rules applied.
  }
*/

/*
  template <typename T>
  void func(T)
  {
    std::cout << "func(T)\n";
  }

  template <typename T, int n>
  void func(T(&)[n])
  {
    std::cout << "func(T(&)[n])\n";
  }

  int main()
  {
    int arr[10]{};
    func(arr);    // output -> func(T(&)[n])
    // There are 2 viable function specializations
    // more specific will be chosen
  }
*/

/*
  template <typename T>
  void baz(T&){}

  template <typename T>
  void bar(T* p)
  {
    baz(*p);
  }

  template <typename T>
  void foo(T x)
  {
    bar(&x);
  }

  int main()
  {
    int x{ 2 };
    foo(x); 
    // void foo<int>(int)  specialization
    // void bar<int>(int*) specialization
    // void baz<int>(int&) specialization
  }
*/

/*
  #include <utility>  // std::move

  template <typename T>
  void Swap(T& r1, T& r2) noexcept
  {
    T temp{ std::move(r1) };
    r1 = std::move(r2);
    r2 = std::move(temp);
  }
*/

/*
  #include <vector>
  #include <list>

  template <typename Pos>
  void Print(Pos beg, Pos end)
  {
    while (beg != end) {
      std::cout << *beg << ' ';
      ++beg;
    }

    std::cout << '\n';
  }
  // Pos type needs to be must meet these conditions
  // - an operand of binary equality operators (!=)
  // - an operand of dereferencing operator (*)
  // - an operand of prefix increment operator.
  // also *beg expression needs to be insertable to output stream.

  int main()
  {
    int arr[] = { 1, 2, 3, 4, 5, 6 };

    Print(arr, arr + 6);        // output -> 1 2 3 4 5 6
    Print(arr + 2, arr + 6);    // output -> 3 4 5 6
    // Pos type will be deduce to int* (array to pointer conversion)

    std::vector<int> ivec{ 1, 2, 3, 4, 5, 6 };
    Print(ivec.begin(), ivec.end());    // output -> 1 2 3 4 5 6

    std::list<int> ilist{ 1, 2, 3, 4, 5, 6 };
    Print(ilist.begin(), ilist.end());  // output -> 1 2 3 4 5 6
  }
*/

// ------------------------------------------------------
// ------------------------------------------------------
// ------------------------------------------------------
// ------------------------------------------------------
// ------------------------------------------------------

/*
  // Do not make functions return type a `const` class object.

  class Myclass {
  public:
    Myclass() = default;
    Myclass(const Myclass&) = default;

    Myclass& operator=(const Myclass&)
    {
      std::cout << "copy assignment called\n";
      return *this;
    }

    Myclass& operator=(Myclass&&)
    {
      std::cout << "move assignment called\n";
      return *this;
    }
  };

  Myclass func_1()
  {
    Myclass x;
    return x;
  }

  const Myclass func_2()
  {
    Myclass x;
    return x;
  }

  int main()
  {
    Myclass x;

    x = func_1();     // output -> move assignment called
    x = func_2();     // output -> copy assignment called

    // returning a const class object will prevent move semantics.
    // because of return type is `const` 
    // Myclass& operator=(Myclass&&) can not be choosen.
  }
*/

/*
  #include <utility>  // std::move

  class Myclass {};

  void foo(const Myclass&)
  {
    std::cout << "const Myclass& called\n";
  }

  void foo(Myclass&&)
  {
    std::cout << "Myclass&& called\n";
  }

  int main()
  {
    Myclass mx;

    Myclass&& r_ref = std::move(mx);
    // "r_ref" is an LValue expression
    // its data type is Myclass&&(R value reference)

    foo(r_ref);             // output -> const Myclass& called
    // passing LValue expression as a function argument

    foo(std::move(r_ref));  // output -> Myclass&& called
    // passing XValue expression(R) as a function argument
  }
*/

/*
  class Myclass {};

  Myclass func_1()
  {
    Myclass x;
    return x; 
    // NRVO(Named Return Value Optimization) 
    // not a mandatory copy ellision
    // L value "x" object will converted to XValue expression(R)
  }

  Myclass func_2()
  {
    Myclass x;
    return std::move(x);
    // no need to use std::move(x)
    // because returning named object from a class type
    // is already an XValue expression(R)

    // it is called Pessimistic move.
  }
*/

// ------------------------------------------------------
// ------------------------------------------------------
// ------------------------------------------------------
// ------------------------------------------------------
// ------------------------------------------------------

/*
                        -------------------
                        | class templates |
                        -------------------
*/

/*
  template <typename T>
  class Myclass {};

  int main()
  {
    Myclass m1; // syntax error
    // error: class template argument deduction failed:
    // note: couldn't deduce template parameter 'T'

    Myclass<int> m2;  // VALID
  }
*/

/*
  template <typename T>
  class AClass {};

  template <int N>
  class BClass {};

  int main()
  {
    // ---------------------------------------------------

    AClass<int> a1;
    AClass<double> a2;
    // both specializations are different classes.

    a2 = a1;  // syntax error.
    // error: no match for 'operator=' 
    // (operand types are 'AClass<double>' and 'AClass<int>')

    // ---------------------------------------------------

    BClass<10> b1;
    BClass<12> b2;
    // both specializations are different classes.

    b2 = b1;  // syntax error
    // error: no match for 'operator=' 
    // (operand types are 'BClass<12>' and 'BClass<10 ')

    // ---------------------------------------------------
  }
*/

/*
  template <typename T>
  class Myclass {
  private:
    T m_x;
  public:
    T foo(T);
    T func(T&&);
  };

  int main()
  {
    Myclass<int> m1;

    m1.foo(12);
    // there won't be any type deduction happening
    // when foo function called with an int argument.
    // because T's will be deduced to int.
    // when class template is specialized with int.

    // for Myclass<int> specialization 
    // "func" functions parameter's type is int&& 
    // which is an R value reference
    // not a universal reference
  }
*/

/*
  template <typename T, std::size_t N>
  class Myclass {
  private:
    T m_arr[N];
    typename T::value_type m_x;    // nested type
  public:
    std::size_t func(T, int);
  };
*/

/*
  template <typename T>
  class Myclass {
  public:
    T foo(T x)
    {
      // class template member function definition
      // in class definition

      Myclass<T> y1;
      Myclass y2;
      // Those 2 lines are equivalent.

      // if this class definition is Myclass<int> specialization
      // y1's data type is Myclass<int>
      // y2's data type is Myclass<int>

      // if this class definition is Myclass<double> specialization
      // y1's data type is Myclass<double>
      // y2's data type is Myclass<double>
    }

    T** func(T* x)
    {
      Myclass m;

      // if this class definition is Myclass<int> specialization
      // "func" function's parameter type is int*
      // "func" function's return type is int**
      // m local variable's data type is Myclass<int>

      // if this class definition is Myclass<double> specialization
      // "func" function's parameter type is double*
      // "func" function's return type is double**
      // m local variable's data type is Myclass<double>
    }

    void bar()
    {
      Myclass m1;
      Myclass<double> m2;
      Myclass<T*> m3;

      // We can also declare different variables which have 
      // different Myclass class template specialization types.

      // if this class definition is Myclass<int> specialization
      // m1 local variable's data type is Myclass<int>
      // m2 local variable's data type is Myclass<double>
      // m3 local variable's data type is Myclass<int*>

      // if this class definition is Myclass<double> specialization
      // m1 local variable's data type is Myclass<double>
      // m2 local variable's data type is Myclass<double>
      // m3 local variable's data type is Myclass<double*>
    }
  };
*/

/*
  template <typename T>
  class Myclass {
  public:
    T func_1(T);
    T func_2(T);
  };

  // class template member function definition
  // outside of class definition

  // ---------------------------------------------------

  template <typename T>
  T Myclass<T>::func_1(T x){ return x; }

  // ---------------------------------------------------

  template <typename T>
  T Myclass::func_2(T x){ return x; }   // syntax error
  // error: 'template<class T> class Myclass' used 
  // without template arguments

  // template arguments need to be provided when we are defining
  // class template member functions outside of the class definition.

  // ---------------------------------------------------
*/

/*
  template <typename T, typename U>
  class Myclass {
  public:
    Myclass foo(Myclass);
    // definition of foo function inside of class definition

    Myclass func_1(Myclass);
    Myclass func_2(Myclass);
  };

  // ---------------------------------------------------

  // definition of foo function outside of class definition
  template<typename T, typename U>
  Myclass<T, U> Myclass<T, U>::foo(Myclass m_param)
  {
    Myclass<T, U> m1;
    Myclass m2;
    // Those 2 lines are equivalent.

    return m_param;
  }

  // member function's return type and 
  // function name is NOT in class scope
  // but parameters are in class scope.
  // function body is also in class scope.

  // so "Myclass<T,U>" MUST BE use for return type and function name
  // but "Myclass" can be used for parameters and local variables,
  // instead of "Myclass<T,U>".

  // ---------------------------------------------------

  template<typename T, typename U>
  Myclass Myclass<T, U>::func_1(Myclass m_param) { return m_param; }
  // syntax error 
  // error: deduced class type 'Myclass' in function return type

  // return type MUST BE "Myclass<T, U>" instead of "Myclass"

  // ---------------------------------------------------

  template<typename T, typename U>
  Myclass<T, U> Myclass::func_2(Myclass m_param) { return m_param; }
  // syntax error
  // error: 'template<class T, class U> class Myclass' 
  // used without template arguments

  // function name MUST BE "Myclass<T, U>" instead of "Myclass"

  // ---------------------------------------------------
*/

/*
  template <typename T, typename U>
  class Myclass {
  public:
    T foo(U);
  };

  // member function definition outside of class definition
  template <class A, class B>
  A Myclass<A, B>::foo(B bx)
  {
    return A{};
  }

  // member function definition outside of class definition
  template <typename T, typename U>
  T Myclass<T, U>::foo(U ux)
  {
    return T{};
  }
  // syntax error
  // error: redefinition of 'T Myclass<T, U>::foo(U)'
*/

/*
  template <typename T>
  class Myclass {};

  Myclass<int> foo(Myclass<double>);
  // class specializations can be used 
  // - as a function parameter variable
  // - as a function return type

  class AClass {
    Myclass<int> m_x;
    Myclass<double*> m_y;
    // class specializations can be used 
    // - as classes member variables
  };

  template <typename T>
  class BClass {};

  int main()
  {
    // ---------------------------------------------------

    Myclass<int> m_arr[11];
    Myclass<int>* p_m = m_arr;

    // ---------------------------------------------------

    BClass<Myclass<int>> b1;
    Myclass<Myclass<double>> m1;
    // class specializations can be used 
    // - as a template argument

    // ---------------------------------------------------
  }
*/

/*
  class AClass {};

  template <typename T>
  class Myclass {
  public:
    void foo()
    {
      T tx;
      ++tx;
      // if "Myclass::foo" invoked 
      // because of AClass does not have an "operator++" overload
      // it will be a syntax error.
    }

    void bar()
    {
      T tx;
      tx.foo();
      // if "Myclass::bar" invoked 
      // because of AClass does not have "foo" member function
      // it will be a syntax error.
    }
  };

  int main()
  {
    Myclass<AClass> mx;

    mx.foo();   // syntax error
    // error: no match for 'operator++' (operand type is 'AClass')

    mx.bar();    // syntax error
    // error: 'class AClass' has no member named 'foo'
  }
*/

/*
  template <int N>        // N is a NTTP
  class Myclass {};

  template <unsigned N>   // N is a NTTP
  class Myclass {};
  
  // syntax error
  // error: template parameter 'int N'
*/

/*
  // auto type as a non-type template parameter (C++17)
  template <auto N>     // N is a NTTP
  class Myclass {
  public:
    Myclass()
    {
      std::cout << typeid(N).name() << '\n';
    }
  };

  int main()
  {
    Myclass<10> m1;   // output -> int
    Myclass<20u> m2;  // output -> unsigned int
    Myclass<'A'> m3;  // output -> char
  }
*/

/*
  // floating types added as a NTTP in (C++20)
  template <double N>
  class Myclass {};
*/

/*
  #include <array>
  #include <bitset>

  template <typename T, std::size_t N>
  struct Array {};

  int main()
  {
    double d_arr1[20];

    std::array<double, 20> d_arr2;
    // 2nd template parameter is a NTTP
    std::bitset<32> bs; 
    // std::bitset have only 1 NTTP
  }
*/

/*
  // splitting interface and implementation of templates.

  // ----------------------------------------------------
  // --------------------SCENARIO 1----------------------
  // ----------------------------------------------------

  // ==== first.h
  // -------------

  template <typename T>
  void func(T x);   
  // function template declaration

  template <typename T, typename U>
  class Myclass {
    void foo(T);  // member function declaration
  };

  // ==== firstimpl.h
  // ----------------
  // #include "first.h"

  template <typename T>
  void func(T x){}
  // function template definition

  template <typename T, typename U>
  class Myclass {
    void foo(T){} // member function definition
  };

  // ----------------------------------------------------
  // --------------------SCENARIO 2----------------------
  // ----------------------------------------------------

  // ==== first.h
  // -------------

  namespace first {
    template <typename T>
    void foo(T);
    // function template declaration

      // nested namespace
      namespace details { 
        // function template definitions...
      }
  }

  // ----------------------------------------------------
*/

/*
  template <int* p>
  class AClass{};

  template<int& r>
  class BClass {};

  int g_x = 10;   // static storage duration object
  int g_y = 20;   // static storage duration object

  int main()
  {
    // ---------------------------------------------------

    AClass<&g_x> a1;
    AClass<&g_y> a2;

    // ---------------------------------------------------

    BClass<g_x> b1;
    BClass<g_y> b2;

    // ---------------------------------------------------

    int l_x = 15;         
    // automatic storage duration object (local variable)
    static int s_x = 20;  
    // static storage duration object (static local variable)

    AClass<&l_x> m3;  // syntax error
    // error: the address of 'l_x' is not a valid template argument 
    // because it does not have static storage duration

    AClass<&s_x> m4;  // VALID

    // ---------------------------------------------------
  }
*/

/*
  template <int(*fp)(int)> 
  class Myclass {};

  int foo(int);
  int bar(int);
  int baz(int);

  int main()
  {
    Myclass<foo> m1;
    Myclass<bar> m2;
    Myclass<baz> m3;
  }
*/

/*
  template <typename T>
  class Myclass {
  public:
    void foo(Myclass);
    // foo function's parameter type is Myclass<T>
  };

  int main()
  {
    // ---------------------------------------------------

    Myclass<int> m1;
    Myclass<int> m2;

    m1.foo(m2);   // VALID

    // ---------------------------------------------------

    Myclass<double> m3;
    Myclass<int> m4;

    m4.foo(m3);   // syntax error
    // error: cannot convert 'Myclass<double>' to 'Myclass<int>'

    // passing Myclass<int> specialization's "foo" function
    // Myclass<double> specialization variable
    // which is not a valid argument type.

    // ---------------------------------------------------
  }
*/

/*
  class AClass {
  public:
    template <typename T>
    void func(BClass<T>);
  };

  template <typename T>
  class BClass {};

  int main()
  {
    AClass ax;

    BClass<int> b1;
    BClass<double> b2;

    ax.func(b1);  // VALID
    ax.func(b2);  // VALID
  }
*/

/*
  template <typename T>
  class Myclass {
  public:
    template <typename U>
    void foo(U)
    {
      std::cout << "type of *this = " 
                << typeid(*this).name() << '\n';

      std::cout << "type of U     = " 
                << typeid(U).name() << '\n';

      std::cout << '\n';
    }
  };

  int main()
  {
    Myclass<int> m1;
    Myclass<long> m2;

    // ---------------------------------------------------

    m1.foo(13.5);
    // output ->
    //  type of *this = class Myclass<int>
    //  type of U     = double

    // ---------------------------------------------------

    m1.foo(14);
    // output -> 
    // type of *this = class Myclass<int>
    // type of U     = int

    // ---------------------------------------------------

    m1.foo("hello");
    // output ->
    //  type of *this = class Myclass<int>
    //  type of U     = const char*

    // ---------------------------------------------------

    m2.foo(12L);
    // output->
    //  type of *this = class Myclass<long>
    //  type of U = long
    
    // ---------------------------------------------------
  }
*/

/*
  template <typename T>
  class Myclass {
  public:
    template <typename U>
    void foo(Myclass<U> x)
    {
      std::cout << "type of *this = " 
                << typeid(*this).name() << '\n';
      std::cout << "type of x = " 
                << typeid(x).name() << '\n';

      std::cout << '\n';
    }
  };

  int main()
  {
    Myclass<int> m1;
    Myclass<long> m2;

    m1.foo(m2);
    // output ->
    //  type of *this = class Myclass<int>
    //  type of x     = class Myclass<long>
  }
*/

/*
  struct Data {
    int m_a, m_b, m_c;
  };

  struct Data_2 {
  private:
    int m_a, m_b, m_c;
  };

  struct Data_3 {
    int m_arr[10];
  };

  int main()
  {
    // ---------------------------------------------------

    Data d1 = { 1, 2, 3 };  
    // aggregate initialization

    // ---------------------------------------------------

    Data_2 d2 = { 11, 22, 33 }; // syntax error
    // error: could not convert '{11, 22, 33}' from 
    // '<brace-enclosed initializer list ' to 'Data_2'

    // because of Data_2's data members are in 
    // private section Data_2 is not an aggregate class.
    // so aggregate initialization is not allowed.

    // ---------------------------------------------------

    Data_3 d3 = { 11, 22, 33, 44, 55, 66 };	
    // aggregate initialization

    for (int i = 0; i < 10; ++i)
      std::cout << d3.m_arr[i] << ' ';
    // output -> 11 22 33 44 55 66 0 0 0 0

    // ---------------------------------------------------
  }
*/

/*
  // std::array is an aggregate class

  #include <array>

  template <typename T, std::size_t N>
  struct Array {
    T m_arr[N];
  };

  int main()
  {
    std::array<int, 5> i_arr{ 1, 2, 3, 4, 5 };
    // aggregate initialization

    Array<int, 6> y{ 11, 22, 33, 44, 55, 66 };
    // aggregate initialization
  }
*/

// ------------------------------------------------------
// ------------------------------------------------------
// ------------------------------------------------------
// ------------------------------------------------------
// ------------------------------------------------------

/*
      <---- check not_related/std::pair class template ---->
*/

/*
          <---- check not_related/perfect forwarding ---->
*/

// ------------------------------------------------------
// ------------------------------------------------------
// ------------------------------------------------------
// ------------------------------------------------------
// ------------------------------------------------------

/*
                ---------------------------------
                | explicit(full) specialization |
                ---------------------------------
*/

/*
  template <typename T>
  void func(T x)
  {
    std::cout << "primary template\n";  
  }

  // explicit specialization for func<int> funcion template 
  template <>   
  void func(int x)
  {
    std::cout << "explicit specialization for func<int>\n";
  }

  int main()
  {
    func(2.4);    // output -> primary template
    func(3.5f);   // output -> primary template
    func(2u);     // output -> primary template
    func(12);     // output -> explicit specialization for func<int>
  }
*/

/*
  template <typename T>
  void func(T)
  {
    std::cout << "1";
  }

  // explicit specialization for func<int*> function template
  template <> 
  void func(int*)
  {
    std::cout << "2";
  }

  template <typename T>
  void func(T*)
  {
    std::cout << "3";
  }

  int main()
  {
    int x{ 5 };
    func(&x);   // output -> 3

    // "&x" argument's data type is int*
    // so function overload set will include 
    //  -> func(T)
    //  -> func(T*)

    // func(T*) will be chosen because it is more specific.
    // so explicit specialization for func<int*> function template
    // will not be in Function Overload Resolution Set.
  }
*/

/*
  template <typename T>
  void func(T)
  {
    std::cout << "1";
  }

  // explicit specialization for func<int*> function template
  // its primary template is func(T)
  template <> 
  void func(int*)
  {
    std::cout << "2";
  }

  template <typename T>
  void func(T*)
  {
    std::cout << "3";
  }

  // explicit specialization for func(int*) function template
  // its primary template is func(T*)
  template <>
  void func(int*)
  {
    std::cout << "4";
  }

  int main()
  {
    int x{ 5 };
    func(&x);   // output -> 4

    // "&x" argument's data type is int*
    // so function overload set will include
    //  -> func(T)
    //  -> func(T*)

    // because of func(T*) is more specific than func(T)
    // explicit specialization of func(int*) function template(4)
    // will also be in Function Overload Resolution Set.
    // and because of "&x"'s data type is int* 
    // explicit specialization for func(int*) function template
    // will be chosen.
  }
*/

/*
  // primary template for Myclass<T> class template
  template <typename T>
  class Myclass {
  public:
    Myclass()
    {
      std::cout << "primary template\n";
    }

    void foo()
    {
      std::cout << "Myclass<T>::foo()\n";
    }
  };

  // explicit specialization for Myclass<int> class template
  template <>
  class Myclass<int> {
  public:
    Myclass()
    {
      std::cout << "explicit specialization for Myclass<int>\n";
    }

    void bar()
    {
      std::cout << "Myclass<int>::bar()\n";
    }
  };

  int main()
  {
    // ---------------------------------------------------

    Myclass<char> m1;   
    // output -> primary template

    m1.foo();   // VALID
    m1.bar();   // syntax error
    // error: 'class Myclass<char>' has no member named 'bar'

    // ---------------------------------------------------

    Myclass<int> m2;    
    // output -> explicit specialization for Myclass<int>

    m2.foo();   // syntax error
    // error: 'class Myclass<int>' has no member named 'foo'
    m2.bar();   // VALID

    // ---------------------------------------------------
  }
*/

/*
  // primary template for Myclass<T, U> class template
  template <typename T, typename U>
  class Myclass {
  public:
    Myclass()
    {
      std::cout << "primary template\n";
    }
  };

  // explicit specialization for Myclass<int, char> class template
  template <>
  class Myclass<int, char> {
  public:
    Myclass()
    {
      std::cout << "Myclass<int,char> explicit specialization\n";
    }
  };

  int main()
  {
    Myclass<int, int> m1;   
    // output -> primary template
    Myclass<char, int> m2;  
    // output -> primary template
    Myclass<int, char> m3;
    // output -> Myclass<int, char> explicit specialization
  }
*/

/*
  // primary template for Myclass<N> class template
  template <int N>
  class Myclass {
  public:
    Myclass()
    {
      std::cout << "primary template, N = " << N << '\n';
    }
  };

  // explicit specialization for Myclass<5> class template
  template <>
  class Myclass<5> {
  public:
    Myclass()
    {
      std::cout << "Myclass<5> explicit specialization\n";
    }
  };

  int main()
  {
    Myclass<1> m1;  // output -> primary template, N = 1
    Myclass<3> m2;  // output -> primary template, N = 3
    Myclass<5> m3;  // output -> Myclass<5> explicit specialization
  }
*/

/*
  // primary template for Myclass<N> class template
  template <int N>
  struct Myclass : Myclass<N - 1> {
    Myclass()
    {
      std::cout << "N = " << N  << '\n';
    }
  };

  // explicit specialization for Myclass<0> class template
  // base case for stopping recursivity.
  template <>
  struct Myclass<0>{
    Myclass()
    {
      std::cout << "N = 0\n";
    }
  };

  int main()
  {
    Myclass<5> mx;  // compile-time recursivity
    // output ->
    //  N = 0
    //  N = 1
    //  N = 2
    //  N = 3
    //  N = 4
    //  N = 5

    // for Derived class object to become alive
    // base class object has to become alive first.

    // for Myclass<5> object to become alive
    // Myclass<4> object has to become alive first.
    // ...

    // Myclass<1> class will call Myclass<0> class's constructor
    // and Myclass<0> is NOT inherit from any class,
    // so recursion will stop. (base case)
  }
*/

/*
  // metafunction is a class template
  // its purpose is,
  // calculating a value or a type in compile time.

  // primary template for Factorial<N> class template
  template <int N>
  struct Factorial {
    static const int value = N * Factorial<N - 1>::value;
  };

  // explicit specialization for Factorial<1> class template
  template <>
  struct Factorial<1> {
    static const int value = 1;
  };

  // explicit specialization for Factorial<0> class template
  template <>
  struct Factorial<0> {
    static const int value = 1;
  };

  int main()
  {
    constexpr auto val1 = Factorial<12>::value;
    // val1 -> 479001600 (compile time calculation)
  }
*/

/*
  #include <string>

  template <typename T>
  T Max(T x, T y)
  {
    return x > y ? x : y;
  }

  int main()
  {
    // ---------------------------------------------------

    std::cout << Max(2, 3) << '\n';  // output -> 3
    std::cout << Max(3, 2) << '\n';  // output -> 3

    // ---------------------------------------------------

    std::string str_1{ "aaaa" }, str_2{ "bbbb" };

    std::cout << Max(str_1, str_2) << '\n'; 
    // output -> bbbb
    std::cout << Max(str_2, str_1) << '\n';
    // output -> bbbb

    // "bbbb" is greater than "aaaa" in lexicographical compare.

    // ---------------------------------------------------

    const char* p1{ "zzzz" };
    const char* p2{ "cccc" };

    std::cout << Max(p1, p2) << '\n'; 
    // output -> cccc

    std::printf("address of p1 = %p\n", (void*)p1);
    // output -> address of p1 = 00007ff77719c08c
    std::printf("address of p2 = %p\n", (void*)p2);
    // output -> address of p2 = 00007ff77719c08e

    // "zzzz" is greater than "cccc" in lexicographical compare.
    // but because of T will be deduced to const char* 
    // addresses that p1 and p2 are pointing to will be compared.

    // 00007ff77719c08e > 00007ff77719c08c

    // ---------------------------------------------------
  }
*/

/*
  #include <cstring>    // std::strcmp

  // primary template for Max<T> function template
  template <typename T>
  T Max(T x, T y)
  {
    return x > y ? x : y;
  }

  // explicit specialization for 
  // Max<const char*>(const char*, const char*) function template
  template <>
  const char* Max(const char* p1, const char* p2)
  {
    return std::strcmp(p1, p2) > 0 ? p1 : p2;
  }

  int main()
  {
    const char* p1{ "zzzz" };
    const char* p2{ "cccc" };

    std::cout << Max(p1, p2) << '\n';   // output -> zzzz
  }
*/

/*
                    --------------------------
                    | partial specialization |
                    --------------------------
*/

/*
  - partial specialization is VALID for class templates 
  - partial specialization is NOT VALID for function templates.
*/

/*
  // primary template for Myclass<T> class template
  template <typename T>
  class Myclass {
  public:
    Myclass()
    {
      std::cout << "primary template\n";
    }
  };

  // partial specialization for Myclass<T*> class template
  template <typename T>
  class Myclass<T*> {
  public:
    Myclass()
    {
      std::cout << "partial specialization for Myclass<T*>\n";
    }
  };

  template <typename T>
  class Myclass<T[]> {
  public:
    Myclass()
    {
      std::cout << "partial specialization for Myclass<T[]>\n";
    }
  };

  template <typename T>
  class Myclass<T[5]> {
  public:
    Myclass()
    {
      std::cout << "partial specialization for Myclass<T[5]>\n";
    }
  };

  int main()
  {
    Myclass<int> m1;    
    // output -> primary template
    Myclass<long> m2;   
    // output -> primary template
    Myclass<char*> m3;  
    // output -> partial specialization for Myclass<T*>
    Myclass<int**> m4;
    // output -> partial specialization for Myclass<T*>
    Myclass<int[]> m5;
    // output -> partial specialization for Myclass<T[]>
    Myclass<long[5]> m6;
    // output -> partial specialization for Myclass<T[5]>
  }
*/

/*
  // primary template for Myclass<T> class template
  template <typename T>
  struct Value_Category {
    static constexpr const char* p = "PR value";
  };

  // partial specialization for Myclass<T&> class template
  template <typename T>
  struct Value_Category<T&> {
    static constexpr const char* p = "L value";
  };

  // partial specialization for Myclass<T&&> class template
  template <typename T>
  struct Value_Category<T&&> {
    static constexpr const char* p = "X value";
  };

  int main()
  {
    using namespace std;

    // ---------------------------------------------------

    cout << Value_Category<int>::p << '\n';
    // output -> PR value
    cout << Value_Category<int&>::p << '\n';
    // output -> L value
    cout << Value_Category<int&&>::p << '\n';
    // output -> X value

    // ---------------------------------------------------

    int ival{};
    int* i_ptr = &ival;

    cout << Value_Category<decltype((12))>::p << '\n';  
    // output -> PR value
    cout << Value_Category<decltype((ival))>::p << '\n';
    // output -> L value    ((ival) is an expression)
    cout << Value_Category<decltype(i_ptr)>::p << '\n';
    // output -> PR value   (i_ptr is an identifier)
    cout << Value_Category<decltype(*i_ptr)>::p << '\n';
    // output -> L value    (*iptr is an expression)
    
    // ---------------------------------------------------
  }
*/

/*
  // primary template for Myclass<T, U> class template
  template <typename T, typename U>
  struct Myclass {
    Myclass()
    {
      std::cout << "primary template\n";
    }
  };

  // partial specialization for Myclass<T, T> class template
  template <typename T>
  struct Myclass<T, T> {
    Myclass()
    {
      std::cout << "partial specialization for Myclass<T,T>\n";
    }
  };

  // partial specialization for Myclass<T, T*> class template
  template <typename T>
  struct Myclass<T, T*> {
    Myclass()
    {
      std::cout << "partial specialization for Myclass<T, T*>\n";
    }
  };

  // partial specialization for Myclass<T*, T*> class template
  template <typename T>
  struct Myclass<T*, T*> {
    Myclass()
    {
      std::cout << "partial specialization for Myclass<T*, T*>\n";
    }
  };

  int main()
  {
    Myclass<int, double> m1;
    // output -> primary template
    Myclass<int, int> m2;
    // output -> partial specialization for Myclass<T, T>
    Myclass<int, int*> m3;
    // output -> partial specialization for Myclass<T, T*>
    Myclass<int*, int*> m4;
    // output -> partial specialization for Myclass<T*, T*>
  }
*/

/*
  #include <utility>  // std::pair
  #include <tuple>

  template <typename T>
  struct Myclass {
    Myclass()
    {
      std::cout << "primary template\n";
    }
  };

  template <typename T, typename U>
  struct Myclass<std::pair<T, U>> {
    Myclass()
    {
      using namespace std;
      cout << "partial specialization for Myclass<pair<T, U>>\n";
    }
  };

  template <typename T, typename U, typename K, typename L>
  struct Myclass<std::tuple<T, U, K, L>> {
    Myclass()
    {
      using namespace std;
      cout << 
        "partial specialization for Myclass<tuple<T, U, K, L>>\n";
    }
  };

  int main()
  {
    Myclass<int> m1;
    // output -> primary template
    Myclass<std::pair<int, long>> m2;
    // output -> partial specialization for Myclass<pair<T, U>>
    Myclass<std::tuple<int, long, char, int>> m3;
    // output -> partial specialization for Myclass<tuple<T, U, K, L>>
  }
*/

/*
  // primary template for Myclass<int, int> class template
  template <int Base, int Exp>
  struct Power {
    static const int value = Base * Power<Base, Exp - 1>::value;
  };

  // partial specialization for Myclass<int, 0> class template
  template <int Base>
  struct Power<Base, 0> {
    static const int value = 1;
  };

  int main()
  {
    constexpr auto val1 = Power<2, 4>::value; 
    // val1 -> 16 (compile-time calculation)
    constexpr auto val2 = Power<3, 9>::value;
    // val2 -> 19683 (compile-time calculation)
    constexpr auto val3 = Power<9, 5>::value;
    // val3 -> 59049 (compile-time calculation)
  }
*/

/*
  // std::vector class's bool specialization 
  // is a partial specialization

  #include <vector>

  int main()
  {
    std::vector<int> ivec;
    std::vector<bool> bvec;

    ivec.flip();	// syntax error
    // error: 'class std::vector<int>' has no member named 'flip'

    bvec.flip(); // VALID
  }
*/

/*
                        -------------------
                        | alias templates |
                        -------------------
*/

/*
            <---- check not-related/type-alias ---->
*/

/*
  template <typename T>
  using Ptr = T*;
  // `Ptr` is template identifier.
  // `Ptr<int>` is template specialization.

  template <typename T>
  using arr10 = T[10];

  template <typename T, int N>
  using arrN = T[N];

  int main()
  {
    // ---------------------------------------------------

    Ptr<int> p = nullptr;     // p's type is int*

    double dval{};
    Ptr<double> dp = &dval;   // dp's type is double*

    // ---------------------------------------------------

    arr10<int> i_arr;       // i_arr's type is int[10]
    arr10<double> d_arr;    // d_arr's type is double[10]

    // ---------------------------------------------------

    arrN<int, 20> i_arr20;    // i_arr20's type is int[20]
    arrN<char, 40> c_arr40;   // c_arr40's type is char[40]

    // ---------------------------------------------------
  }
*/

/*
  template <typename T>
  using i_pair = std::pair<T, int>;

  template <typename T>
  using eq_pair = std::pair<T, T>;

  int main()
  {
    // ---------------------------------------------------

    i_pair<long> i1;  // "i1"'s type is std::pair<long, int>
    i_pair<char> i2;  // "i2"'s type is std::pair<char, int>

    // ---------------------------------------------------

    eq_pair<long> e1; // "e1"'s type is std::pair<long, long>
    eq_pair<int> e2;  // "e2"'s type is std::pair<int, int>

    // ---------------------------------------------------
  }
*/

/*
  #include <set>
  #include <functional>   // std::greater, std::less

  template <typename T>
  using greater_set = std::set<T, std::greater<T>>;

  template <typename T>
  using less_set = std::set<T, std::less<T>>;

  int main()
  {
    greater_set<int> s1;
    // "s1"'s type is std::set<int, std::greater<int>>

    less_set<double> s2;
    // "s2"'s type is std::set<double, std::less<double>>
  }
*/

/*
  template <typename T>
  struct Myclass {
    using type = T*;
  };

  // alias template for "Myclass<T>::type" type 
  template <typename T>
  using Myclass_t = typename Myclass<T>::type;

  int main()
  {
    Myclass<int>::type i_ptr1;   // i_ptr1's type is int*
    Myclass_t<int> i_ptr2;       // i_ptr2's type is int*
  }
*/

/*
  #include <type_traits>  // std::add_pointer

  template <typename T>
  using AddPointer_t = typename std::add_pointer<T>::type;

  int main()
  {
    // ---------------------------------------------------

    std::add_pointer<int>::type i_ptr = nullptr;
    // i_ptr's type is int*

    std::add_pointer<double>::type d_ptr = nullptr;
    // d_ptr's type is double*

    // ---------------------------------------------------

    std::add_pointer_t<int> i_ptr2 = nullptr;
    // i_ptr2's type is int*

    std::add_pointer_t<double> d_ptr2 = nullptr;
    // d_ptr2's type is double*

    // ---------------------------------------------------

    AddPointer_t<int> i_ptr3 = nullptr;
    // i_ptr3's type is int*

    AddPointer_t<double> d_ptr3 = nullptr;
    // d_ptr3's type is double*
    // ---------------------------------------------------
  }
*/

/*
  #include <type_traits>  
  // std::is_same, std::integral_constant, std::bool_constant

  template <typename T, T N>
  struct Integral_Constant {
    constexpr T static value = N;
  };

  using TrueType  = Integral_Constant<bool, true>;
  using FalseType = Integral_Constant<bool, false>;

  int main()
  {
    // ---------------------------------------------------

    constexpr int val = std::integral_constant<int, 5>::value;
    // val -> 5 (compile-time calculation)

    constexpr int val2 = Integral_Constant<int, 5>::value;
    // val2 -> 5 (compile-time calculation)

    // ---------------------------------------------------

    constexpr bool b1 = Integral_Constant<bool, true>::value;
    // b1 -> true (compile-time calculation)

    constexpr bool b2 = Integral_Constant<bool, false>::value;
    // b2 -> false (compile-time calculation)

    // ---------------------------------------------------

    std::integral_constant<int, 5>::type ic_1;
    // "ic_1"'s type is std::integral_constant<int, 5>

    std::is_same_v<std::integral_constant<int, 5>, decltype(ic_1)>;
    // holds

    // ---------------------------------------------------

    using namespace std;

    std::true_type t;

    is_same_v<true_type, decltype(t)>;
    is_same_v<bool_constant<true>, true_type>;
    is_same_v<integral_constant<bool, true>, true_type>;

    std::false_type f;

    is_same_v<false_type, decltype(f)>;
    is_same_v<bool_constant<false>, false_type>;
    is_same_v<integral_constant<bool, false>, false_type>;    

    // ---------------------------------------------------
  }
*/

/*
  #include <type_traits>  // std::is_pointer

  // primary template for IsPointer<T> class template
  template <typename T>
  struct IsPointer : std::false_type {};

  // partial specialization for IsPointer<T*> class template
  template <typename T>
  struct IsPointer<T*> : std::true_type {};

  template <typename T>
  void func(T)
  {
    static_assert(IsPointer<T>::value);
  }

  int main()
  {
    // ---------------------------------------------------

    constexpr auto b1 = IsPointer<int>::value;
    // b1 -> false (compile-time calculation)

    // value is a static constexpr data member of 
    // std::false_type(base class when T is not pointer) 

    // ---------------------------------------------------

    constexpr auto b2 = IsPointer<int*>::value;
    // b2 -> true (compile-time calculation)

    // value is a static constexpr data member of
    // std::true_type(base class when T is pointer)

    // ---------------------------------------------------

    func(12);   // error: static assertion failed
    // note: 'std::integral_constant<bool, false>::value' 
    // evaluates to false

    // ---------------------------------------------------
    
    int x{};
    func(&x);   // VALID
    
    // ---------------------------------------------------
  }
*/

/*
  #include <type_traits> // std::is_lvlaue_reference

  template <typename T>
  struct Is_LValueReference : std::false_type {};

  // partial specialization for Is_LValueReference<T&> class template
  template <typename T>
  struct Is_LValueReference<T&> : std::true_type {};

  int main()
  {
    using namespace std;

    // ---------------------------------------------------

    // std::is_lvalue_reference is a meta function

    constexpr auto b2 = is_lvalue_reference<int>::value;
    // b2 -> false
    constexpr auto b1 = is_lvalue_reference<int&>::value;
    // b1 -> true
    constexpr auto b3 = is_lvalue_reference<int&&>::value;
    // b3 -> false

    // ---------------------------------------------------

    constexpr auto b4 = Is_LValueReference<int>::value;
    // b4 -> false

    // Is_LValueReference<int> is inherited from std::false_type
    // so Is_LValueReference<int>::value will be false.

    constexpr auto b5 = Is_LValueReference<int&>::value;
    // b5 -> true

    // Is_LValueReference<int&> is inherited from std::true_type
    // so Is_LValueReference<int&>::value will be true.

    // ---------------------------------------------------
  }
*/

/*
  #include <type_traits>

  // primary template for Is_LValueReference<T> class template
  template <typename T>
  struct Is_LValueReference : std::false_type {};

  // partial specialization for Is_LValueReference<T&> class template
  template <typename T>
  struct Is_LValueReference<T&> : std::true_type {};


  template <typename T>
  class LRefOnly_Class {
    static_assert(Is_LValueReference<T>::value, 
                  "only for L value reference types");
  };


  int main()
  {
    LRefOnly_Class<int> x1;
    // error: static assertion failed: 
    // only for L value reference types

    LRefOnly_Class<int&> x2;  // VALID
  }
*/

/*
  // type transformation meta-function 
  // std::remove_reference implementation

  #include <type_traits>  // std::remove_reference

  // template <typename T>
  // std::remove_reference_t<T> func(T);

  // primary template for Remove_Reference<T> class template
  template <typename T>
  struct Remove_Reference {
    using type = T;
  };

  // partial specialization for Remove_Reference<T&> class template
  template <typename T>
  struct Remove_Reference<T&> {
    using type = T;
  };

  // partial specialization for Remove_Reference<T&&> class template
  template <typename T>
  struct Remove_Reference<T&&> {
    using type = T;
  };

  // alias template for Remove_Reference<T>::type
  template<typename T>
  using Remove_Reference_t = typename Remove_Reference<T>::type;

  template <typename T>
  Remove_Reference_t<T> func(T);

  int main()
  {
    // ---------------------------------------------------

    Remove_Reference_t<int&> i1;  
    // i1's type is int
    Remove_Reference_t<int&&> i2; 
    // i2's type is int

    // ---------------------------------------------------

    int ival = 12;
    int& lref = ival;
    func(lref);  
    // T will be deduced to int&
    // Remove_Reference_t<int&>'s type is int
    // "func" functions return type will be int

    // ---------------------------------------------------

    int&& rref = 15;
    func(rref);
    // T will be deduced to int&&
    // Remove_Reference_t<int&&>'s type is int
    // "func" functions return type will be int

    // ---------------------------------------------------
  }
*/

/*
                  ------------------------------
                  | default template parameter |
                  ------------------------------
*/

/*
  // class template with default template parameter
  template <typename T = int>
  class Myclass {};

  int main()
  {
    Myclass<> m1;
    // T will be deduced to int
    Myclass<int> m2;
    // T's type is int
  }
*/

/*
  template <typename T = int, typename U> 
  class Myclass {};
  // syntax error -> error: no default argument for 'U'

  // after the last default template parameter,
  // there won't be any template parameter  
  // that is NOT a default template parameter.
*/

/*
  template <typename T = int, typename U = double>  
  class Myclass {};

  int main()
  {
    Myclass<char, char> m1;   
    // m1's type is Myclass<char, char>

    Myclass<char> m2;
    // m2's type is Myclass<char, double>

    Myclass<> m3;
    // m3's type is Myclass<int, double>
  }
*/

/*
  #include <type_traits>  // std::is_same

  template <typename T, typename = void>
  class Myclass {};

  int main()
  {
    Myclass<int> m1;
    Myclass<int, void> m2;

    std::is_same_v<decltype(m1), decltype(m2)>;
  }
*/

/*
  template <typename>
  class Myclass;  // incomplete type

  template <typename T>
  class Myclass<T*> {};

  int main()
  {
    Myclass<int> x;   // syntax error
    // error: aggregate 'Myclass<int> x' 
    // has incomplete type and cannot be defined

    Myclass<int*> y;  // VALID
  }
*/

/*
  template <typename T>
  void func(T&& x)  // universal reference
  {
    T&& y = x;
    // because of T's type is int&
    // y's type will be int&, (& - && -> &) reference collapsing
  }

  int main()
  {
    int ival{};
    func(ival);
    // "ival" is an L value 
    // T's type will be deduced to `int&`
    // x's type will become `int&` 
    // with reference collapsing(& - && -> &)
  }
*/

/*
                      ----------------------
                      | variable templates |
                      ----------------------
*/

/*
  template <typename T>
  constexpr auto pi = (T)3.14159265358979;
  // identification of template is pi

  int main()
  {
    pi<double>;   // template specialization
    // pi<double> specialization's type is double.
    // pi<double> is a constant expression.

    // ---------------------------------------------------

    int i_arr[pi<int>]{};
    int i_arr[3]{};
    // Those 2 lines are equivalent.

    // ---------------------------------------------------
  }
*/

/*
  #include <type_traits>

  // primary template for Is_LValueReference class template
  template <typename T>
  struct Is_LValueReference : std::false_type {};

  // partial specialization for 
  // Is_LValueReference<T&> class template
  template <typename T>
  struct Is_LValueReference<T&> : std::true_type {};


  // variable template for Is_LValueReference<T>::value
  template <typename T>
  constexpr bool Is_LValueReference_v = Is_LValueReference<T>::value;


  template <typename T>
  class LRefOnly_Class {
    static_assert(Is_LValueReference_v<T>, 
                  "only for L value ref types");
  };

  int main()
  {
    LRefOnly_Class<int> x1;  
    // error: static assertion failed: only for L value ref types

    LRefOnly_Class<int&> x2;  // VALID
  }
*/

/*
  #include <type_traits>  
  // std::is_pointer, std::is_reference

  template <typename T>
  void func(T x)
  {
    static_assert(std::is_pointer_v<T> || std::is_reference_v<T>, 
                  "only pointer or reference types are valid");
  }

  // std::is_pointer_v and std::is_reference_v are 
  // variable templates.
  
  int main()
  {
    func(12);
    // error: static assertion failed: 
    // only pointer or reference types are valid

    int ival{};
    func(&ival);  // VALID
  }
*/

/*
  #include <type_traits>  // std::enable_if, std::is_pointer

  // primary template for Enable_If<bool, T = void> class template
  template<bool b, typename T = void>
  struct Enable_If {};

  // partial specialization for Enable_If<true, T> class template
  template <typename T>
  struct Enable_If<true, T>
  {
    using type = T;
  };

  int main()
  {
    using namespace std;

    // ---------------------------------------------------

    Enable_If<true, double>::type d1;
    // d1's type is double

    Enable_If<true, char>::type c1;
    // c1's type is char

    Enable_If<false, char>::type c2;  // syntax error
    // error: 'type' is not a member of 'Enable_If<false, char>'

    // because of Enable_if<false, T> specialization
    // does not have ::type member
    // it will be syntax error.

    // ---------------------------------------------------

    Enable_If<is_pointer_v<int*>, double>::type d2;
    // d1's type is double
    // "is_pointer<int*>::value" member is true
    // "is_pointer_v<int*>" is true

    Enable_If<is_pointer_v<int>, double>::type d3;  // syntax error
    // error: 'type' is not a member of 'Enable_If<false, double>'

    // "is_pointer<int>::value" member is false
    // "is_pointer_v<int>" is false

    // because of Enable_if<false, T> specialization 
    // does not have ::type member
    // it will be syntax error.

    // ---------------------------------------------------

    std::enable_if<is_pointer_v<int*>>::type* vp = nullptr;
    // is_pointer_v<int*> is true
    // std::enable_if<true>::type is void type
    // because default template parameter is void

    // ---------------------------------------------------

    // std::enable_if_t is an alias template.

    std::enable_if<is_pointer_v<int*>,double>::type d4;
    std::enable_if_t<is_pointer_v<int*>,double> d5;
    // Those 2 lines are equivalent.

    // d5's type is double
    // d4's type is double

    // ---------------------------------------------------
  }
*/

/*
          -------------------------------------------------
          | SFINAE (Substitution Failure Is Not An Error) |
          -------------------------------------------------
*/

/*
  #include <type_traits>  // std::enable_if, std::is_pointer

  template <typename T>
  std::enable_if_t<std::is_pointer_v<T>> func(T x);
  // if T will be deduced to a pointer type
  // "std::enable_if_t<std::is_pointer_v<T>>" expression
  // will be void type.

  template <typename T>
  std::enable_if_t<std::is_pointer_v<T>,T> foo(T x);
  // if T will be deduced to a pointer type
  // "std::enable_if_t<std::is_pointer_v<T>,T>" expression
  // will be T type.

  void foo(double)
  {
    std::cout << "foo(double)\n";
  }

  int main()
  {
    // ---------------------------------------------------

    func(12); // syntax error
    // error: no matching function for call to 'func(int)'
    // error: no type named 'type' in 
    // 'struct std::enable_if<false, void>'

    //  T will be deduced to int
    // because of `int` is not a pointer type
    // std::enable_if<false, void>::type is not a valid type
    // so this function will be removed from Function Overload Set
    // (SFINAE'd out) 
    // and because of there is not any other overload
    // it will be syntax error.

    // ---------------------------------------------------

    foo(12);  // output -> foo(double)
    // T will be deduced to int
    // because of `int` is not a pointer type
    // "std::enable_if<false,int>::type" is not a valid type
    //  so this function will be removed from Function Overload Set
    // (SFINAE'd out)
    // and because of there is another overload
    // it will be chosen.

    // ---------------------------------------------------
  }
*/

/*
  #include <type_traits>  // std::enable_if, std::is_pointer

  template <typename T, 
            typename U = std::enable_if_t<std::is_pointer_v<T>>>
  void func(T x);

  int main()
  {
    // ---------------------------------------------------

    func(12);   // syntax error
    // error: no matching function for call to 'func(int)'
    // error: no type named 'type' in 
    // 'struct std::enable_if<false, void>'

    // T will be deduced to int
    // because of `int` is not a pointer type
    // std::enable_if_t<false, void> is not a valid type
    // "func" is SFINAE'd out
    
    // ---------------------------------------------------

    int ival{};
    func(&ival);  // VALID
    // T will be deduced to int*
    // because of `int*` is a pointer type
    // std::enable_if_t<true, void> is `void` type 
    // U will become `void` type (default template parameter)

    // ---------------------------------------------------
  }
*/

/*
  #include <type_traits>  // std::enable_if, std::is_pointer

  template <typename T>
  void func(T x, std::enable_if_t<std::is_pointer_v<T>>* = nullptr);

  // std::enable_if_t<std::is_pointer_v<T>> expression 
  // will be syntax error
  // or if not syntax error it will be void type

  int main()
  {
    // ---------------------------------------------------

    int x{};
    func(&x); // VALID
    // T will be deduced to int*
    // because of `int*` is a pointer type
    // std::enable_if_t<true> is `void` type
    // so functions signature will be
    // void func(int*, void* = nullptr);

    // ---------------------------------------------------

    func(10); // syntax error    
    // error: no matching function for call to 'func(int)'
    // error: no type named 'type' in 
    // 'struct std::enable_if<false, void>'

    // T will be deduced to int
    // because of `int` is not a pointer type
    // std::enable_if_t<false> is not a valid type
    // so this function will be removed from Function Overload Set
    // (SFINAE'd out)
    // and because of there is not any other overload
    // it will be syntax error.

    // ---------------------------------------------------
  }
*/

/*
  #include <type_traits>  // std::enable_if, std::is_integral

  template <typename T>
  std::enable_if_t<std::is_integral_v<T>> func(T x);

  int main()
  {
    // ---------------------------------------------------

    func(12.43);    // syntax error
    // error: no matching function for call to 'func(double)'
    // error: no type named 'type' in 
    // 'struct std::enable_if<false, void>'

    // T will be deduced to double
    // because of `double` is not an integral type
    // std::enable_if_t<false> is not a valid type
    // so this function will be removed from Function Overload Set
    // (SFINAE'd out)
    // and because of there is not any other overload
    // it will be syntax error.

    // ---------------------------------------------------

    func(12);       // VALID
    // T will be deduced to int
    // because of `int` is an integral type
    // std::enable_if_t<true> is `void` type

    func(true);     // VALID
    // T will be deduced to bool
    // because of `bool` is an integral type
    // std::enable_if_t<true> is `void` type

    func('a');      // VALID
    // T will be deduced to char
    // because of `char` is an integral type
    // std::enable_if_t<true> is `void` type

    // ---------------------------------------------------
  }
*/

/*
  #include <type_traits>  // std::is_same

  // primary template for Is_Same<T, U> class template
  template <typename T, typename U>
  struct Is_Same : std::false_type {};

  // partial specialization for Is_Same<T, T> class template
  template <typename T>
  struct Is_Same<T, T> : std::true_type{};

  // variable template for Is_Same<T, U>::value
  template <typename T, typename U>
  constexpr bool Is_Same_v = Is_Same<T, U>::value;

  template <typename T>
  void func(T)
  {
    static_assert(std::is_same_v<T, int>);
  }

  int main()
  {
    // ---------------------------------------------------

    func(1.23); // syntax error
    // error: static assertion failed
    // note: 'std::is_same_v<double, int>' evaluates to false

    // T will be deduced to double

    // ---------------------------------------------------

    func(12);   // VALID
    // T will be deduced to int

    // ---------------------------------------------------

    constexpr bool b1 = Is_Same_v<int,double>;
    // b1 -> false

    constexpr bool b2 = Is_Same_v<int, int>;
    // b2 -> true

    // ---------------------------------------------------
  }
*/

/*
                      ----------------------
                      | variadic templates |
                      ----------------------
*/

/*
  // template type parameter pack
  template <typename ...Ts>
  class Myclass {};

  int main()
  {
    Myclass<int> m1;                // VALID
    Myclass<long, double> m2;       // VALID
    Myclass<int, double, int> m3;   // VALID
  }
*/

/*
  template <typename ...Ts>
  void func(Ts... args);   // pack expansion

  template <typename T, typename U, typename W>
  void func(T t, U u, W w);

  int main()
  {
    func(12, 34L, 4.5);
    // for "func(12, 34L, 4.5)" statement
    // both func functions are equivalent.
  }
*/

/*
  // 1'st template parameter is type parameter
  // 2'nd template parameter is type parameter pack
  template <typename T, typename ...Ts>
  void func(T x, Ts... args);

  int main()
  {
    func(12, 34L, 4.5);
    // T will be deduced to int (12)
    // Ts... will be deduced to long, double (34L, 4.5)
  }
*/

/*
  #include <cstddef>  // std::size_t

  class Myclass {
  private:
    int m_x, m_y;
  };

  template <typename ...Ts>
  void func(Ts... args)
  {
    constexpr std::size_t x = sizeof...(args);
    constexpr std::size_t y = sizeof...(Ts);

    std::cout << "sizeof...(args) = " << x << '\n';
    std::cout << "sizeof...(Ts) = " << y << '\n';
  }

  int main()
  {
    func(12, 34L, 4.5, Myclass{});
    // output ->
    //  sizeof...(args) = 4
    //  sizeof...(Ts) = 4

    func(12, "hello");
    // output ->
    //  sizeof...(args) = 2
    //  sizeof...(Ts) = 2

    func();
    // output ->
    //  sizeof...(args) = 0
    //  sizeof...(Ts) = 0
  }
*/

/*
  // 1'st template parameter is type parameter
  // 2'nd template parameter is type parameter pack
  template <typename T, typename ...Ts>
  void func(T t, Ts... args)
  {
    constexpr std::size_t x = sizeof...(args);
    constexpr std::size_t y = sizeof...(Ts);

    std::cout << "sizeof...(args) = " << x << '\n';
    std::cout << "sizeof...(Ts) = " << y << '\n';
  }

  int main()
  {
    func(12, 34L, 4.5);
    // output ->
    //	sizeof...(args) = 2
    //	sizeof...(Ts) = 2

    // T will be deduced to int (12)
    // Ts... will be deduced to long, double (34L, 4.5)
  }
*/

/*
  template <typename ...Ts>
  void func(Ts ...args);

  int main()
  {
    func<int, long, double>('a', 34L, 4.5f);
    // explicit template argument declaration.

    // 'a' will be implicitly converted to int
    // 4.5f will be implicitly converted to double
  }
*/

/*
  #include <string>

  template <typename ...Ts>
  void func(Ts&... args);

  int main()
  {
    int ival{};
    double dval{};
    std::string str{ "hello" };

    func(ival, dval, str);
    // Ts... will be deduced to int, double, std::string
    // functions parameters will be int&, double&, std::string&
  }
*/

/*
  #include <string>

  template <typename ...Ts>
  void func(Ts&&... args);
  // universal(forwarding) reference parameter pack

  template <typename T, typename U, typename W>
  void func(T&& t, U&& u, W&& w );

  int main()
  {
    int ival{};
    double dval{};
    std::string str{ "hello" };

    func(ival, dval, str);
    // Ts... will be deduced to int, double, std::string
    // functions parameters will be int&&, double&&, std::string&&

    // both "func" functions are equivalent.
  }
*/

/*
  #include <tuple>

  // std::tuple class template have 
  // a variadic type parameter pack

  template <typename ...Ts>
  class Tuple {};

  int main()
  {
    Tuple<int> t1;                    // VALID
    Tuple<int, double> t2;            // VALID
    Tuple<int, int, long> t3;         // VALID

    std::tuple<int> st1;              
    std::tuple<int, double> st2;
    std::tuple<int, int, long> st3;
  }
*/

/*
  // non-type template parameter pack
  template <int ...N>
  class Myclass {};

  int main()
  {
    Myclass<1> m1;          // VALID
    Myclass<1, 3> m2;       // VALID  
    Myclass<1, 3, 5, 8> m3; // VALID
  }
*/

/*
                        ------------------
                        | pack expansion |
                        ------------------
*/

/*
  void foo(int a, double b, long c)
  {
    std::cout << "a = " << a << '\n';
    std::cout << "b = " << b << '\n';
    std::cout << "c = " << c << '\n';
  }

  template <typename ...Ts>
  void func(Ts ...args)
  {
    foo(args...);   // pack expansion
    // foo(p1, p2, p3);
  }

  template <typename T, typename U, typename W>
  void bar(T t, U u, W w)
  {
    foo(t, u, w);
  }

  int main()
  {
    func(12, 26.3, 75L);
    // output ->
    //  a = 12
    //  b = 26.3
    //  c = 75

    bar(12, 26.3, 75L);
    // output ->
    //  a = 12
    //  b = 26.3
    //  c = 75

    // "func" and "bar" functions are equivalent.
  }
*/

/*
  template <typename ...Ts>
  void func(Ts... args)
  {
    int i_arr[] = { args... };  // pack expansion
    // int i_arr[] = { p1, p2, p3, p4 };

    for (auto val : i_arr)
      std::cout << val << ' ';
  }

  int main()
  {
    func(1, 2, 7, 8); // output -> 1 2 7 8
  }
*/

/*
  void foo(int x, int y, int z)
  {
    std::cout << "x = " << x << '\n';
    std::cout << "y = " << y << '\n';
    std::cout << "z = " << z << '\n';
  }

  template <typename ...Ts>
  void func(Ts&... args)
  {
    foo(++args...);  // pack expansion
    // foo(++p1, ++p2, ++p3);
  }

  int main()
  {
    int x = 10, y = 15, z = 20;

    func(x, y, z);
    // output ->
    //  x = 11
    //  y = 16
    //  z = 21
  }
*/

/*
  #include <tuple>

  template <typename ...Ts>
  void func(Ts... args)
  {
    std::tuple<Ts...> t1; // pack expansion
    // std::tuple<int, int, int, int> t1;

    std::cout << typeid(x).name() << '\n';
  }

  int main()
  {
    func(1, 4, 3, 6);
    // output -> 
    //  class std::tuple<int, int, int, int>

    func(1, 4.2, 3L, 6.f, "hello");
    // output -> 
    //  class std::tuple<int, double, long, float, const char*>
  }
*/

/*
  #include <tuple>

  template <typename ...Ts>
  void func(Ts... args)
  {
    std::tuple<Ts...> t1(args...); // pack expansion
    // std::tuple<int, int, int> t1(p1, p2, p3);

    // pack expansion for both 
    //  explicit template arguments
    //  function arguments
  }

  int main()
  {
    func(1, 4, 3);
  }
*/

/*
  #include <tuple>

  template <typename ...Ts>
  void bar(Ts...)
  {
    std::tuple<Ts...> t1;  // pack expansion
    // std::tuple<int*, double*, float*> t1;

  }

  template <typename ...Ts>
  void func(Ts... args)
  {
    bar(&args...);  // pack expansion
    // bar(&p1, &p2, &p3);
  }

  int main()
  {
    func(1, 4.5, 6.f);
  }
*/

/*
  template <typename ...Ts>
  void bar(Ts... args)
  {
    std::cout << "sizeof...(args) = " 
              << sizeof...(args) << '\n';
  }

  template <typename ...Ts>
  void func(Ts... args)
  {
    bar(args...);  // pack expansion 
    // bar(p1, p2, p3);
  }

  int main()
  {
    func(1, 2.3, 6L, 6.5f); // output -> sizeof...(args) = 4
  }
*/

/*
  template <typename ...Ts>
  void foo(Ts... args)
  {
    std::cout << "sizeof...(args) = " 
              << sizeof...(args) << '\n';
  }

  template <typename ...Ts>
  void func(Ts... args)
  {
    foo<Ts...>(args...);  // pack expansion
    // foo<int, double, long, float>(p1, p2, p3, p4);

    // pack expansion for both
    //  explicit template arguments
    //  and function arguments
  }

  int main()
  {
    func(1, 2.3, 6L, 6.5f);
    // output -> sizeof...(args) = 4
  }
*/

/*
  #include <memory>   // std::unique_ptr
  #include <utility>  // std::forward

  template <typename ...Ts>
  class Myclass {
  public:
    Myclass(Ts... args)
    {
      std::cout << sizeof...(args) << '\n';
    }
  };

  template <typename T, typename ...Ts>
  std::unique_ptr<T> Make_Unique(Ts&&... args)
  {
    return std::unique_ptr<T>(new T(std::forward<Ts>(args)...));
    
    // unique_ptr<Myclass>(new Myclass( forward<int>(p1), 
                                        forward<int>(p2), 
                                        forward<int>(p3));
  }

  int main()
  {
    auto p = Make_Unique<Myclass<int, int>>(1, 2);
    // output -> 2

    auto p1 = std::make_unique<Myclass<int, int, int>>(1, 2, 3);
    // output -> 3

    // perfect forwarding function arguments to Myclass's ctor 
  }
*/

/*
  // ---------------- C variadic function ----------------
 
  #include <stdarg.h>
  #include <stdio.h>

  int sum(int N, ...)
  {
    va_list args;
    va_start(args, N);

    int sum = 0;

    for (int i = 0; i < N; ++i)
    {
      sum += va_arg(args, int);
    }

    va_end(args);

    return sum;
  }

  int main()
  {
    printf("%d\n", sum(4, 1, 5, 7, 9));
  }

  // Disadvantages
  // ------------------
  // - no type safety 
  //    when double argument is passed to sum function
  //    it will cause Undefined Behaviour(UB).
  // - number of arguments must be passed to sum function
*/

/*
  #include <cstddef>  // std::size_t
  #include <typeinfo> // typeid

  template <typename ...Ts>
  class AClass {
  public:
    AClass()
    {
      std::cout << typeid(*this).name() << '\n';
      std::cout << typeid(AClass).name() << '\n';
    }
  };

  template <typename ...Types>
  class Myclass : public AClass<Types...> {
  public:
    constexpr static std::size_t ms_size = sizeof...(Types);
  };

  int main()
  {
    // ---------------------------------------------------

    Myclass<int, double, long> mx;
    // output ->
    //  class AClass<int, double, long>
    //  class AClass<int, double, long>

    // class Myclass<int, double, long> specialization
    // will public inherit from AClass<int, double, long>


    constexpr auto val1 = Myclass<int, double, long>::ms_size;
    // val1 -> 3u  (compile time constant)

    // ---------------------------------------------------

    constexpr auto val2 = Myclass<int, double>::ms_size;
    // val2 -> 2u (compile time constant)

    // class Myclass<int, double> specialization
    // will public inherit from AClass<int, double>

    // ---------------------------------------------------
  }
*/

/*
  #include <cstddef>  // std::size_t
  #include <typeinfo> // typeid

  template <typename ...Ts>
  class AClass {
  public:
    AClass()
    {
      std::cout << typeid(*this).name() << '\n';
    }
  };

  template <typename ...Types>
  class Myclass : public AClass<Types*...> {
  public:
    constexpr static std::size_t ms_size = sizeof...(Types);
  };

  int main()
  {
    Myclass<int, long, double> mx;
    // output -> class AClass<int*, long*, double*>

    constexpr auto val1 = Myclass<int, long, double>::ms_size;
    // val1 -> 3u  (compile time constant)

    // Myclass<int, long, double> specialization
    // will public inherit from AClass<int*, long*, double*>
  }
*/

/*
  struct XStruct {
    XStruct(int i)
    {
      std::cout << "XStruct(int i), i = " << i << '\n';
    }
  };

  struct YStruct {
    YStruct(int i)
    {
      std::cout << "YStruct(int i), i = " << i << '\n';
    }
  };

  struct ZStruct {
    ZStruct(int i)
    {
      std::cout << "ZStruct(int i), i = " << i << '\n';
    }
  };

  template <typename ...Types>
  class AClass : public Types... {
  public:
    AClass() : Types{ 11 }... {}
  };

  class BClass : public XStruct, YStruct, ZStruct {
  public:
    BClass() : XStruct{ 22 }, YStruct{ 22 }, ZStruct{ 22 } {}
  };

  int main()
  {
    // ---------------------------------------------------

    AClass<XStruct, YStruct, ZStruct> ax;
    // output ->
    //  XStruct(int i), i = 11
    //  YStruct(int i), i = 11
    //  ZStruct(int i), i = 11

    // AClass<XStruct, YStruct, ZStruct> specialization
    // will public inherit from XStruct, YStruct, ZStruct

    // multiple inheritance
    // AClass<XStruct, YStruct, ZStruct> 
    //  : public XStruct, public YStruct, public ZStruct

    // ---------------------------------------------------

    BClass bx;
    // output ->
    //  XStruct(int i), i = 22
    //  YStruct(int i), i = 22
    //  ZStruct(int i), i = 22

    // ---------------------------------------------------
  }
*/

/*
  #include <tuple>

  template <typename T>
  void print_type(const T&)
  {
    std::cout << typeid(T).name() << '\n';
  }

  template <class A, class B, class ...Ts>
  void func(A arg1, B arg2, Ts... args)
  {
    std::tuple <A, B, Ts...> t1;
    print_type(t1);
    // output -> 
    //  class std::tuple<int, float, double, long, char>

    std::tuple<Ts..., A, B> t2;
    print_type(t2);
    // output ->
    // class std::tuple<double, long, char, int, float>

    std::tuple<A, Ts..., B> t3;
    print_type(t3);
    // output ->
    // class std::tuple<int, double, long, char, float>
  }

  int main()
  {
    func(1, 1.2f, 3.4, 4L, 'A');
    // A will be deduced to int
    // B will be deduced to float
    // Ts... will be deduced to double, long, char
  }
*/

/*
  #include <cstddef>  // std::size_t
  #include <typeinfo> // typeid

  // non-type template parameter pack
  template <std::size_t ...Ns>
  struct AStruct {
    AStruct()
    {
      std::cout << typeid(AStruct).name() << '\n';
    }
  };

  // non-type template parameter pack
  template <std::size_t ...Ns>
  void func()
  {
    AStruct<Ns...> ax;
  }

  int main()
  {
    func<1, 3, 7, 9>();
    // output -> struct AStruct<1, 3, 7, 9>
  }
*/

/*
  #include <type_traits>  // std::is_same

  template <typename T>
  void foo(T)
  {
    static_assert(std::is_same_v<T, int*>);
  }

  template <typename T>
  void func(T&)
  {
    static_assert(std::is_same_v<T,  int[10]>);
    static_assert(std::is_same_v<T&, int(&)[10]>);
  }

  int main()
  {
    int i_arr[10]{};

    foo(i_arr);   // holds -> array decay will be applied (T)
    func(i_arr);  // holds -> array decay will NOT be applied (T&)
  }
*/

/*
  template <typename ...TS>
  void func(int, TS...){}

  // template <>
  // void func<double, const char*>(int, double, const char*)
  // {
  //   std::cout << "1";
  // }

  int main()
  {
    func(1, 3.4, "hello");
    // func<double, const char*>(int, double, const char*)
    // specialization
  }
*/

/*
  template <typename... Types, int... N>
  void func(Types(&...args)[N]){}

  int main()
  {
    int i_arr[2]{};
    char c_arr[3]{};
    long l_arr[5]{};
    double d_arr[7]{};

    func(i_arr, c_arr, l_arr, d_arr);

    // func<int, char, long, double, 2, 3, 5, 7>
    //    (int(&)[2], char(&)[3], long(&)[5], double(&)[7])
  }
*/

/*
        -----------------------------------------------
        | compile-time recursivity (eksiltme teknigi) |
        -----------------------------------------------
*/

/*
  HOW TO USE VARIADIC TEMPLATE PARAMETERS ONE BY ONE?
  ----------------------------------------------------
  1. compile-time recursivity (eksiltme teknigi)
  2. init_list
  3. fold expressions	(katlama ifadeleri)	[C++17]
  4. static if	[C++17]
*/

/*
  #include <bitset>
  #include <string>

  template <typename T>
  void print(const T& elem)
  {
    std::cout << "print(const T& elem), elem = " << elem << '\n';
  }

  template <typename T, typename ...Ts>
  void print(const T& first, const Ts&... rest)
  {
    std::cout << "print(const T& first, const Ts&... rest), ";
    std::cout << sizeof...(rest) << '\n';

    print(first);
    print(rest...);
  }

  int main()
  {
    int ival = 11;
    double dval = 22.22;
    std::string str{ "universe" };

    print(str, ival, dval, 9L, "galaxy", std::bitset<16>(45u));
    // output ->
    //  print(const T& first, const Ts&... rest), 5
    //  print(const T& elem), elem = universe
    //  print(const T& first, const Ts&... rest), 4
    //  print(const T& elem), elem = 11
    //  print(const T& first, const Ts&... rest), 3
    //  print(const T& elem), elem = 22.22
    //  print(const T& first, const Ts&... rest), 2
    //  print(const T& elem), elem = 9
    //  print(const T& first, const Ts&... rest), 1
    //  print(const T& elem), elem = galaxy
    //  print(const T& elem), elem = 0000000000101101
  }
*/

/*
  #include <string>

  template <typename T>
  T sum(const T& elem)
  {
    return elem;
  }

  template <typename T, typename ...Ts>
  T sum(const T& first, const Ts&... rest)
  {
    return first + sum(rest...);
  }

  int main()
  {
    std::cout << sum(1, 3, 5, 7, 9) << '\n';  
    // output -> 25

    std::string s1{"h"}, s2{"e"}, s3{"l"}, s4{"o"};
    std::cout << sum(s1, s2, s3, s3, s4) << '\n'; 
    // output -> hello
  }
*/

/*
              -----------------------------------
              | std::initializer_list technique |
              -----------------------------------
*/

/*
  // comma operator is creating a sequence point,
  // so side effect will be applied
  // comma operator is left associative
  // comma operator will generate rightmost operands value.

  int main()
  {
    // ------------------------------------------------------
    int i_arr1[]{ 1, 2, 3, 4, 5 };
    std::cout << sizeof(i_arr1) << '\n';
    // output -> 20 (5 * sizeof(int))

    int i_arr2{ (1, 2, 3, 4, 5) };
    std::cout << sizeof(i_arr2) << '\n';
    // output -> 4 (1 * sizeof(int))

    // ------------------------------------------------------

    int x = 10;
    int y = 20;
    int z{};

    x++, y = ++x , z = x + y;

    std::cout << "x = " << x << '\n'; // output -> x = 12
    std::cout << "y = " << y << '\n'; // output -> y = 12
    std::cout << "z = " << z << '\n'; // output -> z = 24

    // ------------------------------------------------------

    int a = 10;
    int b = 33;
    int c{};

    c = (a, b);
    std::cout << "c = " << c << '\n'; // output -> c = 33
    c = (b, a);
    std::cout << "c = " << c << '\n'; // output -> c = 10

    // ------------------------------------------------------
  }
*/

/*
  template <typename ...Ts>
  void print(const Ts&... args)
  {
    int i_arr[] = { ((std::cout << args << '\n'), 0)... };
    // pack expansion

    // int i_arr[] = { (std::cout << p1 << '\n'), 0),
    //                 (std::cout << p2 << '\n'), 0),
    //                 (std::cout << p3 << '\n'), 0)};
    // int i_arr = { 0, 0, 0 };
  }

  int main()
  {
    print(2, 3.4, 7L, "hello");
    // output ->
    //  2
    //  3.4
    //  7
    //  hello
  }
*/

/*
  #include <initializer_list> 

  template <typename ...Ts>
  void print(const Ts&... args)
  {
    // instead of using C style array 
    // better using temporary std::initializer_list variable
    // cast to void to avoid warning for unused variable

    (void)std::initializer_list<int> { 
      ((std::cout << args << '\n'), 0)... };
    // pack expansion

    // initializer_list<int>{ (std::cout << p1 << '\n'), 0),
    //                        (std::cout << p2 << '\n'), 0),
    //                        (std::cout << p3 << '\n'), 0)};
    // std:;initializer_list<int>{ 0, 0, 0 };
  }

  int main()
  {
    print(2, 3.4, 7L, "hello");
    // output ->
    //  2
    //  3.4
    //  7
    //  hello
  }
*/

/*
                  ----------------------------
                  | fold expressions (C++17) |
                  ----------------------------
*/

/*
  // unary left fold
  template <typename ...Ts>
  auto sum_unary_left_fold(const Ts&... args)
  {
    return (... + args);
    // return (((p1 + p2) + p3) + p4) + p5
    // left associative
  }

  // unary right fold
  template <typename ...Ts>
  auto sum_unary_right_fold(const Ts&... args)
  {
    return (args + ...);
    // return p1 + (p2 + (p3 + (p4 + p5)))
    // right associative
  }

  int main()
  {
    std::cout << sum_unary_left_fold(1, 3, 5, 7, 9, 11) << '\n';  
    // output -> 36
    std::cout << sum_unary_right_fold(1, 3, 5, 7, 9, 11) << '\n';
    // output -> 36
  }
*/

/*
  // unary left fold
  template <typename ...Ts>
  auto sum_left(Ts... args)
  { 
    return (... + args); 
  }

  // unary right fold
  template <typename ...Ts>
  auto sum_right(Ts... args)
  { 
    return (args + ...); 
  }

  int main()
  { 
    // ---------------------------------------------------

    using namespace std::literals;

    // std::string + const char* -> std::string
    // const char* + std::string -> std::string

    // const char* + const char* -> syntax error 
    // pointer + pointer is syntax error

    // ---------------------------------------------------

    auto s1 = sum_left("hello"s, " world ", "galaxy ", "universe");
    std::cout << s1 << '\n';
    // output -> hello world galaxy universe

    // ((std::string + const char*) + const char*) + const char*
    // (std::string + const char*) + const char*
    // std::string + const char*
    // std::string 

    static_assert(std::is_same_v<decltype(s1), std::string>);

    // ---------------------------------------------------

    auto s2 = sum_right("hello", " world", " galaxy ", "universe"s);
    std::cout << s2 << '\n';
    // output -> hello world galaxy universe

    // const char* + (const char* + (const char* + std::string))
    // const char* + (const char* + std::string)
    // const char* + std::string
    // std::string

    static_assert(std::is_same_v<decltype(s2), std::string>);

    // ---------------------------------------------------

    auto s3 = sum_left("hello", " world ", "galaxy ", "universe"s);
    // syntax error
    // error: invalid operands of types 'const char*' 
    // and 'const char*' to binary 'operator+'

    // ((const char* + const char*) + const char*) + std::string 
    // --> syntax error

    // ---------------------------------------------------
  }
*/

/*
  void func(int i)
  {
    std::cout << "func(i), i = " << i << '\n';
  }

  // unary left fold for comma operator(',')
  template <typename ...Ts>
  void call_func(Ts... args)
  {
    (func(args), ...);
    // func(p1), (func(p2), (func(p3), (func(p4), func(p5))))
  }

  int main()
  {
    call_func(1, 2, 3, 4, 5, 6);
    // output ->
    //  func(i), i = 1
    //  func(i), i = 2
    //  func(i), i = 3
    //  func(i), i = 4
    //  func(i), i = 5
    //  func(i), i = 6
  }
*/


/*
  // unary left fold for logical and operator('&&')
  template <typename ...Ts>
  bool logical_and(Ts... args)
  {
    return (... && args);
  }

  int main()
  {
    std::cout << std::boolalpha;

    std::cout << logical_and(true, true, true, true) << '\n';
    // output -> true
    // (((true && true) && true) && true

    std::cout << logical_and(true, true, true, false) << '\n';  
    // output -> false
    // (((true && true) && true) && false
  }
*/

/*
  // unary right fold for ('/') operator
  template <typename ...Args>
  auto fdiv_right(Args&&... args)
  {
    return (args / ...);
  }

  // unary left fold for ('/') operator
  template <typename ...Args>
  auto fdiv_left(Args&&... args)
  {
    return (... / args);
  }

  int main()
  {
    // ---------------------------------------------------    

    std::cout << fdiv_right(500, 50, 5, 2) << '\n'; 
    // output -> 20
    // 500 / (50 / (5 / 2))
    // 500 / (50 / 2)
    // 500 / 25
    // 20

    // ---------------------------------------------------    

    std::cout << fdiv_left(500, 50, 5, 2) << '\n';
    // output -> 1

    // ((500 / 50) / 5) / 2;
    // (10 / 5) / 2;
    // 2 / 2;
    // 1

    // ---------------------------------------------------    
  }
*/

/*
  // binary left fold for ('+') operator
  template <typename T, typename ...TS>
  auto sum(T init, TS... args)
  {
    return (init + ... + args);
  }

  int main()
  {
    int ival = 100;

    std::cout << sum(ival, 1, 3, 5, 6);
    // output -> 115

    // (((ival + 1) + 3) + 5) + 6
  }
*/

/*
  // binary left fold for ('-') operator
  template <typename... Ts>
  int substract(int init, Ts... args)
  {
    return (init - ... - args); 
  }

  int main()
  {
    std::cout << substract(100, 50, 20, 7) << '\n';
    // output -> 23

    // ((100 - 50) - 20) - 7
  }
*/

/*
  #include <bitset>
  #include <string>
  #include <utility>    // std::forward

  // binary left fold for ('<<') operator
  template <typename ...Args>
  void fprintf(Args&&... args)
  {
    (std::cout << ... << std::forward<Args>(args)) << '\n';

    // init (op) ... (op) pack -> binary left fold
    // init -> std::cout 
    // op   -> ('<<')

    // (((std::cout << p1) << p2) << p3) << p4
  }

  int main()
  {
    std::string str{ "hello" };
    std::bitset<8> bs{ 15u };

    fprintf(str, 12, 4.5, "world", bs);
    // output -> hello124.5world00001111
  }
*/

/*
  // binary right fold for ('+') operator
  template <typename ...Args>
  auto sum(Args&&... args)
  {
    return (std::forward<Args>(args) + ... + 10);
  }

  int main()
  {
    std::cout << sum(12, 4.5, 50L) << '\n'; 
    // output -> 76.5

    // 12 + (4.5 + (50L + 10))
  }
*/

/*  
                    ---------------------
                    | static if (C++17) |
                    ---------------------
*/

/*
  template <typename T>
  void func(T x)
  {
    if constexpr (expr){
      // code;
    }

    // expr needs to be a `constant expression`
  }
*/

/*
  template <typename T>
  void func(T x)
  {
    if constexpr (sizeof(T) > 4)
      ++x;
  }

  struct AStruct {};

  struct BStruct {
    int m_i1, m_i2;  
  };

  int main()
  {
    // ---------------------------------------------------

    func(AStruct{});
    // T will be deduce to `struct AStruct`
    // because of sizeof(AStruct) is 1 byte
    // "sizeof(T) > 4" constant expression will be false
    // and compiler will not generate if block.
    // func will be an empty function.

    // ---------------------------------------------------

    func(BStruct{});  // syntax error
    // error: no match for 'operator++' (operand type is 'BStruct')

    // T will be deduce to `struct BStruct`
    // because of sizeof(BStruct) is 8 byte
    // "sizeof(T) > 4" constant expression will be true
    // and compiler will generate if block.
    // but there is no operator++ overload in BStruct
    // so this code will be a syntax error.

    // ---------------------------------------------------
  }
*/

/*
  #include <type_traits>  // std::is_integral

  template <typename T>
  void func(T x)
  {
    if constexpr (std::is_integral_v<T>)
      ++x;
    else 
      x.foo();
  }

  int main()
  {
    // ---------------------------------------------------

    func(12);
    // T will be deduced to int
    // "std::integral_v<int>" constant expression will be true
    // so compiler will generate if block.
    // "++x" expression is valid for `int` type.

    // ---------------------------------------------------

    func(11.22);  // syntax error
    // error: request for member 'foo' in 'x', 
    // which is of non-class type 'double'

    // T will be deduced to double
    // "std::integral_v<double>" constant expression will be false
    // so compiler will generate else block.
    // "x.foo()" expression is invalid for `double` type.
    // so this code will be a syntax error.

    // ---------------------------------------------------
  }
*/

/*
  #include <type_traits>  // std::is_integral

  template <typename T>
  void func(T x)
  {
    if constexpr (std::is_integral_v<T>)
      ++x;
    else if constexpr (sizeof(T) > 4)
      --x;
  }
*/

/*
  #include <string>
  #include <type_traits>  // std::is_same, std::is_arithmetic

  template <typename T>
  std::string as_string(T x)
  {
    if constexpr (std::is_same_v<T, std::string>) 
      return x;
    else if constexpr (std::is_arithmetic_v<T>) 
      return std::to_string(x);
    else 
      return std::string(x);
  }

  int main()
  {
    // ---------------------------------------------------

    std::cout << as_string(42) << '\n'; 
    // output -> 42
    // T will be deduced to int
    // compiler will write else if block

    // ---------------------------------------------------

    std::cout << as_string(4.2) << '\n';
    // output -> 4.2
    // T will be deduced to double
    // compiler will write else if block

    // ---------------------------------------------------

    std::cout << as_string(std::string("hello")) << '\n';
    // T will be deduced to std::string
    // compiler will write if block

    // ---------------------------------------------------

    std::cout << as_string("world") << '\n';
    // T will be deduced to const char*
    // compiler will write else block

    // ---------------------------------------------------
  }
*/

/*
  #include <type_traits>  // std::is_integral

  template <typename T>
  void func(T& t)
  {
    if (t > 0) {
      if constexpr (std::is_integral_v<T>) 
        ++t;
      else 
        --t;
    }
  }

  int main()
  {
    // ---------------------------------------------------

    int ival = 5;
    func(ival);
    std::cout << "ival = " << ival << '\n'; // output -> 6

    // because of the outer if is not a static if(if constexpr)
    // compiler must have write that if block
    // but inner if block is a static if block 
    // so because of "std::is_integral_v<is>" evaluates as true
    // compiler will generate "++t" expression.

    // compiler generated "func" with int argument
    //  void func<int>(int& t)
    //  {
    //    if (t > 0)
    //      ++t;
    //  } 

    // ---------------------------------------------------

    double dval = 2.5;
    func(dval);
    std::cout << "dval = " << dval << '\n'; // output -> 1.5

    // because of the outer if is not a static if(if constexpr)
    // compiler must have write that if block
    // but inner if block is a static if block
    // so because of "std::is_integral_v<is>" evaluates as false
    // compiler will generate "--t" expression.

    // compiler generated "func" with double argument
    //  void func(double& t)
    //  {
    //    if (t > 0)
    //      --t;
    //  }

    // ---------------------------------------------------
  }
*/

/*
  // FOR OLD COMPILERS
  // -------------------------
  // when `static if` is used compiler will only write
  // the necessary code block.
  // but when `static_assert` is used compiler will always
  // write the code block. 

  #include <type_traits>    // std::is_integral

  template <typename T>
  void func(T x)
  {
    if constexpr (std::is_integral_v<T>)
      static_assert(false, "always false assert");
    else 
      ++x;
  }

  int main()
  {
    // for new compilers versions, 
    func(1);    
    // error: static assertion failed: always false assert
    func(2.5);  // VALID
  }
*/

/*
  #include <type_traits>  // std::is_pointer

  template <typename T>
  class AClass {
  private:
    static_assert(std::is_pointer_v<T>, "pointer type required");
  };

  template <typename T>
  class BClass {
  public:
    static_assert(std::is_pointer_v<T>, "pointer type required");
  };

  template <typename T>
  class CClass {
  protected:
    static_assert(std::is_pointer_v<T>, "pointer type required");
  };

  int main()
  {
    AClass<int> ax;
    // error: static assertion failed: pointer type required

    BClass<int> bx;
    // error: static assertion failed: pointer type required

    CClass<int> cx;
    // error: static assertion failed: pointer type required

    // static_assert in public, private or protected section
    // is not changing the behaviour.
  }
*/

/*
  #include <type_traits>  // std::is_pointer

  template <typename T>
  class Myclass {
    void func()
    {
      static_assert(std::is_pointer_v<T>, "pointer type required");
    }
  };

  int main()
  {
    Myclass<int> x; // VALID
  }
*/

/*
  #include <type_traits>  // std::is_integral

  template <typename T>
  void func(T x)
  {
    if constexpr (std::is_integral_v<T>) 
      ; // null statement
    else { 
      foo();  // syntax error
      // error: there are no arguments to 'foo' 
      // that depend on a template parameter, 
      // so a declaration of 'foo' must be available

      bar(x);  // VALID
      // "bar" function's argument is dependent on T's type
      // so it won't be a syntax error before 
      // it has been called.

      x.baz();  // VALID
      // "x.bax()" expression is dependent on T's type
      // so it won't be a syntax error before
      // this statement is reached.
    }
  }
*/

/*
  class Myclass{};

  int main()
  {
    Myclass mx;

    if constexpr (sizeof(int) > 4)
      ++mx; // syntax error
    else
      --mx; // syntax error

    // error: no match for 'operator++' (operand type is 'Myclass')
    // error: no match for 'operator--' (operand type is 'Myclass')

    // when if constexpr block is not used in a template
    // for generic type 
    // compiler will always generate the code blocks
  }
*/

/*
  #include <type_traits>  // std::is_pointer

  template <typename T>
  auto get_val(T t)
  {
    if constexpr (std::is_pointer_v<T>)
      return *t;
    else
      return t;
  }

  int main()
  {
    int ival{ 87 };
    double dval{ 4.5 };
    int* ip{ &ival };
    double* dp{ &dval };

    std::cout << get_val(ival) << '\n'; // output -> 87
    std::cout << get_val(ip) << '\n';   // output -> 87

    std::cout << get_val(dval) << '\n'; // output -> 4.5
    std::cout << get_val(dp) << '\n';   // output -> 4.5
  }
*/

/*
  template <unsigned N>
  constexpr unsigned fibonacci()
  {
    if constexpr (N >= 2)
      return fibonacci<N - 1>() + fibonacci<N - 2>();
    else
      return N;
  }

  int main()
  {
    constexpr unsigned val = fibonacci<8>();
    // val -> 21 (compile time constant)

    constexpr unsigned val2 = fibonacci<15>();
    // val2 -> 610 (compile time constant)
  }
*/

/*
  #include <string>       // std::to_string
  #include <type_traits>  // std::is_same, std::is_arithmetic

  template <typename T>
  std::string to_str(T t)
  {
    return std::to_string(t);
  }

  std::string to_str(const std::string& str)
  {
    return str;
  }

  std::string to_str(const char* c_str)
  {
    return c_str;
  }

  std::string to_str(bool b)
  {
    return b ? "true" : "false";
  }


  template <typename T>
  std::string To_Str(T t)
  {
    if constexpr (std::is_same_v<T, std::string> || 
                  std::is_same_v<T, const char*>)
      return t;
    else if constexpr (std::is_arithmetic_v<T>)
      return std::to_string(t);
    else if constexpr (std::is_same_v<T, bool>)
      return t ? "true" : "false";
  }

  int main()
  {
    std::cout << to_str("galaxy") << '\n';
    // output -> hello
    std::cout << to_str(std::string{"universe"}) << '\n';
    // output -> world
    std::cout << to_str(13) << '\n';
    // output -> 13
    std::cout << to_str(5.9) << '\n';
    // output -> 5.900000
    std::cout << to_str(true) << '\n';
    // output -> true

    std::cout << To_Str("galaxy") << '\n';
    // output -> hello
    std::cout << To_Str(std::string{"universe"}) << '\n';
    // output -> world
    std::cout << To_Str(13) << '\n';
    // output -> 13
    std::cout << To_Str(5.9) << '\n';
    // output -> 5.900000
    std::cout << To_Str(true) << '\n';
    // output -> true
  }
*/