#include <iostream>

/*
                ========================================
                | Concurrency (eşzamanlılık / eşgüdüm) |
                ========================================
*/

/*
------------------------------------------------------------------------
concurrency : 
  - işlerin "belirli bir zaman diliminde(aralığında)" birlikte yapılması.
  - iş parçalarını birbirinden bağımsız parçalara ayırmak.

  - bir programın concurrent olması, birden fazla görevi belirli bir 
    zaman dilimi içinde parçalara ayırarak yönetebilmesi, 
    gerçekleştirebilmesi anlamına gelir.

  - aynı zaman dilimi içerisinde yapılması gereken işlerin yönetilmesi
    (Managing tasks that need to be done within the same time period)
    i.e orchestra playing together 

  - an application can be concurrent but not parallel.
  - more than one task needed.

------------------------------------------------------------------------
paralelism : 
  - simultaneously doing the different jobs 
  - ilişkili olabilecek işlemlerin aynı zamanda yürütülmesi.
  - aynı anda birden fazla işlem yapılması.
  - need more than one core.

  - for job to done faster (işin daha hızlı yapılması için)
    i.e splitting a vector(1'000'000 elem) in 4 different threads.
    and sorting them in parallel. 

  - an application can be parallel but not concurrent.
    (1 task's subtasks can be divided into different threads)

------------------------------------------------------------------------
- an application can both be concurrent and parallel.
  different tasks are done in different cores at the same time.

- an application can be neither concurrent nor parallel.
  sequential execution of tasks.
------------------------------------------------------------------------
*/

/*
                        -------------------
                        | <thread> module |
                        -------------------
*/

/*
  #include <thread>

  int main(){
    // if we want to run a task as a thread, we need to have an object
    // from thread class type.

    std::thread t;  
    // default initialized thread object 
    // does not have work load to execute.

    // work load(iş yükü) that thread will execute is a function.
    // 1. can be a global function
    // 2. can be a static member function of a class
    // 3. can be a non-static member function of a class
    // 4. can be an operator function of a functor class
    // 5. can be a closure type function 
    //    obtained from a lambda expression
  }
*/

/*
  #include <thread>
  #include <chrono>

  int main(){
    std::cout << std::boolalpha;

    std::thread t;
    std::cout << t.joinable() << '\n';  // output -> false
    // thread does not have a workload
  }
*/

/*
  #include <thread>
  #include <chrono>

  void func(){
    std::cout << "func\n";
    std::this_thread::sleep_for(std::chrono::seconds(2));
  }

  int main(){
    std::cout << std::boolalpha;

    std::thread t{func};
    std::cout << t.joinable() << '\n';  
    // output -> 
    //  true
    //  func

    t.join(); 

    std::cout << t.joinable() << '\n';  
    // output -> false
  }
*/

/*
  #include <thread>
  #include <chrono>

  void func(){
    for (int i = 0; i < 1'000'000; ++i)
      std::cout << '*';
  }

  int main(){
    using namespace std;

    thread t{func};
    // for this thread object to be generated, 
    // some operating system code need to be executed.
    // after those OS code is executed,
    // work load of thread will start to execute.


    //  <-----LINE 1----->  
    // when LINE 1 is being executed 
    // both "t" thread and main thread are running concurrently.
    // but "t" thread might already been finished in LINE 1.

    for (int i = 0; i < 1'000'000; ++i)
      cout << '.';
    
    t.join();
    // <-----LINE 2----->
    // when LINE 2 is being executed
    // main thread will be blocked and wait for "t" thread to finish.
    // becuase of t.join() function has been called call.
  }
*/

/*
  #include <thread>
  #include <chrono>

  void func(){
    for (int i = 0; i < 1'000'000; ++i)
      std::cout << '*';
  }

  void foo(){
    for (int i = 0; i < 1'000'000; ++i)
      std::cout << '?';
  }

  void bar(){
    for (int i = 0; i < 1'000'000; ++i)
      std::cout << '-';
  }

  int main(){
    using namespace std;

    // <-----LINE_1----->
    // in LINE_1 only main thread is running.

    thread t1{func};
    // <-----LINE_2----->
    // - in LINE_2 both main and t1 threads are running concurrently.
    // - t1 thread might already been finished depending on its workload.
    
    thread t2{foo};
    // <-----LINE_3----->
    // - in LINE_3 both main, t1 and t2 threads 
    // are running concurrently.
    // - t1 and t2 threads might already been finished 
    // depending on their workloads.
    
    thread t3{bar};
    // <-----LINE_4----->
    // - in LINE_4 both main, t1, t2 and t3 threads 
    // are running concurrently.
    // - t1, t2 and t3 threads might already been finished 
    // depending on their workloads.

    for (int i = 0; i < 1'000'000; ++i)
      cout << '.';
    
    t1.join();
    t2.join();
    t3.join();
  }
*/

/*
  // we gave a callable to the thread object as a work load
  // when thread object's destructor is called
  // if that thread object is still joinable, 
  // std::terminate() will be called.

  #include <thread>
  #include "nutility.h" // my_terminate

  void func(){
    for (int i = 0; i < 1'000'000; ++i)
      std::cout << '*';
  }

  int main(){
    using namespace std;
    set_terminate(my_terminate);

    thread t{func};

    std::cout << "thread objects destructor will be called\n";
  }
  // output -> 
  //  thread objects destructor will be called
  //  std::terminate cagrildi....
  //  myterminate cagrildi....
  //  std::abort() cagrildi
*/

/*
  #include <thread>

  void func(){
    for (int i = 0; i < 1'000'000; ++i)
      std::cout << '*';
  }

  int main(){
    using namespace std;

    thread t{func};

    t.detach();
    // t thread object is detached from the main thread
    // and will work in the background.
  }
*/

/*
  BOOK advice : anthony williams - concurrency in action
*/

/*
  // to call join() function of the thread object
  // thread must be joinable (thread object must have a work load)
  // else it will throw an exception

  #include <thread>

  int main(){
    using namespace std;

    thread tx;

    try{
      tx.join();  
    }
    catch (const std::exception& ex){
      cout << "exception caught : " << ex.what() << '\n';
    }
    // output -> exception caught : Invalid argument
  }
*/

/*
  #include <thread>

  void foo(){}

  int main(){
    using namespace std;

    thread tx{foo};
    tx.join();  

    // <---- LINE_1 ---->
    // thread object "tx" is not joinable in LINE_1

    try{
      tx.join();  // calling join() function again
    }
    catch (const std::exception& ex){
      cout << "exception caught : " << ex.what() << '\n';
    }
    // output -> exception caught : Invalid argument
  }
*/

/*
  - when thread objects detach() function is called
    if one of the variable's lifetime is ended 
    that the threads workload is using
    it will be an undefined behaviour(ub).
*/

/*
  - thread class is not a template 
    but thread classes constructor is a template
    CTOR(callable, ...args)
    args will be perfect forwarded to the callable.

  #include <thread>

  void foo(int x){
    std::cout << "foo x = " << x << '\n';
  }

  void func(int x, int y, int z){
    std::cout << "func x = " << x 
              << " y = " << y 
              << " z = " << z << '\n';
  }

  int main(){
    using namespace std;

    thread t1{foo, 10}; 
    t1.join();
    // output -> foo x = 10

    thread t2{func, 10, 20, 30};
    t2.join();
    // output -> func x = 10 y = 20 z = 30
  }
*/

/*
  // some function's parameters are references

  // if we need to send the objects itself to the threads workload  
  // we need to use reference wrapper class.

  // eğer thread tarafından çalıştırılacak iş yükü olan fonksiyona 
  // bir nesnenin kendisini göndermek istiyorsak,
  // bu durumda reference wrapper sınıfını kullanmamız gerekmektedir.

    #include <thread>
    #include <vector>
    #include <functional>   // std::ref

    void foo(const std::vector<int>& ivec){
      for (const auto val : ivec)
        std::cout << val << ' ';
    } // foo functions parameter is const reference

    int main(){
      using namespace std;

      vector<int> ivec{ 1, 2, 3, 4, 5 };

      thread t1{ foo, ivec };             
      // ivec will be copied

      thread t2{ foo, std::ref(ivec) };   
      // ivec objects itself will be sent

      t1.join();
      t2.join();
    }
*/

/*
  #include <thread>
  #include <vector>

  void foo(std::vector<int> ivec){
    for (const auto val : ivec)
      std::cout << val << ' ';
  } // parameter is not a reference

  int main(){
    using namespace std;

    vector<int> ivec{ 1, 2, 3, 4, 5 };

    thread t1{ foo, ivec };  // ivec will be copied
    t1.join();
  }
*/

/*
  #include <thread>
  #include <vector>

  void foo(std::vector<int>& ivec){
    for (const auto val : ivec)
      std::cout << val << ' ';
  } // foo functions parameter is LValue reference

  int main(){
    using namespace std;

    vector<int> ivec{ 1, 2, 3, 4, 5 };

    thread t1{ foo, ivec };  // SYNTAX ERROR
    t1.join();
  }
*/

/*
  #include <thread>
  #include <vector>
  #include <utility>   // std::move

  void foo(std::vector<int>&& ivec){
    for (const auto val : ivec)
      std::cout << val << ' ';
  } // bar function's parameter is RValue reference

  int main(){
    using namespace std;

    vector<int> ivec{ 1, 2, 3, 4, 5 };

    thread t1{ foo, std::move(ivec) }; // ivec will be moved
    t1.join();

    std::cout << "ivec.size() = " << ivec.size() << '\n';
    // output -> ivec.size() = 0
  }
*/

/*
  #include <thread>
  #include <utility>      // std::move
  #include <functional>   // std::ref 

  class Myclass{
  public:
    Myclass() = default;

    Myclass(const Myclass&)
    {
      std::cout << "Myclass copy ctor\n";
    }

    Myclass(Myclass&&)
    {
      std::cout << "Myclass move ctor\n";
    }
  };

  void func(const Myclass&){}

  void foo(Myclass&&){}

  int main(){
    using namespace std;

    Myclass mx;

    thread tx{ func, mx };  
    tx.join();  // output -> Myclass copy ctor

    thread ty{ func, std::ref(mx) };  
    ty.join();  // output -> empty

    thread tz{ foo, std::move(mx) };
    tz.join();  // output -> Myclass move ctor
  }
*/

/*
  // function's parameter is out parameter

  #include <thread>

  void foo(int& r){
    ++r;
  }

  int main(){
    using namespace std;

    int x{ 43 };

    thread tx{ foo, ref(x) };
    tx.join();

    std::cout << "x = " << x << '\n';   // output -> x = 44
  }
*/

/*
  #include <thread>

  void foo(int x){
    std::cout << "x = " << x << '\n';
  }

  int main(){
    using namespace std;

    auto fp = foo;

    thread tx{ fp, 10 };    
    // thread's workload is a function pointer(as a callable)

    tx.join();  // output -> x = 10 
  }
*/

/*
  #include <thread>

  class Functor{
  public:
    void operator()(int x) const {
      std::cout << "x = " << x << '\n';
    }
  };

  int main(){
    using namespace std;

    Functor f;

    thread tx{ f, 12 };
    // thread's workload is a functor object
    tx.join();  // output -> x = 12
  }
*/

/*
  #include <thread>

  class Functor{
  public:
    void operator()() const {
      std::cout << "Functor::operator()()\n";
    }
  };

  int main(){
    using namespace std;

    thread tx{ Functor{} };
    tx.join();  // output -> Functor::operator()()

    thread ty( Functor() ); 
    ty.join();  // syntax error 
    // most vexing parse

    // warning: parentheses were disambiguated 
    // as a function declaratio
  }
*/

/*
  #include <thread>

  int main(){
    using namespace std;

    thread tx{ [](int x){
      std::cout << "x = " << x << '\n'; }, 12 };

    tx.join();  // output -> x = 12
  }
*/

/*
  // if we want to use some classes 
  // non-static member function as a work load
  // we need to send threads constructor, a pointer to the object
  // as second argument(variadic parameter)

  #include <thread>
  #include <functional>  // std::ref

  class Myclass{
  public:
    Myclass() = default;
    Myclass(const Myclass&){
      std::cout << "Myclass copy ctor\n";
    }

    void func(){
      std::cout << "Myclass::func()\n";
    }
  };

  int main(){
    using namespace std;

    Myclass mx;
    thread tx{ &Myclass::func, mx };
    tx.join();  

    // Question : Is Myclass object is copied ? (YES)
    // output ->
    //  Myclass copy ctor
    //  Myclass::func()

    thread ty{ &Myclass::func, std::ref(mx) };
    ty.join();

    // Question : Is Myclass object is copied ?  (NO)
    // output -> Myclass::func()
  }
*/

/*
  #include <thread>
  #include <functional>  // std::ref

  // ostream class is not copyable
  void func(const std::ostream& os);

  int main(){
    std::thread tx{ func, std::cout };
    tx.join();  // syntax error

    std::thread ty{ func, std::ref(std::cout) };
    ty.join();    // not syntax error
  }
*/

/*
  - thread is non copyable but movable
  - when thread is joinable and moved to another thread object
    other thread object will become joinable 
    and moved thread object will become non-joinable.
*/

/*
  #include <thread>

  int main(){
    using namespace std;

    thread tx;
    thread ty(tx);  // syntax error (call to deleted copy ctor)
    // error: use of deleted function 
    // 'std::thread::thread(const std::thread&)'

    thread tz;
    tz = tx;  // syntax error (call to deleted copy assignment operator)
    // use of deleted function 
    // 'std::thread& std::thread::operator=(const std::thread&)'
  }
*/

/*
  #include <thread>
  #include <utility>  // std::move

  void func(){}

  int main(){
    using namespace std;

    thread tx{ func }; 
    cout << boolalpha << tx.joinable() << '\n';  // output -> true

    thread ty{ move(tx) };  // tx is moved to ty
    cout << boolalpha << tx.joinable() << '\n';  // output -> false
    cout << boolalpha << ty.joinable() << '\n';  // output -> true
    ty.join();

    cout << boolalpha << ty.joinable() << '\n';  // output -> false
  }
*/

/*
  #include <thread>
  #include <utility>  // std::move

  void func(std::thread t)
  {
    t.join();
  }

  void workload(){}

  int main(){
    using namespace std;

    thread tx{ workload };

    func(std::move(tx));
    func( thread{workload} ); // RValue expression
  }
*/

/*
  #include <thread>
  #include <utility>  // std::move

  std::thread make_thread()
  {
    std::thread tx{ []{ std::cout << "func\n"; } };
    // return value optimization is not guaranteed
    // Named Return Value Optimization (NRVO)

    // but if an automatic storage duration object is returned
    // move semantics will be applied.
    return tx;
  }

  int main(){
    using namespace std;

    thread t;
    t = make_thread();  // "make_thread()" is RValue expression
    t.join(); // output -> func
  }
*/

/*
  #include <thread>

  void func(std::thread&& t)
  {
    auto tx = std::move(t);
    tx.join();
  }

  int main(){
    using namespace std;

    thread tx{ []{} };
    func(std::move(tx));
  }
*/

/*
  // RAII wrapping of std::thread

  #include <thread>
  #include <utility>  // std::forward, std::move

  class JThread{
  public:
    JThread()noexcept = default;

    // member template constructor
    template <typename Function, typename... Args>  
    explicit JThread(Function&& f, Args&& ...args)
      : m_thread( std::forward<Function>(f), std::forward<Args>(args)...)
    {}

    ~JThread(){
      if (joinable())
        join();
    }

    explicit JThread(std::thread t) noexcept : m_thread{std::move(t)}{}

    JThread(JThread&& other) noexcept
      : m_thread{ std::move(other.m_thread) } {}

    JThread& operator=(JThread&& other){
      if (joinable())
        join();

      m_thread = std::move(other.m_thread);
      return *this;
    }

    bool joinable() const noexcept{
      return m_thread.joinable(); 
    }

    void join(){
      m_thread.join();
    }

    void swap(JThread& other) noexcept{
      m_thread.swap(other.m_thread);
    }

    void detach(){
      m_thread.detach();
    }

  private:
    std::thread m_thread; 
    // because of std::thread's copy ctor and copy assignment operator
    // are deleted, JThead's copy ctor and copy assignment operator
    // will be implicitly deleted by compiler.
  };
*/

