#include <iostream>

/*
                ========================================
                | Ratio Library (Compile Time Library) |
                ========================================
*/

/*
  #include <ratio>

  // ratio class template implementation
  template <long long x, long long y>
  class Ratio{
    constexpr static auto num = x;
    constexpr static auto den = y;
  };
  // the largest signed int type has been used as "x" and "y" "intmax_t"
  // in the original ratio class template

  int main(){
    using namespace std;

    Ratio<45, 79> r1; // ratio<45, 79>
    Ratio<4, 16> r2;  // ratio<1, 4>

    // first template parameter is constexpr static data member "num"
    // second template parameter is constexpr static data member "den"

    ratio<3, 7>;        // (3/7)
    ratio<3, 7>::num;   // 3
    ratio<3, 7>::den;   // 7
  
    ratio<3, 21>;       // (1/7)
    ratio<3, 21>::num;  // 1
    ratio<3, 21>::den;  // 7

    ratio<5> r1;    // ratio<5, 1>
    ratio<5>::den;  // 1

    cout << typeid(ratio<3, 21>::type).name() << '\n';     
    // output -> struct std::ratio<1, 7> in MSVC
  }
*/

/*
  #include <ratio>

  // compile time meta functions :
  // ratio_add, ratio_subtract, ratio_multiply, ratio_divide,
  // ratio_less, ratio_less_equal, ratio_greater, ratio_greater_equal
  // ratio_equal, ratio_not_equal, 

  using one_third = std::ratio<1, 3>;
  using two_fifth = std::ratio<2, 5>;

  int main(){
    using namespace std;

    using type = ratio_add<ratio<3, 5>, ratio<4, 5>>::type;

    constexpr auto num = type::num; // 7
    constexpr auto den = type::den; // 5

    cout << typeid(ratio_add<one_third, two_fifth>::type).name() 
          << '\n';  // struct std::ratio<11, 15> in MSVC
    cout << typeid(ratio_subtract<one_third, two_fifth>::type).name() 
          << '\n';  // struct std::ratio<-1, 15> in MSVC
    cout << typeid(ratio_divide<one_third, two_fifth>::type).name() 
          << '\n';  // struct std::ratio<5, 6> in MSVC
    cout << typeid(ratio_multiply<one_third, two_fifth>::type).name() 
          << '\n';  // struct std::ratio<2, 15> in MSVC


    cout << ratio_less<ratio<13977, 57913>, ratio<13913, 57019>>::value 
          << '\n'; // 1
    cout << ratio_less_equal_v<ratio<13977, 57913>, ratio<13913, 57019>>
          << '\n'; // 1
  }
*/

/*
  #include <ratio>
  #include <iomanip>

  using Milli = std::ratio<1, 1000>;

  template <typename T>
  void print_ratio(const char* pname){
    std::cout << std::left;
    std::cout << std::setw(10) << pname << typeid(T).name() << '\n';
  }

  int main(){
    using namespace std;

    print_ratio<deci>("deci");
    print_ratio<centi>("centi");
    print_ratio<milli>("milli");
    print_ratio<micro>("micro");  
    print_ratio<nano>("nano");
    print_ratio<pico>("pico");

    // output ->
    //  deci      struct std::ratio<1,10>
    //  centi     struct std::ratio<1,100>
    //  milli     struct std::ratio<1,1000>
    //  micro     struct std::ratio<1,1000000>
    //  nano      struct std::ratio<1,1000000000>
    //  pico      struct std::ratio<1,1000000000000>

    print_ratio<deca>("deca");
    print_ratio<hecto>("hecto");
    print_ratio<kilo>("kilo");
    print_ratio<mega>("mega");
    print_ratio<giga>("giga");
    print_ratio<tera>("tera");

    // output ->
    //  deca      struct std::ratio<10,1>
    //  hecto     struct std::ratio<100,1>
    //  kilo      struct std::ratio<1000,1>
    //  mega      struct std::ratio<1000000,1>
    //  giga      struct std::ratio<1000000000,1>
    //  tera      struct std::ratio<1000000000000,1>

    ratio_multiply<kilo, milli>::num; // 1
    ratio_multiply<kilo, milli>::den; // 1
    //  (1000 * (1 /1000)) 
  }
*/