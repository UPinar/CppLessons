#include <iostream>

/*
                      --------------------
                      | moved-from state |
                      --------------------
*/

/*
  C++ STL is giving some guarantees for moved-from state objects.

    -> Object will be in a valid state.
    -> Object will be destructable(No UB when calling destructor).
    -> Object will be reusable(assignable).

  - easiest way to create moved-from state object is
    to make that object back to default initialized state.
*/

/*
  #include <string>

  int main()
  {
    std::string str(10'000, 'A');

    // ------------------------------------------------------

    std::string s = std::move(str);
    // "str" object's resource was stolen.
    // "str" object's state become moved-from state.

    std::cout << str << '\n'; // output -> "" -> empty string
    
    // ------------------------------------------------------

    str = "Hello World!";
    // moved-from state objects are reusable(assignable)
    
    std::cout << str << '\n'; // output -> Hello World!

    // ------------------------------------------------------
  }
*/

/*
  #include <string>
  #include <fstream>
  #include <vector>

  int main()
  {
    using namespace std;

    ifstream ifs{ "terms_for_classes.cpp" };

    if (!ifs) {
      cerr << "folder can not be opened\n";
      return 1;
    }

    string sline;
    vector<string> svec;

    while (getline(ifs, sline))
      svec.push_back(std::move(sline));
    // "sline" object's resource was stolen.
    // moved-from state "sline" object is being reused.

    for (const auto& s : svec)
      cout << s << '\n';
    // output -> print all lines in the file.
  }
*/

/*
  #include <string>

  void foo(std::string&& s_ref)
  {
    std::string str = std::move(s_ref);
    // "s_ref" parameter variable's data type is R value reference 
    // "std::move(s_ref)" is an XValue expression(R)
    // std::string object's(str) move ctor will be called.
  }

  void bar(std::string&& s_ref)
  {
    std::string str = s_ref;
    // "s_ref" parameter variable's data type is R value reference
    // "s_ref" is an LValue expression
    // std::string object's(str) copy ctor will be called.
  }

  int main()
  {
    std::string str(20'000, '!');

    // ------------------------------------------------------
    
    bar(std::move(str));
    // R value reference parameter variable 
    // will bind to XValue expression(R)

    // "str" objects resource has been copied
    // inside "bar" function.

    std::cout << "str.size() = " << str.size() << '\n'; 	
    // output -> str.size() = 20000

    // ------------------------------------------------------

    foo(std::move(str));
    // R value reference parameter variable
    // will bind to XValue expression(R)

    // "str" objects resource has been stolen.
    // inside "foo" function.

    std::cout << "str.size() = " << str.size() << '\n';	
    // output -> str.size() = 0

    // ------------------------------------------------------
  }
*/

/*
  void func(const std::string& str_c_ref)
  {
    std::string str_1 = str_c_ref;
    // "str_c_ref" is an LValue expression
    // std::string object's(str_1) copy ctor will be called.

    std::string str_2;
    str_2 = str_c_ref;
    // "str_c_ref" is an LValue expression
    // std::string object's(str_2) copy assignment will be called.
  }

  void func(std::string&& str_rref)
  {
    std::string str = std::move(str_rref);
    // "std::move(str_rref)" is an XValue expression(R)
    // std::string object's(str) move ctor will be called.
  }

  void foo(std::string&& str_rref)
  {
    std::string str;
    str = std::move(str_rref);
    // "std::move(str_rref)" is an XValue expression(R)
    // std::string object's(str) move assignment will be called.
  }
*/

/*
  int main()
  {
    int x = 190;

    int y = x;
    int y = std::move(x);
    // These 2 lines are equivalent.
    // "x" object's value will be copied to "y" object.
  }
*/

/*
  int main()
  {
    int x = 10;
    int* p{ &x };

    int* ptr = p;
    int* ptr = std::move(p);
    // These 2 lines are eqivalent. 
    // "p" object's value will be copied to "ptr" object.
  }
*/

/*
  class Myclass {
  public:
    // Myclass(const Myclass& other): m_x(other.m_x)	
    // Myclass(Myclass&& other): m_x(std::move(other.m_x))	....
  private:
    int m_x, m_y, m_z;
    int m_arr[10];
    int* m_p1;
    int* m_p2;
  };

  // If classes data members are primitive types or pointers,
  // there is no difference between classes move and copy members
  // move constructor will act like copy constructor.
  // move assignment will act like copy assignment.
*/


/*
  class Myclass {
  public:
    // Myclass(const Myclass& other): m_str(other.m_str)	....
    // Myclass(Myclass&& other): m_str(std::move(other.m_str)) ....
  private:
    std::string m_str;
    int m_x, m_y, m_z;
    int m_arr[10];

  };

  // when a class have a data member that its move members 
  // are different from its copy members
  // classes move and copy ctors members will become different too.
*/

