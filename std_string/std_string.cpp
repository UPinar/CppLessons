#include <iostream>

/*
                      =====================
                      | std::string class |
                      =====================
*/

/*
  - std::string class is a container
  - std::string class is a dynamic array
*/

/*
  template <class CharT,
            class Traits = std::char_traits<CharT>,
            class Allocator = std::allocator<CharT>> 
  class basic_string;
*/

/*
  #include <type_traits>  // std::is_same
  #include <string>

  int main()
  {
    using namespace std;
    cout << boolalpha;
    
    // ------------------------------------------------

    std::basic_string<char, 
                      std::char_traits<char>,
                      std::allocator<char>> str_1{ "hello world" };

    // ------------------------------------------------

    std::basic_string<char> str_2{ "hello galaxy" };

    // ------------------------------------------------

    using my_string = std::basic_string<char>;
    my_string str_3{ "hello universe" };

    // ------------------------------------------------

    std::string str_4{ "hello soul" };
    // `std::string` is a type alias  

    // ------------------------------------------------

    cout << is_same_v<decltype(str_1), decltype(str_1)> << '\n'; 
    // output -> true
    cout << is_same_v<decltype(str_1), decltype(str_3)> << '\n';
    // output -> true
    cout << is_same_v<decltype(str_1), decltype(str_4)> << '\n';
    // output -> true

    // str_1, str_2, str_3, str_4 are all same type

    // ------------------------------------------------
  }
*/

/*
  std::string class have 3 pointers and a buffer data members.

  1st pointer points to the first char in the string
  2nd pointer points to the last char in the string
  3rd pointer points to the end of the capacity.


                                ---------------------------------
                                | H | E | L | L | O |  |  |  |  |
                                ---------------------------------
                                ^                 ^           ^
                                |                 |           |
  -----------                   |                 |           |
  | pointer |--------------------                 |           |
  -----------                                     |           |
  | pointer |-------------------------------------            |
  -----------                                                 |
  | pointer |-------------------------------------------------
  -----------
  | buffer  |
  -----------
*/

/*
  #include <cstdlib>  // std::malloc, std::free
  #include <new>      // std::bad_alloc
  #include <string>

  void* operator new(std::size_t sz)
  {
    std::cout << "operator new called for the size of : " 
              << sz << '\n';

    if (sz == 0)
      ++sz;

    if (void* ptr = std::malloc(sz)){
      std::cout << "memory allocated at the address of : " 
                << ptr << '\n';
      return ptr;
    }

    throw std::bad_alloc{};
  }

  void operator delete(void* ptr)
  {
    std::cout << "operator delete called for the address of : " 
              << ptr << '\n';

    std::free(ptr);
  }

  // operator delete overload for gcc compiler
  void operator delete(void* ptr, size_t sz)
  {
    std::cout << "operator delete called for the address of : " 
              << ptr << '\n';

    std::free(ptr);
  }

  int main()
  {
    // ------------------------------------------------

    std::cout << "[0] main started\n";

    std::string str_1{ "hello world" };
    // because of std::string class have a buffer member variable
    // it can hold small strings without heap allocation.
    // SSO (Small String Optimization)

    // std::string object itself is created in stack memory
    // char's(resource) are created in stack memory (SSO)

    // ------------------------------------------------

    std::cout << "[1] main continues\n";

    std::string str_2{ "hello world we are live from Istanbul" };
    // output -> 
    //  operator new called for the size of : 38
    //  memory allocated at the address of : 0x1f7691c3ba0

    // std::string object itself is created in stack memory
    // char's(resource) are created in heap memory

    // ------------------------------------------------

    std::cout << "[2] main continues\n";

    auto ps = new std::string(100, 'A');
    // output ->
    //  operator new called for the size of : 32
    //  memory allocated at the address of : 0x1f7691c3c00
    //  operator new called for the size of : 101
    //  memory allocated at the address of : 0x1f7691bf150

    // std::string object itself is created in heap memory
    // char's(resource) are created in heap memory

    delete ps;
    // output ->
    //  operator delete called for the address of : 0x1f7691bf150
    //  operator delete called for the address of : 0x1f7691c3c00

    // ------------------------------------------------

    std::cout << "[3] before main ends\n";

    // output -> 
    //  operator delete called for the address of : 0x1f7691c3ba0

    // ------------------------------------------------
  }
*/

/*
  small string(buffer) optimization (SSO - SBO) :
    if string is small enough, it can be stored 
    inside the buffer data member of the std::string class.
*/

/*
  #include <string>

  int main()
  {
    std::string str;

    str.reserve(100'000);
    // reserving memory for no reallacation

    for (size_t i = 0; i < 100'000; ++i)
      str.push_back('A');
  }
*/

/*
  std::string str;

  str.func(const char* p) 
  // Null-Terminated Byte String(NTBS)  - CString param

  str.func(const char* p, string::size_type)
  // data param

  str.func(const char* ps, const char* pe)
  // range param

  str.func(const string&)
  // std::string param (const lvalue reference)

  str.func(string&&)
  // std::string param  (rvalue reference)

  str.func(const string&, string::size_type)
  // sub-string param

  str.func(const string&, string::size_type, string::size_type)	
  // sub-string param

  str.func(std::string::size_type, char)
  // fill param

  str.func(char)
  // char param

  str.func(std::initializer_list<char>)
  // initializer_list param
*/

/*
  // std::string(const char* p) 
  // Null-Terminated Byte String(NTBS) - CString param

  int main()
  {
    char c_arr[20];

    c_arr[0] = 'h';
    c_arr[1] = 'e';
    c_arr[2] = 'l';
    c_arr[3] = 'l';
    c_arr[4] = 'o';

    std::cout << c_arr; // undefined behaviour(UB)
    // c_arr is not null-terminated byte string(NTBS)

    // ------------------------------------------------

    std::string str_1{ c_arr };
    // array to pointer conversion (char[20] -> char*)

    std::cout <<str_1 << '\n'; // output -> hello

    std::string str_2{ "hello world" };
    // string literal is static storage duration NTBS 
    // and its data type is (const char[])
    // array to pointer conversion (const char[12] -> const char*)

    // ------------------------------------------------
  }
*/

/*
  string::size_type
  size_t
    -> index type
    -> field parameter type
    -> length and capacity type
*/

