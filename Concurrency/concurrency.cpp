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

// 71_Concurrency_1 : 01:17:37






