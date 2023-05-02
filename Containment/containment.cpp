 #include <iostream>

/*
	=============================
	| composition / containment |
	=============================
*/

/*
	class A {
	private:
		void foo();
		// friend class B;
		// if class B declared as friend. In class B, we can reach private section of A
	};
	
	class B {
	public:
		void func()
		{
			ax.foo(); // is not legal, sythax error.
			// inside class B it is not possible to reach private section of class A.
		}
	private:
		A ax;
	};
*/

/*
	class A {
	public:
		A()
		{
			std::cout << "A default ctor\n";
		}
	};
	
	class B {
	private:
		A ax;
	};
	
	int main()
	{
		B bx;
		// when we default initialize bx(class B) object, its member type A will call its constructor.
		// A::A() will be called in default initialization of bx's A member type.
	}
*/

/*
	class A {
	public:
		A(int);
	};
	
	class B {
	public:
		// B() = delete; -> this is what happens.
	private:
		A ax;
	};
	
	int main()
	{
		B bx;
		// when we try to create an object from class B and default initalize it,
		// we need to default initialize its member type ax(class A) too.
		// In ax objects default initialization class A's default ctor will be called..
		// because of there is no default ctor in class A [when A(int) ctor user declared, no default ctor A()]
		// it will be an error.
		// when an error occurs in initialization process of member type.
		// class B's default ctor will be deleted by the compiler.
	}
*/

/*
	class A {
		A();
	};
	
	class B {
	public:
		// B() = delete; -> this is what happens.
	private:
		A ax;
	};
	
	int main()
	{
		B bx;
		// because of class A's default ctor need to call, for member type variable of class B (A ax)
		// we need to reach A's private section from B.
		// It is not possible without a friend decleration so
		// compiler will end up deleting B::B() [class B's default ctor].
	}
*/

/*
	class A {
	public:
		A(int x)
		{
			std::cout << "A(int x) x = " << x << '\n';
		}
	};
	
	class B {
	public:
		B() {} // sythax error. 
		// because of we declared B() [class B's default ctor].
		// compiler can not delete it implicitly so it will throw a sythax error.
	
		// B() : ax(19){} // constructor initializer list.
	private:
		A ax;
	};
	
	int main()
	{
		B bx;	// syntax error
	}
*/

/*
	class Member {
	public:
		void f1();
		void f2();
	};
	
	class Owner {
		void f1()
		{
			mx.f1(); // reaching Member classes f1() function [Owner's interface] by using a member type mx.
		}
	private:
		Member mx;
	};
	
	// Member classes interface is not include in Owner's interface.
	// Owner class can reach Member classes interface by using its member type(mx) object.
*/

/*
	class Member;  // incomplete type class.
	
	class Owner {
	public:
	private:
		Member mx;
		// A class needs to be complete type to be a member type of another class.
		// It's size is not known when a class is an incomplete type.
	
		Member* mpx;
		// A pointer to class(Member*), can be a data member of another class.
		// Pointers size is known even the class itself is an incomplete type or a complete type.
	
		Member& mrx;
		// A reference to a class(Member&), can be a data member of another class.
		// References size is same as pointers. So it is not important that a class is an incomplete or a complete type.
	};
*/

/*
	class A {
	public:
		A(int, int, int)
		{
			std::cout << "A(i,i,i)\n";
		}
	};
	
	class B {
	public:
	private:
		A ax = { 2,3,7 };		// -> works 	(copy list initialization)
		// A ay{ 2,3,5 };		// -> works	(direct list initalization)
		// A az(1,2,3);			// -> not works	-> acts like a function decleration
		// A al = (2,3,4);		// -> not works	-> same as [A al = 4;] no 1 parameter ctor.
	};
	
	int main()
	{
		B x;
	}
*/

/*
	==========================================
	| special member functions incomposition |
	==========================================
*/

/*
	class A {};
	class B {};
	class C {};
	
	class Myclass {
		// default ctor
		Myclass() : ax(), bx(),cx() {}
		
		// copy ctor
		Myclass(const Myclass& other) : ax(other.ax), bx(other.bx), cx(other.cx){}
		
		// copy assignment
		Myclass& operator=(const Myclass& other)
		{
			ax = other.ax;
			bx = other.bx;
			cx = other.cx;
			return *this;
		}
		
		// move ctor
		Myclass(Myclass&& other) : ax(std::move(other.ax)), bx(std::move(other.bx)),
			cx(std::move(other.cx)) {}
			
		// move assignment
		Myclass& operator=(Myclass&& other)
		{
			ax = std::move(other.ax);
			bx = std::move(other.bx);
			cx = std::move(other.cx);
			return *this;
		}
	private:
		A ax;
		B bx;
		C cx;
	};
*/

/*
	class A {
	public:
		A()
		{
			std::cout << "A class default ctor\n";
		}
	
		A(const A&)
		{
			std::cout << "A class copy ctor\n";
		}
	};
	
	class B {
	public:
		B() = default;
		B(const B& other) : mval(other.mval) {}
		// we did not initialize ax member type varible object in initializer list.
		// so it will use A::A() [class A's default ctor] to initialize ax object.
		
		// B(const B & other) : mval(other.mval), ax(other.ax) {}
	private:
		int mval;
		A ax;
	};
	
	int main()
	{
		B b1;
		B b2 = b1; // copy constructor
	
		// B(const B& other) : mval(other.mval) {}
		// output -> 
		// 	A class default ctor
		// 	A class default ctor

		// Because of we did not initialize A member type inside copy constructor
		// default ctor of class A will be called.
	
		// B(const B & other) : mval(other.mval), ax(other.ax) {}
		// output ->
		// 	A class default ctor
		// 	A class copy ctor

		// Because of we initialize A member type inside copy constructor
		// copy ctor of class A will be called.
	}
*/
