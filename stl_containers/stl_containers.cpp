#include <iostream>

/*
                      ==================
                      | STL Containers |
                      ==================
*/

/*
  sequence containers
  ----------------------------------
  C Arrays
  std::vector
  std::deque
  std::list
  std::forward_list         (C++11)
  std::string
  std::array                (C++11)

  associative containers
  ----------------------------------
  std::set
  std::multiset
  std::map
  std::multimap

  unordered associative containers
  ----------------------------------
  std::unordered_set        (C++11)
  std::unordered_multiset   (C++11)
  std::unordered_map        (C++11)
  std::unordered_multimap   (C++11)
*/

/*
  -----------------------------------------------------------

  -> C arrays are fixed arrays.
  -> std::vector is a dynamic array.
  -> std::deque is double ended queue. (vector of vectors)
  -> std::list is doubly linked list.
  -> std::forward_list is linked list
  -> std::string is a dynamic array.
  -> std::array is C array wrapper.

  -----------------------------------------------------------

  -> std::set is a binary tree of unique keys.
  -> std::multiset is a binary tree of non-unique keys. 
  -> std::map is holding [unique key - value] pairs. 
  -> std::multimap is holding [non-unique key - value] pairs.

  -----------------------------------------------------------

  -> search in assosiative containers           -> O(log n) 
      those are binary search trees.
  -> search in unordered associative containers -> O(1) 
      those are hash tables.

  -----------------------------------------------------------
*/

/*
  container adaptors
  -----------------------
  std::stack          -> stack interface. Last In First Out(LIFO)
  std::queue          -> tail interface.  First In First Out(FIFO)
  std::priority_queue -> high priority first out.
*/

/*
  // mental model for containers

  template <typename T>
  class Vector {
  public:
    // constiner member functions
    void push_back(const T&);
    void push_back(T&&);
    void pop_back();
    std::size_t size()const;
    bool empty()const;

    // nested type iterator interface
    class iterator {
    public:
      T& operator*();
      iterator& operator++();
      iterator& operator--();
      T* operator->();
      bool operator==(iterator)const;
      bool operator!=(iterator)const;
    };

    iterator insert(iterator, const T& val);
    iterator erase(iterator);

    iterator begin(); 
    // returns first elements position
    iterator end();   
    // returns sentinel position (last element + 1)
  };
*/

/*
  template <typename Container>
  void func(Container& c)
  {
    auto iter = c.begin();      
    // all containers have "begin" member function.
    typename C::iterator iter;
    // all containers have an 'iterator' nested type.
    typename C::value_type;
    // all containers have 'value_type' nested type.
  }
*/

/*
  template <typename Iter>
  void func(Iter beg, Iter end)
  {
    typename Iter::value_type;
    // all iterator type have a 'value_type' nested type.
  }
*/

/*
  #include <vector>
  int main()
  {
    std::vector<int>::value_type;             // int
    std::vector<int*>::iterator::value_type;  // int*

    // - containers 
    // - 'iterator' nested type of containers
    //    have a 'value_type' nested type

    std::vector<int>::pointer;          // int*
    std::vector<int>::reference;        // int&
  }
*/

/*
  - In sequence containers elements 
    CAN BE add to a specific index.
  - In associative containers elements 
    CAN NOT be added to a random index.

  Standart Library containers have common functions,
    - empty   -> returns true if container is empty
    - clear   -> deletes all elements from the container
    - size    -> returns count of elements in the container

  Sequence containers in Standart Library have common functions,
    - front   -> returns the first element of container
    - back()  -> returns the last element of container
    - resize  -> change the size of the container
*/

/*
  // containers have common nested types,
  // i.e. "size_type", "value_type", "pointer", "reference"...

  #include <vector>
  #include <list>
  #include <map>
  #include <forward_list>
  #include <set>

  int main()
  {
    // --------------------------------------------------

    std::vector<int>::size_type vec_size{};
    std::list<int>::size_type list_size{};
    std::map<int, int>::size_type map_size{};
    std::set<int>::size_type  set_size{};
    std::forward_list<int>::size_type forward_list_size{};

    // --------------------------------------------------

    std::vector<int>::value_type ival{};
    // std::vector<int>::value_type -> int 

    std::list<double>::value_type dval{};
    // std::list<double>::value_type -> double

    std::map<int, double>::value_type pair_int_double{};	
    // std::map<int, double>::value_type -> 
    //    std::pair<const int, double>

    // --------------------------------------------------

    std::vector<int>::pointer i_ptr{};
    // std::vector<int>::pointer -> int*

    int i1 = 10;
    std::vector<int>::reference i_ref = i1;
    // std::vector<int>::reference -> int&

    // --------------------------------------------------
  }
*/

