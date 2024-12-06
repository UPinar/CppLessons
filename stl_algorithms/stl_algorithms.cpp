#include <iostream>

/*
                        ==================
                        | STL Algorithms |
                        ==================
*/

/*
  #include <vector>
  #include <list>
  #include <string>

  // Print is an algorithm example
  // It is a generic function template.

  template <typename Iter>
  void Print(Iter beg, Iter end)
  {
    while (beg != end) {
      std::cout << *beg++ << ' ';
    }
    std::cout << '\n';
  }

  int main()
  {
    using namespace std;

    // -------------------------------------------------

    int i_arr[5]{ 1, 2, 3, 4, 5 };

    Print(i_arr, i_arr + 5);        
    // output -> 1 2 3 4 5
    Print(i_arr + 1, i_arr + 4);    
    // output -> 2 3 4

    // -------------------------------------------------

    std::vector<int> ivec{ 10, 20, 30, 40, 50 };
    Print(ivec.begin(), ivec.end());    
    // output -> 10 20 30 40 50

    // -------------------------------------------------

    list<string> mylist{ "world", "galaxy", "universe" };
    Print(mylist.begin(), mylist.end());  
    // output -> world galaxy universe

    // -------------------------------------------------
  }
*/

/*
  #include <algorithm>  // std::sort, std::reverse
  #include <vector>

  template <typename Iter>
  void Print(Iter beg, Iter end)
  {
    while (beg != end) {
      std::cout << *beg++ << ' ';
    }
    std::cout << '\n';
  }

  int main()
  {
    std::vector<int> ivec{10, 3, 54, 23, 26, 98, 63};

    // --------------------------------------------------

    std::sort(ivec.begin(), ivec.end());
    // "std::sort" function template is a standart algorithm

    Print(ivec.begin(), ivec.end());
    // output -> 3 10 23 26 54 63 98

    // --------------------------------------------------

    std::reverse(ivec.begin(), ivec.end());
    // "std::reverse" function template is a standart algorithm

    Print(ivec.begin(), ivec.end()); 
    // output -> 98 63 54 26 23 10 3

    // --------------------------------------------------
  }
*/

/*
              -------------------------------------
              | std::copy, std::copy_if algorithm |
              -------------------------------------
*/

/*
  #include <vector>
  #include <list>

  // minimal input iterator for 1st template parameter
  // minimal output iterator for 2nd template parameter
  template <typename InIter, typename OutIter>
  OutIter Copy(InIter src_beg, InIter src_end, OutIter dest_beg)
  {
    while (src_beg != src_end) 
      *dest_beg++ = *src_beg++;

    return dest_beg;
  }

  int main()
  {
    using namespace std;

    vector<int> ivec{ 11, 22, 33, 44, 55, 66 };
    list<int> ilist(6);

    Copy(ivec.begin(), ivec.end(), ilist.begin());
    // InIter will be deduced to std::vector<int>::iterator
    // OutIter will be deduced to std::list<int>::iterator

    for (auto i : ilist)
      std::cout << i << ' ';
    // output -> 11 22 33 44 55 66
  }
*/

/*
  #include <vector>
  #include <list>

  template <typename InIter, typename OutIter>
  OutIter Copy(InIter src_beg, InIter src_end, OutIter dest_beg)
  {
    while (src_beg != src_end) 
      *dest_beg++ = *src_beg++;

    return dest_beg;
  }

  int main()
  {
    using namespace std;

    vector<int> ivec{ 11, 22, 33, 44, 55, 66};

    // ---------------------------------------------------

    list<int> ilist_1;  // default initialization
    Copy(ivec.begin(), ivec.end(), ilist_1.begin());
    // because of there is no element in the ilist_1
    // "*dest_beg" expression will be undefined behaviour(UB)

    // ---------------------------------------------------

    list<int> ilist_2(5);
    Copy(ivec.begin(), ivec.end(), ilist_2.begin());
    // because of there are 5 elements in ilist_2
    // 6th assignment will be an undefined behaviour(UB)

    // ---------------------------------------------------

    list<int> ilist_3(11);  
    Copy(ivec.begin(), ivec.end(), ilist_3.begin());
    // because of there are more elements than vector
    // all assingments are VALID.

    // ---------------------------------------------------
  }
*/

/*
  #include <algorithm>  // std::copy
  #include <vector>
  #include <list>
  #include <string>

  int main()
  {
    using namespace std;

    vector<string> svec{ "world", "galaxy", "universe" };

    list<string> slist(3);
    std::copy(svec.begin(), svec.end(), slist.begin());

    for (auto str : slist)
      cout << str << ' ';
    // output -> world galaxy universe
  }
*/

/*
  template <typename InIter, typename OutIter, typename UnaryPred>
  OutIter Copy_if(InIter src_beg_iter, 
                  InIter src_end_iter, 
                  OutIter dest_beg_iter, 
                  UnaryPred fn)
  {
    while (src_beg_iter != src_end_iter) 
    {
      if (fn(*src_beg_iter)) 
        *dest_beg_iter++ = *src_beg_iter;
      
      src_beg_iter++;
    }

    return dest_beg_iter;
  }
*/

/*
                      -----------------------
                      | std::sort algorithm |
                      -----------------------
  -> O(nlogn)
*/

/*
  #include <algorithm>  // std::sort
  #include <vector>

  int main()
  {
    using namespace std;

    vector<int> ivec{ 1, 5, 2, 54, 7, 3, 6, 75, 23, 34, 645, 12 };

    std::sort(ivec.begin(), ivec.end());

    for (auto elem : ivec)
      std::cout << elem << ' ';
    // output -> 1 2 3 5 6 7 12 23 34 54 75 645
  }
*/

/*
  #include <algorithm>  // std::sort
  #include <list>

  int main()
  {
    using namespace std;

    list<int> ilist{ 1, 3, 2, 5, 6, 7, 3, 54, 75, 23, 34, 645, 12 };

    std::sort(ilist.begin(), ilist.end());  // syntax error
    // error: no match for 'operator-' 
    // (operand types are 'std::_List_iterator<int>' 
    // and 'std::_List_iterator<int>')

    // std::sort algorithms template parameter category
    // needs to be minimum random-access iterator
    // std::sort(const _RanIt first, const _RanIt second)

    // list<int>::iterator type is bidirectional iterator
    // which is lower than random-access iterator
  }
*/

/*
              -------------------------------------
              | std::find, std::find_if algorithm |
              -------------------------------------
  -> linear search - O(n) 
*/

/*
  #include <algorithm>  // std::find
  #include <vector>
  #include <string>

  template <typename InIter, typename Key>
  InIter Find(InIter beg, InIter end, const Key& key)
  {
    while (beg != end) 
    {
      if (*beg == key)
        return beg;

      ++beg;
    }
    return end;
  }

  int main()
  {
    using namespace std;

    vector<string> svec{ "in", "twenty", "years", "we",
                      "will", "become", "half", "robots" };

    //-----------------------------------------------------------

    auto iter = Find(svec.begin(), svec.end(), "years");
    if (iter != svec.end()) 
    {
      std::cout << '[' << *iter << "] has been found\n";
      std::cout << "its length = " << iter->length() << '\n';
      std::cout << "its index = " << iter - svec.begin() << '\n';
    }
    else
      std::cout << "has not been found\n";

    // output ->
    //  [years] has been found
    //  its length = 5
    //  its index = 2

    // random_access iterator supports '-' operator.

    //-----------------------------------------------------------

    // if_with initializer syntax (no scope leakage)

    if (auto iter = Find(svec.begin(), svec.end(), "days"); 
        iter != svec.end()) 
    {
      std::cout << "has been found -> " << *iter << '\n';
      std::cout << "its length = " << iter->length() << '\n';
      std::cout << "its index = " << iter - svec.begin() << '\n';
    }
    else
      std::cout << "has not been found\n";

    // output -> has not been found

    //-----------------------------------------------------------
  }
*/

/*
  template <typename InIter, typename UnaryPred>
  InIter Find_If(InIter iter_beg, InIter iter_end, UnaryPred fn)
  {
    while (iter_beg != iter_end) 
    {
      if (fn(*iter_beg)) {
        return iter_beg;
      }
      ++iter_beg;
    }
    return iter_end;
  }
*/

/*
  #include <vector>
  #include <string>
  #include <algorithm>  // std::find_if

  int main()
  {
    using namespace std;

    vector<string> svec{ 
        "hello", "world", "we", "are", "live", "from", "Istanbul"
        "monday", "friday", "sunday", "galaxy", "univers"};

    string key{ "la" }; 

    if (auto iter = std::find_if(svec.begin(), svec.end(),
                      [key](const string& str) { 
                        return str.find(key) != string::npos; 
                      }); iter != svec.end()) 
    {
      std::cout << "has been found = " << *iter << '\n';
    }
    else 
      std::cout << "has not been found\n";

    // output -> has been found = galaxy
    

    // "key" is being captured in capture clause,
    // when compiler is generating closure object
    // it will add a data member to the closure object
    // that is why "key" can be used inside function body
  }
*/

/*
            ------------------------------------------
            | std::back_inserter, st::front_inserter |
            ------------------------------------------
*/

