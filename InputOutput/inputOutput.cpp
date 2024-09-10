/*
	-----------------------------
	| Input - Output Operations |
	-----------------------------
*/

/*
	1. Formatted I/O
		a. writing to standart output & reading from standart input	
		b. read & write(IO) operations on files.					
		In C++	-> basic_ifstream	inherited from basic_istream
				-> basic_ofstream	inherited from basic_ostream 
				-> basic_fstream	inherited from basic_iostream 
		c. read & write(IO) operations in memory
		In C++	-> basic_istringstream	inherited from basic_istream
				-> basic_ostringstream	inherited from basic_ostream 

	2. Unformatted I/O
	3. Exception Handling in stream operations.
	4. File operations
*/

/*
	Open IO_Hierarchy.png
	-> ios_base is not a class template it is a class
	-> basic_ios<> is a class template,
		can create specialization with charachter type in the stream
*/

/*
	#include <iostream>

	int main()
	{
		using namespace std;
	
		basic_ios<char>;
		ios; 
		// These 2 lines are same.
	
		basic_ios<wchar_t>;
		wios;
		// These 2 lines are same.
	
		basic_ostream<char>;
		ostream;
		// These 2lines are same.
	
		basic_ostream<wchar_t>;
		wostream;
		// These 2lines are same.
	
		// cout wcout 
		// cin  wcin
		// cerr wcerr
	}
*/

/*
	---------------------------
	| Formatted IO Operations |
	---------------------------
*/

/*

	Formatted Output -> 
	Converting data to text first then sending to stream
	UnFormatted Output ->
	Directly sending binary data to stream 
*/

/*
	#include <iostream>
	
	class Basic_ostream {
	public:
		// inserter member functions
		Basic_ostream& operator<<(int);
		Basic_ostream& operator<<(double);
		// return type is *this
	};
	
	// there are some global operator<<() functions
	// for some classes and for some basic types
	// when we include header files we can use that global operator<<() functions
	#include <string>
	//	ostream& operator<<(ostream&, const string&)
	// return type is a reference to first parameter
*/

/*
	#include <iostream>
	
	void new_line()
	{
		std::cout << '\n';
	}
	
	int main()
	{
		using namespace std;
	
		int x{ 254 };
		double dval{ 2.3 };
	
		cout << x << dval;
		cout.operator<<(x).operator<<(dval);
		// These 2 lines are same.
		// Because of operator<<() return ostream& we can use chaining.
		new_line();
	
	
		cout << "hello world";
		operator<<(cout, "hello world");
		// These 2 lines are same.
		// parameter is const char* (array decay)
		// Function is a global operator<<() function
		// ostream& operator<<(ostream&, const char*)
		new_line();
	
		cout.operator<<("live from izmir");	// output -> 00007FF7AAB2ACF0
		// Function is a member operator<<() function
		// ostream& operator<<(void*)
		new_line();
	
	
		cout << 'A';			// output -> A		--> global function
		// ostream& operator(ostream&, char);
		new_line();
	
		cout.operator<<('A');	// output -> 65		--> member function
		// ostream& operator<<(int)
	}
*/

/*
	// ostream and istream classes both have operator bool() function
	// inherited from base class
	
	#include <iostream>
	
	int main()
	{
		using namespace std;
	
		if (cout && cin)	// if (cout.operator bool() && cin.operator bool())
		{
			// in logic context conversion is valid.
		}
	
		cout ? 10 : 20;		// logic context
	
		bool b1 = cout;							// syntax error
		bool b2 = cin;							// syntax error
		bool b3 = static_cast<bool>(cout);		// valid
		bool b4 = static_cast<bool>(cin);		// valid
		// because of operator bool() function is explicit
		// implicit conversion from cout to bool is not valid.
	}
*/

/*
	#include <iostream>
	#include <string>
	#include <memory>
	#include <bitset>
	#include <complex>
	#include <utility>
	
	int main()
	{
		using namespace std;
	
		cout << string{ "hello world" } << '\n';
		// ostream& operator<<(ostream&, const std::string&);
		// global operator<<() function which is inside <string> header.
	
		auto ptr = make_unique<string>("hello galaxy");
		cout << ptr << '\n';
		// global operator<<() function which is inside <memory> header
	
		cout << bitset<32>{236283626323u} << '\n';
		// global operator<<() function which is inside <bitset> header
	
		cout << complex<double>{3.5, 6.7} << '\n';
		// global operator<<() function which is inside <complex> header
	
		cout << pair<int,int>{ 23,56 };
		// no global operator<<() function for pair
	}
*/

/*
	#include <iostream>
	
	// writing inserter functions
	template <typename T, typename U>
	std::ostream& operator<<(std::ostream& os, const std::pair<T, U>& p)
	{
		return os << '[' << p.first << ", " << p.second << ']';
	}
*/

/*
	#include <fstream>	// for ostream and ofstream
	#include <sstream>	// for ostringstream
	#include <vector>
	#include <string>
	#include "nutility.h"
	#include <algorithm>	// for reverse()
	
	int main()
	{
		using namespace std;
	
		vector<string> svec;
		rfill(svec, 5, rtown);
	
		for (const auto& s : svec){
			cout << s << '-';
		}
		// output -> malatya-tekirdag-yozgat-tokat-batman-
	
		ofstream ofs{ "out.txt" };
		if (!ofs) {
			std::cerr << "can not create out.txt file\n";
			exit(EXIT_FAILURE);
		}
	
		for (const auto& s : svec){
			ofs << s << '-';
		}
		// out.txt output -> malatya-tekirdag-yozgat-tokat-batman-
	
		ostringstream oss;
	
		for (const auto& s : svec) {
			oss << s << '-';
		}
	
		cout << '\n';
		string str = oss.str();
		reverse(str.begin(), str.end());
		cout << str << '\n';
		// output -> -namtab-takot-tagzoy-gadriket-aytalam
	
		// all the memory that has written by ostringstream
		// converted to string by str() function.
		// then we reverse that string
	}
*/

/*
	#include <iostream>
	#include <string>
	
	class Ostream {
	public:
		Ostream& operator<<(int);
		Ostream& operator<<(double);
		Ostream& operator<<(long);
		Ostream& operator<<(void*);
		// if we want to write down an address
		// (void*) overload will be chosen.
	
		Ostream& operator<<(Ostream& (*fp)(Ostream&))
		{
			return fp(*this);
		}
		// its parameter is a function pointer (callback function)
	};
	
	// ostream manipulator function
	std::ostream& Endl(std::ostream& os)
	{
		os.put('\n');
		os.flush();
		return os;
	}
	
	std::ostream& dash(std::ostream& os)
	{
		return os << "\n-----------------------------------\n";
	}
	
	int main()
	{
		std::cout << std::endl;
		// we are basically sending cout object to endl() function.
	
		int x{ 32848 };
		double d{ 982.32 };
		std::string name{ "hello world" };
	
		std::cout << x << dash << d << dash << name << '\n';
		// output ->
		//	32848
		//	----------------------------------
		//	982.32
		//	----------------------------------
		//	hello world
	}
*/

/*
	#include <random>
	#include <iostream>
	
	int main()
	{
		using namespace std;
	
		mt19937 eng;
	
		cout << eng() << '\n';	// output -> 3499211612
	
		// ostream& operator<<(mt19937& eng) overload
		cout << eng << '\n';
		// output ->
		//	1301868182 2938499221 2950281878 1875628136 751856242 944701696 2243192071
		//	694061057 219885934 2066767472 3182869408 485472502 2336857883 1071588843
		//	3418470598 951210697 3693558366 2923482051 1793174584 2982310801 1586906132
		//	1951078751 1808158765 1733897588 431328322 4202539044 530658942 1714810322
		//	3025256284 3342585396 1937033938 2640572511 1654299090 3692403553 4233871309
		//	3497650794 862629010 2943236032 2426458545 1603307207 1133453895 3099196360
		//	2208657629 2747653927 931059398 761573964 3157853227 785880413 730313442 ....
	
		// serialization :
		// for different computer to understand our object as same as how we understand it
		// needs an operation called serialization. This operation declare our objects state.
		// for example turning that objects bytes to string and sending it.
		// then the other computer will use deserialization functions to understand that objects
		// actual state.
	}
*/

/*
	#include <chrono>
	#include <iostream>
	
	int main()
	{
		using namespace std::chrono;
	
		milliseconds ms{ 456 };
	
		std::cout << ms << '\n';
		// output -> 456ms
	
		std::cout << 2min + 17s + 1234ms + 23987us << '\n';
		// output -> 138257987us
	
		constexpr auto x = minutes{ 2 } + seconds{ 17 } +
			milliseconds{ 1234 } + microseconds{ 23987 };
	}
*/

/*
	-> stream objects have a format state.
	-> format states can be changed.
	-> how stream object will be written to console/file/memory 
		will be declared in that objects format state.
*/

/*
	#include <iostream>
	
	int main()
	{
		using namespace std;
	
		cout << (10 > 6) << '\n';	// output -> 1
		// ostream objects(cout) format state will be checked.
		//	by how that object will write bool values.
		//	is it 1 or 0, or is it true or false
	
		cout.setf(ios::boolalpha);
		// its format state has been changed.
	
		cout << (10 > 6) << '\n';	// output -> true
	}
*/

