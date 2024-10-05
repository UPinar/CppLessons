#include <iostream>

/*
                  ============================
                  | Special Member Functions |
                  ============================
*/

/*
  class Myclass {
    Myclass();                            // default constructor
    ~Myclass();                           // destructor

    Myclass(const Myclass&);              // copy ctor
    Myclass(Myclass&&);                   // move ctor

    Myclass& operator=(const Myclass&);   // copy assignment
    Myclass& operator=(Myclass&&);        // move assignment
  };
*/

/*
  class Myclass {
  public:
    Myclass()
    {
      std::cout << "default ctor, this = " << this << '\n';
    }

    ~Myclass()
    {
      std::cout << "destructor, this   = " << this << '\n';
    }

    Myclass(const Myclass&)
    {
      std::cout << "copy ctor, this    = " << this << '\n';
    }
  };

  int main()
  {
    Myclass m1;         // defult ctor will be called.

    Myclass m2(m1);     // copy ctor will be called.
    Myclass m3{ m1 };   // copy ctor will be called.
    Myclass m4 = m1;    // copy ctor will be called.
    auto m5 = m1;       // copy ctor will be called.

    // output ->
    //  default ctor, this = 0x93ecdffa9f
    //  copy ctor, this    = 0x93ecdffa9e
    //  copy ctor, this    = 0x93ecdffa9d
    //  copy ctor, this    = 0x93ecdffa9c
    //  copy ctor, this    = 0x93ecdffa9b
    //  destructor, this   = 0x93ecdffa9b
    //  destructor, this   = 0x93ecdffa9c
    //  destructor, this   = 0x93ecdffa9d
    //  destructor, this   = 0x93ecdffa9e
    //  destructor, this   = 0x93ecdffa9f
  }
*/

/*
  class Myclass {
  public:
    Myclass()
    {
      std::cout << "default ctor this = " << this << '\n';
    }

    ~Myclass()
    {
      std::cout << "destructor this   = " << this << '\n';
    }

    Myclass(const Myclass&)
    {
      std::cout << "copy ctor this    = " << this << '\n';
    }
  };

  void foo(Myclass param)   // call by value
  {
    std::cout << "inside foo()..\n";
  }

  int main()
  {
    Myclass m1;     // defult ctor will be called.
    foo(m1);        // copy ctor will be called.

    std::cout << "inside main()..\n";

    // output ->
    //  default ctor this = 0xd9225ff9ee
    //  copy ctor this    = 0xd9225ff9ef
    //  inside foo()..
    //  destructor this   = 0xd9225ff9ef
    //  inside main()..
    //  destructor this   = 0xd9225ff9ee
  }
*/

/*
  Implicitly declared special member functions are,
    -> non-static
    -> public
    -> inline
*/

/*
            ------------------------------------
            | implicitly declared default ctor |
            ------------------------------------
*/

/*
  // Implicitly declared default ctor  
  // will default initialize all data members

  class Myclass {
  public:
    void print() const
    {
      std::cout << "m_a = " << m_a << "\n";
      std::cout << "m_b = " << m_b << "\n";
      std::cout << "m_c = " << m_c << "\n";
    }

  private:
    int m_a, m_b, m_c;
  };

  int main()
  {
    Myclass mx;	
    // implicitly declared default ctor will be called.

    mx.print();	
    // m_a, m_b and m_c will have garbage(indetermined) value.
    // undefined behaviour(ub)
  }
*/

/*
  class ClassA {
  public:
    ClassA()
    {
      std::cout << "default ctor ClassA() is called\n";
    }
  };

  class Myclass {
  private:
    ClassA m_a;
  };

  int main()
  {
    Myclass mx;
    // 1. Myclass's implicitly declared default ctor will be called
    // 2. Myclass's default ctor will default initialize 
    //    its data member "m_a"
    // 3. to default initialize "m_a", 
    //    ClassA's default ctor will be called.

    // output -> default ctor ClassA() is called
  }
*/