/*
  class AClass {
  private:
    int m_x, m_y, m_z;
    int m_arr[10];
  };

  class Myclass {

  private:
    AClass m_a;
  };

  // There is no difference in Myclasses copy and move members,
  // because there is no difference in AClasses copy and move members.
*/

/*
  // if one of the move members is user declared
  // compiler will implicitly delete the copy members.

  class MoveOnly {
  public:
    MoveOnly() = default;

    MoveOnly(MoveOnly&&);
    MoveOnly& operator=(MoveOnly&&);
  };

  class Myclass {
  private:
    MoveOnly mx;
  };

  // when Myclass's copy ctor has been called
  // it will call MoveOnly's(its data member) copy ctor
  // and because MoveOnly's copy ctor is deleted 
  // it will be syntax error so the compiler will delete 
  // Myclass's copy ctor too.
  // same also applied in copy assignment.

  int main()
  {
    // ------------------------------------------------------

    Myclass m1;
    Myclass m2 = m1;  // syntax error
    // error: use of deleted function 'Myclass::Myclass(const Myclass&)'

    Myclass m3, m4;
    m3 = m4;          // syntax error
    // error: use of deleted function 
    // 'Myclass& Myclass::operator=(const Myclass&)'

    // ------------------------------------------------------

    Myclass m5;
    Myclass m6 = std::move(m5); // VALID
    // Myclass's move constructor is implicitly declared defaulted.

    Myclass m7, m8;
    m7 = std::move(m8);         // VALID
    // Myclass's move assignment is implicitly declared defaulted.

    // ------------------------------------------------------
  }
*/

/*
                ------------------------------
                | default member initializer |
                ------------------------------
*/

/*
  class AClass {
  public:
    void print() const
    {
      std::cout << "m_x = " << m_x << '\n';
      std::cout << "m_y = " << m_y << '\n';
    }
  private:
    int m_x;
    int m_y;
  };

  class BClass {
  public:
    // BClass() : mx(10), my(20) {}
    void print() const
    {
      std::cout << "m_x = " << m_x << '\n';
      std::cout << "m_y = " << m_y << '\n';
    }
  private:
    // default member initializer.
    int m_x = 10;
    int m_y{ 20 };
  };

  // implicitly declared default ctor will use
  // default member initializer values to initialize data members.
  // if there is no default member initializer values
  // data members will be default initialized.


  int main()
  {
    // ------------------------------------------------------

    AClass ax;
    ax.print();	// undefined behaviour(UB)
    // AClass did not have default member initializer.
    // When AClass object is default initialized,
    // its data members will also be default initialized
    // AClass's default initialized int data members 
    // will have indeterminate(garbage) value.

    // ------------------------------------------------------

    BClass bx;
    bx.print();
    // output -> 
    //	m_x = 10
    //	m_y = 20

    // BClass have default member initializer.
    // When BClass object is default initialized,
    // its data members will be initialized with 
    // default member initializer values.
    // BClass's int data members won't have indeterminate value.

    // ------------------------------------------------------
  }
*/

/*
  class AClass {
  public:
    AClass() : m_x(12938), m_y(82939) {} 
    // user declared default constructor

    void print() const
    {
      std::cout << "m_x = " << m_x << '\n';
      std::cout << "m_y = " << m_y << '\n';
    }
  private:
    int m_x = 10;
    int m_y{ 20 };
  };

  class BClass {
  public:
    BClass() : m_x(12938) {} 
    // user declared default constructor.

    void print() const
    {
      std::cout << "m_x = " << m_x << '\n';
      std::cout << "m_y = " << m_y << '\n';
    }
  private:
    int m_x = 10;
    int m_y{ 20 };
  };

  int main()
  {
    AClass ax;
    ax.print();
    // output ->
    //	m_x = 12938
    //	m_y = 82939

    // ------------------------------------------------------

    BClass bx;
    bx.print();
    // output ->
    //	m_x = 12938
    //	m_y = 20
  }
*/

/*
                  -------------------------
                  | delegated constructor |
                  -------------------------
*/

