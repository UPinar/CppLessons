#include <iostream>

/*
	======================================
	| static member variables of classes |
	======================================
*/

/*
	class Myclass {
	private:
		int a{};
		static int x1;
		static int x2;
		static int x3;
		static int x4;
	};
	
	int main()
	{
		std::cout << "sizeof(Myclass) = " << sizeof(Myclass) << '\n';
	}
*/

/*
	// main.h
	class Myclass {
		int a{};
	public:
		static int x; // non-defining decleration
	};
	

	// main.cpp
	int Myclass::x;
	
	int main()
	{
	
	}
	// static member variable need to be defined in .cpp file not in header file
	// if it is defined in .h file it will violate One Definition Rule (ODR)
	// because, more than 1 file can include the header file
*/

/*
	class Yourclass; // incomplete type class
	
	// myclass.h
	class Myclass {
	public:
		Yourclass my;
		// sythax error because compiler needs to create a storage for a non-static variable
		// but because it is incomplete type(its size is unknown) compiler can not create a storage 
	
		static Yourclass smy;
		// this is a decleration, because of it is decleration compiler is
		// not need to create a storage for this expression.
	
	};
	
	int main()
	{
		std::cout << sizeof(Yourclass);
		// already a sythax error. Size of incomplete type is not known.
	}
*/

/*
	class Myclass {
	public:
		Myclass mx;
		// because of Myclass is still incomplete type while compiler is reading it
		// it will throw sythax error. Its size has not been known yet
	
		Myclass* mp;
		// valid because pointers size already known
	
		static Myclass smx;
		// valid because this is declaration, compiler did not need to know
		// Myclass objects(smx) size
	};
*/

/*
	class Myclass {
	public:
		int x;
		static int mx;
	};
	
	int main()
	{
		Myclass m1, m2;
	
		m1.mx = 5;					// same
		m2.mx = 5;					// same
		Myclass::mx = 5;			// same
	
		Myclass* p = new Myclass;
		p->mx = 5;					// same
	}
*/

/*
	class Myclass {
	public:
	private:
		static int mx;
	};
	
	int foo()
	{
		std::cout << "foo() has been called\n";
		return 5;
	}
	
	int Myclass::mx = foo();
	// static variables are initializing before main() function[the program] starts to execute.
	
	int main()
	{
		std::cout << "main started\n";
	}
*/

/*
	class Erg {
	public:
		Erg()
		{
			std::cout << "Erg default ctor\n";
		}
	};
	
	// myclass.h
	class Myclass {
	public:
	private:
		static Erg merg;
	};
	
	// myclass.cpp
	Erg Myclass::merg{};
	
	int main()
	{
		std::cout << "main started\n";
	}
*/

/*
	class Myclass {
	public:
		Myclass() : mval{ 24 }, mx{ 67 } {}
	private:
		static int mx;
		int mval;
	};
	
	// static member variables can not be initialized in initializer list.
	// They need to initialize before program starts.
*/

/*
	class Myclass {
	private:
		// const and integral type static member variables can be initialized in class definition.
		static int mx = 10;				// invalid.		integral type but not const
		const static double md = 1.0;	// invalid.		is not a integral type
		const static int my = 20;		// valid.		const and integral type
		const static bool mb = false;	// valid.		const and integral type
	
		enum Color{blue, black, purple};
		const static Color mc = black; // valid.		const and integral type
	
		enum class Mycolors {red,green,yellow};
		const static Mycolors mmc = Mycolors::yellow; // valid const and integral type
	};
*/

/*
	// C++ 17 adds inline keyword usage in non-const static variable
	// [for .h only libraries]
	
	// myclass.h
	#include <vector>
	#include <string>
	
	class Myclass {
	public:
	private:
		inline static int x = 10;
		inline static std::vector<int> mivec{};
		inline static std::string msname{ "hello world" };
	};
	
	inline int gcount{}; 
	// using inline keyword for global variables
	// in the link phase only 1 gcount variable created(ODR).
*/

/*
	// date.h
	class Date {
	public:
		// using constexpr keyword make static member variables implicitly inline
		constexpr static int ms_min_year = 1940;
		constexpr static int ms_max_year = 2020;
	};
	
	// date.cpp
	int main()
	{
		constexpr auto mean_year = (Date::ms_max_year + Date::ms_min_year) / 2;
		// no need to define static variables in .cpp files because they are inline
	}
*/

