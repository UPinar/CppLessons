#include <iostream>

/*
              ----------------------------------------
              | static member variables(data member) |
              ----------------------------------------
*/

/*
  class Myclass {
  private:
    int m_a{};
    static int ms_x1;
    static int ms_x2;
    static int ms_x3;
    static int ms_x4;
  };

  int main()
  {
    std::cout << "sizeof(Myclass) = " << sizeof(Myclass) << '\n';
    // output -> sizeof(Myclass) = 4  
  }
*/

/*
  // Myclass.h
  // ----------------

  class Myclass {
    int m_a{};
  public:
    static int ms_x; // non-defining declaration
  };

  // Myclass.cpp
  // ----------------
  int Myclass::ms_x;

  // static member variables need to be defined 
  // in source(.cpp) file NOT in header(.h) file.

  // because of MORE THAN 1 file can include the header(.h) files
  // if a static data member defined in header file 
  // it will violate One Definition Rule (ODR)
*/

/*
  class BClass; // forward declaration
  // BClass is an incomplete type

  class AClass {
  public:
    // ------------------------------------------------

    BClass m_bx;  // syntax error
    // error: field 'm_bx' has incomplete type 'BClass'

    // compiler is creating a storage of the class 
    // using its non-static member variables
    // BClass is a member type of AClass
    // so its size needs to be known by the compiler
    // but because of BClass is an incomplete type
    // compiler can not know its size

    // ------------------------------------------------

    static BClass ms_by;  // non-defining declaration
    // this is a declaration not a definition.
    // compiler is not need to create a storage for "ms_by"
    // static member variable.

    // ------------------------------------------------
  };

  int main()
  {
    std::cout << sizeof(BClass);  // syntax error
    // error: invalid application of 'sizeof' to incomplete type 'BClass'
  }
*/

/*
  class Myclass {
  public:
    // ------------------------------------------------

    Myclass m_x;  // syntax error
    // error: field 'm_x' has incomplete type 'Myclass'

    // "Myclass" is an incomplete type 
    // before compiler reads the whole class definition
    // so its size is not known yet by the compiler

    // ------------------------------------------------

    Myclass* mp_x;
    // pointer to an incomplete type(Myclass) can be a data member
    // because compiler knows the size of a pointer

    // ------------------------------------------------

    static Myclass ms_x;  // non-defining declaration
    // becuase of "ms_x" is declared not defined 
    // compiler does not need to know its size

    // ------------------------------------------------
  };
*/

/*
  class Myclass {
  public:
    int m_x;          // non-static member variable
    static int ms_x;  // static member variable
  };

  int Myclass::ms_x;  // static member variable definition

  int main()
  {
    Myclass m1, m2;

    // ------------------------------------------------

    m1.ms_x = 5;

    std::cout << "m1.ms_x = " << m1.ms_x << '\n'; 
    // output -> m1.ms_x = 5
    std::cout << "m2.ms_x = " << m2.ms_x << '\n';
    // output -> m2.ms_x = 5

    // ------------------------------------------------

    m2.ms_x = 10;

    std::cout << "m1.ms_x = " << m1.ms_x << '\n';
    // output -> m1.ms_x = 10
    std::cout << "m2.ms_x = " << m2.ms_x << '\n';
    // output -> m2.ms_x = 10

    // ------------------------------------------------

    Myclass::ms_x = 15;

    std::cout << "m1.ms_x = " << m1.ms_x << '\n';
    // output -> m1.ms_x = 15
    std::cout << "m2.ms_x = " << m2.ms_x << '\n';
    // output -> m2.ms_x = 15

    // ------------------------------------------------

    Myclass* p = new Myclass;
    p->ms_x = 20;

    std::cout << "p->ms_x = " << p->ms_x << '\n';
    // output -> p->ms_x = 20
    std::cout << "m1.ms_x = " << m1.ms_x << '\n';
    // output -> m1.ms_x = 20
    std::cout << "m2.ms_x = " << m2.ms_x << '\n';
    // output -> m2.ms_x = 20

    delete p;

    // ------------------------------------------------
  }
*/

