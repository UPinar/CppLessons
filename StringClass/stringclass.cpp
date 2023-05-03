#include <iostream>
#include <string>

/*
	string class is a container.
	it's data structure is dynamic array.
*/

/*
	template< typename C, typename T = char_traits<C>, typename A = allocator<C>>
	class basic_string{
	};
*/

/*
	int main()
	{
		// using namespace std;
	
		std::basic_string<char, std::char_traits<char>, std::allocator<char>> str{ "Hello" };
		std::basic_string<char> str{ "Hello" };
	
		using String = std::basic_string<char>;
		String str{ "Hello" };
	
		// string is a type alias.
	}
*/

/*
	string objects have 3 pointers and a buffer.
	first pointer points to starting memory of char's in heap
	second pointer points to end memory of chars
	third pointer points to capacity memory

	
				     ---------------------------------
				     | H | E | L | L | O |  |  |  |  |
				     ---------------------------------
				       ^		^	    ^
				       |		|	    |
	-----------		       |		|           |
	| pointer |--------------------			|           |
	-----------				        |	    |
	| pointer |-------------------------------------            |
	-----------                                                 |
	| pointer |-------------------------------------------------
	-----------
	| buffer  |
	-----------
*/

/*
	// x64 release mode
	----------------------
	
	void* operator new(std::size_t sz)
	{
		std::cout << "operator new called for the size of : " << sz << '\n';
	
		if (sz == 0)
			++sz;
	
		if (void* ptr = std::malloc(sz))
			return ptr;
	
		throw std::bad_alloc{};
	}
	
	void operator delete(void* ptr) noexcept
	{
		std::cout << "operator delete called for the address of : " << ptr << '\n';
	}
	
	int main()
	{
		std::string str{ "Hello World" };
		// in release version for a small size string no heap allocation happens
		// output -> ..
	
		std::string str_2{ "Hello World we are live from Istanbul" };
		// because of the string size is longer, needs an heap allocation.
		// output -> operator new called for the size of : 48
		// output -> operator delete called for the address of : 000001B541546EF0
	
		// both string objects are in stack in previous examples.
	
		// string object can also be created in heap
	
		auto ps = new std::string(100, 'A');
		// output -> operator new called for the size of : 32		-> string object(3 pointers and a buffer) in heap
		// output -> operator new called for the size of : 112		-> char's(resource) in heap
		delete ps;
		// operator delete called for the address of : 000001F103CDED70
		// operator delete called for the address of : 000001F103CD57F0
	}
*/

/*
	-------------------------------------------------
	| small string(buffer) optimization - SSO - SBO |
	-------------------------------------------------
	if your string is small enough, you can use a buffer in string class to 
	store it without using heap memory.
*/

/*
	int main()
	{
		std::string str;
	
		str.reserve(100'000);
		// reserve memory allocation for not reallacation happening
	
		for (size_t i = 0; i < 100'000; ++i)
		{
			str.push_back('A');
		}
	}
*/

/*
	str.xyz(const char* p) // Null-Terminated Byte String(NTBS)			// CString param
	str.xyz(const char* p, std::string::size_type)					// data param
	str.xyz(const char* ps, const char* pe)						// range param
	str.xyz(const std::string&)							// std::string param
	str.xyz(std::string&&)								// std::string param
	str.xyz(const std::string&, std::string::size_type)				// sub-string param
	str.xyz(const std::string&, std::string::size_type, std::string::size_type)	// sub-string param
	str.xyz(std::string::size_type, char)						// fill param
	str.xyz(char)									// char param
	str.xyz(std::initializer_list<char>)						// initializer_list param
*/

/*
	// str.xxx(const char* p)

	int main()
	{
		char str[20];
	
		str[0] = 'H';
		str[1] = 'E';
		str[2] = 'Y';
	
		std::string name{ str };
	
		std::cout << str; // undefined behaviour
		// str is not a NTBS(Null Terminated Byte String)
	
	
		std::string name{ "Hello World" };
		// string_literal is static storage duration NTBS and its type is (const char[])
	}
*/

/*
	string::size_type
	size_t
		-> index type
		-> field parameter type
		-> length and capacity type
*/

/*
	int main()
	{
		std::string str;
	
		std::cout << "str.size() = " << str.size() << '\n';		// str.size() = 0
		std::cout << "str.length() = " << str.length() << '\n';		// str.length() = 0
		std::cout << "str.capacity() = " << str.capacity() << '\n'; 	// str.capacity() = 15
	
		auto len = str.size();
		std::string::size_type len = str.size();
		size_t len = str.size();
		// all 3 are same.
	
		if(str.size() == 0) {}
		if(str.empty()) {}
		// both are same
	}
*/

/*
	int main()
	{
		std::string str{ "Hello world this is string class" };
	
		str.reserve(500);
	
		auto cap = str.capacity();
		int realloc_count{};
	
		for (int i = 0; i < 1'000; ++i)
		{
			str.push_back('.');
	
			if (str.capacity() > cap)
			{
				std::cout << ++realloc_count << " size = " << str.size()
					<< " capacity = " << str.capacity() << '\n';
	
				cap = str.capacity();
			}
		}
	}
	
	// without reserve() function
	// 1 size = 48 capacity = 70
	// 2 size = 71 capacity = 105
	// 3 size = 106 capacity = 157
	// 4 size = 158 capacity = 235
	// 5 size = 236 capacity = 352
	// 6 size = 353 capacity = 528
	// 7 size = 529 capacity = 792
	// 8 size = 793 capacity = 1188
	
	// with str.reserve(500);
	// 1 size = 512 capacity = 766
	// 2 size = 767 capacity = 1149
*/

