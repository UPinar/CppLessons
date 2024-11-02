#include <iostream>

/*
                            =============
                            | namespace |
                            =============
*/

/*
  namespace ASpace {
    int foo();

    enum class Pos{ on, off, hold };

    class Myclass {
    public:
      void func(){}
      void bar();
    };

    void Myclass::bar() {}

    namespace NestedSpace{
    } // nested namespace
  }
  // "ASpace" is a namespace which is inside global namespace 
*/

/*
  namespace std {
    namespace regex_constants {
    }
  }
*/

/*
  ------------
  | C Scopes |
  ------------
  - file scope
  - block scope
  - function prototype scope
  - function scope

  --------------
  | C++ scopes |
  --------------
  - namespace scope
  - class scope
  - block scope
  - function prototype scope
  - function scope
*/

/*
  // ----------------------------------------------------

  // same identifiers can not be used in the same namespace
  namespace ASpace {
    int x;
    double x[10]; // syntax error
    //  error: conflicting declaration 'double ASpace::x [10]'
    // note: previous declaration as 'int ASpace::x'
  }

  // ----------------------------------------------------

  // same identifiers can be used in different namespaces
  namespace BSpace {
    int ival;
  }

  namespace CSpace {
    int ival;
  }

  // ----------------------------------------------------
*/

/*
  // variables inside namespaces are declared as global variables
  // so they are zero initialized like other static storage duration 
  // objects when they are default initialized.

  namespace ASpace {
    int ival; // default initialization
  }

  int main()
  {
    // ------------------------------------------------

    //ival; // syntax error
    // error: 'ival' was not declared in this scope; 

    // ------------------------------------------------

    std::cout << ASpace::ival << '\n'; // output -> 0
    // variables inside namespaces needs to be qualified
    // before being used outside of the their namespace scope.

    // ------------------------------------------------
  }
*/

/*
  #include <vector>
  #include <string>

  // namespace declarations are cumulative
  
  namespace ASpace {
    int a, b, c;
  }

  namespace ASpace {
    double x, y;
  }

  int main()
  {
    // ------------------------------------------------

    ASpace::x = 5.3;
    ASpace::a = 4;

    // ------------------------------------------------

    std::vector<int> ivec;
    std::string str;

    // because of std namespace is cumulative
    // different header(.h) files can be in the same namespace
    // <string> and <vector> are in std namespace
    
    // ------------------------------------------------
  }
*/

/*
  namespace ASpace {
    namespace NestedSpace {

      class Myclass {
      public:
        int foo(int); // member function declaration
      };
    }
  }

  int ASpace::NestedSpace::Myclass::foo(int x){}
  // member function definition
*/

/*
  namespace ASpace {
    class Myclass {};

    ASpace::Myclass bar();  // not necessary
    Myclass foo();          // VALID
    // Myclass is in ASpace namespace
    // so no need to qualify the name of the class
  }
*/

/*
  Question : 
    - is it possible to use a name outside of that namespace without 
      qualifying it with its namespace name ?
      -> using declaration
      -> using namespace declaration(directive)
      -> ADL (argument dependent lookup)
*/

/*
                      -----------------------
                      | `using` declaration |
                      -----------------------
*/

/*
  void foo()
  {
    using std::cout;  
    // using declaration in "foo" functions scope
    cout << "Hello from foo\n"; // VALID
  }

  void bar()
  {
    cout << "Hello from bar"; // syntax error
    // error: 'cout' was not declared in this scope;
  }
*/

/*
  // using declarator-list; (since C++17)
  // comma-separated list of one or more declarators of the typename

  using std::cout, std::endl;
*/

/*
  namespace ASpace {
    int ival;
  }

  int main()
  {
    using ASpace::ival;
    ival = 10;

    int ival = 5;   // syntax error
    // error: 'int ival' conflicts with a previous declaration
  }
*/

/*
  namespace ASpace {
    int ival;
  }

  namespace BSpace {
    using ASpace::ival;
    // "ASpace::ival" is injected to BSpace namespace
  }

  int main()
  {
    // ------------------------------------------------

    auto elem1 = BSpace::ival;  // VALID
    auto elem2 = ASpace::ival;  // VALID

    std::cout << elem1 << '\n'; // output -> 0
    std::cout << elem2 << '\n'; // output -> 0

    // ------------------------------------------------

    ASpace::ival = 5;

    std::cout << ASpace::ival << '\n'; // output -> 5
    std::cout << BSpace::ival << '\n'; // output -> 5

    // ------------------------------------------------

    BSpace::ival = 10;

    std::cout << ASpace::ival << '\n'; // output -> 10
    std::cout << BSpace::ival << '\n'; // output -> 10

    // ------------------------------------------------
  }
*/

