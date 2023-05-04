#include <iostream>

/*
	===============
	| inheritance |
	===============
*/

/*
	super class			parent class			[BASED CLASS]
	sub class			child class			[DERIVED CLASS]
*/

/*
	Multi-Level Inheritance :	Car <- Volvo <- Volvo XC90

	Multiple Inheritance    :	Animal <- Whale -> Endangered
*/

/*
	Inheritance specifiers
	------------------------
	public inheritance 
	private inheritance 
	protected inheritance
*/

/*
	// Incomplete type classes CAN NOT be a Base class.
	class Car; // forward decleration
	
	class Audi : public Car {
	
	}
	// E0070 incomplete type is not allowed
*/

/*
	class Base {};
	
	class DerClass : Base {};
	class Der_2_Class : private Base{};
	// default inheritance specifier is PRIVATE for CLASSES
	
	struct DerStruct : Base {};
	struct Der_2_Struct : public Base{};
	// default inheritance specifier is PUBLIC for STRUCTS

	// <--- THINK ---> (SIMILAR)
	// default section inside classes is PRIVATE
	// default section inside structs is PUBLIC
*/

/*
	// Base classes public interface is added to Der classes interface
	class Base {
	public:
		void foo();
		int mx;
	
		class Nested {
		};
	};
	
	class Der : public Base {
	
	};
	
	int main()
	{
		Der myder;
	
		myder.foo();
		myder.mx = 10;
		Der::Nested;
	}
*/

/*
	class X {
		int a, b;
	};
	
	class Y {
		X mx;
	};
	
	class Z : public X
	{
	
	};
	
	int main()
	{
		std::cout << "sizeof(X) = " << sizeof(X) << '\n'; // output -> sizeof(X) = 8
		std::cout << "sizeof(Y) = " << sizeof(Y) << '\n'; // output -> sizeof(Y) = 8
		std::cout << "sizeof(Z) = " << sizeof(Z) << '\n'; // output -> sizeof(Z) = 8
	}
*/

/*
	class Base {
	public:
		void foo();
	};
	
	class Der : public Base {
	
	};
	
	int main()
	{
		Der myder;
		myder.foo();
	
		// Non-static member functions have a hidden parameter [this pointer]
		// When we create a derived class inherited from base class,
		// and use Base classes member function with Der class object
		// we are sending the address[this pointer] of Base class created inside Der class,
		// to Base classes non-static member function.
	}
*/

/*
	// requires no more, promise no less
	// SOLID's(L) Liskov substitution principle 

	// There is an implicit conversion from Derived class to Base class (upcasting)

	class Base {
	public:
	};
	
	class Der : public Base {
	
	};
	
	int main()
	{
		Der myder;
		Base* baseptr = &myder; // up-casting
		Base& baseref = myder;	// up-casting
	
		Base x = myder; // DO NOT USE!!! (object slicing) [nesne dilimlenmesi]
	}
*/

/*
	class Car {};
	
	class Audi : public Car{};
	class Volvo : public Car{};
	class Mercedes : public Car{};
	
	void car_game(Car* p);
	void car_game_2(Car&);
	
	int main(void)
	{
		car_game(new Audi);
		car_game_2(*new Volvo);
	
		std::cout << typeid(new Audi).name() << '\n';	// output -> class Audi * __ptr64
		std::cout << typeid(*new Audi).name() << '\n';	// output -> class Audi
	}
*/

/*
	class Car {
	public:
		void run();
	};
	
	class Audi : public Car {
	
	};
	
	int main(void)
	{
		Audi myaudi;
		myaudi.run(); // upcasting
	}
*/

/*
	-------------------------------
	| inheritance and name-lookup |
	-------------------------------
*/

/*
	class Base {
	public:
		void foo(int);
	};
	
	class Der : public Base {
	public:
		void foo(double);
	};
	
	int main(void)
	{
	
		// name-lookup will start from derived class scope, then will go to the base class scope.
		// name-hiding(shadowing) can happen between derived and base class.
	
		Der myder;
		myder.foo(12);
	
		// in Der class scope name was found. It will NOT go to Base class for continue searching.
		// [name-hiding(shadowing)]
		// int will implicitly convert to double[standart conversion] and Der::foo(double) will be invoked.
	}
*/

/*
	class Base {
	public:
		void foo(int);
	};
	
	class Der : public Base {
	private:
		void foo(double);
	};
	
	int main(void)
	{
		Der myder;
		myder.foo(12); // syntax error
	
		// name-lookup will found Der::foo()
		// context control is okay, int to double standart conversion.
		// access control is NOT okay because of Der::foo() in private section.
		// E0265 function "Der::foo"  is inaccessible
	}
*/

/*
	class Base {
	public:
		void foo(int);
	};
	
	class Der : public Base {
	private:
		void foo(double);
	};
	
	class Myclass {
	public:
		void func();
	};
	
	int main(void)
	{
	
		Myclass m;
		
		m.func();
		m.Myclass::func();
		// these 2 lines are same
	
		Der myder;
		myder.Base::foo(12); // calling Base::foo() function with Der class object
		// upcasting myder(Der class) object(to Base class) then casting 
		// hidden parameter this pointer(Der*) to Base* to call foo() function in Base class.
	}
*/

/*
	class Base {
	public:
		void func(int, int);
	};
	
	class Der : public Base {
		void func(int);
	
		void foo()
		{
			func(1, 1); // syntax error
			// name-lookup will start from foo() functions block
			// then continue with Der class scope and it will find func(int);
			// context control will throw an error.
			// process will stop and Base::func(int,int) can not be invoked.
	
			func(1);		// legal
			Base::func(1, 1);	// legal
	
			((Base*)this)->func(1, 1);
			// casting [this] pointer(Der*) to [Base*] then call func()
			// will also invoke Base::func()
		}
	};
*/

/*
	----------------------------------
	| inheritance and access control |
	----------------------------------
*/

/*
	class Base {
	public:
		int m_base_public;
	protected:
		int m_base_protected;
		void bar();
	private:
		int m_base_private;
	
		// friend class Der;
	};
	
	class Der : public Base {
		void foo()
		{
			m_base_private = 10; // syntax error
			// can not reach Base classes private section.
			// Only can reach Base classes private section with a friend decleration.
	
			m_base_protected = 12;	// legal
			bar();			// legal
			// derived class can reach base classes protected section
	
			m_base_public = 15;
			// everyone can reach base classes public section
		}
	};
	
	int main()
	{
		Base mybase;
		mybase.m_base_public = 10;	// legal
		mybase.m_base_protected = 10;	// syntax error
		mybase.m_base_private = 10;	// syntax error
		// Client codes can not reach classes private and protected sections.
	}
*/

/*
	#include <stack>
	
	class Mystack : public std::stack<int>{
		void foo()
		{
			c.push_back(12);
			// c is in protected section of std::stack<int> base class
			// derived class can reach base classes protected section
		}
	};
	
	int main()
	{
		std::stack<int> x;
		x.c; // syntax error
		// client can not reach protected section
	}
*/

