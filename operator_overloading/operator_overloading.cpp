#include <iostream>

/*
                  ========================
                  | operator overloading |
                  ========================
*/

/*
  Question : What is operator overloading ?
    When a class object used as an operand of operator,
    compiler willconvert that expression to a function call.
*/

/*
  ----------------------------------------------------

  operator functions can be
    - a free(global) function
    - a non-static member function

  operator functions can not be
    - a static member function

  ----------------------------------------------------

  operator function's minimum 1 operand needs to be
    - a class type OR
    - an enum type

  ----------------------------------------------------
*/

/*
  ----------------------------------------------------
  |        operators that CAN NOT be overload        |
  ----------------------------------------------------
  ::          scope resolution operator
  .           member selection (dot) operator
  sizeof()    sizeof operator
  ? :         ternary operator
  .*          pointer to member of object operator
  typeid()    typeid operator
  noexcept    noexcept operator
*/

/*
  operators that CAN ONLY BE a member operator function
  ----------------------------------------------------
  []          subscript operator
  ->          member selection (arrow) operator
  ()          function call operator
  =           assignment operator
  type conversion operators
*/

/*
  ONLY operator() function call operator can have a default argument.
*/

/*
  // ----------------------------------------------------
  //                        !x                          |
  //                   x.operator!()                    |
  //            (unary) not equals operator             |
  // ----------------------------------------------------

  // member not equals operator function
  class Myclass {
  public:
    bool operator!()const;
  };

  // because of unary operator's affect will be applied to
  // the operand of that operator and because of operator function
  // is a non-static member function, it does not need any parameter.
  // it already has a hidden parameter(this pointer)
  // the object itself(*this) -> operand of the operator

  // ----------------------------------------------------

  // global operator not equals function
  bool operator!(const Myclass&);

  // because of unary operator's affect will be applied to
  // global operator function needs to know its operand
  // so const Myclass& is used as a parameter variable

  // ----------------------------------------------------
*/

/*
  // ----------------------------------------------------
  //                      a < b                         |
  //                  a.operator<(b)                    |
  //            (binary) less than operator             |
  // ----------------------------------------------------
*/

/*
  // member less than operator function
  class Myclass {
  public:
    bool operator<(const Myclass& other) const
    {
      std::cout << "this   = " << this << "\n";
      std::cout << "&other = " << &other << "\n";
      return true;
    }
  };

  int main()
  {
    Myclass a, b;

    // ----------------------------------------------------

    std::cout << "&a = " << &a << '\n';
    // output -> &a = 0x4600bffa8d
    std::cout << "&b = " << &b << '\n';
    // output -> &b = 0x4600bffa8c

    // ----------------------------------------------------

    auto ret = a < b;
    auto ret2 = a.operator<(b);
    // Those 2 lines are equivalent.

    // output ->
    //  this   = 0x4600bffa8d
    //  &other = 0x4600bffa8c

    // ----------------------------------------------------
  }
*/

/*
  // global less than operator function
  class Myclass {};

  bool operator<(const Myclass& lhs, const Myclass& rhs)
  {
    std::cout << "&lhs = " << &lhs << "\n";
    std::cout << "&rhs = " << &rhs << "\n";
    return true;
  }

  int main()
  {
    Myclass m1, m2;

    // ----------------------------------------------------

    std::cout << "&m1 = " << &m1 << "\n";
    // output -> &m1 = 0x2730dffb2d
    std::cout << "&m2 = " << &m2 << "\n";
    // output -> &m2 = 0x2730dffb2c

    // ----------------------------------------------------

    auto b1 = m1 < m2;
    auto b2 = operator<(m1, m2);
    // Those 2 lines are equivalent.

    // output ->
    //  &lhs = 0x2730dffb2d
    //  &rhs = 0x2730dffb2c

    // ----------------------------------------------------
  }
*/