/*
  class Myclass {
  public:
    static int ms_x;
  };

  int foo()
  {
    std::cout << "foo has been called\n";
    return 5;
  }

  int Myclass::ms_x = foo();
  // static data members(static storage duration objects) 
  // is being initialized
  // before "main" function started to executed

  int main()
  {
    std::cout << "[0] main started\n";
    std::cout << "Myclass::ms_x = " << Myclass::ms_x << '\n';

    // output -> 
    // foo has been called
    // [0] main started
    // Myclass::ms_x = 5
  }
*/

/*
  class AClass {
  public:
    AClass() { std::cout << "AClass default ctor\n";}
  };

  class Myclass {
  public:
  private:
    static AClass ms_a;   // non-defining declaration
  };

  AClass Myclass::ms_a{}; // static member variable definition

  int main()
  {
    std::cout << "[0] main started\n";

    // output ->
    // AClass default ctor
    // [0] main started
  }
*/

/*
  class Myclass {
  public:
    Myclass() : m_val{ 24 }, ms_x{ 67 } {}  // syntax error
    // error: 'int Myclass::ms_x' is a static data member; 
    // it can only be initialized at its definition
  private:
    int m_val;
    static int ms_x;
  };

  // static member variables can not be initialized 
  // in constructor initializer list.

  // because of static member variables are only initialized once.
  // so if ms_x initialized in Myclass's member initializer list
  // it will be initialized every time a Myclass object created.

  // https://stackoverflow.com/a/27885867
*/

/*
  // const and integral type static member variables 
  // can be initialized in class definition.

  class Myclass {
  private:
    // ------------------------------------------------

    static int ms_ival = 10;  // syntax error 
    // error: ISO C++ forbids in-class initialization of 
    // non-const static member 'Myclass::ms_ival'

    // (integral type but not const)

    // ------------------------------------------------

    const static double ms_dval = 1.0; // syntax error
    // error: 'constexpr' needed for in-class initialization of 
    // static data member 'const double Myclass::ms_dval' 
    // of non-integral type 

    // (const but not integral type)

    // ------------------------------------------------

    const static int ms_ival2 = 20;	// VALID
    // (const and integral type)

    // ------------------------------------------------

    const static bool ms_bval = false; // VALID
    // (const and integral type)

    // ------------------------------------------------

    enum Color{ blue, black, purple };
    const static Color ms_enum_Color = black;  // VALID
    // (const and integral type)

    // ------------------------------------------------

    enum class Color_2 { red, green, yellow };
    const static Color_2 ms_enum_Color_2 = Color_2::yellow; // VALID
    // (const and integral type)

    // ------------------------------------------------
  };
*/

/*
                -----------------------------------
                | `inline` static member variable |
                -----------------------------------
*/

/*
  // `inline` keyword usage in non-const static variable (C++17)
  // for header-only libraries which static variables 
  // are defined in header(.h / .hpp) file

  // `inline` keyword is being used in global variable 
  // Linker will only see 1 g_count variable (ODR is not violated)


  // myclass.hpp (header-only library)
  // ----------------
  #include <vector>
  #include <string>

  class Myclass {
  public:
  private:
    inline static int ms_x = 10;
    inline static std::vector<int> ms_ivec{};
    inline static std::string ms_str{ "hello world" };
  };

  inline int g_count{};
*/

  /*
              --------------------------------------
              | `constexpr` static member variable |
              --------------------------------------
*/
  

/*
  // `constexpr` variables are implicitly inline
  // so no need to use `inline` keyword explicitly 

  // date.h
  // ----------------
  class Date {
  public:
    constexpr static int ms_min_year = 0;
    constexpr static int ms_max_year = 9999;
  };

  // because of `constexpr `static member variables are implicitly inline
  // they did not need to be defined in source(.cpp) file

  int main()
  {
    constexpr auto mean_year = 
        (Date::ms_max_year + Date::ms_min_year) / 2;
    // mean_year -> 4999
  }
*/


