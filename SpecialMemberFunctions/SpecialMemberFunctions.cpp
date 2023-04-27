#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

/*
	============================
	| Special Member Functions |
	============================
*/

/*
	class Myclass {
		Myclass();				// default constructor
		~Myclass();				// destructor
	
		Myclass(const Myclass&);		// copy ctor
		Myclass(Myclass&&);			// move ctor
	
		Myclass& operator=(const Myclass&);	// copy assignment
		Myclass& operator=(Myclass&&);		// move assignment	
	};
*/

/*
	--------------------
	| copy constructor |
	--------------------
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
			std::cout << "destructor this = " << this << '\n';
		}
	
		Myclass(const Myclass&)
		{
			std::cout << "copy ctor this = " << this << '\n';
		}
	};
	
	int main()
	{
		Myclass m1;
	
		Myclass m2(m1);		// copy ctor called.
		Myclass m3{ m1 };	// copy ctor called.
		Myclass m4 = m1;	// copy ctor called.
		auto m5 = m1;		// copy ctor called.
	
		// output ->
		//	default ctor this = 012FFA43
		//	copy ctor this = 012FFA37
		//	copy ctor this = 012FFA2B
		//	copy ctor this = 012FFA1F
		//	copy ctor this = 012FFA13
		//	destructor this = 012FFA13
		//	destructor this = 012FFA1F
		//	destructor this = 012FFA2B
		//	destructor this = 012FFA37
		//	destructor this = 012FFA43
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
			std::cout << "destructor this = " << this << '\n';
		}
	
		Myclass(const Myclass&)
		{
			std::cout << "copy ctor this = " << this << '\n';
		}
	};
	
	void foo(Myclass param)	// call by value
	{
		std::cout << "inside foo()..\n";
	}
	
	int main()
	{
		Myclass m1;	// defult ctor will be called.
		foo(m1);	// copy ctor will be called.
	
		std::cout << "inside main()..\n";
	
		// output ->
		//	default ctor this = 00F5FCE7
		//	copy ctor this = 00F5FC00	param variable -> copy ctor
		//	inside foo()..
		//	destructor this = 00F5FC00	param variable dtor.
		//	inside main()..
		//	destructor this = 00F5FCE7
	}
*/

/*
	 IMPLICITLY DECLARED SPECIAL MEMBER FUNCTIONS ARE
		-> non-static
		-> public
		-> inline
*/

/*
	// Implicitly declared default ctor will default initialize all data members !!!!

	class Myclass {
	public:
		void print() const
		{
			std::cout << "a = " << a << "\n";
			std::cout << "b = " << b << "\n";
			std::cout << "c = " << c << "\n";
		}

	private:
		int a, b, c;
	};

	int main()
	{
		Myclass m;	// implicitly declared default ctor will be called.
		m.print();	// Undefined behaviour
	}

	// This code will create Undefined Behaviour
	// Implicitly declared default ctor will default initialize member variables.
	// a, b and c will have garbage(indetermined) value.
*/

/*
	class A {
	public:
		A()
		{
			std::cout << "default ctor A() is called\n";
		}
	};
	
	class Myclass {
	public:
	
	private:
		A m_a;
	};
	
	int main()
	{
		Myclass m;
		// 1. implicitly declared default ctor Myclass() will be called.
		// 2. Myclass() will default initialize m_a data member.
		// 3. to default initialize m_a, A() default ctor will be called.
	
		// output -> default ctor A() is called
	}
*/

/*
	class Myclass {
	public:

	private:
		const int mx;
	};

	int main()
	{
		Myclass m;
		// default constructor of "Myclass" cannot be referenced -- it is a deleted function
	}

	// When we default initialize Myclass object, its default ctor will called.
	// Default ctor's job is initializing all data members with default initialization.
	// const variables can not be default initialized so it will be a syntax error.
	// When syntax error happens in any special member funtion,
	// compiler will delete that special member function.
	// Myclass have a default ctor but it is deleted by the compiler.
*/

/*
	class Myclass {
	public:

	private:
		const int mx;
	};

	// when we compile this code. There won't be any syntax error.
	// because delete special member functions, in this case default ctor
	// is not creating any syntax error
*/

/*
	class Myclass {
	public:

	private:
		int& r;
	};

	int main()
	{
		Myclass m;
	}

	// default ctor is deleted by compiler 
	// references can not be default initialized.
*/

