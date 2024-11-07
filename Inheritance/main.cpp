#include <iostream>

/*
                          ===============
                          | inheritance |
                          ===============
*/

/*
  <--- check inheritance.png --->

  super class     parent class      [BASED CLASS]
  sub class       child class       [DERIVED CLASS]
*/

/*
  <--- check single_level_inheritance.png --->
  <--- check multi_level_inheritance.png --->
  <--- check multiple_inheritance.png --->

  single-level inheritance  : BMW -> Car <- Audi
  multi-level inheritance   : BMW M3 -> BMW -> Car
  multiple inheritance      : Animal <- Whale -> Endangered
*/

/*
  inheritance specifiers
   - public inheritance
   - private inheritance
   - protected inheritance
*/

/*
  // incomplete types can not be base class

  class Car; // forward declaration
  // "Car" is an incomplete type

  class Audi : public Car {}; // syntax error
  // error: invalid use of incomplete type 'class Car'
*/

/*
  class Base {};

  // ----------------------------------------------------

  class DerClass    : Base {};
  class DerClass_2  : private Base{};
  // default inheritance specifier is "private" for classes

  // ----------------------------------------------------

  struct DerStruct    : Base {};
  struct DerStruct_2  : public Base{};
  // default inheritance specifier is "public" for structs

  // ----------------------------------------------------
*/

/*
  class Base {
  public:
    void foo(){}      // non-static member function
    int m_x;          // non-static data member
    class Nested {};  // nested type
  };

  class Der : public Base {};
  // public inheritance
  // Base classes public interface is added to Der classes interface

  int main()
  {
    Der d1;

    d1.foo();         // VALID
    d1.m_x = 10;      // VALID
    Der::Nested n1;   // VALID
  }
*/

/*
  class AClass {
    int m_a, m_b;
  };

  class BClASS {
    AClass m_AClass;  // member type
  };

  class CClass : public AClass {};
  // public inheritance

  int main()
  {
    std::cout << "sizeof(AClass) = " << sizeof(AClass) << '\n';
    // output -> sizeof(AClass) = 8
    std::cout << "sizeof(BClASS) = " << sizeof(BClASS) << '\n';
    // output -> sizeof(BClASS) = 8
    std::cout << "sizeof(CClass) = " << sizeof(CClass) << '\n';
    // output -> sizeof(CClass) = 8
  }
*/

/*
  class Base {
  public:
    void foo(){}     // non-static member function
  };

  class Der : public Base {};
  // public inheritance

  int main()
  {
    Der d1;
    d1.foo();

    // non-static member functions have a hidden parameter so,
    // "foo" function have a hidden Base* parameter (`this` pointer)
    // when a derived class object calls base classes member function
    // it sends the address of the derived class object
    // (which is actually same as the address of the base class object)
    // to the base classes member function.
  }
*/

/*
  // - requires no more, promise no less
  // - SOLID's(L) Liskov substitution principle

  // implicit conversion from Derived class to Base class

  class Base {};

  class Der : public Base {};
  // public inheritance

  int main()
  {
    // ------------------------------------------------------

    Der der;
    Base* p_base = &der;  // upcasting
    Base& r_base = der;   // upcasting

    // der's address is actually same as the address of 
    // base class object inside of der object

    // ------------------------------------------------------

    Base b1 = der; 
    // "der" object has a Base class object inside of it
    // but Der classes interface might have more data members 
    // except Base classes data members.
    // when we copy "der" object to "b1" object
    // only Base class object inside "der" will be copied to b1 object
    // the rest of the "der" object will be sliced off
    // it is called "object slicing"

    // ------------------------------------------------------
  }
*/

/*
  #include <typeinfo>

  class Car {};

  class Audi      : public Car{};
  class Volvo     : public Car{};
  class Mercedes  : public Car{};

  void car_game_1(Car* p_Car){}
  void car_game_2(Car& r_Car){}

  int main()
  {
    car_game_1(new Audi);
    car_game_2(*new Volvo);

    constexpr bool b1 = typeid(new Mercedes) == typeid(Mercedes*);
    // b1 -> true

    constexpr bool b2 = typeid(*new Mercedes) == typeid(Mercedes);
    // b2 -> true
  }
*/

/*
  class Car {
  public:
    void speed();
  };

  class Audi : public Car {};

  int main()
  {
    Audi a1;
    a1.speed(); // upcasting
    // Audi class object is implicitly upcasted to Car class object
  }
*/

/*
                  -------------------------------
                  | inheritance and name lookup |
                  -------------------------------
*/

/*
  class Base {
  public:
    void foo(int)
    {
      std::cout << "Base::foo(int)\n";
    }
  };

  class Der : public Base {
  public:
    void foo(double)
    {
      std::cout << "Der::foo(double)\n";
    }
  };

  int main()
  {
    Der d1;
    d1.foo(12);   // output -> Der::foo(double)
    // "foo" is an identfier
    // name lookup for "foo" will start from Der class scope -> FOUND
    // name lookup will stop and will not search Base class scope
    // "Der::foo" hides "Base::foo" (name hiding-shadowing)

    // conversion from int to double 
    // (int ===> double standart conversion)
  }
*/

/*
  class Base {
  public:
    void foo(int)
    {
      std::cout << "Base::foo(int)\n";
    }
  };

  class Der : public Base {
  private:
    void foo(double)
    {
      std::cout << "Der::foo(double)\n";
    }
  };

  int main()
  {
    Der d1;
    d1.foo(12); // syntax error
    // error: 'void Der::foo(double)' is private within this context

    // name lookup for "foo" will start from Der class scope -> FOUND
    // name lookup will stop and will not search Base class scope

    // context control phase will start 
    // (int ===> double standart conversion)

    // access control phase will start
    // access control is NOT okay because of 
    // Der::foo() in private section -> syntax error
  }
*/

/*
  class Myclass {
  public:
    void func()
    {
      std::cout << "Myclass::func()\n";
    }
  };

  int main(void)
  {
    Myclass m1;

    m1.func();              // output -> Myclass::func()
    m1.Myclass::func();     // output -> Myclass::func()
    // Those two lines are equivalent.
  }
*/

/*
  class Base {
  public:
    void foo(int)
    {
      std::cout << "Base::foo(int)\n";
    }
  };

  class Der : public Base {
  private:
    void foo(double)
    {
      std::cout << "Der::foo(double)\n";
    }
  };

  int main()
  {
    Der d1;
    d1.Base::foo(12);   // output -> Base::foo(int)

    // name lookup for "foo" will start from Base class scope
    // because of it is a qualified name("Base::foo")

    // d1 object will be implicitly upcasted to Base class object
    // Base classes member function can be called with the 
    // Base class objects pointer inside of the derived class object.
  }
*/

/*
  class Base {
  public:
    void func(int, int)
    {
      std::cout << "Base::func(int,int)\n";
    }
  };

  class Der : public Base {
  public:
    void func(int)
    {
      std::cout << "Der::func(int)\n";
    }

    void foo()
    {
      // ------------------------------------------------

      func(11, 12); // syntax error
      // error: no matching function for call to 'Der::func(int, int)'

      // name lookup for "func" identiier
      // will start from "foo" function scope -> NOT FOUND
      // will continue with "Der" class scope -> FOUND
      // name lookup will stop.
      // context control phase will throw an error (no matching function)

      // ------------------------------------------------

      func(33);  // output -> Der::func(int)

      // name lookup for "func" identiier
      // will start from "foo" function scope -> NOT FOUND
      // will continue with "Der" class scope -> FOUND

      // ------------------------------------------------

      Base::func(44, 55); // output -> Base::func(int,int)

      // name lookup for "func" identiier
      // will start from Base class scope -> FOUND

      // ------------------------------------------------

      ((Base*)this)->func(66, 77);  // output -> Base::func(int,int)
      // casting `this(Der*)` pointer to Base* 
      // will make name lookup start from Base class scope -> FOUND

      // ------------------------------------------------
    }
  };

  int main()
  {
    Der d1;
    d1.foo();
  }
*/

/*
                ----------------------------------
                | inheritance and access control |
                ----------------------------------
*/

/*
  class Base {
  public:
    int m_base_public;
  protected:
    int m_base_protected;
    void bar();
  private:
    int m_base_private;

    friend class Der_2;
  };

  // Der is not friend declared in Base class
  // so Der can not reach Base classes private section
  // but Der can reach Base classes protected section
  class Der : public Base {
    void foo()
    {
      m_base_public = 11;     // VALID
      m_base_protected = 22;  // VALID
      m_base_private = 33;    // syntax error
      // error: 'int Base::m_base_private' is 
      // private within this context
    }
  };

  // Der_2 is friend declared in Base class
  // so Der_2 can reach Base classes private section

  class Der_2 : public Base {
    void foo()
    {
      m_base_public = 11;     // VALID
      m_base_protected = 22;  // VALID
      m_base_private = 33;    // VALID
    }
  };

  int main()
  {
    Base b1;
    // client codes can only reach classes public section

    b1.m_base_public = 44;    // VALID

    b1.m_base_protected = 55; // syntax error
    // error: 'int Base::m_base_protected' is 
    // protected within this context

    b1.m_base_private = 66;   // syntax error
    // error: 'int Base::m_base_private' is
    // private within this context
  }
*/


/*
  #include <stack>

  class Der : public std::stack<int> {
    void foo()
    {
      c.push_back(12);
      // c is in protected section of std::stack<int>(base) class
      // Der class can reach std::stack<int> classes protected section
    }
  };

  int main()
  {
    std::stack<int> s1;
    s1.c; // syntax error
    // error: 'std::deque<int, std::allocator<int>> 
    // std::stack<int>::c' is protected within this context
    
    // client code can only reach classes public section
  }
*/

