#include <iostream>
#include <exception>

/*
                      ======================
                      | exception handling |
                      ======================
*/

/*
  - throw
  - try
  - catch
  keywords are used for exception handling.
*/

/*
  - if an exception thrown and program did not catch that exception
    it is called uncaught exception.

  - if there is an uncaught exception, std::terminate function invoked.
    std::terminate function's default behaviour is 
    calling std::abort function.

  - std::abort is an abnormal termination function
  - std::abort is not like std::exit, does not give any guarantees.

  - std::exit is a normal termination function.
  - std::exit gave those guarantees
    -> closing files,
    -> flushing buffers of files
    -> calling functions that registered with std::atexit function  
      in reverse order of registration.
*/

/*
  void func_2()
  {
    std::cout << "func_2 called\n";
    throw 1;
    std::cout << "func_2 returns\n";
  }

  void func_1()
  {
    std::cout << "func_1 called\n";
    func_2();
    std::cout << "func_1 returns\n";
  }

  int main()
  {
    std::cout << "[0] - main started\n";
    func_1();
    std::cout << "[1] - main ends\n";

    // output -> 
    // [0] - main started
    //  func_1 called
    //  func_2 called
    //  terminate called after throwing an instance of 'int'
  }
*/

/*
  - to change the default behaviour of std::terminate function
    which is calling std::abort function,
    there is a function called std::set_terminate which gets 
    a function pointer as a parameter. 

  - when std::terminate function called, 
    it will call the function that registered with
    std::set_terminate function else it will call std::abort function.
*/

/*
  using terminate_handler = void(*)();
  typedef void(*terminate_handler_2)();
  // Those 2 lines are equivalent.

  terminate_handler gp_func = &std::abort;

  void terminate()
  {
    gp_func();
  }

  terminate_handler set_terminate(terminate_handler fp_param)
  {
    auto fp_temp = gp_func;
    gp_func = fp_param;
    return fp_temp;

    // returns the previous function pointer that 
    // std::terminate function would call.

    // changes the global function pointer that  
    // std::terminate function will be call.
  }
*/

/*
  #include <cstdlib>    // std::exit
  #include <exception>  // std::set_terminate

  void terminate_func()
  {
    std::cout << "terminate_func called\n";
    std::exit(EXIT_FAILURE);
  }

  void func_1()
  {
    std::cout << "func_1 called\n";
    throw 1;
    std::cout << "func_1 returns\n";
  }

  int main()
  {
    std::set_terminate(terminate_func);
    func_1();
    // output ->
    // func_1 called
    // terminate_func called
  }
*/

/*
  - throw expr;   // throw statement
  - throw;        // rethrow statement
*/

/*
  exception object
  -----------------
  - throw 12;
  compiler will generate an object(exception object) 
  that have a type of int

  - throw Myclass{};
  compiler will generate an object(exception object) 
  that have a type of Myclass 
*/

/*
  class Myclass {};

  void func()
  {
    Myclass mx;
    throw mx;
    // "mx" will used for initialization of the exception object.
    // thrown object is not "mx" itself, it is a copy of "mx".

    throw Myclass{};
    // temporary object is created and thrown.
  }
*/

/*
  int main()
  {
    try {
      int ival = 11;
    }
    catch (int)
    {
      ival = 22; // syntax error.
      // error: 'ival' was not declared in this scope

      // ival is in try block's scope 
      // and CAN NOT be used in catch block.
    }
  }
*/

/*
  int main()
  {
    try {

    }
    catch (int param_1, int param_2)  // syntax error
    {
      // catch can only have 1 parameter
    }
  }
*/

/*
  void func_2()
  {
    std::cout << "func_2 called\n";
    throw 11;
    std::cout << "func_2 returns\n";
  }

  void func_1()
  {
    std::cout << "func_1 called\n";
    func_2();
    std::cout << "func_1 returns\n";
  }

  int main()
  {
    std::cout << "[0] - main started\n";

    try {
      func_1();
    }
    catch (int ival){
      std::cout << "exception caught. catch(int x), x = " 
                << ival << '\n';
    }

    std::cout << "[1] - main ends\n";
    // output ->
    //  [0] - main started
    //  func_1 called
    //  func_2 called
    //  exception caught. catch(int x), x = 11
    //  [1] - main ends
  }
*/

/*
  void func_2()
  {
    std::cout << "func_2 called\n";
    throw 'A';
    // no implicit conversion from char to int
    // because of uncaught exception 
    // std::terminate() function will be invoked
    std::cout << "func_2 returns\n";
  }

  void func_1()
  {
    std::cout << "func_1 called\n";
    func_2();
    std::cout << "func_1 returns\n";
  }

  int main()
  {
    std::cout << "[0] - main started\n";
    try {
      func_1();
    }
    catch (int ival) {
      std::cout << "exception caught. catch(int x), x = " 
                << ival << '\n';
    }

    std::cout << "[1] - main ends\n";

    // output ->
    //  [0] - main started
    //  func_1 called
    //  func_2 called
    //  terminate called after throwing an instance of 'char'
  }
*/

/*
  void func_2()
  {
    std::cout << "func_2 called\n";
    throw 12.3;
    std::cout << "func_2 returns\n";
  }

  void func_1()
  {
    std::cout << "func_1 called\n";
    func_2();
    std::cout << "func_1 returns\n";
  }

  int main()
  {
    std::cout << "[0] - main started\n";

    try {
      func_1();
    }
    catch (double d) {
      std::cout << "exception caught. catch(double d) d = " 
                << d << '\n';
    }
    catch (long l) {
      std::cout << "exception caught. catch(long l) l = " 
                << l << '\n';
    }
    catch (int x) {
      std::cout << "exception caught. catch(int x) x = " 
                << x << '\n';
    }
    catch (char c) {
      std::cout << "exception caught. catch(char c) c = " 
                << c << '\n';
    }

    std::cout << "[1] - main ends\n";

    // output ->
    //  [0] - main started
    //  func_1 called
    //  func_2 called
    //  exception caught. catch(double d) d = 12.3
    //  [1] - main ends
  }
*/