/*
  // function overloading in operator functions

  class Myclass {
  public:
    Myclass operator+(int) const
    {
      std::cout << "Myclass operator+(int) const\n";
      return *this;
    }
    Myclass operator+(double) const
    {
      std::cout << "Myclass operator+(double) const\n";
      return *this;
    }
    Myclass operator+(long) const
    {
      std::cout << "Myclass operator+(long) const\n";
      return *this;
    }
  };

  int main()
  {
    Myclass m;

    auto m1 = m + 1;
    // output -> Myclass operator+(int) const

    auto m2 = m + 1.2;
    // output -> Myclass operator+(double) const

    auto m3 = m + 12L;
    // output -> Myclass operator+(long) const
  }
*/

/*
   +x           [sign operator]               [unary]
   a + b        [addition operator]           [binary]

   -x           [sign operator]               [unary]
   a - b        [substraction operator]       [binary]

   &x           [address of operator]         [unary]
   a & b        [bitwise and operator]        [binary]

   *ptr         [dereference operator]        [unary]
   a * b        [multiplication operator]     [binary]
*/

/*
  class Myclass {
  public:
    // member sign operator function
    Myclass operator+()const
    {
      std::cout << "sign operator\n";
      return *this;
    }

    // member addition operator function
    Myclass operator+(const Myclass&)const
    {
      std::cout << "addition operator\n";
      return *this;
    }
  };

  int main()
  {
    Myclass mx;

    // (unary) sign operator
    auto val1 = +mx;              // output -> sign operator
    auto val2 = mx.operator+();   // output -> sign operator

    // (binary) addition operator
    auto val3 = mx + mx;          // output -> addition operator
    auto val4 = mx.operator+(mx); // output -> addition operator
  }
*/

/*
  class Matrix {
  public:
    // member operator functions
    Matrix operator*(const Matrix&)const;   // binary 
    Matrix operator+(const Matrix&)const;   // binary
    Matrix operator!()const;                // unary 
  };

  int main()
  {
    Matrix m1, m2, m3, m4, m5;

    // m5 = (m1 * m2) + (m3 * (!m4));
    m5 = m1 * m2 + m3 * !m4;
    m5 = (m1.operator*(m2)).operator+(m3.operator*(m4.operator!()));
  }
*/

/*
  class Matrix {};

  // global operator functions
  Matrix operator*(const Matrix&, const Matrix&);   // binary
  Matrix operator+(const Matrix&, const Matrix&);   // binary
  Matrix operator!(const Matrix&);                  // unary

  int main()
  {
    Matrix m1, m2, m3, m4, m5;

    // m5 = (m1 * m2) + (m3 * (!m4));
    m5 = m1 * m2 + m3 * !m4;
    m5 = operator+(operator*(m1, m2), operator*(m3, operator!(m4)));
  }
*/

/*
  int main()
  {
    int x = 10;

    // ----------------------------------------------------

    std::cout << x > 5;   // syntax error 
    // error: no match for 'operator>' 
    // (operand types are 'std::basic_ostream<char>' and 'int')

    // precedence of 'operator<<' is bigger than 'operator>'
    // (std::cout << x) > 5
    // "std::cout << x" expression's data type is std::cout object
    // there is no comparison with std::cout object and int
    
    // ----------------------------------------------------

    std::cout << (x > 5);          // output -> 1
    std::cout.operator<<(x > 5);   // output -> 1

    // ----------------------------------------------------
  }
*/

/*
  #include <bitset>
  #include <cstdio>   // std::putchar

  int main()
  {
    std::bitset<8> bs(5);

    // ----------------------------------------------------

    std::cout << bs;    
    // output -> 00000101

    putchar('\n');

    operator<<(std::cout, bs);
    // output -> 00000101

    putchar('\n');

    // ----------------------------------------------------

    std::cout << (bs << 5);     
    // output -> 10100000

    putchar('\n');

    operator<<(std::cout, bs.operator<<(5));
    // output -> 10100000

    putchar('\n');

    // ----------------------------------------------------

    // "<<" is a left associative operator

    std::cout << bs << 5;
    // output -> 000001015

    std::putchar('\n');

    operator<<(std::cout, bs).operator<<(5);
    // output -> 000001015

    // ----------------------------------------------------
  }
*/


