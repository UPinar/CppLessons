/*
	--------------------
	| moved-from state |
	--------------------
*/

/*
	C++ std library gave some guarantees for moved-from state objects.
		-> Object is in valid state.
		-> Object can be destructable.	[No Undefined Behaviour when destructor called.]
		-> Can be reusable(assignable).

	Easiest way to create moved-from state object is to make that object 
	return back to default initialized state.
*/

/*
	#include <string>
	
	int main()
	{
		std::string str(10'000, 'A');
	
		std::string s = std::move(str);
		// str objects resource was stolen.
		// str object's state become moved-from state.

		std::cout << str << '\n';	// output -> ""

		str = "Hello World!";
		// moved-from state objects are reusable.
		std::cout << str << '\n';	// output -> Hello World!
	}
*/

/*
	#include <string>
	#include <fstream>
	#include <vector>
	
	int main()
	{
		using namespace std;
	
		ifstream ifs{ "main.cpp" };
	
		if (!ifs) {
			cerr << "folder can not be opened\n";
			return 1;
		}
	
		string sline;
		vector<string> svec;
	
		while (getline(ifs, sline))
		{
			svec.push_back(std::move(sline));
		}
	}
*/

/*
	#include <string>

	void foo(std::string&& r)
	{
		std::string l_str = std::move(r);
		// r's type is R value reference and std::move(r) is an R value expression.
		// l_str's move ctor will be called.
	}

	void func(std::string&& r)
	{
		std::string l_str = r;
		// r's type is R value reference but r is an L value expression.
		// l_str's copy ctor will be called.
	}

	int main()
	{
		std::string str(20'000, '!');

		func(std::move(str));
		std::cout << "str.size() = " << str.size() << '\n'; // output -> str.size() = 20000
		// str's resource has been copied.

		foo(std::move(str));
		std::cout << "str.size() = " << str.size() << '\n';	// output -> str.size() = 0
		// str's resource has been stolen.
	}
*/

/*
	void func(const std::string& r)
	{
		std::string s = r; // copy ctor.

		std::string t;
		t = r; // copy assingment
	}

	void func(std::string&& r)
	{
		std::string s = std::move(r); // move ctor.
	}

	void foo(std::string&& r)
	{
		std::string s;
		s = std::move(r); // move assignment.
	}
*/

/*
	int main()
	{
		int x = 190;
	
		int y = x;
		int y = std::move(x);
		// These 2 lines are same. Both lines are copying x
	}
*/

/*
	int main()
	{
		int x = 10;
		int* p{ &x };

		int* ptr = p;
		int* ptr = std::move(p);
		// These 2 lines are same. Both lines are copying p.
	}
*/

/*
	class Myclass {
	public:
		// Myclass(const Myclass&other): mx(other.mx)	....
		// Myclass(Myclass&&): mx(std::move(other.mx))	....
	private:
		int mx, my, mz;
		int a[10];
		int* p1;
		int* p2;
	};
	
	// There is no difference between copy constructor and move constructor.
	// If data members are not classes there is no difference between move and copy ctors.
*/

/*
	class Myclass {
	public:
		// Myclass(const Myclass&other): mx(other.mstr)	....
		// Myclass(Myclass&&): mstre(std::move(other.mstr))	....
	private:
		std::string mstr;
		int mx, my, mz;
		int a[10];

	};

	// There is difference between copy and move constructors.
	// One of its data member is std::string class,
	// because of std::string classes copy and move ctor's are different.
	// Myclass's copy and move ctor's are different
*/

/*
	class A {
	public:
	
	private:
		int mx, my, mz;
		int a[10];
	};
	
	class Myclass {
	
	private:
		A m_a;
	};
	
	// There is no difference in Myclasses copy and move ctors.
	// Because there is no difference in A classes copy and move ctors.
*/

