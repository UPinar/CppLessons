#include <iostream>

/*
	====================
	| Vocabulary Types | C++17
	====================
*/

/*
	-----------------
	| std::optional |
	-----------------
*/

/*
	#include <optional>
	
	template <typename T>
	class Optional {
	
	private:
		unsigned char buffer[sizeof(T)];
		bool mflag;
	};
	// buffer will hold the element if there is an element.
	// mflag will hold true if there is an element else false
*/

/*
	#include <optional>
	
	class Myclass {
	private:
		unsigned char buf[256];
	};
	
	int main()
	{
		std::cout << "sizeof(Myclass) = " << sizeof(Myclass) << '\n';
		// output -> sizeof(Myclass) = 256
	
		std::cout << "sizeof(std::optional<Myclass>) = "
			<< sizeof(std::optional<Myclass>) << '\n';
		// output -> sizeof(std::optional<Myclass>) = 257
		// sizeof(Myclass) + sizeof(bool) = 257
	}
*/

/*
	#include <optional>
	
	template <std::size_t n>
	struct Mystruct {
	
		char buf[n]{};
	};
	
	using oType_256 = std::optional<Mystruct<256>>;
	using oType_1024 = std::optional<Mystruct<1024>>;
	using oType_2048 = std::optional<Mystruct<2048>>;
	
	int main()
	{
		std::cout << "sizeof(oType_256) = " << sizeof(oType_256) << '\n';
		// output -> sizeof(oType_256) = 257
		std::cout << "sizeof(oType_1024) = " << sizeof(oType_1024) << '\n';
		// output -> sizeof(oType_1024) = 1025
		std::cout << "sizeof(oType_2048) = " << sizeof(oType_2048) << '\n';
		// output -> sizeof(oType_2048) = 2049
	}
*/

/*
	#include <optional>
	
	int main()
	{
		using namespace std;
	
		// optional<string> z();
		// most vexing parse function decleration
	
		optional<string> x;
		optional<string> y{};
		optional<string> z{ nullopt };
	
		// CHECKING IF std::optional OBJECT HAS VALUE //
	
		// ------------- WAY 1 -----------------
		if (x) {}
		if (x.operator bool()) {}
		// Those 2 lines are same
	
		y = "hello world";
		if (y)
			std::cout << "I have value, i am not empty\n";
		else
			std::cout << "I don't have a value\n";
		// output -> I have value, i am not empty
	
	
		// ------------- WAY 2 -----------------
		if (z.has_value())
			std::cout << "I have value, i am not empty\n";
		else
			std::cout << "I don't have a value\n";
		// output -> I don't have a value
		// has_value() member function returns bool
		// operator bool() and has_value() functions job are same.
	
	
		// ------------- WAY 3 -----------------
		if (x != nullopt)
			std::cout << "I have value, i am not empty\n";
		else
			std::cout << "I don't have a value\n";
		// output -> I don't have a value
	}
*/

/*
	#include <optional>
	
	int main()
	{
		using namespace std;
	
		optional<int> x(12);
		optional<int> y{ 3 };			// value initialize
		optional<int> z = 5;			// copy initialize
	
		optional t = 56;					// CTAD -> optional<int>
	
		optional s = "hello";			// CTAD -> optional<const char*>
		optional str = "hello"s;	// CTAD -> optional<std::string>
		// using string literal
	}
*/

/*
	#include <optional>
	
	int main()
	{
		using namespace std;
	
		optional<int> x(345);
		optional<int> y(x);	 // copy constructor
	
		optional<double> z(x);
		// using conversion from int -> double
	}
*/

/*
	#include <optional>
	#include <string>
	#include <complex>
	
	class Myclass {
	public:
		Myclass(int);
	};
	
	class Yourclass {
	public:
		Yourclass(int, int);
	};
	
	int main()
	{
		using namespace std;
	
		optional<Myclass> x{ Myclass{12} };
		optional<Myclass> y{ 12 };
	
	
		optional<Yourclass> z{ 12, 34 };			// not valid
		optional<Yourclass> k(in_place, 12, 34);	// valid
		// arguments needs to be perfect forward to
		// Yourclass objects constructor -> Yourclass(int, int);
		// using in_place object as first argument is solving this problem
	
		optional<string>(45, 'A');				// not valid
		optional<string>(in_place, 45, 'A');	// valid
	
		auto op = make_optional<string>(12, 'A');
		// make_optional() factory function will also handle the problem
		// that in_place object solved.
	
		optional<complex<double>>(in_place, 2.3, 5.6);
		make_optional<complex<double>>(2.3, 5.6);
		// Those 2 lines are same
	}
*/

/*
	#include <optional>
	#include <string>
	
	int main()
	{
		using namespace std;
	
		optional str = "hello world"s;
	
		cout << "str = " << *str << '\n';
		cout << "str = " << str.operator*() << '\n';
		// Those 2 lines are same
		// output -> str = hello world
	
		*str = "hello";	// returns a reference to string object
		cout << "length = " << str->length() << '\n';
		// output -> length = 5
	
	
		str->assign(30, 'a');
		cout << "length = " << str->length() << '\n';
		// output -> length = 30
	}
*/

/*
	// ---------------------------------------------
	// ---------------!! ATTENTION !!---------------
	// ---------------------------------------------
	// operator->()
	// operaotor*()
	
	// if those functions are used with an empty optional object
	// they will not throw an exception

	// using those functions with empty optional object 
	// is UB(Undefined Behaviour)
	
	#include <optional>
	#include <string>
	
	int main()
	{
		using namespace std;
	
		optional<string> ox;
	
		try{
			auto val = *ox;
		}
		catch (const std::exception& ex){
			std::cout << "exception caught: " << ex.what() << '\n';
		}
		// No exception caught -> Undefined Behaviour
	}
*/

/*
	#include <optional>
	#include <string>
	
	int main()
	{
		using namespace std;
	
		optional<string> ox;
	
		if (ox.has_value()) {
			auto val = *ox;
		}
		// controlling before using operator->() or operator*()
		// if optional object has value
	}
*/

/*
	// value() member function returns a reference
	// if object is empty it throws an exception
	
	#include <optional>
	
	int main()
	{
		using namespace std;
	
		optional<string> ox;
	
		try {
			auto x = ox.value();
			cout << "x = " << x << '\n';
		}
		catch (const std::exception& ex) {
			std::cout << "exception caught: " << ex.what() << '\n';
		}
		// output -> exception caught: Bad optional access
	}
*/

/*
	// value_or() member function
	#include <optional>
	
	int main()
	{
		using namespace std;
	
		optional<string> ox;
		optional<string> oy{ "hello world" };
	
		std::cout << "ox = " << ox.value_or("no string") << '\n';
		// output -> ox = no string
		
		std::cout << "oy = " << oy.value_or("no string") << '\n';
		// output -> oy = hello world
	}
*/

/*
	// value_or() member function
	// not returning reference
	#include <optional>
	
	int main()
	{
		using namespace std;
	
		optional<string> ox = "hello world";
		cout << *ox << '\n';	// output -> hello world
	
	
		ox.value() = "hello galaxy";
		cout << *ox << '\n';	// output -> hello galaxy
	
		// value() member function returns a reference
	
		ox.value_or("no string") = "lets try if value or returns a reference";
		cout << *ox << '\n';	// output -> hello galaxy
		// value_or() member function does not return reference
	}
*/