/*
  #include <algorithm>  // std::copy
  #include <vector>
  #include <iterator>   // std::back_inserter

  template <typename InIter , typename OutIter>
  OutIter Back_Inserter_Copy( InIter src_beg, 
                              InIter src_end, 
                              OutIter dest_beg)
  {
    while (src_beg != src_end)
      dest_beg = *src_beg++;
  
    return dest_beg;
  }

  template <typename Con>
  class Back_Insert_Iterator {
  private:
    Con& m_con;
  public:
    Back_Insert_Iterator(Con &c) : m_con(c) {}

    Back_Insert_Iterator& operator*()
    {
      return *this;
    }

    Back_Insert_Iterator& operator++(int)
    {
      return *this;
    }

    Back_Insert_Iterator& operator++()
    {
      return *this;
    }

    Back_Insert_Iterator& 
    operator=(const typename Con::value_type& val)
    {
      m_con.push_back(val);
      return *this;
    }
  };

  template <typename Con>
  Back_Insert_Iterator<Con> Back_Inserter(Con& c)
  {
    return Back_Insert_Iterator<Con>(c);
  }

  int main()
  {
    using namespace std;

    vector ivec1{ 11, 22, 33, 44, 55, 66, 77 };   // CTAD

    // ---------------------------------------------------------

    vector<int> ivec2;
    Back_Insert_Iterator<vector<int>> iter{ ivec2 };
    // Back_Insert_Iterator's data member m_con binds to ivec2.

    std::copy(ivec1.begin(), ivec1.end(), iter);
    // because of Back_Insert_Iterator class's
    // "operator*" and "operator++()" and "operator++(int)" 
    // overloads are returning Back_Insert_Iterator object itself,
    // "*dest_beg++ = *src_beg++;" statement will become 
    // "dest_beg = *src_beg++;" statement.
    // "operator=" overload will call container's(data member)
    // "push_back" member function.

    for (auto elem : ivec2)
      std::cout << elem << ' ';
    // output -> 11 22 33 44 55 66 77

    std::cout << '\n';
 
    // ---------------------------------------------------------

    vector<int> ivec3;
    std::copy(ivec1.begin(), 
              ivec1.end(), 
              Back_Insert_Iterator<vector<int>>{ ivec3 });
    // temporary Back_Insert_Iterator<vector<int>> object

    for (auto elem : ivec3)
      std::cout << elem << ' ';
    // output -> 11 22 33 44 55 66 77
    
    std::cout << '\n';

    // ---------------------------------------------------------

    vector<int> ivec4;
    std::copy(ivec1.begin(), ivec1.end(), Back_Inserter(ivec4));

    for (auto elem : ivec4)
      std::cout << elem << ' ';
    // output -> 11 22 33 44 55 66 77

    std::cout << '\n';

    // ---------------------------------------------------------

    vector<int> ivec5;
    std::copy(ivec1.begin(), 
              ivec1.end(), 
              std::back_inserter(ivec5));

    for (auto elem : ivec5)
      std::cout << elem << ' ';
    // output -> 11 22 33 44 55 66 77

    // ---------------------------------------------------------
  }
*/

/*
  #include <algorithm>  // std::copy
  #include <iterator>   
  // std::back_inserter, std::front_inserter
  #include <string>
  #include <vector>
  #include <list>

  int main()
  {
    using namespace std;

    vector<string> svec{ "world", "galaxy", "universe" };

    // ------------------------------------------------------

    list<string> slist1;
    copy(svec.begin(), svec.end(), back_inserter(slist1));

    std::cout << "back_inserter(slist1) : ";
    for (auto elem : slist1)
      std::cout << elem << ' ';
    // output -> back_inserter(slist1) : world galaxy universe

    // operator=() overload is calling push_back()
    // member function of the container.

    std::cout << '\n';

    // ------------------------------------------------------

    list<string> slist2;
    copy(svec.begin(), svec.end(), front_inserter(slist2));

    std::cout << "front_inserter(slist1) : ";
    for (auto elem : slist2)
      std::cout << elem << ' ';
    // output -> front_inserter(slist1) : universe galaxy world

    // operator=() overload is calling push_front() 
    // member function of the container.

    // ------------------------------------------------------
  }
*/

/*
              ---------------------------------------
              | std::count, std::count_if algorithm |
              ---------------------------------------
*/


/*
  #include <list>
  #include <string>
  #include <algorithm>  // std::count

  // mental model for std::count algorithm
  template <typename InIter, typename T>
  int Count(InIter iter_beg, InIter iter_end, const T& val)
  {
    int total_count{};

    while (iter_beg != iter_end) {
      if (*iter_beg == val)
        ++total_count;

      ++iter_beg;
    }
    return total_count;
  }

  int main()
  {
    using namespace std;

    list<string> slist{ "world", "galaxy", "universe",
      "hello", "istanbul", "world", "galaxy" }; 

    string str{ "galaxy" };

    int total_count = std::count(slist.begin(), slist.end(), str);
    std::cout << "total_count = " << total_count << '\n';
    // output -> total_count = 2
  }
*/

/*
  #include <string>
  #include <algorithm>  // std::count

  int main()
  {
    std::string str{ "hello world, we are live from Istanbul" };
    char ch = 'o';

    int total_count = std::count(str.begin(), str.end(), ch);
    std::cout << "total_count = " << total_count << '\n';
    // total_count = 3
  }
*/

/*
  template <typename InIter, typename UnaryPred>
  int Count_If(InIter iter_beg, InIter iter_end, UnaryPred fn)
  {
    int total_count{};

    while (iter_beg != iter_end) 
    {
      if (fn(*iter_beg)) 
        ++total_count;
      
      ++beg;
    }
    return total_count;
  }
*/

/*
  #include <vector>
  #include <algorithm>  // std::count_if
  #include <cstdio>     // std::printf

  bool is_even(int x) { return x % 2 == 0; }
  // unary predicate : have 1 parameter, returns bool

  class Div_Pred {
  private:
    int m_val;

  public:
    Div_Pred(int val) : m_val{ val } {}

    bool operator()(int x) const
    {
      return x % m_val == 0;
    }
  };

  int main()
  {
    using namespace std;

    // ---------------------------------------------------

    vector<int> ivec{ 
      10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
      20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 
      30, 31, 32, 33, 34, 35, 36, 37, 38, 39 };

    int even_count = count_if(ivec.begin(), ivec.end(), &is_even);
    std::cout << "even count = " << even_count << '\n';
    // output -> even count = 12

    // ---------------------------------------------------

    int val = 7;
    int divisible_count = 0;

    divisible_count = 
      std::count_if(ivec.begin(), ivec.end(), Div_Pred{ val });

    std::printf("divisible to %d count = %d\n", 
                val, divisible_count);
    // output -> divisible to 7 count = 4

    // Div_Pred{ val } temp objects "operator()(int)" function
    // is a unary predicate
    // Div_Pred is a functor class.
    
    // ---------------------------------------------------
  }
*/

/*
  #include <vector>
  #include <algorithm>
  #include <string>
  #include <cstddef>    // std::size_t
  #include <cstdio>     // std::printf

  class Len_Pred {
  private:
    std::size_t m_len;

  public:
    Len_Pred(std::size_t len) : m_len{ len } {}

    bool operator()(const std::string& str) const
    {
      return str.length() == m_len;
    }
  };

  int main()
  {
    using namespace std;

    vector<string> svec{ 
      "a", "aa", "aaa", "aaaa", 
      "b", "bb", "bbbb", 
      "c", "cc", "ccc", "cccc", 
      "d", "dd", "ddd", "dddd", "ddddd" };

    // -------------------------------------------------

    size_t val = 2;
    int same_len_count = 0;

    same_len_count = 
      count_if(svec.begin(), svec.end(), Len_Pred{ val });
      
    std::printf("count of %d length strings = %d\n", 
                val, same_len_count);
    // output -> count of 2 length strings = 4

    // -------------------------------------------------

    for (std::size_t i{ 1 }; i < 6; ++i)
    {
      cout << "count of " << i << " length strings = " <<
        count_if(svec.begin(), svec.end(), Len_Pred{ i }) << '\n';
    }
    // output ->
    //  count of 1 length strings = 4
    //  count of 1 length strings = 4
    //  count of 2 length strings = 4
    //  count of 3 length strings = 3
    //  count of 4 length strings = 4
    //  count of 5 length strings = 1

    // -------------------------------------------------
  }
*/

/*
  when a lambda expression is being used, 
  compiler is writing a class and 
  generate a temporary object(closure object) from that class
  
  lambda expression can be sent instead of a functor class
  no need to explicitly write a functor class

  []            -> lambda introducer
  [expr]        -> expr is capture clause
  [](int x)()   -> function call operator

  "[](int x) { return x * 5; }" is a PRValue expression(R)
  
  "[](int x) { return x *5; }(10);" statement will generate 
  a temporary object and call the function call operator
  with 10 as an argument and the generated value will be 50.

  // compiler generated temporary class

  class ztr_yuq {	
  public:
    auto operator()(int x) const { return x * 5; }
    // return type of the operator() function 
    // will be calculated with type deduction
  };
*/

/*
  // using lambda expression in std::count_if algorithm

  #include <vector>
  #include <string>
  #include <cstddef>      // std::size_t
  #include <algorithm>    // std::count_if

  int main()
  {
    using namespace std;

    vector<string> svec{ 
      "a", "aa", "aaa", "aaaa", 
      "b", "bb", "bbbb", 
      "c", "cc", "ccc", "cccc", 
      "d", "dd", "ddd", "dddd", "ddddd" };

    int total_count = 0;
    for (size_t i{ 1 }; i < 6; ++i)
    {
      total_count = std::count_if(svec.begin(), svec.end(),
          [i](const string& s) { return s.length() == i; });

      std::cout << "count of " << i << " length strings = " 
                << total_count << '\n';
    }
    // output ->
    //  count of 1 length strings = 4
    //  count of 2 length strings = 4
    //  count of 3 length strings = 3
    //  count of 4 length strings = 4
    //  count of 5 length strings = 1
  }
*/

