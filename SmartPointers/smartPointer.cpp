/*
	==================
	| smart pointers |
	==================
*/

/*
	------------------
	| unique pointer |
	------------------
*/

/*
	#include <memory>
	
	template <typename T>
	struct DefaultDelete {
		void operator(T* p)
		{
			delete p;
		}
	};
	
	template <typename T, typename D = DefaultDelete<T>>
	class UniquePtr {
	public:
		UniquePtr() = default;
	
		UniquePtr(T* p) : mp{p} {}
	
		~UniquePtr()
		{
			if (mp)
				D{}(mp);
		}
	
		T& operator*()
		{
			return *mp;
		}
		T* operator->()
		{
			return mp;
		}
	private:
		T* mp{};
	};
	// unique_ptr class template is a wrapper class for a pointer.
*/

/*
	#include <memory>
	#include <string>
	
	class Myclass {
	public:
		Myclass() = default;
	
		Myclass(std::string str) : mx{ str } {}
	
		~Myclass()
		{
			std::cout << "object in address = " << this << " has been deleted.\n";
		}
	
		std::string& operator*()
		{
			return mx;
		}
	
		friend std::ostream& operator<<(std::ostream& os, const Myclass& myclass)
		{
			return os << myclass.mx;
		}
	private:
		std::string mx;
	};
	
	int main()
	{
		std::unique_ptr<std::string> a;	// default initalization
	
		{
			std::unique_ptr<Myclass> upx(new Myclass{ "hello world" });
			std::cout << *upx << '\n';	// output -> hello world
		}
		// output ->
		//	hello world
		//	object in address = 00F8A370 has been deleted.
	}
*/

/*
	#include <memory>
	#include <string>
	
	class Myclass {
	public:
		Myclass() = default;
	
		Myclass(std::string str) : mx{ str } {}
	
		~Myclass()
		{
			std::cout << "object in address = " << this << " has been deleted.\n";
		}
	private:
		std::string mx;
	};
	
	int main()
	{
		using namespace std;
	
		unique_ptr<Myclass> p1;
		unique_ptr<Myclass> p2{};
		unique_ptr<Myclass> p3{ nullptr };
		unique_ptr<Myclass> p4 = nullptr;
		// These are all default initialized.
	
		// if(p1.operator bool())
		if (p1)
			std::cout << "i am full\n";
		else
			cout << "i am empty\n";
		// output -> i am empty
	
		if (p2 != nullptr)
			std::cout << "i am full\n";
		else
			cout << "i am empty\n";
		// output -> i am empty
	
		if (!(p1 && p2 && p3 && p4))
			std::cout << "all of them are empty\n";
		// output -> all of them are empty
	
		{
			unique_ptr<Myclass> p5{ new Myclass };
			if (p5)
				std::cout << "i am full\n";
			else
				cout << "i am empty\n";
			// output
			//	i am full
			//	object in address = 00773590 has been deleted.
		}
	}
*/

/*
	#include <memory>
	#include <string>
	
	class Myclass {
	public:
		Myclass() = default;
	
		Myclass(std::string str) : mx{ str } {}
	
		~Myclass()
		{
			std::cout << "object in address = " << this << " has been deleted.\n";
		}
	
		std::string& operator*()
		{
			return mx;
		}
	
		friend std::ostream& operator<<(std::ostream& os, const Myclass& myclass)
		{
			return os << myclass.mx;
		}
	private:
		std::string mx;
	};
	
	int main()
	{
		using namespace std;
	
		unique_ptr<Myclass> m1;
	
		try {
			*m1; // undefined behaviour
		}
		catch(const std::exception& ex)
		{
			cout << "exception caught : " << ex.what() << '\n';
		}
		// not throwing an exception, it is undefined behaviour to dereference
		// an empty unique_ptr object.
	}
*/

/*
	#include <memory>
	#include <string>
	#include <vector>
	
	class Myclass {
	public:
		Myclass() = default;
	
		Myclass(std::string str) : mx{ str } {}
	
		~Myclass()
		{
			std::cout << "object in address = " << this << " has been deleted.\n";
		}
	
		std::string& operator*()
		{
			return mx;
		}
	
		friend std::ostream& operator<<(std::ostream& os, const Myclass& myclass)
		{
			return os << myclass.mx;
		}
	private:
		std::string mx;
	};
	
	int main()
	{
		using namespace std;
	
		unique_ptr<Myclass> p1{ new Myclass{"hello world"} };
		// unique_ptr is a move only type
	
		unique_ptr<Myclass> p2 = p1;	// syntax error
		// unique_ptr does nove have a copy constructor.
	
		unique_ptr<Myclass> p3;
		p3 = p1;						// syntax error
		// unique_ptr does nove have a copy assignment.
	
		vector <unique_ptr<Myclass>> myvec;
		unique_ptr<Myclass> p4;
		myvec.push_back(p4);			// syntax error
		// push_back functions is using copy constructor
	
	
		unique_ptr<Myclass> p5{ new Myclass{"Live show"} };
		unique_ptr<Myclass> p6 = std::move(p5);	// legal
		// move ctor has been used
	
		unique_ptr<Myclass> p7;
		cout << (p6 ? "p6: full" : "p6: empty") << '\n';	// output -> p6: full
		cout << (p7 ? "p7: full" : "p7: empty") << '\n';	// output -> p7: empty
	
		p7 = std::move(p6);
		// move assignment has been used.
	
		cout << (p6 ? "p6: full" : "p6: empty") << '\n';	// output -> p6: empty
		cout << (p7 ? "p7: full" : "p7: empty") << '\n';	// output -> p7: full
		// because of p6 has been moved to p7 (its resources has been stolen!)
	}
*/

/*
	#include <memory>
	#include <string>
	
	class Myclass {
	public:
		Myclass() = default;
	
		Myclass(std::string str) : mx{ str } {}
	
		~Myclass()
		{
			std::cout << *this << " -> object has been deleted .\n";
		}
	
		std::string& operator*()
		{
			return mx;
		}
	
		friend std::ostream& operator<<(std::ostream& os, const Myclass& myclass)
		{
			return os << myclass.mx;
		}
	private:
		std::string mx;
	};
	
	int main()
	{
		using namespace std;
	
		unique_ptr<Myclass> up1{ new Myclass{"hello world"} };
		unique_ptr<Myclass> up2{ new Myclass{"live in Izmir"} };
	
		cout << "up1 : " << (up1 ? "full" : "empty") << '\n';	// output -> up1 : full
		cout << "up2 : " << (up2 ? "full" : "empty") << '\n';	// output -> up2 : full
	
		cout << *up1 << ' ' << *up2 << '\n';
		// output -> hello world live in Izmir
	
		up1 = std::move(up2);
		// hello world -> object has been deleted .
		// up1 gave back its resources than steal up2's resources.
	
		cout << "up1 : " << (up1 ? "full" : "empty") << '\n';	// output -> up1 : full
		cout << "up2 : " << (up2 ? "full" : "empty") << '\n';	// output -> up2 : empty
	
		cout << "main continues\n";
	
		// output -> live in Izmir -> object has been deleted .
		// up1 that has stole up2's resource, will gave its resources (deleted) at the end of the main scope.
	}
*/