/*
  void func_2()
  {
    std::cout << "func_2 called\n";
    throw 'A';
    std::cout << "func_2 returns\n";
  }

  void func_1()
  {
    std::cout << "func_1 called\n";
    func_2();
    std::cout << "func_1 returns\n";
  }

  int main()
  {
    std::cout << "[0] - main started\n";

    try {
      func_1();
    }
    catch (int x) {
      std::cout << "exception caught. catch(int x) x = " 
                << x << '\n';
    }
    catch (double d) {
      std::cout << "exception caught. catch(double d) d = " 
                << d << '\n';
    }
    catch (...) {
      // ellipsis token(...)
      // catches all parameter.
      std::cout << "exception caught in function main. catch(...)\n";
      // output -> exception caught in function main. catch(...)
    }

    std::cout << "[1] - main ends\n";

    // output ->
    //  [0] - main started
    //  func_1 called
    //  func_2 called
    //  exception caught in function main. catch(...)
    //  [1] - main ends
  }
*/

/*
  void func_2()
  {
    std::cout << "func_2 called\n";
    throw 'A';
    std::cout << "func_2 returns\n";
  }

  void func_1()
  {
    std::cout << "func_1 called\n";
    func_2();
    std::cout << "func_1 returns\n";
  }

  int main()
  {
    try {
      func_1();
    }
    catch (...) { // syntax error
      std::cout << "exception caught in function main. catch(...)\n";
    } 
    catch (int x) {
      std::cout << "exception caught. catch(int x) x = " 
                << x << '\n';
    }
    catch (double d) {
      std::cout << "exception caught. catch(double d) d = " 
                << d << '\n';
    }

    // error: '...' handler must be the last handler for its try block
    // because of catch(...) catches all exceptions
    // it must be the last catch block.
  }
*/

/*
  // polymorphic base class
  class AClass {
  public:
    virtual ~AClass() = default;
  };

  class XClass : public AClass {};
  class YClass : public AClass {};

  class ZClass : public XClass {};

  void func_2()
  {
    std::cout << "func_2 called\n";
    throw XClass{};
    // "XClass{}" is an PRValue expression(R)
    // PRValue expression(R) can not bind L value reference 
    // but because of exception object will be copied from temp object
    // it can bind to XClass& in catch(XClass&)

    std::cout << "func_2 returns\n";
  }

  void func_1()
  {
    std::cout << "func_1 called\n";
    func_2();
    std::cout << "func_1 returns\n";
  }

  int main()
  {
    std::cout << "[0] - main started\n";

    try {
      func_1();
    }
    catch (XClass&) {
      std::cout << "exception caught catch(XClass&)\n";
    }

    std::cout << "[1] - main ends\n";

    // output ->
    //  [0] - main started
    //  func_1 called
    //  func_2 called
    //  exception caught catch(XClass&)
    //  [1] - main ends
  }
*/

/*
  // polymorphic base class
  class AClass {
  public:
    virtual ~AClass() = default;
  };

  class XClass : public AClass {};
  class YClass : public AClass {};

  class ZClass : public XClass {};

  void func_2()
  {
    std::cout << "func_2 called\n";
    throw ZClass{};
    // because of ZClass is derived from XClass
    // upcasting is VALID.

    std::cout << "func_2 returns\n";
  }

  void func_1()
  {
    std::cout << "func_1 called\n";
    func_2();
    std::cout << "func_1 returns\n";
  }

  int main()
  {
    std::cout << "[0] - main started\n";

    try {
      func_1();
    }
    catch (XClass&) {
      std::cout << "exception caught catch(XClass&)\n";
    }

    std::cout << "[1] - main ends\n";

    // output ->
    //  [0] - main started
    //  func_1 called
    //  func_2 called
    //  exception caught catch(XClass&)
    //  [1] - main ends
  }
*/

/*
  // polymorphic base class
  class AClass {
  public:
    virtual ~AClass() = default;
  };

  class XClass : public AClass {};
  class YClass : public AClass {};

  class ZClass : public XClass {};

  void func_2()
  {
    std::cout << "func_2 called\n";
    throw ZClass{};
    // because of ZClass is derived from XClass
    // and XClass is derived from AClass
    // upcasting is VALID.

    std::cout << "func_2 returns\n";
  }

  void func_1()
  {
    std::cout << "func_1 called\n";
    func_2();
    std::cout << "func_1 returns\n";
  }

  int main()
  {
    std::cout << "[0] - main started\n";

    try {
      func_1();
    }
    catch (AClass&) {
      std::cout << "exception caught catch(AClass&)\n";
    }

    std::cout << "[1] - main ends\n";

    // output ->
    //  [0] - main started
    //  func_1 called
    //  func_2 called
    //  exception caught catch(AClass&)
    //  [1] - main ends
  }
*/

/*
  class AClass {
  public:
    virtual ~AClass() = default;

    virtual const char* get_str() const
    {
      return "AClass";
    }
  };

  class XClass : public AClass {
  public:
    virtual const char* get_str() const override
    {
      return "XClass";
    }
  };
  class YClass : public AClass {
  public:
    virtual const char* get_str() const override
    {
      return "YClass";
    }
  };
  class ZClass : public XClass {
  public:
    virtual const char* get_str() const override
    {
      return "ZClass";
    }
  };

  void func_1()
  {
    throw ZClass{};
    // because of ZClass is derived from XClass
    // and XClass is derived from AClass
    // upcasting is VALID.
  }

  int main()
  {
    std::cout << "[0] - main started\n";

    try {
      func_1();
    }
    catch (AClass& ref_AClass) {
      std::cout << "exception caught. catch(AClass&)\n";
      std::cout << ref_AClass.get_str() << '\n';
    }

    std::cout << "[1] - main ends\n";

    // output -> 
    // [0] - main started
    // exception caught. catch(AClass&)
    // ZClass       ----> virtual dispatch
    // [1] - main ends

    // virtual dispatch mechanism works in catch block.
  }
*/