/*
  int g_x = 10;

  namespace ASpace {
    using ::g_x;
    // unary scope resolution operator(::)
    // "g_x" is injected to ASpace namespace 
  }

  int main()
  {
    // ------------------------------------------------

    ASpace::g_x = 11; // VALID

    std::cout << g_x << '\n';         // output -> 11
    std::cout << ASpace::g_x << '\n'; // output -> 11

    // ------------------------------------------------

    g_x = 22;

    std::cout << g_x << '\n';         // output -> 22
    std::cout << ASpace::g_x << '\n'; // output -> 22

    // ------------------------------------------------
  }
*/

/*
  namespace ASpace {
    int x, y, z;
  }

  using ASpace::x;
  // "ASpace::x" is injected to global namespace scope

  int main()
  {
    // ------------------------------------------------

    int x = 11;   // local variable

    std::cout << x << '\n';           // output -> 11
    std::cout << ASpace::x << '\n';   // output -> 0
    std::cout << ::x << '\n';         // output -> 0

    // ------------------------------------------------

    ::x = 22;   // unary scope resolution operator(::)

    std::cout << x << '\n';           // output -> 11
    std::cout << ::x << '\n';         // output -> 22
    std::cout << ASpace::x << '\n';   // output -> 22

    // ------------------------------------------------

    // name lookup for "x" identifier
    // started from local scope -> FOUND

    // name lookup for "::x" identifier
    // started from global scope -> FOUND
    // "x" identifier is injected to global scope by using declaration 

    // name lookup for "ASpace::x" identifier
    // started from namespace scope -> FOUND
    // ------------------------------------------------
  }
*/

/*
  namespace ASpace {
    int x;
  }

  using ASpace::x;
  // "ASpace::x" is injected to global namespace scope

  int main()
  {
    x = 11; 
    // name lookup started in local scope -> NOT FOUND
    // name lookup started in global scope -> FOUND 
    // "x" identifier is injected to global scope by using declaration 

    std::cout << x << '\n';           // output -> 11
    std::cout << ASpace::x << '\n';   // output -> 11
    std::cout << ::x << '\n';         // output -> 11
  }
*/

/*
              -------------------------------------------
              | using namespace (directive) declaration |
              -------------------------------------------
*/

/*
  namespace ASpace {
    int x, y, z;
  }

  using ASpace::x;
  // "x" is injected to global namespace scope by using declaration

  int x = 5;  // syntax error
  // error: 'int x' conflicts with a previous declaration
  // note: previous declaration 'int ASpace::x'
*/

/*
  namespace ASpace {
    int x = 44;
  }

  using namespace ASpace;
  // whole ASpace namespace is injected to global namespace scope
  int x = 35; 

  int main()
  {
    x = 5;  // ambiguity error
    // error: reference to 'x' is ambiguous

    // name lookup for "x" identifier
    // started from local scope -> NOT FOUND
    // name lookup started in global scope -> FOUND but 2
    // because of 2 variable with "x" identifier found, ambiguity error
  }
*/

/*
  namespace ASpace {
    int x = 44;
  }

  using namespace ASpace;
  // whole ASpace namespace is injected to global namespace scope
  int x = 33; 

  int main()
  {
    std::cout << ::x << '\n';       // output -> 33
    std::cout << ASpace::x << '\n'; // output -> 44
  }
*/

/*
  namespace ASpace {
    int x, y, z;
  }

  namespace BSpace {
    int x;
  }

  using namespace ASpace;
  using namespace BSpace;

  int main()
  {
    x = 10; // ambiguity error
    // error: reference to 'x' is ambiguous
  }
*/

