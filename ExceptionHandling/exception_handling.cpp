#include <iostream>
#include <exception>

/*
	static  assertions (compile-time assertions)
	dynamic assertions (run-time assertions)
*/

/*
	throw, try, catch 
	keywords are used for exception handling.
*/

/*
	// If there is an exception thrown and the program did not catch that exception
	// it is called uncaught exception
	
	// If there is an uncaught exception, std::terminate() function invoked.
	// std::terminate() functions default behaviour is calling abort() function.
	// abort() is abnormal termination function
	// abort() is not like exit(). exit() is normal termination function.
	
	// exit() gave guarantees
	// -> closing files,
	// -> flushing buffers of files
	// -> calling atexit() functions that saved in reverse order.
	
	void f2()
	{
		std::cout << "f2 called\n";
		throw 1;
		std::cout << "f2 returns\n";
	}
	
	void f1()
	{
		std::cout << "f1 called\n";
		f2();
		std::cout << "f1 returns\n";
	}
	
	int main()
	{
		std::cout << "main called\n";
		f1();
		std::cout << "main returns\n";
	}
*/

/*
	// to change the default behaviour of terminate() function
	// there is a function called set_terminate()

	// if we want to change the behaviour of terminate() function
	// we can create a function [func()] and send it to set_terminate(&func)
	
	using terminate_handler = void(*)();
	//typedef void(*terminate_handler)();
	
	terminate_handler gfp = &std::abort;
	
	void terminate()
	{
		gfp();
	}
	
	terminate_handler set_terminate(terminate_handler f)
	{
		// returns function pointer
		// have a function pointer parameter
	
		auto fptemp = gfp;
		gfp = f;
		return fptemp;
	}
*/

/*
	#include <cstdlib>
	
	void myterminate()
	{
		std::cout << "myterminate()\n";
		std::exit(EXIT_FAILURE);
	}
	
	void f1()
	{
		std::cout << "f1 called\n";
		throw 1;
		std::cout << "f1 returns\n";
	}
	
	int main()
	{
		auto f = std::set_terminate(&myterminate);
		std::cout << std::boolalpha << (f == &abort) << '\n';
		// f's type is &abort because std::set_terminate() function is calling abort() function.
	
		f1();
	}
*/

/*
	throw expr; 	// throw statement
	throw;		// rethrow statement
*/

/*
	class Myclass {};
	
	// throw 12;
	// compiler will generate an object have a type of 12(int) [EXCEPTION OBJECT]
	
	// throw Myclass{};
	// compiler will generate an object have a type of Myclass [EXCEPTION OBJECT]
	
	void func()
	{
		Myclass mx;
		throw mx;
		// mx will used for initialization of the EXCEPTION OBJECT created by compiler.
		// sent object is not mx.
		// sent object will be the copy of mx.
	
		throw Myclass{};
		// generally we will use temp object in throw statement
		// for compiler to create its own EXCEPTION OBJECT.
	}
*/

/*
	int main()
	{
		try {
			int x = 10;
		}
		catch (int)
		{
			x = 20; // syntax error.
			// we can not use a variable create in try BLOCK in catch BLOCK.
		}
	}
*/

/*
	int main()
	{
		try {
	
		}
		catch (int x, int y) // syntax error
		{
			// catch can only have 1 parameter
			// C2310 catch handlers must specify one type
		}
	}
*/

/*
	void f2()
	{
		std::cout << "f2 called\n";
		throw 1;
		std::cout << "f2 returns\n";
	}
	
	void f1()
	{
		std::cout << "f1 called\n";
		f2();
		std::cout << "f1 returns\n";
	}
	
	int main()
	{
		try {
			f1();
		}
		catch (int){
			std::cout << "exception caught in function main.. catch(int)\n";
		}
	
		std::cout << "main continuing\n";
	}
*/

/*
	void f2()
	{
		std::cout << "f2 called\n";
		throw 'A';
		// NO IMPLICIT CONVERSION FROM CHAR TO INT
		// uncaught exception thrown std::terminate() function invoked
		// std::terminate function will call std::abort() function
		std::cout << "f2 returns\n";
	}
	
	void f1()
	{
		std::cout << "f1 called\n";
		f2();
		std::cout << "f1 returns\n";
	}
	
	int main()
	{
		try {
			f1();
		}
		catch (int) {
			std::cout << "exception caught in function main.. catch(int)\n";
		}
	
		std::cout << "main continuing\n";
	}
*/

