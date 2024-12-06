#include <iostream>

/*
                        =================
                        | STL Iterators |
                        =================
*/

/*
    <--- check stl_iterators/images/iterators_general.png --->
*/

/*
  #include <vector>
  #include <algorithm>

  int main()
  {
    using namespace std;

    vector<int> ivec;  // default initialization
    vector<int> ivec2(20);
    vector<int> ivec3{ 33, 11, 55, 44, 22 , 77, 66 };

    // --------------------------------------------------

    auto iter = ivec.begin();
    *iter;    // undefined behaviour(UB)
    --iter;   // undefined behaviour(UB)

    // --------------------------------------------------
    
    iter = ivec2.end();
    *iter;    // undefined behaviour(UB)
    ++iter;   // undefined behaviour(UB)

    // dereferncing "end" iterator is undefined behaviour
    // incrementing "end" iterator is undefined behaviour

    // --------------------------------------------------

    std::sort(ivec3.begin(), ivec3.end());

    for (auto elem : ivec3)
      std::cout << elem << ' ';
    // output -> 11 22 33 44 55 66 77

    std::cout << '\n';

    // --------------------------------------------------

    std::sort(ivec3.end(), ivec3.begin());  // undefined behaviour(UB)

    // --------------------------------------------------
  }
*/

/*
  // With modern C++ global inline function templates are added.
  // i.e std::begin, std::end, std::cbegin, std::cend...
  
  #include <vector>     // std::begin, std::end
  #include <algorithm>  // std::sort

  int main()
  {
    std::vector<int> ivec{ 2, 54, 6, 7, 8 };

    // ---------------------------------------------------

    auto iter_beg1 = ivec.begin();
    // std::vector<int>::begin member function
    auto iter_beg2 = std::begin(ivec);
    // "std::begin" global function template

    // Those 2 lines are equivalent.

    if (iter_beg1 == iter_beg2)
      std::cout << "iter_beg1 == iter_beg2\n";

    // ---------------------------------------------------

    // Question: Why global function templates are added?

    // Answer: Cstyle arrays are not classes, so they don't 
    //  have member functions like "begin" and "end" etc..

    // ---------------------------------------------------

    int i_arr[] = { 33, 11, 55, 44, 22 , 77, 66 };

    std::sort(std::begin(i_arr), std::end(i_arr));

    for (auto elem : i_arr)
      std::cout << elem << ' ';
    // output -> 11 22 33 44 55 66 77

    // ---------------------------------------------------
  }
*/

/*
  // global function template "std::begin" and "std::end" 
  // for C style arrays

  template <typename Container>
  typename Container::iterator Begin(Container& c);

  template <typename Container>
  typename Container::iterator End(Container& c);

  template <typename T, std::size_t N>
  T* Begin(T(&r)[N])
  {
    return &r[0];
  }

  template <typename T, std::size_t N>
  T* End(T(&r)[N])
  {
    return &r[N];
  }
*/

/*
                      -----------------------
                      | iterator categories |
                      -----------------------
*/

/*
        <--- check images/1_output_iterator_interface.png --->
        <--- check images/2_input_iterator_interface.png --->
        <--- check images/3_forward_iterator_interface.png --->
        <--- check images/4_bidirectional_iterator_interface.png --->
        <--- check images/5_random-access_iterator_interface.png --->
*/

/*
  1. input iterator
  2. output iterator
  3. forward iterator
  4. bidirectional iterator
  5. random access iterator
  6. contigious iterator (Modern C++)
*/

/*
  #include <forward_list>   // singly linked list

  int main()
  {
    // forward list's iterator's category is forward iterator
    std::forward_list<int> i_flist(10); 

    // ---------------------------------------------------

    auto iter = i_flist.begin();

    *iter;    // VALID  (dereferencable)
    ++iter;   // VALID  (pre-incrementable)
    iter++;   // VALID  (post-incrementable)
    --iter;   // syntax error
    // error: no match for 'operator--' 
    // (operand type is 'std::_Fwd_list_iterator<int>')

    // ---------------------------------------------------

    auto iter1 = i_flist.begin();
    auto iter2 = i_flist.begin();

    auto b = iter1 == iter2;  // VALID
    auto c = iter1 < iter2;   // syntax error
    // error: no match for 'operator<' 
    // (operand types are 'std::_Fwd_list_iterator<int>' and  
    // std::_Fwd_list_iterator<int>')

    // ---------------------------------------------------
  }
*/