/*
  #include <vector>
  #include <iterator>   // std::iterator_traits

  // Question :
  // what if C style array's sent to "func_1"
  // std::begin(arr), std::end(arr)
  // Answer :
  // C style array does not have a "value_type"
  // so it will be a syntax error.

  template <typename InIter>
  void func_1(InIter iter_beg, InIter iter_end)
  {
    typename InIter::value_type x{};
  }

  // for the problem above std::iterator_traits 
  // class template will be used.
  template <typename InIter>
  void func_2(InIter iter_beg, InIter iter_end)
  {
    typename std::iterator_traits<InIter>::value_type x{};
  }

  // -----------------------------------------------------

  // primary template for Iterator_Traits 
  template <typename Iter>
  struct Iterator_Traits {
    using value_type = typename Iter::value_type;
    using pointer = typename Iter::pointer;
    using reference = typename Iter::reference;
  };

  // partial specialization for pointer type
  template <typename T>
  struct Iterator_Traits<T*> {
    using value_type = T;
    using pointer = T*;
  };

  // because of C array will decay to pointer 
  // it will choose the partial specialization
  // so value_type will become int.

  // -----------------------------------------------------

  int main()
  {
    std::vector<int> ivec(100);
    int i_arr[5] = { 11, 22, 33, 44, 55 };

    // ---------------------------------------------

    func_1(ivec.begin(), ivec.end());           // VALID
    func_1(std::begin(i_arr), std::end(i_arr)); // syntax error
    // error: 'int*' is not a class, struct, or union type
    func_1(i_arr, i_arr + 5);                   // syntax error
    // error: 'int*' is not a class, struct, or union type

    // ---------------------------------------------

    func_2(ivec.begin(), ivec.end());           // VALID
    func_2(std::begin(i_arr), std::end(i_arr)); // VALID
    func_2(i_arr, i_arr + 5);                   // VALID 

    // ---------------------------------------------
  }
*/

/*
                  -------------------------
                  | std::vector container |
                  -------------------------
*/


/*
  - in std::vector all index's can be reached in constant time
    using pointer arithmetics because std::vector is 
    a sequence container.

  - when adding an element at the end of the std::vector 
    sometimes reallocation will be needed, 
    other times O(1), 
    so it was called amortized constant time.
*/

/*
  #include <vector>
  #include <memory>   // std::allocator

  template <typename T, typename A = std::allocator<T>>
  class Vector {};

  int main()
  {
    std::cout << std::boolalpha;

    // -----------------------------------------------

    std::vector<int, std::allocator<int>> ivec1;
    std::vector<int> ivec2;
    // Those 2 lines are equivalent

    // -----------------------------------------------

    std::vector<int> ivec;  // default initialization

    std::cout << "ivec.size() = " << ivec.size() << '\n';
    // output -> ivec.size() = 0
    std::cout << "ivec.empty() = " << ivec.empty() << '\n';
    // output -> ivec.empty() = true

    // -----------------------------------------------
  }
*/

/*
  // insert functions of std::vector, 
  // are increasing the size of the container.

  // remove functions of std::vector, 
  // are decreasing the size of the container.

  #include <vector>

  int main()
  {
    std::vector<int> ivec;

    // insert functions of std::vector
    ivec.push_back(10);
    ivec.emplace_back(10);
    ivec.insert(ivec.begin(), 5);

    // remove functions of std::vector
    ivec.pop_back();
    ivec.erase(ivec.begin());
  }
*/

/*
  #include <utility>  // std::forward

  // mental model for insert functions of std::vector
  template <typename T>
  class Vector {
  public:
    // const L value reference parameter
    void push_back(const T&);

    // R value reference parameter
    void push_back(T&&);       

    // universal reference parameter
    template <typename ...Args>
    void emplace_back(Args&&... args) 
    {
      new(address) T(std::forward<Args>(args)...);
      // address in std::vector 
      // that the object will be constructed.
    }
  };
*/

/*
  #include <vector>

  class Myclass {
  public:
    Myclass() 
    {
      std::cout << "Myclass::Myclass() : default constructor\n";
    }

    Myclass(int, int, int)
    {
      std::cout << "Myclass::Myclass(int, int, int)\n";
    }

    Myclass(const Myclass&)
    {
      std::cout << 
        "Myclass::Myclass(const Myclass&) : copy constructor\n";
    }

    Myclass(Myclass&&)
    {
      std::cout << 
        "Myclass::Myclass(Myclass&&) : move constructor\n";
    }
  };

  int main()
  {
    std::vector<Myclass> m_vec;
    m_vec.reserve(100);

    // ----------------------------------------------------

    Myclass m1;
    m_vec.push_back(m1);
    // output ->
    //  Myclass::Myclass() : default constructor
    //  Myclass::Myclass(const Myclass&) : copy constructor

    // default constructor for m1 object
    // copy constructor for copying m1 object to std::vector

    // ----------------------------------------------------

    m_vec.push_back(Myclass{});
    // output ->
    //  Myclass::Myclass() : default constructor
    //  Myclass::Myclass(Myclass&&) : move constructor

    // default constructor for temporary Myclass{} object
    // move constructor for moving temporary object to std::vector

    // ----------------------------------------------------

    m_vec.emplace_back();
    // output -> Myclass::Myclass() : default constructor 

    // Myclass object will directly constructed in std::vector
    // because of no arguments has been pass to "emplace_back"
    // function, default constructor of Myclass will be called.

    // ----------------------------------------------------

    m_vec.emplace_back(11, 22, 33);
    // output -> Myclass::Myclass(int, int, int)

    // arguments of the "emplace_back" will be 
    // perfect forwarded to Myclass(int, int, int) constructor

    // ----------------------------------------------------
  }
*/