/*
  Q.1 : 
  Why there is global operator functions?
  What if whole operator functions are member operator functions?

  Mint class has an int data member. It is a wrapper class for int.
  (Mint + int) 
  can be applied with Mint.operator+(int) member operator function.

  (int + Mint) should be same with (Mint + int)
  to make this possible, global operator functions are needed.
  with global operator function,
  operator+(int,Mint) and 
  operator+(Mint,int) can be called.
*/


/*
  struct Date {
    Date(int d, int m, int y) : m_d{ d }, m_m{ m }, m_y{ y } {}
    int m_d, m_m, m_y;
  };

  std::ostream& operator<<(std::ostream& os, const Date& d)
  {
    return os << d.m_d << '/' << d.m_m << '/' << d.m_y;
  }

  int main()
  {
    Date dx{ 1, 1, 2001 };

    std::cout << dx << '\n';    // output -> 1/1/2001
    operator<<(std::cout, dx);  // output -> 1/1/2001
  }
*/

/*
  "a + b" is RValue expression
    operator overload function will return value type.

  "a = x" is LValue expression
    operator overload function will return L value reference type.

  "++x" is LValue expression
    operator overload function will return L value reference type.

  "x++" is RValue expression
    operator overload function will return value type
*/

/*
  class Date {
  public:
    Date(int, int, int);

    // member operator+ function will generate RValue expression
    Date operator+(int)const;	
    // return type is Date 

    // int operator-(const Date&)const;
    // Two Date object will be used in 
    // operator-() function 
    // better to use global operator function

    // member operator+= function will generate LValue expression
    Date& operator+=(int);
    // return type is Date&

    // assignment operators will generate LValue expression
  };

  // global operator- function
  int operator-(const Date&, const Date&);

  int main()
  {
    // ----------------------------------------------------

    Date dx{ 12, 5, 1977 };

    auto dy = dx + 100; // member operator+ function called
    // Date dy = dx.operator+(100);

    // ----------------------------------------------------

    Date d1{ 1, 1, 2001 };
    Date d2{ 2, 2, 2002 };

    int d_diff = d2 - d1;   // global operator- function called
    // int d_diff = operator-(d2, d1);

    // ----------------------------------------------------
  }
*/

/*
  #include <string>

  int main()
  {
    std::string city{ "istanbul" };

    auto x = city[2];
    // "city[2]" is an LValue expression
    // [] subscript(index) operator generates an LValue expression
    
    // char& operator[](size_t idx);

    city[0] = 'I';
    // because of [] subscript operator generates an LValue expression
    // assignment to city[0] is VALID.
  }
*/

/*
            ----------------------------------------------
            | const correctness for operator overloading |
            ----------------------------------------------
*/

/*
  // "m1 + m2" will generate RValue expression
  // both Matrix objects will not change so better 
  // making operator+ function const

  class Matrix {
  public:
    Matrix operator+(const Matrix& m2) const;
    // (const Matrix&) -> m2 object is const 
    // const member function -> *this(m1) object is const
  };

  Matrix operator+(const Matrix& m1, const Matrix& m2);
  // both m1 and m2 objects are const
*/


/*
  // "+m1" is PRValue expression
  // Matrix object will not change so better
  // making operator+ function const

  class Matrix {
  public:
    Matrix operator+() const;
    // const member function -> *this(m1) object is const
  };

  Matrix operator+(const Matrix& m1);
  // m1 object is const
*/


/*
  // assignment operators will generate LValue expression

  // "m1 += m2" will generate LValue expression
  // m1 object will be changed but m2 object won't be changed.

  class Matrix {
  public:
    Matrix& operator+=(const Matrix& m2)
    {
      return *this;
    }
    // (const Matrix&) -> m2 object is const 
    // non-const member functions -> *this(m1) object is non-const
  };

  Matrix& operator+=(Matrix& m1, const Matrix& m2);
  // m1 object is non-const
  // m2 object is const
*/