/*
	class Base {
	public:
		Base()
		{
			std::cout << "Base() default ctor\n";
		}
		~Base()
		{
			std::cout << "~Base() dtor\n";
		}
	};
	
	class Der : public Base {
	
	};
	
	int main()
	{
		Der myder;
	
		// output -> 
		// Base() default ctor
		// ~Base() dtor
	
		// implicitly declared[by compiler] defaulted Der classes default ctor will invoke Base classes default ctor.
		// implicitly declared[by compiler] defaulted Der classes dtor will invoke Base classes dtor
	}
*/

/*
	class Base {
	public:
		Base(int) {}
	};
	
	class Der : public Base {
	public:
	};
	
	int main()
	{
		Der myder; // syntax error
		// E1790 the default constructor of "Der" cannot be referenced -- it is a deleted function
	
		// Der's default ctor will try to invoke Base() default ctor.
		// Because of there is a user declared ctor in Base class,
		// Base() default ctor is not declared.
		// Because of Der's default ctor needs to invoke Base() default ctor, 
		// and Base::Base() is not declared.
		// Compiler will delete Der() default ctor
	}
*/

/*
	class Base {
	private:
		Base();
	public:
	};
	
	class Der : public Base {
	};
	
	int main()
	{
		Der myder; // syntax error
		// E1790  the default constructor of "Der" cannot be referenced -- it is a deleted function
	
		// Same error(default ctor deleted). Because of Base() default ctor is in the private section
		// Der() can not reach Base classes private section.
		// Compiler will delete Der's default ctor.
	}
*/

/*
	class Base {
	public:
		Base()
		{
			std::cout << "Base() default ctor\n";
		}
		Base(int)
		{
			std::cout << "Base(int)\n";
		}
		Base(double)
		{
			std::cout << "Base(double)\n";
		}
		Base(int,int)
		{
			std::cout << "Base(int,int)\n";
		}
	};
	
	class Der : public Base {
	public:
		// Der() : Base(){}	// implicitly declared default ctor acts like this
		// Der() : Base(3) {}	// output -> Base(int)
		// Der() : Base(3.) {}	// output -> Base(double)
		Der() : Base{3,4} {}	// output -> Base(int,int)
	
		Der(int x, int y) : Base((x+y)/ 2.0){}
	};
	
	int main()
	{
		Der myder; // output -> Base() default ctor
	
		Der myder_2(2, 4); // output -> Base(double)
	}
*/

/*
	class Base {
	public:
		Base()
		{
			std::cout << "Base() default ctor\n";
		}
	};
	
	class Member {
	public:
		Member()
		{
			std::cout << "Member() default ctor\n";
		}
	};
	
	class Der : public Base {
	public:
		Der() : mx(), Base()
		{
			// Base object and member object are already alive in here.
		}
	
		// Member object is first in the queue but Base classes default ctor will invoke first.
		// It is better write first Base() in initializer list.
	private:
		Member mx;
	};
	
	int main()
	{
		Der myder;
	
		// output -> 
		// Base() default ctor
		// Member() default ctor
	
		// first Base class default ctor will invoked.
		// then Member objects default ctor.
	}
*/

/*
	-------------------------------------------
	| special member functions in inheritance |
	-------------------------------------------
*/

/*
	class Base {
	public:
		Base() = default;
		Base(const Base&)
		{
			std::cout << "Base copy ctor\n";
		}
		Base(Base&&)
		{
			std::cout << "Base move ctor\n";
		}
	};
	
	class Der : public Base {};
	
	int main()
	{
		Der dx;
		Der dy = dx; 		// output -> Base copy ctor
		Der dz = std::move(dx); // output -> Base move ctor
	}
*/

/*
	class Base {
	public:
		Base()
		{
			std::cout << "Base default ctor\n";
		}
		Base(const Base&)
		{
			std::cout << "Base copy ctor\n";
		}
		Base(Base&&)
		{
			std::cout << "Base move ctor\n";
		}
	};
	
	class Der : public Base {
	public:
		Der() = default;
	
		Der(const Der&)
		{
			// because of Der's copy ctor is user declared
			// and not used in initializer list to call Base's copy ctor
			// Base() default ctor will invoked to create Base object inside of Der object.
		}
	
		// Der(const Der& other) : Base(other) {}
		// this is how compiler implicitly wrote Der's copy ctor (upcasting)

		// Der(Der&& other) : Base(std::move(other)) {}
		// this is how compiler implicitly wrote Der's move ctor (upcasting)
	};
	
	int main()
	{
		Der dx;
		Der dy = dx; // output -> Base default ctor
	}
*/

/*
	class Base {
	public:
		Base& operator=(const Base&)
		{
			std::cout << "Base copy asssignment\n";
			return *this;
		}
		Base& operator=(Base&&)
		{
			std::cout << "Base move asssignment\n";
			return *this;
		}
	};
	
	class Der : public Base {
	public:
		Der& operator=(const Der& other)
		{
			std::cout << "Der copy asssignment\n";
			Base::operator=(other);
			// calling Base classes copy assignment (upcasting)
			return *this;
		}
	
		Der& operator=(Der&& other)
		{
			std::cout << "Der move asssignment\n";
			Base::operator=(std::move(other));
			// calling Base classes move assignment (upcasting)
			return *this;
		}
	};
	
	int main()
	{
		Der dx, dy;
		dx = dy;	    	// output -> Base copy asssignment
		dx = std::move(dy); 	// output -> Base move asssignment
	}
*/

/*
	-------------------------------------
	| using declerations in inheritance |
	-------------------------------------
*/

/*
	class Base {
	protected:
		void foo(int);
		int mx;
	};
	
	class Der : public Base {
	public:
		using Base::foo;
		using Base::mx;
	};
	
	int main()
	{
		Der myder;
		myder.foo(12);
		myder.mx;
		// Client can reach Base classes protected section by using `using` decleration
	}
*/

/*
	class Base {
	protected:
		void foo(int)
		{
			std::cout << "Base::foo(int)\n";
		}
	};
	
	class Der : public Base {
	public:
		void foo(double)
		{
			std::cout << "Der::foo(double)\n";
		}
		using Base::foo;
	};
	
	int main()
	{
		Der myder;
	
		// Before using decleration
		myder.foo(12);	// output -> Der::foo(double)
		myder.foo(0.9);	// output -> Der::foo(double)
	
		// After using decleration
		myder.foo(12);	// output -> Base::foo(int)
		myder.foo(0.9);	// output -> Der::foo(double)
	
		// Base::foo() and Der::foo() acts like function overloads.
	}
*/

/*
	class Base {
	protected:
		void foo(int)
		{
			std::cout << "Base::foo(int)\n";
		}
		void foo(int,int)
		{
			std::cout << "Base::foo(int,int)\n";
		}
		void foo(int,int,int)
		{
			std::cout << "Base::foo(int,int,int)\n";
		}
	};
	
	class Der : public Base {
	public:
		void foo(double)
		{
			std::cout << "Der::foo(double)\n";
		}
		using Base::foo;
		// all Base::foo() function overloads became visible
	};
	
	int main()
	{
		Der myder;
	
		myder.foo(.9);		// output -> Der::foo(double)
		myder.foo(12);		// output -> Base::foo(int)
		myder.foo(12,12);	// output -> Base::foo(int,int)
		myder.foo(12,12,12);	// output -> Base::foo(int,int,int)
	}
*/