/*
  - static member functions have external linkage
  - static global functions have internal linkage
*/

/*
  class Myclass {
  public:
    void foo();
    // void foo(Myclass* this);
    // "foo" has an hidden Myclass* parameter
    // can only be called with Myclass object

    static void bar();
    // "bar" static member function 
    // does NOT have an hidden Myclass* parameter
    // can be called without Myclass object
  };

  int main()
  {
    // ------------------------------------------------

    Myclass::foo();
    // error: cannot call member function 
    // 'void Myclass::foo()' without object

    // Myclass objects address is not sent as an hidden parameter

    // ------------------------------------------------

    Myclass{}.foo();  // VALID
    // Myclass object(address of temporary Myclass object) 
    // send as an hidden parameter

    // ------------------------------------------------

    Myclass::bar();   // VALID
    // "bar" is a static member function
    // does not have an hidden Myclass* parameter

    // ------------------------------------------------
  }
*/

/*
    -------------------------------------------------------------
    |    global(free) functions   |   static member functions   |
    | ----------------------------|-----------------------------|
    | - CAN NOT reach classes     | - CAN reach classes         |
    |   private section           |   private section           |
    | - in namespace scope        | - in class scope            |
    -------------------------------------------------------------
*/

/*
  class Myclass {
  private:
    int m_x{};
  public:
    static void bar() 
    {
      std::cout << "static member function bar() called\n";
    }

    void baz()
    {
      std::cout << "this = " << this << '\n';
    }
  };

  int main()
  {
    Myclass m1, m2;
    Myclass* p_myclass = &m2;

    // ------------------------------------------------

    m1.baz();           // this = 0xc1ebffc14
    m2.baz();           // this = 0xc1ebffc10
    p_myclass->baz();   // this = 0xc1ebffc10

    // ------------------------------------------------

    Myclass::bar();   // output -> static member function bar() called
    m1.bar();         // output -> static member function bar() called
    m2.bar();         // output -> static member function bar() called
    p_myclass->bar(); // output -> static member function bar() called

    // ------------------------------------------------
  }
*/

/*
  // myclass.h
  // ----------------

  class Myclass {
  public:
    static void foo(int); // non-defining declaration

    static void bar()
    {
      // static member function definition in header(.h) file 
    }  
  };

  // myclass.cpp
  // ----------------

  void Myclass::foo(int x)
  {
    // static member function definition in source(.cpp) file
  }
*/


/*
  // myclass.h
  // ----------------

  class Myclass {
  public:
    static void foo(int);   // non-defining declaration
    void bar(int);          // non-defining declaration
  };

  // myclass.cpp
  // ----------------

  #define   STATIC

  STATIC void Myclass::foo(int x)
  {
    // static member function definition in source(.cpp) file
  }

  void Myclass::bar(int x)
  {
    // non-static member function definition in source(.cpp) file
  }

  // defining a macro called STATIC
  // preprocessor will delete STATIC identifier.
  // so it will not be seen by the compiler
  // but for the programmer it will be seen and understood.
*/

/*
  class Myclass {
  private:
    int m_x{};
  public:
    static void foo()
    {
      auto ptr = this;  // syntax error
      // error: 'this' is unavailable for static member functions

      // because of static member functions
      // do not have an hidden Myclass* parameter
      // "this" pointer is not available
    }

    static void bar()
    {
      m_x = 5;  // syntax error
      // error: invalid use of member 'Myclass::m_x' 
      // in static member function
      
      // to assign a value to a non-static member variable
      // "this" pointer is needed

      // in non-static member functions "m_x = 5" 
      // is equilavent to "this->m_x = 5"
      // because of "this" pointer is not available
      // "m_x = 5" is a syntax error
    }

    static void baz() const // syntax error
    {
      // error: static member function 
      // 'static void Myclass::baz()' cannot have cv-qualifier

      // `const` keyword makes "this" pointer const  
      // because of there is no "this" pointer 
      // no `const` keyword is allowed.
    }
  };
*/