/*
	// when user declared one of move members, copy members become deleted.
	class MoveOnly {
	public:
		MoveOnly() = default;
		// MoveOnly(const MoveOnly&) = delete;
		// MoveOnly& operator=(const MoveOnly&) = delete;
		MoveOnly(MoveOnly&&);
		MoveOnly& operator=(MoveOnly&&);
	};

	class Myclass {
	private:
		MoveOnly mx;
	};
	// Myclasses copy ctor and copy assignments are deleted.

	// When we call Myclasses copy ctor it will call MoveOnly's copy ctor
	// and because MoveOnly classes copy ctor is deleted it will be syntax error
	// Because of the syntax error Myclasses copy ctor will be deleted by the compiler.
	// Same also applied in copy assignment.
	// Compiler will delete Myclasses copy assignment too.

	int main()
	{
		Myclass m1;
		Myclass m2 = m1; // sythax error
		// Myclasses copy ctor is implicitly declared deleted.

		Myclass m3, m4;
		m3 = m4;	// sythax error
		// Myclasses copy assignment is implicitly declared deleted.

		Myclass m5;
		Myclass m6 = std::move(m5);	// valid
		// Myclasses move constructor is implicitly declared defaulted.

		Myclass m7, m8;
		m7 = std::move(m8);		// valid
		// Myclasses move assignment is implicitly declared defaulted.
	}
*/

/*
	------------------------------
	| default member initializer |
	------------------------------
*/

/*
	class A {
	public:
		void print() const
		{
			std::cout << "mx = " << mx << '\n';
			std::cout << "my = " << my << '\n';
		}
	private:
		int mx;
		int my;
	};
	
	class B {
	public:
		// B() : mx(10), my(20) {} -> default ctor will be like this..
	
		void print() const
		{
			std::cout << "mx = " << mx << '\n';
			std::cout << "my = " << my << '\n';
		}
	private:
		// default member initializer.
		int mx = 10;
		int my{ 20 };
	};
	// implicitly declared default ctor will used default member initializer values
	// to initializer data members. It will not default initialize data members.
	
	
	int main()
	{
		A ax;
		ax.print();	// undefined behaviour
		// A class did not have default member initializer.
		// It's data members will be default initialized
		// (indetermined value for primitive types)
		// calling print() function is Undefined Behaviour
	
		B bx;
		bx.print();
		// B classes data members used default member initializer values in initialization phase.
		// output ->
		//	mx = 10
		//	my = 20
	}
*/

/*
	class A {
	public:
		A() : mx(12938), my(82939) {} // user declared default ctor.
	
		void print() const
		{
			std::cout << "mx = " << mx << '\n';
			std::cout << "my = " << my << '\n';
		}
	private:
		int mx = 10;
		int my{ 20 };
	};
	
	class B {
	public:
		B() : mx(12938) {} // user declared default ctor.
	
		void print() const
		{
			std::cout << "mx = " << mx << '\n';
			std::cout << "my = " << my << '\n';
		}
	private:
		int mx = 10;
		int my{ 20 };
	};
	
	int main()
	{
		A ax;
		ax.print();
		// output ->
		//	mx = 12938
		//	my = 82939
	
		B bx;
		bx.print();
		// output ->
		//	mx = 12938
		//	my = 20
	}
*/

/*
	-------------------------
	| delegated constructor |
	-------------------------
*/

/*
	class Myclass {
	public:
		Myclass() : Myclass(0, 0, 0)
		{
			std::cout << "Myclass() default ctor.\n";
		}
		// this ctor delegated 3 parameter ctor.
		Myclass(int x) : Myclass(x, x, x)
		{
			std::cout << "Myclass(int)\n";
		}
		// this ctor delegated 3 parameter ctor
		Myclass(int x, int y) : Myclass(x + y)
		{
			std::cout << "Myclass(int, int)\n";
		}
		// this ctor delegated 1 parameter ctor.
		Myclass(int a, int b, int c) : ma(a), mb(b), mc(c)
		{
			std::cout << "Myclass(int, int, int)\n";
		}
	
	private:
		int ma, mb, mc;
	};
	
	int main()
	{
		Myclass mx(5, 9);
		// First 2 parameter ctor delegate to 1 parameter ctor.
		// Then 1 parameter ctor delegate to 3 parameter ctor.
		// 3 parameter ctor's code will execute
		// Then 1 parameter ctor's code will execute.
		// At last 2 parameter ctor's code will execute.
	
		// output ->
		//	Myclass(int, int, int)
		//	Myclass(int)
		//	Myclass(int, int)
	}
*/

