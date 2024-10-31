#include <iostream>

/*
                          ===============
                          | Containment |
                          ===============
*/

/*
  class AClass {
  private:
    void foo();
    friend class BClass;  // friend declaration to a class
    // BClass can reach AClass's private section
  };

  class BClass {
  private:
    AClass m_Aclass;
  public:
    void func()
    {
      m_Aclass.foo(); // VALID
    }
  };

  class CClass {
  private:
    AClass m_Aclass;
  public:
    void func()
    {
      m_Aclass.foo(); // syntax error
      // error: 'void AClass::foo()' is private within this context
    }
  };
*/

/*
  class AClass {
  public:
    AClass()
    {
      std::cout << "AClass::AClass()\n";
    }
  };

  class BClass {
  private:
    AClass m_AClass;
  };

  int main()
  {
    BClass bx;  // default initialization
    // output -> AClass::AClass()

    // when we default initialize "bx" object, 
    // BClass's implicitly declared defaulted default ctor will be called.
    // BClass's constructor will call AClass's default ctor
    // for default initialize its member type variable m_AClass.
  }
*/

/*
  class AClass {
  public:
    AClass(int);
  };

  class BClass {
  public:
    // BClass() = delete; -> this is what happens.
  private:
    AClass m_AClass;
  };

  int main()
  {
    BClass bx;  // syntax error
    // error: use of deleted function 'BClass::BClass()'
    // error: no matching function for call to 'AClass::AClass()'

    // when we default initialize "bx" object, 
    // BClass's implicitly declared defaulted default ctor will be called.
    // Then BClass's constructor will call AClass's default ctor
    // to default initialize its member type variable m_AClass.
    // But AClass does not have a default ctor because  
    // AClass(int) ctor user declared.

    // so BClass's default ctor will try to call 
    // AClass's deleted default ctor which will cause an error.
    // Because there is an error happened in initialization 
    // compiler will implictly delete BClass's default ctor. 

    // default initialization of "bx" object will 
    // become a call to BClass's deleted default ctor. 
    // which will cause a syntax error.
  }
*/

/*
  class AClass {
  private:
    AClass();
  };

  class BClass {
  private:
    AClass m_AClass;
  public:
    // BClass() = delete; -> this is what happens.
  };

  int main()
  {
    BClass bx;  // syntax error
    // error: use of deleted function 'BClass::BClass()'
    // error: 'AClass::AClass()' is private within this context

    // when we default initialize "bx" object,
    // BClass's implicitly declared defaulted default ctor will be called.
    // Then BClass's constructor will call AClass's default ctor
    // to default initialize its member type variable m_AClass.
    // But AClass's default ctor is private section 
    // so inside BClass's constructor, 
    // AClass's default ctor is not reachable it will cause error.
    // so compiler will implicitly delete BClass's default ctor.
  }
*/

/*
  class AClass {
  public:
    AClass(int x)
    {
      std::cout << "AClass(int x) x = " << x << '\n';
    }
  };

  class BClass {
  private:
    AClass m_AClass;
  public:
    BClass() {}   // syntax error
    // error: no matching function for call to 'AClass::AClass()'

    // BClass's default ctor is user declared defined
    // so compiler can not implicitly delete it.
    // but constructor needs to call AClass's default ctor
    // to default initialize its member type variable m_AClass.
    // but AClass does not have a default ctor because
    // AClass(int) ctor user declared.
    // so BClass's default ctor will be a syntax error.
  };
*/

/*
  class AClass {
  public:
    AClass(int x)
    {
      std::cout << "AClass(int x) is called,  x = " << x << '\n';
    }
  };

  class BClass {
  private:
    AClass m_AClass;
  public:
    BClass() : m_AClass(11) {} 
    // constructor initializer list
  };

  int main()
  {
    BClass bx;  // VALID
    // output -> AClass(int x) is called,  x = 11
  }
*/

/*
  class Member {
  public:
    void public_member_func();
  private:
    void private_member_func();
  };

  class Owner {
  private:
    Member m_member;
  public:
    void f1()
    {
      m_member.public_member_func(); // VALID
      // reaching member type object's public section is VALID.

      m_member.private_member_func(); // syntax error
      // error: 'void Member::private_member_func()' 
      // is private within this context

      // reaching member type object's private section is INVALID.
    }
  };
*/