/*
  #include <string>

  int main()
  {
    std::string str;

    // ------------------------------------------------

    std::cout << "str.size() = " << str.size() << '\n';		
    // output -> str.size() = 0
    std::cout << "str.length() = " << str.length() << '\n';
    // output -> str.length() = 0
    std::cout << "str.capacity() = " << str.capacity() << '\n';
    // output -> str.capacity() = 15

    // ------------------------------------------------

    auto len_1 = str.size();
    std::string::size_type len_2 = str.size();
    size_t len_3 = str.size();
    // Those 3 lines are equivalent.

    // ------------------------------------------------

    if (str.size() == 0) {}
    if (str.empty()) {}
    // Those conditins are equivalent.

    // ------------------------------------------------
  }
*/

/*
  #include <string>

  int main()
  {
    std::string str{ "hello world we are live from Istanbul" };
    str.reserve(500);
    
    auto str_capacity = str.capacity();
    int realloc_count{};

    for (int i = 0; i < 1'000; ++i)
    {
      str.push_back('.');

      if (str.capacity() > str_capacity)
      {
        std::cout << ++realloc_count << " ";
        std::cout << "size = " << str.size() << " ";
        std::cout << "capacity = " << str.capacity() << '\n';

        str_capacity = str.capacity();
      }
    }
  }

  // without str.reserve(500) 
  // output ->
  //  1 size = 38 capacity = 74
  //  2 size = 75 capacity = 148
  //  3 size = 149 capacity = 296
  //  4 size = 297 capacity = 592
  //  5 size = 593 capacity = 1184

  // with str.reserve(500);
  // output ->
  //  1 size = 501 capacity = 1000
  //  2 size = 1001 capacity = 2000
*/

/*
  #include <string>

  int main()
  {
    std::string str{ "hello world" };
    std::cout << str << '\n'; // output -> hello world

    // ------------------------------------------------

    str.assign(300'000, 'a');
    // fill the string with 300'000 'a' characters

    //std::cout << str << '\n';
    // output -> aaaaaaaaaaaaaaa...aaaaa

    std::cout << "str.size() = " << str.size() << '\n';
    // output -> str.size() = 300000
    std::cout << "str.capacity() = " << str.capacity() << '\n';
    // output -> str.capacity() = 300000

    // ------------------------------------------------

    str.erase(50);
    // erase every char after the 50th char.

    std::cout << "str.size() = " << str.size() << '\n';
    // output -> str.size() = 50
    std::cout << "str.capacity() = " << str.capacity() << '\n';
    // output -> str.capacity() = 300000

    // ------------------------------------------------

    str.shrink_to_fit();
    // shrink the capacity to the size

    std::cout << "str.size() = " << str.size() << '\n';
    // output -> str.size() = 50
    std::cout << "str.capacity() = " << str.capacity() << '\n';
    // output -> str.capacity() = 50

    // ------------------------------------------------
  }
*/

/*
  #include <string>

  int main()
  {
    char c_str[] = "Istanbul Ankara Izmir Bursa";
    std::string str_2;

    // ------------------------------------------------

    str_2.assign(c_str + 9, 6); 
    // str.func(const char* p, string::size_type)
    // data parameter assign function

    std::cout << "str_2 = " << str_2 << '\n'; 
    // output -> str_2 = Ankara

    // ------------------------------------------------

    str_2.assign(c_str + 16, c_str + 22); 
    // str.func(const char* ps, const char* pe)
    // range parameter assign function

    std::cout << "str_2 = " << str_2 << '\n'; 
    // output -> str_2 = Izmir

    // ------------------------------------------------
  }
*/

/*
  #include <string>

  int main()
  {
    std::string str_1{ "abcdefghijklmnoprstuvyz" };
    std::string str_2;

    // ------------------------------------------------

    str_2.assign(str_1, 5);
    // str.func(const string&, string::size_type)	
    // sub-string parameter assign function

    std::cout << "str_2 = " << str_2 << '\n'; 
    // output -> str_2 = fghijklmnoprstuvyz

    // ------------------------------------------------
    
    str_2.assign(str_1, 3, 5);
    // str.func(const string&, string::size_type, string::size_type)	
    // sub-string parameter assign function

    std::cout << "str_2 = " << str_2 << '\n'; 
    // output -> str_2 = defgh

    // ------------------------------------------------
  }
*/

/*
  #include <string>

  int main()
  {
    std::string str{ "hello world" };

    std::cout << "str = |" << str << "|\n"; 
    // output -> str = |hello world|

    // ------------------------------------------------

    str += '!'; 
    // str.func(char) -> str.operator+=('!')
    // char parameter operator+= function

    std::cout << "str = |" << str << "|\n";
    // output -> str = |hello world!| 

    // ------------------------------------------------
  }
*/

/*
  #include <string>

  int main()
  {
    std::string str{ "hello" };

    std::cout << "str = |" << str << "|\n";
    // output -> str = |hello|

    // ------------------------------------------------

    str.assign({'w','o','r','l','d'});	
    // initializer_list parameter assign function

    std::cout << "str = |" << str << "|\n";
    // output -> str = |world|

    // ------------------------------------------------
  }
*/

/*
            ------------------------------------
            | std::string class's constructors |
            ------------------------------------
*/

/*
  #include <string>

  int main()
  {
    // ------------------------------------------------

    std::string str_1;    // default constructor
    std::string str_2{};  // default constructor
    std::string str_3();  // function declaration (most vexing parse)

    // ------------------------------------------------

    // std::string class'es CString parameter construtor 
    // is not explicit, it is converting constructor

    std::string str_4{ "hello world" };   
    // converting CString parameter constructor

    std::string str_6("hello world");     
    // converting CString parameter constructor

    std::string str_7 = "hello world";    
    // converting CString parameter constructor
    // if it was explicit ctor this expression would throw error.

    // ------------------------------------------------

    const char* p_str = "hello world we are live from Istanbul";

    std::string str_8{ p_str + 6, 5 }; 
    // data constructor
    // string(const char* p, string::size_type)

    // ------------------------------------------------
  }
*/

/*
  #include <string>

  int main()
  {
    std::string str;  // default initialization (empty string)

    // ------------------------------------------------

    auto is_empty = str.empty();  
    // will return bool 

    std::cout << "is_empty = " << is_empty << '\n';
    // output -> is_empty = 1

    // ------------------------------------------------

    auto size = str.size();       
    // will return string::size_type

    std::cout << "size = " << size << '\n';
    // output -> size = 0

    // ------------------------------------------------
  }
*/

/*
  #include <vector>
  #include <string>

  int main()
  {
    // ------------------------------------------------

    const char* p_str = "hello world";

    std::string str_1{ p_str, p_str + 5 };
    // string(const char* ps, const char* pe)
    // range constructor

    std::cout << "str_1 = " << str_1 << '\n'; 
    // output -> str_1 = hello

    // ------------------------------------------------

    std::vector<char> cvec{ 'w', 'o', 'r', 'l', 'd' };

    std::string str_2{ cvec.begin(), cvec.end() }; 
    // range constructor

    std::cout << "str_2 = " << str_2 << '\n';
    // output -> str_2 = world

    // ------------------------------------------------
  }
*/