/*
  class Base {
  public:
    Base()
    {
      std::cout << "Base() default ctor\n";
    }
    ~Base()
    {
      std::cout << "~Base() dtor\n";
    }
  };

  class Der : public Base {};

  int main()
  {
    Der d1;
    // output ->
    //  Base() default ctor
    //  ~Base() dtor

    // implicitly declared defaulted Der classes default ctor 
    // will invoke Base classes default ctor.
    // implicitly declared defaulted Der classes dtor
    // will invoke Base classes dtor
  }
*/

/*
  class Base {
  public:
    Base(int)
    {
      std::cout << "Base(int)\n";
    }
  };

  class Der : public Base {};

  int main()
  {
    Der d1; // syntax error
    // error: use of deleted function 'Der::Der()'
    // error: no matching function for call to 'Base::Base()'

    // Der's default constructor will try to invoke 
    // Base classes default ctor.
    // Because of there is a user declared ctor in Base class,
    // Base() default ctor is not declared by compiler.
    // so compiler will delete Der() default ctor
  }
*/

/*
  class Base {
  private:
    Base()
    {
      std::cout << "Base() default ctor\n";
    }
  };

  class Der : public Base {};

  int main()
  {
    Der d1; // syntax error
    // error: use of deleted function 'Der::Der()'
    // error: 'Base::Base()' is private within this context

    // Der's default constructor will try to invoke
    // Base classes default ctor.
    // Because of Base() default ctor is in the private section
    // Der() can not reach Base classes private section.
    // Compiler will delete Der's default ctor.
  }
*/

/*
  class Base {
  public:
    Base()
    {
      std::cout << "Base() default ctor\n";
    }
    Base(int)
    {
      std::cout << "Base(int)\n";
    }
    Base(double)
    {
      std::cout << "Base(double)\n";
    }
    Base(int,int)
    {
      std::cout << "Base(int,int)\n";
    }
  };

  class Der : public Base {
  public:
    // ------------------------------------------------

    // Scenario 1
    Der() : Base(){} 

    // Scenario 2
    Der() : Base(3) {} 

    // Scenario 3
    Der() : Base(3.) {}  

    // Scenario 4
    Der() : Base{ 3, 4 }{}	

    // ------------------------------------------------

    Der(int x, int y) : Base{ (x + y)/ 2.0 }{}
    // output -> Base(double)

    // ------------------------------------------------
  };

  int main()
  {
    Der d1;
    // Scenario 1 : output -> Base() default ctor
    // Scenario 2 : output -> Base(int)
    // Scenario 3 : output -> Base(double)
    // Scenario 4 : output -> Base(int,int)

    Der d2(2, 4); // output -> Base(double)
  }
*/

/*
  class Base {
  public:
    Base()
    {
      std::cout << "Base() default ctor\n";
    }
  };

  class AClass {
  public:
    AClass()
    {
      std::cout << "AClass() default ctor\n";
    }
  };

  class Der : public Base {
  public:
    Der() : Base(), m_AClass() {}
    
    // Base classes default ctor will invoke
    // before m_AClass member object's default ctor.

    // Better write base class before member type in 
    // constructor initializer list
  private:
    AClass m_AClass;  // member type
  };

  int main()
  {
    Der d1;

    // output ->
    //  Base() default ctor
    //  AClass() default ctor
  }
*/

/*
            -------------------------------------------
            | special member functions in inheritance |
            -------------------------------------------
*/

/*
  #include <utility> // std::move

  class Base {
  public:
    Base() = default;
    Base(const Base&)
    {
      std::cout << "Base copy ctor\n";
    }
    Base(Base&&)
    {
      std::cout << "Base move ctor\n";
    }
  };

  class Der : public Base {};

  int main()
  {
    Der d1;
    Der d2 = d1;            // output -> Base copy ctor
    Der d3 = std::move(d2); // output -> Base move ctor
  }
*/

/*
  #include <utility> // std::move

  class Base {
  public:
    Base()
    {
      std::cout << "Base default ctor\n";
    }
    Base(const Base&)
    {
      std::cout << "Base copy ctor\n";
    }
    Base(Base&&)
    {
      std::cout << "Base move ctor\n";
    }
  };

  class Der : public Base {
  public:
    Der() = default;

    Der(const Der&) {}
    // Der classes copy ctor is user declared
    // and not used in initializer list to call Base's copy ctor
    // Base() default ctor will invoked
    // to create Base object inside of Der object.
  };

  class Der_2 : public Base {
  public:
    Der_2() = default;

    Der_2(const Der_2& other) : Base(other) {}
    // implicitly declared defaulted Der_2's copy ctor
    // is equivalent to this user declared copy ctor.
    // upcasting is happening(other(Der) is implicitly upcasted to Base)

    Der_2(Der_2&& other) : Base(std::move(other)) {}
    // implicitly declared defaulted Der_2's move ctor
    // is equivalent to this user declared move ctor.
    // upcasting is happening(other(Der) is implicitly upcasted to Base)
  };

  int main()
  {
    // ------------------------------------------------

    Der d1;       // output -> Base default ctor
    Der d2 = d1;  // output -> Base default ctor

    // ------------------------------------------------

    Der_2 d3;         // output -> Base default ctor
    Der_2 d4 = d3;    // output -> Base copy ctor

    // ------------------------------------------------
  }
*/

/*
  class Base {
  public:
    Base& operator=(const Base&)
    {
      std::cout << "Base copy asssignment\n";
      return *this;
    }
    Base& operator=(Base&&)
    {
      std::cout << "Base move asssignment\n";
      return *this;
    }
  };

  class Der : public Base {
  public:
    Der& operator=(const Der& other)
    {
      std::cout << "Der copy asssignment\n";
      Base::operator=(other);
      // calling Base classes copy assignment (upcasting)
      return *this;
    }

    Der& operator=(Der&& other)
    {
      std::cout << "Der move asssignment\n";
      Base::operator=(std::move(other));
      // calling Base classes move assignment (upcasting)
      return *this;
    }
  };

  int main()
  {
    Der d1, d2;

    d1 = d2;              
    // output -> 
    //  Der copy asssignment
    //  Base copy asssignment

    d1 = std::move(d2);
    // output ->
    //  Der move asssignment
    //  Base move asssignment
  }
*/

/*
                ------------------------------------
                | using declaration in inheritance |
                ------------------------------------
*/

/*
  class Base {
  protected:
    void foo(int);
    int m_x;
  };

  class Der : public Base {
  public:
    using Base::foo;
    using Base::m_x;
  };

  int main()
  {
    Der d1;
    d1.foo(12); // VALID
    d1.m_x;     // VALID

    // because of using declarations in Der classes public section
    // Base classes protected members are now visible in Der class.

    // in client side, 
    // namelookup for "foo" and "m_x" 
    // will start from Der class scope -> FOUND 
  }
*/

/*
  class Base {
  protected:
    void foo(int)
    {
      std::cout << "Base::foo(int)\n";
    }
  };

  class Der : public Base {
  public:
    void foo(double)
    {
      std::cout << "Der::foo(double)\n";
    }
  };

  class Der_2 : public Base {
  public:
    void foo(double)
    {
      std::cout << "Der_2::foo(double)\n";
    }

    using Base::foo;
  };

  int main()
  {
    Der d1;
    Der_2 d2;

    // ------------------------------------------------

    d1.foo(0.9);    // output -> Der::foo(double)
    d1.foo(12);     // output -> Der::foo(double)

    // ------------------------------------------------

    d2.foo(0.9);    // output -> Der::foo(double)
    d2.foo(12);     // output -> Base::foo(int)

    // because of the using declaration (using Base::foo)
    // Der_2::foo(double) and Base::foo(int) are now overloads.

    // ------------------------------------------------
  }
*/

/*
  class Base {
  protected:
    void foo(int)
    {
      std::cout << "Base::foo(int)\n";
    }
    void foo(int, int)
    {
      std::cout << "Base::foo(int, int)\n";
    }
    void foo(int, int, int)
    {
      std::cout << "Base::foo(int, int, int)\n";
    }
  };

  class Der : public Base {
  public:
    void foo(double)
    {
      std::cout << "Der::foo(double)\n";
    }
    using Base::foo;
  };

  // because of using declaration(using Base::foo) in Der class
  // Base::foo(int), Base::foo(int, int), Base::foo(int, int, int)
  // and Der::foo(double) are now overloads.
  // There are 4 "foo" function overloads in Der classes interface

  int main()
  {
    Der d1;

    d1.foo(.9);           // output -> Der::foo(double)
    d1.foo(12);           // output -> Base::foo(int)
    d1.foo(12, 12);       // output -> Base::foo(int, int)
    d1.foo(12, 12, 12);   // output -> Base::foo(int, int, int)
  }
*/

/*
  class Base {
  private:
    void foo(double)
    {
      std::cout << "Base::foo(double)\n";
    }
  };

  class Der : public Base {
  public:
    void foo(int)
    {
      std::cout << "Der::foo(int)\n";
    }

    using Base::foo;  // syntax error
    // error: 'void Base::foo(double)' is private within this context
  };
*/

/*
                    -------------------------
                    | inherited constructor |
                    -------------------------
*/

