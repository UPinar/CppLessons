#include <iostream>

/*
	================
	| namespace(s) |
	================
*/

/*
	namespace nspaceX {
		int foo();
	
		enum class Pos{ on, off, hold };
	
		class Myclass {
		public:
			void func()
			{
	
			}
	
			void bar();
		};
	
		void Myclass::bar()
		{
	
		}

		namespace details{
		}	// nested namespace
		
	}
	// still in global namespace it is nested namespace
*/

/*
	namespace std {
		namespace regex_constants {

		}
	}
*/

/*
	C Scopes
	---------
	file scope
	block scope
	function prototype scope
	function scope

	C++ scopes
	-----------
	namespace scope
	class scope
	block scope
	function prototype scope
	function scope

*/

/*
	namespace Nspace {
		int x;
		double x[10];
		// we can not have same names in same namespaces.
	}
	
	namespace Nspace_2 {
		int x;
		// we can have same names in different namespaces.
	}
*/

/*
	// variables inside namespaces are global variables
	// global variables are zero initializing as default initialization
	namespace Nspace {
		int x;
	}
	
	int main()
	{
		x = 5; // not valid
		Nspace::x = 5; // valid [qualified name]
		// we need to qualify the name with its namespace to use it outside of the namespace scope
	}
*/

/*
	#include <vector>
	#include <string>
	
	namespace Nspace {
		int a, b, c;
	}
	
	namespace Nspace {
		double x, y;
	}
	// namespace declerations are cummilative
	
	int main()
	{
		Nspace::x = 5.3;
		Nspace::a = 4;
	
		std::vector<int> ivec;
		std::string sname;
	
		// because of std namespace is cummilative,
		// different header files (vector, string..) can be in the same namespace(std)
	}
*/

/*
	namespace Nspace {
		namespace Nspace_2 {
	
			class Myclass {
			public:
				int foo(int);
			};
		}
	}
	
	int Nspace::Nspace_2::Myclass::foo(int x)
	{
	
	}
*/

/*
	namespace Nspace {
		class Myclass {
	
		};
	
		Myclass foo();
		// Nspace::Myclass foo(); -> no need to qualify the function
		// we don't need to qualified name for Myclass when using inside same namespace.
	}
*/

/*
	Q : Can i use a name(declared inside namespace), outside of that namespace without 
	qualifying it, with its namespace name ?

	-> using decleration
	-> using namespace (directive) decleration
	-> ADL (argument dependent lookup)
*/

/*
	---------------------
	| using decleration |
	---------------------
*/

/*
	void foo()
	{
		using std::cout;
		cout; // can used cout
	}
	
	void bar()
	{
		cout; // can not used cout
	}

	using std::cout; // this is a decleration and it has a scope.
*/

/*
	// in modern cpp we declare using decleration with commas.
	using std::cout, std::endl;
*/

/*
	namespace Nspace {
		int a;
	}

	int main()
	{
		using Nspace::a;
		a = 10;

		int a = 5;
		// because of [int a] injected in main's scope
		// we can not create another variable named [a] inside main scope.
		// C2086  'int Nspace::a': redefinition
	}
*/

/*
	namespace First {
		int a;
	}

	namespace Second {
		using First::a;
		// we inject [int a] to namespace Second, from namespace First
	}

	int main()
	{
		auto x = Second::a; // legal
	}
*/

/*
	int x = 10;

	namespace Nspace {
		using ::x;
	}

	int main()
	{
		Nspace::x = 12; // no sythax error
	}
*/

/*
	namespace Nspace {
		int x, y, z;
	}

	using Nspace::x;

	int main()
	{
		int x = 57; // no sythax error

		::x = 34; // unary scope resolution operator.
		// x is injected in global scope [using Nspace::x]

		std::cout << x << '\n';		// 57
		std::cout << ::x << '\n';	// 34
	}
*/

/*
	namespace Nspace {
		int x, y, z;
	}

	using Nspace::x, Nspace::y, Nspace::z;

	int main()
	{
		x = 5;
		y = 45;
		z = 85;
	}
*/

