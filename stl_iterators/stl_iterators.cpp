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

/*
                ----------------------------------
                | iterator manipulator functions |
                ----------------------------------
*/

/*
                        ----------------
                        | std::advance |
                        ----------------
*/

/*
  #include <vector>
  #include <list>
  #include <iterator>   // std::advance

  template <typename Iter>
  void func(Iter beg, Iter end)
  {
    int N = 5;
    beg += N;
    // if Iter will deduce to 
    //  - random-access iterator, code is VALID
    //  - bidirectional iterator, code is syntax error
    // operator+= function will be called.
  }

  template <typename Iter>
  void better_func(Iter beg, Iter end)
  {
    int N = 5;
    std::advance(beg, N);
    // std::advance iterator adaptor can be used for both
    // bidirectional and random-access iterators.
  }

  int main()
  {
    using namespace std;

    // ----------------------------------------------------

    vector<int> ivec(100);

    func(ivec.begin(), ivec.end());           // VALID
    better_func(ivec.begin(), ivec.end());    // VALID

    // ----------------------------------------------------

    list<int> ilist(100);

    func(ilist.begin(), ilist.end());         // syntax error
    //  error: no match for 'operator+=' 
    // (operand types are 'std::_List_iterator<int>' and 'int')

    better_func(ilist.begin(), ilist.end());  // VALID

    // ----------------------------------------------------
  }
*/

/*
                    --------------------------
                    | tag dispatch technique |
                    --------------------------
*/

/*
  #include <vector>
  #include <list>
  #include <iterator>   // std::advance 

  template <typename Iter>
  void advance_impl(Iter& iter, int N, 
                    std::random_access_iterator_tag)
  {
    std::cout << "random-access iterator\n";
    iter += N;
  }

  template <typename Iter>
  void advance_impl(Iter& iter, int N, 
                    std::bidirectional_iterator_tag)
  {
    std::cout << "bidirectional iterator\n";

    while (N--)
      ++iter;
  }

  template <typename Iter>
  void Advance(Iter& iter, int N)
  {
    advance_impl(iter, N, typename Iter::iterator_category{});
    // if Iter will deduce to 
    //  - random-access iterator,
    //    3rd parameter will be random_access_iterator_tag
    //  - bidirectional iterator,
    //    3rd parameter will be bidirectional_iterator_tag
  }

  int main()
  {
    // ---------------------------------------------------

    std::vector<int> ivec(100);
    auto iter1 = ivec.begin();

    Advance(iter1, 5);    
    // output -> random-access iterator

    // ---------------------------------------------------

    std::list<int> ilist(100);
    auto iter2 = ilist.begin();

    Advance(iter2, 5);   
    // output -> bidirectional iterator

    // ---------------------------------------------------
  }
*/

/*
  // when a negative value passed as a 2nd argument
  // to std::advance iterator adaptor function,
  // itertor type needs to be minimum bidirectional iterator

  #include <list>
  #include <vector>
  #include <iterator>   // std::advance

  int main()
  {
    // ---------------------------------------------------

    std::vector<int> ivec(100);
    auto iter1 = ivec.end();

    std::advance(iter1, -20);    // VALID

    // ---------------------------------------------------

    std::list<int> ilist(100);
    auto iter2 = ilist.end();

    std::advance(iter2, -20);   // VALID

    // ---------------------------------------------------
  }
*/

/*
                        -----------------
                        | std::distance |
                        -----------------
*/

/*
  #include <list>
  #include <algorithm>  // std::find

  template <typename Iter>
  int return_difference(Iter beg, Iter current)
  {
    return current - beg;
  }

  int main()
  {
    using namespace std;

    list<string> slist{ "monday", "tuesday", "wednesday", 
      "thursday", "friday", "saturday", "sunday" };

    string str{ "friday" };

    if (auto iter = std::find(slist.begin(), slist.end(), str); 
        iter != slist.end())
    {
      std::cout << str << " is found, index = " 
                << return_difference(slist.begin(), iter) << '\n';
    }
    else
      std::cout << str << " is not found.\n";
    
    // syntax error
    //  error: no match for 'operator-' 
    //  (operand types are 'std::_List_iterator<basic_string<char>>' 
    //  and 'std::_List_iterator<basic_string<char> >')

    // bidirectional operator did not have "operator-" overload. 
  }
*/