/*
  int main()
  {
    using namespace std;

    // ----------------------------------------------------

    // global operator<< function 
    // ostream& operator<<(ostream&, const char*);

    cout << "hello\n";            // output -> hello
    operator<<(cout, "world\n");  // output -> world

    // ----------------------------------------------------

    // std::ostream classes member function
    // ostream& operator<<(const void*); 

    cout.operator<<("hello\n");	  // output -> 0x7ff673065050

    // ----------------------------------------------------

    // global operator<< function
    // ostream& operator<<(ostream&, const char); 

    char c1 = 'A';
    cout << c1;             // output -> A
    operator<<(cout, c1);   // output -> A

    // ----------------------------------------------------

    // std::ostream classes member function
    // ostream& operator<<(int);

    char c2 = 'A';
    cout.operator<<(c2);   // output -> 65

    // ----------------------------------------------------
  }
*/

/*
  // std::endl is an ostream maniplator function
  std::ostream& Endl(std::ostream& os)
  {
    os.put('\n');
    os.flush();
    return os;
  }

  int main()
  {
    using namespace std;

    int ival{ 24 };

    // ----------------------------------------------------

    // global operator<< functions
    // ostream& operator<<(ostream&, int);
    // ostream& operator<<(ostream&, ostream& (*fp)(ostream&));

    cout << ival << Endl << ival << Endl; 
    // output -> 
    //  24 
    //  24

    // ----------------------------------------------------

    // std::ostream classes member functions
    // ostream& operator<<(int);
    // ostream& operator<<(ostream& (*fp)(ostream&));

    cout.operator<<(ival).operator<<(Endl).
          operator<<(ival).operator<<(Endl);
    // output ->
    //  24
    //  24

    // ----------------------------------------------------
  }
*/

/*
  // We can write our own std::ostream manipulator functions
  std::ostream& dashline(std::ostream& os)
  {
    return os << "\n--------------\n";
  }

  int main()
  {
    using namespace std;

    int ival{ 345 };
    double dval{ 524.2343 };
    long lval{ 23432L };

    cout  << ival << dashline 
          << dval << dashline 
          << lval << dashline;

    // output ->
    //  345
    //  --------------
    //  524.234
    //  --------------
    //  23432
    //  --------------
  }
*/

/*
  in C++ zero cost abstraction classes can be created.
  <chrono> class is a wrapper class in std
*/

/*
  - do not write global operator function and 
    a member operator function doing the same job.
    Will cause ambiguity error.

  - if operator function setting the class object (set functions)
    better to write member operator function.
    operator++(), operator--()
  
  - if there is a simetric operation 
    (a + b) and (b + a) will generate logical results.
    better to write global operator function.
    operator+(), operator*(), operator-() ...

  - for comparison operations, 
    because of two class objects being used
    better to write global operator function.
    operator==(), operator<(), operator>() ...
*/

/*
          ------------------------------------------------
          | overloading inserter and extractor operators |
          ------------------------------------------------
*/

/*
  #include "mint.hpp"
  
  int main()
  {
    Mint m1{}, m2{};

    std::cout << m1;
    operator<<(std::cout, m1);
    // Those 2 lines are equivalent.

    std::cin >> m2;
    operator>>(std::cin, m2);
    // Those 2 lines are equivalent.
  }
*/

/*
  #include "mint.hpp"

  int main()
  {
    Mint m1{}, m2{};

    std::cout << "Write two numbers: ";
    std::cin >> m1 >> m2;
    // input -> Write two numbers: 11 22

    std::cout << "m1 = " << m1 << " m2 = " << m2;
    // output -> m1 = 11 m2 = 22
  }
*/

/*
              ------------------------------------
              | overloading comparison operators |
              ------------------------------------
*/

/*
  ---------------------------------------
  |         equality operators          |
  ---------------------------------------
    ==    : equal to 
    !=    : not equal
  ---------------------------------------
  |         relational operators        |
  ---------------------------------------
    <     : less than
    <=    : less or equal
    >	    : greater than  
    >=    : greater or equal
  ---------------------------------------
  ---------------------------------------
          a != b  -> a !(==) b
          a > b   ->  !(b < a)
          a >= b  ->  !(a < b)
          a <= b  ->  !(b < a)
  ---------------------------------------
  ---------------------------------------
*/