/*
                  ----------------------------
                  | std::transform algorithm |
                  ----------------------------
*/


/*
  // wanted to transform a vector of strings to 
  // vector of string lengths.

  #include <vector>
  #include <string>
  #include <cstddef>    // std::size_t
  #include <algorithm>  // std::transform
  #include <iterator>   // std::back_inserter

  // mental model for std::transform algorithm
  template <typename InIter, typename OutIter, typename UnaryFunc>
  OutIter Transform(InIter src_iter_beg, 
                    InIter src_iter_end, 
                    OutIter dest_iter_beg, 
                    UnaryFunc fn)
  {
    while (src_iter_beg != src_iter_end) 
      *dest_iter_beg++ = fn(*src_iter_beg++);
    
    return dest_iter_beg;
  }

  int main()
  {
    using namespace std;

    vector<string> svec{ 
        "yes", "no", "stop", "go", "mars", "earth", 
        "side", "fight", "far", "bar" };

    vector<size_t> len_vec;

    std::transform( svec.begin(), 
                    svec.end(), 
                    std::back_inserter(len_vec), 
                    [](const string& str) { return str.length(); });

    std::size_t vec_size = len_vec.size();

    for (size_t i = 0; i < vec_size; i++)
      cout << svec[i] << " - " << len_vec[i] << '\n';
    // output ->
    //  yes - 3
    //  no - 2
    //  stop - 4
    //  go - 2
    //  mars - 4
    //  earth - 5
    //  side - 4
    //  fight - 5
    //  far - 3
    //  bar - 3
  }
*/

/*
  #include <vector>
  #include <string>
  #include <algorithm>  // std::transform

  std::string Reverse(std::string str)
  {
    std::reverse(str.begin(), str.end());
    return str;
  }

  int main()
  {
    using namespace std;

    vector<string> svec{ 
        "yes", "no", "stop", "go", "mars", "earth", "side" };

    for (auto elem : svec)
      std::cout << elem << ' ';
    // output -> yes no stop go mars earth side
    std::cout << '\n';

    std::transform(svec.begin(), svec.end(), svec.begin(), Reverse);
    // sending svec.begin() as a dest_beg_iter 
    // so svec will be overwritten with reversed strings.

    for (auto elem : svec)
      std::cout << elem << ' ';
    // output -> sey on pots og sram htrae edis
  }
*/

/*
  #include <vector>
  #include <list>
  #include <algorithm>    // std::transform
  #include <iterator>     // std::back_inserter

  // mental model for std::transform(5 parameter) algorithm 
  template <typename InIter_1, typename InIter_2, 
            typename OutIter, typename BinaryFunc>
  OutIter Transform(InIter_1 src_iter_beg1, 
                    InIter_1 src_iter_end1, 
                    InIter_2 src_iter_beg2, 
                    OutIter dest_iter_beg, 
                    BinaryFunc fn)
  {
    while (src_iter_beg1 != src_iter_end1) 
      *dest_iter_beg++ = fn(*src_iter_beg1++, *src_iter_beg2++);
    
    return dest_iter_beg;
  }

  int sum_square(int a, int b)
  {
    return a * a + b * b;
  }

  int main()
  {
    using namespace std;

    int i_arr[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    vector<int> ivec{ 11, 22, 33, 44, 55, 66, 77, 88, 99 };

    // ---------------------------------------------------

    list<int> ilist1;

    transform(std::begin(i_arr), 
              std::end(i_arr), 
              ivec.begin(),  
              std::back_inserter(ilist1), 
              &sum_square);

    for (auto elem : ilist1)
      std::cout << elem << ' ';
    // output -> 122 488 1098 1952 3050 4392 5978 7808 9882

    std::cout << '\n';

    // ---------------------------------------------------

    list<int> ilist2;

    transform(std::begin(i_arr), 
              std::end(i_arr), 
              ivec.begin(),
              std::back_inserter(ilist2), 
              [](int a, int b) { return a * a + b * b; });

    for (auto elem : ilist2)
      std::cout << elem << ' ';

    // output -> 122 488 1098 1952 3050 4392 5978 7808 9882

    // ---------------------------------------------------
  }
*/

/*
                  ---------------------------
                  | std::for_each algorithm |
                  ---------------------------
*/

/*
  - returns a callable
*/


/*
  #include <cctype>       // std::toupper
  #include <vector>
  #include <string>
  #include <algorithm>    // std::for_each

  // mental model for std::for_each algorithm
  template <typename Iter, typename UnaryFunc>
  UnaryFunc For_Each(Iter iter_beg, Iter iter_end, UnaryFunc fn)
  {
    while (iter_beg != iter_end) 
      fn(*iter_beg++);
    
    return fn;
  }

  void increment_one(int& x) { ++x; }

  class Functor_1 {
  private:
    char m_ch;
  public:
    Functor_1(char ch) : m_ch{ ch } {}

    void operator()(std::string& str)
    {
      if (str[0] == m_ch)
        str[0] = std::toupper(str[0]);
    }
  };

  class Functor_2 {
  private:
    char  m_ch;
    int   m_cnt{};
  public:
    Functor_2(char ch) : m_ch{ ch } {}

    void operator()(std::string& str)
    {
      if (str[0] == m_ch) {
        str[0] = std::toupper(str[0]);
        ++m_cnt;
      }
    }
    int get_count() const
    {
      return m_cnt;
    }
  };

  int main()
  {
    using namespace std;

    // ----------------------------------------------------

    int i_arr[] = { 11, 22, 33, 44, 55, 66, 77, 88, 99};
    std::for_each(std::begin(i_arr), 
                  std::end(i_arr), 
                  &increment_one);

    for (auto elem : i_arr)
      std::cout << elem << ' ';
    // output -> 12 23 34 45 56 67 78 89 100

    std::cout << '\n';

    // ----------------------------------------------------

    vector<string> svec1{ 
      "yes", "no", "buy", "sell", "ying", "yang",
      "black", "white", "easy", "hard" };

    std::for_each(svec1.begin(), svec1.end(), Functor_1('y'));

    for (auto elem : svec1)
      std::cout << elem << ' ';
    // output -> Yes no buy sell Ying Yang black white easy hard

    std::cout << '\n';

    // ----------------------------------------------------

    vector<string> svec2{ 
      "yes", "no", "buy", "sell", "ying", "yang",
      "black", "white", "easy", "hard" };

    auto functor_2 = 
      std::for_each(svec2.begin(), svec2.end(), Functor_2('y'));


    std::cout << functor_2.get_count() 
              << " elements has been changed.\n";
    // output -> 3 elements has been changed.

    for (auto elem : svec2)
      std::cout << elem << ' ';
    // output -> Yes no buy sell Ying Yang black white easy hard

    // ----------------------------------------------------
  }
*/

/*
        -----------------------------------------------------
        | std::all_of, std::any_of, std::none_of algorithms |
        -----------------------------------------------------
*/

/*
  #include <vector>
  #include <algorithm>  // std::all_of, std:any_of, std::none_of

  int main()
  {
    using namespace std;
    cout << boolalpha;

    vector<int> ivec1{ 11, 22, 33, 44, 55, 66, 77, 88, 99 };
    vector<int> ivec2{ 10, 20, 30, 40, 50, 60, 70, 80, 90 };

    // --------------------------------------------------

    bool b1 = std::any_of(ivec1.begin(), 
                          ivec1.end(), 
                          [](int x) { return x % 2 != 0; });
    cout << b1 << '\n';   // output -> true

    bool b2 = std::any_of(ivec2.begin(), 
                          ivec2.end(), 
                          [](int x) { return x % 2 != 0; });
    cout << b2 << '\n';   // output -> false

    // --------------------------------------------------

    bool b3 = std::all_of(ivec1.begin(), 
                          ivec1.end(), 
                          [](int x) { return x % 2 == 0; });
    cout << b3 << '\n';   // output -> false

    bool b4 = std::all_of(ivec2.begin(), 
                          ivec2.end(), 
                          [](int x) { return x % 2 == 0; });
    cout << b4 << '\n';   // output -> true

    // --------------------------------------------------

    bool b5 = std::none_of(ivec1.begin(), 
                           ivec1.end(), 
                           [](int x) { return x % 2 != 0; });
    cout << b5 << '\n';   // output -> false

    bool b6 = std::none_of(ivec2.begin(), 
                           ivec2.end(), 
                           [](int x) { return x % 2 != 0; });
    cout << b6 << '\n';   // output -> true

    // --------------------------------------------------
  }
*/

/*
                  ------------------------------
                  | std::max_element algorithm |
                  ------------------------------
*/

/*
  // std::max_element returns an iterator to the element

  #include <vector>
  #include <string>
  #include <algorithm>  // std::max_element
  #include <iterator>   // std::distance

  int main()
  {
    using namespace std;

    vector<string> svec{ 
      "hello", "is", "this", "sparta", "am", 
      "I", "in", "wrong", "place"};

    auto iter = std::max_element(svec.begin(), svec.end());

    cout << "max_element = " << *iter << " , idx = " 
         << distance(svec.begin(), iter) << '\n';
    // output -> max_element = wrong , idx = 7
    // (lexicographical compare)

    cout << "iter->size() = " << iter->size() << '\n';
    // output -> iter->size() = 5
  }
*/

/*
                ---------------------------------
                | std::minmax_element algorithm |
                ---------------------------------
*/