/*
  #include <vector>
  #include <string>
  #include <utility>  // std::move

  int main()
  {
    std::vector<int> ivec;

    // -----------------------------------------------

    // std::vector class's member functions

    auto iter_1 = ivec.begin();    // iterator
    auto iter_2 = ivec.cbegin();   // const iterator
    auto iter_3 = ivec.rbegin();   // reverse iterator
    auto iter_4 = ivec.crbegin();  // const reverse iterator

    // -----------------------------------------------

    // global functions (generally used for C style arrays)

    auto iter_5 = std::begin(ivec);   // iterator
    auto iter_6 = std::cbegin(ivec);  // const iterator
    auto iter_7 = std::rbegin(ivec);  // reverse iterator
    auto iter_8 = std::crbegin(ivec); // const reverse iterator

    // -----------------------------------------------

    int i_arr[]{ 11, 22, 33, 44, 55 };
    std::crbegin(i_arr);

    // -----------------------------------------------

    // all containers have default constructor

    std::vector<int> ivec1;    // default initialization
    // std::vector classes default constructor will be called
    std::vector<int> ivec2{};  // value initialization
    // std::vector classes default constructor will be called

    std::vector<int> ivec3();
    // this is a function declaration not a variable definition
    // most vexing parse 

    // -----------------------------------------------

    std::vector<std::string> svec_1{ 
      "istanbul", "ankara", "izmir", "bursa", "eskisehir" };

    auto svec_2 = svec_1;
    auto svec_3{ svec_1 };
    // std::vector classes copy constructor will be called.

    std::cout << "svec_1.capacity() = " 
              << svec_1.capacity() << '\n';
    // output -> svec_1.capacity() = 5

    std::cout << "svec_2.capacity() = "
              << svec_2.capacity() << '\n';
    // output -> svec_2.capacity() = 5

    std::cout << "svec_3.capacity() = "
              << svec_3.capacity() << '\n';
    // output -> svec_3.capacity() = 5

    // -----------------------------------------------

    auto svec_4 = std::move(svec_1);
    // std::vector classes move constructor will be called.
    // "svec" will become moved-from state. 
    // like default initialized state for std::vector class

    std::cout << "svec_4.capacity() = "
          << svec_4.capacity() << '\n';
    // output -> svec_4.capacity() = 5

    std::cout << "svec_1.capacity() = "
      << svec_1.capacity() << '\n';
    // output -> svec_1.capacity() = 0
    
    // -----------------------------------------------
  }
*/

/*
  #include <vector>
  #include <type_traits>  // std::is_same

  class Myclass {
  public:
    Myclass(int);
  };

  int main()
  {
    // --------------------------------------------------

    std::vector<std::string> svec(100);   
    // fill constructor
    // there are 100 default constructed 
    // "std::string" objects in "svec"

    std::vector<Myclass> m_vec(100);  // syntax error
    // error: no matching function for call to 'Myclass::Myclass()'

    // because of there is user-defined 
    // Myclass::Myclass(int) constructor,  
    // Myclass's default constructor is not declared.

    // --------------------------------------------------

    std::vector<std::string> svec_2(10, "xyz");
    // fill constructor

    std::cout << "svec_2.size() = " << svec_2.size() << '\n';
    // output -> svec_2.size() = 10

    for (auto elem : svec_2)
      std::cout << elem << ' '; 
    // output -> xyz xyz xyz xyz xyz xyz xyz xyz xyz xyz
    std::cout << '\n';

    // --------------------------------------------------

    std::vector<int> ivec(20);
    // fill constructor
    std::cout << "ivec.size = " << ivec.size() << '\n';
    // output -> ivec.size = 20

    std::vector<int> ivec_2{ 20 };
    // std::initializer_list parameter constructor
    std::cout << "ivec_2.size() = " << ivec_2.size() << '\n';
    // output -> ivec_2.size() = 1

    // --------------------------------------------------

    std::vector<int> ivec_3(10, 11);
    // fill constructor

    std::cout << "ivec_3.size() = " << ivec_3.size() << '\n';
    // output -> ivec_3.size() = 10

    for (auto elem : ivec_3)
      std::cout << elem << ' ';
    // output -> 11 11 11 11 11 11 11 11 11 11
    std::cout << '\n';


    std::vector<int> ivec_4{ 10, 11 };
    // std::initializer_list parameter constructor

    std::cout << "ivec_4.size() = " << ivec_4.size() << '\n';	
    // output -> ivec_4.size() = 2

    for (auto elem : ivec_4)
      std::cout << elem << ' ';
    // output -> 10 11
    std::cout << '\n';

    // --------------------------------------------------

    std::vector<int> ivec_5{ 11, 22, 33, 44, 55 }; 

    std::vector ivec_6{ 11, 22, 33, 44, 55 }; 
    // CTAD(Class Template Argument Deduction)

    constexpr bool b1 = 
      std::is_same_v<decltype(ivec_5), decltype(ivec_6)>;
    // b1 -> true

    // --------------------------------------------------
  }
*/