/*
	class Base {
	private:
		void foo(int);
	};
	
	class Der : public Base {
	public:
	
		void foo(int);
		using Base::foo; // syntax error [using decleration to Base classes private section]
		// E0265 function "Base::foo" (declared at line 737) is inaccessible
	};
*/

/*
	=========================
	| inherited constructor |
	=========================
*/

/*
	class Base {
	public:
		void foo();
	
		// Base classes constructors
		Base(int);
		Base(int, int);
		Base(double);
	};
	
	class Der : public Base {
	public:
		void func();
	
		// before Modern C++
		// -----------------------------------------------
		// Der(int x) : Base(x) {};			// 1
		// Der(int x,int y) : Base(x,y) {};		// 2
		// Der(double x) : Base(x) {};			// 3
	
		// after Modern C++
		using Base::Base;
	};
	
	int main()
	{
		Der myder; // syntax error -> Der() default ctor was deleted by compiler
		// Der() tries to call Base() default ctor, because of there is a user declared Base(int) ctor
		// there is no Base() default ctor. It will cause [Der() = delete;]
	
		// when we use [using Base::Base;] expression in Der classes public section
		Der myder1(12);
		// compiler will implicitly write a ctor like 1 [Der(int x) : Base(x) {};]
		Der myder2(1, 2);
		// compiler will implicitly write a ctor like 2 [Der(int x,int y) : Base(x,y) {};]
		Der myder3(12.5);
		// compiler will implicitly write a ctor like 3 [Der(double x) : Base(x) {};]
	}
*/

/*
	class Base {
	protected:
		// Base classes constructors are in PROTECTED section
		Base(int);
		Base(int, int);
		Base(double);
	};
	
	class Der : public Base {
	public:
		using Base::Base;
	};
	
	int main()
	{
		// when we use [using Base::Base;] expression in Der classes PROTECTED section
		Der myder1(12);		// syntax error
		Der myder2(1, 2);	// syntax error
		Der myder3(12.5);	// syntax error
		// all statements cause syntax error because Base classes ctors are in protected section
		// and client codes can not reach Base classes protected section
	}
*/

/*
	=========================
	| run-time polymorphism |
	=========================
*/

/*
	There are 3 types of Base classes member functions.

	1. Member functions that gave Derived classes, an interface and an implementation.

	2. Member functions that gave Derived classes, an interface and a default implementation.
		- If Base class has a function in type 2, that will make Base class, a polymorphic class.

	3. Member functions that gave Derived classes an interface but not an implementation.
		- If Base class has a function in type 3, that will make Base class, a polymorphic class.
		- If Base class has a function in type 3, that will make Base class, an abstract class.
			[polymorphic && abstract class(soyut sinif)]
		- Abstract classes can not be instantiated. We can not create an object from an abstract class.
		- We can create a pointer and a reference from an abstract class.
		- If a class is not an abstract class, it is concrete class(we can create an object from concrete class)
*/

/*
	// ---> TYPE 1 

	class Airplane {
	public:
		void fly(); // TYPE 1
	};
	
	class Airbus : public Airplane {
	
	};
*/

/*
	// ---> TYPE 2
	class Airplane {
	public:
		void fly();
		virtual void land(); // virtual function, TYPE 2
		// we can override land() function in derived class or
		// use land() function from base class in derived class.
	};
	
	class Airbus : public Airplane {
	};
*/

/*
	// ---> TYPE 3

	class Airplane {
	public:
		void fly();
		virtual void land();
		virtual void takeoff() = 0; // pure virtual function, TYPE 3
		// Because of base class have a pure virtual function, it is now an abstract class.
	};
	
	class Airbus : public Airplane {
	};
	
	int main()
	{
		Airplane x; // can not instantiate an abstract class.
		// E0322 object of abstract class type "Airplane" is not allowed.
	
		Airbus y; // syntax error.
		// Because of we did not override base classes pure virtual function,
		// now our derived class is also an abstract class.
		// E0322 object of abstract class type "Airbus" is not allowed.
	}
*/

/*
	// base.h
	class Base {
	public:
		virtual int foo(int, int)
		{
			// inline virtual member function (can be defined inside .h file)
		}
	};
	
	// base.cpp
	// if we want to define virtual function in .cpp file [DO NOT USE VIRTUAL KEYWORD not in function signature]
	int Base::foo(int x, int y)
	{
	
	}
*/

/*
	class Base {
	public:
		virtual int foo(int, int);
	};
	
	class Der : public Base {
	public:
		double foo(int, int); // syntax error
		// declaring a function with same name and same signature but different return type
		// as base classes virtual function is NOT VALID!
	
		double foo(int, double); // valid
		// names are same but signatures are different. This [double foo(int,double)],
		// IS NOT AN OVERRIDE of the base classes virtual function.
	
		int foo(int, int); // valid
		// this is an override function of base classes virtual function.
		// same as [int foo(int, int)override]
	};
*/

/*
	class Base {
	public:
		virtual int foo(int, int) const;
	};
	
	class Der : public Base {
	public:
		int foo(int, int); // valid
		// This is NOT OVERRIDE FUNCTION. Because signatures(const keyword is a part of signature) are different.
	
		int foo(int, int) const; // valid
		// This is an OVERRIDE FUNCTION of base classes virtual function.
		// same as [int foo(int, int) const override]
	};
*/

/*
	override keyword is CONTEXTUAL KEYWORD.
	- can be a keyword
	- can be an identifier.

	-> can still be used as an identifier for backward compatibility 
		coders might wrote a class called `override` before. 
		For not broking that codes `override` can be used as an identifier.
*/

/*
	class Base {
	public:
		virtual int foo(int, int);
	};
	
	class Der : public Base {
	public:
		int foo(int, int)override; // keyword
	};
	
	class override {
		// identifier
	};
	
	int override(int override)
	{
		// identifier
	}
*/

/*
	====================
	| virtual dispatch |
	====================
*/

/*
	If a virtual function called with 
	1. Base class pointer
	2. Base class reference

	The function that called will be understood in run time, NOT IN COMPILE TIME 
	[Late(Dynamic) binding]
*/

/*
	class Base {
	public:
		void func()
		{
			std::cout << "Base::func()\n";
		}
	
		virtual void bar()
		{
			std::cout << "Base::bar()\n";
		}
	};
	
	class Der : public Base {
	public:
		void func()
		{
			std::cout << "Der::func()\n";
		}
	
		void bar()override
		{
			std::cout << "Der::bar()\n";
		}
	};
	
	int main()
	{
		Der myder;
		Base* baseptr = &myder;
	
		baseptr->func();	// output -> Base::func()
		// func() is not a virtual function
		baseptr->bar();		// output -> Der::bar()
		// Base::bar() is a virtual function
	}
*/