/*
	void f2()
	{
		std::cout << "f2 called\n";
		throw 3;
		std::cout << "f2 returns\n";
	}
	
	void f1()
	{
		std::cout << "f1 called\n";
		f2();
		std::cout << "f1 returns\n";
	}
	
	int main()
	{
		try {
			f1();
		}
		catch (double) {
			std::cout << "exception caught in function main.. catch(double)\n";
		}
		catch (long) {
			std::cout << "exception caught in function main.. catch(long)\n";
		}
		catch (int x) {
			std::cout << "exception caught in function main.. catch(int x) x = " << x << '\n';
			// output -> exception caught in function main.. catch(int x) x = 3
		}
		catch (char) {
			std::cout << "exception caught in function main.. catch(char)\n";
		}
	}
*/

/*
	void f2()
	{
		std::cout << "f2 called\n";
		throw 'A';
		std::cout << "f2 returns\n";
	}
	
	void f1()
	{
		std::cout << "f1 called\n";
		f2();
		std::cout << "f1 returns\n";
	}
	
	int main()
	{
		try {
			f1();
		}
		catch (int) {
			std::cout << "exception caught in function main.. catch(double)\n";
		}
		catch (double) {
			std::cout << "exception caught in function main.. catch(double)\n";
		}
		catch (...) {
			// ellipsis token(...)
			// catch all parameter.
			std::cout << "exception caught in function main.. catch(...)\n";
			// output -> exception caught in function main.. catch(...)
		}
	}
*/

/*
	void f2()
	{
		std::cout << "f2 called\n";
		throw 'A';
		std::cout << "f2 returns\n";
	}
	
	void f1()
	{
		std::cout << "f1 called\n";
		f2();
		std::cout << "f1 returns\n";
	}
	
	int main()
	{
		try {
			f1();
		}
		catch (...) {
			std::cout << "exception caught in function main.. catch(...)\n";
		} // syntax error
		// catch(...) needs to be last
		// E0532 handler is masked by default handler
		// error C2311 : 'int' : is caught by '...'
		// error C2311: 'double': is caught by '...'
		catch (int) {
			std::cout << "exception caught in function main.. catch(double)\n";
		}
		catch (double) {
			std::cout << "exception caught in function main.. catch(double)\n";
		}
	}
*/

/*
	class Base {
	public:
		virtual ~Base() = default;
		// polymorphic base class
	};
	
	class Der : public Base {};
	class Ser : public Base {};
	class SDer : public Der {};
	
	void f2()
	{
		std::cout << "f2 called\n";
		throw Der{};
		// Der{} temp object is R value expression
		// because of it is copied to EXCEPTION OBJECT
		// it can bind to Der& in catch()
	
		// output -> exception caught catch(Der&)
		std::cout << "f2 returns\n";
	}
	
	void f1()
	{
		std::cout << "f1 called\n";
		f2();
		std::cout << "f1 returns\n";
	}
	
	int main()
	{
		try {
			f1();
		}
		catch (Der&) {
			std::cout << "exception caught catch(Der&)\n";
		}
	}
*/

/*
	class Base {
	public:
		virtual ~Base() = default;
	};
	
	class Der : public Base {};
	class Ser : public Base {};
	class SDer : public Der {};
	
	void f1()
	{
		std::cout << "f1 called\n";
		throw SDer{};
		// output -> exception caught catch(Der&)
		std::cout << "f1 returns\n";
	}
	
	int main()
	{
		try {
			f1();
		}
		catch (Der&) {
			std::cout << "exception caught catch(Der&)\n";
		}
	}
*/

/*
	class Base {
	public:
		virtual ~Base() = default;
	};

	class Der : public Base {};
	class Ser : public Base {};
	class SDer : public Der {};

	void f1()
	{
		std::cout << "f1 called\n";
		throw SDer{};
		// output -> exception caught catch(Base&)
		std::cout << "f1 returns\n";
	}

	int main()
	{
		try {
			f1();
		}
		catch (Base&) {
			std::cout << "exception caught catch(Base&)\n";
		}
	}
*/

