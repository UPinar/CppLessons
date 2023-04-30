#include <iostream>

/*	=============
	| Templates |
	=============
*/

/*
	Template categories
	----------------------- 
	-> function template
	-> class template
	-> alias template (C++11)
	-> variable template (C++14)
	-> concepts (C++20)
*/

/*
	Template parameters
	-----------------------
	-> type parameter
	-> non-type parameter
	-> template parameter
*/

/*
	template <class T, typename U>
	// T is a type parameter, U is also a type parameter.
*/

/*
	non-type parameter represents a constant

	template <int n>
	class Myclass {
		
	}; // n is a non-type parameter (NTTP)
*/

/*
	template <typename T, int n>
	class Myclass {
	private:
		T ar[n];
	};
	// type parameter and NTTP can be templete parameters together.
*/

/*
	template <typename T>
	void func(T x, T y)
	{
	
	}
	// 1 template parameter 2 function parameter
*/

/*
	template <typename T>
	void foo(T x)
	{
		std::cout << "foo() called\n";
		std::cout << typeid(T).name() << '\n';
	}
	
	int main()
	{
		// 1. explicit template argument
		foo<int>(12);
	
		// 2. deduction
			// template argument deduction
			// Before C++17 template argument deduction only valid for function templates.
			// After C++17 class templates are also use template argument deduction called CTAD.
			// CTAD -> [Class Template Argument Deduction.]

		// 3. default template argument
	}
*/

/*
	Template code needs to be in the header(.h) file.
	It will not violate ODR (One Definition Rule).
	Implicitly inline.
*/

/*
	template <typename T>
	void func(T x)
	{
		foo(x);		// legal
		baz();		// syntax error
		x.bar();	// legal
	
		// baz() is not dependent to any template parameter(T's) type.
		// namelookup applied for baz() function before T's deduction happens.
	
	
		// foo(x) and x.bar() are dependent to T type, because x's type is T.
		// Even if namelookup has been failed for foo(x) function.
		// Argument Dependent Lookup[ADL] rules applied.
		// T might be a type that inside a namespace and
		// there might be a function called foo() in that namespace.
		// Based on this probabilities they will throw syntax error.
	}
*/

/*	
	-------------------------------
	| template argument deduction |
	-------------------------------
*/

/*
	template <typename T>
	void func(T x)
	{
	
	}
	
	int main()
	{
		func(12);		// func<int>(12)
		func(1.2);		// func<double>(1.2)
		func(29L);		// func<long>(29L)
	
		// Template argument deduction applied.
	}
*/

/*
	template <typename T>
	void func(T x) {}
	
	int main()
	{
	}
	
	// For T type	-> auto x = expr; rules applied.
	// For T& type  -> auto& y = expr; rules applied.
	// For T&& type	-> auto&& z = expr; rules applied.
*/

/*
	template <typename T>
	void func(T x) {}
	
	int main()
	{
		const int c = 24;
		func(c);	// T is int
	
		int a[10]{};
		func(a);	// T is int*
	
		const int b[10]{};
		func(b);	// T is const int*
	}
*/

/*
	template <typename>
	class TypeTeller;
	
	template <typename T>
	void func(T)
	{
		TypeTeller<T> x;
	}
	
	int foo(int);
	
	int main()
	{
		func(12);
		// 'x' uses undefined class 'TypeTeller<int>'
	
		int a[4]{};
		func(a);
		// 'x' uses undefined class 'TypeTeller<int *>'
	
		const int b[5]{};
		func(b);
		// 'x' uses undefined class 'TypeTeller<const int *>'
	
		int x = 10;
		int& r = x;
		func(r);
		// 'x' uses undefined class 'TypeTeller<int>'
	
		func("Hello");
		// 'x' uses undefined class 'TypeTeller<const char *>'
	
		func(foo);
		// 'x' uses undefined class 'TypeTeller<int (__cdecl *)(int)>'
		// int(*)int
	}
*/

/*
	template <typename>
	class TypeTeller;
	
	template <typename T>
	void func(T& )
	{
		TypeTeller<T> x;
	}
	
	int foo(int);
	
	int main()
	{
		int x = 10;
		func(x);
		// 'x' uses undefined class 'TypeTeller<int>'
	
		int a[5]{};
		func(a);
		// 'x' uses undefined class 'TypeTeller<int [5]>'
		// T's type is int[5]
		// function parameter is int(&r)[5]
	
		func(foo);
		// 'x' uses undefined class 'TypeTeller<int (int)>'
		// T's type is int(int)
	
		const int b = 4;
		func(b);
		// 'x' uses undefined class 'TypeTeller<const int>'
		// T's type is const int
	}
*/

/*
	template <typename>
	class TypeTeller;
	
	template <typename T>
	void func(T&&)	
	{
		// functions parameter can only be L value reference (&) or R value reference(&&)
		TypeTeller<T> x;

	}
	
	int main()
	{
		func(123);	// R value expression
		// T's type is int
		// 'x' uses undefined class 'TypeTeller<int>'
		// functions parameter will be int&&
	
		int y = 23;
		func(y);	// L value exprssion
		// T's type is int&
		// 'x' uses undefined class 'TypeTeller<int&>'
		// functions parameter will be T&& (int& &&)
		// reference collapsing rules applied -> int&
	}
*/

/*
	template <typename T>
	void func(T&&)
	{
		T x; // if T's type int& syntax error.
		// int& variable can not be default initialized.
	}
	
	int main()
	{
		int y = 23;
		func(y);	// y is an L value expression
		// T's type will be int&
	}
*/

/*
	#include <initializer_list>
	
	template <typename T>
	void func(T);
	
	int main()
	{
	
		auto list = { 1,3,5,6 };	// valid
		func({ 1,3,5,6 });		// syntax error
		// only exception that is different between
		// auto type deduction and template type deduction is std::initialzer_list.
	}
*/

/*
	template <typename T>
	T foo();
	
	int main()
	{
		foo(); // syntax error
		// compiler can not understand T's type.
	
		int x = foo(); // still syntax error.
	
		// 'T foo(void)': could not deduce template argument for 'T'
	}
*/

/*
	template <typename T>
	void func(T, T);
	
	int main()
	{
		func(1, 5u); // syntax error
		// 'void func(T,T)': template parameter 'T' is ambiguous
	}
*/

/*
	template <typename T>
	void func(T, T&&);
	
	int main()
	{
		func(10, 20);	// no syntax error
	
		int x{ 1 };
		func(x, x);	// syntax error
	
		// 1st parameter -> T is int
		// 2nd parameter -> T is int&
		// 'void func(T,T &&)': template parameter 'T' is ambiguous
	}
*/

/*
	template <typename T>
	void func(T, T);
	
	template <typename T>
	void foo(T&, T&);
	
	int main()
	{
		func("hello", "hello");		// legal
		func("hello", "myworld");	// legal
		foo("hello", "hello");		// legal
		foo("hello", "myworld");	// syntax error
	}
*/

/*
	template <typename T, int n>
	void func(T(&r)[n]);
	
	int main()
	{
		int ar[5]{};
		func(ar);
	
		// T's type is int, n = 5
	}
*/

/*
	template <typename T>
	void func(T* a);
	
	int main()
	{
		int x{};
		int* p = &x;
		int** ptr = &p;
	
		func(p);	// T's type is int, a's type int*
		func(ptr);	// T's type is int*, a's type is int**
	}
*/

/*
	template <typename T, typename U>
	void func(T(*)(U));
	
	int bar(double);
	
	int main()
	{
		func(bar);
		func(&bar);
		// These 2 lines are same
	}
*/

/*
	template <typename T, std::size_t n>
	constexpr std::size_t asize(T(&)[n])
	{
		return n;
	}
	
	int main()
	{
		int a[] = { 3,5,4,3,6,5,7,5,4,3 };
		constexpr auto val = asize(a);
	}
*/

/*
	// compiler will wrote different functions for different T types.
	template <typename T>
	void func(T)
	{
		std::cout << typeid(T).name() << '\n';
	}
	
	int main()
	{
		func(12);		// output -> int
		func('A');		// output -> char
		func(true);		// output -> bool
	
		func(12);		// output -> int
		func<int>('A');		// output -> int
		func<int>(true);	// output -> int
	}
*/

/*
	template <typename F>
	void func(F f)
	{
		f();
	}
	
	void compilerWrotefunc(void(*f)())
	{
		f();	// callable
	}
	
	void bar()
	{
		std::cout << "bar() called\n";
	}
	
	class Myclass {
	public:
		void operator()()const
		{
			std::cout << "Myclass::operator()() called\n";
		}
	};
	
	int main()
	{
		// 1.
		func(bar);			// output -> bar() called
		compilerWrotefunc(bar);		// output -> bar() called
		// These 2 function calls are same.
	
		// 2.
		func(Myclass{});		// output -> Myclass::operator()() called
	}
*/

/*
	class Myclass {
	public:
		class value_type {
	
		};
	};
	
	template <typename T>
	void func(T)
	{
		T::value_type x;
		// compiler thinks that value_type is a T classes static data member.
	
		typename T::value_type x;
		// now compiler thinks that value_type is T classes nested type.
		// IN ALL Dependent types to T we need to use `typename`
	}
	
	int main()
	{
		func(Myclass{}); // syntax error
		// C7510 : 'value_type' : use of dependent type name must be prefixed with 'typename'
	}
*/

/*
	template <typename T>
	void func(T x);
	
	
	template <typename T, typename U>
	void foo(T, U);
	
	int main()
	{
		func<double>(12);
		// no template argument deduction for T, because we explicitly declared its type.
	
		foo(12, 45);		// (T-> int, U-> int)
		// T and U can be same type.
		foo(12, 2.121);		// (T-> int, U-> double)
	
		foo<int>('A', 5.6);	// (T-> int, U-> double)
		// compiler will only do template argument deduction for U, not for T.
	}
*/

/*
	// Q. Why explicit template arguments used?

	#include <memory>
	#include <string>
	
	
	template <typename T, typename ...Args>
	std::unique_ptr<T> MakeUnique(Args&&...args);
	
	// compiler can not understand T's type if we did not declare T
	// as an explicit template argument.
	
	int main()
	{
		using namespace std;
	
		make_unique<string>(120, 'A');
	}
*/

/*
	------------------------
	| Trailing return type |
	------------------------
*/

/*
	
	// Write a function that returns the address of int foo(int,int).
	
	int foo(int, int);
	
	// func()'s return type should be int(*)(int,int)
	
	int(*func())(int, int)
	{
		return foo;
	}
	
	auto func() -> int(*)(int, int)
	{
		return foo;
	}
*/

/*
	template <typename T,typename U>
	T sum(T x, U y)
	{
		return x + y;
	}
	
	template <typename Result, typename T, typename U>
	Result sum_withResult(T x, U y)
	{
		return x + y;
	}
	
	// trailing return type
	template <typename T, typename U>
	auto sum_with_trailingReturnType(T x, U y)-> decltype(x + y)
	{
		return x + y;
	}

	// auto return type
	template <typename T, typename U>
	auto sum_with_autoReturnType(T x, U y) 
	{
		return x + y;
	}
	
	int main()
	{
		auto val = sum(6, 4.5);
		// functions return type will be int, because T->int
	
		auto val_2 = sum<double>(6, 2.4);
		// client code can declare trailing return type.
	
		auto val_3 = sum_with_trailingReturnType(6, 2.2);
	}
*/

/*
	class Myclass {
	public:
		template <typename T>	// member template
		void foo(T x)
		{
			std::cout << typeid(T).name() << '\n';
		}
	};
	
	int main()
	{
		Myclass m;
		m.foo(12);
		m.foo(1.2);
		m.foo('a');
		m.foo("hello");
	}
*/