/*
	class Myclass {
	public:
		Myclass() : Myclass(111, 2222){}
		Myclass(int a, int b) : ma(a), mb(b){}
	
		void print() const
		{
			std::cout << "ma = " << ma << '\n';
			std::cout << "mb = " << mb << '\n';
			std::cout << "mc = " << mc << '\n';
		}
	
	private:
		int ma, mb, mc{ 33 };
	};
	
	int main()
	{
		Myclass mx;
		mx.print();
		// output ->
		//	ma = 111
		//	mb = 2222
		//	mc = 33
	}
*/

/*
	---------------------
	| temporary objects |
	---------------------
*/

/*
	void swap(T& r1, T& r2)
	{
		T temp(r1);
	
		r1 = r2;
		r2 = temp;
	}
	
	There are 2 problems in swap functions code.
		1. T can be a std::string and we are using copy ctor and copy assignment for std::string
			it is not efficient.
		2. T can be move only type e.g., unique_ptr

	void better_swap(T& r1, T& r2)
	{
		T temp(std::move(r1));

		r1 = std::move(r2);
		r2 = std::move(temp);
	}

	template <typename T>
	void Swap(T x, T y)
	{
		T temp(std::move(x));
		x = std::move(y);
		y = std::move(temp);
	}
*/

/*
	class Myclass {
	public:
		Myclass()
		{
			std::cout << "Myclass() default ctor this : " << this << '\n';
		}
	
		~Myclass()
		{
			std::cout << "~Myclass() destructor this : " << this << '\n';
		}
	
		Myclass(int x)
		{
			std::cout << "Myclass(int x) ctor x = " << x << " this : " << this << '\n';
		}
	};
	
	int main()
	{
		Myclass mx;
		mx = 19;
		std::cout << "main continues..\n";
	
	
		// output ->
		//	Myclass() default ctor this : 008FF92F
		//	Myclass(int x) ctor x = 19 this : 008FF863	-> Temp object
		//	~Myclass() destructor this : 008FF863		-> Temp object destroyed.
		//	main continues..
		//	~Myclass() destructor this : 008FF92F
	}
*/

/*
	int main()
	{
		const int& r = 45;
		// compiler will generate temp int object
		// const int& will bind to that temp object.
	}
*/

/*
	class Myclass {
	public:
		Myclass(int x, int y){}
		Myclass(){}
	private:
		int mx{}, my{};
	};
	
	int main()
	{
		Myclass();			// temp object	-> direct initialize
		Myclass(10, 20);	// temp object constructed with its 2 parameter constructor
		Myclass{};			// temp object	-> value initialize
	}
*/

/*
	// Temporary objects are PR value expression. R value expression.

	class Myclass{};

	int main()
	{
		Myclass& r = Myclass{};			// syntax error.
		// L value reference can not bind to R value expression.
		const Myclass& cr = Myclass{};	// legal
		Myclass&& rr = Myclass{};		// legal
	}
*/

/*
	class Myclass {};
	
	void foo(Myclass);
	void func(Myclass&&);
	void bar(const Myclass&);
	void baz(Myclass&);
	
	int main()
	{
		foo(Myclass{});		// valid (call by value)
		func(Myclass{});	// valid
		bar(Myclass{});		// valid
		baz(Myclass{});		// syntax error
	}
*/

/*
	#include <string>
	
	class Myclass {
	};
	
	void baz(const Myclass&);
	
	int main()
	{
		// statement1
		Myclass{};
		// statement2
	
		// In statement1 temporary object Myclass{} is not alive.
		// In statement2 temporary object Myclass{} is not alive,
		// its destructor is already called and executed.
	
	
		Myclass mx;
		baz(mx);
		// If we want to send an object will not used after baz() functions execution.
		// creating mx object will cause a scope leakage.
	
		{
			std::string str(10'000, 'A');
		}	// nested block for scope leakage.
	}
*/

