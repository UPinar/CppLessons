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
    int mx, my;                 // non-static data members
    static double msval         // static data member

    void foo(int)               // non-static member function
    static void func(int,int)   // static member function

    class Nested{};             // member type
    using integer = int;        // member type alias
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
  void foo(double);     // promotion
  void foo(int);        // conversion

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
  a.x         -> member selection operator ('.')
    name lookup in a's class scope

  ptr->x      -> member selection operator ('->')
    name lookup in ptr's class scope

  ::x         -> unary scope resolution operator ('::')
    name lookup in global namespace scope

  Myclass::x  -> binary scope resolution operator ('::')
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
    int func(int)   // member function
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

  void foo(struct Data* p,int); // global namespace scope
  // ------- C Code -------

  // ------- C++ Code -------
  class Myclass {
  public:
    void func(int);   // class scope
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

    void func(int x);   // member function declaration
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
    int mx;   // private data member
  };

  int mx;     // global variable

  void Myclass::func(int x)
  {
    int mx;   // local variable
    mx = 12;
    // assignment to local variable.

    ::mx = 14;        // ("::op1" unary scope resolution operator)
    // assignment to global variable.

    Myclass::mx = 20; // ("op1::op2" binary scope resolution operator)
    // assignment to Myclass's private data member
    // inside Myclass's non-static member function.
  }
*/

/*
  // algo.h
  // ----------------
  class Algo {
  public:
    int foo(int x);
    int bar(int x);
  private:
    int mx = 0;
  };

  // algo.cpp
  // ----------------
  // #include "algo.h"
  int Algo::foo(int x)
  {
    return bar(x);
    // name lookup will start from local scope
    // will continue from class scope.

    // "foo" and "bar" functions are non-static member functions
    // when "bar" function is called from "foo" function
    // hidden parameter (Algo*) will be sent to bar() function.
    // bar(Algo*, int) will be the underlying function call.
  }

  int Algo::bar(int x)
  {
    mx = x + 4;
    // name lookup will start from local scope, failed.
    // will continue from class scope, succeeded.

    // Algo class's private data member is accessible from
    // Algo class's non-static member function.
    return mx;
  }

  // main.cpp
  // ----------------
  // #include "algo.h"
  int main()
  {
    Algo algo;
    int b = algo.foo(15);
    std::cout << "b = " << b << '\n';   // output -> b = 19
  }
*/

/*
  class Myclass {
  public:
    void foo();
  private:
    int mx;
  };

  int foo(int x); // global function

  void Myclass::foo()
  {
    foo(3); // syntax error
    // error: no matching function for call to 'Myclass::foo(int)'

    // namelookup will start from local scope, failed.
    // namelookup will continue from class scope, succeeded.
    // Myclass's non-static member function foo does not have parameter
    // context control will fail.

    ::foo(3); // VALID
    // namelookup will start from global namespace scope.

    foo();  // VALID
    // namelookup will start from local scope, failed.
    // namelookup will continue from class scope, succeeded.
    // context control will succeed.
    // access control will succeed.

    Myclass::foo()  // VALID
    // namelookup will start from class scope, succeeded.
    // context control will succeed.
    // access control will succeed.
  }
*/

/*
  class Myclass{
  public:
    void foo(int);
  private:
    int foo;
  };
  // syntax error
  // error: 'int Algo::foo' conflicts with a previous declaration

  // all sections(public, private, protected)
  // are in the same scope(class scope)
  // so, name conflict will occur between data member and
  // non-static member function.
*/

/*
  class Myclass{
  public:
    void foo(int);
  private:
    void foo(double);
  };
  // `foo(int)` and `foo(double)` are overloads
  // they are in the same scope(class scope)
*/

/*
  int foo(int);
  int foo(int);
  // function redeclaration is VALID in global scope

  class Myclass {
  public:
    int bar(int);
    int bar(int); // syntax error
    // error: 'int Myclass::bar(int)' cannot be overloaded with
    // 'int Myclass::bar(int)'
  };
  // function redeclaration IS NOT VALID in class scope
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
    // error: 'int Myclass::foo(double)' is private within this context

    // name lookup will start from Myclass's class scope
    // 2 overloads will be found, name lookup succeeds.

    // context control will find the best match.
    // int(int) overload is conversion
    // int(double) overload is exact match
    // context control will choose int(double) overload.

    // access control will fail because of int(double) is
    // in private section of the class and it can not be
    // accessed from the client side.
  }
*/

