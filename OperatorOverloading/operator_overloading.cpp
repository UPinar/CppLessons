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

// ----------------------------------------------------
// TODO: CONTINUE FIXING FROM HERE
// ----------------------------------------------------

/*
  // ostream and istream << and >> operator overloading
  #include "mint.h"

  int main()
  {
    Mint m1{}, m2{};

    // std::cout << m1;
    // operator<<(std::cout, m1);
    // these two lines are same

    // std::cin >> m2;
    // operator>>(std::cin, m1);
    // these two lines are same

    std::cout << "Write two numbers: ";
    std::cin >> m1 >> m2;

    std::cout << "m1 = " << m1 << " m2 = " << m2;
  }
*/

/*
  ====================================
  | overloading comparison operators |
  ====================================
*/

/*
  ---------------------------------------
  ==	equality operators
  !=
  ---------------------------------------
  <
  <=	relational operators(simetric operators)
  >	it is better overloading global function
  >=
  ---------------------------------------


  == -> !(=)

  a < b	// if we write operator< overload function, we can write >, >=, <= with using operator< function
  a > b	->  !(b < a)
  a >= b	->	!(a < b)
  a <= b  ->  !(b < a)
*/

/*
  #include "mint.h"

  int main()
  {
    Mint m1{ 243 }, m2{ 345 };

    if (m1 < m2)
    {
      std::cout << "true\n";
    }
    if (m2 >= Mint{345})
    {
      std::cout << "true\n";
    }
  }
*/

/*
  ====================================
  | overloading assignment operators |
  ====================================
*/

/*
  #include "mint.h"
  int main()
  {
    Mint m1{ 243 }, m2{ 345 };
    std::cout << "m1 = " << m1 << '\n';	// output -> (243)

    m1 += m2;
    std::cout << "m1 = " << m1 << '\n';	// output -> (588)
  }
*/

/*
  ====================================
  | overloading arithmetic operators |
  ====================================
*/

/*
  #include "mint.h";

  int main()
  {
    Mint m1{ 243 }, m2{ 345 };

    std::cout << m1 + m2 + Mint{ 102 } << '\n';
  }
*/

/*
  =================================================
  | overloading increment and decrement operators |
  =================================================
*/

/*
  #include "mint.h"

  int main()
  {
    Mint m1{ 34 }, m2{ 34 };

    // prefix operator++
    auto my = ++m1;
    std::cout << "m1 = " << m1 << '\n'; // output -> (35)
    std::cout << "my = " << my << '\n'; // output -> (35)

    // postfix operator++
    auto mz = m2++;
    std::cout << "m2 = " << m2 << '\n'; // output -> (35)
    std::cout << "mz = " << mz << '\n'; // output -> (34)
  }
*/

/*	---------------------------
  | [[nodiscard]] Attribute |
  ---------------------------
*/

/*
  // [[nodiscard]] Attribute
  // warning C4834: discarding return value of function with 'nodiscard' attribute

  [[nodiscard]] int square(int x)
  {
    return x * x;
  }

  int main()
  {
    int ival{ 33 };

    square(ival);
  }

  // [[nodiscard]] attribute in comparison and arithmetic operator overload functions is a good practice.
*/

/*
  ==================================
  | overloading subscript operator |
  ==================================
*/

/*
  #include <vector>

  class ivector {
  public:
    ivector();
    ivector(std::size_t size);

    // CONST OVERLOADING
    int& operator[](std::size_t);			// non-const member function
    const int& operator[](std::size_t) const;	// const member function
  };

  int main()
  {
    ivector vec(100);

    vec[3] = 12;		// for changing the value (writing purpose)
    auto val = vec[45];	// for reading purpose


    std::vector ivec{ 3, 6, 8, 1, 2 };
    const std::vector cvec{ 3, 6, 8, 1, 2 };

    auto a = ivec[2];
    auto b = cvec[2];
    ivec[3] = 6;
    cvec[3] = 6; // sythax error

    // front() and back() functions are CONST OVERLOADED member functions of std::vector class

    ivec.front() = 87;	// legal
    cvec.front() = 87;	// sythax error
    ivec.back() = 90;	// legal
    cvec.back() = 90;	// sythax error

    // multi-index overload (C++23 standards)
    // can be used overloading operator[] for multi dimensional arrays
  }
*/

