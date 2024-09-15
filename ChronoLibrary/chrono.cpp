#include <iostream>

/*
              =========================================
              | Chrono Library (Compile Time Library) |
              =========================================
*/

/*
  namespace std{
    namespace chrono{
      // chrono is a nested namespace inside std namespace
    }
  }
*/

/*
  #include <chrono>
  #include <ratio>

  int main(){

    using namespace std;
    using namespace std::chrono;

    duration<int, ratio<1, 10>>;

    // if using directives are not used, 
    // then the following syntax is used
    std::chrono::duration<int, std::ratio<1, 10>>;
    std::chrono::duration<int, std::deci>;
    // Those 2 lines are equivalent
  }
*/

/*
  There are 3 main types 
    1. duration types 
    an integral or floating point type has been wrapped and 
    made strong type. (zero cost abstraction)

    2. time points
      - In order to talk about a time point, we need to have an epoch.
      (bir time pointten bahsedebilmemiz için, epochumuz olması gerekiyor.)

      - time point is represented by the time elapsed in an epoch.
      (time point bir epochtan geçen süre ile temsil ediliyor.)  

      - Each clock has an epoch.
      (Her clock'un bir epoch'u var.)

      - a clock can be associated with duration, 
      but duration does not have to be associated with a clock
      (bir clock, duration ile ilişkilendirilebilir ama duration 
      bir clock'a ilişkin olmak zorunda değil)

    <--- check time_points.cpp --->
    time_point - time_point = duration
    time_point + duration = time_point
    time_point - duration = time_point
    
    3. clock types
*/

/*
                            ------------
                            | duration |
                            ------------
*/

/*
  #include <chrono>
  #include <ratio>

  template <typename Rep, typename Period>
  struct Duration{
    Rep rep;
  };

  int main(){
    Duration<int, std::ratio<1>>;

    std::chrono::duration<int, std::ratio<1, 10>> d1;
    // her bir tik saniyenin 1/10'u kadar
    // kaç adet tik olduğu int tipinde tutuluyor
    // every tick is 1/10 of a second
    // how many ticks are there is stored in an int

    std::chrono::duration<double, std::ratio<1>> x(34.78);
    // duration saniyelerden(1) oluşuyor 
    // her bir saniye double tipinde tutuluyor
    // duration is made up of seconds(1)
    // each second is stored in a double
    // x is 34.78 seconds

    std::chrono::duration<double, std::ratio<1, 2>> y(34.78);

    // y is 34.78 * 1/2 = 17.39 seconds
    // y -> 34.78 tane 1/2 saniye
  }
*/

/*
  #include <ratio>
  #include <chrono>

  int main(){
    using namespace std;
    using namespace std::chrono;

    duration<int, ratio<10>> x(87);
    // x is 87 * 10 = 870 seconds

    duration<int, ratio<1, 10>> y(87);
    // y is 87 * 1/10 = 8.7 seconds

    duration<long long, ratio<1, 1000>> dx{465556};
    // this duration represent milliseconds
    // dx is 465556 * 1/1000 = 465.556 seconds

    duration<long long, milli> dy{465556};
    // dy and dx are the same

    duration<long long, nano>;
    // duration is made up of nanoseconds;
  }
*/

/*
  #include <chrono>
  #include <ratio>

  int main(){
    using namespace std;
    using namespace std::chrono;

    using halfsec = duration<double, ratio<1, 2>>;

    halfsec x{9823.123};
    // x is 9823.123 * 1/2 = 4911.5615 seconds

    using Day = duration<int, ratio<60 * 60 * 24>>;
    Day ndays{456}; // 456 days
  }
*/

/*
  // standart library provides type aliases 
  // for some template specializations

  #include <chrono>
  #include <ratio>

  int main(){
    using namespace std;
    using namespace std::chrono;

    seconds; 
    cout << typeid(seconds).name() << '\n';
    // duration<long long, ratio<1, 1>> in MSVC

    milliseconds;
    cout << typeid(milliseconds).name() << '\n';
    // duration<long long, ratio<1, 1000>> in MSVC

    microseconds;
    cout << typeid(microseconds).name() << '\n';
    // duration<long long, ratio<1, 1000000>> in MSVC

    nanoseconds;
    cout << typeid(nanoseconds).name() << '\n';
    // duration<long long, ratio<1, 1000000000>> in MSVC

    minutes;
    cout << typeid(minutes).name() << '\n';
    // duration<long long, ratio<60, 1>> in MSVC

    hours;
    cout << typeid(hours).name() << '\n';
    // duration<long long, ratio<3600, 1>> in MSVC
  }
*/