/*
	class A {
		A();
	};

	class Myclass {
	public:
		
	private:
		A m_a;
	};

	int main()
	{
		Myclass mx;

	}

	// Myclass's default ctor will default initialize m_a member variable.
	// For m_a data member to initialize, its default ctor A() have to be called.
	// A() default ctor can not be reach from Myclass, becuase it is in A classes private section.
	// That will create a syntax error. Compiler will delete Myclass()'s default ctor.
*/

/*
	class A {
	public:
		A(int);
	};

	class Myclass {
	public:

	private:
		A m_a;
	};

	int main()
	{
		Myclass mx;
	}

	// when any ctor declared, default ctor will not be declared by compiler.
	// Myclass's default ctor will default initialize m_a data member.
	// For m_a's default initialization A() default ctor needs to be called.
	// Because of there is user declared ctor A(int), A() is not declerad.
	// It will be syntax error and Myclass() default ctor will be deleted by the compiler.
*/

/*
	---------------------------------------------
	| constructor(member) initializer list [MIL]| 
	---------------------------------------------
*/

/*
	class Myclass {
	public:
		Myclass()
		{
			// IN THIS LINE mx and my data members are already alive.

			mx = 10; // this is not initialization, this is assignment
			my = 20;
		}
	private:
		int mx, my;
	};

	// const memmber variables and reference member variable can not be default initialized.
	// so we need to use constructor initializer list to initialize them.
*/

/*
	class Myclass {
	public:
		Myclass() : mx(10), my(20) //  this is initialization
		{ 
		}
	private:
		const int mx, my;
	};
*/

/*
	class B {
	public:
		B(int);
	};

	class A {
	public:
		A()
		{
		
		}
	private:
		B m_b;
	};

	int main()
	{
		A ax;
	}

	// When we call A classes default ctor, its data members will be default initialized.
	// For initializing B type data member m_b we need to call B() default ctor.
	// Because of B class has a ctor different than default ctor which is B(int)
	// its default ctor is not declared. So it was a syntax error.

	// ERROR : no default constructor exists for class "B"
*/

/*
	class Myclass {
	public:
		// Myclass(int a, int b) : ma(a), mb(b){}
		Myclass(int a, int b) : ma{ a }, mb{ b } {}
		// came with modern C++
		// narrowing conversion is NOT VALID.
	private:
		int ma, mb;
	};
*/

/*
	class Myclass {
	public:
		Myclass(int a, int b) : m_b{ a + b }, m_a{ m_b / 5 }
		{

		}
	private:
		int m_a, m_b; // First m_a then m_b will be created.

	};

	// Data members decleration order will be the order in constructor initializer list. 
	// In this scenerio first m_a then m_b will be created.
	// When we try to use m_a{ m_b / 5 } in initializer list because of 
	// m_b is not initialized(garbage value) yet, this code will be undefined behaviour.
*/

/*
	class Myclass {
	public:
		Myclass(int x) : m_a{}	// value initialize 
	private:
		int m_a;
	};
*/

/*
	#include <string>
	
	class Person {
	
		Person(const char* p_name, const char* p_surname)
		{
			m_name = p_name;
			m_surname = p_surname;
	
			// In this code data members(m_name, m_surname) first default initialized.
			// Their(std::string) default ctor have been called.
			// Then we use assignment functions to assign,
			// p_name and p_surname parameters to our data members.
		}
	
		Person(const char* p_name, const char* p_surname): m_name{p_name}, m_surname{p_surname}
		{
			// In this code we are initializing our data members with parameters.
			// We are calling string classes ctor with a parameter(const char*).
			// Prefer using Constructor Initializer List to initialize data members.
			// It is more efficient.
		}
	private:
		std::string m_name;
		std::string m_surname;
	};
*/

/*
	-------------------------------------------
	| implicitly declared defaulted copy ctor |
	-------------------------------------------
		-> public, 
		-> non-static 
		-> inline member function
*/

/*
	class Myclass {};

	void foo(Myclass);		// copy ctor (call by value function call)

	int main()
	{
		Myclass m1;		// default ctor
		Myclass m2 = m1;	// copy ctor
		Myclass m3(m1);		// copy ctor
		Myclass m4{ m1 };	// copy ctor
		auto m5 = m1;		// copy ctor
		auto m6(m1);		// copy ctor
		auto m7{ m1 };		// copy ctor

		Myclass m;		// default ctor
		foo(m);  // copy ctor will call for functions parameter variable
	}
*/

/*
	class Myclass {};

	Myclass g;

	Myclass foo()
	{
		return g;
	}

	int main()
	{
		Myclass x = foo();   // copy ctor will call for local variable x
	}
*/