/*
	#include "Car_1.h"
	
	void car_game_pointer(Car* p)
	{
		p->start();
		p->run();
		p->stop();
		std::cout << '\n';
	}
	
	void car_game_reference(Car& r)
	{
		r.start();
		r.run();
		r.stop();
		std::cout << '\n';
	}
	
	void car_game_value(Car c)
	{
		c.start();
		c.run();
		c.stop();
		std::cout << '\n';
	}
	
	int main()
	{
	
		Car* p = new Mercedes;
		car_game_pointer(p);		// Virtual Dispatch is working
		// output ->	
		// Mercedes has just started
		// Mercedes is running
		// Mercedes has just stopped
	
		car_game_reference(*p);		// Virtual Dispatch is working
		// output ->	
		// Mercedes has just started
		// Mercedes is running
		// Mercedes has just stopped
	
		car_game_value(*p);		// Virtual Dispatch IS NOT working [object slicing]
		// output ->	
		// Car has just started
		// Car is running
		// Car has just stopped
	
		// --------------------------------------------------------------------------------------
	
		Car* p_1 = new VolvoXC90;
		
		car_game_pointer(p_1);		// Virtual Dispatch is working
		// output ->	
		// VolvoXC90 has just started
		// VolvoXC90 is running
		// VolvoXC90 has just stopped
	
		// --------------------------------------------------------------------------------------
	
		// IF VolvoXC90 CLASS IS NOT OVERRIDING run() FUNCTION
		car_game_pointer(p_1);		// Virtual Dispatch is working
		// output ->	
		// VolvoXC90 has just started
		// Volvo is running ----------------------------> PARENT CLASSES[Volvo] run() function
		// VolvoXC90 has just stopped
	}
*/

/*
	#include "Car_2.h"
	
	void car_game(Car* p)
	{
		p->start();
		p->run();
		p->stop();
	
		p->open_sunroof(); // syntax error
		// name-lookup will applied for static type.
		// static type of this argument expression(Car* p) is Car*
		// and because of Car(Base) class did not have a member function as open_sunroof()
		// (only derived class Mercedes has it) it will throw a syntax error.
	}
	
	int main()
	{
		Car* c = new Mercedes;
		car_game(c);
	}
*/

/*
	#include "Car_3.h"
	
	void car_game(Car* p)
	{
		p->test_car();
	}
	
	int main()
	{
		Car* c = new Mercedes;
		car_game(c);
	
		// output ->
		// Mercedes has just started
		// Mercedes is running
		// Mercedes has just stopped
	
		// virtual dispatch also applied when we call a non-virtual function,
		// which is calling virtual functions with [this pointer]
	}
*/

/*
	class Base {
	public:
		virtual void foo()
		{
			std::cout << "Base::foo()\n";
		}
	};
	
	class Der : public Base {
	private:
		void foo()override
		{
			std::cout << "Der::foo()\n";
		}
		// no syntax error
		// overriding Base virtual function in derived classes private section.
	};
	
	void gf(Base* p)
	{
		p->foo();
	}
	
	int main()
	{
		Der myder;
		gf(&myder); // output -> Der::foo()
		// virtual dispatch mechanism applied in RUN TIME.
		// access control phase is in compile-time (static type).
		// access control applied to static type of argument expression (Base* p) which is [Base*]
		// foo() function in Base class is in public section, so no access control error.
		// in run-time because of there is no access control phase, virtual dispatch can happen
	
		myder.foo(); // syntax error
		// because static type is Der type and access control error happens
		// [foo() is in private section of Der class].
	}
*/

/*
	=====================================
	| non-virtual interface idiom (NVI) |
	=====================================
*/

/*
	class Base {
	public:
		void bar()
		{
			foo();
		}
	private:
		virtual void foo()
		{
			std::cout << "Base::foo()\n";
		}
	};
	
	class Der : public Base {
	private:
		void foo()override
		{
			std::cout << "Der::foo()\n";
		}
		// we can override Base classes virtual member function which is in private section.
	};
	
	void gf(Base* p)
	{
		p->foo(); // syntax error
		// static type access control error.
		// [foo() virtual function is Base class is in private section]
	
		p->bar();
		// non-static and non-virtual member function in public section of the base class 
		// can call virtual member function in private section.
		// virtual dispatch will be applied.
	}
	
	int main()
	{
		Base* b = new Der;
		gf(b);	// output -> Der::foo()
	}
*/

/*
	Virtual dispatch mechanism is not working, when
	1. object slicing
	2. in base classes ctor
	3. in base classes dtor
	4. when used qualified name[Car::start()] of base class, used in non-static member functions of base class
*/

/*
	#include "Car_4.h"
	
	int main()
	{
		Volvo vx;
	
		// For Volvo::Volvo() -> ctor function
	
		// output ->
		// Car has just started
		// Car is running
		// Car has just stopped
	
		// Virtual dispatch mechanism is not working!!
		// Before derived class become alive
		// first Base class needs to become alive then derived classes other data members,etc..
		// Virtual dispatch can not be applied inside of base classes constructor because
		// when executing Base() classes constructor function, derived class is still NOT alive.
		// calling member functions of a class which is not alive is not possible.
	
	
		// For Volvo::~Volvo() -> dtor function
	
		// output ->
		// Car has just started
		// Car is running
		// Car has just stopped
	
		// Virtual dispatch mechanism is not working!!
		// Before derived class objects get destroyed,
		// first data members, then base class object inside derived class then derived class object will get destroyed.
		// Virtual dispatch mechanism can not be applied inside of base classes destructor because
		// if virtual dispatch happens, we seem like using the destroyed base class object in derived class object.
		// That will cause undefined behaviour.
	}
*/

/*
	#include "Car_5.h"
	
	int main()
	{
		Volvo vx;
		vx.test_car();

		// Virtual dispatch mechanism is not working!!
		// when we use qualified name[Car::start()] of base class
		// base classes member functions will be called.
	
		// output ->
		// Car has just started
		// Car is running
		// Car has just stopped
	}
*/

/*
	class Base_1{
	private:
		int mx, my;
		virtual void foo();
	};
	
	class Base_2 {
	private:
		int mx, my;
		virtual void foo();
		virtual void bar();
	};
	
	class Der : public Base_1 {
	
	};
	
	int main()
	{
		// For x64(pointer is 8 byte) system
	
		std::cout << "sizeof(Base_1) = " << sizeof(Base_1) << '\n';
		// output -> sizeof(Base_1) = 16 -> 2 int and 1 pointer
	
		std::cout << "sizeof(Base_2) = " << sizeof(Base_2) << '\n';
		// output -> sizeof(Base_2) = 16 -> 2 int and still 1 pointer
	
		std::cout << "sizeof(Der) = " << sizeof(Der) << '\n';
		// output -> sizeof(Der) = 16 -> 2 int and 1 pointer
	
		// Virtual function table pointer[vptr] is embedded in Base class.
		// vptr is pointing to(have an address of) the virtual function table in heap memory.
	}
*/

/*
	* Every polymorphic object have to instantiate the virtual function pointer to become alive.
	 
	* For Each polymorphic object class, 1 virtual function table created in heap.
	
	If we have 100 Volvo object(derived class) created in run time, 
	we will have 100 virtual function pointer and 1 virtual function table created in heap.
*/

/*
	===================================
	| virtual constuctor(clone) idiom |
	===================================
*/