/*
  class Base {
  public:
    Base(int)
    {
      std::cout << "Base(int)\n";
    }
    Base(int, int)
    {
      std::cout << "Base(int, int)\n";
    }
    Base(double)
    {
      std::cout << "Base(double)\n";
    }
  };

  class Der_BeforeModernCPP : public Base {
  public:
    Der_BeforeModernCPP(int x)        : Base(x) {}
    Der_BeforeModernCPP(int x,int y)  : Base(x, y) {}
    Der_BeforeModernCPP(double x)     : Base(x) {}
  };

  class Der_AfterModernCPP : public Base {
  public:
    using Base::Base;
    // with using declaration(using Base::Base)
    // Base classes constructors are now inherited in Der class
  };

  int main()
  { 
    Der_BeforeModernCPP d1(12);     // output -> Base(int)
    Der_BeforeModernCPP d2(1, 2);   // output -> Base(int, int)
    Der_BeforeModernCPP d3(12.5);   // output -> Base(double)

    Der_AfterModernCPP d4(12);      // output -> Base(int)
    Der_AfterModernCPP d5(1, 2);    // output -> Base(int, int)
    Der_AfterModernCPP d6(12.5);    // output -> Base(double)
  }
*/

/*
  class Base {
  protected:
    // Base classes constructors are in protected section
    Base(int) 
    {
      std::cout << "Base(int)\n";
    }
    Base(int, int)
    {
      std::cout << "Base(int, int)\n";
    }
    Base(double)
    {
      std::cout << "Base(double)\n";
    }
  };

  class Der_BeforeModernCPP : public Base {
  public:
    Der_BeforeModernCPP(int x)        : Base(x) {}
    Der_BeforeModernCPP(int x,int y)  : Base(x, y) {}
    Der_BeforeModernCPP(double x)     : Base(x) {}
  };

  class Der_AfterModernCPP : public Base {
  public:
    using Base::Base;
  };

  int main()
  {
    // ------------------------------------------------

    Der_BeforeModernCPP d1(12);   // output -> Base(int)
    Der_BeforeModernCPP d2(1, 2); // output -> Base(int, int)
    Der_BeforeModernCPP d3(12.5); // output -> Base(double)

    // client code can reach derived classes public section

    // ------------------------------------------------

    Der_AfterModernCPP d1(12);   // syntax error
    // error: 'Base::Base(int)' is protected within this context
    Der_AfterModernCPP d2(1, 2); // syntax error
    // error: 'Base::Base(int, int)' is protected within this context
    Der_AfterModernCPP d3(12.5); // syntax error
    // error: 'Base::Base(double)' is protected within this context

    // even if we use using declaration(using Base::Base)
    // base constructors are visible but because of 
    // they are in protected section, client code can not call them.

    // ------------------------------------------------
  }
*/

/*
                    -------------------------
                    | run-time polymorphism |
                    -------------------------
*/

/*
  There are 3 types of Base class member functions.

  1. member functions that gave an interface and an implementation
    to the derived classes.
  
  2. member functions that gave an interface and a default implementation
    to the derived classes.
      -> if base class has a member function which is in type_2,
      that will make base class a polymorphic class.

  3. member functions that gave an interface but not an implementation
    to the derived classes.
      -> if base class has a member function which is in type_3,
      that will make base class a polymorphic class.
      -> if base class has a member function which is in type_3,
      that will make base class an abstract class.

      -> abstract classes can not be instantiated.
      -> can not create an object from an abstract class.
      -> can create a pointer and a reference from an abstract class.
      -> if a class is not an abstract class, it is a concrete class.
      -> can create an object from concrete class.
*/    

/*
  class Airplane {
  public:
    // type_1 member function
    void fly()
    {
      std::cout << "Airplane::fly()\n";
    }
  };

  class Airbus_A380 : public Airplane {};
*/

/*
  class Airplane {
  public:
    // type_1 member function
    void fly()
    {
      std::cout << "Airplane::fly()\n";
    }

    // type_2 virtual member function
    virtual void land()
    {
      std::cout << "Airplane::land()\n";
    }
    // "land" function is a virtual function
    // can be overridden in derived classes
    // or can be used from base class in derived classes. 
  };

  // because of Airplane class has a virtual function
  // it is now a polymorphic class.

  class Airbus_A380 : public Airplane {};
*/


/*
  class Airplane {
  public:
    // type_1 member function
    void fly()
    {
      std::cout << "Airplane::fly()\n";
    }
    // type_2 virtual member function
    virtual void land()
    {
      std::cout << "Airplane::land()\n";
    }

    // type_3 pure virtual member function
    virtual void takeoff() = 0; 
    // "takeoff" function is a pure virtual function
    // derived classes MUST override this function
  };

  // because of Airplane class has a pure virtual function
  // it is now an abstract class.

  class Airbus_A380 : public Airplane {};

  int main()
  {
    // ------------------------------------------------

    Airplane a1; // syntax error.
    // error: cannot declare variable 'a1' to be 
    // of abstract type 'Airplane'

    // ------------------------------------------------

    Airbus_A380 a2_derived; // syntax error.
    // error: cannot declare variable 'a2_derived' to be 
    // of abstract type 'Airbus_A380'

    // because of Airbus_A380 class did not override
    // Airplane(base) classes pure virtual function
    // it is also become an abstract class.

    // ------------------------------------------------
  }
*/

/*
  // base.h
  // -------------

  class Base {
  public:
    // inline virtual member function definition in header(.h) file
    virtual int foo(int, int)
    {
      std::cout << "virtual Base::foo(int, int)\n";
    }

    virtual int bar(int, int);
  };

  // base.cpp
  // -------------

  // definition of a virtual member function in source(.cpp) file
  // do not use "virtual" keyword in definition
  int Base::bar(int x, int y)
  {
    std::cout << "virtual Base::bar(int, int)\n";
  } 
*/

/*
  class Base {
  public:
    virtual int foo(int, int);
  };

  class Der : public Base {
  public:
    double foo(int, int);   // syntax error
    // error: conflicting return type specified 
    // for 'virtual double Der::foo(int, int)'

    // declaring a function with same name and same signature
    // but different return type 
    // as same as base classes virtual function is NOT VALID.
  };

  class Der_2 : public Base {
  public:
    double foo(int, double);  // VALID
    // identifiers are same but signatures are different.
    // this is NOT an override of base classes virtual function.
  };

  class Der_3 : public Base {
  public:
    int foo(int, int);        // VALID
    // this is an override function of base classes virtual function.
  };
*/

/*
  class Base {
  public:
    virtual int foo(int, int) const;
  };

  class Der : public Base {
  public:
    // ------------------------------------------------

    int foo(int, int);
    // this is NOT an override of base classes virtual "foo" function
    // because signatures(`const` keyword is a part of signature) 
    // are different.

    // ------------------------------------------------

    int foo(int, int) const;  
    // this is override of base classes virtual "foo" function
    // because signatures and return types are same.

    // ------------------------------------------------
  };
*/

/*
  `override` keyword is contextual keyword
    - can be a keyword
    - can be an identifier.

    can still be used as an identifier for backward compatibility.
    programmers might have used "override" as an identifier, 
    for not breaking their code, "override" keyword is contextual.
*/

/*
  class Base {
  public:
    virtual int foo(int, int);
  };

  class Der : public Base {
  public:
    int foo(int, int) override; // `override` used as a keyword
  };

  class override {};  // `override` used as an identifier
  int override(int override){}  // `override` used as an identifier
*/

/*
                        --------------------
                        | virtual dispatch |
                        --------------------
*/

/*
  if a virtual function called with a
    - Base class pointer
    - Base class reference

  function that will be called will be understood in run time 
  not in compile time it is called "late(dynamic) binding"
*/

/*
  class Base {
  public:
    void func()
    {
      std::cout << "Base::func()\n";
    }

    virtual void bar()
    {
      std::cout << "Base::bar()\n";
    }
  };

  class Der : public Base {
  public:
    void func()
    {
      std::cout << "Der::func()\n";
    }

    void bar() override
    {
      std::cout << "Der::bar()\n";
    }
  };

  int main()
  {
    // ------------------------------------------------

    Der d1;
    Base* p_base = &d1;

    p_base->func();   // output -> Base::func()
    p_base->bar();    // output -> Der::bar()  -> virtual dispatch

    // "func" is a non-virtual function
    // "bar" is a virtual function

    // ------------------------------------------------

    Base b1;
    Base* p_base_2 = &b1;

    p_base_2->func();   // output -> Base::func()
    p_base_2->bar();    // output -> Base::bar()

    // ------------------------------------------------
  }
*/

/*
  #include "headers/Car_1.h"
  #include <cstdio>

  void car_with_pointer(Car* p_car)
  {
    p_car->start();
    p_car->run();
    p_car->stop();

    std::putchar('\n');
  }

  void car_with_reference(Car& r_car)
  {
    r_car.start();
    r_car.run();
    r_car.stop();

    std::putchar('\n');
  }

  void car_with_value(Car car)
  {
    car.start();
    car.run();
    car.stop();

    std::putchar('\n');
  }

  int main()
  {
    Car* car_ptr = new Mercedes;

    // -------------------------------------------------
    
    car_with_pointer(car_ptr);
    // output ->
    //  Mercedes has just started
    //  Mercedes is running
    //  Mercedes has just stopped

    // virtual dispatch will work.

    // -------------------------------------------------

    car_with_reference(*car_ptr);
    // output ->
    //  Mercedes has just started
    //  Mercedes is running
    //  Mercedes has just stopped
    
    // virtual dispatch will work.

    // -------------------------------------------------

    car_with_value(*car_ptr);
    // output ->
    //  Car has just started
    //  Car is running
    //  Car has just stopped

    // because of *car_ptr will be copied to parameter variable 
    // Car object, object slicing will happen.
    // virtual dispatch mechanism WILL NOT work.

    // -------------------------------------------------

    Car* car_ptr_2 = new VolvoXC90;

    car_with_pointer(car_ptr_2);
    // output ->
    //  VolvoXC90 has just started
    //  VolvoXC90 is running
    //  VolvoXC90 has just stopped

    // virtual dispatch will work.

    // -------------------------------------------------

    car_with_pointer(car_ptr_2);
    // output ->
    //  VolvoXC90 has just started
    //  Volvo is running
    //  VolvoXC90 has just stopped

    // VolvoXC90 class did not override its base classes "run" 
    // virtual function, so base classes(Volvo) "run" 
    // function will be called.

    // virtual dispatch will work.

    // -------------------------------------------------
  }
*/