/*
	#include <memory>
	#include <string>
	#include <vector>
	
	class Myclass {
	public:
		Myclass() = default;
	
		Myclass(std::string str) : mx{ str } {}
	
		~Myclass()
		{
			std::cout << *this << " -> object has been deleted .\n";
		}
	
		std::string& operator*()
		{
			return mx;
		}
	
		friend std::ostream& operator<<(std::ostream& os, const Myclass& myclass)
		{
			return os << myclass.mx;
		}
	private:
		std::string mx;
	};
	
	int main()
	{
		using namespace std;
	
		unique_ptr<Myclass> up1{ new Myclass{"hello world"} };
		unique_ptr<Myclass> up2{ new Myclass{"live in Izmir"} };
	
	
		vector<unique_ptr<Myclass>> myvec;
		myvec.reserve(20);
	
		//	myvec.push_back(up1);			// syntax error -> copy overload will be called.
		myvec.push_back(std::move(up1));	// legal -> move overload will be called.
	}
*/

/*
	#include <memory>
	#include <string>
	
	class Myclass {
	public:
		Myclass() = default;
	
		Myclass(std::string str) : mx{ str } {}
	
		~Myclass()
		{
			std::cout << *this << " -> object has been deleted .\n";
		}
	
		std::string& operator*()
		{
			return mx;
		}
	
		friend std::ostream& operator<<(std::ostream& os, const Myclass& myclass)
		{
			return os << myclass.mx;
		}
	private:
		std::string mx;
	};
	
	
	void func(std::unique_ptr<Myclass>);
	
	std::unique_ptr<Myclass> foo()
	{
		// code
		return new{ "try another" };
		// also not valid becuase of the explicit ctor
	}
	
	int main()
	{
		using namespace std;
	
		unique_ptr<Myclass> up = new Myclass{ "hello world!" };		
    // syntax error (copy initialization)
		// becuase of the [new Myclass{"hello world!}] expression 
    // returns a pointer to Myclass object (Myclass*),
		// and because of unique_ptr's one parameter ctor is an explicit ctor,
		// implicit conversion from T* to unique_ptr<T>  is not valid.
	
		unique_ptr<Myclass> up1 = static_cast<unique_ptr<Myclass>>(new Myclass{ "hello world!" });		// legal
		// explicit conversion from T* to unique_ptr<T> with static_cast
	
		unique_ptr<Myclass> up2(new Myclass{ "hello world!" });		
    // direct initialization is	valid
		unique_ptr<Myclass> up3{ new Myclass{ "hello world!" } };	
    // value initialization is also	valid
	
	
		func(new Myclass{ "lets try" });	// also not valid because of ctor is explicit.
		//E0415	no suitable constructor exists to convert 
    // from "Myclass *" to "std::unique_ptr<Myclass, std::default_delete<Myclass>>"
	
		func(unique_ptr<Myclass>{new Myclass{ "this is valid" }});	// legal
	}
*/

/*
	#include <memory>
	
	class Myclass {
	public:
		Myclass() = default;
	
		Myclass(std::string str) : mx{ str } {}
	
		~Myclass()
		{
			std::cout << *this << " -> object has been deleted .\n";
		}
	
		std::string& operator*()
		{
			return mx;
		}
	
		friend std::ostream& operator<<(std::ostream& os, const Myclass& myclass)
		{
			return os << myclass.mx;
		}
	private:
		std::string mx;
	};
	
	int main()
	{
		auto dpx = new Myclass{ "Hello World" };
		// dpx's type is Myclass*
	
		std::unique_ptr<Myclass> up1{ dpx };
		std::unique_ptr<Myclass> up2{ dpx };	// undefined behaviour
	
		std::cout << *up1 << '\n';
		std::cout << *up2 << '\n';
	
		(void)getchar();
		// double deletion will be happen (run-time error)
	}
*/

/*
	#include <memory>
	#include <vector>
	
	class Myclass {
	public:
		Myclass() = default;
	
		Myclass(std::string str) : mx{ str } {}
	
	
		std::string& operator*()
		{
			return mx;
		}
	
		friend std::ostream& operator<<(std::ostream& os, const Myclass& myclass)
		{
			return os << myclass.mx;
		}
	private:
		std::string mx;
	};
	
	void func(std::unique_ptr<Myclass>);
	
	std::unique_ptr<Myclass> foo()
	{
		return MakeUnique<Myclass>("hey now");
	}
	// mandatory copy ellision
	
	
	template <typename T, typename ...Args>
	std::unique_ptr<T> MakeUnique(Args&& ...args)
	{
		return std::unique_ptr<T>{new T(std::forward<Args>(args)...)};
	}
	
	int main()
	{
		auto uptr = MakeUnique<Myclass>("hello world");
	
		func(MakeUnique<Myclass>("Live from Izmir"));
	
	
		std::vector<std::unique_ptr<Myclass>> myvec;
		myvec.reserve(100);
	
		myvec.push_back(std::unique_ptr<Myclass>{});
		myvec.push_back(std::make_unique<Myclass>("hello again"));
		myvec.emplace_back(new Myclass{ "unique_ptr's constructor." });
	}
*/

/*
	#include <memory>

	class Myclass {
	public:
		Myclass() = default;

		Myclass(std::string str) : mx{ str } {}

		~Myclass()
		{
			std::cout << *this << " object has been deleted\n";
		}
		std::string& operator*()
		{
			return mx;
		}

		friend std::ostream& operator<<(std::ostream& os, const Myclass& myclass)
		{
			return os << myclass.mx;
		}
	private:
		std::string mx;
	};

	int main()
	{
		using namespace std;

		auto upx = make_unique<Myclass>("hello world");
		std::cout << *upx << '\n';	// output -> hello world

		upx = new Myclass{ "hello galaxy" };	// syntax error
		// unique_ptr does not have an assignment operator= function 
    // which gets T* as a parameter

		upx.reset();
		// output -> hello world object has been deleted
		// reset() functions job is calling unique_ptr objects destructor immediately 
    // before scope ends.

		cout << "main continues\n";
	}
*/

/*
	#include <memory>
	
	class Myclass {
	public:
		Myclass() = default;
	
		Myclass(std::string str) : mx{ str } {}
	
		~Myclass()
		{
			std::cout << *this << " object has been deleted\n";
		}
		std::string& operator*()
		{
			return mx;
		}
	
		friend std::ostream& operator<<(std::ostream& os, const Myclass& myclass)
		{
			return os << myclass.mx;
		}
	private:
		std::string mx;
	};
	
	int main()
	{
		using namespace std;
	
		auto upx = make_unique<Myclass>("hello world");
	
		upx.reset();
		upx.reset(nullptr);
		upx = nullptr;
		upx = unique_ptr<Myclass>{};
		upx = {};
		// Those 5 lines are same, they both delete the object inside unique_ptr
	}
*/