/*
  class Myclass {
  public:
    int foo(int);
  private:
    int foo(double);

    void bar()
    {
      foo(12);
      foo(1.2);
    }
  };
  // This kind of function overloads(1 in public, 1 in private)
  // can be useful when it has been called from another
  // member functions of the class.
  // non-static member functions can access all sections of the class.
*/

/*
  class Myclass {
  private:
    int foo()
    {
      int mx{};

      mx = 5;           // assignment to local variable
      Myclass::mx = 5;  // assignment to data member
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
  - `this` is a keyword and its value category is
    PRValue expression.

  - `this` is a pointer.

  - using `this` pointer in class's static member function
    is syntax error.

  - using `this` pointer in global function is syntax error.
*/

/*
  class Myclass {
  public:
    void func() // non-static member function
    {
      std::cout << "this = " << this << '\n';
      // output -> this = 009BFE2F

      foo();
    }

    void foo()  // non-static member function
    {
      std::cout << "this = " << this << '\n';
      // output -> this = 009BFE2F
    }
  };

  int main()
  {
    Myclass mx;
    std::cout << "&mx = " << &mx << '\n';
    // output -> &mx = 009BFE2F

    mx.func();
  }
*/

/*
  // myclass.h
  // ----------------
  class Myclass {
  public:
    void foo();
  };


  // myclass.cpp
  // ----------------
  // #include "myclass.h"

  void Myclass::foo()
  {
    Myclass mx;
    this = &mx;       // syntax error.
    // error: lvalue required as left operand of assignment

    auto x = &this;   // syntax error
    // error: lvalue required as unary '&' operand

    // `this` is a PRValue expression
  }
*/

/*
  // myclass.h
  // ----------------
  class Myclass {
  public:
    void foo();
    void bar();
  private:
    int mx;
  };


  // myclass.cpp
  // ----------------
  // #include "myclass.h"

  void Myclass::foo()   // non-static member function
  {
    mx = 10;
    this->mx = 10;
    Myclass::mx = 10;
    // These 3 lines are equivalent.

    bar();
    this->bar();
    Myclass::bar();
    // These 3 lines are equivalent.
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

  void Myclass::func()    // non-static member function
  {
    f1(this);
    f2(*this);
    f3(*this);
  }
*/

/*
  // ------ C code ------
  typedef struct {
    int a, b, c;
  }CClass;

  CClass* foo(CClass* p)
  {
    return p;
  }
  void bar(CClass*);
  // ------ C code ------


  // ------ C++ code ------
  class CPPClass {
  public:
    CPPClass& foo()
    {
      return *this;
    }
    CPPClass& bar()
    {
      return *this;
    }
    CPPClass& baz()
    {
      return *this;
    }
  };
  // ------ C++ code ------

  int main()
  {
    // ------ C code ------
    CClass c_x = { 43, 46, 98 };
    bar(foo(&c_x));
    // passing the address of the CClass object
    // returns from "foo" function to "bar" function.

    // ------ C++ code ------
    CPPClass cpp_x;
    cpp_x.foo().bar().baz();
    // chaining the member functions
    // passing the address of the CPPClass object
    // returns from "foo" function to "bar" function
    // returns from "bar" function to "baz" function.
  }
*/

/*
  int main()
  {
    int ival{ 432 };
    double dval{ 23.22 };

    std::cout << ival << dval;
    std::cout.operator<<(ival).operator<<(dval);  // chaining

    std::cout.operator<<(ival);
    // returns std::ostream&

    std::cout.operator<<(ival).operator<<(dval);
    // returns std::ostream&

    // Function overloading in operator<< functions
    // std::ostream& operator<<(int);
    // std::ostream& operator<<(double);
  }
*/

/*
                    --------------------------
                    | const member functions |
                    --------------------------
*/

/*
  class Myclass{};

  void func(Myclass&);        // mutator
  void func(const Myclass&);  // accessor

  void foo(Myclass* p);       // mutator
  void foo(const Myclass* p); // accesssor
*/