/*
	class A{};
	class B{};
	class C{};
	
	class Myclass {
	public:
		Myclass(const Myclass& other) :
			m_a(other.m_a),
			m_b(other.m_b),
			m_c(other.m_c)
		{
	
		}
	private:
		A m_a;
		B m_b;
		C m_c;
	};
	
	// Implicitly declared defaulted copy ctor code is like this.
	// if A,B,C are primitive types, it will copy the data members.
	// if A,B,C are pointer types, it will copy the data members.
	// if A,B,C are classes, their copy constructors will be called too..
*/

/*
	class Date {
	public:
		Date(int day, int mon, int year) : m_day{day}, m_mon{mon}, m_year{year} {}

		// copy constructor
		Date(const Date& other) : m_day(other.m_day), m_mon(other.m_mon), m_year(other.m_mon)
		{
			std::cout << "this = " << this << '\n';
			// this pointer's value is the address of the object will be created by copy constructor.

			std::cout << "&other " << &other << '\n';
			// object that will bind to Date&(other) is the object that its data members will be copied.
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
		std::cout << "Address of dx(object that will used for copying) = " << &dx << '\n';
		std::cout << "Address of dy(object that copy ctor create) = " << &dy << '\n';
	}

	// output ->
	//	this = 010FFCE0
	//	& other 010FFCF4
	//	Address of dx(object that will used for copying) = 010FFCF4
	//	Address of dy(object that copy ctor create) = 010FFCE0
*/

/*
	#include <cstring>
	#include <cstdlib>

	class String {
	public:
		String(const char* p) : mlen{ std::strlen(p) }, mp{ static_cast<char*>(std::malloc(mlen + 1)) }
		{
			std::strcpy(mp, p);
		}

		~String()
		{
			std::free(mp);
		}

		void print()const
		{
			std::cout << mp << '\n';
		}

		std::size_t length()const
		{
			return mlen;
		}

		bool empty()const
		{
			return mlen == 0;
		}

	private:
		std::size_t mlen;
		char* mp;
	};

	void func(String copiedStr)
	{
		copiedStr.print();
	}

	int main()
	{
		String str{ "Hello world" };

		str.print();

		func(str);
		// Copy ctor will be used to create function parameter variable.
		// At the end of the function(func()) scope copiedStr's destructor will be called.
		// Its destructor will delete `mp`(pointer that points to string literal)
		// COPY CONSTRUCTOR IS DONE SHALLOW COPY

		str.print();
		// str object needs to reach its member variable `char* mp`, in print() member function.
		// Because of the memory in heap, that copiedStr.mp is deleted(free'd) at the end of the func() functions scope,
		// and because of both objects char* mp (str.mp && copiedStr.mp) points to the same string literal in heap.
		// Memory that str objects (char *)mp variable points to can have some other(garbage) values in it. 
		// Might already been used for any other purpose because of it is free'd.
		// str.mp became a dangling pointer. Reaching str.mp is Undefined Behaviour now.
	}
*/

/*
	#include <cstring>
	#include <cstdlib>

	class String {
	public:
		String(const char* p) : mlen{ std::strlen(p) }, mp{ static_cast<char*>(std::malloc(mlen + 1)) }
		{
			std::strcpy(mp, p);
		}
	
		// COPY CONSTRUCTOR THAT DONE DEEP COPY
		String(const String& other) : mlen(other.mlen), mp{ static_cast<char*>(std::malloc(mlen + 1)) }
		{
			std::strcpy(mp, other.mp);
		}
	
		~String()
		{
			std::free(mp);
		}
	
		void print()const
		{
			std::cout << mp << '\n';
		}
	
		std::size_t length()const
		{
			return mlen;
		}
	
		bool empty()const
		{
			return mlen == 0;
		}
	
	private:
		std::size_t mlen;
		char* mp;
	};

	void func(String copiedStr)
	{
		copiedStr.print();
	}

	int main()
	{
		String str{ "Hello world" };

		str.print();
		func(str);
		str.print();
	}
*/

/*
	-------------------
	| copy assignment |
	-------------------
*/

/*
	class A {};
	class B {};
	class C {};
	
	class Myclass
	{
		Myclass(const Myclass& other) : m_a(other.m_a), m_b(other.m_b), m_c(other.m_c)
		{
	
		}
	
		Myclass& operator=(const Myclass& other)
		{
			// x = y
			// x.operator=(y)
			// this pointer points to x objects address
			// other is y object
	
			m_a = other.m_a;
			m_b = other.m_b;
			m_c = other.m_c;
	
			return *this;
			// *this returns the assigned object itself.
			// assigned object is L value expression
		}
	
	private:
		A m_a;
		B m_b;
		C m_c;
	};

	// if A,B,C are primitive types, it will copy the data members.
	// if A,B,C are pointer types, it will copy the data members.
	// if A,B,C are classes, their copy assignment operator functions will be called too..
*/