/*
	int main()
	{
		std::string str{ "Hello World" };
	
		str.assign(300'000, 'a');
		// change and assign chars in string
		std::cout << "str.size() = " << str.size() << '\n';
		std::cout << "str.capacity() = " << str.capacity() << '\n';
		// size (300'000), capacity(300'015)
	
		str.erase(50);
		// it deletes every char's after the 50th char.
		std::cout << "str.size() = " << str.size() << '\n';
		std::cout << "str.capacity() = " << str.capacity() << '\n';
		// size changes, capacity remains same
		// size (50), capacity(300'015)
	
		str.shrink_to_fit();
		// shrink capacity related to size.
		std::cout << "str.size() = " << str.size() << '\n';
		std::cout << "str.capacity() = " << str.capacity() << '\n';
		// size(50), capacity(63)
	}
*/

/*
	int main()
	{
		std::string str{ "Hello World" };
		std::cout << "str = " << str << '\n';

		char ar[] = "This is Istanbul";
		str.assign(ar + 8, 8);
		std::cout << "str = " << str << '\n'; // output -> str = Istanbul
	}
*/

/*
	int main()
	{
		int a[5] = { 2,4,6,7,9 };
	
		// range [a, a + 5) [ 2, 4, 6, 7, 9 ]
		// range [a, a + 3) [ 2, 4, 6 ]
	
		char str[] = "Hello World";
		// 0123456789ABC
		// Hello World
		// B is '\0'
		// C is 1 more than last char
	
		std::string word;
	
		word.assign(str + 6, 5);		// data param
		std::cout << word << '\n';		// output -> World
		word.assign(str + 6, str + 12);		// range param
		std::cout << word << '\n';		// output -> World
	}
*/

/*
	int main()
	{
		std::string str{ "HelloWorld!" };
	
		std::string s;
	
		s.assign(str, 3);
		std::cout << "s = " << s << '\n'; // output -> s = loWorld! 	|| sub-string param
	
		s.assign(str, 3, 5);
		std::cout << "s = " << s << '\n'; // output -> s = loWor 	|| sub-string param
	}
*/

/*
	int main()
	{
		std::string str{ "Hello World" };
	
		std::cout << '|' << str << "|\n";
		str += '!'; // char param
		std::cout << '|' << str << "|\n";
	}
*/

/*
	int main()
	{
		std::string str{ "Zbam" };
	
		std::cout << '|' << str << "|\n";	// output -> |Zbam|
	
		str.assign({'W','o','r','l','d'});	// initializer_list param
		std::cout << '|' << str << "|\n";	// output -> |World|
	}
*/

/*
	int main()
	{
		std::string s1;		// default ctor
		std::string s2{};	// default ctor
	
		std::string s1();	// most vexing parse, function decleration
	
		std::string str{ "Hello World!" }; // CString ctor
		// ctor is !NOT EXPLICIT
	
		std::string str_2 = "Hello everybody";
		std::string str_2("Hello everybody");
		std::string str_2{ "Hello everybody" };
		// if it was explicit ctor this expression would throw error.
	
		const char* p = "Around the world!";
		std::string str_3{ p + 6, 6 }; // data ctor
	}
*/

/*
int main()
{
	using namespace std;

	string str;
	auto is_empty = str.empty(); // will return true.
	auto size = str.size();

	std::cout << "is empty? " << is_empty << '\n';	// output -> 1
	std::cout << "size =  " << size << '\n';	// output -> 0
}
*/

/*
	#include <vector>
	
	int main()
	{
		using namespace std;
	
		const char* p = "Hello World";
	
		string str{ p, p + 5 }; // range ctor
		std::cout << str << '\n'; // output -> Hello
	
		vector<char> cvec{ 'U', 'Y', 'G', 'A', 'R' };
		string str_2{ cvec.begin(), cvec.end() }; // range ctror
		std::cout << str_2 << '\n'; // output -> UYGAR
	}
*/

/*
	int main()
	{
		using namespace std;
	
		string str(100, 'A'); // fill ctor
		std::cout << "str.size() = " << str.size() << '\n';
		// output -> str.size() = 100
	
		string s = { std::move(str) };
		// str becomes moved from state
		std::cout << str << s << '\n'; 				// output -> ""
		std::cout << "str.size() = " << str.size() << '\n';	// output -> str.size() = 0
		std::cout << "str.capacity() = " << str.capacity() << '\n';
		// output -> str.capacity() = 15 (buffer inside string)
	}
*/

/*
	int main()
	{
		using namespace std;
	
		// These are examples of constructing string object with 1 char value.
	
		string str{ 'A' };
		// this is not char parameter ctor.
		// this is initializer list parameter ctor
	
		string s('A'); // not legal
		// there is no char parameter ctor in string class
	
		string s_2 = "A"; // CString parameter ctor
	
		string s_3(1, 'A'); // fill ctor
	}
*/

/*
	int main()
	{
		using namespace std;
	
		string str(20, '\0'); // 20 null characters
	
		std::cout << "str.length() = " << str.length() << '\n';
		// output -> str.length() = 20
	
		// the necessity of '\0' (null character) at the end of the string
		// is for Cstring objects, not string object itself.
	}
*/

/*
	===============================
	| std::initializer_list class |
	===============================
*/