/*
  class Myclass {
  private:
    const int m_cx;
  };

  int main()
  {
    Myclass mx; // syntax error
    // error: use of deleted function 'Myclass::Myclass()'
    // error: uninitialized const member in 'class Myclass'
  }

  // 1. Myclass's implicitly declared default ctor will be called.
  // 2. Myclass's default ctor will try to default initialize 
  //  its const data member "m_cx"
  // 3. because of const variables can not be default initialized,
  //  Myclass's default ctor will throw an error.
  // 4. because of Myclass's default ctor is throwing error,
  //  it will be deleted by the compiler. (implictly declared deleted)
  //  `Myclass() = delete;`
*/

/*
  class Myclass {
  private:
    const int m_cx;
  };

  // compiling this code will not create any syntax error.
  // because of Myclass's default ctor is not called,
  // this code will not create any syntax error.
*/

/*
  class Myclass {
  private:
    int& m_r;
  };

  int main()
  {
    Myclass m;  // syntax error
    // error: use of deleted function 'Myclass::Myclass()'
    // error: uninitialized reference member in 'class Myclass'
  }

  // 1. Myclass's implicitly declared default ctor will be called.
  // 2. Myclass's default ctor will try to default initialize
  //  its reference data member "m_r"
  // 3. because of references can not be default initialized,
  //  Myclass's default ctor will throw an error.
  // 4. because of Myclass's default ctor is throwing error,
  //  it will be deleted by the compiler. (implictly declared deleted)
  //  `Myclass() = delete;`
*/

/*
  class ClassA {
  private:
    ClassA();
  };

  class Myclass {
  private:
    ClassA m_a;
  };

  int main()
  {
    Myclass mx; // syntax error
    // error: use of deleted function 'Myclass::Myclass()'
    // error: 'ClassA::ClassA()' is private within this context
  }

  // 1. Myclass's implicitly declared default ctor will be called.
  // 2. Myclass's default ctor will default initialize m_a data member.
  // 3. For m_a data member to initialize, 
  //  its default ctor ClassA() have to be called.
  // 4. ClassA's default ctor is in private section.
  //  Myclass's default ctor can not reach to ClassA's default ctor.
  // 5. That will create a syntax error.
  // 6. Compiler will delete Myclass()'s default ctor.
  //  `Myclass() = delete;`
*/

/*
  class ClassA {
  public:
    ClassA(int);
  };

  class Myclass {
  private:
    ClassA m_a;
  };

  int main()
  {
    Myclass mx; // syntax error
    // error: use of deleted function 'Myclass::Myclass()'
    // error: no matching function for call to 'ClassA::ClassA()'
  }

  // 1. Myclass's implicitly declared default ctor will be called.
  // 2. Myclass's default ctor will default initialize m_a data member.
  // 3. For m_a data member to initialize,
  //  its default ctor ClassA() have to be called.
  // 4. because of there is user declared ctor `ClassA(int)`,
  //  ClassA's default ctor is not declared by the compiler.
  // 5. That will create a syntax error.
  // 6. Compiler will delete Myclass()'s default ctor.
  //  `Myclass() = delete;`
*/

/*
            ----------------------------------------------
            | constructor(member) initializer list (MIL) |
            ----------------------------------------------
*/

/*
  class Myclass {
  public:
    Myclass()
    {
      // -----> "m_x" and "m_y" data members are already alive.

      m_x = 10; // this is not initialization, this is an assignment
      m_y = 20; // this is not initialization, this is an assignment
    }
  private:
    int m_x, m_y;
  };

  // const data members and reference data members 
  // can not be default initialized.
  // Using constructor initializer list is the way to initialize them.
*/

/*
  class Myclass {
  public:
    Myclass() : m_x(10), m_y(20)  // this is initialization
    {
      // initialization of const data members 
      // in constructor initializer list.
    }
  private:
    const int m_x, m_y;   // const data members
  };
*/