/*
	#include <memory>
	
	class Myclass {
	public:
		Myclass() = default;
	
		Myclass(std::string str) : mx{ str } {}
	
		~Myclass()
		{
			std::cout << *this << " object has been deleted\n";
		}
		std::string& operator*()
		{
			return mx;
		}
	
		friend std::ostream& operator<<(std::ostream& os, const Myclass& myclass)
		{
			return os << myclass.mx;
		}
	private:
		std::string mx;
	};
	
	int main()
	{
		using namespace std;
	
		auto upx = make_unique<Myclass>("hello world");
		cout << *upx << '\n';	// output -> hello world
	
		upx.reset(new Myclass{"hello galaxy"});
		// output -> hello world object has been deleted
		// reset(Myclass* new_ptr) member function has been used to delete old object that it owns,
		// and get ownership of the new Myclass* object.
	
		cout << *upx << '\n';	// output -> hello galaxy
	}
*/

/*
	#include <memory>
	
	class Myclass {
	public:
		Myclass() = default;
	
		Myclass(std::string str) : mx{ str } {}
	
		~Myclass()
		{
			std::cout << *this << " object has been deleted\n";
		}
		std::string& operator*()
		{
			return mx;
		}
	
		friend std::ostream& operator<<(std::ostream& os, const Myclass& myclass)
		{
			return os << myclass.mx;
		}
	private:
		std::string mx;
	};
	
	int main()
	{
		using namespace std;
	
		auto upx = make_unique<Myclass>("hello world");
		cout << "upx = " << (upx ? "full" : "empty") << "\n";	// output -> upx = full
	
		auto ptr = upx.release();
		// ptr's type will be Myclass*; which is, the pointer that unique_ptr wrapped before.
	
		cout << "upx = " << (upx ? "full" : "empty") << "\n";	// output -> upx = empty
	
		// Because of ptr now holds the Myclass* object.
		// It will not be deleted at the end of the scope.
		// It will exactly act like raw pointer so we manually need to call delete.
	
		delete ptr;
		// output -> hello world object has been deleted
	}
*/

/*
	#include <memory>
	
	class Myclass {
	public:
		Myclass() = default;
	
		Myclass(std::string str) : mx{ str } {}
	
		~Myclass()
		{
			std::cout << *this << " object has been deleted\n";
		}
		std::string& operator*()
		{
			return mx;
		}
	
		friend std::ostream& operator<<(std::ostream& os, const Myclass& myclass)
		{
			return os << myclass.mx;
		}
	private:
		std::string mx;
	};
	
	int main()
	{
		using namespace std;
	
		auto upx = make_unique<Myclass>("hello world");
		cout << "upx = " << (upx ? "full" : "empty") << "\n";	// output -> upx = full
	
		auto ptr = upx.get();
		// ptr's type is Myclass*
	
		cout << "upx = " << (upx ? "full" : "empty") << "\n";	// output -> upx = full
		// upx is still wrapping a pointer and it has still a value ("hello world") inside it.
	
		delete ptr;
		// output -> hello world object has been deleted
		// when we delete the raw pointer (Myclass*) that we get with get() member function.
		// upx unique_ptr still has the same pointer that has been deleted.
		// when main() scope end unique_ptr will delete the pointer but it will be the second time.
		// double deletion error(run-time error) will be happen.
	
		(void)getchar();
	}
*/

/*
	#include <memory>
	
	class Myclass {
	public:
		Myclass() = default;
	
		Myclass(std::string str) : mx{ str } {}
	
		~Myclass()
		{
			std::cout << *this << " object has been deleted\n";
		}
		std::string& operator*()
		{
			return mx;
		}
	
		friend std::ostream& operator<<(std::ostream& os, const Myclass& myclass)
		{
			return os << myclass.mx;
		}
	private:
		std::string mx;
	};
	
	int main()
	{
		using namespace std;
	
		auto upx = make_unique<Myclass>("hello world");
		cout << "upx = " << (upx ? "full" : "empty") << "\n";	// output -> upx = full
	
		auto ptr = upx.get();
		// ptr's type is Myclass*
	
		unique_ptr<Myclass> upx_2{ ptr };
		// When we create a second unique_ptr 
    // with the raw pointer that we get from get() member function.
		// It will cause double deletion error when the scope ends.
		// Both upx and upx_2 are pointing the same location.
	}
*/

/*
	#include <memory>
	
	class Myclass {
	public:
		Myclass() = default;
	
		Myclass(std::string str) : mx{ str } {}
	
		friend std::ostream& operator<<(std::ostream& os, const Myclass& myclass)
		{
			return os << myclass.mx;
		}
	private:
		std::string mx;
	};
	
	int main()
	{
		using namespace std;
	
		auto upx = make_unique<Myclass>("hello world");
	
		cout << "Myclass objects address is = " << upx.get() << '\n';
		cout << "Myclass objects address is = " << upx << '\n';
		// Those 2 lines are same
		cout << "unique_ptr<Myclass> objects address is " <<  &upx << '\n';
	
		// output ->
		//	Myclass objects address is = 013935D8
		//	Myclass objects address is = 013935D8
		//	unique_ptr<Myclass> objects address is 00DEFEAC
	}
*/

/*
	#include <memory>
	
	class Myclass {
	public:
		Myclass() = default;
	
		Myclass(std::string str) : mx{ str } {}
	
		friend std::ostream& operator<<(std::ostream& os, const Myclass& myclass)
		{
			return os << myclass.mx;
		}
	private:
		std::string mx;
	};
	
	int main()
	{
		using namespace std;
	
		auto upx = make_unique<Myclass>("hello world");
	
		auto upy = std::move(upx);
		auto upy(upx.release());
		// Those 2 lines are same.
	
		// Because of the Myclass object that holds "hello world" is on the heap 
    // [dynamically allocated]
		// because of it's creation we use make_unique() factory function 
    // which created object on the heap.
		// auto upy(upx.release()); statement will act like 
    // auto upy(new Myclass{"hello world});
	}
*/

/*
	#include <memory>
	#include <string>
	
	int main()
	{
		using namespace std;
	
		unique_ptr<string> ups;
	
		auto fd = ups.get_deleter();
		// fd's type is std::default_delete<std::string>
	}
*/