/*
                  ------------------------------
                  | std::this_thread namespace |
                  ------------------------------
*/

/*
  #include <thread>

  void func(){
    // std::this_thread is a nested namespace
    std::cout << std::this_thread::get_id() << '\n';
    // output -> 2
  }

  int main(){
    using namespace std;

    thread tx{ func };

    auto id = tx.get_id();
    func(); // output -> 1 (main thread id)

    cout << typeid(id).name() << '\n';
    // output -> class std::thread::id (MSVC)
    // std::thread::id class has an operator==() function
    // std::thread::id class has an operator<<() function

    std::cout << "tx id = " << tx.get_id() << '\n'; 
    // output -> tx id = 2

    tx.join();  // output -> 2 (tx thread id)
  }
*/

/*
  #include <thread>

  std::thread::id g_id;

  void func(){
    auto id = std::this_thread::get_id();

    if (id == g_id)
      std::cout << "function called by the main thread\n";
    else
      std::cout << "function called by child thread\n";
  }

  int main(){
    g_id = std::this_thread::get_id();
    func(); // output -> function called by the main thread

    std::thread tx{ func };
    tx.join();  // output -> function called by child thread
  }
*/

/*
  çalışan threadi belirli bir süre ya da 
  belirli bir time point'e kadar 
  bloke eden sleep_for ve sleep_until fonksiyonları

  std::this_thread::sleep_for  
   blocking the current thread for a duration
  std::this_thread::sleep_until 
   blocking the current thread until a time point
*/

/*
  #include <thread>
  #include <chrono>

  void func(){
    using namespace std::chrono;
    std::this_thread::sleep_for(1s);
  }

  int main(){
    using namespace std;

    thread tx{ func };
    tx.join();
  }
*/

/*
  #include <chrono>
  #include <thread>

  auto now() { return std::chrono::steady_clock::now(); }

  auto awake_time(){
    using std::chrono::operator""ms;
    return now() + 2000ms;
  }

  int main(){
    std::cout << "Hello\n" << std::flush;
    const auto start{ now() };
    std::this_thread::sleep_until(awake_time());
    std::chrono::duration<double, std::milli> elapsed{ now() - start };
    std::cout << "Waited " << elapsed.count() << " ms\n";
  }
*/

/*
  #include <thread>
  #include <atomic>
  #include <chrono>

  // std::this_thread::yield function is "busy sleep"
  // while suggesting the OS to give the CPU to another thread

  std::atomic<bool> ga_start{ false };

  void func(char id)
  {
    using namespace std::chrono;

    while (!ga_start)
      std::this_thread::yield();

    std::this_thread::sleep_for(500ms);
    std::cout << id << '\n';
  }

  int main(){
    std::thread tArr[26];

    for (char i{'A'}; auto& tx : tArr)
      tx = std::thread{ func, i++ };

    ga_start = true;

    for (auto& tx : tArr)
      tx.join();
  }
*/

/*
              ---------------------------------------------
              | exception handling - threads relationship |
              ---------------------------------------------
*/

/*
  // when thread objects destructor is called,  
  // if that thread object is still joinable,
  // std::terminate() will be called.

  #include <thread>

  void foo(){
    std::cout << "foo called\n";
  }

  void func(){
    std::cout << "func called\n";
    throw std::runtime_error{ "runtime error exception from func()" };
  }

  int main(){
    std::thread t{ foo };
    func();

    // output ->
    //  func called
    //  terminate called after throwing 
    //  an instance of 'std::runtime_error'
    //  what():  runtime error exception from func()

    t.join(); // won't be exucuted
  }
*/

/*
  // what to do if there was not any JThread or a RAII wrapper class ?

  #include <thread>

  void foo(){
    std::cout << "foo called\n";
  }

  void func(){
    std::cout << "func called\n";
    throw std::runtime_error{ "runtime error exception from func()" };
  }

  int main(){
    std::thread t{ foo };

    try{
      func(); 
      t.join();
    }
    catch (const std::exception& ex){
      std::cout << "exeption caught : " << ex.what() << '\n';
      t.join();
    }

    // output ->
    //  func called
    //  exeption caught : runtime error exception from func()
    //  foo called -> t.join() is executed
  }
*/

/*
  // if thread object's workload(calleble) throws an exception

  #include <thread>
  #include "../nutility.h"

  void func(){
    std::cout << "func() called\n";

    if(1){
      throw std::runtime_error{ "error from func()" };
    }
  }

  int main(){

    std::set_terminate(my_terminate);

    try{
      std::thread tx{ func };
      tx.join();
      // exception can not be caught here
      // directly std::terminate() will be called

      // output ->
      //  func() called
      //  std::terminate cagrildi....
      //  myterminate cagrildi....
      //  std::abort() cagrildi
    }
    catch (const std::exception& ex){
      std::cout << "exception caught : " << ex.what() << '\n';
    }
  }
*/

/*
  // What to do if thread object's workload(calleble) throws an exception?

  // we can catch the exception and 
  // store that exception object in a variable
  // and using that variable we can rethrow that exception

  // std::exception_ptr & 
  // std::current_exception() & 
  // std::rethrow_exception()

  #include <thread>
  #include <stdexcept>

  std::exception_ptr exptr = nullptr;

  void func(int x){
    std::cout << "func(int x) called x = " << x << '\n';

    try{
      if (x % 2 == 0)
        throw std::invalid_argument{ "invalid argument --- func()" };
    }
    catch (...){
      exptr = std::current_exception();
    }

    std::cout << "func(int x) finished x = " << x << '\n';
  }

  int main(){
    std::thread tx { func, 10 };
    tx.join();

    try{
      if (exptr)
        std::rethrow_exception(exptr);
    }
    catch (const std::exception& ex){
      std::cout << "exception caught : " << ex.what() << '\n';
    }

    // output ->
    //  func(int x) called x = 10
    //  func(int x) finished x = 10
    //  exception caught : invalid argument --- func()
  }
*/

/*
  #include <thread>
  #include <stdexcept>
  #include "../nutility.h"

  std::exception_ptr exptr = nullptr;

  void func(){

    try{
      throw std::runtime_error{ "error from func()" };
    }
    catch (...){
      exptr = std::current_exception();
    }
  }

  int main(){
    std::thread tx { func };
    tx.join();

    std::set_terminate(my_terminate);

    if (exptr){
      std::cout << "exception has been caught in func()\n";

      // there is no necessity to rethrow the exception
      // but if an exception occured in func() function
      // that thread's is not successfully executed
      // and I could not do the work that I wanted to do
      // so I can rethrow the same exception
      std::rethrow_exception(exptr);

      // because of rethrow_exception() function is called
      // an exception will be thrown again
      // because of that exception is not caught in main()
      // std::terminate() will be called
    }
    else
      std::cout << "no exception has been caught in func()\n";

    // output ->
    //  exception has been caught in func()
    //  std::terminate cagrildi....
    //  myterminate cagrildi....
    //  std::abort() cagrildi
  }
*/

/*
  #include <vector>
  #include <stdexcept>  // std::runtime_error
  #include <mutex>
  #include <thread>

  std::vector<std::exception_ptr> g_ex_vec;
  std::mutex g_mutex;

  void f1(){
    throw std::runtime_error{ "exception from f1()" };
  }

  void f2(){
    throw std::runtime_error{ "exception from f2()" };
  }

  void thread_func1(){
    try{
      f1();
    }
    catch (...){
      std::lock_guard<std::mutex> guard{ g_mutex };
      g_ex_vec.push_back(std::current_exception());
    }
  }

  void thread_func2(){
    try{
      f2();
    }
    catch (...){
      std::lock_guard<std::mutex> guard{ g_mutex };
      g_ex_vec.push_back(std::current_exception());
    }
  }

  int main(){
    std::thread t1{ thread_func1 };
    std::thread t2{ thread_func2 };

    t1.join();
    t2.join();

    for (const auto& ex : g_ex_vec){
      try{
        if (ex != nullptr)
          std::rethrow_exception(ex);
      }
      catch (const std::exception& ex){
        std::cout << "exception caught : " << ex.what() << '\n';
      }
    }
    
    // output ->
    //  exception caught : exception from f1()
    //  exception caught : exception from f2()
  }
*/

/*
  // before C++20 ostream objects i.e std::cout is not synchronized

  #include <thread>

  void f1(){
    using namespace std::literals;
    std::this_thread::sleep_for(2000ms);

    for(int i = 0; i < 10000; ++i)
      std::cout << 13 << "hello" << 34.2341 << "world\n"; 
  }

  void f2(){
    using namespace std::literals;
    std::this_thread::sleep_for(2000ms);

    for (int i = 0; i < 10000; ++i)
      std::cout << 25 << "Izmir" << 72.2393 << "Ankara\n";
  }

  int main(){
    std::thread t1{ f1 };
    std::thread t2{ f2 };

    t1.join();
    t2.join();

    // output ->
    //  13hello72.2393Ankara
    //  25Izmir72.2393Ankara
    //  25Izmir72.2393Ankara
    //  34.2341world                  -> synchronization problem
    //  13hello25Izmir72.2393Ankara   -> synchronization problem
  }
*/

/*
  // after C++20 <syncstream> header file is added

  #include <syncstream>
  #include <thread>

  void f1(){
    using namespace std::literals;
    std::this_thread::sleep_for(2000ms);
    std::osyncstream os{ std::cout }

    for(int i = 0; i < 10000; ++i)
      os << 13 << "hello" << 34.2341 << "world\n"; 
  }

  void f2(){
    using namespace std::literals;
    std::this_thread::sleep_for(2000ms);
    std::osyncstream os{ std::cout }

    for (int i = 0; i < 10000; ++i)
      os << 25 << "Izmir" << 72.2393 << "Ankara\n";
  }

  int main(){
    std::thread t1{ f1 };
    std::thread t2{ f2 };

    t1.join();
    t2.join();

    // output ->
    //  25Izmir72.2393Ankara    
    //  25Izmir72.2393Ankara
    //  25Izmir72.2393Ankara
    //  25Izmir72.2393Ankara
    //  13hello34.2341world
    //  25Izmir72.2393Ankara
    //  13hello34.2341world
    //  25Izmir72.2393Ankara
    //  13hello34.2341world

    // no synchronization problem
  }
*/

/*
  #include <thread>
  #include <chrono>

  void cprint(char c){
    using namespace std::literals;
    // operator""ms is in chrono::literals
    // chrono::literals is an inline namespace
    // so it is visible in std::literal namespace

    for (int i = 0; i < 1000; ++i){
      std::cout << c;
      std::this_thread::sleep_for(50ms);
    }
  }

  int main()
  {
    std::thread tarr[26]; 
    // thread objects are default initialized
    // they are not joinable

    for (int i{}; auto& tx : tarr){
      tx = std::thread{ cprint, 'A' + i++ };
    }

    for (auto& tx : tarr){
      tx.join();
    }

    // output ->
    //  ABXDEFGHIJKMLNOPQRSTUVWCYZYCBXOFIJDAGLUEHQTRNSZVPKWMIRVK
    //  LCEGQAHXJYWBTDNFUOMZSPSQULMRYJZBWAFEKXOVDPTCGINHIABLRESQ
    //  GKYOHUZMFJTVDCXNWPRCYFHVANDKSUBPGJQLTXMOEIMNYBPRKWTZDIPX
    //  ...
  }
*/

/*
  #include <thread>
  #include <chrono>
  #include <vector>

  void cprint(char c){
    using namespace std::literals;

    for (int i = 0; i < 1000; ++i){
      std::cout << c;
      std::this_thread::sleep_for(50ms);
    }
  }

  int main()
  {
    std::vector<std::thread> tvec;

    for (int i = 0; i < 26; ++i){
      // tvec.push_back(std::thread{ cprint, 'A' + i });
      tvec.emplace_back(cprint, 'A' + i);
    }

    for (auto& tx : tvec){
      tx.join();
    }

    // output ->
    //  EDCBAGFHIJKLMNOPRQSTUVWXYZSGBPVZQTJYNCXWADEHROIFMLKU
    //  VHDEBKOTXIQYAPWGZUNFRJSCLMFMCHTLYUGWZRVOQDESKBAIPXNJ
    //  AKOZSNIUJPEDBTHCVGQXRWLYFMALSVQECHUIJOGXFMNYBPRKWTZD
    //  ...
  }
*/

/*
        --------------------------------------------------------
        | thread-local storage duration | thread_local keyword |
        --------------------------------------------------------
*/

/*
  - if we need a static variable for each thread
    but when that thread is finished, 
    that variable is not needed anymore
    we can use thread_local variables

  - every thread_local variable is unique for each thread
  - thread_local variable is like a static variable for each thread
*/

/*
  #include <syncstream>
  #include <string>
  #include <thread>

  thread_local int tl_ival { 0 };
  // every thread has its own copy of tl_ival

  void func(const std::string& thread_name){
    ++tl_ival;  // no synchronization problem

    std::osyncstream os{ std::cout };
    os  << "tl_ival in thread " 
        << thread_name << " is " << tl_ival << '\n';
  }

  int main(){
    std::thread t1{ func, "a" };
    std::thread t2{ func, "b" };

    {
      std::osyncstream os{ std::cout };
      os << "tl_ival in main thread is " << tl_ival << '\n';
    }

    t1.join();
    t2.join();

    // output ->
    //  tl_ival in thread b is 1
    //  tl_ival in main thread is 0
    //  tl_ival in thread a is 1
  }
*/

/*
  #include <thread>

  thread_local int tl_ival { 0 };

  void thread_func(int* p){
    *p = 42;
    std::cout << "tl_ival = " << tl_ival << '\n';   // (3)
  }

  int main(){
    std::cout << "tl_ival = " << tl_ival << '\n';   // (1)
    tl_ival = 9;
    std::cout << "tl_ival = " << tl_ival << '\n';   // (2)

    std::thread tx{ thread_func, &tl_ival };
    // main thread's tl_ival is sent to the thread_func
    tx.join();

    std::cout << "tl_ival = " << tl_ival << '\n';   // (4)  

    // output ->
    //  tl_ival = 0     // main thread's tl_ival  (1)
    //  tl_ival = 9     // main thread's tl_ival  (2)
    //  tl_ival = 0     // tx thread's tl_ival    (3)
    //  tl_ival = 42    // main thread's tl_ival  (4)
  }
*/