/*
  class ClassB {
  public:
    ClassB(int);
  };

  class ClassA {
  public:
    ClassA(){}    // user declared default ctor
    // syntax error
    // error: no matching function for call to 'ClassB::ClassB()'
  private:
    ClassB m_b;
  };

  int main()
  {
    ClassA ax;
  }

  // ax object will be default initialized.
  // ClassA's default ctor will be called
  // ClassA's default ctor will default initialize m_b data member.
  // For m_b data member to initialize, 
  // its default ctor ClassB() have to be called.
  // Because of there is user declared ctor `ClassB(int)`,
  // ClassB's default ctor is not declared by the compiler.
  // That will create a syntax error.
  // because of ClassA's default ctor is user declared
*/

/*
  class ClassA{
  public:
    ClassA(int x, int y) : m_a(x), m_b(y) {}
    // narrowing conversion is VALID
  private:
    int m_a, m_b;
  };

  class ClassB{
  public:
    ClassB(int x, int y) : m_a{ x }, m_b{ y } {}
    // narrowing conversion is NOT VALID.
  private:
    int m_a, m_b;
  };
*/

/*
  class Myclass {
  public:
    Myclass(int a, int b) : m_b{ a + b }, m_a{ m_b / 5 } {}
    // undefined behaviour(ub)
  private:
    int m_a, m_b;  // declaration order
  };

  // data member's declaration order will be the order
  // in their construction. (first m_a, second m_b)

  // in m_a data member's initialization, m_b data member
  // is not initialized yet, it has garbage value.
  // but in this scenario(in the constructor initializer list),
  // in m_a data member's initialization, m_b data member
  // is being used, and using m_b will be undefined behaviour.
  // because it has not been initialized yet and have garbage value.
*/


/*
  class Myclass {
  public:
    Myclass(int x) : m_a{} // value initialize
    {}	
  private:
    int m_a;
  };
*/

/*
  #include <string>

  class Person_1{
  public:
    Person_1(const char* p_name, const char* p_surname)
    {
      m_name = p_name;
      m_surname = p_surname;

      // m_name and m_surname data members will be default initialized.
      // `std::string` class's default ctor will be called.
      // Then we use their assignment functions to assign 
      // p_name and p_surname to them.
    }

  private:
    std::string m_name;
    std::string m_surname;
  };

  class Person_2{
  public:
    Person_2(const char* p_name, const char* p_surname) 
          : m_name{ p_name }, m_surname{ p_surname }
    {
      // directly std::string class's `std::string(const char*)` 
      // `const char*` parameter ctor will be called, and 
      // there won't be any assignment operation.
      // using constructor initializer list is more efficient.
    }
  private:
    std::string m_name;
    std::string m_surname;
  };
*/

/*
            
  Implicitly declared defaulted copy ctor 
  -> public,
  -> non-static
  -> inline member function
*/

/*
  class Myclass {};

  void foo(Myclass);    // copy ctor (call by value function call)

  int main()
  {
    Myclass m1;         // default ctor
    Myclass m2 = m1;    // copy ctor
    Myclass m3(m1);     // copy ctor
    Myclass m4{ m1 };   // copy ctor
    auto m5 = m1;       // copy ctor
    auto m6(m1);        // copy ctor
    auto m7{ m1 };      // copy ctor

    Myclass m;          // default ctor
    foo(m);             // copy ctor 
  }
*/

/*
  class Myclass {};

  Myclass g_x;

  Myclass foo()
  {
    return g_x;
  }

  int main()
  {
    Myclass mx = foo();   
    // copy ctor will be called for local variable mx
  }
*/

/*
  class T1{};
  class T2{};
  class T3{};

  class Myclass {
  public:
    Myclass(const Myclass& other) 
            : m_1(other.m_1), m_2(other.m_2), m_3(other.m_3) {}
    // This is how compiler generate 
    // implicitly declared defaulted copy ctor.
  private:
    T1 m_1;
    T2 m_2;
    T3 m_3;
  };

  // - if T1, T2 and T3 are primitive types, 
  //    data members will be copied.
  // - if T1, T2 and T3 are pointer types,
  //    data members will be copied.
  // - if T1, T2 and T3 are classes,
  //    their copy constructors will be called.
*/