/*
	#include <memory>
	#include <string>
	
	struct SDeleter {
	public:
		void operator()(std::string* p)
		{
			std::cout << "the object in address: " << p << " has been deleted.\n";
			delete p;
		}
	};
	
	int main()
	{
		using namespace std;
	
		std::cout << "main has been started\n";
	
		{
			unique_ptr<string, SDeleter> uptr{ new string {"hello world"} };
		}
	
		std::cout << "main continues\n";
		// output ->
		//	main has been started
		//	the object in address : 0123AA38 has been deleted.
		//	main continues
	}
*/

/*
	#include <memory>
	#include <string>
	
	void mydeleter(std::string* p)
	{
		std::cout << "mydeleter function has been called\n";
		delete p;
	}
	
	int main()
	{
		using namespace std;
	
		std::cout << "main has been started\n";
		{
			unique_ptr<string, decltype(&mydeleter)> uptr{ new string {"hello world"}, &mydeleter };
			unique_ptr<string, void(*)(string*)> uptr2{ new string {"from Izmir"}, &mydeleter };
		}
		std::cout << "main continues\n";
		// output ->
		//	main has been started
		//	mydeleter function has been called
		//	mydeleter function has been called
		//	main continues
	}
*/

/*
	#include <memory>
	#include <string>
	
	int main()
	{
		using namespace std;
	
		auto fdel = [](string* p) {
			std::cout << "fdel lambda objects operator() function has been called\n";
			delete p;
		};
	
		std::cout << "main has been started\n";
		{
			unique_ptr<string, decltype(fdel)> uptr{ new string {"hello world"}, fdel };
			// before C++20 because of stateless lambda objects does not have default ctor.
	
			unique_ptr<string, decltype(fdel)> uptr{ new string {"hello world"} };
			// after C++20 because of stateless lambda object does have default ctor.
			// before C++20 -> syntax error
		}
		std::cout << "main continues\n";
	}
*/

/*
	Since C++20
	STATELESS lambda expressions
		1. does have default constructor
		2. does have copy assignment function
		3. can be used in unevaluated context
*/

/*
	#include <memory>
	#include <string>
	
	int main()
	{
		using namespace std;
	
		std::cout << "main has been started\n";
		{
			unique_ptr < string, decltype([](string* p) {
				cout << "stateless lambda expression in unevaluated context\n";
				delete p;
				}) > uptr{ new string {"hello world"} };
		}
		std::cout << "main continues\n";
		// output ->
		//	main has been started
		//	stateless lambda expression in unevaluated context
		//	main continues
	}
*/

/*
	#include <memory>
	#include <string>
	#include <cstdio>
	#define _CRT_SECURE_NO_WARNINGS
	
	int main()
	{
		using namespace std;
	
		{
			FILE* f = fopen("out.txt", "w");
	
			fprintf(f, "hello world\n");
			fprintf(f, "from Izmir\n");
	
			fclose(f);
			// 1. we can forget to close the file.
			// 2. before fclose() function called some exception can be thrown.
		}
	
		using file_closer = decltype([](FILE* fp) {fclose(fp); });
		unique_ptr<FILE, file_closer> uptr{ fopen("out.txt", "w") };
	}
*/

/*
	#include <memory>
	#include <string>
	
	template <typename T>
	class Myclass {
	public:
		Myclass()
		{
			std::cout << "primary template\n";
		}
	};
	
	template <typename T>
	class Myclass<T[]> {
	public:
		Myclass()
		{
			std::cout << "array partial specialization\n";
		}
	};
	
	template <typename T>
	struct DefaultDelete {
		void operator()(T* p)
		{
			delete p;
		}
	};
	
	template <typename T>
	struct DefaultDelete<T[]> {
		void operator()(T* p)
		{
			delete[] p;
		}
	};
	
	int main()
	{
		using namespace std;
	
		Myclass<int> m1;
		Myclass<int[]> m2;
		// output ->
		//	primary template
		//	array partial specialization
	
		auto fdel = [](string* p) {delete[] p; };
	
		{
			unique_ptr<string> uptr{ new string[100] };
			// Error using default_deleter for an array.
	
			unique_ptr<string, decltype(fdel)> uptr_2{ new string[100] };
			// Valid but not a good solution
		}
	
		// unique_ptr has a partial specialization for array
		// 2nd template argument default_delete also have array partial specialization.
	
		unique_ptr<string[]> uptr_3(new string[100]);
		// There aren't any operator* and operator-> functions for array specialization.
		// There is an operator[] function for array specialization.
	
		for (int i{}; i < 100; ++i) {
			uptr_3[i];	// operator[] function.
		}
	}
*/

/*
	#include <vector>
	#include <memory>
	#include <string>
	#include <algorithm>
	
	int main()
	{
		using namespace std;
	
		vector<unique_ptr<string>> vec;
		vec.emplace_back(new string{"hello world"});
		vec.emplace_back(new string{"hello galaxy"});
		vec.emplace_back(new string{"hello universe"});
		vec.emplace_back(new string{"hello matrix"});
	
		sort(vec.begin(), vec.end());
		// sorted by pointer addresses not the strings inside pointers.
	
		for (const auto& up : vec)
			cout << *up << '\n';
		// output ->
		//	hello world
		//	hello matrix
		//	hello galaxy
		//	hello universe
	
		sort(vec.begin(), vec.end(), [](const auto& p1, const auto& p2){
			return *p1 < *p2;
			});
	
		for (const auto& up : vec)
			cout << *up << '\n';
		// output ->
		//	hello galaxy
		//	hello matrix
		//	hello universe
		//	hello world
	}
*/

/*
	#include <memory>
	#include <string>
	
	class Myclass {
		Myclass(std::string name, int age);
	};
	
	std::unique_ptr<Myclass> make_myclass(std::string name, int age)
	{
		return std::make_unique<Myclass>(name, age);
	}
	
	int main()
	{
		auto up = make_myclass("hello", 28);
		// we can create our own factory functions.
	}
*/

/*
	#include <memory>
	#include <string>
	
	void sink(std::unique_ptr<std::string> up)
	{
	
	}
	// sink functions
	// takes an argument, use that argument and
	// its life will be end after using it.
	
	std::unique_ptr<std::string> pass_through(std::unique_ptr<std::string> up)
	{
		// code here
		std::cout << "length: " << up->length() << '\n';
		std::cout << "string: " << *up << '\n';
		// code here
	
		return up;
	}
	// pass_through functions
	// takes an argument, do some operations
	// returns that argument.
	
	int main()
	{
		using namespace std;
	
		{
			auto up = pass_through(make_unique<string>("hello world"));
		}
		std::cout << "main continious\n";
		// output ->
		//	length: 11
		//	string : hello world
		//	main continious
	}
*/