/*
	#include <initializer_list>
	
	void func(std::initializer_list<int> x)
	{
	
	}
	
	int main()
	{
		std::initializer_list<int> myList = { 1,3,5,7,9 };
	
		// initializer list class have 2 pointer inside.
		// one points to the address of arrays beginning.
		// second points to the address of the array end.
	
		// list variables are created in STACK MEMORY!
	
		std::cout << "sizeof(myList) = " << sizeof(myList) << '\n';
		// x64 // output -> sizeof(myList) = 16
	
		func(myList);
		// we are sending 2 pointer to function.
		// not array variables.
	}
*/

/*
	#include <initializer_list>
	
	class Myclass {
		char buffer[1024] {};
	};
	
	int main()
	{
		using namespace std;
	
		initializer_list<int> x{ 2, 4, 8, 7, 9, 10 };
		initializer_list<double> y{ .2, 14.2, 8.2, .7, .9, 10.1 };
		initializer_list<Myclass> z{ Myclass{}, Myclass{}, Myclass{} };
	
		std::cout << "sizeof(Myclass) = " << sizeof(Myclass) << '\n';	// output -> sizeof(Myclass) = 1024
		std::cout << "sizeof(x) = " << sizeof(x) << '\n';		// output -> sizeof(x) = 16
		std::cout << "sizeof(y) = " << sizeof(y) << '\n';		// output -> sizeof(y) = 16
		std::cout << "sizeof(z) = " << sizeof(z) << '\n';		// output -> sizeof(z) = 16
	}
*/

/*
	int main()
	{
		auto x = { 1,3,4,6,7 }; // initializer_list<int>
	
		auto y = { 1,2,3,4,5.5 };
		// sythax error because 2 types (int, double) in initializer list
		// auto type deduction can not deduce both types in 1 list type
	}
*/

/*
	int main()
	{
		auto x{ 1 };	// x's type is int
		auto y{ 1,2 };	// sythax error
		auto z = { 1 }; // z's type is initializer_list<int>
	}
*/

/*
	#include <initializer_list>
	
	void func(std::initializer_list<int> x) {}
	
	int main()
	{
		func({ 1,3,5 });
	
		// initializer_list classes member functions
	
		std::initializer_list<int> myList{ 1,4,7,2,9 };
	
		std::cout << "myList.size() = " << myList.size() << '\n';
		// output -> myList.size() = 5
	
		// SAME 1
		for (auto iter = myList.begin(); iter != myList.end(); ++iter)
		{
			std::cout << *iter << " "; // output -> 1 4 7 2 9
		}
		// SAME 2
		for (auto x : myList)
		{
			std::cout << x << " "; // output -> 1 4 7 2 9
		}
	}
*/

/*
	int bar(int);
	
	void foo(int a, int b, int c, int d)
	{
		// using initializer list in range based for loop
		for (auto val : { a, b, c, d })
		{
			bar(val);
		}
	}
*/

/*
	#include <initializer_list>
	
	int main()
	{
		std::initializer_list<double> x = { 1, 4, .6, 7, .3 };
		// int variables inside initializer_list<double> implicitly convert to double.
	}
*/

/*
	int main()
	{
		auto x = { 1,3,4,6,7 };
	
		auto iter = x.begin();
		std::cout << *iter << '\n'; // output -> 1 (first int variable in array)
		++iter;
		std::cout << *iter << '\n'; // output -> 3 (second int variable in array)
	
		// variables of array that reached with initializer_list are const variables
		// they can not be modified
	
		*iter = 10; // sythax error because of *iter is const
	}
*/

/*
	#include <initializer_list>
	#include <vector>
	
	class Myclass {
	public:
		Myclass(std::initializer_list<int>  x)
		{
			std::cout << "initializer_list<int> ctor\n";
		}
	};
	
	int main()
	{
		Myclass m1{ 1, 3, 5, 7 };	// output -> initializer_list<int> ctor
		Myclass m2 = { 1, 3, 5, 7 };	// output -> initializer_list<int> ctor
	
		std::vector<int> ivec{ 2,5,6,7 }; // vector class initializer_list param ctor
	
		std::string str{ 'U', 'Y', 'G', 'A', 'R' };
		std::cout << "str = " << str << '\n'; // output -> UYGAR
		// string class's initializer_list<char> ctor
	}
*/

/*
	#include <initializer_list>
	
	class Myclass {
	public:
		Myclass(int, int)
		{
			std::cout << "Myclass(int,int)\n";
		}
	
		Myclass(int)
		{
			std::cout << "Myclass(int)\n";
		}
	
		Myclass(std::initializer_list<int>)
		{
			std::cout << "Myclass(std::initializer_list<int>)\n";
		}
	};
	
	int main()
	{
		Myclass m1(12, 24);	// Myclass(int,int)
		Myclass m2{ 12, 34 };	// Myclass(std::initializer_list<int>)
		Myclass m3(20);		// Myclass(int)
		Myclass m4{ 20 };	// Myclass(std::initializer_list<int>)
	}
*/

/*
	int main()
	{
		using namespace std;
	
	
		string s1(52, 'A');	// fill ctor
		string s2{ 52,'A' };	// initializer_list ctor<char>
	
		std::cout << "s1.size() = " << s1.size() << '\n'; // output -> s1.size() = 52
		std::cout << "s2.size() = " << s2.size() << '\n'; // output -> s2.size() = 2
		// int to char conversion happens in s2
	}
*/