/*
  #include "headers/Car_2.h"

  void car_game(Car* p)
  {
    p->start();
    p->run();
    p->stop();

    p->open_sunroof();  // syntax error
    // error: 'class Car' has no member named 'open_sunroof'

    // virtual dispatch is a run-time mechanism
    // before run-time, there is a compile-time mechanism
    // name-lookup - context control - access control (static type)

    // name-lookup for "open_sunroof" 
    // will start from Car class scope -> NOT FOUND -> syntax error
  }

  int main()
  {
    Car* p_car = new Mercedes;
    car_game(p_car);
  }
*/

/*
  #include "headers/Car_3.h"

  void car_game(Car* p)
  {
    p->test_car();
  }

  int main()
  {
    Car* p_car = new Mercedes;

    car_game(p_car);
    // output ->
    //  Mercedes has just started
    //  Mercedes is running
    //  Mercedes has just stopped

    // virtual dispatch mechanism applied when 
    // a called non-virtual function is calling virtual functions.
    // because used `this` pointer is same in both function call.
  }
*/

/*
  class Base {
  public:
    virtual void foo()
    {
      std::cout << "Base::foo()\n";
    }
  };

  class Der : public Base {
  private:
    void foo() override
    {
      std::cout << "Der::foo()\n";
    }
    // overriding Base classes virtual function 
    // in derived classes private section is VALID.
  };

  void global_func(Base* p)
  {
    p->foo();
  }

  int main()
  {
    // ------------------------------------------------

    Der d1;
    global_func(&d1); // output -> Der::foo()

    // in compile time name lookup for "foo" 
    // will start from Base class scope -> FOUND
    // context control is OKAY.
    // access control is okay because "foo" is in public section 
    // of Base class.

    // in run-time virtual dispatch mechanism will be applied.
    // run-time does not care access control(public-protected-private)
    // virtual dispatch mechanism will be applied.
    // Der classes "foo" function in private section will be called.

    // ------------------------------------------------

    d1.foo(); // syntax error
    // error: 'virtual void Der::foo()' is private within this context

    // in compile time name lookup for "foo"
    // will start from Der class scope -> FOUND
    // context control is OKAY.
    // access control is NOT OKAY because of "foo" is in private section.

    // ------------------------------------------------
  }
*/

/*
              -------------------------------------
              | non-virtual interface idiom (NVI) |
              -------------------------------------
*/

/*
  class Base {
  public:
    void bar()
    {
      foo();
    }
  private:
    virtual void foo()
    {
      std::cout << "Base::foo()\n";
    }
  };

  class Der : public Base {
  private:
    void foo() override
    {
      std::cout << "Der::foo()\n";
    }
    // we can override Base classes virtual member function 
    // which is in private section.
  };

  void global_func(Base* p_base)
  {
    // ------------------------------------------------

    p_base->foo(); // syntax error
    // "foo" is an identifier 
    // its name lookup will start from Base class scope -> FOUND
    // context control is OKAY.
    // access control is NOT OKAY because of "foo" is in private section.

    // ------------------------------------------------

    p_base->bar();
    // "bar" is an identifier
    // its name lookup will start from Base class scope -> FOUND
    // context control is OKAY.
    // access control is OKAY.

    // in run-time virtual dispatch mechanism will be applied.
    // foo() function that invoked will be the overriden function
    // in Der class.

    // ------------------------------------------------
  }

  int main()
  {
    Base* b1 = new Der;
    global_func(b1);  // output -> Der::foo()
  }
*/

/*
  virtual dispatch mechanism will NOT work when
    - object slicing happens
    - in base classes constructor
    - in base classes destructor
    - when Base classes member function is called with 
      qualified name (Base::foo())
*/

/*
  #include "headers/Car_4.h"

  int main()
  {
    // ------------------------------------------------

    Volvo vx;
    // output ->
    //  Car has just started      -> Base::Base()
    //  Car is running            -> Base::Base()
    //  Car has just stopped      -> Base::Base()
    //  Car has just started      -> Base::~Base()
    //  Car is running            -> Base::~Base()
    //  Car has just stopped      -> Base::~Base()

    // ------------------------------------------------

    // when "vx" object is default initialized, Base(Car) classes
    // default constructor will be called.
    // Inside of Base classes default constructor, 
    // virtual functions("start", "run", "stop") 
    // which are overriden by Derived(Volvo) class
    // are being called.
    // Virtual dispatch mechanism will not work in 
    // Base classes constructor so Base classes 
    // virtual functions will be called.

    // for Derived class object("vx") to become alive,
    // first, Base class object inside of Derived class object
    // need to become alive 
    // then Derived classes data members,
    // after all of them, Derived class object will become alive.
    // Based on this information, when Base classes constructor
    // is executed, Derived class object is not alive yet.
    // so virtual dispatch mechanism
    // (calling Derived classes member function) is NOT possible.

    // ------------------------------------------------

    // when "vx" object is destroyed, Base(Car) classes
    // destructor will be called.
    // Inside of Base classes destructor,
    // virtual functions("start", "run", "stop")
    // which are overriden by Derived(Volvo) class
    // are being called.
    // Virtual dispatch mechanism will not work in
    // Base classes destructor so Base classes
    // virtual functions will be called.

    // for Derived class object("vx") to get destroyed,
    // first, Base class object inside of Derived class object
    // need to get destroyed,
    // then Derived classes data members,
    // after all of them, Derived class object will get destroyed.
    // Based on this information, when Base classes destructor
    // is executed, it will be destroyed. 
    // if virtual dispatch mechanism happens,
    // it will mean calling Derived classes member functions
    // without having a Base class object(it is already destroyed).
    // which is NOT possible.

    // ------------------------------------------------
  }
*/

/*
  #include "headers/Car_5.h"

  int main()
  {
    Volvo vx;

    vx.test_car();
    // output ->
    //  Car has just started
    //  Car is running
    //  Car has just stopped

    // because of "test_car" function is a non-virtual function
    // name lookup for "test_car" identifier,
    // will start from Volvo class scope -> NOT FOUND
    // will continue to Base class scope -> FOUND
    // Base classes "test_car" function will be called.

    // Base classes "test_car" function is calling
    // virtual functions("start", "run", "stop")
    // which are overriden by Derived(Volvo) class
    // but calling them with qualified name
    // (Base::start(), Base::run(), Base::stop())
    // so virtual dispatch mechanism will NOT work.
  }
*/

/*
  class Base_1{
  private:
    int m_x, m_y;
    virtual void foo();
  };

  class Base_2 {
  private:
    int m_x, m_y;
    virtual void foo();
    virtual void bar();
  };

  class Der : public Base_1 {};

  int main()
  {
    std::cout << "sizeof(Base_1) = " << sizeof(Base_1) << '\n';
    // output -> sizeof(Base_1) = 16 
    // 2 * sizeof(int) + sizeof(VPTR)

    std::cout << "sizeof(Base_2) = " << sizeof(Base_2) << '\n';
    // output -> sizeof(Base_2) = 16
    // 2 * sizeof(int) + sizeof(VPTR)

    std::cout << "sizeof(Der) = " << sizeof(Der) << '\n';
    // output -> sizeof(Der) = 16
    // 2 * sizeof(int) + sizeof(VPTR)

    // Virtual Function Table Pointer(VPTR) is embedded
    // inside of the Base_1 and Base_2 classes,
    // which have virtual functions.
    // VPTR is a pointer that points to the 
    // Virtual Function Table in heap memory.
  }
*/

/*
  - Every polymorphic object have to instantiate
    a Virtual Function Table Pointer(VPTR) to become alive.

  - For each polymorphic class, a Virtual Function Table
    created in heap memory.

    i.e, Volvo is a polymorphic class and there is 100 Volvo objects
    created in run time,
      - there will be 100 Virtual Function Table Pointer(VPTR)
      - there will be 1 Virtual Function Table created in heap memory.
*/

/*
  - static member functions CAN NOT be virtual functions.
  - global(free) functions CAN NOT be virtual functions.
  - constructors CAN NOT be virtual functions.
*/

/*
  virtual void global_func();   // syntax error
  // error: 'virtual' outside class declaration

  class Myclass {
  public:
    // ------------------------------------------------

    virtual Myclass(int); // syntax error
    // error: constructors cannot be declared 'virtual'

    // ------------------------------------------------

    virtual void foo();   // VALID (non-static member function)

    // ------------------------------------------------

    static virtual void bar();  // syntax error
    // error: member 'bar' cannot be declared both 
    // 'virtual' and 'static'

    // ------------------------------------------------
  };
*/

/*
                -----------------------------------
                | virtual constuctor(clone) idiom |
                -----------------------------------
*/