/*
	#include <memory>
	#include <exception>
	
	struct Date {
		Date(int d, int y, int m) : d(d), y(y), m(m){}
		int d, y, m;
	};
	
	void bar()
	{
		throw std::runtime_error{ "error error error!" };
	}
	
	void foo(int d, int m, int y)
	{
		Date* p = new Date(d, m, y);
	
		bar();
		// if bar() throws an exception
		// Date objects destructor can not be called.
	
		delete p;
	
		auto up2 = std::make_unique<Date>(d, m, y);
		// if some exception thrown, objects life will be end in stack unwinding phase.
		// else at the end of the scope unique_ptr's life will end.
	}
	
	int main()
	{
		try {
			foo(1, 1, 1111);
		}
		catch (const std::exception& ex){
			std::cout << "exception caught: " << ex.what() << '\n';
		}
		// output -> exception caught: error error error!
	}
*/

/*
	#include <memory>
	#include <string>
	
	// if we use classes data member as unique_ptr,
	// compiler generated copy constructor and copy assignment
	// will become implicitly deleted.
	
	class Person {
	public:
		std::unique_ptr<std::string> mp_name{};
	};
	// Person class become move only class.
	
	int main()
	{
		Person p1;
		auto p2 = p1;		// syntax error, calling copy ctor
	
		Person p3;
		p1 = p3;			// syntax error, calling copy assingment
	
		p1 = std::move(p3);	// valid, calling move assignment.
	}
*/

/*
	------------------
	| shared pointer |
	------------------
*/

/*
	reference counting technique has been used in shared_ptr class template.

	shared_ptr holds 2 pointers
		1. Pointer to dynamic storage duration object
		2. Pointer to control block 
			(Reference Count, Weak Count, Other Data.. e.g custom deleter, allocator)

	Control block created when we create a shared_ptr. 
	If we copy that shared_ptr to create a new shared_ptr,
	control block will not be created again.

	shared_ptr have an overhead compared to the unique_ptr.
	control block has cost (creating cost, memory cost)

	if we did not call make_shared() factory function to create a shared_ptr
	compiler can not allocate dynamic storage duration object and the control block 
	as one block of memory (contigious)

	deleter is a template parameter in unique_ptr but not in shared_ptr
	constructor will get deleter as an argument in shared_ptr
*/

/*
	#include <memory>
	#include <string>
	
	int main()
	{
		using uptr = std::unique_ptr<std::string>;
		using sptr = std::shared_ptr<std::string>;
	
		std::cout << "sizeof(uptr) = " << sizeof(uptr) << '\n';
		std::cout << "sizeof(sptr) = " << sizeof(sptr) << '\n';
		// output ->
		//	sizeof(uptr) = 8
		//	sizeof(sptr) = 16
	}
*/

/*
	#include <memory>
	#include <string>
	
	int main()
	{
		using namespace std;
	
		shared_ptr<string> sp1{ new string{"hello world"} };
	
		auto sp2 = sp1;	// copy constructor called.
		auto sp3 = sp1;
		auto sp4 = sp1;
	
		*sp1 += " we are live";
		cout << *sp2 << '\n';	// output -> hello world we are live
		*sp3 += " from Izmir.";
		cout << *sp4 << '\n';	// output -> hello world we are live from Izmir.
	}
*/

/*
	#include <memory>
	#include <string>
	
	int main()
	{
		using namespace std;
	
		shared_ptr<string> sp1{ new string{"hello world"} };
		cout << "sp1.use_count() = " << sp1.use_count() << '\n';
	
		auto sp2 = sp1;
		cout << "sp1.use_count() = " << sp1.use_count() << '\n';
	
		{
			auto sp3 = sp1;
			cout << "sp1.use_count() = " << sp1.use_count() << '\n';
		}
	
		cout << "sp1.use_count() = " << sp1.use_count() << '\n';
	
		auto sp4 = sp1;
		cout << "sp1.use_count() = " << sp1.use_count() << '\n';
	
		// output ->
		//	sp1.use_count() = 1
		//	sp1.use_count() = 2
		//	sp1.use_count() = 3
		//	sp1.use_count() = 2
		//	sp1.use_count() = 3
	}
*/

/*
	#include <memory>
	#include <string>
	
	int main()
	{
		using namespace std;
	
		shared_ptr<string> sp1{ new string{"hello world"} };
	
		cout << "sp1.use_count() = " << sp1.use_count() << '\n';
		// output -> sp1.use_count() = 1
	
		auto sp2 = sp1;
		cout << "sp1.use_count() = " << sp1.use_count() << '\n';
		cout << "sp2.use_count() = " << sp2.use_count() << '\n';
		// output ->
		//	sp1.use_count() = 2
		//	sp2.use_count() = 2
	
		sp1.reset();
		cout << "sp1.use_count() = " << sp1.use_count() << '\n';
		cout << "sp2.use_count() = " << sp2.use_count() << '\n';
		// output ->
		//	sp1.use_count() = 0
		//	sp2.use_count() = 1
	
		cout << *sp2 << '\n';	// output -> hello world
	}
*/

/*
	#include <memory>
	#include <string>
	
	int main()
	{
		using namespace std;
	
		shared_ptr<string> sp1;
		shared_ptr<string> sp2(new string{ "hello world" });
	
		// operator bool() function
		cout << "sp1 = " << (sp1 ? "full" : "empty") << '\n';	// output -> sp1 = empty
		cout << "sp2 = " << (sp2 ? "full" : "empty") << '\n';	// output -> sp2 = full
	}
*/

/*
	unique() member function deleted in C++17, no longer exist after C++20.
	use_count() returns 1 and unique() returns true are same behaviours
*/

/*
	#include <memory>
	#include <string>
	
	int main()
	{
		using namespace std;
	
		{
			shared_ptr<string> sp1(new string{ "hello world" }, [](string* p) {
				cout << "custom deleter\n"; delete p;
				});
		}
		// sending lambda expression (custom deleter)(callable) to shared_ptr's constructor 
	
		cout << "main continues\n";
		// output ->
		//	custom deleter
		//	main continues
	}
*/

/*
	#include <memory>
	#include <string>
	
	
	struct Date {
		Date(int d, int m, int y) : m_day(d), m_mon(m), m_year(y) {}
		int m_day, m_mon, m_year;
	};
	
	int main()
	{
		using namespace std;
	
		auto sp = make_shared<string>(10, 'A');
		cout << *sp << '\n';	// output -> AAAAAAAAAA
	
		auto sp2 = make_shared<Date>(1, 1, 1991);
	
		cout << "year = " << sp2->m_year << '\n';	// output -> 1991
		cout << "month = " << sp2->m_mon << '\n';	// output -> 1
		cout << "day = " << sp2->m_day << '\n';		// output -> 1
	}
*/