/*
	class Myclass {
	public:
		template<typename T>
		Myclass(T);	// constructor
	};
	
	int main()
	{
		Myclass m1{ 35 };
		Myclass m2{ 3.5 };
		Myclass m3{ 3.5f };
		Myclass m4{ 35L };
		Myclass m5{ 35LL };
	}
*/

/*
	class Myclass {
	public:
		template<typename T>
		Myclass& operator=(const T&);
	};
	
	int main()
	{
		Myclass mx;
	
		mx = 5;
		mx = 5.4;
		mx = 5L;
		mx = "hello";
		mx = 'B';
	}
*/

/*
	class Myclass {
	public:
		template<typename T>
		T operator()(T)const;
	};
	
	int main()
	{
		Myclass mx;
	
		auto r1 = mx(12);
		auto r2 = mx("Hello");
		auto r3 = mx(1.4);
		auto r4 = mx('C');
	}
*/

/*
	class Myclass {
	public:
		template<typename T>
		operator T()const
		{
			std::cout << typeid(T).name() << '\n';
			return 0;
		}
	};
	
	int main()
	{
		Myclass mx;
	
		int ival = mx;
		double dval = mx;
		long lval = mx;
	}
*/

/*
	template <typename T>
	T foo(T);
	
	// When there is a call to function template. 
	// Compiler will do a substitution and generate template specialization for that function.
	// That template specialization will join Function Overload Resolution.
	// Not the function template itself.
	
	// int foo<int>(int); -> specialization
	
	
	template <typename T>
	T* func(T*);
	
	// int** func<int*>(int**) -> specialization
	
	int main()
	{
		foo(12);
	
		int x = 10;
		int* p = &x;
		int** ptr = &p;
		func(ptr);
	}
*/

/*
	template <typename T>
	typename T::value_type foo(T){}

	void foo(double){}

	int main()
	{
		foo(2);
		// we are calling foo() function with an int argument.

		// because of function template's return type is T::value_type,
		// there is no such thing as an int::value_type.
		// but because there is another overload it will not create a syntax error.
		// SFINAE (Substitution Failure Is Not An Error)

		// if we comment out [void foo(double);], there will be a syntax error.
		// syntax error happens because of there is no viable function left.

		// When substitution failure happens compiler will remove that template specialization
		// from Function Overload Resolution set.
	}
*/

/*
	template <typename T>
	void foo(T x)
	{
		std::cout << "template type T is " << typeid(T).name() << '\n';
	}
	
	void foo(int)
	{
		std::cout << "foo(int)\n";
	}
	
	int main()
	{
		foo(2.3);	// output -> template type T is double
		// void foo<double>(double)		-> exact match
		// void foo(int)			-> conversion
		// 2 overloads are viable.
	
		foo('A');	// output -> template type T is char
		// void foo<char>(char)			-> exact match
		// void foo(int)			-> promotion
		// 2 overloads are viable.
	
		foo(12);	// output -> foo(int)
		// void foo<int>(int)			-> exact match
		// void foo(int)			-> exact match	[Real function will be chosen]
		// 2 overloads are viable.
	}
*/

/*
	template <typename T>
	void func(T) = delete;
	
	void func(double);
	
	int main()
	{
		func(123);	// syntax error
		func(1.f);	// syntax error
		func(1u);	// syntax error
	
		func(12.3);
		// func() function can only be called with double argument.
	}
*/

/*
	template <typename T>
	void func(T)
	{
		std::cout << "func(T)\n";
	}
	
	template <typename T>
	void func(T*)
	{
		std::cout << "func(T*)\n";
	}
	
	template <typename T>
	void func(T**)
	{
		std::cout << "func(T**)\n";
	}
	
	int main()
	{
		int x{};
		func(&x);	// output -> func(T*)
	
		int* ptr{};
		func(&ptr);	// output -> func(T**)
		// 3 viable function specializations are viable.
	
		// generally more specific will be chosen
		// partial ordering rules applied.
	}
*/

/*
	template <typename T>
	void func(T)
	{
		std::cout << "func(T)\n";
	}
	
	template <typename T, int n>
	void func(T(&)[n])
	{
		std::cout << "func(T(&)[n])\n";
	}
	// more specific
	
	int main()
	{
		int a[10]{};
		func(a); // output -> func(T(&)[n])
		// 2 template specialization are viable in function overload resolution set
	}
*/

/*
	template <typename T>
	void baz(T&)
	{
		// T is int
	}
	
	template <typename T>
	void bar(T* p)
	{
		baz(*p);
		// T is int
	}
	
	template <typename T>
	void foo(T x)
	{
		bar(&x);
		// T is int
	}
	
	int main()
	{
		int x{ 2 };
		foo(x);
		// void foo<int>(int)  specialization
		// void bar<int>(int*) specialization
		// void baz<int>(int&) specialization
	
		// Those 3 specialization are created when foo(x) function called.
	}
*/

/*
	template <typename T>
	void Swap(T& r1, T& r2) noexcept
	{
		T temp{ std::move(r1) };
		r1 = std::move(r2);
		r2 = std::move(temp);
	}
*/

/*
	class Myclass {
	public:
		Myclass() = default;
		Myclass(const Myclass&) = default;
	
		Myclass& operator=(const Myclass&)
		{
			std::cout << "copy assignment called\n";
			return *this;
		}
		Myclass& operator=(Myclass&&)
		{
			std::cout << "move assignment called\n";
			return *this;
		}
	};
	
	Myclass foo()
	{
		Myclass x;
		return x;
	}
	
	const Myclass func()
	{
		Myclass x;
		return x;
	}
	
	int main()
	{
		Myclass x;
	
		x = foo();	// output -> move assignment called
		x = func();	// output -> copy assignment called
	
		// returning a const class object will choose copy assignment overload
		// because of the constness. It will inhibit move semantics.
	
		// DO NOT MAKE FUNCTIONS RETURN TYPE, A CONST CLASS OBJECT !!!
	}
*/

/*
	class Myclass {
	
	};
	
	void foo(const Myclass&)
	{
		std::cout << "const Myclass& called\n";
	}
	void foo(Myclass&&)
	{
		std::cout << "Myclass&& called\n";
	}
	
	int main()
	{
		Myclass m;
	
		Myclass&& r = std::move(m);
		// r objects data type is R value reference
		// r expression is an L value expression.
	
		foo(r);			// output -> const Myclass& called
		foo(std::move(r));	// output -> Myclass&& called
	}
*/

/*
	class Myclass {};
	
	Myclass foo()
	{
		Myclass x;
		return std::move(x); // no need to use std::move(x)
		// Pessimistic Move
	
		return x;	// NRVO(Named Return Value Optimization)
	}
*/

/*
	#include <vector>
	#include <list>
	
	template <typename Pos>
	void Print(Pos beg, Pos end)
	{
		while (beg != end) {
			std::cout << *beg << ' ';
			++beg;
		}
	
		std::cout << '\n';
	}
	// Pos need use in unequality comparison
	// Pos needs to be the operand of dereferencing operator.
	// Pos needs to be the operand of prefix increment operator.
	// *beg expression needs to be insertable to std output.
	
	int main()
	{
		using namespace std;
	
		int a[] = { 1,5,7,8,3,4 };
	
		Print(a, a + 6);				// output -> 1 5 7 8 3 4
		Print(a + 2, a + 6);				// output -> 7 8 3 4
		// Pos type will be int* (array decay)
	
		vector<int> ivec{ 4,6,5,3,2,3,5,6,4 };
		Print(ivec.begin(), ivec.end());		// output -> 4 6 5 3 2 3 5 6 4
	
		list<int> ilist{ 4,6,7,2,1,5 };
		// DoublyLink List(std::list) Data structure.
		Print(ilist.begin(), ilist.end());		// output -> 4 6 7 2 1 5
	}
*/

/*
	-------------------
	| class templates |
	-------------------
*/

/*
	template <typename T>
	class Myclass {
	
	};
	
	int main()
	{
		Myclass m;	// syntax error.
		// No specialization.
	
		Myclass<int> x;	// legal
	}
*/

/*
	template <typename T>
	class Myclass {
	
	};
	
	template <int n>
	class Someclass {
	
	};
	
	int main()
	{
	
		Myclass<int> m1;
		Myclass<double> m2;
		// Both specializations are different classes!
	
		m2 = m1; // syntax error.
		// E0349 no operator "=" matches these operands
	
		Someclass<10> s1;
		Someclass<12> s2;
		// Someclass<10> and Someclass<12> are different classes.
	
		s1 = s2; // syntax error
	}
*/

/*
	template <typename T>
	class Myclass {
	public:
		T foo(T);
		T func(T&&);
	
	private:
		T mx;
	};
	
	int main()
	{
		Myclass<int> m;
	
		m.foo(12);
		// when we call this function with an argument.
		// there won't be any type deduction happening.
		// Because T's type have already been found out
		// in [Myclass<int> m;] statement.
	
		// For Myclass<int> specialization.
		// [T func(T&&);] member functions parameter
		// is an R value reference NOT universal reference.
		// Because of no type deduction happening.
	}
*/

/*
	template <typename T, std::size_t n>
	class Myclass {
	public:
		std::size_t bar(T, int);
	
		typename T::value_type x;
		// if nested type we need to use typename keyword
	
	private:
		T ma[n];
	};
*/

/*
	template <typename T>
	class Myclass {
	public:
		T foo(T x)
		{
			// if we are defining member function INSIDE class template definition.
	
			Myclass<T> y1;
			Myclass y2;
			// Those 2 lines are same.
	
			// For Myclass<int> specialization
			// y1's data type is Myclass<int>
			// y2's data type is also Myclass<int>
		}
	
		T** func(T* x)
		{
			Myclass m;
		}
		// For Myclass<int> specialization
		// func functions parameter type is int*
		// func functions return type is int**
		// m local variables data type is Myclass<int>
	
		void bar()
		{
			Myclass x;
			Myclass<double> y;
			Myclass<T*> z;
	
			// We can also create different Myclass specialization objects.
	
			// For Myclass<int> specialization
			// x's data type is Myclass<int>
			// y's data type is Myclass<double>
			// z's data type is Myclass<int*>
		}
	private:
	};
*/

/*
	template <typename T>
	class Myclass {
	public:
		T foo(T);
		T bar(T);
		T baz(T)
	private:
	};
	
	// defining Myclass member functions outside of the class definition.
	
	template <typename T>
	T Myclass<T>::foo(T x)
	{
		return x;
	}
	
	template <typename T>
	T Myclass<T>::bar(T x)
	{
		return x;
	}
	// we always need to use [template <typename T>]
	// even if these functions defined for the same class template.
	
	template <typename T>
	T Myclass::baz(T x)	// syntax error
	{
		return x;
	}
	// using Myclass instead of Myclass<int>
	// as we did in the previous scenerio where we define member functions inside
	// class definition is not valid.
*/

/*
	template <typename T, typename U>
	class Myclass {
	public:
		Myclass foo(T, U ,Myclass);
	};
	
	// defining foo function outside of class definition
	
	template<typename T, typename U>
	Myclass<T, U> Myclass<T, U>::foo(T x, U y, Myclass<T, U> z)
	{
		Myclass<T, U> a;
	
		return z;
	}
	
	template<typename T, typename U>
	Myclass<T, U> Myclass<T, U>::foo(T x, U y, Myclass z)
	{
		Myclass<T, U> a;
		Myclass b;
		// Those 2 lines are same
	
		// we can also use Myclass instead of Myclass<T,U>
		return z;
	}
	// We can use Myclass instead of Myclass<T,U> in parameter variables.
	// as we did in z argument
	
	template<typename T, typename U>
	Myclass Myclass<T, U>::foo(T x, U y, Myclass z)	// syntax error
	{
		Myclass b;
		return z;
	}
	// We can not use Myclass instead of Myclass<T,U> in return type.
*/