/*
  #include "headers/Car_6.h"

  void clone_cars(Car* p_car)
  {
    // We need to clone the same car object 
    // using Base class pointer object("p_car" -> parameter variable)

    // i.e, 
    //  if Volvo* object is passed to "p_car" parameter variable
    //  we need to clone Volvo object using "p_car" pointer object.

    Car* p_car2 = p_car->clone();
    p_car2->start();
    p_car2->run();
    p_car2->stop();

    // output
    //  Volvo has just started
    //  Volvo is running
    //  Volvo has just stopped
  }

  int main()
  {
    Car* p_Volvo = new Volvo;
    clone_cars(p_Volvo);
  }
*/

/*
                    -------------------------
                    |       covariance      |
                    |  variant return type  |
                    |       covariant       |
                    -------------------------
*/

/*
  // covariance is legal ONLY when the return type 
  // is a pointer or a reference.
  
  class AClass{};
  class BClass : public AClass {};

  class Base {
  public:
    virtual AClass* foo_1();
    virtual AClass& foo_2();
    virtual AClass  foo_3();
  };

  class Der : public Base {
  public:
    BClass* foo_1() override; // VALID
    // covariance is valid because the return type is a pointer

    BClass& foo_2() override; // VALID
    // covariance is valid because the return type is a reference

    BClass  foo_3() override; // syntax error
    // error: invalid covariant return type for 
    // 'virtual BClass Der::foo_3()'
  };
*/

/*
  #include "headers/Car_9.h"

  int main()
  {
    Audi* p_audi_1 = new Audi;

    // ------------------------------------------------

    Audi* p_audi_2 = p_audi_1->clone();  // syntax error
    // error: invalid conversion from 'Car*' to 'Audi*' 
    // "Audi::clone" function is returning Car* type 

    // ------------------------------------------------

    Audi* p_audi_3 = static_cast<Audi*>(p_audi_1->clone()); // VALID
    // casting Car* to Audi*

    // ------------------------------------------------

    Volvo* p_volvo_1 = new Volvo;
    Volvo* p_volvo_2 = p_volvo_1->clone();  // VALID
    // Volvo::clone function is returning Volvo* type
    // Car::clone pure virtual function is returning Car* type
    // covariance is valid because the return type is a pointer

    // ------------------------------------------------
  }
*/

/*
  // Question : 
  // How to write a function, when we dereference it, 
  // it will write derived classes name.

  #include "headers/Car_7.h"

  int main()
  {
    Car* p_car_1 = new Volvo;
    Car* p_car_2 = new Audi;

    std::cout << *p_car_1 << '\n';  
    // output -> I am Volvo

    std::cout << *p_car_2 << '\n';
    // output -> I am Audi
  }
*/

/*
                    ----------------------
                    | virtual destructor |
                    ----------------------
*/

/*
  class Base {
  public:
    ~Base()
    {
      std::cout << "Base destructor\n";
    }
  };

  class Der : public Base {
  public:
    ~Der()
    {
      std::cout << "Der destructor\n";
    }
  };

  void foo(Base* p_base)
  {
    delete p_base;
  }

  int main()
  {
    Base* p_base = new Der;
    foo(p_base);  // undefined behaviour(UB)
    // output -> Base destructor

    // deleting Base object inside Derived object
    // but not deleting Derived object itself.
  }
*/

/*
  class Base {
  public:
    virtual ~Base()
    {
      std::cout << "virtual Base destructor\n";
    }
  };

  class Der : public Base {
  public:
    ~Der() override
    {
      std::cout << "Der destructor override\n";
    }
  };

  void foo(Base* p_base)
  {
    delete p_base;
  }

  int main()
  {
    Base* p_base = new Der;
    foo(p_base);
    // output -> 
    //  Der destructor override
    //  virtual Base destructor

    // virtual dispatch mechanism will work
    // Der desturctor will be called first
    // inside of Der destructor, Base destructor will be called.
    // after Base destroyed, Der will also be destroyed
  }
*/

/*
  polymorphic Base classes destructor should be,

  - public virtual

  when client called Base classes destructor with Derived class object
  public virtual destuctor will let virtual dispatch mechanism work
  so it won't be an undefined behaviour.

  - protected non-virtual

  when Base classes non-virtual destructor is in protected region 
  because of client codes can not reach protected region,
  client code should call Derived classes destructor, 
  because Derived class can reach Base classes protected region.
  else, it will be a syntax error.
*/

/*
  class Base {
  protected:
    ~Base()
    {
      std::cout << "Base destructor\n";
    }
  };

  class Der : public Base {
  public:
    ~Der()
    {
      std::cout << "Der destructor\n";
    }
  };

  int main()
  {
    // ----------------------------------------------

    Base* p_base = new Der;

    delete p_base; // syntax error
    // error: 'Base::~Base()' is protected within this context

    // ----------------------------------------------

    Der* p_der = new Der;
    delete p_der; // VALID
    // output ->
    //  Der destructor
    //  Base destructor

    // ----------------------------------------------
  }
*/

// ------------------------------------------------------
// ------------------------------------------------------
// ------------------------------------------------------
// ------------------------------------------------------
// ------------------------------------------------------

/*
  class Base {
  public:
    virtual void vfunc(int x = 5)
    {
      std::cout << "Base::vfunc(int x), x = " << x << '\n';
    }
  };

  class Der : public Base{
  public:
    void vfunc(int x = 9) override
    {
      std::cout << "Der::vfunc(int x),  x = " << x << '\n';
    }
  };

  int main()
  {
    Der d1;
    Base* p_base = &d1;

    // --------------------------------------------------

    p_base->vfunc();
    // output -> Der::vfunc(int x), x = 5

    // virtual dispatch mechanism will work(run time)
    // but default argument is related with static type(compile time)

    // compiler will call Base::vfunc(5)
    // but in run time because of the virtual dispatch mechanism
    // Der::vfunc(5) will be called. 

    // --------------------------------------------------

    d1.vfunc();
    // output -> Der::vfunc(int x) x = 9

    // name lookup for "vfunc" identifier
    // will start from Der class scope -> FOUND

    // --------------------------------------------------
  }
*/

/*
  // overloaded functions can be overriden.

  class Base {
  public:
    virtual void func(int);
    virtual void func(double);
    virtual void func(int, int);
    // There are 3 overloads of "func" function

    virtual void foo();
    virtual void foo() const;
    // There are 2 overloads of "foo" function, const overloads
  };

  class Der : public Base {
  public:
    void func(int) override;
    void func(double) override;
    void func(int, int) override;

    void foo() override;
    void foo() const override;
  };

  void gf(Base& ref_base)
  {
    ref_base.foo();
    ref_base.func(1);
    ref_base.func(1.45);
    ref_base.func(2, 2);
  }
*/

/*
                        -------------------
                        | `final` keyword |
                        -------------------
*/

/*
  `final` is a contextual keyword.
    - can be use as a keyword
    - can be use as an identifier
*/

/*
  class AClass {};

  class BClass final : public AClass {};

  class CClass : public BClass {};  // syntax error
  // error: cannot derive from 'final' base 'BClass' 
  // in derived type 'CClass'
*/

/*
  class AClass {
  public:
    virtual void foo();
    virtual void func();
  };

  class BClass : public AClass {
  public:
    virtual void foo()  override;

    virtual void func() override final;
    // final virtual member function
  };

  class CClass : public BClass {
    virtual void foo() override;
    virtual void func() override; // syntax error
    // error: virtual function 'virtual void CClass::func()' 
    // overriding final function
  };
*/

/*
        --------------------------------------------------
        | run time type identification(information) RTTI |
        --------------------------------------------------
*/

/*
              ------------------------------------
              | `dynamic_cast` operator for RTTI |
              ------------------------------------
*/

/*
  class Base {};  // non-polymorphic class
  class Der : public Base{};

  int main()
  {
    Der d1;
    Base* p_base = &d1;

    Der* p_der = dynamic_cast<Der*>(p_base);  // syntax error
    // error: cannot 'dynamic_cast' 'p_base' (of type 'class Base*') 
    // to type 'class Der*' (source type is not polymorphic)
  }
*/

/*
  class Base{
  public:
    virtual void bar(){}
  };

  class Der : public Base{};

  int main()
  {
    Der d1;
    Base* p_base = &d1;

    Der* p_der = dynamic_cast<Der*>(p_base); // VALID
  }
*/

/*
  #include "headers/Car_8.h"

  void car_game(Car* p_car)
  {
    std::cout << *p_car << '\n';
    p_car->start();
    p_car->run();
    p_car->stop();

    // we want to open sunroof if it is a Volvo
    // when dynamic_cast failed it will return nullptr
    if (Volvo* p_volvo = dynamic_cast<Volvo*>(p_car))
      p_volvo->open_sunroof();
    
    std::cout << '\n';
  }

  int main()
  {
    // ------------------------------------------------

    Car* p_car_1 = new Volvo;
    car_game(p_car_1);
    // output ->
    //  I am Volvo              -> virtual dispatch
    //  Volvo has just started  -> virtual dispatch
    //  Volvo is running        -> virtual dispatch
    //  Volvo has just stopped  -> virtual dispatch
    //  Volvo's sunroof opened  (dynamic cast succeeded)
    // downcasting with `dynamic_cast` operator

    delete p_car_1;

    // ------------------------------------------------

    Car* p_car_2 = new Audi;
    car_game(p_car_2);
    // output ->
    //  I am Audi               -> virtual dispatch
    //  Audi has just started   -> virtual dispatch
    //  Audi is running         -> virtual dispatch
    //  Audi has just stopped   -> virtual dispatch
    // (dynamic cast failed)

    delete p_car_2;

    // ------------------------------------------------

    Car* p_car_3 = new VolvoXC90;
    car_game(p_car_3);
    // output ->
    //  I am VolvoXC90
    //  VolvoXC90 has just started
    //  VolvoXC90 is running
    //  VolvoXC90 has just stopped
    //  Volvo's sunroof opened  (dynamic cast succeeded)
    // upcasting with `dynamic_cast` operator

    delete p_car_3;

    // ------------------------------------------------
  }
*/