/*
  class Date {
  public:
    Date(int day, int mon, int year) 
            : m_day{ day }, m_mon{ mon }, m_year{ year } {}

    // copy constructor
    Date(const Date& other) 
      : m_day(other.m_day), m_mon(other.m_mon), m_year(other.m_mon)
    {
      std::cout << "this   = " << this << '\n';
      // this pointer's value is the address of the object 
      // will be created by the copy constructor.

      std::cout << "&other = " << &other << '\n';
      // object that will bind to Date&(other) 
      // is the object that its data members will be copied from.
    }
  private:
    int m_day;
    int m_mon;
    int m_year;
  };

  int main()
  {
    Date dx{ 10,2,2023 };

    Date dy{ dx };
    std::cout << "Address of dx(object that will used for copying) = " 
              << &dx << '\n';
    std::cout << "Address of dy(object that copy ctor create)      = " 
              << &dy << '\n';
  }

  // output ->
  //  this   = 0x52675ff908
  //  &other = 0x52675ff914
  //  Address of dx(object that will used for copying) = 0x52675ff914
  //  Address of dy(object that copy ctor create)      = 0x52675ff908
*/

/*
          ---------------------------------------------
          | deep and shallow copy in copy constructor |
          ---------------------------------------------
*/

/*
  #include <cstring>
  #include <cstdlib>

  class String {
  public:
    String(const char* p) : 
        m_len{ std::strlen(p) }, 
        m_p{ static_cast<char*>(std::malloc(m_len + 1)) }
    {
      std::strcpy(m_p, p);
    }

    ~String()
    {
      std::free(m_p);
    }

    void print()const
    {
      std::cout << m_p << '\n';
    }

    std::size_t length()const
    {
      return m_len;
    }

    bool empty()const
    {
      return m_len == 0;
    }

  private:
    std::size_t m_len;
    char* m_p;
  };

  void func(String copied_str)
  {
    copied_str.print();
  }

  int main()
  {
    String local_str{ "Hello World" };
    local_str.print();  // output -> Hello World

    func(local_str);    // output -> Hello World
    // copy ctor will be called to create function parameter variable.
    // its copy constructor will copy the data members of str object.
    // so both objects "m_p" data members will point to 
    // the same address in heap.
    // copy constructor is done Shallow Copy.

    // At the end of the "func" function's scope 
    // "copied_str" variable's destructor will be called.
    // its destructor will delete the memory that "m_p" points to.

    local_str.print(); // undefined behaviour(ub)
    // "local_str" objects "m_p" data member is being used 
    // when its "print" mamber function is called.

    // after "func" functions execution,
    // because of both object's(local str and copied_str) 
    // "m_p" data members are pointing to the same address in heap.
    // after "copied_str" object's destructor will free'd the memory.
    // "local_str" object's "m_p" data member become a dangling pointer.
    // address that "local_str" objects "m_p" data member points to
    // might already been used for any other purpose.
    // so using the value that "local_str" objects "m_p" data member 
    // is pointing to is undefined behaviour(UB).
  }
*/

/*
  #include <cstring>
  #include <cstdlib>

  class String {
  public:
    String(const char* p) : 
        m_len{ std::strlen(p) }, 
        m_p{ static_cast<char*>(std::malloc(m_len + 1)) }
    {
      std::strcpy(m_p, p);
    }

    // Copy constructor that does Deep Copy
    String(const String& other) : 
        m_len(other.m_len), 
        m_p{ static_cast<char*>(std::malloc(m_len + 1)) }
    {
      std::strcpy(m_p, other.m_p);
      // allocating new memory in heap for copy constructed object.
      // copying the data that other object's 
      // "m_p" data member points to.
    }

    ~String()
    {
      std::free(m_p);
    }

    void print()const
    {
      std::cout << m_p << '\n';
    }

    std::size_t length()const
    {
      return m_len;
    }

    bool empty()const
    {
      return m_len == 0;
    }

  private:
    std::size_t m_len;
    char* m_p;
  };

  void func(String copiedStr)
  {
    copiedStr.print();
  }

  int main()
  {
    String str{ "Hello World" };

    str.print();  // output -> Hello World
    func(str);	  // output -> Hello World
    str.print();  // output -> Hello World
  }
*/