/*
	template <typename T, typename U>
	class Myclass {
	public:
		T foo(U);
	};
	
	template < class A, class B>
	A Myclass<A, B>::foo(B bx)
	{
		std::cout << "foo() called\n";
		return A{};
	}
	
	template <typename T, typename U>
	T Myclass<T, U>::foo(U ux)
	{
		return T{};
	}
	// This 2 function definitions are same!!!!
	// We do not need to use the same name in template parameters
	
	int main()
	{
		Myclass<int, double> mx;
		mx.foo(2.4);
	}
*/

/*
	template <typename T>
	class Myclass {
	
	};
	
	Myclass<int> foo(Myclass<double>);
	// we can use class specializations as a parameter and return type of a function.
	
	class Someclass {
		Myclass<int> mx;
		Myclass<double *> my;
		// we can use class specializations as classes member variables.
	};
	
	template <typename T>
	class Yourclass {
	
	};
	
	int main()
	{
		Myclass<int> arr[210];
		Myclass<int>* p = arr;
	
		Yourclass<Myclass<int>> x;
		Myclass<Myclass<double>> y;
		// We can use a class specialization as a template argument.
	}
*/

/*
	class class_a {
	};
	
	template <typename T>
	class Myclass {
	public:
		void foo()
		{
			T tx;
			++tx;
			// if Myclass::foo() called because of class_a does not have an
			// operator++() overload it will be a syntax error
		}
	
		void bar()
		{
			T tx;
			tx.foo();
			// if Myclass::bar() called because of class_a does not have foo()
			// function it will be a syntax error.
		}
	};
	
	int main()
	{
		Myclass<class_a> m;
		// Because of class templates member functions are written by compiler
		// if we call that member function. There is no syntax error now.
	
		m.foo();	// syntax error
		// unary '++': 'T' does not define this operator or a conversion to a type
		// acceptable to the predefined operator
	
		m.bar();	// syntax error
		// 'foo': is not a member of 'class_a'
	}
*/

/*
	template <int n>
	class Myclass {
	
	};
	
	template <unsigned n>
	class Myclass {
	
	};
	
	// syntax error
	// 'Myclass': template parameter 'n' is incompatible with the declaration
*/

/*
	template <auto n>	// C++17
	class Myclass {
	public:
		Myclass()
		{
			std::cout << typeid(n).name() << '\n';
		}
	};
	
	int main()
	{
		Myclass<10> x;	// output -> int
		Myclass<20u> y;	// output -> unsigned int
	}
*/

/*
	// floating types added as an NTTP in C++20
	template <double n>
	class Myclass {
	
	};
*/

/*
	#include <array>
	#include <bitset>
	
	template <typename T, std::size_t n>
	struct Array {
	};
	
	int main()
	{
		double a[20];
		std::array<double, 20> arr;
	
		std::bitset<32> bs;
		// Only have 1 NTTP
	}
*/

/*
	// splitting implementation and interface 
	
	// scenerio 1
	//------------------------

	// first.h
	template <typename T>
	void func(T x);
	
	template <typename T, typename U>
	class Myclass {
		void foo(T);
	};
	// #include "firstimp.h"
	
	// firstimp.h
	template <typename T>
	void func(T x)
	{
		// code here...
	}
	
	template <typename T, typename U>
	class Myclass {
		void foo(T)
		{
			// code here...
		}
	};


	// scenerio 2
	//------------------------

	// first.h
	namespace first {
		template <typename T>
		void foo(T);

			namespace details {	// Nested namespace
				// implementations
			}
	}	
*/

/*
	template <int* p>
	class Myclass{
	
	};
	
	template<int& r>
	class Yourclass {
	
	};
	
	int x = 10;		// static storage duration object
	int y = 20;		// static storage duration object
	
	int main()
	{
		Myclass<&x> m1;
		Myclass<&y> m2;

		int l = 15;
		static int s = 20;

		Myclass<&l> m3; // syntax error		->	automatic storage duration object
		Myclass<&s> m4; // legal		->	static storage duration object 
	
		Yourclass<x> y1;
		Yourclass<y> y2;
	}
*/

/*
	template <int (*p)(int)>
	class Myclass {
	
	};
	
	int foo(int);
	int bar(int);
	int baz(int);
	
	int main()
	{
		Myclass<foo> m1;
		Myclass<bar> m2;
		Myclass<baz> m3;
	}
*/

/*
	template <typename T>
	class Myclass {
	public:
		void foo(Myclass);
		// foo functions parameter's type is Myclass<T>
	};
	
	int main()
	{
		Myclass<int> m1;
		Myclass<int> m2;
		Myclass<double> m3;
	
		m1.foo(m2);	// legal
		m1.foo(m3);	// syntax error.
		// we are sending Myclass<double> object to the foo function
		// which is expecting Myclass<int> type argument
	}
*/

/*
	template <typename T>
	class B {
	
	};
	
	class A {
	public:
		template <typename T>
		void foo(B<T>);
	};
	
	int main()
	{
		A ax;
	
		B<int> b1;
		B<double> b2;
	
		ax.foo(b1);	// legal
		ax.foo(b2); // legal
	}
*/

/*
	template <typename T>
	class Myclass {
	public:
		template <typename U>
		void foo(U)
		{
			std::cout << "type of *this = " << typeid(*this).name() << '\n';
			std::cout << "type of U = " << typeid(U).name() << '\n';
	
			std::cout << '\n';
		}
	};
	
	int main()
	{
		Myclass<int> m1;
	
		m1.foo(13.5);
		m1.foo(14);
		m1.foo("hello");
	
		// output ->
		// type of *this = class Myclass<int>
		// type of U = double
	
		// type of *this = class Myclass<int>
		// type of U = int
	
		// type of *this = class Myclass<int>
		// type of U = char const* __ptr64
	
		Myclass<long> m2;
		m2.foo(12L);
	
		// output->
		// type of *this = class Myclass<long>
		// type of U = long
	}
*/

/*
	template <typename T>
	class Myclass {
	public:
		template <typename U>
		void foo(Myclass<U> x)
		{
			std::cout << "type of *this = " << typeid(*this).name() << '\n';
			std::cout << "type of x = " << typeid(x).name() << '\n';
	
			std::cout << '\n';
		}
	};
	
	int main()
	{
		Myclass<int> m1;
		Myclass<long> m2;

		m1.foo(m2);
		// output ->
		// type of *this = class Myclass<int>
		// type of x = class Myclass<long>
	}
*/

/*
	struct Data {
		int a, b, c;
	};
	
	struct Data_2 {
	private:
		int a, b, c;
	};

	struct Myclass {
		int a[10];
	};
	
	int main()
	{
		Data mydata = { 1,4,6 };		// aggregate initialization
	
		Data_2 mydata = { 1,4,6 };		// syntax error
		// because of Data_2 has private data member it is not an aggregate type
		// aggregate initialization is not valid.

		Myclass mx = { 29, 32, 12, 3, 54, 2 };	// aggregate initialization
	}
*/

/*
	// std::array is an aggregate class

	#include <array>
	
	template <typename T, std::size_t n>
	struct Array {
		T a[n];
	};
	
	int main()
	{
		std::array<int, 5> x{ 1, 4, 52, 5, 6 };		// aggregate initialization
		Array<int, 6> y{ 1, 4, 52, 5, 6, 2 };		// aggregate initialization
	}
*/

/*
	// std::pair is an aggregate class

	#include <utility>
	#include <string>
	
	template <typename T, typename U>
	struct Pair {
		T first;
		U sencond;
	};
	
	std::pair<int, std::string> foo();
	// If we want to return 2 different types we can use std::pair
	
	int main()
	{
		std::pair<int, double> x;
		std::cout << x.first << '\n';			// output -> 0
		std::cout << x.second << '\n';			// output -> 0
		// default ctor is value initializing data members
	
		std::pair <int, std::string> p;
		std::cout << p.first << '\n';			// output -> 0
		std::cout << p.second.size() << '\n';		// output -> 0
		// string's default ctor will be called
		// when second data member(std::string) is value initialized 
		// in std::pair's default ctor.
	}
*/

/*
	#include <utility>
	#include <string>
	
	int main()
	{
		std::pair<int, double> p{ 1, 2.5 };
		// The ctor that has been called in here is
		// Pair(const T& x, const U& y)
	
		std::pair <std::string, double> px{ "hello", 2.3 };
		std::cout << px.first << '\n';	// output -> hello
		std::cout << px.second << '\n';	// output -> 2.3
	
		std::pair p_ctad{ 4, 5.4 };	// CTAD (Class Template Argument Deduction)
		// std::pair<int, double> p_ctad;
	}
*/

/*
	#include <utility>
	#include <string>
	
	template <typename T, typename U>
	struct Pair {
	public:
		Pair() = default;
		Pair(const T& t, const U& u) : first(t), second(u) {}
	
		template <typename A, typename B>	// member template
		Pair(const Pair<A, B>& other) : first(other.first), second(other.second){}

		// template <typename A, typename B>
		// Pair& operator=(const Pair<A, B>& other)
		// {
		// 	first = other.first;
		// 	second = other.second;
		// 	return *this;
		// }
		// for x = y assignment
	
		T first{};
		U second{};
	};
	
	int main()
	{
		std::pair<double, double> x{ 2., 6.5 };
		std::pair<int, int> y{ 18, 27 };
		x = y;	// valid
	
		Pair<double, double> a{ 2., 6.5 };
		Pair<int, int> b{ 18, 27 };
		a = b;	// valid
	
		std::pair<std::string, double> k;
		std::pair<const char*, int> l{ "hello", 27 };
		k = l;	// valid
	}
*/

/*
	template <typename T, typename U>
	struct Pair {
	public:
		Pair() = default;
		Pair(const T& t, const U& u) : first(t), second(u) {}
	
		template <typename A, typename B>	// member template
		Pair(const Pair<A, B>& other) : first(other.first), second(other.second) {}
		// conversion constructor
	
		T first{};
		U second{};
	};
	
	int main()
	{
		Pair<double, double> a{ 2., 6.5 };
		Pair<int, int> b{ 18, 27 };
		a = b;
	}
*/

/*
	template <typename T, typename U>
	std::pair<T, U> MakePair(const T& t, const U& u)
	{
		return std::pair<T, U>(t, u);
	}
	
	int main()
	{
		auto p  = MakePair(12, 4.5);
		// [MakePair(12, 4.5);] is PR value expression
	
		// before CTAD make_pair function template used for CTAD.
	}
*/

/*
	#include <utility>
	#include <string>
	
	template <typename T, typename U>
	std::ostream& operator<<(std::ostream& os, const std::pair<T, U>& p)
	{
		return os << '[' << p.first << ", " << p.second << ']';
	}
	
	int main()
	{
		using namespace std;
	
		pair<int, double> x{ 2,4.6 };
		cout << x << '\n';	// output -> [2, 4.6]
	
		string str{ "hello" };
		cout << make_pair(12, 5.6) << '\n';	// output -> [12, 5.6]
	
	
		cout << make_pair( make_pair(12, 5.6), make_pair(str,34L) ) << '\n';
		// output -> [[12, 5.6], [hello, 34]]
	}
*/