/*
  #include "mint.hpp"

  int main()
  {
    Mint m1{ 243 }, m2{ 345 };

    if (m1 < m2)
      std::cout << "(m1 < m2)\n";
    // output -> (m1 < m2)
    
    if (m2 >= Mint{ 345 })
      std::cout << "(m2 >= 345)\n";
    // output -> (m2 >= 345)
  }
*/

/*
              ------------------------------------
              | overloading assignment operators |
              ------------------------------------
*/

/*
  #include "mint.hpp"
  // check 

  int main()
  {
    Mint m1{ 243 }, m2{ 345 };
    std::cout << "m1 = " << m1 << '\n';
    // output -> m1 = 243

    m1 += m2;
    std::cout << "m1 = " << m1 << '\n';
    // output -> m1 = 588
  }
*/

/*
              ------------------------------------
              | overloading arithmetic operators |
              ------------------------------------
*/

/*
  #include "mint.hpp"

  int main()
  {
    Mint m1{ 243 }, m2{ 345 };

    std::cout << m1 + m2 + Mint{ 102 } << '\n';
    // output -> 690
  }
*/

/*
          -------------------------------------------------
          | overloading increment and decrement operators |
          -------------------------------------------------
*/

/*
  #include "mint.hpp"

  int main()
  {
    Mint m1{ 34 }, m2{ 34 };

    // prefix operator++
    auto mx = ++m1;
    std::cout << "m1 = " << m1 << '\n';   // m1 = 35
    std::cout << "mx = " << mx << '\n';   // my = 35

    // postfix operator++
    auto my = m2++;
    std::cout << "m2 = " << m2 << '\n';   // m2 = 35
    std::cout << "my = " << my << '\n';   // my = 34
  }
*/

/*	
                    ---------------------------
                    | [[nodiscard]] Attribute |
                    ---------------------------
*/

/*
  [[nodiscard]] 
  int square(int x)
  {
    return x * x;
  }

  int main()
  {
    int ival{ 33 };

    square(ival);
    // warning: ignoring return value of 'int square(int)', 
    // declared with attribute 'nodiscard' 
  }

  // for comparison and arithmetic operator overload functions
  // it is a good practice to use [[nodiscard]] attribute
*/


/*
              ----------------------------------
              | overloading subscript operator |
              ----------------------------------
*/

/*
  #include <vector>

  class int_vector {
  public:
    int_vector();
    int_vector(std::size_t size);

    // const overloads 
    int& operator[](std::size_t);
    // non-const member function
    const int& operator[](std::size_t) const;
    // const member function
  };

  int main()
  {
    // ----------------------------------------------------

    int_vector vec(100);  // size_t parameter constructor

    vec[3] = 12;        // for writing purpose
    auto val = vec[45]; // for reading purpose


    std::vector ivec{ 3, 6, 8, 1, 2 };
    const std::vector civec{ 3, 6, 8, 1, 2 };

    // ----------------------------------------------------

    int a = ivec[2];          // VALID  (reading)
    const int b = civec[2];   // VALID  (reading)

    ivec[3] = 6;    // VALID
    civec[3] = 6;   // syntax error
    // error: assignment of read-only location 
    // 'civec.std::vector<int, std::allocator<int> >::operator[](3)'

    // ----------------------------------------------------

    // "front" and "back" member functions of std::vector class 
    // have const overloads

    ivec.front() = 87;    // VALID 
    civec.front() = 87;   // syntax error
    //  error: assignment of read-only location 
    // 'civec.std::vector<int, std::allocator<int> >::front()'


    ivec.back() = 90;     // VALID
    civec.back() = 90;    // sythax error
    // error: assignment of read-only location 
    // 'civec.std::vector<int, std::allocator<int> >::back()'
  }
*/

/*
          ------------------------------------------------
          |       overloading dereferencing operator     |
          ------------------------------------------------
          | overloading member selection(arrow) operator |
          ------------------------------------------------
*/