/*
  #include <mutex>
  #include <thread>

  std::mutex mtx;

  void func(int id)
  {
    int x = 0;                // thread's own stack memory
    static int y = 0;         // shared memory
    thread_local int z = 0;   // thread's own memory

    ++x;
    ++z;
    std::lock_guard guard(mtx);
    ++y;

    std::cout << "thread id : " << id 
              << " - x (automatic storage) = " << x << '\n';

    std::cout << "thread id : " << id 
              << " - y (static storage) = " << y << '\n';

    std::cout << "thread id : " << id
              << " - z (thread local storage) = " << z << "\n\n";
  }

  void foo(int id){
    func(id);
    func(id);
    func(id);
  }

  int main(){
    std::thread tx { foo, 0 };
    std::thread ty { foo, 1 };
    std::thread tz { foo, 2 };

    tx.join();
    ty.join();
    tz.join();

    // output ->
    //  thread id : 2 - x (automatic storage) = 1
    //  thread id : 2 - y (static storage) = 1
    //  thread id : 2 - z (thread local storage) = 1
    //  
    //  thread id : 2 - x (automatic storage) = 1
    //  thread id : 2 - y (static storage) = 2
    //  thread id : 2 - z (thread local storage) = 2
    //  
    //  thread id : 2 - x (automatic storage) = 1
    //  thread id : 2 - y (static storage) = 3
    //  thread id : 2 - z (thread local storage) = 3
    //  
    //  thread id : 1 - x (automatic storage) = 1
    //  thread id : 1 - y (static storage) = 4
    //  thread id : 1 - z (thread local storage) = 1
    //  
    //  thread id : 1 - x (automatic storage) = 1
    //  thread id : 1 - y (static storage) = 5
    //  thread id : 1 - z (thread local storage) = 2
    //  
    //  thread id : 1 - x (automatic storage) = 1
    //  thread id : 1 - y (static storage) = 6
    //  thread id : 1 - z (thread local storage) = 3
    //  
    //  thread id : 0 - x (automatic storage) = 1
    //  thread id : 0 - y (static storage) = 7
    //  thread id : 0 - z (thread local storage) = 1
    //  
    //  thread id : 0 - x (automatic storage) = 1
    //  thread id : 0 - y (static storage) = 8
    //  thread id : 0 - z (thread local storage) = 2
    //  
    //  thread id : 0 - x (automatic storage) = 1
    //  thread id : 0 - y (static storage) = 9
    //  thread id : 0 - z (thread local storage) = 3
  }
*/

/*
  #include <thread>
  #include <vector>
  #include <syncstream>
  #include <mutex>

  thread_local int g_tl_ival{};
  int g_ival{};

  std::mutex mtx;
  void func(char c)
  {
    ++g_tl_ival;
    std::lock_guard<std::mutex> myguard{ mtx };
    ++g_ival;
    std::osyncstream{ std::cout } << c  
                                  << " - g_tl_ival = " << g_tl_ival 
                                  << " - g_ival = " << g_ival << '\n';
  }

  int main(){
    using namespace std;

    vector<thread> tvec;

    for(char c = 'a'; c <= 'z'; ++c)
      tvec.emplace_back(func, c);

    for (auto& t : tvec)
      t.join();

    // output ->
    //  g - g_tl_ival = 1 - g_ival = 1
    //  a - g_tl_ival = 1 - g_ival = 2
    //  h - g_tl_ival = 1 - g_ival = 3
    //  f - g_tl_ival = 1 - g_ival = 4
    //  d - g_tl_ival = 1 - g_ival = 5
    //  b - g_tl_ival = 1 - g_ival = 6
    //  c - g_tl_ival = 1 - g_ival = 7
    //  i - g_tl_ival = 1 - g_ival = 8
    //  e - g_tl_ival = 1 - g_ival = 9
    //  j - g_tl_ival = 1 - g_ival = 10
    //  k - g_tl_ival = 1 - g_ival = 11
    //  l - g_tl_ival = 1 - g_ival = 12
    //  m - g_tl_ival = 1 - g_ival = 13
    //  n - g_tl_ival = 1 - g_ival = 14
    //  o - g_tl_ival = 1 - g_ival = 15
    //  q - g_tl_ival = 1 - g_ival = 16
    //  s - g_tl_ival = 1 - g_ival = 17
    //  t - g_tl_ival = 1 - g_ival = 18
    //  v - g_tl_ival = 1 - g_ival = 19
    //  w - g_tl_ival = 1 - g_ival = 20
    //  x - g_tl_ival = 1 - g_ival = 21
    //  y - g_tl_ival = 1 - g_ival = 22
    //  p - g_tl_ival = 1 - g_ival = 23
    //  r - g_tl_ival = 1 - g_ival = 24
    //  u - g_tl_ival = 1 - g_ival = 25
    //  z - g_tl_ival = 1 - g_ival = 26
  }
*/

/*
  #include <cstdint>
  #include <chrono>
  #include <thread>

  uint64_t sum_odd = 0ull;
  uint64_t sum_even = 0ull;

  constexpr uint64_t n = 1'000;

  void get_sum_odds(){
    using namespace std::literals;

    for (uint64_t i = 1; i <= n; i += 2){
      std::this_thread::sleep_for(4ms);
      sum_odd += i;
    }
  }

  void get_sum_evens(){
    using namespace std::literals;
    for (uint64_t i = 2; i <= n; i += 2){
      std::this_thread::sleep_for(4ms);
      sum_even += i;
    }
  }

  int main(){
    using namespace std;
    using namespace chrono;

    // ----------- PART 1 ------------
    auto start = steady_clock::now();
    get_sum_evens();
    get_sum_odds();
    auto end = steady_clock::now();

    std::cout << "calculations completed in " 
              << duration_cast<milliseconds>(end - start).count() 
              << " milliseconds\n";
    
    std::cout << "sum of odds   : " << sum_odd << '\n';
    std::cout << "sum of evens  : " << sum_even << '\n';

    // output ->
    //  calculations completed in 15790 milliseconds
    //  sum of odds   : 250000
    //  sum of evens  : 250500


    // ----------- PART 2 ------------
    std::thread tx{ get_sum_evens };
    std::thread ty{ get_sum_odds };

    sum_even = 0ull;
    sum_odd = 0ull;

    start = steady_clock::now();
    tx.join();
    ty.join();
    end = steady_clock::now();

    std::cout << "calculations completed in " 
              << duration_cast<milliseconds>(end - start).count() 
              << " milliseconds\n";

    std::cout << "sum of odds   : " << sum_odd << '\n';
    std::cout << "sum of evens  : " << sum_even << '\n';
    
    // output ->
    //  calculations completed in 7872 milliseconds
    //  sum of odds   : 250000
    //  sum of evens  : 250500
  }
*/

/*
  // https://en.cppreference.com/w/cpp/thread/thread/native_handle
  #include <thread>

  void foo(){}

  int main(){
    std::thread tx{ foo };

    std::cout << tx.native_handle() << '\n';    // output -> 2
    // returns a handle for OS specific API's 

    tx.join();
  }
*/

/*
  #include <thread>

  void foo(){};
  void bar(){};
  void baz(){};

  int main(){
    std::thread t1;
    std::thread t2;
    std::thread t3;

    std::cout << "t1 id : " << t1.get_id() << '\n';
    std::cout << "t2 id : " << t2.get_id() << '\n';
    std::cout << "t3 id : " << t3.get_id() << '\n';

    // output ->
    //  t1 id : thread::id of a non-executing thread
    //  t2 id : thread::id of a non-executing thread
    //  t3 id : thread::id of a non-executing thread

    t1 = std::thread{ foo }; 
    t2 = std::thread{ bar };
    t3 = std::thread{ baz };

    std::cout << "t1 id : " << t1.get_id() << '\n';
    std::cout << "t2 id : " << t2.get_id() << '\n';
    std::cout << "t3 id : " << t3.get_id() << '\n';

    // output ->
    //  t1 id : 2
    //  t2 id : 3
    //  t3 id : 4

    t1.join();
    t2.join();
    t3.join();
  }
*/

/*
                  --------------------------------
                  | std::async function template |
                  --------------------------------
*/

/*
  - to get the outcome from std::async's workload(callable)
    if function throws an exception, we can get that exception
    if not we can get the return value

  - thread's paralel execution in high level interface
*/

/*
  - for transfering the return value 
    from running thread to runner thread
    we need to have a shared state.
  - if we did not use std::async() function template
    we need to create that shared state manually
*/

/*
  // https://en.cppreference.com/w/cpp/thread/async

  - overload that does not have std::launch policy parameter
    will work as same as (std::launch::async | std::launch::deferred)
*/

/*
  #include <future>

  int foo(int x){
    std::cout << "foo called x = " << x << '\n';
    return x * x;
  }

  class Myclass{};

  Myclass bar();

  int main(){
    std::async(foo, 10);
    std::async(std::launch::async | std::launch::deferred, foo, 10);
    // Those 2 lines are equivalent

    // std::async(foo, 10) functions return value type is 
    // std::future<int> type 

    std::future<int> ft1 = std::async(foo, 10);
    auto ft2 = std::async(foo, 10);
    // Those 2 lines are equivalent

    std::future<Myclass> ft3 = std::async(bar);
    auto ft4 = std::async(bar);
    // Those 2 lines are equivalent
  }
*/

/*
  #include <future>

  int foo(int x){
    std::cout << "foo called x = " << x << '\n';
    return x * x;
  }

  int main(){
    auto ft = std::async(foo, 10);
    auto val = ft.get();

    std::cout << "val = " << val << '\n';

    // SCENARIO 1
    // std::async(foo, 10); function is called and executed.
    // we can get the return type directly

    // SCENARIO 2
    // std::async(std::launch::deferred, foo, 10);
    // when ft.get() is called, foo function will be called and executed

    // SCENARIO 3
    // when ft.get() is called, foo function will be called 
    // but its execution is not finished(still continuing)
    // ft.get() will block the caller thread 
    // until foo function's execution is finished
  }
*/

/*
  // when workload function has no return type 
  // and we did not hold return type 
  // of std::async() function in a variable
  // we can not call get() function of the std::async() function's 
  // return type (std::future<void>.get())
  // if async() function is called with std::launch::deferred policy
  // in this scenario that workload function will never be executed.
*/

/*
  #include <future>

  int f1(){
    return 1;
  }

  int f2(){
    return 2;
  }

  int f3(){
    return 3;
  }

  int main(){
    auto ft1 = std::async(std::launch::async, f1);
    auto ft2 = std::async(std::launch::async, f2);
    auto ft3 = std::async(std::launch::async, f3);

    std::cout << ft1.get() << '\n';   // output -> 1
    std::cout << ft2.get() << '\n';   // output -> 2
    std::cout << ft3.get() << '\n';   // output -> 3

    // SCENARIO 1 -> f1 function is called and executed
    // SCENARIO 2 -> f1 function is called but execution is not finished
    //  ft1.get() will be blocked

    // we need to call get() function 1 time
    std::cout << ft1.get() << '\n';   

    // output -> 
    //  terminate called after 
    //  throwing an instance of 'std::future_error'
    //  what():  std::future_error: No associated state
  }
*/

/*
  #include <future>
  #include <stdexcept>

  // <------ SCENARIO 1 ------>
  int foo(){
    return 11;
  }
  // output -> return value is: 11

  // <------ SCENARIO 2 ------>
  int foo(){
    throw std::runtime_error{ "exception from foo()" };
  }
  // output -> exception caught: exception from foo()


  int main(){
    try{
      auto ft1 = std::async(std::launch::async, foo);
      auto val = ft1.get();

      std::cout << "return value is: " << val << '\n';
    }
    catch(const std::exception& ex){
      std::cout << "exception caught: " << ex.what() << '\n';
    }
  }
*/

/*
  int func();
  int foo();
  // func and foo functions are taking long time to execute
  // but we need the sum of their return values

  int main(){

    auto x = func() + foo();  
    // we run func and foo functions sequentially
    // which function will be called is unspecified behaviour


    auto ft1 = async(std::launch::async, foo);
    auto func_val = func();
    auto y = func_val + ft1.get();
    // we run func and foo functions parallel(simultaneously)
  }
*/

/*
  #include <string>
  #include <cstdlib>      // std::rand 
  #include <algorithm>    // std::generate_n
  #include <thread>
  #include <future>

  std::string get_str_letters(int n){
    using namespace std::literals;

    std::string str(n ,'\0'); // fill constructor

    std::generate_n(str.begin(), n, []{return rand() % 26 + 'A';});
    std::this_thread::sleep_for(3s);

    return str;
  }

  std::string get_str_digits(int n){
    using namespace std::literals;

    std::string str(n, '\0'); // fill constructor

    std::generate_n(str.begin(), n, []{return rand() % 10 + '0';});
    std::this_thread::sleep_for(3s);

    return str;
  }

  int main(){
    auto start = std::chrono::steady_clock::now();

    // auto ft1 = std::async(std::launch::deferred, get_str_letters, 20);
    // auto ft2 = std::async(std::launch::deferred, get_str_digits, 20);

    auto ft1 = std::async(std::launch::async, get_str_letters, 20);
    auto ft2 = std::async(std::launch::async, get_str_digits, 20);

    auto s1 = ft1.get();
    auto s2 = ft2.get();
    auto end = std::chrono::steady_clock::now();

    std::cout << std::chrono::duration<double>{end - start}.count() 
              << " seconds\n";

    std::cout << "s1 + s2 = " << s1 + s2 << '\n';

    // output -> (std::launch::deferred)
    //  6.02061 seconds
    //  s1 + s2 = PHQGHUMEAYLNLFDXFIRC14232216857618927954

    // with std::launch::deferred policy
    // ft1.get() will block the caller thread
    // until its workload function is finished executing
    // then ft2.get() will be called

    // output -> (std::launch::async)
    //  3.01504 seconds
    //  s1 + s2 = PHQGHUMEAYLNLFDXFIRC17409488245517115276

    // with std::launch::async policy
    // ft1.get() and ft2.get() will be called simultaneously
    // and they will be executed in parallel
  }
*/

/*
  #include <future>
  #include <thread>

  void foo(){
    using namespace std::literals;
    std::cout << "foo called\n";
    std::this_thread::sleep_for(3s);
  }

  void bar(){
    using namespace std::literals;
    std::cout << "bar called\n";
    std::this_thread::sleep_for(3s);
  }

  int main(){

    auto start = std::chrono::steady_clock::now();
    async(std::launch::async, foo);
    auto end = std::chrono::steady_clock::now();
    std::cout << std::chrono::duration<double>{end - start}.count() 
              << " seconds\n";

    start = end;
    async(std::launch::async, bar);
    end = std::chrono::steady_clock::now();
    std::cout << std::chrono::duration<double>{end - start}.count() 
              << " seconds\n";

    // output -> 
    //  foo called
    //  3.01237 seconds
    //  bar called
    //  3.01364 seconds

    // when `async(std::launch::async, foo);` this line has been executed
    // temporary std::future<void> object is created
    // and after line's execution 
    // temporary object's destructor will be called
    // and its destructor will call temporary objects get() function
    // and that get() function will block the caller thread
  }
*/

/*
  #include <chrono>
  #include <future>

  int main(){
    using namespace std;
    using namespace std::chrono;

    auto tp_start = system_clock::now();

    auto lazy_async = std::async(std::launch::deferred, []{
      return system_clock::now();
    });
    // std::async(std::launch::deferred, ) will wait 
    // till its get() member function is called

    auto eager_async = std::async(std::launch::async, []{
      return system_clock::now();
    });
    // std::async(std::launch::async, ) will be executed immediately

    std::this_thread::sleep_for(std::chrono::seconds(1));

    using dsec = duration<double>;

    auto deferred_sec = 
              static_cast<dsec>(lazy_async.get() - tp_start).count();

    auto eager_sec = 
              static_cast<dsec>(eager_async.get() - tp_start).count();

    std::cout << "duration for deferred : " 
              << deferred_sec << " seconds\n";

    std::cout << "duration for eager    : " 
              << eager_sec << " seconds\n";

    // output ->
    //  duration for deferred : 1.00044 seconds
    //  duration for eager    : 0.0005003 seconds
  }
*/