/*
  class Member; // forward declaration
  // Member is an incomplete type.

  class Owner {
  public:
  private:
    // ------------------------------------------------

    Member m_member;  // syntax error
    // error: field 'm_member' has incomplete type 'Member'

    // compiler needs to know the size Owner class
    // but it can not know the size of Member class
    // because Member is an incomplete type.

    // ------------------------------------------------

    Member* mp_member;  // VALID

    // pointer's size is known by the compiler
    // even the member type itself is an incomplete type

    // ------------------------------------------------

    Member& mr_member;  // VALID

    // reference's size(same as pointers) is known by the compiler
    // even the member type itself is an incomplete type

    // ------------------------------------------------
  };
*/

/*
  class AClass {
  public:
    AClass(int, int, int)
    {
      std::cout << "AClass(int, int, int) ctor\n";
    }
  };

  class BClass {
  private:
    // ------------------------------------------------

    AClass m_AClass1 = { 1, 2, 3 };  // VALID
    // copy list initialization

    // ------------------------------------------------

    AClass m_AClass2{ 4, 5, 6 };      // VALID
    // direct list initialization

    // ------------------------------------------------

    AClass m_AClass3(7, 8, 9);        // syntax error
    // error: expected identifier before numeric constant
    // member function declaration syntax

    // ------------------------------------------------

    AClass m_AClass4 = (10, 11, 12);  // syntax error
    // error: could not convert '((void)0, 12)' from 'int' to 'AClass'

    // "(10, 11, 12)" expression is evaluated as 12
    // comma operators rightmost operand is the value generated 
    // by the expression

    // ------------------------------------------------
  };
*/


/*
            -------------------------------------------
            | special member function's incomposition |
            -------------------------------------------
*/

/*
  #include <utility>  // std::move

  class AClass {};
  class BClass {};
  class CClass {};

  class Myclass {
  private:
    AClass m_AClass;  // member type
    BClass m_BClass;  // member type
    CClass m_CClass;  // member type
  public:
    // default constructor
    Myclass() : m_AClass(), m_BClass(), m_CClass() {}

    // copy constructor
    Myclass(const Myclass& other) :
                    m_AClass(other.m_AClass), 
                    m_BClass(other.m_BClass), 
                    m_CClass(other.m_CClass)  {}

    // copy assignment
    Myclass& operator=(const Myclass& other)
    {
      m_AClass = other.m_AClass;
      m_BClass = other.m_BClass;
      m_CClass = other.m_CClass;
      return *this;
    }

    // move constructor
    Myclass(Myclass&& other) : 
              m_AClass(std::move(other.m_AClass)), 
              m_BClass(std::move(other.m_BClass)),
              m_CClass(std::move(other.m_CClass)) {}

    // move assignment
    Myclass& operator=(Myclass&& other)
    {
      m_AClass = std::move(other.m_AClass);
      m_BClass = std::move(other.m_BClass);
      m_CClass = std::move(other.m_CClass);
      return *this;
    }
  };
*/

/*
  class AClass {
  public:
    AClass()
    {
      std::cout << "AClass::AClass() default ctor\n";
    }
    AClass(const AClass&)
    {
      std::cout << "AClass::AClass(const AClass&) copy constructor\n";
    }
    // because of copy constructor is user declared
    // move members are not declared
  };

  class BClass {
  private:
    int m_ival;
    AClass m_AClass;
  public:
    // user declared defaulted default ctor
    BClass() = default;

    // user declared copy constructor
    BClass(const BClass& other) : m_ival(other.m_ival) {}
    // m_AClass member type is not initialized 
    // in constructor initializer list
    // so to initialize m_AClass member type 
    // AClass's default ctor will be called.
  };

  int main()
  {
    BClass b1;
    BClass b2 = b1;
    // output ->
    //  AClass::AClass() default ctor
    //  AClass::AClass() default ctor ------->
  }
*/

/*
  class AClass {
  public:
    AClass()
    {
      std::cout << "AClass::AClass() default ctor\n";
    }
    AClass(const AClass&)
    {
      std::cout << "AClass::AClass(const AClass&) copy constructor\n";
    }
    // because of copy constructor is user declared
    // move members are not declared
  };

  class BClass {
  private:
    int m_ival;
    AClass m_AClass;
  public:
    // user declared defaulted default ctor
    BClass() = default;

    // user declared copy constructor
    BClass(const BClass& other) : 
                  m_ival(other.m_ival), 
                  m_AClass(other.m_AClass) {}
  };

  int main()
  {
    BClass b1;
    BClass b2 = b1;
    // output ->
    //  AClass::AClass() default ctor
    //  AClass::AClass(const AClass&) copy constructor ------->
  }
*/