/*
  template <typename T>
  class UniquePtr {
  public:
    UniquePtr() : m_p{ nullptr } {}    // default constructor

    ~UniquePtr()    // destructor
    {
      if (m_p)
        delete m_p;
    }

    explicit UniquePtr(T *p) : m_p{ p }{} 
    // explicit constructor for preventing implicit conversion

    // move constructor
    UniquePtr(UniquePtr&& other) : m_p{ other.m_p }
    {
      other.mp = nullptr; // to prevent double deletion 
    }

    // move assignment
    UniquePtr& operator=(UniquePtr&& other)
    {
      if (this == &other)
        return *this;
      // if the same object is assigned to itself, return itself

      m_p = other.m_p;
      other.m_p = nullptr;  // to prevent double deletion

      return *this;
    }

    // copy members are deleted 
    // because of one of the move member is user declared.

    T* get()
    {
      return m_p;
    }
    
    T* release()
    {
      auto ret = m_p;
      m_p = nullptr;
      return ret;
    }

    // dereferencing operator overload
    T& operator*()
    {
      return *m_p;
    }

    // arrow operator is a binary operator
    // but its overload function is like a unary operator

    T* operator->()
    {
      return m_p;
    }

  private:
    T* m_p;
  };

  class Myclass {
  public:
    void foo(){ std::cout << "Myclass::foo()\n";}
    void bar(){ std::cout << "Myclass::bar()\n";}
  };

  int main()
  {
    UniquePtr<Myclass> uptr{ new Myclass };

    (*uptr).bar();            // output -> Myclass::bar()


    uptr->foo();              // output -> Myclass::foo()
    uptr.operator->()->foo(); // output -> Myclass::foo()
    // Those 2 lines are equivalent
  }
*/

/*
            --------------------------------------
            | overloading function call operator |
            --------------------------------------
*/

/*
  class Functor {
  public:
    void operator()(int x = -1)
    {
      std::cout << "void Functor::operator()(int x)\n";
      std::cout << "x = " << x << '\n';
      std::cout << "this = " << this << '\n';
    }
  };

  int main()
  {
    Functor fn;

    std::cout << "&fn = " << &fn << '\n';
    // output -> &fn = 0x220d7ffdff

    fn();
    // output -> 
    //  void Functor::operator()(int x)
    //  x = -1
    //  this = 0x220d7ffdff

    fn(22);
    // output -> 
    //  void Functor::operator()(int x)
    //  x = 22
    //  this = 0x220d7ffdff

    fn.operator()(44);
    // output ->
    //  void Functor::operator()(int x)
    //  x = 44
    //  this = 0x220d7ffdff
  }
*/

/*
  class Myclass {
  public:
    // function call operator can be overloaded
    void operator()(int) 
    { 
      std::cout << "void Myclass::operator()(int)\n"; 
    }
  
    void operator()(double)
    { 
      std::cout << "void Myclass::operator()(double)\n"; 
    }

    void operator()(char)
    { 
      std::cout << "void Myclass::operator()(char)\n"; 
    }

    void operator()(const char*)
    { 
      std::cout << "void Myclass::operator()(const char*)\n"; 
    }
  };

  int main()
  {
    Myclass m;

    m(12);  
    // output -> void Myclass::operator()(int)

    m("hello world");
    // output -> void Myclass::operator()(const char*)

    m(3.4);
    // output -> void Myclass::operator()(double)

    m('A');
    // output -> void Myclass::operator()(char)
  }
*/

/*
  #include <cstdlib>  // std::rand

  class Random {
  public:
    Random(int low, int high) : m_low(low), m_high(high) {}

    int operator()()
    {
      return std::rand() % (m_high - m_low + 1) + m_low;
    }
  private:
    int m_low, m_high;
  };

  void foo(Random rx)
  {
    for (int i = 0; i < 10; ++i)
    {
      std::cout << rx() << " ";
    }
    std::cout << '\n';
  }

  int main()
  {
    Random rand1{ 2300, 2360 };
    Random rand2{ 40, 45 };

    foo(rand1);
    // output -> 2341 2345 2351 2326 2315 2347 2310 2317 2300 2303
    foo(rand2);
    // output -> 45 45 41 43 41 45 41 42 43 40
    foo(Random{ 129, 1231 });
    // output -> 533 394 722 282 421 378 1005 1197 1096 170
  }
*/