/*
	======================================
	| static member functions of classes |
	|		have an external linkage	 |
	======================================
		
	// static global functions have an internal linkage 
	// but it is better using unnamed-namespace to create an internal linkage
*/

/*
	class Myclass {
	public:
		void foo();
		// it has an hidden Myclass*(const Myclass&) parameter.
		// it can call only with Myclass object
	
		static void bar();
		// it does not have an hidden Myclass*(const Myclass&) parameter
		// can be called without Myclass object
	};
	
	int main()
	{
		Myclass::foo();		// no Myclass object send as an hidden parameter
		Myclass{}.foo();	// Myclass object send as an hidden parameter
	
		Myclass::bar();		// no need to send Myclass object
	}
*/

/*
	-------------------------------------------------------------------------
	| global(free) functions			|	static member functions			|
	| ----------------------------------|---------------------------------- |
	| - can not reach classes private	|	- can reach classes private		|	
	| section							|	section							|
	| - in the namespace scope			|	- in the class scope			|
	-------------------------------------------------------------------------
*/

/*
	class Myclass {
	public:
		static void bar();
		void baz();
	};
	
	int main()
	{
		Myclass::bar();
		Myclass m1, m2;
		Myclass* p = &m1;
	
		m1.bar();
		m2.bar();
		p->bar();
	
		m1.baz(); // baz() is related with m1(Myclass object)
		m1.bar(); // bar() is NOT related with m1(Myclass object)
	
		// Calling static function with different Myclass objects (m1, m2, p).
		// All of the function calls are same because the member function[bar()] is static.
	}
*/

/*
	// myclass.h
	class Myclass {
	public:
		static void foo(int);	// declared inside class
		static void bar()		// defined inside class
		{
	
		}
	};
	
	// myclass.cpp
	void Myclass::foo(int x)	// declared in class defined in .cpp file
	{
	
	}
*/

/*
	// myclass.h
	class Myclass {
	public:
		static void foo(int);
		void bar(int);
	};
	
	// myclass.cpp
	#define STATIC
	STATIC void Myclass::foo(int x)
	{
	
	}
	void Myclass::bar(int x)
	{
	
	}

	// we can not understand which function is static and which is not.
	// when we check function both definitions in .cpp file.
	// it is better using a macro to show static function as static.
*/

/*
	class Myclass {
	public:
		static void foo()
		{
			auto p = this;
			// there is no hidden (Myclass*) parameter in static member functions
			// we can not use [this] pointer in static member functions.
	
			mx = 5;
			// sythax error.if this function was not static member function
			// compiler will create an expression (this->mx = 5) to reach member variable.
			// there is no [this] pointer so it is a  sythax error
	
		}
	
		static void func() const
		{
			// const keyword means [this] pointer is a low level const
			// no [this] pointer, const is NOT ALLOWED.
		}
	private:
		int mx;
	};
*/

/*
	class Myclass {
	public:
		void foo() const
		{
			smx = 10; // legal there is no relation between [this] pointer.
	
			my = 12; 
			// changing mx member variables value (this->mx = 12) not legal, sythax error
			// because of [this pointer] is low level const.
			// it is not possible to change non static member variable.
		}
	
		static void func()
		{
			smx = 15; // legal
			// (name lookup started in function scope no found )
			// (name lookup continued in class scope smx is found and change is legal)
		}
	private:
		static int smx;
		int my;
	};
*/

/*
	class Myclass {
	public:
		static int foo();
	private:
	};
	
	void foo(int);
	// different scopes no function overloading
*/

/*
	class Myclass {
	public:
		static int foo()
		{
			return 1;
		}
		static int x;
	};
	
	int foo()
	{
		return 9999;
	}
	
	int Myclass::x = foo();
	// FIRST declaration of static member variable
	// name lookup starts in class scope.
	// Myclass::foo() function will selected.
	
	
	int Myclass::x = ::foo();
	// In FIRST declaration, if unary scope resolution operator used
	// name lookup needs to start in global scope
	
	int main()
	{
		std::cout << Myclass::x << '\n';
		// FIRST declaration in class scope

		Myclass::x = foo();
		std::cout << Myclass::x << '\n';
		// in the next declaretions name lookup will start 
		// first in main block scope than continues in global scope.[NOT IN CLASS SCOPE]
	}
*/