/*
	#include <iostream>
	
	int main()
	{
		using namespace std;
	
		int ival = 47802;
	
		cout << ival << '\n';	// output -> 47802
		// decimal
	
		cout.setf(ios::hex, ios::basefield);
		cout << ival << '\n';	// output -> baba
	
		cout.setf(ios::uppercase);
		cout << ival << '\n';	// output -> BABA
	}
*/

/*
	#include <iostream>
	
	// ostream manipulator
	std::ostream& Boolalpha(std::ostream& os)
	{
		os.setf(std::ios::boolalpha);
	}
	
	int main()
	{
		using namespace std;
	
		cout << boolalpha << (40 > 5);
		// boolalpha is a global ostream manipulator function
		// which is formatting the state of the stream object
		// in its scope with setf()[Set Format] function.
	}
*/

/*
	#include <iostream>
	
	// ostream manipulator
	std::ostream& Boolalpha(std::ostream& os)
	{
		os.setf(std::ios::boolalpha);
		return os;
	}
	
	int main()
	{
		using namespace std;
	
		cout << (40 > 5) << ' ' << boolalpha << (40 > 5);	// output -> 1 true
		// boolalpha is a global ostream manipulator function
		// which is formatting the state of the stream object
		// in its scope with setf()[Set Format] function.
	}
*/

/*
	#include <iostream>

	void func(std::ostream& os)
	{
		// the stream object that comes here will write
		// boolean values 1/0 or true/false ?
		// we need to know the state of the object.
		
		// if we are changing its state inside the scope
		// before scope ends it is better return it back to its old state.
	}
	
	int main()
	{
		using namespace std;
	
		ios_base::fmtflags;			// base class
		basic_ios<char>::fmtflags;
		ios::fmtflags;
	
		cout << typeid(ios::fmtflags).name() << '\n';	// output -> int
	
		auto saved_flags = cout.flags();
		// saved_flags object now holds the cout objects states.
		// we can apply that state to another stream object
	}
*/

/*
	#include <iostream>
	
	int main()
	{
		using namespace std;
	
		std::ios_base::boolalpha;	// -> 00010000 (bitmask)
		// boolalpha is static constexpr fmtflag
	
		cout.setf(ios_base::boolalpha);
		cout.setf(ios::boolalpha);
		// These 2 lines are same
	
		cout.flags(cout.flags() | ios::boolalpha);
		// we are applying BITWISE OR operation to the flags.
		// then using as a new flags.
	
		cout.setf(ios_base::boolalpha);
		cout.flags(cout.flags() | ios::boolalpha);
		// These 2 are lines job are same.
	}
*/

/*
	#include <iostream>
	
	int main()
	{
		using namespace std;
	
		bool b = true;
		cout << b << '\n';	// output -> 1
		// default state of the boolalpha flag is 0(off).
		// boolean values will be written as 0/1.
	
		cout.setf(ios::boolalpha);
		cout << b << '\n';	// output -> true
		// state of the boolalpha flag become 1(on)
		// boolean values will be written as true/false
	
		cout.flags(cout.flags() & ~ios::boolalpha);
		cout.unsetf(ios::boolalpha);
		// Those 2 lines are same
		cout << b << '\n';	// output -> 1
		// if we BITWISE and with any of the ~NOT fmtflag.
		// we will reverse that bit.
		// --> THINK
		// 010101010	-> cout.flags()
		// 000000010	-> ios::boolalpha
		// 000000000	-> ~ios::boolalpha
	
		//	010101010	-> cout.flags()
		//		   0	-> ~ios::boolalpha	(other bits needs to be 1)
		// &----------
		//	010101000	-> will always become 0.
	}
*/

/*
	#include <iostream>
	
	int main()
	{
		using namespace std;
	
		// think about we have 2 or more fmtflags(bitmasks)
		// when we BITWISE OR them and send them as an argument to setf() function
		// we will set both fmtflags at the same time.
	
		cout.setf(ios::boolalpha | ios::uppercase | ios::showbase | ios::showpos);
	}
*/

/*
	boolean(on/off) flags
	---------------------
	boolalpha	
	showpos		
	uppercase
	showbase
	showpoint
	skipws[skip white space] (input) 

	stream.setf(showpos | showpoint);
	stream.unsetf(showpos | showpoint);
*/

/*
	#include <iostream>
	
	int main()
	{
		using namespace std;
	
		cout << 1234 << '\n';	// output -> 1234
		cout.setf(ios::showpos);
		cout << 1234 << '\n';	// output -> +1234
	}
*/

/*
	#include <iostream>
	
	int main()
	{
		using namespace std;
	
		cout.setf(ios::hex, ios::basefield);
	
		cout << 47802 << '\n';	// output -> baba
		cout.setf(ios::uppercase);
		cout << 47802 << '\n';	// output -> BABA
		cout.setf(ios::showbase);
		cout << 47802 << '\n';	// output -> 0XBABA
	}
*/

/*
	#include <iostream>
	
	void func(std::ostream& os)
	{
		os << "boolalpha : "
			<< (os.flags() & std::ios::boolalpha ? "set" : "unset") << '\n';
	
		os << "uppercase : "
			<< (os.flags() & std::ios::uppercase ? "set" : "unset") << '\n';
	
		os << "showpos : "
			<< (os.flags() & std::ios::showpos ? "set" : "unset") << '\n';
	
		os << "showpoint : "
			<< (os.flags() & std::ios::showpoint ? "set" : "unset") << '\n';
	
		os << "showbase : "
			<< (os.flags() & std::ios::showbase ? "set" : "unset") << '\n';
	}
	
	int main()
	{
		func(std::cout);
		// output ->
		//	boolalpha: unset
		//	uppercase : unset
		//	showpos : unset
		//	showpoint : unset
		//	showbase : unset
	
		std::cout.setf(std::ios::boolalpha | std::ios::uppercase);
		func(std::cout);
		// output ->
		//	boolalpha: set
		//	uppercase : set
		//	showpos : unset
		//	showpoint : unset
		//	showbase : unset
	}
*/

/*
	#include <iostream>
	
	// RAII idiom for fmtflags
	class fmguard {
	public:
		fmguard(std::ostream& os) : m_os{os}, m_flags{os.flags()} {}
	
		~fmguard()
		{
			m_os.flags(m_flags);
		}
	private:
		std::ostream& m_os;
		std::ios::fmtflags m_flags;
	};
	
	
	// We want to use the old format state of the stream object
	// when we reach the end of foo() functions scope.
	void foo(std::ostream& os)
	{
		auto fflag = os.flags();
	
		// code changes stream objects state(flags)
		// code changes stream objects state(flags)
		// ...
		// code throws an exception
	
		os.flags(fflag);
		// If an exception occurs inside of the function we can not
		// return stream objects old state.
	}
	
	void foo_RAII(std::ostream& os)
	{
		fmguard myguard{ os };
	
		// code changes stream objects state(flags)
	
		// If an exception occurs inside of the function
		// in stack unwinding phase fmguard classes
		// destructor will be called.
		// stream objects state will return to its old state.
	}
*/

/*
	field flags
	-------------
	hex - dec - oct			| basefield
	left - right - internal | adjustfield
	fixed - scientific		| floatfield

*/

/*
	hex - dec - oct	| basefield
	---------------------------
	hex ->	100
	oct ->	010
	dec ->	001

	If we want to use oct, we first need to 000 all bits 
	then manipulate the oct bit.
*/

/*
	#include <iostream>
	#include <bitset>
	
	int main()
	{
		using namespace std;
	
		cout << bitset<32>{ ios::basefield } << '\n';	
		// output -> 00000000000000000000111000000000
		cout << bitset<32>{ ios::hex } << '\n';;		
		// output -> 00000000000000000000100000000000
		cout << bitset<32>{ ios::oct } << '\n';;		
		// output -> 00000000000000000000010000000000
		cout << bitset<32>{ ios::dec } << '\n';;		
		// output -> 00000000000000000000001000000000
	
		// ios::basefield is the bitmask for 0'ing out all the hex, oct, dec bits
	
		// 1. BITWISE AND with ~ios::basefield made all bits(hex, oct, dec) 0'ed out.
		// 2. BITWISE OR with ios::hex will set the hex bit.
	
		cout << 47802 << '\n';	// output -> 47802
		// default is decimal (dec bit is set)
	
		cout.setf(ios::hex, ios::basefield);
		cout << 47802 << '\n';	// output -> baba
	
		cout.setf(ios::oct, ios::basefield);
		cout << 47802 << '\n';	// output -> 135272
	
		cout.setf(ios::dec, ios::basefield);
		cout << 47802 << '\n';	// output -> 47802
	}
*/

/*
	#include <iostream>
	
	void print_state(std::ostream& os)
	{
		std::cout << "hex bit : " << (os.flags() & std::ios::hex ? "set" : "unset") << '\n';
		std::cout << "oct bit : " << (os.flags() & std::ios::oct ? "set" : "unset") << '\n';
		std::cout << "dec bit : " << (os.flags() & std::ios::dec ? "set" : "unset") << '\n';
	}
	
	int main()
	{
		using namespace std;
	
		print_state(cout);
		// output ->
		//	hex bit : unset
		//	oct bit : unset
		//	dec bit : set
	
		cout.setf(ios::hex, ios::basefield);
		print_state(cout);
		// output ->
		//	hex bit : set
		//	oct bit : unset
		//	dec bit : unset
	
		cout.setf(ios::oct, ios::basefield);
		print_state(cout);
		// output ->
		//	hex bit : unset
		//	oct bit : set
		//	dec bit : unset
	}
*/