/*
  #include <vector>
  #include <list>
  #include <string>
  #include <cstddef>  // std::size_t

  int main()
  {
    std::list<int> ilist{ 11, 22, 33, 44, 55, 66, 77 };

    // ---------------------------------------------------

    // std::vector<int> ivec{ ilist };  // syntax error
    // error: no matching function for call to 
    // 'std::vector<int>::vector(
    //      <brace-enclosed initializer list>)'

    // assigning different containers to each other
    // is syntax error

    // ---------------------------------------------------

    std::vector<int> ivec_2{ ilist.begin(), ilist.end() };
    // range parameter constructor 

    std::cout << "ivec_2.size() = " 
              << ivec_2.size() << '\n';
    // output -> ivec_2.size() = 7

    for (auto elem : ivec_2)
      std::cout << elem << ' '; 
    // output -> 11 22 33 44 55 66 77
    std::cout << '\n';

    // ---------------------------------------------------

    std::vector<double> dvec{ ilist.begin(), ilist.end() };
    // range parameter constructor

    std::cout << "dvec.size() = " 
              << dvec.size() << '\n';
    // output -> dvec.size() = 7

    for (auto elem : dvec)
      std::cout << elem << ' '; 
    // output -> 11 22 33 44 55 66 77
    std::cout << '\n';

    // ---------------------------------------------------

    std::list<const char*> cstr_list{ 
      "world", "universe", "galaxy" };

    std::vector<std::string> svec{ 
      cstr_list.begin(), cstr_list.end() };
    // range parameter constructor

    std::cout << "svec.size() = " 
              << svec.size() << '\n';
    // output -> svec.size() = 3

    for (auto elem : svec)
      std::cout << elem << ' ';
    // output -> world universe galaxy
    std::cout << '\n';

    // ---------------------------------------------------

    int i_arr[]{ 111, 222, 333, 444, 555 };

    std::size_t i_arr_size = sizeof(i_arr) / sizeof(*i_arr);

    std::vector<int> ivec_3{ i_arr, i_arr + i_arr_size };
    // range parameter constructor

    std::cout << "ivec_3.size() = " 
              << ivec_3.size() << '\n';
    // output -> ivec_3.size() = 5

    for (auto elem : ivec_3)
      std::cout << elem << ' ';
    // output -> 111 222 333 444 555
    std::cout << '\n';

    // ---------------------------------------------------

    std::vector<int> ivec_4{ std::begin(i_arr), std::end(i_arr)};
    // range parameter constructor

    std::cout << "ivec_4.size() = " 
              << ivec_4.size() << '\n';
    // output -> ivec_4.size() = 5

    for (auto elem : ivec_4)
      std::cout << elem << ' ';
    // output -> 111 222 333 444 555
    std::cout << '\n';

    // ---------------------------------------------------
  }
*/

/*
  std::vector container constructors
  ----------------------------------
  - copy constructor
  - move constructor
  - default constructor
  - (std::size_t)             -> fill constructor
  - (std::size_t, T)          -> fill constructor
  - (std::initializer_list)   -> initializer_list cosntructor
  - (iter_beg, iter_end)      -> range constructor
*/

/*
  // global "std::size" and "std::empty" functions

  #include <vector>   // std::size, std::empty

  int main()
  {
    std::vector<int> ivec;


    std::cout << "std::size(ivec) = " 
              << std::size(ivec) << '\n';
    // output -> std::size(ivec) = 0

    std::cout << "std::empty(ivec) = " 
              << std::empty(ivec) << '\n';
    // output -> std::empty(ivec) = 1
  }
*/

/*
  // global "std::data" function template
  // returns a pointer to the block of memory 
  // containing the elements of the range. 

  #include <vector>   // std::data

  int main()
  {
    std::vector<int> ivec(10);

    auto ivec_ptr_1 = std::data(ivec);
    auto ivec_ptr_2 = ivec.data();

    std::cout << "&ivec[0] = " << &ivec[0] << '\n';
    // output -> &ivec[0] = 0x2297f322b80
    std::cout << "ivec_ptr_1 = " << ivec_ptr_1 << '\n';
    // output -> ivec_ptr_1 = 0x2297f322b80
    std::cout << "ivec_ptr_2 = " << ivec_ptr_2 << '\n';
    // output -> ivec_ptr_2 = 0x2297f322b80
  }
*/

/*
  #include <vector>

  int main()
  {
    std::vector<int> ivec(20);

    auto current_capacity = ivec.capacity();
    int reallocation_count{};

    while (ivec.size() < 2000) 
    {
      ivec.push_back(1);
      // when size reaches to capacity
      // reallocation will occur
      // (implementation defined - 1.5x or 2x the capacity)

      if (ivec.capacity() != current_capacity) 
      {
        std::cout << "reallocation_count = "
                  << ++reallocation_count
                  << ", size = " << ivec.size();

        std::cout << ", new capacity = " 
                  << ivec.capacity() << '\n';

        current_capacity = ivec.capacity();
      }
    }
    // output ->
    //  reallocation_count = 1, size = 21, new capacity = 40
    //  reallocation_count = 2, size = 41, new capacity = 80
    //  reallocation_count = 3, size = 81, new capacity = 160
    //  reallocation_count = 4, size = 161, new capacity = 320
    //  reallocation_count = 5, size = 321, new capacity = 640
    //  reallocation_count = 6, size = 641, new capacity = 1280
    //  reallocation_count = 7, size = 1281, new capacity = 2560
  }
*/

/*
  #include <vector>

  int main()
  {
    std::vector<int> ivec(20);
    ivec.reserve(1200);   
    // std::vector containers "reserve" member function 

    auto current_capacity = ivec.capacity();
    int reallocation_count{};

    while (ivec.size() < 2'000) 
    {
      ivec.push_back(1);

      if (ivec.capacity() != current_capacity)
      {
        std::cout << "reallocation_count = "
                  << ++reallocation_count
                  << ", size = " << ivec.size();

        std::cout << ", new capacity = " 
                  << ivec.capacity() << '\n';

        current_capacity = ivec.capacity();
      }
    }
    // output ->
    //  reallocation_count = 1, size = 1201, new capacity = 2400
  }
*/

