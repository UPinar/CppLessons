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