/*
  #include <string>
  #include <utility>  // std::move

  int main()
  {
    // ------------------------------------------------

    std::string str_1(20, 'A'); 
    // string(size_type count, char ch) -> fill constructor

    std::cout << "str_1.size() = " << str_1.size() << '\n';
    // output -> str_1.size() = 20

    // ------------------------------------------------

    std::string str_2 = { std::move(str_1) };
    // string(string&& str) -> move constructor
    // str_1 becomes moved-from state

    std::cout << "str_1 = |" << str_1 << "|\n"; 
    // output -> str_1 = ||

    std::cout << "str_2 = |" << str_2 << "|\n";
    // output -> str_2 = |AAAAAAAAAAAAAAAAAAAA|

    std::cout << "str_1.size() = " << str_1.size() << '\n';	
    // output -> str.size() = 0

    std::cout << "str_2.size() = " << str_2.size() << '\n';	
    // output -> str.size() = 20

    std::cout << "str_1.capacity() = " << str_1.capacity() << '\n';
    // output -> str_1.capacity() = 15 (buffer inside string)

    std::cout << "str_2.capacity() = " << str_2.capacity() << '\n';
    // output -> str_2.capacity() = 20

    // ------------------------------------------------
  }
*/

/*
  // examples of constructing string object with 1 char

  #include <string>

  int main()
  {
    using namespace std;

    // ------------------------------------------------

    string str_1{ 'A' };
    // string(initializer_list<char>) ctor

    // ------------------------------------------------

    string str_2('A');  // syntax error
    // error: no matching function for call to 
    // 'std::__cxx11::basic_string<char>::basic_string(char)'
    // string class does not have char parameter ctor

    // ------------------------------------------------

    string str_3 = "A"; 
    // CString(string literal) parameter ctor 

    // ------------------------------------------------

    string str_4(1, 'A'); 
    // string(size_type count, char ch) ctor -> fill ctor

    // ------------------------------------------------
  }
*/

/*
  #include <string>

  int main()
  {
    using namespace std;

    string str(20, '\0'); 
    // fill constructor -> string with 20 null('\0') characters

    std::cout << "str.length() = " << str.length() << '\n';
    // output -> str.length() = 20

    // the necessity of '\0' (null character) only 
    // at the end of the string(stream) 
    // is for Cstring(const char*) objects, 
    // not for std::string objects.
  }
*/

/*
  <---- check not_related/std::initializer_list class template ---->
*/

/*
  #include <string>

  int main()
  {
    // ------------------------------------------------

    std::string str_1(66, 'A'); 
    // string(size_type count, char ch) -> fill constructor

    std::cout << "str_1 = " << str_1 << '\n';
    // output -> str_1 = AAAAAAAAAAAA...AAAAAAAAAAAA

    std::cout << "str_1.size() = " << str_1.size() << '\n'; 
    // output -> s1.size() = 52

    // ------------------------------------------------

    std::string str_2{ 66, 'A' };
    // string(std::initializer_list<char>) -> initializer_list ctor

    std::cout << "str_2 = " << str_2 << '\n';
    // output -> str_2 = BA

    std::cout << "str_2.size() = " << str_2.size() << '\n'; 
    // output -> s2.size() = 2
    // initializer_list<char> implicit (int ==> char) conversion

    // ------------------------------------------------
  }
*/

/*
  #include <string>

  int main()
  {
    // ------------------------------------------------

    char p_str[] = "hello";
    std::string str_1(p_str, 20); // undefined behavior(UB)

    std::string str_2(p_str, p_str + 20); // undefined behavior(UB)

    // ------------------------------------------------

    std::string str_3{ "helloworld" };

    std::string str_4(str_3, 5);      // substring ctor
    std::cout << str_4 << '\n';       // output -> world

    std::string str_5(str_3, 2, 3);   // substring ctor
    std::cout << str_5 << '\n';       // output -> llo

    std::string str_6(str_3, 5, 65);   // substring ctor
    std::cout << str_6 << '\n';   // output -> World
    // no UB in substring ctor

    // ------------------------------------------------
  }
*/

/*
        --------------------------------------------------
        | constexpr static data member std::string::npos |
        --------------------------------------------------
*/

/*
  #include <string>

  int main()
  {
    std::string str;
    std::cout << str.npos << '\n';
    // output -> 18446744073709551615

    std::cout << std::string::npos << '\n';
    // output -> 18446744073709551615


    // search functions in std::string classes interface 
    // returns an index if it finds the value its looking for
    // returns std::string::npos if it can not find it
    // std::string::npos is the max value of std::string::size_type
  }
*/

/*
  #include <string>

  int main()
  {
    std::string str{ "hello world" };

    // ------------------------------------------------

    size_t idx = str.find('r');
    std::string::size_type idx2 = str.find('r');
    auto idx3 = str.find('r');
    // Those 3 lines are equivalent.

    if (idx != std::string::npos)
    {
      std::cout << str[idx];
      std::cout << " found, idx = " << idx << '\n';
    }
    else
      std::cout << "can not found\n";
    
    // output -> r found, idx = 8

    // ------------------------------------------------

    // using if with initializer to prevent scope leakage

    if (auto idx = str.find('d'); idx != std::string::npos)
    {
      std::cout << str[idx];
      std::cout << " found, idx = " << idx << '\n';
    }
    else
      std::cout << "can not found\n";

    // output -> d found, idx = 10

    // ------------------------------------------------
  }
*/

/*
  #include <string>

  int main()
  {
    std::string str{ "helloworld" };

    // ------------------------------------------------

    std::string str_1 = str.substr(1, 4);
    std::cout << str_1 << '\n';  
    // output -> ello

    // ------------------------------------------------

    auto str_2 = str.substr(1, std::string::npos);
    std::cout << str_2 << '\n'; 
    // output -> elloworld

    // ------------------------------------------------

    std::string str_3 = str.substr(5);
    std::cout << str_3 << '\n';
    // output -> world
    // substr(const size_type _Off = 0, const size_type _Count = npos)
    // 2nd parameter's default argument is std::string::npos

    // ------------------------------------------------

    auto str_4 = str.substr();
    std::cout << str_4 << '\n';
    // output -> helloworld
    // substr(const size_type _Off = 0, const size_type _Count = npos)
    // 1st parameter's default argument is 0
    // 2nd parameter's default argument is std::string::npos

    // ------------------------------------------------

    std::string str_5 = str.substr(0 , std::string::npos);
    std::cout << str_5 << '\n';
    // output -> helloworld

    // ------------------------------------------------
  }
*/