/*
	fixed - scientific | floatfield
	depends on the number	(00)
	hex-float				(11)
*/

/*
	#include <iostream>
	
	void print_state(std::ostream& os)
	{
		std::cout << "fixed      : " << 
								(os.flags() & std::ios::fixed ? "set" : "unset") << '\n';
		std::cout << "scientific : " << 
								(os.flags() & std::ios::scientific ? "set" : "unset") << '\n';
	}
	
	int main()
	{
		using namespace std;
	
		print_state(cout);
		// output ->
		//	fixed: unset
		//	scientific : unset
	
		// depends on the number, it will be written as fixed or scientific.(default state)
		cout << 2.3 << '\n' << 57625635263.91238 << '\n';
		// output ->
		//	2.3				-> fixed
		//	5.76256e+10		-> scientific
	
	
		cout.setf(ios::fixed, ios::floatfield);
		print_state(cout);
		// output ->
		//	fixed: set
		//	scientific : unset
		cout << 2.3 << '\n' << 57625635263.91238 << '\n';
		// output ->
		//	2.300000			-> fixed
		//	57625635263.912376	-> fixed
	
	
		cout.setf(ios::scientific, ios::floatfield);
		print_state(cout);
		// output ->
		//	fixed: unset
		//	scientific : set
		cout << 2.3 << '\n' << 57625635263.91238 << '\n';
		// output ->
		//	2.300000e+00	-> scientific
		//	5.762564e+10	-> scientific
	
	
		cout.setf(ios::fixed | ios::scientific);	// hex-float
		print_state(cout);
		// output ->
		//	fixed: set
		//	scientific : set
		cout << 2.3 << '\n' << 57625635263.91238 << '\n';
		// output ->
		//	0x1.2666666666666p+1	-> hex-float
		//	0x1.ad582d37fd323p+35	-> hex-float
	}
*/

/*
	left - right - internal | adjustfield

	-> .width() member function to get and set the width.
	-> fill() member function to get and set the fill character.

	???????435 right
	435??????? left

	+      981
	-    35678
	+		12	internal
*/

/*
	#include <iostream>
	#include <iomanip>
	
	int main()
	{
		using namespace std;
	
		cout.width(20);
		// default width is 0
	
		cout << "hello" << "world" << '\n';
		// output ->                helloworld
		// default ios::right
	
		cout.setf(ios::left, ios::adjustfield);
		cout << "hello" << "world" << '\n';
		// output -> helloworld
	}
*/

/*
	#include <iostream>
	#include <iomanip>
	
	int main()
	{
		using namespace std;
	
		cout.width(3);
	
		// if width is smaller than the width of the object
		// it will act like 0.
	
		int ival{ 879'376'293 };
		cout << ival << '\n';
		// output -> 879376293
	
		cout.width(20);
		cout << ival << '\n';
		// output ->            879376293
	}
*/

/*
	#include <iostream>
	#include <iomanip>
	
	int main()
	{
		using namespace std;
	
		cout.width(20);
	
		int ival{ 879'376'293 };
		cout << ival << "hello" << '\n';
		// output ->            879376293hello
		// ival will be inside 20 width field and aligned to right
	}
*/

/*
	#include <iostream>
	#include <iomanip>
	
	int main()
	{
		using namespace std;
	
		// width is TEMPORARY and its default value is 0.
		cout.width(20);
		auto n = cout.width();
		std::cout << "n = " << n << '\n';
	
		n = cout.width();
		std::cout << "n = " << n << '\n';
		// output ->
		//                 n = 20
		//	n = 0
	}
*/

/*
	#include <iostream>
	#include <iomanip>
	
	class Triple {
	public:
		Triple(int x, int y, int z) : mx{ x }, my{ y }, mz{ z } {}
	
		friend std::ostream& operator<<(std::ostream& os, const Triple& t)
		{
			return os << "(" << t.mx << ", " << t.my << ", " << t.mz << ")\n";
		}
	private:
		int mx{}, my{}, mz{};
	};
	
	int main()
	{
		using namespace std;
	
		Triple trip{ 3, 8, 12 };
		cout << trip;
		// output -> (3, 8, 12)
	
		cout.width(20);
		cout.setf(ios::left, ios::adjustfield);
		cout << trip;
		// output -> (                   3, 8, 12)
	
		// There are 7 stream jobs in this operation.
		// 1. "("
		// 2. t.mx
		// 3. ", "
		// 4. t.my
		// 5. ", "
		// 6. t.mz
		// 7. ")\n"
		// But after the first one width() will become from 20 -> 0.
	}
*/

/*
	#include <iostream>
	#include <iomanip>
	#include <sstream>
	
	class Triple {
	public:
		Triple(int x, int y, int z) : mx{ x }, my{ y }, mz{ z } {}
	
		friend std::ostream& operator<<(std::ostream& os, const Triple& t)
		{
			std::ostringstream oss;
			oss << "(" << t.mx << ", " << t.my << ", " << t.mz << ")\n";
	
			return os << oss.str();
		}
	private:
		int mx{}, my{}, mz{};
	};
	
	int main()
	{
		using namespace std;
	
		Triple trip{ 3, 8, 12 };
		cout << trip;
		// output -> (3, 8, 12)
	
		// If we want to apply width() for all of the stream operations.
		// We can write the characters to memory, convert to string and return
		// then apply width(20) to that string in only 1 operation.
	
		cout.width(20);
		cout << trip;
		// output ->          (3, 8, 12)
	}
*/

/*
	#include <iostream>
	
	int main()
	{
		using namespace std;
	
		auto c = cout.fill();
		cout << "c = " << static_cast<int>(c) << '\n';
		// output -> 32 (ASCII of space character)
	
		cout.fill('$');
		cout.width(30);
		cout.setf(ios::left, ios::adjustfield);
		cout << "hello";
		// output -> hello$$$$$$$$$$$$$$$$$$$$$$$$$
	}
*/

/*
	// formatting with setf() or unsetf() functions are creating verbose code
	// also chaining is not possible. (bitwise or can be done)
	// solution is ostream manipulators.

	#include <iostream>

	int main()
	{
		using namespace std;
	
		int x{ 354 };
		int y{ 47802 };
		int z{ 98123 };
	
		cout << x << " ";
	
		cout.setf(ios::hex, ios::basefield);
		cout.setf(ios::uppercase);
		cout.setf(ios::showbase);
		cout << y << " ";
	
		cout.setf(ios::oct, ios::basefield);
		cout << z << "\n";
		// output -> 354 0XBABA 0277513
	}
*/

/*
	#include <iostream>
	
	std::ostream& Boolalpha(std::ostream& os)
	{
		os.setf(std::ios::boolalpha);
		return os;
	}
	
	std::ostream& NoBoolalpha(std::ostream& os)
	{
		os.unsetf(std::ios::boolalpha);
		return os;
	}
	
	int main()
	{
		using namespace std;
	
		cout << (10 > 5) << ' ' << Boolalpha << (10 > 5) << NoBoolalpha << ' ' << (10 > 5) << '\n';
		// output -> 1 true 1
	
		// Standart library ostream manipulator functions
		cout << (10 < 5) << ' ' << boolalpha << (10 < 5) << noboolalpha << ' ' << (10 < 5) << '\n';
		// output -> 0 false 0
	}
*/

/*
	#include <iostream>

	std::ostream& Hex(std::ostream& os)
	{
		os.setf(std::ios::hex, std::ios::basefield);
		return os;
	}

	std::ostream& Dec(std::ostream& os)
	{
		os.setf(std::ios::dec, std::ios::basefield);
		return os;
	}

	std::ostream& Oct(std::ostream& os)
	{
		os.setf(std::ios::oct, std::ios::basefield);
		return os;
	}

	std::ostream& MyManipulator(std::ostream& os)
	{
		os.setf(std::ios::hex, std::ios::basefield);
		os.setf(std::ios::uppercase | std::ios::showbase);
		return os;
	}

	int main()
	{
		using namespace std;

		cout << Hex << 47802 << ' ' << Oct << 47802 << ' ' << Dec << 47802 << '\n';
		// output -> baba 135272 47802

		// Standart library ostream manipulator functions
		cout << hex << 47802 << ' ' << oct << 47802 << ' ' << dec << 47802 << '\n';
		// output -> baba 135272 47802

		std::cout << 47802 << MyManipulator << " " << 47802 << '\n';
		// output -> 47802 0XBABA
	}
*/

/*
	#include <iostream>
	
	int main()
	{
		using namespace std;
	
		cout.width(20);
		cout << left << 123 << 56 << '\n';
		// output -> 123                 56
	
		cout.width(20);
		cout << right << 123 << 56 << '\n';
		// output ->                  12356
	
	
		double dval = 243.2376483;
		cout << fixed << dval << '\n' << scientific << dval << '\n' << hexfloat << dval << '\n';
		// output ->
		//	243.237648
		//	2.432376e+02
		//	0x1.e679ad09b8e66p+7
	}
*/

/*
	#include <iostream>
	
	int main()
	{
		using namespace std;
	
		auto n = cout.precision();
		// default precision is 6
		cout << "n = " << n << '\n';
		// output -> n = 6
	
		cout << fixed << 345.8723938 << '\n';	// output -> 345.872394
		cout.precision(10);
		cout << fixed << 345.8723938 << '\n';	// output -> 345.8723938000
	}
*/