/*
  class AClass {
  public:
    virtual ~AClass() = default;
  };

  class XClass : public AClass {};
  class YClass : public AClass {};
  class ZClass : public XClass {};

  void func_1()
  {
    // ---------------------------------------------

    throw ZClass{};
    // output -> exception caught catch(XClass&)
    // ZClass will upcasted to XClass

    // ---------------------------------------------

    throw YClass{};
    // output -> exception caught catch(AClass&)
    // YClass will upcasted to AClass

    // ---------------------------------------------
  }

  int main()
  {
    try {
      func_1();
    }
    catch (XClass& ref_XClass) {
      std::cout << "exception caught catch(XClass&)\n";
    }
    catch (AClass& ref_AClass) {
      std::cout << "exception caught catch(AClass&)\n";
    }
    catch (...) {
      std::cout << "exception caught catch(...)\n";
    }
  }
*/

/*
  #include <string>

  void func(int x)
  {
    std::string str{ "hello world" };
    auto ch = str.at(x);
  }

  int main()
  {
    try {
      func(333333);
    }
    catch (const std::out_of_range& ex) {
      std::cout << "out_of_range caught: " << ex.what() << '\n';
    }
    catch (const std::logic_error& ex) {
      std::cout << "logic_error caught: " << ex.what() << '\n';
    }
    catch (const std::exception& ex) {
      std::cout << "exception caught: " << ex.what() << '\n';
    }

    // output ->
    // out_of_range caught: basic_string::at: __n 
    // (which is 333333) >= this->size() (which is 11)
  }
*/

/*
  struct XStruct {
    XStruct()
    {
      std::cout << "XStruct::XStruct(), this = " 
                << this << '\n';
    }
    XStruct(const XStruct&)
    {
      std::cout << "XStruct(const XStruct&), this = " 
                << this << '\n';
    }
    XStruct(XStruct&&)
    {
      std::cout << "XStruct(XStruct&&), this = " 
                << this << '\n';
    }
    ~XStruct()
    {
      std::cout << "XStruct::~XStruct(), this = " 
                << this << '\n';
    }
  };

  void foo()
  {
    throw XStruct{};
    // "XStruct{}" is a PRValue expression
    // mandatory copy ellision will occur.
  }

  int main()
  {
    try {
      foo();
    }
    catch (const XStruct& ex) {
      std::cout << "exception caught. &ex= " << &ex << '\n';
    }

    // output -> 
    //  XStruct::XStruct(), this = 0x27f8026f360
    //  exception caught. &ex= 0x27f8026f360
    //  XStruct::~XStruct(), this = 0x27f8026f360
  }
*/

/*
                        -------------------
                        | stack unwinding |
                        -------------------
*/

/*
  if an exception has NOT been caught, 
  objects inside stack frame will cause a resource leak
  because their destructors WON'T be called when 
  std::terimate function has been called.
*/

/*
  class AClass {
  public:
    AClass()
    {
      std::cout << "AClass object " 
                << this << " obtain resources.\n";
    }
    ~AClass()
    {
      std::cout << "AClass object " 
                << this << " give resources back.\n";
    }
  };

  class BClass {
  public:
    BClass()
    {
      std::cout << "BClass object " 
                << this << " obtain resources.\n";
    }
    ~BClass()
    {
      std::cout << "BClass object " 
                << this << " give resources back.\n";
    }
  };

  class CClass {
  public:
    CClass()
    {
      std::cout << "CClass object " 
                << this << " obtain resources.\n";
    }
    ~CClass()
    {
      std::cout << "CClass object " 
                << this << " give resources back.\n";
    }
  };

  void func_4()
  {
    AClass a1; BClass b1;
    throw std::exception();
  }

  void func_3()
  {
    CClass c1;
    func_4();
  }

  void func_2()
  {
    AClass a1; BClass b1; CClass c1;
    func_3();
  }

  void func_1()
  {
    BClass b1, b2, b3;
    func_2();
  }

  int main()
  {
    // --------------------------------------------------------

    // func_1();
    // output ->
    //  BClass object 0xae3b9ff7ef obtain resources.
    //  BClass object 0xae3b9ff7ee obtain resources.
    //  BClass object 0xae3b9ff7ed obtain resources.
    //  AClass object 0xae3b9ff79f obtain resources.
    //  BClass object 0xae3b9ff79e obtain resources.
    //  CClass object 0xae3b9ff79d obtain resources.
    //  CClass object 0xae3b9ff74f obtain resources.
    //  AClass object 0xae3b9ff6ff obtain resources.
    //  BClass object 0xae3b9ff6fe obtain resources.

    // all the resources are leaked.

    // --------------------------------------------------------

    try {
      func_1();
    }
    catch (const std::exception& ex)
    {
      std::cout << "exception caught: " << ex.what() << '\n';
    }

    // output ->
    //  BClass object 0x690d7ff79f obtain resources.
    //  BClass object 0x690d7ff79e obtain resources.
    //  BClass object 0x690d7ff79d obtain resources.
    //  AClass object 0x690d7ff74f obtain resources.
    //  BClass object 0x690d7ff74e obtain resources.
    //  CClass object 0x690d7ff74d obtain resources.
    //  CClass object 0x690d7ff6ff obtain resources.
    //  AClass object 0x690d7ff6af obtain resources.
    //  BClass object 0x690d7ff6ae obtain resources.
    //  BClass object 0x690d7ff6ae give resources back.
    //  AClass object 0x690d7ff6af give resources back.
    //  CClass object 0x690d7ff6ff give resources back.
    //  CClass object 0x690d7ff74d give resources back.
    //  BClass object 0x690d7ff74e give resources back.
    //  AClass object 0x690d7ff74f give resources back.
    //  BClass object 0x690d7ff79d give resources back.
    //  BClass object 0x690d7ff79e give resources back.
    //  BClass object 0x690d7ff79f give resources back.
    //  exception caught: std::exception

    // using try-catch block, prevents resource leak because
    // of the stack unwinding mechanism.

    // --------------------------------------------------------
  }
*/