/*
  #include <string>

  int main()
  {
    std::string str{ "hello world" };

    std::string str_6(str, 3);                    // substring ctor
    std::string str_7(str, 3, std::string::npos); // substring ctor  
    // Those 2 lines are equivalent.

    std::cout << str_6 << '\n'; // output -> lo world
    std::cout << str_7 << '\n'; // output -> lo world
  }
*/

/*
  #include <string>
  #include <cstdio> // std::putchar

  int main()
  {
    std::string str{ "hello world" };

    // --------------------------------------------

    str[0] = '!';
    str.operator[](0) = '!';
    // These 2 lines are equivalent.

    std::cout << "str = " << str << '\n'; 
    // output -> str = !ello world

    // --------------------------------------------

    str.at(1) = '3';

    std::cout << "str = " << str << '\n';
    // output -> str = !3llo world

    // --------------------------------------------

    for (size_t i{}; i < str.size(); ++i)
      std::cout << str[i] << ' '; 
    // output -> ! 3 l l o   W o r l d
    std::putchar('\n');

    // --------------------------------------------

    // reaching non-valid index with '[]' subscript operator
    // is undefined behaviour(UB), will not throw exception

    try {
      auto ch = str[250]; // undefined behaviour(UB)
    }
    catch (const std::exception& ex)
    {
      std::cout << "exception caught: " << ex.what() << '\n';
    }

    // --------------------------------------------

    // reaching non-valid index with 'at' member function
    // of std::string class will throw exception.

    try {
      auto c = str.at(250);
    }
    catch (std::exception& ex)
    {
      std::cout << "exception caught: " << ex.what() << '\n';
    }
    // output -> 
    //  exception caught: basic_string::at: __n 
    //  (which is 250) >= this->size() (which is 11)

    // --------------------------------------------
  }
*/

/*
  #include <string>

  int main()
  {
    std::string str{ "hello world" };

    // --------------------------------------------

    str.front() = 'H';
    str[0] = 'H';
    // Those 2 lines are equivalent.

    std::cout << "str = " << str << '\n';
    // output -> str = Hello world

    // --------------------------------------------

    str.back() = 'K';
    str[str.size() - 1] = 'K';
    // Those 2 lines are equivalent.

    std::cout << "str = " << str << '\n'; 
    // output -> str = Hello worlK

    // --------------------------------------------
  }
*/

/*
  #include <initializer_list>

  int main()
  {
    std::initializer_list<int> init_list{ 1, 2, 3, 4, 5 };

    auto init_list_2 = init_list;
    // copying initializer_list<int> object is 
    // copying 2 pointer data members.

    std::cout << &*init_list.begin() << '\n';
    // output -> 0x7ff644ac5090

    std::cout << &*init_list_2.begin() << '\n';
    // output -> 0x7ff644ac5090
  }
*/

/*
  #include <string>

  void foo(std::string str)
  {
    std::cout << '|' << str << "|\n";
  }

  std::string bar()
  {
    return "istanbul";
    // implicit conversion from CString to std::string
    // (const char* ===> std::string)
  }

  void func(const char* p) {}
  // func's parameter variable's type is CString(const char*)


  int main()
  {
    // ------------------------------------------------

    foo("hello world");
    // output -> |hello world|
    // implicit conversion from CString to std::string
    // (const char* ===> std::string)

    // ------------------------------------------------

    auto str_1 = bar();
    // implicit conversion from CString to std::string
    // (const char* ===> std::string)

    // ------------------------------------------------

    std::string str_2{ "around the world" };

    //puts(str_2);  // sythax error
    // error: cannot convert 'std::string' 
    // {aka 'std::__cxx11::basic_string<char>'} to 'const char*'
    // conversion from std::string to CString is NOT VALID

    // ------------------------------------------------

    func(str_2.c_str());  // VALID
    func(str_2.data());   // VALID

    // c_str() and data() member functions of std::string class
    // are returning CString(const char*) type.
    // (std::string ===> const char*)

    // ------------------------------------------------
  }
*/

/*
  #include <type_traits>  // std::is_same
  #include <string>

  int main()
  {
    std::string str{ "we are live from istanbul" };

    const char* p_const_str1 = str.c_str();
    char* p_str2 = str.data();

    // c_str() member function returns const char* type
    constexpr bool b1 = std::is_same_v< decltype(p_const_str1), 
                                        const char*>;
    // b1 -> true

    // data() member function returns char* type
    constexpr bool b2 = std::is_same_v< decltype(p_str2),
                                        char*>;
    // b2 -> true
  }
*/

/*
  int main()
  {
    std::string str{ "universe is big" };
    auto p_str = str.c_str();
    puts(p_str);  // output -> universe

    str += " and reallocation happens all the time.";
    puts(p_str);  // undefined behaviour(UB)

    // c_str() and data() member functions of std::string class
    // are returning a Null Terminated Byte Stream(NTBS) address 
    // which string object's characters are stored in heap memory.

    // when string object's content is changed,
    // reallocation might happen because std::string object itself
    // is basically a dynamic array of char's 
    // which are stored in heap contigiously.
    // so if reallocation happens, the address of the NTBS will change
    // but the pointer that is returned by c_str() and data() functions
    // will still point the old address which is now dangling.
  }
*/

/*
  #include <string>

  int main()
  {
    std::string str{ "hello world" };

    std::cout << (void*)&str[0] << '\n';
    std::cout << (void*)str.data() << '\n';
    std::cout << (void*)&*str.begin() << '\n';

    // output -> 0x9525bffae0
    // output -> 0x9525bffae0
    // output -> 0x9525bffae0
  }
*/

/*
  some member functions have 2 different interfaces (erase, insert, ...)
    -> index interface
    -> iterator interface (STL containers)
*/

/*
  int main()
  {
    using namespace std;

    string str1{ "0123456789" };
    string str2 = str1;
    string str3 = str1;

    // ------------------------------------------------

    str1.erase(2);    // index interface
    // erasing every char after the 2nd index

    std::cout << str1 << '\n'; 
    // output -> 01

    // ------------------------------------------------

    str2.erase(2, 3); // index interface
    // erasing 3 char after the 2nd index

    std::cout << str2 << '\n';
    // output -> 0156789

    // ------------------------------------------------

    str3.erase(str3.begin() + 2);   // iterator interface
    // erasing the element in the index that iterator is pointing to

    // std.begin() is an iterator to the 0th index
    // so str.begin() + 2 is an iterator to the 2nd index

    std::cout << str3 << '\n';
    // output -> 013456789

    // ------------------------------------------------
  }
*/