/*
  // return type of std::minmax_element is an iterator pair

  #include <algorithm>  // std::minmax_element
  #include <vector>
  #include <string>
  #include <iterator>   // std::distance

  int main()
  {
    using namespace std;

    vector<string> svec{ 
      "hello", "is", "this", "sparta", "am", 
      "I", "in", "wrong", "place"};

    auto iter_pair = std::minmax_element(svec.begin(), svec.end());
    // iter_pair's type is 
    // pair<vector<string>::iterator, vector<string>::iterator> 

    cout  << "min element = " << *iter_pair.first 
          << ", max element  = " << *iter_pair.second << '\n';
    // output -> min element = I, max element  = wrong

    // --------------------------------------------------------

    // splitting elements of the pair in old C++
    auto old_iter_min = iter_pair.first;
    auto old_iter_max = iter_pair.second;

    // --------------------------------------------------------

    // splitting elements of the pair with structured binding

    auto [iter_min, iter_max] = 
      std::minmax_element(svec.begin(), svec.end());

    cout  << "min idx = " 
          << std::distance(svec.begin(), iter_min) 
          << ", min element = " << *iter_min << '\n';

    // output -> min idx = 5, min element = I

    cout  << "max idx = " 
          << std::distance(svec.begin(), iter_max) 
          << ", max element = " << *iter_max << '\n';
    // output -> max idx = 7, max element = wrong

    // --------------------------------------------------------
  }
*/

/*
            -------------------------------------------
            | std::replace, std::replace_if algorithm |
            -------------------------------------------
*/

/*
  #include <vector>
  #include <algorithm>    // std::replace, std::replace_if
  #include <functional>
  #include <string>

  int main()
  {
    std::vector<int> ivec{ 
      3, 3, 1, 2, 4, 1, 0, 2, 3, 2, 4, 3, 1, 2 };

    // ----------------------------------------------------
    
    std::replace( ivec.begin(), ivec.end(), 3, 7);
    // replacing all 3's with 7's

    for (int elem : ivec)
      std::cout << elem << ' ';
    // output -> 7 7 1 2 4 1 0 2 7 2 4 7 1 2
    std::cout << '\n';

    // ----------------------------------------------------

    std::replace_if(ivec.begin(), ivec.end(),         
                    [](int a) { return a % 2 == 0; }, 0);
    // replacing even numbers with 0's

    for (int elem : ivec)
      std::cout << elem << ' ';
    // output -> 7 7 1 0 0 1 0 0 7 0 0 7 1 0  
    std::cout << '\n';

    // ----------------------------------------------------

    std::vector<std::string> svec{ 
      "red", "green", "blue", "hey", "istanbul", "ankara" };

    std::replace_if(svec.begin(), svec.end(), 
                    [](const std::string& s) {
                      return s.length() == 3; 
                    }, "***");
    // replacing strings that have 3 characters with "***"

    for (auto elem : svec)
      std::cout << elem << ' ';
    // output -> *** green blue *** istanbul ankara
    std::cout << '\n';

    // ----------------------------------------------------
  }
*/

/*
          ---------------------------------------------
          | std::reverse, std::reverse_copy algorithm |
          ---------------------------------------------
*/


/*
  #include <vector>
  #include <algorithm>  // std::reverse, std::reverse_copy
  #include <string>
  #include <list>
  #include <iterator>   // std::back_inserter

  int main()
  {
    // -------------------------------------------------------

    std::vector<std::string> svec1{ 
      "red", "green", "blue", "hey", "istanbul", "ankara" };

    std::reverse(svec1.begin(), svec1.end());

    for (auto elem : svec1)
      std::cout << elem << ' ';
    // output -> ankara istanbul hey blue green red
    std::cout << '\n';

    // -------------------------------------------------------

    std::vector<std::string> svec2{ 
      "red", "green", "blue", "hey", "istanbul", "ankara" };

    std::list<std::string> slist;

    std::reverse_copy(svec2.begin(), svec2.end(),   // source
                      back_inserter(slist));        // destination

    for (auto elem : slist)
      std::cout << elem << ' ';
    // output -> ankara istanbul hey blue green red
    std::cout << '\n';

    // -------------------------------------------------------
  }
*/

/*
        ---------------------------------------------------
        | std::remove_copy, std::remove_copy_if algorithm |
        ---------------------------------------------------
*/

/*
  #include <vector>
  #include <algorithm>  // std::remove_copy, std::remove_copy_if
  #include <iterator>   // std::back_inserter

  int main()
  {
    std::vector<int> ivec{ 
        3, 3, 1, 2, 4, 1, 0, 2, 3, 2, 4, 3, 1, 2 };

    std::vector<int> dest_vec;

    std::remove_copy( ivec.begin(), ivec.end(), 
                      std::back_inserter(dest_vec), 3);
    // removing all 3's and copying the rest to dest_vec

    for (auto elem : dest_vec)
      std::cout << elem << ' ';
    // output -> 1 2 4 1 0 2 2 4 1 2
    std::cout << '\n';

    // ------------------------------------------------------

    std::vector<std::string> svec{ 
        "red", "green", "blue", "hey", "istanbul", "ankara" };

    std::vector<std::string> dest_svec;
    
    std::remove_copy_if(svec.begin(), svec.end(),
                        std::back_inserter(dest_svec),
                        [](const std::string& str){
                      return str.find('a') != std::string::npos;
                    });
    // removing all strings that have 'a' character 
    // and copying the rest to dest_svec

    for (auto elem : dest_svec)
      std::cout << elem << ' ';
    // output -> red green blue hey
    std::cout << '\n';
    

    // ------------------------------------------------------
    
    // std::string class has a "contains" member function (C++23) 

    std::vector<std::string> svec2{ 
        "red", "green", "blue", "hey", "istanbul", "ankara" };

    std::vector<std::string> dest_svec2;

    std::remove_copy_if(svec2.begin(), svec2.end(),
                        std::back_inserter(dest_svec2),
                        [](const std::string& str){
                      return str.contains('a');
                    });

    for (auto elem : dest_svec2)
      std::cout << elem << ' ';
    // output -> red green blue hey

    // ------------------------------------------------------
  }
*/

/*
            ------------------------------------------
            | std::lexicographical_compare algorithm |
            ------------------------------------------
*/

/*
  ------------------------------------------------------------

  - containers default comparison is lexicographical compare.

  - containers are equal if 
    element counts are equal 
    elements are same 

  ------------------------------------------------------------

  1st container -> 5 6 7 2 5 5 3 2
  2nd container -> 7

  2nd container > 1st container (lexicographical compare)
    2nd container's first element(7) is bigger than 
    1st container's first element(5).

  ------------------------------------------------------------

  1st container -> 5 3 4 5
  2nd container -> 5 3 4 5 6

  2nd container > 1st container (lexicographical compare)
    first 4 elements are same but 2nd container 
    has one more element so it is bigger than 1st container.

  ------------------------------------------------------------

  1st container -> "z"
  2nd container -> "abc"

  1st container > 2nd container (lexicographical compare)
    1st containers first element('z') is bigger than 
    2nd containers first element('a').

  ------------------------------------------------------------

  1st container -> "hello"
  2nd container -> "helloworld"

  2nd container > 1st container (lexicographical compare)
    first 5 elements are same but 2nd container
    has more elements so it is bigger than 1st container.

  ------------------------------------------------------------
*/

/*
  #include <vector>

  int main()
  {
    std::cout << std::boolalpha;

    std::vector<int> ivec_1(100'000, 11);
    std::cout << "ivec_1.size() = " 
              << ivec_1.size() << '\n';
    // output -> ivec_1.size() = 100000

    std::vector<int> ivec_2{ 99 };
    std::cout << "ivec_2.size() = " 
              << ivec_2.size() << '\n';
    // output -> ivec_2.size() = 1

    std::cout << (ivec_1 > ivec_2);   // output -> false

    // ivec_2 containers first element(99) is bigger than 
    // ivec_1 containers first element(11)
    // ivec_2 > ivec_1 (lexicographical compare)
  }
*/

/*
  #include <vector>
  #include <list>
  #include <algorithm>    // std::lexicographical_compare
  #include <functional>   // std::greater

  int main()
  {
    std::cout << std::boolalpha;

    std::vector<int> ivec{ 11, 22, 33, 33 };
    std::list<int> ilist{ 11, 22, 33, 44 };

    // ----------------------------------------------------

    //ivec < ilist; // syntax error
    // error: no match for 'operator<' 
    // (operand types are 'std::vector<int>' and 'std::list<int>')

    // ----------------------------------------------------

    auto b1 = std::lexicographical_compare(
          ivec.begin(), ivec.end(),       // 1st container
          ilist.begin(), ilist.end());    // 2nd container
    // both container's first 3 elements are same
    // 1st container's 4th element(33) is less than 
    // 2nd container's 4th element(44)
    // 1st container < 2nd container (lexicographical compare)

    // because of default binary predicate is std::less
    // function will return true.

    std::cout << b1 << '\n';  // output -> true

    // ----------------------------------------------------

    auto b2 = lexicographical_compare(
        ivec.begin(), ivec.end(), 
        ilist.begin(), ilist.end(), std::greater{});

    std::cout << b2 << '\n';  // output -> false

    // ----------------------------------------------------
  }
*/

/*
                  -----------------------------
                  | std::generate_n algorithm |
                  -----------------------------
*/