/*
  #include <memory>   // std::unique_ptr

  class AClass {
  public:
    AClass()
    {
      std::cout << "AClass object " 
                << this << " obtain resources.\n";
    }
    ~AClass()
    {
      std::cout << "AClass object " 
                << this << " give resources back.\n";
    }
  };

  class BClass {
  public:
    BClass()
    {
      std::cout << "BClass object " 
                << this << " obtain resources.\n";
    }
    ~BClass()
    {
      std::cout << "BClass object " 
                << this << " give resources back.\n";
    }
  };

  class CClass {
  public:
    CClass()
    {
      std::cout << "CClass object " 
                << this << " obtain resources.\n";
    }
    ~CClass()
    {
      std::cout << "CClass object " 
                << this << " give resources back.\n";
    }
  };

  void func_4()
  {
    AClass* p_a1 = new AClass;
    BClass* p_b1 = new BClass;
    throw std::exception();
    delete p_a1;
    delete p_b1;
  }

  void func_3()
  {
    auto p_c1 = new CClass;
    func_4();
    delete p_c1;
  }

  void func_2()
  {
    AClass* p_a1 = new AClass;
    func_3();
    delete p_a1;
  }

  void func_1()
  {
    BClass* p_b1 = new BClass;
    BClass* p_b2 = new BClass;
    func_2();
    delete p_b1;
    delete p_b2;
  }

  int main()
  {
    try {
      func_1();
    }
    catch (const std::exception& ex)
    {
      std::cout << "exception caught: " << ex.what() << '\n';
    }

    // output ->
    //  BClass object 0x1ea8d654450 obtain resources.
    //  BClass object 0x1ea8d64c0b0 obtain resources.
    //  AClass object 0x1ea8d64c0d0 obtain resources.
    //  CClass object 0x1ea8d649100 obtain resources.
    //  AClass object 0x1ea8d649120 obtain resources.
    //  BClass object 0x1ea8d649140 obtain resources.
    //  exception caught: std::exception

    // because of using raw pointers, 
    // after exception caught, resources will not given back.
    // resource leak will occur.
  }
*/

/*
  #include <memory>   // std::unique_ptr

  class AClass {
  public:
    AClass()
    {
      std::cout << "AClass object " 
                << this << " obtain resources.\n";
    }
    ~AClass()
    {
      std::cout << "AClass object " 
                << this << " give resources back.\n";
    }
  };

  class BClass {
  public:
    BClass()
    {
      std::cout << "BClass object " 
                << this << " obtain resources.\n";
    }
    ~BClass()
    {
      std::cout << "BClass object " 
                << this << " give resources back.\n";
    }
  };

  class CClass {
  public:
    CClass()
    {
      std::cout << "CClass object " 
                << this << " obtain resources.\n";
    }
    ~CClass()
    {
      std::cout << "CClass object " 
                << this << " give resources back.\n";
    }
  };

  void func_4()
  {
    std::unique_ptr<AClass> p_a1{ new AClass };
    std::unique_ptr<BClass> p_b1{ new BClass };
    throw std::exception();
  }

  void func_3()
  {
    std::unique_ptr<CClass> p_c1{ new CClass };
    func_4();
  }

  void func_2()
  {
    std::unique_ptr<AClass> p_a1{ new AClass };
    func_3();
  }

  void func_1()
  {
    std::unique_ptr<BClass> p_b1{ new BClass };
    std::unique_ptr<BClass> p_b2{ new BClass };
    func_2();
  }

  int main()
  {
    try {
      func_1();
    }
    catch (const std::exception& ex)
    {
      std::cout << "exception caught: " << ex.what() << '\n';
    }

    // output ->
    //  BClass object 0x1fb893fc6c0 obtain resources.
    //  BClass object 0x1fb893fc6e0 obtain resources.
    //  AClass object 0x1fb893f9100 obtain resources.
    //  CClass object 0x1fb893f9120 obtain resources.
    //  AClass object 0x1fb893f9140 obtain resources.
    //  BClass object 0x1fb893fc5a0 obtain resources.
    //  BClass object 0x1fb893fc5a0 give resources back.
    //  AClass object 0x1fb893f9140 give resources back.
    //  CClass object 0x1fb893f9120 give resources back.
    //  AClass object 0x1fb893f9100 give resources back.
    //  BClass object 0x1fb893fc6e0 give resources back.
    //  BClass object 0x1fb893fc6c0 give resources back.
    //  exception caught: std::exception

    // because of using smart pointers,
    // after exception caught, resources will be given back.
    // NO resource leak will occur.
  }
*/

/*
                      ---------------------
                      | rethrow statement |
                      ---------------------
*/

/*
  void bar()
  {
    try {
      throw std::out_of_range{ "value out of range" };
    }
    catch (const std::exception& ex) {
      std::cout << "exception caught in `bar` function\n";
      std::cout << "address of exception object = " << &ex << '\n';

      throw ex;
      // "ex"'s type is std::out_of_range but 
      // it will be copied to a new exception object
      // and its type is std::exception because of 
      // std::exception is a base class of std::out_of_range
      // object slicing will occur.
    }
  }

  int main()
  {
    using namespace std;

    try {
      bar();
    }
    catch (const std::out_of_range& ex)
    {
      cout << "std::out_of_range exception caught in `main` function\n";
      cout << "address of exception object = " << &ex << '\n';
    }
    catch (const std::exception& ex)
    {
      cout << "std::exception exception caught in `main` function\n";
      cout << "address of exception object = " << &ex << '\n';
    }

    // output ->
    //  exception caught in `bar` function
    //  address of exception object = 0x2225deef8f0
    //  std::exception exception caught in `main` function
    //  address of exception object = 0x2225deec640
  }
*/


/*
  void bar()
  {
    try {
      throw std::out_of_range{ "value out of range" };
    }
    catch (const std::exception& ex) {
      std::cout << "exception caught in `bar` function\n";
      std::cout << "address of exception object = " << &ex << '\n';
      throw;  // rethrow statement

      // when rethrow statement used,
      // object slicing will not be occured
      // we will send the same exception object.
    }
  }

  int main()
  {
    using namespace std;

    try {
      bar();
    }
    catch (const std::out_of_range& ex)
    {
      cout << "std::out_of_range exception caught in `main` function\n";
      cout << "address of exception object = " << &ex << '\n';
    }
    catch (const std::exception& ex)
    {
      cout << "std::exception exception caught in `main` function\n";
      cout << "address of exception object = " << &ex << '\n';
    }

    // output ->
    //  exception caught in `bar` function
    //  address of exception object = 0x19d06c3f2d0
    //  std::out_of_range exception caught in `main` function
    //  address of exception object = 0x19d06c3f2d0
  }
*/

