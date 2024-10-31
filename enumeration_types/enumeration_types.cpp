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
            --------------------------------------------
            | old-school(conventional) enum's problems |
            --------------------------------------------
*/

/*
  enum Color { Red, Silver, Blue };

  int main()
  {
    Color my_color{ Red };

    int ival = 1;
    ival = my_color;
    // implicit conversion between conventional enums 
    // and integral types can lead problems
  }
*/

/*
  // first.h
  // ----------------
  enum Color { Red, Silver, Blue };

  // second.h
  // ----------------
  enum TrafficLight { Red, Yellow, Green };

  // main.cpp
  // ----------------
  #include "first.h"
  #include "second.h"

  // syntax error 
  // error: 'Red' conflicts with a previous declaration
*/

/*
  enum Color { Red = 2834723, Silver = 3844634, Blue = 902383 };

  // In C default underlying type is int.
  // In C++ there is no default underlying type.
  
  // compilers underlying types are different. 
  // (implementation-defined)
  // Some can hold them as an int, some hold as a long.
*/

/*
                -------------------------------
                | complete & incomplete types |
                -------------------------------
*/

/*
  class Myclass;  // forward decleration.

  Myclass f1(Myclass);
  Myclass* f2(Myclass*);
  Myclass& f3(Myclass&);
  // we can use incomplete types as 
  //  - function's return type
  //  - function's parameter type.

  int main()
  {
    Myclass* ptr = nullptr;
    // Compiler did NOT know incomplete type's storage need.
    // Because of pointer's storage is known,
    // creating a pointer to incomplete type is valid.
  }
*/

/*
  class Myclass;

  typedef Myclass* MyclassPtr;	
  // typedef declaration is valid with incomplete types.

  using MyclassPtr = Myclass*;	
  // using declarations is valid with incomplete types.

  extern Myclass x;
  // extern declaration does not need to know 
  // the storage need of the type, so it is valid.
*/

/*
  struct Data {
    struct Data x;    // not legal
    struct Data* ptr; // legal
  };

  // struct Data is incomplete type in the first line.
  // Compiler does not know the storage need of struct Data.
  // So, creating a struct Data object is not valid.
  // But creating a pointer to struct Data is valid.
*/

/*
  struct Myclass; 

  int main()
  {
    Myclass m; // syntax error
    // error: aggregate 'Myclass m' has incomplete type 
    // and cannot be defined

    // can not create an object from an incomplete type.
  }
*/

/*
  struct Myclass;

  int main()
  {
    sizeof(Myclass); // syntax error.
    // error: invalid application of 'sizeof' to 
    // incomplete type 'Myclass'

    // can not use incomplete type 
    // as an operand of the sizeof operator.
  }
*/

/*
  struct Myclass;

  int main()
  {
    Myclass* p;
    auto x = *p; // syntax error
    // error: deduced type 'Myclass' for 'x' is incomplete

    // dereferencing incomplete type pointer is syntax error.
  }
*/

/*
  class incomplete_class;

  class Myclass {
    incomplete_class ic;    // syntax error.
    // error: field 'ic' has incomplete type 'incomplete_class'

    incomplete_class& r;    // VALID
    incomplete_class* p;    // VALID
  };
*/

/*
  enum Color; // forward decleration

  struct Data {
    Color x;
    // In C++ underlying type is implementation-defined, 
    // this will cause problems.
    // In C, underlying type is int, no problem.
  };
*/

/*
  // Modern C++ : declaring the underlying type.

  enum Color : int { Red, Silver, Blue };
  enum TrafficLight : unsigned char { Red, Yellow, Green };
*/

/*
  // header_file.h
  // ----------------
  enum RandomEnum : unsigned char;
  // declared the underlying type of RandomEnum in forward declaration.

  // source_file.cpp
  // ----------------
  #include "header_file.h"

  struct Data {
    RandomEnum x;
    // No longer a problem related with 
    // implementation-defined underlying type
  };
*/

/*
  enum class Color : unsigned char { Red, Silver, Blue };
  // We can also declare underlying type in scoped enums.

  // If we did not declare underlying type in scoped enums,
  // default underlying type will be signed int.
*/

/*
  // color.h
  // ----------------
  enum class Color { Red, Silver, Blue };

  // traffic_light.h
  // ----------------
  enum class TrafficLight { Red, Yellow, Green };

  #include "color.h"
  #include "traffic_light.h"

  // In scoped enums, enumerators are in different scope.
  // Color and TrafficLight are in the global scope but
  // Color::Red, and TrafficLight::Red are in different scopes.

  int main()
  {
    auto mycolor = Color::Red;
    auto lightcolor = TrafficLight::Red;
  }
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
  enum class Color { Red, Silver, Blue };
  enum class City { Ankara, Istanbul, Izmir };

  void foo()
  {
    auto mycolor = Color::Red;
    // If we will use Color::Red, Color::Blue a lot of times,
    // always qualifying that colors will create verbose code.

    // ---------------------------------------------------------
    using enum Color; // using declaration for scoped enums.

    auto col_1 = Red;     // VALID
    auto col_2 = Silver;  // VALID
    auto col_3 = Blue;    // VALID
    // after using declaration, using unqualified names is valid.

    // ---------------------------------------------------------
    using City::Istanbul; 
    auto a = Istanbul;  // VALID
    auto b = Ankara;    // syntax error.
  }
*/

/*
  enum class Directions { Up, Down, Left, Right };
  enum class TrafficLight { Red, Yellow, Green };

  void foo()
  {
    using Directions::Up;
    // using declaration for a single enumerator.

    auto dir_1 = Up;      // VALID
    auto dir_2 = Down;    // syntax error.

    using TrafficLight::Green, TrafficLight::Yellow;  
    // using declaration with comma seperator list.

    auto col_1 = Green;   // VALID
    auto col_2 = Yellow;  // VALID
    auto col_3 = Red;     // syntax error
  }
*/

/*
  enum Directions { Up, Down, Left, Right };      // unscoped enum
  enum class TrafficLight { Red, Yellow, Green }; // scoped enum

  int main()
  {
    Directions my_dir{ Up };
    int ival{};
    ival = my_dir;
    // implicit conversion is valid 
    // from unscoped enum's enumerator to integral types.

    TrafficLight my_light{ TrafficLight::Green };
    ival = my_light;	// syntax error.
    // error: cannot convert 'TrafficLight' to 'int' in assignment

    // no implicit conversion 
    // from scoped enum's enumerator to integral types.

    ival = static_cast<int>(my_light);	// VALID
  }
*/