/*
  // ------ C code ------
  struct Data {
    int a, b, c;
  };

  void foo(struct Data*);

  void func(const struct Data* p)
  {
    // --------------------------------------------------
    struct Data* ptr;
    *p = ptr;	  // syntax error
    // error: assignment of read-only location '*p'

    p->a = 12;	// syntax error
    // error: assignment of member 'a' in read-only object

    // --------------------------------------------------

    struct Data* ptr_2 = p;
    // syntax error in C++, VALID in C
    // error: invalid conversion from 'const Data*' to 'Data*'

    foo(p);
    // syntax error in C++, VALID in C
    // error: invalid conversion from 'const Data*' to 'Data*'

    // --------------------------------------------------
  }
*/

/*
  class Myclass {
  public:
    void foo();       // non-const, non-static member function
    void bar()const;  // non-static const member function
    void baz()const;  // non-static const member function
    // const function's `this` pointer is also const.

  private:
    int m_x;
  };

  Myclass global_myclass_obj;

  // non-static, const member function definition
  void Myclass::bar()const
  {
    // -------------------------------------------------------

    m_x = 20;           // syntax error
    // error: assignment of member 'Myclass::mx' in read-only object

    this->m_x = 20;     // syntax error
    // error: assignment of member 'Myclass::mx' in read-only object

    Myclass::m_x = 20;  // syntax error
    // error: assignment of member 'Myclass::mx' in read-only object

    // These 3 lines are equivalent.
    // Becuase of `this` pointer is const Myclass* inside
    // const non-static member function, we can not change the value of
    // non-static data members of the class.

    // -------------------------------------------------------

    Myclass m;
    *this = m;        // syntax error
    // error: passing 'const Myclass' as
    // 'this' argument discards qualifiers

    // -------------------------------------------------------

    global_myclass_obj.m_x = 15;    // VALID

    // we are in Myclass's non-static member function
    // so we can access global Myclass object's private data member.

    // `this pointer` we have inside `Myclass::bar() const`
    // non-static member function have a different address from
    // global Myclass object's `this pointer`.

    // because global Myclass object's `this pointer` is not const
    // (because global Myclass object is not const),
    // changing global Myclass object's data member is legal.

    // -------------------------------------------------------

    foo();    // syntax error.
    // error: passing 'const Myclass' as
    // 'this' argument discards qualifiers

    // inside Myclass::bar() const non-static member function.
    // hidden parameter(`this` pointer) is const Myclass*
    // when "foo" function(non-const member function) is called
    // from Myclass::bar() function,
    // because of "foo" function's hidden parameter is Myclass*,
    // we are forcing a conversion from const Myclass* to Myclass*,
    // which is syntax error in C++.

    // conversion from const T* to T* is NOT VALID in C++.

    // -------------------------------------------------------

    baz();    // VALID
    // inside Myclass::bar() const non-static member function.
    // hidden parameter(`this` pointer) is const Myclass*
    // when "baz" function(const member function) is called
    // from Myclass::bar() function,
    // because of "baz" function's hidden parameter is const Myclass*,
    // we are sending const Myclass* to const Myclass*,

    // -------------------------------------------------------
  }

  // non-static, non-const member function definition
  void Myclass::foo()
  {
    bar();
    // inside Myclass::foo() non-const, non-static member function.
    // hidden parameter(`this` pointer) is Myclass*
    // when "bar" function(const member function) is called
    // from Myclass::foo() function,
    // because of "bar" function's hidden parameter is const Myclass*,
    // we are sending Myclass* to const Myclass*,
    // which is legal in C++.

    // conversion from T* to const T* is VALID in C++.
  }
*/

/*
  class Myclass {
  public:
    void foo();
    void bar()const;
  };

  int main()
  {
    // ----------------------------------------------------

    const Myclass cm;
    // "&cm" expression's data type is const Myclass*
    // we are sending &cm, when we call non-static member functions

    cm.foo(); // syntax error
    // error: passing 'const Myclass' as
    // 'this' argument discards qualifiers
    // sending const Myclass* to Myclass* is not valid.

    cm.bar(); // VALID
    // sending const Myclass* to const Myclass*.

    // ----------------------------------------------------

    Myclass m;
    // "&m" expression's data type is Myclass*
    // we are sending &m, when we call non-static member functions

    m.foo();  // VALID
    // sending Myclass* to Myclass*.
    m.bar();  // VALID
    // sending Myclass* to const Myclass*.

    // ----------------------------------------------------
  }
*/