/*
  #include <list>
  #include <algorithm>  // std::find
  #include <iterator>   // std::distance

  int main()
  {
    using namespace std;

    list<string> slist{ "monday", "tuesday", "wednesday", 
      "thursday", "friday", "saturday", "sunday" };

    string str{ "friday" };

    if (auto iter = std::find(slist.begin(), slist.end(), str); 
        iter != slist.end())
    {
      std::cout << str << " is found, index = " 
                << std::distance(slist.begin(), iter) << '\n';
    }
    else
      std::cout << str << " is not found.\n";

    // output -> friday is found, index = 4
  }
*/

/*
  "std::advance" function has a reference parameter
  so it will change the value of the iterator 
  that has been passed.

  "std::next" function will return a new iterator.
  It will not change the value of the iterator that has been passed.
*/

/*
                      ------------------------
                      | std::next, std::prev |
                      ------------------------
*/

/*
  #include <list>
  #include <vector>
  #include <string>
  #include <iterator>   // std::next, std::back_inserter
  #include <algorithm>  // std::copy

  int main()
  {
    using namespace std;

    list<string> slist{ "monday", "tuesday", "wednesday", 
      "thursday", "friday", "saturday", "sunday" };

    // ----------------------------------------------------

    std::cout << *std::next(slist.begin(), 2) << '\n';
    // output -> wednesday

    // ----------------------------------------------------

    std::cout << *std::next(slist.begin()) << '\n';
    //  std::cout << *std::next(slist.begin(), 1) << '\n';
    // Those 2 lines are equivalent
    // output -> tuesday

    // std::next function's 2nd argument 
    // is a default argument with value 1

    // ----------------------------------------------------

    vector<string> svec;
    copy(next(slist.begin(), 3), slist.end(), back_inserter(svec));

    for (auto elem : svec)
      std::cout << elem << ' ';
    // output -> thursday friday saturday sunday

    // ----------------------------------------------------
  }
*/

/*
  #include <list>
  #include <iterator>   
  // std::prev, std::next, std::back_inserter
  #include <algorithm>  // std::copy

  int main()
  {
    std::list<int> ilist1{ 11, 22, 33, 44, 55, 66, 77, 88, 99 };
    std::list<int> ilist2;

    std::copy(std::next(ilist1.begin()), 
              std::prev(ilist1.end()), 
              std::back_inserter(ilist2));

    for (auto elem : ilist2)
      std::cout << elem << ' ';
    // output -> 22 33 44 55 66 77 88
  }
*/

/*
                        ------------------
                        | std::iter_swap |
                        ------------------
*/

/*
  #include <list>
  #include <vector>
  #include <algorithm>    // std::iter_swap
  #include <utility>      // std::move, std::swap
  #include <iterator>     // std::next

  template <typename Type>
  void Swap(Type& elem1, Type& elem2)
  {
    Type temp{ std::move(elem1) };
    elem1 = std::move(elem2);
    elem2 = std::move(temp);
  }

  template <typename IterX, typename IterY>
  void Iter_Swap(IterX x, IterY y)
  {
    Swap(*x, *y);
  }
  // "std::iter_swap" function is calling 
  // "std::swap" function which have 1 template parameter
  // so when std::iter_swap's arguments are dereferenced
  // they have to be the same type.

  int main()
  {
    // ----------------------------------------------------

    std::list<int> ilist{ 11, 22, 33, 44 };
    std::vector<int> ivec{ 99, 88, 77, 66};

    std::iter_swap(ilist.begin(), std::next(ivec.begin()));

    for (auto elem : ilist)
      std::cout << elem << ' ';
    // output -> 88 22 33 44

    std::cout << '\n';

    for (auto elem : ivec)
      std::cout << elem << ' ';
    // output -> 99 11 77 66

    //  *ilist.begin()            -> int
    //  *std::next(ivec.begin())  -> int

    // ----------------------------------------------------

    int i_arr[] = { 11, 22, 33, 44 };
    double d_arr[] = { 55.5, 66.6, 77.7, 88.8 };

    std::iter_swap(std::begin(i_arr), std::begin(d_arr));
    // syntax error
    // error: no matching function for call to 'swap(int&, double&)'

    // *std::begin(i_arr)   -> int
    // *std::begin(d_arr)   -> double

    // ----------------------------------------------------
  }
*/

