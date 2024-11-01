#include <iostream>

/*
                        ================
                        | nested types |
                        ================
*/

/*
  class Myclass {
    int m_x;             
    // data member

    void func();          
    // member function

    class Nested {};      
    // nested type, member type, type member
  };
*/

/*
  class Myclass {
    class Nested {
      int m_a, m_b, m_c, m_d;
    };
  };

  int main()
  {
    std::cout << "sizeof(Myclass) = " << sizeof(Myclass) << "\n";
    // output -> sizeof(Myclass) = 1
  }
*/

/*
  class AClass {
  public:
    class Nested {
    private:
      int m_a, m_b, m_c, m_d;
    };
  };

  int main()
  {
    // --------------------------------------------------

    Nested n1; // syntax error
    // error: 'Nested' was not declared in this scope

    // name lookup will start in main() block scope -> NOT FOUND
    // name lookup will continue in global scope    -> NOT FOUND

    // --------------------------------------------------

    AClass::Nested n2; // VALID
    // name lookup for `Nested` starts from AClass's class scope -> FOUND

    // --------------------------------------------------
  }
*/

/*
  class AClass {
  private:
    class Nested {
      int m_a, m_b, m_c, m_d;
    };
  };

  int main()
  {
    AClass::Nested n1;  // syntax error
    // error: 'class AClass::Nested' is private within this context

    // name lookup for `Nested` starts from AClass's class scope -> FOUND
    // in access control phase because member type Nested 
    // is in private section of class AClass, 
    // inside main function we can not reach Nested type.
  }  
*/

/*
  class AClass {
  private:
    class Nested {        
    private:
      int m_a, m_b, m_c, m_d;
    };  // member type

    void member_func()  // non-static inline member function
    {
      Nested n1;  // VALID
      auto val = n1.m_a; // sythax error.
      // error: 'int AClass::Nested::m_a' is private within this context

      // Outer class can not reach 
      // inner class's(Nested) private section.
    }
  };
*/

/*
  class Outer {
  private:
    int m_x;

    class Inner {
      void func()
      {
        auto sz = sizeof(m_x);  // VALID
        auto sz = sizeof(m_y);  // VALID
        ms_z = 5;               // VALID
        // inner class can reach outer class private section.
      }
    };

    int m_y;
    static int ms_z;
  };
*/

/*
  - nested type can be a class or struct
  - nested type can be an enumeration type  
      enum or enum class(scoped enum)
  - nested type can be a type alias
*/

/*
  class AClass {
  public:
    class NestedClass {};               
    // nested type (class)

    enum Color {Red, Yellow, Green};    
    // nested type (enum)

    using Word = int;                   
    // nested type (type alias)
  };

  int main()
  {
    AClass::Word myword;
    AClass::Color mycolor = AClass::Red;
    AClass::NestedClass mynested;
  }
*/

/*
  class AClass {
  private:
    class Nested {};
  public:
    static Nested foo() { return Nested{}; }
  };

  int main()
  {
    std::cout <<std::boolalpha;

    // --------------------------------------------------

    AClass::Nested n1;  // syntax error
    // error: 'class AClass::Nested' is private within this context

    AClass::Nested n2 = AClass::foo();  // syntax error
    // error: 'class AClass::Nested' is private within this context

    // name lookup for `Nested` starts from AClass's class scope -> FOUND
    // in access control phase because member type Nested
    // is in private section of class AClass,
    // inside main function we can not reach Nested type.

    // --------------------------------------------------

    auto n3 = AClass::foo(); // VALID
    // "n3"'s declaration type is AClass::Nested

    // `auto` keyword is not a name
    // name-lookup - context control - access control WON'T be applied.

    // compiler deduce the type of `auto` (auto type deduction)
    // from the return type of static AClass::foo() function.
    
    // --------------------------------------------------
  }
*/

/*
  class AClass {
    // --------------------------------------------------

    // non-static inline member function
    void func() 
    {
      m_x = 5;
      // name-lookup for "m_x" will be done in whole class scope
      // from top to bottom. Because func is an INLINE member function.
      // "m_x" will be found in class scope.
    }

    // --------------------------------------------------
  
    Nested n1;  // syntax error
    // error: 'Nested' does not name a type

    // name-lookup will be done from top to bottom of the class scope
    // in "n1" objects declaration, "Nested" type is not defined yet.

    // --------------------------------------------------

    class Nested {};
    int m_x;
  };
*/

/*
    using selected_type = double;

    class Myclass {
      // --------------------------------------------------
      selected_type m_x; 
      // "m_x"'s declaration type is double 

      // name-lookup for "selection_type" will be done from 
      // top of Myclass scope to "m_x" objects declaration. -> NOT FOUND
      // name-lookup will continue from top of global scope
      // to Myclass definition. -> FOUND(221)

      // --------------------------------------------------

      using selected_type = int;
      selected_type m_y; 
      // "m_y"'s declaration type is int

      // name-lookup for "selection_type" will be done from 
      // top of Myclass scope to "m_x" objects declaration. -> FOUND(235)

      // --------------------------------------------------
    };
*/

