#ifndef MINT_H // include guard
#define MINT_H

// do not include <iostream>
// include <ostream> and <istream>

// if you will define friend std::ostream& operator<<(std::ostream&, const Mint&); 
// and friend std::istream& operator>>(std::istream&, Mint&);
// global operator overload functions in .cpp file 
// just include lightweight library, #include <iosfwd> in header(.h) file
// <iosfwd> includes ostream and istream function forward declerations

// if you will define them in header file
// include <ostream> and <istream>

#include <ostream>
#include <istream>

class Mint {
public:
	// if we don't want an implicit conversion from int to Mint, we need to make ctor explicit.
	explicit Mint(int x = 0) : mx{ x } {}

	// <---------------------------------------------------------------------------->

	// we can not write member function for ostream class, that is why << and >> functions 
	// will be global operator functions [hidden friend member functions]
	
	// inserter function [inserting data to ostream object]
	friend std::ostream& operator<<(std::ostream& os, const Mint& mint)
	{
		return os << '(' << mint.mx << ')';
		// return os.operator<<(mint.mx);
	}

	// extractor function [extracting data from istream object]
	friend std::istream& operator>>(std::istream& is, Mint& mint)
	{
		// return is >> mint.mx;
		return is.operator>>(mint.mx);
	}

	// <---------------------------------------------------------------------------->

	// FROM C++ 20
	// auto operator<=>(const Mint&) = default; [SPACESHIP OPERATOR]

	// because of these functions are friends, they can reach Mint classes private section
	// global operator overload function

	[[nodiscard]] friend bool operator==(const Mint& lhs, const Mint& rhs)
	{
		return lhs.mx == rhs.mx;
	}
	// [!= operator overload function is outside of the class]

	[[nodiscard]] friend bool operator<(const Mint& lhs, const Mint& rhs)
	{
		return lhs.mx < rhs.mx;
	}
	// [>, >=, <= operators overload functions are outside of the class]

	// <---------------------------------------------------------------------------->

	// [ASSIGNMENT OPERATORS WILL RETURN L VALUE] 
	// [member operator functions]
	Mint& operator+=(const Mint& other)
	{
		mx += other.mx;
		return *this;
	}	

	Mint& operator-=(const Mint& other)
	{
		mx -= other.mx;
		return *this;
	}

	Mint& operator/=(const Mint& other)
	{
		if (other.mx == 0)
			throw std::runtime_error{ "divided by zero error" };

		mx /= other.mx;
		return *this;
	}
	Mint& operator*=(const Mint& other)
	{
		mx *= other.mx;
		return *this;
	}

	// <---------------------------------------------------------------------------->

	// [INCREMENT AND DECREMENT OPERATORS]
	// prefix increment member operator overload function [++operator] [returns L value]
	Mint& operator++()
	{
		++mx;
		return *this;
	}

	// postfix increment member operator overload function [operator++] [returns R value]
	// have dummy int parameter
	Mint operator++(int)
	{
		Mint temp{ *this };
		operator++(); // calling prefix increment operator member function
		return temp;
	}

	Mint& operator--()
	{
		--mx;
		return *this;
	}

	Mint operator--(int)
	{
		Mint temp{ *this };
		operator--(); // calling prefix decrement operator member function
		return temp;
	}

	// <---------------------------------------------------------------------------->

	// member (sign) operator+ overload  function -> return value is [Rvalue] -> +x
	Mint operator+() const
	{
		return *this;
	}
	// member (sign) operator- overload  function -> return value is [Rvalue] -> -x
	Mint operator-() const
	{
		return Mint{ -mx };
	}

private:
	int mx;
};

// <---------------------------------------------------------------------------->

// [SIMETRIC OPERATORS, IT IS BETTER TO OVERLOAD AS A GLOBAL OPERATOR FUNCTIONS]

// no need to use friend because operator!= function is not accessing private members of Mint class
// == operator overload function is reaching private members.
// we are calling operator== overload function in operator!= overload function.
[[nodiscard]] inline bool operator!=(const Mint& lhs, const Mint& rhs)
{
	return !operator==(lhs, rhs);
	// return !(lhs == rhs);
}

[[nodiscard]] inline bool operator>(const Mint& lhs, const Mint& rhs)
{
	// (a > b) -> (b < a) 
	return operator<(rhs, lhs);
	// return rhs < lhs
}
[[nodiscard]] inline bool operator<=(const Mint& lhs, const Mint& rhs)
{
	// (a <= b) ->  !(b < a)
	return !operator<(rhs, lhs);
	// return !(rhs < lhs);
}
[[nodiscard]] inline bool operator>=(const Mint& lhs, const Mint& rhs)
{
	// (a >= b) ->  !(a < b)
	return !operator<(lhs, rhs);
	// return !(lhs < rhs);
}

// <---------------------------------------------------------------------------->

// [ARITHMETIC OPERATOS]
// not reaching private section of Mint class [no need to be a friend operator overload function]
[[nodiscard]] inline Mint operator+(const Mint& r1, const Mint& r2)
{
	return Mint{ r1 } += r2;

	// Mint temp{ r1 };
	// temp += r2;
	// return temp;
}
[[nodiscard]] inline Mint operator-(const Mint& r1, const Mint& r2)
{
	return Mint{ r1 } -= r2;
}
[[nodiscard]] inline Mint operator/(const Mint& r1, const Mint& r2)
{
	return Mint{ r1 } /= r2;
}
[[nodiscard]] inline Mint operator*(const Mint& r1, const Mint& r2)
{
	return Mint{ r1 } *= r2;
}

#endif