/*
  #include <exception>  // std::exception

  int func_2()
  {
    std::cout << "func_2 started\n";
    throw std::exception{};
  }

  void func_3()
  {
    std::cout << "func_3 started\n";
    throw;  // rethrow statement
  }

  void func_1()
  {
    std::cout << "func_1 started\n";

    try {
      func_2();
    }
    catch (const std::exception& ex)
    {
      std::cout << "catch block `func_1` function\n";
      std::cout << "address of exception object = " << &ex << '\n';
      func_3(); 
      throw;  // rethrow statement
    }
  }

  int main()
  {
    std::cout << "main started\n";

    try {
      func_1();
    }
    catch (const std::exception& ex)
    {
      std::cout << "catch block `main` function\n";
      std::cout << "address of exception object = " << &ex << '\n';
    }

    // output ->
    //  main started
    //  func_1 started
    //  func_2 started
    //  catch block `func_1` function
    //  address of exception object = 0x1c0c8be26c0
    //  func_3 started
    //  catch block `main` function
    //  address of exception object = 0x1c0c8be26c0
  }
*/

/*
  void func_1()
  {
    throw;  // rethrow statement
  }

  int main()
  {
    func_1(); // output -> terminate called without an active exception

    // rethrow statement without an exception
    // will call std::terminate function.
  }
*/

/*
                    ------------------------
                    | exception dispatcher |
                    ------------------------
*/

/*
  // both "func_operation_1" and "func_operation_2" functions
  // are handling errors in same way.

  void func_1(){}
  void func_2(){}
  void func_handle_network_error(){}
  void func_handle_invalid_data(){}
  void func_handle_too_much_data(){}

  class NetworkError{};
  class InvalidData{};
  class TooMuchData{};

  void func_operation_1()
  {
    try {
      func_1();
    }
    catch (const NetworkError& exc)
    {
      func_handle_network_error();
    }
    catch (const InvalidData& exc)
    {
      func_handle_invalid_data();
    }
    catch (const TooMuchData& exc)
    {
      func_handle_too_much_data();
    }
  }

  void func_operation_2()
  {
    try {
      func_2();
    }
    catch (const NetworkError& exc)
    {
      func_handle_network_error();
    }
    catch (const InvalidData& exc)
    {
      func_handle_invalid_data();
    }
    catch (const TooMuchData& exc)
    {
      func_handle_too_much_data();
    }
  }
*/

/*
  void func_1(){}
  void func_2(){}
  void func_handle_network_error(){}
  void func_handle_invalid_data(){}
  void func_handle_too_much_data(){}

  class NetworkError{};
  class InvalidData{};
  class TooMuchData{};

  void func_operation_1()
  {
    try {
      func_1();
    }
    catch (...) // catch all exceptions
    {
      handle_exceptions();
    }
  }

  void func_operation_2()
  {
    try {
      func_2();
    }
    catch (...) // catch all exceptions
    {
      handle_exceptions();
    }
  }
  void handle_exceptions()
  {
    try
    {
      throw;	// rethrow statement
      // catch-block will be catch the rethrown exception.
    }
    catch (const NetworkError& exc)
    {
      func_handle_network_error();
    }
    catch (const InvalidData& exc)
    {
      func_handle_invalid_data();
    }
    catch (const TooMuchData& exc)
    {
      func_handle_too_much_data();
    }
  }
*/


/*
                    ----------------------------
                    | translating an exception |
                    ----------------------------
*/

/*
  - translating an exception is converting one exception type 
    to another. 
    i.e, in a GUI application std::bad_alloc exception thrown
    but it is not logical to send that exception to user.
    instead sending an exception that user can understand.

*/

/*
  #include <new> // std::bad_alloc

  class BadGuiComponent : public std::exception{};
  
  void func_2()
  {
    throw std::bad_alloc{};
  }

  void func()
  {
    try {
      func_2();
    }
    catch (const std::bad_alloc&) {
      throw BadGuiComponent{};
    }
  }
*/

/*
                    ------------------------
                    | exception guarantees |
                    ------------------------
*/

/*
  <--- check exceptions_cpp.pdf file --->

  No throw guarantee
  -> Operation will not throw
    - C functions like "fclose"
    - std::swap(a,b)
    - memory deallocation, clean up functions
    - move ctor, move assignment

  Strong exception safety
  -> Operation will either succeed, or be rolled back
    - std::vector::push_back functions

  Basic exception safety
  -> No resource leaks, invariants preserved, 
    but operation can be half done.

  No exception safety
  -> If function throw exceptions, std::terminate will be invoked
      (segfaults, memory corruption)
*/

/*
  // Strong exception safety 

  #include <string>
  #include <utility>  // std::swap
  #include <vector>

  struct Map {

    std::vector<int> keys;
    std::vector<std::string> values;

    // -------------------------------------------------------

    void insert_1(int key, std::string value)
    {
      auto new_keys = keys;
      auto new_values = values;	

      new_keys.push_back(key);    
      // can throw, but object is not modified yet.

      new_values.push_back(value);
      // can throw, but object is not modified yet.

      std::swap(new_keys, keys);
      // std::swap does not throw (no throw guarantee)
      std::swap(new_values, values);	
      // std::swap does not throw (no throw guarantee)
    }

    // insert_1 function has strong exception safety guarantee.
    // if an exception thrown in push_back, object will not be modified.
    // so invariants will not be broke.
    // if an exception is not thrown, object will be modified.
    // because of std::swap has no throw guarantee.

    // -------------------------------------------------------

    void insert_2(int key, std::string value)
    {
      keys.push_back(key);

      try
      {
        values.push_back(value);
      }
      catch(...)
      {
        keys.pop_back();
      }
    }

    // if `keys.push_back(key);` throws an exception,
    // nothing will be modified.
    // variants will be preserved.

    // if `values.push_back(value);` throws an exception,
    // it will be catched and `keys.pop_back();` will be called.
    // invariants will be preserved.

    // -------------------------------------------------------
  };
*/