/*

  1. const member functions CAN NOT change non-static data members.
  2. const member functions CAN NOT call non-const member functions.
  3. we can not assign any data member, using *this
    inside non-static const member functions.
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

    vector<int> ivec{ 1, 2, 3, 4, 5 };
    const vector<int> c_ivec{ 1, 2, 3, 4, 5 };

    // ----------------------------------------------------

    ivec.at(2) = 99;    // VALID
    c_ivec.at(2) = 99;  // syntax error
    // error: assignment of read-only location
    // 'c_ivec.std::vector<int>::at(2)'

    // "at" non-static member function
    // have 2 overloads(const overloads).

    // const overload is returning const int&,
    // assigning to that reference(const elem) is NOT VALID.

    // non-const overload returns int&
    // assigning to that reference(non-const elem) is VALID.

    // ----------------------------------------------------

    ++ivec.front();   // VALID
    ++c_ivec.front(); // syntax error
    // error: increment of read-only location
    // 'c_ivec.std::vector<int>::front()'

    // "front" non-static member function
    // have 2 overloads(const overloads).

    // const overload of front() function returns const int&
    // assigning to that reference(const elem) is NOT VALID.

    // non-const overload of front() function returns int&
    // assigning to that reference(non-const elem) is VALID.

    // ----------------------------------------------------
  }
*/

/*
  class Myclass {
  public:
    Myclass* foo()const
    {
      return this;	// syntax error
      // error: invalid conversion from 'const Myclass*' to 'Myclass*'

      // `this` pointer's data type is const Myclass*
      // function's return type is Myclass*
    }

    Myclass& bar() const
    {
      return *this;	// syntax error.
      // error: binding reference of type 'Myclass&' to
      // 'const Myclass' discards qualifiers

      // `this` pointer's data type is const Myclass*
      // "*this" expression's data type is const Myclass
      // function's return type is Myclass&
      // const L value can not bind to non-const L value reference.
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
      ++debug_function_call_count;
    }
    void defend()
    {
      ++debug_function_call_count;
    }
    std::string get_name()const
    {
      ++debug_function_call_count;
    }
  private:
    mutable int debug_function_call_count;
    // debug_function_call_count data member'ss value
    // did not have a relation with Fighter object's state.
  };

  // In problem domain changing debug_function_call_count
  // is not changing the state of the object.
  // Its only purpose is increasing the count in every
  // call to Fighter class's any member functions.
  // Because of debug_function_call_count is a data member
  // of Fighter class, in Fighter class's const member functions
  // changing its data member's value is not allowed.
  // For these kind of scenarios "mutable" keyword is used.
  // "mutable" data member is independent from
  // other data members of Fighter class.

  // ----------------------------------------------------

  class Date {
    int m_day;
    int m_month;
    int m_year;
  };

  // Making m_year data member mutable does not make sense.
  // Date class itself depends on m_year data member's value.
*/

/*
  class RandomEngine {
  public:
    int generate();
    // non-static, non-const member function.
    // changing RandomEngine class's state.

    void discard(int n);
    // non-static non-const member function.
    // changing RandomEngine class's state.
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
      // if non-static const function have to change "eng"
      // object's state, using mutable keyword in
      // RandomEngine data member is a solution.
    }
  private:
    mutable RandomEngine eng;
  };

  int main()
  {
    const RandomEngine eng;
    eng.generate();	// syntax error
    // error: passing 'const RandomEngine' as
    // 'this' argument discards qualifiers

    // calling non-static non-const member function
    // with const RandomEngine object is not valid.
    // Forcing conversion from hidden parameter
    // const RandomEngine* to RandomEngine*
  }
*/

/*
  #include <mutex>

  class Myclass {
  public:
    void foo()
    {
      mtx.lock();
      // critical section
      mtx.unlock();
    }

    void func() const
    {
      mtx.lock();
      // critical section
      mtx.unlock();
    }
  private:
    mutable std::mutex mtx;
    // std::mutex member type has to be modified
    // in Myclass's const member functions.
  };
*/