/*
  namespace ASpace {
    void func(int)
    {
      std::cout << "ASpace::func(int)\n";
    }
  }

  void func(double)
  {
    std::cout << "::func(double)\n";
  }
  // No function overloading because scopes are different
  //  ASpace::func is in ASpace namespace scope
  //  ::func is in global namespace scope

  int main()
  {
    func(4);  // output -> ::func(double) 
    // standart conversion from int to double

    ASpace::func(3.5);  // output -> ASpace::func(int)
    // standart conversion from double to int.
  }
*/

/*
  namespace ASpace {
    void func(int)
    {
      std::cout << "ASpace::func(int)\n";
    }
  }

  void func(double)
  {
    std::cout << "::func(double)\n";
  }

  using namespace ASpace;
  // when using namespace declaration is used,
  // ASpace::func is injected to global namespace scope
  // so "func" functions are now function overloads.

  int main()
  {
    func(4);    // output -> ASpace::func(int)
    func(4.2);  // output -> ::func(double)
  }
*/

/*
  namespace First {
    void func(int)
    {
      std::cout << "First::func(int)\n";
    }
  }

  namespace Second {
    void func(double)
    {
      std::cout << "Second::func(double)\n";
    }
  }

  using namespace First;
  using namespace Second;
  // "func" functions are now function overloads.

  int main()
  {
    func(10);   // output -> First::func(int)
    func(2.2);  // output -> Second::func(double)
  }
*/

/*
  namespace ASpace {
    int a, b, c;
  }

  void foo()
  {
    a = 4;  // syntax error
    // error: 'a' was not declared in this scope;
    // using namespace directive is after "foo" function's definition
  }

  using namespace ASpace;

  void bar()
  {
    b = 45; // VALID
    // using namespace directive is before "bar" function's definition
    // so "b" is injected to global namespace scope

    // name lookup for "b" identifier
    // started from "bar" function scope      -> NOT FOUND
    // name lookup continued in global scope  -> FOUND
  }
*/

/*
                      ---------------------
                      | unnamed namespace |
                      ---------------------
*/

/*
  // ---------------------------------------------------

  static int foo(int);    // internal linkage
  static int sg_x = 10;   // internal linkage

  // "foo" and "sg_x" are in global namespace scope
  // because of static keyword they have internal linkage

  // ---------------------------------------------------

  namespace {
    int bar(int);
    int g_ival = 10;
  }

  // "bar" and "g_ival" are in unnamed namespace scope
  // because of unnamed namespace they have internal linkage

  // ---------------------------------------------------

  // when an identifier will only be used in a source(.cpp) file
  // which will not be included by any other header(.h) file
  // better using unnamed namespace
  // for identifiers to have an internal linkage

  // ---------------------------------------------------
*/

/*
                      -------------------
                      | namespace alias |
                      -------------------
*/

/*
  namespace ASpace_xyz_proj {
    int ival = 5;

    namespace NestedSpace {
      int x, y;
    }
  }

  namespace ASpace = ASpace_xyz_proj;
  // namespace alias used for "ASpace_xyz_proj" namespace

  void foo()
  {
    namespace Nested = ASpace_xyz_proj::NestedSpace;
    // namespace alias for "ASpace_xyz_proj::NestedSpace" namespace
    Nested::x = 5;
  }

  int main()
  {
    using ASpace_xyz_proj::ival;

    std::cout << ival << '\n';    // output -> 5

    ASpace_xyz_proj::ival++;
    std::cout << ival << '\n';    // output -> 6

    ASpace::ival++;
    std::cout << ival << '\n';    // output -> 7
  }
*/

/*
                -----------------------------------
                | argument dependent lookup (ADL) |
                -----------------------------------
*/

/*
  if a function identifier is not qualified and 
  one of the argument that passed to the function 
  is related with namespace scope.
  So, name lookup for that function identifier will also
  check that namespace scope.
*/

/*
  namespace ASpace {
    class Myclass {};

    void foo(Myclass)
    {
      std::cout << "ASpace::foo(Myclass)\n";
    }
  }

  int main()
  {
    ASpace::Myclass mx;

    foo(mx);  // output -> ASpace::foo(Myclass)
    // "foo" is a non-qualified function identifier
    // "mx" is an object of type "ASpace::Myclass"
    // so Argument Dependent Lookup(ADL) will be applied.

    // name lookup for "foo" identifier
    // name lookup started from main() function scope   -> NOT FOUND
    // name lookup continued in global namespace scope  -> NOT FOUND
    // ADL continued in ASpace namespace scope          -> FOUND
  }
*/