/*
	#include <iomanip>	//setw, setfill, setprecision
	#include <iostream>
	
	int main()
	{
		using namespace std;
	
		int ival = 5;
		double dval = 8723.12391893;
	
		cout << setfill('*') << left << setw(12) << ival << '\n';
		// output -> 5***********
		cout << setprecision(15) << fixed << dval << '\n';
		// output -> 8723.123918929999491
	}
*/

/*
	#define _CRT_SECURE_NO_WARNINGS
	#include <iomanip>
	#include <iostream>
	#include <sstream>
	#include <ctime>
	
	std::string get_current_date_time()
	{
		using namespace std;
	
		auto timer = time(nullptr);
		auto tptr = localtime(&timer);
	
		ostringstream oss;
		oss.fill('0');
		oss << tptr->tm_year + 1900 << '_' << setw(2) <<  tptr->tm_mon + 1 << '_' << setw(2)
			<< tptr->tm_mday << '_' << setw(2) << tptr->tm_hour << '_' << setw(2) << tptr->tm_min << '_'
			<< setw(2) << tptr->tm_sec << ".txt";
	
		return oss.str();
	}
	
	int main()
	{
		using namespace std;
	
		// yyyy_mm_dd_hh_mm_ss.txt
	
		cout << '|' << get_current_date_time() << "|\n";
	}
*/

/*
	// writing parameter manipulator

	#include <iostream>
	#include <string>
	
	class ns {
	public:
		ns() = default;
		explicit ns(int val) : m_space{val} {}
	
		friend std::ostream& operator<<(std::ostream& os, const ns& obj)
		{
			auto n = obj.m_space;
			while (n--)
				os.put(' ');
	
			return os;
		}
	private:
		int m_space{};
	};
	
	// ns will be a manipulator add spaces to end of the stream object
	int main()
	{
		using namespace std;
	
		int x{ 23 };
		string str{ "hello" };
		int y{ 5746 };
	
		cout << x << ns(5) << str << ns(10) << y << ns(20) << "world";
		// output -> 23     hello          5746                    world
	}
*/

/*
	#include <iostream>
	
	int main()
	{
		int x, y, z;
	
		std::cout << "write 3 integers : ";	// input -> 41 41 41
		std::cin >> std::hex >> x >> std::oct >> y >> std::dec >> z;
	
		std::cout << "x = " << x << '\n';
		std::cout << "y = " << y << '\n';
		std::cout << "z = " << z << '\n';
		// output ->
		//	x = 65
		//	y = 33
		//	z = 41
	}
*/

/*
	#include <iostream>
	#include <iomanip>
	
	int main()
	{
		using namespace std;
		char str[20];
	
		std::cout << "wrote something: ";	// input -> helloworld
		cin >> setw(5) >> str;
	
		cout << str << '\n';	// output -> hell
		// null character included.
	}
*/

/*
	#include <iostream>
	
	class Myclass {
	public:
		Myclass() = default;
		Myclass(int x) : mval{x} {}
		friend std::ostream& operator<<(std::ostream& os, const Myclass& m)
		{
			return os << "(" << m.mval << ")";
		}
	private:
		int mval{};
	};
	
	template <typename T>
	void func(T x, T y)
	{
		std::cout << x << " " << y << '\n';
	}
	
	int main()
	{
		int ival = 56;
		func(ival, {});	// output -> 56 0
	
		int x = int{ 20 };
		int y = int{};	// value initialize
		int z = {};
	
		std::cout << Myclass{ 35 } << '\n';		// output ->(35)
		std::cout << Myclass{} << '\n';			// output ->(0)
	
		func(Myclass{ 35 }, {});				// output -> (35) (0)
		// T becomes Myclass and Myclass object can be default initialize.
	}
*/

/*
	#include <iostream>
	#include <sstream>
	#include <algorithm>
	
	int main()
	{
		using namespace std;
	
		ostringstream oss;
	
		for (int i = 0; i < 10; ++i){
			oss << i << '.';
		}
	
		auto s = oss.str();
		cout << '|' << s << "|\n";	// output -> |0.1.2.3.4.5.6.7.8.9.|
	
		sort(s.begin(), s.end());
		cout << '|' << s << "|\n";	// output -> |..........0123456789|
	
		reverse(s.begin(), s.end());
		cout << '|' << s << "|\n";	// output -> |9876543210..........|
	}
*/

/*
	#include <iostream>
	#include <sstream>
	#include <bitset>
	
	int main()
	{
		using namespace std;
	
		ostringstream oss;
	
		int ival = 567;
	
		oss << bitset<16>(ival) << ival;
		cout << oss.str() << '\n';	// output -> 0000001000110111567
	}
*/

/*
	#include <iostream>
	#include <sstream>
	#include <bitset>
	#include <iomanip>
	
	int main()
	{
		using namespace std;
	
		ostringstream oss;
		oss << setfill('0');
	
		for (int i = 1; i < 5; ++i)
		{
			oss << "hello_" << setw(2) << i << ".txt ";
			cout << oss.str() << '\n';
		}
		// output ->
		//	hello_01.txt
		//	hello_01.txt hello_02.txt
		//	hello_01.txt hello_02.txt hello_03.txt
		//	hello_01.txt hello_02.txt hello_03.txt hello_04.txt
	
	
		for (int i = 1; i < 5; ++i)
		{
			ostringstream oss_2;
			oss_2 << setfill('0');
			oss_2 << "hello_" << setw(2) << i << ".txt ";
			cout << oss_2.str() << '\n';
		}
	
		// output ->
		//	hello_01.txt
		//	hello_02.txt
		//	hello_03.txt
		//	hello_04.txt
	
	
		ostringstream oss_3;
		oss_3 << setfill('0');
	
		for (int i = 1; i < 5; ++i)
		{
			oss_3 << "hello_" << setw(2) << i << ".txt ";
			cout << oss_3.str() << '\n';
			oss_3.str("");
			// parameter overload of str() function.
			// makes stream object empty
		}
	
		// output ->
		//	hello_01.txt
		//	hello_02.txt
		//	hello_03.txt
		//	hello_04.txt
	}
*/

/*
	#include <sstream>
	#include <iostream>
	
	int main()
	{
		using namespace std;
	
		ostringstream oss;
		oss << uppercase << hex << boolalpha;
	
		oss << 47802 << ' ' << (10 > 5);
		cout << oss.str() << '\n';	// output -> BABA true
		// stream format manipulators also working
	}
*/

/*
	#include <sstream>
	#include <string>
	#include <iostream>
	#include <algorithm>
	
	int main()
	{
		using namespace std;
	
		istringstream iss{ "hello world we are live from Izmir" };
		string word;
	
		while (iss >> word) {
			reverse(word.begin(), word.end());
			cout << word << '\n';
		}
		// output ->
		//	olleh
		//	dlrow
		//	ew
		//	era
		//	evil
		//	morf
		//	rimzI
	}
*/

/*
	#include <sstream>
	#include <string>
	#include <set>
	#include <iostream>
	
	int main()
	{
		using namespace std;
	
		string line{ "ccc bbb eee zzz kkk ccc eee ooo ddd eee bbb" };
		istringstream iss(line);
	
		string word;
		multiset<string> myset;
	
		while (iss >> word){
			myset.insert(std::move(word));
		}
	
		for (const auto& s : myset)
			cout << s << "\n";
		// output ->
		//	bbb
		//	bbb
		//	ccc
		//	ccc
		//	ddd
		//	eee
		//	eee
		//	eee
		//	kkk
		//	ooo
		//	zzz
	}
*/

/*
	#include <sstream>
	
	int main()
	{
		using namespace std;
	
		stringstream ss;	// both input and output operation
		ss << "12345";
		ss >>
	}
*/

/*
	#include <iostream>
	
	int main()
	{
		using namespace std;
	
		ostream os{ cout.rdbuf()};
		// initializing an ostream object with another ostream objects stream buffer.
		os << hex << boolalpha << uppercase << showbase << showpoint;
	
		cout << 47802 << ' ' << (10 > 5) << ' ' << 4. << '\n';
		// output -> 47802 1 4
		os << 47802 << ' ' << (10 > 5) << ' ' << 4. << '\n';
		// output -> 0XBABA true 4.00000
	}
*/

/*
	Condition state
	-------------------
	cin.good()
	cin.bad()
	cin.fail()
	cin.operator!()

	static constexpr data members of base class (iostate manipulators)
	ios::goodbit
	ios::badbit
	ios::failbit
	ios::eofbit
*/

/*
	#include <iostream>
	
	int main()
	{
		using namespace std;
	
		std::cout << typeid(ios::iostate).name() << '\n';
		// output -> int
	
		cin.eof();
		// returns bool and get the stream is eof state or not
	
		cin.fail();
		// returns bool and get if the stream is failed state or not.
	}
*/

/*
	#include <iostream>
	
	int main()
	{
		using namespace std;
	
		int x;
		std::cout << "write an integer: ";
		cin >> x;
	
		if (cin.good())
			cout << "no fail, streams condition is good state.\n";
		else
			cout << "fail, stream is not in a good state.\n";
	
		// input -> 5, output -> no fail, streams condition is good state.
		// input -> hello, output -> fail, stream is not in a good state.
	}
*/

