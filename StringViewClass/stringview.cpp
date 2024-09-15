#include <iostream>

/*
	--------------------
	| std::string_view | C++17
	--------------------
*/

/*
	#include <string>

	class StringView {
	public:
		// std::string_view classes interface can have
		// all the const member functions of std::string class
	private:
		const char* mp_start;
		// const char* mp_end; -> can also be used
		std::size_t len;
	};


	void func(const std::string& r) {}

	void foo(std::string_view sv) {}
	// only pointers will be copied

	int main()
	{
		using namespace std;

		string str{ "hello world" };
		func(str);	// no copying

		func("hello world we are live from Izmir");
		// temp string object has been constructed
		// this string literal will be copied to the memory
		// allocated in heap.
	}
*/

/*
	#include <string>
	#include <string_view>

	void func(const std::string& strObj)
	{
		auto str = strObj.substr(10, 4500);
		// we are using only for reading purpose
		// but substr() will copy all the char's in range 10,4500
	}

	void func_efficient(const std::string& strObj)
	{
		std::string_view sv = strObj;
	}


	int main()
	{
		using namespace std;

		string str{ "hello world" };
		func(str);	// no copying

		func("hellow world we are live from Izmir");
		// temp string object has been constructed
		// this string literal will be copied to the memory
		// allocated in heap.
	}
*/

/*
	#include <string_view>

	int main()
	{
		using namespace std;

		// x64 mode

		std::cout << "sizeof(char*) = " << sizeof(char*) << '\n';
		// output -> sizeof(char*) = 8
		std::cout << "sizeof(size_t) = " << sizeof(std::size_t) << '\n';
		// output -> sizeof(size_t) = 8
		std::cout << "sizeof(string_view) = " << sizeof(string_view) << '\n';
		// output -> sizeof(string_view) = 16
	}
*/

/*
	#include <string>
	#include <string_view>

	int main()
	{
		using namespace std;

		auto p = new string{ "hello world" };
		string_view sv(*p);

		cout << "|" << sv << "|\n";	// output -> |hello world|
		cout << sv.front() << '\n';	// output -> h
		cout << sv.back() << '\n';	// output -> d

		for (size_t idx{}; idx != sv.size(); ++idx) {
			cout << sv[idx] << " ";
		}
		// output -> h e l l o   w o r l d

		cout << '\n';
		cout << boolalpha;

		cout << "sv.length() = " << sv.length() << '\n';
		// output -> sv.length() = 11
		cout << "sv.size() = " << sv.size() << '\n';
		// output -> sv.size() = 11

		delete p;
		// pointers inside string_view object becomes dangling pointer
		// when we gave back the memory from heap with delete

		cout << "|" << sv << "|\n";	// Undefined Behaviour(UB)
	}
*/

/*
	#include <string>
	#include <string_view>

	int main()
	{
		using namespace std;

		string str{ "hello world" };
		string_view sv = str;

		cout << "|" << sv << "|\n";

		str += " We are live from Izmir";
		cout << str << '\n';	
    // output -> hello world We are live from Izmir

		// reallocation can be happen in this operation
		// but string_view objects pointers still pointing the same memory

		cout << "|" << sv << "|\n";	// Undefined Behaviour
	}
*/

/*
	#include <string>
	#include <string_view>

	std::string get_name()
	{
		return "hello world";
		// will create a temp string object is holding the string literal
		// when the function ends temp objects destructor will be called
	}

	int main()
	{
		using namespace std;

		const auto& r = get_name();
		// no Undefined Behaviour -> life extension happened
		// the temp string object life will extend

		string& str_ref = get_name();	// syntax error
		// l value reference can not bind to PR value expression


		string_view sv = get_name();
		// string_view object's pointers is pointing 
    // temp string objects begin and end

		// when temp string object get destroyed 
    // at the end of the function
		// string_view objects pointers will become dangling
		cout << sv << '\n';
		// Undefined Behaviour(UB)
	}
*/

/*
	#include <string>
	#include <string_view>

	int main()
	{
		using namespace std;

		char str[] = "hello world";	// str CArray is -> null terminated byte stream

		cout << '|' << str << "|\n";	// output -> |hello world|

		string_view sv(str, 5);
		cout << sv.length() << '\n';	// output -> 5
		cout << sv << '\n';				    // output -> hello
		cout << sv.front() << '\n';		// output -> h
		cout << sv.back() << '\n';		// output -> o

		cout << sv.data() << '\n';		// output -> hello world
		// even if "sv" is not pointing through the whole CArray (only "hello")
		// data() member function will check for NULL character
    // and will find it at the end of the CArray
	}
*/

/*
	#include <string_view>
	#include <vector>

	int main()
	{
		using namespace std;

		vector<char> cvec{ 'h', 'e', 'l', 'l', 'o' };
		// there is no NULL character at the end of the vector

		string_view sv(cvec.data(), 5);
		cout << "|" << sv << "|\n";			// output -> |hello|

		cout << "|" << sv.data() << "|\n";	// Undefined Behaviour
		// data() member function is looking for NULL character
    // and there is not any NULL character at the end of the vector
	}
*/