/*
                  ----------------------------
                  | constructor & destructor |
                  ----------------------------
*/

/*
  Constuctor(CTOR) -> Myclass()
  -------------------------------
  1. ctor's identifier should be same as class identifier.
  2. there is no return value concept for constructors.
  3. constructor has to be a non-static member function.
      can not be a global function.
      can not be a static member function.
  4. constructor can not be a const member function.
  5. constructor can not be called with "." or "->"
      [member selection(dot and arrow)] operators.
  6. constructors can be in class's
      public, private and protected sections
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

    m.func();   // VALID
    p->func();  // VALID

    m.Myclass();  // sytax error
    p->Myclass(); // syntax error
    // error: invalid use of 'Myclass::Myclass'

    // constructor can not be called with member selection operators.
  }
*/

/*
  class Myclass {
  private:
    Myclass();  // default ctor is in private section
  };

  int main()
  {
    Myclass m;  // syntax error
    // error: 'Myclass::Myclass()' is private within this context
  }
*/

/*
  class Myclass {
  public:
    Myclass();  // default ctor
    Myclass(int);
    Myclass(int,int);
    Myclass(double);
    // There are 4 constructor overloads here.
  };
*/

/*
  Destructor (DTOR)	-> ~Myclass()
  --------------------------------
  1. dtor's identifier should be same as class identifier.
  2. there is no return value concept for destructors.
  3. destructor has to be a non-static member function.
      can not be a global function.
      can not be a static member function.
  4. destructor can not be a const member function.
  5. destructor can be in classes
      public, private and protected sections
  6. destructor can not be overloaded.
      A class can only have a destructor without a parameter.
  7. destructor can be called with "." or "->"
      [member selection(dot and arrow)] operators.
    -mostly we are not calling destructor with member selection operators.
*/

/*
      -------------------------------------------------------
      | RAII idiom (Resource Acquisition Is Initialization) |
      -------------------------------------------------------

  -> Ctor will get the resources of the class object.
  -> Dtor will release the resources that class object have been used.

  - ctor will allocate memory in heap (dynamic memory allocation)
  - dtor will give back the memory (free)

  - ctor will open a file.
  - dtor will close a file.

  - ctor will create a database connection
  - dtor will end the database connection

  - ctor will lock mutex
  - dtor will unlock mutex

  -> stl container classes, smart pointers, string class
*/

/*
  default constructor
  --------------------
    - no parameter constructor.
    - all of its parameters have default arguments.
*/

/*
  class AClass{
  public:
    AClass();           // default ctor
  };

  class BClass{
  public:
    BClass(int x = 0);  // default ctor
  };
*/

/*
  special member functions
  ------------------------
  -> default ctor
  -> destructor
  -> copy ctor
  -> move ctor		    (C++11)
  -> copy assignment
  -> move assignment  (C++11)
*/

/*
  void func(double) = delete;   // global function

  class Myclass {
  public:
    void foo(int) = delete;     // non-static member function
  };

  // deleted functions are declared functions.
  // calling a deleted function will be sythax error.

  int main()
  {
    Myclass m;
    m.foo(12);  // syntax error
    // error: use of deleted function 'void Myclass::foo(int)'

    func(5.4);  // syntax error
    // error: use of deleted function 'void func(double)'

    bar();      // syntax error
    // error: 'bar' was not declared in this scope
  }

  // Not declaring a function instad of deleting it is a syntax error.
  // name lookup phase will not find the function identifier.
*/

/*
  void func(int);
  void func(long);
  void func(double) = delete;
  // There are 3 function overloads here.
  // deleting a function does not mean that function does not exists.
  // deleted function will be in the overload set and
  // join the function overload resolution process.

  int main()
  {
    func(12);   // VALID
    func(12L);  // VALID

    func(3.4);  // syntax error
    // error: use of deleted function 'void func(double)'

    // in context control phase,
    // `func(double)`overload will be choosen (exact match)
    // because of it is a deleted function, will be a syntax error
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
    // When any constructor other than the default ctor is declared,
    // there won't be any default ctor.
    // default ctor is not declared.
  };

  int main()
  {
    Myclass m;  // syntax error
    // error: no matching function for call to 'Myclass::Myclass()'
  }
*/