/*
	#include <optional>
	
	class Myclass {
	public:
		Myclass() {
			std::cout << "default ctor this = " << this << '\n';
		}
	
		Myclass(const Myclass&) {
			std::cout << "copy ctor this = " << this << '\n';
		}
	
		~Myclass() {
			std::cout << "destructor this = " << this << '\n';
		}
	
		unsigned char buf[1024]{};
	};
	
	int main()
	{
		using namespace std;
	
		Myclass m;
		optional<Myclass> x{ m };
	
		// output ->
		//	default ctor this = 000000C86CAFEAA0	
		//		-> m objects ctor
		//	copy ctor this = 000000C86CAFEEC0		
		//		-> Myclass object that optional class holds
		//	destructor this = 000000C86CAFEEC0		
		//		-> optional's Myclass objects destructor
		//	destructor this = 000000C86CAFEAA0		
		//		-> m objects dtor
	}
*/

/*
	#include <optional>
	
	class Myclass {
	public:
		~Myclass() {
			std::cout << "destructor this = " << this << '\n';
		}
	
		unsigned char buf[1024]{};
	};
	
	int main()
	{
		using namespace std;
	
		auto way1 = make_optional<Myclass>();
		way1.reset();
		std::cout << "main continues\n";
		// output ->
		//	destructor this = 000000DF48AFDC50
		//	main continues
	
		auto way2 = make_optional<Myclass>();
		way2 = nullopt;
		std::cout << "main continues\n";
		// output ->
		//	destructor this = 000000DF48AFE080
		//	main continues
	
		auto way3 = make_optional<Myclass>();
		way3 = optional<Myclass>{};
		std::cout << "main continues\n";
		// output ->
		//	destructor this = 000000DF48AFE4B0
		//	main continues
	
		auto way4 = make_optional<Myclass>();
		way4 = {};
		std::cout << "main continues\n";
		// output ->
		//	destructor this = 000000DF48AFE8E0
		//	main continues
	}
*/

/*
	// usage example
	#include <optional>
	#include <string>
	
	struct Person {
	public:
		bool has_email()const;
		std::string get_email() const;
	};
	
	std::optional<std::string> get_email_address(const Person& p)
	{
		if (p.has_email())
			return "hello_world@gmail.com";
	
		return std::nullopt;
		//return {};
	}
	
	int main()
	{
		Person myperson;
	
		auto opx = get_email_address(myperson);
	
		//if (opx) {}
		if (opx.has_value()) {}
	}
*/

/*
	#include <optional>
	#include <string>
	
	struct Person {
	public:
		bool has_email()const;
		std::string get_email() const;
	};
	
	std::optional<std::string> get_email_address(const Person& p)
	{
		if (p.has_email())
			return "hello_world@gmail.com";
	
		return std::nullopt;
		//return {};
	}
	
	int main()
	{
		Person p;
		if (auto opx = get_email_address(p)) {}								
		// before C++17
	
		if (auto opx = get_email_address(p); opx) {}					
		// C++17

		if (auto opx = get_email_address(p); opx.operator bool()) {}	
		// C++17

		if (auto opx = get_email_address(p); opx.has_value()) {}		
		// C++17 -> if with initializer syntax
	}
*/

/*
	#include <optional>
	
	class Myclass {
	public:
		Myclass(int x)
		{
			std::cout << "Myclass(int) this = " << this << '\n';
		}
	
		~Myclass()
		{
			std::cout << "destuctor this = " << this << '\n';
		}
	};
	
	int main()
	{
		using namespace std;
	
		auto opx = make_optional<Myclass>(45);
		opx.emplace(56);
	
		std::cout << "main continues\n";
		// output ->
		//	Myclass(int) this	= 00BBFB48
		//	destuctor this		= 00BBFB48	
		//			-> opx objects dtor called
		//	Myclass(int) this	= 00BBFB48	
		//			-> new opx object will be created at the same location
		//	main continues
		//	destuctor this		= 00BBFB48
	}
*/

/*
	class Myclass {
	public:
		Myclass(int x)
		{
			std::cout << "Myclass(int) this = " << this << '\n';
		}
	
		~Myclass()
		{
			std::cout << "destuctor this = " << this << '\n';
		}
	};
	
	int main()
	{
		using namespace std;
	
		auto opx = make_optional<Myclass>(45);
	
		opx = Myclass{ 3456 };
		std::cout << "main continues\n";
		// output ->
		//	Myclass(int) this = 004FFD3C	
		//			-> Myclass object in opx
		//	Myclass(int) this = 004FFD3B	
		//			-> temp object will be created to assign opx
		//	destuctor this = 004FFD3B		
		//			-> temp object destroyed
		//  main continues
		//	destuctor this = 004FFD3C		
		//			-> Myclass object in opx is destroyed
	}

	// difference between emplace() and operator=() 
	// emplace() will destroy the object in opx first then 
	// create another object in the same place
	// operator=() directly assign object that is created before 
	// did not destroy before assign
*/

/*
	#include <optional>
	#include <string>
	
	std::optional<int> to_int(const std::string& str)
	{
		try{
			return std::stoi(str);
			// stoi() throws an exception if it can not convert string to int
		}
		catch (...){
			return std::nullopt;
		}
	}
	
	std::optional<int> to_int2(const std::string& str)
	{
		std::optional<int> ret;
		try {
			ret = std::stoi(str);
		}
		catch(...) {}
	
		return ret;
	}
	
	int main()
	{
		for (auto str : { "42", "077", "hello", "0x33" }) {
			std::optional<int> op = to_int(str);
			if (op) {
				std::cout << str << " converted to int.. value : " << *op << '\n';
			}
			else
				std::cout << "(" << str << ") can not be converted to int\n";
		}
		// output ->
		//	42 converted to int..value : 42
		//	077 converted to int..value : 77
		//	(hello)can not be converted to int
		//	0x33 converted to int..value : 0
	}
*/

/*
	#include <optional>
	#include <string>
	
	class UserRecord {
	public:
		UserRecord(	const std::string& name, 
								std::optional<std::string> nick, 
								std::optional<int> age) :
			m_name{ name }, m_nick{ nick }, m_age{ age } {}
	
		friend std::ostream& operator<<(std::ostream& stream, 
																		const UserRecord& user);
	private:
		std::string m_name;
		std::optional<std::string> m_nick;
		std::optional<int> m_age;
	};
	
	std::ostream& operator<<(std::ostream& os, const UserRecord& user)
	{
		os << user.m_name << ' ';
	
		if (user.m_nick)
			os << *user.m_nick << ' ';
	
		if (user.m_age)
			os << *user.m_age << " years old.";
	
		return os;
	}
	
	int main()
	{
		UserRecord ur1{ "Hello world", "ey" , 20 };
		UserRecord ur2{ "Hello galaxy", std::nullopt , std::nullopt };
	
		std::cout << ur1 << '\n';	// output -> Hello world ey 20 years old.
		std::cout << ur2 << '\n';	// output -> Hello galaxy
	}
*/