/*
	class Date {
	public:
		Date(int day, int mon, int year) : m_day{day}, m_mon{mon}, m_year{year} {}


		Date& operator=(const Date& other)
		{
			m_day = other.m_day;
			m_mon = other.m_mon;
			m_year = other.m_year;
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

		dx.print();
		dy.print();

		dx = dy;
		// dx.operator=(dy);

		(dx = dy).print();
		// dx.operator=(dy).print();	// chaining

		// because of copy assignment operator returns an L value and dx object itself.
		// dx = dy;
		// dx.print() 
		// AND 
		// (dx = dy).print();
		// statements are same.
	}
*/

/*
	#include <cstring>
	#include <cstdlib>

	class String {
	public:
		String(const char* p) : mlen{ std::strlen(p) }, mp{ static_cast<char*>(std::malloc(mlen + 1)) }
		{
			std::strcpy(mp, p);
		}

		String(const String& other) : mlen(other.mlen), mp{ static_cast<char*>(std::malloc(mlen + 1)) }
		{
			std::strcpy(mp, other.mp);
		}

		String& operator=(const String& other)
		{
			// SELF ASSIGNMENT
			if(this == &other)
				return *this;
			// if this copy operator function called for same objects.
			// we are controling their addresses to check if their equal or not.
			// str.operator=(str); will return
			// str = str;

			mlen = other.mlen;
			// mp = other.mp; -> implicitly declared copy operator function does.

			std::free(mp);
			mp = static_cast<char*>(std::malloc(mlen + 1));
			std::strcpy(mp, other.mp);

			return *this;
		}
		~String()
		{
			std::free(mp);
		}

		void print()const
		{
			std::cout << mp << '\n';
		}

	private:
		std::size_t mlen;
		char* mp;
	};

	int main()
	{
		String s1{ "Hello World!" };
		s1.print();

		if(true)
		{
			String s2{ "I am robot" };
			s2.print();
			s2 = s1;
			s2.print();
		}

		s1.print();
	}
*/

/*
	---------------------------------
	| move ctor and move assignment |
	---------------------------------
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

		func(m);	// m is an L value expression
		// output -> func(const Myclass&) 

		func(Myclass{});			// Myclass{} is a temp object which is an R value expression
		// output -> func(Myclass&&)

		func(static_cast<Myclass&&>(m));  	// static_cast<Myclass&&>(m) is X value R value expression
		// output -> func(Myclass&&)

		func(std::move(m));			// std::move(m) change L value expression to R value expression
		// output -> func(Myclass&&)

		func(std::move(Myclass{}));		// R value expression Myclass{} still will be an R value expression
		// output -> func(Myclass&&)

		// if L value goes into std::move(Lvalue expression) goes out as an R value
		// if R value goes into std::move(Rvalue expression) also goes out as an R value
	}
*/

/*
	#include <string>
	
	std::string foo();
	
	int main()
	{
		std::string s1;
	
		s1 = foo();	// foo() function returns R value expression.
		// move assignment called.
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
		func(r);		// output -> const LVALUE REF
		func(std::move(r));	// output -> RVALUE REF
	}
*/

/*
	------------------------------------
	| implicitly declared move members |
	------------------------------------
*/

/*
	class A{};
	class B{};
	class C{};
	
	class Myclass {
	public:
		// implicitly declared move ctor by the compiler.
		Myclass(Myclass&& other) :
			m_a(std::move(other.m_a)),
			m_b(std::move(other.m_b)),
			m_c(std::move(other.m_c))
		{}
	
		// implicitly declared move assignment operator by the compiler.
		Myclass& operator=(Myclass&& other)
		{
			m_a = std::move(other.m_a);
			m_b = std::move(other.m_b);
			m_c = std::move(other.m_c);
			return *this;
		}
	private:
		A m_a;
		B m_b;
		C m_c;
	};

	// If A, B, C are classes their move assignment operator or move ctor will be called too.
*/