/*
              --------------------------------------------
              | deep and shallow copy in copy assignment |
              --------------------------------------------
*/

/*
  class T1 {};
  class T2 {};
  class T3 {};

  class Myclass
  {
    Myclass(const Myclass& other) : 
      m_1(other.m_1), m_2(other.m_2), m_3(other.m_3) {}


    // copy assignment operator function
    Myclass& operator=(const Myclass& other)
    {
      // x = y
      // x.operator=(y)
      // this pointer points to "x" object's address
      // other is "y" object

      m_1 = other.m_1;
      m_2 = other.m_2;
      m_3 = other.m_3;

      return *this;
      // "*this" is an LValue expression
      // returning "*this" is returning the assigned object itself.
    }

  private:
    T1 m_1;
    T2 m_2;
    T3 m_3;
  };

  // if T1, T2 and T3 are primitive types, 
  //  it will copy the data members.

  // if T1, T2 and T3 are pointer types,
  //  it will copy the data members.

  // if T1, T2 and T3 are classes,
  //  their copy assignment operators will be called.
*/

/*
  class Date {
  public:
    Date(int day, int mon, int year) : 
        m_day{ day }, m_mon{ mon }, m_year{ year } {}

    // copy assignment operator function
    Date& operator=(const Date& other)
    {
      m_day = other.m_day;
      m_mon = other.m_mon;
      m_year = other.m_year;

      return *this;
    }

    void print() const
    {
      std::cout << m_day << '-' << m_mon << '-' << m_year << '\n';
    }

  private:
    int m_day;
    int m_mon;
    int m_year;
  };

  int main()
  {
    Date dx{ 10, 2, 2023 };
    Date dy{ 5, 5, 1955 };

    dx.print(); // output -> 10-2-2023
    dy.print(); // output -> 5-5-1955

    dx = dy;
    dx.operator=(dy);
    // Those 2 lines are equivalent.

    // ----------------------------------------------------------

    // because of copy assignment operator function 
    // returns an L value(dx object itself (*this))
    // chaining it with other member functions is possible.

    dx = dy;    // returns dx object itself(L value)
    dx.print(); 
    // AND
    (dx = dy).print();  // chaining 

    // ----------------------------------------------------------
  }
*/

/*
  #include <cstring>
  #include <cstdlib>

  class String {
  public:
    String(const char* p) : 
        m_len{ std::strlen(p) }, 
        m_p{ static_cast<char*>(std::malloc(m_len + 1)) }
    {
      std::strcpy(m_p, p);
    }

    // copy constructor that does Deep Copy
    String(const String& other) : 
        m_len(other.m_len), 
        m_p{ static_cast<char*>(std::malloc(m_len + 1)) }
    {
      std::strcpy(m_p, other.m_p);
    } 

    // copy assignment operator function that does Deep Copy
    String& operator=(const String& other)
    {
      // to prevent unnecessary self assignment
      if(this == &other)
        return *this;

      // str.operator=(str);
      // str = str;
      // if copy assingment operator function called for same object
      // (object assigned to itself), it will be unnecessary.

      m_len = other.m_len;

      // m_p = other.m_p; 
      // implicitly declared copy assingment operator function does
      // this will be a shallow copy.

      // ----------------------------------------------------------

      // deep copy

      std::free(m_p);
      // first we need to free the memory that 
      // our data member pointer points to.
      // we don't know how much storage it has. 

      m_p = static_cast<char*>(std::malloc(m_len + 1));
      // then we need to allocate new memory in heap 
      // that have the same size of other.m_len + 1.
      // "+ 1" is for null character('\0')

      std::strcpy(m_p, other.m_p);
      // copying the data that other object's "m_p" 
      // data member points to.

      // ----------------------------------------------------------

      return *this;
    }
    ~String()
    {
      std::free(m_p);
    }

    void print()const
    {
      std::cout << m_p << '\n';
    }

  private:
    std::size_t m_len;
    char* m_p;
  };

  int main()
  {
    String s1{ "Hello World!" };
    s1.print();     // output -> Hello World!

    if(true)
    {
      String s2{ "Hello Galaxy" };  
      s2.print();   // output -> Hello Galaxy
      s2 = s1;      // copy assignment will be called.
      s2.print();   // output -> Hello World!
    }

    s1.print();    // output -> Hello World!
  }
*/