/*
	class Base {
	public:
		virtual ~Base() = default;

		virtual const char* str() const
		{
			return "Base";
		}
	};

	class Der : public Base {
	public:
		virtual const char* str() const override
		{
			return "Der";
		}
	};
	class Ser : public Base {
	public:
		virtual const char* str() const override
		{
			return "Ser";
		}
	};
	class SDer : public Der {
	public:
		virtual const char* str() const override
		{
			return "SDer";
		}
	};

	void f1()
	{
		throw SDer{};
		// output
		// -> exception caught catch(Base&)
		// -> SDer

		// virtual dispatch mechanism works.
	}

	int main()
	{
		try {
			f1();
		}
		catch (Base& r) {
			std::cout << "exception caught catch(Base&)\n";
			std::cout << r.str() << '\n';
		}
	}
*/

/*
	class Base {
	public:
		virtual ~Base() = default;
	};
	
	class Der : public Base {};
	class Ser : public Base {};
	class SDer : public Der {};
	
	void f1()
	{
		// throw SDer{};
		// output -> exception caught catch(Der&)
	
		throw Ser{};
		// output -> exception caught catch(Base&)
	}
	
	int main()
	{
		try {
			f1();
		}
		catch (Der& r) {
			std::cout << "exception caught catch(Der&)\n";
		}
		catch (Base& r) {
			std::cout << "exception caught catch(Base&)\n";
		}
		catch (...) {
			std::cout << "exception caught catch(...)\n";
		}
	}
*/

/*
	#include <string>
	
	void func(int x)
	{
		std::string str{ "Hello World" };
		auto c = str.at(x);
	}
	
	int main()
	{
		try {
			func(234);
		}
		catch (const std::out_of_range& ex) {
			std::cout << "exception caught: " << ex.what() << '\n';
		}
		catch (const std::logic_error& ex) {
			std::cout << "exception caught: " << ex.what() << '\n';
		}
		catch (const std::exception& ex) {
			std::cout << "exception caught: " << ex.what() << '\n';
		}
	}
*/

/*
	struct Ex {
		Ex()
		{
			std::cout << "Ex default ctor this = " << this << '\n';
		}
		Ex(const Ex&)
		{
			std::cout << "Ex copy ctor this = " << this << '\n';
		}
		Ex(Ex&&)
		{
			std::cout << "Ex move ctor this = " << this << '\n';
		}
		~Ex()
		{
			std::cout << "Ex destructor this = " << this << '\n';
		}
	};
	
	void foo()
	{
		throw Ex{};
		// returning temp object (PR value),
		// mandatory copy ellision will occurs.
		// Only default ctor will be called.
	}
	
	int main()
	{
		try {
			foo();
		}
		catch (const Ex& ex) {
			std::cout << "exception caught... &ex= " << &ex << '\n';
		}
	}
*/

/*
	-------------------
	| stack unwinding |
	-------------------
*/

/*
	// if exception has not caught, objects in stack frame will cause a resource leak
	// because non of their destructors will called when terimate() function call abort() function.
*/

/*
	class A {
	public:
		A()
		{
			std::cout << "A object in this " << this << " address obtain resources.\n";
		}
		~A()
		{
			std::cout << "A object in this " << this << " address gave its resources back.\n";
		}
	};
	class B {
	public:
		B()
		{
			std::cout << "B object in this " << this << " address obtain resources.\n";
		}
		~B()
		{
			std::cout << "B object in this " << this << " address gave its resources back.\n";
		}
	};
	class C {
	public:
		C()
		{
			std::cout << "C object in this " << this << " address obtain resources.\n";
		}
		~C()
		{
			std::cout << "C object in this " << this << " address gave its resources back.\n";
		}
	};
	
	void f4()
	{
		A a1;
		B b1;
		throw std::exception();
	}
	
	void f3()
	{
		C c1;
		f4();
	}
	
	void f2()
	{
		A ax; B bx; C cx;
		f3();
	}
	
	void f1()
	{
		B b1, b2, b3;
		f2();
	}
	
	int main()
	{
		// f1();
		// resource has been leaked
	
		try {
			f1();
		}
		catch (const std::exception& )
		{
			(void)getchar();
		}
		// when we use try-catch block, resource has been given back
		// no resource leak happened
	}
*/