/*
  #include <string>
  #include <utility>  // std::move

  int main()
  {
    using namespace std;

    // ------------------------------------------------

    string str1{ "hello world" };
    string str2{ "hello galaxy" };
    string str3{ "hello universe" };

    str1 = str2;            // copy assignment
    std::cout << "str1 = " << str1 << '\n';
    // output -> str1 = hello galaxy

    str1 = std::move(str3); // move assignment
    std::cout << "str1 = " << str1 << '\n';
    // output -> str1 = hello universe

    // ------------------------------------------------

    string str4 = { "istanbul ankara izmir" };

    str4 = "kadikoy, besiktas, uskudar";
    // CString parameter copy assignment

    std::cout << "str4 = " << str4 << '\n';
    // output -> str3 = kadikoy, besiktas, uskudar

    // ------------------------------------------------

    char c_arr[] = "we are live from Istanbul";

    str4 = c_arr; 
    // CString parameter copy assignment

    std::cout << "str4 = " << str4 << '\n';
    // output -> str4 = we are live from Istanbul

    // ------------------------------------------------

    str4 = 'H'; 
    // char parameter copy assignment

    std::cout << "str4 = " << str4 << '\n';
    // output -> str4 = H

    // ------------------------------------------------

    str4 = { 'B','J','K' };
    // initializer_list parameter copy assignment
    
    std::cout << "str4 = " << str4 << '\n';
    // output -> str4 = BJK

    // ------------------------------------------------
  }
*/

/*
  #include <string>

  int main()
  {
    std::string str{ "hello world" };

    // ------------------------------------------------

    str.assign(12, 'x');  // fill assign
    std::cout << "str = " << str << '\n';
    // output -> str = xxxxxxxxxxxx

    // ------------------------------------------------

    std::string str2{ "jerzy_kosinski" };

    str.assign(str2, 6);
    std::cout << "str = " << str << '\n';
    // output -> str = kosinski

    // ------------------------------------------------

    str.assign(str2, 6, 5);
    std::cout << "str = " << str << '\n';
    // output -> str = kosin

    // ------------------------------------------------

    char c_arr[] = "andrew_niccol";

    str.assign(c_arr + 7, 5);
    std::cout << "str = " << str << '\n';
    // output -> str = nicco

    // ------------------------------------------------

    str.assign(c_arr, c_arr + 3);   // range assign
    std::cout << "str = " << str << '\n';
    // output -> str = and

    // ------------------------------------------------

    str.assign({ 'i', 's', 't', 'a', 'n', 'b', 'u', 'l' });
    // initializer_list assign
    std::cout << "str = " << str << '\n';
    // output -> str = istanbul

    // ------------------------------------------------
  }
*/

/*
  int main()
  {
    std::string str{ "hello" };

    // ------------------------------------------------

    std::cout << "str.size() = " << str.size() << '\n'; 
    // output -> str.size() = 5

    str.resize(10); 
    // resize member function's 2nd argument has a default argument 
    // which is '\0', so it will fill the string with null characters.

    std::cout << "str.size() = " << str.size() << '\n';
    // output -> str.size() = 10

    // ------------------------------------------------

    for (size_t i = 0; i < str.size(); ++i)
      std::cout << "str[" << i << "] = " << (int)str[i] << '\n';
    // output -> 
    //  str[0] = 104
    //  str[1] = 101
    //  str[2] = 108
    //  str[3] = 108
    //  str[4] = 111
    //  str[5] = 0
    //  str[6] = 0
    //  str[7] = 0
    //  str[8] = 0
    //  str[9] = 0

    // ------------------------------------------------

    str = { "hello" };
    std::cout << "str.size() = " << str.size() << '\n'; 
    // output -> str.size() = 5

    str.resize(10, '_');
    std::cout << "str.size() = " << str.size() << '\n'; 
    // output -> str.size() = 10

    std::cout << "str = " << str << '\n';
    // output -> str = hello_____

    // ------------------------------------------------
  }
*/

/*
  int main()
  {
    using namespace std;

    string str{ "hello" };

    // ------------------------------------------------

    str += 'Z';
    // operator +=(char) overload

    std::cout << "str = " << str << '\n'; 
    // output -> str = helloZ

    // ------------------------------------------------

    str += "ero";
    // operator +=(const char*) overload

    std::cout << "str = " << str << '\n'; 
    // output -> str = helloZero

    // ------------------------------------------------

    string str_2{ "Hero" };
    str += str_2;
    // operator +=(const string&) overload

    std::cout << "str = " << str << '\n'; 
    // output -> str = helloZeroHero

    // ------------------------------------------------

    str += {'s', 't', 'o', 'n', 'e'};
    // operator +=(initializer_list<char>) overload

    std::cout << "str = " << str << '\n'; 
    // output -> str = helloZeroHerostone

    // ------------------------------------------------
  }
*/

/*
  #include <string>

  int main()
  {
    std::string str;

    for (char ch{'A'}; ch <= 'Z'; ++ch)
      str.push_back(ch);

    std::cout << "str = " << str << '\n'; 
    // output -> str -> ABCDEFGHIJKLMNOPQRSTUVWXYZ
  }
*/

/*
  #include <string>

  int main()
  {
    // ------------------------------------------------

    std::string str{ "hello" };
    str.append(3, '_');
    std::cout << "str = " << str << '\n'; 
    // output -> str = hello___

    // ------------------------------------------------

    char c_arr[] = "12345";
    str.append(c_arr, 3);
    std::cout << "str = " << str << '\n'; 
    // output -> str = hello___123

    // ------------------------------------------------

    std::string str_2{ "ISTANBUL" };
    str.append(str_2, 3, 4);
    std::cout << "str = " << str << '\n'; 
    // output -> str = hello___123ANBU

    // ------------------------------------------------
  }
*/

/*
  #include <string>

  int main()
  {
    std::string str{ "0123456789" };

    // insert member function -> iterator interface
    // iterator interace functions wants,
    // an address as a 1st parameter  (where to insert)
    // and a value as a 2nd parameter (what to insert)

    // ------------------------------------------------

    str.insert(str.begin(), 'A');
    std::cout << "str = " << str << '\n'; 
    // output -> str = A0123456789

    // ------------------------------------------------

    str.insert(str.begin() + 3, 'B');
    std::cout << "str = " << str << '\n'; 
    // output -> str = A01B23456789

    // ------------------------------------------------

    str = { "0123456789" };
    char c_arr[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    str.insert(str.begin(), c_arr, c_arr + 5);
    std::cout << "str = " << str << '\n'; 
    // output -> str = ABCDE0123456789

    // ------------------------------------------------

    str = { "0123456789" };
    str.insert(str.begin() + 3, c_arr + 5, c_arr + 9);
    std::cout << "str = " << str << '\n'; 
    // output -> str = 012FGHI3456789

    // ------------------------------------------------

    str = { "0123456789" };
    str.insert(str.begin() + 5, { 'Z','E','R','O' });
    std::cout << "str = " << str << '\n'; 
    // output -> str = 01234ZERO56789

    // ------------------------------------------------

    // insert member function -> index interface
    // add characters to a known range

    str = { "0123456789" };
    str.insert(5, 10, '_');
    std::cout << "str = " << str << '\n';
    // output -> str = 01234________56789

    // ------------------------------------------------
  }
*/