/*
  #include "headers/Car_8.h"

  void car_game(Car& ref_car)
  {
    std::cout << ref_car << '\n';
    ref_car.start();
    ref_car.run();
    ref_car.stop();

    try
    {
      // if dynamic_cast to a reference type failed 
      // it will throw a bad_cast exception
      Volvo& ref_volvo = dynamic_cast<Volvo&>(ref_car);
      ref_volvo.open_sunroof();
    }
    catch (const std::exception& ex)
    {
      std::cout << "exception caught: " << ex.what() << '\n';
    }

    std::cout << '\n';
  }

  int main()
  {
    // ------------------------------------------------

    Car* p_car_1 = new Volvo;
    car_game(*p_car_1);
    // output ->
    //  I am Volvo
    //  Volvo has just started
    //  Volvo is running
    //  Volvo has just stopped
    //  Volvo's sunroof opened  (dynamic cast succeeded)
    // downcasting with `dynamic_cast` operator

    delete p_car_1;

    // ------------------------------------------------

    Car* p_car_2 = new Audi;
    car_game(*p_car_2);
    // output ->
    //  I am Audi
    //  Audi has just started
    //  Audi is running
    //  Audi has just stopped
    //  exception caught: std::bad_cast

    delete p_car_2;

    // ------------------------------------------------
  }
*/

/*
                ------------------------------
                | `typeid` operator for RTTI |
                ------------------------------
*/

/*
  - an expression created with `typeid` operator is a 
    const reference to an object from `std::type_info` class
*/

/*
  #include <typeinfo>

  class Myclass{};

  int main()
  {
    int x = 10;
    const std::type_info& cr1 = typeid(x);
    const std::type_info& cr2 = typeid(Myclass);

    // ----------------------------------------------------
    // can not create an object from `std::type_info` class
    // ----------------------------------------------------

    std::type_info obj1; // syntax error
    // error: no matching function for call to 
    // 'std::type_info::type_info()'

    // std::type_info classes default constructor is not declared

    // ----------------------------------------------------

    std::type_info obj2 = typeid(Myclass);  // syntax error
    // error: use of deleted function 
    // 'std::type_info::type_info(const std::type_info&)'

    // std::type_info classes copy ctor is deleted.

    // ----------------------------------------------------

    Myclass m1;
    constexpr bool b1 = typeid(Myclass) == typeid(m1);
    // b1 -> true

    // std::type_info class have an operator== function

    // ----------------------------------------------------
  }
*/

/*
  // if Base class is not a polymorphic class

  class Base {};

  class Der : public Base {};

  int main()
  {
    Der d1;
    Base* p_base = &d1;

    constexpr bool b1 = (typeid(*p_base) == typeid(Der));
    // b1 -> false
    // "*p_base" is a constant expression
    // when Base class is not a polymorphic class
  }
*/

/*
  // if Base class is a polymorphic class

  class Base {
  public:
    virtual ~Base() = default;  
  };

  class Der : public Base {};

  int main()
  {
    std::cout << std::boolalpha;

    Der d1;
    Base* p_base = &d1;

    // ------------------------------------------------

    constexpr bool b1 = (typeid(*p_base) == typeid(Der)); // syntax error
    // error: call to non-'constexpr' function 
    // 'bool std::type_info::operator==(const std::type_info&) const'

    // "*p_base" is not a constant expression
    // when Base class is a polymorphic class

    // ------------------------------------------------

    std::cout << (typeid(*p_base) == typeid(Der)) << '\n';
    // output -> true

    // ------------------------------------------------
  }
*/

/*
  #include "headers/Car_8.h"

  void car_game(Car* p_car)
  {
    std::cout << *p_car << '\n';
    p_car->start();
    p_car->run();
    p_car->stop();

    if (typeid(*p_car) == typeid(Volvo))
    {
      // Volvo type CAN get inside if-block
      // VolvoXC90 type CAN NOT get inside if-block.

      Volvo* p_Volvo = static_cast<Volvo*>(p_car);
      p_Volvo->open_sunroof();
    }
    std::cout << '\n';
  }

  int main()
  {
    // --------------------------------------------

    Car* p_car_1 = new Volvo;
    car_game(p_car_1);
    // output ->
    // I am Volvo
    //  Volvo has just started
    //  Volvo is running
    //  Volvo has just stopped
    //  Volvo's sunroof opened

    delete p_car_1;

    // --------------------------------------------

    Car* p_car_2 = new Audi;
    car_game(p_car_2);
    // output ->
    //  I am Audi
    //  Audi has just started
    //  Audi is running
    //  Audi has just stopped

    delete p_car_2;

    // --------------------------------------------

    Car* p_car_3 = new VolvoXC90;
    car_game(p_car_3);
    // output ->
    //  I am VolvoXC90
    //  VolvoXC90 has just started
    //  VolvoXC90 is running
    //  VolvoXC90 has just stopped

    delete p_car_3;

    // --------------------------------------------
  }
*/

/*
  // compiler WILL NOT generate an operation code for 
  // typeid() operator's operand (unevaluated context)

  int main()
  {
    // --------------------------------------------

    int x = 10;

    auto& obj_1 = typeid(x++);
    std::cout << x << '\n';   // output -> 10

    // --------------------------------------------

    int arr[10];
    auto& obj_2 = typeid(arr[40]);  // VALID, NO UB

    // --------------------------------------------
  }
*/

/*
                      -----------------------
                      | private inheritance |
                      -----------------------
*/

/*
  -> Base classes public section will be 
    in your derived classes private section.
  -> Clients can not reach Base classes 
    public member function from with Der object.

  --> Upcasting is NOT valid in global functions.
  --> Upcasting is valid in derived classes member functions
  --> Upcasting is valid in friend functions of derived class.
*/

/*
  class Base {
  public:
    void foo();
  };

  class Der : private Base {
    void bar()
    {
      foo();  // VALID
    }

    void derived_member_func()
    {
      Der d1;
      Base* p_base = &d1;
      Base& ref_base = d1;
      // Der classes member functions 
      // can reach Der classes private section
      // so upcasting is LEGAL in derived classes member functions
    }

    friend void func(); // global friend function of Der class
  };

  void func()
  {
    Der d1;
    Base* p_base = &d1;   // VALID
    Base& ref_base = d1;  // VALID

    // friend function of Der class 
    // can reach Der classes private section
    // so upcasting is LEGAL inside friend functions of Derived class.
  }

  int main()
  {
    // --------------------------------------------------

    Der d1;
    d1.foo(); // syntax error
    // error: 'void Base::foo()' is inaccessible within this context

    // in private inheritance, Base classes public interface
    // will be added to Derived classes private interface

    // so name lookup for "foo" identifier
    // will start from Der class scope -> FOUND 
    // context control is OKAY
    // access control is NOT OKAY because "foo" is in private section.

    // --------------------------------------------------

    Base* p_base = &d1;   // syntax error
    // 'Base' is an inaccessible base of 'Der'

    Base& ref_base = d1;  // syntax error
    // 'Base' is an inaccessible base of 'Der'

    // in private inheritance, there is no implicit conversion
    // from derived class to base class in client code.

    // --------------------------------------------------
  }
*/

/*
  // --------------- COMPOSITION (CONTAINMENT) ---------------
  
  class AClass {
  protected:
    void protected_A_func();
  public:
    void public_A_func();
    virtual void public_virtual_A_func();
  };

  class BClass {
  public:
    void public_B_func()
    {
      m_AClass.public_A_func();     // VALID
      // reaching member type's public section is VALID
    }

    void public_B_func2()
    {
      m_AClass.protected_A_func();  // syntax error
      // error: 'void AClass::protected_A_func()' 
      // is protected within this context

      // reaching member type's protected section is NOT VALID
    }

    void forwarding_public_B_func()    // forwarding function
    {
      m_AClass.public_A_func();
    }

    // ------------------------------------------------

    virtual void public_virtual_A_func() override;  // syntax error
    // error: 'virtual void BClass::public_virtual_A_func()' 
    // marked 'override', but does not override

    // overriding member type's virtual function is NOT VALID

    // ------------------------------------------------
  private:
    AClass m_AClass; // member type(object)
  };

  // ------------------------------------------------

  // BClass can reach AClass's public section by its member function.

  // BClass can not reach AClass's protected
  // section by its member function. 

  // It is not VALID to override member type(AClass)'s virtual function

  // ------------------------------------------------
*/

/*
  // --------------- PRIVATE INHERITANCE ---------------
  
  class AClass {
  protected:
    void protected_A_func();
  public:
    void public_A_func();
    virtual void public_virtual_A_func();
  };

  class BClass : private AClass {
  public:
    void public_B_func()
    {
      public_A_func();  // VALID
      // reaching Base classes public section is VALID

      protected_A_func(); // VALID
      // reaching Base classes protected section is VALID
    }

    void forwarding_public_B_func()   // forwarding function
    {
      public_A_func();
    }
    //using AClass::public_A_func; 

    virtual void public_virtual_A_func() override;  // VALID
  };

  // ------------------------------------------------

  // Derived class can reach its private inherited 
  // base classes public section

  // Derived class can reach its private inherited
  // base classes protected section

  // Derived class can override its private inherited
  // base classes virtual function

  // ------------------------------------------------
*/