/*
	#include <cstring>
	#include <cstdlib>

	class String {
	public:
		String(const char* p) : mlen{ std::strlen(p) }, mp{ static_cast<char*>(std::malloc(mlen + 1)) }
		{
			std::strcpy(mp, p);
		}

		// move constructor
		String(String&& other) :mlen(other.mlen), mp(other.mp)
		{
			// When we use mp(other.mp) in constructor initializer list 
			// we basically copy other objects pointer data member(other.mp) to our
			// string objects pointer variable(mp)
			
			// After move ctor, other object will be deleted because its an R value object.
			// Because of R value objects dtor will be called, its data member pointer will be free'd. 
			// So because of both string objects have a data member pointer that points to the same address.
			// This will make our string objects pointer data member a dangling pointer. 
			// When data has been moved we need to secure ourselves.
			// In destructor we need to declare a condition by adding if 
			// objects data was stolen do not delete data member pointer.

			other.mp = nullptr;		// for our condition in destructor. 
			// Now our string object(this->mp) have the address.
			// We can set nullptr to other.mp because we won't use it anymore.
			other.mlen = 0;
		}
		// move assignment
		String& operator=(String&& other)
		{
			// SELF ASSIGNMENT CONTROL
			if (this == &other)
				return *this; 

			std::free(mp);
			// We first need to release the resource that our(this->mp) data member pointer points to.

			mlen = other.mlen;
			mp = other.mp;
			// We copy the other(R value objects) data member pointer.

			other.mp = nullptr;
			// Assign its pointer(other->mp) to nullptr to find out its data was stolen in destructor.
			other.mlen = 0;

			return *this ;
		}
		~String()
		{
			if (mp)   // If data member mp pointer is not nullptr, give its resource back.
				std::free(mp);
			// Else do not give its resource back for not making our objects pointer(this->mp) dangling
		}

	private:
		std::size_t mlen;
		char* mp;
	};
*/

/*
	// user did not declare any special member functions.
	// user did not declare any constructor.
	class Myclass {
	public:
		// both 6 special member functions are implicitly declared by the compiler.
	};
	
	class Myclass_imp{
	public:
		Myclass_imp() = default;
		~Myclass_imp() = default;
	
		Myclass_imp(const Myclass_imp&) = default;
		Myclass_imp& operator=(const Myclass_imp&) = default;
	
		Myclass_imp(Myclass_imp&&) = default;
		Myclass_imp& operator=(Myclass_imp&&) = default;
	};
	
	// Myclass is exactly same as Myclass_imp class!!!
*/

/*
	// if user declare a constructor which is not a default ctor.
	// Myclass default ctor is not declared.
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
	// if user declare a default ctor to Myclass
	class Myclass {
	public:
		Myclass();
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
	// if user declare a destructor to Myclass.
	// Move members are not declared.
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
	// if user declare a copy constructor to Myclass.
	// because of user declare a constructor, default ctor is not declared.
	// move members are not declared.
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
	// if user declared a copy asssignment operator function to Myclass.
	// move members are not declared.
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
	// if user declared move constructor
	// default ctor is not declared.
	// both copy members are deleted.
	// move assignment is not declared.
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
	// if user declared move assignment
	// copy members are deleted.
	// move constructor is not declared.
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
	3. non-copyable && movable classes
		-> istream, ostream classes
		-> std::thread class
		-> unique_ptr class
*/

/*
	// non-copyable && movable

	#include <thread>
	#include <memory>

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
		std::thread t1;
		std::thread t2 = t1;				// syntax error(copy ctor is deleted)
		std::thread t3 = std::thread{};			// valid (move ctor)
		t2 = std::move(t1);				// valid (move assignment)
	
	
		std::unique_ptr<int> uptr{ new int };
		std::unique_ptr<int> x = uptr;			// syntax error(copy ctor is deleted)
		std::unique_ptr<int> x = std::move(uptr);	// valid

		Myclass m1, m2;
		m1 = m2;					// syntax error
		Myclass m3 = m1;				// syntax error
		Myclass m4 = std::move(m1);			// valid
		m2 = std::move(m1);				// valid
	}
*/

/*
	// non-copyable && non-movable classes
	
	class Myclass {
	public:
		Myclass() = default;
		Myclass(const Myclass&) = delete;
		Myclass& operator=(const Myclass&) = delete;
	};
	// move members are not declared.
	
	int main()
	{
		Myclass m1;
		Myclass m2 = m1;		// syntax error
		// copy ctor is deleted.
	
		Myclass m3;
		m1 = m3;			// syntax error
		// copy assignment deleted
	
		m2 = std::move(m1);		// syntax error
		// move assignment not declared
		// copy assignment called and its deleted.
	
		Myclass m4 = std::move(m2);	// syntax error
		// move ctor is not declared.
		// copy ctor is called and its deleted.
	}
*/