/*
	class Myclass {
	public:
		Myclass(int x)
		{
			std::cout << "Myclass(int x) x = " << x << '\n';
		}
	
		~Myclass()
		{
			std::cout << "~Myclass() destructor\n";
		}
	};
	
	// life extension
	int main()
	{
		std::cout << "main starts\n";
		{
			std::cout << "main continues [1]\n";
			const Myclass& r = Myclass{ 12 };
			// Myclass{12} temporary objects life depends on r(const Myclass&)'s scope.
			std::cout << "main continues [2]\n";
		}
		std::cout << "main continues [3]\n";
	}
	
	// output ->
	//	main starts
	//	main continues[1]
	//	Myclass(int x) x = 12
	//	main continues[2]
	//	~Myclass() destructor
	//	main continues[3]
*/

/*
	--------------------------
	| conversion constructor |
	--------------------------
*/

/*
	class Myclass {
	public:
		Myclass()
		{
			std::cout << "Myclass default ctor this = " << this << '\n';
		}
	
		~Myclass()
		{
			std::cout << "Myclass destructor this = " << this << '\n';
	
		}
	
		Myclass(int x)
		{
			std::cout << "Myclass(int x) x = " << x << " this = " << this << '\n';
		}
	};
	
	int main()
	{
		Myclass m;
		m = 35;
	
		// output ->
		//	Myclass default ctor this = 00AFF80F
		//	Myclass(int x) x = 35 this = 00AFF80E	-> temporary object
		//	Myclass destructor this = 00AFF80E		-> temporary objects dtor
		//	Myclass destructor this = 00AFF80F
	}
*/

/*
	class Myclass {
	public:
		Myclass()
		{
			std::cout << "Myclass default ctor this = " << this << '\n';
		}
	
		~Myclass()
		{
			std::cout << "Myclass destructor this = " << this << '\n';
	
		}
	
		Myclass(int x)
		{
			std::cout << "Myclass(int x) x = " << x << " this = " << this << '\n';
		}
	
		Myclass& operator=(const Myclass& other)
		{
			std::cout << "Myclass copy assignment this = " << this << '\n';
			std::cout << "&other = " << &other << '\n';
			return *this;
		}		
		// normally move assignment will be called but because we declare copy assingment, 
		// move assignment will not be declared by the compiler
	};
	
	int main()
	{
		Myclass m;
		std::cout << "&m = " << &m << '\n';
		m = 35;
		std::cout << "main continues\n";
	
		// output ->
		//	Myclass default ctor this = 012FF71F	-> m objects ctor
		//	&m = 012FF71F							-> m objects address
		//	Myclass(int x) x = 35 this = 012FF71E	-> conversion ctor called, temporary object came alive.
		//	Myclass copy assignment this = 012FF71F	-> copy assignment called, temporary objects value assign to m object.
		//	&other = 012FF71E						-> temporary objects address
		//	Myclass destructor this = 012FF71E		-> temporary object destroyed.
		//	main continues
		//	Myclass destructor this = 012FF71F		-> m object destroyed end of the main scope.
	}
*/

/*
	User Defined Conversion
		-> conversion ctor
		-> type-cast operator function

	Standart Conversion + UDC	-> LEGAL
	UDC + Standart Conversion	-> LEGAL
	UDC + UDC					-> NOT LEGAL
*/

/*
	class Myclass {
	public:
		Myclass();
		Myclass(int);
	};
	
	int main()
	{
		Myclass m;
		double dval{ 2.3 };
	
		m = dval;
		// double ==> int ==> Myclass
		// Standart conversion + UDC
	}
*/

/*
	class Myclass {
	public:
		Myclass();
		Myclass(bool);
	};
	
	int main()
	{
		Myclass m;
		double dval{ 2.3 };
		auto pd = &dval;
	
		m = pd;	// valid
	
		// double* ==> bool ==> Myclass
		// Standart conversion + UDC
	}
*/

/*
	------------------------
	| explicit constructor |
	------------------------
*/

/*
	class Myclass {
	public:
		Myclass();
		explicit Myclass(int);	// explicit conversion only
		// Do not allow implicit conversion from int to Myclass
	};
	
	void foo(Myclass);
	void bar(const Myclass&);
	void baz(Myclass&&);
	
	Myclass func()
	{
		return 16;	// syntax error
	}
	
	int main()
	{
		Myclass m;
		m = 12;		// syntax error
	
		foo(13);	// syntax error
		bar(14);	// syntax error
		baz(15);	// syntax error
	}
*/