/*
  #include <vector>

  int main()
  {
    // -----------------------------------------------------

    std::vector<int> ivec(100'000, 5);
    std::cout << "ivec.size() = " 
              << ivec.size() 
              << ", ivec.capacity() = " 
              << ivec.capacity() << '\n';
    // output -> ivec.size() = 100000, ivec.capacity() = 100000

    ivec.resize(10);
    std::cout << "ivec.size() = " 
              << ivec.size() 
              << ", ivec.capacity() = " 
              << ivec.capacity() << '\n';
    // output -> ivec.size() = 10, ivec.capacity() = 100000

    ivec.shrink_to_fit();
    std::cout << "ivec.size() = " 
          << ivec.size() 
          << ", ivec.capacity() = " 
          << ivec.capacity() << '\n';
    // output -> ivec.size() = 10, ivec.capacity() = 10

    // -----------------------------------------------------
    // -----------------------------------------------------

    // before "shrink_to_fit" member function, 
    // "swap" member function is being used.

    std::vector<int> ivec2(200'000, 5);
    ivec2.resize(10);

    std::cout << "ivec2.size() = " 
        << ivec2.size() 
        << ", ivec2.capacity() = " 
        << ivec2.capacity() << '\n';
    // output -> ivec2.size() = 10, ivec2.capacity() = 10


    std::vector<int>{ ivec2 }.swap(ivec2);
    // std::vector class has a constructor,
    // "vector( const vector& other )"
    // temporary object is being created and 
    // "swap" member function is being called.

    std::cout << "ivec2.size() = " 
        << ivec2.size() 
        << ", ivec2.capacity() = " 
        << ivec2.capacity() << '\n';
    // output -> ivec2.size() = 10, ivec2.capacity() = 10
    
    // -----------------------------------------------------
  }
*/

/*
  #include <vector>
  #include <string>

  int main()
  {
    std::vector<int> ivec{ 11, 22, 33, 44, 55 };
      
    // --------------------------------------------------

    // compiler written range based for loop -> Scenario_1 
    for (auto elem : ivec);

    for (auto it = ivec.begin(); it != ivec.end(); ++it) 
      auto elem = *it;
    
    // --------------------------------------------------

    // compiler written range based for loop -> Scenario_2
    for (const auto elem : ivec);

    for (auto c_it = ivec.begin(); c_it != ivec.end(); ++c_it)
      const auto elem = *c_it;

    // --------------------------------------------------

    // compiler written range based for loop -> Scenario_3
    for (const auto& elem : ivec);

    for (auto it = ivec.begin(); it != ivec.end(); ++it)
      const auto& elem = *it;
  
    // --------------------------------------------------

    // compiler written range based for loop -> Scenario_4
    for (auto&& elem : ivec) {}

    for (auto it = ivec.begin(); it != ivec.end(); ++it) 
      auto&& elem = *it;
    
    // --------------------------------------------------
  }
*/

/*
  #include <vector>
  #include <string>
  #include <algorithm>  // std::copy
  #include <iterator>   // std::back_inserter

  int main()
  {
    std::vector<int> ivec{ 11, 22, 33, 44, 55 };
    // "front" and "back" member functions 
    // are reaching first and the last elements 
    // of the std::vector with reference semantics.

    ivec.front() += 99;
    ivec.back() += 9999;

    for (auto elem : ivec)
      std::cout << elem << ' ';
    // output -> 110 22 33 44 10054

    // ----------------------------------------------------
    
    std::vector<std::string> svec;

    auto beg_iter = svec.begin();   // NOT undefined behaviour
    auto end_iter = svec.end();     // NOT undefined behaviour

    *beg_iter;      // undefined behaviour(UB)
    *end_iter;      // undefined behaviour(UB)

    bool b1 = (beg_iter == end_iter);
    // NOT undefined behaviour result is true

    std::distance(beg_iter, end_iter);
    // NOT undefined behaviour result is 0

    // ----------------------------------------------------

    std::vector<int> ivec_x;
    std::vector<int> ivec_y;

    std::copy(ivec_x.begin(), ivec_x.end(),   // source
              std::back_inserter(ivec_y));    // destination
    // NOT undefined behaviour 
    // because can not get into while loop in 
    // std::copy function.

    // ----------------------------------------------------
  }
*/

/*
  #include <vector>

  int main()
  {
    std::vector<int> ivec(5, 11);

    // --------------------------------------------------

    std::cout << "ivec.size() = " 
              << ivec.size() 
              << ", ivec.capacity() = " 
              << ivec.capacity() << '\n';
    // output -> ivec.size() = 5, ivec.capacity() = 5

    for (auto elem : ivec)
      std::cout << elem << ' ';
    // output -> 11 11 11 11 11
    std::cout << '\n';

    // --------------------------------------------------

    ivec.resize(10);
    std::cout << "ivec.size() = " 
          << ivec.size() 
          << ", ivec.capacity() = " 
          << ivec.capacity() << '\n';
    // output -> ivec.size() = 10, ivec.capacity() = 10

    for (auto elem : ivec)
      std::cout << elem << ' ';
    // output -> 11 11 11 11 11 0 0 0 0 0
    std::cout << '\n';

    // --------------------------------------------------

    ivec.resize(15, 22);
    std::cout << "ivec.size() = " 
          << ivec.size() 
          << ", ivec.capacity() = " 
          << ivec.capacity() << '\n';
    // output -> ivec.size() = 15, ivec.capacity() = 20

    for (auto elem : ivec)
      std::cout << elem << ' ';
    // output -> 11 11 11 11 11 0 0 0 0 0 22 22 22 22 22
    std::cout << '\n';

    // --------------------------------------------------

    // deleting elements from container 
    // with "resize" member function.

    ivec.resize(3);
    std::cout << "ivec.size() = " 
          << ivec.size() 
          << ", ivec.capacity() = " 
          << ivec.capacity() << '\n';
    // output -> ivec.size() = 3, ivec.capacity() = 20

    for (auto elem : ivec)
      std::cout << elem << ' ';
    // output -> 11 11 11
    std::cout << '\n';

    // --------------------------------------------------

    // deleting every element in container
    // with "resize(0)" is valid but better using
    // "clear member function"

    ivec.resize(0);
    std::cout << "ivec.size() = " 
          << ivec.size() 
          << ", ivec.capacity() = " 
          << ivec.capacity() << '\n';
    // output -> ivec.size() = 0, ivec.capacity() = 20

    for (auto elem : ivec)
      std::cout << elem << ' ';
    // output -> 

    // --------------------------------------------------
  }
*/