/*
	#include <memory>
	#include <exception>
	
	void* operator new(std::size_t sz)
	{
		std::cout << "operator new called. sz = " << sz << '\n';
	
		void* vp = std::malloc(sz);
	
		if (!vp)
			throw std::bad_alloc{};
	
		return vp;
	}
	
	struct Date {
		Date(int d, int m, int y) : m_day(d), m_mon(m), m_year(y) {}
		int m_day, m_mon, m_year;
	};
	
	int main()
	{
		using namespace std;
	
		std::cout << "sizeof(Date) = " << sizeof(Date) << '\n';
		// output -> //	sizeof(Date) = 12
	
		shared_ptr<Date> sptr{ new Date{1, 1, 1991} };
		// output ->
		//	operator new called.sz = 12		-> for Date object
		//	operator new called.sz = 24		-> for Control block
		// 2 allocation happened.
	
		auto sptr2 = make_shared<Date>(1, 1, 1991);
		// output -> operator new called.sz = 32
		// only 1 allocation happened. (Date object + Control Block)
	}
*/

/*
	#include <memory>
	
	struct Date {
		Date() = default;
		Date(int d, int m, int y) : m_day(d), m_mon(m), m_year(y) {}
		int m_day, m_mon, m_year;
	};
	
	int main()
	{
		using namespace std;
	
		shared_ptr<Date[]> sptr(new Date[10]);
		auto sptr2 = make_shared<Date[]>(10);
	
		sptr.operator[](2) = Date(1, 1, 1991);
		// operator[]() function for array specialization
	
		*sptr;	// syntax error for array specialization
	}
*/

/*
	#include <memory>
	#include <string>
	
	int main()
	{
		using namespace std;
	
		shared_ptr<string> sp1(new string{ "hello world" }, [](string* p) {
			cout << *p << " will be deleted\n"; delete p;
			});
		shared_ptr<string> sp2(new string{ "hello universe" });
	
		cout << "sp1.use_count() = " << sp1.use_count() << '\n';
		cout << "sp2.use_count() = " << sp2.use_count() << '\n';
	
		sp1 = sp2;
		cout << "after assingment\n";
		cout << "sp1.use_count() = " << sp1.use_count() << '\n';
		cout << "sp2.use_count() = " << sp2.use_count() << '\n';
	
		// output ->
		//	sp1.use_count() = 1
		//	sp2.use_count() = 1
		//	hello world will be deleted 
		//		-> because of sp1 is now owns the same pointer that sp2 owns before. 
		//	after assingment
		//	sp1.use_count() = 2	
		//	sp2.use_count() = 2
		//		-> sp1 and sp2 use_count = 2, they both point 
    //       the same pointer that points to "hello universe" string
	}
*/

/*
	#include <memory>
	#include <string>
	
	int main()
	{
		using namespace std;
	
		shared_ptr<string> sp1(new string{ "hello world" }, [](string* p) {
			cout << *p << " will be deleted\n"; delete p;
			});
		shared_ptr<string> sp2(new string{ "hello universe" });
	
		cout << "sp1.use_count() = " << sp1.use_count() << '\n';
		cout << "sp2.use_count() = " << sp2.use_count() << '\n';
	
		sp1 = move(sp2);
		cout << "after assingment\n";
		cout << "sp1.use_count() = " << sp1.use_count() << '\n';
		cout << "sp2.use_count() = " << sp2.use_count() << '\n';
	
		// output ->
		//	sp1.use_count() = 1
		//	sp2.use_count() = 1
		//	hello world will be deleted -> sp1 is become pointing to the string that 
    //                                 sp2 is pointing before.
		//	after assingment
		//	sp1.use_count() = 1	-> sp1(the pointer that sp1 wraps, owns) is now 
    //                         pointing to "hello universe"
		//	sp2.use_count() = 0 -> pointer that sp2 owns has stolen by sp1, 
    //                         sp2 do not own any pointer now.
	}
*/

/*
	#include <memory>
	#include <vector>
	#include <list>
	#include "nutility.h"
	
	int main()
	{
		using namespace std;
	
		vector<shared_ptr<string>> svec;
	
		for (int i = 0; i < 5; ++i) {
			svec.emplace_back(new string(rtown()));
		}
	
		cout << "svec.size() = " << svec.size() << '\n';	// output -> svec.size() = 10
	
		for (const auto& sp : svec) {
			cout << *sp << '\n';
		}
		// output ->
		//	rize
		//	canakkale
		//	balikesir
		//	bolu
		//	igdir
	
		list<shared_ptr<string>> slist(svec.begin(), svec.end());
		for (auto& sp : slist) {
			*sp += "111";
		}
	
		for (const auto& sp : svec) {
			cout << *sp << '\n';
		}
		// output ->
		//	rize111
		//	canakkale111
		//	balikesir111
		//	bolu111
		//	igdir111
	
		// both shared_ptr's in vector and list are pointing to the same objects.
	}
*/

/*
	#include <memory>
	
	int main()
	{
		using namespace std;
	
		auto sp = make_shared<string>("hello world");
	
		cout << "string is @" << sp << '\n';
		cout << "string is @" << sp.get() << '\n';
		// Those 2 lines are same
		cout << "*sp = " << *sp << '\n';
	
		// output ->
		//	string is @000001E0BE686EF0
		//	string is @000001E0BE686EF0
		//	* sp = hello world
	}
*/

/*
	#include <memory>
	
	int main()
	{
		using namespace std;
	
		auto sp = make_shared<string>("hello world");
	
		sp = nullptr;
		sp = {};
		sp.reset();
		// Those 3 lines are same and they all will make sp empty.
	}
*/

/*
	#include <memory>
	#include <list>
	#include <string>
	#include <vector>
	#include <algorithm>

	class City {
	public:
		City(std::string str) : mcity_name(str) {}
		friend std::ostream& operator<<(std::ostream& os, const City& c)
		{
			return os << c.mcity_name << ' ';
		}
		auto operator<=>(const City& c)const = default;
	private:
		std::string mcity_name;
	};

	int main()
	{

		using CityPtr = std::shared_ptr<City>;

		std::list<CityPtr> mylist;

		mylist.emplace_back(new City{ "istanbul" });
		mylist.emplace_back(new City{ "ankara" });
		mylist.emplace_back(new City{ "izmir" });
		mylist.emplace_back(new City{ "rize" });
		mylist.emplace_back(new City{ "sanliurfa" });

		{
			std::vector<CityPtr> myvec(mylist.begin(), mylist.end());

			std::sort(myvec.begin(), myvec.end(), [](const auto& p1, const auto& p2) {
				return *p1 < *p2;
				});

			for (auto& s : myvec)
				std::cout << *s;
			// output -> ankara istanbul izmir rize sanliurfa
			std::cout << '\n';
		}


		for (auto& s : mylist)
			std::cout << *s;
		// output -> istanbul ankara izmir rize sanliurfa

		std::cout << '\n';
		std::cout << "main continues\n";
	}
*/

/*
	--------------------------------
	| week pointer - std::weak_ptr |
	--------------------------------
*/