/*
	#include <iostream>
	
	int main()
	{
		using namespace std;
	
		int x;
		std::cout << "write an integer: ";
		cin >> hex >> x;
	
		if (cin.good())
			cout << "no fail, streams condition is good state.\n";
		else
			cout << "fail, stream is not in a good state.\n";
	
		// input -> 5, output -> no fail, streams condition is good state.
		// input -> apple, output -> no fail, streams condition is good state.
		// (a is valid in hexadecimal system [0-9 & A-F])
	}
*/

/*
	#include <iostream>
	
	int main()
	{
		using namespace std;
	
		int x;
		std::cout << "write an integer: ";
		cin >> x;
	
		// cin.good(); and cin.operator bool() functions acting same.
	
		if (cin.operator bool())
			cout << "no fail, streams condition is good state.\n";
		else
			cout << "fail, stream is not in a good state.\n";
		// input -> 5, output -> no fail, streams condition is good state.
		// input -> hello, output -> fail, stream is not in a good state.
	}
*/

/*
	#include <bitset>
	#include <iostream>
	
	int main()
	{
		using namespace std;
	
		cout << bitset<16>(ios::badbit) << '\n';	// output -> 0000000000000100
		cout << bitset<16>(ios::failbit) << '\n';	// output -> 0000000000000010
		cout << bitset<16>(ios::eofbit) << '\n';	// output -> 0000000000000001
		cout << bitset<16>(ios::goodbit) << '\n';	// output -> 0000000000000000
	}
*/

/*
	#include <iostream>
	
	int main()
	{
		using namespace std;
	
		if (cin.rdstate() == 0)
			// checking if no bits are set
	
		if (cin.rdstate() & ios::badbit)	// BITWISE AND with ios::badbit
		// checking if ios::badbit set or not.
	}
*/

/*
	#include <iostream>
	
	int main()
	{
		using namespace std;
	
		int x{};
	
		while (cin >> x)
		{
			cout << x << " * " << x << " = " << x * x << '\n';
		}
		// (cin >> x) returns istream&, and istream object have an operator bool() function
		// which returns true if there is no fail in stream object
	
		// -> while(cin.operator>>(x).operator bool())
		// -> while (cin >> x)
		// Those 2 lines are same.
	
		// output ->
		//	12
		//	12 * 12 = 144
		//	14
		//	14 * 14 = 196
		//	16
		//	16 * 16 = 256
		//	92
		//	92 * 92 = 8464
		//	hello
	}
*/

/*
	#include <iostream>
	
	int main()
	{
		using namespace std;
		cout << boolalpha;
	
		int x{};
	
		cout << "cin.good() : " << cin.good() << '\n';
		cout << "cin.bad() : " << cin.bad() << '\n';
		cout << "cin.fail() : " << cin.fail() << '\n';
		cout << "cin.eof() : " << cin.eof() << '\n';
		// output ->
		//	cin.good() : true
		//	cin.bad() : false
		//	cin.fail() : false
		//	cin.eof() : false
	
	
		cout << "Write an integer : ";
		cin >> x;	// input -> 10
	
		cout << "cin.good() : " << cin.good() << '\n';
		cout << "cin.bad() : " << cin.bad() << '\n';
		cout << "cin.fail() : " << cin.fail() << '\n';
		cout << "cin.eof() : " << cin.eof() << '\n';
		// output ->
		//	cin.good() : true
		//	cin.bad() : false
		//	cin.fail() : false
		//	cin.eof() : false
	
	
		cout << "Write an integer : ";
		cin >> x;	// input -> hello
	
		cout << "cin.good() : " << cin.good() << '\n';
		cout << "cin.bad() : " << cin.bad() << '\n';
		cout << "cin.fail() : " << cin.fail() << '\n';
		cout << "cin.eof() : " << cin.eof() << '\n';
		// output ->
		//	cin.good() : false
		//	cin.bad() : false
		//	cin.fail() : true
		//	cin.eof() : false
	
	
		cout << "Write an integer : ";
		cin >> x;	// input -> ^Z (Ctrl + Z for windows) (Ctrl + D for unix)
	
		cout << "cin.good() : " << cin.good() << '\n';
		cout << "cin.bad() : " << cin.bad() << '\n';
		cout << "cin.fail() : " << cin.fail() << '\n';
		cout << "cin.eof() : " << cin.eof() << '\n';
		// output ->
		//	cin.good() : false
		//	cin.bad() : false
		//	cin.fail() : true
		//	cin.eof() : true
	
		// if there is no memory kind of error will make cin.bad() = true
	}
*/

/*
	#include <iostream>
	#include <string>
	
	int main()
	{
		using namespace std;
		cout << boolalpha;
	
		// if (cin.fail())
		// if (!cin)
		// Those 2 lines are same.
	
		// if (cin)
		// if (cin.good()
		// Those 2 lines are same.
	
		int x{};
	
		while (true){
			cout << "-> write an integer : ";
			cin >> x;
			if (cin.good())
			{
				std::cout << "entered integer is valid\n";
				break;
			}
	
			if (cin.eof()) // (Ctrl+Z)
			{
				std::cout << "not entered, buffer is empty\n";
				cin.clear();
			}
	
			if (cin.fail())
			{
				std::cout << "entered value is not valid\n";
				cin.clear();	// BUFFER is not become empty. Still holds the not valid value.
				string str;
				cin >> str;
				cout << str << " is not a valid integer\n";
			}
		}
		// output ->
		//	-> write an integer : HELLO
		//	entered value is not valid
		//	HELLO is not a valid integer
		//	-> write an integer : ^Z
		//	not entered, buffer is empty
		//	-> write an integer : 12
		//	entered integer is valid
	}
*/

/*
	#include <iostream>
	#include <string>
	#include <algorithm>
	
	int main()
	{
		using namespace std;
	
		string sline;
		while (getline(cin, sline)) {
			reverse(sline.begin(), sline.end());
			cout << sline << '\n';
		}
		// output ->
		//	hello world
		//	dlrow olleh
		//	we are live
		//	evil era ew
		//	from Izmir
		//	rimzI morf
	}
*/

/*
	#include <iostream>
	
	int main()
	{
		using namespace std;
	
		int x = 10;
		cout << "write an integer : ";
		cin >> x;	// input hello
	
		cout << (cin ? "good" : "no good") << '\n';	// output -> no good
	
		cin.clear();
		cin.clear(ios::goodbit);
		// These 2 lines are same
		// default argument is ios::goodbit
	
		cout << (cin ? "good" : "no good") << '\n';	// output -> good
	
		// clear() member function returns stream object to a good state
	}
*/

/*
	#include <iostream>
	
	int main()
	{
		using namespace std;
	
		cout << boolalpha;
	
		cin.clear(ios::eofbit);
		cout << "eof bit   : " << cin.eof() << '\n';
		cout << "good bit  : " << cin.good() << '\n';
		cout << "fail bit  : " << cin.fail() << '\n';
		cout << "bad bit   : " << cin.bad() << '\n';
		cout << "op bool() : " << cin.operator bool() << '\n';
		cout << "op !()    : " << cin.operator !() << '\n';
	
		// output ->
		//	eof bit   : true
		//	good bit  : false
		//	fail bit  : false
		//	bad bit   : false
		//	op bool() : true
		//	op !()    : false
	}
*/

/*
	#include <iostream>
	
	int main()
	{
		using namespace std;
	
		cout << boolalpha;
	
		cin.clear(ios::failbit | ios::eofbit | ios::badbit);
	
		cin.setstate(ios::failbit);
		cin.setstate(ios::eofbit);
		cin.setstate(ios::badbit);
		// We can set ios states individually with setstate() member function
		// or we can use clear() member function to set one or mor ios states with BITWISE OR.
	
		cout << "eof bit   : " << cin.eof() << '\n';
		cout << "good bit  : " << cin.good() << '\n';
		cout << "fail bit  : " << cin.fail() << '\n';
		cout << "bad bit   : " << cin.bad() << '\n';
		cout << "op bool() : " << cin.operator bool() << '\n';
		cout << "op !()    : " << cin.operator !() << '\n';
		// output ->
		//	eof bit : true
		//	good bit : false
		//	fail bit : true
		//	bad bit : true
		//	op bool() : false
		//	op !() : true
	}
*/

/*
	#include <iostream>
	#include <string>
	
	int main()
	{
		using namespace std;
	
		int x{};
	
		while (std::cout << "enter an integer : " && !(std::cin >> x)) {
			if (cin.eof()) {
				std::cout << "you have not entered anything!\n";
				cin.clear();
			}
			else{
				cin.clear();
				string line;
				getline(cin, line);
				cout << '[' << line << "] is not a valid integer!\n";
			}
		}
	
		cout << "your number is : " << x << '\n';
	}
*/

/*
	#include <iterator>
	#include <iostream>
	
	int main() {
		using namespace std;
	
		istream_iterator<int> iter{ cin };
		istream_iterator<int> end{};	// default constructed
	
		int x{};
		while (iter != end) {
			x = *iter;
			cout << "x = " << x << '\n';
			++iter;
		}
		// for to check if there is an int left stream object
		// we compare our iterator with a default constructed another same type iterator.
	}
*/