/*
	-------------------------------------------
	| using namespace (directive) decleration |
	-------------------------------------------
*/

/*
	namespace Nspace {
		int x, y, z;
	}

	using Nspace::x;
	int x = 5; // sythax error because we inject [int x] to global scope
	// we can not declare a new variable named x in global scope
	// C2086	'int Nspace::x': redefinition
*/

/*
	namespace Nspace {
		int x = 44;
	}
	
	using namespace Nspace;
	// this decleration is for using all the namespace scope as global scope.
	// but this is not like injecting
	int x = 35;
	
	int main()
	{
		x = 5;
		// ambiguity because there is 2 int variable [x] is defined in global scope
		// when we use [using namespace Nspace] decleration.
	
		std::cout << ::x << '\n';			// 35
		std::cout << Nspace::x << '\n';		// 44
	}
*/

/*
	namespace First {
		int x, y, z;
	}
	
	namespace Second {
		int x;
	}
	
	using namespace First;
	using namespace Second;
	
	int main()
	{
		x = 10; // ambiguity error
	}
*/

/*
	namespace First {
		void func(int)
		{
			std::cout << "First::func(int)\n";
		}
	}
	
	void func(double)
	{
		std::cout << "::func(double)\n";
	}
	// no function overloading because scopes are different
	
	using namespace First;
	// when we declare [using namespace First;]
	// functions become overloads.
	
	int main()
	{
		// before declering [using namespace First;]
		func(4);			// output -> ::func(double) standart conversion from int to double
		First::func(3.5);		// output -> First::func(int) standart conversion from double to int.
	
		// after declaring [using namespace First;]
		func(4);			// output -> First::func(int)
		func(4.2);			// output -> ::func(double)
	}
*/

/*
	namespace First {
		void func(int)
		{
			std::cout << "First::func(int)\n";
		}
	}
	
	namespace Second {
		void func(double)
		{
			std::cout << "Second::func(double)\n";
		}
	}
	
	using namespace First;
	using namespace Second;
	
	int main()
	{
		func(10);	// output -> First::func(int)
		func(2.2);	// output -> Second::func(double)
	}
*/

/*
	namespace Nspace {
		int a, b, c;
	}
	
	void foo()
	{
		a = 4;
		// sythax error because [using namespace Nspace;] decleration after foo() function
		// C2065 'a': undeclared identifier
		// using namespace decleration has also a scope.
	}
	
	using namespace Nspace;
	
	void bar()
	{
		b = 45;
	}
*/

/*
	// Myclass.h
	#include <vector>
	#include <string>
	
	using namespace std;
	// DO NOT USE (NEVER)
	// using namespace decleration and using decleration in .h file
	
	class Myclass {
		std::vector<std::string> msvec;
	};
*/

/*
	---------------------
	| unnamed namespace |
	---------------------
*/

/*
	static int foo(int);	// internal linkage
	static int g = 10;		// internal linkage
	
	// internal linkage
	namespace {
		int foo(int);
		int g = 10;
	}
	
	// both are same using static keyword and using unnamed namespace
	
	// compiler acts like, there is a namespace with name
	// and that name declared [using namespace WhatCompilerThinksAboutUnnamedNamespace;]
	// with using namespace decleration.

	// if you will use some names only in .cpp file it is better using unnamed namespaces.
*/

/*
	-------------------
	| namespace alias |
	-------------------
*/

/*
	namespace nspace_xyz_proj {
		int ival = 5;
	
		namespace details {
			int x, y;
		}
	}
	
	namespace nspace = nspace_xyz_proj;
	
	void foo()
	{
		namespace dtl = nspace_xyz_proj::details;
		dtl::x = 5;
	}
	
	int main()
	{
		nspace_xyz_proj::ival++;
		nspace::ival++;
	}
*/

/*
	-----------------------------------
	| argument dependent lookup (ADL) |
	-----------------------------------
*/