/*
            -------------------------------------------
            | overloading type-cast operator function |
            -------------------------------------------
*/

/*
  - must be a member function, can not be a global function!
*/

/*
  class Myclass { 
  public:
    // type-cast to int operator overload function
    // operator int() function's return type is `int`
    operator int() const
    {
      std::cout << "Myclass::operator int() this = " << this << '\n';
      return 198;
    }
    // calling operator int() function,
    // Myclass object can implicitly converted to int type
    // -- User Defined Conversion --
  };

  int main()
  {
    Myclass m;
    int ival{};

    std::cout << "&m = " << &m << '\n'; 
    // output -> &m = 0xdabbffc8b

    ival = m;
    ival = m.operator int();
    ival = static_cast<int>(m);
    // These 3 lines are equivalent.
    // output -> Myclass::operator int() this = 0xdabbffc8b

    std::cout << "ival = " << ival << '\n';
    // output -> ival = 198
  }
*/

/*
  User Defined Conversion(UDC)
  ------------------------
  - conversion ctor
  - type-cast operator overload function
*/

/*
  class Myclass {
  public:
    operator int()const;
  };

  int main()
  {
    Myclass m;
    double dval{};
    bool flag;

    // ----------------------------------------------------
    
    dval = m;
    dval = (double)(m.operator int());
    // These 2 lines are equivalent.

    // Myclass ===> int ===> double
    // Myclass ===> int  (UDC)
    // int ===> double  (standart conversion)

    // ----------------------------------------------------

    flag = m;
    // Myclass ===> int ===> bool
    // Myclass ===> int  (UDC)
    // int ===> bool  (standart conversion)

    // ----------------------------------------------------
  }
*/

/*
  class Myclass {
  public:
    explicit operator int() const;
  };

  int main()
  {
    Myclass m;
    int ival{};

    // ----------------------------------------------------

    ival = m; // syntax error
    // error: cannot convert 'Myclass' to 'int' in assignment

    // because of the explicit operator int() function
    // convertion from Myclass to int can not be done implicitly

    // ----------------------------------------------------

    ival = static_cast<int>(m);
    ival = (int)m;
    ival = int(m);
    ival = m.operator int();
    // These 4 lines are equivalent.

    // ----------------------------------------------------
  }
*/

/*
  class Counter {
  public:
    Counter() = default;
    explicit Counter(int x) : m_c{ x } {}

    // hidden friend function operator<< overload
    friend std::ostream& operator<<(std::ostream& os, 
                                    const Counter& c)
    {
      return os << '(' << c.m_c << ')';
    }

    // prefix operator++ overload function
    Counter& operator++()
    {
      ++m_c;
      return *this;
    }

    // postfix operator++ overload function
    Counter operator++(int)
    {
      Counter temp{ *this };
      operator++();
      return temp;
    }

    explicit operator int() const
    {
      return m_c;
    }
  private:
    int m_c{};
  };

  int main()
  {
    Counter mycounter{ 34 };

    for (size_t i = 0; i < 10; i++)
      ++mycounter;  
      // prefix operator++ overload function
    
    mycounter++;  
    // postfix operator++ overload function

    auto x1 = static_cast<int>(mycounter);
    auto x2 = (int)mycounter;
    auto x3 = int(mycounter);
    // operator int() overload function

    std::cout << "x1 = " << x1 << '\n';   // output -> x1 = 45
    std::cout << "x2 = " << x2 << '\n';   // output -> x2 = 45
    std::cout << "x3 = " << x3 << '\n';   // output -> x3 = 45

    operator<<(std::cout, mycounter); // output -> (45)
    // hidden friend operator<< overload function 
  }
*/