/*
  #include <chrono>
  #include <future>

  int main(){
    using namespace std;
    using namespace std::chrono;

    auto tp_start = system_clock::now();

    auto lazy_async = std::async(std::launch::deferred, []{
      return system_clock::now();
    });

    auto no_policy_async = std::async([]{return system_clock::now();});
    // when first parameter is not given
    // one of std::launch::deferred or std::launch::async 
    // will be choosen in run-time

    std::this_thread::sleep_for(std::chrono::seconds(1));

    using dsec = duration<double>;

    auto deferred_sec = 
          static_cast<dsec>(lazy_async.get() - tp_start).count();

    auto no_policy_sec = 
          static_cast<dsec>(no_policy_async.get() - tp_start).count();

    std::cout << "duration for deferred  : " 
              << deferred_sec << " seconds\n";

    std::cout << "duration for no policy : " 
              << no_policy_sec << " seconds\n";

    // output ->
    //  duration for deferred  : 1.00623 seconds
    //  duration for no policy : 0.0005693 seconds

    // in run-time std::launch::async policy is choosen
  }
*/

/*
  #include <chrono>
  #include <future>

  int main(){
    using namespace std;
    using namespace std::chrono;

    auto tp_start = system_clock::now();

    auto no_policy_async = std::async(
              []{ return system_clock::now();});

    auto both_policy_async = std::async(
              std::launch::async | std::launch::deferred,
              []{ return system_clock::now(); });

    std::this_thread::sleep_for(std::chrono::seconds(1));

    using dsec = duration<double>;

    auto no_policy_sec = 
        static_cast<dsec>(no_policy_async.get() - tp_start).count();

    auto both_policy_sec = 
        static_cast<dsec>(both_policy_async.get() - tp_start).count();

    std::cout << "duration for no policy   : " 
              << no_policy_sec << " seconds\n";

    std::cout << "duration for both policy : " 
              << both_policy_sec << " seconds\n";

    // output ->
    //  duration for no policy   : 0.000593 seconds
    //  duration for both policy : 0.0006259 seconds

    // for no policy(means std::launch::async | std::launch::deferred)
    // std::launch::async policy is choosen

    // for both policy(std::launch::async | std::launch::deferred)
    // std::launch::async policy is choosen

    // when get() functions are called both of them will 
    // already been executed without waiting main threads 1 second
}
*/

/*
  #include <map>
  #include <string>
  #include <future>
  #include <algorithm>
  #include <iomanip>

  std::map<char, size_t> histogram(const std::string& str)
  {
    std::map<char, size_t> cmap;

    for (char c : str)
      ++cmap[c];
    // when a char not exists in the map
    // ++ operator will create that char in the map
    // and value initialize .second (int -> 0)

    return cmap;
  }

  std::string get_sorted(std::string str)
  {
    std::sort(begin(str), end(str));
    std::erase_if(str, [](char c){ return isspace(c); });   // C++20
    return str;
  }

  bool is_vowel(char c)
  {
    static const char vowels[] = { "AEIOUaeiou" };
    return std::find(std::begin(vowels), std::end(vowels), c) 
                                                != std::end(vowels);
  }

  size_t count_vowels(const std::string& str)
  {
    return std::count_if(std::begin(str), std::end(str), is_vowel);
  }

  int main(){
    std::string sline = "Hello_world_we_are_live_from_Istanbul";

    auto hist = std::async( std::launch::async, 
                            histogram, 
                            sline);

    auto sorted_str = std::async( std::launch::async, 
                                  get_sorted, 
                                  sline);

    auto vowel_count = std::async(std::launch::async, 
                                  count_vowels, 
                                  sline);

    for (const auto& [c, count] : hist.get())
      std::cout << c << " : " << count << '\n';

    std::cout << "sorted string : " 
              << std::quoted(sorted_str.get()) << '\n'
              << "total_vowels : "
              << vowel_count.get() << '\n';

    // output -> 
    //  H : 1
    //  I : 1
    //  _ : 6
    //  a : 2
    //  b : 1
    //  d : 1
    //  e : 4
    //  f : 1
    //  i : 1
    //  l : 5
    //  m : 1
    //  n : 1
    //  o : 3
    //  r : 3
    //  s : 1
    //  t : 1
    //  u : 1
    //  v : 1
    //  w : 2
    //  sorted string : "HI______aabdeeeefilllllmnooorrrstuvww"
    //  total_vowels : 12
  }
*/

/*
                  --------------------------------
                  | `std::future` class template |
                  --------------------------------
*/

/*
  - std::promise objects get_future() member function
    will return us a std::future object that will shared state
  
  - std::async function will return us a std::future object

  - std::packaged_task get_future() member function
    will return us a std::future object
*/

/*
                <--- check promise_future.png --->

  Biz bir `std::promise` oluşturduğumuzda, bu std::promise 
  sınıf nesnesi vasıtasıyla shared state'i set ediyoruz, böylece
  bir result oluşturuyoruz.

    - shared state'i bir value ile set etmek.
    - shared state'i bir exception ile set etmek.
  
  `std::promise` sınıfının `set_value()` fonksiyonu ile shared 
  state SET edilir ise, `std::future` sınıfı get() üye fonksiyonu ile
  bu value GET edilir, alınır.

  `std::promise` sınıfının `set_exception()` fonksiyonu ile shared
  state SET edilir ise, `std::future` sınıfı get() üye fonksiyonu ile
  bu exception GET edilir, yakalanır.

  `std::promise` ve `std::future` sınıfları 
  ayrı threadler tarafından kullanılabilirler.

  `std::promise` ile `std::future` arasında kurulan iletişim kanalı
  (channel) bir defa kullanıldıktan sonra tekrar kullanılamaz.
    `std::promise` shared state'i bir kere set edebilir.
    `std::future` shared state'i bir kere get edebilir.

  `std::shared_future` sınıfı kullanılarak shared state 
  birden fazla kere get edilebilir.
*/

/*
  #include <future>  // std::promise, std::future, std::async

  int main()
  {
    std::promise<int> prom;
    // std::promise class is non copyable but movable

    std::future<int> ftr = prom.get_future();

    prom.set_value(999);

    // std::future objects get() function has not been called
    if (ftr.valid())  
      std::cout << "future object is in valid state\n";
    else
      std::cout << "future is not a valid state\n";

    // output -> future object is in valid state

    auto val = ftr.get();
    std::cout << "val = " << val << '\n';
    // output -> val = 999

    // std::future objects get() function has been called
    if (ftr.valid())
      std::cout << "future object is in valid state\n";
    else
      std::cout << "future is not a valid state\n";

    // output -> future is not a valid state


    // if get() function called for the second time
    try{
      val = ftr.get();
    }
    // catch(const std::exception& ex){
    catch(const std::future_error& ex){
      std::cout << "exception caught : " << ex.what() << '\n';
    }
    // output ->
    // exception caught : std::future_error: No associated state
  }
*/

/*
  // what happens we call std::future's get() function 
  // when std::promise did not set the shared state yet

  #include <future>  // std::promise, std::future

  int main(){
    std::promise<int> prom;
    auto ftr = prom.get_future();

    auto val = ftr.get();   
    // program will be blocked here and wait for 
    // shared state to be set by std::promise
  }
*/

/*
  // !!!!! If async will solve your problem, use async !!!!!

  #include <future>   // std::promise, std::future
  #include <thread>   // std::thread
  #include <utility>  // std::move

  void sum_square(std::promise<int>&& prom, int a, int b)
  {
    prom.set_value(a * a + b * b);
  }

  struct Div{
    void operator()(std::promise<int>&& prom, int a, int b) const 
    {
      prom.set_value(a / b);
    }
  };

  int main(){
    int x{ 90 }, y{ 15 };

    std::promise<int> sum_square_prom;
    std::promise<int> div_prom;
    std::future<int> fp_sum_square = sum_square_prom.get_future();
    std::future<int> fp_div = div_prom.get_future();

    std::thread tx{ sum_square, std::move(sum_square_prom), x, y };
    std::thread ty{ Div{}, std::move(div_prom), x, y };

    std::cout << x << " * " << x << " + " 
              << y << " * " << y << " = "
              << fp_sum_square.get() << '\n';

    std::cout << x << " / " << y << " = " 
              << fp_div.get() << '\n';
    
    tx.join();
    ty.join();

    // tx, ty and main thread are running asynchronously

    // output -> 
    //  90 * 90 + 15 * 15 = 8325
    //  90 / 15 = 6
  }
*/

/*
  #include <future>

  // a function can also return `std::promise` object
  std::promise<int> foo(int x, int y)
  {
    std::promise<int> prom;
    prom.set_value(x * y);

    return prom;
  }
*/

/*
  #include <exception>  // std::current_exception
  #include <future>     // std::promise, std::future
  #include <thread>     // std::thread
  #include <utility>    // std::move
  #include <string>     // std::to_string

  struct Div{
    void operator()(std::promise<int>&& prom, int a, int b) const
    {
      try{
        if (b == 0){
          auto err_str = "division by zero error : "
                          + std::to_string(a) + " / " 
                          + std::to_string(b);  
          // const char* + std::string -> std::string   
          // std::string + const char* -> std::string

          throw std::runtime_error(err_str);              
        }
        prom.set_value(a / b);
      }
      catch(...){
        prom.set_exception(std::current_exception());
      }
    }
  };

  void func(int x, int y)
  {
    std::promise<int> prom;
    std::future<int> ftr = prom.get_future();
    std::thread tx{ Div{}, std::move(prom), x, y };

    try{
      std::cout << x << " / " << y << " = " << ftr.get() << '\n';
    }
    catch(const std::exception& ex){
      std::cout << "exception caught : " << ex.what() << '\n';
    }

    tx.join();
  }

  int main()
  {
    func(12, 7);
    // output -> 12 / 7 = 1

    func(12, 0);
    // output -> 
    //  12 / 0 = exception caught : division by zero error : 12 / 0
  }
*/

/*
  #include <future>  // std::promise, std::future_error

  int main()
  {
    std::promise<int> prom;
    prom.set_value(10);     // -------> (1)

    try{
      prom.set_value(20);   // -------> (2)
      // trying to set shared state for the second time
    }
    // catch(const std::exception& ex){
    catch(const std::future_error& ex){
      std::cout << "exception caught : " << ex.what() << '\n';
    }
  }

  // output ->
  // exception caught : std::future_error: Promise already satisfied
*/

/*
  #include <future> // std::promise, std::future, std::future_error

  int main()
  {
    std::promise<double> dprom;
    auto ftr = dprom.get_future();

    dprom.set_value(3.14);

    auto val = ftr.get();   // -------> (1)
    std::cout << "val = " << val << '\n';
    // output -> val = 3.14

    try{
      auto x = ftr.get();   // -------> (2)
      // trying to get shared state for the second time
    }
    catch(const std::future_error& ex){
      std::cout << "exception caught : " << ex.what() << '\n';
    }

    // output ->
    // exception caught : std::future_error: No associated state
  }
*/

/*
  #include <future> // std::async, std::future_error, std::future

  int foo(){
    return 1;
  }

  int main()
  {
    auto ftr = std::async(foo);

    if (ftr.valid())
      std::cout << "future is valid, get() can be called!\n";
    else
      std::cout << "future is invalid, get() cannot be called!\n";
    // output -> future is valid, get() can be called!

    auto ival = ftr.get();
    std::cout << "ival = " << ival << '\n';
    // output -> ival = 1

    if (ftr.valid())
      std::cout << "future is valid, get() can be called!\n";
    else
      std::cout << "future is invalid, get() cannot be called!\n";
    // output -> future is invalid, get() cannot be called!

    try{
      auto ival2 = ftr.get();
    }
    catch(const std::future_error& ex){
      std::cout << "exception caught : " << ex.what() << '\n';
    }
    // output -> 
    //  exception caught : std::future_error: No associated state
  }
*/

/*
            ---------------------------------------
            | `std::shared_future` class template |
            ---------------------------------------
*/

/*
  #include <future>     // std::promise, std::shared_future
  #include <thread>     // std::thread
  #include <syncstream> // std::osyncstream

  struct SumSquare{
    void operator()(std::promise<int>&& prom, int a, int b) const
    {
      prom.set_value(a * a + b * b);
    }
  };

  // copy semantics  -> std::shared_future object is copyable
  void func(std::shared_future<int> sftr)
  {
    std::osyncstream os{ std::cout };
    os << "threadId(" << std::this_thread::get_id() << ") : ";
    os << "result = " << sftr.get() << "\n" << std::flush;
    // os << "result = " << sftr.get() << std::endl;
  }

  int main()
  {
    std::promise<int> prom;
    std::shared_future<int> sftr = prom.get_future();

    std::thread tx(SumSquare{}, std::move(prom), 10, 20);

    std::thread t1(func, sftr);
    std::thread t2(func, sftr);
    std::thread t3(func, sftr);
    std::thread t4(func, sftr);
    std::thread t5(func, sftr);

    tx.join();

    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();

    // output ->
    //  threadId(3) : result = 500
    //  threadId(5) : result = 500
    //  threadId(6) : result = 500
    //  threadId(7) : result = 500
    //  threadId(4) : result = 500
  }
*/

/*
  #include <future>     // std::promise, std::future, std::shared_future
  #include <thread>     // std::thread
  #include <syncstream> // std::osyncstream

  struct SumSquare{
    void operator()(std::promise<int>&& prom, int a, int b) const
    {
      prom.set_value(a * a + b * b);
    }
  };

  void func(std::shared_future<int> sftr)
  {
    std::osyncstream os{ std::cout };
    os << "threadId(" << std::this_thread::get_id() << ") : ";
    os << "result = " << sftr.get() << std::endl;
  }

  int main()
  {
    std::promise<int> prom;
    std::future<int> ftr = prom.get_future();

    std::cout << "ftr is " 
              << (ftr.valid() ? "valid" : "invalid") << '\n';
    // output -> ftr is valid

    std::thread tx(SumSquare{}, std::move(prom), 11, 22);
    std::cout << "ftr is " 
              << (ftr.valid() ? "valid" : "invalid") << '\n';
    // output -> ftr is valid

    std::shared_future<int> sftr = ftr.share();
    
    std::cout << "ftr is " 
              << (ftr.valid() ? "valid" : "invalid") << '\n';
    // output -> ftr is invalid

    std::thread t1(func, sftr);
    std::thread t2(func, sftr);
    std::thread t3(func, sftr);
    std::thread t4(func, sftr);
    std::thread t5(func, sftr);

    tx.join();

    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();

    // output ->
    //  threadId(3) : result = 605
    //  threadId(4) : result = 605
    //  threadId(6) : result = 605
    //  threadId(5) : result = 605
    //  threadId(7) : result = 605
  }
*/

/*
  std::future<T>::wait_for
  https://en.cppreference.com/w/cpp/thread/future/wait_for

  template< class Rep, class Period >
  std::future_status wait_for( 
      const std::chrono::duration<Rep,Period>& timeout_duration) const;

  std::future_status is an enum class type
    - future_status::deferred
      -> lazy evaluation has already been done, so until get() 
        function is called workload will be executed
    - future_status::ready
      -> result is ready, promise has been set
    - future_status::timeout
      -> result is not ready yet, promise has not been set

*/

/*
  #include <future>   // std::promise
  #include <thread>   // std::thread
  #include <chrono>   

  using namespace std::literals;

  // std::promise object is non copyable but movable
  void func(std::promise<int> iprom)
  {
    std::this_thread::sleep_for(5s);
    // pseudo function execution for 5 seconds 
    iprom.set_value(999);
    // shared state is set
  }

  int main()
  {
    std::promise<int> prom;
    auto ftr = prom.get_future();
    std::thread tx{ func, std::move(prom) };

    std::future_status status{};
    do{
      status = ftr.wait_for(1s);
      std::cout << "... doing some work here\n" << std::flush;
    } while (status != std::future_status::ready);

    std::cout << "the return value is " << ftr.get() << '\n';

    tx.join();   

    // output ->
    //  ... doing some work here    -> status = timeout
    //  ... doing some work here    -> status = timeout
    //  ... doing some work here    -> status = timeout
    //  ... doing some work here    -> status = timeout  
    //  ... doing some work here    -> status = timeout
    //  the return value is 999     -> status = ready
  }
*/