/*
	int main()
	{
		using namespace std;
	
		char str[] = "uygar";
		string s1(str, 20); 		// undefined behavior
	
		string s2(str, str + 20); 	// undefined behavior in range ctor.
	
		string s3{ "HelloWorld" };
	
		string s4(s3, 5); 		// substring ctor
		std::cout << s4 << '\n'; 	// output -> World
	
		string s5(s3, 2, 3);		// substring ctor
		
		string s6(s3, 5, 65);		// substring ctor -> NO UNDEFINED BEHAVIOUR IN SUBSTRING CTOR.
		std::cout << s6 << '\n'; 	// output -> World
	}
*/

/*
	---------------------------------------------
	| constexpr static data member string::npos |
	---------------------------------------------
*/

/*
	int main()
	{
		using namespace std;
	
		string s;
		s.npos;
	
		std::cout << string::npos << '\n';
		// x64 -> 18446744073709551615
	
		// a lot search functions in string class interface [find()..] returns index
		// if it finds the value its looking for it returns index
		// if it can not find it returns string::npos
		// npos is the max value of string class's size_type
	}
*/

/*
	int main()
	{
		using namespace std;
	
		string s{ "helloworld!" };
	
		
		auto idx = s.find('r');
		// size_t idx = s.find('r');
		// string::size_type idx = s.find('r');
		// These 3 lines are same
	
		if (idx != string::npos)
		{
			std::cout << "found, idx = " << idx << '\n';
			cout << s[idx] << '\n';
		}
		else
			std::cout << "can not found\n";
	
		// it is better to use if with initializer for no scope leakage
	
		if (auto idx = s.find('r'); idx != string::npos)
		{
			std::cout << "found, idx = " << idx << '\n';
			cout << s[idx] << '\n';
		}
		else
			std::cout << "can not found\n";
	}
*/

/*
	int main()
	{
		std::string str{ "Helloworld" };
	
		auto s1 = str.substr(1, 4);
		std::cout << s1 << '\n';	// output -> ello
	
		auto s2 = str.substr(1, std::string::npos);
		std::cout << s2 << '\n';	// output -> elloworld
	
		auto s3 = str.substr(5);
		std::cout << s3 << '\n';	// output -> world
		// second parameter default argument is string::npos
	
		auto s4 = str.substr();
		std::cout << s4 << '\n';	// output -> Helloworld
		// first parameter default argument is 0
	
		auto s5 = str.substr(0 , std::string::npos);
		std::cout << s5 << '\n';	// output -> Helloworld
	
		std::string s6(str, 3);
		std::string s7(str, 3, std::string::npos);
		// These 2 lines are same
	}
*/

/*
	int main()
	{
		std::string str{ "Hello World" };
	
		str[0] = '!';
		str.operator[](0) = '!';
		// These 2 lines are same
	
		for (size_t i{}; i < str.size(); ++i)
		{
			std::cout << str[i] << ' '; // output -> ! e l l o   W o r l d
		}
	
		try {
			auto c = str[250];
		}
		catch (std::exception& ex)
		{
			std::cout << "exception caught: " << ex.what() << '\n';
		}
		// giving non-valid index to operator[] -> undefined behaviour
		// no exception thrown, it is undefined behaviour
		// operator[] is not throwing exception but at() member function does
		
		try {
			auto c = str.at(250);
		}
		catch (std::exception& ex)
		{
			std::cout << "exception caught: " << ex.what() << '\n';
		}
		// output -> exception caught: invalid string position
	}
*/

/*
	int main()
	{
		std::string str{ "HelloWorld" };
	
		str.front() = 'Z';
		str[0] = 'Z';
		// These 2 lines are same
		std::cout << "str = " << str << '\n'; // output -> str = ZelloWorld
	
		str.back() = 'K';
		str[str.size() - 1] = 'K';
		// These 2 lines are same
		std::cout << "str = " << str << '\n'; // output -> str = ZelloWorlK
	}
*/

/*
	#include <initializer_list>
	int main()
	{
		std::initializer_list<int> x{ 2,4,5,6,1 };
	
		auto y = x;
		// copying pointers(2 pointers) inside initializer_list<int>
	
		std::cout << &*x.begin() << '\n';	// output -> 00000085E0F6FBD8
		std::cout << &*y.begin() << '\n';	// output -> 00000085E0F6FBD8
		// address of first variable in initializer_list<int>
	}
*/

/*
	void foo(std::string s)
	{
		std::cout << '|' << s << "|\n";
	}
	
	std::string bar()
	{
		return "Istanbul";
		// implicit conversion from CString to std::string
	}
	
	void func(const char* p) // wants CString as a parameter
	{
	
	}
	
	int main()
	{
		foo("Hello World!");
		// because of string class's ctor is not explicit
		// conversion from CString to std::string is valid
	
		auto s = bar();
	
		std::string str{ "i am in istanbul" };
	
		puts(str); // sythax error
		// conversion from std::string to CString is not valid!
	
		func(str.c_str());
		func(str.data());
		// c_str() and data() functions are converting std::string type to CString type
		// conversion from std::string to CString
	
		std::string str_2{ "We are live from Taksim" };
		auto p = str.c_str();
		puts(p);
		str += "doing some stuff in string";
		puts(p);
		// c_str() and data() is creating a NTBS in heap and returning the address of it.
		// when reallocation happens by concatenation
		// pointer that used by c_str() function still pointing the same location
		// but because of the reallocation, NTBS's address was changed in heap.
		// and the pointer become dangling.
	
		std::string str_3{ " We are live from Istanbul" };
		const char* x = str_3.c_str();
		char* y = str_3.data();
		// difference between c_str() and data() is
		// c_str() returns const char*
		// data() return char*
	}
*/

