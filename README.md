# CppLessons

### [Reference Semantics](https://github.com/UPinar/CppLessons/tree/main/ReferenceSematics)
  - L value references
  - differences between pointer semantics and reference semantics
  
### [Type Deduction](https://github.com/UPinar/CppLessons/tree/main/TypeDeduction)
  - `auto`
  	- auto x   = expr
	- auto& y  = expr
	- auto&& z = expr -> forwarding reference
		- reference collapsing
	- trailing return type
	- auto return type
  - `decltype`
  	- decltype(identifier)
	- decltype(expression)
  - unevaluated context
  
### [`friend` Declerations](https://github.com/UPinar/CppLessons/tree/main/FriendDeclerations)
  - to a global function
  - to another classes member function
  - to another classes all functions(whole class)
  
### [Operator Overloading](https://github.com/UPinar/CppLessons/tree/main/OperatorOverloading)
  - const correctness for operator overloading 
  - overloading assignment operators
  - overloading arithmetic operators
  - overloading increment and decrement operators
  - [[nodiscard]] Attribute
  - overloading subscript operator
  - dereferencing & arrow(member selection) operator overload
  - function call operator overload
  - type-cast operator overload function
  - enum type global operator functions
  
### [`static` In Classes](https://github.com/UPinar/CppLessons/tree/main/staticInClass)
  - static member variables
  - static member functions
  - singleton design pattern
  - remove-erase idiom
  - range based for loop
  - if with initializer
  
### [Composition / Containment](https://github.com/UPinar/CppLessons/tree/main/Containment)
  - composition / containment
  - special member functions incomposition
  
### [Nested Types](https://github.com/UPinar/CppLessons/tree/main/NestedTypes)
  - nested types
  - pimpl idiom
 
### [`namespace`(s)](https://github.com/UPinar/CppLessons/tree/main/Namespaces)
  - using decleration
  - using namespace (directive) decleration
  - unnamed namespace
  - namespace alias
  - argument dependent lookup
  - inline namespace
  - versioning with inline namespaces
  
### [std::string Class](https://github.com/UPinar/CppLessons/tree/main/StringClass)
  - using iterator and index interfaces in std::string class functions
  - std::initializer_list class
  - constexpr static data member string::npos
  - three-way comparison(spaceship) operator [ <=> ]
  - std::string_view class (C++ 17)
  - remove-erase idiom
  
### [Inheritance](https://github.com/UPinar/CppLessons/tree/main/Inheritance)
  - inheritance and name-lookup
  - inheritance and access control
  - special member functions in inheritance
  - using declerations in inheritance
  - inherited constructor
  - run-time polymorphism
  - virtual dispatch mechanism
  - NVI (Non Virtual Interface Idiom)
  - virtual constuctor(Clone) idiom
  - variant return type (covariance)
  - virtual destructor
  - `final` (contextual) keyword
  - RTTI Run Time Type Identification(information)
    - `dynamic_cast` operator for RTTI
    - `typeid` operator for RTTI
  - private inheritance
    - EBO (Empty Base Optimization)
  - restricted polymophism
  - protected inheritance
  - multiple inheritence
	  - DDD (Dreadful Diamond on Derivation)
	  - virtual inheritance

### [Exception Handling](https://github.com/UPinar/CppLessons/tree/main/ExceptionHandling)
  - stack unwinding
  - rethrow statement
  - exception dispatcher
  - translating an exception
  - exception guarantees
  - `noexcept` keyword
  - constructors & exceptions
  - function try block