/*
	// static member functions and global(free) functions can not be virtual.
	// constructors can not be virtual
	
	class Myclass {
	public:
		virtual void foo(); 		// legal
		static virtual void foo(); 	// not legal
	
		virtual Myclass(int); 		// not legal
	};
	
	virtual void gfoo(); 			// not legal
*/

/*
	#include "Car_6.h"
	
	void car_game(Car* p)
	{
		// How to create a copy of, derived class of Car inside this function ?
		// If Volvo comes as an argument WE need to clone the same Volvo
		p->start();
	
		Car* pnewcar = p->clone();
		pnewcar->start();
		pnewcar->run();
		pnewcar->stop();
	
		// output
		// Volvo has just started
		// Volvo has just started
		// Volvo is running
		// Volvo has just stopped
	}
	
	int main()
	{
		Car* p = new Volvo;
		car_game(p);
	}
*/

/*
	=========================
	| covariance		|
	| variant return type	|
	| covariant		|
	=========================
*/

/*
	class B{};
	// class D{};
	class D : public B {};

	class Base {
	public:
		virtual B* foo();
		virtual B& foo_2();

		virtual B func();
	};

	class Der : public Base {
	public:
		D* foo()override;
		// if D class is not derived from B class, syntax error.
		// 'Der::foo': overriding virtual function return type differs and is not covariant from 'Base::foo'

		D& foo_2()override;
		D func()override; // syntax error
		// covariance is legal ONLY when the return type is a pointer or reference !!
	};
*/

/*
	#include "Car_9.h"

	int main()
	{
		Audi* p = new Audi;
		Audi* pa = p->clone(); // clone() override of Audi class is returning Car* type (not legal)
		Audi* pa = static_cast<Audi*>(p->clone()); // legal

		Volvo* vp = new Volvo;
		Volvo* pv = vp->clone(); // clone() override of Volvo class is returning Volvo* type (legal, covariance)
	}
*/

/*
	#include "Car_7.h"
	
	int main()
	{
		Car* v = new Volvo;
		Car* a = new Audi;
	
		// How can we write a function, when we dereference it, it will write derived class name
		// If Volvo -> "I am a Volvo"
		// If Audio -> "I am an Audi"
		// How to make global function virtual ?
		std::cout << *v << '\n';
		std::cout << *a << '\n';
	}
*/

/*
	======================
	| virtual destructor |
	======================
*/

/*
	class Base {
	public:
		// ~Base()
		// {
		// 	std::cout << "Base dtor\n";
		// }

		virtual ~Base()
		{
			std::cout << "Base dtor\n";
		}
	};

	class Der : public Base {
	public:
		~Der()
		{
			std::cout << "Der dtor is releasing resources\n";
		}
	};

	void foo(Base* p)
	{
		delete p;
	}

	int main()
	{
		Base* baseptr = new Der;
		foo(baseptr);
		// undefined behaviour happens because, we are deleting Base object inside derived class
		// but not deleting Derived class object itself.
		// output -> Base dtor

		// When we make base classes dtor virtual, dispatch mechanism started working.
		// First Base dtor called inside Der dtor function then Der dtor finished executing.
		// output ->
		// Der dtor is releasing resources
		// Base dtor
	}
*/

/*
	Polymorphic Base classes dtor needs to be,
	----------------------------------------------
	* public virtual
	- When client called Base classes dtor with a derived class object instance
	public virtual dtor lets virtual dispatch works and do not create an undefined behaviour.

	OR

	* protected non virtual
	- When we use protected specifier in non virtual Base classes destructor,
	client can not reach Base classes dtor and can not delete Base class.
	- Client needs to call derived class dtor to reach protected section of Base class.
	Because Derived classes can reach Base classes protected section, it can call Base classes dtor in protected section.
*/

/*
	class Base {
	protected:
		~Base()
		{
			std::cout << "Base dtor\n";
		}
	};
	
	class Der : public Base {
	public:
		~Der()
		{
			std::cout << "Der dtor is releasing resources\n";
		}
	};
	
	int main()
	{
		Base* baseptr = new Der;
		delete baseptr; // syntax error
		// client tries to reach Base classes protected section.
	
		Der* derptr = new Der;
		delete derptr; // no sythax error.
		// client will reach Base::~Base() from Der::~Der which is in the public section
	}
*/

/*
	class Base {
	public:
		virtual void vfunc(int x = 5)
		{
			std::cout << "Base::vfunc(int x) x = " << x << '\n';
		}
	};
	
	class Der : public Base{
	public:
		void vfunc(int x = 9) override
		{
			std::cout << "Der::vfunc(int x) x = " << x << '\n';
		}
	};
	
	int main()
	{
		Der myder;
		Base* p = &myder;
		p->vfunc();	// output -> Der::vfunc(int x) x = 5
	
		// Virtual dispatch works but default argument type is related with static type
		// compiler will call the function in compile time [p->vfunc(5)] with an argument of int(5)
	
		myder.vfunc();	// output -> Der::vfunc(int x) x = 9
		// static type of default argument is 9 in compile time now.
	}
*/

/*
	// overload functions can be overriden too.

	class Base {
	public:
		virtual void func(int);
		virtual void func(double);
		virtual void func(int,int);
	
		virtual void foo();
		virtual void foo()const; // const overload
	};
	
	class Der : public Base {
	public:
		void func(int) override;
		void func(double) override;
		void func(int, int) override;
	
		void foo() override;
		void foo()const override; // const overload function's override
	};
	
	void gf(Base& r)
	{
		r.foo();
		r.func(1);
		r.func(1.45);
		r.func(2,2);
	}
*/

/*
	======================================
	| final keyword (contextual keyword) |
	======================================
	// can be used as an identifier and a keyword
*/

/*
	class Base {
	
	};
	
	class Der final : public Base {
	
	};
	
	class SDer : public Der {
		// syntax error
		// E1904 a 'final' class type cannot be used as a base class
	};
*/

/*
	class Base {
	public:
		virtual void foo();
		virtual void func();
	};
	
	class Der : public Base {
	public:
		virtual void foo() override;
		virtual void func() override final; // final virtual member function
	};
	
	class SDer : public Der {
		virtual void foo() override;
		virtual void func() override; // can not be overriden
		// because virtual member function Der::func() declare func() as a 'final'
	};
*/

/*
	==================================================
	| Run time type identification(information) RTTI |
	==================================================
*/

/*
	1. dynamic_cast operator
	2. typeid operator
	3. type_info class

	are used for RTTI 
*/

/*
	----------------------------------
	| dynamic_cast operator for RTTI |
	----------------------------------
*/

/*
	class Base {
	public:
		// virtual void bar();
	};
	
	class Der : public Base{
	
	};
	
	int main()
	{
		Der myder;
		Base* baseptr = &myder;
	
		Der* derptr = dynamic_cast<Der*>(baseptr);
		// baseptr NEEDS TO BE A POLYMORPHIC CLASS( have at least 1 virtual or pure virtual function.)
		// E0698 the operand of a runtime dynamic_cast must have a polymorphic class type
	}
*/