/*
  // 2. User declared

  class A {
    A();            // user declared to be defined
    // user will define the default constructor.
  };

  class B {
    B() = default;  // user declared defaulted
    // user declared default declaration means,
    // compiler will generate default constructor's code.
  };

  class C {
    C() = delete;   // user declared deleted
    // user declared delete declaration means,
    // calling user declared ctor will be a syntax error.
  };
*/

/*
  // 3. Implicitly declared

  // ------------------------------------------------------
  // Implicitly declared defaulted

  class AClass {
  public:
    // all 6 special member functions are
    // implicitly declared defaulted.
  };

  // ------------------------------------------------------
  // -> Implicitly declared deleted
  class BClass {
  public:
  private:
    const int mx;
  };
  // default ctor is implicitly declared deleted

  int main()
  {
    BClass x;	// syntax error
    // error: use of deleted function 'BClass::BClass()'

    // implicitly declared defaulted default ctor will
    // default initialize all data members of the class.
    // because of a const data member can not be default initialized
    // default ctor will throw an error so because of the error
    // compiler will implicitly delete the default constructor.
    // constructor will become implicitly declared deleted.
  }
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
    // -----------------------------------------------------------

    Myclass m0;	// default initialization

    // Myclass's default ctor will be called.
    //	-> if default ctor is in private section  -> syntax error
    //	-> if default ctor is deleted             -> syntax error
    //	-> if default ctor is not declared        -> syntax error
    // Myclass's data members will also be default initialized
    // so they have intedermined values.

    // -----------------------------------------------------------

    Myclass m1{};	// value initialization
    // Myclass's default ctor will be called.
    // at first Myclass's data members will be zero initialized.

    // -----------------------------------------------------------

    Myclass m[3];
    // default constructor will be called for every member in array.

    // -----------------------------------------------------------

    // output ->
    //  Myclass default ctor  >> this: 0x4e9c7ff88f
    //  Myclass default ctor  >> this: 0x4e9c7ff88e
    //  Myclass default ctor  >> this: 0x4e9c7ff88b
    //  Myclass default ctor  >> this: 0x4e9c7ff88c
    //  Myclass default ctor  >> this: 0x4e9c7ff88d
    //  Myclass dtor          >> this: 0x4e9c7ff88d
    //  Myclass dtor          >> this: 0x4e9c7ff88c
    //  Myclass dtor          >> this: 0x4e9c7ff88b
    //  Myclass dtor          >> this: 0x4e9c7ff88e
    //  Myclass dtor          >> this: 0x4e9c7ff88f
  }
*/

/*
  class Myclass {
  public:
    Myclass() = default;
    Myclass(int x)
    {
      std::cout << "Myclass(int x) -> x = " << x
                << " this = " << this << '\n';
    }
  };

  int main()
  {
    // -----------------------------------------------------------
    Myclass m1(1);      // direct initialization
    // output -> Myclass(int x) x = 1 this = 0x2d3bbffe5f

    Myclass m1_2(1.3);  // direct initialization
    // output -> Myclass(int x) -> x = 1 this = 0x2d3bbffe5e
    // narrowing conversion(double -> int) VALID in direct initialization

    // -----------------------------------------------------------

    Myclass m2{ 2 };    // direct list initialization
    // // output -> Myclass(int x) x = 2 this = 0x2d3bbffe5d

    Myclass m2_2{2.3}; // syntax error
    // error: narrowing conversion of '2.2999999999999998e+0'
    // from 'double' to 'int'

    // narrowing conversion(double -> int) syntax error in
    // direct list initialization

    // -----------------------------------------------------------

    Myclass m3 = 3;     // copy initialization
    // output -> Myclass(int x) x = 3 this = 0x2d3bbffe5c

    Myclass m3_2 = 3.3; // copy initialization
    // output -> Myclass(int x) -> x = 3 this = 0x2d3bbffe5b
    // narrowing conversion(double -> int) VALID in copy initialization

    // -----------------------------------------------------------
  }
*/