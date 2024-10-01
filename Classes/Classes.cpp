#include <iostream>

/*
                          ===========
                          | Classes |
                          ===========
*/

/*
  class Data {};	
  // this is an empty class
  // "Data" is a class tag
*/

/*
  struct Data{
    int x;
  };

  // In C, its type   -> `struct Data`
  // In C++ its type  -> `Data`
*/

/*
  Class Members
  --------------
  1. data members
    -> static data members
    -> non-static data members
  2. member functions
    -> static member functions
    -> non-static member functions
  3. member types (type member - nested type)
*/

/*
  class Data {
    int mx, my;			            // non-static data members
    static double msval 		    // static data member

    void foo(int)			          // non-static member function
    static void func(int,int)	  // static member function

    class Nested{};			        // member type
    using integer = int;		    // member type alias
  };
*/

/*
  1. name lookup
  2. context control
  3. access control
*/

/*
  int x = 10;

  int main()
  {
    int x = x;
    // name lookup starts from block scope
    // initializing local variable "x" with 
    // its garbage(indetermined) value.

    int x = ::x;
    // name lookup starts from global namespace scope.
    // initializing local variable "x" 
    // with global variable "x"s value.
  }
*/

/*
  void func(int);

  int main()
  {
    int func = 5;
    func(19); // syntax error
    // error: 'func' cannot be used as a function

    // name lookup starts from main block scope, it succeeds. 
    // func has been found inside main block scope.
    // context control failed.
  }
*/

/*
  void func(int);

  int main()
  {
    ++func; // syntax error
    // error: lvalue required as increment operand

    // name lookup starts from main block scope,
    // name lookup continues from global namespace scope, it succeeds.
    // func has been found inside global namespace scope.
    // context control failed.
  }
*/

/*
  void foo(double); // promotion 
  void foo(int);    // conversion

  class Myclass {
  private:
    void func(double);  // promotion
  public:
    void func(int);     // conversion
  };


  int main()
  {
    foo(3.4f);
    // foo(double) overload will be called.
    // foo(double)[promotion] > foo(int)[conversion]

    Myclass m;
    m.func(3.4f); // syntax error
    // error: 'void Myclass::func(double)' is private within this context

    // name lookup will start from Myclass's class scope
    // 2 overloads will be found, name lookup succeeds.
    // Overloads : `void func(double)` and `void func(int)`

    // `void func(double)` will be choosen
    // context control succeeds.

    // `void func(double)` functions access specifier is private
    // so function is not accessible from client side (main block scope).
    // access control failed.
  }
*/

/*
  qualified name(nitelenmiş isim) scopes
  ---------------------------------------
  a.x		-> member selection operator ('.')		
    name lookup in a's class scope

  ptr->x		-> member selection operator ('->')		
    name lookup in ptr's class scope

  ::x		-> unary scope resolution operator ('::')	
    name lookup in global namespace scope

  Myclass::x	-> binary scope resolution operator ('::')	
    name lookup in Myclass's(class/namespace) scope
*/

/*
                ---------------------------
                | non-static data members |
                ---------------------------
*/

/*
  class Myclass {
    int a, b;
    // non-static data members are in the instance.
  };

  int main()
  {
    std::cout << "sizeof(Myclass) = " << sizeof(Myclass) << '\n';
    // output -> sizeof(Myclass) = 8
  }
*/

/*
  class Myclass {};

  int main()
  {
    std::cout << "sizeof(Myclass) = " << sizeof(Myclass) << '\n';
    // output -> sizeof(Myclass) = 1
  }
*/

/*
  class Myclass {
    static int x;
    static int y;
    // static data members are not in the instance.
  };

  int main()
  {
    std::cout << "sizeof(Myclass) = " << sizeof(Myclass) << '\n';
    // output -> sizeof(Myclass) = 1
  }
*/

/*
                    --------------------
                    | member functions |
                    --------------------
*/

/*
  class Myclass {
    void func(int, int);
    void foo(double);
  };

  int main()
  {
    std::cout << "sizeof(Myclass) = " << sizeof(Myclass) << '\n';
    // output -> sizeof(Myclass) = 1
  }
*/

/*
  void func(int, int);
  // free function || global function ||stand-alone function

  class Myclass {
  public:
    int func(int)		// member function
    {
      return 11;
    }
  private:
    int mx;
  };

  int main()
  {
    Myclass m;
    int b  = m.func(5);
    std::cout << "b = " << b << '\n';   // output -> b = 11
  }
*/

/*
  // C and C++ ways to define and call member functions
  // even if C does not have member functions.

  // ------- C Code -------
  struct Data {
    int x, y, z;
  };

  void foo(struct Data* p,int);	// global namespace scope
  // ------- C Code -------

  // ------- C++ Code -------
  class Myclass {
  public:
    void func(int);		// class scope
    // void func(Myclass* p, int) -> hidden parameter is Myclass*
  };
  // ------- C++ Code -------

  int main()
  {
    // ------- C Code -------
    struct Data mydata = { 2, 5, 8 };
    foo(&mydata,12);
    // ------- C Code -------

    // ------- C++ Code -------
    Myclass m;
    m.func(12);

    Myclass* p{ &m };
    p->func(12);
    // ------- C++ Code -------
  }
*/