/*
  class Myclass {};

  void func(const Myclass&)
  {
    std::cout << "func(const Myclass&)\n";
  }

  void func(Myclass&&)
  {
    std::cout << "func(Myclass&&)\n";
  }

  int main()
  {
    Myclass m;

    func(m);  
    // "m" is an LValue expression
    // output -> func(const Myclass&)

    func(Myclass{});                  // output -> func(Myclass&&)
    // "Myclass{}" is PRValue expression  (RValue)
    

    func(static_cast<Myclass&&>(m));  // output -> func(Myclass&&) 	
    // "static_cast<Myclass&&>(m)" is XValue expression (RValue)
    

    func(std::move(m));               // output -> func(Myclass&&)			
    // "std::move(m)" is XValue expression (RValue)
    

    func(std::move(Myclass{}));       // output -> func(Myclass&&)
    // "std::move(Myclass{})" is PRValue expression (RValue)
    
    // std::move(LValue expression) goes out as an R value
    // std::move(Rvalue expression) goes out as an R value
  }
*/

/*
  #include <string>

  std::string foo();

  int main()
  {
    std::string s1;

    s1 = foo();	
    // "foo()" is an RValue expression
    // move assignment will be called
  }
*/

/*
  void func(const int&)
  {
    std::cout << "const LVALUE REF\n";
  }

  void func(int&&)
  {
    std::cout << "RVALUE REF\n";
  }

  int main()
  {
    int&& r = 10;
    func(r);            // output -> const LVALUE REF
    // "r" is an LValue expression

    func(std::move(r)); // output -> RVALUE REF
    // "std::move(r)" is an XValue expression (RValue)
  }
*/

/*
                        ----------------
                        | move members |
                        ----------------
*/

/*
  class T1{};
  class T2{};
  class T3{};

  class Myclass {
  public:
    // implicitly declared move constructor generated by the compiler.
    Myclass(Myclass&& other) :
        m_1(std::move(other.m_1)),
        m_2(std::move(other.m_2)),
        m_3(std::move(other.m_3))
    {}

    // implicitly declared move assignment generated by the compiler. 
    Myclass& operator=(Myclass&& other)
    {
      m_1 = std::move(other.m_1);
      m_2 = std::move(other.m_2);
      m_3 = std::move(other.m_3);
      return *this;
    }
  private:
    T1 m_1;
    T2 m_2;
    T3 m_3;
  };

  // If T1, T2, T3 are classes their 
  // move assignment or move ctor will be called too.
*/

/*
  #include <cstring>
  #include <cstdlib>

  class String {
  public:
    String(const char* p) : 
        m_len{ std::strlen(p) }, 
        m_p{ static_cast<char*>(std::malloc(m_len + 1)) }
    {
      std::strcpy(m_p, p);
    }

    // move constructor
    String(String&& other) : 
        m_len(other.m_len), 
        m_p(other.m_p)
    {
      // after constructor initializer list executed,
      // "*this" objects data member pointer "m_p"
      // is pointing the same address of "other->m_p" points to.
      // basically "other" object's "m_p" data member 
      // is copied to "*this" object's "m_p" data member.

      // In this situation when "other" objects lifetime ends,
      // its destructor will be called and its data member pointer
      // will be free'd. So "*this" object's "m_p" data member
      // will become a dangling pointer.

      other.m_len = 0;
      other.m_p = nullptr;
      // to prevent "*this" object's "m_p" data member
      // to become a dangling pointer, we are setting 
      // "other" objects "m_p" data member to nullptr.
      // for controlling in destructor later.
      // this is a way that telling "other" objects' data was stolen.
    }

    // move assignment
    String& operator=(String&& other)
    {
      // self assignment control
      if (this == &other)
        return *this;

      std::free(m_p);
      // releasing the memory that "*this" object's 
      // "m_p" data member points to.

      m_len = other.m_len;
      m_p = other.m_p;
      // copying "other" objects data members to "*this" object.

      other.m_p = nullptr;
      // to prevent "*this" object's "m_p" data member
      // to become a dangling pointer, we are setting 
      // "other" objects "m_p" data member to nullptr.
      // for controlling in destructor later.
      // this is a way that telling "other" objects' data was stolen.
      other.m_len = 0;

      return *this;
    }

    // destructor
    ~String()
    {
      if (m_p)   
        std::free(m_p);
      // if object's data member pointer(m_p) is not nullptr
      // it still points to a memory in heap.
      // so we need to free that memory.
      // else do not give its resource back
      // its already stolen by another object.
    }
  private:
    std::size_t m_len;
    char* m_p;
  };
*/