/*
	#include <memory>
	
	class A {
	public:
		A()
		{
			std::cout << "A object in this " << this << " address obtain resources.\n";
		}
		~A()
		{
			std::cout << "A object in this " << this << " address gave its resources back.\n";
		}
	};
	class B {
	public:
		B()
		{
			std::cout << "B object in this " << this << " address obtain resources.\n";
		}
		~B()
		{
			std::cout << "B object in this " << this << " address gave its resources back.\n";
		}
	};
	class C {
	public:
		C()
		{
			std::cout << "C object in this " << this << " address obtain resources.\n";
		}
		~C()
		{
			std::cout << "C object in this " << this << " address gave its resources back.\n";
		}
	};
	
	void f4()
	{
		// A* a1 = new A;
		// B* b1 = new B;
		std::unique_ptr<A> a1{ new A };
		std::unique_ptr<B> b1{ new B };
		throw std::exception();
		// delete a1;
		// delete b1;
	}
	
	void f3()
	{
		// auto c1 = new C;
		std::unique_ptr<C> c1{ new C };
		f4();
		// delete c1;
	}
	
	void f2()
	{
		// A* ap = new A;
		std::unique_ptr<A> ap{ new A };
		f3();
		// delete ap;
	}
	
	void f1()
	{
		// B* b1 = new B;
		// B* b2 = new B;
		std::unique_ptr<B> b1{ new B };
		std::unique_ptr<B> b2{ new B };
		f2();
		// delete b1;
		// delete b2;
	}
	
	int main()
	{
		try {
			f1();
		}
		catch (const std::exception& ex)
		{
			std::cout << "exception caught: " << ex.what() << '\n';
		}
		// if we use raw pointers, after exception caught,
		// dynamic objects resources will not gave back.
		// Using smart pointers can solve the giving back resources problem.
	}
*/

/*
	---------------------
	| rethrow statement |
	---------------------
*/

/*
	void bar()
	{
		try {
			throw std::out_of_range{ "value out of range" };
		}
		catch (const std::exception& ex) {
			std::cout << "Exception caught in bar() function..\n";
			std::cout << "The address of the exception object is: " << &ex << '\n';
			throw ex;
			// when we throw ex again, object slicing occurs
			// [ex's type before out_of_range but after std::exception]
			// new Exception object created, have a type of std::exception
		}
	}
	
	int main()
	{
		try {
			bar();
		}
		catch (const std::out_of_range& ex)
		{
			std::cout << "Exception caught in main() function..\n";
			std::cout << "out_of_range exception\n";
			std::cout << "The address of the exception object is: " << &ex << '\n';
		}
		catch (const std::exception& ex)
		{
			std::cout << "Exception caught in main() function..\n";
			std::cout << "exception\n";
			std::cout << "The address of the exception object is: " << &ex << '\n';
		}
	}
	
	// Exception caught in bar() function..
	// The address of the exception object is : 0x12d0f30
	// Exception caught in main() function..
	// exception
	// The address of the exception object is : 0x12d2020
*/

/*
	void bar()
	{
		try {
			throw std::out_of_range{ "value out of range" };
		}
		catch (const std::exception& ex) {
			std::cout << "Exception caught in bar() function..\n";
			std::cout << "The address of the exception object is: " << &ex << '\n';
			throw;
			// when we use rethrow statement `throw;`
			// no object slicing occurs we are sending the same EXCEPTION OBJECT came befor
			// which have a type of std::out_of_range
		}
	}
	
	int main()
	{
		try {
			bar();
		}
		catch (const std::out_of_range& ex)
		{
			std::cout << "Exception caught in main() function..\n";
			std::cout << "out_of_range exception\n";
			std::cout << "The address of the exception object is: " << &ex << '\n';
		}
		catch (const std::exception& ex)
		{
			std::cout << "Exception caught in main() function..\n";
			std::cout << "exception\n";
			std::cout << "The address of the exception object is: " << &ex << '\n';
		}
	}
	
	// Exception caught in bar() function..
	// The address of the exception object is : 0x1f7df30
	// Exception caught in main() function..
	// out_of_range exception
	// The address of the exception object is : 0x1f7df30
*/