/*
  // enclosing.h
  // ----------------

  class Enclosing {
    class Nested {};

    Nested m_x;
    Enclosing::Nested m_y;
    // both "m_x" and "m_y" objects declaration type is Enclosing::Nested

  public:
    Nested func(Nested);
  };


  // enclosing.cpp
  // ----------------
  // --------------------------------------------------

  Nested Enclosing::func(Nested x) {} // syntax error
  // error: 'Nested' does not name a type

  // name-lookup for return type "Nested" 
  // will be done in global scope -> NOT FOUND

  // name-lookup for parameter varibale type "Nested"
  // will be done in Enclosing class scope -> FOUND

  // --------------------------------------------------

  Enclosing::Nested Enclosing::func(Nested x) {}
  // name-lookup for return type "Nested" 
  // will be done in Enclosing class scope -> FOUND

  // name-lookup for parameter varibale type "Nested"
  // will be done in Enclosing class scope -> FOUND

  // --------------------------------------------------
*/

/*
  class Enclosing {
    class Nested {
    public:
      int foo(int x) { return x + 5; }
      // non-static inline member function
     
      int func(int);  
      // member function declaration
    };

    int Nested::func(int x) { return x + 6; }
    // error: cannot define member function 
    // 'Enclosing::Nested::func' within 'Enclosing'

    // member type's member functions needs to define INLINE 
    // in member type's class scope, or in namespace scope.
  };

  int Enclosing::Nested::func(int x) { return x + 6; }
  // nested member function definition
*/

/*
  // enclosing.h
  // ----------------

  class Enclosing {
    class Nested {
    public:
      Nested& operator=(const Nested&); // copy assignment
    };
  };

  // enclosing.cpp
  // ----------------

  Enclosing::Nested& Enclosing::Nested::operator=(const Nested&)
  {
    return *this;
  }
*/

/*
            -------------------------------------------
            | Pimpl idiom (pointer to implementation) |
            -------------------------------------------
*/

/*
  class Myclass; 
  // forward declaration in global namespace scope
  // Myclass is an incomplete type

  class Enclosing {
    class Nested; // member type (Nested) forward declaration
    // Nested is an incomplete type
  };

  class Enclosing::Nested {};
*/

/*
  - Is it possible to make classes private section hidden
    for client code, if yes why would should we do that?
*/

/*
  // Myclass.h
  // ----------------

  // #include "AClass.h"

  class Myclass {
  private:
    AClass m_AClass; 
  };

  // every file that includes Myclass.h will also include AClass.h
  // and also include every header file that AClass.h includes...
  // this will increase compile time
*/

/*
  // myclass.h
  // ----------------

  // #include "AClass.h"
  // #include "BClass.h"
  // #include "CClass.h"
  
  class Myclass {
  private:
    AClass m_AClass;
    BClass m_BClass;
    CClass m_CClass;
  };

  // If we change member object's positions (i.e AClass and BClass),
  // we need to compile the project again.
  // will indicate `binary incompatibility`

  // If user code did not see the private section of Myclass,
  // there won't be any binary incompatibility issue.
*/

/*
                <---- check Pimpl_idiom.jpg ---->
*/

/*
  // myclass.h
  // ----------------

  class Myclass {
  public:
    Myclass(){}
    void foo();
  private:
    struct Pimpl; // forward declaration, `Pimpl` is an incomplete type
    Pimpl* mp_Pimpl;
  };

  // myclass.cpp
  // ----------------

  // #include "AClass.h"
  // #include "BClass.h"
  // #include "CClass.h"

  Myclass::Myclass() : mp_Pimpl(new Pimpl) {}

  struct Myclass::Pimpl {
    AClass m_AClass;
    BClass m_BClass;
    CClass m_CCLass;
  };

  void Myclass::foo()
  {
    mp_Pimpl->m_AClass.func();
    mp_Pimpl->m_BClass.bar();
    mp_Pimpl->m_CCLass.baz();
  }

  // because of myclass.cpp file includes header files
  // (AClass.h, BClass.h, CClass.h).
  // any header file that includes `myclass.h`
  // won't be include AClass.h, BClass.h, CClass.h

  // also no binary incompatibility issue will be occured
  // because member objects are now not in Myclass's interface.
*/

/*
            ------------------------------------------
            | modern Pimpl idiom using smart pointer |
            ------------------------------------------
*/

/*
  // myclass.h
  // ----------------

  #include<memory>  // std::unique_ptr

  class Myclass {
  public:
    Myclass() {}
    void foo();
  private:
    struct Pimpl;
    std::unique_ptr<Pimpl> m_Pimple;
  };

  // myclass.cpp
  // ----------------

  // #include "A.h"
  // #include "B.h"
  // #include "C.h"
*/