/*
  #include <vector>

  namespace ASpace {
    class Myclass {};

    void foo(std::vector<Myclass>)
    {
      std::cout << "ASpace::foo(Myclass)\n";
    }
  }

  int main()
  {
    std::vector<ASpace::Myclass> myclass_vec;

    foo(myclass_vec);
    // foo is a non-qualified function identifier
    // "myclass_vec" is an object of type std::vector<ASpace::Myclass>
    // which is related with ASpace namespace
    // so Argument Dependent Lookup(ADL) will be applied.

    // name lookup for "foo" identifier
    // name lookup started from main() function scope   -> NOT FOUND
    // name lookup continued in global namespace scope  -> NOT FOUND
    // ADL continued in ASpace namespace scope          -> FOUND
  }
*/

/*
  namespace ASpace {
    enum Color { Red, Yellow, Green };
    void foo(Color);
  }

  int main()
  {
    foo(ASpace::Red);
    // ADL will be applied. 

    // name lookup for "foo" identifier
    // name lookup started from main() function scope   -> NOT FOUND
    // name lookup continued in global namespace scope  -> NOT FOUND
    // ADL continued in ASpace namespace scope          -> FOUND
  }
*/

/*
  namespace ASpace {
    class Myclass {};
    void foo(Myclass);
  }

  void foo(ASpace::Myclass);

  int main()
  {
    ASpace::Myclass mx;

    foo(mx);  // ambiguity error
    // error: call of overloaded 'foo(ASpace::Myclass&)' is ambiguous

    // name lookup for "foo" identifier
    // name lookup started from main() function scope       -> NOT FOUND
    // ordinary lookup for "foo" identifier in global scope -> FOUND
    // ADL for "foo" identifier in ASpace namespace scope   -> FOUND
    // --- ambiguity error ---
  }
*/

/*
  #include <vector>     // std::begin, std::end
  #include <algorithm>  // std::sort

  int main()
  {
    std::vector<int> ivec;

    sort(begin(ivec), end(ivec));
    // "ivec" is an object of type std::vector<int>
    // so Argument Dependent Lookup(ADL) will be applied
    // for "begin" and "end" identifiers.

    // name lookup for "begin" and "end" identifiers  
    // will be found in "std" namespace

    // "std::begin(ivec)" is a function in "std" namespace
    // so Argument Dependent Lookup(ADL) will be applied 
    // for "sort" function identifier.

    // name lookup for "sort" identifier
    // will be found in "std" namespace
  }
*/

/*
  namespace ASpace {
    class Myclass {};
    void foo(Myclass)
    {
      std::cout << "ASpace::foo(Myclass)\n";
    }
  }

  int main()
  {
    ASpace::Myclass mx;

    void foo(int);  // function declaration

    foo(mx);  // syntax error
    // error: cannot convert 'ASpace::Myclass' to 'int'

    // foo is a non-qualified function identifier
    // "mx" is an object of type "ASpace::Myclass"
    // so Argument Dependent Lookup(ADL) CAN be applied.

    // name lookup for "foo" identifier
    // name lookup started from main() function scope -> FOUND
    // context control phase will started for "foo" function
    // "foo" function is not a viable function for "mx" object
  }
*/

/*
  int main()
  {
    std::operator<<(std::cout, "Hello World\n");
    // output -> Hello World

    operator<<(std::cout, "Hello World\n"); 
    // output -> Hello World

    // "operator<<" is not a non-qualified function identifier
    // "std::cout" is an object which is related with "std" namespace
    // so Argument Dependent Lookup(ADL) will be applied.

    // name lookup for "operator<<" identifier
    // name lookup started from main() function scope -> NOT FOUND
    // name lookup continued in "std" namespace scope -> FOUND
  }
*/

/*
  // Herb Sutter's blog
  
  namespace ASpace {
    struct XStruct {};
    struct YStruct {};

    void foo(int);
    void bar(XStruct);
  }

  namespace BSpace {
    void foo(int ival)
    {
      foo(ival);
      // calling itself(BSpace::foo) - endless recursion
      // no ADL
    }

    void bar(ASpace::XStruct struct_x)
    {
      bar(struct_x);  // ambiguity error
      // ambiguous between 
      //   -  BSpace::bar (ordinary lookup) 
      //   -  ASpace::bar (argument-dependent lookup)
    }

    void baz(ASpace::YStruct struct_y)
    {
      baz(struct_y);  // VALID
      // calling itself(BSpace::baz) - endless recursion

      // ADL examines the ASpace namespace 
      // but there is no ASpace::baz() function,
      // so only BSpace::baz() from ordinary lookup is used.
    }
  }
*/