/*
	class Myclass {
	public:
		Myclass() = default;
		explicit Myclass(int)
		{
			std::cout << "explicit ctor called\n";
		}
	};
	
	int main()
	{
		int ival{ 2321 };
	
		Myclass m1, m2, m3;
		m1 = static_cast<Myclass>(ival);	// output -> explicit ctor called
		m2 = (Myclass)ival;					// output -> explicit ctor called
		m3 = Myclass(ival);					// output -> explicit ctor called
	}
*/

/*
	class Myclass {
	public:
		explicit Myclass(int);
	};
	
	int main()
	{
		Myclass m1(12);		// direct initialization is valid for explicit ctor.
		Myclass m2{ 15 };	// direct list initialization is valid for explicit ctor.
		Myclass m3 = 16;	// copy initialization is NOT VALID for explicit ctor.
	}
*/

/*
	#include <string>
	#include <vector>
	#include <stdexcept>
	#include <memory>
	
	int main()
	{
		std::string str = "hello world";	// VALID
		// std::string classes Cstring parameter ctor -> String(const char*) is not explicit!!
	
		std::vector<int> ivec = 123;		// NOT VALID
		// std::vector<int> classes int parameter ctor -> Vector(std::size_t) is explicit!!
		std::vector<int> ivec(123);			// VALID(direct initialization)
	
	
		std::runtime_error ex = "error!!";	// NOT VALID
		// std::runtime_error classes Cstring parameter ctor
		// -> Runtime_error(const char*) is explicit!!
		std::runtime_error ex("error!!");		// VALID(direct initialization)
	
	
		std::unique_ptr<int> uptr = new int; // NOT VALID
		// UniquePtr(int*) int* parameter ctor is explicit!! 
		std::unique_ptr<int> uptr(new int);	// VALID(direct initialization)
	}
*/

/*
	// myclass.h (header file)
	class Myclass {
	public:
		explicit Myclass(int);	// explicit ctor decleration
	};
	
	// myclass.cpp
	explicit Myclass::Myclass(int)
	{
		// SYNTAX ERROR
		// error C2178: 'Myclass::{ctor}' cannot be declared with 'explicit' specifier
	}
	
	Myclass::Myclass(int)
	{
		// VALID
	}
	// explicit keyword needs to be only in decleration NOT IN DEFINITION
*/

/*
	class Myclass {
	public:
		explicit Myclass(int)
		{
			std::cout << "explicit Myclass(int)\n";
		}
	
		Myclass(double)
		{
			std::cout << "Myclass(double)\n";
		}
	};
	
	int main()
	{
		Myclass m = 5;	// output -> Myclass(double)
		// explicit ctor is not in Function Overload Set
	}
*/

/*
	class A {
	public:
		A();
	};
	
	class B {
	public:
		B();
		B(A);	// conversion ctor
	};
	
	int main()
	{
		B bx;
		A ax;
	
		bx = ax;	// valid
		// User Defined Conversion
	}
*/

/*
	class A {
	public:
		A();
	};
	
	class B {
	public:
		B();
		B(A);	// conversion ctor
		void func();
	};
	
	int main()
	{
		B bx(A());	// most vexing parse
		bx.func();	// syntax error
		// 1. A function called bx which have a parameter type A(*)()
		//		and return type of B
		// 2. B object called bx, initialized with temp A object.
		// ----> most vexing parse will choose option 1.
	
		B bc((A()));
		bc.func();	// valid
	
		B bd(A{});
		bd.func();	// valid
	
		B be{ A() };
		be.func();	// valid
	
		B bf{ A{} };
		bf.func();	// valid
	}
*/

/*
	class A {
	public:
		A();
	};
	
	class B {
	public:
		B();
		B(A);	// conversion ctor
	};
	
	class C {
	public:
		C();
		C(B);	// conversion ctor
	};
	
	int main()
	{
		C cx;
		B bx;
		cx = bx;	// valid
	
	
		A ax;
		cx = ax;	// syntax error
		// ax object can be convert to B object with B(A) ctor -> [UDC] and
		// B object can be convert to C object with C(B) ctor ->  [UDC]
		// BUT implicitly 2 User Defined Conversion IS NOT VALID!!!
	}
*/