/*
                ---------------------------------
                | Empty Base Optimization (EBO) |
                ---------------------------------
*/

/*
  class EmptyClass {};

  class AClass {
  private:
    int m_val;
    EmptyClass m_EmptyClass;  // member type(object)
  };

  class BClass {
  private:
    int m_val;
  };

  class CClass : private EmptyClass {
  private:
    int m_val;
  };
  // EBO will be applied in private inheritance.

  int main()
  {
    std::cout << "sizeof(EmptyClass) = " << sizeof(EmptyClass) << '\n';
    // output -> sizeof(EmptyClass) = 1

    std::cout << "sizeof(AClass) = " << sizeof(AClass) << '\n';		
    // output -> sizeof(AClass) = 8  
    // (sizeof(int)[4] + sizeof(EmptyClass)[1] + 3byte padding)

    std::cout << "sizeof(BClass) = " << sizeof(BClass) << '\n';
    // output -> sizeof(BClass) = 4 

    std::cout << "sizeof(CClass) = " << sizeof(CClass) << '\n';		
    // output -> sizeof(CClass) = 4 (NOT 5 or 8 -> EBO)
  }
*/

/*
                    --------------------------
                    | restricted polymophism |
                    --------------------------
*/

/*
  class Base {
  public:
    virtual void vfunc()
    {
      std::cout << "Base::vfunc\n";
    }
  };

  class Der : public Base {
  public:
    void vfunc() override
    {
      std::cout << "Der::vfunc\n";
    }
  };

  class Der_2 : private Base {
  public:
    void vfunc() override
    {
      std::cout << "Der_2::vfunc\n";
    }
    friend void g_func2();
  };

  void foo(Base& ref_base)
  {
    ref_base.vfunc();
  }

  void g_func1()
  {
    // ------------------------------------------------

    Der d1;
    foo(d1);  // VALID
    // upcasting to public inherited Base class
    // is VALID in global functions

    // ------------------------------------------------

    Der_2 d2;
    foo(d2);  // syntax error
    // error: 'Base' is an inaccessible base of 'Der_2'

    // upcasting to private inherited Base class 
    // is NOT VALID in global functions
    
    // ------------------------------------------------
  }

  void g_func2()
  {
    // ------------------------------------------------

    Der d1;
    foo(d1);  // VALID
    // upcasting to public inherited Base class
    // is VALID in global functions

    // ------------------------------------------------

    Der_2 d2;
    foo(d2);  // VALID
    // upcasting to private inherited Base class
    // is VALID if a function is declared as friend in Derived class

    // ------------------------------------------------
  }

  int main()
  {
    g_func1();  
    // output -> Der::vfunc

    g_func2();
    // output -> 
    //  Der::vfunc
    //  Der_2::vfunc
  }
*/

/*
                    -------------------------
                    | protected inheritance |
                    -------------------------
*/

/*
  class AClass {
  public:
    void public_A_func()
    {
      std::cout << "AClass::public_A_func\n";
    }
  };

  class BClass : protected AClass {
  public:
    void public_B_func()
    {
      public_A_func();
    }
  };

  class CClass : public BClass {
  public:
    void public_C_func()
    {
      public_B_func();

      // ---> class BClass : private AClass
      // "public_B_func" function CAN NOT invoke "public_A_func" function
      // because of the private inheritence 
      // "public_A_func" function is in BClass's private section

      // ---> class BClass : protected AClass
      public_A_func();
      // "public_B_func" function CAN invoke "public_A_func" function
      // because of the protected inheritence
      // "public_A_func" function is in BClass's protected section
      // so Derived class can reach Base classes protected section.
    }
  };


  int main()
  {
    CClass c1;
    c1.public_C_func();
    // output -> 
    //  AClass::public_A_func
    //  AClass::public_A_func
  }
*/

/*
                    ------------------------
                    | multiple inheritence |
                    ------------------------
*/

/*
  // classes default inheritance is private inheritance
  // structs default inheritance is public inheritance

  class AClass {};
  class BClass {};

  class Der_1 : public AClass, public BClass {
    // public inheritance AClass
    // public inheritance BClass
  };

  class Der_2 : public AClass, BClass {
    // public inheritance AClass
    // private inheritance BClass
  };

  class Der_3 : AClass, BClass {
    // private inheritance AClass
    // private inheritance BClass
  };

  struct Der_4 : AClass, BClass {
    // public inheritance AClass
    // public inheritance BClass
  };
*/

/*
  class AClass {
    int m_x;
  };
  class BClass {
    int m_x;
  };

  class Der : public AClass, public BClass {};

  int main()
  {
    std::cout << "sizeof(AClass) = " << sizeof(AClass) << '\n';
    // output -> sizeof(AClass) = 4
    std::cout << "sizeof(BClass) = " << sizeof(BClass) << '\n';
    // output -> sizeof(BClass) = 4
    std::cout << "sizeof(Der) = " << sizeof(Der) << '\n';
    // output -> sizeof(Der) = 8
  }
*/

/*
  class XClass {
  public:
    XClass()
    {
      std::cout << "XClass default ctor\n";
    }

    XClass(int a)
    {
      std::cout << "XClass(int a), a = " << a << '\n';
    }
  };

  class YClass {
  public:
    YClass()
    {
      std::cout << "YClass default ctor\n";
    }

    YClass(int b)
    {
      std::cout << "YClass(int b), b = " << b << '\n';
    }
  };

  class Der_1 : public XClass, public YClass {
  public:
    Der_1()
    {
      std::cout << "Der_1 default ctor\n";
    }
  };

  class Der_2 : public XClass, public YClass {
  public:
    Der_2() : YClass(1), XClass(9)
    {
      std::cout << "Der_2 default ctor\n";
    }
  };

  int main()
  {
    // ------------------------------------------------

    Der_1 d1;
    // output ->
    //  XClass default ctor
    //  YClass default ctor
    //  Der_1 default ctor

    // class Der : public XClass, public YClass
    // because of XClass is before YClass in inheritance definition
    // XClass default ctor will be called first

    // ------------------------------------------------

    Der_2 d2;
    // output ->
    //  XClass(int a), a = 9
    //  YClass(int b), b = 1
    //  Der_2 default ctor

    // ------------------------------------------------

    // It is better writing ctor initializer list
    // in the same order in inheritance definition.

    // if -> class Der : public XClass, public YClass
    // constructor initializer list should be 
    // Der_2() : XClass(9), YClass(1)

    // ------------------------------------------------
  }
*/

/*
  class XClass {
  public:
    void x_func() { std::cout << "XClass::x_func\n"; }
  };

  class YClass {
  public:
    void y_func() { std::cout << "YClass::y_func\n"; }
  };

  class Der : public XClass, public YClass {};

  void foo(XClass&) { std::cout << "foo(XClass&)\n"; }
  void foo(YClass&) { std::cout << "foo(YClass&)\n"; }

  void bar(XClass*) { std::cout << "bar(XClass*)\n"; }
  void bar(YClass*) { std::cout << "bar(YClass*)\n"; }

  int main()
  {
    // ------------------------------------------------

    Der d1;
    d1.x_func();  // output -> XClass::x_func
    d1.y_func();  // output -> YClass::y_func

    // both XClass and YClass's public interface
    // will be in Der class's public interface

    // ------------------------------------------------

    XClass* p_XClass = &d1;
    YClass* p_YClass = &d1;

    XClass& ref_XClass = d1;
    YClass& ref_YClass = d1;

    // upcasting is VALID in both pointers and references
    
    // ------------------------------------------------

    foo(d1);  // syntax error
    // error: call of overloaded 'foo(Der&)' is ambiguous

    foo(static_cast<XClass&>(d1));  // output -> foo(XClass&)
    foo(static_cast<YClass&>(d1));  // output -> foo(YClass&)

    // ------------------------------------------------

    bar(&d1); // syntax error
    // error: call of overloaded 'bar(Der*)' is ambiguous

    bar(static_cast<XClass*>(&d1)); // output -> bar(XClass*)
    bar(static_cast<YClass*>(&d1)); // output -> bar(YClass*)

    // ------------------------------------------------
  }
*/

/*
  class XClass {
  public:
    virtual void virtual_X_func(int)
    {
      std::cout << "XClass::virtual_X_func(int)\n";
    }
  };

  class YClass {
  public:
    virtual void virtual_Y_func(int, int)
    {
      std::cout << "YClass::virtual_Y_func(int, int)\n";
    }
  };

  class Der : public XClass, public YClass {
  public:
    virtual void virtual_X_func(int) override
    {
      std::cout << "Der::virtual_X_func(int)\n";
    }

    virtual void virtual_Y_func(int,int) override
    {
      std::cout << "Der::virtual_Y_func(int, int)\n";
    }
  };

  void foo(XClass& ref_XClass, YClass& ref_YClass)
  {
    ref_XClass.virtual_X_func(0);	
    ref_YClass.virtual_Y_func(0, 12);	
  }

  int main()
  {
    Der d1;
    foo(d1, d1);    // upcasting will be done for both Base classes
    // output ->
    //  Der::virtual_X_func(int)
    //  Der::virtual_Y_func(int, int)
  }
*/