/*
	int main()
	{
		// getting the address of first char in the std::string
		std::string str{ "Hello World" };
	
		std::cout << (void*)&str[0] << '\n';
		std::cout << (void*)str.data() << '\n';
		std::cout << (void*)&*str.begin() << '\n';
	
		// output -> 000000FA7F5EF610
		// output -> 000000FA7F5EF610
		// output -> 000000FA7F5EF610
	}
*/

/*
	some member function (erase(), insert(), ..) have 2 different interfaces
		-> index interface		
		-> iterator interface (STL containers) // string is container too..
*/

/*
	int main()
	{
		using namespace std;
	
		string str1{ "0123456789" };
		str1.erase(2);	// index interface
		// erase every char after 2nd index
		std::cout << str1 << '\n'; // output -> 01
	
		string str2{ "0123456789" };
		str2.erase(2, 3); // index interface
		// erase 3 char starting with 2nd index
		std::cout << str2 << '\n'; // output -> 0156789
	
		string str3{ "0123456789" };
		str3.erase(str3.begin() + 2); // iterator interface
		// erase str.begin() + 2'nd address -> 0 + 2 = 2
		std::cout << str3 << '\n'; // output -> 013456789
	}
*/

/*
	int main()
	{
		using namespace std;
	
		string str1{ "helloworld" };
		string str2{ "hifromistanbul" };
	
		str1 = str2;		// copy assignment
		str1 = std::move(str2); // move assignment
	
	
		string str3 = { "uygarpinar" };
	
		str3 = "hello world";
		std::cout << str3 << '\n'; // output -> hello world
	
		char s[] = "thisIsIstanbul";
		str3 = s;
		std::cout << str3 << '\n'; // output -> thisIsIstanbul
	
		str3 = 'H';
		std::cout << str3 << '\n'; // output -> H
	
		str3 = { 'B','J','K' };
		std::cout << str3 << '\n'; // output -> BJK
	}
*/

/*
	int main()
	{
		using namespace std;
	
		string str{ "helloworld" };
		std::cout << str << '\n'; // output -> helloworld
	
		str.assign(12, 'a');					// fill assign
		std::cout << str << '\n'; // output -> aaaaaaaaaaaa
	
		string str2{ "stringLessons" };
		str.assign(str2, 6);
		std::cout << str << '\n'; // output -> Lessons
	
		str.assign(str2, 3, 3);
		std::cout << str << '\n'; // output -> ing
	
		char ar[] = "andrewniccol";
	
		str.assign(ar + 6, 3);
		std::cout << str << '\n'; // output -> nic
	
		str.assign(ar, ar + 3); 				// range assign
		std::cout << str << '\n'; // output -> and
	
		str.assign({ 'k','o','s','i','n','s','k','i' });	// initializer_list assign
		std::cout << str << '\n'; // output -> kosinski
	}
*/

/*
	int main()
	{
		std::string str{ "hello" };
		std::cout << "str.size() = " << str.size() << '\n'; // output -> 5
	
		str.resize(10); // second argument is default argument null
		std::cout << "str.size() = " << str.size() << '\n'; // output -> 10
	
		for (size_t i = 0; i < str.size(); ++i)
		{
			std::cout << "str[" << i << "] = " << (int)str[i] << '\n';
		}
		// str[0] = 104
		// str[1] = 101
		// str[2] = 108
		// str[3] = 108
		// str[4] = 111
		// str[5] = 0
		// str[6] = 0
		// str[7] = 0
		// str[8] = 0
		// str[9] = 0
	
		str = { "hello" };
		str.resize(10, '!');	// default argument is not used for second argument.
		std::cout << str << '\n'; // output -> hello!!!!!
	}
*/

/*
	int main()
	{
		using namespace std;
	
		string str{ "hey" };
	
		str += 'z';
		std::cout << str << '\n'; // output -> heyz
	
		str += "ero";
		std::cout << str << '\n'; // output -> heyzero
	
		string str_2{ "brick" };
		str += str_2;
		std::cout << str << '\n'; // output -> heyzerobrick
	
		str += {'s', 't', 'o', 'n', 'e'};
		std::cout << str << '\n'; // output -> heyzerobrickstone
	}
*/

/*
int main()
{
	using namespace std;

	string str;
	for (char c{ 'A' }; c <= 'Z'; ++c)
	{
		str.push_back(c);
	}

	std::cout << str << '\n'; // output -> ABCDEFGHIJKLMNOPQRSTUVWXYZ
}
*/

/*
	int main()
	{
		using namespace std;
	
		string str{ "hello" };
		str.append(3, 'z');
		std::cout << str << '\n'; // output -> hellozzz
	
		str = "hello";
		char ar[] = "world";
		str.append(ar, 3);
		std::cout << str << '\n'; // output -> hellowor
	
		str = "hello";
		string str_2{ "istanbul" };
		str.append(str_2, 2, 3);
		std::cout << str << '\n'; // output -> hellotan
	}
*/