/*
  #include <list>   // doubly linked list

  int main()
  {
    // std::list iterator's category is bidirectional iterator
    std::list<int> i_list(10);

    // ---------------------------------------------------

    auto iter = i_list.begin();
    *iter;    // VALID  (dereferencable)
    ++iter;   // VALID  (pre-incrementable)
    iter++;   // VALID  (post-incrementable)
    --iter;   // VALID  (pre-decrementable)   
    iter--;   // VALID  (post-decrementable)

    // ---------------------------------------------------

    auto iter1 = i_list.begin();
    auto iter2 = i_list.begin();

    auto b = iter1 == iter2;  // VALID
    auto c = iter1 < iter2;   // syntax error
    // error: no match for 'operator<' 
    // (operand types are 'std::_List_iterator<int>' and 
    // 'std::_List_iterator<int>')

    // ---------------------------------------------------
  }
*/

/*
  #include <vector>   // dynamic array

  int main()
  {
    // std::vector iterator's category is random-access iterator

    // random-access iterator's operation interface 
    // is same as raw pointers.

    std::vector<int> ivec(10);

    // --------------------------------------------------

    auto iter = ivec.begin();
    *iter;    // VALID  (dereferencable)
    ++iter;   // VALID  (pre-incrementable)
    iter++;   // VALID  (post-incrementable)
    --iter;   // VALID  (pre-decrementable)
    iter--;   // VALID  (post-decrementable)

    // --------------------------------------------------

    iter += 3;          // VALID  (random-access)
    auto val = iter[2]; // VALID  (random-access)

    // --------------------------------------------------

    auto iter1 = ivec.begin();
    auto iter2 = ivec.begin();

    auto b = iter1 == iter2;    // VALID
    auto c = iter1 < iter2;     // VALID

    // --------------------------------------------------
  }
*/

/*
  for compile time operations, every 'iterator' type 
  have a nested type called 'iterator_category'

  in STL, empty classes are used for declaring iterator categories

  input iterator          -> input_iterator_tag         (Empty class)
  output iterator         -> output_iterator_tag        (Empty class)
  forward iterator        -> forward_iterator_tag       (Empty class)
  bidirectional iterator  -> bidirectional_iterator_tag (Empty class)
  random-access iterator  -> random_access_iterator_tag (Empty class)
*/

/*
  #include <vector>
  #include <set>
  #include <forward_list>
  #include <type_traits>    // std::is_same
  #include <iterator>
  // std::forward_iterator_tag, std::random_access_iterator_tag, 
  // std::bidirectional_iterator_tag


  using fl_iter   = std::forward_list<int>::iterator;
  using vec_iter  = std::vector<int>::iterator;
  using set_iter  = std::set<int>::iterator;
  
  int main()
  {
    // ---------------------------------------------------

    constexpr auto b1 = 
      std::is_same_v< typename fl_iter::iterator_category, 
                      std::forward_iterator_tag>;    
    // b1 -> true  

    // ---------------------------------------------------

    constexpr auto b2 = 
      std::is_same_v< typename vec_iter::iterator_category,
                      std::random_access_iterator_tag>;
    // b2 -> true
    
    // ---------------------------------------------------

    constexpr auto b3 = 
      std::is_same_v< typename set_iter::iterator_category,
                      std::bidirectional_iterator_tag>;
    // b3 -> true

    constexpr auto b4 = 
      std::is_same_v< typename set_iter::iterator_category,
                      std::random_access_iterator_tag>;
    // b4 -> false

    // ---------------------------------------------------
  }
*/

/*
  #include <iterator>
  // std::istream_iterator, std::ostream_iterator
  // std::input_iterator_tag, std::output_iterator_tag
  #include <type_traits>  // std::is_same


  using istream_it = std::istream_iterator<int>;
  using ostream_it = std::ostream_iterator<int>;

  int main()
  {
    static_assert(
      std::is_same_v< typename istream_it::iterator_category, 
                      std::input_iterator_tag>);
    // holds 

    static_assert(
      std::is_same_v< typename ostream_it::iterator_category, 
                      std::output_iterator_tag>);
    // holds 
  }
*/