/*
  class Myclass {
  public:
    Myclass() : Myclass(0, 0, 0)
    {
      std::cout << "Myclass() default ctor.\n";
    }
    // Myclass() default ctor
    // delegated Myclass(int, int, int) ctor

    Myclass(int x) : Myclass(x, x, x)
    {
      std::cout << "Myclass(int)\n";
    }
    // Myclass(int) ctor
    // delegated Myclass(int, int, int) ctor

    Myclass(int x, int y) : Myclass(x + y)
    {
      std::cout << "Myclass(int, int)\n";
    }
    // Myclass(int, int) ctor
    // delegated Myclass(int) ctor

    Myclass(int a, int b, int c) : m_a(a), m_b(b), m_c(c)
    {
      std::cout << "Myclass(int, int, int)\n";
    }
    // Myclass(int, int, int) ctor

  private:
    int m_a, m_b, m_c;
  };

  int main()
  {
    Myclass mx(5, 9);
    // Myclass(int, int) will delegate Myclass(int) ctor
    // Myclass(int) will delegate Myclass(int, int, int) ctor

    // first Myclass(int, int, int) ctor will be called
    // then Myclass(int) ctor will be called
    // then Myclass(int, int) ctor will be called

    // output ->
    //  Myclass(int, int, int)
    //  Myclass(int)
    //  Myclass(int, int)
  }
*/

/*
  class Myclass {
  public:
    Myclass() : Myclass(111, 2222) {}
    Myclass(int a, int b) : m_a(a), m_b(b) {}

    void print() const
    {
      std::cout << "m_a = " << m_a << '\n';
      std::cout << "m_b = " << m_b << '\n';
      std::cout << "m_c = " << m_c << '\n';
    }

  private:
    int m_a, m_b, m_c{ 33 };
  };

  int main()
  {
    Myclass mx;
    // Myclass() default ctor will delegate Myclass(int, int) ctor
    // Myclass(int, int) ctor will initialize m_a and m_b
    // using member initializer list
    // Myclass() default ctor will initialize m_c 
    // using default member initializer.

    mx.print();
    // output ->
    //	m_a = 111
    //	m_b = 2222
    //	m_c = 33
  }
*/

/*
                      ---------------------
                      | temporary objects |
                      ---------------------
*/

/*
  template <typename T>
  void swap_1(T& r1, T& r2)
  {
    T temp(r1);

    r1 = r2;
    r2 = temp;
  }

  // There are 2 problems in swap_1 funtion's code.
  //  1. T can be deduce to std::string and because swap_1 function
  //    will use copy members, it will not be efficient for std::string.

  //  2. T can be deduce to move only type e.g., unique_ptr
  //    and because swap_1 function will use copy members, 
  //    it will become a syntax error.

  template <typename T>
  void swap_2(T& r1, T& r2)
  {
    T temp(std::move(r1));

    r1 = std::move(r2);
    r2 = std::move(temp);
  }

  template <typename T>
  void Swap(T x, T y)
  {
    T temp(std::move(x));
    x = std::move(y);
    y = std::move(temp);
  }
*/

/*
  class Myclass {
  public:
    Myclass(int x)
    {
      std::cout << "Myclass(int x) ctor x = " << x 
                << " this : " << this << '\n';
    }

    Myclass()
    {
      std::cout << "Myclass() default ctor this : " 
                << this << '\n';
    }

    ~Myclass()
    {
      std::cout << "~Myclass() destructor this : " 
                << this << '\n';
    }
  };

  int main()
  {
    Myclass mx;
    mx = 19;  // -------> (1)
    // in line (1)
    // temporary Myclass object will be constructed 
    // and its destructor will be called after assignment.
    std::cout << "main continues..\n";

    // output ->
    //  Myclass() default ctor this     : 0x9de57ff84e
    //  Myclass(int x) ctor x = 19 this : 0x9de57ff84f
    //  ~Myclass() destructor this      : 0x9de57ff84f
    //  main continues..
    //  ~Myclass() destructor this      : 0x9de57ff84e
  }
*/

/*
  int main()
  {
    const int& r = 45;
    // compiler will generate temporary int object
    // const int& will bind to that temporary object.
    // temporary object's life will be extended to "r"'s scope.
    // const L value reference can bind to PRValue expression(R).
  }
*/

/*
  class Myclass {
  public:
    Myclass(){}
    Myclass(int x, int y){}
  private:
    int m_x{}, m_y{};
  };

  int main()
  {
    Myclass();  
    // temporary object with Myclass() ctor
    // direct initialization

    Myclass{};		
    // temporary object with Myclass() ctor
    // value initialization

    Myclass(10, 20);	
    // temporary object with Myclass(int, int) parameter constructor
  }
*/

/*
  // temporary object's value category is PRValue expression(R)

  class Myclass{};

  int main()
  {
    Myclass& r = Myclass{}; // syntax error
    // error: cannot bind non-const lvalue reference of type 'Myclass&'
    // to an rvalue of type 'Myclass'
    // L value reference can not bind to PRValue expression(R).

    const Myclass& cr = Myclass{};    // VALID
    // const L value reference can bind to PRValue expression(R).

    Myclass&& rr = Myclass{};         // VALID
    // R value reference can bind to PRValue expression(R).
  }
*/