/*
            ---------------------------------------
            | reverse_iterator - iterator adaptor |
            ---------------------------------------
*/

/*
  - reverse iterator is wrapping an iterator.
  - minumum bidirectional iterator is needed.
*/

/*
  #include <vector>
  #include <type_traits>    // std::is_same

  template <typename Iter>
  void display_range(Iter beg, Iter end)
  {
    while (beg != end) 
      std::cout << *beg++ << ' ';
    
    std::cout << '\n';
  }

  int main()
  {
    std::vector<int> ivec{ 11, 22, 33, 44, 55, 66 };

    display_range(ivec.begin(), ivec.end());
    // output -> 11 22 33 44 55 66

    display_range(ivec.rbegin(), ivec.rend());
    // output -> 66 55 44 33 22 11

    // -----------------------------------------------

    auto riter_beg = ivec.rbegin();
    constexpr bool b1 = 
      std::is_same_v< decltype(riter_beg), 
                      std::vector<int>::reverse_iterator>;
    // b1 -> true

    std::cout << *riter_beg << '\n';        // output -> 66
    std::cout << *(++riter_beg) << '\n';    // output -> 55

    // -----------------------------------------------

    auto iter_beg = ivec.begin();

    std::cout << *iter_beg << '\n';         // output -> 11
    std::cout << *(++iter_beg) << '\n';     // output -> 22

    // -----------------------------------------------
  }
*/

/*
    <--- check stl_iterators/images/reverse_iterator.png --->
*/

/*
  #include <vector>

  int main()
  {
    std::vector<int> ivec{ 11, 22, 33, 44, 55, 66 };

    // ---------------------------------------------------

    auto riter_beg = ivec.rbegin();
    // riter_beg's type is std::vector<int>::reverse_iterator

    // "rbegin" member function returns the position of
    // the last element in container.

    std::cout << *riter_beg << '\n';   // output -> 66

    // ---------------------------------------------------

    auto riter_beg_base = riter_beg.base();
    // std::vector<int>::reverse_iterator interface  
    // has a "base" member function
    // which will return std::vector<int>::iterator
    // to the end of the container position
    // (last elemeent + 1)(sentinel)

    if (riter_beg_base == ivec.end())
      std::cout << "riter_beg_base == ivec.end()\n";
    else 
      std::cout << "riter_beg_base != ivec.end()\n";
    // output -> riter_beg_base == ivec.end()

    std::cout << *riter_beg_base << '\n'; // undefined behaviour(UB)
    // dereferencing the sentinel position is UB

    // ---------------------------------------------------
  }
*/

/*
  #include <vector>

  template <typename Iter>
  void display_range(Iter beg, Iter end)
  {
    while (beg != end) 
      std::cout << *beg++ << ' ';
    
    std::cout << '\n';
  }

  int main()
  {
    std::vector<int> ivec{ 11, 22, 33, 44, 55, 66 };

    // -----------------------------------------------------

    auto riter_beg = ivec.rbegin(); 
    // riter_beg's type is std::vector<int>::reverse_iterator
    // riter_beg's position is last element's position
    // in the container (66)

    auto riter_end = ivec.rend();
    // riter_end's type is std::vector<int>::reverse_iterator
    // riter_end's position is the (first element - 1)
    // dereferencing riter_end is undefined behaviour(UB)

    display_range(riter_beg, riter_end);
    // output -> 66 55 44 33 22 11

    // -----------------------------------------------------

    auto riter_beg_base = riter_beg.base();
    // "riter_beg_base" data type is std::vector<int>::iterator 
    // it's position is the end of the container
    // (last element + 1)(sentinel)

    auto riter_end_base = riter_end.base();
    // "riter_end_base" data type is std::vector<int>::iterator
    // it will return the position of the first element
    // in the container

    display_range(riter_end_base, riter_beg_base);
    // output -> 11 22 33 44 55 66

    // -----------------------------------------------------

    if (riter_end_base == ivec.begin())
      std::cout << "riter_end.base() == ivec.begin()\n";
    else
      std::cout << "riter_end.base() != ivec.begin()\n";
    
    if (riter_beg_base == ivec.end())
      std::cout << "riter_beg.base() == ivec.end()\n";
    else
      std::cout << "riter_beg.base() != ivec.end()\n";
    
    // output ->
    //  riter_end.base() == ivec.begin()
    //  riter_beg.base() == ivec.end()

    // -----------------------------------------------------
  }
*/

