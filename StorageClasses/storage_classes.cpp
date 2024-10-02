#include <iostream>

/*
                      ===================
                      | Storage Classes |
                      ===================
*/

/*
  Storage Classes(Lifetime)
  ==========================
  -> static storage class
  -> automatic storage class
  -> dynamic storage class
  -> thread local storage class (concurrency)
*/

/*
                    ------------------------
                    | Static storage class |
                    ------------------------
*/

/*
                      --------------------
                      | global variables |
                      --------------------
*/

/*
  class AClass {
  public:
    AClass()
    {
      std::cout << "AClass default ctor.. this: " << this << '\n';
    }

    ~AClass()
    {
      std::cout << "AClass dtor.. this: " << this << '\n';
    }
  };

  class BClass {
  public:
    BClass()
    {
      std::cout << "BClass default ctor.. this: " << this << '\n';
    }

    ~BClass()
    {
      std::cout << "BClass dtor.. this: " << this << '\n';
    }
  };


  AClass m;   // global variable
  BClass y;   // global variable

  // global variables will be created from top to bottom.
  // First In Last Out(FILO) principle applied.

  int main()
  {
    std::cout << "int main() scope starts" << '\n';
    std::cout << "int main() scope ends" << '\n';
  }

  // output ->
  //  AClass default ctor.. this: 0x7ff6713890a0
  //  BClass default ctor.. this: 0x7ff6713890a1
  //  int main() scope starts
  //  int main() scope ends
  //  BClass dtor.. this:         0x7ff6713890a1
  //  AClass dtor.. this:         0x7ff6713890a0
*/

/*
                  --------------------------------
                  | static initialization fiasco |
                  --------------------------------
*/

/*
  - Every global variable will be constructed before
   "main" function's execution.
  - There is NO guarantee which global variable
   will become alive first!

  first.cpp
  ---------------
  F fx; // global variable

  second.cpp
  ---------------
  S sx; // global variable

  third.cpp
  ---------------
  T tx; // global variable

  eight.cpp
  ---------------
  E ex; // global variable

  main.cpp
  ---------------
*/

/*
  first.cpp
  ---------------
  F g_fx;
  extern S g_sx;

  F::F()
  {
    g_sx.xyz();
  }

  second.cpp
  ---------------
  S g_sx;

  main.cpp

  g_fx global variable depends on g_sx global variable.
  because of which one will become alive first is not guaranteed.
  - if g_sx become alive before g_fx : no problem
  - if g_fx become alive before g_sx : problem!
    it has been called static initialization fiasco

  --------------------------------
  - std::cout is also a global variable.
  - Static initialization fiasco does not
    effect to std::cout global variable
    -> schwarz idiom - nifty counter.
*/

/*
                  --------------------------
                  | static local variables |
                  --------------------------
*/

/*
  class AClass {
  public:
    AClass()
    {
      std::cout << "AClass default ctor.. this: " << this << '\n';
    }

    ~AClass()
    {
      std::cout << "AClass dtor.. this: " << this << '\n';
    }
  };

  class BClass {
  public:
    BClass()
    {
      std::cout << "BClass default ctor.. this: " << this << '\n';
    }

    ~BClass()
    {
      std::cout << "BClass dtor.. this: " << this << '\n';
    }
  };

  void f1()
  {
    static AClass s_ax; // static local variable
  }

  void f2()
  {
    static BClass s_bx; // static local variable
  }

  int main()
  {
    std::cout << "int main() scope starts" << '\n';
    std::cout << "int main() scope ends" << '\n';
  }
  // output ->
  //	int main() scope starts
  //	int main() scope ends

  // static local variables are not alive because
  // "f1" or "f2" has not been called.
*/

