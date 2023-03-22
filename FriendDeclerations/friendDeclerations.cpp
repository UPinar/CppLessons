#include <iostream>


/*	
	=======================
	| friend declerations |
	=======================
*/

/*
	Q1: Why do we let other codes to reach private members?
	-> Friend decleration is not for client codes.
	If we want client codes to reach data members of our class, we can make them public members.

	Q2: What is in classes public interface ?
	-> Public members of the class and global members declerad in .h(header) file.
*/

/*
	#include <string>
	int main()
	{
		std::string str{ "Hello World" };
		str += "!";
	
		bool x;
		if (str == "Hello World")
			x = true;
		else
			x = false;
	
		// [str == "Hello World"] expression is a global function.
		auto y = std::operator==(str, "Hello World");
	
		// Because of global functions can not reach classes private section.
		// If we want to do this comparison between strings we need to use
		// friend decleration.
	}
*/

/*
	A class can give friend decleration to
	-> a free(global) function
	-> another classes member function
	-> another classes all functions.(to a class)
*/

/*
	// FRIEND DECLERATION TO A GLOBAL(FREE) FUNCTION
	class First {
	private:
		int mx;
		void func();
	};
	
	class Second {
	public:
		friend void gf_2(Second&);
	private:
		int mx;
		void func();
	};
	
	void gf_1(First& ref)
	{
		// <------------- NO FRIEND DECLERATION IN (FIRST) CLASS-------------->
		First x;
		First* p{ &x };
	
		reff.mx = 10;
		x.func();
		p->func();
		// access control errors. Because global function can not reach First's private section.
	}
	
	void gf_2(Second& ref)
	{
		// <------------- FRIEND DECLERATION IN (SECOND) CLASS -------------->
		Second y;
		Second* py{ &y };
	
		ref.mx = 20;
		y.func();
		py->func();
		// no access control error. Because global function can reach Second's private section.
	}
*/

/*
	// There is no difference between making friend declerations in classes public, protected or private sections.

	void func_3()
	{
		Myclass m;
		m.mx = 10;
	}

	void func_2()
	{
		Myclass m;
		m.mx = 11;
	}

	void func_1()
	{
		Myclass m;
		m.mx = 12;
	}

	class Myclass {
	public:
		friend void func_1();
	protected:
		friend void func_2();
	private:
		int mx;
		friend void func_3();
	};
*/

/*
	class Myclass {
	public:
		// hidden friend function
		// gf is still a global function.
		// When we define function in class scope, it will become inline.

		friend void gf(Myclass& r)
		{
			Myclass x;
			Myclass* p{ &x };
	
			r.mx = 10;
			x.func();
			p->func();
		}
	private:
		int mx;
		void func();
	};
*/

/*
* // Friend decleration to another classes member function

	class First {
	public:
		void foo(int);
		void bar(int);
	};
	
	class Myclass {
	private:
		// we only declare First classes foo(int) function as a friend.
		// inside First::foo(int) function reaching Myclass's private members is valid.
		friend void First::foo(int);
		void func();
		int mx;
	};
	
	// First::foo()[member function of class First] CAN reach Myclass's private section
	void First::foo(int x)
	{
		Myclass m;
		m.func();
		m.mx = 12;
	}
	// First::bar()[member function of class First] CAN NOT reach
	void First::bar(int x)
	{
		Myclass m;
		m.func();
		m.mx = 12;
	}
*/

/*
	// We CAN NOT make a friend decleration to an incomplete type classes member functions.
	
	class First; // forward decleration (incomplete type)
	
	class Second {
	private:
		friend void First::foo(int); // NOT VALID
		void func();
	};
	// E0070 incomplete type is not allowed
*/

/*
	class First {
	public:
	private:
		friend class Second;

		// we CAN declare another class as friend
		// when the friend declared class is yet an incomplete type.

		int mx;
		void foo();
	};

	// Second is not an incomplete type anymore.
	// Because we define the class below.
	class Second {
	public:
		void f1(First f)
		{
			f.mx = 345;
		}
		void f2()
		{
			First f;
			f.foo();
		}
	};
*/

/*
* 1.
	when A class declare B class as a friend. 
	B class is not declared A as a friend.
	B can reach private section of A class, but A can not reach B classes private section.
* 2.
	when A class declare B class as a friend.
	and B class declare C clasas as a friend.
	B can reach A class's private section and C can reach B classes private section.
	But C can not reach A class's private section
* 3.
	If A's parent(base) class AP declare C as a friend.
	C can reach AP class's private section
	But C can not reach A class's private section
*/

/*
	class A {
	private:
		friend class B;
		void afoo();
	};

	class B {
	private:
		friend class C;
		void bfoo()
		{
			A xa;
			xa.afoo(); // legal
			// [A declerad B as its friend]
		}
	};

	class C {
	private:
		void cfoo()
		{
			A xa;
			xa.afoo(); // sythax error
			// [A did not declare C as its friend]

			B xb;
			xb.bfoo(); // legal
			// [B declared C as its friend]
		}
	};
*/

/*
	// base(parent)[TABAN sinif] and derived(child)[TUREMIS sinif] classes

	class AParent {
	private:
		friend class C;
		void apf();
	};

	class A : public AParent {
	private:
		void afoo();
	};

	class C {
	private:
		void cf()
		{
			AParent apx;
			apx.apf(); // legal
			//[AParent declerad C as its friend]

			A ax;
			ax.afoo();
			// [A did not declerad C as its friend]
			// C class can not reach AP's child classes private section
			// even if AP(parent class) declared C as its friend
		}
	};
*/

/*
	class First {
	private:
		void f1();
			void f2();
		void f3();
			void f4();
	};
	
	// When you declere a function or a class as a friend
	// they can reach all of your private section.
	// But what if you want them to reach only a part of your classes private section
	// [ CAN REACH First::f2() and First::f4()
	// [ CAN NOT REACH First::f1() and First::f3() ]
	
	// Attorney - Client idiom
*/