/*
	class A {
	public:
		A();
	};
	
	class B {
	public:
		B();
		B(A);	// conversion ctor
	};
	
	class C {
	public:
		C();
		C(B);	// conversion ctor
	};
	
	int main()
	{
		A ax;
		C cx;
	
		cx = static_cast<B>(ax);	// valid
		// from A to B explicit conversion
		// from B to C implicit USER DEFINED CONVERSION.
	}
*/

/*
	----------------
	| copy elision |
	----------------
	->	after C++17 some compiler optimization copy elisions, 
		become mandatory copy elision.

	-> If copy elision is not mandatory, and user deleted copy ctor
		it will be syntax error. But if it is a mandatory copy ellision, 
		copy ctor is not needed so deleted copy ctor will not be syntax error.
*/

/*
	--------------
	| Scenerio 1 |
	--------------
	If a function parameter variable's type is a class type,
	and calling this function with a PR value expression.
	Mandatory Copy Ellision will be applied.
*/

/*
	class Myclass {
	public:
		Myclass()
		{
			std::cout << "Myclass default ctor\n";
		}
		Myclass(int)
		{
			std::cout << "Myclass(int) ctor\n";
		}
	
		Myclass(const Myclass&)
		{
			std::cout << "Myclass copy ctor\n";
		}
	};
	
	void foo(Myclass)
	{
	
	}
	
	int main()
	{
		foo(Myclass{});
		// In normal, for temp object default ctor and
		// for functions parameter variable move or copy ctor will be called.
	
		// output -> Myclass default ctor
	
	
		foo(Myclass{12});
		// In normal, for temp object ctor with int parameter will be called.
		// for function parameter variable move or copy ctor will be called.
	
		// output -> Myclass(int) ctor
	}
*/

/*
	class Myclass {
	public:
		Myclass()
		{
			std::cout << "Myclass default ctor\n";
		}
		Myclass(int)
		{
			std::cout << "Myclass(int) ctor\n";
		}
	
		Myclass(const Myclass&) = delete;
	};
	
	void foo(Myclass)
	{
	
	}
	
	int main()
	{
		foo(Myclass{});			// output -> Myclass default ctor
		foo(Myclass{ 12 });		// output -> Myclass(int) ctor
	
		// This copy ellision becomes mandatory copy ellision after C++17
		// So deleting copy ctor will be a syntax error.
	}
*/

/*
	class Myclass{};

	void foo(Myclass);

	int main()
	{
		Myclass m1;
		foo(m1);		// no copy elision.	[Default ctor and copy ctor]

		foo(Myclass{});	// copy ellision [only default ctor]
	}
*/

/*
	-----------------------------------------------
	| Scenerio 2 (Return Value Optimization)[RVO] |
	-----------------------------------------------
	If a functions return value type is a class type,
	and this function will return PR value expression.
	Mandatory Copy Ellision will be applied.
*/

/*
	class Myclass {
	public:
		Myclass()
		{
			std::cout << "Myclass default ctor\n";
		}
		Myclass(int)
		{
			std::cout << "Myclass(int) ctor\n";
		}
	
		Myclass(const Myclass&)
		{
			std::cout << "Myclass copy ctor\n";
		}
	};
	
	Myclass foo()
	{
		// code
		return Myclass{};
	}
	
	Myclass bar()
	{
		// code
		return Myclass{ 12 };
	}
	
	int main()
	{
		Myclass m1 = foo();		// output -> Myclass default ctor
		// In normal, in foo() function default ctor will be called for temp object
		// Then for [Myclass m = foo()] statement copy ctor will be called.
	
		Myclass m2 = bar();		// output -> Myclass(int) ctor
	}
*/

/*
	class Myclass {
	public:
		Myclass()
		{
			std::cout << "Myclass default ctor\n";
		}
		Myclass(int)
		{
			std::cout << "Myclass(int) ctor\n";
		}
	
		Myclass(const Myclass&) = delete;
	};
	
	Myclass foo()
	{
		return Myclass{};
	}
	
	Myclass bar()
	{
		return Myclass{ 12 };
	}
	
	int main()
	{
		Myclass m1 = foo();		// output -> Myclass default ctor
		Myclass m2 = bar();		// output -> Myclass(int) ctor
	
		// No syntax error when user delete the copy ctor.
		// Because this copy elision becomes mandatory copy elision with C++17.
	}
*/