/*
  class Myclass {};

  void foo(Myclass);
  void func(Myclass&&);
  void bar(const Myclass&);
  void baz(Myclass&);

  int main()
  {
    foo(Myclass{});   // VALID
    // call by value
    
    func(Myclass{});  // VALID
    // R value reference can bind to PRValue expression(R).

    bar(Myclass{});		// VALID
    // const L value reference can bind to PRValue expression(R).

    baz(Myclass{});   // syntax error
    // error: cannot bind non-const lvalue reference of type 'Myclass&' 
    // to an rvalue of type 'Myclass'

    // L value reference can NOT bind to PRValue expression(R).
  }
*/

/*
  #include <string>

  class Myclass {};

  void baz(const Myclass&);

  int main()
  {
    // ------------------------------------------------------
    Myclass{};   // -----> (1)

    // in (1) temp Myclass object will be contructed and destroyed

    // ------------------------------------------------------

    Myclass mx;
    baz(mx);
    // If we want to pass Myclass object that will not used after 
    // baz() function's execution, creating a local Myclass object
    // and passing it to baz() function will cause scope leakage.

    baz(Myclass{});
    // temp object was sent to baz() function
    // no scope leakage

    // ------------------------------------------------------

    {
      std::string str(10'000, 'A');
    }	
    // nested blocks are also useful for scope leakage prevention.

    // ------------------------------------------------------
  }
*/

/*
  class Myclass {
  public:
    Myclass(int x)
    {
      std::cout << "Myclass(int x), x = " << x << '\n';
    }

    ~Myclass()
    {
      std::cout << "~Myclass() destructor\n";
    }
  };

  // life extension
  int main()
  {
    std::cout << "main starts\n";

    {
      std::cout << "[1] - main continues\n";
      const Myclass& r = Myclass{ 12 };
      // Myclass{12} temporary objects life depends on "r"'s life.
      std::cout << "[2] - main continues\n";
    }

    std::cout << "[3] - main continues\n";
  }

  // output ->
  //  main starts
  //  [1] - main continues
  //  Myclass(int x), x = 12
  //  [2] - main continues
  //  ~Myclass() destructor
  //  [3] - main continues
*/

/*
                  --------------------------
                  | conversion constructor |
                  --------------------------
*/

/*
  class Myclass {
  public:
    Myclass()
    {
      std::cout << "Myclass default ctor this = " 
                << this << '\n';
    }

    ~Myclass()
    {
      std::cout << "Myclass destructor this   = " 
                << this << '\n';

    }

    Myclass(int x)  // conversion ctor
    {
      std::cout << "Myclass(int x) x = " << x 
                << " this = " << this << '\n';
    }

    Myclass& operator=(const Myclass& other)
    {
      std::cout << "Myclass copy assignment this = " 
                << this << '\n';
      std::cout << "&other = " << &other << '\n';
      return *this;
    }
  };

  int main()
  {
    Myclass m;
    std::cout << "&m = " << &m << '\n';
    m = 35; // -----> (1)
    // m = Myclass{35};
    // move assignment should be called but 
    // because of user declared copy assignment
    // Myclass's move assignment will not be declared by the compiler.
    std::cout << "main continues\n";

    // output ->
    //  Myclass default ctor this     = 0x679fdffcbe
    //  &m = 0x679fdffcbe
    //  Myclass(int x) x = 35 this    = 0x679fdffcbf
    //  Myclass copy assignment this  = 0x679fdffcbe
    //  &other = 0x679fdffcbf
    //  Myclass destructor this       = 0x679fdffcbf
    //  main continues
    //  Myclass destructor this       = 0x679fdffcbe
  }
*/

/*
  User Defined Conversion
    -> conversion ctor
    -> type-cast operator function

  Standart Conversion + UDC -> VALID
  UDC + Standart Conversion -> VALID
  UDC + UDC                 -> NOT VALID
*/

/*
  class Myclass {
  public:
    Myclass();
    Myclass(int);
  };

  int main()
  {
    Myclass m;
    double dval{ 2.3 };

    m = dval; // VALID
    // conversion order : double ==> int ==> Myclass
    // Standart conversion(double ==> int) + UDC(int ==> Myclass)
  }
*/

/*
  class Myclass {
  public:
    Myclass();
    Myclass(bool);
  };

  int main()
  {
    Myclass m;
    double dval{ 2.3 };
    auto ptr_d = &dval;

    m = ptr_d; // VALID  

    // conversion order : double* ==> bool ==> Myclass
    // Standart conversion(double* ==> bool) + UDC(bool ==> Myclass)
  }
*/