/*
  class Myclass {
  public:
    Myclass()
    {
      std::cout << "Myclass default ctor.. this: " << this << '\n';
    }

    ~Myclass()
    {
      std::cout << "Myclass dtor.. this: " << this << '\n';
    }
  };

  void f1()
  {
    static Myclass mx;  // static local variable
  }

  int main()
  {
    std::cout << "int main() scope starts" << '\n';
    f1();
    std::cout << "int main() scope ends" << '\n';
  }
  // output ->
  //  int main() scope starts
  //  Myclass default ctor.. this:  0x7ff6d2c490a0
  //  int main() scope ends
  //  Myclass dtor.. this:          0x7ff6d2c490a0
*/

/*
  class Myclass {
  public:
    Myclass()
    {
      std::cout << "Myclass default ctor >> this: " << this << '\n';
    }

    ~Myclass()
    {
      std::cout << "Myclass dtor >> this: " << this << '\n';
    }
  };

  void foo()
  {
    static int call_count{};  // static local variable
    std::cout << ++call_count << ". call for foo() function\n";
    static Myclass m;         // static local variable
  }

  int main()
  {
    std::cout << "int main() scope starts" << '\n';
    foo();
    foo();
    foo();
    std::cout << "int main() scope ends" << '\n';
  }

  // output ->
  //  int main() scope starts
  //  1. call for foo() function
  //  Myclass default ctor    >> this: 0x7ff7280c90a4
  //  2. call for foo() function
  //  3. call for foo() function
  //  int main() scope ends
  //  Myclass dtor            >> this: 0x7ff7280c90a4
*/

/*
                ----------------------------
                | Automatic storage class  |
                ----------------------------
        1.functions local variables
        2.local and non-static variables in block scopes
*/

/*
  class Myclass {
  public:
    Myclass()
    {
      std::cout << "Myclass default ctor >> this: " << this << '\n';
    }

    ~Myclass()
    {
      std::cout << "Myclass dtor >> this: " << this << '\n';
    }
  };

  void foo()
  {
    std::cout << "foo statement 1\n";
    Myclass m;
    std::cout << "foo statement 2\n";
  }

  void func()
  {
    std::cout << "func statement 1\n";

    {
      Myclass m;
    }

    std::cout << "func statement 2\n";
  }

  int main()
  {
    std::cout << "int main() scope starts" << '\n';
    foo();
    func();
    std::cout << "int main() scope ends" << '\n';
  }
  // output ->
  //  int main() scope starts
  //  foo statement 1
  //  Myclass default ctor  >> this: 0xa3ccbff87f
  //  foo statement 2
  //  Myclass dtor          >> this: 0xa3ccbff87f
  //  func statement 1
  //  Myclass default ctor  >> this: 0xa3ccbff88f
  //  Myclass dtor          >> this: 0xa3ccbff88f
  //  func statement 2
  //  int main() scope ends
*/

/*
  class AClass {
  public:
    AClass()
    {
      std::cout << "AClass default ctor >> this: " << this << '\n';
    }

    ~AClass()
    {
      std::cout << "AClass dtor >> this: " << this << '\n';
    }
  };

  class BClass {
  public:
    BClass()
    {
      std::cout << "BClass default ctor >> this: " << this << '\n';
    }

    ~BClass()
    {
      std::cout << "BClass dtor >> this: " << this << '\n';
    }
  };

  int main()
  {
    std::cout << "int main() scope starts" << '\n';
    for (size_t i = 0; i < 3; i++)
    {
      static BClass s_bx;
      AClass ax;
    }
    std::cout << "int main() scope ends" << '\n';
  }

  // output ->
  //  int main() scope starts
  //  BClass default ctor   >> this: 0x7ff6018790a0
  //  AClass default ctor   >> this: 0x4ef89ffc07
  //  AClass dtor           >> this: 0x4ef89ffc07
  //  AClass default ctor   >> this: 0x4ef89ffc07
  //  AClass dtor           >> this: 0x4ef89ffc07
  //  AClass default ctor   >> this: 0x4ef89ffc07
  //  AClass dtor           >> this: 0x4ef89ffc07
  //  int main() scope ends
  //  BClass dtor           >> this: 0x7ff6018790a0
*/