/*
	#include <string_view>

	int main()
	{
		using namespace std;

		string_view sv;

		cout << boolalpha;

		cout << "is empty? " << sv.empty() << '\n';	// output -> is empty? true
		cout << sv.length() << '\n';				        // output -> 0
		cout << sv.size() << '\n';					        // output -> 0
		cout << (sv.data() == nullptr) << '\n';		  // output -> true
	}
*/

/*
	#include <string_view>
	#include <array>

	int main()
	{
		char str[] = "Hello World";
		std::string s{ "Life is an illusion" };
		std::array<char, 6> arr{ 'm', 'a', 'r', 'v', 'e','l' };

		std::string_view sv1;
		std::cout << "sv1.length() = " << sv1.length() << " sv1 = (" << sv1 << ")\n";
		// output -> sv1.length() = 0 sv1 = ()

		std::string_view sv2 = "Whats going on!";
		std::cout << "sv2.length() = " << sv2.length() << " sv2 = (" << sv2 << ")\n";
		// output -> sv2.length() = 15 sv2 = (Whats going on!)

		std::string_view sv3 = { str, 5 };
		std::cout << "sv3.length() = " << sv3.length() << " sv3 = (" << sv3 << ")\n";
		// output -> sv3.length() = 5 sv3 = (Hello)

		std::string_view sv4{ s };
		std::cout << "sv4.length() = " << sv4.length() << " sv4 = (" << sv4 << ")\n";
		// output -> sv4.length() = 19 sv4 = (Life is an illusion)

		std::string_view sv5{ s.data() + 11, 8};
		std::cout << "sv5.length() = " << sv5.length() << " sv5 = (" << sv5 << ")\n";
		// output -> sv5.length() = 8 sv5 = (illusion)

		std::string_view sv6{ arr.data(), size(arr)};
		std::cout << "sv6.length() = " << sv6.length() << " sv6 = (" << sv6 << ")\n";
		// output -> sv6.length() = 6 sv6 = (marvel)

		std::string_view sv7{ str, str + 4 };
		std::cout << "sv7.length() = " << sv7.length() << " sv7 = (" << sv7 << ")\n";
		// output -> sv7.length() = 4 sv7 = (Hell)

		std::string_view sv8{ s.begin(), s.begin() + 4};
		std::cout << "sv8.length() = " << sv8.length() << " sv8 = (" << sv8 << ")\n";
		// output -> sv8.length() = 4 sv8 = (Life)
		// range constructor C++20
	}
*/

/*
	#include <string>
	#include <string_view>

	void func(std::string);

	int main()
	{
		using namespace std;

		string str{ "hello world" };
		string_view sv{ "We are live from Izmir" };

		string s = sv;	// syntax error
    // error: conversion from 'std::string_view' to non-scalar 
		string s{ sv };
		// explicit std::string constructor have a string_view paramater

		sv = str;
		sv = str.operator std::basic_string_view<char, std::char_traits<char>>();
		// string object convert to string_view object


		auto sv1 = "hello world"sv;
		func(sv1);					// syntax error
    // error: could not convert 'sv1' from 'std::basic_string_view<char>' 
    // to 'std::string'
		func(std::string{ sv1 });	// VALID
	}
*/

/*
	#include <string_view>
	#include <string>

	std::string func(std::string_view sv)
	{
		return sv;					// not valid -> explicit constructor
		// explicit std::string(std::string_view)

		return std::string{ sv };	// valid

		return sv.data();			// valid
		// data() returns const char*
		// string class has CString(const char*) parameter constructor
	}

	void foo(std::string);

	int main()
	{
		std::string_view sw("hello world");

		foo(sw);					          // not valid -> explicit ctor
		std::string str = sw;		    // not valid -> explicit ctor

		std::string str{ sw };		  // valid -> explicit string(string_view) ctor
		std::string s = sw.data();	// valid -> string(const char*) ctor
		foo(std::string{ sw });		  // valid -> explicit string(string_view) ctor
		foo(sw.data());				      // valid -> string(const char*) ctor
	}
*/

/*
	#include <string_view>

	int main()
	{
		using namespace std;

		char str[] = "hello world";
		string_view sv{ str };

		str[1] = 'a';
		cout << "|" << sv << "|\n"; // output -> |hallo world|
	}
*/

/*
	#include <string_view>
	#include <string>

	int main()
	{
		using namespace std;

		std::string str{ "hello world" };
		std::string_view sv{ str };

		std::cout << "[" << sv << "]\n";	// output -> [hello world]

		str.front() = 'X';
		str.back() = 'X';
		std::cout << "[" << sv << "]\n";	// output -> [Xello worlX]

		str.append(500, 'A');	// reallocation happened
		std::cout << "[" << sv << "]\n";	// Undefined Behaviour(UB)
	}
*/