/*
  class Myclass {
  public:
    void foo();
  private:
    int mx;
  };

  void g_foo(Myclass* p)
  {
    p->foo();   // VALID
    // name lookup succeeds.
    // context control succeeds.
    // access control succeeds.

    auto var = p->mx;	// syntax error
    // error: 'int Myclass::mx' is private within this context

    // name lookup succeeds.
    // context control succeeds.
    // access control failed.
  }

  void g_bar(Myclass& r)
  {
    r.foo();    // VALID
    // name lookup succeeds.
    // context control succeeds.
    // access control succeeds.

    auto var = r.mx;	// syntax error
    // error: 'int Myclass::mx' is private within this context

    // name lookup succeeds.
    // context control succeeds.
    // access control failed.
  }

  int main()
  {
    Myclass m;

    g_foo(&m);
    g_bar(m);
  }
*/

/*
                        ---------------------
                        | access specifiers |
                        ---------------------
*/

/*
  class Myclass {
  public:     // public access specifier
    class NestedPublic {};
    int mx;
    void foo();
    
  private:    // private access specifier
    class NestedPrivate {};
    int my;
    void bar();

  protected:  // protected access specifier
    class NestedProtected {};
    int mz;
    void baz();
  };

  int main()
  {
    Myclass m;

    // ------------------------------------------------------------

    Myclass::NestedPublic nested_public;        // VALID
    auto var = m.mx;                            // VALID
    m.foo();                                    // VALID
    // NestedPublic class(member type) is in public section.
    // It can be accessed from client side.

    // ------------------------------------------------------------

    Myclass::NestedPrivate private_nested;      // syntax error
    // error: 'class Myclass::NestedPrivate' is 
    // private within this context

    auto var = m.my;                            // syntax error
    // error: 'int Myclass::my' is private within this context

    m.bar();                                    // syntax error
    // error: 'void Myclass::bar()' is private within this context

    // NestedPrivate class(member type) is in private section.
    // It can not be accessed from client side.

    // ------------------------------------------------------------

    Myclass::NestedProtected protected_nested;  // syntax error
    // error: 'class Myclass::NestedProtected' is 
    // protected within this context

    auto var = m.mz;                            // syntax error
    // error: 'int Myclass::mz' is protected within this context

    m.baz();                                    // syntax error
    // error: 'void Myclass::baz()' is protected within this context

    // NestedProtected class(member type) is in private section.
    // It can not be accessed from client side.

    // ------------------------------------------------------------
  }
*/

/*
  // myclass.h
  // ----------------
  class Myclass {
  public:
    void bar(int x) // implicitly inline member function definition.
    {
      // ...
      // ...
    }

    void func(int x);		// member function declaration
    void foo(double x); // member function declaration

    inline void baz(float x);	// inline member function declaration
  };

  void Myclass::func(int x)
  {
    // Member function definition outside the class scope in 
    // same header(.h) file.
    // Myclass::func will not be implicitly inline. 
    // It will violate ODR(One Definition Rule). 
  }

  inline void Myclass::foo(double x)
  {
    // inline member function definition outside the class scope
    // in same header(.h) file.
    // It will NOT violate ODR.
  }

  void Myclass::baz(float x)
  {
    // Member function declaration is inline.
    // Member function definition is outside the class scope in 
    // same header(.h) file.
    // It will NOT violate ODR.
  }

  inline void f1(int x)
  {
    // this is a global function, not a member function.
  }

  // For creating header only module, we need to define all 
  // member functions inline in header file for not violating ODR.
*/

/*
  // myclass.h
  // ----------------
  class Myclass {
  public:
    void func(int x);	// class scope
  };


  // myclass.cpp
  // ----------------
  #include "myclass.h"
  void func(double x)
  {
    // global namespace scope
  }
  // These functions are not overloads, their scopes are different.
*/

/*
  class ABC {
  public:
    void func(ABC a, int x);
  private:
    int mx;
  };

  ABC g_a;

  void ABC::func(ABC a, int x)
  {
    // ABC class's private section is always open 
    // for its non-static member functions.

    // -----------------------------------------------------

    int val = a.mx;
    // reaching parameter variable ABC object's private data member
    // inside ABC class's non-static member function.

    // -----------------------------------------------------

    g_a.mx = 32452;
    // reaching global ABC class object's private data member
    // inside ABC class's non-static member function

    // -----------------------------------------------------

    ABC local_obj;
    local_obj.mx = 12;
    // reaching local ABC class object's private data member
    // inside ABC class's non-static member function.

    // -----------------------------------------------------

    mx = 24;
    this->mx = 24;
    ABC::mx = 24;
    // These 3 lines are equivalent.
    // reaching ABC class's private data member 
    // inside ABC class's non-static member function.

    // -----------------------------------------------------

    int mx = 12;
    mx = x;
    // declaring a local variable with same name as ABC class's
    // data member, name lookup phase will start from the local scope
    // and it will find the local variable.
    // Because of it founds local variable, name lookup phase will stop.
    // Local mx variable will hide ABC class's data member.
    // Assignment will be done to local variable.

    // -----------------------------------------------------
  }
*/