/*
	#include <memory>
	
	struct Date {
		Date() = default;
		Date(int d, int m, int y) : m_day(d), m_mon(m), m_year(y) {}
		int m_day, m_mon, m_year;
	};
	
	int main()
	{
		using namespace std;
	
		auto sp = make_shared<Date>(1, 2, 1993);
		cout << "sp.use_count() = " << sp.use_count() << '\n';		// output -> sp.use_count() = 1
	
		weak_ptr<Date> wp1(sp);
		weak_ptr<Date> wp2(sp);
		weak_ptr<Date> wp3(sp);
		cout << "sp.use_count() = " << sp.use_count() << '\n';		// output -> sp.use_count() = 1
		cout << "wp1.use_count() = " << wp1.use_count() << '\n';	// output -> wp1.use_count() = 1
	
		*sp;	// valid
		// we can reach the object that shared pointer points to with dereferencing operator.
		*wp1;	// syntax error.
		// we can not reach the object that weak pointer points to with dereferencing operator.
	}
*/

/*
	#include <memory>
	
	struct Date {
		Date() = default;
		Date(int d, int m, int y) : m_day(d), m_mon(m), m_year(y) {}
		int m_day, m_mon, m_year;
	};
	
	int main()
	{
		using namespace std;
	
		auto sp = make_shared<Date>(1, 2, 1993);
		weak_ptr<Date> wp(sp);
	
		if (wp.expired())
			cout << "object not exists\n";
		else
			cout << "object exists\n";
		// output -> object exists
		// because of shared_ptr is still alive. wp is not expired. object exists.
	
		wp.reset();
	
		if (wp.expired())
			cout << "object not exists\n";
		else
			cout << "object exists\n";
		// output -> object not exists
	}
*/

/*
	#include <memory>
	
	struct Date {
		Date() = default;
		Date(int d, int m, int y) : m_day(d), m_mon(m), m_year(y) {}
	
		friend std::ostream& operator<<(std::ostream& os, const Date& d)
		{
			return os << '(' << d.m_day << ", " << d.m_mon << ", " << d.m_year << ")\n";
		}
	
		int m_day, m_mon, m_year;
	};
	
	int main()
	{
		using namespace std;
	
		auto sp = make_shared<Date>(1, 2, 1993);
		weak_ptr<Date> wp(sp);
	
		cout << "sp.use_count() = " << sp.use_count() << '\n';
	
		// weak_ptr.lock() member function returns shared_ptr
		// if the object that shared_ptr pointing is still alive,
		// will return a new shared_ptr pointing the same object
		// else return nullptr
	
		if (auto spx = wp.lock())
		{
			cout << "object still exists\n";
			cout << "sp.use_count() = " << sp.use_count() << '\n';
			cout << *spx;
			cout << *sp;
		}
		else
			cout << "object is not exists\n";
	
		// output ->
		//	sp.use_count() = 1
		//	object still exists
		//	sp.use_count() = 2
		//	(1, 2, 1993)
		//	(1, 2, 1993)
	
		wp.reset();
		if (auto spx = wp.lock())
			cout << "object still exists\n";
		else
			cout << "object is not exists\n";
		// output -> cout << "object is not exists\n";
	}
*/ 

/*
	#include <memory>
	#include <exception>
	#include <string>
	
	int main()
	{
		using namespace std;
	
		auto sp = make_shared<string>("hello world");
		weak_ptr<string> wp(sp);
	
		sp.reset();	// reset the shared_ptr resource that used to create weak_ptr
	
		try
		{
			shared_ptr<string> spx(wp);	// output -> exception caught: bad_weak_ptr
		}
		catch (const std::exception& ex)
		{
			cout << "exception caught: " << ex.what() << '\n';
		}
	
		if (!wp.expired()) {
			shared_ptr<string> spx(wp);
		}
		// not possible to throw exception in this scenerio.
		// we are controlling that if the shared_ptr(that weak_ptr is created from) still have the resources.
		// with weak_ptr's expired() member function
	}
*/

/*
	#include <memory>

	struct B;

	struct A {
		std::shared_ptr<B> bptr;
		~A() {
			std::cout << "A destructor\n";
		}
	};

	struct B {
		std::shared_ptr<A> aptr;
		~B() {
			std::cout << "B destructor\n";
		}
	};

	int main()
	{
		std::shared_ptr<A> spa{ new A };
		std::shared_ptr<B> spb{ new B };

		std::cout << "spb.use_count() = " << spb.use_count() << '\n';
		spa->bptr = spb;
		std::cout << "spb.use_count() = " << spb.use_count() << '\n';

		// output ->
		//	spb.use_count() = 1
		//  spb.use_count() = 2
		//	A destructor
		//	B destructor
	}
*/

/*
	#include <memory>
	
	struct B;
	
	struct A {
		std::shared_ptr<B> bptr;
		~A() {
			std::cout << "A destructor\n";
		}
	};
	
	struct B {
		std::shared_ptr<A> aptr;
		~B() {
			std::cout << "B destructor\n";
		}
	};
	
	int main()
	{
		std::shared_ptr<A> spa{ new A };
		std::shared_ptr<B> spb{ new B };
	
		spa->bptr = spb;
		std::cout << "spb.use_count() = " << spb.use_count() << '\n';
		spb->aptr = spa;
		std::cout << "spa.use_count() = " << spa.use_count() << '\n';
	
		// output ->
		//	spb.use_count() = 2
		//  spa.use_count() = 2
	}
*/

/*
	#include <memory>
	
	struct B;
	
	struct A {
		std::weak_ptr<B> bptr;
		~A() {
			std::cout << "A destructor\n";
		}
	};
	
	struct B {
		std::shared_ptr<A> aptr;
		~B() {
			std::cout << "B destructor\n";
		}
	};
	
	int main()
	{
		std::shared_ptr<A> spa{ new A };
		std::shared_ptr<B> spb{ new B };
	
		spa->bptr = spb;
		std::cout << "spb.use_count() = " << spb.use_count() << '\n';
		spb->aptr = spa;
		std::cout << "spa.use_count() = " << spa.use_count() << '\n';
	
		// output ->
		//	spb.use_count() = 1
		//	spa.use_count() = 2
		//	B destructor
		//	A destructor
	}
*/

/*
	#include <memory>
	#include <string>
	
	class Dog {
	public:
		Dog(std::string name) : m_name(std::move(name))
		{
			std::cout << m_name << " born\n";
		}
		~Dog()
		{
			std::cout << m_name << " dead\n";
		}
	
		void bark()
		{
			std::cout << m_name << " is barking\n";
		}
	
		void make_friend(std::shared_ptr<Dog> friend_dog)
		{
			mp_friend = friend_dog;
			std::cout << m_name << " and " << friend_dog->m_name << " become friends\n";
		}
	
		bool has_friend() const
		{
			return !mp_friend.expired();
		}
	
		void print() const
		{
			std::cout << "dog name: " << m_name;
	
			if (!mp_friend.expired())
				std::cout << ", has a friend called " << mp_friend.lock()->m_name << '\n';
			else
				std::cout << ", doesn't have friend\n";
		}
	private:
		std::weak_ptr<Dog> mp_friend;
		std::string m_name;
	};
	
	int main()
	{
		using namespace std;
		shared_ptr<Dog> sp1(make_shared<Dog>("dog1"));
		shared_ptr<Dog> sp2(make_shared<Dog>("dog2"));
	
		sp1->make_friend(sp2);
		sp2->make_friend(sp1);
	
		std::cout << sp1.use_count() << '\n';
		std::cout << sp2.use_count() << '\n';
	
		sp1->print();
		sp2->print();
	}
*/