/*
	int main()
	{
		using namespace std;
		string s{ "0123456789" };
	
		// insert() -> iterator interface
		// iterator wants an address from you then what to add to that address.
	
		s.insert(s.begin(), 'A');
		cout << s << '\n'; // output -> A0123456789
	
		s.insert(s.begin() + 3, 'B');
		cout << s << '\n'; // output -> A01B23456789
	
		s = { "0123456789" };
		char ar[] = "abcdefghi";
		s.insert(s.begin(), ar, ar + 5);
		cout << s << '\n'; // output -> abcde0123456789
	
		s = { "0123456789" };
		s.insert(s.begin() + 2, ar, ar + 5);
		cout << s << '\n'; // output -> 01abcde23456789
	
		s = { "0123456789" };
		s.insert(s.begin() + 5, { 'Z','E','R','O' });
		cout << s << '\n'; // output -> 01234ZERO56789
	
	
		// insert() -> index interface
		// add characters to a known index
	
		s = { "0123456789" };
		s.insert(5, 10, 'A');
		cout << s << '\n'; // output -> 01234AAAAAAAAAA56789
	}
*/

/*
	int main()
	{
		using namespace std;

		// erase() -> iterator interface

		string s{ "0123456789" };
		s.erase(s.begin());
		cout << s << '\n'; // output -> 123456789

		s = { "0123456789" };
		s.erase(s.begin() + 2);
		cout << s << '\n'; // output -> 013456789

		s = { "0123456789" };
		s.erase(s.end() - 1);
		cout << s << '\n'; // output -> 012345678

		s = { "0123456789" };
		s.erase(s.begin() + 1, s.end() - 1); // range
		cout << s << '\n'; // output -> 09
	}
*/

/*
	int main()
	{
		using namespace std;
	
		string str;
		std::cout << "Write a line : ";
		getline(cin, str);
	
		while (!str.empty()) {
			cout << str << '\n';
			str.erase(str.begin());
		}
	
		// HELLOWORLD
		// ELLOWORLD
		// LLOWORLD
		// LOWORLD
		// OWORLD
		// WORLD
		// ORLD
		// RLD
		// LD
		// D
	}
*/

/*
	int main()
	{
		using namespace std;
	
		string str;
		std::cout << "Write a line : ";
		getline(cin, str);
	
		while (!str.empty()) {
			cout << str << '\n';
			str.pop_back();
		}
	
		// HELLOWORLD
		// HELLOWORL
		// HELLOWOR
		// HELLOWO
		// HELLOW
		// HELLO
		// HELL
		// HEL
		// HE
		// H
	}
*/

/*
	int main()
	{
		using namespace std;
	
		string str;
		std::cout << "Write a line : ";
		getline(cin, str);
	
		while (!str.empty()) {
			cout << str << '\n';
			str.erase(0, 1); // index interface
		}
	
		// HELLOWORLD
		// ELLOWORLD
		// LLOWORLD
		// LOWORLD
		// OWORLD
		// WORLD
		// ORLD
		// RLD
		// LD
		// D
	}
*/

/*
	int main()
	{
		std::string str{ "helloworld" };
	
		std::cout << "str.size() = " << str.size() << '\n';
	
		// Ways to delete every char in a string?
	
		str = "";
		str = std::string{};
		str = {};
		str.resize(0);
		str.clear();
		str.erase(0);
		str.erase(); // default argument is 0
		str.erase(str.begin(), str.end()); // range erase
	}
*/

/*
	int main()
	{
		using namespace std;
	
		string str{ "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz" };
		cout << "lenght() = " << str.length() << '\n';		// output -> lenght() = 62
		cout << "capacity() = " << str.capacity() << '\n';	// output -> capacity() = 63
	
		str.erase(10, 5);
		cout << "lenght() = " << str.length() << '\n';		// output -> lenght() = 57
		cout << "capacity() = " << str.capacity() << '\n';	// output -> capacity() = 63
		// starting from 10th index delete 5 chars, index interface
	
		str = { "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz" };
		str.erase(10); 
		cout << "lenght() = " << str.length() << '\n';		// output -> lenght() = 10
		cout << "capacity() = " << str.capacity() << '\n';	// output -> capacity() = 63
		// starting from 10th index delete all chars, index interface
		// second argument is default and it is string::npos -> str.erase(10, std::string::npos)
	
		str = { "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz" };
		str.erase(10,1);
		cout << "lenght() = " << str.length() << '\n';		// output -> lenght() = 61
		cout << "capacity() = " << str.capacity() << '\n';	// output -> capacity() = 63
		// starting from 10th index delete only 1 char, deleting 10th index.
	
		str = { "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz" };
		str.erase(0);
		cout << "lenght() = " << str.length() << '\n';		// output -> lenght() = 0
		cout << "capacity() = " << str.capacity() << '\n';	// output -> capacity() = 63
		// starting from 0th index delete all chars, deleting all chars(empty string)
	
		str = { "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz" };
		str.erase();
		cout << "lenght() = " << str.length() << '\n';		// output -> lenght() = 0
		cout << "capacity() = " << str.capacity() << '\n';	// output -> capacity() = 63
		// starting from 0th index delete all chars, deleting all chars(empty string)
		// first default argument is 0, second default argument is string::npos
	
	
		str = { "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz" };
		str.resize(0);
		cout << "lenght() = " << str.length() << '\n';		// output -> lenght() = 0
		cout << "capacity() = " << str.capacity() << '\n';	// output -> capacity() = 63
		// resize'in string with 0 value makes an empty string.
	
		// decreasing char count in string is not changing its capacity.
		// for decreasing its capacity, using shrink_to_fit() function.
	
		str.shrink_to_fit();
		cout << "capacity() = " << str.capacity() << '\n';	// output -> capacity() = 15
	}
*/