/*
  #include <algorithm>  // std::generate_n
  #include <vector>
  #include <cstdlib>    // std::rand
  #include <random>     
  // std::mt19937, std::uniform_int_distribution

  int foo(){ return 11; }

  int main()
  {
    std::vector<int> ivec(10);

    // --------------------------------------------------

    std::generate_n(ivec.begin(), 10, &foo);

    for (auto elem : ivec)
      std::cout << elem << ' ';
    // output -> 11 11 11 11 11 11 11 11 11 11
    std::cout << '\n';

    // --------------------------------------------------

    std::generate_n(ivec.begin(), 10, 
                    []{ return std::rand() % 1000; });

    for (auto elem : ivec)
      std::cout << elem << ' ';
    // output -> 41 467 334 500 169 724 478 358 962 464
    std::cout << '\n';

    // --------------------------------------------------

    std::mt19937 eng;
    std::uniform_int_distribution dist{ 0, 100 };

    std::generate_n(ivec.begin(), 10, 
                    [&eng, &dist]{ return dist(eng); });

    for (auto elem : ivec)
      std::cout << elem << ' ';
    // output -> 82 13 91 84 12 97 92 22 63 31
    std::cout << '\n';

    // --------------------------------------------------
  }
*/

/*
            ------------------------------------------
            | std::remove, std::remove_if algorithms |
            ------------------------------------------
*/

/*
  // std::vector's size is not changed when "std::remove"
  // algorithm is being used. (logic remove operation)

  #include <vector>
  #include <algorithm>

  int main()
  {
    std::vector<int> ivec{ 1, 2, 4, 3, 3, 2, 1, 4, 5 };
    std::cout << "ivec.size() = " << ivec.size() << '\n';	
    // output -> ivec.size() = 9

    for (auto elem : ivec)
      std::cout << elem << ' ';
    // output -> 1 2 4 2 1 4 5 4 5
    std::cout << '\n';

    std::cout << "ivec.size() = " << ivec.size() << '\n';
    // output -> ivec.size() = 9
  }
*/

/*
  #include <vector>
  #include <algorithm>    // std::remove, std::for_each
  #include <iterator>     // std::distance

  int main()
  {
    // When (3's) are removed from the container, 
    // 1232432352314312
    // 12242521412|
    //            returns an iterator to ('|') position (logic_end)


    std::vector<int> ivec{ 
      1, 2, 3, 2, 4, 3, 2, 3, 5, 2, 3, 1, 4, 3, 1, 2 };

    std::cout << "ivec.size() = " << ivec.size() << '\n';
    // output -> ivec.size() = 16

    auto logic_end = std::remove(ivec.begin(), ivec.end(), 3);

    auto stay_elem_count = std::distance(ivec.begin(), logic_end);
    std::cout << "element count that will not deleted = " 
              << stay_elem_count << '\n';
    // output -> element count that will not deleted = 11

    auto delete_elem_count = distance(logic_end, ivec.end());
    std::cout << "element count that will be deleted = "
              << delete_elem_count << '\n';
    // output -> element count that will be deleted = 5

    std::for_each(ivec.begin(), logic_end,      // source
                  [](int x) { std::cout << x << ' '; });
    std::cout << '\n';
    // output -> 1 2 2 4 2 5 2 1 4 1 2

    ivec.erase(logic_end, ivec.end());
    // range parameter "erase" member function

    std::cout << "ivec.size() = " << ivec.size() << '\n';
    // output -> ivec.size() = 11

    ivec.shrink_to_fit();
    std::cout << "ivec.capacity() = " << ivec.capacity() << '\n';
    // output -> ivec.capacity() = 11
  }
*/

/*
                      ----------------------
                      | remove-erase idiom |
                      ----------------------
*/

/*
  #include <vector>       // std::erase(vector)
  #include <algorithm>    // std::remove

  int main()
  {
    // -------------------------------------------------------

    // remove-erase idiom before C++20 

    std::vector<int> ivec1{ 
      1, 2, 3, 2, 4, 3, 2, 3, 5, 2, 3, 1, 4, 3, 1, 2 };

    std::cout << "ivec1.size() = " << ivec1.size() << '\n';
    // output -> ivec1.size() = 16

    ivec1.erase(std::remove(ivec1.begin(), ivec1.end(), 3), 
                ivec1.end());
    // remove-erase idiom

    std::cout << "ivec1.size() = " << ivec1.size() << '\n';
    // output -> ivec1.size() = 11

    // -------------------------------------------------------

    // remove-erase idiom since C++20

    std::vector<int> ivec2{ 
      1, 2, 3, 2, 4, 3, 2, 3, 5, 2, 3, 1, 4, 3, 1, 2 };

    std::cout << "ivec2.size() = " << ivec2.size() << '\n';
    // output -> ivec2.size() = 16

    auto delete_elem_count = std::erase(ivec2, 3);
    std::cout << "element count that will be deleted = "
          << delete_elem_count << '\n';
    // output -> element count that will be deleted = 5

    std::cout << "ivec2.size() = " << ivec2.size() << '\n';
    // output -> ivec2.size() = 11

    // -------------------------------------------------------
  }
*/

/*
  #include <algorithm>  // std::generate_n
  #include <vector>
  #include <iterator>   // std::back_inserter
  #include <random>     
  // std::mt19937, std::uniform_int_distribution

  int main()
  {
    std::vector<int> ivec;
    std::mt19937 eng;
    std::uniform_int_distribution dist{ 1, 5 };
    // vector will contain {1, 2, 3, 4, 5}

    std::generate_n(std::back_inserter(ivec), 
                    1000, 
                    [&] {return dist(eng); });

    std::cout << "ivec.size() = " << ivec.size() << '\n';
    // output -> ivec.size() = 1000

    ivec.erase( std::remove_if( ivec.begin(), ivec.end(), 
                                [](int x){ return x > 3; }), 
                              ivec.end());
    // (4) and (5)'s in the vector will be removed.
    // remove-erase idiom

    std::cout << "ivec.size() = " << ivec.size() << '\n';
    // output -> ivec.size() = 609
  }
*/  

/*
  #include <algorithm>    
  // std::generate_n, std::remove, std::for_each
  #include <iterator>     // std::back_inserter
  #include <vector>
  #include <random>

  int main()
  {
    std::vector<int> ivec;

    std::generate_n(std::back_inserter(ivec),     // destination
                    10,                           // elem count
                    [&]{ return rand() % 4; });   // predicate

    auto iter_logic_end = std::remove(ivec.begin(), ivec.end(), 2);
    // remove all of the 2's from the vector

    // ----------------------------------------------------

    std::for_each(
      ivec.begin(), iter_logic_end,             // source
      [](int x){ std::cout << x << ' '; });     // predicate
    // output -> 1 3 0 1 0 0
    // elements have not been removed [ivec.begin(), logic_end]

    std::cout << '\n';

    // ----------------------------------------------------

    std::for_each(
          iter_logic_end, ivec.end(),             // source
          [](int x){ std::cout << x << ' '; });   // predicate
    // output -> 2 2 2 0
    // elements have been removed [logic_end, ivec.end]

    // reading from [logic_end, ivec.end] is NOT UB.
    // but there is no guarantee that all elements are (2)'s.

    // ----------------------------------------------------
  }
*/

/*
  #include <algorithm>  // std::remove_if
  #include <string>     // std::erase_if(std::string)

  int main()
  {
    // ----------------------------------------------------------

    // before C++20

    std::string str{ 
        "istanbul, ankara, izmir, eskisehir, rize, trabzon" };

    // (aeoiu) : wanted to remove those character

    str.erase(std::remove_if( 
                  str.begin(), str.end(),    // source 
                  [](char ch){
      return std::string{ "aeoui" }.find(ch) != std::string::npos; }), 
              str.end());

    std::cout << str << '\n';
    // output -> stnbl, nkr, zmr, skshr, rz, trbzn
    // ----------------------------------------------------------

    // since C++20 - std::erase_if(std::string)

    std::string str2{ 
      "istanbul, ankara, izmir, eskisehir, rize, trabzon" };


    std::erase_if(str2, 
                  [](char ch){ 
      return std::string{ "aeoui" }.find(ch) != std::string::npos; });

    std::cout << str2 << '\n';
    // output -> stnbl, nkr, zmr, skshr, rz, trbzn

    // ----------------------------------------------------------
  }
*/

/*
                    -------------------------
                    | std::unique algorithm |
                    -------------------------
*/

/*
  // 33344466669999111233334555511118888999222333
  // 34691234518923
  // defaul binary predicate(function object) is std::equal_to

  #include <algorithm>  // std::unique
  #include <vector>

  int main()
  {
    std::vector<int> ivec{ 
      3, 3, 3, 4, 4, 4, 6, 6, 6, 6, 9, 9, 9, 9, 1, 1, 1, 2, 3, 
      3, 3, 3, 4, 5, 5, 5, 5, 1, 1, 1, 1, 8, 8, 8, 8, 9, 9, 9, 
      2, 2, 2, 3, 3, 3 };

    std::cout << "ivec.size() = " << ivec.size() << '\n';
    // output -> ivec.size() = 44

    ivec.erase(std::unique(ivec.begin(), ivec.end()), ivec.end());

    for (auto elem : ivec)
      std::cout << elem << ' ';
    // output -> 3 4 6 9 1 2 3 4 5 1 8 9 2 3
    std::cout << '\n';

    std::cout << "ivec.size() = " << ivec.size() << '\n';
    // output -> ivec.size() = 14
  }
*/

/*
  if std::vector's elements wants to be unique and 
  ordered in ascending order,
    - can be sorted ans then unique algorithm can be used.
    - can be sent to std::set(only contains unique keys) 
      set's elements assigned back to vector and sort it.
*/