/*
	#include <optional>
	
	int main()
	{
		// operator=() function
		using namespace std;
	
		optional x = 3.5;
	
		x = 5.6;
		x.value() = 3.4;
		*x = 7.8;
		// Those 3 lines are same
	
		x = nullopt;
		x = {};
	
		x = 56;	// int can convert to double
	
		optional i = 57;
		x = i;
	}
*/

/*
	#include <optional>
	#include <limits>
	
	int main()
	{
		// comparison functions
		using namespace std;
	
		optional<int> x = 88;
		optional<int> y = 981;
	
		cout << boolalpha;
		cout << (x < y) << '\n';		// output -> true
		cout << (x == y) << '\n';		// output -> false
		cout << (x != y) << '\n';		// output -> true
	
		optional int_min = numeric_limits<int>::min();
		// x_min has the smallest value that an int can have
		optional<int> i;
	
		cout << (i < int_min) << '\n';				// output -> true
		cout << (nullopt < int_min) << '\n';	// output -> true
	}
*/

/*
	#include <optional>
	
	int main()
	{
		using namespace std;
	
		optional<bool> b1{ true };
		optional<bool> b2{ false };
		optional<bool> b3{ true };
		optional<bool> b4;	// nullopt
	
		cout << boolalpha;
		cout << "b1 == b2 : " << (b1 == b2) << '\n';	// output -> b1 == b2 : false
		cout << "b1 == b3 : " << (b1 == b3) << '\n';	// output -> b1 == b3 : true
	
	
		cout << "b1 < b2 : " << (b1 < b2) << '\n';		// output -> b1 < b2 : false
		cout << "b1 > b2 : " << (b1 > b2) << '\n';		// output -> b1 > b2 : true
	
		cout << "b4 < b1 : " << (b4 < b1) << '\n';		// output -> b4 < b1 : true
		cout << "b4 < b2 : " << (b4 < b2) << '\n';		// output -> b4 < b2 : true
		cout << "b4 == b1 : " << (b4 == b2) << '\n';	// output -> b4 < b2 : false
		cout << "b4 == b2 : " << (b4 == b2) << '\n';	// output -> b4 < b2 : false
	}
*/

/*
	----------------
	| std::variant |
	----------------
*/

/*
	// type-safe union
	// variadic class template
*/

/*
	#include <variant>
	#include <string>
	
	int main()
	{
		using namespace std;
	
		variant<int, char, double, string> vx;
		// in T time, variant's value can be
		// int or char or double or std::string
		// these type are variants alternatives
	}
*/

/*
	#include <variant>
	#include <string>
	
	int main()
	{
		using namespace std;
	
		// in x64 system
	
		std::cout << "sizeof(int) = " << sizeof(int) << '\n';
		std::cout << "sizeof(double) = " << sizeof(double) << '\n';
		std::cout << "sizeof(std::string) = " << sizeof(std::string) << '\n';
		// output ->
		//	sizeof(int) = 4
		//	sizeof(double) = 8
		//	sizeof(std::string) = 40
	
	
		using vtype = variant<int, int>;
		std::cout << "sizeof(vtype) = " << sizeof(vtype) << '\n';
		// output -> sizeof(vtype) = 8
	
		// normally it will hold only 4 byte(int)
		// but there is an overhead in implementation to know
		// variant that which alternative it is holding
		// in this scenerio it is 4 byte
		// sizeof(overhead) = sizeof(vtype) - sizeof(int)
	
		using vtype2 = variant<int, double>;
		std::cout << "sizeof(vtype2) = " << sizeof(vtype2) << '\n';
		// output -> sizeof(vtype2) = 16
		// sizeof(overhead) = sizeof(vtype2) - sizeof(double)
	
		using vtype3 = variant<int, double, string>;
		std::cout << "sizeof(vtype3) = " << sizeof(vtype3) << '\n';
		// output -> sizeof(vtype3) = 48
		// sizeof(overhead) = sizeof(vtype3) - sizeof(std::string)
	}
*/

/*
	#include <variant>
	
	struct Buf {
		char buff[1024]{};
	};
	
	int main()
	{
		using namespace std;
	
		std::cout << "sizeof(Buf) = " << sizeof(Buf) << '\n';
		// output -> sizeof(Buf) = 1024
	
		using vtpe = variant<int, double, Buf>;
		std::cout << "sizeof(vtpe) = " << sizeof(vtpe) << '\n';
		// output -> sizeof(vtpe) = 1032
	
		// it is guaranteed that the object that variant holds
		// will always be inside of variant object
	}
*/

/*
	#include <variant>
	#include <string>
	
	int main()
	{
		using namespace std;
	
		variant<int, double, string> vx;
		// if we default initialize variant object
		// it will hold the first alternative
		// in this scenerio -> (int)
	
		// default initialization of variant object will
		// value initialize the first alternative
		// if it is std::string, length of std::string object will be 0
		// if it is int, it will have a value of 0
	}
*/

/*
	#include <variant>
	#include <string>
	
	class NoDefaultCtor {
	public:
		NoDefaultCtor(int);
	};
	
	int main()
	{
		using namespace std;
	
		variant<NoDefaultCtor, double, string> vx;	// syntax error
		// E0291 ->	no default constructor exists for class
		// "std::variant<NoDefaultCtor, double, std::string>"

		variant<double, NoDefaultCtor, int> vy;		// valid 
		// because of the first altrernatives default ctor will be called 
		// when variant is default initialized. There is no syntax error.
	}
*/

/*
	#include <variant>
	#include <string>
	
	int main()
	{
		using namespace std;
	
		variant<int, double, string> vx;
	
		int x = vx;	// syntax error
		// no implicit conversion from variant type to variant's alternatives type
	
		// E0413 ->no suitable conversion function from
		// "std::variant<int, double, std::string>" to "int" exists
	}
*/

/*
	#include <variant>
	#include <string>
	
	int main()
	{
		using namespace std;
	
		variant<int, double, string> vx;
	
		int x = vx;											// syntax error
		int y = static_cast<int>(vx);		// syntax error
		// no implicit or explicit conversion from
		// variant type to variant's alternatives type
	
		// E0413 ->no suitable conversion function from
		// "std::variant<int, double, std::string>" to "int" exists
	}
*/

/*
	#include <variant>
	#include <string>
	
	// to learn which alternative that variant holds
	
	int main()
	{
		using namespace std;
	
		variant<int, double, string> vx;
		cout << "vx.index() = " << vx.index() << '\n';
		// output -> vx.index() = 0
		// holds int and (int)'s index is 0
	
	
		variant<int, double, string> vy(3.5);
		cout << "vy.index() = " << vy.index() << '\n';
		// output -> vy.index() = 1
		// holds double and (double)'s index is 1
	
	
		variant<int, double, string> vz("hello world");
		cout << "vz.index() = " << vz.index() << '\n';
		// output -> vz.index() = 2
	}
*/

/*
	#include <variant>
	#include <string>
	
	int main()
	{
		using namespace std;
	
		variant<int, double, string> vx("hello world");
		cout << "vx.index() = " << vx.index() << '\n';
		// output -> vz.index() = 2
	
		vx = 12;
		cout << "vx.index() = " << vx.index() << '\n';
		// output -> vx.index() = 0
	
		vx = 5.4;
		cout << "vx.index() = " << vx.index() << '\n';
		// output -> vx.index() = 1
	}
*/