/*
	#include <utility>
	
	template <typename T, typename U>
	bool operator<(const std::pair<T, U>& lhs, const std::pair<T, U>& rhs)
	{
		return lhs.first < rhs.first || !(rhs.first < lhs.first) && lhs.second < rhs.second;
	}
	
	
	int main()
	{
		auto p1 = std::make_pair(1, 5);
		auto p2 = std::make_pair(1, 7);
	
		auto b1 = p1 < p2;
		std::cout << std::boolalpha << b1 << '\n';
	}
*/

/*
	#include <utility>
	#include <string>
	
	int main()
	{
		using namespace std;
	
		auto p = make_pair("hello", 12);
		// p.first type is const char*
	
		auto ps = make_pair("world"s, 12);
		ps = make_pair(operator""s("world", 6), 12);
		// ps.first type is std::string
		// user defined literal
	}
*/

/*
	#include <tuple>
	#include <string>
	
	int main()
	{
		std::tuple<int, std::string, long, char, double>;
	}
*/

/*
	#include <utility>
	#include <string>
	
	int main()
	{
		using namespace std;
	
		int a{ 45 };
		string name{ "hello" };
	
		pair<int, string> x{ a,name };
		x.first *= 10;
		x.second += " world";
	
		std::cout << "a = " << a << '\n';		// output -> a = 45
		std::cout << "name = " << name << '\n';		// output -> name = hello
	
		pair<int&, string&> y{ a,name };
		y.first *= 10;
		y.second += " world";
	
		std::cout << "a = " << a << '\n';		// output -> a = 450
		std::cout << "name = " << name << '\n';		// output -> name = hello world
	}
*/

/*
	----------------------
	| perfect forwarding |
	----------------------
*/

/*
	class Myclass{};
	
	void foo(Myclass&)
	{
		std::cout << "foo(Myclass&)" << '\n';
	}
	
	void foo(const Myclass&)
	{
		std::cout << "foo(const Myclass&)" << '\n';
	}
	
	void foo(Myclass&&)
	{
		std::cout << "foo(Myclass&&)" << '\n';
	}
	
	void foo(const Myclass&&)
	{
		std::cout << "foo(const Myclass&&)" << '\n';
	}
	
	void call_foo(Myclass& r)
	{
		foo(r);
	}
	
	void call_foo(const Myclass& r)
	{
		foo(r);
	}
	
	void call_foo(Myclass&& r)
	{
		foo(std::move(r));
	}
	
	void call_foo(const Myclass&& r)
	{
		foo(std::move(r));
	}
	
	
	// If foo() function have 2 parameters i need to write 16 call_foo() overloads
	// If foo() function have 3 parameters i need to write 64 call_foo() overloads
	
	template <typename T>
	void forward_foo(T&& r)
	{
		foo(std::forward<T>(r));
	}
	
	// If bar() function have 2 parameters
	template <typename T,typename U>
	void forward_bar(T&& t, U&& u)
	{
		bar(std::forward<T>(t), std::forward<U>(u));
	}
	
	// If func() function have n parameters
	template <typename ...Args>
	void forward_func(Args&& ...args)
	{
		func(std::forward<Args>(args)...);
	}
	
	int main()
	{
		Myclass mx;
		const Myclass cx;
		const Myclass ccx;
	
		foo(mx);			// output -> foo(Myclass&)
		foo(cx);			// output -> foo(const Myclass&)
		foo(Myclass{});			// output -> foo(Myclass&&)
		foo(std::move(ccx));		// output -> foo(const Myclass&&)
	
		// call_foo(mx);		// output -> foo(Myclass&)
		// call_foo(cx);		// output -> foo(const Myclass&)
		// call_foo(Myclass{});		// output -> foo(Myclass&&)
		// call_foo(std::move(cx));	// output -> foo(const Myclass&&)
	
		forward_foo(mx);		// output -> foo(Myclass&)
		forward_foo(cx);		// output -> foo(const Myclass&)
		forward_foo(Myclass{});		// output -> foo(Myclass&&)
		forward_foo(std::move(cx));	// output -> foo(const Myclass&&)
	}
*/

/*
	template <typename T>
	class Vector {
	public:
		void push_back(const T&);
		void push_back(T&&);	// R value reference not an universal reference.
	};

	template <typename T>
	class Myclass {
	public:
		void foo(T&&);		// foo()'s parameter is R value reference
	
		template <typename U>
		void func(U&&);		// func()'s parameter is universal reference
	};
	
	int main()
	{
		Myclass<int> m;
		int x{};
		int y{};
	
		m.foo(x);		// syntax error -> x' is not an R value.
		m.foo(std::move(x));	// legal
		m.func(y);		// legal
	}
*/

/*
	template <typename T>
	void bar(T&&);			// forwarding(universal) reference
	
	template <typename T>
	void baz(const T&&);		// NOT universal reference
	
	template <typename T>
	class Myclass {};
	
	template <typename T>
	void func(Myclass<T>&&);	// R value reference not a universal
	
	int main()
	{
		Myclass<int> x;
		func(x);		// syntax error
	
		auto&& x = 10;		// forwarding(universal) reference
	}
*/

/*
	---------------------------------
	| explicit(full) specialization |
	---------------------------------
*/

/*
	template <typename T>
	T Max(T x, T y)
	{
		return x > y ? x : y;
	}
	
	int main()
	{
		using namespace std;
	
		cout << Max(2, 3) << '\n';	// output -> 3
		cout << Max(3, 2) << '\n';	// output -> 3
	
		string s1{ "aaaa" }, s2{ "bbbb" };
		cout << Max(s1, s2) << '\n';	// output -> bbbb
		cout << Max(s2, s1) << '\n';	// output -> bbbb

		const char* p1{ "dddd" }, * p2{ "cccc" };
		cout << Max(p1, p2) << '\n';	// output -> cccc
		// in lexicographical compare dddd needs to be grater than cccc
		// for const char*, addresses are compared not dddd and cccc

		const char* p3{ "kkkk" }, * p4{ "llll" };
		cout << Max(p3, p4) << '\n';	// output -> llll
	}
*/

/*
	template <typename T>
	void func(T x)
	{
		std::cout << "primary template for type " << typeid(T).name() << '\n';
	}
	
	template < >	// diamond
	void func(int x)
	{
		std::cout << "explicit specialization for func<int>\n";
	}
	// [void func<int>(int x)] and [void func(int x)] are same
	
	int main()
	{
		func(2.4);	// output -> primary template for type double
		func(3.5f);	// output -> primary template for type float
		func(2u);	// output -> primary template for type unsigned int
		func(12);	// output -> explicit specialization for func<int>
	}
*/

/*
	template <typename T>
	void func(T)
	{
		std::cout << "1";
	}
	
	template < >
	void func(int*)
	{
		std::cout << "2";
	}
	
	template <typename T>
	void func(T*)
	{
		std::cout << "3";
	}
	
	// template < >
	// void func(int*)
	// {
	// 	std::cout << "4";
	// }
	
	int main()
	{
		int x{ 5 };
		func(&x);	// output -> 3
	
		// explicit specialization will not be in Function Overload Resolution Set.
		// In this scenerio only func(T) and func(T*) overloads are in Function Overload Resolution Set.
		// func(T*) will be chosen.
		// If func(T) overload  was chosen output will be 2
		// because func(int*) is explicit specialization for func(T) overload.
	
		// When we add func(int*) explicit specialization for func(T*) overload
		// new output will become 4.
	}
*/

/*
	template <typename T>
	class Myclass {
	public:
		Myclass()
		{
			std::cout << "primary template for type " << typeid(T).name() << '\n';
		}
	
		void foo(){}
	};
	
	template <>
	class Myclass<int> {
	public:
		Myclass()
		{
			std::cout << "explicit specialization for Myclass<int>\n";
		}
	
		void bar(){}
	};
	
	int main()
	{
		Myclass<char> m1;		// output -> primary template for type char
		Myclass<double> m2;		// output -> primary template for type double
		Myclass<int> m3;		// output -> explicit specialization for Myclass<int>
	
		m1.foo();
		m2.foo();
		m3.bar();
		// Myclass<T> primary template has a foo() function in its interface
		// Myclass<int> explicit specialization has bar() function in its interface
		// There interfaces can be different and it is perfectly valid.
	}
*/

/*
	template <typename T, typename U>
	class Myclass {
	public:
		Myclass()
		{
			std::cout << "primary template\n";
		}
	};
	
	template <>
	class Myclass<int, char> {
	public:
		Myclass()
		{
			std::cout << "Myclass<int,char> explicit specialization\n";
		}
	};
	
	int main()
	{
		Myclass<int, int> x1;	// output -> primary template
		Myclass<char, int> x2;	// output -> primary template
		Myclass<int, char> x3;	// output -> Myclass<int, char> explicit specialization
	}
*/

/*
	template <int n>
	class Myclass {
	public:
		Myclass()
		{
			std::cout << "primary template for n = " << n << '\n';
		}
	};
	
	template <>
	class Myclass<5> {
	public:
		Myclass()
		{
			std::cout << "Myclass<5> explicit specialization\n";
		}
	};
	
	int main()
	{
		Myclass<1> m1;	// output -> primary template for n = 1
		Myclass<3> m2;	// output -> primary template for n = 3
		Myclass<5> m3;	// output -> Myclass<5> explicit specialization
	}
*/

/*
	template <int n>
	struct Myclass : Myclass<n - 1> { // public inheritance
		Myclass()
		{
			std::cout << n << ' ';
		}
		// multi-level inheritance
	};
	
	template <>
	struct Myclass<0>{
		// base case for stopping recursivity.
	};
	
	int main()
	{
		Myclass<100> x; // compile time recursivity
	
		// 1 2 3 4 5 .....99 100
		// first base class object will become alive then derived class object.
		// for Myclass<2>'s ctor code to be executed (become alive) first Myclass<1> needs to become alive
	}
*/

/*
	// meta function is a class and its purpose is
	// calculating a value or a type in compile time
	
	template <int n>
	struct Factorial {
		static const int value = n * Factorial<n - 1>::value;
	};
	
	template <>
	struct Factorial<1> {
		static const int value = 1;
	};
	
	template <>
	struct Factorial<0> {
		static const int value = 1;
	};
	
	int main()
	{
		Factorial<12>::value;
	}
*/

/*
	#include <cstring>
	
	template <typename T>
	T Max(T x, T y)
	{
		return x > y ? x : y;
	}
	
	template <>
	const char* Max(const char* p1, const char* p2)
	{
		return strcmp(p1, p2) > 0 ? p1 : p2;
	}
	
	int main()
	{
		using namespace std;
	
		const char* p1{ "dddd" }, * p2{ "cccc" };
		cout << Max(p1, p2) << '\n';	// output -> dddd

		const char* p3{ "kkkk" }, * p4{ "llll" };
		cout << Max(p3, p4) << '\n';	// output -> llll
	}
*/

/*
	--------------------------
	| partial specialization |
	--------------------------
*/

/*
	partial specialization is valid for class templates.
	partial specialization is NOT VALID for function templates.
*/