/*
  #include <string>

  int main()
  {
    using namespace std;

    // erase member function -> iterator interface

    // ------------------------------------------------

    string str{ "123456789" };
    str.erase(str.begin());
    std::cout << "str = " << str << '\n';
    // output -> str = 23456789

    // ------------------------------------------------

    str = { "123456789" };
    str.erase(str.begin() + 2);
    std::cout << "str = " << str << '\n';
    // output -> str = 12456789

    // ------------------------------------------------

    str = { "123456789" };
    str.erase(str.end() - 1);
    std::cout << "str = " << str << '\n';
    // output -> str = 12345678

    // ------------------------------------------------

    str = { "123456789" };
    str.erase(str.begin() + 1, str.end() - 1);  // range
    std::cout << "str = " << str << '\n';
    // output -> str = 19

    // ------------------------------------------------
  }
*/

/*
  #include <string>

  int main()
  {
    std::string str{ "HELLOWORLD" };

    while (!str.empty()){
      std::cout << str << '\n';
      str.erase(str.begin()); // iterator interface
    }
    // output ->
    //  HELLOWORLD
    //  ELLOWORLD
    //  LLOWORLD
    //  LOWORLD
    //  OWORLD
    //  WORLD
    //  ORLD
    //  RLD
    //  LD
    //  D
  }
*/

/*
  #include <string>

  int main()
  {
    std::string str{ "HELLOWORLD" };


    while (!str.empty()) {
      std::cout << str << '\n';
      str.erase(0, 1); // index interface
    }

    // HELLOWORLD
    // ELLOWORLD
    // LLOWORLD
    // LOWORLD
    // OWORLD
    // WORLD
    // ORLD
    // RLD
    // LD
    // D
  }
*/

/*
  #include <string>

  int main()
  {
    using namespace std;

    std::string str{ "HELLOWORLD" };

    while (!str.empty()) {
      std::cout << str << '\n';
      str.pop_back();
    }

    // output -> 
    //  HELLOWORLD
    //  HELLOWORL
    //  HELLOWOR
    //  HELLOWO
    //  HELLOW
    //  HELLO
    //  HELL
    //  HEL
    //  HE
    //  H
  }
*/

/*
  // ways to empty a string object (deleting all chars)

  int main()
  {
    std::string str{ "helloworld" };

    std::cout << "str.size() = " << str.size() << '\n';
    // output -> str.size() = 10

    str = "";
    str = std::string{};
    str = {};
    str.resize(0);
    str.clear();
    str.erase(0);
    str.erase();
    str.erase(str.begin(), str.end()); // range erase
  }
*/

/*
  #include <string>

  int main()
  {
    using namespace std;

    // ------------------------------------------------

    string str{ "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ" };
    cout << "lenght() = " << str.length() << '\n';
    // output -> lenght() = 36
    cout << "capacity() = " << str.capacity() << '\n';
    // output -> capacity() = 36

    str.erase(10, 5);
    // (index interface) starting from 10th index delete 5 chars

    std::cout << "str = " << str << '\n';
    // output -> str = 0123456789FGHIJKLMNOPQRSTUVWXYZ

    cout << "lenght() = " << str.length() << '\n';
    // output -> lenght() = 31
    cout << "capacity() = " << str.capacity() << '\n';
    // output -> capacity() = 36
    
    // ------------------------------------------------

    str = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    str.erase(10);
    // (index interface) starting from 10th index delete all chars
    // str.erase(10, string::npos); is equivalent.

    cout << "str = " << str << '\n';
    // output -> str = 0123456789

    cout << "lenght() = " << str.length() << '\n';
    // output -> lenght() = 10
    cout << "capacity() = " << str.capacity() << '\n';
    // output -> capacity() = 36

    // ------------------------------------------------

    str = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    str.erase(10,1);
    // (index interface) starting from 10th index delete 1 char
    cout << "str = " << str << '\n';
    // output -> str = 0123456789BCDEFGHIJKLMNOPQRSTUVWXYZ


    cout << "lenght() = " << str.length() << '\n';
    // output -> lenght() = 35
    cout << "capacity() = " << str.capacity() << '\n';
    // output -> capacity() = 36

    // ------------------------------------------------

    str = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    str.erase(0);
    // (index interface) starting from 0th index delete all chars
    // str.erase(0, string::npos); is equivalent.

    cout << "str = " << str << '\n';
    // output -> str =

    cout << "lenght() = " << str.length() << '\n';
    // output -> lenght() = 0
    cout << "capacity() = " << str.capacity() << '\n';
    // output -> capacity() = 36
    
    // ------------------------------------------------

    str = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    str.erase();
    // (index interface) starting from 0th index delete all chars
    // str.erase(0, string::npos); is equivalent.

    cout << "str = " << str << '\n';
    // output -> str =

    cout << "lenght() = " << str.length() << '\n';
    // output -> lenght() = 0
    cout << "capacity() = " << str.capacity() << '\n';
    // output -> capacity() = 36

    // ------------------------------------------------

    str = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    str.resize(0);

    cout << "str = " << str << '\n';
    // output -> str =

    cout << "lenght() = " << str.length() << '\n';
    // output -> lenght() = 0
    cout << "capacity() = " << str.capacity() << '\n';
    // output -> capacity() = 36

    // resize(0) will make the string object empty

    // ------------------------------------------------

    str.shrink_to_fit();

    cout << "lenght() = " << str.length() << '\n';
    // output -> lenght() = 0

    cout << "capacity() = " << str.capacity() << '\n';	
    // output -> capacity() = 15

    // ------------------------------------------------
  }
*/

