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
                    -----------------------
                    | std::copy algorithm |
                    -----------------------
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
                    -----------------------
                    | std::find algorithm |
                    -----------------------
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