/*
  class AClass {
  public:
    AClass();
  };

  class BClass {
  public:
    BClass();
    BClass(AClass); // conversion ctor
  };

  int main()
  {
    BClass bx;
    AClass ax;

    bx = ax;  // VALID
    // (AClass ==> BClass) is a User Defined Conversion.
  }
*/

/*
  class AClass {
  public:
    AClass();
  };

  class BClass {
  public:
    BClass();
    BClass(AClass); // conversion ctor
    void func();
  };

  int main()
  {
    // ------------------------------------------------------
    BClass b_x(AClass());  // most vexing parse
    // this is a function declaration
    b_x.func();  // syntax error

    // ------------------------------------------------------

    BClass b_1((AClass()));
    b_1.func();  // VALID

    BClass b_2(AClass{});
    b_2.func();  // VALID

    BClass b_3{ AClass() };
    b_3.func();  // VALID

    BClass b_4{ AClass{} };
    b_4.func();  // VALID

    // ------------------------------------------------------
  }
*/

/*
  class AClass {
  public:
    AClass();
  };

  class BClass {
  public:
    BClass();
    BClass(AClass); // conversion ctor
  };

  class CClass {
  public:
    CClass();
    CClass(BClass); // conversion ctor
  };

  int main()
  {
    CClass cx;
    BClass bx;
    cx = bx;  // VALID


    AClass ax;
    cx = ax;  // syntax error
    // conversion order : AClass ==> BClass ==> CClass
    // (AClass ==> BClass) is a User Defined Conversion.
    // (BClass ==> CClass) is a User Defined Conversion.
    // UDC + UDC -> NOT VALID
  }
*/

/*
  class AClass {
  public:
    AClass();
  };

  class BClass {
  public:
    BClass();
    BClass(AClass); // conversion ctor
  };

  class CClass {
  public:
    CClass();
    CClass(BClass); // conversion ctor
  };

  int main()
  {
    AClass ax;
    CClass cx;

    cx = static_cast<BClass>(ax); // VALID
    // conversion order : AClass ==> BClass ==> CClass
    // (AClass ==> BClass) is explicit conversion(static_cast)
    // (BClass ==> CClass) is a User Defined Conversion.
  }
*/

/*
                    ------------------------
                    | explicit constructor |
                    ------------------------
*/

/*
  class Myclass {
  public:
    Myclass();              // default ctor
    explicit Myclass(int);  // explicit constructor
    // does not allow implicit conversion from int to Myclass
  };

  void foo(Myclass);
  void bar(const Myclass&);
  void baz(Myclass&&);

  Myclass func()
  {
    return 16;  // syntax error
    // error: could not convert '16' from 'int' to 'Myclass'
    // implicit conversion from int to Myclass is not allowed
  }

  int main()
  {
    Myclass mx;
    mx = 12;  // syntax error
    // no implicit conversion from int to Myclass
    // so no temp Myclass object can created to assign mx. 

    foo(13);  // syntax error
    bar(14);  // syntax error
    baz(15);  // syntax error
  }
*/

/*
  class Myclass {
  public:
    Myclass() = default;
    explicit Myclass(int)
    {
      std::cout << "explicit ctor called\n";
    }
  };

  int main()
  {
    int ival{ 2321 };

    Myclass m1, m2, m3;
    m1 = static_cast<Myclass>(ival);  
    // output -> explicit ctor called

    m2 = (Myclass)ival;               
    // output -> explicit ctor called

    m3 = Myclass(ival);               
    // output -> explicit ctor called
  }
*/

/*
  class Myclass {
  public:
    explicit Myclass(int);
  };

  int main()
  {
    Myclass m1(12);
    // direct initialization is VALID for explicit ctor.

    Myclass m2{ 15 };
    // direct list initialization is VALID for explicit ctor.

    Myclass m3 = 16;
    // copy initialization is NOT VALID for explicit ctor.
  }
*/

/*
  #include <string>
  #include <vector>
  #include <stdexcept>  // std::runtime_error
  #include <memory>     // std::unique_ptr

  int main()
  {
    // ------------------------------------------------------

    std::string str = "hello world";  // VALID
    // std::tring(const char*) is not explicit

    // ------------------------------------------------------

    std::vector<int> ivec_1 = 123;  // syntax error
    // std::vector<T>(std::size_t) is explicit

    std::vector<int> ivec_2(123);
    // VALID(direct initialization)

    // ------------------------------------------------------

    std::runtime_error ex_1 = "error";  // syntax error
    // std::runtime_error(const char*) is explicit

    std::runtime_error ex_2("error");
    // VALID(direct initialization)

    // ------------------------------------------------------

    std::unique_ptr<int> uptr_1 = new int;  // syntax error
    // std::unique_ptr(T*) is explicit

    std::unique_ptr<int> uptr_2(new int);
    // VALID(direct initialization)

    // ------------------------------------------------------
  }
*/