/*
      <--- check special_member_functions.png --->
*/

/*
  // If user does not declare any special member functions,
  // all special member functions will be
  // implicitly declared defaulted by the compiler.

  class Myclass {};

  class Myclass_imp{
  public:
    Myclass_imp() = default;
    ~Myclass_imp() = default;

    // copy members 
    Myclass_imp(const Myclass_imp&) = default;
    Myclass_imp& operator=(const Myclass_imp&) = default;

    // move members
    Myclass_imp(Myclass_imp&&) = default;
    Myclass_imp& operator=(Myclass_imp&&) = default;
  };
*/

/*
  // If user declares a constructor other than default ctor,
  // default ctor will not be declared.

  class Myclass {
  public:
    Myclass(int);
  };

  class Myclass_imp {
  public:
    Myclass_imp(int);
    ~Myclass_imp() = default;

    Myclass_imp(const Myclass_imp&) = default;
    Myclass_imp& operator=(const Myclass_imp&) = default;

    Myclass_imp(Myclass_imp&&) = default;
    Myclass_imp& operator=(Myclass_imp&&) = default;
  };
*/

/*
  // If user declares default ctor,
  // all other special member functions will be 
  // implicitly declared defaulted by the compiler.

  class Myclass {
  public:
    Myclass();  // user declared to be defined default ctor
  };

  class Myclass_imp {
  public:
    Myclass_imp();    
    ~Myclass_imp() = default;

    Myclass_imp(const Myclass_imp&) = default;
    Myclass_imp& operator=(const Myclass_imp&) = default;

    Myclass_imp(Myclass_imp&&) = default;
    Myclass_imp& operator=(Myclass_imp&&) = default;
  };
*/

/*
  // If user declares destructor,
  // move members will not be declared.

  class Myclass {
  public:
    ~Myclass();
  };

  class Myclass_imp {
  public:
    Myclass_imp() = default;
    ~Myclass_imp();

    Myclass_imp(const Myclass_imp&) = default;
    Myclass_imp& operator=(const Myclass_imp&) = default;
  };
*/

/*
  // If user declares copy constructor,
  // default ctor is will not be declared.
  // move members will not be declared.

  class Myclass {
  public:
    Myclass(const Myclass&);
  };

  class Myclass_imp {
  public:
    ~Myclass_imp() = default;

    Myclass_imp(const Myclass_imp&);
    Myclass_imp& operator=(const Myclass_imp&) = default;
  };
*/

/*
  // If user declares copy asssignment,
  // move members will not be declared.
  // copy constructor will be implicitly declared defaulted.

  class Myclass {
  public:
    Myclass& operator=(const Myclass&);
  };

  class Myclass_imp{
  public:
    Myclass_imp() = default;
    ~Myclass_imp() = default;

    Myclass_imp(const Myclass_imp&) = default;
    Myclass_imp& operator=(const Myclass_imp&);
  };
*/