/*
  // Basic exception safety 

  // -------------------------------------------------------

  #include <vector>
  #include <string>

  // -------------------------------------------------------

  struct A {};

  void half_done_copy(std::vector<A>& vec_dest,
                    const std::vector<A>& vec_source)
  {
    for (const auto& elem : vec_source)
      vec_dest.push_back(elem);
  }

  // if vector's copy constructor is throw an exception
  // while copying 3rd element, 1st, 2nd elements WILL be copied.
  // but 3rd and the rest elements WILL NOT be copied.
  // invariants preserved but operation is half done.

  // -------------------------------------------------------

  struct Map
  {
    std::vector<int> keys;
    std::vector<std::string> values;

    void insert(int key, std::string value)
    {
      keys.push_back(key);
      values.push_back(value);
    }
  };

  // if `values.push_back(value)` throws an exception,
  // because of `keys.push_back(key)` is already called,
  // invariants changed.
  // this function is NOT exception safe. 
  // not giving basic exception safety guarantee.

  // -------------------------------------------------------
*/

/*
  // No exception safety

  char* no_safety(const A& a)
  {
    char* buffer = new char[100];
    a.fill(buffer);
    return buffer;
  }

  // if a.fill(buffer) throws an exception,
  // buffer can not be deleted.
  // resource leak will occur.
*/

/*
                      ----------------------
                      | `noexcept` keyword |
                      ----------------------
*/

/*
                      ------------------------
                      | `noexcept` specifier |
                      ------------------------
*/

/*
  void foo(int) noexcept; // noexcept specifier.
  // "foo" function is giving a no throw guarantee.

  virtual const char* what() const noexcept
  // "what" function is giving a no throw guarantee.
*/

/*

  void func() noexcept(sizeof(int) > 2);
  // if sizeof(int) is greater than 2 byte,
  // "func" function will give a no throw guarantee.

  void foo() noexcept;
  void foo() noexcept(true);
  // Those 2 lines are equaivalent.

  void bar();
  void bar() noexcept(false);
  // Those 2 lines are equaivalent.
*/

/*
  // `noexcept` specifier is a part of function SIGNATURE.

  // file.h
  // ----------------
  void foo() noexcept; // "foo" function's declaration

  // because of `noexcept` is part of the signature, 
  // `noexcept` specifier should also be used in function definition.

  // file.cpp
  // ----------------
  void foo() noexcept // "foo" function's definition
  {
    std::cout << "foo\n";
  }

  int main()
  {
    foo();  // output -> foo
  }
*/

/*
  // if a function that has a no throw guarantee throws an exception,
  // std::terminate will be invoked.

  void throw_exception()
  {
    throw std::runtime_error{ "`throw_exception` throws" };
  }

  void func() noexcept
  {
    throw_exception();
  }
  // "func" function is giving a no throw guarantee.

  int main()
  {
    try {
      func();
    }
    catch (const std::exception& ex) {
      std::cout << "exception caught: " << ex.what() << '\n';
    }

    // terminate called after throwing 
    // an instance of 'std::runtime_error'
    // what():  `throw_exception` throws
  }
*/

/*
                      -----------------------
                      | `noexcept` operator |
                      -----------------------
*/

/*
  class Myclass{};

  void func() noexcept(noexcept(Myclass{}));

  // 1st `noexcept` is a specifier.
  // 2nd `noexcept` is an operator.

  // if Myclass's default ctor is giving a no throw guarantee,
  // noexcept(Myclass{}) will be evaluated as true.

  int main()
  {
    int x = 10;
    constexpr bool b1 = noexcept(x + 5);    // b1 -> true

    // "noexcept(x + 5)" is a constant expression.
    // its data type is bool.

    // because of integer addition is a no throw operation,
    // b1 will be evaluated as true.
  }
*/

/*
  int main()
  {
    int x = 10;
    int y = 4;

    constexpr auto b = noexcept(++x / ++y); // b -> true

    std::cout << "x = " << x << '\n'; // output -> x = 10
    std::cout << "y = " << y << '\n'; // output -> y = 4

    // `noexcept` operator creates an unevaluated context.
    // expression(noexcept operators operand) is not evaluated.
  }
*/

/*
  class Myclass {
  public:
    Myclass();    // user declared to be defined
    ~Myclass();   // user declared to be defined
  };

  int main()
  {
    Myclass mx;
    constexpr auto b = noexcept(mx.~Myclass()); // b -> true

    // destructors have no throw guarantee.
    // if an exception thrown in a destructor,
    // it will directly invoke "std::terminate" function.

    // desturctor is called,
    // -  at the end of object's life.
    // -  an exception thrown and then caugth in try-catch block
    //    stack unwinding phase started and dtor called.

    // In destructor it is possible to catch the exception
    // with `try-catch` block.
    // if exception is not caught, error will try to propagate
    // so "std::terminate" will be invoked.
  }
*/

/*
  class Base {
  public:
    virtual void func() noexcept;	
    // Base classes virtual member function "func"
    // is giving a no throw guarantee.
  };

  class Der : public Base {
  public:
    virtual void func() override; // syntax error
    // error: looser exception specification 
    // on overriding virtual function.
  };
*/

/*
  class Base {
  public:
    virtual void func();
  };

  class Der : public Base {
  public:
    virtual void func() noexcept override;	
    // Der's virtual override "func" function
    // is giving a no throw guarantee.
  };
*/

/*
  void func(int) noexcept;
  void bar(int);

  int main()
  {
    // -------------------------------------------------------

    void (*fp1)(int);
    void (*fp2)(int) noexcept;
    // `noexcept` operator can be used in 
    // function pointer declaration and definition.

    // -------------------------------------------------------

    void (*fp3)(int) = &bar;   // VALID
    fp3 = &func;               // VALID
    // function calls done with using "fp3" function pointer
    // is not giving a no throw guarantee.

    // but it can hold the address of a function
    // that will have a no throw guarantee.

    // -------------------------------------------------------

    void (*fp4)(int)noexcept = &func; // VALID  
    // function calls done with using "fp4" function pointer
    // is giving a no throw guarantee.

    fp4 = &bar; // syntax error
    // error: invalid conversion from 'void (*)(int)' to 
    // 'void (*)(int) noexcept'

    // -------------------------------------------------------
  }
*/

/*
                  -----------------------------
                  | constructors & exceptions |
                  -----------------------------
*/