/*
  class Myclass {
  public:
    void func(int x);
  private:
    int mx;		// private data member
  };

  int mx;			// global variable

  void Myclass::func(int x)
  {
    int mx;		// local variable
    mx = 12;
    // assignment to local variable.

    ::mx = 14;  // ("::op1" unary scope resolution operator)
    // assignment to global variable.

    Myclass::mx = 20; // ("op1::op2" binary scope resolution operator)
    // assignment to Myclass's private data member
    // inside Myclass's non-static member function.
  }
*/

// continue from here

/*
  // algo.h
  class Algo {
  public:
    int foo(int x);
    int bar(int x);
  private:
    int mx = 0;
  };

  // algo.cpp
  // #include "algo.h"
  int Algo::foo(int x)
  {
    return bar(x);
    // namelookup will start in local scope
    // will continue in class scope.

    // Algo will send hidden parameter (Algo*) to bar() member function.
  }

  int Algo::bar(int x)
  {
    mx = x + 4;
    return mx;
  }

  int main()
  {
    Algo a;
    int b = a.foo(15);
    std::cout << "b = " << b << '\n';
  }
*/

/*
  class Myclass {
  public:
    void foo();
  private:
    int mx;
  };

  int foo(int x);

  void Myclass::foo()
  {
    foo(3);	// syntax error

    // namelookup will start from local scope [NOT FOUND]
    // will continue in class scope	[FOUND]
    // member function foo do not have an int parameter. [context control phase error]

    ::foo(3); // legal
    // namelookup directly starts from global namespace scope.

    foo(); // legal
    Myclass::foo() // legal
    // These 2 lines are same
    // recursive function call.
  }
*/

/*
  class Algo {
  public:
    void foo(int);
  private:
    int foo;
  };
  // sythax error
  // private, public and protected sections are in the same scope(class scope).

  class Algo {
  public:
    void foo(int);
  private:
    void foo(double);
  };
  // 2 function overloads because of same scope.
*/

/*
  int foo(int);
  int foo(int);
  // function redecleration is possible in global scope

  class Myclass {
  public:
    int bar(int);
    int bar(int);	// syntax error
  };
  // function redecleration IS NOT possible in class scope
*/

/*
  class Myclass {
  public:
    int foo(int);
  private:
    int foo(double);
  };

  int main()
  {
    Myclass mx;
    mx.foo(2.3); // syntax error

    // 1. name-lookup control
    // There are 2 overloads of foo() member function in class scope
    // 2. context control
    // Because of int(int) is conversion and int(double) is exact match
    // int(double) will be chosen
    // 3. access control
    // The chosen overload [int(double)] in private section
    // can not be accessed from global scope it will be sythax error.
  }
*/

/*
  class Myclass {
  public:
    int foo(int);
  private:
    int foo(double);

    // This kind of function overloads(1 in public, 1 in private section)
    // can be used for calling them from another member functions of class.
    // class member functions can reach classes private section.
    void bar()
    {
      foo(12);
      foo(1.2);
    }
  };
*/

/*
  class Myclass {
    int foo()
    {
      int mx{};

      mx = 5;			// local variable
      Myclass::mx = 5;	// data member
    }
    int mx;
  };
*/

/*
  ----------------
  | this pointer |
  ----------------
*/

/*
  this is a keyword and its value category is PR value expression
  this is a pointer.
  using this pointer in classes static member function is syntax error.
  using this pointer in global function is syntax error.
*/

/*
  class Myclass {
  public:
    void func()
    {
      std::cout << "this = " << this << '\n';  // output -> this = 009BFE2F
      foo();
    }

    void foo()
    {
      std::cout << "this = " << this << '\n';  // output -> this = 009BFE2F
    }
  };

  int main()
  {
    Myclass mx;
    std::cout << "&mx = " << &mx << '\n'; // output -> &mx = 009BFE2F
    mx.func();
  }
*/

/*
  class Myclass {
  public:
    void foo();
  };

  void Myclass::foo()
  {
    Myclass mx;
    this = &mx;		// syntax error.
    auto x = &this;		// syntax error
    // this is a PR value expression.
  }
*/

/*
  class Myclass {
  public:
    void foo();
    void bar();
  private:
    int mx;
  };

  void Myclass::foo()
  {
    mx = 10;
    this->mx = 10;
    Myclass::mx = 10;
    // These 3 lines are same.

    bar();
    this->bar();
    Myclass::bar();
    // These 3 line are same.
  }
*/

/*
  class Myclass {
  public:
    void func();
  private:

    int x;
    int y;
    int z;
  };

  void f1(Myclass*);
  void f2(Myclass&);
  void f3(Myclass);

  void Myclass::func()
  {
    f1(this);
    f2(*this);
    f3(*this);
  }
*/