/*
  namespace ASpace {
    int x1 = 11;

    namespace BSpace {
      int y1 = 111;

      namespace CSpace {
        int z1 = 1111;
      }
    }
  }

  namespace ASpace {
    int x2 = 22;
  }

  namespace ASpace::BSpace {
    int y2 = 222;
  }

  namespace ASpace::BSpace::CSpace {
    int z2 = 2222;
  }

  int main()
  {
    std::cout << ASpace::BSpace::CSpace::z1 << '\n';  // output -> 1111
    std::cout << ASpace::BSpace::CSpace::z2 << '\n';  // output -> 2222

    std::cout << ASpace::BSpace::y1 << '\n';  // output -> 111
    std::cout << ASpace::BSpace::y2 << '\n';  // output -> 222

    std::cout << ASpace::x1 << '\n';  // output -> 11
    std::cout << ASpace::x2 << '\n';  // output -> 22
  }
*/

/*
                      ----------------------
                      | `inline` namespace |
                      ----------------------
*/

/*
  inline namespace ASpace {
    int ival; // default initialization
  }

  // "ASpace" is an inline namespace
  // inside global namespace scope

  int main()
  {
    std::cout << ival << '\n';            // output -> 0
    std::cout << ::ival << '\n';          // output -> 0
    std::cout << ASpace::ival << '\n';    // output -> 0

    ival = 5;
    std::cout << ival << '\n';            // output -> 5
    std::cout << ::ival << '\n';          // output -> 5
    std::cout << ASpace::ival << '\n';    // output -> 5

    int ival = 10;  
    // local variable "ival" identifier will hide (name hiding)
    // in global namespace scope comes from inline namespace

    std::cout << ival << '\n';            // output -> 10
    std::cout << ::ival << '\n';          // output -> 5
    std::cout << ASpace::ival << '\n';    // output -> 5
  }
*/

/*
  namespace ASpace {
    namespace NestedASpace {
      int ival;
    }
    using namespace NestedASpace;
  }

  namespace BSpace {
    inline namespace NestedBSpace {
      int ival;
    }
  }

  namespace CSpace {
    namespace NestedCSpace {
      int ival;
    }
  } 

  int main()
  {
    ASpace::ival = 4; // VALID

    BSpace::ival = 5; // VALID

    CSpace::ival = 6; // syntax error
    // error: 'ival' is not a member of 'CSpace'
  }
*/

/*
  // ADL will not be applied from ASpace::NestedASpace -> ASpace
  // because of NestedASpace namespace is NOT `inline`

  namespace ASpace {
    namespace NestedASpace {
      class Myclass {};
    }
    using namespace NestedASpace;

    void func(NestedASpace::Myclass);
  }

  int main()
  {
    ASpace::NestedASpace::Myclass mx;

    func(mx); // syntax error
    // error: 'func' was not declared in this scope;

    // name lookup for "func" identifier
    // started from main() function scope               -> NOT FOUND
    // name lookup continued in global namespace scope  -> NOT FOUND
    // ADL in ASpace::NestedASpace namespace scope      -> NOT FOUND
  }
*/

/*
  // ADL will be applied from ASpace::NestedASpace -> ASpace
  // because of NestedASpace is an `inline` nested namespace

  namespace ASpace {
    inline namespace NestedASpace {
      class Myclass {};
    }

    void func(NestedASpace::Myclass)
    {
      std::cout << "ASpace::func(NestedASpace::Myclass)\n";
    }
  }

  int main()
  {
    ASpace::NestedASpace::Myclass mx;
    func(mx); 
    // output -> ASpace::func(NestedASpace::Myclass)

    // name lookup for "func" identifier
    // started from main() function scope               -> NOT FOUND
    // name lookup continued in global namespace scope  -> NOT FOUND
    // ADL ASpace::NestedASpace namespace scope         -> NOT FOUND
    // ADL ASpace namespace scope                       -> FOUND
  }
*/