/*
  #include <chrono>
  #include <future>   // std::async, std::future

  constexpr int x = 41;

  // do not write recursive fibonnaci function
  // use lookup table instead
  long long fib(int n)
  {
    return n < 3 ? 1 : fib(n - 1) + fib(n - 2);
  }

  int main()
  {
    using namespace std::literals;

    auto ftr = std::async(fib, x);

    std::cout << "wait result will come\n";
    while (ftr.wait_for(10ms) == std::future_status::timeout)
      std::cout << "." << std::flush;

    auto result = ftr.get();

    std::cout << "\nfib(" << x << ") = " << result << '\n';

    // output ->
    //  wait result will come
    //  .................................
    //  fib(41) = 165580141
  }
*/

/*
            -------------------------------------
            | std::packaged_task class template |
            -------------------------------------
*/

/*
  - wrapping a callable for calling it asynchronously

  - like std::promise, std::packaged_task is also have 
    get_future() member function that returns a std::future object

  - unlike std::promise where task is acting like std::launch::async,
    task is acting like std::launch::deferred(will wait) until 
    std::packaged_task classes operator() call function is called

  - std::packaged_task is non copyable but movable class
*/

/*
  #include <future>  // std::packaged_task, std::future

  int foo(int x, int y){
    return x * y + 5;
  }

  using ftype = int(int, int);

  int main()
  {
    std::packaged_task<int(int, int)> ptask{ foo };
    // std::packaged_task p_task{ foo };  -> C++17 - CTAD
    // std::packaged_task<ftype>; can be choose for default ctor   

    std::future<int> ftr = ptask.get_future();
    ptask(10, 20);
  }
*/

/*
  #include <cmath>    // std::pow
  #include <future>   // std::packaged_task, std::future

  int main()
  {
    std::packaged_task<double(double, double)> ptask{ 
      [](double a, double b){
        return std::pow(a, b) + std::pow(b, a);
      }};

    std::future<double> ftr_result = ptask.get_future();
    // auto ftr_result = ptask.get_future();

    ptask(1.2, 3.4);

    std::cout << "result = " << ftr_result.get() << '\n';
    // output -> result = 6.20158
  }
*/

/*
  #include <utility>  // std::move
  #include <future>   // std::packaged_task, std::future
  #include <thread>   // std::thread

  int main()
  {
    using ftype = int(int, int);

    std::packaged_task<ftype> pt_x; // default initialized
    std::packaged_task<ftype> pt_y([](int x, int y){ 
      return x * x + y * y; });

    pt_x = std::move(pt_y);   // move assignment

    std::future<int> ftr_return = pt_x.get_future();
    std::thread(std::move(pt_x), 10, 20).detach();
    // giving packaged_task to a thread as a workload 

    auto result = ftr_return.get();

    std::cout << "result = " << result << '\n';
    // output -> result = 500
  }
*/

/*
                -------------------------------
                | shared resources in threads |
                -------------------------------
*/

/*
  // Unsyncronized data access

  int x;
  void foo(int);

  void func()
  {
    if (x >= 0)
      foo(x);
    else
      foo(-x);
  }

  // first thread will call func() when "x" is 10
  // foo() will be called with 10 and in the middle of the execution
  // second thread will change the value of "x" to negative
*/

/*
  Unsychronized data access
  - When two threads running in parallel read and write the same data,
    it is open which statement comes first.

  Half-written data: 
  - When one thread reads data, which another thread modifies, 
  the reading thread might even read the data in the middle of the write
  of the other thread, thus reading neither the old nor the new value.

  Reordered statements:
  - Statements and operations might be reordered so that the behaviour
  of each single thread is correct, but in combination of all threads,
  expected behaviour is broken.
*/

/*
  - Birden fazla thread eğer aynı değişkeni kullanıyorsa, hangi 
  threading o değişkene erişeceği konusunda bunu garantiye alacak 
  bir mekanizma yok ise, paralel olarak çalışan threadlerden 
  hangisinin daha önce o değişkeni kullanacağı konusunda 
  bir garanti yoktur.

  race condition: farklı threadlerin daha önce paylaşılan değişkene
  erişmesine bağlı olarak oluşan farklı sonuçlar.
    - race condition bir hata oluşturmayabilir.
      farklı sonuçlar oluşabilir ama programın genel yapısı üzerinde
      bir problem oluşturmayabilir. (benign : iyi huylu)
    - race condition hata oluşturabilir (malign : kötü huylu)

  data race : malign race condition (undefined behaviour)
    -> if all threads are read only, no problem will occur.
    -> if even one of the threads is writing, risk for data race.
*/

/*
  - inside threads workloads(callables), automatic storage duration
    variables are not shared between threads.
  - every thread have their own stack memory.
  - static storage duration variables are shared between threads.
    global variables and static local variables
  - variable that will sent to the function with reference semantics
*/

/*
  #include <vector>

  std::vector<double> dvec;

  void func()
  {
    if (!dvec.empty())
      std::cout << dvec.back() << '\n';
  }

  // first thread will call func() when dvec is not empty
  // but in if statements execution, second thread will clear dvec
  // undefined behaviour(ub)
*/

/*
  #include <cstdint>  // std::int64_t

  std::int64_t g_x{};

  void foo()
  {
    g_x = -1;
  }

  void bar()
  {
    std::cout << g_x << '\n';
  }

  // std::int64_t does not have an atomic guarantee 
  // first thread will call foo() and between the assignment to g_x
  // second thread will call bar() and read the value of g_x
  // because of it was not atomic, it is undefined behaviour(ub)
  // can be torn read

  // atomic: guarantee that g_x's value will be 0 or -1 
  // it can not be between 
  // the code that assignment operation is executing
*/

/*
  #include <cstdint> // std::int64_t

  std::int64_t g_x{};
  bool ready_flag = false;

  void foo(std::int64_t x)
  {
    g_x = x;
    ready_flag = true;
  }

  void bar()
  {
    while(!ready_flag)
      ;

    foo(g_x);
  }

  // first thread will call foo() 
  // compiler can execute "ready_flag = true;" statement 
  // before "g_x = x;" statement
  // when second thread will call bar() function
  // foo(g_x) will be called with the value of g_x = 0
*/

/*
                  ----------------------------
                  | mutex (mutual exclusion) |
                  ----------------------------
*/

/*
  - when one of the thread locks(acquire) the mutex, other threads 
    must wait(blocked) until the mutex is unlocked(released).
    when mutex has been released, another thread can acquire it.
*/

/*
  #include <mutex>
  #include <shared_mutex>

  // -------------------------------------------------------------

  // use it minimal, which one is necessary. Cost will increase
  // all of them have lock() and unlock() member functions

  std::mutex m1;
  std::timed_mutex m2;
  std::recursive_mutex m3;
  std::recursive_timed_mutex m4;
  std::shared_mutex m5;

  // -------------------------------------------------------------

  // mutex wrapper RAII class templates used 
  //  - forget to unlock() the mutex
  //  - exception thrown in the critical section before unlock()

  std::lock_guard<std::mutex> lg1{ m1 };   
  std::unique_lock<std::mutex> ul1{ m1 };  
  std::scoped_lock<std::mutex> sl1{ m1 };  // (C++17)
  std::shared_lock<std::shared_mutex> sl2{ m5 }; 

  // -------------------------------------------------------------

  std::lock()  // global function
*/

/*
  std::mutex :
    - lock() and unlock() member functions
    - try_lock() member function

    - time based lock operations can not be done with std::mutex
    - when a std::mutex is locked it can not be locked again
    it will be undefined behaviour(ub)

  std::timed_mutex :
    - time based lock operations can be done with std::timed_mutex

  std::recursive_mutex :
    - can be locked more than once.
*/

/*
  #include <mutex>    // std::mutex

  std::mutex m1;

  int main()
  {
    // -------------------------------------------------------------

    m1.lock();  // will acquire the mutex or get blocked 

    // if this mutex is locked(acquired) by the first thread
    // second thread will be blocked until the first thread 
    // unlocked(released) the mutex.

    // -------------------------------------------------------------

    m1.try_lock();  // will try to acquire the mutex

    // if this mutex is locked(acquired) by the first thread
    // second thread will NOT be blocked, it will return false
    // else it will acquire the mutex and return true

    while(!m1.try_lock())
    {
      // do other stuff until the mutex is acquired
    }

    // -------------------------------------------------------------

    m1.unlock();  // will release the mutex
  }
*/

/*
  #include <mutex>  // std::timed_mutex
  #include <chrono> // std::chrono::steady_clock

  std::timed_mutex tm1;

  int main()
  {
    // -------------------------------------------------------------
    
    tm1.lock();       // same as std::mutex::lock()
    tm1.try_lock();   // same as std::mutex::try_lock()
    tm1.unlock();     // same as std::mutex::unlock()

    // -------------------------------------------------------------

    using namespace std::literals;

    tm1.try_lock_for(1000ms);   
    // will try to acquire the mutex 
    // for "a std::chrono::duration" time

    // will return true if the mutex is acquired
    // will return false if the mutex is not acquired

    // -------------------------------------------------------------

    auto tp = std::chrono::steady_clock::now() + 2s;

    tm1.try_lock_until(tp);  
    // will try to acquire the mutex
    // until "a std::chrono::time_point" time
    
    // will return true if the mutex is acquired
    // will return false if the mutex is not acquired

    // -------------------------------------------------------------
  }
*/

/*
  #include <mutex>  // std::mutex
  #include <thread> // std::thread

  unsigned long long counter = 0;
  std::mutex mtx;

  void func()
  {
    // ------------------ critical region ------------------
    for(unsigned long long i = 0; i < 1'000'000ull; ++i)
      ++counter;
    // ------------------ critical region ------------------
  }

  void foo()
  {
    mtx.lock();
    // ------------------ critical region ------------------
    for(unsigned long long i = 0; i < 1'000'000ull; ++i)
      ++counter;
    // ------------------ critical region ------------------
    mtx.unlock();
  }

  int main()
  {
    // std::thread t1{ func };
    // std::thread t2{ func };
    // std::thread t3{ func };
    // std::thread t4{ func };

    std::thread t1{ foo };
    std::thread t2{ foo };
    std::thread t3{ foo };
    std::thread t4{ foo };

    t1.join();
    t2.join();
    t3.join();
    t4.join();

    // std::cout << "counter = " << counter << '\n';
    // output -> counter = 1'182'405  -> func
    // output -> counter = 4'000'000  -> foo
  }
*/

/*
  #include <mutex>  // std::mutex
  #include <thread> // std::thread

  unsigned long long counter = 0;
  std::mutex mtx;

  void foo()
  {
    mtx.lock();
    // ------------------ critical region ------------------
    for(unsigned long long i = 0; i < 1'000'000ull; ++i)
      ++counter;
    // ------------------ critical region ------------------

    // mtx.unlock(); is forgotten -> dead lock
    // other threads will be blocked
  }

  int main()
  {
    std::thread t1{ foo };
    std::thread t2{ foo };
    std::thread t3{ foo };
    std::thread t4{ foo };

    t1.join();
    t2.join();
    t3.join();
    t4.join();
  }
*/

/*
  #include <mutex>  // std::mutex, std::lock_guard
  #include <thread> // std::thread

  unsigned long long counter = 0;
  std::mutex mtx;

  void foo()
  {
    std::lock_guard<std::mutex> guard{ mtx };

    // ------------------ critical region ------------------
    for(unsigned long long i = 0; i < 1'000'000ull; ++i)
      ++counter;
    // ------------------ critical region ------------------
  }

  int main()
  {
    std::thread t1{ foo };
    std::thread t2{ foo };
    std::thread t3{ foo };
    std::thread t4{ foo };

    t1.join();
    t2.join();
    t3.join();
    t4.join();

    std::cout << "counter = " << counter << '\n';
    // output -> counter = 4'000'000
  }
*/

/*
  #include <mutex>  // std::mutex, std::lock_guard
  #include <thread> // std::thread

  unsigned long long counter = 0;
  std::mutex mtx;

  void foo()
  {
    mtx.lock(); 
    // we already acquired or wait for acquiring the mutex

    std::lock_guard<std::mutex> guard(mtx, std::adopt_lock);
    // we already acquired the mutex, so we can adopt it
    // and RAII wrapper lock_guard will unlock() the mutex
    // at the end of its scope

    // ------------------ critical region ------------------
    for(unsigned long long i = 0; i < 1'000'000ull; ++i)
      ++counter;
    // ------------------ critical region ------------------
  }

  int main()
  {
    std::thread t1{ foo };
    std::thread t2{ foo };

    t1.join();
    t2.join();

    std::cout << "counter = " << counter << '\n';
    // output -> counter = 2'000'000
  }
*/

/*
  - unique_lock can wrap, an already acquired mutex. (adopting)
  - unique_lock can wrap a mutex for acquiring(locking) it later
  - unique_lock can wrap a mutex for 
    attemting to acquire it in a future time point 
*/

/*
  #include <mutex>  // std::mutex, std::lock_guard
  #include <thread> // std::thread, std::this_thread::sleep_for
  #include <chrono> // std::chrono::milliseconds

  std::mutex mtx;


  void print_block_1(int n, char c)
  {
    using namespace std::literals;
    for(int i = 0; i < n; ++i){
      std::this_thread::sleep_for(5ms);
      std::cout << c;
    }
    std::cout << '\n';
  }

  void print_block_2(int n, char c)
  {
    using namespace std::literals;

    std::lock_guard guard{ mtx }; // CTAD(C++17)
    // ------------------ critical region ------------------
    for(int i = 0; i < n; ++i){
      std::this_thread::sleep_for(5ms);
      std::cout << c;
    }
    std::cout << '\n';
    // ------------------ critical region ------------------
  }

  int main()
  {
    std::thread t1{ print_block_1, 20, '*' };
    std::thread t2{ print_block_1, 20, '$' };
    t1.join();
    t2.join();

    // output ->
    //  $*$*$**$$*$**$$*$*$**$$**$*$*$$*$**$$**
    //  $

    t1 = std::thread{ print_block_2, 20, '*' };
    t2 = std::thread{ print_block_2, 20, '$' };
    t1.join();
    t2.join();

    // output ->
    //  ********************
    //  $$$$$$$$$$$$$$$$$$$$
  }
*/

/*
  #include <mutex>  // std::mutex
  #include <thread> // std::thread

  int g_counter{};    // not atomic shared variable 
  std::mutex counter_mtx; 

  void try_increase()
  {
    for(int i = 0; i < 100'000; ++i){
      if (counter_mtx.try_lock()){  
        ++g_counter;
        // g_counter will be increase only if the mutex is acquired
        counter_mtx.unlock();
      }
    }
  }

  int main()
  {
    std::thread arr_tx[10];

    for(int i = 0; i < 10; ++i)
      arr_tx[i] = std::thread{ try_increase };

    for(auto& tx : arr_tx)
      tx.join();

    std::cout << "g_counter = " << g_counter << '\n';
    // output -> g_counter = 50732

    // normally g_counter should be 1'000'000
    // if all try_lock() calls are successful(returns true)
  }
*/