/*
  // C code
  typedef struct {
    int a, b, c;
  }Myclass;

  Myclass* foo(Myclass* p)
  {
    // code here...
    return p;
  }
  void bar(Myclass*);


  // C++ Code
  class Yourclass {
  public:
    Yourclass& foo()
    {
      // code here...
      return *this;
    }
    Yourclass& bar()
    {
      // code here...
      return *this;
    }
    Yourclass& baz()
    {
      // code here...
      return *this;
    }
  };

  int main()
  {
    // C Code
    Myclass mx = { 43,46,98 };
    bar(foo(&mx));
    // sending the address of object returns from foo() function to bar() function.

    // C++ Code
    Yourclass yx;
    yx.foo().bar().baz();	// Chaining
  }
*/

/*
  int main()
  {
    int ival{ 432 };
    double dval{ 23.22 };

    std::cout << ival << dval;
    std::cout.operator<<(ival).operator<<(dval);	// Chaining

    std::cout.operator<<(ival);			// returns std::ostream&
    std::cout.operator<<(ival).operator<<(dval);	// returns std::ostream&
    // There is function overloading in operator<< functions	[int, double]
  }
*/

/*
  --------------------------
  | const member functions |
  --------------------------
*/

/*
  class Myclass{};

  void func(Myclass&);		// mutator
  void func(const Myclass&);	// accessor

  void foo(Myclass* p);		// mutator
  void foo(const Myclass* p);	// accesssor
*/

/*
  // C code
  struct Data {
    int a, b, c;
  };

  void foo(struct Data*);

  void func(const struct Data* p)
  {
    struct Data* ptr;
    *p = ptr;	// syntax error
    p->a = 12;	// syntax error

    struct Data* ptr = p;
    // C++ sytax error
    // C legal

    foo(p);	// conversion from const T* to T*
    // C++ sytax error
    // C legal
  }
*/

/*
  class Myclass {
  public:
    void foo();		// non-const member function
    void bar()const;	// const member function
    // const makes this pointer const.

    void baz()const;
  private:
    int mx;
  };

  Myclass gx;

  void Myclass::bar()const
  {
    mx = 20;		// syntax error
    this->mx = 20;		// syntax error
    Myclass::mx = 20;	// syntax error
    // These 3 lines are same.
    // We are trying to change data member(mx) of the Myclass object that, this pointer points to.

    Myclass m;
    *this = m;		// syntax error

    gx.mx = 15;		// legal
    // this pointer points to the address of Myclass object
    // which called bar() const member function.

    // changing gx objects(different object)(this pointer is not pointing gx)
    // is perfectly legal.

    foo();			// syntax error.
    // hidden parameter(this pointer) is const Myclass*
    // when we call foo() function which is non-const member function
    // and its hidden parameter is Myclass*
    // we are forcing conversion from const T* to T*, which is syntax error.

    baz();			// legal
    // baz() is const member function so
    // sending const T*(hidden parameter)(this pointer) to const T* is legal.

    CALLING NON CONST MEMBER FUNCTION INSIDE CONST MEMBER FUNCTION IS NOT LEGAL!!
  }

  void Myclass::foo()	// non-const member function
  {
    bar();	// const member function
    // conversion from const T*(hidden parameter)(this pointer) to T* is legal.

    CALLING CONST MEMBER FUNCTION INSIDE NON CONST MEMBER FUNCTION IS LEGAL!!
  }
*/

/*
  class Myclass {
  public:
    void foo();
    void bar()const;
  private:
    int mx;
  };

  int main()
  {
    const Myclass cm;

    // &cm -> const Myclass* (we are sending &cm to function's hidden variable)
    cm.foo();	// syntax error. 	sending (const T*) to (T*) is		NOT LEGAL
    cm.bar();	// legal		sending (constT*) to (const T*)		LEGAL

    Myclass m;
    m.foo();	// legal		sending (T*) to (T*)			LEGAL
    m.bar();	// legal		sending (T*) to (const T*) [conversion]	LEGAL
  }
*/

/*

  1. const member functions can not change non-static data members.
  2. const member functions can not call non-const member functions.
  3. we can not assign *this object to any value in const member functions.
  4. const class objects can only call const member functions.
*/

/*
  class Myclass {
  public:
    void foo()
    {
      std::cout << "void Myclass::foo()\n";
    }

    void foo()const
    {
      std::cout << "void Myclass::foo()const\n";
    }
    // These functions are overloads(const overload)
  };

  int main()
  {
    Myclass m;
    const Myclass cm;

    m.foo();	// output -> void Myclass::foo()
    cm.foo();	// output -> void Myclass::foo()const
  }
*/

/*
  #include <vector>

  int main()
  {
    using namespace std;

    vector<int> ivec{ 1,2,3,5,6 };
    const vector<int> civec{ 1,2,3,5,6 };

    ivec.at(2) = 99;	// legal
    civec.at(2) = 99;	// syntax error

    // at() member function have 2 overloads(const overloads).

    // const overload returns const int& -> assigning a value is not legal.
    // non-const overload returns int&

    ++ivec.front();		// legal
    ++civec.front();	// syntax error
  }
*/