/*
	template <typename T>
	class Myclass {
	public:
		Myclass()
		{
			std::cout << "Myclass primary template for type " << typeid(T).name() << '\n';
		}
	};
	
	template <typename T>
	class Myclass<T*> {
	public:
		Myclass()
		{
			std::cout << "Myclass partial specialization for<T*>\n";
		}
	};
	
	template <typename T>
	class Myclass<T[]> {
	public:
		Myclass()
		{
			std::cout << "Myclass partial specialization for<T[]>\n";
		}
	};
	
	template <typename T>
	class Myclass<T[5]> {
	public:
		Myclass()
		{
			std::cout << "Myclass partial specialization for<T[5]>\n";
		}
	};
	
	int main()
	{
		Myclass<int> m1;	// output -> Myclass primary template for type int
		Myclass<long> m2;	// output -> Myclass primary template for type long
		Myclass<char*> m3;	// output -> Myclass partial specialization for<T*>
		Myclass<int**> m4;	// output -> Myclass partial specialization for<T*>
		Myclass<int[]> m5;	// output -> Myclass partial specialization for<T[]>
		Myclass<long[5]> m7;	// output -> Myclass partial specialization for<T[5]>
	}
*/

/*
	template <typename T>
	struct ValCat {
		static constexpr const char* p = "PR value";
	};
	
	template <typename T>
	struct ValCat<T&> {
		static constexpr const char* p = "L value";
	};
	
	template <typename T>
	struct ValCat<T&&> {
		static constexpr const char* p = "X value";
	};
	
	int main()
	{
		using namespace std;
	
		cout << ValCat<int>::p << '\n';			// output -> PR value
		cout << ValCat<int&>::p << '\n';		// output -> L value
		cout << ValCat<int&&>::p << '\n';		// output -> X value
	
		cout << ValCat<decltype((12))>::p << '\n';	// output -> PR value
	
		int x{};
		int* ptr = &x;
		cout << ValCat<decltype((x))>::p << '\n';	// output -> L value
		cout << ValCat<decltype(ptr)>::p << '\n';	// output -> PR value
		cout << ValCat<decltype(*ptr)>::p << '\n';	// output -> L value
	}
*/

/*
	template <typename T, typename U>
	struct Myclass {
		Myclass()
		{
			std::cout << "primary\n";
		}
	};
	
	template <typename T>
	struct Myclass<T, T> {
		// this is a partial specialization
	
		Myclass()
		{
			std::cout << "partial<T,T>\n";
		}
	};
	
	template <typename T>
	struct Myclass<T, T*> {
		// this is a partial specialization
	
		Myclass()
		{
			std::cout << "partial<T,T*>\n";
		}
	};
	
	template <typename T>
	struct Myclass<T*, T*> {
		// this is a partial specialization
	
		Myclass()
		{
			std::cout << "partial<T*,T*>\n";
		}
	};
	
	int main()
	{
		Myclass<int, double> m1;	// output -> primary
		Myclass<int, int> m2;		// output -> partial<T,T>
		Myclass<int, int*> m3;		// output -> partial<T,T*>
		Myclass<int*, int*> m4;		// output -> partial<T*,T*>
	}
*/

/*
	#include <utility>
	#include <tuple>
	
	template <typename T>
	struct Myclass {
		Myclass()
		{
			std::cout << "primary template Myclass<T>\n";
		}
	};
	
	template <typename T, typename U>
	struct Myclass<std::pair<T, U>> {
		Myclass()
		{
			std::cout << "partial specialization Myclass<std::pair<T,U>>\n";
		}
	};
	
	template <typename T, typename U, typename K, typename L>
	struct Myclass<std::tuple<T, U, K, L>> {
		Myclass()
		{
			std::cout << "partial specialization Myclass<std::tuple<T,U,K,L>>\n";
		}
	};
	
	int main()
	{
		Myclass<int> x;
		// output -> primary template Myclass<T>
		Myclass<std::pair<int, long>> y;
		// output -> partial specialization Myclass<std::pair<T,U>>
		Myclass<std::tuple<int, long, char, int>> z;
		// output -> partial specialization Myclass<std::tuple<T,U,K,L>>
	}
*/

/*
	template <int base, int exp>
	struct Power {
		static const int value = base * Power<base, exp - 1>::value;
	};
	
	template <int base>
	struct Power<base,0> {
		static const int value = 1;
	};
	
	int main()
	{
		Power<2, 4>::value;	// 16
		Power<3, 9>::value;	// 19683
		Power<9, 5>::value;	// 59049
		// calculated in compile time.
	}
*/

/*

	// vector classes bool specaialization is partial specialization
	#include <vector>

	int main()
	{
		using namespace std;
	
		vector<int> x;
		vector<bool> y;
	
		y.flip();
		x.flip();	// no flip() function for vector<int> specialization
	}
*/

/*
	-------------------
	| alias templates |
	-------------------
*/

/*
	Typedef declerations
	-----------------------
	1. declare a variable from the type that you want to use as an alias
	2. add typedef keyword in front of the decleration
	3. change the variable identifier with the alias identifier.

	1. int x;
	2. typedef int x;
	3. tyedef int Word;

	1. int x[10];
	2. typedef int x[10];
	3. typedef int ar10[10] 

	1. int(*fp)(const char*, const char*);
	2. typedef int(*fp)(const char*, const char*);
	3. typedef int(*cmpfunc)(const char*, const char*);
*/

/*
	typedef int* IPTR;
	
	int main()
	{
		int x = 10;
		const IPTR p = &x;
		int* const ptr = &x;
		// These 2 lnes are same
		// p is top level const
	
		int y = 12;
		p = &y;	// syntax error(top-level const)
	}
*/

/*
	using declerations
	---------------------
	using cmpfunc = int(*)(const char*, const char*);
	using ipair = std::pair<int, int>;
*/

/*
	template <typename T>
	using Ptr = T*;
	// Ptr is template identifier.
	// Ptr<int> is a specialization.
	
	template <typename T>
	using ar10 = T[10];
	
	template <typename T, int n>
	using Array = T[n];
	
	int main()
	{
		Ptr<int> p = nullptr;
	
		double dval{};
		Ptr<double> dp = &dval;
	
		ar10<int> x;
		ar10<double> y;
	
		Array<int, 20> a;
		Array<char, 40> b;
	}
*/

/*
	template <typename T>
	using ipair = std::pair<T, int>;
	
	template <typename T>
	using eq_pair = std::pair<T, T>;
	
	int main()
	{
		ipair<long>;	// std::pair<long, int>
		ipair<char>;	// std::pair<char, int>
	
		eq_pair<long>;	// std::pair<long,long>
		eq_pair<int>;	// std::pair<int,int>
	}
*/

/*
	#include <set>
	
	template <typename K>
	using gset = std::set<K, std::greater<K>>;
	
	template <typename K>
	using lset = std::set<K, std::less<K>>;
	
	int main()
	{
		using namespace std;
	
		gset<int>;	// std::set<int, std::greater<int>>;
		lset<double>;	// std::set<double, std::less<double>>;
	}
*/

/*
	template <typename T>
	struct Myclass {
		using type = T*;
	};
	
	template <typename T>
	using Myclass_t = typename Myclass<T>::type;
	
	int main()
	{
		Myclass<int>::type;
		Myclass_t<int>;
		// These 2 lines are same.
	}
*/

/*
	#include <type_traits>
	
	template <typename T>
	using AddPointer_t = typename std::add_pointer<T>::type;
	
	int main()
	{
		using namespace std;
	
		add_pointer<int>::type;		// int*
		add_pointer<double>::type;	// double*
	
		AddPointer_t<int>;		// int*
		AddPointer_t<double>;		// double*
	}
*/

/*
	#include <type_traits>

	template <typename T, T n>
	struct IntegralConstant {
		constexpr T static value = n;
	};
	
	using TrueType = IntegralConstant<bool, true>;
	using FalseType = IntegralConstant<bool, false>;
	
	int main()
	{
		std::integral_constant<int, 5>::value;	// 5
	
		IntegralConstant<int, 5>::value;	// 5
		IntegralConstant<bool, true>::value;	// true
		IntegralConstant<bool, false>::value;	// true
	
		std::integral_constant<int, 5>::type;	// std::integral_constant<int, 5>
	
		std::true_type x;			// std::integral_constant<bool,true>
		std::cout << typeid(x).name() << '\n';
	
		std::false_type x;			// std::integral_constant<bool,false>
		std::cout << typeid(x).name() << '\n';
	}
*/

/*
	#include <type_traits>
	
	template <typename T>
	struct IsPointer : std::false_type {
	
	};
	
	template <typename T>
	struct IsPointer<T*> : std::true_type {
		// partial specialization
	};
	
	template <typename T>
	void func(T)
	{
		static_assert(IsPointer<T>::value);
	}
	
	int main()
	{
		IsPointer<int>::value;	// came from base class(std::false type)
		// bool, constexpr static data member,  false
	
		IsPointer<int>::value;	// false
		IsPointer<int*>::value;	// true
	
		func(12);	// static_assert failed: 'IsPointer<T>::value'
	
		int x{};
		func(&x);	// no syntax error
	}
*/

/*
	template <typename T = int>	// default template parameter
	class Myclass {
	
	};
	
	int main()
	{
		Myclass<double> m1;
	
		Myclass<> m2;
		Myclass<int> m3;
		// These 2 lines are same.
	}
*/

/*
	template <typename T = int, typename U>	// syntax error.
	class Myclass {
	
	};
	// After the last default template parameter,
	// It is not valid any template parameter that is NOT default template parameters.
*/

/*
	template <typename T = int, typename U = double>
	class Myclass {
	
	};
	
	int main()
	{
		Myclass<char, char> m1;
		Myclass<char> m2; // Myclass<char, double>
		Myclass<> m3; // Myclass<int, double>
	}
*/

/*
	template <typename T, typename = void>
	class Myclass {
	
	};
*/

/*
	template <typename >
	class Myclass;
	
	template <typename T>
	class Myclass<T*> {
		// full specialization.
	};
	
	int main()
	{
		Myclass<int> x;		// syntax error
		Myclass<int*> y;	// valid
	}
*/

/*
	template <typename T>
	void func(T&& x)	// universal reference
	{
		T&& y = x;
		// & - && -> &
		// reference collapsing - y's type will be int&
	}
	
	int main()
	{
		int ival{};
		func(ival);
		// because of ival is an L value,
		// T's type will be int&, x's type will be int&
	}
*/

/*
	----------------------
	| variable templates |
	----------------------
*/

/*
	template <typename T>
	constexpr auto pi = (T)3.14159265358979;
	// identification of template is pi
	
	int main()
	{
		pi<double>; // template specialization
		// pi<double> specialization's type is double.
		// pi<double> is constant expression.
	
		int a[pi<int>]{};
		int a[3]{};
		// These are same lines.
	}
*/

/*
	#include <type_traits>
	
	template <typename T>
	struct IsLValueReference : std::false_type {
	
	};
	
	template <typename T>
	struct IsLValueReference<T&> : std::true_type {
	
	};
	
	int main()
	{
		using namespace std;
	
		// is_lvalue_reference is a meta function(class)
		is_lvalue_reference<int&>::value;	// true
		is_lvalue_reference<int>::value;	// false
		is_lvalue_reference<int&&>::value;	// false
	
	
		IsLValueReference<int>::value;		// false
		// because of inherited from std::false_type,
		// if there is no partial specialization
		// every type specializations value will be false.
	
		IsLValueReference<int&>::value;		// true
		// because of partial specialization IsLValueReference<T&>
		// inherited from std::true_type
		// every L value reference specialization's value will be true.
	}
*/

/*
	#include <type_traits>
	
	template <typename T>
	struct IsLValueReference : std::false_type {
	
	};
	
	template <typename T>
	struct IsLValueReference<T&> : std::true_type {
	
	};
	
	template <typename T>
	class Refclass {
		static_assert(IsLValueReference<T>::value, "only for L value ref types");
	};
	
	
	int main()
	{
		Refclass<int> x;	// syntax error
		// error C2338: static_assert failed: 'only for L value ref types'
	
		Refclass<int&> y;	// valid
	}
*/

