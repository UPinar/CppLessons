#include <iostream>

/*
	=======================
	| unevaluated context | (Islem kodu uretilmeyen baglam)
	=======================
*/

/*
	int x = 10;
	size_t sz = sizeof(x++);
	int y = x;

	std::cout << "Value of y = " << y << '\n';
	return 0;
*/

/*
	// sizeof(x++);     // value of x is not going to increase
	// sizeof(foo());   // foo() function will not call
	// NO SIDE EFFECT
	// in C, unevaluated context is only happens in `sizeof()` operator.
*/

/*
	int* p = nullptr;
	int a[5]{};
	int x = 356;

	auto t = a[67]; // undefined behavior.(array bound overflow)
	*p = 4;		// undefined behavior.(null pointer dereferencing)
	x << 45;        // undefined behavior.

	sizeof(*p) + sizeof(a[67]) + sizeof(x << 8765)  
	// no undefined behaviour because of unevaluated context
*/

/*
	// C code

	typedef struct {
		int x, y;
		double dval;
	}*MyclassPtr;
	
	int main()
	{
		MyclassPtr p;
		// type does not have a name
		// but we can create a dynamic storage duration object
	
		MyclassPtr px = (MyclassPtr)malloc(sizeof(*px));
	
		// if *px evaluated it will cause undefined behaviour
		// but we use unevaluated context to find the structs size.
	}
*/

/*
	in C++ there are more unevaluated operators some are
	sizeof
	decltype
	typeid
	noexcept 
*/

/*
	int main()
	{
		int x = 10;

		decltype(x++) y = 6;
		// x is still 10. (unevaluated context)

		int a[10]{};

		decltype(a[20]) y = x;
		int& y = x;
		// These 2 lines are same
		// (a[20]) is an L value expression decltype(a[20])'s type is int&
	}
*/