/*
  #include <chrono>
  #include <ratio>

  int main(){
    using namespace std;
    using namespace std::chrono;

    milliseconds ms{349123};
    // 349123 milliseconds

    // this duration types are not holding ratio values
    // ratio has been used in compile time
    // the value that duration stores(wraps) an integral or a 
    // floating point number
    // in this case -> 349123
  }

  // compiled with 
  // main:
  //   push rbp
  //   mov rbp, rsp
  //   mov QWORD PTR [rbp-8], 349123  : lon long int ms = 349123;
  //   mov eax, 0
  //   pop rbp
  //   ret
*/

/*
    #include <chrono>
    #include <ratio>

    int main(){
      using namespace std;
      using namespace std::chrono;

      milliseconds ms = 349123; // syntax error
      // conversion from 'int' to non-scalar type 'std::chrono::milliseconds'
      // it has an explicit constructor (no implicit conversion)

      milliseconds ms = 234ms; // C++14 added literal operators

      auto ms2 = 234ms;   // milliseconds ("ms" is the literal operator)
      auto ns = 234ns;    // nanoseconds  ("ns" is the literal operator)
      auto x = 1231234us; // microseconds ("us" is the literal operator)

      // because of those are applied in compile time
      // those variables can be contexpr
      constexpr auto mic = 123us;
    }
*/

/*
  struct Mystruct {
    int mx;
  };

  int main(){
    using namespace std;

    Mystruct ms;  // default initialization

    ms.mx;  // indeterminate(garbage) value 
    cout << ms.mx << '\n';  // undefined behavior(ub)


    Mystruct ms2{}; // value initialization
    cout << ms2.mx << '\n';   // output -> 0
  }
*/

/*
  #include <chrono>
  #include <ratio>

  template <typename T>
  struct Duration{
    T val;
  };

  int main(){
    using namespace std;
    using namespace std::chrono;

    milliseconds ms;  // default initialization

    cout << "ms = " << ms.count() << "ms\n";   // undefined behavior(ub)
    // before C++20, we had to use count() member function

    cout << "ms = " << ms << '\n';              // undefined behavior(ub)
    // C++20 added inserter functions for duration types

    milliseconds ms2{};  // value initialization

    cout << "ms2 = " << ms2.count() << "\n";      // output -> ms2 = 0
    cout << "ms2 = " << ms2 << '\n';              // output -> ms2 = 0ms
  }
*/

/*
  // different duration types can be aritmetically combined
  // results will be calculated in compile time

  #include <chrono>
  #include <ratio>

  int main(){
    using namespace std;
    using namespace std::chrono;

    constexpr auto val = 12h + 123min + 239s + 3127ms; 
    // "12h + 123min + 239s + 3127ms" expression is compile time constant
    // val's type will be milliseconds

    cout << val.count() << "\n";  // output -> 50822127 
    cout << val << "\n";          // output -> 50822127ms   (C++20)
  }
*/

/*
  #include <chrono>
  #include <ratio>

  using halfsec = std::chrono::duration<int, std::ratio<1, 2>>;
  using salise  = std::chrono::duration<int, std::ratio<1, 60>>;

  int main(){
    using namespace std;
    using namespace std::chrono;

    constexpr auto d = salise{ 2346 } + halfsec{ 9823 } + seconds{ 123 };
    cout << d.count() << '\n'; // output -> 304416
  }
*/

/*
  <--- check duration_arithmetic_operations.png --->
  durations does not need to be same type in binary operations
*/

/*
  #include <chrono>
  #include <ratio>

  int main(){
    using namespace std;
    using namespace std::chrono;

    auto sec = 1231s;
    sec += 61345ms; // syntax error
    // no match for 'operator+=' 
    // (operand types are 'std::chrono::duration<long long int>' and 
    // 'std::chrono::milliseconds' 
    // {aka 'std::chrono::duration<long long int, std::ratio<1, 1000> >'})

    // ------------------------------------------------
    // fine   (ince, hassas)
    // coarse (kaba)

    // milliseconds is finer than seconds
    // seconds is coarser than milliseconds

    // implicit conversion will be done 
    // if there was not any no value loss 
    // valid from (coarser to finer) 
    // ------------------------------------------------

    auto x = 4567ms;
    nanoseconds ns = x; // implicit conversion allowed
    // conversion from ms to ns (ms is coarser than ns)
    // no value loss will be happen
  }
*/


/*
  // if represtation type (duration's first template parameter) 
  // is floating point type, then implicit conversion is always allowed

  #include <chrono>
  #include <ratio>

  using dsec = std::chrono::duration<double, std::ratio<1>>;

  int main(){
    using namespace std;
    using namespace std::chrono;

    milliseconds ms{ 4558474 };

    dsec ds = ms; // implicit conversion allowed
    // normally seconds is coarser than milliseconds
    // but representation type is double

    cout << ds.count() << " seconds \n"; 
    // output -> 4558.47 seconds
  }
*/