/*
  class Myclass {
  private:
    static int ms_x;
    int m_y;
  public:
    // non-static const member function
    void foo() const  
    {
      ms_x = 10;  // VALID
    }

    // non-static const member function
    void bar() const  
    {
      m_y = 12;   // syntax error
      // error: assignment of member 'Myclass::m_y' in read-only object

      // changing m_x member variables value is NOT VALID.
      // because of `this` pointer is low-level const 
      // "this" pointer is equivalent to "const Myclass*"
    }

    // static member function
    static void baz() 
    {
      ms_x = 15;  // VALID
      // name lookup starts in function scope -> NOT FOUND
      // name lookup continues in class scope -> FOUND
    }
  };
*/

/*
  class Myclass {
  public:
    static void foo(double);
    // static member function in class scope
  };

  void foo(int);  
  // global(free) function in global scope

  // function identifiers are same      [+]
  // functiom signatures are different  [+]
  // function scopes are same           [-]
  // NO function overloading
*/

/*
  class Myclass {
  public:
    static int foo()
    {
      return 11;
    }

    static int ms_x;
    static int ms_y;
  };

  int foo()
  {
    return 22;
  }

  int Myclass::ms_x = foo();
  // in FIRST declaration of static member variable
  // name lookup will start from class scope.
  // Myclass::foo() function will be found and called.

  int Myclass::ms_y = ::foo();
  // in FIRST declaration of static member variable
  // if unary scope resolution operator(::) is used
  // name lookup will start from global scope.


  int main()
  {
    std::cout << Myclass::ms_x << '\n';   // output -> 11
    std::cout << Myclass::ms_y << '\n';   // output -> 22

    Myclass::ms_x = foo();
    // second declaration of static member variable
    // name lookup will start from block scope(main)  -> NOT FOUND
    // name lookup will continue in global scope      -> FOUND

    std::cout << Myclass::ms_x << '\n';   // output -> 22
  }
*/

/*
  class Myclass {
  public:
    static void static_public_foo()
    {
      non_static_public_func(); // syntax error
      // error: cannot call member function 
      // 'void Myclass::non_static_public_func()' 
      // without Myclass object

      // name lookup starts in function scope -> NOT FOUND
      // name lookup continues in class scope -> FOUND

      // non_static_public_func function needs to be called  
      // with Myclass object to sent Myclass object's address
      // to "non_static_public_func" function's hidden parameter 
    }

    static void static_public_bar(Myclass m)
    {
      // --------------------------------------------

      m.non_static_public_func();   // VALID
      // inside static member functions scope
      // non-static member functions can be called.

      // used parameter variable "m" object's address 
      // to sent "non_static_public_func" function's 
      // hidden parameter(Myclass*)

      // --------------------------------------------

      Myclass x;
      x.non_static_public_func();  // VALID
      // inside static member functions scope
      // non-static member functions can be called.

      // created local variable "x" and used object's address
      // to sent "non_static_public_func" function's 
      // hidden parameter(Myclass*)

      // --------------------------------------------

      x.private_func();   // VALID
      // inside static member functions scope
      // private section of the class can be reached.
      
      // --------------------------------------------
    }
    void non_static_public_func() {}
  private:
    void private_func() {}
  };
*/

/*
  class Myclass {
  public:
    static Myclass create_myclass_obj(int x)
    {
      return Myclass{ x };  // VALID
      // static member function can reach class's private section
      // calling private ctor from static member function is VALID
    }
  private:
    Myclass(int);
  };

  int main()
  {
    // --------------------------------------------

    Myclass m1{ 4 };  // syntax error
    // error: 'Myclass::Myclass(int)' is private within this context

    // private section of Myclass can not be reached from 
    // main function(block scope)

    // --------------------------------------------

    Myclass m2 = Myclass::create_myclass_obj(243); // VALID

    // --------------------------------------------
  }
*/