/*
  #include <string>
  #include <vector>
  #include <algorithm>    // std::unique

  int main()
  {
    using namespace std;

    // --------------------------------------------------------

    vector<string> svec{ "a", "b", "c", 
      "ab", "ac", "cd", "abc", "bcd", "efg", "hij",
      "abcd", "bcde", "cdef", "defg", "efgh", "fghi",
      "abcde", "bcdef", "cdefg", "defgh", "efghi", "fghij" };

    svec.erase( unique( svec.begin(), svec.end(),   
                        [](const string& s1, const string& s2) {
                      return s1.length() == s2.length();}),
                svec.end());
    // removing all same length strings except first one.

    for (auto str : svec)
      cout << str << ' ';
    // output -> a ab abc abcd abcde

    cout << '\n';

    // --------------------------------------------------------

    vector<string> svec2{ "b", "a", "c", 
      "ab", "ac", "cd", "abc", "bcd", "efg", "hij",
      "abcd", "bcde", "cdef", "defg", "efgh", "fghi",
      "abcde", "bcdef", "cdefg", "defgh", "efghi", "fghij" };

    svec2.erase( unique(svec2.begin(), svec2.end(), 
                [](const string& s1, const string& s2) {
               return s1.front() != s2.front();
      }), svec2.end());
    // removing all strings except strings that have 
    // different first character from the first string.

    for (auto str : svec2)
      cout << str << ' ';
    // output -> b bcd bcde bcdef

    // --------------------------------------------------------
  }
*/

/*
                      ----------------------
                      | sorting algorithms |
                      ----------------------
*/

/*
                      -----------------------
                      | std::sort algorithm |
                      -----------------------
*/

/*
  #include <algorithm>  // std::sort
  #include <vector>
  #include <cmath>      // std::abs

  int main()
  {
    std::vector<int> ivec{ 9, -5, 8, -4, 7, -3, 6, -2, -1, 0};

    // -------------------------------------------------------

    std::sort(ivec.begin(), ivec.end());

    for (auto elem : ivec)
      std::cout << elem << ' ';
    // output -> -5 -4 -3 -2 -1 0 6 7 8 9
    std::cout << '\n';

    // -------------------------------------------------------

    std::sort(ivec.begin(), ivec.end(),
              [](int x, int y){ 
            return std::abs(x) < std::abs(y);
          });

    for (auto elem : ivec)
      std::cout << elem << ' ';
    // output -> 0 -1 -2 -3 -4 -5 6 7 8 9
    std::cout << '\n';

    // -------------------------------------------------------
  }
*/

/*
  #include <vector>
  #include <string>
  #include <algorithm>    // std::sort
  #include <functional>   // std::less

  int main()
  {
    using namespace std;

    vector<string> svec{ "istanbul", "ankara", "izmir", 
      "bursa", "eskisehir", "adana", "rize", "trabzon", 
      samsun", "konya" };

    // -------------------------------------------------------

    std::sort(svec.begin(), svec.end());

    for (auto str : svec)
      std::cout << str << ' ';
    // output ->
    //  adana ankara bursa eskisehir istanbul  
    //  izmir konya rize samsun trabzon
    std::cout << '\n';

    // -------------------------------------------------------

    std::sort(svec.rbegin(), svec.rend());

    for (auto str : svec)
      std::cout << str << ' ';
    // output ->
    //  trabzon samsun rize konya izmir istanbul
    //  eskisehir bursa ankara adana
    std::cout << '\n';

    // -------------------------------------------------------
    
    std::sort(svec.begin(), svec.end(), std::less<string>{});
    std::sort(svec.begin(), svec.end(), std::less{});
    // Those 2 lines are equivalent.

    for (auto i : svec)
      std::cout << i << ' ';
    // output ->
    //  adana ankara bursa eskisehir istanbul 
    //  izmir konya rize samsun trabzon
    std::cout << '\n';

    // -------------------------------------------------------

    const auto fn = [](const string& s1, const string& s2){
      return s1.length() < s2.length() || 
            (s1.length() == s2.length() && s1 < s2);
    };

    std::sort(svec.begin(), svec.end(), fn);

    for (auto i : svec)
      std::cout << i << ' ';
    // output ->
    //  rize adana bursa izmir konya ankara  
    //  samsun trabzon istanbul eskisehir
    std::cout << '\n';

    // -------------------------------------------------------
  }
*/

/*
  - std::vector, 
  - std::deque, 
  - std::string, 
  - std::array, 
  - C-style arrays 
  can be used in std::sort algorithm.
*/

/*
  #include <string>
  #include <algorithm>    // std::sort
  #include <functional>   // std::greater

  int main()
  {
    std::string str{ "istanbul, ankara, izmir, eskisehir" };

    // ---------------------------------------------------

    std::sort(str.begin(), str.end());
    std::cout << '[' << str << "]\n";
    // output -> [   ,,,aaaabeehiiiiikklmnnrrrssstuz]

    // ---------------------------------------------------

    std::sort(str.begin(), str.end(), std::greater{});
    std::cout << '[' << str << "]\n";
    // output -> [zutsssrrrnnmlkkiiiiiheebaaaa,,,   ] 

    // ---------------------------------------------------
  }
*/

/*
  ------------------------------------------------------
  before sort
  ------------------------------------------------------
  ali 15
  ali 26
  ayse 29
  mehmet 17
  ali 24
  ayse 43
  mehmet 39
  mehmet 27

  ------------------------------------------------------
  unstable sort (kararsız) (numbers are also sorted)
  ------------------------------------------------------
  ali 15
  ali 24
  ali 26
  ayse 29
  ayse 43
  mehmet 17
  mehmet 27
  mehmet 39

  - unstable sort will sort the elements 
    but if elements hiearachies are same,
    there is NO guarantee that those elements
    will be ordered as same as before the sorting operation
  ------------------------------------------------------

  ------------------------------------------------------
  stable sort (kararlı) (numbers are NOT sorted) 
  ------------------------------------------------------
  ali 15
  ali 26
  ali 24
  ayse 29
  ayse 43
  mehmet 17
  mehmet 39
  mehmet 27

  - stable sort will sort the elements,
    and if elements hiearchies are same,
    it is guaranteed that those elements 
    will be ordered as same as before the sorting operation
  ------------------------------------------------------
  ------------------------------------------------------
*/

/*
  #include <vector>     // std::size
  #include <utility>    // std::pair, std::make_pair
  #include <string>
  #include <cstddef>    // std::size_t
  #include <cstdlib>    // std::rand
  #include <algorithm>  // std::sort, std::stable_sort

  using str_int_pair = std::pair<std::string, int>;

  void print_vec(const std::vector<str_int_pair>& si_vec)
  {
    for (const auto& [str, val] : si_vec)
      std::cout << "str = " << str << ", age = " << val << '\n';

    std::cout << "------------------------------------\n";
  }

  int main()
  {
    const std::string str_arr[]{ "istanbul", "ankara", "izmir" };
    const int age_arr[]{ 11, 22, 33, 44, 55, 66 };

    std::vector<str_int_pair> si_vec;
    si_vec.reserve(20);

    for (size_t i = 0; i < 20; i++)
      si_vec.push_back( std::make_pair( 
                          str_arr[rand() % std::size(str_arr)], 
                          age_arr[rand() % std::size(age_arr)]));

    std::sort(si_vec.begin(), si_vec.end());
    print_vec(si_vec);

    // output (BEFORE SORT) ->
    //  str = ankara, age = 44
    //  str = ankara, age = 55
    //  str = ankara, age = 55
    //  str = ankara, age = 66
    //  str = ankara, age = 66
    //  str = istanbul, age = 11
    //  str = istanbul, age = 22
    //  str = istanbul, age = 22
    //  str = istanbul, age = 33
    //  str = istanbul, age = 44
    //  str = istanbul, age = 44
    //  str = istanbul, age = 66
    //  str = istanbul, age = 66
    //  str = izmir, age = 22
    //  str = izmir, age = 22
    //  str = izmir, age = 33
    //  str = izmir, age = 44
    //  str = izmir, age = 55
    //  str = izmir, age = 66
    //  str = izmir, age = 66

    // -----------------------------------------------------
    
    // unstable sort
    std::sort(si_vec.begin(), si_vec.end(), 
              [](const auto& p1, const auto& p2){
        return p1.second < p2.second;
      });

    print_vec(si_vec);

    // output (UNSTABLE SORT) ->
    //  str = istanbul, age = 11
    //  str = istanbul, age = 22
    //  str = istanbul, age = 22
    //  str = izmir, age = 22
    //  str = izmir, age = 22
    //  str = izmir, age = 33     ---> unstable sort
    //  str = istanbul, age = 33  ---> unstable sort
    //  str = istanbul, age = 44
    //  str = ankara, age = 44
    //  str = izmir, age = 44
    //  str = istanbul, age = 44
    //  str = ankara, age = 55
    //  str = izmir, age = 55
    //  str = ankara, age = 55
    //  str = izmir, age = 66
    //  str = izmir, age = 66
    //  str = istanbul, age = 66
    //  str = istanbul, age = 66
    //  str = ankara, age = 66
    //  str = ankara, age = 66

    // -----------------------------------------------------

    std::sort(si_vec.begin(), si_vec.end());

    std::stable_sort(si_vec.begin(), si_vec.end(), 
                      [](const auto& p1, const auto& p2){
        return p1.second < p2.second;
      });

    print_vec(si_vec);

    // output (STABLE SORT) ->
    //  str = istanbul, age = 11
    //  str = istanbul, age = 22
    //  str = istanbul, age = 22
    //  str = izmir, age = 22
    //  str = izmir, age = 22
    //  str = istanbul, age = 33    ---> stable sort
    //  str = izmir, age = 33       ---> stable sort
    //  str = ankara, age = 44
    //  str = istanbul, age = 44
    //  str = istanbul, age = 44
    //  str = izmir, age = 44
    //  str = ankara, age = 55
    //  str = ankara, age = 55
    //  str = izmir, age = 55
    //  str = ankara, age = 66
    //  str = ankara, age = 66
    //  str = istanbul, age = 66
    //  str = istanbul, age = 66
    //  str = izmir, age = 66
    //  str = izmir, age = 66

    // -----------------------------------------------------
  }
*/