/*
  // myclass.h
  // -------------
  class Myclass {
  public:
    explicit Myclass(int);    // explicit ctor declaration
    explicit Myclass(double); // explicit ctor declaration
  };


  // myclass.cpp
  // -------------
  explicit Myclass::Myclass(int) {} // syntax error
  // error: 'explicit' outside class declaration

  Myclass::Myclass(double) {} // VALID
  
  // `explicit` keyword should be used only in member function's
  // declaration not in definition.
*/

/*
  class Myclass {
  public:
    explicit Myclass(int)
    {
      std::cout << "explicit Myclass(int)\n";
    }

    Myclass(double)
    {
      std::cout << "Myclass(double)\n";
    }
  };

  int main()
  {
    Myclass m = 5;  // output -> Myclass(double)

    // because of explicit constructor is not in Function Overload Set
    // int ==> double ==> Myclass conversion will be applied.
    // (int ==> double) is a standard conversion.
    // (double ==> Myclass) is a user defined conversion.
    // Standart Conversion + UDC -> VALID
  }
*/

/*
                          ----------------
                          | copy elision |
                          ----------------
*/

/*
  ->	after C++17 some copy ellisions which are compiler optimization,
      becomes standart(mandtory copy ellision).

  ->  if copy elision is not mandatory, and if user delete the copy ctor
    it will cause syntax error. If it is mandatory, deleting copy ctor
    will not cause syntax error.
*/

/*
                  <----- SCENARIO_1 ----->

  - if functions parameter variable's type is a class type,
    and we can this function with a PRValue expression.
    Mandatory Copy Ellision will be applied.
*/

/*
  class Myclass {
  public:
    Myclass()
    {
      std::cout << "Myclass default ctor\n";
    }
    Myclass(int)
    {
      std::cout << "Myclass(int) ctor\n";
    }

    Myclass(const Myclass&)
    {
      std::cout << "Myclass copy ctor\n";
    }
    // move members are not declared by the compiler
    // because of copy ctor is user declared.
  };

  void foo(Myclass){}
  // foo function's parameter variable is a class type.

  int main()
  {
    // ------------------------------------------------------

    foo(Myclass{});
    // "Myclass{}" is a PRValue expression(R) 

    // if no mandatory copy ellision will be applied
    //  1 - Myclass default ctor will be called for temp object
    //  2 - Myclass move or copy ctor will be called
    //      (copy ctor for this scenario - move ctor not declared) 
    //      for function's parameter variable.

    // output -> Myclass default ctor
    // because of the mandatory copy ellision only default ctor
    
    // ------------------------------------------------------

    foo(Myclass{12});
    // "Myclass{12}" is a PRValue expression(R)

    // if no mandatory copy ellision will be applied
    //  1 - Myclass(int) ctor will be called for temp object
    //  2 - Myclass move or copy ctor will be called
    //      (copy ctor for this scenario - move ctor not declared) 
    //      for function's parameter variable.

    // output -> Myclass(int) ctor
    // because of the mandatory copy ellision only Myclass(int) ctor

    // ------------------------------------------------------
  }
*/

/*
  class Myclass {
  public:
    Myclass()
    {
      std::cout << "Myclass default ctor\n";
    }

    Myclass(int)
    {
      std::cout << "Myclass(int) ctor\n";
    }

    Myclass(const Myclass&) = delete;
    // because of copy ctor is user declared
    // move members are not declared by the compiler.
  };

  void foo(Myclass){}
  // foo function's parameter variable is a class type.

  int main()
  {
    foo(Myclass{});       // VALID
    // "Myclass{}" is a PRValue expression(R)
    // output -> Myclass default ctor

    foo(Myclass{ 12 });   // VALID
    // "Myclass{12}" is a PRValue expression(R)
    // output -> Myclass(int) ctor

    // because of those copy ellisions are mandatory
    // no need for copy or move members.
  }
*/

/*
  class Myclass{};

  void foo(Myclass) {}

  int main()
  {
    Myclass m1;
    foo(m1);
    // "m1" is an LValue expression
    // no copy ellision will be applied.
    // default ctor for m1 variable 
    // and copy ctor for function's parameter variable.

    foo(Myclass{});	
    // "Myclass{}" is a PRValue expression(R)
    // mandatory copy ellision will be applied.
    // only default ctor will be called for parameter variable.
  }
*/

// TODO: Add assembly code for the first mandatory copy ellision scenerio.

/*
  -----------------------------------------------
  | Scenerio 2 (Return Value Optimization)[RVO] |
  -----------------------------------------------
  If a functions return value type is a class type,
  and this function is returning a PR value expression.
  Mandatory Copy Ellision will be applied.
*/

