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