/*
  partial sort algorithm :
    i.e : had a 100k students with their exam results
          only the best(exam result) 20 student needed
    sorting 100k students and getting first 20 is inefficient.
*/

/*
  #include <vector>     // std::size
  #include <string>
  #include <algorithm>  // std::partial_sort
  #include <cstdlib>    // std::rand
  #include <cstddef>    // std::size_t
  #include <iterator>   // std::next

  int main()
  {
    std::vector<std::string> svec;
    svec.reserve(100);

    const std::string str_arr[]{ 
      "ali", "ayse", "mehmet", "sadik", "ceyda", "cemile", 
      "baran", "faruk", "zehra", "kerem", "tevfik", "sergen", 
      "sibel", "kamil"};

    for (std::size_t i = 0; i < 100; i++) {
      svec.push_back( str_arr[rand() % std::size(str_arr)] + " " + 
                      str_arr[rand() % size(str_arr)]);
    }

    // -----------------------------------------------------
    
    std::partial_sort(svec.begin(), 
                      std::next(svec.begin(), 5), 
                      svec.end());
    // only sorting first 5 elements.

    for (auto str : svec)
      std::cout << str << '\n';
    std::cout << '\n';

    // output ->
    //  ali cemile      --> sorted area starts
    //  ali kamil
    //  ali kerem
    //  ali sibel
    //  ali zehra
    //  sibel baran     --> unsorted area starts
    //  mehmet sadik
    //  kamil kamil
    //  cemile faruk
    //  ceyda sergen
    //  mehmet kerem
    //  ...

    // -----------------------------------------------------

    std::vector<std::string> dest_vec(5);

    std::partial_sort_copy( svec.begin(), svec.end(), 
                            dest_vec.begin(), dest_vec.end());

    for (auto str : dest_vec)
      std::cout << str << '\n';

    // output ->
    //  ali cemile
    //  ali kamil
    //  ali kerem
    //  ali sibel
    //  ali zehra

    // -----------------------------------------------------
  }
*/

/*
                    -------------------------
                    | nth_element algorithm |
                    -------------------------
*/

/*
  #include <vector>
  #include <string>
  #include <algorithm>  // std::generate, std::nth_element
  #include <random>   
  // std::mt19937, std::uniform_int_distribution

  int main()
  {
    std::mt19937 eng;
    std::uniform_int_distribution dist{ 0, 10000 };

    std::vector<int> ivec(11);
    std::generate(ivec.begin(), ivec.end(), 
                  [&](){ return dist(eng); });

    for (auto elem : ivec)
      std::cout << elem << ' ';
    // output ->
    //  8148 1354 9058 8350 1269 9689 9134 2210 6324 3081 975
    std::cout << '\n';

    std::nth_element( ivec.begin(),                   
                      ivec.begin() + ivec.size() / 2,
                      ivec.end());                   

    // elements before nth_element(in this case middle element) 
    // needs to be smaller than nth_element,
    // elements after nth_element needs to be bigger than 
    // nth element.
    // which basically means, putting the median element
    // to the middle of the container.

    
    for (auto elem : ivec)
      std::cout << elem << ' ';
    // output ->
    //  1354 975 1269 3081 2210 6324 8148 9134 9689 9058 8350
    std::cout << '\n';
      
    std::cout << "median = " << ivec[ivec.size() / 2] << '\n';
    // output -> median = 6324
  }
*/

/*
                    ----------------------------
                    | std::partition algorithm |
                    ----------------------------
*/

/*
  #include <random>   
  // std::mt19937, std::uniform_int_distribution
  #include <vector>
  #include <algorithm>  // std::generate, std::partition

  int main()
  {
    using namespace std;

    std::mt19937 eng;
    std::uniform_int_distribution dist{ 0, 100 };

    std::vector<int> ivec(30);
    std::generate(ivec.begin(), ivec.end(), 
                  [&](){ return dist(eng); });

    auto p_iter = std::partition( ivec.begin(), ivec.end(), 
                                  [](int a){ return a % 2 != 0; });

    for (auto elem : ivec)
      cout << elem << ' ';
    // output -> 
    //  29 13 91 49 11 97 99 73 63 31 9 55 15 19 55 97 97
    //  (100) 96 100 28 22 98 92 96 12 84 80 80 82
    cout << '\n';

    if (p_iter != ivec.end())
      cout << "partition point = " << *p_iter << '\n';
    // output -> partition point = 100

    // odd elements range -> [ivec.begin(), p_iter)
    // even elements range -> [p_iter, ivec.end())
  }
*/

/*
                -----------------------------------
                | std::stable_partition algorithm |
                -----------------------------------
*/

/*
  #include <algorithm>  
  // std::generate, std::sort, std::partition,
  // std::stable_partition
  #include <vector>
  #include <random>
  // std::mt19937, std::uniform_int_distribution

  int main()
  {
    std::mt19937 eng;
    std::uniform_int_distribution dist{ 0, 200 };

    std::vector<int> ivec(100);
    std::generate(ivec.begin(), ivec.end(), 
                  [&](){ return dist(eng); });

    // -------------------------------------------------------

    std::sort(ivec.begin(), ivec.end());

    auto p_iter = std::partition(ivec.begin(), ivec.end(), 
                                [](int a){ return a >= 100; });

    for (auto elem : ivec)
      std::cout << elem << ' ';
    // output -> 
    //  200 199 199 197 195 194 194 193 192 192 192 190 187 
    //  185 184 183 182 176 175 170 167 165 165 163 162 160 
    //  160 160 160 159 159 159 153 153 152 151 149 148 145 
    //  142 141 139 136 136 133 131 131 101 109 109 127 128 
    //  129 (98) 98 98 97 95 92 89 88 84 84 82 80 78 76 72 63 
    //  63 61 60 59 55 55 44 42 42 37 37 34 34 31 29 28 27 
    //  25 25 25 22 22 19 19 10 9 7 7 6 6 0
    std::cout << '\n';

    if (p_iter != ivec.end())
      std::cout << "partition point = " << *p_iter << '\n';
    // output -> partition point = 98

    // std::partition algorithm is not a stable algorithm.

    // -------------------------------------------------------

    std::sort(ivec.begin(), ivec.end());

    p_iter = std::stable_partition(ivec.begin(), ivec.end(), 
                                  [](int a){ return a >= 100; });

    for (auto elem : ivec)
      std::cout << elem << ' ';
    // output ->
    //  101 109 109 127 128 129 131 131 133 136 136 139 141 
    //  142 145 148 149 151 152 153 153 159 159 159 160 160 
    //  160 160 162 163 165 165 167 170 175 176 182 183 184 
    //  185 187 190 192 192 192 193 194 194 195 197 199 199 200 
    //  (0) 6 6 7 7 9 10 19 19 22 22 25 25 25 27 28 29 31 34 34 
    //  37 37 42 42 44 55 55 59 60 61 63 63 72 76 78 80 82 84 
    //  84 88 89 92 95 97 98 98 98
    std::cout << '\n';

    std::cout << "partition point = " << *p_iter << '\n';
    // output -> partition point = 0

    // std::stable_partition algorithm is a stable algorithm.

    // -------------------------------------------------------
  }
*/

/*
                ---------------------------------
                | std::partition_copy algorithm |
                ---------------------------------
*/

/*
  // std::partition_copy function's return type is 
  // std::pair<iterator, iterator>

  #include <algorithm>  // std::generate
  #include <vector>
  #include <deque>
  #include <list>
  #include <iterator>   // std::back_inserter
  #include <random>
  // std::mt19937, std::uniform_int_distribution

  int main()
  {
    std::mt19937 eng;
    std::uniform_int_distribution dist{ 0, 200 };

    std::vector<int> ivec(30);
    std::generate(ivec.begin(), ivec.end(), 
                  [&]() { return dist(eng); });

    std::deque<int> i_deque;
    std::list<int> i_list;

    auto [p_deque_iter, p_list_iter] = 
        std::partition_copy(ivec.begin(), ivec.end(), 
                            std::back_inserter(i_deque), 
                            std::back_inserter(i_list), 
                            [](int a){ return a >= 100; });

    // ----------------------------------------------------

    std::cout << "std::deque<int> i_deque = \n";
    for (auto elem : i_deque)
      std::cout << elem << ' ';
    std::cout << '\n';

    // output ->
    //  std::deque<int> i_deque =
    //  163 182 167 194 183 127 109 109 199 
    //  192 200 193 194 145 195 197 192 160 160

    // ----------------------------------------------------

    std::cout << "std::list<int> i_list = \n";
    for (auto elem : i_list)
      std::cout << elem << ' ';
    // output -> 
    //  std::list<int> i_list =
    //  27 25 44 61 19 55 37 31 22 97 59

    // ----------------------------------------------------
  }
*/