/*
  #include <mutex>      // std::timed_mutex
  #include <thread>     // std::thread
  #include <chrono>     // std::this_thread::sleep_for
  #include <syncstream> // std::osyncstream

  int g_counter{};
  std::timed_mutex t_mtx;

  void increment(int i)
  {
    using namespace std::literals;

    std::osyncstream os{ std::cout }; // (C++20)

    if (t_mtx.try_lock_for(10ms)){
      ++g_counter;
      os << "thread : " << i << " gets is in critical region\n";
      std::this_thread::sleep_for(5ms);
      t_mtx.unlock();
    }
    else
      os << "thread : " << i << " can not get in critical region\n";
  }

  int main()
  {
    std::thread t1{ increment, 1 };
    std::thread t2{ increment, 2 };
    std::thread t3{ increment, 3 };
    std::thread t4{ increment, 4 };
    t1.join();
    t2.join();
    t3.join();
    t4.join();

    std::cout << "g_counter = " << g_counter << '\n';
    // output ->
    //  thread : 3 can not get in critical region
    //  thread : 2 can not get in critical region
    //  thread : 1 can not get in critical region
    //  thread : 4 gets is in critical region
    //  g_counter = 1
  }
*/

/*
  // ------------------- rdbuf() reminder -------------------
  #include <fstream>  // std::ifstream

  int main()
  {
    std::ifstream ifs{ "run.bat" };
    if(!ifs){
      std::cerr << "file can not be opened\n";
      return 1;
    }

    std::cout << ifs.rdbuf();    
    // ifs.rdbuf() function returns filebuf*

    // output ->
    //  cls
    //  @echo off
    //  g++ -o prog concurrency.cpp -std=c++20
    //  if %errorlevel% neq 0 (
    //      echo Compilation failed.
    //      exit /b %errorlevel%
    //  )
    //  prog.exe
    //  del prog.exe
  }
*/

/*
  // before std::osyncstream class (C++20)
  #include <sstream>  // std::stringstream
  #include <mutex>    // std::mutex, std::lock_guard
  #include <thread>   // std::thread
  #include <vector>

  void print_1(int x)
  {
    std::cout << "print() x = " << x << '\n';
  }

  struct pcout : std::stringstream{
    ~pcout()
    {
      std::lock_guard guard{ cmutex };  // CTAD(C++17)
      std::cout << rdbuf();
      std::cout.flush();
    }
    static inline std::mutex cmutex;
  };

  void print_2(int x)
  {
    pcout{} << "print() x = " << x << '\n';
  }

  int main()
  {
    std::vector<std::thread> tvec;

    for (int i = 0; i < 10; ++i)
      tvec.emplace_back(std::thread{ print_2, i });

    for (auto& t : tvec)
      t.join();

    // output (print_1) ->
    //  print() x = print() x = 0
    //  print() x = 4
    //  print() x = 5print() x = 2
    //  print() x = 8
    //  
    //  print() x = 7
    //  print() x = 9
    //  1
    //  print() x = 3
    //  print() x = 6

    // output (print_2) ->
    //  print() x = 4
    //  print() x = 3
    //  print() x = 2
    //  print() x = 1
    //  print() x = 5
    //  print() x = 6
    //  print() x = 0
    //  print() x = 7
    //  print() x = 8
    //  print() x = 9
  }
*/

/*
  #include <mutex>      // std::mutex

  std::mutex mtx;

  int main()
  {
    try{
      mtx.lock();
      mtx.lock();

      mtx.unlock();
    }
    catch(const std::exception& ex){
      std::cout << "exception caught : " << ex.what() << '\n';
    }

    // when a mutex is acquired, it can not be acquired again 
    // if we try to acquire it again, compiler can throw an exception
    // but it is not guaranteed

    // - if it will throw an exception, 
    //  it will be system_error class
    // - if it will not throw an exception, 
    //  it will be undefined behaviour(ub)

    // msvc output ->
    //  exception caught : resource deadlock would occur: 
    //  resource deadlock would occur
  }
*/

/*
  #include <mutex>  // std::mutex, std::recursive_mutex
  #include <thread> // std::thread

  std::recursive_mutex r_mtx;
  std::mutex mtx;
  int g_counter = 0;

  void recursive_func_rmutex(char c, int n)
  {
    if (n < 0)
      return;

    r_mtx.lock();
    std::cout << c << ' ' << g_counter++ << '\n';
    recursive_func_rmutex(c, n - 1);
    r_mtx.unlock();
  }

  void recursive_func_mutex(char c, int n)
  {
    if (n < 0)
      return;

    mtx.lock();
    std::cout << c << ' ' << g_counter++ << '\n';
    recursive_func_mutex(c, n - 1);
    mtx.unlock();
  }

  int main()
  {
    // -------------------------------------------------------------
    // recursive function with std::mutex

    std::thread t1{ recursive_func_mutex, 'x', 5 };
    std::thread t2{ recursive_func_mutex, 'y', 5 };

    t1.join();
    t2.join();

    // output (recursive function with std::mutex) ->
    // y 0 
    // deadlock would occur

    // -------------------------------------------------------------
    // recursive function with std::recursive_mutex

    std::thread t1{ recursive_func_rmutex, 'x', 5 };
    std::thread t2{ recursive_func_rmutex, 'y', 5 };

    t1.join();
    t2.join();

    // output (recursive function with std::recursive_mutex) ->
    //  x 0
    //  x 1
    //  x 2
    //  x 3
    //  x 4
    //  x 5
    //  y 6
    //  y 7
    //  y 8
    //  y 9
    //  y 10
    //  y 11

    // x or y orders are not guaranteed(deterministic)

    // -------------------------------------------------------------
  }
*/

/*
  #include <mutex>  // std::mutex, std::lock_guard

  class AClass{
  public:
    void func()
    {
      std::lock_guard guard{ mtx };
      std::cout << "func() is called\n";
      foo();
      std::cout << "func() is finished\n";
    }

    void foo()
    {
      std::lock_guard guard{ mtx };
      std::cout << "foo() is called\n";
      std::cout << "foo() is finished\n";
    }
  private:
    // mutable std::mutex mtx;
    mutable std::recursive_mutex mtx;
  };

  int main()
  {
    AClass a;

    try{
      a.func();   // may throw exception depends on the compiler
    }
    catch(const std::exception& ex){
      std::cout << "exception caught : " << ex.what() << '\n';
    }

    // output -> (recursive mutex is used)
    //  func() is called
    //  foo() is called
    //  foo() is finished
    //  func() is finished
  }
*/

/*
  #include <mutex>  // std::mutex, std::lock_guard
  #include <thread> // std::thread

  int g_x{};  // non atomic shared variable 

  std::mutex mtx_func;
  std::mutex mtx_foo;

  void func()
  {
    std::lock_guard guard{ mtx_func };

    for (int i = 0; i < 1000; ++i)
      ++g_x;
  }

  void foo()
  {
    std::lock_guard guard{ mtx_foo };

    for (int i = 0; i < 1000; ++i)
      ++g_x;
  }

  int main()
  {
    std::thread t1{ func };
    std::thread t2{ foo };
    t1.join();
    t2.join();

    // no guarantee that g_x will be 2000 
    // after the execution of both threads
    // should be lock with same mutex object

    // std::cout << "g_x = " << g_x << '\n';
  }
*/

/*
  #include <mutex>  // std::mutex, std::unique_lock, std::timed_mutex
  #include <chrono> // std::chrono::steady_clock

  std::mutex mtx_1;
  std::mutex mtx_2;
  std::timed_mutex mtx_3;
  std::timed_mutex mtx_4;
  std::timed_mutex mtx_5;
  std::timed_mutex mtx_6;

  void func()
  {
    // --------------------------------------------------------------

    mtx_1.lock();
    std::unique_lock<std::mutex> guard_1(mtx_1, std::adopt_lock);

    // --------------------------------------------------------------
    
    std::unique_lock<std::mutex> guard_2(mtx_2, std::defer_lock);
    guard_2.lock();
    guard_2.try_lock();

    // --------------------------------------------------------------

    std::unique_lock<std::timed_mutex> guard_3(mtx_3, std::defer_lock);

    using namespace std::literals;
    auto tp = std::chrono::steady_clock::now() + 2s;

    guard_2.try_lock_for(1000ms); 
    guard_2.try_lock_until(tp); 

    // --------------------------------------------------------------

    std::unique_lock<std::timed_mutex> guard_4(mtx_4, std::try_to_lock);
    // guard_4 will try to lock the mutex
    // mtx_4 can be locked or not in this point

    if (guard_4)  // operator bool() member function
      std::cout << "mtx_4 is locked\n";
    else
      std::cout << "mtx_4 is not locked\n";

    if (guard_4.owns_lock())  // owns_lock() member function
      std::cout << "mtx_4 is locked\n";
    else
      std::cout << "mtx_4 is not locked\n";

    // --------------------------------------------------------------

    std::unique_lock guard_5(mtx_5, 1000ms);
    // guard_5 will try to lock the mutex for 1 second

    // --------------------------------------------------------------

    auto tp_2 = std::chrono::steady_clock::now() + 2s;
    std::unique_lock guard_6(mtx_6, tp_2);
    // guard_6 will try to lock the mutex until 2 seconds

    // --------------------------------------------------------------

    // std::unique_lock<> class template is non copyable but movable
    // can be transferred to another unique_lock object
  }
*/

/*
  // ------------ Problem ------------
  #include <mutex>  // std::mutex
  #include <thread> // std::thread, std::this_thread::sleep_for

  std::mutex mtx_a;
  std::mutex mtx_b;

  void foo()
  {
    using namespace std::literals;

    mtx_a.lock();
    std::this_thread::sleep_for(100ms);
    mtx_b.lock();
    std::cout << "foo()" << '\n';

    mtx_a.unlock();
    mtx_b.unlock();
  }

  void bar()
  {
    using namespace std::literals;

    mtx_b.lock();
    std::this_thread::sleep_for(100ms);
    mtx_a.lock();
    std::cout << "bar()" << '\n';

    mtx_b.unlock();
    mtx_a.unlock();
  }

  int main()
  {
    std::thread t1{ foo };
    std::thread t2{ bar };
    t1.join();
    t2.join();

    // t1 thread will acquire mtx_a and t2 thread will acquire mtx_b
    // for t1 thread to continue it needs to acquire mtx_b
    // and for t2 thread to continue it needs to acquire mtx_a
    // because of both of them are blocked by each other, 
    // it is a deadlock
  }
*/

/*
  // ------------ 1st solution ------------
  // if both threads acquire the mutexes in the same order
  // there will be no deadlock

  #include <mutex>  // std::mutex
  #include <thread> // std::thread, std::this_thread::sleep_for

  std::mutex mtx_a;
  std::mutex mtx_b;

  void foo()
  {
    using namespace std::literals;

    mtx_a.lock();
    std::this_thread::sleep_for(100ms);
    mtx_b.lock();
    std::cout << "foo()" << '\n';

    mtx_a.unlock();
    mtx_b.unlock();
  }

  void bar()
  {
    using namespace std::literals;

    mtx_a.lock();
    std::this_thread::sleep_for(100ms);
    mtx_b.lock();
    std::cout << "bar()" << '\n';

    mtx_a.unlock();
    mtx_b.unlock();
  }

  int main()
  {
    std::thread t1{ foo };
    std::thread t2{ bar };
    t1.join();
    t2.join();
    // output ->
    //  foo()
    //  bar()
  }
*/

/*
  // ------------ 2nd solution ------------
  // using std::lock() global function

  #include <mutex>  // std::mutex, std::lock, std::lock_guard
  #include <thread> // std::thread, std::this_thread::sleep_for

  std::mutex mtx_a;
  std::mutex mtx_b;

  void foo()
  {
    using namespace std::literals;

    std::lock(mtx_a, mtx_b);
    std::lock_guard guard_a{ mtx_a, std::adopt_lock };
    std::lock_guard guard_b{ mtx_b, std::adopt_lock };

    std::this_thread::sleep_for(100ms);
    std::cout << "foo()" << '\n';
  }

  void bar()
  {
    using namespace std::literals;

    std::lock(mtx_a, mtx_b);
    std::lock_guard guard_a{ mtx_a, std::adopt_lock };
    std::lock_guard guard_b{ mtx_b, std::adopt_lock };

    std::this_thread::sleep_for(100ms);
    std::cout << "bar()" << '\n';
  }

  int main()
  {
    std::thread t1{ foo };
    std::thread t2{ bar };
    t1.join();
    t2.join();
    // output ->
    //  foo()
    //  bar()
  }
*/

/*
  // ------------ 3rd solution ------------
  // using std::scoped_lock variadic class template (C++17)

  #include <mutex>  // std::mutex, std::scoped_lock
  #include <thread> // std::thread, std::this_thread::sleep_for

  std::mutex mtx_a;
  std::mutex mtx_b;

  void foo()
  {
    using namespace std::literals;

    std::scoped_lock<std::mutex, std::mutex> guard{ mtx_a, mtx_b };
    std::this_thread::sleep_for(100ms);
    std::cout << "foo()" << '\n';
  }

  void bar()
  {
    using namespace std::literals;

    std::scoped_lock guard{ mtx_a, mtx_b }; // CTAD(C++17)
    std::this_thread::sleep_for(100ms); 
    std::cout << "bar()" << '\n';
  }

  int main()
  {
    std::thread t1{ foo };
    std::thread t2{ bar };
    t1.join();
    t2.join();
    // output ->
    //  bar()
    //  foo()
  }
*/

/*
  #include <mutex>      // std::mutex, std::lock
  #include <syncstream> // std::osyncstream
  #include <thread>     // std::thread

  std::mutex mtx_1, mtx_2; 

  void foo()
  {
    std::lock(mtx_1, mtx_2);
    // std::lock() will guarantee that after std::lock() call
    // both mtx_1 and mtx_2 will be acquired(locked)

    mtx_1.unlock();
    mtx_2.unlock();
    std::osyncstream{ std::cout } << "foo()\n";
  }

  void bar()
  {
    std::lock(mtx_1, mtx_2);

    mtx_1.unlock();
    mtx_2.unlock();
    std::osyncstream{ std::cout } << "bar()\n";
  }

  int main()
  {
    std::thread t1{ foo };
    std::thread t2{ bar };

    t1.join();
    t2.join();

    // output ->
    //  foo()
    //  bar()
  }
*/

/*
  #include <thread>     // std::this_thread::sleep_for, std::thread
  #include <mutex>      // std::mutex
  #include <syncstream> // std::osyncstream
  #include <functional> // std::ref

  struct HasCriticalCode{
    std::mutex mtx;
  };

  void func(HasCriticalCode& x, HasCriticalCode& y)
  {
    using namespace std::literals;
    std::osyncstream os{ std::cout };

    x.mtx.lock();
    std::this_thread::sleep_for(1ms);
    os << "acquired mutex at the address of " << &x << '\n';

    y.mtx.lock();
    os << "acquired mutex at the address of " << &y << '\n';

    y.mtx.unlock();
    x.mtx.unlock();
  }

  int main()
  {
    HasCriticalCode a, b;

    // -------------------------------------------------

    std::thread t1{ func, std::ref(a), std::ref(b) };
    std::thread t2{ func, std::ref(b), std::ref(a) };

    // because of the call order, this will cause a deadlock

    // -------------------------------------------------

    std::thread t1{ func, std::ref(a), std::ref(b) };
    std::thread t2{ func, std::ref(a), std::ref(b) };

    t1.join();
    t2.join();

    // output ->
    //  acquired mutex at the address of 0xe5d2bff768
    //  acquired mutex at the address of 0xe5d2bff760
    //  acquired mutex at the address of 0xe5d2bff768
    //  acquired mutex at the address of 0xe5d2bff760

    // -------------------------------------------------
  }
*/