/*
	#include <variant>
	#include <string>
	
	int main()
	{
		using namespace std;
	
		variant<int, double, string> vx(4.5);
		cout << "vx.index() = " << vx.index() << '\n';
		// output -> vx.index() = 1
	
		variant<int, double, string> vy(4u);	// syntax error
		// ambiguity -> both int and double are viable
	}
*/

/*
	#include <variant>
	#include <string>

	int main()
	{
		using namespace std;

		//variant<int, float, string> vx(3.4);	// syntax error
		// conversion from double -> float
		// conversion from double -> int

		variant<int, float, string> vy(in_place_index<1>, 3.4);
		// will use [1 -> float] index


		variant<int, const char*, string> vz("hello world");
		// normally alternative will be [const char*]
		std::cout << "vz.index() = " << vz.index() << '\n';
		// output -> vz.index() = 1


		// how to start with std::string

		variant<int, const char*, string> vz_way1("hello world"s);
		// using string literal
		std::cout << "vz_way1.index() = " << vz_way1.index() << '\n';
		// output -> vz_way1.index() = 2

		variant<int, const char*, string> vz_way2(in_place_index<2>, "hello world");
		// using tag -> in_place_index<>
		std::cout << "vz_way2.index() = " << vz_way2.index() << '\n';
		// output -> vz_way2.index() = 2

		variant<int, const char*, string> vz_way3(in_place_type<string>, "hello world");
		// using type tag -> in_place_type<>
		std::cout << "vz_way3.index() = " << vz_way3.index() << '\n';
		// output -> vz_way3.index() = 2
	}
*/

/*
	#include <variant>
	#include <string>
	
	class Date {
	public:
		Date(int x , int y , int z) : m_x{ x }, m_y{ y }, m_z{ z } {}
	
		friend std::ostream& operator<<(std::ostream& os, const Date& dt)
		{
			return os << "[" << dt.m_x << '-' << dt.m_y << '-' << dt.m_z << "]";
		}
	private:
		int m_x, m_y, m_z;
	};
	
	int main()
	{
		using namespace std;
	
		variant<int, Date, string> v1(Date{ 2, 5, 1987 });				// valid
	
		// variant<int, Date, string> v2( 2, 5, 1987 );						// syntax error
		variant<int, Date, string> v2(in_place_index<1>, 2, 5, 1987 );	// valid
	
		cout << get<1>(v2) << '\n';	// returns a reference
		// output -> [2-5-1987]
	}
*/

/*
	#include <variant>
	#include <string>
	
	int main()
	{
		using namespace std;
	
		variant<int, double, string> vx{ "hello world" };
	
		std::cout << "vx.index() = " << vx.index() << '\n';
		// output -> vx.index() = 2
	
		try
		{
			auto val = get<0>(vx);
			auto val = get<int>(vx);
			// using non-active alternatives index in get<>
			// output -> Exception caught: bad variant access
		}
		catch (const std::exception& ex)
		{
			std::cout << "Exception caught: " << ex.what() << '\n';
		}
	}
*/

/*
	#include <variant>
	#include <string>
	
	int main()
	{
		using namespace std;
	
		variant<int, double, string> vx{ "hello world" };
	
		std::cout << "vx.index() = " << vx.index() << '\n';
		// output -> vx.index() = 2
	
		auto val = get<char>(vx);	// compile time error
		// not a valid alternative
		// C2338 static_assert failed: 'get<T>(variant<Types...>&) 
		//	requires T to occur exactly once in Types.
	}
*/

/*
	#include <variant>
	#include <string>
	
	int main()
	{
		using namespace std;
	
		variant<int, double, string> vx{ "hello world" };
	
		std::cout << "vx.index() = " << vx.index() << '\n';
		// output -> vx.index() = 2
	
	
		auto val = get<4>(vx);	// will be a compile time error
		// C2338 static_assert failed: 'variant index out of bounds'
	}
*/

/*
	#include <variant>
	#include <string>
	
	int main()
	{
		using namespace std;
	
		variant<int, double, string> vx{ "hello world" };
	
		get<2>(vx) += " and galaxy";
		// get<> returns reference
	
		cout << get<string>(vx) << '\n';
		// output -> hello world and galaxy
	}
*/

/*
	#include <variant>
	#include <string>

	int main()
	{
		using namespace std;

		//-------------------------------
		// TESTING ALTERNATIVE TYPE WAY 1
		//-------------------------------

		variant<int, double, string> vx{ "hello world" };

		auto ptr = get_if<double>(&vx);
		// if alternative is double ptr's type will be double*
		// else it will be nullptr

		if (auto pk = get_if<int>(&vx))
			cout << "holding int: " << *pk << '\n';
		else if (auto pl = get_if<double>(&vx))
			cout << "holding double: " << *pl << '\n';
		else if (auto pm = get_if<string>(&vx))
			cout << "holding string: " << *pm << '\n';
		// output -> holding string: hello world

		//-------------------------------
		// TESTING ALTERNATIVE TYPE WAY 2
		//-------------------------------

		vx = 12;

		if (vx.index() == 0)
			cout << "holding int: " << get<0>(vx) << '\n';
		else if (vx.index() == 1)
			cout << "holding double: " << get<1>(vx) << '\n';
		else if (vx.index() == 2)
			cout << "holding string: " << get<2>(vx) << '\n';
		// output -> holding int: 12

		//-------------------------------
		// TESTING ALTERNATIVE TYPE WAY 3
		//-------------------------------

		vx = 5.6;

		if (holds_alternative<int>(vx))
			cout << "holding int: " << get<int>(vx) << '\n';
		else if (holds_alternative<double>(vx))
			cout << "holding double: " << get<double>(vx) << '\n';
		else if (holds_alternative<string>(vx))
			cout << "holding string: " << get<string>(vx) << '\n';
		// output -> holding double: 5.6
	}
*/

/*
	#include <variant>
	#include <string>
	
	int main()
	{
		using namespace std;
	
		variant<int, double, string> vx{ "hello world" };
		variant<int, double, string> vy{ "hello universe" };
	
		get<2>(vx) = "changed to different string";
	
		vx = 3.4;
		vx = "hello galaxy";
		vx = 75;
	
		cout << "vx.index() = " << vx.index() << '\n';
		// output -> vx.index() = 0
	
		vx = vy;
		cout << "vx.index() = " << vx.index() << '\n';
		// output -> vx.index() = 2
	
		vx.emplace<double>(3.4);
		cout << "vx.index() = " << vx.index() << '\n';
		// output -> vx.index() = 1
	}
*/

/*
	template <class Visitor, class... Variants>
	constexpr visit(Visitor&& vis, Variants&&... vars);
*/

/*
	#include <variant>
	#include <string>
	
	struct Visitor {
		void operator()(int x)const
		{
			std::cout << "int : (" << x << ")\n";
		}
		void operator()(double x)const
		{
			std::cout << "double : [" << x << "]\n";
		}
		void operator()(const std::string& x)const
		{
			std::cout << "string : \"" << x << "\"\n";
		}
	};
	
	int main()
	{
		using namespace std;
	
		variant<int, double, string> vx{ "hello world" };
	
		// using visitor design pattern visit() -> variadic function template
	
		visit(Visitor{}, vx);
		// output -> string : "hello world"
	
		vx = 4.57;
		visit(Visitor{}, vx);
		// output -> double : [4.57]
	
		vx = 4653;
		visit(Visitor{}, vx);
		// output -> int : (4653)
	}
*/