/*
  #include <algorithm>  // std::lexicographical_compare
  #include <string>

  int main()
  {

    std::string str{ "hello world" };

    // ------------------------------------------------

    if (str == "HELLO WORLD") {}
    // operator==(const std::string&, const char*)

    // std::string object can be compared with 
    // CString(const char*)

    // ------------------------------------------------

    std::string str_2{ "hello galaxy" };

    if (str == str_2) {}
    // operator==(const std::string&, const std::string&)

    // std::string object can be compared with 
    // another std::string object

    // ------------------------------------------------

    // int compare(str_1, str_2);
    // (+) if result is positive  ->  (str_1 > str_2)
    // (-) if result is negative  ->  (str_1 < str_2)
    // (0) if result is zero      ->  (str_1 = str_2)

    // ------------------------------------------------

    str.compare("istanbul");
    // int compare(const char*) overload  (member function)
    // comparing *this with CString(const char*)

    // ------------------------------------------------

    str.compare(str_2);
    // int compare(const std::string&) overload  (member function)
    // comparing *this with another std::string object

    // ------------------------------------------------

    str.compare(3, 4, str_2, 6, 4);
    // comparing substring of *this 
    // with substring of another std::string object

    // (str)   4 chars starting from 3th index 
    // compared with
    // (str_2) 4 chars starting from 6th index

    // ------------------------------------------------

    constexpr const char* c_str1 = "apple";
    constexpr const char* c_str2 = "banana";

    constexpr bool b1 = std::lexicographical_compare(
                                c_str1, c_str1 + 5, 
                                c_str2, c_str2 + 6);    
    // b1 -> true     
               
    // ------------------------------------------------
  }
*/

/*
  - std::string class is a container class
    functions for containers can also be used for string class
    (e.g, reverse(), sort(), trim functions... )
  - container functions can be used with iterator interface.
*/

/*
  #include <algorithm>  // std::reverse, std::sort
  #include <string>

  int main()
  {
    std::string str{ "hello world" };

    // ------------------------------------------------

    std::reverse(str.begin(), str.end()); // iterator interface
    std::cout << "str = " << str << '\n';
    // output -> str = dlrow olleh

    // ------------------------------------------------

    std::sort(str.begin(), str.end());
    std::cout << "str = " << str << '\n';
    // output -> str =  dehllloorw

    // ------------------------------------------------
  }
*/

/*
                      ----------------------
                      | remove-erase idiom |
                      ----------------------
*/

/*
  #include <algorithm>  // std::remove_if, std::erase_if(C++20)
  #include <string>

  int main()
  {
    // ------------------------------------------------

    std::string str{ "hello world we are live from istanbul" };

    str.erase(
      std::remove_if( str.begin(), 
                      str.end(),
                      [](char ch) { 
        return std::string{ "aeoui" }.find(ch) != std::string::npos;}), 
      str.end());

    std::cout << "str = " << str << '\n';
    // output -> str = hll wrld w r lv frm stnbl

    // ------------------------------------------------

    str = { "hello world we are live from istanbul" };

    std::erase_if(str, [](char ch) {
      return std::string{ "aeoui" }.find(ch) != std::string::npos;
    });

    std::cout << "str = " << str << '\n';
    // output -> str = hll wrld w r lv frm stnbl

    // ------------------------------------------------
  }
*/

/*
          ------------------------------------------------
          | search member functions of std::string class |
          ------------------------------------------------
*/


/*
  - find
  - rfind (reverse find)
  - find_first_of
  - find_first_not_of
  - find_last_of
  - find_last_not_of
    -> if found     -> returns index(string::size_type)
    -> if not found -> returns string::npos

  - contains (C++23) 
    -> returns bool type

  - search functions can be used also for substrings.
*/

/*
  #include <string>

  int main()
  {
    std::string str{ "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ" };

    char ch = 'A';

    if (auto idx = str.find(ch); idx != std::string::npos)
    {
      std::cout << "found, idx = " << idx << '\n';
      str[idx] = '*';
      std::cout << "str = " << str << '\n';
    }
    else
      std::cout << "not found\n";
    
    // output ->
    //  found, idx = 10
    //  str = 0123456789*BCDEFGHIJKLMNOPQRSTUVWXYZ
  }
*/

/*
  #include <string>

  int main()
  {
    std::string str{ "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ" };
    std::string searched{ "KLMNOP" };

    if (auto idx = str.find(searched); idx != std::string::npos)
    {
      std::cout  << "found, idx = " << idx << '\n';
      auto len = searched.length();
      str.replace(idx, len, len, '*');
      std::cout << "str = " << str << '\n';
    }
    else
      std::cout << "not found\n";

    // output ->
    //  found, idx = 20
    //  str = 0123456789ABCDEFGHIJ******QRSTUVWXYZ
  }
*/

/*
  #include <string>

  int main()
  {
    std::string str{ "hello world, hello galaxy" };
    constexpr int len_searched = 5;

    // ------------------------------------------------

    auto idx = str.find("hello");
    str.replace(idx, len_searched, len_searched, '*');

    std::cout << "str = " << str << '\n';
    // output -> sstr = ***** world, hello galaxy

    // ------------------------------------------------

    str = { "hello world, hello galaxy" };

    idx = str.rfind("hello");
    str.replace(idx, len_searched, len_searched, '*');

    std::cout << "str = " << str << '\n';
    // output -> str = hello world, ***** galaxy

    // ------------------------------------------------
  }
*/

/*
  #include <string>

  int main()
  {
    std::string str = { "hello world live from istanbul" };

    // ------------------------------------------------

    if (auto idx = str.find_first_of("aetkms"); 
        idx != std::string::npos)
      std::cout << "found, idx = " << idx << '\n';
    // output -> found, idx = 1 
    // (e is in index 1)

    // ------------------------------------------------

    if (auto idx = str.find_first_not_of("hetkms"); 
        idx != std::string::npos) 
      std::cout << "found, idx = " << idx << '\n';
    
    // output -> found, idx = 2
    // (l is in index 2)

    // ------------------------------------------------
  }
*/

/*
  #include <string>

  int main()
  {
    std::string str_1{ "hello" };
    std::string str_2{ "world" };

    // ------------------------------------------------

    (void)(str_1 + str_2 + 'A' + "really");
    // "+" operator is left associative

    // ------------------------------------------------

    std::cout << str_1 + str_2 + '_' + "real" << '\n';
    // output -> helloworld_real
    // operator+(const std::string&, const std::string&)
    // operator+(const std::string&, char)
    // operator+(const std::string&, const char*)

    std::cout << "dream*" + str_2 << '\n';
    // output -> dream*world
    // operator+(const char*, const std::string&)

    // ------------------------------------------------

    // 2 CString objects can NOT be added with "+" operator
    // because 2 pointers can NOT be added

    const char* p_str1 = "hello";
    const char* p_str2 = "galaxy";

    std::cout << p_str1 + p_str2 << '\n';  // syntax error
    // error: invalid operands of types 'const char*' and
    // 'const char*' to binary 'operator+'

    std::cout << p_str1 + "universe" << '\n'; // syntax error
    // error: invalid operands of types 'const char*' and 
    // 'const char [9]' to binary 'operator+'

    // ------------------------------------------------

    using namespace std::string_literals;

    "hello"s;                   // string literal
    operator""s("hello", 5);    // string literal
    // converts CString(const char*) to std::string object 

    std::cout << "hello"s + " world"s << '\n';	
    // output -> hello world
    // opetator+(const std::string&, const std::string&)

    std::cout << "hello "s + p_str2 << '\n';
    // output -> hello galaxy
    // operator+(const std::string&, const char*)

    // ------------------------------------------------
  }
*/