/*
                  ---------------------------
                  | member function pointer |
                  ---------------------------
*/

/*
  // function pointer REMINDER

  int foo(int);
  using FPTR = int(*)(int);

  int main()
  {
    auto fp1 = foo;   // function to function pointer conversion
    auto fp2 = &foo;
    int (*fp3)(int) = &foo;
    FPTR fp4 = &foo;
    decltype(fp1) fp5 = &foo;
    // Those 5 lines are equivalent.
  }
*/

/*
  class Myclass {
  public:
    int foo(int);           // non-static member function
    static int func(int);   // static member function
  };

  int bar(int);

  int main()
  {
    // ------------------------------------------------

    int (*fp)(int) = &Myclass::foo; // syntax error
    // error: cannot convert 'int (Myclass::*)(int)' to 'int (*)(int)'

    // because of Myclass::foo is a non-static member function
    // it has an hidden Myclass* parameter
    // so its type is not same with int (*)(int)

    // ------------------------------------------------

    auto fp2 = &Myclass::foo;
    // "fp2"'s declaration type is int(Myclass::*fp2)(int)
    // "fp2" is a member function pointer

    // ------------------------------------------------

    int (Myclass::*fp3)(int) = &Myclass::foo;
    // "fp3" is a member function pointer

    // ------------------------------------------------

    int(*fp4)(int) = &Myclass::func;    // VALID
    fp4 = &bar;                         // VALID

    // because of Myclass::func is a static member function
    // it does not have an hidden Myclass* parameter
    // so its type is same with int (*)(int)

    // ------------------------------------------------
  }
*/

/*
                  ---------------------------
                  | named constructor idiom |
                  ---------------------------
*/

/*
  class Complex {
  public:
    static Complex create_cartesian(double reel, double imag)
    {
      return Complex{ reel, imag };
    }
    static Complex create_polar(double angle, double distance)
    {
      return Complex{ angle, distance, 0 };
    }
  private:
    Complex(double reel, double imag);
    Complex(double angle, double distance, int);
  };

  int main()
  {
    auto c1 = Complex::create_cartesian(1.2, 5.6);
    auto c2 = Complex::create_polar(.5, .8346);
  }
*/

/*
                -----------------------------
                | dynamic object only class |
                -----------------------------
*/

/*
  class Dynamic_Only {
  public:
    static Dynamic_Only* create()
    {
      return new Dynamic_Only{};
    }

    Dynamic_Only(const Dynamic_Only&) = delete;
    Dynamic_Only& operator=(const Dynamic_Only&) = delete;
    // copy members are user declared deleted
    // because of one of copy members user declared
    // move members are implicitly deleted by the compiler
  private:
    Dynamic_Only();
  };

  // Dynamic_Only classes copy and move members are deleted.
  // so can not create an object with copy or move operations.

  // To create an object we need to call its default ctor,
  // but default ctor is in private section
  // so only way to create an object is calling create() function
  // and create() function is creating only dynamic objects.
*/

/*
                ----------------------------
                | singleton design pattern |
                ----------------------------
*/

/*
  In singleton design pattern, only 1 instance of class object
  can be created and that instance needs to be used globally.
*/