/*
  #include <stdexcept>  // std::runtime_error

  class Myclass {
  private:
    int m_x;  
  public:
    Myclass(int x)  : m_x{ x }
    {
      std::cout << "[0] - Myclass(int) started\n";
      if (x > 10)
        throw std::runtime_error{ "throw exception in Myclass(int)" };

      // because of Myclass(int) constructor throws an exception,
      // before its scope ends, 
      // m_x data member will not become alive
      // so its ~Myclass() destructor will not be called.
    }
    ~Myclass()
    {
      std::cout << "~Myclass()\n";
    }
  };

  int main()
  {
    try {
      Myclass m1{ 45 };
    }
    catch (const std::exception& ex) {
      std::cout << "exception caught: " << ex.what() << '\n';
    }

    // output ->
    //  [0] - Myclass(int) started
    //  exception caught: throw exception in Myclass(int)
  }
*/

/*
  #include <stdexcept>  // std::runtime_error

  class Myclass {
  private:
    int* mp_arr;
  public:
    Myclass(int x)
    {
      std::cout << "[0] - Myclass(int) started\n";

      mp_arr = new int[x];
      throw std::runtime_error{ "throw exception in Myclass(int)" };
      // if Myclass(int) throws an exception,
      // because of ~Myclass() destructor can not be called
      // resource leak will occur.
    }
    ~Myclass()
    {
      std::cout << "[1] - ~Myclass()\n";
      delete mp_arr;
    }
  };

  int main()
  {
    try {
      Myclass x{ 45 };
    }
    catch (const std::exception& ex){
      std::cout << "exception caught: " << ex.what() << '\n';
    }
    // output ->
    //  [0] - Myclass(int) started
    //  exception caught: throw exception in Myclass(int)
  }
*/

/*
  #include <stdexcept>  // std::runtime_error

  class Member {
  public:
    Member()
    {
      std::cout << "[0] - Member::Member() started\n";

      throw std::runtime_error{ "throw exception in Member::Member()" };
      // becuase of Member objects constructor throws an exception
      // Member object will not become alive.
      // Myclass object will not become alive.
      // Member and Myclass objects destructors will not be called.

      std::cout << "[1] - Member::Member() ends\n";
    }

    ~Member()
    {
      std::cout << "Member::~Member() destructor\n";
    }
  };

  class Myclass {
  private:
    Member m_Member;
  public:
    Myclass()
    {
      std::cout << "Myclass::Myclass() constructor\n";
    }

    ~Myclass()
    {
      std::cout << "Myclass::~Myclass() destructor\n";
    }
  };

  int main()
  {
    try{
      Myclass mx;
    }
    catch (const std::exception& ex)
    {
      std::cout << "exception caught: " << ex.what() << '\n';
    }
    // output ->
    //  [0] - Member::Member() started
    //  exception caught: throw exception in Member::Member()
  }
*/

/*
  class Member {
  public:
    Member()
    {
      static int counter = 0;

      std::cout << "[0] - Member::Member() started, this = " 
                << this << '\n';

      if (counter == 1)
        throw std::runtime_error{ "throw exception in Member::Member()" };
      

      std::cout << "[1] - Member::Member() ends\n";
      ++counter;

      // if m_Member_1 becomes alive and 
      // m_Member_2 ctor throws an exception,
      // in stack unwinding phase m_Member_1's dtor WILL be called
      // but m_Member_2's dtor WILL NOT be called.
    }
    
    ~Member()
    {
      std::cout << "Member::~Member() destructor, this = " 
                << this << '\n'; 
    }
  };

  class Myclass {
  private:
    Member m_Member_1, m_Member_2;
  public:
    Myclass()
    {
      std::cout << "Myclass::Myclass() constructor\n";
    }
    ~Myclass()
    {
      std::cout << "Myclass::~Myclass() destructor\n";
    }
  };

  int main()
  {
    try {
      Myclass mx; 
    }
    catch (const std::exception& ex)
    {
      std::cout << "exception caught: " << ex.what() << '\n';
    }

    // output ->
    //  [0] - Member::Member() started, this = 0x1001ff6a6
    //  [1] - Member::Member() ends
    //  [0] - Member::Member() started, this = 0x1001ff6a7
    //  Member::~Member() destructor, this = 0x1001ff6a6
    //    --> stack unwinding phase
    //  exception caught: throw exception in Member::Member()
  }
*/

/*
  class Member {
  public:
    Member()
    {
      std::cout << "[0] - Member::Member() started\n";
      std::cout << "[1] - Member::Member() ends\n";
    }
  };

  class Myclass {
  private:
    Member* mp_Member;
  public:
    Myclass() : mp_Member(new Member)
    {
      std::cout << "[0] - Myclass::Myclass() started\n";
      throw std::runtime_error{ "throw exception in Myclass::Myclass()"};

      // after mp_Member objects initialization
      // if Myclass::Myclass() throws an exception,
      // Myclass object WILL NOT become alive.
      // Myclass::~Myclass() destructor WILL NOT be called.
      // so mp_Member object WILL NOT be deleted.
      // resource leak will occur.

      std::cout << "[1] - Myclass::Myclass() ends\n";
     }
    ~Myclass()
    {
      std::cout << "Myclass::~Myclass() destructor\n";
      delete mp_Member;
    }
  };

  int main()
  {
    try {
      Myclass mx;
    }
    catch (const std::exception& ex)
    {
      std::cout << "exception caught: " << ex.what() << '\n';
    }

    // output -> 
    //  [0] - Member::Member() started
    //  [1] - Member::Member() ends
    //  [0] - Myclass::Myclass() started
    //  exception caught: throw exception in Myclass::Myclass()
  }
*/

/*
  class Myclass {
  public:
    Myclass()
    {
      std::cout << "Myclass ctor\n";
      throw std::runtime_error{ "exception in Myclass ctor" };
    }
    ~Myclass()
    {
      std::cout << "Myclass dtor\n";
    }
  };

  int main()
  {
    try {
      Myclass* p_m1 = new Myclass;
    }
    catch (const std::exception& ex)
    {
      std::cout << "exception caught: " << ex.what() << '\n';
    }

    // 1st phase : "operator new" function
    // memory allocated for Myclass object in heap 
    // 2nd phase : "Myclass::Myclass()" constructor

    // if an exception thrown in Myclass::Myclass() constructor,
    // phase 2 becomes INCOMPLETE.

    // !! compiler is responsible for 1st phase's memory deallocation.
  }
*/