/*
  ----------------------------------------------------
  | CRTP(Curiously Recurring Template Pattern) idiom |
  ----------------------------------------------------
*/

/*
	// CRTP(Curiously Recurring Template Pattern) idiom
	// 1. compile-time polymorphism
	// 2. calling derived class member functions from base classes member function.
	
	#include <memory>
	
	template <typename T>
	class Animal {
	public:
		void cry()
		{
			static_cast<T*>(this)->make_sound();
		}
	};
	
	class Dog : public Animal<Dog> {
	public:
		void make_sound()
		{
			std::cout << "hav hav hav\n";
		}
	};
	
	class Cat : public Animal<Cat> {
	public:
		void make_sound() {
			std::cout << "miyav miyav\n";
		}
	};

	class Lamb : public Animal<Lamb> {
	public:
		void make_sound() {
			std::cout << "meee\n";
		}
	};

	template <typename T>
	void talk_pet(Animal<T>& x)
	{
		x.cry();
	}
	
	int main()
	{
		Dog mydog;
		Cat mycat;
		Lamb mylamb;

		talk_pet(mylamb);
		talk_pet(mycat);	
		talk_pet(mydog);
		// output ->
		//	meee
		//	miyav miyav
		//	hav hav hav
	}
*/

/*
	template <typename D>
	class Base {
	public:
		bool is_greater(const Base& other)const
		{
			return !static_cast<const D&>(*this).operator<(other);
		}
	};
	
	class Der : public Base<Der> {
	public:
		bool operator<(const Der&);
	};
	
	class Mer : public Base<Mer> {
	public:
		bool operator<(const Mer&);
	};
*/

/*
	#include <string>
	
	template <typename Der>
	struct comparison {
		const Der& derived() const
		{
			return static_cast<const Der&>(*this);
		}
	
		friend bool operator>(const comparison<Der>& left, const comparison<Der>& right)
		{
			return right.derived() < left.derived();
		}
	
		friend bool operator>=(const comparison<Der>& left, const comparison<Der>& right)
		{
			return !(left.derived() < right.derived());
		}
	
		friend bool operator<=(const comparison<Der>& left, const comparison<Der>& right)
		{
			return !(right.derived() < left.derived());
		}
	
		friend bool operator==(const comparison<Der>& left, const comparison<Der>& right)
		{
			return !(left.derived() < right.derived()) && !(right.derived() < left.derived());
		}
	
		friend bool operator!=(const comparison<Der>& left, const comparison<Der>& right)
		{
			return !(left == right);
		}
	};
	
	class Myclass : public comparison<Myclass>
	{
	public:
		Myclass(int x) : x_{ x } {}
		bool operator<(const Myclass& other)const
		{
			return x_ < other.x_;
		}
	private:
		int x_;
	};
	
	class Person : public comparison<Person> {
	public:
		Person(std::string name) : name_(std::move(name)) {}
		bool operator<(const Person& other) const
		{
			return name_ < other.name_;
		}
	private:
		std::string name_;
	};
	
	// Think about you have different wrapper classes and all of its members are sorted
	// with different comparison styles Every classes operator<() function behaves different.
	// Normally you have to write all of the functions in Comparison class to all of your classes.
	// But when using CRTP if we define only operator<() function inside our Der class
	// we can also use operator>=(), operator<=() operator==(),operator!=() functions
	// which are defined inside its Base class.
	
	// e.g think about der_1.operator>(der_2) function needs to be executed.
	// because of base class does have operator>() overload, inside of this function
	// Base classes derived() member function will be called for both of the objects (right and left) ,
	// that are actually has been used as a Base object (Base class inside of the Derived class object).
	// Applying static_cast to "Base objects" them to become "Derived objects" again,
	// and using Derived classes member operator<() function to inside Base classes operator>() function.
	
	int main()
	{
		using namespace std;
	
		Myclass x{ 123 }, y{ 111 };
		cout << boolalpha;
	
		cout << "x < y	:	"	<< (x < y) << '\n';
		cout << "x <= y	:	"	<< (x <= y) << '\n';
		cout << "x > y	:	"	<< (x > y) << '\n';
		cout << "x > y	:	"	<< (x >= y) << '\n';
		cout << "x > y	:	"	<< (x == y) << '\n';
		cout << "x > y	:	"	<< (x != y) << '\n';
	
	
		Person str_x{ "hello" };
		Person str_y{ "world" };
	
		cout << "str_x < str_y	:	" << (str_x < str_y) << '\n';
		cout << "str_x <= str_y	:	" << (str_x <= str_y) << '\n';
		cout << "str_x > str_y	:	" << (str_x > str_y) << '\n';
		cout << "str_x > str_y	:	" << (str_x >= str_y) << '\n';
		cout << "str_x > str_y	:	" << (str_x == str_y) << '\n';
		cout << "str_x > str_y	:	" << (str_x != str_y) << '\n';
	}
*/

/*
	#include <memory>
	
	class Myclass : public std::enable_shared_from_this<Myclass> {	// CRTP
	public:
		Myclass()
		{
			std::cout << "Myclass ctor this: " << this << '\n';
		}
	
		void func()
		{
			std::cout << "Myclass::func() function : " << this << '\n';
			// i am sure that func() function is called for a dynamic Myclass object,
			// controlled by a shared_ptr
			auto sptr = shared_from_this();
			std::cout << "sptr.use_count() = " << sptr.use_count() << '\n';
		}
	
		~Myclass()
		{
			std::cout << "Myclass desturctor : " << this << '\n';
		}
	};
	
	int main()
	{
		using namespace std;
	
		auto sp = make_shared<Myclass>();
		sp->func();
	
		// output ->
		//	Myclass ctor this: 000001F3E66CFB90
		//	Myclass::func() function : 000001F3E66CFB90
		//	sptr.use_count() = 2 -> We created another shared_ptr as same as (sp) in main block.
		//	Myclass desturctor : 000001F3E66CFB90
	
	
		Myclass* p = new Myclass;
		try
		{
			p->func();
		}
		catch (const std::exception& ex)
		{
			cout << "exception caught: " << ex.what() << '\n';
		}
		// calling func() member function with raw pointer.
		// output -> exception caught: bad_weak_ptr
	}
*/