/*
	#include <iterator>
	#include <iostream>
	#include <fstream>
	#include <vector>
	#include <string>
	
	int main() {
		using namespace std;
	
		ifstream ifs{ "out.txt" };
	
		if (!ifs) {
			cerr << "file can not be opened!\n";
			return 1;
		}
	
		// out.txt -> hello world we are live from Izmir
	
		vector<string> svec{ istream_iterator<string>{ifs}, istream_iterator<string>{} };
		//	vector<string> svec{ istream_iterator<string>{ifs}, {} };
		// Those 2 lines are same, range constructor of vector<string>
	
		cout << "svec.size() = " << svec.size() << '\n';	// output -> svec.size() = 7
	
		copy(svec.begin(), svec.end(), ostream_iterator<string>(cout, " - "));
		// output -> hello - world - we - are - live - from - Izmir -
	}
*/

/*
	#include <sstream>
	#include <iostream>
	#include <vector>
	#include <numeric>
	#include <string>
	
	int main()
	{
		using namespace std;
	
		istringstream iss{ "12 34 56 23 45 94 20 68" };
	
		copy(istream_iterator<int>(iss), {}, ostream_iterator<int>(cout, " - "));
		// output -> 12 - 34 - 56 - 23 - 45 - 94 - 20 - 68 -
	
		cout << '\n';
	
		istringstream iss_2{ "14 36 58 25 47 96 22 70" };
		vector<int> ivec;
		copy(istream_iterator<int>(iss_2), {}, back_inserter(ivec));
		copy(ivec.begin(), ivec.end(), ostream_iterator<int>(cout, " - "));
		// output -> 14 - 36 - 58 - 25 - 47 - 96 - 22 - 70 -
	
		cout << '\n';
		istringstream iss_3{ "11 22 33 44 55 66 77 88 99" };
		cout << accumulate(istream_iterator<int>{iss_3}, {}, 0) << '\n';
		// output -> 495
	
		istringstream iss_4{ "11 22 33 44 55 66 77 88 99" };
		string s{};
		cout << accumulate(istream_iterator<string>{iss_4}, {}, s) << '\n';
		// output -> 112233445566778899
	}
*/

/*
	// finding first word starts with letter 'h'
	
	#include <fstream>
	#include <iostream>
	#include <algorithm>
	#include <string>
	
	int main()
	{
		using namespace std;
	
		// out.txt -> world we are live hello from Izmir
	
		ifstream ifs{ "out.txt" };
		if (!ifs) {
			cerr << "file can not be opened!\n";
			return 1;
		}
	
		istream_iterator<string> end;
		char c = 'h';
		auto iter = find_if(istream_iterator<string>{ifs}, end, [c](const string& s) {
			return s[0] == c;
			});
	
		if (iter != end)
			cout << "found : " << *iter << '\n';	// output -> found : hello
		else
			cout << "can not found\n";
	}
*/

/*
	// write the biggest number to console comes from istream object(cin)
	// write the total of the integers
	
	#include <iostream>
	#include <algorithm>
	#include <numeric>
	#include <string>
	
	int main()
	{
		using namespace std;
	
		cout << "enter integers : ";
	
		cout << *max_element(istream_iterator<int>{cin}, {}) << '\n';
		cout << accumulate(istream_iterator<int>{cin}, {}, 0) << '\n';
		// Check last two lines one by one and use -> ( Ctrl^Z + Enter)
	}
*/

/*
	// from cppreference.com
	#include <iostream>
	#include <algorithm>
	#include <iterator>
	#include <numeric>
	#include <sstream>
	
	int main()
	{
		using namespace std;
	
		istringstream str("0.1 0.2 0.3 0.4 0.5");
	
		partial_sum(istream_iterator<double>(str),
			istream_iterator<double>(),
			ostream_iterator<double>(cout, " "));
	
		istringstream str2("1 3 5 7 8 9 10");
	
		auto it = find_if(istream_iterator<int>(str2),
			istream_iterator<int>(),
			[](int i) {return i % 2 == 0; });
	
		if (it != istream_iterator<int>())
			cout << "\nThe first even number is : " << *it << "\n";
		// " 9 10" left in the stream
	
		// output ->
		//	0.1 0.3 0.6 1 1.5
		//	The first even number is : 8
	}
*/

/*
	--------------------------------
	| file input/output operations |
	--------------------------------
*/

/*
	#include <fstream>
	#include <string>
	#include <iostream>
	
	int main()
	{
		using namespace std;
	
		// ofstream -> only write to a file
		// ifstream -> only read from file
		// fstream	-> both read and write from file
	
	
		ofstream ofs1("out.txt");
		string filename{ "hello.txt" };
		ofstream ofs2(filename);
		// 2 different constructor CString and std::string
	
	
		// open_mode masks
		// --------------------------------------------------------------------------
		// ios::in			-> read
		// ios::out			-> write
		// ios::app			-> append / write will be applied to the end of the file
		// ios::trunc		-> truncate the file
		// ios::binary		-> open in binary mode
		// ios::ate			-> attend / file pointer will be at the end of the file
	
		ofstream ofs3("place.txt", ios::out | ios::trunc);
		//	ofstream ofs3("place.txt");
		// These 2 lines are same, default argument is (ios::out | ios::trunc)
	
		if (ofs3.fail()) {
			std::cerr << "place.txt can not be created\n";
			return 1;
		}
	
		ofs3 << "space\n";
		ofs3 << "galaxy\n";
		ofs3 << "universe\n";
	
		for (int i = 0; i < 10; ++i) {
			ofs3 << i << " ";
		}
	
		// place.txt ->
		//	space
		//	galaxy
		//	universe
		//	0 1 2 3 4 5 6 7 8 9
	}
*/

/*
	#include <fstream>
	#include <iostream>
	
	int main()
	{
		using namespace std;
	
		ofstream ofs("out.txt");
		// if exists it will be truncated, if not exist it will be created
	
		ofstream ofs2;	// default constructed
	
		cout << boolalpha;
		cout << ofs.is_open() << '\n';	// output -> true
		cout << ofs2.is_open() << '\n';	// output -> faLse
	
		ofs.close();
		cout << ofs.is_open() << '\n';	// output -> false

		// fstream objects are RAII objects.
		// if you do not close it will close the file at ofstream objects destructor.
	}
*/

/*
	#include <fstream>
	#include <iostream>
	
	int main()
	{
		using namespace std;
	
		ofstream ofs;
	
		ofs.open("out.txt");
		ofs << "hello world";
		ofs.close();
		// out.txt -> hello world
	
		ofs.open("place.txt");
		ofs << "Istanbul";
		// place.txt -> Istanbul
	}
*/

/*
	#include <fstream>
	#include "nutility.h"
	
	int main()
	{
		using namespace std;
	
		ofstream ofs("out.txt");
	
		for (int i = 0; i < 10; ++i) {
			ofs << rname() + ' ' + rtown() << '\n';
		}
		// out.txt ->
		//	tuncer sivas
		//	sezer artvin
		//	sade gaziantep
		//	belgin giresun
		//	mahir malatya
		//	askin denizli
		//	zubeyde yalova
		//	nazli ordu
		//	azize cankiri
		//	selenay samsun
	}
*/

/*
	#include <fstream>
	#include <algorithm>
	#include <vector>
	#include <string>
	#include "nutility.h"
	
	int main()
	{
		using namespace std;
	
		vector<string> svec;
		rfill(svec, 10, rtown);
		cout << "svec.size() = " << svec.size() << '\n';
		// output -> svec.size() = 10
	
		ofstream ofs("out.txt");
	
		copy(svec.begin(), svec.end(), ostream_iterator<string>{ofs, "\n"});
		// out.txt ->
		//	adiyaman
		//	mugla
		//	yalova
		//	karabuk
		//	sanliurfa
		//	bartin
		//	canakkale
		//	kastamonu
		//	tekirdag
		//	kahramanmaras
	}
*/

/*
	#include "file.h"
	#include "nutility.h"
	#include <iostream>
	
	int main()
	{
		using namespace std;
	
		auto ofs = create_text_file("out.txt");
	
		// ofs << hex << uppercase << showbase;
	
		for (int i = 0; i < 10; ++i){
			ofs << Irand{ 0, 10'000 }() << '\n';
		}
		// output ->
		//	9624
		//	7734
		//	8165
		//	7531
		//	2463
		//	4898
		//	1069
		//	9883
		//	2133
		//	8817
	
		try
		{
			auto ifs_2 = open_text_file("nofile.txt");
		}
		catch (const std::exception& ex)
		{
			std::cout << "exception caught : " << ex.what() << '\n';
		}
		// output -> exception caught : nofile.txt can not be opened!
	}
*/

/*
	#include "file.h"
	#include <iostream>
	#include "nutility.h"
	
	int main()
	{
		using namespace std;
	
		auto ifs = open_text_file("out.txt");
		int ival;
		
		// out.txt ->
		//	9624
		//	7734
		//	8165
		//	7531
		//	2463
		//	4898
		//	1069
		//	9883
		//	2133
		//	8817

		while (ifs >> ival) {
			if (isprime(ival))
				cout << ival << " ";
		}
		// output -> 1069 9883
	}
*/

/*
	#include <algorithm>
	#include <fstream>
	#include "file.h"
	#include <iostream>
	
	int main()
	{
		using namespace std;
	
		auto ifs = open_text_file("out.txt");
	
		// writing values mod3 = 0
	
		int val = 3;
		copy_if(istream_iterator<int>{ifs}, {}, ostream_iterator<int>{cout, " "},
			[val](int x) {
				return x % val == 0;
			});
		// output -> 9624 7734 2463 2133 8817
	}
*/