/*
	#include <variant>
	#include <string>
	
	struct Visitor {
		template <typename T>
		void operator()(T x)const
		{
			std::cout << x << '\n';
		}
	};
	
	int main()
	{
		using namespace std;
	
		variant<int, double, string> vx{ "hello world" };
	
		visit(Visitor{}, vx);
		// output -> hello world
	
		vx = 4.57;
		visit(Visitor{}, vx);
		// output -> 4.57
	
		vx = 4653;
		visit(Visitor{}, vx);
		// output -> 4653
	
		// we can use function Template in operator() function
		// but function needs to be same for all alternatives.
	}
*/

/*
	#include <variant>
	#include <string>
	
	struct Visitor {
		// abbreviated template syntax C++20
		void operator()(auto x)const
		{
			std::cout << x << '\n';
		}
	};
	
	int main()
	{
		using namespace std;
	
		variant<int, double, string> vx{ "hello world" };
	
		visit(Visitor{}, vx);
		// output -> hello world
	
		vx = 4.57;
		visit(Visitor{}, vx);
		// output -> 4.57
	
		vx = 4653;
		visit(Visitor{}, vx);
		// output -> 4653
	}
*/

/*
	#include <variant>
	#include <string>
	
	int main()
	{
		using namespace std;
	
		variant<int, double, string> vx{ "hello world" };
	
		auto fn = [](const auto& x) { cout << "[" << x << "]\n"; };
	
		visit(fn, vx);
		// output -> [hello world]
	
		vx = 4.57;
		visit(fn, vx);
		// output -> [4.57]
	
		vx = 4653;
		visit(fn, vx);
		// output -> [4653]
	
	
		visit([](const auto& y) {std::cout << "(" << y << ")\n";}, vx);
		// output -> (4653)
	}
*/

/*
	#include <variant>
	#include <string>
	
	int main()
	{
		using namespace std;
	
		variant<int, double, string> vx;
	
		auto print_visitor = [](const auto& x) {
			std::cout << "[" << x << "]\n"; };
	
		auto triple_visitor = [](auto& x) {
			x = x + x + x; };
	
	
		vx = "hello";
		visit(print_visitor, vx);
		// output -> [hello]
		visit(triple_visitor, vx);
		visit(print_visitor, vx);
		// output -> [hellohellohello]
	
		vx = 30;
		visit(print_visitor, vx);
		// output -> [30]
		visit(triple_visitor, vx);
		visit(print_visitor, vx);
		// output -> [90]
	
		vx = 3.333;
		visit(print_visitor, vx);
		// output -> [3.333]
		visit(triple_visitor, vx);
		visit(print_visitor, vx);
		// output -> [9.999]
	}
*/

/*
	#include <variant>
	#include <bitset>
	#include <string>
	#include <type_traits>
	
	class PrintVisitor {
	public:
		template <typename T>
		void operator()(const T& x)
		{
			if constexpr (std::is_same_v<double, T>)
				std::cout << "implementation for double\n";
			else
				std::cout << "implementation for other alternatives\n";
		}
	};
	
	int main()
	{
		using namespace std;
	
		variant<int, double, string, bitset<32>> vx{ 23 };
	
		visit(PrintVisitor{}, vx);
		// output -> implementation for other alternatives
	
		vx = 3.567;
		visit(PrintVisitor{}, vx);
		// output -> implementation for double
	
		vx = "hello world";
		visit(PrintVisitor{}, vx);
		// output -> implementation for other alternatives
	
		vx = bitset<32>{ 748372 };
		visit(PrintVisitor{}, vx);
		// output -> implementation for other alternatives
	}
*/

/*
	#include <variant>
	#include <bitset>
	#include <string>
	#include <type_traits>
	#include <vector>
	#include <iomanip>
	
	int main()
	{
		using namespace std;
	
		using vtype = variant<int, double, string>;
		vector<vtype> vec{ 199, 3.15263, "hello world", "Universe" };
	
		// vector[0] holds variant<int, double,string>{199}
		// vector[1] holds variant<int, double,string>{3.15263}
		// vector[2] holds variant<int, double,string>{"hello world"}
		// vector[3] holds variant<int, double,string>{"Universe"}
	
		for (const vtype& val : vec){
			std::visit([](const auto& v) {
				if constexpr (std::is_same_v<decltype(v), const std::string&>)
					std::cout << "variant holds string: " << quoted(v) << '\n';
				else
					std::cout << "variant is not holding string, holds: " << v << '\n';
			}, val);
		}
		// output ->
		//	variant is not holding string, holds: 199
		//	variant is not holding string, holds : 3.15263
		//	variant holds string : "hello world"
		//	variant holds string : "Universe"
	}
*/

/*
	#include <variant>
	#include <string>
	
	// variant can have same type alternatives
	int main()
	{
		using namespace std;
	
		using nick = string;
		using name = string;
		using id = int;
	
		variant<nick, id, name> vx1(in_place_index<0>, "myNick");
		variant<nick, id, name> vx2(in_place_index<2>, "myName");
	
		vx1.emplace<0>("yourNick");
	}
*/

/*
	#include <variant>
	#include <string>
	
	enum { nick_idx, id_idx, name_idx };
	
	int main()
	{
		using namespace std;
	
		using nick = string;
		using name = string;
		using id = int;
	
		variant<nick, id, name> vx1(in_place_index<nick_idx>, "myNick");
		variant<nick, id, name> vx2(in_place_index<name_idx>, "myName");
	
		vx1.emplace<0>("yourNick");
	}
*/

/*
	#include <variant>
	#include <bitset>
	#include <string>

	struct Myvisitor {

		void operator()(const auto& x, const auto& y)
		{
			std::cout << "(" << x << ") [" << y << "]\n";
		}
	};

	int main()
	{
		using namespace std;

		variant<int, string, long> vx{ "hello world" };
		variant<char, double, bitset<16>> vy{ bitset<16>{12756u } };

		visit(Myvisitor{}, vx, vy);
		// output -> (hello world) [0011000111010100]

		vx = 18;
		vy = 'A';
		visit(Myvisitor{}, vx, vy);
		// output -> (18) [A]
	}
*/

/*
	#include <variant>
	#include <bitset>
	#include <string>
	#include <type_traits>
	
	struct Myvisitor {
	
		template <typename T, typename U>
		void operator()(const T& x, const U& y)
		{
			if constexpr (std::is_same_v<T, std::string> && 
										std::is_same_v<U, std::bitset<16>>)
				std::cout << "string - bitset\n";
			else if constexpr (	std::is_same_v<T, int> && 
													std::is_same_v<U, double>)
				std::cout << "int - double\n";
			else
				std::cout << "other combinations\n";
		}
	};
	
	int main()
	{
		using namespace std;
	
		variant<int, string, long> vx{ "hello world" };
		variant<char, double, bitset<16>> vy{ bitset<16>{12756u } };
	
		visit(Myvisitor{}, vx, vy);
		// output -> string - bitset
	
		vx = 18;
		vy = 2.5;
		visit(Myvisitor{}, vx, vy);
		// output -> int - double
	
		vx = 18;
		vy = 'B';
		visit(Myvisitor{}, vx, vy);
		// output -> other combinations
	}
*/