/*
	----------------------------------------------------
	| three-way comparison(spaceship) operator [ <=> ] |
	----------------------------------------------------
*/

/*
	spaceship operator comes with C++20

	nearly all comparison operators in stl classes are changed.

	Spaceship operator can be defaulted. Normally only special member
	functions can be defaulted before C++20

	The rules of == operator has been changed, you do not need to write 
	!= operator if == are already overloaded. Compiler will implicitly
	write != operator overload
*/

/*
	#include <algorithm>
	
	int main()
	{
		using namespace std;
	
		string str{ "helloWorld" };
		if (str == "helloWorld") {}
		// std::string object can compare with CStrings
	
		string name{ "hello" };
		if (str == name) {}
		// std::string objects can compare with each other
	
		// int compare(x, y);
		// if result is positive ->	(x > y)
		// if result is negative ->	(x < y)
		// if result is zero	 ->	(x = y)
	
		str.compare("istanbul");
		// return value type is int
		// compare is a member function of std::string class
		// we are comparing with [*this](str) with CString
	
		str.compare(name);
		// we are comparing with [*this](str) with another string object
	
		str.compare(3, 4, name, 6, 4);
		// we are comparing substrings
		// (str) 4 chars starting from 3th index compare with
		// (name)4 chars starting from 6th index
	
		lexicographical_compare();
		// from algorithm header file we can use
		// lexicographical_compare() function to compare strings
	}
*/

/*
	because of std::string class also a container, functions for containers can also
	be used for string class (e.g, reverse(), sort(), trim functions... ).
	Container functions can be used with iterator interface.
*/

/*
	#include <algorithm>
	int main()
	{
		using namespace std;
		string str{ "hello world" };
		cout << str << '\n'; // output -> [hello world]
	
		reverse(str.begin(), str.end()); // iterator interface
		cout << str << '\n'; // output -> [dlrow olleh]
	
		sort(str.begin(), str.end());
		cout << str << '\n'; // output -> [ dehllloorw]
	
		// remove-erase idiom
		str = { "hello world we are live from istanbul" };
		str.erase(remove_if(str.begin(), str.end(),
			[](char c) {return string{ "aeoui" }.find(c) != string::npos;}), str.end());
		cout << str << '\n'; // output -> [hll wrld w r lv frm stnbl]
	
		// erase_if() global function comes with C++20
		str = { "hello world we are live from istanbul" };
		erase_if(str, [](char c) {return string{ "aeoui" }.find(c) != string::npos;});
		cout << str << '\n'; // output -> [hll wrld w r lv frm stnbl]
	}
*/

/*
	SEARCH FUNCTIONS
	-------------------
	find
	rfind [reverse find -> searching from last index to first index]
	find_first_of
	find_first_not_of
	find_last_of
	find_last_not_of

	-> returns index(string::size_type)[size_t] if finds 
	-> returns string::npos if can not find

	C++23 
	contains() function return bool type

	search functions can be used for substrings too.. 
	no need to search in all string
*/

/*
int main()
{
	using namespace std;
	string str{ "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz" };

	char c;
	cout << "add the char value to find: ";
	cin >> c;

	if (auto idx = str.find(c); idx != string::npos)
	{
		cout << "found... idx = " << idx << '\n';
		str[idx] = '*';
		cout << str << '\n';
	}
	else
		cout << "cannot found\n";
}
*/

/*
	int main()
	{
		using namespace std;
		string str{ "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz" };
	
		cout << "add string to find: ";
		string searched;
		cin >> searched;
	
		if (auto idx = str.find(searched); idx != string::npos)
		{
			cout << "found... idx = " << idx << '\n';
			auto len = searched.length();
			str.replace(idx, len, len, '*');
			cout << str << '\n';
		}
		else
			cout << "cannot found\n";
	}
*/

/*
	int main()
	{
		using namespace std;
		string str{ "hello world i am saying hello" };
		constexpr int hello_length = 5;
	
		auto idx = str.find("hello");
		str.replace(idx, hello_length, hello_length, '*');
		cout << str << '\n'; // output -> ***** world i am saying hello
	
		str = { "hello world i am saying hello" };
		idx = str.rfind("hello");
		str.replace(idx, hello_length, hello_length, '*');
		cout << str << '\n'; // output -> hello world i am saying *****
	}
*/

/*
	int main()
	{
		using namespace std;
		string str = { "Hello world! This is Istanbul" };
	
		if (auto idx = str.find_first_of("aetkms"); idx != string::npos) {
			cout << "found...  idx = " << idx << '\n';
		}
		// output -> [found...  idx = 1] -> 'e' is in index 1
	
	
		if (auto idx = str.find_first_not_of("Hetkms"); idx != string::npos) {
			cout << "found...  idx = " << idx << '\n';
		}
		// output -> [found...  idx = 2] -> 'l' is in index 2
	}
*/

/*
	int main()
	{
		using namespace std;
	
		string s1{ "hello" };
		string s2{ "world" };
	
		s1 + s2 + 'A' + "really";
		// addition operator starts goes from left to right
	
		std::cout << s1 + s2 + 'A' + "really" << '\n'; // output -> helloworldAreally
		std::cout << "real " + s2 << '\n'; // output -> real world
	
		// 2 pointers can not added
		const char* p = "galaxy";
	
		 // std::cout << p + " hello" << '\n';
		// not possible because CString is const char*(pointer)
	
		"hello"s;
		operator""s("hello", 5);
		// converts CStrings to std::string object [string literal]
	
		std::cout << "hello"s + " world"s << '\n';	// output -> hello world
		// adding 2 std::string objects
		std::cout << "hello "s + p << '\n';		// output -> hello galaxy
		// adding pointer(const char*)[CString] to std::string object
	}
*/