/*
  class Myclass {
  public:
    Myclass* foo()const
    {
      return this;	// syntax error
      // this pointer is const Myclass*
      // trying to conversion from const T* to T* is not valid.
    }

    Myclass& bar() const
    {
      return *this;	// syntax error.
    }
  };
*/

/*
  -------------------
  | mutable keyword |
  -------------------
*/

/*
  class Fighter {
  public:
    void attack()
    {
      ++debug_call_count;
    }
    void defend()
    {
      ++debug_call_count;
    }
    std::string get_name()const
    {
      ++debug_call_count;
    }
  private:
    mutable int debug_call_count;
    // debug_call_count data members value did not have a relation with Fighter objects state.
  };

  // In problem domain changing debug_call_count is not changing the state of the object.
  // Its only purpose is increasing the call_count in every call to member functions.
  // But because of debug_call_count is a data member of our Fighter class,
  // in const member functions we can not change data member's value
  // for these kind of situations we use MUTABLE keyword.
  // mutable data member is independent from other data members of this class.

  class Date {
    int m_day;
    int m_month;
    int m_year;
  };

  // if we make m_year data member mutable. It does not make sense.
  // Our Date class depends on m_year.
*/

/*
  #include <mutex>

  class RandomEngine {
  public:
    int generate();
    // non-const member function. It is changing RandomEngines state.

    void discard(int n);
    // non-const member function. It is changing RandomEngines state.
  };

  class Algo {
  public:
    void func()
    {
      auto ival = eng.generate();
      eng.discard(1);
    }

    void foo()const
    {
      auto val = eng.generate();
      eng.discard(1);
      // if const function have to change eng state too..
      // we can use mutable keyword in our RandomEngine data member.
    }
  private:
    mutable RandomEngine eng;
  };

  class Myclass {
  public:
    void foo()
    {
      mtx.lock();
      // code...
      mtx.unlock();
    }

    void func() const
    {
      mtx.lock();
      // code...
      mtx.unlock();
    }
  private:
    mutable std::mutex mtx;
  };

  int main()
  {
    const RandomEngine eng;
    eng.generate();	// syntax error
    // calling non const member function with const RandomEngine object
    // trying to force conversion from hidden parameter (const T*) to (T*)
  }
*/

/*
  ----------------------------
  | constructor & destructor |
  ----------------------------
*/

/*
  CONSTRUCTOR (CTOR)	Myclass()
  -------------------------------
  1. ctor's identifier should be same as class identifier.
  2. there is no return value concept for constructors.
  3. constructor has to be a non-static member function.
    Can not be a global function or a static member function.
  4. constructor can not be a const member function.
  5. constructor can not be called with .(dot) or ->(arrorw) [member selection] operators.
  6. constructors can be in classes public, private and protected sections
  7. constructors can be overloaded.
*/

/*
  class Myclass {
  public:
    Myclass();
    void func();
  };

  int main()
  {
    Myclass m;
    Myclass* p = &m;

    m.func();	// valid
    p->func();	// valid

    m.Myclass();	// sytax error
    p->Myclass();	// syntax error
  }
*/

/*
  class Myclass {
  public:
  private:
    Myclass();
  };

  int main()
  {
    Myclass m;	// syntax error
    // access control error.
  }
*/

/*
  class Myclass {
  public:
    Myclass();
    Myclass(int);
    Myclass(int,int);
    Myclass(double);
  };
*/

/*
  DESTRUCTOR (DTOR)	~Myclass()
  --------------------------------
  1. dtor's identifier should be same as class identifier.
  2. there is no return value concept for destructors.
  3. destructor has to be a non-static member function.
    Can not be a global function or a static member function.
  4. destructor can not be a const member function.
  5. destructor can be in classes public, private and protected sections
  6. destructor can not be overloaded
    class can only have a destructor without parameter.
  7. destructor can be called with .(dot) or ->(arrorw) [member selection] operators.
    mostly we are not calling destructor with member selection operators.
*/

/*
  -------------------------------------------------------
  | RAII idiom (Resource Acquisition Is Initialization) |
  -------------------------------------------------------

  -> Ctor will get the resources of that class object will use.
  -> Dtor will release the resources that class object have been used.

  ctor will allocate memory in heap (dynamic memory allocation)
  dtor will gave back the memory (free)

  ctor will open a file.
  dtor will close a file.

  ctor will create a database connection
  dtor will end database connection

  ctor will lock mutex
  dtor will unloack mutex

  -> stl container classes, smart pointers, string class
*/

/*
  default constructor
  --------------------
  1. a no parameter constructor
  OR
  2. it's all parameters have default arguments.
*/

/*
  class Myclass{
  public:
    Myclass();		//default ctor
  };

  class Yourclass{
  public:
    Yourclass(int x = 0);	//default ctor
  };
*/