/*
	#include <type_traits>
	
	template <typename T>
	struct IsLValueReference : std::false_type {
	
	};
	
	template <typename T>
	struct IsLValueReference<T&> : std::true_type {
	
	};
	
	// instead of using (IsLValueReference<T>::value) value type
	// we can create a variable template named IsLValueReference_v
	// and use IsLValueReference_v<T>
	
	template <typename T>
	constexpr bool IsLValueReference_v = IsLValueReference<T>::value;
	
	
	
	template <typename T>
	class Refclass {
		static_assert(IsLValueReference_v<T>, "only for L value ref types");
	};
	
	int main()
	{
		Refclass<int> x;	// syntax error
		// error C2338: static_assert failed: 'only for L value ref types'
	
		Refclass<int&> y;	// valid
	}
*/

/*
	#include <type_traits>
	
	template <typename T>
	void func(T x)
	{
		using namespace std;
	
		static_assert(is_pointer_v<T> || is_reference_v<T>, "only pointer or reference types!!");
	}
	
	int main()
	{
		func(12);	// func(int) syntax error
		// error C2338: static_assert failed: 'only pointer or reference types!!'
	
		int ival{};
		func(&ival);	// func(int*) valid.
	}
*/

/*
	#include <type_traits>
	// meta function -> std::enable_if
	
	template<bool b, typename T = void>
	struct EnableIf {
	
	};
	
	template <typename T>
	struct EnableIf<true, T>
	{
		using type = T;
	};
	// partial specialization
	
	
	int main()
	{
		using namespace std;
	
		EnableIf<true, double>::type;				// double
		EnableIf<true, char>::type;				// char
		EnableIf<false, char>::type;				// syntax error no type
	
		EnableIf<is_pointer_v<int*>, double>::type;		// true.
		// is_pointer_v<int*> is true
		EnableIf<is_pointer_v<int>, double>::type;		// syntax error
		// is_pointer_v<int> is false so EnableIf<false,double> does not have ::type
	
		std::enable_if<is_pointer_v<int*>>::type;
		std::enable_if_t<is_pointer_v<int*>>;			// void
		std::enable_if_t<is_pointer_v<int*>,double>;		// double
		// These 2 lines are same
		// enable_if_t is an alias template.
	}
*/

/*
	#include <type_traits>
	
	template <typename T>
	std::enable_if_t<std::is_pointer_v<T>> func(T x);
	// if T's type is pointer type
	// func() functions return type will be void
	
	template <typename T>
	std::enable_if_t<std::is_pointer_v<T>,T> foo(T x);
	// foo() functions return type will be T
	
	void foo(double);
	
	int main()
	{
		func(12);	// syntax error
		// func() functions will be removed from Function Overload Set.
	
		foo(12);	// valid
		// std::enable_if_t<std::is_pointer_v<T>> func(T x); will removed from
		// function overload set (SFINAE'd out) but there is another overload.
	}
*/

/*
	#include <type_traits>
	
	template <typename T, typename U = std::enable_if_t<std::is_pointer_v<T>>>
	void func(T x);
	
	int main()
	{
		func(12);	// func() is SFINAE'd out. No more overloads -> syntax error
	
		int ival{};
		func(&ival);	// valid
	}
*/

/*
	#include <type_traits>
	
	template <typename T>
	void func(T x, std::enable_if_t<std::is_pointer_v<T>>* = nullptr);
	
	// std::enable_if_t<std::is_pointer_v<T>> expression will be syntax error
	// or if not syntax error it will be void type
	
	int main()
	{
		int x{};
		func(&x);	// valid
	
		func(10);	// syntax error [SFINAE'd out]
	}
*/

/*
	#include <type_traits>
	
	template <typename T>
	std::enable_if_t<std::is_integral_v<T>> func(T x);
	
	int main()
	{
		func(12.43);	// syntax error
		func(12);	// valid
		func(true);	// valid
		func('a');	// valid
	
		// if std::is_integral_v<T> is true
		// std::enable_if_t<true> will not be a syntax error becuase it has ::type
		// if std::is_integral_v<T> is false (when T is not an integral type)
		// std::enable_if_t<false> will be syntax error because it does not have ::type
	}
*/

/*
	#include <type_traits>
	
	template <typename T, typename U>
	struct IsSame : std::false_type {
	
	};
	
	template <typename T>
	struct IsSame<T,T> : std::true_type{};
	// partial specialization
	
	template <typename T, typename U>
	constexpr bool IsSame_v = IsSame<T, U>::value;
	// variable template
	
	template <typename T>
	void func(T)
	{
		static_assert(std::is_same_v<T, int>);
	}
	
	int main()
	{
		func(1.23);	// syntax error
		func(12);	// valid
	
		IsSame_v<int,double>;	// false
		IsSame_v<int, int>;	// true
	}
*/

/*
	#include <type_traits>
	
	// type transformation meta functions implementation.
	
	// template <typename T>
	// std::remove_reference_t<T> func(T);
	
	
	template <typename T>
	struct RemoveReference {
		using type = T;
	};
	
	template <typename T>
	struct RemoveReference<T&> {
		using type = T;
	};
	// partial specialization
	
	template <typename T>
	struct RemoveReference<T&&> {
		using type = T;
	};
	// partial specialization
	
	template<typename T>
	using RemoveReference_t = typename RemoveReference<T>::type;
	// alias template
	
	template <typename T>
	RemoveReference_t<T> func(T);
	
	int main()
	{
		RemoveReference_t<int&>;	// int
		RemoveReference_t<int&&>;	// int
	
	
		int a = 12;
		int& r = a;
		func(r);		// returns int
	
		int&& rref = 15;
		func(rref);		// returns int.
	}
*/

/*
	----------------------
	| variadic templates |
	----------------------
*/

/*
	// template parameter pack
	template <typename ...Ts>
	class Myclass {
	
	};
	
	int main()
	{
		Myclass<int> m1;
		Myclass<long, double> m2
		Myclass<int, double,int> m3;
	}
*/

/*
	template <typename ...Ts>
	void func(Ts ... args);	// pack expansion
	
	template <typename T, typename U, typename W>
	void func(T t, U u, W w);
	
	int main()
	{
		func(12, 34L, 4.5);
		// Both func functions are same for [func(12, 34L, 4.5)] statement.
	}
*/

/*
	template <typename T, typename ...Ts>
	void func(T x, Ts ...args)
	{
	
	}
	
	int main()
	{
		func(12, 34L, 4.5);
		// 2 arguments in template parameter pack.
	}
*/

/*
	class Myclass {
	private:
		int mx, my;
	};
	
	template <typename ...Ts>
	void func(Ts ...args)
	{
		constexpr std::size_t x = sizeof...(args);
		constexpr std::size_t y = sizeof...(Ts);
	
		std::cout << "sizeof...(args) = " << x << '\n';
		std::cout << "sizeof...(Ts) = " << y << '\n';
	}
	
	int main()
	{
		func(12, 34L, 4.5, Myclass{});
		// output ->
		//	sizeof...(args) = 4
		//	sizeof...(Ts) = 4
	
		func(12, "hello");
		// output ->
		//	sizeof...(args) = 2
		//	sizeof...(Ts) = 2
	
		func();
		// output ->
		//	sizeof...(args) = 0
		//	sizeof...(Ts) = 0
	}
*/

/*
	template <typename T,typename ...Ts>
	void func(T t, Ts ...args)
	{
		constexpr std::size_t x = sizeof...(args);
		constexpr std::size_t y = sizeof...(Ts);
	
		std::cout << "sizeof...(args) = " << x << '\n';
		std::cout << "sizeof...(Ts) = " << y << '\n';
	}
	
	int main()
	{
		func(12, 34L, 4.5);
		// output ->
		//	sizeof...(args) = 2
		//	sizeof...(Ts) = 2
	}
*/

/*
	template <typename ...Ts>
	void func(Ts ...args)
	{
	
	}
	
	int main()
	{
		func<int, long, double>('a', 34L, 4.5f);
		// we can explicitly declare template arguments types.
		// implicit conversion will be happen here.
	}
*/

/*
	#include <string>
	
	template <typename ...Ts>
	void func(Ts& ...args);
	
	int main()
	{
		int x{};
		double dval;
		std::string str{ "hello" };
	
		func(x, dval, str);
		// functions parameters will be int&, double&, std::string&
	}
*/

/*
	#include <string>
	
	template <typename ...Ts>
	void func(Ts&& ...args);	// universal(forwarding) reference
	
	template <typename T, typename U, typename W>
	void func(T&& t, U&& u, W&& w );
	
	int main()
	{
		int x{};
		double dval;
		std::string str{ "hello" };
	
		func(x, dval, str);
		// functions parameters will be int&, double&, std::string&
		// Both functions are same for this function call.
	}
*/

/*
	#include <tuple>
	
	template <typename ...Ts>
	class Tuple {
	
	};
	
	int main()
	{
		Tuple<int> t1;
		Tuple<int, double> t2;
		Tuple<int, int, long> t3;
	
		std::tuple<int> st1;
		std::tuple<int, double> st2;
		std::tuple<int, int, long> st3;
	}
*/

/*
	template <int ...n>
	class Myclass {
	
	};
	
	int main()
	{
		Myclass<1> m1;
		Myclass<1, 3> m2;
		Myclass<1,3,5,8> m3;
		// template parameter pack can be from NTTP's (Non Type Template Parameter)
	}
*/

/*
	------------------
	| pack expansion |
	------------------
*/

/*
	void foo(int a, double b, long c)
	{
		std::cout << "a = " << a << '\n';
		std::cout << "b = " << b << '\n';
		std::cout << "c = " << c << '\n';
	}
	
	template <typename ...Ts>
	void func(Ts ...args)
	{
		foo(args ...);
		// p1, p2, p3 (pack expension)
	}
	
	template <typename T, typename U, typename W>
	void bar(T t, U u, W w)
	{
		foo(t, u, w);
	}
	
	int main()
	{
		func(12, 26.3, 75L);
		// output ->
		//	a = 12
		//	b = 26.3
		//	c = 75
	
		bar(12, 26.3, 75L);
		// func and bar functions acts same.
	}
*/

/*
	template <typename ...Ts>
	void func(Ts ...args)
	{
		int arr[] = { args ... };
	
		for (auto val : arr)
			std::cout << val;
	}
	
	int main()
	{
		func(1, 2, 7, 8);	// output -> 1278
	}
*/

/*
	void foo(int x, int y, int z)
	{
		std::cout << "x = " << x << '\n';
		std::cout << "y = " << y << '\n';
		std::cout << "z = " << z << '\n';
	}
	
	template <typename ...Ts>
	void func(Ts& ...args)
	{
		foo(++args...);
		// foo(++p1, ++p2, ++p3);
	}
	
	int main()
	{
		int x = 10;
		int y = 15;
		int z = 20;
	
		func(x, y, z);
		// output ->
		//	x = 11
		//	y = 16
		//	z = 21
	}
*/

/*
	#include <tuple>
	
	template <typename ...Ts>
	void func(Ts ...args)
	{
		std::tuple<Ts...> x;
		std::cout << typeid(x).name() << '\n';
	}
	
	int main()
	{
		func(1, 4, 3, 6);
		// output -> class std::tuple<int,int,int,int>
	
		func(1, 4.2, 3L, 6.f, "hello");
		// output -> class std::tuple<int,double,long,float,char const * __ptr64>
	}
*/