/*
  #include <vector>

  int main()
  {
    std::vector<int> ivec;
    ivec.reserve(10);

    for (int i = 0; i < 10; ++i)
      ivec.push_back(i);

    for (auto elem : ivec)
      std::cout << elem << ' ';
    // output -> 0 1 2 3 4 5 6 7 8 9
  }
*/

/*
  #include <vector>
  #include <string>
  #include <cstddef>  // std::size_t
  #include <utility>  // std::move

  int main()
  {
    std::vector<std::string> svec{ 
      "istanbul", "ankara", "izmir", "eskisehir", "rize" };
      
    std::vector<std::string> dest_vec;

    for (std::size_t i{}; i < svec.size(); ++i)
      dest_vec.push_back(std::move(svec[i]));


    std::cout << "svec.size() = " << svec.size() << '\n';
    // output -> svec.size() = 5

    // svec container's size is 5 but std::string objects 
    // in svec container are in moved-from state.

    for (const auto& str : svec) 
      std::cout << str.size() << ' ';
    // output -> 0 0 0 0 0   
    
    // (std::string's "size" member function )
  }
*/

/*
  #include <vector>
  #include <string>

  int main()
  {
    std::vector<std::string> svec{ 
      "istanbul", "ankara", "izmir", "eskisehir" };

    for (auto str : svec)
      std::cout << str << ' ';
    // output -> istanbul ankara izmir eskisehir
    std::cout << '\n';

    // -------------------------------------------------

    svec = { "samsun", "erzurum", "sivas" };
    // std::initializer list assignment

    for (auto str : svec)
      std::cout << str << ' ';
    // output -> samsun erzurum sivas
  }
*/

/*
  #include <vector>
  #include <list>
  #include <string>

  int main()
  {
    std::list<std::string> slist{ 
      "istanbul", "ankara", "izmir", "eskisehir" };

    std::vector<std::string> svec;

    // -----------------------------------------------

    svec.assign(slist.begin(), slist.end());
    // assing member function with range parameters

    for (auto str : svec)
      std::cout << str << ' ';
    std::cout << '\n';
    // output -> istanbul ankara izmir eskisehir

    // -----------------------------------------------

    svec.assign(5, "universe");
    // assign member function with fill parameters

    for (auto str : svec)
      std::cout << str << ' ';
    // output -> universe universe universe universe universe
    std::cout << '\n';

    // -----------------------------------------------
  }
*/

/*
  // insert member functions of std::vector are returning
  // an iterator (inserted element(s) address)

  #include <vector>
  #include <iterator>   // std::next

  int main()
  {
    std::vector<int> ivec{ 
      11, 22, 33, 44, 55, 66, 77, 88, 99 };

    // ----------------------------------------------------

    ivec.insert(ivec.begin(), 999);
    // inserting element to the beginning of the container

    for (auto elem : ivec)
      std::cout << elem << ' ';
    // output -> 999 11 22 33 44 55 66 77 88 99
    std::cout << '\n';

    // ----------------------------------------------------

    ivec.insert(ivec.begin() + 1, 777);
    ivec.insert(std::next(ivec.begin()), 777);
    // Those 2 lines are equivalent.
    // inserting element to the 2nd position in container

    for (auto elem : ivec)
      std::cout << elem << ' ';
    // output -> 999 777 777 11 22 33 44 55 66 77 88 99
    std::cout << '\n';

    // ----------------------------------------------------

    ivec.insert(ivec.end(), 111);
    ivec.push_back(111);
    // Those 2 lines are equivalent.
    // inserting element to the end of the container

    for (auto elem : ivec)
      std::cout << elem << ' ';
    // output -> 999 777 777 11 22 33 44 55 66 77 88 99 111 111
    std::cout << '\n';

    // ----------------------------------------------------
  }
*/