/*
  class Myclass {
  public:
    Myclass()
    {
      std::cout << "Myclass default ctor\n";
    }
    Myclass(int)
    {
      std::cout << "Myclass(int) ctor\n";
    }

    Myclass(const Myclass&)
    {
      std::cout << "Myclass copy ctor\n";
    }
  };

  Myclass foo()
  {
    // code
    return Myclass{};
  }

  Myclass bar()
  {
    // code
    return Myclass{ 12 };
  }

  int main()
  {
    Myclass m1 = foo();		// output -> Myclass default ctor
    // In normal, in foo() function default ctor will be called for temp object
    // Then for [Myclass m = foo()] statement copy ctor will be called.

    Myclass m2 = bar();		// output -> Myclass(int) ctor
  }
*/

/*
  class Myclass {
  public:
    Myclass()
    {
      std::cout << "Myclass default ctor\n";
    }
    Myclass(int)
    {
      std::cout << "Myclass(int) ctor\n";
    }

    Myclass(const Myclass&) = delete;
  };

  Myclass foo()
  {
    return Myclass{};
  }

  Myclass bar()
  {
    return Myclass{ 12 };
  }

  int main()
  {
    Myclass m1 = foo();		// output -> Myclass default ctor
    Myclass m2 = bar();		// output -> Myclass(int) ctor

    // No syntax error when user deletes the copy ctor.
    // Because this copy elision becomes mandatory copy elision with C++17.
  }
*/

/*
  --------------------------------------------------------
  | Scenerio 3 (Named Returned Value Optimization)[NRVO] |
  --------------------------------------------------------
  NRVO is NOT a Mandatory copy elision !!!
  for NRVO a callable copy/move ctor is required.

*/

/*
  #include <string>

  std::string get_str()
  {
    std::string str;
    // code... (string manipulations)
    return str;
  }

  int main()
  {
    std::string retval = get_str();
    // In normal, for str object in get_str() function, default ctor will be called.
    // Move ctor will be called for [std::string retval = get_str()] statement.

    // But because of named return value optimization,  str object inside get_str() function
    // we be constructed as retval object.
  }
*/

/*
  class Myclass {
  public:
    Myclass()
    {
      std::cout << "Myclass default ctor\n";
    }
    Myclass(int x) :m_x(x)
    {
      std::cout << "Myclass(int) ctor\n";
    }

    Myclass(const Myclass& other) : m_x(other.m_x)
    {
      std::cout << "Myclass copy ctor\n";
    }

    void print() const
    {
      std::cout << "m_x = " << m_x << '\n';
    }

    void setx(int val)
    {
      m_x = val;
    }
  private:
    int m_x;
  };

  Myclass foo()
  {
    Myclass m{ 12 };
    m.setx(45);
    // code
    m.setx(23);
    return m;
  }

  int main()
  {
    Myclass m1 = foo();
    m1.print();
    // output ->
    //	Myclass(int) ctor
    //	m_x = 23
    // Only int parameter ctor called!!	-> NRVO(Named Return Value Optimization)
  }
*/

/*
  class Myclass {
  public:
    Myclass()
    {
      std::cout << "Myclass default ctor\n";
    }
    Myclass(int x) : m_x(x)
    {
      std::cout << "Myclass(int) ctor\n";
    }

    Myclass(const Myclass& other) = delete;

    void setx(int val)
    {
      m_x = val;
    }
  private:
    int m_x;
  };

  Myclass foo()
  {
    Myclass m{ 12 };
    m.setx(45);
    return m;
    // Because of NRVO is not a mandatory copy elision
    // deleted copy ctor will be a syntax error !!!!
  }

  int main()
  {
    Myclass m1 = foo();
  }
*/

/*
  --------------------
  | pessimistic move |
  --------------------
*/

/*
  class Myclass {
  public:
    Myclass() = default;
    Myclass(const Myclass&) = default;
    Myclass(Myclass&&) = default;

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

  Myclass foo()
  {
    Myclass x;

    return x;
    // return std::move(x);	-> pessimistic move..

    // When returning automatic storage duration object
    // compiler will change L value object to X value object
    // so move assignment will call for this scenerio.
  }

  int main()
  {
    Myclass m1;
    m1 = foo();	// output -> move assignment called
  }
*/

/*
  #include <memory>

  std::unique_ptr<int> foo()
  {
    std::unique_ptr<int> up{ new int };

    return up;	// no syntax error
    // because up will convert L value to X value.
  }

  int main()
  {
    std::unique_ptr<int> up1{ new int };
    std::unique_ptr<int> up2{ new int };

    up1 = up2;			// copy assignment deleted
    auto up3 = up1;			// copy constructor deleted
    // UNIQUE POINTERS ARE MOVE ONLY TYPES!!!

    up1 = std::move(up2);		// move assignment legal
    auto up3 = std::move(up2);	// move constructor legal
  }
*/