/*
	Think about a function having a non-qualified name called.
	If one of its argument is related with a type in namespace,
	that function's namelookup phase will also include that namespace scope too.
*/

/*
	namespace Nspace {
	
		class Myclass {
	
		};
	
		void foo(Myclass)
		{
			std::cout << "Nspace::foo(Myclass)\n";
		}
	}
	
	int main()
	{
		Nspace::Myclass mx;
	
		foo(mx);
		// foo is a non-qualified function name
		// because of mx(its argument)'s type is Nspace::Myclass
		// which is in Nspace namespace
		// namelookup will check Nspace scope to find foo() function.
		// output -> Nspace::foo(Myclass)
	}
*/

/*
	#include <vector>
	namespace Nspace {
	
		class Myclass {
	
		};
	
		void foo(std::vector<Myclass>)
		{
			std::cout << "Nspace::foo(Myclass)\n";
		}
	}
	
	int main()
	{
		std::vector<Nspace::Myclass> x;
	
		foo(x); // ADL
		// foo is a non-qualified function name
		// because of x(its argument)'s type is std::vector<Nspace::Myclass>
		// which is RELATED with Nspace namespace
		// namelookup will check Nspace scope to find foo() function.
	}
*/

/*
	namespace Nspace {
	
		enum Color {Red, Yellow, Green};
		void foo(Color);
	}
	
	int main()
	{
		foo(Nspace::Red); // ADL
	}
*/

/*
	namespace Nspace {
		class Myclass {
	
		};
	
		void foo(Myclass);
	}
	
	void foo(Nspace::Myclass);
	
	int main()
	{
		Nspace::Myclass x;
	
		foo(x); // ambiguity
	
		// C2668 : 'foo' : ambiguous call to overloaded function
		// could be 'void foo(Nspace::Myclass)'
		// or 'void Nspace::foo(Nspace::Myclass)'[found using argument - dependent lookup]
		// while trying to match the argument list '(Nspace::Myclass)'
	}
*/

/*
	#include <vector>
	#include <algorithm>
	
	int main()
	{
		std::vector<int> ivec;
	
		sort(begin(ivec), end(ivec));
	
		// all [sort], [begin] and [end] names are in std namespace
		// ADL occur for all of them.
	}
*/

/*
	namespace Nspace {
	
		class Myclass {
	
		};
	
		void foo(Myclass);
	}
	
	int main()
	{
		Nspace::Myclass mx;
	
		void foo(int);
	
		foo(mx); // synthax error
		// foo's namelookup first starts from main() function block
		// if it finds that name in main block it stops and
		// will start to context control phase then access control..
		// if it can not find in main function scope
		// 2 way road starts 1-ADL 2-global scope as in previous example.
	}
*/

/*
	int main()
	{
		std::cout << "Hello world";
	
		std::operator<<(std::cout, "Hello World");
		operator<<(std::cout, "Hello World");	// ADL
	}
*/

/*
	// Herb Sutter's blog
	namespace A {
		struct X {};
		struct Y {};
		void f(int);
		void g(X);
	}
	
	namespace B {
		void f(int i)
		{
			f(i);   
			// calls B::f (endless recursion)
		}
	
		void g(A::X x)
		{
			g(x);   
			// Error: ambiguous between B::g (ordinary lookup) and A::g (argument-dependent lookup)
		}
	
		void h(A::Y y)
		{
			h(y);  
			// calls B::h (endless recursion): ADL examines the A namespace but finds no A::h,
			// so only B::h from ordinary lookup is used
		}
	}
*/

/*
	// SAME 1
	namespace A {
		namespace B {
			namespace C {
	
			}
		}
	}
	
	// SAME 2
	namespace A::B::C {
		int x = 4;
	}
	
	namespace A::B {
		int y = 10;
	}
	
	namespace A {
		int z = 5;
	}
	
	int main()
	{
		std::cout << A::B::C::x << '\n';	// output -> 4
		std::cout << A::B::y << '\n';		// output -> 10
		std::cout << A::z << '\n';			// output -> 5
	}
*/

