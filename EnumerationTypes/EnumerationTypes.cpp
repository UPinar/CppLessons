#include <iostream>

/*
	=====================
	| enumeration types |
	=====================
*/

/*
	1. conventional enums (unscoped enums)
	2. scoped enum (enum class)
*/

/*
	enum Color { Red, Silver, Blue };
	// Red, Silver and Blue are enumeration constants (enumerators)
*/

/*
	-----------------------------
	| old-school enums problems |
	-----------------------------
*/

/*
	enum Color {Red, Silver, Blue};
	
	int main()
	{
		Color myclolor{ Red };
	
		int ival = 1;
		ival = myclolor;
		// implicit conversion between conventional enums and integral types.
		// This can create big problems!
	}
*/

/*
	// first.h
	enum Color {Red, Silver, Blue};
	
	// second.h
	enum TrafficLight {Red, Yellow, Green};
	
	// main.cpp
	// #include "first.h"
	// #include "second.h"
	
	// syntax error.
	// C2365 'Red': redefinition; previous definition was 'enumerator'
*/

/*
	enum Color { Red = 2834723, Silver = 3844634, Blue = 902383 };

	// In C default underlying type is int.
	// but in C++ there is no default underlying type.
	// compilers underlying types are different.
	// Some can hold them as an int, some hold as a long.
*/

/*
	-------------------------------
	| complete & incomplete types |
	-------------------------------
*/

/*
	class Myclass;
	// forward decleration.
	
	Myclass f1(Myclass);
	Myclass* f2(Myclass*);
	Myclass& f3(Myclass&);
	// we can use incomplete types as a return type and a paramater.
	
	int main()
	{
		Myclass* ptr = nullptr;
		// compiler does not know the incomplete type's storage need,
		// but because of pointer's storage is known,
		// creating a pointer to incomplete type is valid.
	}
*/

/*
	class Myclass;
	
	typedef Myclass* MyclassPtr;	// typedef decleration is valid with incomplete types.
	using MyclassPtr = Myclass*;	// using declerations is valid with incomplete types.
	
	extern Myclass x;
	// extern decleration is not need a storage. Valid.
*/

/*
	struct Data {
		struct Data x;		// not legal
		struct Data* ptr;	// legal
	};
*/

/*
	struct Myclass;
	
	int main()
	{
		Myclass m; // syntax error
		// can not create an object from incomplete type.
	}
*/

/*
	struct Myclass;
	
	int main()
	{
		sizeof(Myclass); // syntax error.
		// can not use incomplete type as an operand of the sizeof operator.
	}
*/

/*
	struct Myclass;
	
	Myclass* foo();
	
	int main()
	{
		Myclass* p = foo();
	
		auto x = *p; // syntax error
		// dereferencing incomplete type pointer is not valid.
	}
*/

/*
	class incompleteClass;
	
	class Myclass {
		incompleteClass ic;		// syntax error.
		incompleteClass& r;		// legal
		incompleteClass* p;		// legal
	};
*/

/*
	enum Color; // forward decleration
	
	struct Data {
		Color x;
		// Because of underlying type can be differ from compiler to compiler in C++.
		// This will cause problems.
		// If this is C, underlying type will be int and no problem happens.
	};
*/

/*
	enum Color : int {Red, Silver, Blue};
	enum TrafficLight : unsigned char {Red, Yellow, Green};
	// Modern C++ declaring the underlying type.
*/

/*
	// header_file.h
	enum RandomEnum : unsigned char;
	
	struct Data {
		RandomEnum x;
		// will not be a problem from now on.
		// Because we declare its underlying type in enum's forward decleration.
	};
*/

/*
	enum class Color : unsigned char { Red, Silver, Blue };
	// we can also declare underlying type in scoped enums.
	// if we did not, default underlying type is signed int.
*/

/*
	// #include "color.h"
	enum class Color {Red, Silver, Blue};
	// #incluce "traffic.h"
	enum class TrafficLight {Red, Yellow, Green};
	
	// when we compile it will not create a syntax error.
	// Because in scoped enums, Enumerators are in different scope.
	// Color and TrafficLight are in the global scope but
	// Color::Red, and TrafficLight::Red are in different scopes.
*/

/*
	qualified name
	------------------
	-> x.y
	-> p->y
	-> class::x
	-> ::g

	unqualified name
	-----------------
	-> y
*/

/*
	// #include "color.h"
	enum class Color { Red, Silver, Blue };
	// #incluce "traffic.h"
	enum class TrafficLight { Red, Yellow, Green };
	
	// when we compile it will not create a syntax error.
	// Because in scoped enums, Enumerators are in different scope.
	// Color and TrafficLight are in the global scope but
	// Color::Red, and TrafficLight::Red are in different scopes.
	
	int main()
	{
		auto mycolor = Color::Red;
		auto lightcolor = TrafficLight::Red;
	}
*/

/*
	enum class Color { Red, Silver, Blue };
	
	void foo()
	{
		auto mycolor = Color::Red;
		// Think about we will use Color::Red, Color::Silver alot in our code.
		// always qualifying that colors are creating verbose code.
	
		using enum Color;
		// Now we can use all of the enumerators in Color scope without qualifing them.
		auto x = Silver;
		auto y = Blue;

		using Color::Red;
	}
*/

/*
	enum class Directions { Up, Down, Left, Right };
	enum class TrafficLight { Red, Yellow, Green };
	
	void foo()
	{
		using Directions::Up;
		auto a = Up;		// legal
		auto b = Down;		// syntax error.
	
		using TrafficLight::Green, TrafficLight::Yellow;  // comma seperator list.
	
		auto x = Green;		// legal
		auto y = Yellow;	// legal
		auto z = Red;		// syntax error
	}
*/

/*
	enum Directions { Up, Down, Left, Right };		// enscoped enums
	enum class TrafficLight { Red, Yellow, Green };		// scoped enums
	
	int main()
	{
		Directions my_dir{ Up };
		int ival{};
		ival = my_dir;
		// implicit conversion is valid from unscoped enums enumerator to integral types.
	
		TrafficLight my_light{ TrafficLight::Green };
		ival = my_light;	// syntax error.
		// no implicit conversion from scoped enums enumerator to integral types.
		ival = static_cast<int>(my_light);	// valid
	}
*/