/*
  #include <vector>
  #include <list>

  int main()
  {
    std::vector<int> ivec{ 11, 22, 33, 44, 55 };

    // ----------------------------------------------------

    ivec.insert(ivec.begin(), { 66, 77, 88, 99 });
    // inserting std::initializer_list to the beginning 
    // of the container

    for (auto elem : ivec)
      std::cout << elem << ' ';
    // output -> 66 77 88 99 11 22 33 44 55
    std::cout << '\n';

    // ----------------------------------------------------

    ivec.insert(ivec.begin(), 3 , 222);
    // inserting 3 elements with value 222 to the beginning

    for (auto elem : ivec)
      std::cout << elem << ' ';
    // output -> 222 222 222 66 77 88 99 11 22 33 44 55
    std::cout << '\n';

    // ----------------------------------------------------

    std::list<int> ilist{ 20, 30, 40 };
    ivec.insert(ivec.begin(), ilist.begin(), ilist.end());
    // inserting elements from list container to the beginning
    // of the vector container

    for (auto elem : ivec)
      std::cout << elem << ' ';
    // output -> 20 30 40 222 222 222 66 77 88 99 11 22 33 44 55

    // ----------------------------------------------------
  }
*/

/*
  #include <vector>
  #include <list>
  #include <string>
  #include <iterator>   // std::distance

  int main()
  {
    std::vector<int> ivec{ 11, 22, 33, 44, 55 };

    // -------------------------------------------------

    auto iter_added = ivec.insert(ivec.begin() + 1, 88);

    std::cout << *iter_added << '\n';	
    // output -> 88
    std::cout << std::distance(ivec.begin(), iter_added) << '\n';
    // output -> 1

    // -------------------------------------------------

    iter_added = ivec.insert(ivec.begin() + 1, { 55, 66, 77 });
    std::cout << *iter_added << '\n';	
    // output -> 55
    std::cout << std::distance(ivec.begin(), iter_added) << '\n';
    // output -> 1

    // 3 elements from std::initializer_list added 
    // and an iterator to a first element added is returned.

    // -------------------------------------------------

    std::vector<std::string> svec{ "hello", "world" };

    svec.emplace(svec.begin() + 1, 10, 'T');
    // (20, 'T') parameters will be pass 
    // to std::string's constructor
    // which will be constructed in 2nd position of the vector.

    for (auto str : svec)
      std::cout << str << ' ';
    // output -> hello TTTTTTTTTT world
    std::cout << '\n';

    // -------------------------------------------------

    // C_string("istanbul") parameter will be pass to 
    // std::string(const char*) constructor 
    // which will be constructed at end of the vector.

    svec.emplace_back("istanbul");
    for (auto str : svec)
      std::cout << str << ' ';
    // output -> hello TTTTTTTTTT world istanbul
    
    // -------------------------------------------------
  }
*/

/*
  // "pop_back" member function is constant time operation O(1)
  // "pop_back" member function will return void

  #include <vector>

  int main()
  {
    std::vector<int> ivec{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };

    while (!ivec.empty())
    {
      for (auto elem : ivec)
        std::cout << elem << ' ';
      std::cout << '\n';

      ivec.pop_back();
    }
    // output ->
    //  1 2 3 4 5 6 7 8 9
    //  1 2 3 4 5 6 7 8
    //  1 2 3 4 5 6 7
    //  1 2 3 4 5 6
    //  1 2 3 4 5
    //  1 2 3 4
    //  1 2 3
    //  1 2
    //  1
  }
*/

/*
  #include <vector>
  #include <iterator>   // std::prev

  int main()
  {
    std::vector<int> ivec{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };

    for (auto elem : ivec)
      std::cout << elem << ' ';
    // output -> 1 2 3 4 5 6 7 8 9
    std::cout << '\n';

    // -------------------------------------------------

    auto iter_deleted = ivec.erase(ivec.begin());

    for (auto elem : ivec)
      std::cout << elem << ' ';
    // output -> 2 3 4 5 6 7 8 9
    std::cout << '\n';

    std::cout << "iterator position after deletion  = " 
              << *iter_deleted << '\n';
    // output -> iterator position after deletion  = 2

    // -------------------------------------------------

    ivec.erase(std::prev(ivec.end()));

    for (auto elem : ivec)
      std::cout << elem << ' ';
    // output -> 2 3 4 5 6 7 8
    std::cout << '\n';

    // -------------------------------------------------

    ivec = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

    while (!ivec.empty()) 
    {
      for (auto i : ivec) 
        std::cout << i << ' ';
      std::cout << '\n';
      
      ivec.erase(ivec.begin());
    }
    // output ->
    //  1 2 3 4 5 6 7 8 9
    //  2 3 4 5 6 7 8 9
    //  3 4 5 6 7 8 9
    //  4 5 6 7 8 9
    //  5 6 7 8 9
    //  6 7 8 9
    //  7 8 9
    //  8 9
    //  9

    // -------------------------------------------------
  }
*/

/*
  #include <vector>
  #include <iterator>  // std::next, std::prev

  int main()
  {
    using namespace std;

    vector<int> ivec{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    
    // -----------------------------------------------------

    ivec.erase(ivec.begin(), ivec.begin() + 3);
    // range parameter "erase" member function

    for (auto i : ivec) 
      std::cout << i << ' ';
    // output -> 4 5 6 7 8 9
    std::cout << '\n';

    // -----------------------------------------------------

    ivec.erase(ivec.begin(), std::next(ivec.begin(), 3));
    // range parameter "erase" member function
    
    for (auto i : ivec) 
      std::cout << i << ' ';
    // output -> 7 8 9
    std::cout << '\n';

    // -----------------------------------------------------

    // deleting only first and the last element from the vector

    ivec = { 11, 22, 33, 44, 55, 66, 77, 88, 99 };

    ivec.erase(std::next(ivec.begin()), std::prev(ivec.end()));
    for (auto i : ivec) 
      std::cout << i << ' ';
    // output -> 11 99
    std::cout << '\n';

    // -----------------------------------------------------
  }
*/

