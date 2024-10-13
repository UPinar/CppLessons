#include <iostream>

/*
                      =======================
                      | friend declarations |
                      =======================
*/

/*
  - If we want client code to reach classes private members
    we can define those members in public section and 
    make them public members.
  - `friend` declaration is not for client codes.

  Question: What is in classes public interface ?
    - public members of the class 
    - global members declared in .h(header) file.
*/

/*
  #include <string>

  int main()
  {
    std::cout << std::boolalpha;

    std::string str{ "Hello World" };
    str += "!";

    bool x;
    if (str == "Hello World")
      x = true;
    else
      x = false;

    std::cout << x << '\n';   // output -> false

    auto y = std::operator==(str, "Hello World");
    auto z = (str == "Hello World");
    // Those 2 lines are the equivalent.

    std::cout << y << '\n';  // output -> false
    std::cout << z << '\n';  // output -> false

    // global functions can not reach classes private members.
    // std::operator==(std::string, const char*) is a global function.
    // string that std::string class holds is a private data member.
    // to do this comparison(==) std::operator==() function 
    // needs to reach private data member of std::string class
    // friend declaration is the solution.
  }
*/

/*
  A class can give friend declaration to
    -> a free(global) function
    -> another classes specific member function
    -> all functions of another class(another class)
*/

/*
  // friend declaration to a global function

  class AClass {
  private:
    int m_x;
    void func();    // private member function
  };

  class BClass {
  public:
    friend void gf_2(BClass&);  
    // friend declaration to a global function
    // inside BClass's public

  private:
    int m_x;
    void func();    // private member function
  };

  void gf_1(AClass& a_ref)
  {
    AClass a;
    AClass* p_a{ &a };

    a_ref.m_x = 10; // syntax error
    // error: 'int AClass::m_x' is private within this context

    a.func();
    // error: 'void AClass::func()' is private within this context
    p_a->func();
    // error: 'void AClass::func()' is private within this context

    // access control phase error.
    // global "gf_1" function can not reach AClass's private section.
  }

  void gf_2(BClass& b_ref)
  {
    BClass b;
    BClass* p_b{ &b };

    b_ref.m_x = 20;   // VALID
    b.func();         // VALID
    p_b->func();      // VALID

    // global "gf_2" function can reach BClass's private section.
    // because of BClass gave a friend decleration to gf_2 function.
  }
*/

/*
  // There is no difference giving a friend declaration 
  // to a global function in classses
  // public, protected or private sections.

  void g_f1()
  {
    Myclass m;
    m.m_x = 11;   // VALID
    // global "g_f1" function can reach Myclass's private section.
  }

  void g_f2()
  {
    Myclass m;
    m.m_x = 22;   // VALID
    // global "g_f2" function can reach Myclass's private section.
  }

  void g_f3()
  {
    Myclass m;
    m.m_x = 33;   // VALID
    // global "g_f3" function can reach Myclass's private section.
  }

  class Myclass {
  public:
    friend void g_f1(); 
    // friend decleration to a global "g_f1" function in public section
  protected:
    friend void g_f2();
    // friend decleration to a global "g_f2" function in protected section
  private:
    int m_x;
    friend void g_f3();
    // friend decleration to a global "g_f3" function in private section
  };
*/

/*
  class Myclass {
  public:
    friend void g_f(Myclass& m_ref)   // hidden friend function
    {
      Myclass m;
      Myclass* p_m{ &m };

      m_ref.m_x = 10;
      m.func();
      p_m->func();
    }

    // "g_f" is called a hidden friend function
    // "g_f" is defined inside Myclass's class scope.
    // "g_f" is not a member function it is a global function
    // "g_f" is defined in class scope, it is now an inline function
  private:
    int m_x;
    void func();
  };

  int main()
  {
    Myclass m1;
    Myclass m2;
    // --------------------------------------------

    g_f(m1);  // VALID
    // "g_f" is a global function

    // --------------------------------------------

    m2.g_f(m1); // syntax error
    // error: 'class Myclass' has no member named 'g_f'

    // --------------------------------------------
  }
*/