/*
	int foo()
	{
		throw std::exception{};
	}
	
	void baz()
	{
		throw;
	}
	
	void func()
	{
		try {
			foo();
		}
		catch (const std::exception&){
			// code..
			baz(); // in baz() function we can rethrow the error (propagate to upper level).
	
			// same as rethrow inside catch block.
			throw;
		}
	}
	
	int main()
	{
		func();
	
		baz(); // if baz() will throw -> terminate() will called.
	}
*/

/*
	------------------------
	| exception dispatcher |
	------------------------
*/

/*
	void doSomeWork()
	{
		try {
			somework();
		}
		catch (const NetworkError& exc)
		{
			loadFromFile();
		}
		catch (const InvalidData& exc)
		{
			dropConnection();
		}
		catch (const TooMuchData& exc)
		{
			reSendSammlerRequest();
		}
	}
	
	void doSomeOtherWork()
	{
		try {
			otherWork();
			otherStuff();
		}
		catch (const NetworkError& exc)
		{
			loadFromFile();
		}
		catch (const InvalidData& exc)
		{
			dropConnection();
		}
		catch (const TooMuchData& exc)
		{
			reSendSammlerRequest();
		}
	}
	
	// These 2 functions have all same catch blocks. Repeating themselves. It is not good.
	
	void doSomeWork()
	{
		try {
			somework();
		}
		catch (...)
		{
			handleExceptions();
			// catch(...) all errors in catch block.
			// called handleExceptions() functions
		}
	}
	
	void doSomeOtherWork()
	{
		try {
			otherWork();
			otherStuff();
		}
		catch (...)
		{
			handleExceptions();
			// catch(...) all errors in catch block.
			// called handleExceptions() functions
		}
	}	
	void hangleExceptions()
	{
		try
		{
			throw;	// rethrow the error catched in doSomework() or doSomeOtherWork function()'s catch block.
		}
		catch (const NetworkError& exc)
		{
			loadFromFile();
		}
		catch (const InvalidData& exc)
		{
			dropConnection();
		}
		catch (const TooMuchData& exc)
		{
			reSendSammlerRequest();
		}
		// catch which error is suitable for the rethrown error.
	}
*/

/*
	----------------------------
	| translating an exception |
	----------------------------
*/

/*
	// e.g, a scenerio where GUI application throws a bad_alloc exception
	// it is not logical to send that bad_alloc error to user.
	
	void foo()
	{
		try {
			//
		}
		catch (const std::bad_alloc&) {
			// some code
			throw BadGuiComponent;
			// some user declared exception class can be sent.
			// It will be more logical..
		}
	}
*/

/*
	------------------------
	| exception guarantees |
	------------------------
*/

/*
	1. basic guarantee
		-> no resource leak 
		-> program will stay in valid state (Invariants did not broke )
			e.g, think about a PushBack() function
			before an exception thrown an item added to vector
			but the size did not increased. So the state of the vector
			(invariants) are changed. Not valid now.
	2. strong ( commit or rollback ) guarantee
		-> state did not change.
	3. no throw guarantee
		-> guarantees that no exception will thrown.
*/

/*
	No throw guarantee
		-> Operation will not throw
	Strong execption safety
		-> Operation will either succeed, or be rolled back
	Basic exception safety
		-> No resource leaks, invariants preserved,
			but operation can be half done.
	No exception safety
		-> If you will throw exceptions, terminate() will invoked
			then abort() [segfaults, memory corruption]
*/