/*
  #include <vector>

  int main()
  {
    std::vector<int> ivec{ 11, 22, 33, 44, 55, 66 };  

    // --------------------------------------------------

    auto riter_beg = ivec.rbegin();   
    // ivec.end() - 1   -> last elements position (66)
    // dereferencing will be the last element (66)

    std::cout << *riter_beg << '\n'; // output -> 66

    // --------------------------------------------------

    auto riter_end = ivec.rend();     
    // ivec.begin() - 1 -> (first element - 1) position
    // dereferencing is UB

    // --------------------------------------------------

    auto riter_beg_base = riter_beg.base();
    // ((ivec.end() - 1) + 1) = ivec.end() -> sentinel position
    // dereferencing is UB

    // --------------------------------------------------

    auto riter_end_base = riter_end.base();
    // ((ivec.begin() - 1) + 1) = ivec.begin() -> first element
    // dereferencing will be the first element (11)
    
    std::cout << *riter_end_base << '\n'; // output -> 11

    // --------------------------------------------------
  }
*/


/*
  // deleting the right-most specific element from a container

  #include <vector>
  #include <algorithm>  // std::find

  int main()
  {
    using namespace std;

    vector<int> ivec{ 11, 22, 33, 44, 11, 22, 33, 44 };

    int val = 22;
    if (auto riter = std::find(ivec.rbegin(), ivec.rend(), val); 
        riter != ivec.rend())
    {
      ivec.erase(riter);  // syntax error
      // error: no matching function for call to 
      // 'std::vector<int>::erase(
      //  std::reverse_iterator<std::vector<int>>&)'

      // erase member function of the std::vector
      // wants std::iterator type as an argument.
    }
    else 
      cout << val << " is not found.\n";
  }
*/

/*
  // deleting the right-most specific element from a container

  #include <vector>
  #include <algorithm>  // std::find

  int main()
  {
    using namespace std;

    vector<int> ivec{ 11, 22, 33, 44, 11, 22, 33, 44 };

    int val = 22;
    if (auto riter = std::find(ivec.rbegin(), ivec.rend(), val); 
        riter != ivec.rend())
    {
      std::cout << *(riter.base()) << '\n';
      // output -> 33

      ivec.erase(riter.base());
    }
    else 
      cout << val << " is not found.\n";

    for (auto elem : ivec)
      std::cout << elem << ' ';
    // output -> 11 22 33 44 11 22 44

    // wanted to delete the (22) but (33) is deleted. 
  }
*/

/*
  // deleting the right-most specific element from a container

  #include <vector>
  #include <algorithm>  // std::find
  #include <iterator>   // std::prev

  int main()
  {
    using namespace std;

    vector<int> ivec{ 11, 22, 33, 44, 11, 22, 33, 44 };

    int val = 22;
    if (auto riter = std::find(ivec.rbegin(), ivec.rend(), val); 
        riter != ivec.rend())
    {
      std::cout << *std::prev(riter.base()) << '\n';
      // output -> 22

      ivec.erase(std::prev(riter.base()));
    }
    else 
      cout << val << " is not found.\n";

    for (auto elem : ivec)
      std::cout << elem << ' ';
    // output -> 11 22 33 44 11 33 44
  }
*/