/*
	--------------------
	| overloader idiom |
	--------------------
	https://www.youtube.com/watch?v=6iRUTKKclmM&t=1468s
*/

/*
	template <typename ...Args>
	struct Der : Args ... {
		using Args::foo...;
	};
	
	struct A {
		void foo(int)
		{
			std::cout << "A::foo(int)\n";
		}
	};
	
	struct B {
		void foo(double)
		{
			std::cout << "B::foo(double)\n";
		}
	};
	
	struct C {
		void foo(long)
		{
			std::cout << "C::foo(long)\n";
		}
	};
	
	int main()
	{
		Der<A, B, C> myder;
	
		myder.foo(12);
		myder.foo(3.4);
		myder.foo(587L);
		// without "using" declaration these function calls are ambigious
		// when we add "using" declaration of foo functions 
		// in derived class template, functions will be added to 
		// derived classes interface so, they will become overloads 
		// in derived classes interface
	
		// output ->
		//	A::foo(int)
		//	B::foo(double)
		//	C::foo(long)
	}
*/

/*
	auto fn1 = [](int x) {return x * x; };
	auto fn2 = [](int x) {return x + x; };
	auto fn3 = [](int x) {return x - x; };
	
	struct Der : decltype(fn1), decltype(fn2), decltype(fn3){
	
	};
	
	int main()
	{
	
	}
*/

/*
	#include <variant>
	#include <vector>
	
	template <typename... Args>
	struct Overload : Args ...
	{
		using Args::operator() ...;
	};
	
	// deduction guide
	template <class... Args>
	Overload(Args...)->Overload<Args...>;
	
	struct StructA {};
	struct StructB {};
	
	int main()
	{
		using var_type = std::variant<int, char, unsigned, 
																	float, double, long long, StructA, StructB>;
	
		auto stypes = Overload{
			[](int) {return "int"; },
			[](char) {return "char"; },
			[](unsigned) {return "unsigned"; },
			[](float) {return "float"; },
			[](double) {return "double"; },
			[](long long) {return "long long"; },
			[](StructA) {return "StructA"; },
			[](auto) {return "unknown type"; },
		};
		// Overload is an aggregate type
	
		std::vector<var_type> varvec{ 23, 'A', 45U, 5.f, 34LL, 
																	StructA{}, StructB{} };
	
		for (auto v : varvec) {
			std::cout << std::visit(stypes, v) << '\n';
		}
		// output ->
		//	int
		//	char
		//	unsigned
		//	float
		//	long long
		//	StructA
		//	unknown type
	}
*/

/*
	----------------------
	| mono state pattern |
	----------------------
*/

/*
	class Myclass {
	public:
		static void foo();
		static void bar();
		static void baz();
	
		// no non-static data member 
		// no non-static member function
		// can be static data member
	};
	
	
	int main()
	{
		Myclass m1;
		Myclass m2;
		Myclass m3;
		// all objects created from Myclass will become same state(mono state)
	}
*/

/*
	#include <variant>
	
	int main()
	{
		std::monostate x, y;
	
		std::cout << (x == y) << '\n';	// output -> 1
		// always returns true
	}
*/

/*
	#include <variant>
	
	struct A {
		A(int);
	};
	
	int main()
	{
		using namespace std;
	
		variant<A, int, double> vx;	// syntax error
		// first alternative needs to be default constructible
		// when we default initialize variant
	
		// what if no alternative have default constructor?
		variant<monostate, int, A, double> vy;
	}
*/

/*
	#include <variant>
	
	struct A {
		A(int);
	};
	
	int main()
	{
		using namespace std;
	
		variant<monostate, A, int, double> vx;
	
		if (vx.index() == 0) 
			std::cout << "variant is empty\n";
		
		if (!vx.index()) 
			std::cout << "variant is empty\n";
		
		if (holds_alternative<monostate>(vx)) 
			std::cout << "variant is empty\n";
		
		if(get_if<monostate>(&vx))
			std::cout << "variant is empty\n";

		// output ->
		//	variant is empty
		//	variant is empty
		//	variant is empty
		//	variant is empty
	}
*/

/*
	#include <variant>
	#include <string>
	
	int main()
	{
		using namespace std;
	
		variant<bool, string> vx{ "hello world" };
		// const char* to bool			-> standart conversion
		// const char* to std::string	-> user defined conversion
	
		// C++17 standart -> bool will be choosen as an alternative
		cout << "vx.index() = " << vx.index() << '\n';
		// output ->  vx.index() = 0
	
		// C++20 and later ->
		cout << "vx.index() = " << vx.index() << '\n';
		// output ->  vx.index() = 1
	
		// We can solve that problem with
		variant<bool, string> vy{ in_place_index<1>, "hello world" };
		variant<bool, string> vz{ in_place_type<string>, "hello world" };
		variant<bool, string> vz{"hello world"s };
	}
*/

/*
	------------------------
	| variant polymorphism |
	------------------------
*/

/*
	#include <variant>
	#include <algorithm>
	#include <list>
	#include <string>
	
	class Cat {
	public:
		Cat(std::string name) : m_name{std::move(name)} {}
		void meow() const
		{
			std::cout << m_name << " meows!\n";
		}
	private:
		std::string m_name;
	};
	
	class Dog {
	public:
		Dog(std::string name) : m_name{ std::move(name) } {}
		void woof() const
		{
			std::cout << m_name << " woofs!\n";
		}
	private:
		std::string m_name;
	};
	
	class Lamb {
	public:
		Lamb(std::string name) : m_name{ std::move(name) } {}
		void bleat() const
		{
			std::cout << m_name << " beeeas!\n";
		}
	private:
		std::string m_name;
	};
	
	using Animal = std::variant<Dog, Cat, Lamb>;
	
	template <typename T>
	bool is_type(const Animal& a)
	{
		return std::holds_alternative<T>(a);
	}
	
	struct AnimalVoice
	{
		void operator()(const Dog& dog) const { dog.woof(); }
		void operator()(const Cat& cat) const { cat.meow(); }
		void operator()(const Lamb& lamb) const { lamb.bleat(); }
	};
	
	
	int main()
	{
		using namespace std;
	
		list<Animal> animal_farm{ Cat{"pamuk"}, Dog{"kont"}, 
															Lamb{"kuzucuk"}, Lamb{"pamuk"}, Cat{"kara"} };
	
		for (const Animal& a : animal_farm) {
			switch (a.index()) {
			case 0:
				get<Dog>(a).woof();
				break;
			case 1:
				get<Cat>(a).meow();
				break;
			case 2:
				get<Lamb>(a).bleat();
				break;
			}
		}
	
		// output ->
		//	pamuk meows!
		//	kont woofs!
		//	kuzucuk beeeas!
		//	pamuk beeeas!
		//	kara meows!
	
		cout << "--------------------\n";
	
		for (const Animal& a : animal_farm) {
			if (const auto dog_ptr = get_if<Dog>(&a))
				dog_ptr->woof();
			else if (const auto cat_ptr = get_if<Cat>(&a))
				cat_ptr->meow();
			else if (const auto lamb_ptr = get_if<Lamb>(&a))
				lamb_ptr->bleat();
		}
	
		// output ->
		//	pamuk meows!
		//	kont woofs!
		//	kuzucuk beeeas!
		//	pamuk beeeas!
		//	kara meows!
	
		cout << "--------------------\n";
	
		for (const Animal& a : animal_farm) {
			visit(AnimalVoice{}, a);
		}
	
		// output ->
		//	pamuk meows!
		//	kont woofs!
		//	kuzucuk beeeas!
		//	pamuk beeeas!
		//	kara meows!
	
		cout << "--------------------\n";
	
		cout << "In animal farm "
			<< count_if(begin(animal_farm), 
									end(animal_farm), 
									is_type<Cat>) << " cat, "
			<< count_if(begin(animal_farm), 
									end(animal_farm), 
									is_type<Dog>) << " dog and "
			<< count_if(begin(animal_farm), 
									end(animal_farm), 
									is_type<Lamb>) << " lamb are living.\n";
	
		// output -> In animal farm 2 cat, 1 dog and 2 lamb are living.
	}
*/