/*
	-> No throw guarantee
		C functions, like fclose()
		std::swap(a,b)
		memory deallocation, clean up functions
		move ctor, move assignment

	-> Strong execption safety
		std::vector::push_back(a);

	void insert(int key, string value)
	{
		auto newKeys = keys;
		auto newValues = values;	// can throw, but object is not modified yet.
		newKeys.push_back(key);
		newValues.push_back(value);

		std::swap(newKeys, keys);
		std::swap(newValues, values);	// std::swap does not throw (no throw guarantee)
	}

	void insert(int key, string value)
	{
		keys.push_back(key);
		try
		{
			values.push_back(value);
		}
		catch(...)
		{
			keys.pop_back(key);
		}
	}

	-> Basic execption safety
		if copy ctor will throw,
		only some elements will be copied, not all of them.
		its invariants will not be broke.
	void halfDoneCopy(const std::vector<A>& in, std::vector<A>& out)
	{
		for (const auto& a : in)
		{
			out.push_back(a);
		}
	}

	struct Map
	{
		vector<int> keys;
		vector<string> values;

		void insert(int key, string value)
		{
			keys.push_back(key);
			values.push_back(value);		
			// if values.push_back(value) will throw
			// key has already be added but invariants changed.
			// need to be same amount of key and value...
		}
	};

	-> No exception safety
		if fill() will throw, we will have a memory leak
	char* noSafety(const A& a)
	{
		char* buffer = new char[100];	// memory allocated.
		a->fill(buffer);		// if throw (resource leak) 
		return buffer;
	}
	
*/

/*
	--------------------
	| noexcept keyword |
	--------------------
*/

/*
	1. noexcept specifier
	2. noexcept operator
*/

/*
	1. noexcept SPECIFIER
	void foo(int) noexcept; // noexcept specifier.
		// -> it will guarantee not to throw an exception.
	//	virtual const char* what() const noexcept

	noexcept is a part of functions SIGNATURE.

	void func()noexcept(sizeof(int) > 2);
	// if sizeof(int) is bigger than 2 byte, 
	// func() function guarantees to not throw an exception.

	void foo()noexcept
	void foo()noexcept(true)
	// These 2 foo() functions are same

	void bar()
	void bar()noexcept(false)
	// These 2 bar() functions are same

	If inside a no throw guarantee function, exception thrown in runtime
	terminate() function will invoked and terminate() will call abort() function.
*/

/*
	// .h file (header file)
	void foo() noexcept; // decleration
	
	// because of noexcept is part of the signature.
	// we need to use noexcept in function definition too.
	
	
	void bar()
	{
		throw std::runtime_error{ "error error !!!" };
		// terminate() invoked, then abort() invoked
		// because of foo() is no throw guarantee function.
	}
	
	// .cpp file
	void foo() noexcept
	{
		bar();
	}
	
	int main()
	{
		try {
			foo();
		}
		catch (const std::exception& ex) {
			std::cout << "exception caught: " << ex.what() << '\n';
		}
	}
*/

/*
	// 2. noexcept OPERATOR

	class Myclass{};

	void func() noexcept(noexcept(Myclass{}));
	
	// first noexcept is a specifier.
	// second noexcept is an operator.
	
	// If Myclass{} classes default ctor guarantees to not throw an exception
	// noexcept(Myclass{}) will become true.
	
	
	int main()
	{
		int x = 10;
	
		noexcept(x + 5);
		// creates a bool type.
		// the statement that created with noexcept operator is a constant expression.
	
		constexpr bool b = noexcept(x + 10); // no syntax error.
	}
*/

/*
	void foo(int)noexcept;
	void foo(int);
	// noexcept operator is a part of the function signature
	// but it can not used in function overloads
	// These 2 functions create a syntax error.
*/

/*
	void foo(int)noexcept;
	// if this function throws an error.
	// it will directly invoke terminate() function
	// terminate will call abort() function.
*/

/*
	int main()
	{
		int x = 10;
		int y = 4;
	
		constexpr auto b = noexcept(++x / ++y);
	
		std::cout << "x = " << x << '\n';	// output -> x = 10
		std::cout << "y = " << y << '\n';	// output -> y = 4
		// becuase of noexcept operator creates an unevaluated context.
		// no side effect will occur. x and y's values will not change.
	}
*/

/*
	class Myclass {
	public:
		Myclass();
		~Myclass();
	};
	
	int main()
	{
		Myclass x;
		constexpr auto b = noexcept(x.~Myclass());
		// b is true because Destructors have no throw guarantee.
		// if error thrown in dtor and propagated, it will directly invoked terminate() function.
	
		// Dtor called ->
		// 1. at the end of objects life.
		// 2. an exception thrown then caugth in try-catch block,
		// stack unwinding phase started and dtor called. (CAN NOT THROW ANY ERROR)
	
		// In Dtor we can catch if error thrown inside try-catch block.
		// But if we can not caught it(uncaught error), error will try to propagated (CAN NOT BE HAPPEN!!)
		// Directly terminate() function invoke then abort() will called.
	}
*/