/*
  ===================================
  | dereferencing operator overload |
  =============================================
  | member selection(arrow) operator overload |
  =============================================
*/

/*
  template <typename T>
  class UniquePtr {
  public:
    // default ctor
    UniquePtr() : mp{nullptr}{}

    // destructor
    ~UniquePtr()
    {
      if (mp)
        delete mp;
    }

    explicit UniquePtr(T *p) : mp{p}{}

    // move ctor
    UniquePtr(UniquePtr&& other) : mp{ other.mp }
    {
      other.mp = nullptr; // for not creating a dangling pointer after move ctor
    }
    // move assignment
    UniquePtr& operator=(UniquePtr&& other)
    {
      if (this == &other)
        return *this;

      mp = other.mp;
      other.mp = nullptr;

      return *this;
    }
    // copy ctor and copy assignment are deleted because one of move members user declared.

    T* get()
    {
      return mp;
    }
    T* release()
    {
      auto ret = mp;
      mp = nullptr;
      return ret;
    }

    // dereferencing operator overload
    T& operator*()
    {
      return *mp;
    }

    // arrow operator is a binary operator but its overloads like unary operator.
    // arrow operator overload
    // uptr.operator->()->foo();
    // [uptr.operator->()] expression needs be to pointer for to create an expression like this [(T*)->foo()]
    // [Return type needs to be a pointer type]
    T* operator->()
    {
      return mp;
    }

  private:
    T* mp;
  };

  class Myclass {
  public:
    void foo();
    void bar();
  };

  int main()
  {
    UniquePtr<Myclass> uptr{ new Myclass };

    (*uptr).bar();
    // *uptr is Myclass object

    uptr->foo();
    // uptr.operator->()->foo();
  }
*/

/*
  ===================================
  | function call operator overload |
  ===================================
*/

/*
  class Functor {
  public:
    // can have a default argument
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
    fn();

    // fn(12);
    // fn.operator()(12);
  }
*/

/*
  class Myclass {
  public:
    // function call operator can be overloaded
    void operator()(int);
    void operator()(double);
    void operator()(char);
    void operator()(const char*);
  };

  int main()
  {
    Myclass m;
    m(12);
  }
*/

/*
  #include <cstdlib>

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
    Random rand3{ 1'000'000, 1'001'000 };


    foo(rand1);
    foo(rand2);
    foo(Random{ 129,1231 });
  }
*/

/*
  ========================================
  | type-cast operator overload function |
  ========================================
  // needs to be member operator function CAN NOT BE GLOBAL OPERATOR FUNCTION
*/

/*
  class Myclass {
  public:
    // type-cast to int operator overload function, return type is int
    operator int() const
    {
      std::cout << "Myclass::operator int() this = " << this << '\n';
      return 198;
    }
    // [operator int() const] function lets Myclass type implicitly convert to int type [user defined conversion]
  };

  int main()
  {
    Myclass m;
    int ival{};
    std::cout << "&m = " << &m << '\n';

    // ival = m;
    // ival = m.operator int();
    ival = static_cast<int>(m);
    // These 3 lines are same

    std::cout << "varInt = " << ival << '\n';
  }
*/

/*
  user-defined conversion
  ------------------------
  conversion ctor
  type-cast operator overload function
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

    dval = m;
    // Myclass object will convert to int [operator int() const] user-defined conversion
    // int will implicitly conver to double standart conversion

    dval = (double)(m.operator int());
    // same lines

    bool flag;
    flag = m; // legal
    // conversion from Myclass to int (UDC)
    // conversion from int to bool (standart conversion)
  }
*/