/*
	===================================
	| std::string_view class (C++ 17) |
	===================================
*/

/*
	if our purpose is just reading from a string.
	it is better using string_view class.

	string_view class have 2 pointer in its interface.

	All the read only functions in std::string class is  
	also in std::string_view class's interface.
*/

/*
	int main()
	{
		// simplified
		class StringView {
		public:
			std::size_t length()
			{
				return pointerEnd - pointerStart;
			}
		private:
			const char* pointerStart;
			const char* pointerEnd;
		};
	}
*/

/*
	#include <string_view>
	int main()
	{
		using namespace std;
	
		string str(200'000, 'A');
	
		auto s = str.substr(30'000, 70'000);
		// we are copying 40'000 chars when we call substr() function
		// when we use string_view class object to show 40'000 chars
		// we are not copying chars
	
		std::cout << "sizeof(string_view) = " << sizeof(string_view) << '\n';
		// x64 system output -> sizeof(string_view) = 16 [2 pointers]
	}
*/

/*
	#include <string_view>
	int main()
	{
		const char* p = "Hello from Istanbul";
	
		std::string str(p);
		// we created a copy of CString
		std::string_view sv = p;
		// created 2 pointer which are pointing CString's begin and end.
	
	
		std::string str_1{ "this life is an illusion" };
		std::string_view sv_1{ str_1 };
		std::cout << sv_1 << '\n';
	
		str_1.append(300, 'A');
		// reallocation happens in str_1
		std::cout << sv_1 << '\n'; // undefined behaviour
		// when reallocation happens std::string objects place
		// will change so pointers in std::string_view object
		// are still pointing same location.
		// pointers become dangling.
	}
*/

/*
	int main()
	{
		using namespace std;
	
		string s1(100'000, 'A');
		string s2(100'000, 'Z');
	
		s1.swap(s2);		// string classes swap function
		std::swap(s1, s2);	// global swap function
	}
*/

/*
	int main()
	{
		using namespace std;
	
		string str;
		cout << "write something: ";
		getline(cin, str, '!');
		// 3rd parameter is delimiter character.
		// Default delimiter argument is -> '\n'(new line)
		std::cout << str << '\n';
	
		// write something : hello world!Live from istanbul
		// output -> hello world
		// [Live from Istanbul] is still in buffer
	}
*/

/*
	int main()
	{
		int ival{ 343234234 };
		double dval{ 3432.34234 };
		std::string str = {"hello"};
	
		str = str + std::to_string(ival);
		std::cout << str << '\n'; // output -> hello343234234
	
		str = "hello";
		str = str + std::to_string(dval);
		std::cout << str << '\n'; // output -> hello3432.342340
	
	
		str = { "9123helloworld" };
		int intVal;
	
		intVal = std::atoi(str.c_str());
		std::cout << intVal << '\n'; // output -> 9123
		// std::atoi(const char*) [wants CString as an argument
		// sending c_str() or data() functions are valid
	
		int x = std::stoi(str, nullptr, 16);
		std::cout << "0x9123 = " << x << '\n'; // output -> 0x9123 = 37155
	
		// third parameter wants [base values]
		// [3rd parameter]16 converts int(base 10) to int(base 16)
	
		std::size_t idx;
		x = stoi(str, &idx);
		std::cout << "idx = " << idx << '\n'; // output -> idx = 4
		std::cout << "x = " << x << '\n'; // output -> x = 9123
		// [2nd parameter] at 4th index there is no digit to convert to int type.
		// [3rd parameter] default argument is 10[base10]
	}
*/

/*
	#include <sstream>

	int main()
	{
		int x{ 34365 };
		double dval = 234.96;
	
		std::string str = { "hello World" };
	
		std::ostringstream oss;
		// we are creating a space in memory and 
		// std::ostringstream object will write to that memory
	
		oss << x << "!!" << dval << '&' << str;
		std::cout << oss.str() << '\n'; // output -> 34365!!234.96&hello World
		// std::ostringstream.str() function will extract the data 
		// in its memory to an std::string object
	}
*/

/*
	#include <algorithm>
	#include <vector>
	int main()
	{
		using namespace std;
	
		string str{ "Hello world, we are live from Istanbul as you know" };
		char cval = 'o';
	
		std::cout << "char count 'o': " << count(str.begin(), str.end(), cval) << '\n';
		// count() global function using iterator interface
	
		vector<char> cvec = { 'j','o','k','e' };
	
		str.assign(cvec.begin(), cvec.end());
		std::cout << str << '\n'; // output -> joke
	
		str = { "Hello world, we are live from Istanbul as you know" };
		transform(str.begin(), str.end(), str.begin(), &std::toupper);
		std::cout << str << '\n'; // output -> HELLO WORLD, WE ARE LIVE FROM ISTANBUL AS YOU KNOW
	}
*/

/*
	int main()
	{
		using namespace std;
	
		string str = { "helloworld.jpeg" };
	
		auto a = str.starts_with("hello");
		auto b = str.ends_with(".jpeg");
		// returns bool
	
		// C++ 23
		auto c = str.contains("wor");
	}
*/