/*
                      ---------------------
                      | exception classes |
                      ---------------------
*/

/*
  // std::bad_alloc exception

  #include <vector>

  class Myclass {
  public:
    unsigned char m_buffer[1024 * 1024]{};
  };

  std::vector<Myclass*> g_vec;

  int main()
  {
    try
    {
      for (int i = 0; i < 100'000'000; ++i)
      {
        g_vec.push_back(new Myclass);
        std::cout << i << '\n';
      }
    }
    catch (const std::bad_alloc& ex)
    {
      std::cout << "exception caught: " << ex.what() << '\n';
    }
    catch (const std::exception& ex)
    {
      std::cout << "exception caught: " << ex.what() << '\n';
    }

    // output ->
    //  ...
    //  82183
    //  82184
    //  82185
    //  exception caught: std::bad_alloc
  }
*/

/*
  // std::bad_cast exception

  class Base {
  public:
    virtual ~Base() {};
  };
  // Base is a polymorphic class.

  class Der_1 : public Base {};
  class Der_2 : public Base {};

  void foo(Base& ref_base)
  {
    Der_1& d1 = dynamic_cast<Der_1&>(ref_base);
  }

  int main()
  {
    Der_2 d2_x;

    try {
      foo(d2_x);
    }
    catch (const std::bad_cast& ex)
    {
      std::cout << "exception caught: " << ex.what() << '\n';
    }
    catch (const std::exception& ex)
    {
      std::cout << "exception caught: " << ex.what() << '\n';
    }

    // output -> exception caught: std::bad_cast
  }
*/

/*
  // std::bad_typeid exception

  class Base {
  public:
    virtual ~Base() {};
  };

  class Der : public Base {};

  void foo(Base* p_Base)
  {
    if (typeid(*p_Base) == typeid(Der))
      std::cout << "Der object\n";
  }

  int main()
  {
    Der* p_d1{};

    try {
      foo(p_d1);
    }
    catch (const std::bad_typeid& ex)
    {
      std::cout << "Exception caught: " << ex.what() << '\n';
    }
    catch (const std::exception& ex)
    {
      std::cout << "Exception caught: " << ex.what() << '\n';
    }
  }
*/

/*
                      ----------------------
                      | function try block |
                      ----------------------
                  generally used in constructors
*/

/*
  int func(int param_var)
  try {
    int x = 5;
  }
  catch (const std::exception&)
  {
    ++x;  // syntax error
    // error: 'x' was not declared in this scope
    // local try block variables are not accessible in catch block.

    auto y = param_var;
    // parameter variable is accessible in catch block.

    return 2;
    // return statement in catch block is VALID
  }
*/

/*
  #include <stdexcept>  // std::runtime_error

  class Myclass {
  public:
    Myclass()
    {
      std::cout << "[0] Myclass default constructor started\n";
      std::cout << "[1] Myclass default constructor end\n";
    }
    Myclass(const Myclass&)
    {
      std::cout << "[0] - Myclass copy constructor started\n";

      throw std::runtime_error{ "exception in Myclass copy constructor" };
      
      std::cout << "[1] - Myclass copy constructor end\n";
    }
  };

  int func(Myclass)
  try {
  }
  catch (const std::exception& ex)
  {
    std::cout << "exception caught: " << ex.what() << '\n';
  }

  // if Myclass's copy constructor throws an exception,
  // function try block WILL NOT catch that exception.
  // so std::terminate will be invoked.

  int main()
  {
    Myclass mx;
    func(mx);

    // output ->
    //  [0] Myclass default constructor started
    //  [1] Myclass default constructor end
    //  [0] - Myclass copy constructor started
    //  terminate called after throwing an instance 
    //  of 'std::runtime_error'
    //  what():  exception in Myclass copy constructor
  }
*/

/*
  #include <stdexcept>  // std::runtime_error

  class Member {
  public:
    Member(int x)
    {
      using namespace std;

      if (x > 10) 
        throw runtime_error{ "exception error in Member default ctor" };
    }
  };

  class Myclass {
  private:
    Member m_Member;
  public:
    Myclass(int x) : m_Member{ x }  
    {
    	try {
        
    	}
    	catch (const std::exception& ex)
    	{
      std::cout << "catch block in Myclass constructor\n";
    		std::cout << "exception caught: " << ex.what() << '\n';
    	}
    }
    // IT IS try-catch block in Myclass's default ctor scope.
    // IT IS NOT function try block.

    // in m_Member objects initialization phase 
    // exception thrown in Member classes ctor.
    // and exception CAN NOT be catched 
    // when Myclass ctor is not a function try block.
  }; 

  int main()
  {
    try {
      Myclass mx{ 12 };
    }
    catch (const std::exception& ex)
    {
      std::cout << "catch block in main function\n";
      std::cout << "exception caught: " << ex.what() << '\n';
    }

    // output ->
    //  catch block in main function
    //  exception caught: exception error in Member default ctor

    // exception will propagate to main function.
  }
*/

/*
  #include <stdexcept>  // std::runtime_error

  class Member {
  public:
    Member(int x)
    {
      using namespace std;

      if (x > 10) 
        throw runtime_error{ "exception error in Member default ctor" };
    }
  };

  class Myclass {
  private:
    Member m_Member;
  public:
    Myclass(int x) try : m_Member{ x }
    {

    }
    catch (const std::exception& ex)
    {
      std::cout << "catch block in Myclass constructor\n";
      std::cout << "exception caught: " << ex.what() << '\n';
      // if exception is not handled in catch block,
      // compiler will write a rethrow statement.
      // that will invoke "std::terminate" function.
    }
    // IT IS function try block.
  };


  int main()
  {
    try {
      Myclass mx{ 12 };
    }
    catch (const std::exception& ex)
    {
      std::cout << "catch block in main function\n";
      std::cout << "exception caught: " << ex.what() << '\n';
    }

    // output ->
    //  catch block in Myclass constructor
    //  exception caught: exception error in Member default ctor
    //  catch block in main function
    //  exception caught: exception error in Member default ctor
  }
*/