/*
  special member functions
  ------------------------
  -> default ctor
  -> destructor
  -> copy ctor
  -> move ctor		(C++11)
  -> copy assignment
  -> move assignment	(C++11)

  COMPILER CAN DEFAULT SPECIAL MEMBER FUNCTIONS!
*/

/*
  void func(double) = delete;		// global functions

  class Myclass {
  public:
    void foo(int) = delete;		// non-static member function
  };

  // Deleted functions are declared functions
  // but calling deleted function is a sythax error.

  int main()
  {
    Myclass m;
    m.foo(12);	//syntax error
    // function "Myclass::foo(int)"cannot be referenced, it is a deleted function

    func(5.4);	// syntax error
    // function "func(double)"cannot be referenced, it is a deleted function
  }

  // If you not declare a function instead of deleting it,
  // it is still a syntax error but it is because of namelookup phase(undefined identifier).
*/

/*
  void func(int);
  void func(long);
  void func(double) = delete;
  // There are 3 overloads of this function.
  // Deleting DOES NOT mean the function does not exists.
  // Deleted functions will join Function Overload Resolution.

  int main()
  {
    func(12);	// legal
    func(12L);	// legal
    func(3.4);	// syntax error
    // in namelookup phase [func(double)] overload will be chosen for func(3.4) call.
    // Because of func(double) is deleted it is a syntax error.
  }
*/

/*
  Special Member Functions can be
  -------------------------------
  1. Not declared
  2. User declared
  3. Implicitly declared
    -> Implicitly declared defaulted
    -> Implicitly declared deleted
*/

/*
  // 1. Not declared

  class Myclass {
  public:
    Myclass(int);
    // If we declare any constructor other than the default ctor
    // there won't be any default ctor. (NOT DECLARED)
  };

  int main()
  {
    Myclass m;	// syntax error
    // no default constructor exists for class "Myclass"
  }
*/

/*
  // 2. User declared

  class A {
    A();
    // user declared default ctor and will also define it.
  };

  class B {
    B() = default;
    // default decleration means, compiler will write
    // user declared default constructors code.
  };

  class C {
    C() = delete;
    // delete decleration means, calling this user declared ctor
    // will be a syntax error.
  };
*/

/*
  // 3. Implicitly declared

    // -> Implicitly declared defaulted
  class Myclass {
  public:
    // all 6 special member functions are implicitly declared defaulted.
  };

    // -> Implicitly declared deleted
  class Yourclass {
  public:
  private:
    const int mx;
  };

  int main()
  {
    Yourclass y;	// syntax error
    // C2280 'Yourclass::Yourclass(void)': attempting to reference a deleted function
    // default ctor is, implicitly declared deleted special member function.
    // because of const data member can not be default initialize default ctor will throw sythax error
    // compiler will implicitly delete default constructor.
  }
*/

/*
  STORAGE CLASSES (LIFETIME)
  ==========================
  -> static storage class
  -> automatic storage class

  -> dynamic storage class
  -> thread local storage class (concurrency)
*/

/*
  ==========================
  | STATIC STORAGE CLASSES |
  ==========================
*/

/*
  --------------------
  | global variables |
  --------------------
*/

/*
  class Myclass {
  public:
    Myclass()
    {
      std::cout << "Myclass default ctor.. this: " << this << '\n';
    }

    ~Myclass()
    {
      std::cout << "Myclass dtor.. this: " << this << '\n';
    }
  };

  class Yourclass {
  public:
    Yourclass()
    {
      std::cout << "Yourclass default ctor.. this: " << this << '\n';
    }

    ~Yourclass()
    {
      std::cout << "Yourclass dtor.. this: " << this << '\n';
    }
  };


  Myclass m;	// global variable
  Yourclass y;	// global variable

  // global variables will be created from top to bottom.
  // FIRST IN LAST OUT prinsible applied.

  int main()
  {
    std::cout << "int main() scope starts" << '\n';

    std::cout << "int main() scope ends" << '\n';
  }

  // Myclass default ctor.. this: 0048F138	-> FIRST IN
  // Yourclass default ctor.. this : 0048F139
  // int main() scope starts
  // int main() scope ends
  // Yourclass dtor.. this : 0048F139
  // Myclass dtor.. this : 0048F138		-> LAST OUT
*/

/*
  --------------------------------
  | static initialization fiasco |
  --------------------------------
*/

/*
  // Every global variable will be constructed before main() function called.
  // But there is NO guarantee which global variable will become alive first!

  first.cpp
  ---------------
  F fx;

  second.cpp
  ---------------
  S sx;

  third.cpp
  ---------------
  T tx;

  eight.cpp
  ---------------
  E ex;

  main.cpp
*/

/*
  first.cpp
  ---------------
  F g_fx;

  extern S g_sx;
  F::F()
  {
    sx.xyz();
  }

  // When g_fx variable depends on g_sx variable.
  // If g_sx become alive before g_fx become alive there will be no problem.
  // But there is no guarantee that g_sx will become alive first!!!

  second.cpp
  ---------------
  S g_sx;

  third.cpp
  ---------------
  T g_tx;

  eight.cpp
  ---------------
  E g_ex;

  main.cpp


  --------------------------------
  std::cout is also a global variable.
  Static initialization fiasco do not effect to std::cout global variable
  -> schwarz idiom - nifty counter.
*/