/*
  class Myclass {
  public:
     explicit operator int()const;
  };

  int main()
  {
    Myclass m;
    int ival{};

    ival = m; // syntax error

    ival = static_cast<int>(m);
    ival = (int)m;
    ival = int(m);
    ival = m.operator int();
    // These 4 lines can be used when type cast operator overload is explicit
  }
*/

/*
  class Counter {
  public:
    Counter() = default;
    explicit Counter(int x) : mc{ x } {}

    // inserter function [hidden friend]
    friend std::ostream& operator<<(std::ostream& os,const Counter& c)
    {
      return os << '(' << c.mc << ')';
    }

    Counter& operator++()
    {
      ++mc;
      return *this;
    }

    Counter operator++(int)
    {
      Counter temp{ *this };
      operator++();
      return temp;
    }

    explicit operator int()const
    {
      return mc;
    }
  private:
    int mc{};
  };

  int main()
  {
    Counter mycounter{ 34 };

    for (size_t i = 0; i < 10; i++)
    {
      ++mycounter;
    }
    mycounter++;

    auto x1 = static_cast<int>(mycounter);
    auto x2 = (int)mycounter;
    auto x3 = int(mycounter);

    std::cout << "x1 = " << x1 << '\n';
    std::cout << "x2 = " << x2 << '\n';
    std::cout << "x3 = " << x3 << '\n';

    operator<<(std::cout, mycounter);
  }
*/

/*
  #include <memory>
  class Myclass{};

  int main()
  {
    // These are all sythax errors because
    // Myclass did not have a bool operator overload functoion
    Myclass m1, m2;

    auto x = m1 && m2;			// not legal
    auto x = m1 || m2;			// not legal
    while (m1) {}				// not legal
    if (m2) {}				// not legal

    auto x3 = std::cin && std::cout;	// legal
    if (std::cin){}				// legal
    while (std::cout){}			// legal

    std::unique_ptr<int> uptr{ new int };
    if(uptr.operator bool()){}		// legal
  }
*/

/*
  class Myclass {
  public:
    explicit operator bool()const;
  };

  int main()
  {
    Myclass m;

    int x = m;
    bool b = m;
    // explicit operator bool overload function is not legal

    if (m) {}
    auto val = m ? 10 : 20;
    while (m) {}
    bool b = !m;
    b = m || m;
    b = m && m;
    // explicit operator bool overload function is legal when used in logic context
    // [LOJIK BAGLAM]
  }
*/

/*
   class A {
   public:
    operator bool() const
    {
      return true;
    }
   };

   int main()
   {
    A a1, a2;

    // These 2 lines are same
    auto x =  a1 + a2; // type of x is int
    // auto x = a1.operator bool() + a2.operator bool();
    std::cout << "x = " << x << '\n';

    auto y = A{};	// type of y is A
    auto z = +A{};	// type of z is int -> from A to bool UDR, from bool to int promotion(standart) conversion
   }
*/

/*
  =======================================
  | enum type global operator functions |
  =======================================
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

  std::ostream& operator<<(std::ostream& os, const Weekday& wd)
  {
    // for using as a lookup table
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

  // prefix
  Weekday& operator++(Weekday& wd)
  {
    using enum Weekday; // C++ 20
    return wd = wd == Saturday ? Sunday : static_cast<Weekday>(static_cast<int>(wd) + 1);
  }
  // postfix
  Weekday operator++(Weekday& wd, int)
  {
    Weekday temp{ wd };
    operator++(wd); // calling prefix++
    return temp;
  }

  int main()
  {
    // prefix
    auto wd{ Weekday::Monday };

    for (size_t i = 0; i < 24; i++)
    {
      std::cout << ++wd << '\n';
    }

    // postfix
    auto wd2{ Weekday::Saturday };
    std::cout << wd2++ << '\n'; 	// output -> Saturday
    std::cout << wd2 << '\n';	// output -> Sunday
  }
*/