/*
  // friend declaration to another classes specific member function

  class AClass {
  public:
    void foo(int);
    void bar(int);
  };

  class BClass {
  private:
    friend void AClass::foo(int);
    // BClass gave friend declaration to 
    // AClass's "foo(int)" function.
    // AClass::foo(int) function can reach BClass's private section

    void func();
    int m_x;
  };

  void AClass::foo(int x)
  {
    BClass b;

    b.func();   // VALID
    b.m_x = 12; // VALID
    // AClass::foo(int) function can reach BClass's private section
  }
  
  void AClass::bar(int x)
  {
    BClass b;

    b.func();   // syntax error
    // error: 'void BClass::func()' is private within this context

    b.m_x = 12; // syntax error
    // error: 'int BClass::m_x' is private within this context
  }
*/

/*
  // a class can not give a friend declaration 
  // to an incomplete type's member function.

  class AClass; // forward declaration
  // AClass is an incomplete type.

  class BClass {
  private:
    friend void AClass::foo(int); // syntax error
    // error: invalid use of incomplete type 'class AClass'

    void func();
  };
*/

/*
  class BClass; // forward declaration
  // BClass is an incomplete type

  class AClass {
  public:
  private:
    friend class BClass;  // VALID
    // AClass gave friend declaration to BClass(incomplete type)

    int m_x;
    void foo();
  };

  int main(){}
*/

/*
  // friend declaration to all functions of another class(another class)

  class AClass {
  public:
  private:
    friend class BClass;  
    // AClass gave friend declaration to BClass

    int m_x;
    void foo();
  };

  // -------> (1)
  // in line (1), BClass is still an incomplete type.


  // BClass is defined, not an incomplete type anymore.
  class BClass {
  public:
    void f1(AClass a)
    {
      a.m_x = 345;  // VALID
    }
    void f2()
    {
      AClass a;
      a.foo();      // VALID
    }
  };
  // because of AClass gave a friend declaration to BClass
  // BClass's member functions can reach AClass's private section
*/

/*
  - AClass gave a friend declaration to BClass
    -> BClass CAN reach AClass's private section
    -> AClass CAN NOT reach BClass's private section.

  - AClass gave a friend declaration to BClass
    BClass gave a friend declaration to CClass
    -> BClass CAN reach AClass's private section
    -> CClass CAN reach BClass's private section
    -> CClass CAN NOT reach AClass's private section

  - APClass(AClass's parent class) gave a friend declaration to BClass
    -> CClass CAN reach APClass's private section
    -> CClass CAN NOT reach AClass's private section
*/  

/*
  class AClass {
  private:
    friend class BClass;  
    // AClass gave friend declartion to BClass
    void a_foo();
  };

  class BClass {
  private:
    friend class CClass;
    // BClass gave friend declartion to CClass

    void b_foo()
    {
      AClass a;
      a.a_foo(); 
      // BClass can reach AClass's private section.
    }
  };

  class CClass {
  private:
    void c_foo()
    {
      AClass a;
      a.a_foo();  // syntax error
      // error: 'void AClass::a_foo()' is private within this context

      BClass b;
      b.b_foo(); // VALID

      // CClass CAN reach private section of BClass
      // CClass CAN NOT reach private section of AClass
    }
  };
*/

/*
  class APClass {
  private:
    friend class BClass;  
    // APClass gave a friend declaration to BClass

    void ap_foo();
  };

  class AClass : public APClass {
  private:
    void a_foo();
  };

  // AClass is derived(türemiş) class 
  // APClass is base(taban) class

  class BClass {
  private:
    void b_foo()
    {
      APClass ap;
      ap.ap_foo();  // VALID

      AClass a;
      a.a_foo();    // syntax error
      // error: 'void AClass::a_foo()' is private within this context

      // BClass CAN reach private section of APClass
      // BClass CAN NOT reach private section of AClass
    }
  };
*/

/*
  class AClass {
  private:
    void f1();
      void f2();  ---->
    void f3();
      void f4();  ---->
  };

  when AClass gave friend declaration to another function
  or another class's all functions, they can reach all of 
  AClass's private section.

  What if we want them to reach only 
  a part of AClass's private section ?

  i.e friend declared class can reach only f2() and f4(),
    but can not reach f1() and f3()

  --> Attorney - Client idiom 
  check this blog post for more information

  https://necatiergin2019.medium.com/
  avukat-m%C3%BCvekkil-i%CC%87diyomu-attorney-client-idiom-2f88f81e4873
*/