/*
	class Base {
	public:
		virtual void func()noexcept;	// base classes virtual member function gave a no throw guarantee
	};
	
	class Der : public Base {
	public:
		virtual void func()override;	// derived classes override function did not gave nothrow guarantee
		// syntax error
		// C2694 'void Der::func(void)': overriding virtual function has less restrictive exception specification than
		// base class virtual member function 'void Base::func(void) noexcept'
	};
*/

/*
	class Base {
	public:
		virtual void func();
	};
	
	class Der : public Base {
	public:
		virtual void func()noexcept override;	// derived classes override function gave a nothrow guarantee
		// valid.
	};
	
	// If directly Base object is gone, func() function can throw an exception. No problem for Der.
	// If Der object is used. Because of Der classes override gave a non throw guarantee. No problem for Base class.
*/

/*
	void func(int)noexcept;
	void bar(int);
	
	int main()
	{
		void (*fp1)(int)noexcept;
		void (*fp2)(int);
		// noexcept operator can be used in function pointers decleration and definitions.
	
		void (*fp)(int) = &func;
		// legal
		// function calls with fp did not guarantee that not throwing an error.
		// but it can hold the address of a function that will have a no throw guarantee.
	
		void (*fptr)(int)noexcept = &bar;
		// syntax error
		// function pointer fptr guarantees,
		// the function that called with fptr have a no throw guarantee.
		// assigning the address of a function does not have a no throw guarantee to ptr is not valid.
	}
*/

/*
	-----------------------------
	| constructors & exceptions |
	-----------------------------
*/

/*
	#include <stdexcept>
	
	class Myclass {
	public:
		Myclass(int x)
		{
			std::cout << "Myclass(int)\n";
			if (x > 10)
				throw std::runtime_error{ "error" };
	
			// because of Myclass(int) ctors scope couldn't end
			// x object is not came alive
			// because of it is not alive
			// ~Myclass() dtor will not called.
		}
		~Myclass()
		{
			std::cout << "~Myclass()\n";
		}
	};
	
	int main()
	{
		try {
			Myclass x{ 45 };
		}
		catch (const std::exception&){
	
		}
	}
*/

/*
	#include <stdexcept>
	
	class Myclass {
	public:
		Myclass(int x)
		{
			mp = new int[x];
			// if throws an exceptions here, because of dtor can not be called
			// resource leak happens
		}
		~Myclass()
		{
			delete mp;
		}
	
		int* mp;
	};
	
	int main()
	{
		try {
			Myclass x{ 45 };
		}
		catch (const std::exception& ex){
	
		}
	}
*/

/*
	class Member {
	public:
		Member()
		{
			// if throw an exception here.
			// both Member object and Myclass objects dtor's will not called.
			// because neither Member nor Myclass objects becomes alive.
		}
	};
	
	class Myclass {
	public:
		Myclass()
		{
	
		}
	private:
		Member mx;
	};
*/

/*
	class Member {
	public:
		Member()
		{
			// mx1 becomes alive,
			// mx2 ctor throws an exception.
			// in stack unwinding phase mx1's dtor will called
			// mx2 and Myclass's dtor will not called.
		}
	};
	
	class Myclass {
	public:
		Myclass()
		{
	
		}
	private:
		Member mx1,mx2;
	};
*/

/*
	class Member {
	public:
		Member()
		{
		}
	};
	
	class Myclass {
	public:
		Myclass() : mp(new Member)
		{
			// after mp initialized.
			// if exception throw in here.
			// Myclass dtor will not called because Myclass will not become alive
			// resource leak in heap happen.
		}
		~Myclass()
		{
			delete mp;
		}
	private:
		Member* mp;
	};
*/

/*
	class Myclass {
	public:
		Myclass()
		{
	
		}
	};
	
	int main()
	{
		Myclass* p = new Myclass;
		// 1. phase -> memory allocated for Myclass object in heap (operator new function)
		// 2. phase -> Myclass ctor will called.
	
		// If exception thrown in Myclass ctor.
		// Memory allocated for Myclass object in phase 1
		// but phase 2 is not completed.
	
		// Compiler is responsible for phase 1's memory deallocation. (memory allocated for Myclass object in heap)
		// It is not out responsibility.
	}
*/