/*
  // ADL will be applied from ASpace -> ASpace::NestedASpace
  // because of NestedASpace is an `inline` nested namespace

  namespace ASpace {
    class Myclass{};

    inline namespace NestedASpace {
      void func(Myclass)
      {
        std::cout << "ASpace::NestedASpace::func(ASpace::Myclass)\n";
      }
    }
  }

  int main()
  {
    ASpace::Myclass mx;
    func(mx); 
    // output -> ASpace::NestedASpace::func(ASpace::Myclass)

    // name lookup for "func" identifier
    // started from main() function scope               -> NOT FOUND
    // name lookup continued in global namespace scope  -> NOT FOUND
    // ADL ASpace namespace scope                       -> NOT FOUND
    // ADL ASpace::NestedASpace namespace scope         -> FOUND
  }
*/

/*
  namespace ASpace {
    namespace NestedASpace {
      int ival = 5;   // ASpace::NestedASpace::ival
    }
    using namespace NestedASpace;

    int ival = 10;    // ASpace::ival
  }

  int main()
  {
    std::cout << ASpace::ival << '\n'; 
    // output -> 10
    // ASpace::ival hides ASpace::NestedASpace::ival

    std::cout << ASpace::NestedASpace::ival << '\n'; 
    // output -> 5
  }
*/

/*
  namespace ASpace {
    int ival = 10;

    inline namespace NestedASpace {
      int ival = 5;
    }
  }

  int main()
  {
    std::cout << ASpace::NestedASpace::ival << '\n'; 
    // output -> 5 

    std::cout << ASpace::ival << '\n';  // ambiguity error
    // error: reference to 'ival' is ambiguous
  }
*/

/*
              -------------------------------------
              | versioning with inline namespaces |
              -------------------------------------
*/

/*
  // foo.h
  // --------------

  namespace foo {
    class Myclass {
      int m_x;
      int m_y;
      double m_z;
    };
  }
  // changing any data member position will change object code
  // (ABI brackage)
*/

/*
  // foo.h
  // --------------

  namespace foo {
    inline namespace version_01 {   // inline namespace
      class Myclass {
        int m_x;
        int m_y;
        double m_z;
      };
    }
    namespace version_02 {          // non-inline namespace
      class Myclass {
        int m_x;
        double m_z;
        int m_y;
      };
    }
  }

  // version_01's interface will be used.
*/

/*
  #define USE_INLINE_NESTEDASPACE

  namespace ASpace {
  #ifdef USE_INLINE_NESTEDASPACE
    inline
  #endif
    namespace NestedASpace {
      const char* func(bool)
      {
        return "ASpace::NestedASpace::func(bool)";
      }
    }

    const char* func(int)
    {
      return "ASpace::NestedASpace::func(int)";
    }
  }

  int main()
  {
    // ------------------------------------------------

    // USE_INLINE_NESTEDASPACE macro defined 
    std::cout << ASpace::func(true) << '\n'; 
    // output -> ASpace::NestedASpace::func(bool)

    // ------------------------------------------------

    // USE_INLINE_NESTEDASPACE macro is NOT defined
    std::cout << ASpace::func(true) << '\n';
    // output -> ASpace::NestedASpace::func(int)

    // ------------------------------------------------
  }
*/

/*
  #define VERSION_01
  // #define VERSION_02

  namespace ASpace {
  #ifdef VERSION_01
    inline
  #endif
    namespace NestedASpace_version_01 {
      struct Mystruct {
      public:
        Mystruct()
        {
          std::cout << "ASpace::NestedASpace_version_01::Mystruct\n";
        }
      };
    }
  #ifdef VERSION_02
    inline
  #endif
    namespace NestedASpace_version_02 {
      struct Mystruct {
        Mystruct()
        {
          std::cout << "ASpace::NestedASpace_version_02::Mystruct\n";
        }
      };
    }
  }

  int main()
  {
    // ------------------------------------------------

    // VERSION_01 macro is defined
    ASpace::Mystruct mx;
    // output -> ASpace::NestedASpace_version_01::Mystruct

    // ------------------------------------------------

    // VERSION_02 macro is defined
    ASpace::Mystruct my;
    // output -> ASpace::NestedASpace_version_02::Mystruct

    // ------------------------------------------------
  }
*/