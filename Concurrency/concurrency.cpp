#include <iostream>

/*
                  ========================================
                  | Concurrency (eşzamanlılık / eşgüdüm) |
                  ========================================
*/

/*
  --------------------------------------------------------------------------
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

  --------------------------------------------------------------------------
  paralelism : 
    - simultaneously doing the different jobs 
    - birbirleriyle ilişkili olabilecek işlemlerin aynı zamanda yürütülmesi.
    - aynı anda birden fazla işlem yapılması.
    - need more than one core.
  
    - for job to done faster (işin daha hızlı yapılması için)
      i.e splitting a vector(1'000'000 elem) in 4 different threads.
      and sorting them in parallel. 

    - an application can be parallel but not concurrent.
      (1 task's subtasks can be divided into different threads)

  --------------------------------------------------------------------------
  - an application can both be concurrent and parallel.
    different tasks are done in different cores at the same time.

  - an application can be neither concurrent nor parallel.
    sequential execution of tasks.
  --------------------------------------------------------------------------
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
    // default initialized thread object does not have work load to execute.

    // work load(iş yükü) that thread will execute is a function.
    // 1. can be a global function
    // 2. can be a static member function of a class
    // 3. can be a non-static member function of a class
    // 4. can be an operator function of a functor class
    // 5. can be a closure type function obtained from a lambda expression
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

      thread t1{ foo, ivec };             // ivec will be copied
      thread t2{ foo, std::ref(ivec) };   // ivec objects itself will be sent
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
    // warning: parentheses were disambiguated as a function declaratio
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
      : m_thread( std::forward<Function>(f), std::forward<Args>(args)... )
    {}

    ~JThread(){
      if (joinable())
        join();
    }

    explicit JThread(std::thread t) noexcept : m_thread{ std::move(t) } {}

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