/*
  #include <type_traits>  // std::is_same
  #include <vector>
  #include <list>
  #include <iterator>   // std::random_access_iterator_tag

  template <typename Iter>
  void is_random_access_iter(Iter beg, Iter end)
  {
    static_assert(
      std::is_same_v< typename Iter::iterator_category,
                      std::random_access_iterator_tag>,
      "only random-access iterator allowed");
  }

  int main()
  {
    // ----------------------------------------------------

    std::vector<int> ivec(10);
    is_random_access_iter(ivec.begin(), ivec.end());
    //  holds

    // ----------------------------------------------------

    std::list<int> ilist(20);
    is_random_access_iter(ilist.begin(), ilist.end());
    // error: static assertion failed: 
    // only random-access iterator allowed
    // 'std::is_same_v<std::bidirectional_iterator_tag, 
    //  std::random_access_iterator_tag ' evaluates to false

    // ----------------------------------------------------
  }
*/

/*
  #include <type_traits>  // std::is_same
  #include <vector>
  #include <list>
  #include <iterator> 
  // std::bidirectional_iterator_tag, 
  // std::random_access_iterator_tag

  template <typename Iter>
  void control_algorithm(Iter beg, Iter end)
  {
    if constexpr (std::is_same_v<
                    typename Iter::iterator_category, 
                    std::random_access_iterator_tag>)
    {
      beg += 5;
      // "+=" operator CAN be used with random-access iterators
      std::cout << "random-access iterator\n";
    }
    else if constexpr (std::is_same_v<
                        typename Iter::iterator_category, 
                        std::bidirectional_iterator_tag>)
    {
      for (int  i = 0; i < 5; i++)
        ++beg;
      
      // "+=" operator CAN NOT be used with bidirectional iterators
      std::cout << "bidirectional iterator\n";
    }
  }

  int main()
  {
    std::vector<int> ivec(10);
    control_algorithm(ivec.begin(), ivec.end());
    // output -> random-access iterator

    std::list<int> ilist(20);
    control_algorithm(ilist.begin(), ilist.end());
    // output -> bidirectional iterator
  }
*/

/*
              -------------------------------------
              | const_iterator - iterator adaptor |
              -------------------------------------
*/

/*
  #include <vector>
  #include <type_traits>

  int main()
  {
    using namespace std;

    vector<int> ivec{ 11, 22, 33, 44, 55, 66, 77 };

    const vector<int>::iterator iter = ivec.begin();
    // object(vector<int>::iterator) is `const` 
    // element that object is pointing to is not const.
    // top-level const
    // --------------------------------------------------------
    
    ++iter;   // syntax error
    // error: passing 'const std::vector<int>::iterator' 
    // as 'this' argument discards qualifiers

    // "operator++" is a non-const member function
    // of std::vector<int>::iterator nested type.
    // Calling non-const member function 
    // with a const object will cause syntax error.

    // --------------------------------------------------------

    *iter = 54;   // VALID  
    // return type is `int&`
    
    // "operator*" can be called with const or non-const object.
    // changing *iter which is `int`(in this container) is valid. 

    // --------------------------------------------------------
  }
*/

/*
  #include <vector>
  #include <type_traits>

  int main()
  {
    using namespace std;

    vector<int> ivec{ 11, 22, 33, 44, 55, 66, 77 };

    // Iterator adapter -> const_iterator 
    vector<int>::const_iterator citer = ivec.begin();
    // object(vector<int>::const_iterator) is not `const`
    // element that object is pointing to is `const`
    // low-level const

    // --------------------------------------------------------

    ++citer;    // VALID

    // --------------------------------------------------------

    //*citer = 23;  // syntax error 
    // error: assignment of read-only location 
    // 'citer.iterator<const int*, std::vector<int> >::operator*()'
    // return type is `const int&`

    // --------------------------------------------------------

    // if the purpose accessing the container elements
    // not mutating them.
    for (auto iter = ivec.cbegin(); iter != ivec.cend(); ++iter) 
      std::cout << *iter << ' ';
    // output -> 11 22 33 44 55 66 77

    // --------------------------------------------------------
  }
*/

/*
  #include <vector>
  #include <type_traits>  // std::is_same

  using vec_type = std::vector<int>;

  int main()
  {
    vec_type ivec(6);

    auto iter_beg   = ivec.begin();		
    constexpr auto b1 = std::is_same_v< decltype(iter_beg), 
                                        vec_type::iterator>;
    // b1 -> true

    auto citer_beg  = ivec.cbegin();
    constexpr auto b2 = std::is_same_v< decltype(citer_beg), 
                                        vec_type::const_iterator>;
    // b2 -> true

    auto citer_end = ivec.cend();
    constexpr auto b2 = std::is_same_v< decltype(citer_beg), 
                                        vec_type::const_iterator>;
    // b2 -> true
  }
*/