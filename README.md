# CppLessons

### [Reference Semantics](https://github.com/UPinar/CppLessons/tree/main/ReferenceSematics)
  - L value references
  - pointer semantics 
  - reference semantics
  
### [Type Deduction](https://github.com/UPinar/CppLessons/tree/main/TypeDeduction)
  - `auto` type deduction
    - `auto`   x = expr
    - `auto&`  y = expr
    - `auto&&` z = expr (forwarding reference)
  - reference collapsing
  - trailing return type
  - auto return type
  - `decltype` specifier type deduction
    - decltype(identifier)
    - decltype(expression)
  - unevaluated context (İşlem kodu üretilmeyen bağlam) 
  
### [Default Arguments](https://github.com/UPinar/CppLessons/tree/main/DefaultArguments)
  - default arguments
  - maximal munch
  
### [Typecast Operators](https://github.com/UPinar/CppLessons/tree/main/TypecastOperators)
  - (target type) Cstyle cast
  - static_cast
  - const_cast
  - reinterpret_cast
  - dynamic_cast
  
### [Enumeration Types](https://github.com/UPinar/CppLessons/tree/main/EnumerationTypes)
  - old-school(conventional) enum's problems
  - incomplete type
  - scoped & unscoped enums
  
### [`constexpr` Keyword](https://github.com/UPinar/CppLessons/tree/main/ConstexprKeyword)
  - constexpr variables
  - constexpr functions
  
### [Inline Functions](https://github.com/UPinar/CppLessons/tree/main/InlineFunctions)
  - inline functions
    - inline expansion optimization
    - One Definition Rule (ODR)
    - `static` vs `inline` functions
  - inline variables **C++17**
  
### [Function Overloading](https://github.com/UPinar/CppLessons/tree/main/FunctionOverloading)
  - function signature
  - Function Overload Resolution
    - variadic conversion 
    - user-defined conversion
    - standart conversion
      - exact match
      - promotion
      - conversion
  - name decoration(mangling)
  
### [Classes](https://github.com/UPinar/CppLessons/tree/main/Classes)
  - qualified & unqualified names
  - non-static data members
  - member functions
  - access specifiers
  - `this` pointer
  - const member functions
  - `mutable` keyword
  - constructor & destructor
  - RAII idiom
  - Storage Classes(Lifetime)
     - Static storage classes
     	 - global variables,
	 static initialization fiasco,
	 static local variables
     - Automatic storage classes
     - Dynamic storage classes (new/delete keyword)
     
### [Special Member Functions](https://github.com/UPinar/CppLessons/tree/main/SpecialMemberFunctions)
  - copy constructor
  - constructor(member) initializer list [MIL]
  - implicitly declared defaulted copy ctor
  - copy assignment
  - move ctor and move assignment
  - implicitly declared move members
  
### [Terms For Classes](https://github.com/UPinar/CppLessons/tree/main/TermsForClasses)
  - moved-from state
  - default member initializer
  - delegated constructor
  - temporary objects
  - conversion constructor
  - explicit constructor
  - copy elision
     - Mandatory copy elision scenerios
     - Named Return Value Optimization [NRVO]
  - pessimistic move
  - reference qualifiers
  
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
  
### [`std::string` Class](https://github.com/UPinar/CppLessons/tree/main/StringClass)
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
  
### [Templates](https://github.com/UPinar/CppLessons/tree/main/Templates)
  - template parameters
  - template argument deduction
  - function templates
  - trailing return type int templates
  - class templates
  - class template argument deduction
  - perfect forwarding
  - explicit(full) specialization 
  - partial specialization
  - alias templates
     - typedef declerations
     - using declerations
  - default template parameter
  - variable templates
  - variadic templates
  - pack expansion
  - Using variadic parameters one by one
     - compile time recursivity
     - init_list
     - fold expressions (C++17)
     - static if