/*
  --------------------------
  | static local variables |
  --------------------------
*/

/*
  class Myclass {
  public:
    Myclass()
    {
      std::cout << "Myclass default ctor.. this: " << this << '\n';
    }

    ~Myclass()
    {
      std::cout << "Myclass dtor.. this: " << this << '\n';
    }
  };

  class Yourclass {
  public:
    Yourclass()
    {
      std::cout << "Yourclass default ctor.. this: " << this << '\n';
    }

    ~Yourclass()
    {
      std::cout << "Yourclass dtor.. this: " << this << '\n';
    }
  };

  void f1()
  {
    static Myclass mx;
  }

  void f2()
  {
    static Yourclass yx;
  }

  int main()
  {
    std::cout << "int main() scope starts" << '\n';

    std::cout << "int main() scope ends" << '\n';
  }
  // output ->
  //	int main() scope starts
  //	int main() scope ends

  // static local variables are not alive because f1() or f2() did not called.
*/

/*
  class Myclass {
  public:
    Myclass()
    {
      std::cout << "Myclass default ctor.. this: " << this << '\n';
    }

    ~Myclass()
    {
      std::cout << "Myclass dtor.. this: " << this << '\n';
    }
  };

  void f1()
  {
    static Myclass mx;
  }

  int main()
  {
    std::cout << "int main() scope starts" << '\n';
    f1();
    std::cout << "int main() scope ends" << '\n';
  }
  // output ->
  //	int main() scope starts
  //	Myclass default ctor.. this: 0017E140
  //	int main() scope ends
  //	Myclass dtor.. this : 0017E140
*/

/*
  class Myclass {
  public:
    Myclass()
    {
      std::cout << "Myclass default ctor >> this: " << this << '\n';
    }

    ~Myclass()
    {
      std::cout << "Myclass dtor >> this: " << this << '\n';
    }
  };

  void foo()
  {
    static int call_count{};
    std::cout << ++call_count << ". call for foo() function\n";
    static Myclass m;
  }

  int main()
  {
    std::cout << "int main() scope starts" << '\n';
    foo();
    foo();
    foo();
    std::cout << "int main() scope ends" << '\n';
  }

  // output ->
  //	int main() scope starts
  //	1. call for foo() function
  //	Myclass default ctor >> this: 005AE144
  //	2. call for foo() function
  //	3. call for foo() function
  //	int main() scope ends
  //	Myclass dtor >> this : 005AE144
*/

/*
    ============================
    | AUTOMATIC STORAGE CLASS  |
    ============================

    1.functions local variables
    2.local and non-static variables in block scopes
*/

/*
  class Myclass {
  public:
    Myclass()
    {
      std::cout << "Myclass default ctor >> this: " << this << '\n';
    }

    ~Myclass()
    {
      std::cout << "Myclass dtor >> this: " << this << '\n';
    }
  };

  void foo()
  {
    std::cout << "foo statement 1\n";
    Myclass m;
    std::cout << "foo statement 2\n";
  }

  void func()
  {
    std::cout << "func statement 1\n";

    {
      Myclass m;
    }

    std::cout << "func statement 2\n";
  }

  int main()
  {
    std::cout << "int main() scope starts" << '\n';
    foo();
    func();
    std::cout << "int main() scope ends" << '\n';
  }
  // output ->
  //	int main() scope starts
  //	foo statement 1
  //	Myclass default ctor >> this: 0053FA97
  //	foo statement 2
  //	Myclass dtor >> this : 0053FA97
  //	func statement 1
  //	Myclass default ctor >> this : 0053FAA3
  //	Myclass dtor >> this : 0053FAA3
  //	func statement 2
  //	int main() scope ends
*/

/*
  class Myclass {
  public:
    Myclass()
    {
      std::cout << "Myclass default ctor >> this: " << this << '\n';
    }

    ~Myclass()
    {
      std::cout << "Myclass dtor >> this: " << this << '\n';
    }
  };

  class Yourclass {
  public:
    Yourclass()
    {
      std::cout << "Yourclass default ctor >> this: " << this << '\n';
    }

    ~Yourclass()
    {
      std::cout << "Yourclass dtor >> this: " << this << '\n';
    }
  };

  int main()
  {
    std::cout << "int main() scope starts" << '\n';
    for (size_t i = 0; i < 3; i++)
    {
      static Yourclass yx;
      Myclass mx;
    }
    std::cout << "int main() scope ends" << '\n';
  }

  // output ->
  //	int main() scope starts
  //	Yourclass default ctor >> this : 006BE140
  //	Myclass default ctor >> this: 0135FB2B
  //	Myclass dtor >> this : 0135FB2B
  //	Myclass default ctor >> this : 0135FB2B
  //	Myclass dtor >> this : 0135FB2B
  //	Myclass default ctor >> this : 0135FB2B
  //	Myclass dtor >> this : 0135FB2B
  //	int main() scope ends
  //	Yourclass dtor >> this : 006BE140
*/

