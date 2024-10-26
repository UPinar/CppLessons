#ifndef MINT_HPP
#define MINT_HPP

/*
  "istream" and "ostream" classes will be used in
  operator overload functions
    - if operator overload functions will be defined in header(.h) file
    (header only library)
    include <ostream> and <istream> modules

    - if operator overload functions will be defined in source(.cpp) file
    include <iosfwd> module in header file

  <iosfwd> module have ostream and istream forward declarations
  do not include <iostream> module
*/

#include <ostream>
#include <istream>

class Mint
{
public:
  explicit Mint(int x = 0) : m_x{ x } {} // explicit ctor
  // implicit conversion from int to Mint is not allowed

  // -------------------------------------------------------

  // operator<< and operator>> functions must be global functions
  // because ostream and istream classes are not our classes
  // - can be global operator overload function
  // - can be hidden friend operator overload function

  // operator<< : inserter function(inserting data to ostream object)
  friend std::ostream& operator<<(std::ostream &os, const Mint &mint)
  {
    return os << mint.m_x;
    return os.operator<<(mint.m_x);
    // Those 2 lines are equivalent.
  }

  // operator>> : extractor function(extracting data from istream object)
  friend std::istream& operator>>(std::istream &is, Mint &mint)
  {
    return is.operator>>(mint.m_x);
    return is >> mint.m_x;
    // Those 2 lines are equivalent.
  }

  // -------------------------------------------------------

  // since C++20
  // auto operator<=>(const Mint&) = default; 
  // spaceship(three-way comparison) operator function can be defaulted

  [[nodiscard]] 
  friend bool operator==(const Mint &lhs, const Mint &rhs)
  {
    return lhs.m_x == rhs.m_x;
  }
  // [!= operator overload function is outside of the class]

  [[nodiscard]] 
  friend bool operator<(const Mint &lhs, const Mint &rhs)
  {
    return lhs.m_x < rhs.m_x;
  }

  // friend declared global operator overload functions
  // (hidden friend functions)
  // can reach private data members of Mint class
  // because of friend declaration

  // operator!=() function can be written by using operator==() function
  // operator> - operator>= - operator<= functions 
  // can be written by using operator<() function
  
  // -------------------------------------------------------

  // assignment operator overload functions 
  // will return L value reference(object itself)
  // assignment operator functions are member functions.

  // assignment by sum operator overload function
  Mint& operator+=(const Mint &other)
  {
    m_x += other.m_x;
    return *this;
  }

  // assignment by difference operator overload function
  Mint& operator-=(const Mint &other)
  {
    m_x -= other.m_x;
    return *this;
  }

  // assignment by quotient operator overload function
  Mint& operator/=(const Mint &other)
  {
    if (other.m_x == 0)
      throw std::runtime_error{"divided by zero error"};

    m_x /= other.m_x;
    return *this;
  }

  // assignment by product operator overload function
  Mint& operator*=(const Mint &other)
  {
    m_x *= other.m_x;
    return *this;
  }

  // -------------------------------------------------------

  // increment and decrement operator overload functions
  // are member functions.

  // prefix increment and decrement operator overload functions
  // returns L value reference(object itself)

  // postfix increment and decrement operator overload functions
  // returns R value

  // prefix increment operator overload function
  Mint& operator++()
  {
    ++m_x;
    return *this;
  }
  
  // prefix decrement operator overload function
  Mint& operator--()
  {
    --m_x;
    return *this;
  }

  // postfix increment operator overload function (dummy int parameter)
  Mint operator++(int)
  {
    Mint temp{ *this };
    operator++(); // calling prefix increment operator function
    return temp;
  }

  // postfix decrement operator overload function (dummy int parameter)
  Mint operator--(int)
  {
    Mint temp{ *this };
    operator--(); // calling prefix decrement operator function
    return temp;
  }

  // -------------------------------------------------------

  // sign operator overload functions returns R value
  // sign operator overload functions are member functions

  // sign operator(plus) overload function 
  Mint operator+() const
  {
    return *this;
  }

  // sign operator(minus) overload function
  Mint operator-() const
  {
    return Mint{ -m_x };
  }

private:
  int m_x;
};

// -------------------------------------------------------
// -------------------------------------------------------

// 1. better to use global operator overload functions 
// for simetric operations.

// 2. if a function will be defined outside of the class
// in header(.h) file, it must be declared as `inline` function

// -------------------------------------------------------
// -------------------------------------------------------

// global comparison operator overload functions

// operator!= can call hidden friend operator== overload function
// so making operator!= as an hidden friend function is not necessary

// global operator!= overload function
[[nodiscard]] 
inline bool operator!=(const Mint &lhs, const Mint &rhs)
{
  return !operator==(lhs, rhs);
  return !(lhs == rhs);
  // Those 2 lines are equivalent.
}

// '>', '<=', '>=' operations can be written by using '<' operation
// so making those functions as hidden friend functions is not necessary
// because they can call hidden friend '<' operator overload function

// global operator> overload function
[[nodiscard]] 
inline bool operator>(const Mint &lhs, const Mint &rhs)
{
  // (a > b) -> (b < a)
  return operator<(rhs, lhs);
  return rhs < lhs;
  // Those 2 lines are equivalent.
}

// global operator<= overload function
[[nodiscard]] 
inline bool operator<=(const Mint &lhs, const Mint &rhs)
{
  // (a <= b) -> !(b < a)
  return !operator<(rhs, lhs);
  return !(rhs < lhs);
  // Those 2 lines are equivalent.
}

// global operator>= overload function
[[nodiscard]] 
inline bool operator>=(const Mint &lhs, const Mint &rhs)
{
  // (a >= b) -> !(a < b)
  return !operator<(lhs, rhs);
  return !(lhs < rhs);
  // Those 2 lines are equivalent.
}

// -------------------------------------------------------

// arithmetic operator overload functions

// '+' operation can be written by using '+=' operation
// '-' operation can be written by using '-=' operation
// '*' operation can be written by using '*=' operation
// '/' operation can be written by using '/=' operation

// so making those operator overload functions as 
// hidden friend function is not necessary

// global operator+ overload function 
[[nodiscard]] 
inline Mint operator+(const Mint &r1, const Mint &r2)
{
  return Mint{ r1 } += r2;
}

// global operator- overload function
[[nodiscard]] 
inline Mint operator-(const Mint &r1, const Mint &r2)
{
  return Mint{r1} -= r2;
}

// global operator/ overload function
[[nodiscard]] 
inline Mint operator/(const Mint &r1, const Mint &r2)
{
  return Mint{r1} /= r2;
}

// global operator* overload function
[[nodiscard]] 
inline Mint operator*(const Mint &r1, const Mint &r2)
{
  return Mint{r1} *= r2;
}

// -------------------------------------------------------

#endif // MINT_HPP