/*
  class XClass {
  public:
    void foo()
    {
      std::cout << "XClass::foo\n";
    }
  };

  class YClass {
  public:
    void foo(int, int)
    {
      std::cout << "YClass::foo(int, int)\n";
    }
  };

  class Der : public XClass, public YClass {};

  int main()
  {
    Der d1;

    // ------------------------------------------------

    //d1.foo(); // syntax error
    // error: request for member 'foo' is ambiguous

    // name lookup for "foo" identifier
    // will start from Der class scope -> NOT FOUND
    // IN SAME TIME will continue in XClass classes scope -> FOUND
    // IN SAME TIME will continue in YClass classes scope -> FOUND
    // so ambiguity error will be occured.

    // ------------------------------------------------

    d1.XClass::foo();     
    // output -> XClass::foo
    d1.YClass::foo(1, 2); 
    // output -> YClass::foo(int, int)

    // ------------------------------------------------

    static_cast<XClass&>(d1).foo();
    // output -> XClass::foo
    static_cast<YClass&>(d1).foo(1,2);
    // output -> YClass::foo(int, int)

    // ------------------------------------------------
  }
*/

/*
  class XClass {
  public:
    void foo()
    {
      std::cout << "XClass::foo\n";
    }
  };

  class YClass {
  public:
    void foo(int, int)
    {
      std::cout << "YClass::foo(int, int)\n";
    }
  };

  class Der : public XClass, public YClass {
  public:
    using XClass::foo;
    using YClass::foo;
  };

  int main()
  {
    Der d1;

    // ------------------------------------------------

    d1.foo();         
    // output -> XClass::foo

    // name lookup for "foo" identifier
    // will start from Der class scope -> FOUND (2 overloads)
    // context control will select XClass::foo

    // ------------------------------------------------

    d1.foo(12, 23);   
    // output -> YClass::foo(int, int)

    // name lookup for "foo" identifier
    // will start from Der class scope -> FOUND (2 overloads)
    // context control will select YClass::foo

    // ------------------------------------------------
  }
*/

/*
            ----------------------------------------
            | Dreadful Diamond on Derivation (DDD) |
            ----------------------------------------
*/

/*
  class Person {
  public:
    Person()
    {
      std::cout << "Person::Person(), this = " << this << '\n';
    }
    void speak()
    {
      std::cout << "Person::speak(),  this = " << this << '\n';
    }
  };

  class Worker  : public Person {};
  class Teacher : public Person {};

  class MathTeacher : public Worker, public Teacher {
  public:
    void solve_equation()
    {
      // speak();   // unqualified name(ambiguity)
      // error: reference to 'speak' is ambiguous

      Worker::speak();  // qualified name
      Teacher::speak(); // qualified name
    }
  };

  int main()
  {
    // ------------------------------------------------

    MathTeacher m;
    // output ->
    //  Person::Person(), this = 0x23d1ffe4e (Person inside Worker)
    //  Person::Person(), this = 0x23d1ffe4f (Person inside Teacher)

    // ------------------------------------------------

    m.speak();  // syntax error
    // error: request for member 'speak' is ambiguous

    // name lookup for "speak" identifier
    // will start from MathTeacher class scope    -> NOT FOUND
    // - unqualified name in Worker class scope   -> FOUND
    // - unqualified name in Teacher class scope  -> FOUND
    // ambiguity error will be occured.

    // ------------------------------------------------

    // using qualified names for disambiguity.

    m.Worker::speak();
    // output -> Person::speak(),  this = 0x23d1ffe4e
    m.Teacher::speak();
    // output -> Person::speak(),  this = 0x23d1ffe4f

    // ------------------------------------------------

    // using static_cast operator for disambiguity.

    static_cast<Worker&>(m).speak();
    // output -> Person::speak(),  this = 0x23d1ffe4e
    static_cast<Teacher&>(m).speak();
    // output -> Person::speak(),  this = 0x23d1ffe4f

    // ------------------------------------------------

    Person* p_person = &m;  // syntax error
    // error: 'Person' is an ambiguous base of 'MathTeacher'

    // ------------------------------------------------

    // using static_cast operator for disambiguity.

    Person* p_person1 = static_cast<Teacher*>(&m);
    Person* p_person2 = static_cast<Worker*>(&m);

    // ------------------------------------------------
  }
*/

/*
  class Device {
  private:
    bool m_flag{};
  public:
    bool is_on() const
    {
      return m_flag;
    }
    void turn_on()
    {
      m_flag = true;
      std::cout << "Device ON\n";
    }
    void turn_off()
    {
      m_flag = false;
      std::cout << "Device OFF\n";
    }
  };

  class Fax : public Device {
  public:
    virtual void send_fax(){
      if (is_on())
        std::cout << "Device ON, fax CAN be sent.\n";
      else
        std::cout << "Device OFF, fax CAN NOT be sent.\n";
    }
    virtual void recieve_fax(){
      if (is_on())
        std::cout << "Device ON, fax CAN be recieved.\n";
      else
        std::cout << "Device OFF, fax CAN NOT be recieved.\n";
    }
  };

  class Modem : public Device {
  public:
    virtual void send_packet() {
      if (is_on())
        std::cout << "Device ON, packet CAN be sent.\n";
      else
        std::cout << "Device OFF, packet CAN NOT be sent.\n";
    }
    virtual void recieve_packet() {
      if (is_on())
        std::cout << "Device ON, packet CAN be recieved.\n";
      else
        std::cout << "Device OFF, packet CAN NOT be recieved.\n";
    }
  };

  class FaxModem : public Fax, public Modem {};

  int main()
  {
    FaxModem fm;

    // ------------------------------------------------

    fm.Fax::turn_on();  // output -> Device ON
    fm.recieve_fax();   // output -> Device ON, fax CAN be recieved.
    fm.send_packet();   // output -> Device OFF, packet CAN be sent.

    // Device in Fax(1st Base) is ON 
    // but Device in Modem(2nd Base) is still OFF

    // ------------------------------------------------

    fm.Modem::turn_off(); // output -> Device OFF
    fm.send_fax();        // output -> Device ON, fax CAN be sent.

    // Device in Modem is OFF,  
    // but Device in Fax is still ON

    // ------------------------------------------------
  }
*/

/*
                    -----------------------
                    | virtual inheritance |
                    -----------------------
*/

/*
  class Person {
  public:
    Person()
    {
      std::cout << "Person::Person(), this = " << this << '\n';
    }
    void speak()
    {
      std::cout << "Person::speak(),  this = " << this << '\n';
    }
  };

  class Worker  : virtual public Person {};
  class Teacher : virtual public Person {};
  // virtual inheritance

  class MathTeacher : public Worker, public Teacher {
  public:
    void solve_equation()
    {
      speak();
    }
  };

  int main()
  {
    MathTeacher mt;
    // output -> Person::Person(), this = 0x329cfff870

    // because of the virtual inheritence 
    // only one Person object will be created
    // for both base classes(Worker and Teacher)

    mt.speak();
    // output -> Person::speak(),  this = 0x329cfff870

    Person* p = &mt;  // VALID
    Person& r = mt;   // VALID
  }
*/

/*
  class Device {
  private:
    bool m_flag{};
  public:
    bool is_on() const
    {
      return m_flag;
    }
    void turn_on()
    {
      m_flag = true;
      std::cout << "Device ON\n";
    }
    void turn_off()
    {
      m_flag = false;
      std::cout << "Device OFF\n";
    }
  };

  class Fax : virtual public Device {
  public:
    virtual void send_fax(){
      if (is_on())
        std::cout << "Device ON, fax CAN be sent.\n";
      else
        std::cout << "Device OFF, fax CAN NOT be sent.\n";
    }
    virtual void recieve_fax(){
      if (is_on())
        std::cout << "Device ON, fax CAN be recieved.\n";
      else
        std::cout << "Device OFF, fax CAN NOT be recieved.\n";
    }
  };

  class Modem : virtual public Device {
  public:
    virtual void send_packet() {
      if (is_on())
        std::cout << "Device ON, packet CAN be sent.\n";
      else
        std::cout << "Device OFF, packet CAN NOT be sent.\n";
    }
    virtual void recieve_packet() {
      if (is_on())
        std::cout << "Device ON, packet CAN be recieved.\n";
      else
        std::cout << "Device OFF, packet CAN NOT be recieved.\n";
    }
  };

  class FaxModem : public Fax, public Modem {};

  int main()
  {
    FaxModem fm;

    // ------------------------------------------------

    fm.turn_on();       // output -> Device ON  
    fm.recieve_fax();   // output -> Device ON, fax CAN be recieved.
    fm.send_packet();   // output -> Device ON, packet CAN be sent.

    // Device is ON for both Base classes(Fax and Modem)

    // ------------------------------------------------

    fm.turn_off();      // output -> Device OFF
    fm.send_fax();      // output -> Device OFF, fax CAN NOT be sent.
    fm.recieve_packet();
    // output -> Device OFF, packet CAN NOT be recieved.

    // Device is OFF for both Base classes(Fax and Modem)

    // ------------------------------------------------
  }
*/

/*
  class Base {
  public:
    Base(const char* p)
    {
      std::cout << p << '\n';
    }
  };

  class Der_XClass : virtual public Base {
  public:
    Der_XClass() : Base {"Der_XClass"} {}
  };

  class DerYClass : virtual public Base {
  public:
    DerYClass() : Base{ "DerYClass" } {}
  };

  class DerZClass : public Der_XClass, public DerYClass {
  public:
    DerZClass() : Base{ "DerZClass" } {}
  };

  class DerAClass : public DerZClass {
  public:
    DerAClass() : Base{ "DerAClass" } {}
  };

  class DerBClass : public DerAClass {
  public:
    DerBClass() : Base{ "DerBClass" } {}
  };

  int main()
  {
    DerBClass d1; // output -> DerBClass
  }
*/