/*
	class Myclass {
	public:
		static void bar()
		{
			foo(); // sythax error.
			// namelookup will find foo() function but foo() function needs to call with [this pointer]
			// [this->foo()] but static void bar() function
			// did not have [this pointer]
		}
		static void func(Myclass m)
		{
			m.foo();
			Myclass x; // legal
			x.foo();
	
			x.baz(); // also legal because static member functions can reach class's private section
		}
		void foo() 
		{
		}
	private:
		void baz()
		{
		}
	};
*/

/*
	class Myclass {
	public:
		static Myclass create(int x)
		{
			return Myclass{x};	// legal 
			// static member function can reach class's private section 
			// reaching private section and calling ctor Myclass(int)
		}
	private:
		Myclass(int);
	};
	
	int main()
	{
		Myclass m1{4};
		// not legal because private section of Myclass class can not be reach from local scope of main()
	
		auto m2 = Myclass::create(243); 
		// legal reaching ctor from static member function
	}
*/

/*
	-----------------------------
	| function pointer examples |
	-----------------------------
*/

/*
	int foo(int);
	using FPTR = int(*)(int);
	
	int main()
	{
		auto fp1 = foo;
		auto fp2 = &foo;
		int (*fp3)(int) = &foo;
		FPTR fp4 = &foo;
		decltype(fp1) fp5 = &foo;
	}
*/

/*
	class Myclass {
	public:
		int foo(int);
		static int func(int);
	};
	
	int bar(int);
	
	int main()
	{
		int (*fp)(int) = &Myclass::foo;				// sythax error types are not matching
	
		auto fp2 = &Myclass::foo;					// member function pointer
		// fp2's type is int(Myclass::*fp2)(int)
		int (Myclass::*fp3)(int) = &Myclass::foo;	// member function pointer
	
		int(*fp4)(int) = &Myclass::func;			
		fp4 = bar;									
		// static member functions addresses (&Myclass::func) 
		// have same type as global functions
	}
*/

/*
	// named constructor idiom
	class Complex {
	public:
		static Complex create_cartesian(double r, double i)
		{
			return Complex{ r,i };
		}
		static Complex create_polar(double angle, double distance)
		{
			return Complex{ angle,distance,0 };
		}
	private:
		Complex(double r, double i);
		Complex(double angle, double distance, int);
	};
	
	int main()
	{
		auto c1 = Complex::create_cartesian(1.2, 5.6);
		auto c2 = Complex::create_polar(.5, .8346);
	}
*/

/*
	// only lets dynamic object creation
	class Donly {
	public:
		static Donly* create()
		{
			return new Donly{};
		}
	
		Donly(const Donly&) = delete;
		Donly& operator=(const Donly&) = delete;
		// if one of the copy members(copy ctor or copy assignment) declared.
		// move members are implicitly deleted by the compiler.
		
	private:
		Donly();
	};
*/

/*
	============================
	| singleton design pattern |
	============================
	// in singleton design pattern singleton object needs to have only 1 instance
	// that instance needs to be used globally

*/

/*
	class Myclass {
	public:
		static Myclass& get_instance()
		{
			// not thread safe
			if (!mp) {
				mp = new Myclass;
			}
			return *mp;
		}
		void foo() {}
		void bar() {}
	
		Myclass(const Myclass&) = delete;
		Myclass& operator=(const Myclass&) = delete;
	private:
		Myclass()
		{
			std::cout << "Myclass object constructed\n";
		}
		inline static Myclass* mp{};
	
	};
	
	int main()
	{
		std::cout << "main starts\n";
	
		Myclass::get_instance().bar();
		auto& sng = Myclass::get_instance();
	}
*/ 

/*
	// Meyer's singleton

	class Myclass {
	public:
		static Myclass& get_instance()
		{
			// thread safe
			static Myclass instance;
			// static local variable(instance) will come to life when get_instance() function called)
			return instance;
		}
		Myclass(const Myclass&) = delete;
		Myclass& operator=(const Myclass&) = delete;
	private:
		Myclass()
		{
			std::cout << "Myclass object constructed\n";
		}
	};
	
	int main()
	{
		std::cout << "Main started\n";
		Myclass::get_instance();
		std::cout << "Main continiues\n";
		Myclass::get_instance();
		std::cout << "Main continiues\n";
	}
*/