/*
	// dynamic_cast operator examines that downcasting(casting Base class to Derived class) can be done securely.
	
	#include "Car_8.h"
	
	void car_game(Car* carptr)
	{
		std::cout << *carptr << '\n';
		carptr->start();
		carptr->run();
		carptr->stop();
	
		// how can we understand the car that came here is a Volvo ?
	
		// !!! if casting fails it will return nullptr !!!
		if (Volvo* vp = dynamic_cast<Volvo*>(carptr))
		{
			vp->open_sunroof();
		}
		std::cout << '\n';
	}
	
	int main()
	{
		Car* cp = new Volvo;
		car_game(cp);
		// dynamic cast succeeds. Downcasting applied.
		
		Car* cp_2 = new Audi;
		car_game(cp_2);
		// dynamic cast fails.
		
		Car* cp_3 = new VolvoXC90;
		car_game(cp_3);
		// dynamic cast succeeds. Upcasting applied.
		// from VolvoXC90 to Volvo
		
		delete cp;
		delete cp_2;
		delete cp_3;
	}
*/

/*
	#include "Car_8.h"
	
	void car_game(Car& car_ref)
	{
		std::cout << car_ref << '\n';
		car_ref.start();
		car_ref.run();
		car_ref.stop();
	
		try
		{
			auto& vr = dynamic_cast<Volvo&>(car_ref);
			vr.open_sunroof();
		}
		catch (const std::exception& ex)
		{
			std::cout << "exception caught: " << ex.what() << '\n';
		}
	
		std::cout << '\n';
	}
	
	int main()
	{
		Car* cp = new Volvo;
		Car* cp_2 = new Audi;
	
		car_game(*cp);
		// cast succeeds.
		car_game(*cp_2);
		// bad_cast exception
	
		delete cp;
		delete cp_2;
	}
*/

/*
	----------------------------
	| typeid operator for RTTI |
	----------------------------
*/

/*
	an expression created with typeid operator is in fact 
	a const reference to an object from std::type_info class
*/

/*
	#include <typeinfo>
	
	class Myclass{};
	int main()
	{
		int x = 10;
	
		typeid(Myclass); // type is -> const type_info
		const std::type_info& r = typeid(Myclass);
	
		// WE CAN NOT CREATE AN OBJECT FROM TYPE_INFO CLASS!!
	
		std::type_info a; // syntax error
		// does not have a default ctor.
		std::type_info b = typeid(Myclass); // syntax error
		// copy ctor is deleted.
	
		Myclass mx;
	
		auto c = typeid(Myclass) == typeid(mx); 
		std::cout << std::boolalpha << c << '\n'; // output -> true
		// type_info objects have an operator==() overload function
	}
*/

/*
	class Base {
	public:
		// virtual ~Base() = default;
	};
	
	class Der : public Base {
	
	};
	
	int main()
	{
		Der myder;
		Base* baseptr = &myder;
	
		// If Base class is not polymorphic class [related to static type]
		std::cout << (typeid(*baseptr) == typeid(Der)) << '\n'; 	// output -> 0
		std::cout << typeid(*baseptr).name() << '\n';			// output -> class Base
	
		// If Base class is a polymorphic class [related to dynamic type]
		std::cout << (typeid(*baseptr) == typeid(Der)) << '\n'; 	// output -> 1
		std::cout << typeid(*baseptr).name() << '\n';			// output -> class Der
	}
*/

/*
	#include "Car_8.h"
	
	void car_game(Car* carptr)
	{
		std::cout << *carptr << '\n';
		carptr->start();
		carptr->run();
		carptr->stop();
	
		if (typeid(*carptr) == typeid(Volvo))
		{
			// if VolvoXC90 comes it will not get inside if-block.
			// only Volvo type can get inside if-block
	
			Volvo* vp = static_cast<Volvo*>(carptr);
			vp->open_sunroof();
		}
		std::cout << '\n';
	}
	
	int main()
	{
		Car* cp = new Volvo;
		Car* cp_2 = new Audi;
		Car* cp_3 = new VolvoXC90;
	
		car_game(cp);
		car_game(cp_2);
		car_game(cp_3);
	
		delete cp;
		delete cp_2;
		delete cp_3;
	}
*/

/*
	// unevaluated context typeid() operator
	// compiler did not create an operation code for typeid() operator
	
	int main()
	{
		int x = 10;
	
		auto& r = typeid(x++);
		std::cout << x << '\n'; // output -> 10 (no side effect)
	
		int a[10];
		auto& ref = typeid(a[40]); // no undefined behaviour happening
	}
*/

/*
	=======================
	| private inheritance |
	=======================
*/

/*
	-> Base classes public section will be in your derived classes private section.
	-> Clients can not reach Base classes public member function from with Der object.

	--> Upcasting is no valid in global functions.
	--> Upcasting is valid in derived classes member functions
	--> Upcasting is valid in friend functions of derived class.
*/

/*
	class Base {
	public:
		void foo();
	};
	
	class Der : private Base {
		void bar()
		{
			foo(); // legal
		}
	
		void conversion()
		{
			Der myder;
			Base* baseptr = &myder;
			Base& baseref = myder;
			// upcasting is legal in derived classes member functions
		}
	
		friend void func();	// global friend function.
	};
	
	void func()
	{
		Der myder;
		Base* baseptr = &myder;
		Base& baseref = myder;
		// upcasting is legal inside friend functions of derived class(Der).
	}
	
	int main()
	{
		Der myder;
		myder.foo(); // not legal
		// In private inheritance, Base classes public interface added to
		// derived classes private interface.
	
		Base* baseptr = &myder; // syntax error
		Base& baseref = myder;	// syntax error
		// In private inheritance, no implicit conversion from derived class to base class in client code. [no upcasting]
	}
*/

/*
	// COMPOSITION (CONTAINMENT)
	class A {
	protected:
		void protectedAfunc();
	public:
		void Afoo();
	
		virtual void virtualAFoo();
	};
	
	class B {
	public:
		void bar()
		{
			ma.Afoo();
			ma.protectedAfunc(); // not possible to reach class A's protected section, no inheritance
		}
	
		void afoo() // forwarding function
		{
			ma.Afoo();	// possible to reach class A's public section.
		}
	
		virtual void virtualAFoo() override; // not valid to override a member objects virtual function
	private:
		A ma; // member object
	};
	
	// * B class can use A classes public section(function) by its members.
	//	-> reaching class A's public function from B classes member function[bar()]
	// * B class can add class A's public section to its interface.
	//	-> B class have a forwarding function to add Class A's public interface to it's interface.
	
	// * A class can not reach its member objects protected section.
	// * It is not valid for a class to override its member objects virtual function.
	// * There is no implicit conversion from B class to its member object class(class A)
	
	
	
	// PRIVATE INHERITANCE
	class AA {
	protected:
		void protectedAAfunc();
	public:
		void AAfoo();
		virtual void virtualAAFoo();
	};
	
	class BB : private AA {
	public:
		void bar()
		{
			AAfoo();		// legal	
			// we can reach our base classes public section
			protectedAAfunc(); 	// legal
			// we can reach our base classes protected section.
		}
		using AA::AAfoo; // using decleration for BB to add AA classes private interface to itself.
	
		virtual void virtualAAFoo() override;
	};
	
	
	// * BB class can use AA classes public section(function) by its members.
	//	-> reaching class AA's member function in public section from BB classes member function[bar()]
	// * BB class can add class AA's public section to its interface.
	//	-> BB class can have a forwarding function to add Class AA's public interface to it's interface.
	//	-> With using decleration [using AA::AAfoo], BB class added it's base classes private section
	//	   to its interface.
	
	// * We can reach our base classes protected section.
	// * Overriding our base classes member function is perfectly valid.
	// * There is an implicit conversion from BB class to its Base class (class AA)
	//	-> from a friend function or from its member functions.
*/