/*
        ---------------------------------------------------
        | std::is_sorted, std::is_sorted_until algorithms |
        ---------------------------------------------------
*/

/*
  #include <algorithm>    // std::is_sorted, std::is_sorted_until
  #include <functional>   // std::greater(function object)

  int main()
  {
    using namespace std;
    cout << boolalpha;

    // -------------------------------------------------------

    int i_arr1[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    int i_arr2[]{ 99, 33, 22, 11, 0, -11 -22, -44 };

    cout << std::is_sorted(begin(i_arr1), end(i_arr1)) << '\n';
    // output -> true

    cout << std::is_sorted(begin(i_arr2), end(i_arr2)) << '\n';
    // output -> false

    cout << std::is_sorted( begin(i_arr2), end(i_arr2), 
                            std::greater{}) << '\n';
    // output -> true

    // -------------------------------------------------------

    int i_arr3[]{ 11, 22, 33, 44, -11, -22, -33, -44 };

    auto sorted_until_iter = 
      std::is_sorted_until(begin(i_arr3), end(i_arr3));

    cout << *sorted_until_iter << '\n';
    // output -> -11

    // -------------------------------------------------------
  }
*/

/*
          --------------------------------------------
          | std::make_heap, std::pop_heap algorithms |
          --------------------------------------------
*/


/*
  #include <vector>
  #include <algorithm>    // std::make_heap, std::pop_heap
  #include <random>    
  // std::mt19937, std::uniform_int_distribution

  int main()
  {
    std::vector<int> ivec(16);

    std::mt19937 eng;
    std::uniform_int_distribution dist{ 0, 1000 };

    std::generate(ivec.begin(), ivec.end(), 
                  [&](){ return dist(eng); });

    for (auto elem : ivec)
      std::cout << elem << ' ';
    // output -> 
    //  815 135 906 835 127 969 914 221 
    //  632 308 97 547 278 188 547 993
    std::cout << '\n';

    // ---------------------------------------------------

    std::make_heap(ivec.begin(), ivec.end());
    // std::make_heap is O(n) operation.
    // putting the greatest element to the beginning.

    for (auto elem : ivec)
      std::cout << elem << ' ';
    // output -> 
    //  993 835 969 815 308 906 914 221 
    //  632 127 97 547 278 188 547 135
    std::cout << '\n';

    std::cout << "greatest element = " << ivec.front() << '\n';
    // output -> greatest element = 993

    // ---------------------------------------------------

    std::pop_heap(ivec.begin(), ivec.end());
    // std::pop_heap is O(log_n) operation.
    // putting the greatest element to the end.

    for (auto elem : ivec)
      std::cout << elem << ' ';
    // output -> 
    //  969 835 914 815 308 906 547 221 
    //  632 127 97 547 278 188 135 993 
    std::cout << '\n';

    std::cout << "greatest element = " << ivec.back() << '\n';
    // output -> last element : 993

    // ---------------------------------------------------

    ivec.pop_back();
    // 993(last element) is removed from the container.

    for (auto elem : ivec)
      std::cout << elem << ' ';
    // output -> 
    //  969 835 914 815 308 906 547 221 
    //  632 127 97 547 278 188 135
    std::cout << '\n';

    // the greatest element is in the front,
    // container is still in a heap structure.

    // ---------------------------------------------------

    std::pop_heap(ivec.begin(), ivec.end());
    ivec.pop_back();

    for (auto elem : ivec)
      std::cout << elem << ' ';
    // output -> 
    //  914 835 906 815 308 547 547 
    //  221 632 127 97 135 278 188
    std::cout << '\n';

    // still the greatest element is in the beginning
    // and container is still a heap structure.

    // ---------------------------------------------------
  }
*/

/*
                ----------------------------
                | std::push_heap algorithm |
                ----------------------------
*/

/*
  #include <vector>
  #include <algorithm>  
  // std::generate, std::make_heap, std::push_heap
  #include <random>     
  // std::mt19937, std::uniform_int_distribution

  int main()
  {
    using namespace std;

    std::vector<int> ivec(12);

    std::mt19937 eng;
    std::uniform_int_distribution dist{ 0, 99 };

    std::generate(ivec.begin(), ivec.end(), 
                  [&](){ return dist(eng); });

    std::make_heap(ivec.begin(), ivec.end());

    for (auto elem : ivec)
      std::cout << elem << ' ';
    // output -> 96 83 91 63 30 90 81 22 13 12 9 54
    std::cout << '\n';

    // ----------------------------------------------------

    ivec.push_back(100);
    // adding element to the tail

    std::push_heap(ivec.begin(), ivec.end());
    // std::push_heap will get the last element 
    // that added to vector and fix the container 
    // in heap structure.

    for (auto elem : ivec)
      std::cout << elem << ' ';
    // output -> 100 83 96 63 30 91 81 22 13 12 9 54 90
    std::cout << '\n';

    // ----------------------------------------------------
  }
*/

/*
  // removing the greatest element inside a container 
  // in every iteration.

  #include <vector>
  #include <algorithm>  
  // std::generate, std::make_heap, std::pop_heap
  #include <random>   
  // std::mt19937, std::uniform_int_distribution

  int main()
  {
    std::vector<int> ivec(6);

    std::mt19937 eng;
    std::uniform_int_distribution dist{ 0,1000 };

    std::generate(ivec.begin(), ivec.end(), 
                  [&](){ return dist(eng); });

    std::make_heap(ivec.begin(), ivec.end());

    while (!ivec.empty()) 
    {
      std::cout << "container = ";
      for (auto elem : ivec)
        std::cout << elem << ' ';
      std::cout << '\n';

      std::cout << "greatest element = " 
                << ivec.front() << '\n';

      std::pop_heap(ivec.begin(), ivec.end());

      ivec.pop_back();
      std::cout << "greatest element removed.\n";
      std::cout << "------------------------\n";
    }

    // output ->
    //  container = 969 835 906 135 127 815
    //  greatest element = 969
    //  greatest element removed.
    //  ------------------------
    //  container = 906 835 815 135 127
    //  greatest element = 906
    //  greatest element removed.
    //  ------------------------
    //  container = 835 135 815 127
    //  greatest element = 835
    //  greatest element removed.
    //  ------------------------
    //  container = 815 135 127
    //  greatest element = 815
    //  greatest element removed.
    //  ------------------------
    //  container = 135 127
    //  greatest element = 135
    //  greatest element removed.
    //  ------------------------
    //  container = 127
    //  greatest element = 127
    //  greatest element removed.
    //  ------------------------
  }
*/

/*
  // removing the smallest element inside a container 
  // in every iteration.

  #include <vector>
  #include <algorithm>  
  // std::generate, std::make_heap, std::pop_heap
  #include <random>
  // std::mt19937, std::uniform_int_distribution
  #include <functional> // std::greater

  int main()
  {
    std::vector<int> ivec(6);

    std::mt19937 eng;
    std::uniform_int_distribution dist{ 0, 1000 };

    std::generate(ivec.begin(), ivec.end(), 
                  [&](){ return dist(eng); });

    std::make_heap(ivec.begin(), ivec.end(), std::greater{});

    while (!ivec.empty()) 
    {
      std::cout << "container = ";
      for (auto elem : ivec)
        std::cout << elem << ' ';
      std::cout << '\n';

      std::cout << "smallest element = " 
                << ivec.front() << '\n';

      std::pop_heap(ivec.begin(), ivec.end(), std::greater{});

      ivec.pop_back();
      std::cout << "smallest element removed.\n";
      std::cout << "------------------------\n";
    }
    // output->
    //  container = 127 135 906 835 815 969
    //  smallest element = 127
    //  smallest element removed.
    //  ------------------------
    //  container = 135 815 906 835 969
    //  smallest element = 135
    //  smallest element removed.
    //  ------------------------
    //  container = 815 835 906 969
    //  smallest element = 815
    //  smallest element removed.
    //  ------------------------
    //  container = 835 969 906
    //  smallest element = 835
    //  smallest element removed.
    //  ------------------------
    //  container = 906 969
    //  smallest element = 906
    //  smallest element removed.
    //  ------------------------
    //  container = 969
    //  smallest element = 969
    //  smallest element removed.
    //  ------------------------
  }
*/

/*
              -------------------------------------
              | std::sort_heap algorithm O(nlogn) |
              -------------------------------------
*/

/*
  #include <vector>
  #include <algorithm>  
  // std::generate, std::make_heap, std::sort_heap
  #include <random> 
  // std::mt19937, std::uniform_int_distribution
  #include <functional>   // std::greater

  int main()
  {
    using namespace std;

    std::vector<int> ivec(20);

    std::mt19937 eng;
    std::uniform_int_distribution dist{ 0, 1000 };

    std::generate(ivec.begin(), ivec.end(), 
                  [&](){ return dist(eng); });

    // ---------------------------------------------------

    std::make_heap(ivec.begin(), ivec.end());
    std::sort_heap(ivec.begin(), ivec.end());

    for (auto elem : ivec)
      cout << elem << ' ';
    // output ->
    //  97 127 135 188 221 278 308 547 547 632 
    //  815 835 906 914 958 965 968 969 993 997
    cout << '\n';

    // ---------------------------------------------------

    make_heap(ivec.begin(), ivec.end(), std::greater{});
    sort_heap(ivec.begin(), ivec.end(),  std::greater{});

    for (auto elem : ivec)
      cout << elem << ' ';
    // output ->
    //  997 993 969 968 965 958 914 906 835 815 
    //  632 547 547 308 278 221 188 135 127 97
    cout << '\n';
    
    // ---------------------------------------------------
  }
*/