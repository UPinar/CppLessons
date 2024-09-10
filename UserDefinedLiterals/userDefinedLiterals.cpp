#include <iostream>

/*
	#include <string>
	#include <chrono>
	
	int main()
	{
		using namespace std;
		using namespace std::chrono;
	
		"hello"s;
		operator""s("hello", 5);
		// Those 2 lines are same.
	
		// standart library UDL ""s is a function
		// it returns std::string and gets 2 arguments
	
		46ms;
		operator""ms(46);
		// Those 2 lines are same.
	}
*/

/*
	-> we can only create an UDL have a _(underscore) character in the beginning.
		operator""_
	-> UDL function parameter rules
		1. For Floating-point types		-> paramater needs to be LONG DOUBLE
		2. For Integer types			-> parameter needs to be UNSIGNED LONG LONG
		for more information -> https://en.cppreference.com/w/cpp/language/user_literal


	cooked	 -> 46_KB = 46 was sent to the function as an argument.

	uncooked -> 46_KB = "46_KB" string was sent to the function as an argument.
				applying operations to string inside function.
*/

/*
	constexpr double operator""_cm(long double x)
	{
		return static_cast<double>(x / 100);
	}
	
	constexpr double operator""_m(long double x)
	{
		return static_cast<double>(x);
	}
	
	constexpr double operator""_km(long double x)
	{
		return static_cast<double>(x * 1000);
	}
	
	int main()
	{
		auto distance = 5.2_m;
		// operator_m() function called
	
		constexpr auto distance = 234.34_m + 0.123_km + 345.91_cm;
		//	operator""_m(234.34) + operator""_km(0.123) + operator""_cm(345.91);
		// Those 2 lines are same
	
		// distance = 360.7991
	}
*/

/*
	#include <sstream>
	#include <string>
	#include <algorithm>
	
	class Date {
	public:
		Date() = default;
		Date(int d, int m, int y) : m_day{d}, m_mon{m}, m_year{y}{}
	
		Date(std::string str)
		{
			std::replace(str.begin(), str.end(), '_', ' ');
	
			std::istringstream iss{ str };
			int tempInt = 0;
	
			while (iss >> tempInt)
			{
				if (!m_day)
					m_day = tempInt;
				else if (!m_mon)
					m_mon = tempInt;
				else
					m_year = tempInt;
			}
		}
	
		friend std::ostream& operator<<(std::ostream& os, const Date& date)
		{
			return os << "( " << date.m_day << ", " << date.m_mon << ", " << date.m_year << " )";
		}
	private:
		int m_day{};
		int m_mon{};
		int m_year{};
	};
	
	Date operator""_dt(const char* p, size_t n)
	{
		std::cout << "n = " << n << '\n';
		return Date{ p };
	}
	
	int main()
	{
		std::cout << "12_05_1987"_dt;
		// output ->
		//	n = 10
		//	(12, 5, 1987)
	}
*/

/*
	#include <numbers>
	
	constexpr long double operator"" _deg_to_rad(long double deg)
	{
		long double radians = deg * std::numbers::pi_v<long double> / 100;
		return radians;
	}
	
	int main()
	{
		constexpr auto rad = 180._deg_to_rad;
		std::cout << "rad = " << rad << '\n';	// output -> rad = 5.65487
	}
*/

/*
	#include <numbers>

	constexpr int operator"" _i(char c)
	{
		return c;
	}

	int main()
	{
		std::cout << 'A'_i <<  '\n';	// output -> 65
		std::cout << '\n'_i <<  '\n';	// output -> 10
		std::cout << '+'_i <<  '\n';	// output -> 43

		constexpr auto c = 'A'_i;
	}
*/

/*
	#include <string>
	
	std::string operator"" _s2(const char* str, std::size_t)
	{
		return std::string{ str } + str;
	}
	
	std::string operator"" _s3(const char* str, std::size_t)
	{
		return std::string{ str } + str + str;
	}
	
	std::string operator"" _s4(const char* str, std::size_t)
	{
		return std::string{ str } + str + str + str;
	}
	
	int main()
	{
		std::cout << "hello"_s2 << '\n';
		// output -> hellohello
		std::cout << "hello"_s3 << '\n';
		// output -> hellohellohello
		std::cout << "hello"_s4 << '\n';
		// output -> hellohellohellohello
	}
*/

/*
	------------
	| uncooked |
	------------
*/