/*
	class A {
	public:
		A()
		{
			++ms_live_count;
			++ms_ever_lived_count;
		}
	
		~A()
		{
			--ms_live_count;
		}
	
		static int get_live_count()
		{
			return ms_live_count;
		}
		static int get_ever_lived_count()
		{
			return ms_ever_lived_count;
		}
	private:
		inline static int ms_live_count{};
		inline static int ms_ever_lived_count{};
	};
	
	int main()
	{
		A x, y, z;
		A* p1 = new A;
		A* p2 = new A;
	
		{
			A k;
			delete p1;
		}
	
		std::cout << A::get_live_count() << '\n';		// returns 4
		std::cout << A::get_ever_lived_count() << '\n'; // returns 6
	}
*/

/*
	#include <string>
	#include <vector>
	#include<algorithm>
	
	class Fighter {
	public:
		Fighter(const std::string& name) : m_name{ name }
		{
			svec.push_back(this);
		}
	
		~Fighter()
		{
			std::erase(svec,this); // C++20, return value (how many deleted) is size_t type
			// function above add with C++20, if it was not added we need to write remove-erase idiom.
	
			// auto iter = std::find(svec.begin(), svec.end(), this);
			// svec.erase(iter);
		}
	
		void ask_help()
		{
			for (Fighter* p : svec)
			{
				if (p != this)
				{
					std::cout << p->m_name << " ";
				}
			}
			std::cout << '\n';
		}
	private:
		std::string m_name;
		inline static std::vector<Fighter*> svec;
	};
	
	int main()
	{
		Fighter f1{ "f1" }, f2{ "f2" }, f3{ "f3" }, f4{ "f4" };
	
		auto p1 = new Fighter{ "p1" };
		auto p2 = new Fighter{ "p2" };
		f3.ask_help();
	
		delete p1;
		f1.ask_help();
	}
*/ 

/*
	------------------------
	| range based for loop | 
	------------------------
*/

/*
	class A {
	public:
		A();
		A(A&&); // move ctor
		void foo();
	};
	
	int main()
	{
		A a_container[100];
	
		for (auto m : a_container)
		{
			m.foo();
		}
		// because of move constructor is user defined copy members are deleted.
		// in range base loop
		// A m = A object in container will use copy constructor to create m object
	}
*/

/*
	int a[5] = { 1, 2, 3, 4, 5 };
	
	auto foo()
	{
		return &a;
	}
	
	typedef int(*aptr)[5];
	aptr foo_2()
	{
		return &a;
	}
	
	using APTR = int(*)[5];
	APTR foo_3()
	{
		return &a;
	}
	
	int(*foo_4())[5]
	{
		return &a;
	}
	
	int main()
	{
		auto p1 = a;	// p is a pointer				int* p1
		auto p2 = &a;   // p2 is a pointer to array		int(*p2)[5]
	
		// *p1 -> first variable in array
		// *p2 -> array
	
		auto f1 = foo();
		auto f2 = foo_2();
		auto f3 = foo_3();
		auto f4 = foo_4();
	
		for (size_t i = 0; i < 5; i++)
		{
			std::cout << (*f1)[i] << " ";
			std::cout << (*f2)[i] << " ";
			std::cout << (*f3)[i] << " ";
			std::cout << (*f4)[i] << " ";
			std::cout << '\n';
		}
	}
*/

/*
	-----------------------
	| if with initializer |
	-----------------------
	C++17, for scope leakage problem
*/

/*
	#include<vector>
	int main()
	{
		std::vector<int> ivec(100);
		// code
	
	
		// SAME 1
		{
			auto iter = std::find(std::begin(ivec), std::end(ivec), 78);
			if (iter != end(ivec))
			{
				std::cout << iter - begin(ivec);
			}
		}
	
		// SAME 2
		if (auto iter = std::find(std::begin(ivec), std::end(ivec), 78); iter != end(ivec))
		{
			std::cout << iter - begin(ivec);
		}
	}
*/

/*
	int foo()
	{
		return 12;
	}
	
	int main()
	{
		if (int ival = foo(); ival > 10)
		{
			std::cout << "(ival > 10) ival = " << ival << '\n';
		}
		else
		{
			std::cout << "(ival <= 10) ival = " << ival << '\n';
		}
	
		// ival = 10 // sythax error. ival declared inside if/else loop.
	}
*/
