/*
	// bad_alloc exception
	
	#include <vector>
	
	class Myclass {
	public:
		unsigned char buffer[1024 * 1024]{};
	};
	
	std::vector<Myclass*> gvec;
	
	int main()
	{
		try
		{
			for (int i = 0; i < 2000; ++i)
			{
				gvec.push_back(new Myclass);
				std::cout << i << '\n';
			}
		}
		catch (const std::bad_alloc& ex)
		{
			std::cout << "exception caught: " << ex.what() << '\n';
		}
		catch (const std::exception& ex)
		{
			std::cout << "exception caught: " << ex.what() << '\n';
		}
	}
*/

/*
	// bad_cast exception
	
	class Base {
	public:
		virtual ~Base() {};
		// Base is a  polymorphic class
	};
	
	class Der : public Base {
	
	};
	
	class Mer : public Base {
	
	};
	
	void foo(Base& baseref)
	{
		Der& dr = dynamic_cast<Der&>(baseref);
	}
	
	int main()
	{
		try
		{
			Mer mx;
			foo(mx);
		}
		catch (const std::bad_cast& ex)
		{
			std::cout << "Exception caught: " << ex.what() << '\n';
		}
		catch (const std::exception& ex)
		{
			std::cout << "Exception caught: " << ex.what() << '\n';
		}
	}
*/

/*
	// bad_typeid exception
	
	class Base {
	public:
		virtual ~Base() {};
	};
	
	class Der : public Base {
	
	};
	
	void foo(Base* baseptr)
	{
		if (typeid(*baseptr) == typeid(Der))
			std::cout << "yes\n";
	}
	
	int main()
	{
		Der* p{};
		try
		{
			foo(p);
		}
		catch (const std::bad_typeid& ex)
		{
			std::cout << "Exception caught: " << ex.what() << '\n';
		}
		catch (const std::exception& ex)
		{
			std::cout << "Exception caught: " << ex.what() << '\n';
		}
	}
*/

/*
	----------------------
	| function try block |
	----------------------
	// generally used in constructors
*/

/*
	int func(int param)
	try {
		int x = 5;
	}
	catch (const std::exception&)
	{
		return 2;
		// can be a return statement in catch block
	
		++x; // syntax error
		// can not be use local try block variable in catch block.
	
		auto y = param;
		// can use function param in catch block.
	}
*/

/*
	class Myclass {
	public:
		Myclass(const Myclass&)
		{
			// exection thrown here
		}
	};
	
	int func(Myclass) // Myclass's copy ctor will call.
	try {
	}
	catch (const std::exception&)
	{
		// if copy ctor will throw an exception
		// function catch block do not catch that exception.
	}
*/

/*
	class Member {
	public:
		Member(int x)
		{
			if (x > 10) {
				throw std::runtime_error{ "error!!" };
			}
		}
	};
	
	class Myclass {
	public:
		// Myclass(int x) : mx{ x }
		// {
		// 	try {
		//
		// 	}
		// 	catch (const std::exception& ex)
		// 	{
		// 		std::cout << "exception caught: " << ex.what() << '\n';
		// 	}
		// }
	
		// in Member data type's initialization phase exception thrown in Member classes ctor.
		// we can not catch that exeption if we use try and catch blocks inside Myclasses ctor.
		// We need to use function try block to catch that exeption.
	
		Myclass(int x) try : mx{ x }
		{
	
		}
		catch (const std::exception& ex)
		{
			std::cout << "exception caught: " << ex.what() << '\n';
			// if you do not handle that exception in catch block.
			// compiler will write a rethrow statement in catch block.
			// That will invoke terminate() function.
		}
	private:
		Member mx;
	};
	
	
	int main()
	{
		try {
			Myclass my_class{ 12 };
		}
		catch (const std::exception& ex)
		{
			std::cout << "exception caught: " << ex.what() << '\n';
	
			// output ->
			// exception caught : error!!!
			// exception caught : error!!!
		}
	}
*/