/*
  Birden fazla thread'in bulunması durumunda bir fonksiyonun 
  sadece bir kere çalıştırılması gerekiyor. 
    - özellikle bir değişkene atama yaptığımız zaman aynı 
    değişkene birden fazla thread'in atama yapmasına engel olmak.
    - dinamik ömürlü bir değişkenin sadece bir kere hayata 
    gelmesini sağlamak.

  std::once_flag class and std::call_once class template
    - std::once_flag fonksiyonun sadece 1 kere çalıştırılmasına 
    yönelik bayrak vazifesi görüyor.
    - std::call_once, once_flag'i kullanarak çağrılacak 
    callable'ı ve callable'a gönderilecek argümanları alıyor.

  std::call_once çağrısına ilk gelen thread fonksiyonu çağırıyor.
  diğer threadler bu esnada bloke oluyorlar. Fonksiyonun 
  çalışması bittiğinde diğer threadlerin blokesi açılıyor.
*/

/*
  #include <thread> // std::thread
  #include <mutex>  // std::call_once, std::once_flag
  #include <vector>

  std::once_flag g_flag;

  void func(int id)
  {
    std::call_once(g_flag, [id](){
      std::cout << "thread id = " << id << " is called.\n";
    });
  }

  int main()
  {
    std::vector<std::thread> tvec;

    for(int i = 0; i < 10; ++i)
      tvec.emplace_back(func, i);

    for (auto& tx : tvec)
      tx.join();

    // output -> thread id = 5 is called.
  }
*/

/*
  #include <thread> // std::thread, std::this_thread::sleep_for 
  #include <mutex>  // std::call_once, std::once_flag
  #include <thread>
  #include <chrono>

  std::once_flag g_flag;

  void foo()
  {
    using namespace std::literals;
    std::this_thread::sleep_for(100ms);
    std::call_once(g_flag, [](){
      std::cout << "registered in foo\n";
    });
  }

  void bar()
  {
    using namespace std::literals;
    std::this_thread::sleep_for(100ms);
    std::call_once(g_flag, [](){
      std::cout << "registered in bar\n";
    });
  }

  int main()
  {
    std::thread tx_arr[10];

    for(int i = 0; i < 10; ++i){
      tx_arr[i] = i % 2 == 0  ? std::thread{ foo } 
                              : std::thread{ bar };
    }

    for (auto& tx : tx_arr)
      tx.join();

    // output -> registered in foo
  }
*/

/*
  #include <mutex>      // std::once_flag, std::call_once
  #include <vector>
  #include <thread>     // std::thread
  #include <syncstream> // std::osyncstream
  #include <fstream>    // std::ofstream

  class Singleton{
  public:
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

    static void init_function()
    {
      m_instance = new Singleton;
    }

    static Singleton* get_instance()
    {
      std::call_once(m_init_flag, init_function);
      return m_instance;
    }
  private:
    Singleton() = default;  // private constructor

    static inline std::once_flag m_init_flag;
    static inline Singleton* m_instance{};
  };

  void foo()
  {
    static std::ofstream ofs{ "out.txt" };
    std::osyncstream{ ofs } << Singleton::get_instance() 
                            << '\n';
  }

  int main()
  {
    std::vector<std::thread> tvec;

    for(int i = 0; i < 500; ++i)
      tvec.emplace_back(foo);

    for(auto& tx : tvec)
      tx.join();

    // check <--- out.txt ---> file
  }
*/

/*
                    ----------------------
                    | condition variable |
                    ----------------------
*/

/*
  - bir thread'in, bir diğer thread'in ürettiği veriyi kullanması.
  - bir thread'in işlemleri yapıp, diğer thread'i hazır hale getirmesi.
  - producer - consumer problem
*/

/*
  // Bad approach to producer-consumer problem

  #include <mutex>  // std::mutex, std::unique_lock, std::lock_guard
  #include <thread>

  int shared_variable = 0;  // this will be used as a condition
  std::mutex mtx;

  void producer()
  {
    using namespace std::literals;
    std::this_thread::sleep_for(1s);

    std::lock_guard guard{ mtx }; // mutex is acquired
    // ------------------ critical region ------------------
    shared_variable = 999;
    // ------------------ critical region ------------------
  }

  // wasting CPU cycles for checking the condition 
  // while( shared_variable == 0 )
  void consumer()
  {
    std::unique_lock ulock{ mtx }; 
    // ------------------ critical region ------------------
    while (shared_variable == 0){
    // ------------------ critical region ------------------
      ulock.unlock();
      ulock.lock();
    }

    // consume the shared_variable
    std::cout << "shared_variable = " << shared_variable << '\n';
  }

  int main()
  {
    std::thread t1{ producer };
    std::thread t2{ consumer };
    t1.join();
    t2.join();
    // output -> shared_variable = 999
  }
*/

/*
  // Better but still bad approach to producer-consumer problem
  // ------------------------------------------------

  #include <mutex>  // std::mutex, std::unique_lock, std::lock_guard
  #include <thread> // std::this_thread::sleep_for

  int shared_variable = 0;
  std::mutex mtx;

  void producer()
  {
    using namespace std::literals;
    std::this_thread::sleep_for(1s);

    std::lock_guard guard{ mtx }; // mutex is acquired
    // ------------------ critical region ------------------
    shared_variable = 999;
    // ------------------ critical region ------------------
  }

  // wasting CPU cycles for checking the condition 
  // while( shared_variable == 0 )
  void consumer()
  {
    std::unique_lock ulock{ mtx }; 

    while (shared_variable == 0){

      using namespace std::literals;
      std::this_thread::yield();
      std::this_thread::sleep_for(100ms);
      // if sleeping time is too short, it will also waste CPU cycles
      // if sleeping time is too long, once the producer thread
      // is finished, consumer thread will be wait more than it should
      ulock.unlock();
      ulock.lock();
    }
    // consume the shared_variable
    std::cout << "shared_variable = " << shared_variable << '\n';
  }

  int main()
  {
    std::thread t1{ producer };
    std::thread t2{ consumer };
    t1.join();
    t2.join();
    // output -> shared_variable = 999
  }
*/

/*
  - condition variable is basically optimizing the code below
  ```
    while (shared_variable == 0)
    {
      using namespace std::literals;
      std::this_thread::yield();
      std::this_thread::sleep_for(100ms);
      ulock.unlock();
      ulock.lock();
    }
  ```
*/

/*
  - std::condition_variable is non copyable, non movable class

  - both producer and consumer threads will use the same mutex

  Producer thread :
    1. using std::lock_guard and acquire a mutex.
    2. when the mutex is locked it will set the shared_variable
    even the shared_variable is atomic it should be set when 
    mutex is locked.
    3. call the notify_one or notify_all member functions of 
    std::condition_variable object. This should not be done 
    when the mutex is locked.

  Consumer thread(s):
    1. using unique_lock to acquire the same(which producer threads used)
    mutex. mutex might be locked and unlocked more than once so 
    better using unique_lock.
    2. first it should check the condition that shared_variable 
    might already been set. 
    If this condition is not checked and the consumer thread went 
    to wait state it will be block forever.(lost wakeup)
    3. If the condition is not met, it will call one of the wait 
    functions of std::condition_variable object.
    (wait, wait_for, wait_until)
      - when wake function is called, std::condition_variable
      will lock the mutex to itself(unlock consumers thread lock) 
      and block the consumer thread.
    4. When Producer thread calls notify_one or notify_all of 
    std::condition_variable object, consumer thread will wake up
    and will lock the mutex again which before was locked by the
    std::condition_variable.
    5. Wokeup(consumer) thread should check the condition again
    because of spurious wakeup. If the condition is not met,
    it should go to wait state again.
    spuruous wakeup : thread woke up without notification(randomly)
    <--- check spurious_wake.png --->
*/

/*
  #include <condition_variable> // std::condition_variable
  #include <mutex>  // std::unique_lock, std::lock_guard, std::mutex
  #include <thread>

  int data{}; // task
  bool ready_flag = false;
  std::mutex mtx;
  std::condition_variable cond_var;

  void producer()
  {
    std::cout << "producer is producing the data\n";

    {
      std::lock_guard guard{ mtx }; // mutex is locked
      // ------------------ critical region ------------------
      data = 999;
      ready_flag = true;
      // ------------------ critical region ------------------
    }
    // mutex is unlocked here(std::lock_guard's scope ends)
    cond_var.notify_one();
  }

  void consumer()
  {
    {
      std::unique_lock ulock{ mtx }; // mutex is locked
      // ------------------ critical region ------------------
      // wait function's predicate overload
      // will check whole conditions
      cond_var.wait(ulock, []{ return ready_flag; }); 
      // ------------------ critical region ------------------
    }
    // mutex is unlocked here(std::unique_lock's scope ends)

    std::cout << "data = " << data << '\n';
  }

  int main()
  {
    std::thread t1{ producer };
    std::thread t2{ consumer };
    t1.join();
    t2.join();

    // output ->
    //  producer is producing the data
    //  data = 999
  }
*/

/*
  #include <mutex>  // std::unique_lock

  // wait function's predicate overload
  // member template function of std::condition_variable class

  template <typename Pred>
  void wait(std::unique_lock<std::mutex>& ulock, Pred pred)
  {
    while (!pred()){
      ulock.unlock();
      ulock.lock();
    }
  }
*/

/*
  #include <mutex>  // std::mutex, std::unique_lock, std::scoped_lock
  #include <vector>
  #include <condition_variable> // std::condition_variable
  #include <thread>

  class IStack{
  public:
    IStack() {}
    IStack(const IStack&) = delete;
    IStack& operator=(const IStack&) = delete;

    int pop()
    {
      std::unique_lock ulock{ m_mtx };
      m_cv.wait(ulock, [this]{ return !m_vec.empty(); });
      int val = m_vec.back();
      m_vec.pop_back();
      ulock.unlock(); 
      // because of no more shared_variable is being used

      return val;
    }
    void push(int x)
    {
      {
        std::scoped_lock slock{ m_mtx };  // std::scoped_lock (C++17)
        m_vec.push_back(x);
      }
      m_cv.notify_one();
    }
  private:
    std::vector<int> m_vec;
    mutable std::mutex m_mtx;
    mutable std::condition_variable m_cv;
  };

  constexpr int n = 10;
  IStack s;

  void producer()
  {
    for(int i = 0; i < n; ++i)
      s.push(2 * i + 1);
  }

  void consumer()
  {
    for(int i = 0; i < n; ++i)
      std::cout << s.pop() << '\n';
  }

  int main()
  {
    std::thread t1{ producer };
    std::thread t2{ consumer };
    t1.join();
    t2.join();

    // output ->
    //  19
    //  17
    //  15
    //  13
    //  11
    //  9
    //  7
    //  5
    //  3
    //  1
  }
*/

/*
  #include <mutex>  // std::mutex, std::unique_lock, std::lock_guard
  #include <condition_variable> // std::condition_variable
  #include <string>
  #include <thread>

  std::mutex mtx;
  std::condition_variable cv;
  std::string data;
  bool ready_flag = false;
  bool processed_flag = false;

  void worker_thread()
  {
    // Wait until main() sends data
    std::unique_lock<std::mutex> ulock{ mtx };
    cv.wait(ulock, []{ return ready_flag; });

    // after the wait, we own the lock
    std::cout << "Worker thread is processing data\n";

    // ------------------ critical region ------------------
    data += " after processing";

    // send data back to main()
    processed_flag = true;
    // ------------------ critical region ------------------

    std::cout << "Worker thread signals data processing completed\n";

    // Manual unlocking is done before notifying, to avoid waking up
    // the waiting thread only to block again
    ulock.unlock();
    cv.notify_one();
  }

  int main()
  {
    std::thread worker{ worker_thread };  

    data = "Example data";

    // send data to the worker thread
    {
      std::lock_guard guard{ mtx };
      ready_flag = true;
      std::cout << "main() signals data ready for processing\n";
    }
    cv.notify_one();

    // wait for the worker thread
    {
      std::unique_lock ulock{ mtx };
      cv.wait(ulock, []{ return processed_flag; });
    }

    std::cout << "Back in main(), data = " << data << '\n';

    worker.join();

    // output ->
    //  main() signals data ready for processing
    //  Worker thread is processing data
    //  Worker thread signals data processing completed
    //  Back in main(), data = Example data after processing
  }
*/

/*
  #include <condition_variable> // std::condition_variable
  #include <mutex>  
  #include <thread> // std::this_thread::sleep_for
  #include <future> // std::async, std::launch::async
  #include <queue>
  #include <syncstream> // std::osyncstream

  std::queue<int> data_queue;   // shared variable
  std::mutex mtx;
  std::condition_variable cv;

  void provider(int val)
  {
    for (int i = 0; i < 3; ++i)
    {
      {
        std::lock_guard guard{ mtx };
        data_queue.push(val + i);
      } // lock is released here

      cv.notify_one();
      std::this_thread::sleep_for(std::chrono::milliseconds(val));
    }
  }

  void consumer(int num)
  {
    // pop values if available (num identifies the consumer)

    while(true)
    {
      int val;
      {
        std::unique_lock ulock{ mtx };
        cv.wait(ulock, []{ return !data_queue.empty(); });

        val = data_queue.front();
        data_queue.pop();
      } // lock is released here

      std::osyncstream { std::cout }  << "consumer " << num 
                                      << ": "<< val << '\n';
    }
  }

  int main()
  {
    // start 3 providers for values 100+, 300+ and 500+
    auto p1 = std::async(std::launch::async, provider, 100);
    auto p2 = std::async(std::launch::async, provider, 300);
    auto p3 = std::async(std::launch::async, provider, 500);

    // start two consumers printing the values
    auto c1 = std::async(std::launch::async, consumer, 1);
    auto c2 = std::async(std::launch::async, consumer, 2);
  }

  // output ->
  //  consumer 1: 300
  //  consumer 1: 500
  //  consumer 2: 100
  //  consumer 1: 101
  //  consumer 2: 102
  //  consumer 1: 301
  //  consumer 2: 501
  //  consumer 1: 302
  //  consumer 2: 502
  //  ..... (infinite loop in consumer function -> wait())
*/

/*
  #include <condition_variable>
  #include <mutex>  // std::mutex, std::unique_lock
  #include <thread>

  std::condition_variable cv;
  std::mutex cv_mtx;
  // This mutex is used for three purposes
  // 1. to synchronize access to the shared variable i
  // 2. to synchronize access to std::cerr
  // 3. for the conditional variable cv

  int i = 0;

  void waits()
  {
    std::unique_lock<std::mutex> ulock{ cv_mtx };
    std::cerr << "Waiting... \n";
    cv.wait(ulock, [] { return i == 1; });
    std::cerr << "... finished waiting. i == 1\n";
  }

  void signals()
  {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    {
      std::lock_guard guard{ cv_mtx };
      std::cerr << "Notifying...\n";
    }
    cv.notify_all();

    std::this_thread::sleep_for(std::chrono::seconds(1));

    {
      std::lock_guard guard{ cv_mtx };
      i = 1;
      std::cerr << "Notifying again...\n";
    }
    cv.notify_all();
  }

  int main()
  {
    std::thread t1(waits), t2(waits), t3(waits), t4(signals);
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    // output ->
    //  Waiting...
    //  Waiting...
    //  Waiting...
    //  Notifying...
    //  Notifying again...
    //  ... finished waiting. i == 1
    //  ... finished waiting. i == 1
    //  ... finished waiting. i == 1
  }
*/

/*
                          ----------
                          | atomic |
                          ----------
*/