/*
  // if we want to convert from finer to coarser
  // without caring about the data loss
  // conversion can not be done implicitly
  // but duration_cast can be used for explicit conversion

  #include <chrono>
  #include <ratio>

  int main(){
    using namespace std;
    using namespace std::chrono;

    auto x = 1238972882us;
    auto y = duration_cast<seconds>(x); // valid

    cout << "y = " << y << '\n'; // output -> y = 1238s   (C++20)
  }
*/

/*
  #include <chrono>
  #include <ratio>

  int main(){
    using namespace std;
    using namespace std::chrono;

    auto x = 1238'672882us;

    auto k = floor<seconds>(x); // valid (C++14)
    auto l = ceil<seconds>(x);  // valid (C++14)
    auto m = round<seconds>(x); // valid (C++14)

    cout << "k = " << k.count() << '\n'; // output -> k = 1238
    cout << "l = " << l.count() << '\n'; // output -> l = 1239
    cout << "m = " << m.count() << '\n'; // output -> m = 1239
  }
*/

/*
  // there is no conversion from duration types to integral types

  #include <chrono>
  #include <ratio>

  int main(){
    using namespace std;
    using namespace std::chrono;

    milliseconds ms{ 1234 };

    int ival = ms;  // syntax error
    // error: cannot convert 'std::chrono::milliseconds' 
    // to 'int' in initialization

    int ival2 = ms.count(); // valid
  }
*/

/*
  // convert to this format
  // 3 days 23 hours 23 minutes 23 seconds 23 milliseconds

  #include <chrono>
  #include <ratio>

  using Day = std::chrono::duration<int, std::ratio<60 * 60 * 24>>;
  // std::chrono::day added in C++20

  int main(){
    using namespace std;
    using namespace std::chrono;

    int n = 182736482;
    milliseconds ms{ n };

    Day d = duration_cast<Day>(ms); 
    cout << d << " ";
    hours h = duration_cast<hours>(ms % Day{ 1 });
    cout << h << " ";
    minutes m = duration_cast<minutes>(ms % hours{ 1 });
    cout << m << " ";
    seconds s = duration_cast<seconds>(ms % minutes{ 1 });
    cout << s << " ";
    milliseconds msx = duration_cast<milliseconds>(ms % seconds{ 1 });
    cout << msx << '\n';

    // output -> 2d 2h 45min 36s 482ms
  }
*/

/*
  #include <chrono>
  #include <ratio>

  int main(){
    using namespace std;
    using namespace std::chrono;

    milliseconds ms{ 28373 };
    ms += 1234s;
    ms += 12min;
    ms += 1h;
  }
*/

/*
  #include <chrono>
  #include <ratio>

  int main(){
    using namespace std;
    using namespace std::chrono;

    constexpr auto b1 = 456789ms > 457s;  // b1 = false
    constexpr auto b2 = 456789ms > 456s;  // b2 = true
  }
*/

/*
  // durations nested types

  #include <chrono>
  #include <ratio>

  int main(){
    using namespace std;
    using namespace std::chrono;

    // milliseconds::rep nested type
    cout << typeid(milliseconds::rep).name() << '\n'; 
    // output -> long long (__int64 in MSVC)

    // milliseconds::period nested type
    cout << typeid(milliseconds::period).name() << '\n';
    // output -> struct std::ratio<1, 1000>

    using halfsec = duration<double, ratio<1, 2>>;

    cout << typeid(halfsec::rep).name() << '\n';
    // output -> double
    cout << typeid(halfsec::period).name() << '\n';
    // output -> struct std::ratio<1, 2>
  }
*/

/*
  #include <chrono>
  #include <ratio>

  template <typename R, typename P>
  std::ostream& operator<<( std::ostream& os, 
                            const std::chrono::duration<R, P>& dur)
  {
    return os << dur.count() << " * " << "[" 
              << P::num << "/" << P::den << "]"; 
  }

  int main(){
    using namespace std;
    using namespace std::chrono;

    milliseconds ms{ 812783 };
    cout << ms << '\n'; // output -> 812783 * [1/1000]

    duration<int, ratio<1, 10>> x{ 577 };
    cout << x << '\n';  // output -> 577 * [1/10]
  }
*/

/*
                        ---------------
                        | time points |
                        ---------------                  
*/

/*
  system_clock (sistem saati)
  steady_clock (ayarlanmayan, süre ölçümü için kullanılıyor)
  high_resolution_clock (yüksek çözünürlüklü saat)
    typedef name of one of other 2 clocks
*/

/*
*/

// Lesson 70 - 02:07:20
