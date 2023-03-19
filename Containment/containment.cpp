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
		// A::A() will call in default initialization of bx's A member type
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
		// when we try to create an object from class B,
		// we need to default initialize its member type ax(class A).
		// for default initialize ax we need to use default ctor in class A
		// because of there is no default ctor in class A [when A(int) ctor user declared, no default ctor A()]
		// it will throw a sythax error because of context control.
		// when an error occurs in initialization process
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
		// because of class A's default ctor needed to call, for member type variable of class B (A ax)
		// we need to reach A's private section from B.
		// because of that is not possible without a friend decleration
		// compiler will end up deleting B() [class B's default ctor].
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
		B bx;
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
	// Owner class can reach Members interface by using its Member class member type variables.
*/

/*
	class Member;  // incomplete type class.
	
	class Owner {
	public:
	private:
		Member mx;
		// a class needs to be complete type, to be a member type.
		// it's size is not known when it is incomplete type.
	
		Member* mpx;
		// a pointer to class, can be a member variable of a class.
		// pointers size is known even the class itself is incomplete or not.
	
		Member& mrx;
		// a reference to class, can be a member variable of a class.
		// references size is same as pointer and also known by the compiler.
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
		A ax = { 2,3,7 };		// -> works
		// A ay{ 2,3,5 };		// -> works
		// A az(1,2,3);			// -> not works
		// A al = (2,3,4);		// -> not works
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
		Myclass() :ax(), bx(),cx() {}
		// default ctor
		Myclass(const Myclass& other) : ax(other.ax), bx(other.bx), cx(other.cx){}
		// copy ctor
		Myclass& operator=(const Myclass& other)
		{
			ax = other.ax;
			bx = other.bx;
			cx = other.cx;
			return *this;
		}
		// copy assignment
		Myclass(Myclass&& other) : ax(std::move(other.ax)), bx(std::move(other.bx)),
			cx(std::move(other.cx)) {}
		// move ctor
		Myclass& operator=(Myclass&& other)
		{
			ax = std::move(other.ax);
			bx = std::move(other.bx);
			cx = std::move(other.cx);
			return *this;
		}
		// move assignment
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
		// so it will use A() [class A's default ctor] to initialize ax object.
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
		// A class default ctor
		// A class default ctor

		// because we did not initialize A member type inside copy constructor
		// default ctor of A, will be called.
	
		// B(const B & other) : mval(other.mval), ax(other.ax) {}
		// output ->
		// A class default ctor
		// A class copy ctor

		// because we initialize A member type inside copy constructor
		// copy ctor of A, will be called.
	}
*/