/*
  class Myclass {
  public:
    Myclass()
    {
      std::cout << "Myclass default ctor >> this: " << this << '\n';
    }

    ~Myclass()
    {
      std::cout << "Myclass dtor >> this: " << this << '\n';
    }
  private:
    int x, y, z, k;
  };

  int main()
  {
    std::cout << "int main() scope starts" << '\n';
    Myclass marr[5];
    std::cout << "int main() scope ends" << '\n';
  }

  // output ->
  //	int main() scope starts
  //  Myclass default ctor >> this: 0x2cb81ffb60
  //  Myclass default ctor >> this: 0x2cb81ffb70
  //  Myclass default ctor >> this: 0x2cb81ffb80
  //  Myclass default ctor >> this: 0x2cb81ffb90
  //  Myclass default ctor >> this: 0x2cb81ffba0
  //	int main() scope ends
  //  Myclass dtor >> this: 0x2cb81ffba0
  //  Myclass dtor >> this: 0x2cb81ffb90
  //  Myclass dtor >> this: 0x2cb81ffb80
  //  Myclass dtor >> this: 0x2cb81ffb70
  //  Myclass dtor >> this: 0x2cb81ffb60
*/

/*
  // Print 0 to 20
  struct Puzzle {
    Puzzle()
    {
      static int x = 0;
      std::cout << x++ << ' ';
    }
  };

  int main()
  {
    Puzzle arr[20];
    // output -> 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19
  }
*/

/*
                    -------------------------
                    | Dynamic storage class |
                    -------------------------

*/

/*
                    -------------------------
                    | new / delete keyword  |
                    -------------------------
*/

/*
  class Myclass {
  public:
    Myclass()
    {
      std::cout << "Myclass default ctor >> this: " << this << '\n';
    }

    ~Myclass()
    {
      std::cout << "Myclass dtor >> this: " << this << '\n';
    }
  };

  int main()
  {
    std::cout << "int main() started\n";
    auto p = new Myclass;
    std::cout << "main() goes on..[1]\n";
    delete p;
    std::cout << "main() goes on..[2]\n";
  }

  // output ->
  //  int main() started
  //  Myclass default ctor  >> this: 0x1f9c5496020
  //  main() goes on..[1]
  //  Myclass dtor          >> this: 0x1f9c5496020
  //  main() goes on..[2]
*/

/*
  --------------------------------------------------
  void* malloc(size_t n);
  void* operator new(size_t n);

  void free(void*);
  void operator delete(void*);

  --------------------------------------------------

  - new operator(new expression) and
    (std) operator new function is different

  - delete operator(delete expression) and
    (std) operator delete function is different!

  --------------------------------------------------

  - operator new function can be fail
    if it fails, it will throw an exception

  - malloc (C) can be fail.
    if it fails, it will return null pointer (NULL)

  --------------------------------------------------
*/

/*
  // for x86 system
  #include <new>
  #include <vector>

  std::vector<void*> vec;

  int main()
  {
    try
    {
      for (int i = 0; i < 1'000'000; ++i)
      {
        void* vp = operator new(1024u * 1024u);
        vec.push_back(vp);
        std::cout << i << '\n';
      }
    }
    catch (const std::exception& ex)
    {
      std::cout << "execption caught: " << ex.what() << '\n';
    }
  }
*/

/*
  auto p = new Fighter;
  ----------pseudo code-----------
    void* vp = operator new(sizeof(Fighter));
    // operator new() call  -> resource allocation

    Fighter* p = (static_cast<Fighter*>(vp))->Figher();
    // constructor call
  ----------pseudo code-----------

  delete p;
  ----------pseudo code-----------
    p->~Fighter();
    // destructor call
    operator delete(p);
    // operator delete() call	-> resource deallocation
  ----------pseudo code-----------
*/