/*
  class Myclass {
  public:
    Myclass()
    {
      std::cout << "Myclass default ctor >> this: " << this << '\n';
    }

    ~Myclass()
    {
      std::cout << "Myclass dtor >> this: " << this << '\n';
    }
  private:
    int x, y, z, k;
  };

  int main()
  {
    std::cout << "int main() scope starts" << '\n';
    Myclass marr[5];
    std::cout << "int main() scope ends" << '\n';
  }

  // output ->
  //	int main() scope starts
  //	Myclass default ctor >> this : 00A6FB84
  //	Myclass default ctor >> this : 00A6FB94
  //	Myclass default ctor >> this : 00A6FBA4
  //	Myclass default ctor >> this : 00A6FBB4
  //	Myclass default ctor >> this : 00A6FBC4
  //	int main() scope ends
  //	Myclass dtor >> this : 00A6FBC4
  //	Myclass dtor >> this : 00A6FBB4
  //	Myclass dtor >> this : 00A6FBA4
  //	Myclass dtor >> this : 00A6FB94
  //	Myclass dtor >> this : 00A6FB84
*/

/*
  // Print from 0 to 100

  struct Puzzle {
    Puzzle()
    {
      static int x = 0;
      std::cout << x++ << ' ';
    }
  };

  int main()
  {
    Puzzle arr[100];
  }
*/

/*
    =========================
    | DYNAMIC STORAGE CLASS |
    =========================
    | new / delete keyword  |
    -------------------------
*/

/*
  class Myclass {
  public:
    Myclass()
    {
      std::cout << "Myclass default ctor >> this: " << this << '\n';
    }

    ~Myclass()
    {
      std::cout << "Myclass dtor >> this: " << this << '\n';
    }
  };

  int main()
  {
    std::cout << "int main() started\n";
    auto p = new Myclass;
    std::cout << "main() goes on..[1]\n";
    delete p;
    std::cout << "main() goes on..[2]\n";
  }

  // int main() started
  // Myclass default ctor >> this: 0000021754247470
  // main() goes on..[1]
  // Myclass dtor >> this : 0000021754247470
  // main() goes on..[2]
*/

/*

  void* malloc(size_t n);
  void* operator new(size_t n);

  void free(void*);
  void operator delete(void*);

  new operator(new expression) and operator new(std)function are different!
  delete operator(delete expression) and operator delete(std) functions are different!

  operator new function can be fail! If it fails, it will throw an exception!
  malloc (C) can be failed too. But when it fails, it will return null pointer (NULL)
*/

/*
  // for x86 system
  #include <new>
  #include <vector>

  std::vector<void*> vec;

  int main()
  {
    try
    {
      for (int i = 0; i < 1'000'000; ++i)
      {
        void* vp = operator new(1024u * 1024u);
        vec.push_back(vp);
        std::cout << i << '\n';
      }
    }
    catch (const std::exception& ex)
    {
      std::cout << "execption caught: " << ex.what() << '\n';
    }
  }
*/

/*
  ----------pseudo code-----------

  auto p = new Fighter;
  void* vp = operator new(sizeof(Fighter));			// call operator new	-> resource allocation
  Fighter* p = (static_cast<Fighter*>(vp))->Figher();		// call constructor

  delete p;
  p->~Fighter();							// call destructor
  operator delete(p);						// call operator delete	-> resource deallocation
*/

/*
  class Myclass {
  public:
    Myclass()
    {
      std::cout << "Myclass default ctor >> this: " << this << '\n';
    }

    ~Myclass()
    {
      std::cout << "Myclass dtor >> this: " << this << '\n';
    }
  };

  int main()
  {

    Myclass m0;	// default initialization.
    // classes default ctor will be called.
    //	-> if default ctor is in private section	-> syntax error
    //	-> if default ctor is deleted			-> syntax error
    //	-> if default ctor is not declared		-> syntax error
    // classes data members have intedermined values.

    Myclass m1{};	// value initialization
    // classes default ctor will be called.
    // first zero init apllied for class data members.

    Myclass m[10];
    // for every member in c style array will call default ctor.
  }
*/

/*
  class Myclass {
  public:
    Myclass() = default;
    Myclass(int x)
    {
      std::cout << "Myclass(int x) x = " << x << " this = " << this << '\n';
    }
  };

  int main()
  {

    Myclass m1(1);		// direct initialization
    // output -> Myclass(int x) x = 1 this = 004FFE87
    // narrowing conversion IS VALID (warning but not syntax error)

    Myclass m2{ 2 };	// direct list initialization
    // can not send 2.3(dobule) in direct list initalization  -> narrowing conversion IS NOT VALID
    // output -> Myclass(int x) x = 2 this = 004FFE7B
    // Myclass m2{2.3}; will be syntax error

    Myclass m3 = 3;		// copy initialization
    // output -> Myclass(int x) x = 3 this = 004FFE6F
    // narrowing conversion IS VALID (warning but not syntax error)
  }
*/