/*
	--------------------
	| inline namespace |
	--------------------
*/

/*
	inline namespace A {
		int ival;
	}
	
	int main()
	{
		ival = 5;
	}
*/

/*
	namespace X {
		inline namespace Y {
			int ival;
		}
		// using namespace Y;
	}
	
	int main()
	{
		X::ival = 4; // sythax error because ival is in X::Y::ival
		// when we use [using namepace Y;] inside X namespace we can reach ival from X
		// when we make namespace Y inline we can also reach ival from X.
	}
*/

/*
	namespace outer {
		namespace inner {
			class A {
	
			};
		}
	
		using namespace inner;
		void func(inner::A);
	}
	
	int main()
	{
		outer::inner::A x;
		func(x); // ADL is not viable
	
		// we create a tunnel from main() functions block to outer::inner::A
		// [using namespace inner;] namespace decleration in outer namespace
		// is creating a door between them but it can only open from
		// outer namespace to inner.
	
		// but when we make inner namespace inline that door
		// will be open from both sides
		// from outer to inner and from inner to outer.
	}
*/

/*
	namespace outer {
		inline namespace inner {
			class A {
	
			};
		}
	
		void func(inner::A);
	}
	
	int main()
	{
		outer::inner::A x;
		func(x); // ADL is viable
		// because of the door can open from both sides
	}
*/

/*

*/

/*
	namespace Outer {
		int x = 10;
	
		namespace Inner {
			int x = 5;
		}
		using namespace Inner;
	}
	
	int main()
	{
		std::cout << Outer::x << '\n'; // output -> 10
		// because of using namespace decleration is not injecting the variables.
		// there will not a an ambiguity between [int x] variables

		// ---THINK---
		// we find Outer::x and because [Inner::x] variable can not open the door from Inner to Outer
		// and Outer namespace is not opening the door because it find [Outer::x]
		// no ambiguity will be between them.

	}
*/

/*
	namespace Outer {
		int x = 10;
	
		inline namespace Inner {
			int x = 5;
		}
	}
	
	int main()
	{
		std::cout << Outer::x << '\n';
		// if we make Inner namespace inline there will be an ambiguity error
	
		//---THINK---
		// we find a variable named [x] in Outer namespace's scope.
		// but because of Inner namespace can open the door from Inner to Outer
		// Inner::x is opening the door and name-lookup will see [Inner::x] too.
	}
*/

/*
	-------------------------------------
	| versioning with inline namespaces |
	-------------------------------------
*/

/*
	// foo.h
	namespace foo {
		class Myclass {
			int x;
			int y;
			double z;
		};
	}
	// if we change any of the member variables position
	// object code will change (ABI brackage)
*/

/*
	// foo.h
	namespace foo {
		inline namespace ver_01 {
			class Myclass {
				int x;
				int y;
				double z;
			};
		}
		namespace ver_02 {
			class Myclass {
				int x;
				double z;
				int y;
			};
		}
	}
*/

/*
	#define USE_INLINE_Y
	
	namespace X {
	#ifdef USE_INLINE_Y
		inline
	#endif
		namespace Y {
			const char* func(bool)
			{
				return "bool";
			}
		}
	
		const char* func(int)
		{
			return "int";
		}
	}
	
	int main()
	{
		// when macro is not defined
		std::cout << X::func(true); // output -> int
	
		// when macro is defined // output -> bool
	}
*/

/*
	// #define VER1
	// #define VER2
	
	namespace Nspace {
	#ifdef VER1
		inline
	#endif
		namespace Ver_1 {
			class Myclass {
	
			};
		}
	#ifdef VER2
		inline
	#endif
		namespace Ver_2 {
			class Myclass {
	
			};
		}
	}
	
	int main()
	{
		// if Ver_1 namespace was inline
		Nspace::Myclass; // Nspace::Ver_1::Myclass will be used.
	
		// if Ver_2 namespace was inline
		Nspace::Myclass; // Nspace::Ver_2::Myclass will be used.
	}
*/