/*
	--------------------------------------------------------
	| Scenerio 3 (Named Returned Value Optimization)[NRVO] |
	--------------------------------------------------------
	NRVO is NOT a Mandatory copy elision !!!
	for NRVO a callable copy/move ctor is required.

*/

/*
	#include <string>
	
	std::string get_str()
	{
		std::string str;
		// code... (string manuplations)
		return str;
	}
	
	int main()
	{
		std::string retval = get_str();
		// In normal, for str object in get_str() function, default ctor will be called.
		// Move ctor will be called for [std::string retval = get_str()] statement.
	
		// But because of named return value optimization,  str object inside get_str() function
		// we be constructed as retval object.
	}
*/

/*
	class Myclass {
	public:
		Myclass()
		{
			std::cout << "Myclass default ctor\n";
		}
		Myclass(int x) :m_x(x)
		{
			std::cout << "Myclass(int) ctor\n";
		}
	
		Myclass(const Myclass& other) : m_x(other.m_x)
		{
			std::cout << "Myclass copy ctor\n";
		}
	
		void print() const
		{
			std::cout << "m_x = " << m_x << '\n';
		}
	
		void setx(int val)
		{
			m_x = val;
		}
	private:
		int m_x;
	};
	
	Myclass foo()
	{
		Myclass m{ 12 };
		m.setx(45);
		// code
		m.setx(23);
		return m;
	}
	
	int main()
	{
		Myclass m1 = foo();
		m1.print();
		// output ->
		//	Myclass(int) ctor
		//	m_x = 23
		// Only int parameter ctor called!!	-> NRVO
	}
*/

/*
	class Myclass {
	public:
		Myclass()
		{
			std::cout << "Myclass default ctor\n";
		}
		Myclass(int x) :m_x(x)
		{
			std::cout << "Myclass(int) ctor\n";
		}
	
		Myclass(const Myclass& other) = delete;
	
		void setx(int val)
		{
			m_x = val;
		}
	private:
		int m_x;
	};
	
	Myclass foo()
	{
		Myclass m{ 12 };
		m.setx(45);
		return m;
		// Because of NRVO is not a mandatory copy elision
		// deleted copy ctor will be a syntax error !!!!
	}
	
	int main()
	{
		Myclass m1 = foo();
	}
*/

/*
	--------------------
	| pessimistic move |
	--------------------
*/

/*
	class Myclass {
	public:
		Myclass() = default;
		Myclass(const Myclass&) = default;
		Myclass(Myclass&&) = default;
	
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
		// return std::move(x);	-> pessimistic move..
	
		// When returning automatic storage duration object
		// compiler will change L value object to X value object
		// so move assignment will call for this scenerio.
	}
	
	int main()
	{
		Myclass m1;
		m1 = foo();	// output -> move assignment called
	}
*/

/*
	#include <memory>
	
	std::unique_ptr<int> foo()
	{
		std::unique_ptr<int> up{ new int };
	
		return up;	// no syntax error
		// because up will convert L value to X value.
	}
	
	int main()
	{
		std::unique_ptr<int> up1{ new int };
		std::unique_ptr<int> up2{ new int };
	
		up1 = up2;		// copy assignment deleted
		auto up3 = up1;	// copy constructor deleted
		// SMART POINTERS ARE MOVE ONLY TYPES!!!
	
		up1 = std::move(up2);		// move assignment legal
		auto up3 = std::move(up2);	// move constructor legal
	}
*/

/*
	#include <fstream>
	#include <string>
	
	std::ofstream create_text_file(const std::string& filename)
	{
		std::ofstream ofs{ filename };
	
		if (!ofs) {
			throw std::runtime_error{ filename + "can not be created!" };
		}
	
		return ofs;	// move only type but compiler convert L value ofs to X value..
	}
	
	int main()
	{
		std::ofstream ofs{ "out.txt" };
		if (!ofs) {
			std::cerr << "out.txt can not be created\n";
			exit(EXIT_FAILURE);
		}
	
		auto x = ofs;				// no copy constructor
		auto y = std::move(ofs);	// move constructor is valid.
		// std::ofstream IS MOVE ONLY TYPE
	
		std::ofstream fs;
	
		fs = create_text_file("hello.txt");	// move assignment will be called
	}
*/