/*
	#include <string_view>
	#include <string>
	#include <algorithm>

	std::string_view get_reverse(std::string str)
	{
		reverse(begin(str), end(str));
		return str;
	}
	// we are returning a string_view to the object 
  // and its dtor will be called after functions scope end
	// it will cause Undefined Behaviour(UB)

	int main()
	{
		auto s = get_reverse("hello world");	// Undefined Behaviour

		std::cout << s << '\n';
	}
*/

/*
	// remove prefix() changes the start_pointer  of string_view object
	// remove_suffix() changes the end_pointer    of string_view object

	#include <string_view>

	int main()
	{
		using namespace std;

		string_view sv("hello galaxy");

		cout << "sv.length() = " << sv.length() << '\n';
		cout << "|" << sv << "|\n";
		// output ->
		//	sv.length() = 12
		//	|hello galaxy|

		sv.remove_prefix(6);
		cout << "sv.length() = " << sv.length() << '\n';
		cout << "|" << sv << "|\n";
		// output ->
		// sv.length() = 6
		// |galaxy|

		sv.remove_suffix(2);
		cout << "sv.length() = " << sv.length() << '\n';
		cout << "|" << sv << "|\n";
		// output ->
		//	sv.length() = 4
		//	|gala|
	}
*/

/*
	#include <string_view>

	int main()
	{
		using namespace std;

		string_view sv("hello galaxy");

		try{
			auto c1 = sv[20];
			// no exception thrown

			auto c2 = sv.at(20);
      // execption thrown
		}
		catch (const std::exception& ex){
			cout << "exception caught : " << ex.what() << '\n';
		}

    // output ->
    // exception caught : basic_string_view::at: __pos (which is 20) >= 
    // this->size() (which is 12)
	}
*/

/*
	#include <string_view>
	#include <string>

	int main()
	{
		using namespace std;

		string str{ "    empty space in the beginning" };
		std::string_view sv{ str };

		sv.remove_prefix(std::min(sv.find_first_not_of(" "), sv.size()));
		// if the string contains only space characters 
    // find_first_not_of will return string::npos(biggest value of size_t) 
    // so sv.size() will be chosen
		// else find_first_not_of() will get chosen

		std::cout << "(" << str << ")\n";
		// output -> (    empty space in the beginning)
		std::cout << "(" << sv << ")\n";
		// output -> (empty space in the beginning)
	}
*/

/*
	#include <string_view>

	int main()
	{
		using namespace std;

		std::string_view str{ "programming" };

		str.remove_prefix(3);
		str.remove_suffix(4);

		std::cout << "the length of " << str << " is " 
              << std::strlen(str.data()) << '\n';
		// strlen() is looking for a NULL Terminated Byte Stream
		// output -> the length of gram is 8

		std::cout << "the length of " << str << " is " << str.length() << '\n';
		// output -> the length of gram is 4

		std::cout << "str.data() is " << str.data() << '\n';
		// str.data() is looking for a NULL Terminated Byte Stream
		// output -> str.data() is gramming

		std::cout << "str is [" << str << "]\n";
		// output -> str is [gram]
	}
*/

/*
	#include <string_view>

	int main()
	{
		using namespace std;

		char arr[] = { 'a', 'b', 'c', 'd', '\0', '\0' , '\0' };

		std::string_view sv(arr, sizeof arr);

		auto trim_idx = sv.find('\0');
		std::cout << "trim_idx = " << trim_idx << '\n';
		// output -> trim_idx = 4

		if (trim_idx != sv.npos)
			sv.remove_suffix(sv.size() - trim_idx);

		std::cout << "line in arr (" << arr << ") and the size of arr = " 
              << sizeof arr << '\n';
		// line in arr (abcd) and the size of arr = 7

		std::cout << "sv line is (" << sv << ") and the length of sv = " 
              << sv.size() << '\n';
		// sv line is (abcd) and the length of sv = 4
	}
*/

/*
	#include <string_view>

	int main()
	{
		using namespace std;

		string_view sv{ "helloworld" };

		sv.remove_prefix(5);
		sv.remove_suffix(7);

		cout << "(" << sv << ")";	// undefined behaviour
	}
*/

/*
	// C++ 20 starts_with() and ends_with() member functions

	#include <string_view>

	int main()
	{
		std::string_view sv{ "Hello world we are live from Universe" };

		std::cout << std::boolalpha;

		std::cout << sv.length() << '\n';					          // output -> 37
		std::cout << sv.substr(0, sv.find(' ')) << '\n';	  // output -> Hello
		std::cout << (sv == "Hello galaxy") << '\n';		    // output -> false

		std::cout << sv.starts_with("Hello") << '\n';		    // output -> true
		std::cout << sv.ends_with("Galaxy") << '\n';		    // output -> false

		std::cout << '(' << sv << ")";
		// output -> (Hello world we are live from Universe)
	}
*/