/*
  atomic işlem : bölünemeyen işlem
    öyle bir işlem ki, birden fazla parça ile yapılıyor olsa dahi
    o parçaların arasına başka bir thread'deki bir işlem giremez.

  ++x;
    - read
    - modify
        ---> başka bir thread burada araya girebilir 
        ---> örneğin x'in değerini okuyabilir.
    - write

  böyle işlemler atomik olarak yapılmaz ise ve böyle değişkenler 
  birden fazla thread tarafından kullanılan değişkenler ise
  data race oluşur ve tanımsız davranışa(ub) yol açar.

  - bir işlemin atomik olması demek, başka bir thread'in
    -> ya bir işlem tamamlanmadan önce değişkenin eski değerini görmesi
    -> ya da işlem tamanlandıktan sonra, değişkenin yeni değerini 
      görmesi demektir.

  - atomik değişkenler torn read/write riskini ortadan kaldırır.

  - iki ayrı işlem atomik ise, bu iki işlemin oluşturduğu ifadedeki
    işlemlerin toplamı atomik olmak zorunda değil.

    ++x + y++;  // x ve y atomik değişkenler
    "++x + y++" ifadesi(expression) atomik değildir.

  - atomik bir tür üstünde yapılan atomik bir işlem lock-free olmak 
    zorunda değil. Derleyici bu işlemi arka planda bir lock ile
    gerçekleştirebilir.
*/

// TODO: memory model ile alakali olan kismi duzenleyip tekrar ekle

/*
  memory model : multithread çalışacak programların bellekteki 
    okuma, yazma işlemleri ile paylaşılan değişkenler arasındaki 
    ilişkileri tanımlayan bir dokümandır.


  <--- check sequential_consistency.png --->
  <--- check sequential_consistency_2.png --->
  sequencial consistent : her threaddeki program sıralaması korunmak
    zorunda.

  - Java language's memory model is sequencial consistent.
*/  

/*
        -------- happens-before relationship --------

  - A ve B iki operasyon olsun. Bu operasyonlar aynı thread'de 
    gerçekleştirilen operasyonlar olabildiği gibi 
    farklı thread'lerde gerçekleştirilen operasyonlar da olabilir. 

  - Eğer A operasyonunun etkileri, B operasyonunu yürütecek thread'de 
    B operasyonu yürütüldüğünde görülür durumda ise,
    A happens before B garantisi söz konusudur.

  - happens-before ilişkisi "zamansal olarak daha önce gerçekleşme" 
    ilişkisine göre çok daha güçlü bir durumdur.

  - Eğer A operasyonu B operasyonuna göre zamansal açıdan 
    daha önce gerçekleştiriliyor ise bu A'nın etkilerinin 
    B'yi yürütecek thread'de, 
    B yürütülmeden önce görülür olma garantisi değildir.
    caching, store buffer vs gibi mekanizmalar 
    operasyonun etkilerinin 
    diğer thread'lerde görülmesini geciktirebilir.
*/

/*
        -------- synchronizes with relationship --------

  Thread creation : The completion of the constructor for a thread
  object T synchronizes with the start of the invocation 
  of the thread function for T.

  thread sınıfı türünden bir nesne oluşturup, onun ctor'una
  bir workload verildiğinde, eğer ctor'un kodunun 
  çalışması tamamlanmışsa, workload olarak çalışan fonksiyonun 
  çağrısı ile bir senkronizasyon yaratılmış olur.

  -> if there is a synchronizes with relationship it will 
    guarantees happens-before relationship.

  Thread join : The completion of the execution of a thread 
  function for a thread object T synchronizes with(the return of)
  a join operation on T.

  Mutex unlock/lock : All prior unlock operations on a mutex M
  synchronize with (the return of) a lock operation on M.
  <--- check synchronizes_with_mutex.png --->

*/

/*
  #include <thread>
  #include <cassert>

  int shared_variable = 0;

  // Work_C (general execution of this function)
  void func()
  {
    // Spot_D
    assert(shared_variable == 1);

    ++shared_variable;
  }

  int main()
  {
    shared_variable = 1;    
    // Spot_A
    std::thread tx{ func }; 
    // Spot_B

    tx.join();
    // Spot_E

    assert(shared_variable == 2);

    // because of Spot_B(thread's ctor's code is executed) and 
    // Work_C(workload is on execution or already executed) 
    // have a synchronizes with relationship

    // - so it is guaranteed that Spot_A and Spot_D 
    //  have a happens-before relationship 
    // - It is guaranteed that shared_variable's value is 1
    //  when "func" is started executing. 

    // - It is guaranteed that in Spot_E shared_variable's 
    //  value is 2 because thread is already been executed.

    // Work_C's completion of execution synchronizes with
    // Spot_E(join operation's execution) 
  }
*/

/*
  #include <atomic>

  int main()
  {
    std::cout.setf(std::ios::boolalpha);

    std::atomic<int> x;
    std::atomic<long long int> y;

    std::cout << x.is_lock_free() << '\n';  // output -> true
    std::cout << y.is_lock_free() << '\n';  // output -> true


    constexpr auto b = std::atomic<long long int>::is_always_lock_free;
    // std::atomic class template have 
    // constexpr static data member `is_always_lock_free`
    // for compile time operations
    // if sometimes or always not lock free, it will be false
    // else it will be true

    std::cout << b << '\n';  // output -> true
  }
*/

/*
  #include <atomic>

  int main()
  {
    std::atomic_flag f;   // Always lock-free guaranteed
  }
*/

/*
  #include <atomic>

  int main()
  {
    using namespace std;

    cout << boolalpha;

    // -----------------------------------------------------

    // std::atomic_flag flag_x{ false };  // syntax error
    // std::atomic_flag flag_y{ true };   // syntax error

    std::atomic_flag flag_1 = ATOMIC_FLAG_INIT; 
    // initialization C++17 and before, ATOMIC_FLAG_INIT's value
    // is implementation-defined

    std::atomic_flag flag_2;                
    // since C++20, default initialization is valid and it has 
    // false value

    // -----------------------------------------------------

    // "test" member function is added in C++20 
    cout << "flag_1 = " << flag_1.test() << '\n'; 
    // output -> flag_1 = false
    cout << "flag_2 = " << flag_2.test() << '\n'; 
    // output -> flag_2 = false

    auto old_flag_1_value = flag_1.test_and_set();
    cout << "old_flag_1_value = " << old_flag_1_value << '\n';
    // output -> old_flag_1_value = false
    cout << "flag_1 = " << flag_1.test() << '\n';
    // output -> flag_1 = true

    // -----------------------------------------------------

    flag_1.clear();
    cout << "flag_1 = " << flag_1.test() << '\n';
    // output -> flag_1 = false

    // -----------------------------------------------------
  }
*/

/*
  #include <thread>
  #include <atomic>
  #include <mutex>
  #include <vector>

  class SpinLockMutex{
  public:
    SpinLockMutex()
    // : m_atomic_flag{ ATOMIC_FLAG_INIT } // C++17 and before
    {
      m_atomic_flag.clear();
    }

    void lock()
    {
      while(m_atomic_flag.test_and_set())
        ; // null statement
    }
    void unlock()
    {
      m_atomic_flag.clear();
    }
  private:
    std::atomic_flag m_atomic_flag; 
    // C++20 value will be false when default ctor
  };

  SpinLockMutex mtx;
  unsigned long long counter = 0;

  void func()
  {
    for (int i = 0; i < 100'000; ++i)
    {
      mtx.lock();
      ++counter;
      mtx.unlock();
    }
  }

  int main()
  {
    std::vector<std::thread> tvec;

    for (int i = 0; i < 10; ++i)
      tvec.emplace_back(func);

    for (auto& tx : tvec)
      tx.join();

    std::cout << "counter = " << counter << '\n';
    // output -> counter = 1'000'000
  }
*/

/*
  // atomic_flag and atomic<bool> are not the types.

  #include <atomic>

  int main()
  {
    using namespace std;

    cout << boolalpha;

    // -----------------------------------------------------------

    std::atomic<bool> flag_1; // default init of std::atomic<bool>
    // indetermined(garbage) value before C++20
    // false since C++20

    cout << "flag_1 = " << flag_1 << '\n'; 
    // output -> flag_1 = false 

    // -----------------------------------------------------------

    atomic flag_2 = false;   // CTAD(C++17)
    atomic flag_3 = 10;      // CTAD(C++17)

    cout << "flag_2 = " << flag_2 << '\n';
    // output -> flag_2 = false

    cout << "flag_3 = " << flag_3 << '\n';
    // output -> flag_3 = 10

    // -----------------------------------------------------------

    // non copy constructible and non move constructible

    std::atomic<bool>{ flag_2 }; // syntax error
    // error: use of deleted function 
    // 'std::atomic<bool>::atomic(const std::atomic<bool>&)'

    flag_1 = flag_2; // syntax error
    // error: use of deleted function 
    // 'std::atomic<bool>& 
    //    std::atomic<bool>::operator=(const std::atomic<bool>&)'

    // -----------------------------------------------------------

    flag_1 = true;
    flag_2 = false;
    flag_1.store(false);
    flag_2.store(true);

    cout << "flag_1 = " << flag_1 << '\n';    // operator T() const
    // output -> flag_1 = false

    cout << "flag_2 = " << flag_2 << '\n';    // operator T() const
    // output -> flag_2 = true

    // -----------------------------------------------------------

    auto b = flag_1.exchange(true);
    // exchange member function returns the old value  
    // and sets the new value

    cout << "b = " << b << '\n';
    // output -> b = false
    cout << "flag_1 = " << flag_1 << '\n';
    // output -> flag_1 = true
    cout << "flag_1.load() = " << flag_1.load() << '\n';
    // output -> flag_1.load() = true

    // -----------------------------------------------------------
  }
*/

/*
                  --------------------------
                  | Compare and Swap (CAS) |
                  --------------------------
*/

/*
  #include <atomic>

  int main()
  {
    std::cout << std::boolalpha;

    std::atomic<int> a;

    // ----------------------------------------------------------

    std::cout << "a = " << a << '\n';
    // output -> a = 0
    std::cout << "a.load() = " << a.load() << '\n';
    // output -> a.load() = 0

    // ----------------------------------------------------------

    // if "a" is not equal to "expected" 
    // "a" will not be set
    // "expected" will be set to "a"'s value
    // and function will return false

    a.store(11);
    int expected = 22;
    bool result = a.compare_exchange_strong(expected, 88);

    std::cout << "a = " << a << '\n';
    // output -> a = 11
    std::cout << "result = " << result << '\n';
    // output -> result = false
    std::cout << "expected = " << expected << '\n';
    // output -> expected = 11

    // ----------------------------------------------------------

    // if "a" is equal to "expected" 
    // "a" will be set to desired(2nd argument)
    // "expected" will not be set
    // and function will return true

    a = 33;
    expected = 33;
    result = a.compare_exchange_strong(expected, 55);

    std::cout << "a = " << a << '\n';
    // output -> a = 55
    std::cout << "result = " << result << '\n';
    // output -> result = true
    std::cout << "expected = " << expected << '\n';
    // output -> expected = 33

    // ----------------------------------------------------------
  }
*/

/*
  // ------------------------ Problem ------------------------
  #include <atomic>

  int main()
  {
    using namespace std;

    atomic<int> a = 10; 

    // *= operation is not atomic
    // - We want to to a *= 50 operation atomically


    // -----------------------------------------------------

    // - lots of thread can change the value of "a" 
    //  between load and store

    int temp  = a.load();
      // ---> if another thread changes the value of "a" to 100
    a.store(temp * 50);
    // our thread will still use the old value of "a"(temp)
    // and change it to 500(10 * 50) instead of 5000(100 * 50)
  }
*/

/*
  // ------------------------ Solution ------------------------

  #include <atomic>

  int main()
  {
    using namespace std;

    atomic<int> a = 10; 

    // *= operation is not atomic
    // - We want to to a *= 50 operation atomically

    int temp = a.load();

    // -----------------------------------------------------

    // "a" has been changed to 100
    // in first iteration of the loop
    // a.compare_exchange_strong(temp, temp * 50)
    // will return false 
    // temp will be set to 100

    // in second iteration of the loop
    // a.compare_exchange_strong(temp, temp * 50)
    // will return true
    // a will be set to 100 * 50 = 5000

    while (!a.compare_exchange_weak(temp, temp * 50))
      ; // null statement

    // -----------------------------------------------------
  }
*/

/*
  #include <atomic>

  int main()
  {
    using namespace std;

    atomic<int> a = 10;

    ++a;
    a++;
    a = 5;
    a.load();
    a += 5;
    a -= 10;
    a &= 4;
    a ^= 4;
    a |= 4;
    auto result = a.exchange(450);
    
    int expected = 12;
    int desired = 100;
    a.compare_exchange_strong(expected, desired);
    // compare_exchange_strong function have a set guarantee
    // if false expected will be set to a's value
    // if true a will be set to desired's value

    // <---- check compare_exchange_weak.png ---->
    // inside loop compare_exchange_weak can be used
  }
*/

/*
  #include <atomic>

  int main()
  {
    std::atomic<int> x;

    int val = ++x;  // atomic<T>::operator++()
    std::cout << "val = " << val << '\n';
    // output -> val = 1
    std::cout << "x = " << x << '\n';
    // output -> x = 1

    val = x++;      // atomic<T>::operator++(int)
    std::cout << "val = " << val << '\n';
    // output -> val = 1
    std::cout << "x = " << x << '\n';
    // output -> x = 2
  }
*/

/*
  #include <atomic>
  #include <concepts>

  template <std::integral T>
  void atomic_inc(std::atomic<T>& x)
  {
    T val{ x };
    while (!x.compare_exchange_weak(val, val + 1)) {}
  }
*/

/*
  <--- check atomic_type_operations_before_cpp20.png --->
*/

/*
  #include <atomic>
  #include <thread>

  class AtomicCounter{
  public:
    AtomicCounter() : m_counter{ 0 } {}
    AtomicCounter(int val) : m_counter{ val } {}
    int operator++()    { return ++m_counter; }
    int operator++(int) { return m_counter++; }
    int operator--()    { return --m_counter; }
    int operator--(int) { return m_counter--; }
    int get() const { return m_counter.load(); }
    operator int() const { return m_counter.load(); }
  private:
    std::atomic<int> m_counter;
  };

  AtomicCounter cnt;

  void foo()
  {
    for (int i = 0; i < 1'000'000; ++i)
      ++cnt;
  }

  int main()
  {
    std::thread tx_arr[10];

    for (auto& tx : tx_arr)
      tx = std::thread{ foo };

    for (auto& tx : tx_arr)
      tx.join();

    std::cout << "cnt = " << cnt.get() << '\n';
    // output -> cnt = 10'000'000
    std::cout << "cnt = " << cnt << '\n';
    // output -> cnt = 10'000'000
  }
*/

/*
  #include <atomic>

  int main()
  {
    int a[] = { 11, 22, 33, 44, 55, 66 };
    std::atomic<int*> aptr = a;

    std::cout << *aptr.load() << '\n';  // output -> 11
    std::cout << *aptr << '\n';         // output -> 11

    ++aptr;
    std::cout << *aptr << '\n';         // output -> 22

    aptr += 2;
    std::cout << *aptr << '\n';         // output -> 44
  }
*/

/*
  <--- check sequiential_consistency_example.png --->
*/

/*
  #include <atomic>
  #include <thread>
  #include <cassert>

  std::atomic_bool x_flag, y_flag;
  std::atomic<int> ival;

  void set_x()
  {
    x_flag.store(true);
  }

  void set_y()
  {
    y_flag.store(true);
  }

  void read_x_then_y()
  {
    while (!x_flag.load())
      ; // null statement

    if (y_flag.load())
      ++ival;
  }

  void read_y_then_x()
  {
    while (!y_flag.load())
      ; // null statement

    if (x_flag.load())
      ++ival;
  }

  void func()
  {
    x_flag = false;
    y_flag = false;
    ival = 0;

    std::thread t1{ set_x };
    std::thread t2{ set_y };
    std::thread t3{ read_x_then_y };
    std::thread t4{ read_y_then_x };
    t1.join();
    t2.join();
    t3.join();
    t4.join();

    assert(ival != 0);
  }

  int main()
  {
    for (int i = 0; i < 10000; ++i)
      func();
  }
*/