/*
	---------------------------------
	| EBO (Empty Base Optimization) |
	---------------------------------
*/

/*
	class Empty {
	
	};
	
	class A {
	private:
		int mval;
		Empty ex;
	};
	
	class B {
	private:
		int mval;
	};
	
	class C : private Empty {
	private:
		int mval;
	};	// Empty Base Optimization applied when using private inheritance.
	
	int main()
	{
		std::cout << "sizeof(Empty) = " << sizeof(Empty) << '\n';	// output -> sizeof(Empty) = 1
		std::cout << "sizeof(A) = " << sizeof(A) << '\n';		// output -> sizeof(A) = 8
		// 3 bytes added for padding.
		std::cout << "sizeof(B) = " << sizeof(B) << '\n';		// output -> sizeof(B) = 4
		std::cout << "sizeof(C) = " << sizeof(C) << '\n';		// output -> sizeof(C) = 4
	}
*/

/*
	--------------------------
	| restricted polymophism |
	--------------------------
*/

/*
	class Base {
	public:
		virtual void vfunc();
	};
	
	class Der : public Base {
	public:
		void vfunc() override;
	};
	
	class Der_2 : private Base {
	public:
		void vfunc() override;
		friend void gf_2();
	};
	
	// No difference between public inheritance and private inharitance
	// in the context of overriding Base classes virtual function
	
	void foo(Base& baseref)
	{
		baseref.vfunc();
	}
	
	void gf_1()
	{
		Der myder;
		foo(myder); 	// legal 
		// upcasting is valid in global functions, in public inheritace
	
		Der_2 myder_2;
		foo(myder_2); 	// syntax error 
		// upcasting is NOT valid in global functions, in private inheritence
	}
	
	void gf_2()
	{
		Der myder;
		foo(myder); 	// legal 
		// upcasting is valid in global functions, in public inheritace
	
		Der_2 myder_2;
		foo(myder_2);	// legal
		// upcasting is valid in global functions with a friend decleration
	}
*/

/*
	=========================
	| protected inheritance |
	=========================
*/

/*
	class Base {
	public:
		void foo();
	};
	
	class Der : protected Base {
	public:
		void bar()
		{
			foo();
		}
	};
	
	class Der_Der : public Der {
	public:
		void baz()
		{
			bar();
	
			// ---> class Der : private Base
			// foo();
			// can not call foo() function
			// because of the private inheritence foo() function is in Der classes private section
	
			// ---> class Der : protected Base
			foo();
			// can call foo() function
			// because of the protected inheritence foo() function is in Der classes protected section
		}
	};
*/

/*
	========================
	| multiple inheritence |
	======================== 
*/

/*
	class X {};
	class Y {};
	
	class Der : public X, public Y {
		// public inheritance X
		// public inheritance Y
	};
	
	class Der_2 : public X, Y {
		// public inheritance X
		// private inheritance Y
	};
	
	class Der_3 : X, Y {
		// private inheritance X
		// private inheritance Y
	};
	
	struct Der_4 : X, Y {
		// public inheritance X
		// public inheritance Y
	};
*/

/*
	class X {
		int mx;
	};
	class Y {
		int my;
	};
	
	class Der : public X, public Y {
	};
	
	int main()
	{
		std::cout << "sizeof(X) = " << sizeof(X) << '\n';		// output -> sizeof(X) = 4
		std::cout << "sizeof(Y) = " << sizeof(Y) << '\n';		// output -> sizeof(Y) = 4
		std::cout << "sizeof(Der) = " << sizeof(Der) << '\n';		// output -> sizeof(Der) = 8
	}
*/

/*
	class X {
	public:
		X()
		{
			std::cout << "X default ctor\n";
		}
	
		X(int a)
		{
			std::cout << "X(int a) a = " << a << '\n';
		}
	};
	class Y {
	public:
		Y()
		{
			std::cout << "Y default ctor\n";
		}
	
		Y(int b)
		{
			std::cout << "Y(int b) b = " << b << '\n';
		}
	};
	
	class Der : public X, public Y {
	
	public:
		Der() : Y(1), X(9)
		{
			std::cout << "Der default ctor\n";
		}
	};
	
	int main()
	{
		Der myder;
		// output ->
		// Y default ctor
		// X default ctor
	
		// X base class is written before Y base class -> class Der : public X, public Y
		// X object will become alive first then Y object will become alive
	
		// output ->
		// X(int a) a = 9
		// Y(int b) b = 1
		// Der default ctor
	
		// It is better writing ctor initializer list in the same order of Base classes inheritance definition.
		// class Der : public X, public Y
		// Der() : X(9), Y(1)
	}
*/

/*
	class X {
	public:
		void xf();
	};
	
	class Y {
	public:
		void yf();
	};
	
	class Der : public X, public Y {
	
	};
	
	void foo(X&);
	void foo(Y&);
	
	void bar(X*);
	void bar(Y*);
	
	int main()
	{
		Der myder;
		myder.xf();
		myder.yf();
		// both base classes public interfaces are in derived classes public interface now.
	
		X* ptr = &myder;
		Y* ptr = &myder;
		X& ref = myder;
		Y& ref = myder;
		// upcasting is valid for both base classes.
	
		foo(myder); // ambiguity
		foo(static_cast<X&>(myder));
		foo(static_cast<Y&>(myder));
	
		bar(&myder); // ambiguity
		bar(static_cast<X*>(&myder));
		bar(static_cast<Y*>(&myder));
	}
*/

/*
	class X {
	public:
		virtual void xf(int){}
	};
	
	class Y {
	public:
		virtual void yf(int,int){}
	};
	
	class Der : public X, public Y {
	public:
		virtual void xf(int) override
		{
			std::cout << "Der::xf(int)\n";
		}
	
		virtual void yf(int,int) override
		{
			std::cout << "Der::yf(int,int)\n";
		}
	};
	
	void foo(X& xr, Y& yr)
	{
		xr.xf(0);	// output -> Der::xf(int)
		yr.yf(0, 12);	// output -> Der::yf(int,int)
	}
	
	int main()
	{
		Der myder;
		foo(myder, myder);
	}
*/

/*
	class BaseX {
	public:
		void foo();
	};
	
	class BaseY {
	public:
		void foo(int, int);
	};
	
	class Der : public BaseX, public BaseY {
	};
	
	int main()
	{
		Der myder;
	
		myder.foo(); // ambiguity
		// error C2385: ambiguous access of 'foo'
		// name-lookup will applied both Base classes, ambiguity error happens.
	
		myder.BaseX::foo();
		myder.BaseY::foo(1, 2);
		static_cast<BaseX&>(myder).foo();
		static_cast<BaseY&>(myder).foo(1,2);
		// disambiguity created.
	}
*/