/*
  #include <memory>  // std::unique_ptr

  class Myclass{};

  int main()
  {
    Myclass m1, m2;

    // ----------------------------------------------------

    auto x = m1 && m2;  // syntax error
    // error: no match for 'operator&&'
    // (operand types are 'Myclass' and 'Myclass')

    auto x = m1 || m2;  // syntax error
    // error: no match for 'operator||' 
    // (operand types are 'Myclass' and 'Myclass')


    while (m1) {}       // syntax error
    // error: could not convert 'm1' from 'Myclass' to 'bool'


    if (m2) {}          // syntax error
    // error: could not convert 'm2' from 'Myclass' to 'bool'

    // all of them are syntax error because 
    // Myclass does not have operator bool() overload function

    // ----------------------------------------------------

    auto x3 = std::cin && std::cout;  // VALID
    if (std::cin){}                   // VALID
    while (std::cout){}               // VALID

    std::unique_ptr<int> uptr{ new int };
    if(uptr.operator bool()){}        // VALID

    // all of them are VALID because
    // std::cin, std::cout, std::unique_ptr classes
    // do have operator bool() overload function
    
    // ----------------------------------------------------
  }
*/

/*
  class Myclass {
  public:
    explicit operator bool() const;
  };

  int main()
  {
    Myclass m;

    // ----------------------------------------------------

    int x = m;    // syntax error
    // error: cannot convert 'Myclass' to 'int' in initialization
    bool b = m;   // syntax error
    // error: cannot convert 'Myclass' to 'bool' in initialization

    // ----------------------------------------------------

    if (m) {}                 // VALID
    auto val = m ? 10 : 20;   // VALID
    while (m) {}              // VALID
    bool b = !m;              // VALID
    b = m || m;               // VALID
    b = m && m;               // VALID

    // when Myclass object is used in logical context(lojik bağlam)
    // its explicit operator bool() overload function will be called

    // ----------------------------------------------------
  }
*/

/*
   class AClass {
   public:
    operator bool() const { return true; }
   };

   int main()
   {
    AClass a1, a2;

    // ----------------------------------------------------

    auto x1 =  a1 + a2; 
    auto x2 = a1.operator bool() + a2.operator bool();
    // Those 2 lines are equivalent.

    // a1 ===> bool ===> int
    // a2 ===> bool  (UDC)
    // bool ===> int  (integral promotoion)(standart conversion)

    // "x1" and "x2" data types are `int`

    std::cout << "x1 = " << x1 << '\n';   // output -> x1 = 2
    std::cout << "x2 = " << x2 << '\n';   // output -> x2 = 2

    // ----------------------------------------------------

    auto x3 = AClass{};
    // "x3" data type is `AClass`

    // ----------------------------------------------------

    auto x4 = +AClass{};	
    // AClass ===> bool ===> int
    // AClass ===> bool  (UDC)
    // bool ===> int  (integral promotoion)(standart conversion)

    // "x4" data type is `int`

    // ----------------------------------------------------
   }
*/

/*
          --------------------------------------------------
          | enum type's global operator overload functions |
          --------------------------------------------------
*/

/*
  enum class Weekday {
    Sunday,
    Monday,
    Tuesday,
    Wednesday,
    Thursday,
    Friday,
    Saturday,
  };

  // global operator<< overload function
  std::ostream& operator<<(std::ostream& os, const Weekday& wd)
  {
    // lookup table
    static const char* const p[] = {
      "Sunday",
      "Monday",
      "Tuesday",
      "Wednesday",
      "Thursday",
      "Friday",
      "Saturday",
    };

    return os << p[static_cast<int>(wd)];
  }

  // prefix operator++ overload function
  Weekday& operator++(Weekday& wd)
  {
    using enum Weekday; // C++20
    return wd = (wd == Saturday) 
        ? Sunday 
        : static_cast<Weekday>(static_cast<int>(wd) + 1);
  }
  
  // postfix operator++ overload function
  Weekday operator++(Weekday& wd, int)
  {
    Weekday temp{ wd };
    operator++(wd);
    return temp;
  }

  int main()
  {
    auto wd1{ Weekday::Monday };
    auto wd2{ Weekday::Saturday };

    std::cout << ++wd1 << '\n'; // output -> Tuesday
    // prefix operator++ overload function

    std::cout << wd2++ << '\n';   // output -> Saturday
    // postfix operator++ overload function

    std::cout << wd2 << '\n';     // output -> Sunday
  }
*/