/*
  class Myclass {
  private:
    Myclass()
    {
      std::cout << "Myclass object constructed\n";
    }
    inline static Myclass* msp_x{};
  public:
    static Myclass& get_instance()  // not thread safe
    {
      if (!msp_x) {
        msp_x = new Myclass;
      }
      return *msp_x;
    }
    Myclass(const Myclass&) = delete;
    Myclass& operator=(const Myclass&) = delete;

    void foo()
    {
      std::cout << "inside foo, this = " << this << '\n';
    }
  };

  int main()
  {
    std::cout << "[0] - main started\n";
    Myclass::get_instance().foo();
    std::cout << "[1] - main continues\n";
    auto& singleton_obj = Myclass::get_instance();
    std::cout << "singleton_obj = " << &singleton_obj << '\n';
    std::cout << "[2] - main continues\n";

    // output ->
    //  [0] - main started
    //  Myclass object constructed
    //  inside foo, this = 0x22739cb9ac0
    //  [1] - main continues
    //  singleton_obj = 0x22739cb9ac0
    //  [2] - main continues
  }
*/

/*
  // Meyer's implementation of singleton

  class Myclass {
  private:
    Myclass()
    {
      std::cout << "Myclass ctor, this = " << this << '\n';
    }
  public:
    static Myclass& get_instance()  // thread safe
    {
      static Myclass instance;
      // static local variable will come to life one and only once
      // when get_instance() function is being called.
      return instance;
    }
    Myclass(const Myclass&) = delete;
    Myclass& operator=(const Myclass&) = delete;
  };

  int main()
  {
    std::cout << "[0] - main started\n";
    std::cout << &Myclass::get_instance() << '\n';
    std::cout << "[1] - main continues\n";
    std::cout << &Myclass::get_instance() << '\n';
    std::cout << "[2] - main continues\n";

    // output ->
    //  [0] - main started
    //  Myclass ctor, this = 0x7ff6c1744130
    //  0x7ff6c1744130
    //  [1] - main continues
    //  0x7ff6c1744130
    //  [2] - main continues
  }
*/

/*
  class AClass {
  private:
    inline static int ms_live_count{};
    inline static int ms_ever_lived_count{};
  public:
    AClass()
    {
      ++ms_live_count;
      ++ms_ever_lived_count;
    }

    ~AClass()
    {
      --ms_live_count;
    }

    static int get_live_count()
    {
      return ms_live_count;
    }
    static int get_ever_lived_count()
    {
      return ms_ever_lived_count;
    }
  };

  int main()
  {
    AClass a1, a2, a3;
    AClass* pa1 = new AClass;
    AClass* pa2 = new AClass;

    {
      AClass a4;
      delete pa1;
    } // a4 is destructed, pa1 is deleted

    std::cout << AClass::get_live_count() << '\n'; 
    // output -> 4
    std::cout << AClass::get_ever_lived_count() << '\n';
    // output -> 6
  }
*/

/*
  #include <string>
  #include <vector>     // std::erase
  #include <algorithm>  // std::find
  #include <cstdio>     // std::putchar

  class Fighter {
  private:
    std::string m_name;
    inline static std::vector<Fighter*> ms_fpvec;
  public:
    Fighter(const std::string& name) : m_name{ name }
    {
      ms_fpvec.push_back(this);
    }

    ~Fighter()
    {
      std::erase(ms_fpvec, this);   // C++20
      // Erases all elements that compare equal to `this` 
      // from the container
      // https://en.cppreference.com/w/cpp/container/vector/erase2

      // remove-erase idiom is being used before C++20
      // auto iter = std::find(ms_fpvec.begin(), ms_fpvec.end(), this);
      // svec.erase(iter);
    }

    void ask_help()
    {
      std::cout << m_name << " asks help from -> ";

      for (Fighter* fp : ms_fpvec)
      {
        if (fp != this) 
          std::cout << fp->m_name << " ";
      }
      std::putchar('\n');
    }
  };

  int main()
  {
    Fighter f1{ "f1" }, f2{ "f2" }, f3{ "f3" }, f4{ "f4" };
    auto p1 = new Fighter{ "p1" };
    auto p2 = new Fighter{ "p2" };

    f3.ask_help();  
    // output -> f3 asks help from -> f1 f2 f4 p1 p2

    delete p1;
    f1.ask_help();
    // output -> f1 asks help from -> f2 f3 f4 p2
  }
*/