/*
	#include <iostream>
	#include <fstream>
	#include "file.h"
	#include "nutility.h"
	#include <string>
	#include <vector>
	#include <algorithm>
	
	int main()
	{
		using namespace std;
	
		auto ofs = create_text_file("out.txt");
	
		for (int i = 0; i < 10; ++i) {
			ofs << rname() << " " << rfname() << " " << rtown() << '\n';
		}
		ofs.close();
		// out.txt ->
		//	zamir aksakal bursa
		//	tayyar yaradan sanliurfa
		//	halime altindag bolu
		//	necmettin soysalan denizli
		//	arda oltu isparta
		//	melih canlikaya sakarya
		//	emre sefiloglu antalya
		//	pelin uluocak canakkale
		//	ferhat portakal kutahya
		//	tayfun karakuzu denizli
	
		auto ifs = open_text_file("out.txt");
	
		string sline;
		vector<string> svec;
		while (getline(ifs, sline)) {
			svec.push_back(std::move(sline));
		}
		// ifs.close();
	
		sort(svec.begin(), svec.end());
		ofs = create_text_file("place.txt");
		copy(svec.begin(), svec.end(), ostream_iterator<string>{ofs, "\n"});
	
		// place.txt ->
		//	arda oltu isparta
		//	emre sefiloglu antalya
		//	ferhat portakal kutahya
		//	halime altindag bolu
		//	melih canlikaya sakarya
		//	necmettin soysalan denizli
		//	pelin uluocak canakkale
		//	tayfun karakuzu denizli
		//	tayyar yaradan sanliurfa
		//	zamir aksakal bursa
	}
*/

/*
	#include <fstream>
	#include "file.h"
	#include "nutility.h"
	
	int main()
	{
		using namespace std;
	
		ofstream ofs{ "out.txt", ios::app };
	
		// out.txt ->
		//	cesim gilgamis cankiri
		//	fadime zebani usak
		//	yusuf yurekli istanbul
	
		for (auto i = 0; i < 3; ++i) {
			ofs << rtown() << '\n';
		}
		// out.txt ->
		//	cesim gilgamis cankiri
		//	fadime zebani usak
		//	yusuf yurekli istanbul
		//	hatay
		//	diyarbakir
		//	tekirdag
	}
*/

/*
	#include <fstream>
	#include "file.h"
	#include "nutility.h"
	#include <set>
	#include <string>
	
	int main()
	{
		using namespace std;
	
		ofstream ofs = create_text_file("out.txt");
	
		for (int i = 0; i < 10000; ++i) {
			ofs << rname() << '\n';
		}
	
		ifstream ifs = open_text_file("out.txt");
	
		set<string> myset{ istream_iterator<string>{ifs}, {} };
		std::cout << "myset.size() = " << myset.size() << '\n';
		// output -> myset.size() = 333
	}
*/

/*
	#include <fstream>
	#include "file.h"
	#include <iostream>
	
	int main()
	{
		using namespace std;
	
		// out.txt
		//	istanbul izmir
		//	ankara
	
		// place.txt
		//	aaa bbb
		//	ccc
		//	ddd
	
		ifstream ifs = open_text_file("out.txt");
	
		char c;
		while (ifs.get(c)) {
			cout.put(c);
		}
		// output ->
		//	istanbul izmir
		//	ankara
	
		ifs.close();
		ifs = open_text_file("place.txt");
	
		int myint;
		while ((myint = ifs.get()) != EOF) {
			cout << (char)myint;
		}
		// output ->
		//	aaa bbb
		//	ccc
		//	ddd
	}
*/

/*
	#include <fstream>
	#include "file.h"
	#include "nutility.h"
	#include <iostream>
	#include <string>
	
	int main()
	{
		using namespace std;
	
		ofstream ofs = create_text_file("out.txt");
	
		for (int i = 0; i < 1000; ++i)
		{
			ofs << rname() << ';';
		}
		// out.txt -> cahit;gursel;cahide;binnaz;canan;tayyar;kurthan;hande; ...
	
		ifstream ifs = open_text_file("out.txt");
	
		string name;
		while (getline(ifs, name, ';'))
			cout << name << '\n';
		// output ->
		//	cahit
		//	gursel
		//	cahide
		//	binnaz
		//	canan
		//	tayyar
		//	kurthan
		//	hande
	}
*/

/*
	// write first 10k prime number to out.txt
	
	#include <fstream>
	#include <iostream>
	#include "nutility.h"
	#include <iomanip>
	
	int main()
	{
		using namespace std;
	
		ofstream ofs{ "out.txt" };
		if (!ofs) {
			cerr << "file can not be created\n";
			return 1;
		}
	
		constexpr int n = 10'000;
		int prime_count{};
		int x{ 2 };
	
		ofs << left;
	
		while (prime_count < n) {
			if (isprime(x)) {
				if (prime_count != 0 && prime_count % 10 == 0) {
					ofs << '\n';
				}
				ofs << setw(8) <<x << ' ';
				++prime_count;
			}
			++x;
		}
		// out.txt ->
		//	2        3        5        7        11       13       17       19       23       29
		//	31       37       41       43       47       53       59       61       67       71
		//	73       79       83       89       97       101      103      107      109      113
		//	127      131      137      139      149      151      157      163      167      173
		//	179      181      191      193      197      199      211      223      227      229
		//	233      239      241      251      257      263      269      271      277      281
		// ...
	}
*/

/*
	#include <fstream>
	#include <iostream>
	#include "file.h"
	#include <vector>
	
	
	int main()
	{
		using namespace std;
	
		auto ifs = open_text_file("out.txt");
		vector<int> ivec{ istream_iterator<int>{ifs}, istream_iterator<int>{}};
	
		cout << "ivec.size() = " << ivec.size() << '\n';
		// output -> ivec.size() = 10000
	}
*/

/*
	#include <fstream>
	#include <iostream>
	#include "file.h"
	#include <algorithm>
	#include <string>
	
	int main()
	{
		using namespace std;
	
		auto ifs = open_text_file("out.txt");
	
		int len{ 5 };
	
		copy_if(istream_iterator<string>{ifs}, {}, ostream_iterator<string>{cout, "\n"},
			[len](const string& s) {
				return s.length() == len && s.front() == s.back();
			});
		// output ->
		//	10061
		//	10091
		//	10111
		//	10141
		//	10151
		//	10181
		//	10211
		//	10271
		//	10301
		//	...
	}
*/

/*
	#include <fstream>
	#include <iostream>
	#include "file.h"
	#include "nutility.h"
	
	int main()
	{
		using namespace std;
	
		auto ofs = create_binary_file("out.dat");
	
		for (int i = 0; i < 1000; ++i)
		{
			int x = Irand{ 0, 10000 }();
			ofs.write(reinterpret_cast<char*>(&x), sizeof(x));
		}
		// because of int is 4 byte
		// file size will be 4000 byte
	}
*/

/*
	#include <fstream>
	#include <iostream>
	#include "file.h"
	#include "nutility.h"
	
	int main()
	{
		using namespace std;
	
		auto ifs = open_binary_file("out.dat");
	
		int x;
	
		while (ifs.read((char*)&x, sizeof(int))) {
			cout << x << ' ';
		}
		// output ->
		//	662 5420 5583 916 2583 8884 4069 3247 4848 7818 9955 5917 1849 4419 7141 3915 7388
		//	1054 1344 3145 4844 5796 6190 2442 1861 2032 6110 854 5424 8393 3013 5297 7695 852
		//	7322 4776 2198 775 3483 1745 4825 5 9159 581 7073 7950 8690 6182 5983 2444 ...
	}
*/

/*
	#include <fstream>
	#include <iostream>
	#include "file.h"
	#include "nutility.h"
	
	int main()
	{
		using namespace std;
	
		auto ofs = create_binary_file("out.dat");
	
		int prime_count{};
		int x{};
	
		while (prime_count < 1'000'000) {
			if (isprime(x)) {
				ofs.write((char*)&x, sizeof(int));
				++prime_count;
			}
			++x;
		}
		// out.dat files size = 4'000'000 byte
	}
*/

/*
	#include "file.h"
	#include <fstream>
	#include <iostream>
	
	int main()
	{
		using namespace std;
	
		auto ifs = open_binary_file("out.dat");
	
		//	ifs.seekg(std::streamoff, std::ios_base::seekdir);
		//	ifs.seekg(std::streamoff);
		//	seekg() member function has 2 overloads.
	
		// std::ios_base::seekdir ->
		// ios::beg
		// ios::end
		// ios::cur (current)
		// those help changing the file pointers location.
	
		int n{};
		int x{};
	
		for (int i = 0; i < 3; ++i) {
			std::cout << "order of the prime number : ";
			std::cin >> n;
	
			ifs.seekg((n - 1) * sizeof(int));
			//	ifs.seekg((n - 1) * sizeof(int), ios::beg);
			// Those 2 lines are same, default 2nd argument is ios::beg
	
			ifs.read(reinterpret_cast<char*>(&x), sizeof(int));
			cout << x << '\n';
		}
	
		// output ->
		//	order of the prime number : 4567
		//	43889
		//	order of the prime number : 8273
		//	84961
		//	order of the prime number : 162
		//	953
	}
*/