/*
  #include <fstream>
  #include <string>

  std::ofstream create_text_file(const std::string& filename)
  {
    std::ofstream ofs{ filename };

    if (!ofs) {
      throw std::runtime_error{ filename + "can not be created!" };
    }

    return ofs;	// move only type
    // because compiler convert L value ofs to X value it won't be a syntax error.
  }

  int main()
  {
    std::ofstream ofs{ "out.txt" };
    if (!ofs) {
      std::cerr << "out.txt can not be created\n";
      exit(EXIT_FAILURE);
    }

    auto x = ofs;				// no copy constructor
    auto y = std::move(ofs);		// move constructor is valid.
    // std::ofstream IS MOVE ONLY TYPE

    std::ofstream fs;

    fs = create_text_file("hello.txt");	// move assignment will be called
  }
*/

/*
  #include <string>

  void foo(std::string s) {}

  void bar(const std::string& s){}

  int main()
  {
    std::string str(100'000, 'A');

    foo(str);
    // foo functions parameter variable copy ctor will be called
    // deep copy will be applied
    bar(str);
    // no ctor will be called.

    // bar(str) will be the winner in this scenerio performance way.
  }
*/

/*
  #include <string>
  #include <algorithm>

  void foo(std::string s)
  {
    std::reverse(s.begin(), s.end());
  }

  void bar(const std::string& s)
  {
    auto sc = s;	// copy ctor will be called.
    std::reverse(sc.begin(),sc.end());
  }

  int main()
  {

    const char* ptr = "hello";

    bar(ptr);
    // temp object will be created for const char* to std::string conversion
    // const std::string& s(parameter variable) will bind to temp object.
    // then inside bar() function we will create its copy.
    // 2 TIME COPY

    foo(ptr);	// only std::string(const char*) ctor will be called
    // 1 TIME COPY

    foo(pr value expression); // copy ellision will be applied
  }
*/

/*
  #include <string>

  class Person {
  public:
    // Person(const std::string& addr) : m_address(addr){}
    // std::string classes copy ctor will be called
    // in initializing phase [m_address(addr)]
    // (IF L value comes) -> REF semantic + copy ctor
    // (IF R value comes) -> REF semantics + copy ctor

    Person(std::string addr) :m_address{std::move(addr)} {}
    // std::string classes move ctor will be called
    // in initializing phase [m_address(addr)]
    // (IF L value comes) -> copy ctor + move ctor
    // (IF R value comes) -> copy ellision + move ctor
  private:
    std::string m_address;
  };

  int main()
  {
    std::string x;

    Person per(x);
  }
*/

/*
  ------------------------
  | reference qualifiers |	// Modern CPP
  ------------------------
*/

/*
  class Myclass {
  public:
    Myclass& operator=(const Myclass&) = default;
    // Myclass& operator=(const Myclass&)& = default;
    void set();
    void set_lref()&;	// only can call with L value objects
  };

  int main()
  {
    Myclass x;
    x.set();			// valid
    Myclass{}.set();		// valid

    Myclass y;
    (x = y).set();			// valid

    x.set_lref();			// valid
    Myclass{}.set_lref();		// not valid
    std::move(x).set_lref();	// not valid

    Myclass{} = y;
    Myclass{}.operator=(y);
    // if we it is valid because compiler's default copy ctor
    // does not have reference qualifier

    // If we add reference qualifier to copy assignment
    // [Myclass& operator=(const Myclass&)& = default]
    // [Myclass{}.operator=(y)] or [Myclass{} = y] are not valid
  }
*/

/*
  class Myclass {
  public:
    void foo()&;		// L value reference qualified
    void bar()&&;		// R value reference qualified
  };

  int main()
  {
    Myclass m;
    m.foo();		// legal
    m.bar();		// not valid

    Myclass{}.foo();	// not valid
    Myclass{}.bar();	// legal
  }
*/

/*
  // we can overload reference qualifiers in non-static member functions

  class Myclass {
  public:
    void foo()&
    {
      std::cout << "foo() for L values\n";
    }

    void foo()const&
    {
      std::cout << "foo() for const L values\n";
    }

    void foo()&&
    {
      std::cout << "foo() for R values\n";
    }
  };

  int main()
  {
    Myclass m;
    m.foo();			// output -> foo() for L values

    Myclass{}.foo();		// output -> foo() for R values
    std::move(m).foo();		// output -> foo() for R values

    const Myclass cm;
    cm.foo();			// output -> foo() for const L values
  }
*/