/*
	------------------------------------------
	| valueless_by_exception member function |
	------------------------------------------
*/

/*
	#include <variant>
	
	struct S {
		operator int()const
		{
			throw std::runtime_error{ "ERROR from S.operator int()" };
			return 1;
		}	// any conversion to int throws
	};
	
	int main()
	{
		using namespace std;
	
		variant<double, int> var{ 12.2 };
	
		try
		{
			var.emplace<1>(S{});
			// S object will throw an exception 
			// when it tries to convert itself to an int
		}
		catch (const std::exception& ex)
		{
			cout << "error has been caught... " << ex.what() << '\n';
			// output -> error has been caught... ERROR from S.operator int()
	
			cout << boolalpha << var.valueless_by_exception() << '\n';
			// output -> true
	
			cout << "var.index() = " << var.index() << '\n';
			// output -> var.index() = 18446744073709551615 (biggest value of size_t)
	
			cout << (var.index() == variant_npos) << '\n';
			// output -> true
		}
	}
*/

/*
	----------------------
	| variant comparison |
	----------------------
*/

/*
	#include <variant>
	
	int main()
	{
		using namespace std;
	
		variant<int, double, long> v1{ 12.2 };
		variant<int, double, long> v2{ 456 };
	
		std::cout << "v1.index() = " << v1.index() << '\n';	
		// output -> v1.index() = 1
		std::cout << "v2.index() = " << v2.index() << '\n';	
		// output -> v2.index() = 0
	
		cout << boolalpha;
		cout << "v2 < v1 : " << (v2 < v1) << '\n';
		// output -> v2 < v1 : true
	
		// If variant objects have same alternatives in same order.
		// and when they are holding different alternatives (different indexes)
		// small index will be smaller.
		// v1(index = 1) >  v2(index = 0)
	
		variant<int, double, long> v3{ 457 };
		variant<int, double, long> v4{ 456 };
	
		std::cout << "v3.index() = " << v3.index() << '\n';	
		// output -> v3.index() = 0
		std::cout << "v4.index() = " << v4.index() << '\n';	
		// output -> v4.index() = 0
	
		cout << "v3 < v4 : " << (v3 < v4) << '\n';
		// output -> v3 < v4 : false
	
		// If variant objects have same alternatives in same order.
		// and when they are holding same alternatives (same indexes)
		// the value of the alternative will get considered in comparison
		// v3(457) > v4(456)
	}
*/

/*
	#include <variant>
	
	int main()
	{
		using namespace std;
	
		variant<monostate, int, double, long> v1;
		variant<monostate, int, double, long> v2;
	
		cout << boolalpha;
		cout << "v2 == v1 : " << (v2 == v1) << '\n';
		// output -> v2 == v1 : true
	}
*/

/*
	------------
	| std::any |
	------------
*/

/*
	std::any is a class, not a class template
	std::any object can hold any value
	std::any is holding an object and also wraps
		a type_info object related the object it holds
*/

/*
	#include <any>
	#include <vector>
	#include <string>
	#include <bitset>
	
	int main()
	{
		using namespace std;
	
		any x;
		any y{ 23 };
		any z = "hello world";
		any v = vector<string>{};
	
		any h;
		h = 23;
		h = 4.5;
		h = "hello Universe"s;
		h = bitset<16>{ 7564u };
	}
*/

/*
	#include <any>
	#include <cstdlib>
	
	void* operator new(std::size_t sz)
	{
		std::cout << "operator new called for the size of : " << sz << '\n';
	
		if (sz == 0)
			++sz;
		if (void* ptr = std::malloc(sz))
			return ptr;
	
		throw std::bad_alloc{};
	}
	
	struct Mystruct {
		unsigned char buf[56]{};
	};
	
	struct Yourstruct {
		unsigned char buf[58]{};
	};
	
	int main()
	{
		using namespace std;
	
		std::cout << "sizeof(any) = " << sizeof(any) << '\n';
		// output -> sizeof(any) = 64
		std::cout << "sizeof(Mystruct) = " << sizeof(Mystruct) << '\n';
		// ouput -> sizeof(Mystruct) = 56
		std::cout << "sizeof(Yourstruct) = " << sizeof(Yourstruct) << '\n';
		// ouput -> sizeof(Yourstruct) = 58
	
		any x{ Mystruct{} };
		// no heap allocation
		any y{ Yourstruct{} };
		// output -> operator new called for the size of : 58
	
		// there is a buffer inside std::any object.
	}
*/

/*
	#include <any>
	
	int main()
	{
		using namespace std;
	
		any x;
	
		if (x) {}	// syntax error
		// std::any doesn't have an operator bool() member function
	}
*/

/*
	#include <any>
	
	int main()
	{
		using namespace std;
	
		any x;
		any y{ 10 };
	
		if (x.has_value())
			std::cout << "full\n";
		else
			std::cout << "empty\n";
		// output -> empty
	
	
		if (y.has_value())
			std::cout << "full\n";
		else
			std::cout << "empty\n";
		// output -> full
	}
*/

/*
	#include <any>
	#include <string>
	#include <vector>
	
	int main()
	{
		using namespace std;
	
		any x = 89;
		x.emplace<int>(45);
	
		any a1(in_place_type<string>, 10, 'A');
		any b1 = make_any<string>(10, 'B');
	
		any a2{ in_place_type<vector<int>>, { 3, 5, 6, 9 } };
		any b2 = make_any<vector<int>>({ 4, 6, 7, 10 });
	}
*/

/*
	#include <any>
	#include <string>
	
	int main()
	{
		using namespace std;
	
		any x = 12;
		any y = "hello world";
	
		try{
			auto val1 = any_cast<int>(x);
			std::cout << "val1 = " << val1 << '\n';
			// output -> val1 = 12
	
			auto val2 = any_cast<int>(y);
			std::cout << "val2 = " << val2 << '\n';
			// output -> exception caught: Bad any_cast
		}
		catch (const std::exception& ex)
		{
			std::cout << "exception caught: " << ex.what() << '\n';
		}
	}
*/