/*
  // erasing all elements from the container

  #include <vector>

  int main()
  {
    // ------------------------------------------------

    std::vector<int> ivec = { 11, 22, 33, 44, 55, 66, 77, 88, 99 };
    std::cout << "ivec.size() = " << ivec.size() << '\n';
    // output -> ivec.size() = 9

    ivec.clear();
    // "clear" member function does not have a return type

    std::cout << "ivec.size() = " << ivec.size() << '\n';
    // output -> ivec.size() = 0

    // ------------------------------------------------

    ivec = { 11, 22, 33, 44, 55, 66, 77, 88, 99 };
    std::cout << "ivec.size() = " << ivec.size() << '\n';
    // output -> ivec.size() = 9

    ivec.erase(ivec.begin(), ivec.end());
    // "erase" member function with range parameter
    std::cout << "ivec.size() = " << ivec.size() << '\n';
    // output -> ivec.size() = 0

    // ------------------------------------------------

    ivec = { 11, 22, 33, 44, 55, 66, 77, 88, 99 };
    std::cout << "ivec.size() = " << ivec.size() << '\n';
    // output -> ivec.size() = 9

    ivec.resize(0);
    // "resize" member function with "0" as an argument. 
    std::cout << "ivec.size() = " << ivec.size() << '\n';
    // output -> ivec.size() = 0

    // ------------------------------------------------

    ivec = { 11, 22, 33, 44, 55, 66, 77, 88, 99 };
    std::cout << "ivec.size() = " << ivec.size() << '\n';
    // output -> ivec.size() = 9

    ivec = {};    
    // using empty initalizer list
    std::cout << "ivec.size() = " << ivec.size() << '\n';
    // output -> ivec.size() = 0

    // ------------------------------------------------

    ivec = { 11, 22, 33, 44, 55, 66, 77, 88, 99 };
    std::cout << "ivec.size() = " << ivec.size() << '\n';
    // output -> ivec.size() = 9

    ivec = std::vector<int>{};    
    // passing empty temporary std::vector object
    // to copy asssignment operator function
    std::cout << "ivec.size() = " << ivec.size() << '\n';
    // output -> ivec.size() = 0

    // ------------------------------------------------
  }
*/

/*
  #include <vector>
  #include <string>
  #include <utility>  // std::swap

  int main()
  {

    std::vector<std::string> svec_1(100'000, "hello");
    std::vector<std::string> svec_2(100'000, "world");

    svec_1.swap(svec_2);
    // swap member function of std::vector class
    std::swap(svec_2, svec_1);
    // global std::swap function 

    // pointers of the containers will be swapped.
  }
*/

/*
  std::vector<bool> is a partial specialization.
    - not holding bool variables, holding bits.
    - so 10k bool variables can be stored in 1250 bytes.
*/

/*
  #include <vector>

  int main()
  {
    std::vector<int> ivec;
    std::vector<bool> bvec;

    // -------------------------------------------------

    ivec.flip();  // syntax error
    // error: 'class std::vector<int>' has no member named 'flip'
    
    // std::vector<int> specialization does not have 
    // "flip" member function in its interface.

    bvec.flip();
    // std::vector<bool> specialization does have
    // "flip" member function in its interface.

    // -------------------------------------------------

    bvec.data();  // syntax error
    // error: use of deleted function 
    // 'void std::vector<bool, _Alloc>::data()

    // std::vector<bool> partial specialization's 
    // "data" member function is deleted.
    // because of it is not holding bool variables
    // returning bool* is not possible.

    ivec.data();
    // std::vector<int> specialization 
    // does have "data" member function which is returning int* 

    // -------------------------------------------------
  }
*/

/*
  #include <vector>
  #include <cstdio>   // std::printf

  void print_array(const int* p_arr, size_t arr_size)
  {
    while (arr_size--)
      std::printf("%d ", *p_arr++);
  }

  int main()
  {
    std::vector<int> ivec{ 
        11, 22, 33, 44, 55, 66, 77, 88, 99 };

    print_array(ivec.data(), ivec.size());
    // output -> 11 22 33 44 55 66 77 88 99

    // "data" member function can be passed to C api functions
  }
*/

/*
  #include <vector>

  int main()
  {
    std::vector<bool> ivec{ 
      false, false, false, false, false, false, false, false };

    // -----------------------------------------------------

    // operator[] function of 
    // std::vector<bool> partial specialization 
    // is returning a proxy class.

    ivec[2] = true;
    ivec[2].operator=(true);
    // Those 2 lines are equivalent.

    // -----------------------------------------------------

    auto proxy_class = ivec[3];
    // "proxy_class"'s type is std::vector<bool>::reference
    proxy_class = true;

    // -----------------------------------------------------

    for (const auto& val : ivec)
      std::cout << val << ' ';
    // output -> 0 0 1 1 0 0 0 0
  }
*/

/*
  // primary template for Vector
  template <typename T, typename A>
  class Vector {};

  // partial specialization for Vector<bool, A>
  template <typename A>
  class Vector<bool, A> {};
  
  // mental model for std::vector::reference proxy class
  // in std::vector<bool> partial specialization
  class BVector {
  private:
    unsigned char m_buffer[1000]{};   // 8000 bits
  public:
    class Reference {};
    Reference& operator[](size_t N);  // returning bits
  };
*/