### [Standart Template Library(STL)](https://github.com/UPinar/CppLessons/tree/main/StandartTemplateLibrary)
  - iterators 
  - iterator categories
    - input iterator
    - output iterator
    - forward iterator
    - bidirectional iterator
    - random access iterator
    - contigious iterator (Modern C++)
  - `std::copy` algorithm
  - `std::sort` algorithm 
  - `std::find` algorithm
  - `std::back_inserter` && `std::front_inserter` algorithms
  - iterator manipulator functions
    - `std::advance`
    - `std::distance`
    - `std::next` && `std::prev`
    - `std::iter_swap`
  - tag dispatch technique
  - `std::reverse_iterator` (iterator adapter)
  - `std::count` algorithm
  - `std::count_if` algorithm
  - `std::find_if` algorithm
  - `std::copy_if` algorithm
  - `std::transform` algorithm
  - `std::for_each` algorithm`
  - `std::all_of` && `std::any_of` && `std::none_of` algorithms
  - `std::max_element` algorithm
  - Standart function objects(standart functors)
  - `std::replace` && `std::replace_if` algorithms
  - `std::reverse_copy` && `std::remove_copy` && `std::remove_copy_if` algorithms
  - containers
    - `std::vector` container
  - lexicographical compare
  - lambda expressions (function)
  - generalized lambda expression
  - lambda init capture(C++14)
  - positive lambda idiom
  - Immediately Invoked Function(Lambda) Expression [IIFE] idiom
  - remove-erase idiom
  - sorting algorithms
    - `std::stable_sort` && `std::sort` stable and unstable sort algorithms
    - `std::partial_sort` algorithm
    - `std::nth_element` algorithm
    - `std::partition` && `std::stable_parition` && `std::partition_copy` algorithms
  - `std::make_heap` && `std::push_heap` && `std::pop_heap` && `std::sort_heap` algorithms
  - iterator invalidation
  - `std::deque` container
  - `std::list`(double-linked list) container
  - `std::forward_list`(singly-linked list)
  - `std::set` container
  - `std::lower_bound` && `std::upper_bound` && `std::equal_range` algorithms
  - `std::map` and `std::multimap` containers
  - ostream iterator class
  - `std::hash` function object class
  - unordered_ containers
    - `std::unordered_set` && `std::unordered_map`container
  - `std::array` container 
  - `std::stack` container adaptor
  - `std::queue` container adaptor
  - `std::priority_queue` container adaptor
  - reference wrapper `std::reference_wrapper`
  - `std::bind` function adaptor
  - `std::function`
  - member function pointers
  - data member pointers
  - `std::move_iterator` iterator adaptor
  - `std::tuple`
  - `std::apply`
  - sorted ranged algorithms
  - structured binding (C++17)
  - `decltype(auto)`
  - `std::bitset`
  - dynamic storage objects
  - placement new expressions
  - overloading operator new() and operator delete() functions as a member function

### [Smart Pointers](https://github.com/UPinar/CppLessons/tree/main/SmartPointers)
  - `std::unique_ptr` unique pointer
  - `std::shared_ptr` shared pointer
  - `std::weak_ptr` weak pointer
  - CRTP(Curiously Recurring Template Pattern) idiom 

### [Input - Output Operations](https://github.com/UPinar/CppLessons/tree/main/InputOutput)
  - Formatted IO Operations
  - File IO operations

### [User Defined Literals](https://github.com/UPinar/CppLessons/tree/main/UserDefinedLiterals)
  - cooked UDLs
  - uncooked UDLs

### [Random Library](https://github.com/UPinar/CppLessons/tree/main/RandomLibrary)
  - random library
  - algorithms related with random number generators
  - `std::generate` && `std::generate_n` algorithms
  - `std::shuffle` algorithm
  - `std::sample` algorithm (C++17) 

### [`std::string_view` Class (C++17)](https://github.com/UPinar/CppLessons/tree/main/StringViewClass)

### [Vocabulary Types (C++17)](https://github.com/UPinar/CppLessons/tree/main/VocabularyTypes)
  - `std::optional`
  - `std::variant`
  - visitor design pattern
  - overloader idiom
  - mono state pattern
  - variant polymorphism
  - variant comparison
  - `std::any`

### [Ratio Library](https://github.com/UPinar/CppLessons/tree/main/RatioLibrary)

### [Chrono Library](https://github.com/UPinar/CppLessons/tree/main/ChronoLibrary)
  - duration
  - time point
  - clock

### [Concurrency](https://github.com/UPinar/CppLessons/tree/main/Concurrency)
  - `<thread>` module
  - `std::this_thread` namespace
  - exception handling - threads relationship
  - thread-local storage duration | `thread_local` keyword
  - `std::async` function template
  - `std::future` class template
  - `std::shared_future` class template
  - `std::packaged_task` class template
  - shared resources in threads
  - mutex (mutual exclusion)
    - `std::mutex` class
    - `std::timed_mutex` class
    - `std::lock_guard` class template
    - `std::recursive_mutex` class
    - `std::unique_lock` class template
    - `std::lock` function template
    - `std::scoped_lock` variadic class template **(C++17)**
  - `std::call_once` & `std::once_flag`
  - conditional variable