/*
	#include <any>

	int main(){
		using namespace std;

		any ax;
		boolalpha(cout);

		cout << "has value? : " << ax.has_value() << '\n';
		// output -> has value? : false
	}
*/

/*
	// any classes type() function returns 
	// const std::type_info& of the type that it holds  

	#include <any>

	int main(){
		using namespace std;

		any ax;
		boolalpha(cout);

		cout << (ax.type() == typeid(void)) << '\n';	
		// output -> true
	}
*/

/*
	#include <any>

	int main(){
		using namespace std;

		any a1 = 56;
		any a2 = 2.3;
		any a3 = "hello"s;

		int ar[5]{};
		any a4 = ar;			// a4 holds int* -> array to pointer conversion
		any a5 = "world";	// a5 holds const char* -> array to pointer conversion

		cout << a1.type().name() << '\n';	// output -> int
		cout << a2.type().name() << '\n';	// output -> double
		cout << a3.type().name() << '\n';	// output -> std::string
		cout << a4.type().name() << '\n';	// output -> int*
		cout << a5.type().name() << '\n';	// output -> const char*
	}
*/

/*
	#include <any>
	#include <set>

	int main(){
		using namespace std;

		any a1(in_place_type<string>, 10, 'A');
		any a2(in_place_type<set<int>>, { 3, 5, 6, 9 });

		// if we are not using directly the expressions type 
		// but the class that it will be generated 
		// we can use in_place_type helper

		// doğrudan ifadenin türü değil de, oluşturulacak sınıfın türünü
		// belirtmek gerekiyorsa in_place_type yardımcısı kullanılabilir.

		auto a = make_any<string>(10, 'B');
		// or we can also use make_any
	}
*/

/*
	#include <any>

	class Date {
		public:
			Date(int x , int y , int z) : m_x{ x }, m_y{ y }, m_z{ z } {}
		
			friend std::ostream& operator<<(std::ostream& os, const Date& dt)
			{
				return os << "[" << dt.m_x << '-' << dt.m_y << '-' << dt.m_z << "]";
			}
		private:
			int m_x, m_y, m_z;
		};


	int main(){
		using namespace std;

		auto a = make_any<Date>(11, 11, 2011);

		cout << any_cast<Date>(a) << '\n';	
		// output -> [11-11-2011]

		cout << any_cast<Date&>(a) << '\n';	
		// output -> [11-11-2011]
		// if we want to reach the object that any object holds 
		// Date& should be used
	} 
*/

/*
	#include <any>
	
	int main()
	{
		using namespace std;
		boolalpha(cout);
	
		any x;
		cout << "has value : " << x.has_value() << '\n';	
		// output -> has value : false
	
		x = "hello world"s;
		cout << "has value : " << x.has_value() << '\n';	
		// output -> has value : true
	
		x.reset();
		cout << "has value : " << x.has_value() << '\n';	
		// output -> has value : false
	
		x = 6.6;
		cout << "has value : " << x.has_value() << '\n';	
		// output -> has value : true
	
		x = any{};
		cout << "has value : " << x.has_value() << '\n';	
		// output -> has value : false
	
		x = 9L;
		cout << "has value : " << x.has_value() << '\n';	
		// output -> has value : true
	
		x = {};
		cout << "has value : " << x.has_value() << '\n';	
		// output -> has value : false
	}
*/

/*
	#include <any>
	
	class Date {
	public:
		Date(int x, int y, int z) : m_x{ x }, m_y{ y }, m_z{ z } {}
	
		~Date()
		{
			std::cout << "~Date() has been called\n";
		}
	
		friend std::ostream& operator<<(std::ostream& os, const Date& dt)
		{
			return os << "[" << dt.m_x << '-' << dt.m_y << '-' << dt.m_z << "]";
		}
	private:
		int m_x, m_y, m_z;
	};
	
	int main()
	{
		using namespace std;
	
		Date dx{ 25, 11, 2023 };
		any x(dx);
	
		x.emplace<Date>(dx);
		// emplace function will destroy the object that "any" object holds
		// then it will create a new object
	
		// output ->
		//	~Date() has been called
		//	~Date() has been called
		//  ~Date() has been called
	}
*/

/*
	#include <any>
	
	int main()
	{
		using namespace std;
	
		any a{ "Kaya"s };

		auto& ra = std::any_cast<std::string&>(a);
		// we have a reference to the object that "any" object holds

		std::cout << std::any_cast<const string&>(a) << '\n';
		// output -> Kaya

		ra[0] = 'M';
		std::cout << std::any_cast<const string&>(a) << '\n';
		// output -> Maya

		auto str = any_cast<string&&>(move(a));
		// the type that any_cast expression generate is R value
		// so move constructor has been called for str object
		// "str" object steals the content of "a" object

		std::cout << "a.size() = " << any_cast<string>(&a)->size() << '\n'; 
		// output -> a.size() = 0

		cout << "str = " << str << '\n';
		// output -> str = Maya
	}
*/

/*
	#include <vector>
	#include <any>

		class Date {
		public:
			Date(int x, int y, int z) : m_x{ x }, m_y{ y }, m_z{ z } {}
		
			friend std::ostream& operator<<(std::ostream& os, const Date& dt)
			{
				return os << "[" << dt.m_x << '-' << dt.m_y << '-' << dt.m_z << "]";
			}
		private:
			int m_x, m_y, m_z;
		};

	int main(){
		using namespace std;

		vector<any> avec;

		avec.push_back(12);
		avec.push_back(3.4);
		avec.push_back("hello"s);
		avec.push_back(Date{ 25, 11, 2023 });
		avec.push_back(34.5);
		avec.push_back(999);
		avec.push_back(Date{ 31, 12, 2023 });

		for (const auto& a : avec){
			if (auto p = any_cast<int>(&a))
				cout << "int : " << *p << '\n';
			else if (auto p = any_cast<double>(&a))
				cout << "double : " << *p << '\n';
			else if (auto p = any_cast<Date>(&a))
				cout << "Date : " << *p << '\n';
			else
				cout << "unknown type\n";
		}

		// output -> 
		//	int : 12
		//	double : 3.4
		//	unknown type
		//	Date : [25-11-2023]
		//	double : 34.5
		//	int : 999
		//	Date : [31-12-2023]

		// void* is not holding type information
		// "any" can be used like void*, 
		// and "any" also knows the type information
		// because it is holding a type_info object inside itself
	}
*/

/*
	#include <utility>
	#include <any>
	#include <vector>

	using vpair = std::pair<std::string, std::any>;

	int main(){
		using namespace std;

		vector<vpair> avec;
		
		avec.push_back({ "int" , 12 });
		avec.push_back({ "double" , 2.3 });
		avec.push_back({ "string" , "hello"s });
		avec.push_back({ "char" , 'A' });
		// ...
	}
*/

/*
	#include <any>

	struct Base{};
	struct Der : Base{};

	int main(){
		using namespace std;

		any a = Der();

		if (Base* base_ptr = std::any_cast<Base>(&a))
			cout << "Correct type\n";
		else
			cout << "Incorrect type\n";

		// output -> Incorrect type

		// derived class object is also a base class object logic
		// 	is not working in this scenario
		// Base objects type_info object is not same with 
		// 	Der objects type_info object
	}
*/