/*
  // If user declares move constructor,
  // default ctor will not be declared.
  // copy members will be implicitly declared deleted.
  // move assignment will not be declared.

  class Myclass {
  public:
    Myclass(Myclass&&);
  };

  class Myclass_imp {
  public:
    ~Myclass_imp() = default;

    Myclass_imp(const Myclass_imp&) = delete;
    Myclass_imp& operator=(const Myclass_imp&) = delete;

    Myclass_imp(Myclass_imp&&);
  };
*/

/*
  // If user declares move assignment,
  // copy members will be implicitly declared deleted.
  // move constructor will not be declared.

  class Myclass {
  public:
    Myclass& operator=(Myclass&&);
  };

  class Myclass_imp {
  public:
    Myclass_imp() = default;
    ~Myclass_imp() = default;

    Myclass_imp(const Myclass_imp&) = delete;
    Myclass_imp& operator=(const Myclass_imp&) = delete;

    Myclass_imp& operator=(Myclass_imp&&);
  };
*/

/*
  1. copyable && movable classes
    -> std::string
    -> containers
  2. non-copyable && non-movable classes
  3. non-copyable but movable classes
    -> istream, ostream classes
    -> std::thread class
    -> unique_ptr class
*/

/*
  // non-copyable but movable classes examples

  #include <thread>   // std::thread
  #include <memory>   // std::unique_ptr

  class Myclass {
  public:
    Myclass() = default;

    Myclass(const Myclass&) = delete;
    Myclass& operator=(const Myclass&) = delete;

    Myclass(Myclass&&);
    Myclass& operator=(Myclass&&);
  };

  int main()
  {
    // ----------------------------------------------------------

    std::thread t1;

    std::thread t2 = t1;      // syntax error
    // error: use of deleted function 
    // 'std::thread::thread(const std::thread&)'
    // copy ctor is deleted

    std::thread t3 = std::thread{};     // VALID(move ctor)
    t2 = std::move(t1);                 // VALID(move assignment)

    // ----------------------------------------------------------

    std::unique_ptr<int> uptr{ new int }; 

    std::unique_ptr<int> uptr_2 = uptr;    // syntax error
    // error: use of deleted function 
    // 'std::unique_ptr<_Tp, _Dp>::unique_ptr(
    //                      const std::unique_ptr<_Tp, _Dp>&)
    // copy ctor is deleted

    std::unique_ptr<int> uptr_3 = std::move(uptr);  // VALID(move ctor)

    // ----------------------------------------------------------

    Myclass m1, m2;
    m1 = m2; // syntax error
    // error: use of deleted function 
    // 'Myclass& Myclass::operator=(const Myclass&)'
    // copy assignment is deleted

    Myclass m3 = m1;    // syntax error
    // error: use of deleted function 'Myclass::Myclass(const Myclass&)'
    // copy ctor is deleted

    Myclass m4 = std::move(m1);   // VALID(move ctor)
    m2 = std::move(m1);           // VALID(move assignment)

    // ----------------------------------------------------------
  }
*/

/*
  // non-copyable && non-movable class example

  class Myclass {
  public:
    Myclass() = default;
    Myclass(const Myclass&) = delete;
    Myclass& operator=(const Myclass&) = delete;
  };
  // because one of copy members are user declared deleted,
  // move members will not be declared.

  int main()
  {
    Myclass m1;
    Myclass m2 = m1;              // syntax error
    // error: use of deleted function 'Myclass::Myclass(const Myclass&)'
    // copy ctor is deleted.

    Myclass m3;
    m1 = m3;                      // syntax error
    // error: use of deleted function 
    // 'Myclass& Myclass::operator=(const Myclass&)'
    // copy assignment deleted
    
    m2 = std::move(m1);           // syntax error
    // error: use of deleted function 
    // 'Myclass& Myclass::operator=(const Myclass&)'
    // because of move assignment is not declared
    // copy assignment will be called and its deleted.

    Myclass m4 = std::move(m2);   // syntax error
    // error: use of deleted function 'Myclass::Myclass(const Myclass&)'

    // because of move ctor is not declared,
    // copy ctor is called and its deleted.
  }
*/