/*
  #include <string>
  #include <algorithm>  // std::swap

  int main()
  {
    std::string str_1(100'000, 'A');
    std::string str_2(100'000, 'Z');

    str_1.swap(str_2);          
    // std::string classes member swap function

    std::swap(str_1, str_2);    
    // global swap function
  }
*/

/*
  #include <string>   // std::stoi, std::to_string
  #include <cstdlib>  // std::atoi

  int main()
  {
    int ival{ 343234234 };
    double dval{ 3432.34234 };
    std::string str = {"hello"};

    // ------------------------------------------------

    str = str + std::to_string(ival);
    std::cout << "str = " << str << '\n';
    // output -> str = hello343234234

    // ------------------------------------------------

    str = { "hello" };
    str = str + std::to_string(dval);
    std::cout << "str = " << str << '\n';
    // output -> str = hello3432.342340

    // ------------------------------------------------

    str = { "9123helloworld" };
    int int_val;

    // int atoi( const char* str ); 
    // parameter variable type is CString(const char*)
    int_val = std::atoi(str.c_str());

    std::cout << int_val << '\n';
    // output -> 9123

    // ------------------------------------------------

    str = { "9123helloworld" };

    //  int stoi (const std::string& str, 
    //            std::size_t* pos = nullptr, 
    //            int base = 10 );

    int int_val2 = std::stoi(str, nullptr, 16);
    std::cout << "0x9123 = " << int_val2 << '\n';
    // output -> 0x9123 = 37155

    // ------------------------------------------------

    str = { "9123helloworld" };

    std::size_t idx;
    int_val2 = std::stoi(str, &idx);

    std::cout << "idx = " << idx << '\n'; 
    // output -> idx = 4
    // 4th index is the first non-digit character

    std::cout << "int_val2 = " << int_val2 << '\n';
    // output -> int_val2 = 9123

    // ------------------------------------------------
  }
*/

/*
  #include <sstream>  // std::ostringstream
  #include <string>

  int main()
  {
    int ival{ 34365 };
    double dval = 234.96;
    std::string str = { "hello world" };

    std::ostringstream oss;
    // std::ostringstream class is a stream class
    // that will write data to buffer

    oss << ival << '_' << dval << '_' << str;

    std::cout << "oss.str() = " << oss.str() << '\n';
    // output -> oss.str() = 34365_234.96_hello world

    // str member function of std::ostringstream class
    // returns the buffer as a std::string object
  }
*/

/*
  #include <algorithm>  // std::count, std::transform
  #include <vector>
  #include <cctype>     // std::toupper 

  int main()
  {
    std::string str{ "hello world we are live from istanbul" };
    char ch = 'o';

    // ------------------------------------------------

    std::cout << "'o' char count = " 
              << std::count(str.begin(), str.end(), ch) << '\n';
    // output -> 'o' char count = 3

    // std::count global function using iterator interface

    // ------------------------------------------------

    std::vector<char> cvec = { 'j','o','k','e' };
    str.assign(cvec.begin(), cvec.end());

    std::cout << "str = " << str << '\n';
    // output -> str = joke

    // ------------------------------------------------

    str = { "hello world we are live from istanbul" };

    std::transform(str.begin(), str.end(), str.begin(), 
                   [](char ch) { return std::toupper(ch); });

    std::cout << "str = " << str << '\n';
    // output -> str = HELLO WORLD WE ARE LIVE FROM ISTANBUL

    // ------------------------------------------------
  }
*/

/*
  #include <string>

  int main()
  {
    std::cout << std::boolalpha;

    std::string str = { "image_istanbul.jpeg" };

    // ------------------------------------------------

    bool b1 = str.starts_with("image");
    std::cout << b1 << '\n';  // output -> true

    bool b2 = str.ends_with(".jpeg");
    std::cout << b1 << '\n';  // output -> true

    // std::string classes "starts_with" and "ends_with" 
    // member functions are added in C++20

    // ------------------------------------------------

    bool b3 = str.contains("ist");
    std::cout << b1 << '\n';  // output -> true

    // std::string classes "contains" member function
    // is added in C++23

    // ------------------------------------------------
  }
*/

/*
                ----------------------------------
                | std::string_view class (C++17) |
                ----------------------------------
*/

/*
  - purpose is to read from a std::string object 
    it is better to use std::string_view class

  - string_view class have 2 pointer in its interface

  - all of the read-only functions inside std::string class
    are also inside std::string_view class interface
*/

/*
  #include <string_view>

  class String_View {
  private:
    const char* mp_start;
    const char* mp_end;
  public:
    std::size_t length() { return mp_end - mp_start; }
  };

  int main()
  {
    std::cout << "sizeof(std::string_view) = " << 
              sizeof(std::string_view) << '\n';
    // output -> sizeof(std::string_view) = 16
  }
*/

/*
  #include <string>

  int main()
  {
    std::string str(200'000, 'A');

    auto str_2 = str.substr(30'000, 70'000);
    // substr member function creates a new std::string object
    // that means copying 40'000 chars from str to str_2
  }
*/

/*
  #include <string>
  #include <string_view>

  int main()
  {
    // ------------------------------------------------

    const char* p_str = "hello world we are live from istanbul";

    std::string str_1(p_str);
    // copying CString to std::string object

    std::string_view strview_1 = p_str;
    // created a std::string_view object which is pointing
    // to the CString's begin and end.

    // ------------------------------------------------

    std::string str_2{ "real or illusion" };
    std::string_view strview_2{ str_2 };
    // created a std::string_view object from std::string object

    std::cout << strview_2 << '\n';
    // output -> real or illusion

    str_2.append(300, 'A');
    // reallocation happens, address of memory(char array) that 
    // std::string object is pointing in heap is changed.
    // but std::string_view object is still pointing
    // to the old memory address.
    // so std::string_view object's pointers are now dangling.

    std::cout << strview_2 << '\n'; // undefined behavior(UB)

    // ------------------------------------------------
  }
*/