/*
	#include <tuple>
	
	template <typename ...Ts>
	void func(Ts ...args)
	{
		std::tuple<Ts...> x(args...);
		// std::tuple<int, int, int> x(p1, p2, p3);
		// These 2 lines are same
	}
	
	int main()
	{
		func(1, 4, 3);
	}
*/

/*
	#include <tuple>
	
	template <typename ...Ts>
	void bar(Ts ...)
	{
		std::tuple<Ts...> x;
		std::cout << typeid(x).name() << '\n';
	}
	
	template <typename ...Ts>
	void func(Ts ...args)
	{
		bar(&args...);
		// bar(&p1, &p2, &p3);
		// These 2 lines are same.
	}
	
	int main()
	{
		func(1, 4.5, 6.f);
		// output -> class std::tuple<int *,double *,float *>
	}
*/

/*
	template <typename ...Ts>
	void func(Ts ...args)
	{
		bar(args)...;
		// bar(p1), bar(p2), bar(p3), bar(p4);
		// Those 2 line are same for [func(1, 2.3, 6L, 6.5f);] statement
	}
	
	int main()
	{
		func(1, 2.3, 6L, 6.5f);
	}
*/

/*
	template <typename ...Ts>
	void func(Ts ...args)
	{
		foo<Ts>(args)...;
		// foo<int>(p1), foo<double>(p2), foo<long>(p3), foo<float>(p4)
		// Those 2 line are same for [func(1, 2.3, 6L, 6.5f);] statement
	}
	
	int main()
	{
		func(1, 2.3, 6L, 6.5f);
	}
*/

/*
	#include <memory>
	
	template <typename ...Ts>
	class Myclass {
	public:
		Myclass(Ts ...args)
		{
			std::cout << sizeof...(args);
		}
	};
	
	template <typename T, typename ...Ts>
	std::unique_ptr<T> MakeUnique(Ts&& ...args)
	{
		return std::unique_ptr<T>(new T(std::forward<Ts>(args)...));
	}
	
	int main()
	{
		auto ptr = MakeUnique<Myclass<int,int>>(1,2);
	
		// make_unique<Myclass>(x, y, z);
		// perfect forwarding arguments to Myclass's ctor and returning a unique pointer.
	}
*/

/*
	// C Code (change the extension to .c)
	// remove #include <iostream>

	#include <stdarg.h>
	#include <stdio.h>
	
	int sum(int n, ...)
	{
		va_list args;
		va_start(args, n);
	
		int sum = 0;
	
		for (int i = 0; i < n; ++i)
		{
			sum += va_arg(args, int);
		}
	
		va_end(args);
	
		return sum;
	}
	
	int main()
	{
		printf("%d\n", sum(4, 1, 5, 7, 9));
	}

	// Disadvantages
	// ------------------
	// If we sent double in one of our parameter, it will cause Undefined Behaviour(UB).
	// We need to send the number of the parameters(first parameter) to the function other arguments.
*/

/*
	template <typename ...Ts>
	class Var {
	public:
		Var()
		{
			std::cout << typeid(*this).name() << '\n';
			std::cout << typeid(Var).name() << '\n';
		}
	};
	
	template <typename ...Types>
	class Myclass : public Var<Types...> {
	public:
		constexpr static size_t size = sizeof...(Types);
	};
	
	int main()
	{
	
		Myclass<int, double, long> m;
		// output ->
		//	class Var<int,double,long>
		//	class Var<int,double,long>
	
		constexpr auto size_value = Myclass<int, double>::size;
		// Myclass<int,double> specialization will inherit
		// from Var<int,double> specialization.
	}
*/

/*
	template <typename ...Ts>
	class Var {
	public:
		Var()
		{
			std::cout << typeid(*this).name() << '\n';
		}
	};
	
	template <typename ...Types>
	class Myclass : public Var<Types*...> {
	public:
		constexpr static size_t size = sizeof...(Types);
	};
	
	int main()
	{
		Myclass<int, long, double> m;
		// output -> class Var<int *,long *,double *>
	}
*/

/*
	struct X {
		X(int i)
		{
			std::cout << "X(int i) i = " << i << '\n';
		}
	};
	
	struct Y {
		Y(int i)
		{
			std::cout << "Y(int i) i = " << i << '\n';
		}
	};
	
	struct Z {
		Z(int i)
		{
			std::cout << "Z(int i) i = " << i << '\n';
		}
	};
	
	template <typename ...Types>
	class A : public Types ... {	// multiple inheritence [class A : public X, Y, Z]
	public:
		A() : Types{ 0 }...
		{
	
		}
	};
	
	class B : public X, Y, Z{
	public:
		B() : X{ 1 }, Y{ 1 }, Z{ 1 } {}
	};
	
	int main()
	{
		A<X, Y, Z> ax;
		// output ->
		//	X(int i) i = 0
		//	Y(int i) i = 0
		//	Z(int i) i = 0
	
		B bx;
		// output ->
		//	X(int i) i = 1
		//	Y(int i) i = 1
		//	Z(int i) i = 1
	}
*/

/*
	#include <tuple>
	
	template <typename T>
	void print_type(const T&)
	{
		std::cout << typeid(T).name() << '\n';
	}
	
	template <class A, class B, class ...Ts>
	void func(A arg1, B arg2, Ts ...pack)
	{
		std::tuple <A, B, Ts...> t1;
		print_type(t1);
		// output -> class std::tuple<int,float,double,long,char>
	
		std::tuple<Ts..., A, B> t2;
		print_type(t2);
		// output -> class std::tuple<double,long,char,int,float>
	
		std::tuple<A, Ts..., B> t3;
		print_type(t3);
		// output -> class std::tuple<int,double,long,char,float>
	}
	
	int main()
	{
		func(1, 1.2f, 3.4, 4L, 'A');
		// int, float, double, long, char
		// A -> int
		// B -> float
		// Ts... -> double, long, char
	}
*/

/*
	template <size_t ...n>
	struct A {
		A()
		{
			std::cout << typeid(A).name() << '\n';
		}
	};
	
	template <size_t ...n>
	void func()
	{
		A<n...> ax;
	}
	
	int main()
	{
		func<1, 3, 7, 9>();	// output -> struct A<1,3,7,9>

		// parater pack can be Non type parameter pack. 
	}
*/

/*
	template <typename T>
	void func(T&)
	{
		std::cout << __FUNCSIG__ << '\n';
	}
	
	template <typename T>
	void foo(T)
	{
		std::cout << __FUNCSIG__ << '\n';
	}
	
	int main()
	{
		int ar[10]{};
	
		func(ar);
		// output -> void __cdecl func<int[10]>(int (&)[10])
	
		foo(ar);
		// output -> void __cdecl foo<int*>(int *)
	}
*/

/*
	template <typename ...TS>
	void func(int, TS...)
	{
		std::cout << __FUNCSIG__ << '\n';
	}
	
	int main()
	{
		func(1, 3.4, 8.F, "hello");
		// output -> void __cdecl func<double,float,const char*>(int,double,float,const char *)
		// function template func has a
		// func<double, float, const char*> specialization
	}
*/

/*
	template <typename... Types, int... N>
	void func(Types(&...args)[N])
	{
		std::cout << __FUNCSIG__ << '\n';
	}
	
	int main()
	{
		int a[2]{};
		char b[3]{};
		long c[5]{};
		double d[7]{};
	
		func(a, b, c, d);
		// void __cdecl func<int,char,long,double,0x2,0x3,0x5,0x7>(int (&)[2],char (&)[3],long (&)[5],double (&)[7])
	}
*/

/*
	HOW TO USE VARIADIC TEMPLATE PARAMETERS ONE BY ONE?
	----------------------------------------------------
	1. compile-time recursivity (eksiltme teknigi)
	2. init_list 
	3. fold expressions	(katlama ifadeleri)	[C++17]
	4. static if	[C++17]
*/

/*
	#include <bitset>
	#include <string>
	
	template <typename T>
	void print(const T& r)
	{
		std::cout << r << '\n';
	}
	
	template <typename T, typename ...Ts>
	void print(const T& r, const Ts& ...args)
	{
		print(r);
		print(args...);
	}
	
	int main()
	{
		int x = 10;
		double d = 23.5;
	
		std::string str{ "around the world" };
	
		print(str, x, d, 9L, "hello", std::bitset<16>(45u));
		// output ->
		//	around the world
		//	10
		//	23.5
		//	9
		//	hello
		//	0000000000101101
	}
*/

/*
	#include <string>
	
	template <typename T>
	T sum(const T& t)
	{
		return t;
	}
	
	template <typename T, typename ...Ts>
	T sum(const T& t, const Ts&... args)
	{
		return t + sum(args...);
	}
	
	int main()
	{
		std::cout << sum(1, 3, 5, 7, 9) << '\n';	// output -> 25
	
		std::string s1{ "he" }, s2{ "llo " }, s3{ "wor" }, s4{ "ld" };
		std::cout << sum(s1, s2, s3, s4) << '\n';	// output -> hello world
	}
*/

/*
	int main()
	{
		int ar[]{ 1,2,3,4,5 };
		std::cout << sizeof(ar) / sizeof(&ar) << '\n';		// output -> 5
	
		int ar_2{ (1, 2, 3, 4, 5) };
		std::cout << sizeof(ar_2) / sizeof(&ar_2) << '\n';	// output -> 1
	
		//---------------------
	
		int x = 10;
		int y = 20;
		int z{};
	
		x++, y = ++x , z = x + y;	// comma operator will create sequece point
	
		std::cout << "x = " << x << '\n';	// output -> x = 12
		std::cout << "y = " << y << '\n';	// output -> y = 12
		std::cout << "z = " << z << '\n';	// output -> z = 24
	
		//---------------------
	
		int a = 10;
		int b = 33;
		int c{};
	
		c = (a, b);
		std::cout << "c = " << c << '\n';	// output -> c = 33
		c = (b, a);
		std::cout << "c = " << c << '\n';	// output -> c = 10
	}
*/

/*
	#include <initializer_list>
	
	template <typename ...Ts>
	void Print(const Ts&... args)
	{
		int a[] = { ((std::cout << args << '\n'), 0)... };
		// {((std::cout << p1 << '\n'), 0)...},
		// {((std::cout << p2 << '\n'), 0)...},
		// {((std::cout << p3 << '\n'), 0)...},
	
		// It is better using temp initializer_list object
		// instead of using C style array.
	
		(void)std::initializer_list<int> { ((std::cout << args << '\n'), 0)... };
		// temporary std::initializer_list<int> object created
		// and cast to void to declare that we do not use this temp object.
	}
	
	int main()
	{
		Print(2, 3.4, 7L, "hello");
		// output ->
		//	2
		//	3.4
		//	7
		//	hello
	}
*/

/*
	// unary left fold
	template <typename ...TS>
	auto unary_left_fold_sum(const TS&... args)
	{
		return (... + args);
		// return (((p1 + p2) + p3) + p4) + p5	[left associative]
	}
	
	// unary right fold
	template <typename ...TS>
	auto unary_right_fold_sum(const TS&... args)
	{
		return (args + ...);
		// return p1 + (p2 + (p3 + (p4 + p5)))	[right associative]
	}
	
	int main()
	{
		std::cout << unary_left_fold_sum(1, 3, 5, 7, 9, 11) << '\n';	// output -> 36
		std::cout << unary_right_fold_sum(1, 3, 5, 7, 9, 11) << '\n';	// output -> 36
	}
*/