/*
	#include <string>
	
	void foo(std::string s) {}
	
	void bar(const std::string& s){}
	
	int main()
	{
	
		std::string str(100'000, 'A');
	
		foo(str);
		// foo functions parameter variable copy ctor will be called
		// deep copy will be applied
		bar(str);
		// no ctor will be called.
	
		// bar(str) will be the winner in this scenerio performance way.
	}
*/

/*
	#include <string>
	#include <algorithm>

	void foo(std::string s)
	{
		std::reverse(s.begin(), s.end());
	}

	void bar(const std::string& s)
	{
		auto sc = s;	// copy ctor will be called.
		std::reverse(sc.begin(),sc.end());
	}

	int main()
	{

		const char* ptr = "hello";

		bar(ptr);
		// temp object will be created for const char* to std::string conversion
		// const std::string& s(parameter variable) will bind to temp object.
		// then inside bar() function we will create its copy.
		// 2 TIME COPY

		foo(ptr);	// only std::string(const char*) ctor will be called
		// 1 TIME COPY

		foo(pr value expression); // copy ellision will be applied
	}
*/

/*
	#include <string>
	
	class Person {
	public:
		// Person(const std::string& addr) : m_address(addr){}
		// std::string classes copy ctor will be called
		// in initializing phase [m_address(addr)]
		// (IF L value comes) -> REF semantic + copy ctor
		// (IF R value comes) -> REF semantics + copy ctor
	
		Person(std::string addr) :m_address{std::move(addr)} {}
		// std::string classes move ctor will be called
		// in initializing phase [m_address(addr)]
		// (IF L value comes) -> copy ctor + move ctor
		// (IF R value comes) -> copy ellision + move ctor
	private:
		std::string m_address;
	};
	
	int main()
	{
		std::string x;
	
		Person per(x);
	}
*/

/*
	------------------------
	| reference qualifiers |	// Modern CPP
	------------------------
*/

/*
	class Myclass {
	public:
		Myclass& operator=(const Myclass&) = default;
		// Myclass& operator=(const Myclass&)& = default;
		void set();
		void set_lref()&;	// only can call with L value objects
	};
	
	int main()
	{
		Myclass x;
		x.set();					// valid
		Myclass{}.set();			// valid
	
		Myclass y;
		(x = y).set();				// valid
	
		x.set_lref();				// valid
		Myclass{}.set_lref();		// not valid
		std::move(x).set_lref();	// not valid
	
		Myclass{} = y;
		Myclass{}.operator=(y);
		// if we it is valid because compiler's default copy ctor
		// does not have reference qualifier
	
		// If we add reference qualifier to copy assignment
		// [Myclass& operator=(const Myclass&)& = default]
		// [Myclass{}.operator=(y)] or [Myclass{} = y] are not valid
	}
*/

/*
	class Myclass {
	public:
		void foo()&;		// L value reference qualified
		void bar()&&;		// R value reference qualified
	};
	
	int main()
	{
		Myclass m;
		m.foo();			// legal
		m.bar();			// not valid
	
		Myclass{}.foo();	// not valid
		Myclass{}.bar();	// legal
	}
*/

/*
	// we can overload reference qualifiers in non-static member functions

	class Myclass {
	public:
		void foo()&
		{
			std::cout << "foo() for L values\n";
		}

		void foo()const&
		{
			std::cout << "foo() for const L values\n";
		}
	
		void foo()&&
		{
			std::cout << "foo() for R values\n";
		}
	};
	
	int main()
	{
		Myclass m;
		m.foo();				// output -> foo() for L values
	
		Myclass{}.foo();		// output -> foo() for R values
		std::move(m).foo();		// output -> foo() for R values

		const Myclass cm;
		cm.foo();				// output -> foo() for const L values
	}
*/