/*
	#include <cstring>
	#include <string>
	
	int operator""_p(const char* p)
	{
		std::cout << "std::strlen(p) = " << std::strlen(p) << '\n';
		return 0;
	}
	
	constexpr int operator""_x(const char* p)
	{
		int ret{};
		while (*p) {
			if (std::isdigit(*p)) {
				ret = ret * 16 + (*p - '0');
			}
	
			else if (isxdigit(*p)) {
				ret = ret * 16 + std::toupper(*p) - 'A' + 10;
			}
			++p;
		}
		return ret;
	}
	
	constexpr int operator""_b(const char* p)
	{
		int ret{};
		while (*p) {
			if (!(*p == '0' || *p == '1'))
				throw std::runtime_error{ "bad binary constant" };
			ret = ret * 2 + *p - '0';
			++p;
		}
		return ret;
	}
	
	int main()
	{
		12341_p;	// output -> std::strlen(p) = 5
		123_p;		// output -> std::strlen(p) = 3
	
		auto hex1 = 1239_x;
		std::cout << "hex1 = " << hex1 << '\n';	// output -> 4665
		auto hex2 = 8373_x;
		std::cout << "hex2 = " << hex2 << '\n';	// output -> 33651
	
		auto valb1 = 1111_b;
		std::cout << "valb1 = " << valb1 << '\n';	// output -> 15
		auto valb2 = 11111111_b;
		std::cout << "valb2 = " << valb2 << '\n';	// output -> 255

		try {
			auto valb_ex = 1113111_b;
			std::cout << "valb_ex = " << valb_ex << '\n';
		}
		catch (const std::exception& ex){
			std::cout << "exception caught: " << ex.what() << '\n';
		}
		// output -> exception caught: bad binary constant
	}
*/

/*
	#include <complex>
	
	int main()
	{
		using namespace std;
	
		auto c = 5.6i; // c's type is -> std::complex<double>
	}
*/

/*
	// strong type
	#include <ostream>
	#include <iostream>
	
	class Meters {
	private:
		double mts;
	
	public:
		class PreventUsage {};
		explicit constexpr Meters(PreventUsage, double meter) : mts{meter} {}
		explicit constexpr operator double() const { return mts; }
	};
	
	constexpr Meters operator""_m(long double m) {
		return Meters(Meters::PreventUsage(), static_cast<double>(m));
	}
	
	std::ostream& operator<<(std::ostream& os, const Meters& m)
	{
		return os << static_cast<double>(m) << " meters";
	}
	
	int main()
	{
		Meters m{ 23.56 };	// syntax error
		// 2 parameter constructor
	
		constexpr auto m1 = 34.56_m;
		// operator""_m() function is calling contexpr Meters constructor
	
		double dval = m1;								// syntax error
		double dval_valid = static_cast<double>(m1);	// valid
	}
*/

/*
	EXAMPLES ABOUT PERFECT FORWARDING
*/

/*
	// perfect forwarding examples

	template <typename T>
	void func(T&& r)
	{
		foo(std::forward<T>(r));
		foo(std::forward<decltype(r)>(r));
		// These 2 lines are same
	}
	
	int main()
	{
		auto fn = [](auto x) {
			std::forward<decltype(r)>(r);
		};
		// perfect forwarding in generalized lambda expressions
	
		// C++20
		auto fn = []<typename T>(T&& x) {
			std::forward<T>(x);
		};
	}
*/

/*
	template <typename T>
	void func(T&& x)
	{
		auto&& r = x;
		// hold x's value in a variable
	
		// use x for the operation (code here..)
	
		foo(std::forward<decltype(r)>(r));
		// forward the value you hold in the variable
	}
*/

/*
	template <typename T>
	void func(T&& x)
	{
		// if i want to hold the return value in a variable
		// then forward it to another function
	
		auto&& r = foo(std::forward<T>(x));
	
		// code here...
	
		bar(std::forward<decltype(r)>(r));
	}
*/

/*
	// QUESTION

	#include <vector>
	#include <string>
	
	template <typename C, typename T>
	void Fill(C& c, const T& val)
	{
		for (auto& r : c) {
			r = val;
		}
	}
	
	int main()
	{
		using namespace std;
	
		vector<int> ivec(100);
		vector<bool> bvec(100);
		vector<string> svec(100);
	
		Fill(ivec, 12);
		Fill(svec, "hello");
		Fill(bvec, true);	// syntax error
	
		// using auto&& instead of auto& is solving the problem
	}

*/

/*
	// EXAMPLES OF C++20 LAMBDA EXPRESSIONS
*/

/*
	#include <vector>

	class comp_generated_func_lamba {
	public:
		template <typename T, typename U>
		auto operator(T x, U y)
		{

		}
	};

	int main()
	{
		auto func = [](auto x, auto y) {};

		func(12, 4.5);

		auto func_2 = []<typename T>(T x, T y) {};

		func_2(12, 4.5); // syntax error
		// both arguments has to be same type


		auto func_3 = [](const auto& x) {};

		int ival{};
		std::vector<int> ivec(13);

		func_3(ival);	// valid
		func_3(ivec);	// valid

		auto func_4 = []<typename T>(const std::vector<T>& vec) {};
		// we can only send vector to this function

		func_4(ivec);	// valid
		func_4(ival);	// syntax error
	}
*/

/*
	// NTTP needs to be an integral type before C++20
	template <double n>
	class Myclass {
	
	};
	
	int main()
	{
		Myclass<2.3> m1;
		// syntax error before C++20
	}
*/

/*
	struct Data {
		int a, b, c;
	};
	
	// NTTP can also be a literal type after C++20
	template <Data x>
	class Myclass {
	
	};
	
	template <auto x>
	class Yourclass {
		Myclass<5> x;
		Myclass <[](){}> x;
	};
	
	int main()
	{
	
	}
*/