/*
	// unary left fold
	template <typename ...Ts>
	auto sum_left(Ts... args)
	{
		return (... + args);
	}
	
	// unary right fold
	template <typename ...Ts>
	auto sum_right(Ts... args)
	{
		return (args + ...);
	}
	
	int main()
	{
		using namespace std::literals;
	
		auto x = sum_left(1, 3, 5, 7, 9);
		std::cout << "x = " << x << '\n';
		auto y = sum_right(1, 3, 5, 7, 9);
		std::cout << "y = " << y << '\n';
	
		auto sx = sum_left("hello"s, " world ", "i am a ", "robot");
		// ((std::string + const char*) + const char*) + const char*
		std::cout << "sx = " << sx << '\n';
	
		auto sy = sum_right("hello", " world ", "i am a ", "robot"s);
		// const char* + (const char* + (const char* + std::string))
		std::cout << "sy = " << sy << '\n';
	
		// const char* +  const char* -> syntax error
		// adding two pointers is syntax error
		// std::string + const char* -> std::string
	}
*/

/*
	// unary fold for comma(,) operator
	
	void f(int i)
	{
		std::cout << i << ' ';
	}
	
	template <typename ...Ts>
	void call(Ts... ts)
	{
		(f(ts), ...);
		// f(p1), (f(p2),  (f(p3), (f(p4), f(p5))))
	}
	
	int main()
	{
		call(4, 1, 6, 4, 8, 10);	// output -> 4 1 6 4 8 10
	}
*/

/*
	template <typename ...Ts>
	bool all(Ts... args)
	{
		return (... && args);	// unary left fold for &&(logical and) operator
	}
	
	int main()
	{
		std::cout << std::boolalpha;
		std::cout << all(true, true, true, true) << '\n';	// output -> true
		// (((true && true) && true) && true
		std::cout << all(true, true, true, false) << '\n';	// output -> false
		// (((true && true) && true) && false
	}
*/

/*
	template <typename ...Args>
	auto fdiv_r(Args&&... args)
	{
		return (args / ...);	// unary right fold for (/) operator
	}
	
	template <typename ...Args>
	auto fdiv_l(Args&&... args)
	{
		return (... / args);	// unary left fold for (/) operator
	}
	
	int main()
	{
		std::cout << fdiv_r(500, 50, 5, 2) << '\n';	// output -> 20
		// 500 / (50 / (5 / 2));
		std::cout << fdiv_l(500, 50, 5, 2) << '\n';	// output -> 1
		// ((500 / 50) / 5) / 2;
	}
*/

/*
	template <typename T, typename ...TS>
	auto sum(T init, TS... args)
	{
		return (init + ... + args); // binary left fold for (+) operator.
	}
	
	int main()
	{
		int ival = 100;
	
		std::cout << sum(ival, 1, 3, 5, 6);	// output -> 115
		// (((ival + 1) + 3) + 5) + 6
	}
*/

/*
	template <typename... Ts>
	int substract(int num, Ts... args)
	{
		return (num - ... - args); // binary left fold for (-) operator
	}
	
	int main()
	{
		int result = substract(100, 50, 20, 7);
		// ((100 - 50) - 20) - 7
		std::cout << "result = " << result << '\n';	// output -> result = 23
	}
*/

/*
	#include <bitset>
	#include <utility>
	
	template <typename ...Args>
	void fprintf(Args&& ...args)
	{
		(std::cout << ... << std::forward<Args>(args)) << '\n';
		// binary left fold for (<<) operator [init (op) ... (op) pack]
		// init -> std::cout
	
		// (((std::cout << p1) << p2) << p3) << p4
	}
	
	int main()
	{
		std::string str{ "hello" };
		std::bitset<8> bs{ 15u };
	
		fprintf(str, 12, 4.5, "World", bs);
		// output -> hello124.5World00001111
	}
*/

/*
	template <typename ...Args>
	auto sum(Args&&... args)
	{
		return (std::forward<Args>(args) + ... + 10);
		// binary right fold for (+) operator
		// init -> 10
	}
	
	int main()
	{
		std::cout << sum(12, 4.5, 50L) << '\n';	// output -> 76.5
		// 12 + (4.5 + (50L + 10))
	}
*/

/*
	template <typename T>
	void func(T x)
	{
		if constexpr (expr)
		{
			// expr needs to be a constant expression
		}
	}
*/

/*
	template <typename T>
	void func(T x)
	{
		if constexpr (sizeof(T) > 4)
		{
			// sizeof() operator is compile time constant.
	
			++x;
			// because of Myclass{} objects size is 1
			// ++x statement will not be written (not compiled by compiler!!)
		}
	
		// func() will be an empty functions for func(Myclass{}) call.
	}
	
	class Myclass {};
	
	int main()
	{
		func(Myclass{});
	}
*/

/*
	template <typename T>
	void func(T x)
	{
		if constexpr (sizeof(T) < 4)
		{
			++x;
			// because of there is not operator++ overload in Myclass
			// this code will be a syntax error!!
		}
	}
	
	class Myclass {};
	
	int main()
	{
		func(Myclass{});
	}
*/

/*
	#include <type_traits>
	
	template <typename T>
	void func(T x)
	{
		if constexpr (std::is_integral_v<T>)
		{
			++x;
		}
		else {
			x.foo();
		}
	}
	
	//	void func<int>(int x)
	//	{
	//		++x;
	//	}
	//	// The func function that compiler will write is like this..
	
	class Myclass {};
	
	int main()
	{
		func(12);	// VALID
		// because of if constexpr code will be compiled.
		// but else block is no compiled by compiler!!!
	}
*/

/*
	#include <type_traits>
	
	template <typename T>
	void func(T x)
	{
		if constexpr (std::is_integral_v<T>)
		{
			++x;
		}
		else {
			x.foo();
		}
	}
	
	class Myclass {};
	
	int main()
	{
		func(2.3); // syntax error!!
	}
*/

/*
	#include <type_traits>
	
	template <typename T>
	void func(T x)
	{
		if constexpr (std::is_integral_v<T>)
		{
			++x;
		}
		else if constexpr (sizeof(T) > 4)
		{
			// code
		}
	}
	// else if constexpr needs to be used not else if
*/

/*
	#include <string>
	#include <type_traits>
	
	template <typename T>
	std::string as_string(T x)
	{
		if constexpr (std::is_same_v<T, std::string>) {
			return x;
		}
		else if constexpr (std::is_arithmetic_v<T>) {
			return std::to_string(x);
		}
		else {
			return std::string(x);
		}
	}
	
	int main()
	{
		std::cout << as_string(42) << '\n';
		// compiler will compile [return std::to_string(x);]
		std::cout << as_string(4.2) << '\n';
		// compiler will compile [return std::to_string(x);]
		std::cout << as_string(std::string("hello")) << '\n';
		// compiler will compile [return x;]
		std::cout << as_string("world") << '\n';
		// compiler will compile [return std::string(x);]
	}
*/

/*
	#include <type_traits>
	
	template <typename T>
	void func(T& tx)
	{
		if (tx > 0) {
			if constexpr (std::is_integral_v<T>) {
				++tx;
			}
			else {
				--tx;
			}
		}
	}
	
	int main()
	{
		int ival = 5;
		double dval = 2.5;
	
		func(ival);
		func(dval);
	
		std::cout << "ival = " << ival << '\n';
		std::cout << "dval = " << dval << '\n';
	}
	
	// FOR func(ival)
	//	void func<int>(int& tx)
	//	{
	//		if (tx > 0)
	//		{
	//			++tx;
	//		}
	//	}
	// this function will be compile by the compiler!
	
	// FOR func(dval)
	//	void func<int>(int& tx)
	//	{
	//		if (tx > 0)
	//		{
	//			--tx;
	//		}
	//	}
	// this function will be compile by the compiler!
*/

/*
	#include <type_traits>
	
	template <typename T>
	void func(T tx)
	{
		if constexpr (std::is_integral_v<T>) {
	
			static_assert(false, "error!");
		}
		else {
			tx.foo();
		}
	}
	
	int main()
	{
		func(2.5);	// syntax error
		// normally func() functions if constexpr block will not be compile
		// by the compiler, but static_assert() will always be compiled.
		// even if if block is not executed!
	}
*/

/*
	template <typename T>
	class Myclass {
		static_assert(std::is_pointer_v<T>. "pointer type required");
	};
	
	int main()
	{
		Myclass<int> x; // syntax error.
		// not dependent on classes private or public section!
	}
*/

/*
	template <typename T>
	class Myclass {
		void func()
		{
			static_assert(std::is_pointer_v<T>. "pointer type required");
		}
	};
	
	int main()
	{
		Myclass<int> x; // valid, no syntax error
	}
*/

/*
	#include <type_traits>
	
	template <typename T>
	void func(T tx)
	{
		if constexpr (std::is_integral_v<T>) {
	
		}
		else {
			foo();		// syntax error
			bar(tx);	// valid
			// dependent to T's type there might be a function called bar have an
			// argument from T's type
			tx.baz();	// valid
			// dependent to T's type there might be a member function called baz
		}
	}
	
	int main()
	{
		func(2.5);
	}
*/

/*
	class Myclass{};
	
	int main()
	{
		Myclass mx;
	
		if constexpr (sizeof(int) > 4)
		{
			++mx;	// syntax error
		}
		else
		{
			--mx;	// syntax error
		}
	
		// if our code in if constexpr block is not a generic type
		// not deduced in template
		// it will always be syntax error
	}
*/

/*
	#include <type_traits>
	
	template <typename T>
	auto getval(T t)
	{
		if constexpr (std::is_pointer_v<T>)
			return *t;
		else
			return t;
	}
	
	int main()
	{
		int ival{ 87 };
		double dval{ 4.5 };
		int* iptr{ &ival };
		double* dptr{ &dval };
	
		std::cout << getval(ival) << '\n';	// ouput -> 87
		std::cout << getval(dval) << '\n';	// output -> 4.5
		std::cout << getval(iptr) << '\n';	// output -> 87
		std::cout << getval(dptr) << '\n';	// output -> 4.5
	}
*/

/*
	template<int N>
	constexpr int fibo()
	{
		if constexpr (N >= 2)
		{
			return fibo<N - 1>() + fibo<N - 2>();
		}
		else
			return N;
	}
	
	int main()
	{
		constexpr auto y = fibo<8>();
	}
*/

/*
	#include <string>
	#include <type_traits>
	
	template <typename T>
	std::string tostr(T t)
	{
		return std::to_string(t);
	}
	
	std::string tostr(const std::string& s)
	{
		return s;
	}
	
	std::string tostr(const char* cstr)
	{
		return cstr;
	}
	
	std::string tostr(bool b)
	{
		return b ? "true" : "false";
	}
	
	
	template <typename T>
	std::string Tostr(T t)
	{
		if constexpr (std::is_same_v<T, std::string> || std::is_same_v<T, const char*>)
			return t;
		else if constexpr (std::is_arithmetic_v<T>)
		{
			return std::to_string(t);
		}
		else if constexpr (std::is_same_v<T, bool>)
		{
			return t ? "true" : "false";
		}
	}
	
	int main()
	{
		std::cout << tostr("hello") << '\n';				// output -> hello
		std::cout << tostr(std::string{"world"}) << '\n';		// output -> world
		std::cout << tostr(13) << '\n';					// output -> 13
		std::cout << tostr(5.9) << '\n';				// output -> 5.900000
		std::cout << tostr(true) << '\n';				// output -> true
	
	
		std::cout << Tostr("hello") << '\n';				// output -> hello
		std::cout << Tostr(std::string{ "world" }) << '\n';		// output -> world
		std::cout << Tostr(13) << '\n';					// output -> 13
		std::cout << Tostr(5.9) << '\n';				// output -> 5.900000
		std::cout << Tostr(true) << '\n';				// output -> 1
	}
*/
