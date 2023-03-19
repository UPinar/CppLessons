#include <iostream>

/*
	class Myclass {
		int x;					// data member
		void func();			// member function
		class NestedClass {};	// nested type, type member, member type
	};
*/

/*
	class Myclass {
		class NestedClass {
			int a, b, c, d;
		};
	};
	
	int main()
	{
		std::cout << "sizeof(Myclass) = " << sizeof(Myclass) << "\n";
		// output -> sizeof(Myclass) = 1
	}
*/

/*
	class A {
	public:
		class NestedA {
		private:
			int a, b, c, d;
		};
	};
	
	int main()
	{
		// NestedA ma; // sythax error
		// because name lookup will start in main() block continiues with global scope 
		// name-lookup will NOT check in class A's scope.
	
		A::NestedA mb; // legal
		// name lookup will start in main() block scope then class A's scope.
	}
*/

/*
	class A {
	private:
		class NestedA {
			int a, b, c, d;
		};
	};
	
	int main()
	{
		A::NestedA ma; // sythax error
		// name lookup will start in class A's scope. It will find NestedA class
		// but in access control phase, because class NestedA is in private section of class A
		// we can not reach A::NestedA from outside.
		// E0265 class "A::NestedA" is inaccessible
	}
*/

/*
	class A {
		class NestedA {
			int a, b, c, d;
		};
	
		void func()
		{
			NestedA ma;
			auto val = ma.a; // sythax error.
			// we can not reach our nested types private section from outer(class A) class.
			// thinking like nested type is a brain and outer type is like body.
		}
	};
*/

/*
	class A {
	private:
		int mx;
	
		class NestedA {
			void func()
			{
				auto sz = sizeof(mx);	// legal
				auto sz = sizeof(my);	// legal
				val = 5;				// legal
				// member type(inner class - nested type) can reach enclosing types(outer class) private section.
				// like in previous example brain can reach body's private section.
				// but body[enclosing type] can not reach brains[member type] private section.
			}
		};
	
		int my;
		static int val;
	};
*/

/*
	// nested type can be a class / structure
	// nested type can be an enumeration type (enum / enum class[scoped enum])
	// nested type can be a type alias	[Tur esismi]
	
	class A {
	public:
		class NestedA {};
	
		enum Color {Red, Yellow, Green};
	
		using Word = int;
	};
	
	int main()
	{
		A::Word myword;
	}
*/

/*
	class A {
	private:
		class Nested {};
	public:
		static Nested foo() { return Nested{}; }
	};
	
	int main()
	{
		// A::Nested x; // not legal -> A::Nested is in private section

		// A::Nested y = A::foo(); // not legal -> A::Nested is in private section
	
		auto z = A::foo();
		std::cout << typeid(z).name() << '\n'; 	output -> class A::Nested
	
		// if there is no name, is source code like (A::Nested)
		// no access control will applied to that [auto]
	}
*/

/*
	class A {
		void func() // implicitly inline function
		{
			mx = 5;
			// if a function INLINE
			// name-lookup will check all the class scope from top to bottom.
		}
		int mx;
	
		Nested mx; // Nested class is undefined yet..
		// name-lookup will start from top of the class A to [Nested mx;] expression
		// will not check all of the class scope

		class Nested {
		};
	};
*/

/*
	using type = double;
	
	class Myclass {
		type mx; // mx is double type
		// name-lookup will check from Myclass class's top to [type mx;] expression to find definition of type
		// than will check global scope from top to Myclass definition
	
		using type = int;
		type my; // mt is int type
		// name-lookup will find type definition inside Myclass's class scope.
	};
*/

/*
	// .h
	class Enclosing {

		class Nested {
	
		};
	
		Nested x;
		Enclosing::Nested y;
		// both are same if we are in class scope.
	
	public:
		Nested func(Nested);
	};
	
	// .cpp
	Nested Enclosing::func(Nested x) {} // sythax error
	// functions return type can not find in any scope
	
	Enclosing::Nested Enclosing::func(Nested x) {}
	// it needs to be used with Enclosing type
*/

/*
	class Enclosing {
	
		class Nested {
		public:
			int foo(int x) { return x + 5; }
			// int foo(int) is inline function
	
			int func(int);
		};
	
		int Nested::func(int x) { return x + 6; }
		// can not define a member function in Enclosing class scope, which is declared in Nested class, 
		// Nested types member functions, needs to define inline in Nested class scope, or in .cpp namespace scope.
	};
*/

/*
	//.h
	class Enclosing {
	
		class Nested {
		public:
			Nested& operator=(const Nested&); // copy assignment
		};
	};
	
	//.cpp
	Enclosing::Nested& Enclosing::Nested::operator=(const Nested& r)
	{
		// code
		return *this;
	}
	// Enclosing::Nested& return type
	// Enclosing::Nested::operator=() function name
	// const Nested& r parameter and namelookup starts in Class scope.
*/

/*
	========================================
	| pimpl idiom (pointer implementation) |
	========================================
*/

/*
	class Myclass {}; // namesapce scope forward decleration
	
	class Enclosing {
		class Nested{}; // Nested type forward decleration
		// Nested incomplete type
	};
	
	class Enclosing::Nested {
	
	};
*/

/*
	Q.1 | Can i make classes private section hidden, for client codes ?
	Q.2 | If i make classes private section hidden, why would i do that ? 
*/

/*
	// #include "A.h"
	
	// Myclass.h
	class Myclass {
	private:
		A ax; // if you want to use A class in Myclass you need to include header file of A class
	};
	
	// Every code that includes Myclahh.h will also include A.h
	// and also include every header file that A.h includes...
	// this will increase compile time
*/

/*
	// #include "A.h"
	// #include "B.h"
	// #include "C.h"
	
	// Myclass.h
	class Myclass {
	private:
		A ax;
		B bx;
		C cx;
	};
	
	// If we change members positions for example, ax and bx. We need to compile the project again.
	// Binary incompatibility happens.
	// If we did not see the private section, binary compatibility will continiue...
*/

/*
	// myclass.h
	class Myclass {
	public:
		Myclass(){}
		void foo();
	private:
		struct pimpl; // incomplete type
		pimpl* mp;
	};
	
	//myclass.cpp
	
	// #include "A.h"
	// #include "B.h"
	// #include "C.h"
	
	Myclass::Myclass() : mp(new pimpl)
	{
		// code
	}
	
	struct Myclass::pimpl {
		A ax;
		B bx;
		C cx;
	};
	
	void Myclass::foo()
	{
		mp->ax.func();
		mp->bx.bar();
		mp->cx.baz();
	}
*/

/*
	// <---MODERN PIMPL USING SMART POINTER--->
	// myclass.h
	
	#include<memory>
	class Myclass {
	public:
		Myclass() {}
		void foo();
	private:
		struct pimpl;
		std::unique_ptr<pimpl> mp;
	};
	
	//myclass.cpp
	// #include "A.h"
	// #include "B.h"
	// #include "C.h"
*/