/*
	class BaseX {
	public:
		void foo();
	};
	
	class BaseY {
	public:
		void foo(int, int);
	};
	
	class Der : public BaseX, public BaseY {
	public:
		using BaseX::foo;
		using BaseY::foo;
		// both BaseX::foo and BaseY::foo are visible with using decleration.
	};
	
	int main()
	{
		Der myder;
	
		myder.foo();
		myder.foo(12, 23);
	}
*/

/*
	----------------------------------------
	| DDD (Dreadful Diamond on Derivation) |
	----------------------------------------
*/

/*
	class Person {
	public:
		Person()
		{
			std::cout << "Person default ctor this : " << this << '\n';
		}
	
		void speak()
		{
			std::cout << "Person::speak() this : " << this << '\n';
		}
	};
	
	class Worker : public Person {
	
	};
	
	class Teacher : public Person {
	
	};
	
	class MathTeacher : public Worker, public Teacher {
	public:
		void solve_equation()
		{
			speak(); // ambiguity error
	
			Worker::speak();
			Teacher::speak();
			// disambiguity by using qualified names.
		}
	};
	
	int main()
	{
		MathTeacher mt;
		// output ->
		// Person default ctor this : 00AFFBD7 (Person class inside Worker class)
		// Person default ctor this : 00AFFBD8 (Person class inside Teacher class)
	
		mt.speak(); // ambiguity error
		// Are we going to use Worker::speak() or Teacher::speak() ??
	
		mt.Worker::speak();
		mt.Teacher::speak();
		// disambiguity by using qualified names.
		static_cast<Worker&>(mt).speak();
		static_cast<Teacher&>(mt).speak();
		// disambiguity by using static_cast operator.
		// output ->
		// Person::speak() this : 00AFFBD7
		// Person::speak() this : 00AFFBD8
	
	
		Person* p = &mt; // ambiguity error
	
		Person* p = static_cast<Teacher*>(&mt);
		Person* p = static_cast<Worker*>(&mt);
	}
*/

/*
	class Device {
	public:
		bool is_on()const
		{
			return m_flag;
		}
		void turn_on()
		{
			m_flag = true;
			std::cout << "Device is opened\n";
		}
		void turn_off()
		{
			m_flag = false;
			std::cout << "Device is closed\n";
		}
	private:
		bool m_flag{};
	};
	
	class Fax : public Device {
	public:
		virtual void send_fax(){
			if (is_on())
				std::cout << "fax has been sent\n";
			else
				std::cout << "fax can not sent because device is closed.\n";
		}
		virtual void recieve_fax(){
			if (is_on())
				std::cout << "fax has been recieved\n";
			else
				std::cout << "fax can not recieved because device is closed.\n";
		}
	};
	
	class Modem : public Device {
	public:
		virtual void send_packet() {
			if (is_on())
				std::cout << "packet has been sent\n";
			else
				std::cout << "packet can not sent because device is closed.\n";
		}
		virtual void recieve_packet() {
			if (is_on())
				std::cout << "packet has been recieved\n";
			else
				std::cout << "packet can not recieved because device is closed.\n";
		}
	};
	
	class FaxModem : public Fax, public Modem {
	
	};
	
	int main()
	{
		FaxModem fm;
	
		fm.Fax::turn_on();	// Device is opened
		fm.recieve_fax();	// fax has been recieved
		fm.send_packet();	// packet can not sent because device is closed.
	
		// Device in Fax is opened but Device in Modem is still closed.
	
		fm.Modem::turn_off();	// Device is closed
		fm.send_fax();			// fax has been sent
	
		// Device inside Fax is still open, fax can be sent.
	}
*/

/*
	=======================
	| virtual inheritance |
	=======================
*/

/*
	class Person {
	public:
		Person()
		{
			std::cout << "Person default ctor this : " << this << '\n';
		}
	
		void speak()
		{
			std::cout << "Person::speak() this : " << this << '\n';
		}
	};
	
	class Worker : virtual public Person {
		// virtual inheritance
	};
	
	class Teacher : virtual public Person {
		// virtual inheritance
	};
	
	class MathTeacher : public Worker, public Teacher {
	public:
		void solve_equation()
		{
			speak();
		}
	};
	
	int main()
	{
		MathTeacher mt; // output -> Person default ctor this : 0115F8A0
		// Default ctor() of Person class called only 1 time.
	
		mt.speak(); // output -> Person::speak() this : 0115F8A0
	
		Person* p = &mt;
		Person& r = mt;
	}
*/

/*
	class Device {
	public:
		bool is_on()const
		{
			return m_flag;
		}
		void turn_on()
		{
			m_flag = true;
			std::cout << "Device is opened\n";
		}
		void turn_off()
		{
			m_flag = false;
			std::cout << "Device is closed\n";
		}
	private:
		bool m_flag{};
	};
	
	class Fax : virtual public Device {
	public:
		virtual void send_fax() {
			if (is_on())
				std::cout << "fax has been sent\n";
			else
				std::cout << "fax can not sent because device is closed.\n";
		}
		virtual void recieve_fax() {
			if (is_on())
				std::cout << "fax has been recieved\n";
			else
				std::cout << "fax can not recieved because device is closed.\n";
		}
	};
	
	class Modem : virtual public Device {
	public:
		virtual void send_packet() {
			if (is_on())
				std::cout << "packet has been sent\n";
			else
				std::cout << "packet can not sent because device is closed.\n";
		}
		virtual void recieve_packet() {
			if (is_on())
				std::cout << "packet has been recieved\n";
			else
				std::cout << "packet can not recieved because device is closed.\n";
		}
	};
	
	class FaxModem : public Fax, public Modem {
	
	};
	
	int main()
	{
		FaxModem fm;
	
		fm.turn_on();			// Device is opened
		fm.recieve_fax();		// fax has been recieved
		fm.send_packet();		// packet has been sent
		// Device is opened for both Fax and Modem are opened.
	
		fm.turn_off();			// Device is closed
		fm.send_fax();			// fax can not sent because device is closed.
		fm.recieve_packet();		// packet can not recieved because device is closed.
		// When device is closed both Fax and Modem are closed.
	}
*/

/*
	class Base {
	public:
		Base(const char* p)
		{
			std::cout << p << '\n';
		}
	};
	
	class DerX : virtual public Base {
	public:
		DerX() : Base {"DerX"} {}
	};
	
	class DerY : virtual public Base {
	public:
		DerY() : Base{ "DerY" } {}
	};
	
	class DerZ : public DerX, public DerY {
	public:
		DerZ() : Base{ "DerZ" } {}
	};
	
	class DerA : public DerZ {
	public:
		DerA() : Base{ "DerA" } {}
	};
	
	class DerB : public DerA {
	public:
		DerB() : Base{ "DerB" } {}
	};
	
	
	int main()
	{
		DerB a;
	}
*/