/*
	// io.exe
	// iodivide.exe out.dat 5000b
	// part001.par
	// part002.par
	// ...
	
	#include <iostream>
	#include <fstream>
	#include <sstream>
	#include <iomanip>
	
	int main(int argc, char** argv)
	{
		using namespace std;
	
		if (argc != 3) {
			cerr << "using: <iodivide.exe> <filename> <byte>\n";
			return 1;
		}
	
		ifstream ifs{ argv[1], ios::binary };
		if (!ifs) {
			cerr << argv[1] << " file can not be opened\n";
			return 2;
		}
	
		char c;
		int file_count{};
		int chunk = std::atoi(argv[2]);
		int byte_count{};
	
		ofstream ofs;
	
		while (ifs.get(c)) {
			if (!ofs.is_open()) {
				ostringstream oss;
				oss << setfill('0');
				oss << "part" << setw(3) << file_count + 1 << ".par";
				ofs.open(oss.str(), ios::binary);
	
				if (!ofs) {
					cerr << oss.str() << " file can not be created\n";
					return 3;
				}
				++file_count;
			}
			ofs.put(c);
			++byte_count;
			if (byte_count % chunk == 0) {
				ofs.close();
			}
		}
		cout << argv[1] << " named file divided to " << chunk << "byte " << file_count << " file\n";
	}
*/

/*
	// iocombine.exe out2.dat
	
	#include <iostream>
	#include <fstream>
	#include <sstream>
	#include <iomanip>
	
	int main(int argc, char** argv)
	{
		using namespace std;
	
		if (argc != 2) {
			cerr << "using: <iocombine.exe> <filename>\n";
			return 1;
		}
	
		ofstream ofs{ argv[1], ios::binary };
		if (!ofs) {
			cerr << argv[1] << " file can not be created\n";
			return 2;
		}
	
		int file_count{};
		int byte_count{};
	
		while (true) {
			ostringstream oss;
			oss << setfill('0');
			oss << "part" << setw(3) << file_count + 1 << ".par";
			ifstream ifs{ oss.str(), ios::binary };
	
			if (!ifs)
				break;
	
			char c;
	
			while (ifs.get(c)) {
				ofs.put(c);
				++byte_count;
			}
			++file_count;
			ifs.close();
			if (remove(oss.str().c_str())) {
				cerr << oss.str() << " file can not be deleted\n";
				return 3;
			}
		}
	
		cout << file_count << " files combined. " << argv[1] << " file is ready.\n";
	}
*/

/*
	// rdbuf() function gives a pointer to the buffer of a stream
	
	#include <iostream>
	
	int main()
	{
		using namespace std;
	
		ostream ostr{ cout.rdbuf() };
		// ostr will be used cout stream objects buffer
		// so it will also write to console as like cout object.
	
		// but its format state can be different than cout object.
		// in this example we are changing ostream object(ostr)'s
		// format state but its buffer holds cout's buffer.
	
		ostr.setf(ios::boolalpha | ios::uppercase | ios::showbase);
		ostr.setf(ios::hex, ios::basefield);
		ostr.setf(ios::scientific, ios::floatfield);
		ostr.precision(2);
	
		int x = 47'802, y = 57'054;
		double dval = 4177.7233;
	
		cout << x << " " << y << " " << dval << " " << (x > y) << '\n';
		ostr << x << " " << y << " " << dval << " " << (x > y) << '\n';
		// output ->
		//	47802 57054 4177.72 0
		//	0XBABA 0XDEDE 4.18E+03 false
	}
*/

/*
	// writing InputOutput.cpp file to standart output(console)
	
	#include <iostream>
	#include <fstream>
	#include "file.h"
	
	int main()
	{
		using namespace std;
	
		ifstream ifs{ open_text_file("InputOutput.cpp") };
	
		cout << ifs.rdbuf() << '\n';
		// cout.operator<<(std::streambuf*) overload
		// ostream classes inserter overload that wants a buffer pointer as an argument
	}
*/

/*
	// writing InputOutput.cpp file to standart output(console)
	
	#include <iostream>
	#include <fstream>
	#include "file.h"
	
	int main()
	{
		using namespace std;
	
		ifstream ifs{ open_text_file("InputOutput.cpp") };
	
		cout << ifs.rdbuf() << '\n';
		// cout.operator<<(std::streambuf*) overload
		// ostream classes inserter overload that wants a buffer pointer as an argument
	}
*/

/*
	// copying out.dat file to in.dat file

	#include <iostream>
	#include <fstream>
	
	int main(int argc, char** argv)
	{
		using namespace std;
	
		if (argc != 3) {
			cerr << "usage: <exe file> <source file name> <destination file name>\n";
			return 1;
		}
	
		ifstream ifs{ argv[1], ios::binary };
		if (!ifs) {
			cerr << argv[1] << " can not be opened\n";
			return 2;
		}
	
		ofstream ofs{ argv[2], ios::binary };
		if (!ofs) {
			cerr << argv[2] << " can not be created\n";
			return 3;
		}
	
		ofs << ifs.rdbuf();
		// cmd -> InputOutput.exe out.dat in.dat
	}
*/

/*
	#include <iostream>
	#include <fstream>
	#include <sstream>
	
	int main()
	{
		using namespace std;
	
		ostringstream oss;
	
		auto coutOldBuffer = cout.rdbuf();
		// holding cout objects buffer inside a variable before changing
	
		cout.rdbuf(oss.rdbuf());
		// cout objects buffer is now ostringstream objects(oss) buffer.
	
		cout << "hello world\n";
		// output ->
		cout.rdbuf(coutOldBuffer);
		cout << "hello universe\n";
		// output -> hello universe
	
		auto str = oss.str();
		cout << str << '\n';
		// output -> hello world
	}
*/

/*
	#include <iostream>
	#include <fstream>
	#include <sstream>
	#include "file.h"
	#include <algorithm>
	
	int main()
	{
		using namespace std;
	
		ifstream ifs{ open_text_file("InputOutput.cpp") };
	
		ostringstream oss;
		oss << ifs.rdbuf();
	
		auto mystring = oss.str();
	
		// remove erase idiom old way
		mystring.erase(remove_if(mystring.begin(), mystring.end(), [](char c) {
			return isspace(c);
			}), mystring.end());
	
		// remove erase idiom new way
		erase_if(mystring, [](char c) {
			return isspace(c); });
	
	
		cout << mystring << '\n';
		// output ->
		//	/*-----------------------------|Input-OutputOperations|-----------------------------*
		//	//*1.FormattedI/Oa.writingtostandartoutput&readingfromstandartinputb.read&write(IO)op
		//	erationsonfiles.InC++->basic_ifstreaminheritedfrombasic_istream->basic_ofstreaminheri
		//	tedfrombasic_ostream->basic_fstreaminheritedfrombasic_iostreamc.read&write(IO)operati
		//	onsinmemoryInC++->basic_istringstreaminheritedfrombasic_istream->basic_ostring ....
	}
*/

/*
	#include <iostream>
	
	int main()
	{
		using namespace std;
	
		cin.ios::ios_base::exceptions(ios::failbit | ios::eofbit | ios::badbit);
	
		try
		{
			int x{};
			std::cout << "enter an integer: ";
			cin >> x;
		}
		catch (const ios_base::failure& ex)
		{
			cout << "ios_base::failure caught: " << ex.what() << '\n';
		}
		catch (const std::exception& ex)
		{
			cout << "exception caught: " << ex.what() << '\n';
		}
		// output -> ios_base::failure caught: ios_base::failbit set: iostream stream error
	}
*/

/*
	#include <iostream>
	
	int main()
	{
		using namespace std;
	
		auto ist = cin.exceptions();
	
		if (ist == 0) {
			std::cout << "it will not throw an exception\n";
		}
		// default cin stream object will not throw an exception.
	
		if (ist & ios::failbit) {
			std::cout << "when failbit set, it will throw an exception\n";
		}
	
		ist = ist | ios::failbit | ios::eofbit | ios::badbit;
		// we change the cin objects ios_base::iostate
	
		if (ist & ios::eofbit) {
			std::cout << "when eofbit set, it will throw an exception\n";
		}
	
		if (ist & ios::badbit) {
			std::cout << "when badbit set, it will throw an exception\n";
		}
	
		// output ->
		//	it will not throw an exception
		//	when eofbit set, it will throw an exception
		//	when badbit set, it will throw an exception
	}
*/

/*
	#include <iostream>
	#include <sstream>
	
	using namespace std;
	
	double readsum(std::istream& is)
	{
		auto old_exception = is.exceptions();
		is.exceptions(ios::failbit | ios::badbit);
		double dval, sum{};
	
		try {
			while (is >> dval)
				sum += dval;
		}
		catch (...) {
			if (!is.eof()) {
				is.exceptions(old_exception);
				throw;
			}
		}
	
		is.exceptions(old_exception);
	
		return sum;
	}
	
	int main()
	{
		istringstream iss{ "2.6 3.4 5.6 6.8 1.1 8.9" };
		istringstream iss_2{ "2.6 3.4 5.6 6.8 hello 1.1 8.9" };
		// can also be ifstream
	
		double sum;
		try {
			sum = readsum(iss);
			// output -> sum = 28.4
	
			//	sum = readsum(iss_2);
			// output -> input output error: ios_base::failbit set: iostream stream error
	
			cout << "sum = " << sum << '\n';
		}
		catch (const std::ios::failure& ex) {
			cerr << "input output error: " << ex.what() << '\n';
			return 1;
		}
		catch (const std::exception& ex) {
			cerr << "standart library error: " << ex.what() << '\n';
			return 2;
		}
		catch (...) {
			cerr << "unknown error\n";
			return 3;
		}
	}
*/