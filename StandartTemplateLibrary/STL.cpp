#include <iostream>

/*
	===================================
	| Standart Template Library (STL) |
	===================================
*/

/*
	Standart Template Library (STL)
	--------------------------------------
	-> containers[data structures]	
		(class templates)
	-> iterators					
		(class templates or raw pointers)
	-> algorithms					
		(function templates, parameter variables are iterator variables)
*/

/*
	sequance containers
	----------------------------------
	C Arrays
	std::vector
	std::deque
	std::list
	std::forward_list					(C++11)
	std::string
	std::array								(C++11)
	
	associative containers
	----------------------------------
	std::set
	std::multiset
	std::map
	std::multimap
	
	unordered associative containers
	----------------------------------
	std::unordered_set				(C++11)
	std::unordered_multiset		(C++11)
	std::unordered_map				(C++11)
	std::unordered_multimap		(C++11)
*/

/*
	-> C arrays are fixed arrays.
	-> std::vector is a dynamic array.
	-> std::deque is double ended que. Vector of vectors..
	-> std::list is doubly linked list.
	-> std::forward_list is linked list.
	-> std::string is a dynamic array.
	-> std::array is C arrays wrapper.

	-> std::set is binary tree (contains only keys)
	-> std::multiset is a binary tree and can hold same keys multiple times.
	-> std::map is holding (key - value) pairs. Search for key reach value.
	-> std::multimap can hold multiple same keys. ([same] key - value) pairs.
	-> assosiative containers --> O(log n) -> binary search tree

	-> unordered associative containers -> O(1) -> hash tables
*/

/*
	container adaptors
	-----------------------
	std::stack					-> stack interface. Last In First Out(LIFO)
	std::queue					-> tail interface. 	First In First Out
	std::priority_queue	-> high priority first out.
*/

/*
	// Mental Model for containers

	template <typename T>
	class Vector {
	public:
		void push_back(const T&);
		void push_back(T&&);
		void pop_back();
		std::size_t size()const;
		bool empty()const;
	
		// Nested type iterator interface
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
		// returns the first elements position
		iterator end();		
		// returns the next of the last elements position (sentinel)
	};
*/

/*
	#include <vector>
	#include <list>
	#include <string>
	
	// Print is an algorithm, generic function template
	// wants 1 or more than 1 range from client.
	template <typename Iter>
	void Print(Iter beg, Iter end)
	{
		while (beg != end) {
			std::cout << *beg++ << ' ';
		}
		std::cout << '\n';
	}
	
	// compiler wrote Print function for 
	// [Print(mylist.begin(), mylist.end())] statement

	using namespace std;
	void Print(list<string>::iterator beg, list<string>::iterator end)
	{
		while (beg != end) {
			std::cout << *beg++ << ' ';
		}
		std::cout << '\n';
	}
	
	int main()
	{
		int a[5]{ 1, 2, 3, 4, 5 };
		Print(a, a + 5);							// output -> 1 2 3 4 5
		Print(a + 1, a + 4);					// output -> 2 3 4
	
		std::vector<int> ivec{ 10, 20, 30, 40, 50 };
		Print(ivec.begin(), ivec.end());		// output -> 10 20 30 40 50
	
		std::list<std::string> mylist{ "hey", "yoo", "hello", "world"};
		Print(mylist.begin(), mylist.end());	// output -> hey yoo hello world 
	}
*/

/*
	#include <algorithm>
	#include <vector>
	
	int main()
	{
		std::vector<int> ivec{10, 3, 54, 23, 26, 98, 63};
	
		std::sort(ivec.begin(), ivec.end());
		// std::sort is an algorithm and function template
	
		std::reverse(ivec.begin(), ivec.end());
		// std::reverse is an algorithm and function template
	}
*/

/*
	template <typename Container>
	void func(Container& c)
	{
		auto iter = c.begin();			// all containers have begin() member function.
		typename C::iterator iter;	// all container have iterator nested type.
		typename C::value_type			// all container have value_type nested type.
	}
*/

/*
	template <typename Iter>
	void func(Iter beg, Iter end)
	{
		typename Iter::value_type;		// all iterator type have a value_type nested type.
	}
*/

/*
	#include <vector>
	int main()
	{
		std::vector<int>::value_type;				// int
		std::vector<int*>::iterator::value_type;	// int*
		// both containers and iterators have a value type
	
		std::vector<int>::pointer;					// int*
		std::vector<int>::reference;				// int&
	}
*/

/*
	=============
	| iterators |
	=============
*/

/*
	#include <vector>
	#include <algorithm>
	
	int main()
	{
		using namespace std;
	
		vector<int> ivec;	// do not have any value in it.
		auto iter = ivec.begin();
		*iter;	// Undefined behaviour
		--iter;	// Undefined behaviour
	
		vector<int> ivec_2(20);
		iter = ivec_2.end();
		*iter;	// Undefined behaviour
		++iter;	// Undefined behaviour
	
		vector ivec_3{ 3, 6, 4, 2, 65, 63, 23, 11 };
		sort(ivec.begin(), ivec.end());	// valid
		sort(ivec.end(), ivec.begin());	// Undefined behaviour
	
		for (auto val : ivec_3)
		{
			cout << val << " ";
		}
	}
*/

/*
	// With modern C++ global inline functions template added
	// gets container as a parameter and called its member function. 
	//	(e.g, begin())

	#include <vector>
	#include <algorithm>
	
	int main()
	{
		using namespace std;
	
		vector<int> ivec{ 2, 54, 6, 7, 8 };
	
		auto iter = ivec.begin();
		auto iter_2 = begin(ivec);
		// These 2 lines are same
	
		// Q1. Why did they add global functions?
	
		int a[] = { 11, 41, 95, 16, 2, 7, 8 };
		// Most important reason is Cstyle arrays are not classes
		// they do not have begin and end member functions.
	
		sort(begin(a), end(a));
	
		for (auto i : a)
			std::cout << i << '\n';
	}
*/

/*
	// global Begin and End functions for C style arrays

	template <typename C>
	typename C::iterator Begin(C& c);
	
	template <typename C>
	typename C::iterator End(C& c);
	
	template <typename T, std::size_t n>
	T* Begin(T(&r)[n])
	{
		return &r[0];
	}
	
	template <typename T, std::size_t n>
	T* End(T(&r)[n])
	{
		return &r[n];
	}
*/

/*
	-----------------------
	| iterator categories |
	-----------------------
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
	#include <forward_list>
	
	int main()
	{
		std::forward_list<int> x(10);	// Single Linked List
		// forward list classes iterators -> forward iterator category
	
		auto iter = x.begin();
		++iter;						// valid
		iter++;						// valid
		*iter;						// valid
		--iter;						// syntax error
	
		auto iter1 = x.begin();
		auto iter2 = x.begin();
	
		auto b = iter1 == iter2;	// valid
		auto c = iter1 < iter2;		// syntax error
	}
*/

/*
	#include <list>
	
	int main()
	{
		std::list<int> x(10);	// Doubly Linked List
		// list classes iterators -> bidirectional iterator category
	
		auto iter = x.begin();
		++iter;						// valid
		iter++;						// valid
		*iter;						// valid
		--iter;						// valid
	
		auto iter1 = x.begin();
		auto iter2 = x.begin();
	
		auto b = iter1 == iter2;	// valid
		auto c = iter1 < iter2;		// syntax error
	}
*/

/*
	#include <vector>
	
	int main()
	{
		std::vector<int> x(10);
		// vector classes iterators -> random-access iterator category
		// its operation interface is same as raw pointers.
	
		auto iter = x.begin();
		++iter;									// valid
		iter++;									// valid
		*iter;									// valid
		--iter;									// valid
	
		iter += 3;							// valid
		auto val = iter[2];			// valid
	
		auto iter1 = x.begin();
		auto iter2 = x.begin();
	
		auto b = iter1 == iter2;	// valid
		auto c = iter1 < iter2;		// valid
	}
*/

/*
	For compile time operations,
	Every iterator type have a nested type called iterator_category.
	Empty classes in STL is used for declaring iterator categories.

	input iterator					-> input_iterator_tag					(Empty class)
	output iterator					-> output_iterator_tag				(Empty class)
	forward iterator				-> forward_iterator_tag				(Empty class)
	bidirectional iterator	-> bidirectional_iterator_tag	(Empty class)
	random-access iterator	-> random_access_iterator_tag	(Empty class)
*/

/*
	#include <vector>
	#include <set>
	#include <forward_list>
	
	// 1.
	// using container = std::vector<int>;

	// 2.
	// using container = std::set<int>;

	// 3.
	using container = std::forward_list<int>;
	
	using iter = container::iterator;
	using cat = iter::iterator_category;
	
	int main()
	{
		std::cout << typeid(cat).name() << '\n';
		// 1. output	-> struct std::random_access_iterator_tag
		// 2. output	-> struct std::bidirectional_iterator_tag
		// 3. output	-> struct std::forward_iterator_tag
	}
*/

/*
	#include <iterator>
	
	// 1.
	// using iter = std::ostream_iterator<int>;

	// 2.
	using iter = std::istream_iterator<int>;

	using cat = iter::iterator_category;
	
	int main()
	{
		std::cout << typeid(cat).name() << '\n';
		// 1. output -> struct std::output_iterator_tag
		// 2. output -> struct std::input_iterator_tag
	}
*/

/*
	#include <type_traits>
	#include <vector>
	#include <list>
	
	template <typename Iter>
	void algo(Iter beg, Iter end)
	{
		static_assert(std::is_same_v<typename Iter::iterator_category, 
									std::random_access_iterator_tag>,
									"only random-access iterators allowed!");
	}
	
	int main()
	{
		std::vector<int> ivec(10);
		algo(ivec.begin(), ivec.end());		// valid
	
		std::list<int> ilist(20);
		algo(ilist.begin(), ilist.end());	// syntax error
		// static_assert failed: 'only random-access iterators allowed!'
	}
*/

/*
	#include <type_traits>
	#include <vector>
	#include <list>
	
	template <typename Iter>
	void algo(Iter beg, Iter end)
	{
		if constexpr (std::is_same_v<typename Iter::iterator_category, std::random_access_iterator_tag>)
		{
			beg += 5;
			// we can use '+=' operator for random-access iterators.
			std::cout << "random-access iterator\n";
		}
		else if constexpr (std::is_same_v<typename Iter::iterator_category, std::bidirectional_iterator_tag>)
		{
			for (int  i = 0; i < 5; i++)
			{
				++beg;
			}
			// we can not use '+=' operator for bidirectional iterators.
			std::cout << "bidirectional iterator\n";
		}
	}
	
	int main()
	{
		std::vector<int> ivec(10);
		algo(ivec.begin(), ivec.end());		// output -> random-access iterator
	
		std::list<int> ilist(20);
		algo(ilist.begin(), ilist.end());	// output -> bidirectional iterator
	}
*/

/*
	------------------
	| copy algorithm |
	------------------
*/

/*
	#include <vector>
	#include <list>
	
	// minimal input iterator can come to 1st template parameter
	// minimal output iterator can come to 2nd template parameter
	template <typename InIter, typename OutIter>
	OutIter Copy(InIter beg, InIter end, OutIter destbeg)
	{
		while (beg != end) {
			*destbeg++ = *beg++;
		}
		return destbeg;
		// If we last wrote to X location. 
		// We will return X + 1's location.
	}
	
	
	int main()
	{
		using namespace std;
	
		vector<int> ivec{ 1, 3, 5, 7, 9, 13 };
		list<int> ilist(6);
	
		Copy(ivec.begin(), ivec.end(), ilist.begin());
	
		// InIter parameter will be		-> vector<int>::iterator
		// OutIter parameter will be	-> list<int>::iterator
	}
*/

/*
	#include <vector>
	#include <list>
	
	template <typename InIter, typename OutIter>
	OutIter Copy(InIter beg, InIter end, OutIter destbeg)
	{
		while (beg != end) {
			*destbeg++ = *beg++;	// because of list is empty
			// *destbeg will be undefined behaviour.
		}
		return destbeg;
	}
	
	int main()
	{
		using namespace std;
	
		vector<int> ivec{ 1, 3, 5, 7, 9, 13 };
		list<int> ilist(6);
		Copy(ivec.begin(), ivec.end(), ilist.begin());
	
		for (auto i : ilist)
			std::cout << i << ' ';
		// output -> 1 3 5 7 9 13
	
	
		list<int> ilist_1;		// Undefined behaviour
		// because of there is no int in list 
		// assignment will be undefined behaviour.
	
		list<int> ilist_2(5);	// Undefined behaviour
		// because of there are 6 int in vector in 6th assignment to list
		// it will be an undefined behaviour
	
		list<int> ilist_3(17);	// No undefined behaviour
	}
*/

/*
	#include <algorithm>
	#include <vector>
	#include <list>
	#include <string>
	
	int main()
	{
		using namespace std;
	
		vector<string> svec{ "hello", "we", "are", "live", "from", "istanbul" };
		list<string> slist(6);
	
		copy(svec.begin(), svec.end(), slist.begin());
	
		for (auto str : slist)
			cout << str << ' ';
		// output -> hello we are live from istanbul
	}
*/

/*
	-------------------------------
	| sort algorithm -> O(nlog n) |
	-------------------------------
*/

/*
	#include <algorithm>
	#include <vector>
	
	int main()
	{
		using namespace std;
	
		vector<int> ivec{ 1, 3, 2, 5, 6, 7, 3, 54, 75, 23, 34, 645, 12 };
	
		sort(ivec.begin(), ivec.end());
	
		for (auto i : ivec)
			std::cout << i << ' ';
		// output -> 1 2 3 3 5 6 7 12 23 34 54 75 645
	}
*/	

/*
	#include <algorithm>
	#include <list>
	
	int main()
	{
		using namespace std;
	
		list<int> ilist{ 1, 3, 2, 5, 6, 7, 3, 54, 75, 23, 34, 645, 12 };
	
		sort(ilist.begin(), ilist.end());	// syntax error
		// its parameter iterator category needs to be minimum 
		// random-access iterator.
		// sort(const _RanIt first, const _RanIt second)
	
		// sorting list(bidirectional iterator) is not possible!!
	}
*/

/*
	------------------------------------------
	| find algorithm (linear search) -> O(n) |
	------------------------------------------
*/

/*
	#include <algorithm>
	#include <vector>
	#include <string>
	
	template <typename InIter, typename Key>
	InIter Find(InIter beg, InIter end, const Key& key)
	{
		while (beg != end) {
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
	
		auto iter = Find(svec.begin(), svec.end(), "years");
		//	auto iter = Find(svec.begin(), svec.end(), "days");
	
		if (iter != svec.end()) {
			std::cout << "has been found -> " << *iter << '\n';
			std::cout << "its length = " << iter->length() << '\n';
			std::cout << "its index = " << iter - svec.begin() << '\n';
	
			// random access iterator supports '-' operator.
		}
		else
			std::cout << "has not been found\n";
	
	
		// before if_with initializer (C++ 17) -> for scope leakage
		//-----------------------------------------------------------
		{
			auto iter = Find(svec.begin(), svec.end(), "become");
			if (iter != svec.end()) {
				std::cout << "has been found -> " << *iter << '\n';
				std::cout << "its length = " << iter->length() << '\n';
				std::cout << "its index = " << iter - svec.begin() << '\n';
	
				// random access iterator supports '-' operator.
			}
			else
				std::cout << "has not been found\n";
		}
	
		// after if_with initializer
		//-------------------------------
	
		if (auto iter = Find(svec.begin(), svec.end(), "days"); iter != svec.end()) {
			std::cout << "has been found -> " << *iter << '\n';
			std::cout << "its length = " << iter->length() << '\n';
			std::cout << "its index = " << iter - svec.begin() << '\n';
	
			// random access iterator supports '-' operator.
		}
		else
			std::cout << "has not been found\n";
	}
*/


/*
	-----------------------------------------------
	| back_inserter and front_inserter algorithms |
	-----------------------------------------------
*/

/*
	#include <algorithm>
	#include <vector>
	
	template <typename InIter , typename OutIter>
	OutIter Copy(InIter beg, InIter end, OutIter destbeg)
	{
		while (beg != end) {
			*destbeg++ = *beg++;
		}
	
		return destbeg;
	}
	
	template <typename C>
	class BackInsertIterator {
	public:
		BackInsertIterator(C &c) : mc(c) {}
	
		BackInsertIterator& operator*()
		{
			return *this;
		}
	
		BackInsertIterator& operator++(int)
		{
			return *this;
		}
	
		BackInsertIterator& operator=(const typename C::value_type& val)
		{
			mc.push_back(val);
			return *this;
		}
	private:
		C& mc;
	};
	
	template <typename C>
	BackInsertIterator<C> BackInserter(C& c)
	{
		return BackInsertIterator<C>(c);
	}
	
	int main()
	{
		using namespace std;
	
		vector x{ 1,4,7,2,4,6,3 };	
		// CTAD applied-> vector instead of vector<int>

		vector<int> y;
		// copy(x.begin(), x.end(), y.begin());	// undefined behaviour
	
		BackInsertIterator<vector<int>> iter{ y };
		// data member mc of BackInsertIterator binds to y(vector<int>)
	
		Copy(x.begin(), x.end(), iter);
	
		// When we call Copy function, normally we increase 
		// both iterators locations to copy items to new container.
		// Back_Inserter wrapping the container that the data will be copied to.
		// we are overloading operator*() and operator++(int) and 
		// return the BackInserter object itself.
		// We basically not doing anything in *destbeg++ = *beg++; statement.
		// only *beg++ is changing.
		// actually happening -> destbeg = *beg++;
		// because both operator*() and operator++(int) functions return *this.
		// and operator=() function calls vector<int>'s push_back() function.
		// which is adding element to the back of the vector
	
		Copy(x.begin(), x.end(), BackInsertIterator<vector<int>>{ y });
		// temp BackInsertIterator<vector<int>> object
	
		Copy(x.begin(), x.end(), BackInserter(y));	// using BackInserter function template
	
		// STL algorithm
		std::copy(x.begin(), x.end(), std::back_inserter(y));
	}
*/

/*
	#include <algorithm>
	#include <string>
	#include <vector>
	#include <list>
	
	int main()
	{
		using namespace std;
	
		vector<string> x{ "hello", "we", "are", "live", "from", "Mars" };
	
		list<string> y;
		list<string> z;
	
		copy(x.begin(), x.end(), back_inserter(y));
	
		std::cout << "list y(back inserter) = ";
		for (auto elem : y)
			std::cout << elem << ' ';
		std::cout << '\n';
		// output -> list y(back inserter) = hello we are live from Mars
	
		copy(x.begin(), x.end(), front_inserter(z));
	
		std::cout << "list z(front inserter) = ";
		for (auto elem : z)
			std::cout << elem << ' ';
		std::cout << '\n';
		// output -> list z(front inserter) = Mars from live are we hello
	
		// operator=() overload is using push_front() member function of the container.
	}
*/

/*
	#include <iterator>
	#include <vector>
	
	int main()
	{
		using namespace std;
	
		vector<int> ivec{ 3, 2, 4, 56, 7, 5, 6 };
		const vector<int>::iterator iter = ivec.begin();
		// top-level const -> vector<int>::iterator is const
		// that will not make the element(int) that iterator points to const.
	
		++iter;			// syntax error
		// calling non const member function with const object(const vector<int>)
		*iter = 54;		// valid	-> return type is (int&)
	
		// Iterator adapter -> const_iterator
		vector<int>::const_iterator citer = ivec.begin();
		// low-level const -> int(element that iterator points to) is const not vector<int>::iterator
	
		++citer;		// valid
		*citer = 23;	// syntax error -> return type is (const int&)
	
	
		auto iter_2 = ivec.begin();		// std::vector<int>::iterator
		auto citer_2 = ivec.cbegin();	// std::vector<int>::const_iterator
		auto citer_3 = ivec.cend();		// std::vector<int>::const_iterator
	
	
		// if our purpose is just accessing the container not mutating
		for (auto iter = ivec.cbegin(); iter != ivec.cend(); ++iter) {
			++* iter;	// syntax error
		}
	}
*/

/*
	==================================
	| iterator manipulator functions |
	==================================
	std::advance
	std::distance
	std::next
	std::prev
	std::iter_swap
*/

/*
	----------------
	| std::advance |
	----------------
*/

/*
	#include <algorithm>
	#include <vector>
	#include <list>
	
	template <typename Iter>
	void func(Iter first, Iter last)
	{
		int n = 5;
		first += n;
		// for random-access iterator this code is valid
		// for bidirectional iterator it will be syntax error!
	
		std::advance(first, n);
		// std::advance can be used for both bidirectional and random-access iterators.
	}
	
	int main()
	{
		using namespace std;
	
		vector<int> ivec(100);
		func(ivec.begin(), ivec.end());
	
		list<int> ilist(100);
		func(ilist.begin(), ilist.end());
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
	
	template <typename Iter>
	void Advance_impl(Iter& iter, int n, std::random_access_iterator_tag)
	{
		std::cout << "random-access iterator\n";
		iter += n;
	}
	
	template <typename Iter>
	void Advance_impl(Iter& iter, int n, std::bidirectional_iterator_tag)
	{
		std::cout << "bidirectional iterator\n";
		while (n--)
			++iter;
	}
	
	// template <typename Iter, typename Diff>
	// void advance(Iter& iter, Diff n)	-> in STL
	
	template <typename Iter>
	void Advance(Iter& iter, int n)
	{
		Advance_impl(iter, n, typename Iter::iterator_category{});
		// if iterator is random-access iterator
		// third parameter will be random_access_iterator_tag
	}
	
	int main()
	{
		using namespace std;
	
		vector<int> x(100);
		auto iter = x.begin();
		Advance(iter, 5);	// output -> random-access iterator
	
		list<int> y(100);
		auto iter_2 = y.begin();
		Advance(iter_2, 5);	// output -> bidirectional iterator
	}
*/

/*
	#include <list>
	#include <algorithm>
	
	int main()
	{
		using namespace std;
	
		list<int> mylist(100);
	
		auto iter = mylist.end();
	
		std::advance(iter, -20);
		// for negative values in 2nd parameter
		// our iterator needs to be minimum bidirectional iterator
	}
*/

/*
	-----------------
	| std::distance |
	-----------------
*/

/*
	#include <algorithm>
	#include <list>
	
	int main()
	{
		using namespace std;
	
		list<string> slist{ "hello", "world", "lets", "have", "lemonade", "in", "sun" };
	
		string str{ "lemonade" };
	
		if (auto iter = std::find(slist.begin(), slist.end(), str); iter != slist.end())
		{
			std::cout << "Found... index = " << std::distance(slist.begin(), iter) << '\n';
			// iter - slist.begin();	syntax error
			// bidirectional iterators does not have operator-() function.
		}
		else {
			std::cout << "Couldn't found";
		}
		// output -> Found... index = 4
	}
*/

/*
	std::advance	-> have a ref parameter, change the value of the iterator that has been sent.
	std::next		-> will return a new iterator.
*/

/*
	--------------------------
	| std::next && std::prev |
	--------------------------
*/

/*
	#include <algorithm>
	#include <list>
	#include <vector>
	
	int main()
	{
		using namespace std;
	
		list<string> slist{ "hello", "world", "lets", "have", "lemonade", "in", "sun" };
	
		std::cout << *std::next(slist.begin(), 2) << '\n';
		// output -> lets
	
		std::cout << *std::next(slist.begin()) << '\n';	// 2nd argument has a default value which is 1.
		// std::cout << *std::next(slist.begin(), 1) << '\n';	
		// Those 2 lines are same
		// output -> world
	
	
		vector<string> svec;
		copy(next(slist.begin(), 3), slist.end(), back_inserter(svec));
	
		for (auto elem : svec)
			std::cout << elem << ' ';
		// output -> have lemonade in sun
	}
*/

/*
	#include <list>
	#include <algorithm>
	
	int main()
	{
		using namespace std;
		list<int> x{ 1, 5, 7, 8, 12, 34, 534, 2, 5 };
	
		list<int> y;
	
		copy(next(x.begin()), prev(x.end()), back_inserter(y));
	
		for (auto elem : y)
			std::cout << elem << ' ';
		// output -> 5 7 8 12 34 534 2
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
	#include <algorithm>

	template <typename T>
	void Swap(T& t, T& t2)
	{
		T temp{ std::move(t1) };
		t1 = std::move(t2);
		t2 = std::move(temp);
	}

	template <typename IterX, typename IterY>
	void IterSwap(IterX x, IterY y)
	{
		Swap(*x, *y);
	}
	// iter_swap function template is calling Swap function template
	// which has a 1 template parameter so when we dereference the iterator
	// types needs to be same

	
	int main()
	{
		using namespace std;
		list<int> x{ 1, 2, 3, 4 };
		vector<int> y{ 9, 8, 7, 6 };
	
		iter_swap(x.begin(), next(y.begin()));
	
		for (auto elem : x)
			std::cout << elem << ' ';
		// output -> 8 2 3 4
	
		std::cout << '\n';
	
		for (auto elem : y)
			std::cout << elem << ' ';
		// output -> 9 1 7 6
	
		// Iterator categories can be different,
		// but the dereference of the iterator categories have to be same.
		//  *x.begin() -> int
		//	*y.begin() -> int

		int a[] = { 3, 6, 7 };
		double b[] = { 4.5, 7.8, 9.2 };

		iter_swap(begin(a), begin(b));	// syntax error
	}
*/

/*
	----------------------------------------
	| reverse_iterator -> iterator adapter |
	----------------------------------------
	// minimum bidirectional iterator
*/

/*
	#include <vector>
	
	template <typename Iter>
	void display_range(Iter beg, Iter end)
	{
		while (beg != end) {
			std::cout << *beg++ << ' ';
		}
		std::cout << '\n';
	}
	
	int main()
	{
		using namespace std;
	
		vector<int> ivec{ 3, 6, 9, 12, 15, 18 };
	
		display_range(ivec.begin(), ivec.end());
		// output -> 3 6 9 12 15 18
	
		display_range(ivec.rbegin(), ivec.rend());
		// output -> 18 15 12 9 6 3
	
		// ivec.rbegin() and ivec.rend() functions will return reverse_iterator
		auto iter = ivec.rbegin(); // iters type is -> std::reverse_iterator
	
		std::cout << *iter << '\n';	// output -> 18
		++iter;
		std::cout << *iter << '\n';	// output -> 15
	
		// reverse iterator is wrapping an iterator
	}
*/

/*
	#include <vector>
	#include <algorithm>
	
	int main()
	{
		using namespace std;
	
		vector<int> ivec{ 3, 6, 9, 12, 15, 18 };
	
		auto riter = ivec.rbegin();		// riter's is returning 18's position.
	
		auto iter = riter.base();		// iter is returning ivec.end() position
		// base function returning iterator NOT reverse_iterator
	
		cout << boolalpha;
		cout << (iter == ivec.end()) << '\n';	// output -> true
	}
*/

/*
	#include <vector>
	#include <algorithm>
	
	template <typename Iter>
	void display_range(Iter beg, Iter end)
	{
		while (beg != end) {
			std::cout << *beg++ << ' ';
		}
		std::cout << '\n';
	}
	
	int main()
	{
		using namespace std;
	
		vector<int> ivec{ 3, 6, 9, 12, 15, 18 };
	
		auto riter_beg = ivec.rbegin();		// 18's position -> reverse_iterator
		auto riter_end = ivec.rend();		// 3's position	 -> reverse_iterator
	
		display_range(riter_beg, riter_end);
		// output -> 18 15 12 9 6 3
	
		display_range(riter_end.base(), riter_beg.base());
		// output -> 3 6 9 12 15 18
	
		if (riter_end.base() == ivec.begin())
		{
			std::cout << "riter_end.base() == ivec.begin() -> true\n";
		}
		if (riter_beg.base() == ivec.end())
		{
			std::cout << "riter_beg.base() == ivec.end() ->  true\n";
		}
	
		// output ->
		//	riter_end.base() == ivec.begin() -> true
		//	riter_beg.base() == ivec.end() ->  true
	}
*/

/*
	#include <vector>
	#include <algorithm>
	
	int main()
	{
		using namespace std;
	
		vector<int> ivec{ 1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4 };
		int val = 2;
	
		if (auto riter = std::find(ivec.rbegin(), ivec.rend(), val); riter != ivec.rend())
		{
			ivec.erase(riter);	// syntax error
			// erase function wants std::iterator as an argument.
	
			ivec.erase(riter.base());
			// output -> 1 2 3 4 1 2 3 4 1 2 3 4 1 2 4
			// we want to delete 2 in the last but 3 deleted
	
			ivec.erase(prev(riter.base()));
			// output -> 1 2 3 4 1 2 3 4 1 2 3 4 1 3 4
		}
		else {
			cout << "could not found.\n";
		}
	
		for (auto elem : ivec)
			std::cout << elem << ' ';
	}
*/

/*
	// std::count() algorithm

	#include <list>
	#include <string>
	#include <algorithm>
	
	// Mental Model for count algorithm
	template <typename InIter, typename T>
	int Count(InIter beg, InIter end, const T& val)
	{
		int cnt{};
	
		while (beg != end) {
			if (*beg == val)
				++cnt;
			++beg;
		}
		return cnt;
	}
	
	int main()
	{
		using namespace std;
		list<string> slist{ "hello", "robot", "yes", "no", "hello", "robot", "yes", "yes", "no", "robot" };
	
		string str{ "robot" };
	
		std::cout << count(slist.begin(), slist.end(), str);	// output -> 3
	}
*/

/*
	#include <string>
	#include <algorithm>
	
	int main()
	{
		std::string line{ "hello we are live from istanbul" };
		char c = 'a';
	
		std::cout << std::count(line.begin(), line.end(), c);
		// output -> 2
	}
*/

/*
	// std::count_if() algorithm
	// std::find_if() algorithm
	// std::copy_if() algorithm

	// unary predicate -> function that have 1 parameter and return type is bool
	template <typename InIter, typename UnPred>
	int Count_if(InIter beg, InIter end, UnPred f)
	{
		int cnt{};
	
		while (beg != end) {
			if (f(*beg)) {
				++cnt;
			}
			++beg;
		}
		return cnt;
	}
	
	template <typename InIter, typename UnPred>
	InIter Find_if(InIter beg, InIter end, UnPred f)
	{
		while (beg != end) {
			if (f(*beg)) {
				return beg;
			}
			++beg;
		}
		return end;
	}
	
	template <typename InIter, typename OutIter, typename UnPred>
	OutIter Copy_if(InIter beg, InIter end, OutIter destbeg, UnPred f)
	{
		while (beg != end)
		{
			if (f(*beg)) {
				*destbeg++ = *beg;
			}
			beg++;
		}
		return destbeg;
	}
*/

/*
	#include <vector>
	#include <algorithm>
	
	int is_even(int x)
	{
		return x % 2 == 0;
	}
	
	class DivPred {
	public:
		DivPred(int val) : mval{ val }{}
		bool operator()(int x)const
		{
			return x % mval == 0;
		}
	private:
		int mval;
	};
	
	int main()
	{
		using namespace std;
	
		vector<int> ivec{ 1,2,3,4,5,6,7,8,9,1,2,3,4,5,6,7,8,9,1,2,3,4,5,6,7,8,9 };
	
		std::cout << "even count = " << count_if(ivec.begin(), ivec.end(), is_even) << '\n';
		// output -> even count = 12
		// we send a function pointer(&is_even) as UnPred argument.
	
	
		int x = 7;
	
		std::cout << "divisible for 7 count = " <<
			count_if(ivec.begin(), ivec.end(), DivPred{ x }) << '\n';
		// output -> divisible for 7 count = 3
	
		// DivPred{7} temp objects operator()() function will return
		// when an item in vector is divisible for int that DivPred initialized with.
		// which is 7 in this example.
		// DivPred is a functor class.
	}
*/

/*
	#include <vector>
	#include <algorithm>
	#include <string>
	
	class LenPred {
	public:
		LenPred(std::size_t len) : mlen{ len } {}
		bool operator()(const std::string& str)const
		{
			return str.length() == mlen;
		}
	private:
		std::size_t mlen;
	};
	
	int main()
	{
		using namespace std;
	
		vector<string> svec{ "a", "aa", "aaa", "b", "bb", "bbb", "bbbb", "c", "cc", "ccc", "ccc", "d","dd","ddd","dddd","ddddd"};
	
		size_t len = 2;
	
		std::cout << "count of string objects have length 2 = " <<
			count_if(svec.begin(), svec.end(), LenPred{len} ) << '\n';
		// output -> count of string objects have length 2 = 4
	
	
		for (size_t i{ 1 }; i < 6; ++i)
		{
			cout << "count of " << i << " length strings = " <<
				count_if(svec.begin(), svec.end(), LenPred{ i }) << '\n';
		}
		// output ->
		//	count of 1 length strings = 4
		//	count of 2 length strings = 4
		//	count of 3 length strings = 5
		//	count of 4 length strings = 2
		//	count of 5 length strings = 1
	}
*/

/*
	// using lambda expression in count_if() algorithm
	
	#include <vector>
	#include <algorithm>
	#include <string>
	
	int main()
	{
		using namespace std;
	
		vector<string> svec{ "a", "aa", "aaa", "b", "bb", "bbb", "bbbb", "c", "cc", "ccc", "ccc", "d","dd","ddd","dddd","ddddd" };
	
		for (size_t i{ 1 }; i < 6; ++i)
		{
			cout << "count of " << i << " length strings = " <<
				count_if(svec.begin(), svec.end(),
					[i](const string& s) {return s.length() == i; }) << '\n';
		}
		// output ->
		//	count of 1 length strings = 4
		//	count of 2 length strings = 4
		//	count of 3 length strings = 5
		//	count of 4 length strings = 2
		//	count of 5 length strings = 1
	}
	
	// when we use lambda expression, compiler is writing a class
	// that classes name is closure class and the temp object
	// that will compiler create to use in expression called is closure object.
	// we don't need to wrote a Functor class when we use lambda expression.
	
	// [] -> lambda introducer
	// [expr] -> expr is capture clause
	// [](int x) ->	function call operator [operator(int x)()]
	// [](int x) {return x * 5;} -> PR Value expression
	// [](int x) { return x *5; }(10); -> 50
	
	class ztr_yuq {	// compiler generated class
	public:
		auto operator()(int x)const		// return type will be calculated with type deduction
		{
			return x * 5;
		}
	};
*/

/*
	#include <vector>
	#include <string>
	#include <algorithm>
	
	int main()
	{
		using namespace std;
	
		vector<string> svec{ "hello", "bella", "relocation", "mars", "area", "lemonade", "bell" };
	
		string key{ "la" };		// change here !!
	
		if (auto iter = find_if(svec.begin(), svec.end(),
			[key](const string& str) { return str.find(key) != string::npos;}); iter != svec.end()) {
			std::cout << "has been found = " << *iter << '\n';
		}
		else {
			std::cout << "couldn't found\n";
		}
	
		// key will be the compiler generated classes data member.
		// that is why we can use that key string in function body.
	}
*/

/*
	// std::transform algorithm
	#include <algorithm>
	#include <vector>
	#include <string>
	
	// Implementation of Transform algorithm
	template <typename InIter, typename OutIter, typename Ufunc>
	OutIter Transform(InIter beg, InIter end, OutIter destbeg, Ufunc f)
	{
		while (beg != end) {
			*destbeg++ = f(*beg++);
		}
		return destbeg;
	}
	
	int main()
	{
		using namespace std;
	
		vector<string> svec{ "yes", "no", "stop", "go", "mars", "earth", "side", "fight", "far", "bar" };
	
		for (auto elem : svec)
			std::cout << elem << '\n';
	
		// We need to create a vector and that vector needs to hold strings lengths.
	
		vector<size_t> lenvec;
	
		transform(svec.begin(), svec.end(), back_inserter(lenvec), [](const string& s) {return s.length(); });
	
		for (auto elem : lenvec)
			std::cout << elem << ' ';
	
		// output ->
		//	yes
		//	no
		//	stop
		//	go
		//	mars
		//	earth
		//	side
		//	fight
		//	far
		//	bar
		//	3 2 4 2 4 5 4 5 3 3
	}
*/

/*
	#include <algorithm>
	#include <vector>
	#include <string>
	
	std::string Reverse(std::string s)
	{
		std::reverse(s.begin(), s.end());
		return s;
	}
	
	int main()
	{
		using namespace std;
	
		vector<string> svec{ "yes", "no", "stop", "go", "mars", "earth", "side" };
	
		for (auto elem : svec)
			std::cout << elem << ' ';
		// output -> yes no stop go mars earth side
		std::cout << '\n';
	
		transform(svec.begin(), svec.end(), svec.begin(), Reverse);
	
		for (auto elem : svec)
			std::cout << elem << ' ';
		// output -> sey on pots og sram htrae edis
	}
*/

/*
	#include <algorithm>
	#include <vector>
	#include <list>
	
	template <typename InIter_1, typename InIter_2, typename OutIter, typename BiFunc>
	OutIter Transform(InIter_1 beg_1, InIter_1 end, InIter_2 beg_2, OutIter destbeg, BiFunc f)
	{
		while (beg_1 != end) {
			*destbeg++ = f(*beg_1++, *beg_2++);
		}
		return destbeg;
	}
	
	int sum_square(int a, int b)
	{
		return a * a + b * b;
	}
	
	int main()
	{
		using namespace std;
	
		int a[] = { 1, 3, 5, 7, 12, 67, 50, 20, 13 };
		vector<int> ivec{ 11, 23, 41, 76, 12, 34, 76, 6, 2 };
	
		list<int> mylist;
	
		// transform(begin(a), end(a), ivec.begin(), back_inserter(mylist), sum_square);
	
		transform(begin(a), end(a), ivec.begin(),
			back_inserter(mylist), [](int a, int b) { return a * a + b * b; });
	
		for (auto elem : mylist)
			std::cout << elem << ' ';
		// output -> 122 538 1706 5825 288 5645 8276 436 173
	}
*/

/*
	// std::for_each algorithm	-> returns callable

	#include <algorithm>
	#include <vector>
	#include <string>
	
	template <typename Iter, typename Ufunc>
	Ufunc For_each(Iter beg, Iter end, Ufunc f)
	{
		while (beg != end) {
			f(*beg++);
		}
		return f;
	}
	
	void increment(int& x)
	{
		++x;
	}
	
	class Functor {
	public:
		Functor(char c) : m_c{c} {}
	
		void operator()(std::string& s)
		{
			if (s[0] == m_c)
				s[0] = std::toupper(s[0]);
		}
	private:
		char m_c;
	};
	
	class Functor_2 {
	public:
		Functor_2(char c) : m_c{ c } {}
		void operator()(std::string& s)
		{
			if (s[0] == m_c) {
				s[0] = std::toupper(s[0]);
				++m_cnt;
			}
		}
		int get_count()const
		{
			return m_cnt;
		}
	private:
		char m_c;
		int m_cnt{};
	};
	
	int main()
	{
		using namespace std;
	
		int a[] = { 1, 4, 5, 25, 7, 9, 3, 12, 92 };
		for_each(begin(a), end(a), increment);
	
		for (auto elem : a)
			std::cout << elem << ' ';
		// output -> 2 5 6 26 8 10 4 13 93
	
		vector<string> svec{ "yes", "no", "sell", "buy", "ying", "rap", "rock", "easy", "hard", "yang" };
		for_each(svec.begin(), svec.end(), Functor('y'));
	
		for (auto elem : svec)
			std::cout << elem << ' ';
		// output -> Yes no sell buy Ying rap rock easy hard Yang
	
		vector<string> svec_2{ "yes", "no", "sell", "buy", "ying", "rap", "rock", "easy", "hard", "yang" };
		auto f = for_each(svec_2.begin(), svec_2.end(), Functor_2('y'));
	
		std::cout << f.get_count() << " elements has been changed.\n";
		// output -> 3 elements has been changed.
	}
*/

/*
	// all_of, any_of, none_of algorithms
	// all of them returns bool
	
	#include <vector>
	#include <algorithm>
	
	int main()
	{
		using namespace std;
	
		vector<int> ivec{ 2, 4, 6, 5, 87, 12, 34, 534, 21 };
		vector<int> ivec_2{ 2, 4, 6, 12, 88, 12, 34, 534, 24 };
	
		cout << boolalpha;
	
		cout << any_of(ivec.begin(), ivec.end(), [](int x) { return x % 2 != 0; }) << '\n';
		// output -> true
		cout << any_of(ivec_2.begin(), ivec_2.end(), [](int x) { return x % 2 != 0; }) << '\n';
		// output -> false
	
		cout << all_of(ivec.begin(), ivec.end(), [](int x) { return x % 2 == 0; }) << '\n';
		// output -> false
		cout << all_of(ivec_2.begin(), ivec_2.end(), [](int x) { return x % 2 == 0; }) << '\n';
		// output -> true
	
		cout << none_of(ivec.begin(), ivec.end(), [](int x) { return x % 2 != 0; }) << '\n';
		// output -> false
		cout << none_of(ivec_2.begin(), ivec_2.end(), [](int x) { return x % 2 != 0; }) << '\n';
		// output -> true
	}
*/

/*
	//	std::max_element algorithm -> returns an iterator

	#include <algorithm>
	#include <vector>
	#include <string>
	
	int main()
	{
		using namespace std;
	
		vector<string> svec{ "hello", "is", "this", "sparta", "or", "i", "am", "in", "wrong", "place"};
	
		auto iter = max_element(svec.begin(), svec.end());
	
		cout << "max = " << *iter << " , max idx = " << distance(svec.begin(), iter) << '\n';
		// output -> max = wrong , max idx = 8 (lexicographical compare)

		cout << "size = " << iter->size() << '\n';
		// output -> size = 5	[wrong]
		
		// iter->size() [string length] can be used in functions 
	}
*/

/*
	#include <algorithm>
	#include <vector>
	#include <string>
	#include <utility>
	
	int main()
	{
		using namespace std;
	
		vector<string> svec{ "hello", "is", "this", "sparta", "or", "i", "am", "in", "wrong", "place" };
	
		// return type of minmax_element -> pair<vector<string>::iterator, vector<string>::iterator>;
		auto ip = minmax_element(svec.begin(), svec.end());
	
		cout << "min = " << *ip.first << ", max = " << *ip.second << '\n';
		// output -> min = am, max = wrong
	
	
		// SPLITTING ELEMENTS OF PAIR IN OLD C++
		//	auto iter_min = ip.first;
		//	auto iter_max = ip.second;
	
		// structured binding
		auto [iter_min, iter_max] = minmax_element(svec.begin(), svec.end());
	
		cout << "min idx = " << distance(svec.begin(), iter_min) << ' ' << *iter_min << '\n';
		cout << "max idx = " << distance(svec.begin(), iter_max) << ' ' << *iter_max << '\n';
		// output ->
		//	min idx = 6 am
		//	max idx = 8 wrong
	}
*/

/*
	------------------------------------------------
	| standart function objects(standart functors) |
	------------------------------------------------
*/

/*
	template <typename RanIt, typename Bipred>
	void Sort(RanIt beg, RanIt end, Bipred pred)
	{
		// if we send a std::less callable (pred)
		// it will use lesser comparison
	
		// if we send std::greater callable (pred)
		// it will use greater comparison
	}
	
	template <typename Iter,  typename Bipred>
	void foo(Iter beg, Iter end, Bipred f)
	{
		while (beg != end) {
			f(*beg, *(beg + 1))
		}
		// if we send a callable to f argument we can use
		// that callable to make comparison between elements in the range.
	}
	
	template <typename T>
	struct Less {
		bool operator()(const T& t1, const T& t2) const
		{
			return t1 < t2;
		}
	};
	
	int main()
	{
		int x = 20, y = 45;
	
		std::cout << std::boolalpha;
		std::cout << (x < y) << '\n';			// output -> true
	
		std::cout << Less<int>()(x, y) << '\n';	// output -> true	[temp object]
	
		Less<int> myless;
		std::cout << myless(x, y) << '\n';		// output -> true
	}
*/

/*
	template <typename T>
	struct Less {
		bool operator()(const T& t1, const T& t2) const
		{
			return t1 < t2;
		}
	};
	
	template <typename T>
	struct Greater {
		bool operator()(const T& t1, const T& t2) const
		{
			return t1 > t2;
		}
	};
	
	template <typename T>
	struct Plus {
		T operator()(const T& t1, const T& t2) const
		{
			return t1 + t2;
		}
	};
	
	template <typename T>
	struct Multiplies {
		T operator()(const T& t1, const T& t2) const
		{
			return t1 * t2;
		}
	};
	
	// Every operator( <, >, +, * ) can be created as a functor class like that!.
*/

/*
	#include <functional>
	#include <vector>
	#include <string>
	#include <algorithm>
	
	int main()
	{
		using namespace std;
	
		cout << less<int>()(5, 10) << '\n';				// output -> 1
		cout << greater<int>()(5, 10) << '\n';			// output -> 0
		cout << greater_equal<int>()(5, 10) << '\n';	// output -> 0
		cout << plus<int>()(5, 10) << '\n';				// output -> 15
		cout << multiplies<int>()(5, 10) << '\n';		// output -> 50
	
		vector<string> svec{ "yes", "no", "zero", "infinity", "war", "peace", "karamazov", "brothers" };
	
		sort(svec.begin(), svec.end());
		sort(svec.begin(), svec.end(), less<string>{});
		// These 2 lines purposes are same.
		// if we did not use a functor as an argument
		// algorithm will act like using less standart functor.
	
		for (auto elem : svec)
			cout << elem << ' ';
		// output -> brothers infinity karamazov no peace war yes zero
		std::cout << '\n';
	
		sort(svec.begin(), svec.end(), greater<string>{});
	
		for (auto elem : svec)
			cout << elem << ' ';
		// output -> zero yes war peace no karamazov infinity brothers
	}
*/

/*
	#include <functional>
	#include <vector>
	#include <algorithm>
	
	bool myless(int a, int b)
	{
		return std::abs(a) < std::abs(b);
	}
	
	struct MylessAbs {
		bool operator()(int a, int b) const
		{
			return std::abs(a) < std::abs(b);
		}
	};
	
	int main()
	{
		using namespace std;
	
		vector<int> ivec{ 12, 5, 84, 293, 1092, 283, 63, 28, 34, 772, 881, 94, 532 };
	
		auto iter = max_element(ivec.begin(), ivec.end());
		cout << "max = " << *iter << ", index = " << distance(ivec.begin(), iter) << '\n';
		// output -> max = 1092, index = 4
	
	
		ivec = { 12, -1435, -84, 293, 1092, -283, 63, 28, -34, 772, 881, 94, 532, -1254 };
	
		iter = max_element(ivec.begin(), ivec.end(), myless);
		// used myless global function as a callable
		cout << "max = " << *iter << ", index = " << distance(ivec.begin(), iter) << '\n';
		// output -> max = -1435, index = 1
	
		sort(ivec.begin(), ivec.end(), greater{});
		for (auto elem : ivec)
			cout << elem << ' ';
		// output -> 1092 881 772 532 293 94 63 28 12 -34 -84 -283 -1254 -1435
		std::cout << '\n';
	
		// ---------------------------------------------------------- //
	
		// USING FUNCTION AS A CALLABLE
		sort(ivec.begin(), ivec.end(), myless);
		for (auto elem : ivec)
			cout << elem << ' ';
		// output -> 12 28 -34 63 -84 94 -283 293 532 772 881 1092 -1254 -1435
		std::cout << '\n';
	
		// USING FUNCTOR CLASS AS A CALLABLE
		sort(ivec.begin(), ivec.end(), MylessAbs{});
		for (auto elem : ivec)
			cout << elem << ' ';
		// output -> 12 28 -34 63 -84 94 -283 293 532 772 881 1092 -1254 -1435
		std::cout << '\n';
	
		// USING LAMBDA EXPRESSION AS A CALLABLE
		sort(ivec.begin(), ivec.end(), [](int a, int b) {
			return std::abs(a) < std::abs(b);
			});
		for (auto elem : ivec)
			cout << elem << ' ';
		// output -> 12 28 -34 63 -84 94 -283 293 532 772 881 1092 -1254 -1435
		std::cout << '\n';
	}
*/

/*
	#include <vector>
	#include <functional>
	#include <algorithm>
	#include <list>
	
	int main()
	{
		using namespace std;
	
		vector<int> ivec{ 2, 4, 5, 6, 7, -9, -10, 7, 1, 90 };
	
		transform(ivec.begin(), ivec.end(), ivec.begin(), negate<int>{});
	
		// transform(ivec.begin(), ivec.end(), ivec.begin(), negate{});
		// negate used as a transparent function object
	
		for (auto elem : ivec)
			cout << elem << ' ';
		// output -> -2 -4 -5 -6 -7 9 10 -7 -1 -90
		cout << '\n';
	
		vector<int> x{ 2, 4, 5, 6, 7, -9, -10, 7, 1, 90 };
		vector<int> y{ 1, 2, 7, 16, 17, 19, 110, 97, 21, 590 };
		list<int> mylist;
	
		transform(x.begin(), x.end(), y.begin(), back_inserter(mylist), plus{});
		// using standart function object
	
		// transform(x.begin(), x.end(), y.begin(), back_inserter(mylist), [](int a, int b) {
		// 	return a + b; });
		// using lambda expression
	
		for (auto elem : mylist)
			cout << elem << ' ';
		// output -> 3 6 12 22 24 10 100 104 22 680
		cout << '\n';
	
		mylist.clear();
	
		transform(x.begin(), x.end(), y.begin(), back_inserter(mylist), multiplies{});
	
	
		for (auto elem : mylist)
			cout << elem << ' ';
		// output -> 2 8 35 96 119 -171 -1100 679 21 53100
		cout << '\n';
	}
*/

/*
	#include <vector>
	#include <algorithm>
	#include <functional>
	
	int main()
	{
		using namespace std;
	
		vector<int> ivec{ 43, 3, -5, 78, 23, -44, -12, 90, 21 };
	
		sort(ivec.begin(), ivec.end(), greater{});
		// using functional object
		sort(ivec.rbegin(), ivec.rend());
		// using rbegin and rend
	}
*/

/*
	// std::replace, std::replace_if algorithm

	#include <vector>
	#include <algorithm>
	#include <functional>
	#include <string>
	
	int main()
	{
		using namespace std;
	
		vector<int> ivec{ 3,3,1,2,4,1,0,2,3,2,4,3,1,2,0,5,4,3,2,1,3,4,5,2,1,2,3,4,5,1 };
		// replace 3's to 7
		replace(ivec.begin(), ivec.end(), 3, 7);
	
		for (int elem : ivec)
			std::cout << elem;
		// output -> 771241027247120547217452127451
		std::cout << '\n';
	
		// replace even to 0
		replace_if(ivec.begin(), ivec.end(), [](int a) {
			return a % 2 == 0; }, 0);
	
		for (int elem : ivec)
			std::cout << elem;
		// output -> 771001007007100507017050107051
		std::cout << '\n';
	
		vector<string> svec{ "hey", "yes", "no", "faul", "red", "silver", "blue", "karus","human" };
	
		replace_if(svec.begin(), svec.end(), [](const string& s) {return s.length() == 3; }, "***");
	
		for (auto elem : svec)
			std::cout << elem << ' ';
		// output -> *** *** no faul *** silver blue karus human
		std::cout << '\n';
	}
*/

/*
	// reverse_copy, remove_copy, remove_copy_if algorithms
	
	#include <vector>
	#include <algorithm>
	#include <string>
	#include <list>
	
	int main()
	{
		using namespace std;
	
		vector<string> svec{ "hey", "yes", "no", "faul", "red", "silver", "blue", "karus","human" };
		reverse(svec.begin(), svec.end());
	
		for (auto elem : svec)
			std::cout << elem << ' ';
		// output -> human karus blue silver red faul no yes hey
		std::cout << '\n';
	
	
		svec = { "hey", "yes", "no", "faul", "red", "silver", "blue", "karus","human" };
		list<string> slist;
		reverse_copy(svec.begin(), svec.end(), back_inserter(slist));
	
		for (auto elem : slist)
			std::cout << elem << ' ';
		// output -> human karus blue silver red faul no yes hey
		std::cout << '\n';
	
	
		vector<int> ivec{ 1,2,3,4,5,6,7,8,9,1,2,3,4,5,6,7,8,9 };
		vector<int> dest;
		remove_copy(ivec.begin(), ivec.end(), back_inserter(dest), 3);
	
		for (auto elem : dest)
			std::cout << elem << ' ';
		// output -> 1 2 4 5 6 7 8 9 1 2 4 5 6 7 8 9
		std::cout << '\n';
	
	
		svec = { "hey", "yes", "no", "faul", "red", "silver", "blue", "karus","human" };
		vector<string> sdest;
		remove_copy_if(svec.begin(), svec.end(), back_inserter(sdest), [](const string& s)
			{return s.find('a') != string::npos; });
		// C++23 -> contains
		// remove_copy_if(svec.begin(), svec.end(), back_inserter(sdest), [](const string& s) {return s.contains('a'); });
	
		for (auto elem : sdest)
			std::cout << elem << ' ';
		// output -> hey yes no red silver blue
		std::cout << '\n';
	}
*/

/*
	--------------
	| Containers | 
	--------------
*/

/*
	In sequence containers we can add an element in which index we want.
	But in assosiative containers we can not add an element in the random index.

	STL containers have some common functions.
	empty()		-> returns bool
	clear()		-> deletes elements in container
	size()		-> returns count of elements in the container

	Sequance containers
	front()		-> returns first element
	back()		-> returns last element
	resize()	-> change the size of the container
*/

/*
	#include <vector>
	#include <list>
	#include <map>
	#include <forward_list>
	#include <set>
	
	int main()
	{
		using namespace std;
	
		vector<int>::size_type x{};
		list<int>::size_type y{};
		map<int,int>::size_type z{};
		set<int>::size_type k{};
		forward_list<int>::size_type k{};
	
		vector<int>::value_type p{};		// int
		list<double>::value_type r{};		// double
		map<int,double>::value_type r{};	// pair<const int, double>
	
		vector<int>::pointer a{};			// int*
		vector<int>::reference b{};			// int&
	
		// containers have some common nested types. 
		// size_type, value_type, pointer, reference...
	}
*/

/*
	#include <vector>
	
	template <typename InIter>
	void func(InIter beg, InIter end)
	{
		typename InIter::value_type x{};
		// What if we send a C style array in this function?
		// Will be a syntax error now.
		// Because C style array does not have a value_type nested type.
	
		std::cout << typeid(x).name() << '\n';
	}
	
	template <typename InIter>
	void func_2(InIter beg, InIter end)
	{
		typename std::iterator_traits<InIter>::value_type x{};
		std::cout << typeid(x).name() << '\n';
	}
	
	// How does iterator_traits work ?
	template <typename Iter>
	struct IteratorTraits {
		using value_type = typename Iter::value_type;
		using pointer = typename Iter::pointer;
		using reference = typename Iter::reference;
	};
	
	// partial specialization
	template <typename T>
	struct IteratorTraits<T*> {
		using value_type = T;
		using pointer = T*;
	};
	// C array will choose partial specialization.
	// Array will decay to pointer and when int* comes 
	// value_type is going to be int.
	
	
	int main()
	{
		using namespace std;
	
		vector<int> ivec(100);
		int a[5] = { 1,2,3,4,5 };
	
		func(ivec.begin(), ivec.end());		// output -> int
		func(begin(a), end(a));						// syntax error
		func(a, a + 5);										// syntax error
	
		func_2(ivec.begin(), ivec.end());	// output -> int
		func_2(begin(a), end(a));					// output -> int
		func_2(a, a + 5);									// output -> int
	}
*/

/*
	-> In vector we can reach whatever index in constant time 
		using pointer arithmetics.
	-> To add an element in back will be amortized constant time
	// if no reallocation need -> constant time -> O(1)
*/

/*
	#include <vector>
	
	template <typename T, typename A = std::allocator<T>>
	class Vector {
	
	};
	
	int main()
	{
		using namespace std;
		vector<int, allocator<int>> a;
		vector<int> b;
		// These 2 lines are same default argument allocator -> std::allocator<T>
	
		vector<int> x{};	// default initializer will be called.
		vector<int> y;		// default initializer will be called.
	
		cout << "x.size() = " << x.size() << '\n';		// output -> 0
		cout << "x.empty() = " << x.empty() << '\n';	// output -> 1(bool)
	}
*/

/*
	// information about boolalpha 

	int main()
	{
		using namespace std;
	
		cout << (10 > 5) << '\n';	// output -> 1
	
		cout.setf(ios::boolalpha);	// set format function [setf()]
		// changed the format state of the cout class object
		cout << (10 > 5) << '\n';	// output -> true
	
		cout.unsetf(ios::boolalpha);
		cout << (10 > 5) << '\n';	// output -> 1
	
		// ostream manipulator
	
		cout << boolalpha;
		boolalpha(cout);	// global function
		ios::boolalpha;		// constexpr static data member
	}
*/

/*
	#include <vector>
	
	int main()
	{
		// insert functions in vector, increasing size of the container.
		using namespace std;
	
		vector<int> ivec;
	
		ivec.push_back(10);
		ivec.emplace_back(10);
		ivec.insert(ivec.begin(), 5);
	
		// remove functions in vector, decreasing size of the container
	
		ivec.pop_back();
		ivec.erase();
	}
*/

/*
	1. objects copy ctor will be called for insertion.
	2. objects move ctor will be called for insertion.
	3. using perfect forwarding mechanism, 
*/

/*
	#include <vector>
	
	class Myclass {
	public:
		Myclass() = default;
	
		Myclass(int, int, int)
		{
			std::cout << "Myclass(int, int, int)\n";
		}
	
		Myclass(const Myclass&)
		{
			std::cout << "Myclass copy ctor\n";
		}
	
		Myclass(Myclass&&)
		{
			std::cout << "Myclass move ctor\n";
		}
	};
	
	int main()
	{
		using namespace std;
		vector<Myclass> vec;
		vec.reserve(100);
	
		Myclass m;
		vec.push_back(m);								// output -> Myclass copy ctor
		vec.push_back(Myclass{});				// output -> Myclass move ctor
		vec.push_back(std::move(m));		// output -> Myclass move ctor
	
		vec.emplace_back();
		// we will send arguments for constructing Myclass object
		// not Myclass object itself!!
		// emplace functions using perfect forwarding mechanism.
	
		vec.emplace_back(1, 2, 3);		// output -> Myclass(int, int, int)
	}
*/

/*
	// mental model for insert functions of vector
	template <typename T>
	class Vector {
	public:
		void push_back(const T&);
		void push_back(T&&);				// r value reference parameter
	
		template <typename ...Args>
		void emplace_back(Args&& ...args)	// universal reference parameter
		{
			new(address) T(std::forward<Args>(args)...);
			// address -> it is the address that the object will be constructed.
		}
	};
*/

/*
	----------------------------------------
	| member functions of vector container |
	----------------------------------------
*/

/*
	#include <vector>
	#include <string>
	
	int main()
	{
		using namespace std;
	
		vector<int> vec;
	
		auto iter_1 = vec.begin();		// -> iterator
		auto iter_2 = vec.cbegin();		// -> const iterator
		auto iter_3 = vec.rbegin();		// -> reverse iterator
		auto iter_4 = vec.crbegin();	// -> const reverse iterator
	
		auto iter_5 = crbegin(vec);		// global functions
		// generally will be used for C-style arrays
	
		int a[]{ 3,5,6,7,8 };
		crbegin(a);
	
	
		// all containers have default ctor. (list, vector, set)
	
		vector<int> v1;		// default ctor will be called.
		vector<int> v2{};	// default ctor will be called.
		vector<int> v3();	// most vexing parse (function decleration)
	
		vector<string> svec{"hello", "i", "am", "robot"};
	
		auto myvec = svec;
		auto myvec_2 = { svec };
		// vector classes copy ctor will be called.
	
		std::cout << "svec.capacity() = " << svec.capacity() << '\n';
		// output -> svec.capacity() = 4
	
		auto myvec_3 = std::move(svec);
		// vector classes move ctor will be called.
		// svec will become moved from state. Acts like default initialized.
	
		cout << "svec.size() = " << svec.size() << '\n';
		// output -> svec.size() = 0
		std::cout << "svec.capacity() = " << svec.capacity() << '\n';
		// output -> svec.capacity() = 0
	}
*/

/*
	#include <vector>
	
	class A {
	public:
		A(int);
	};
	
	int main()
	{
		using namespace std;
	
		vector<string> svec(100);	// fill constructor
		// Default ctor will be called for string objects
		// There are 100 items in vector.
	
		vector<A> avec(100);	// syntax error
		// error C2512: 'A::A': no appropriate default constructor available
		// value_type(string, A, ...) needs to be default constructable for using
		// vectors size_t parameter ctor.
	
		vector<string> svec_2(10, "hello");
		cout << "svec_2.size() = " << svec_2.size() << '\n';
		// output -> svec_2.size() = 10
	
		vector<int> x(19);		// fill ctor
		cout << "x.size() = " << x.size() << '\n';	// output -> x.size() = 19
	
		vector<int> y{ 19 };	// initializer list param ctor
		cout << "y.size() = " << y.size() << '\n';	// output -> y.size() = 1
	
		vector<int> z(10, 5);	// fill ctor
		for (auto elem : z)
			cout << elem;
		// output -> 5555555555
	
		vector<int> k{ 10, 5 };
		cout << "k.size() = " << k.size() << '\n';	// output -> k.size() = 2
	
		vector l{ 1,4,5,7,8 };	// CTAD(Class Template Argument Deduction)
		cout << typeid(l).name() << '\n';
		// output -> class std::vector<int,class std::allocator<int>>
	}
*/

/*
	#include <vector>
	#include <list>
	
	int main()
	{
		using namespace std;
		list<int> mylist{ 1,5,4,32,2,6,54 };
	
		vector<int> ivec{ mylist };	// syntax error
		// assigning different containers to each other.
	
		// range parameter ctor will solve this issue.
		vector<int> ivec_2{ mylist.begin(), mylist.end() };		// legal
		vector<double> dvec{ mylist.begin(), mylist.end() };	// legal
	
		list<const char*> cslist{ "hello", "world" };
		vector<string> svec{ cslist.begin(),cslist.end() };		// legal
	
		int a[]{ 2,5,6,7,2,3,4 };
	
		vector<int> ivec_3{ a, a + sizeof(a) / sizeof(*a) };
		vector<int> ivec_3{ begin(a), end(a)};
		// These 2 lines are same.
	}
*/

/*
	Vector Container constructors
	------------------------------
	copy ctor
	move ctor
	default ctor
	(size_t)				-> fill ctor
	(size_t, T)				-> fill ctor
	({initializer_list})	-> initializer list ctor
	(iter_beg, iter_end)	-> range ctor
*/

/*
	#include <vector>
	
	int main()
	{
		using namespace std;
		vector<int> ivec;
	
		cout << size(ivec) << '\n';		// output -> 0
		cout << empty(ivec) << '\n';	// output -> 1
		// global size() and empty() function templates
	}
*/

/*
	#include <vector>
	
	int main()
	{
		using namespace std;
		vector<int> ivec(10);
	
		auto data_ptr = data(ivec);
		// global data() function template
	
		auto data_ptr_2 = ivec.data();
		cout << &ivec[0] << " ivec's address\n";
		cout << data_ptr_2 << " data address\n";
		// output ->
		//	01187AA0 ivec's address
		//	01187AA0 data address
	}
*/

/*
	#include <vector>
	
	int main()
	{
		using namespace std;
	
		vector<int> ivec(20);
	
		auto cap = ivec.capacity();
		int count{};
	
		while (ivec.size() < 2'000) {
			ivec.push_back(1);
	
			if (ivec.capacity() != cap) // after reallocation occurs
			{
				cout << ++count << " size = " << ivec.size();
				cout << " new cap = " << ivec.capacity() << '\n';
	
				cap = ivec.capacity();
			}
		}
	
		// output ->
		//	1  size = 21   new cap = 30
		//	2  size = 31   new cap = 45
		//	3  size = 46   new cap = 67
		//	4  size = 68   new cap = 100
		//	5  size = 101  new cap = 150
		//	6  size = 151  new cap = 225
		//	7  size = 226  new cap = 337
		//	8  size = 338  new cap = 505
		//	9  size = 506  new cap = 757
		//	10 size = 758  new cap = 1135
		//	11 size = 1136 new cap = 1702
		//	12 size = 1703 new cap = 2553
	}
*/

/*
	#include <vector>
	
	int main()
	{
		using namespace std;
	
		vector<int> ivec(20);
	
		auto cap = ivec.capacity();
		int count{};
	
		ivec.reserve(1200);	// using reserve() function
	
		while (ivec.size() < 2'000) {
			ivec.push_back(1);
	
			if (ivec.capacity() != cap)
			{
				cout << ++count << " size = " << ivec.size();
				cout << " new cap = " << ivec.capacity() << '\n';
	
				cap = ivec.capacity();
			}
		}
	
		// output ->
		//	1 size = 21 new cap = 1200
		//	2 size = 1201 new cap = 1800
		//	3 size = 1801 new cap = 2700
	}
*/

/*
	// swap trick before shrink_to_fit() function.

	#include <vector>

	int main()
	{
		using namespace std;
	
		vector<int> x(1'000'000, 5);
		cout << "size = " << x.size() << " capacity = " << x.capacity() << '\n';
		// output -> size = 1000000 capacity = 1000000
	
		x.resize(10);
		cout << "size = " << x.size() << " capacity = " << x.capacity() << '\n';
		// output -> size = 10 capacity = 1000000
	
		// x.shrink_to_fit();
		// cout << "size = " << x.size() << " capacity = " << x.capacity() << '\n';
		// output -> size = 10 capacity = 10
	
		vector<int>(x).swap(x);
		// temp object have a shrinked capacity and have a size of x.
		// then we swap that temp object with x.
		cout << "size = " << x.size() << " capacity = " << x.capacity() << '\n';
		// output -> size = 10 capacity = 10
	}
*/

/*
	#include <vector>
	#include <string>
	
	int main()
	{
		using namespace std;
	
		vector<int> ivec{ 10,11,12,13,14,15,16,17,18,19,20 };
	
		// iterating through the elements of vector with raw loop
		for (auto iter = ivec.cbegin(); iter != ivec.cend(); ++iter) {
			cout << *iter << '\n';
		}
	
		// These are the scenerios that compiler wrote for range based loops.
		// 1.
		for (auto i : ivec) {}
		for (auto iter = ivec.begin(); iter != ivec.end(); ++iter) {
			auto i = *iter;
		}
	
		// 2.
		for (const auto i : ivec) {}
		for (auto iter = ivec.begin(); iter != ivec.end(); ++iter) {
			const auto i = *iter;
		}
	
		// 3.
		for (const auto& i : ivec) {}
		for (auto iter = ivec.begin(); iter != ivec.end(); ++iter) {
			const auto& i = *iter;
		}
	
		// 4.
		for (auto&& i : ivec) {}
		for (auto iter = ivec.begin(); iter != ivec.end(); ++iter) {
			auto&& i = *iter;
		}
	}
*/

/*
	#include <vector>
	#include <string>
	
	int main()
	{
		using namespace std;
	
		vector<int> ivec{ 10,11,12,13,14,15,16,17,18,19,20 };
		// front() and back() functions are reaching first 
		// and the last elements of the vector
		// with reference semantics.
	
		ivec.front() += 11;
		ivec.back() += 15;
	
		for (auto i : ivec){
			std::cout << i << ' ';
		}
		// output -> 21 11 12 13 14 15 16 17 18 19 35
	
		vector<string> svec;
	
		auto beg = svec.begin();
		auto end = svec.end();
		// no undefined behaviour in those 2 lines.
	
		*beg;
		*end;
		// both are undefined behaviour in those 2 lines.
	
		auto b = (beg == end);
		// no undefined behaviour and result is true;
	
		distance(beg, end);
		// will be 0.
	
		vector<int> x;
		vector<int> y;
	
		copy(ivec.begin(), ivec.end(), back_inserter(y));
		// no undefined behaviour in here.
		// will not get into algorithms while scope while(beg != end){code;}
		// because beg == end is true.
	}
*/

/*
	#include <vector>
	
	int main()
	{
		using namespace std;
	
		vector<int> ivec(10, 5);
		cout << "size = " << ivec.size() << " cap = " << ivec.capacity() << '\n';
		// output -> size = 10 cap = 10
	
		for (auto i : ivec)
			cout << i << ' ';
		cout << '\n';
		// output -> 5 5 5 5 5 5 5 5 5 5
	
		ivec.resize(15);
		cout << "size = " << ivec.size() << " cap = " << ivec.capacity() << '\n';
		// output -> size = 24 cap = 24
		// new elements will be value initialzied
	
		for (auto i : ivec)
			cout << i << ' ';
		cout << '\n';
		// output -> 5 5 5 5 5 5 5 5 5 5 0 0 0 0 0
	
		ivec.resize(20, 3);
		for (auto i : ivec)
			cout << i << ' ';
		cout << '\n';
		// output -> 5 5 5 5 5 5 5 5 5 5 0 0 0 0 0 3 3 3 3 3
	
	
		// deleting elements from container with resize() function.
		ivec.resize(3);
		for (auto i : ivec)
			cout << i << ' ';
		cout << '\n';
		// output -> 5 5 5
	
		// for deleting every element in container we can call resize(0)
		// but it is better using clear() function of the container..
		ivec.resize(0);
		for (auto i : ivec)
			cout << i << ' ';
		cout << '\n';
		// output ->
	}
*/

/*
	#include <vector>
	
	int main()
	{
		using namespace std;
	
		vector<int> ivec;
		ivec.reserve(20);
	
		for (int i = 0; i < 20; ++i) {
			ivec.push_back(i);
		}
	
		for (auto i : ivec) {
			cout << i << ' ';
		}
		// output -> 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19
	}
*/

/*
	#include <vector>
	#include <string>
	
	int main()
	{
		using namespace std;
	
		vector<string> svec{ "hello", "world", "this", "is", "istanbul" };
		vector<string> dest;
	
		for (size_t i{}; i < svec.size(); ++i) {
			dest.push_back(std::move(svec[i]));
		}
	
		cout << "svec.size() = " << svec.size() << '\n';	// output -> svec.size() = 5
		// svec containers size will still be 5.
		// strings inside svec containe will be in moved-from state.
	
		for (const auto& s : svec) {
			cout << s.size() << ' ';
		}
		// output -> 0 0 0 0 0
	
		// push_back() functions return type is void
	}
*/

/*
	#include <vector>
	#include <string>
	
	int main()
	{
		using namespace std;
	
		vector<string> svec{ "hello", "world", "this", "is", "istanbul" };
	
		svec = { "yes", "no", "do", "so" };
		// initializer list assignment
	
		for (auto str : svec) {
			cout << str << ' ';
		}
		// output -> yes no do so
	}
*/

/*
	#include <vector>
	#include <list>
	#include <string>
	
	int main()
	{
		using namespace std;
	
		list<string> slist{ "hello", "world", "this", "is", "istanbul" };
		vector<string> svec;
	
		// svec = slist; // syntax error
	
		svec.assign(slist.begin(), slist.end());
		// range assign function.
	
		for (auto str : svec)
			cout << str << ' ';
		cout << '\n';
		// output -> hello world this is istanbul
	
		svec.assign(5, "comedy");
		for (auto str : svec)
			cout << str << ' ';
		cout << '\n';
		// output -> comedy comedy comedy comedy comedy
	}
*/

/*
	#include <vector>
	
	// insert functions returns the added element(s) location(iterator).
	
	int main()
	{
		using namespace std;
	
		vector<int> ivec{ 10,11,12,13,14,15,16,17,18,19,20 };
	
		// add element to start
		ivec.insert(ivec.begin(), 3);
		for (auto i : ivec)
			cout << i << ' ';
		// output -> 3 10 11 12 13 14 15 16 17 18 19 20
		cout << '\n';
	
	
		// add element to 2nd position idx[1]
		ivec.insert(ivec.begin() + 1, 99);
		// ivec.insert(next(ivec.begin()), 99);
		// Those 2 lines are same
		for (auto i : ivec)
			cout << i << ' ';
		// output -> 3 99 10 11 12 13 14 15 16 17 18 19 20
		cout << '\n';
	
	
		// add element to last item with insert function. 
		// We can also use push_back()
		// Better using push_back() function.
		ivec.insert(ivec.end(), 77);
		for (auto i : ivec)
			cout << i << ' ';
		// output -> 3 99 10 11 12 13 14 15 16 17 18 19 20 77
		cout << '\n';
	}
*/

/*
	#include <vector>
	#include <list>
	
	int main()
	{
		using namespace std;
		vector<int> ivec{ 11,12,13,14,15 };
	
		ivec.insert(ivec.begin(), { 77,78,79,80 });
	
		for (auto i : ivec)
			cout << i << ' ';
		cout << '\n';
		// output -> 77 78 79 80 11 12 13 14 15
	
		ivec.insert(ivec.begin(),3,55);
		for (auto i : ivec)
			cout << i << ' ';
		cout << '\n';
		// output -> 55 55 55 77 78 79 80 11 12 13 14 15
	
		list<int> ilist{ 35,40,45 };
		ivec.insert(ivec.begin(), ilist.begin(), ilist.end());
		for (auto i : ivec)
			cout << i << ' ';
		cout << '\n';
		// output -> 35 40 45 55 55 55 77 78 79 80 11 12 13 14 15
	
		// Using one liner to add or erase from containers are more cheaper.
	}
*/

/*
	#include <vector>
	#include <list>
	#include <string>
	
	int main()
	{
		using namespace std;
		vector<int> ivec{ 11,12,13,14,15 };
	
		auto iter = ivec.insert(ivec.begin() + 1, 88);
		cout << *iter << '\n';	// output -> 88
		cout << distance(ivec.begin(), iter) << '\n';	// output -> 1
	
		iter = ivec.insert(ivec.begin() + 1, { 55,66,77 });
		cout << *iter << '\n';	// output -> 55
		cout << distance(ivec.begin(), iter) << '\n';	// output -> 1
	
		// 3 elements added(initializer_list) 
		// but it returns an iterator to first element.
	
		vector<string> svec{ "hello", "world" };
	
		svec.emplace(svec.begin() + 1, 20, 'T');
		// these arguments(20,'T') will be sent to string classes ctor.
		// string(size_t, char) ctor.
		for (auto str : svec)
			cout << str << ' ';
		cout << '\n';
		// output -> hello TTTTTTTTTTTTTTTTTTTT world
	
		svec.emplace_back("robot");
		for (auto str : svec)
			cout << str << ' ';
		// output -> hello TTTTTTTTTTTTTTTTTTTT world robot
		// string(const char*) conversion ctor will be called.
	}
*/

/*
	// pop_back() function is constant time in vector container.
	// pop_back() functions return type is void.

	#include <vector>

	int main()
	{
		using namespace std;
	
		vector<int> ivec{ 1,2,3,4,5,6,7,8,9 };
	
		while (!ivec.empty())
		{
			for (auto i : ivec)
			{
				std::cout << i << ' ';
			}
			std::cout << '\n';
			ivec.pop_back();
		}
	
		// output ->
		//	1 2 3 4 5 6 7 8 9
		//	1 2 3 4 5 6 7 8
		//	1 2 3 4 5 6 7
		//	1 2 3 4 5 6
		//	1 2 3 4 5
		//	1 2 3 4
		//	1 2 3
		//	1 2
		//	1
	}
*/

/*
	#include <vector>
	
	int main()
	{
		using namespace std;
	
		vector<int> ivec{ 1,2,3,4,5,6,7,8,9 };
	
		for (auto i : ivec) {
			std::cout << i << ' ';
		}
		std::cout << '\n';
		// output -> 1 2 3 4 5 6 7 8 9
	
		auto iter = ivec.erase(ivec.begin());
		for (auto i : ivec) {
			std::cout << i << ' ';
		}
		std::cout << '\n';
		// output -> 2 3 4 5 6 7 8 9
	
		std::cout << "item in iterators position after erase() = " << *iter << '\n';
		// output -> item in iterators position after erase() = 2
	
	
		ivec.erase(prev(ivec.end()));
		for (auto i : ivec) {
			std::cout << i << ' ';
		}
		std::cout << '\n';
		// output -> 2 3 4 5 6 7 8'
	
		ivec = { 1,2,3,4,5,6,7,8,9 };
		while (!ivec.empty()) {
			for (auto i : ivec) {
				std::cout << i << ' ';
			}
			ivec.erase(ivec.begin());
			std::cout << '\n';
		}
		// output ->
		//	1 2 3 4 5 6 7 8 9
		//	2 3 4 5 6 7 8 9
		//	3 4 5 6 7 8 9
		//	4 5 6 7 8 9
		//	5 6 7 8 9
		//	6 7 8 9
		//	7 8 9
		//	8 9
		//	9
	}
*/

/*
	// range parameter erase()
	#include <vector>
	
	int main()
	{
		using namespace std;
	
		vector<int> ivec{ 1,2,3,4,5,6,7,8,9 };
	
		// ivec.erase(ivec.begin(), ivec.begin() + 3);
		ivec.erase(ivec.begin(), next(ivec.begin(), 3));
		// Those 2 lines are same
	
		for (auto i : ivec) {
			std::cout << i << ' ';
		}
		std::cout << '\n';
		// output -> 4 5 6 7 8 9
	
		// Q. Leave only first and the last element in vector and delete others?
	
		ivec = { 1,2,3,4,5,6,7,8,9 };
	
		ivec.erase(next(ivec.begin()), prev(ivec.end()));
		for (auto i : ivec) {
			std::cout << i << ' ';
		}
		std::cout << '\n';
		// output -> 1 9
	}
*/

/*
	// Erasing all elements in vector.
	#include <vector>
	
	int main()
	{
		using namespace std;
	
		vector<int> ivec{ 1,2,3,4,5,6,7,8,9,10 };
		cout << "ivec.size() = " << ivec.size() << '\n';
		// output -> ivec.size() = 10
	
	
		ivec = { 1,2,3,4,5,6,7,8,9,10 };
		ivec.clear();
		// clear() function does not have a return type.
		cout << "ivec.size() = " << ivec.size() << '\n';
		// output -> ivec.size() = 0
	
	
		ivec = { 1,2,3,4,5,6,7,8,9,10 };
		ivec.erase(ivec.begin(), ivec.end());
		// erase() with whole range erase all elements.
		cout << "ivec.size() = " << ivec.size() << '\n';
		// output -> ivec.size() = 0
	
	
		ivec = { 1,2,3,4,5,6,7,8,9,10 };
		ivec.resize(0);
		// size will become 0 and it means erasing all elements
		cout << "ivec.size() = " << ivec.size() << '\n';
		// output -> ivec.size() = 0
	
	
		ivec = { 1,2,3,4,5,6,7,8,9,10 };
		ivec = {};
		// using empty initalizer list
		cout << "ivec.size() = " << ivec.size() << '\n';
		// output -> ivec.size() = 0
	
	
		ivec = { 1,2,3,4,5,6,7,8,9,10 };
		ivec = vector<int>{};
		// giving temp vector object and using copy assignment.
		cout << "ivec.size() = " << ivec.size() << '\n';
		// output -> ivec.size() = 0
	}
*/

/*
	---------------------------
	| lexicographical compare | 
	---------------------------
*/

/*
	containers default comparison is lexicographical compare.
	if containers element count and elements are same they are equal containers.

	first container  -> 5 6 7 2 5 5 3 2 
	second container -> 7
	-------------------------------
	in these 2 containers because of first elements 7 > 5
	second container is bigge than first container.

	first container  -> 5 3 4 5
	second container -> 5 3 4 5 6
	-------------------------------
	in these 2 containers because of all elements are same
	but second container has one more element
	second container is bigger than first container.

	first container  -> z
	second container -> abc
	-------------------------------
	first container is bigger than second container

	first container  -> hello
	second container -> helloworld
	-------------------------------
	second container is bigger than first container
*/

/*
	#include <vector>
	
	int main()
	{
		using namespace std;
	
		vector<int> x(100'000, 98);
		cout << "x.size() = " << x.size() << '\n';
		// output -> x.size() = 100000
	
		vector<int> y{ 99 };
		cout << "y.size() = " << y.size() << '\n';
		// output -> y.size() = 1
	
		cout << boolalpha << (x < y);	// output -> true
		// second container is bigger than first container
		// 99 is bigger than 98
	}
*/

/*
	#include <vector>
	#include <list>
	
	int main()
	{
		using namespace std;
	
		vector<int> ivec{ 3, 6, 8, 1 };
		list<int> ilist{ 3, 6, 9, 1 };
	
		ivec < ilist;	// syntax error
		// container types are different.
		// one of them is vector, and the other one is list.
	
		auto b = lexicographical_compare(ivec.begin(), ivec.end(), ilist.begin(), ilist.end());
		// is ivec is smaller(lesser) than ilist.
		// default predicate is less.
	
		cout << boolalpha << b << '\n';	// output -> true
		// ivec is lesser than ilist.
	
		auto c = lexicographical_compare(ivec.begin(), ivec.end(), ilist.begin(), ilist.end(), greater());
		cout << boolalpha << c << '\n';	// output -> false
	}
*/

/*
	#include <vector>
	#include <string>
	
	int main()
	{
		using namespace std;
	
		vector<string> x(100'000, "hello");
		vector<string> y(100'000, "world");
	
		x.swap(y);
		std::swap(x, y);
		// Pointers inside vectors will swap.
	}
*/

/*
	---------------------------------
	| lambda expressions (function) |	C++11
	---------------------------------
	-> additions in C++14, C++17, C++20
*/

/*
	-> When we use lambda expression, compiler is generating a temp object.
	-> The temp object that generetade by compiler is called `closure object`.
	-> The class that has been created is called `closure type`.
	-> For every lambda expression even if they are same 
		but used in different places,
		compiler will generate different closure types.
	-> Every lambda expression is a functor class 
	-> Lambda expressions value categoryt is PR value, 
		because of they are temp objects.
*/

/*
	class ytz65 {
	public:
		void operator()()const
		{
	
		}
	};
	
	int main()
	{
		[]() {}();
	
		// [](){}		-> lambda expression.
		// [](){}();	-> temp object created from lambda expression
	
		ytz65{}();	// same like temp object created with lambda expression.
	}
*/

/*
	[ ] -> if it is empty -> stateless lambda
	--> if it is a stateless lambda, the class that compiler generate
	did not have non-static data members.
	--> [ ] if we write something inside it, it is called capture clause.

	[]() -> `()` is functions parameter paranthesis
	[](int x, int y)	
	--> if operator call function does not have a parameter, it is possible that we did not 
	write parameter paranthesis in lambda expressions.
	[]{}(); --> no parameter paranthesis in this lambda expression.

	[](){} -> `{}` is functions main block

	[](){
		// code here in functions main block.
		std::cout << 'here is main block..';
	}
*/

/*
	class ytz65 {
	public:
		int operator()(int x) const
		{
			return x * x;
		}
	};
	
	int main()
	{
		[](int x) { return x * x; };
		// Those 2 classes are same.
		// compiler will use type deduction to find out the return type.
	
		// if there is no return value, return type will be void.
	}
*/

/*
	#include <type_traits>
	
	int main()
	{
		auto y = [](int x) {return x * x; }(10);
		std::cout << "y = " << y << '\n';	// output -> y = 100
		// y's type is int.
	
		auto z = [](int x) {return x * x; };
		// z's type is functor object.
	
		std::cout << z(12) << '\n';	// output -> 144
		std::cout << z(5) << '\n';	// output -> 25
	
		std::cout << typeid(z).name() << '\n';
		// output -> class `int __cdecl main(void)'::`2'::<lambda_2>
		// z is a class type (functor object)
	
	
		auto a = [](int x) {return x * x; };
		auto b = [](int x) {return x * x; };
	
		std::is_same_v<decltype(a), decltype(b)>;	// false
		// compiler will generate different class types for every lambda expressions
		// even if they have the same structure.
	}
*/

/*
	#include <vector>
	
	bool mod5(int x)
	{
		return x % 5 == 0;
	}
	
	int main()
	{
		using namespace std;
	
		vector<int> ivec{ 3, 6, 8, 9, 1, 5, 10, 46 };
	
		if (auto iter = find_if(ivec.begin(), ivec.end(), [](int x) {return x % 5 == 0; });
			iter != ivec.end()) {
			std::cout << "found = " << *iter << '\n';
		} // output -> found = 5
	
		if (auto iter = find_if(ivec.begin(), ivec.end(), &mod5);
		iter != ivec.end()) {
			std::cout << "found = " << *iter << '\n';
		} // output -> found = 5
	
		// Those 2 if statements are same, 
		// one is using lambda expression as a callable,
		// other is using global function as a callable
	}
*/

/*
	#include <set>
	
	template <typename T>
	class Myclass {
	
	};
	
	int main()
	{
		using namespace std;
	
		Myclass<decltype([](int x, int y) {return std::abs(x) < std::abs(y); })> mx;
	
		// we can use the type of lambda expression 
		// which is a functor class object as a class templates specialization.
	}
*/

/*
	[]()mutable {code}
	[]()-> int {code}
	[]()noexcept{code}
	[]()constexpr{code}

	// normally it is possible to not write parameter paranthesis 
	// if there is no parameter.

	// But if we are using mutable keyword, trailing return type, 
	// noexcept keyword or constexpr keyword,
	// we need to write parameter paranthesis even if the lambda expression does not have a parameter.
*/

/*
	int g_x = 10;
	
	int main()
	{
		using namespace std;
	
		auto f = []() {
			cout << "hello\n";
		};
		// this lambda expression is a class object.
	
		f();	// output -> hello
		// we use class objects operator call function.
	
		[]() {
			cout << "world\n";
		}();
		// output -> world
	
		int x = 5;
		static int y = 7;
	
		[]() {
			cout << x;		// syntax error. Local variable is not visible in class scope.
			cout << y;		// legal
			cout << g_x;	// legal
	
			// static storage duration objects(global and static variables) can be used
			// in lambda expressions main block
		}();
	}
*/

/*
	#include <string>
	
	class xyz125_ {
	public:
		xyz125_(int a) : x(a){}
	
		bool operator()(int val)const
		{
			return val % x == 0;
		}
	private:
		int x;
	};
	
	int main()
	{
		using namespace std;
		cout << boolalpha;
		int x = 5;
	
		cout << xyz125_(x)(12) << '\n';		// output -> false
		cout << xyz125_(x)(10) << '\n';		// output -> true
	
		cout << [x](int val) {return val % x == 0; }(12) << '\n';	// output -> false
		cout << [x](int val) {return val % x == 0; }(10) << '\n';	// output -> true
		// this lambda expression acts like xyz125_ class
		// we are capturing local x variable in capture clause -> copy capture
	
	
		int a = 2;
		string s{ "hello" };
		double dval = 4.5;
	
		[a, s, dval]() {}();
		// we can capture multiple local variable in capture clause -> copy capture
	
		[=]() {}();
		auto f = [=]() {return a * dval; }();
		// we can capture all local variables using `=` token inside capture clause.
	}
*/

/*
	#include <random>
	
	class comp_gen {
	public:
		comp_gen(int x) : x(x) {}
		void operator()(int val)const
		{
			x += val;	// syntax error
		}
	private:
		int x;
	};
	
	class comp_gen_2 {
	public:
		int foo()const
		{
			m_eng();	// syntax error
		}
	private:
		std::mt19937 m_eng;
	};
	
	int main()
	{
		using namespace std;
	
		int x = 5;
	
		auto f = [x](int val) {return x += val; };	// syntax error
		// we are using x as a data member of compile generated class
		// but default operator call function of that class 
		// is a const member function
		// const member functions can not change data members values.
	
		auto k = [x](int val)mutable {return x += val; };	// legal
		// when we use mutable keyword, compiler generated classes 
		// operator call function will become a non-const member function.
	
	
		mt19937 eng;
		auto p = [eng]() {return eng(); };			// syntax error
		// we are trying to call non-const member function 
		// with const operator call function(member function)
		// trying to convert hidden parameter const T* to -> T* is not valid.
	
		auto r = [eng]()mutable {return eng(); };	// legal
	}
*/

/*
	class comp_gen {
	public:
		comp_gen(int val) : m_x(val){}
	
		void foo(int i)
		{
			m_x *= i;
		}
	private:
		int m_x;	// m_x has been changed not the local variable.
	};
	
	class comp_gen_2 {
	public:
		comp_gen_2(int& val) : m_x(val) {}
	
		void foo(int i) const
		{
			m_x *= i;
		}
		// const member function is not a syntax error
		// because we are changing the object that reference binds to,
		// not the reference itself.
	private:
		int& m_x;
	};
	
	int main()
	{
		using namespace std;
		int x = 5;
	
		auto f = [x](int val)mutable { x *= val; };
		f(10);
	
		std::cout << "x = " << x << '\n';	// output -> x = 5
		// x inside main block of lambda expression is data member of the class object.
		// we did not change the local variables value, we change classes data members value.
	
		comp_gen gen(x);
		gen.foo(20);
		std::cout << "x = " << x << '\n';	// output -> x = 5
	
		comp_gen_2 gen2(x);
		gen2.foo(19);
		std::cout << "x = " << x << '\n';	// output -> x = 95
	
		int y = 5;
		auto k = [&y](int i) { y *= i; };
		k(20);
		std::cout << "y = " << y << '\n';	// output -> y = 100
	}
*/

/*
	int main()
	{
		using namespace std;
	
		int a = 10;
		string s{ "hello" };
		double dval = 4.5;
	
		[&a, &s, &dval]() {}();
		// local variables are captured by reference semantics.
	
		[&]() {}();
		// capture all local variables by reference semantics.
	
		[&a, s, &dval]() {}();
		// a and dval local variables are captured by reference semantics, s variable is copy captured.
	
		[=, &dval]() {}();
		// capture all by copy but dval by reference
	
		[&, dval]() {}();
		// capture all by reference and dval by copy
	
		auto f = [cout]() {}();	// syntax error
		// E1731 a variable with static storage duration cannot be captured in a lambda
	}
*/

/*
	int main()
	{
		auto k = [](int x) {return x + 5; };
		auto l = [](int x)->double {return x + 5; };
	
		auto x = k(20);	// x's type is int
		auto y = l(20);	// y's type is double
	
	
		auto f1 = [](int x) {
			if (x > 10)
				return x + 5;
			else
				return x * 1.4;
		};
		// return type can both be deduce to int or double. syntax error
		// in this scenerio we need to use trailing return type.
	
		auto f2 = [](int x)->double {
			if (x > 10)
				return x + 5;
			else
				return x * 1.4;
		};
	}
*/

/*
	void foo()noexcept;	// no-throw guarantee
	
	int main()
	{
		auto k = []() {};
		auto l = []()noexcept {};
	
	
		constexpr auto a = noexcept(k());
		// a is false, k function does not give no-throw guarantee
		constexpr auto b = noexcept(l());
		// b is true, l function gives no-throw guarantee
	}
*/

/*
	// constexpr functions can not have static storage duration variables.

	#include <array>
	
	int main()
	{
		auto f = [](int x) {return x * 5; };
	
		// to understand f() function is a constant expression,
		// we can declare a constexpr auto variable and check if it is
		// calculating the result in compile time or giving a syntax error.
	
		constexpr auto val = f(12);	// val = 60
		// f(12) is a constant expression.
	
		auto k = [](int x) {
			static int y = 10;
			return x * y;
		};
	
		constexpr auto val2 = k(5);	// syntax error
		// k(5) is not a constant expression.
	
		std::array<int, f(20)> ar;	// legal
		std::array<int, k(2)> ar2;	// syntax error
	}
*/

/*
	int main()
	{
		auto f = [](int x) constexpr {
			static int y = 6;	// syntax error
			return x * y;
		};
	
		// when we add constexpr keyword in lambda function.
		// If there is any statement that violate constexpr rules,
		// it will be syntax error!
	
		auto k = [](int x) {
			static int y = 6;
			return x * y;
		};
		// no syntax error
		// but we can not use this lambda function as a constant expression.
	}
*/

/*
	---------------------------------
	| generalized lambda expression |
	---------------------------------
*/

/*
	#include <string>
	
	class Myclass {
	public:
		template <typename T>
		T operator()(T x)
		{
			return x;
		}
	};
	
	class comp_gen {
	public:
		template <typename T>
		auto operator()(T x)
		{
			return x + x;
		}
	};
	
	int main()
	{
		using namespace std;
	
		Myclass m;
		m(12);
		m(6.2);
	
		auto f = [](auto x) {
			return x + x;
		};
	
		string str{ "hello" };
		cout << f(12) << '\n';	// output -> 24
		cout << f(6.2) << '\n';	// output -> 12.4
		cout << f(str) << '\n';	// output -> hellohello
	}
*/

/*
	#include <list>
	#include <vector>
	
	int main()
	{
		auto get_size = [](const auto& c) {return c.size(); };
	
		std::vector<int> ivec(20);
		std::list<double> dlist(50);
	
		std::cout << "size of ivec = " << get_size(ivec) << '\n';
		// output -> size of ivec = 20
		std::cout << "size of dlist = " << get_size(dlist) << '\n';
		// output -> size of dlist = 50
	}
*/

/*
	#include <algorithm>
	#include <memory>
	#include <vector>
	#include <string>
	
	using namespace std;
	
	void f1(vector<shared_ptr<string>>& svec)
	{
		sort(begin(svec), end(svec), [](const shared_ptr<string>& a,
			const shared_ptr<string>& b) { return *a < *b;  });
	
		for_each(begin(svec), end(svec), [](const shared_ptr<string>& sp)
			{ cout << *sp << '\n'; });
	
		std::cout << "\n\n";
	}
	
	void f2(vector<shared_ptr<string>>& svec)
	{
		sort(begin(svec), end(svec), [](const auto& a, const auto& b) { return *a < *b;  });
	
		for_each(begin(svec), end(svec), [](const auto& sp) { cout << *sp << '\n'; });
	}
	
	int main()
	{
		vector<shared_ptr<string>> svec;
	
		svec.emplace_back(new string{ "cccc" });
		svec.push_back(make_shared<string>("bbbbb"));
		svec.emplace_back(new string{ "aaaa" });
	
		f1(svec);
		f2(svec);
	}
*/

/*
	#include <cstdio>
	#include <vector>
	#include <algorithm>
	
	void func(int) { putchar('i'); }
	void func(double) { putchar('d'); }
	void func(long) { putchar('l'); }
	
	int main()
	{
		using namespace std;
	
		vector<int> ivec(20);
		vector<double> dvec(5);
	
		for_each(ivec.begin(), ivec.end(), func);	// syntax error
		// which func overload ?
	
		for_each(ivec.begin(), ivec.end(), (void(*)(int))func);
		// casting func functions address to void(*)(int)
		// output -> iiiiiiiiiiiiiiiiiiii
	
		for_each(ivec.begin(), ivec.end(), [](auto x){ func(x); });
		// output -> iiiiiiiiiiiiiiiiiiii
		// x will deduce to int in lambda function, func(int) overload will be called.
	
		for_each(dvec.begin(), dvec.end(), [](auto x){ func(x); });
		// output -> ddddd
	}
*/

/*
	#include <initializer_list>
	
	template <typename... Args>
	void print(Args&&... args)
	{
		std::initializer_list<int>{((std::cout << std::forward<Args>(args) << '\n'), 0)...};
	}
	
	int main()
	{
		auto f = [](auto&&... param) {
			print(std::forward<decltype(param)>(param)...);
		};
	
		f(12, 3.4, 4.5f, "hello world");
		// output ->
		//	12
		//	3.4
		//	4.5
		//	hello world
	}
*/

/*
	-----------------------
	| lambda init capture |		C++14
	----------------------- 
*/

/*
	class comp_gen_f {
	public:
		comp_gen_f(int x) : val{x * 6}{}
	private:
		int val;
	};
	
	class comp_gen_k {
	public:
		comp_gen_k(int x) : x{ x * 6 } {}
	private:
		int x;
	};
	
	int main()
	{
		int x = 10;
	
		auto f = [val = x * 6](int a) {
			return val + a;
		};
	
		auto f2 = [x](int a) {
			return (x * 6) + a;
		};
		// f and f2 functions acts like same but the syntax is different
		// f lambda objects compiler generated class is like comp_gen_f class.
	
		std::cout << f(20) << '\n';	// output -> 80
	
	
		auto k = [x = x * 6](int a) {
			return x + a;
		};
		// [x = x * 6] -> first x is data member, second x is local variable.
		// k lambda objects compiler generated class is like comp_gen_k class.
	
		std::cout << k(20) << '\n';	// output -> 80
	}
*/

/*
	int main()
	{
		int x = 10;
	
		auto f1 = [&val = x](int a) {
	
		};
	
		auto f2 = [&x = x](int a) {
			x = 2;	// when we use x here, we are using compiler generated classes data member x.
		};
		// f1 and f2 lambda expressions are same.
	}
*/

/*
	// The reason that we use lamba init capture is for move-only types.

	#include <memory>
	#include <string>
	
	class Myclass {
	public:
		Myclass() = default;
		Myclass(Myclass&&);
		Myclass& operator=(Myclass&&);
		// copy members are implicitly deleted.
	};
	
	int main()
	{
		Myclass mx;
	
		auto f = [x = std::move(mx)]() {};
		// mx is in moved-from state now.
	
		std::unique_ptr<std::string> uptr{ new std::string{"hello world"} };
	
		std::cout << (uptr ? "not empty" : "empty") << '\n';
		// output -> not empty
	
		auto f = [uptr = std::move(uptr)]() {
			std::cout << *uptr << '\n';
		};
	
		f();	// output -> hello world
	
		std::cout << (uptr ? "not empty" : "empty") << '\n';
		// output -> empty
		// uptr is in moved-from state.
	}
*/

/*
	int main()
	{
		auto f = [](int x) {return x * x; };	// stateless lambda
	
		decltype(f) g;	// syntax error before C++20
		// the default constructor of "lambda [](int x)->int" cannot be referenced, it is a deleted function
		// in C++20 closure types default ctor is not deleted.
	
		auto g = f;
		// copy ctor is not deleted
		g = f;	// syntax error
		// copy assignment is also deleted before C++20
	
		int y = 20;
		auto f2 = [y](int x) {return x * y; };	// stateful lambda
	
		decltype(f2) g2;	// still syntax error after C++20 too when we use stateful lambda.
	}
*/

/*
	using fcmp = int (*)(int);
	
	class comp_gen {
	public:
		int operator()(int x)const
		{
			return x * 6;
		}
	
		operator fcmp()const
		{
			// function that lets implicit conversion from closure object
			// that compiler generated to function pointer.
		}
	};
	
	int main()
	{
		int (*fp2)(int) = [](int x) {return x * 6; };
		// implicit conversion from closure object to function pointer in stateless lambda.
		std::cout << fp2(20) << '\n';	// output -> 120
	
		comp_gen cg;
		int (*ff)(int) = cg;	// legal
		// because of there is an operator member function lets implicit conversion
		// from comp_gen object to function pointer -> int (*)(int)
	
		auto fn = [](int x) {return x * 6; };
		int(*fp)(int) = fn;	// legal
		fp = fn;			// legal
	}
*/

/*
	int main()
	{
		int y = 55;
	
		auto fn = [y](int x) {return x * y; };
		int (*fp)(int) = fn;	// syntax error
		fp = fn;				// syntax error
	
		// when we use stateful lambda
		// there is no implicit conversion from closure object to function pointer.
	}
*/

/*
	-------------------------
	| positive lambda idiom |
	-------------------------
*/

/*
	int foo(int) {}
	
	class Myclass {
	public:
		operator int()const;
	};
	
	using fptr = int (*)(int);
	
	class Yourclass {
	public:
		operator fptr()const;
	};
	
	int main()
	{
		int x = 10;
		int* p = &x;
		auto val = +p;		// legal
	
		int (*fp)(int) = foo;
		auto f_ptr = +fp;	// legal
	
		Myclass m;
		+m;					// legal
		// Myclass can convert to int [operator int() const -> member function]
	
		Yourclass y;
		+y;					// legal
		+y.operator fptr();
		// These 2 lines are same.
	
		// Yourclass can convert to function pointer which can be an operand of sign + operator.
	}
*/

/*
	template <typename T>
	void func(T f)
	{
		f(123);
	}
	
	int main()
	{
		auto f = [](int x) {return x * 5; };
		// f's type is closure type.
	
		auto fp = +[](int x) {return x * 5; };
		// fp's type is function pointer int (*fp)(int)
	
	
		func([](int x) {return x * 5; });
		// sending closure type as an argument.
		func(+[](int x) {return x * 5; });
		// sending function pointer as an argument
	}
*/

/*
	----------------------------------------------------------------
	| Immediately Invoked Function(Lambda) Expression [IIFE] idiom |
	----------------------------------------------------------------
*/

/*
	int main()
	{
		int x = 10;
	
		[x](int y) {
			return x * y;
		}(10);
		// we immediately call the lambda function.
		// general purpose of IIFE is assigning values to const variables.
	
		int a = 5, b = 7;
		int k = 12;
	
		const int cx = [=](int val) {
			return a * b + 3;
		}(k);
	}
*/

/*
	auto foo()
	{
		return [](int val) {return val * 5; };
	}
	// functions return type is closure type
	
	int main()
	{
		auto f = foo();
		std::cout << f(18) << '\n';
	}
*/

/*
	auto foo(int x)
	{
		return [x](int val) {return val * x; };
	}
	
	int main()
	{
		auto f = foo(19);
	
		std::cout << f(10) << '\n';	// output -> 190
		// x = 19, val = 10
	
		std::cout << foo(19)(20) << '\n';	// output -> 380
		// x = 19, val = 20
	}
*/

/*
	auto foo(int x)
	{
		return [&x](int val) {return val * x; };
	}
	
	int main()
	{
		auto f = foo(20);
		// closure objects data member int& will bind to parameter variable x.
		// After foo function executed x's life will end and data member will become dangling reference
	
		std::cout << f(34) << '\n';	// undefined behaviour.
	}
*/

/*
	#include <algorithm>
	#include <vector>
	#include <random>
	
	int foo()
	{
		return 1;
	}
	
	int main()
	{
		using namespace std;
		vector<int> ivec(10);
	
		generate_n(ivec.begin(), 10, foo);
	
		for (auto i : ivec)
		{
			cout << i << ' ';
		}
		cout << '\n';
		// output -> 1 1 1 1 1 1 1 1 1 1
	
		generate_n(ivec.begin(), 10, [] {return rand() % 1000; });
	
		for (auto i : ivec)
		{
			cout << i << ' ';
		}
		cout << '\n';
		// output -> 41 467 334 500 169 724 478 358 962 464
	
		mt19937 eng;
		uniform_int_distribution dist{ 56, 98 };
	
		generate_n(ivec.begin(), 10, [&eng, &dist] {return dist(eng); });
	
		for (auto i : ivec)
		{
			cout << i << ' ';
		}
		// output -> 91 61 94 91 61 97 95 65 83 69
	}
*/

/*
	// remove, remove_if, unique algorithms 
*/

/*
	#include <vector>
	#include <algorithm>
	
	int main()
	{
		using namespace std;
	
		vector<int> ivec{ 1, 2, 4, 3, 3, 2, 1, 4, 5 };
		cout << "ivec.size() = " << ivec.size() << '\n';	// output -> ivec.size() = 9
	
		remove(ivec.begin(), ivec.end(), 3);
	
		for (auto i : ivec) {
			cout << i << ' ';
		}
		cout << '\n';
		// output -> 1 2 4 2 1 4 5 4 5
		cout << "ivec.size() = " << ivec.size() << '\n';	// output -> ivec.size() = 9
	}

	// vector's size is not changing when we use remove algorithm.
	// These algorithms is doing logic remove operation.
*/

/*
	#include <vector>
	#include <algorithm>
	
	int main()
	{
		// 1232432352312312		when we remove 3's.
		// 12242521212
		//			  | returns iterator to this position.
	
		// We can use logic_end and real_end iterators to erase elements for real.
	
		using namespace std;
		vector<int> ivec{ 1, 2, 4, 3, 3, 2, 1, 4, 5 };
		std::cout << "ivec.size() = " << ivec.size() << '\n';
		// output -> ivec.size() = 9
	
		auto logic_end = remove(ivec.begin(), ivec.end(), 3);
	
		auto not_deleted_count = distance(ivec.begin(), logic_end);
		std::cout << "Not deleted element count = " << not_deleted_count << '\n';
		// output -> Not deleted element count = 7
	
		auto deleted_count = distance(logic_end, ivec.end());
		std::cout << "Deleted element count = " << deleted_count << '\n';
		// output -> Deleted element count = 2
	
		for_each(ivec.begin(), logic_end, [](int x) {std::cout << x; });
		std::cout << '\n';
		// output -> 1242145
		// we can use not deleted element in another algorithm
	
		ivec.erase(logic_end, ivec.end());
		std::cout << "ivec.size() = " << ivec.size() << '\n';
		// output -> ivec.size() = 7
		// we can use range erase for physical erase (decreasing size of the container)
	}
*/

/*
	// remove-erase idiom

	#include <vector>
	#include <algorithm>
	
	int main()
	{
		using namespace std;
		vector<int> ivec{ 1, 2, 4, 3, 3, 2, 4, 5, 3, 2, 1, 4, 2, 3, 1, 1, 4, 5 };
	
		std::cout << "ivec.size() = " << ivec.size() << '\n';
		// output -> ivec.size() = 18
	
		ivec.erase(remove(ivec.begin(), ivec.end(), 3), ivec.end());
		// remove-erase idiom.
	
		std::cout << "ivec.size() = " << ivec.size() << '\n';
		// output -> ivec.size() = 14
	
	
		// since C++20
		ivec = { 1, 2, 4, 3, 3, 2, 4, 5, 3, 2, 1, 4, 2, 3, 1, 1, 4, 5 };
		std::cout << "ivec.size() = " << ivec.size() << '\n';
		// output -> ivec.size() = 18
	
		auto deleted_item_count = erase(ivec, 3);
	
		std::cout << "deleted item count = " << deleted_item_count << '\n';
		// output -> deleted item count = 4
		std::cout << "ivec.size() = " << ivec.size() << '\n';
		// output -> ivec.size() = 14
	}
*/

/*
	#include <algorithm>
	#include <vector>
	#include <random>
	
	int main()
	{
		using namespace std;
	
		vector<int> ivec;
		mt19937 eng;
		uniform_int_distribution dist{ 1,5 };
	
		generate_n(back_inserter(ivec), 1000, [&] {return dist(eng); });
		cout << "ivec.size() = " << ivec.size() << '\n';
		// output -> ivec.size() = 1000
	
		ivec.erase(remove_if(ivec.begin(), ivec.end(), [](int x) {return x > 3; }), ivec.end());
		// 4's and 5's are deleted.
	
		cout << "ivec.size() = " << ivec.size() << '\n';
		// output -> ivec.size() = 609
	}
*/

/*
	#include <algorithm>
	#include <vector>
	#include <random>
	
	int main()
	{
		using namespace std;
	
		vector<int> ivec;
	
		generate_n(back_inserter(ivec), 100, [&] {return rand() % 4; });
	
		auto logic_end_iter = remove(ivec.begin(), ivec.end(), 2);
	
		for_each(logic_end_iter, ivec.end(), [](int x) {cout << x; });
		// output -> 12122211013020020300323122211
		// no undefined behaviour. But no guarantee that all of the elements are 2.
	}
*/

/*
	#include <algorithm>
	#include <string>
	
	int main()
	{
		std::string str{ "Hello world we are live from Istanbul, come and join us!" };
	
		// aeoiu -> remove those characters
	
		str.erase(remove_if(str.begin(), str.end(), [](char c) {
			return std::string{ "aeoui" }.find(c) != std::string::npos; }), str.end());
		std::cout << str << '\n';
		// output -> Hll wrld w r lv frm Istnbl, cm nd jn s!
	
		// since C++20
		str = { "Hello world we are live from Istanbul, come and join us!" };
		erase_if(str, [](char c) { return std::string{ "aeoui" }.find(c) != std::string::npos; });
		std::cout << str << '\n';
		// output -> Hll wrld w r lv frm Istnbl, cm nd jn s!
	}
*/

/*
	// 33344466669999111233334555511118888999222333
	// 34691234518923
	// when we use unique algorithm it will become like above.
	// binary default predicate is equal_to
	
	#include <algorithm>
	#include <vector>
	
	int main()
	{
		using namespace std;
	
		vector<int> ivec{ 3,3,3,4,4,4,6,6,6,6,9,9,9,9,1,1,1,2,3,3,3,3,4,5,5,5,5,1,1,1,1,8,8,8,8,9,9,9,2,2,2,3,3,3 };
	
		cout << "ivec.size() = " << ivec.size() << '\n';	// output -> ivec.size() = 44
	
		ivec.erase(unique(ivec.begin(), ivec.end()), ivec.end());
	
		for (auto i : ivec)
			cout << i << ' ';
		// output -> 3 4 6 9 1 2 3 4 5 1 8 9 2 3
		cout << '\n';
	
		cout << "ivec.size() = " << ivec.size() << '\n';	// output -> ivec.size() = 14
	
		// If we want from smaller to larger only 1 elements in vector
		// 1. We can sort the vector than use unique algorithm
		// 2. We can send them to set, because of set has only unique keys,
		// then will range assign to vector and sort it.
	}
*/

/*
	#include <string>
	#include <vector>
	#include <algorithm>
	
	int main()
	{
		using namespace std;
	
		vector<string> svec{ "a","b", "c", "de", "kle", "smpr", "sprman", "hello", "wrld", "sign", "equal", "add", "ab", "run", "car", "thresh" };
	
		svec.erase(unique(svec.begin(), svec.end(), [](const string& s1, const string& s2) {
			return s1.length() == s2.length();
			}), svec.end());
	
		for (auto i : svec)
			cout << i << ' ';
		// output -> a de kle smpr sprman hello wrld equal add ab run thresh
		cout << '\n';
	
	
		svec = { "a","ab", "ac", "de", "dkle", "smpr", "sprman", "hello", "hwrld", "sign", "equal", "add", "ab", "run", "rar", "resh" };
	
		svec.erase(unique(svec.begin(), svec.end(), [](const string& s1, const string& s2) {
			return s1.front() != s2.front();
			}), svec.end());
	
		for (auto i : svec)
			cout << i << ' ';
		// output -> a ab ac add ab
		cout << '\n';
	}
*/

/*
	vector<bool> specialization is a partial specialization.
	-> It is not storing bool variables, it is storing bool values in bits.
	-> If it stores bool variables for 10k bool vector will use 10k byte memory on heap.
		But because of it is holding in bits 10k / 8 = 1250 byte memory on heap
*/

/*
	#include <vector>
	
	int main()
	{
		using namespace std;
	
		vector<int> ivec;
		vector<bool> bvec;
	
		ivec.flip();
		// int specialization does not have flip() function.
		bvec.flip();
		// bool specialization does have flip() function.
	
		bvec.data();
		// bool specialization does not have data() function.
		// There is no bool* pointer, because it is not storing bool variables.
		ivec.data();
		// int specialization does have data() function.
		// Returning int* pointer.
	}
*/

/*
	#include <vector>
	#include <cstdio>
	
	void display_array(const int* p, size_t size)
	{
		while (size--)
			printf("%d ", *p++);
	}
	
	int main()
	{
		using namespace std;
	
		vector<int> x{ 2, 6, 8, 1, 9, 2, 8, 12, 56 };
	
		display_array(x.data(), x.size());
		// usage of data() function in C api's.
	}
*/

/*
	#include <vector>
	#include <typeinfo>
	
	int main()
	{
		using namespace std;
	
		vector<bool> x{ true, false, true, false, true, true, false };
	
		cout << typeid(x[2]).name() << '\n';
		// output -> class std::_Vb_reference<struct std::_Wrap_alloc<class std::allocator<unsigned int>>>
		// this is a proxy class.
	
		x[2] = false;
		x[2].operator=(true);
		// These 2 lines are same
	
		auto b = x[3];
		// b's type is vector<bool>::reference -> nested type, not bool.
	}
*/

/*
	// mental model for proxy class
	class BVector {
	public:
		class Reference {
	
		};
		Reference& operator[](size_t n);	// returns bits
	private:
		unsigned char mbuff[1000]{};
		// can hold 8000 bool as bits
	};
	
	
	template <typename T, typename A>
	class Vector {
	
	};
	
	template <typename A>
	class Vector<bool, A> {
	
	};
*/

/*
	----------------------
	| sorting algorithms |
	----------------------
*/

/*
	#include <algorithm>
	#include <vector>
	#include <string>
	
	int main()
	{
		using namespace std;
	
		vector<int> ivec{ -2, 5, 7, 4, -5, 6, -8, 23, 17, -12, -65, 79, 75, -45, 23 };
		sort(ivec.begin(), ivec.end());
	
		for (auto i : ivec)
			std::cout << i << ' ';
		std::cout << '\n';
		// output -> -65 -45 -12 -8 -5 -2 4 5 6 7 17 23 23 75 79
	
		sort(ivec.begin(), ivec.end(), [](int x, int y) {
			return abs(x) < abs(y);
			});
	
		for (auto i : ivec)
			std::cout << i << ' ';
		std::cout << '\n';
		// output -> -2 4 -5 5 6 7 -8 -12 17 23 23 -45 -65 75 79
	
		vector<string> svec{ "hello", "world", "we", "are", "live", "from", "istanbul", "zero", "talent" };
		sort(svec.begin(), svec.end());
	
		for (auto i : svec)
			std::cout << i << ' ';
		std::cout << '\n';
		// output -> are from hello istanbul live talent we world zero
	
		sort(svec.rbegin(), svec.rend());
	
		for (auto i : svec)
			std::cout << i << ' ';
		std::cout << '\n';
		// output -> zero world we talent live istanbul hello from are
	
		svec = { "hello", "world", "we", "are", "live", "from", "istanbul", "zero", "talent" };
		sort(svec.begin(), svec.end(), greater<string>{});
		// sort(svec.begin(), svec.end(), greater{});
		// Those 2 lines are same
	
		for (auto i : svec)
			std::cout << i << ' ';
		std::cout << '\n';
		// output -> zero world we talent live istanbul hello from are
	
		const auto fpred = [](const string& s1, const string& s2) {
			return s1.length() < s2.length() || (s1.length() == s2.length() && s1 < s2);
		};
	
		sort(svec.begin(), svec.end(), fpred);
	
		for (auto i : svec)
			std::cout << i << ' ';
		std::cout << '\n';
		// output -> we are from live zero hello world talent istanbul
	}
*/

/*
	// vector, deque, string, array, C-style array can be used in sort algorithm.

	#include <string>
	#include <algorithm>
	
	
	int main()
	{
		using namespace std;
	
		string str{ "hello world we are live from istanbul, it is going to rain again" };
		cout << '[' << str << "]\n";
		// output -> [hello world we are live from istanbul, it is going to rain again]
	
		sort(str.begin(), str.end());
		cout << '[' << str << "]\n";
		// output -> [            ,aaaaabdeeeefggghiiiiiiilllllmnnnnooooorrrrsstttuvww]
	
		sort(str.begin(), str.end(), greater{});
		cout << '[' << str << "]\n";
		// ouyput -> [wwvutttssrrrrooooonnnnmllllliiiiiiihgggfeeeedbaaaaa,            ]
	}
*/

/*
	stable sort (kararli)
	unstable sort (kararsiz)


	ali 15
	ali 26
	ayse 29
	mehmet 17
	ali 24
	ayse 43
	mehmet 39
	mehmet 27				SORT THESE NAMES
	-------------------------------------------------------------------------
	ali 15
	ali 24
	ali 26
	ayse 29
	ayse 43
	mehmet 17
	mehmet 27
	mehmet 39				unstable sort because numbers are sorted too.
	------------------------------------------------------------------------
	ali 15
	ali 26
	ali 24
	ayse 29
	ayse 43
	mehmet 17
	mehmet 39
	mehmet 27				stable sort because numbers are not sorted.
	------------------------------------------------------------------------


	// stable sort will sort the elements but if elements hiearchies are same,
	// they will be ordered like their order, before the sorting operation.

	// unstable sort will sort the elements but if elements hiearachies are same,
	// they is no guarantee that which element in same hiearchy are before or after.
*/

/*
	#include <vector>
	#include <utility>
	#include <string>
	#include <algorithm>
	#include <random>
	
	using sipair = std::pair<std::string, int>;
	
	int main()
	{
		using namespace std;
	
		const string name_arr[]{ "ali", "ayse", "mehmet", "baran", "faruk", "zehra", "kerem", "tevfik", "sergen", "sibel", "kamil" };
		const int age_arr[]{20, 21, 22, 23, 24, 25};
	
		vector<sipair> vec;
		vec.reserve(100);
	
		for (size_t i = 0; i < 100; i++)
		{
			vec.push_back(make_pair(name_arr[rand() % size(name_arr)], age_arr[rand() % size(age_arr)]));
		}
	
		sort(vec.begin(), vec.end());
	
		sort(vec.begin(), vec.end(), [](const auto& p1, const auto& p2) {
			return p1.second < p2.second;
			});
	
		for (auto i : vec)
			std::cout << "first = " << i.first << " second = " << i.second << '\n';
		std::cout << '\n';
	
		// SORT output ->
		//  first = ali second = 20
		//	first = ali second = 20
		//	first = ali second = 20
		//	first = ali second = 20
		//	first = sergen second = 20	->
		//	first = kamil second = 20	-> In those 2 line s > k => not stable
		//	first = kamil second = 20
		//	first = faruk second = 20
		//	first = kerem second = 20
		//	first = faruk second = 20
		//	first = faruk second = 20
		//	first = zehra second = 20
		//	first = kamil second = 20	-> In those two lines z > k => not stable
		//	first = sibel second = 20
		//	first = sibel second = 20
		//	first = sibel second = 20
		//	first = kamil second = 20
		//	first = sergen second = 20 ......
	
		sort(vec.begin(), vec.end());
	
		stable_sort(vec.begin(), vec.end(), [](const auto& p1, const auto& p2) {
			return p1.second < p2.second;
			});
	
		for (auto i : vec)
			std::cout << "first = " << i.first << " second = " << i.second << '\n';
		std::cout << '\n';
	
		// STABLE_SORT output ->
		//	first = ali second = 20
		//	first = ali second = 20
		//	first = ali second = 20
		//	first = ali second = 20
		//	first = faruk second = 20
		//	first = faruk second = 20
		//	first = faruk second = 20
		//	first = kamil second = 20
		//	first = kamil second = 20
		//	first = kamil second = 20
		//	first = kamil second = 20
		//	first = kerem second = 20
		//	first = sergen second = 20
		//	first = sergen second = 20
		//	first = sibel second = 20
		//	first = sibel second = 20
		//	first = sibel second = 20
		//	first = zehra second = 20
	}
*/

/*
	partial sort algorithm -> 
		e.g we have 100k students and their exam results
			-> we only need 20 best student(results)
	-> sorting 100k students and getting first 20 is inefficient.
*/

/*
	#include <vector>
	#include <string>
	#include <algorithm>
	#include <random>
	
	int main()
	{
		using namespace std;
	
		vector<string> svec;
		svec.reserve(100);
	
		const string name_arr[]{ "ali", "ayse", "mehmet","sadik","ceyde","cemile", "baran", "faruk", "zehra", "kerem", "tevfik", "sergen", "sibel", "kamil"};
	
	
		for (size_t i = 0; i < 100; i++)
		{
			svec.push_back(name_arr[rand() % size(name_arr)] + " " + name_arr[rand() % size(name_arr)]);
		}
	
		partial_sort(svec.begin(), next(svec.begin(), 10), svec.end());
		// sort first 10 elements.
	
		for (auto i : svec)
			cout << i << '\n';
		cout << '\n';
	
		// output ->
		//	ali cemile
		//	ali kamil
		//	ali kerem
		//	ali sibel
		//	ali zehra
		//	ayse baran
		//	ayse baran
		//	ayse ceyde
		//	ayse faruk
		//	ayse kamil
		//	sibel baran
		//	mehmet sadik
		//	mehmet kerem
		//	sibel cemile
		//	kamil tevfik
		//	sibel ayse
	
		vector<string> destvec(10);
	
		partial_sort_copy(svec.begin(), svec.end(), destvec.begin(), destvec.end());
	
		for (auto i : destvec)
			cout << i << '\n';
		cout << '\n';
	
		// output ->
		//	ali cemile
		//	ali kamil
		//	ali kerem
		//	ali sibel
		//	ali zehra
		//	ayse baran
		//	ayse baran
		//	ayse ceyde
		//	ayse faruk
		//	ayse kamil
	}
*/

/*
	//	nth_element algorithm 

	#include <vector>
	#include <string>
	#include <algorithm>
	#include <random>
	
	int main()
	{
		using namespace std;
	
		mt19937 eng;
		uniform_int_distribution dist{ 0,10000 };
	
		vector<int> ivec(100);
		generate(ivec.begin(), ivec.end(), [&]() {return dist(eng); });
	
		nth_element(ivec.begin(), ivec.begin() + ivec.size() / 2, ivec.end());
	
		cout << "median = " << ivec[ivec.size() / 2] << '\n';
		// output -> median = 6324
	
		for (auto i : ivec)
			cout << i << ' ';
	
		// elements before 6324 needs to be smaller than 6324 but do not need to be in order
		//	e.g first elements -> 971 1354 2119 364 1269 1712 1251 2210 1124 1738 975
	
		// elements after 6324 needs to be biggger than 6324 but also do not need to be in order
		//  e.g last elements -> 7952 8148 7981 9572 9812 7973 9595 9706 9677 7940 8725 9209 9649 8076
	}
*/

/*
	// partition algorithm
	// partition algorithms returns partition points.

	#include <algorithm>
	#include <vector>
	#include <random>
	
	int main()
	{
		using namespace std;
	
		mt19937 eng;
		uniform_int_distribution dist{ 0,200 };
	
		vector<int> ivec(50);
		generate(ivec.begin(), ivec.end(), [&]() {return dist(eng); });
	
		auto iter_pp = partition(ivec.begin(), ivec.end(), [](int a) {
			return a % 2 != 0;
			});
	
		for (auto i : ivec)
			cout << i << ' ';
		cout << '\n';
	
		if (iter_pp != ivec.end()) {
			cout << "partition point = " << *iter_pp << '\n';
		}
	
		// output ->
		// 163 27 187 167 25 7 183 131 127 61 19 109 55 37 109 199 101
		// 159 193 59 31 145 195 197 97 ____ 22 192 160 160 194 28 0 84 22
		// 184 128 200 176 192 192 44 160 194 72 170 42 182 136 136 80
		// partition point = 22
	
		// odd values range -> ivec.begin(), iter_pp
		// even values range -> iter_pp, ivec.end()
	}
*/

/*
	#include <algorithm>
	#include <vector>
	#include <random>
	
	int main()
	{
		using namespace std;
	
		mt19937 eng;
		uniform_int_distribution dist{ 0,200 };
	
		vector<int> ivec(100);
		generate(ivec.begin(), ivec.end(), [&]() {return dist(eng); });
	
		sort(ivec.begin(), ivec.end());
	
		auto iter_pp = partition(ivec.begin(), ivec.end(), [](int a) {
			return a >= 100;
			});
	
		for (auto i : ivec)
			cout << i << ' ';
		cout << '\n';
	
		if (iter_pp != ivec.end()) {
			cout << "partition point = " << *iter_pp << '\n';
		}
	
		// output ->
		// 200 199 199 197 195 194 194 193 192 192 192 190 187 185 184 183 182 176 175
		// 170 167 165 165 163 162 160 160 160 160 159 159 159 153 153 152 151 149 148
		// 145 142 141 139 136 136 133 131 131 101 109 109 127 128 129 ____
		// 98 98 98 97 95 92 89 88 84 84 82 80 78 76 72 63 63 61 60 59 55 55 44 42 42
		// 37 37 34 34 31 29 28 27 25 25 25 22 22 19 19 10 9 7 7 6 6 0
		// partition point = 98
	
		// because of partition is not stable before partition point, 
		// elements are not in order.
	
		sort(ivec.begin(), ivec.end());
	
		iter_pp = stable_partition(ivec.begin(), ivec.end(), [](int a) {
			return a >= 100;
			});
	
		for (auto i : ivec)
			cout << i << ' ';
		cout << '\n';
	
		if (iter_pp != ivec.end()) {
			cout << "partition point = " << *iter_pp << '\n';
		}
	
		// output ->
		// 101 109 109 127 128 129 131 131 133 136 136 139 141 142 145 148 149 151 152
		// 153 153 159 159 159 160 160 160 160 162 163 165 165 167 170 175 176 182 183
		// 184 185 187 190 192 192 192 193 194 194 195 197 199 199 200 ___
		// 0 6 6 7 7 9 10 19 19 22 22 25 25 25 27 28 29 31 34 34 37 37 42 42 44 55 55
		// 59 60 61 63 63 72 76 78 80 82 84 84 88 89 92 95 97 98 98 98
		// partition point = 0
	
		// because of stable_partition is stable, elements are in order.
	}
*/

/*
	#include <algorithm>
	#include <vector>
	#include <random>
	#include <deque>
	#include <list>
	
	int main()
	{
		using namespace std;
	
		mt19937 eng;
		uniform_int_distribution dist{ 0,200 };
	
		vector<int> ivec(100);
		generate(ivec.begin(), ivec.end(), [&]() {return dist(eng); });
	
		deque<int> x;
		list<int> y;
	
		auto [iter_x, iter_y] = partition_copy(ivec.begin(), ivec.end(), back_inserter(x), back_inserter(y), [](int a) {
			return a >= 100;
			});
	
		cout << "deque<int> x = \n";
		for (auto i : x)
			cout << i << ' ';
		cout << '\n';
	
		cout << "list<int> y = \n";
		for (auto i : y)
			cout << i << ' ';
		cout << '\n';
	
		// output ->
		//	deque<int> x =
		//	163 182 167 194 183 127 109 109 199 192 200 193 194 145 195 197 192 160 160
		//	184 128 159 176 192 101 131 160 170 187 136 136 152 148 149 131 141 160 175
		//	199 165 165 139 153 190 133 153 159 129 159 142 185 151 162
		//	list<int> y =
		//	27 25 44 61 19 55 37 31 22 97 59 28 0 84 22 7 72 42 80 95 78 84 34 34 60 6 63
		//	55 9 29 19 25 63 98 6 88 25 76 42 10 7 37 82 98 92 89 98
	
		// partition_copy returns std::pair<iterator, iterator>
	}
*/

/*
	#include <algorithm>
	
	int main()
	{
		using namespace std;
	
		int a[]{ 1, 4, 7, 9, 12, 56, 90, 124 };
		int b[]{ 45, 21, 12, 6, 5, 1 -4, -6 };
	
		cout << boolalpha;
		cout << is_sorted(begin(a), end(a)) << '\n';	// output -> true
		cout << is_sorted(begin(b), end(b)) << '\n';	// output -> false
		cout << is_sorted(begin(b), end(b), greater{}) << '\n';	// output -> true
	
		int c[]{ 3, 6, 9, 12, 5, 6, 90, 124 };
		auto iter = is_sorted_until(begin(c), end(c));
		cout << *iter << '\n';	// output -> 5
	}
*/

/*
	#include <vector>
	#include <algorithm>
	#include <random>
	
	int main()
	{
		using namespace std;
	
		vector<int> ivec(16);
	
		mt19937 eng;
		uniform_int_distribution dist{ 0,1000 };
		generate(ivec.begin(), ivec.end(), [&]() {return dist(eng); });
	
		for (auto i : ivec)
			cout << i << ' ';
		cout << '\n';
		// output -> 815 135 906 835 127 969 914 221 632 308 97 547 278 188 547 993
	
		make_heap(ivec.begin(), ivec.end());
		// making a container heap -> O(n)
	
		for (auto i : ivec)
			cout << i << ' ';
		cout << '\n';
		// output -> 993 835 969 815 308 906 914 221 632 127 97 547 278 188 547 135
	
		std::cout << "biggest element : " << ivec.front() << '\n';
		// output -> biggest element : 993
	
		pop_heap(ivec.begin(), ivec.end());
		// pop_heap takes the biggest element and put it in to the last place in heap -> O(log_n)
	
		cout << "last element : " << ivec.back() << '\n';
		// output -> last element : 993
	
		for (auto i : ivec)
			cout << i << ' ';
		cout << '\n';
		// output -> 969 835 914 815 308 906 547 221 632 127 97 547 278 188 135 993
	
		ivec.pop_back();
		// removing last element from vector.
	
		for (auto i : ivec)
			cout << i << ' ';
		cout << '\n';
		// output -> 969 835 914 815 308 906 547 221 632 127 97 547 278 188 135
	
		// vector is still in a heap structure.
	}
*/

/*
	max heap-> 993 835 969 815 308 906 914 221 632 127 97 547 278 188 547 135

										993
							835							969
					815				308			906				914
				221		632		127		97	547		278		188		547	
			135				
*/

/*
	#include <vector>
	#include <algorithm>
	#include <random>
	
	int main()
	{
		using namespace std;
	
		vector<int> ivec(16);
	
		mt19937 eng;
		uniform_int_distribution dist{ 0,1000 };
	
		generate(ivec.begin(), ivec.end(), [&]() {return dist(eng); });
		make_heap(ivec.begin(), ivec.end());
	
		for (auto i : ivec)
			cout << i << ' ';
		cout << '\n';
		// output -> 993 835 969 815 308 906 914 221 632 127 97 547 278 188 547 135
	
		ivec.push_back(2345);	// adding an element to tail of vector.
		push_heap(ivec.begin(), ivec.end());
		// when we run push_heap() function it will get the last element that added to vector
		// and fix the vector in heap structure.
	
		for (auto i : ivec)
			cout << i << ' ';
		cout << '\n';
		// output -> 2345 993 969 835 308 906 914 815 632 127 97 547 278 188 547 135 221
	}
*/

/*
	// in every run get the biggest element in vector and remove it.
	
	#include <vector>
	#include <algorithm>
	#include <random>
	
	int main()
	{
		using namespace std;
	
		vector<int> ivec(5);
	
		mt19937 eng;
		uniform_int_distribution dist{ 0,1000 };
	
		generate(ivec.begin(), ivec.end(), [&]() {return dist(eng); });
	
		make_heap(ivec.begin(), ivec.end());
	
		while (!ivec.empty()) {
			cout << ivec.front() << " will leave the container\n";
			pop_heap(ivec.begin(), ivec.end());
	
			for (auto i : ivec)
				cout << i << ' ';
			cout << '\n';
			ivec.pop_back();

			cout << "after remove operation : ";

			for (auto i : ivec)
				cout << i << ' ';
			cout << '\n';
		}
		
		// output ->
		//	906 will leave the container
		//	835 135 815 127 906
		//	after remove operation : 835 135 815 127
		//	835 will leave the container
		//	815 135 127 835
		//	after remove operation : 815 135 127
		//	815 will leave the container
		//	135 127 815
		//	after remove operation : 135 127
		//	135 will leave the container
		//	127 135
		//	after remove operation : 127
		//	127 will leave the container
		//	127
		//	after remove operation :
	}
*/

/*
	// in every run get the smallest element in vector and remove it.
	
	#include <vector>
	#include <algorithm>
	#include <random>
	
	int main()
	{
		using namespace std;
	
		vector<int> ivec(5);
	
		mt19937 eng;
		uniform_int_distribution dist{ 0,1000 };
	
		generate(ivec.begin(), ivec.end(), [&]() {return dist(eng); });
	
		make_heap(ivec.begin(), ivec.end(), greater{});	// min_heap
	
		while (!ivec.empty()) {
			cout << ivec.front() << " will leave the container\n";
			pop_heap(ivec.begin(), ivec.end(),  greater{});
	
			for (auto i : ivec)
				cout << i << ' ';
			cout << '\n';
			ivec.pop_back();
	
			cout << "after remove operation : ";
	
			for (auto i : ivec)
				cout << i << ' ';
			cout << '\n';
		}
	
		// output ->
		//	127 will leave the container
		//	135 815 906 835 127
		//	after remove operation : 135 815 906 835
		//	135 will leave the container
		//	815 835 906 135
		//	after remove operation : 815 835 906
		//	815 will leave the container
		//	835 906 815
		//	after remove operation : 835 906
		//	835 will leave the container
		//	906 835
		//	after remove operation : 906
		//	906 will leave the container
		//	906
		//	after remove operation :
	}
*/

/*
	// sort_heap algorithm O(nlogn)

	#include <vector>
	#include <algorithm>
	#include <random>
	#include <functional>
	#include <queue>
	
	int main()
	{
		using namespace std;
	
		vector<int> ivec(50);
	
		mt19937 eng;
		uniform_int_distribution dist{ 0,1000 };
	
		generate(ivec.begin(), ivec.end(), [&]() {return dist(eng); });
	
		make_heap(ivec.begin(), ivec.end());
		sort_heap(ivec.begin(), ivec.end());
	
		for (auto i : ivec)
			cout << i << ' ';
		cout << '\n';
	
		// output ->
		//  4 35 97 109 112 127 135 142 157 188 212 221 278 297 308 361 399 422
		//  485 504 547 547 632 640 656 679 682 726 792 798 798 801 815 835 849
		//	879 906 914 916 934 958 958 960 965 968 969 971 982 993 997
	
		make_heap(ivec.begin(), ivec.end(), greater{});
		sort_heap(ivec.begin(), ivec.end(),  greater{});
	
		for (auto i : ivec)
			cout << i << ' ';
		cout << '\n';
	
		// output ->
		//	997 993 982 971 969 968 965 960 958 958 934 916 914 906 879 849 835
		//  815 801 798 798 792 726 682 679 656 640 632 547 547 504 485 422 399
		//  361 308 297 278 221 212 188 157 142 135 127 112 109 97 35 4
	}
*/

/*
	#include <queue>
	
	int main()
	{
		using namespace std;
	
		priority_queue<int> x;
	
		for (int i = 0; i < 10; ++i) {
			x.push(rand());
		}
		while (!x.empty()) {
			cout << x.top() << '\n';
			x.pop();
		}
	
		// output ->
		//	29358
		//	26962
		//	26500
		//	24464
		//	19169
		//	18467
		//	15724
		//	11478
		//	6334
		//	41
	}
*/

/*
	-------------------------
	| iterator invalidation |
	-------------------------
*/

/*
	//	vector: if reallocation happens every iterator and references become invalid.
	
	#include <vector>
	
	int main()
	{
		using namespace std;
	
		vector<int> ivec{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	
		cout << "ivec.capacity() = " << ivec.capacity() << '\n';
		// output -> ivec.capacity() = 10
	
		auto iter = ivec.begin() + 5;
		int* p = &ivec[5];
	
		ivec.push_back(333);
		// we push_back() another element to vector when size equals capacity.
		// vector will reallocate new memory. Iterators and references will become invalid.
	
		cout << *iter << '\n';	// dereferencing iterator
		// run-time error
	
		cout << *p << '\n';		// dereferencing pointer
		// run-time error
	}
*/

/*
	// iterators and references after the insertion point will become invalid.
	
	#include <vector>
	
	int main()
	{
		using namespace std;
	
		vector<int> ivec{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	
		ivec.reserve(100);
	
		auto iter = ivec.begin() + 5;
		int* ptr = &ivec[4];
	
		cout << *iter << '\n';	// output -> 5
		cout << *ptr << '\n';	// output -> 4
	
		ivec.insert(ivec.begin(), 222);
		cout << *iter << '\n';	// run-time error
		cout << *ptr << '\n';	// run-time error
	}
*/

/*
	// iterators and references after the delete point will become invalid.
	
	#include <vector>
	
	int main()
	{
		using namespace std;
	
		vector<int> ivec{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	
		auto iter = ivec.begin() + 5;
		int* ptr = &ivec[4];
	
		cout << *iter << '\n';	// output -> 5
		cout << *ptr << '\n';	// output -> 4
	
		ivec.erase(ivec.begin() + 3);
	
		cout << *iter << '\n';	// run-time error
		cout << *ptr << '\n';	// run-time error
	}
*/

/*
	#include <string>
	#include <vector>
	
	// loop the elements in vector
	// if strings length is 5 remove
	// if strings length is 6, add 1 more.
	
	int main()
	{
		using namespace std;
	
		vector<string> svec{ "metin", "hasan", "mert", "necati", "remzi", "turhan", "ali", "veli", "selami" };
		// mert, necati, necati, turhan, turhan, ali, veli, selami, selami
	
		//	 RUN-TIME ERROR CODE BECAUSE OF ITERATOR INVALIDATION
		//	-------------------------------------------------------
		//	for (auto iter = svec.begin(); iter != svec.end(); ++iter) {
		//		if (iter->length() == 5) {
		//			svec.erase(iter);
		//			// when we erase an element, iterator will become invalid and
		//			// for continue loop we need to increase iterator (++iter).
		//			// undefined behaviour
		//		}
		//		else if (iter->length() == 6) {
		//			svec.insert(iter, *iter);
		//			// reallocation can be happen.
		//			// next iterators become invalid.
		//		}
		//	}
	
		// when we insert an element e.g "berk" to svec,
		// it will return an iterator to "berk" element which added to svec
	
		auto iter = svec.begin();
	
		while (iter != svec.end()) {
			if (iter->length() == 5) {
				iter = svec.erase(iter);
				// we will erase element in iter position.
				// when we erase an element it will return the next elements position.
				// iter = svec.erase(iter); -> iter will become the next element of the deleted element.
			}
			else if (iter->length() == 6) {
				iter = svec.insert(iter, *iter);
				// insert will return an iterator to inserted element
				// iter will become the position of the inserted element.
				advance(iter, 2);
				// because of iter will become new added element, its next element is the same element.
				// that will cause infinite loop. we need to increase iterators position by 2.
			}
			else {
				++iter;
			}
		}
	
		for (auto s : svec)
			cout << s << ' ';
		// output -> mert necati necati turhan turhan ali veli selami selami
	}
*/

/*
	---------------------------------------
	| deque(double ended queue) container | 
	--------------------------------------- 
*/

/*
	deque container contains different chunk blocks.
	When we reaching an element with an index operator,
	it takes a constant time.
	We first need to reach the chunk that holds the element of that index,
	then the position of the element in that chunk.

	e.g we have 10 chunk of int arrays and every array holds 10 integers.
	We can hold 100 total integers.
	If we want to reach 95th index,
	we first need to go the 10'th chunk then the 6th element in that chunk.

	Chunks are not contigious, for every chunk memory allocation need.

	In implementation all chunk addresses stored in pointer array.

	Its iterators are random_access iterator

	The most important difference from vector container is,
	push_front() is also a constant time like push_back().
	Different chunks have been used for push_front() and push_back() functions.

	deque container is an alternative to a vector container.
	deque<bool> holds bool, vector<bool> did not hold bool.

	deque have push_front(), pop_front(), emplace_front() functions.
	because of chunks are not contigious, deque does not have data() function
*/

/*
	deque : 
		->if the insertion operation is not in corners(first or last) position,
		all iterators and references will become invalid.
		-> if the insertion operation is in corners(first or last) position, 
		all iterators will become invalid but references are still valid.
	
		-> if remove operation is not in corners(first or last) position
		all iterators and references will become invalid.
		-> if the remove operation is in corners(first or last) position
		only iterators and references become invalid for deleted elements.
*/

/*
	#include <deque>
	#include <string>
	
	int main()
	{
		using namespace std;
	
		deque<string> x{ "hello", " world", "we", "are", "live", "from", "istanbul" };
	
		auto iter = x.begin() + 3;
		auto& r = x[3];
	
		cout << "*iter = " << *iter << '\n';	// output -> * iter = are
		cout << "r = " << r << '\n';			// output -> r = are
	
		//	x.insert(x.begin() + 1, "yes");
		//	// insertion from not corners.

		//	cout << "*iter = " << *iter << '\n';	// run-time error
		//	cout << "r = " << r << '\n';			// run-time error
	}
*/

/*
	#include <deque>
	#include <string>
	
	int main()
	{
		using namespace std;
	
		deque<string> x{ "hello", " world", "we", "are", "live", "from", "istanbul" };
	
		auto iter = x.begin() + 3;
		auto& r = x[3];
	
		cout << "*iter = " << *iter << '\n';	// output -> * iter = are
		cout << "r = " << r << '\n';			// output -> r = are
	
		x.push_front("izmir");
		// insertion to first index with push_front().
	
		cout << "r = " << r << '\n';			// output -> r = are
		cout << "*iter = " << *iter << '\n';	// run-time error
	}
*/

/*
	// if the remove operation is in corners(first or last) position
	// only iterators and references become invalid for deleted elements.

	#include <deque>
	#include <string>
	
	int main()
	{
		using namespace std;
	
		deque<string> x{ "hello", " world", "we", "are", "live", "from", "istanbul" };
	
		auto iter = x.begin() + 3;
		auto ptr = &x[3];
	
		cout << *iter << " " << *ptr << '\n';
	
		for (int i = 0; i < 3; ++i) {
			x.pop_front();
			x.pop_back();
			cout << *iter << " " << *ptr << '\n';
		}
	
		cout << *iter << " " << *ptr << '\n';
	
		// output ->
		//	are are
		//	are are	-> in loop
		//	are are	-> in loop
		//	are are	-> in loop
		//	are are
	}
*/

/*
	----------------------------------
	| std::list (doubly-linked list) |
	----------------------------------
*/

/*
	Advantages
	------------
	-> if we know the location that we will insert or delete, 
		this opetion will be in O(1) constant time.
	-> think about the elements in container which will get involved in swap operation 
		have large sizes(e.g 400byte). But if they are hold in nodes (list, forward_list), 
		we will swap pointers. Not objects itself.
		list, forward_list containers have reverse() member functions but vector did not.
		That is because pointers will be swapped in nodular containers.
	-> splice operations, we have two list containers. 
		We can get the node from one list and add to another list. 

	Disadvantages
	------------------
	-> Every insert operation will allocate dynamic memory in list. But in vector with reserve() function 
		we can omit the allocation cost. malloc operation->(object memory + overhead)
*/

/*
	#include <list>
	
	template <typename T, typename A = std::allocator<T>>
	class List {
	
	};
	
	int main()
	{
		using namespace std;
	
		list<int> x(10);
		// list containers iterator is bidirectional iterator
	
		// WE will see these functions.
		x.reverse();
		x.sort();
		x.unique();
		x.merge();
		x.remove();
		x.remove_if();
		x.splice();
	}
*/

/*
	#include <list>
	#include <functional>
	
	int main()
	{
		using namespace std;
	
		list<int> ilist{ 1, 15, 6, 2, 19, 86, 97, 32, 12, 28 };
	
		for (auto i : ilist)
			cout << i << ' ';
		cout << '\n';
		// output -> 1 15 6 2 19 86 97 32 12 28
	
		ilist.reverse();
		for (auto i : ilist)
			cout << i << ' ';
		cout << '\n';
		// output -> 28 12 32 97 86 19 2 6 15 1
	
	
		ilist.sort();	// default predicate is less{}
		for (auto i : ilist)
			cout << i << ' ';
		cout << '\n';
		// output -> 1 2 6 12 15 19 28 32 86 97
	
		ilist.sort(greater{});
		for (auto i : ilist)
			cout << i << ' ';
		cout << '\n';
		// output -> 97 86 32 28 19 15 12 6 2 1
	
		ilist.push_front(32);
		auto n = ilist.remove(32);
		for (auto i : ilist)
			cout << i << ' ';
		cout << '\n';
		cout << "how many 32 deleted: " << n << '\n';
		// output -> 97 86 28 19 15 12 6 2 1
		// output -> how many 32 deleted: 2
	
		ilist.remove_if([](int val) {return val % 2 == 0; });
		for (auto i : ilist)
			cout << i << ' ';
		cout << '\n';
		// output -> 97 19 15 1
	}
*/

/*
	#include <list>
	#include <functional>
	#include <random>
	
	void print(std::ostream& os,std::list<int>& s)
	{
	
		for (auto i : s)
			os << i << ' ';
		os << '\n';
	}
	
	int main()
	{
		using namespace std;
	
		list<int> x(10);
		list<int> y(10);
	
		mt19937 eng;
		uniform_int_distribution dist{ 0,1000 };
	
		generate(x.begin(), x.end(), [&]() {return dist(eng); });
		generate(y.begin(), y.end(), [&]() {return dist(eng); });
	
		x.sort();	// default pred less{}
		y.sort();	// default pred less{}
	
		cout << "x = ";
		print(cout, x);
		cout << "y = ";
		print(cout, y);
		// output ->
		//	x = 127 135 221 308 632 815 835 906 914 969
		//	y = 97 188 278 547 547 958 965 968 993 997
	
		x.merge(y);
	
		cout << "x.size() = " << x.size() << '\n';
		cout << "y.size() = " << y.size() << '\n';
		// output ->
		//	x.size() = 20
		//	y.size() = 0
	
		cout << "x = ";
		print(cout, x);
		cout << "y = ";
		print(cout, y);
		// output ->
		// x = 97 127 135 188 221 278 308 547 547 632 815 835 906 914 958 965 968 969 993 997
		// y =
		// still in less order after merge() operation
	
		list<int> k(10);
		list<int> l(10);
		generate(k.begin(), k.end(), [&]() {return dist(eng); });
		generate(l.begin(), l.end(), [&]() {return dist(eng); });
	
		k.sort(greater{});
		l.sort(greater{});
	
		cout << "k = ";
		print(cout, k);
		cout << "l = ";
		print(cout, l);
		// output ->
		//	k = 982 971 958 801 798 726 485 297 157 109
		//	l = 960 916 879 792 640 504 422 142 112 497
	
		l.merge(k, greater{});
	
		cout << "k.size() = " << k.size() << '\n';
		cout << "l.size() = " << l.size() << '\n';
		// output ->
		//	k.size() = 0
		//	l.size() = 20
	
		cout << "k = ";
		print(cout, k);
		cout << "l = ";
		print(cout, l);
		// output ->
		//	k =
		//	l = 982 971 960 958 916 879 801 798 792 726 640 504 485 422 297 157 142 112 109 4
	}
*/

/*
	#include <list>
	#include <string>
	#include <algorithm>
	
	void print(const auto& con)
	{
		for (auto elem : con)
			std::cout << elem << ' ';
		std::cout << '\n';
	}
	
	void refresh(auto& con_x, auto& con_y)
	{
		con_x = { 1, 2, 3, 4, 5 };
		con_y = { 6, 7, 8, 9, 10 };
	}
	
	int main()
	{
		using namespace std;
	
		list<int> x{ 1, 2, 3, 4, 5 };
		list<int> y{ 6, 7, 8, 9, 10 };
	
		x.splice(x.begin(), y);
		std::cout << "y.size() = " << y.size() << '\n';	// output -> y.size() = 0
		std::cout << "x.size() = " << x.size() << '\n';	// output -> x.size() = 10
		print(x);	// output -> 6 7 8 9 10 1 2 3 4 5
	
	
		refresh(x, y);
		x.splice(x.end(), y);
		std::cout << "y.size() = " << y.size() << '\n';	// output -> y.size() = 0
		std::cout << "x.size() = " << x.size() << '\n';	// output -> x.size() = 10
		print(x);	// output -> 1 2 3 4 5 6 7 8 9 10
	
	
		refresh(x, y);
		x.splice(prev(x.end()), y);
		std::cout << "y.size() = " << y.size() << '\n';	// output -> y.size() = 0
		std::cout << "x.size() = " << x.size() << '\n';	// output -> x.size() = 10
		print(x);	// output -> 1 2 3 4 6 7 8 9 10 5
	
	
		refresh(x, y);
		x.splice(next(x.begin(), 2), y, next(y.begin()));
		print(x);	// output -> 1 2 7 3 4 5
		print(y);	// output -> 6 8 9 10
	
		refresh(x, y);
		x.splice(next(x.begin()), y, y.begin(), next(y.begin(), 3));
		print(x);	// output -> 1 6 7 8 2 3 4 5
		print(y);	// output -> 9 10
	}
*/

/*
	#include <list>
	#include <functional>
	#include <random>
	#include <algorithm>
	
	void print(const auto& con)
	{
		for (auto elem : con)
			std::cout << elem << ' ';
		std::cout << '\n';
	}
	
	int main()
	{
		using namespace std;
	
		mt19937 eng;
		uniform_int_distribution dist{ 0, 1000 };
	
		list<int> x(100);
		generate(x.begin(), x.end(), [&]() {return dist(eng);});
	
		x.unique([](int x, int y) {return x % 2 == y % 2; });
		std::cout << "x.size() = " << x.size() << '\n';	// output -> x.size() = 50
		print(x);
		//	output -> 815 906 835 914 221 632 97 278 547 958 997 968 157 726 971
		//	982 109 798 801 142 879 960 35 212 679 758 741 392 171 302 31 316 277
		//	46 149 824 695 764 951 34 439 126 381 210 51 36 187 490 921 808
	
		x.erase(x.begin());
		x.resize(100);
		generate(x.begin(), x.end(), [&]() {return dist(eng); });
	
		auto deleted_item_count = x.unique([](int x, int y) {return x % 10 == y % 10; });
		std::cout << "x.size() = " << x.size() << '\n';						// output -> x.size() = 92
		std::cout << "deleted item count = " << deleted_item_count << '\n';	// output -> deleted item count = 8
		print(x);
		// output ->
		//	276 680 2 655 711 162 644 119 456 498 774 960 574 340 877 585 808 224 17 752
		//	255 821 506 941 699 413 891 423 960 581 547 158 762 149 230 257 810 841 989
		//	254 332 815 300 243 930 217 350 908 196 849 251 955 616 779 473 988 352 67 831
		//	794 585 550 733 918 695 286 680 757 392 754 562 380 208 527 75 404 353 531 593
		//	779 356 934 965 130 154 569 395 469 387 11 727 388
	}
*/

/*
	----------------------
	| forward_list class |
	----------------------
	-> its iterator is forward iterator.
	-> we can insert the next position of the node that we want to insert.

	forward_list ==>  12 -> 4 -> 43 -> 7
	We can not delete 43 directly if we have an iterator to node(43) 
	because we also need to change node(4)'s next pointers value after delete operation.
	So if we have node(4)'s iterator we can delete node(43) and change next pointer of node(4) to 7. 

	Because of forward_list class is a minimalist class there is only a pointer to the beginning of the list 
	in forward_list class. Because of there is no pointer at the end or a data member holding size.
	For calculating size() of the forward_list container we need to use O(n) algorithm.

	STL guarantees that size() function is O(1) that is why forward_list does not have size() member function.
*/

/*
	#include <forward_list>
	
	int main()
	{
		using namespace std;
	
		forward_list<int> x{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	
		cout << "size = " << distance(x.begin(), x.end()) << '\n';	// output -> size = 9
		// to get size we can use distance algorithm O(n)
	
		auto iter = x.end();
		//--iter; // syntax error -> not a bidirectional iterator, it is forward iterator.
	
		auto iter_2 = x.begin();
		++iter_2; // legal
		cout << *iter_2 << '\n';	// output -> 2
	
		advance(iter_2, 3);
		cout << *iter_2 << '\n';	// output -> 5
	}
*/

/*
	#include <forward_list>
	
	void print(const auto& con)
	{
		for (auto elem : con)
			std::cout << elem << ' ';
		std::cout << '\n';
	}
	
	int main()
	{
		using namespace std;
	
		forward_list<int> x{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	
		auto iter = next(x.begin());
		cout << "*iter = " << *iter << '\n';	// output -> *iter = 2
	
		x.insert_after(iter, -1);
		print(x);	// output -> 1 2 -1 3 4 5 6 7 8 9
		cout << "*iter = " << *iter << '\n';	// output -> *iter = 2
	
		x.erase_after(iter);
		print(x);	// output -> 1 2 3 4 5 6 7 8 9
	
		x.insert_after(iter, { 444, 555, 666 });
		print(x);	// output -> 1 2 444 555 666 3 4 5 6 7 8 9
		cout << "*iter = " << *iter << '\n';	// output -> *iter = 2
	
		x.erase_after(iter, next(iter, 4));
		print(x);	// output -> 1 2 3 4 5 6 7 8 9
	
		x.insert_after(x.begin(), {444, 555, 666});
		print(x);	// output -> 1 444 555 666 2 3 4 5 6 7 8 9
	
		x.erase_after(x.begin(), next(x.begin(), 4));
		print(x);	// output -> 1 2 3 4 5 6 7 8 9
	
		// USING before_begin()
		x.insert_after(x.before_begin(), { 444, 555, 666 });
		print(x);	// output -> 444 555 666 1 2 3 4 5 6 7 8 9
	
		x.erase_after(x.before_begin(), next(x.begin(), 3));
		print(x);	// output -> 1 2 3 4 5 6 7 8 9
	}
*/

/*
	#include <forward_list>
	#include <random>
	
	template<typename T>
	int randint(std::mt19937& eng, T& t)
	{
		return t(eng);
	}
	
	int main()
	{
		std::forward_list<int> x;
	
		for (int i = 0; i < 100; ++i)
			x.push_front(++i);
	
		for (const auto& s : x)
			std::cout << s << ' ';
		std::cout << '\n';
	
		// output -> 99 97 95 93 91 89 87 85 83 81 79 77 75 73 71 69 67
		// 65 63 61 59 57 55 53 51 49 47 45 43 41 39 37 35 33 31 29 27
		// 25 23 21 19 17 15 13 11 9 7 5 3 1
	
		int want_to_delete_int = 59;
		// We need to find the location of 61 to delete 59.
	
		auto iter = x.before_begin();
	
		while (next(iter) != x.end()) {
			if (*next(iter) == want_to_delete_int) {
				x.erase_after(iter);
				break;
			}
			++iter;
		}
	
		for (const auto& s : x)
			std::cout << s << ' ';
	
		// output -> 99 97 95 93 91 89 87 85 83 81 79 77 75 73 71 69 67
		// 65 63 61 57 55 53 51 49 47 45 43 41 39 37 35 33 31 29 27
		// 25 23 21 19 17 15 13 11 9 7 5 3 1
	}
*/

/*
	----------------------
	| std::set container |
	----------------------
*/

/*
	template <typename Key, typename Comp = less<Key>, typename A = allocator<Key>>
	class Set{

	};
*/

/*
	#include <set>
	#include "nutility.h"
	
	int main()
	{
		using namespace std;
	
		set<int> myset;
		set<int, less<int>> myset_2;
		// Those 2 lines are same.
	
		rfill(myset, 20, Irand{0,30});
	
		for (const auto& s : myset)
			cout << s << " ";
		// output -> 0 1 3 4 5 6 8 9 13 15 16 19 20 22 24 25 27 28 29 30
	}
*/

/*
	#include <set>
	#include <cmath>
	#include "nutility.h"
	
	// comparator type is functor class
	struct Comp {
		bool operator()(int x, int y)const
		{
			return std::abs(x) < std::abs(y);
		}
	};
	
	int main()
	{
		using namespace std;
	
		// comparator equality will be values absolutes equality
	
		set<int, Comp> myset;
	
		rfill(myset, 20, Irand{ -100, 100 });
		for (const auto& s : myset)
			cout << s << " ";
		// output -> 9 27 -39 -45 -56 63 67 -69 -73 -75 -81 82 83 92 93 94 95 97 99 100
	}
*/

/*
	#include <set>
	#include <cmath>
	#include "nutility.h"
	
	// comparator type is a global function
	bool fcmp(int x, int y)
	{
		return std::abs(x) < std::abs(y);
	}
	
	int main()
	{
		using namespace std;
	
		set<int, bool(*)(int,int)> myset(fcmp);
		set<int, decltype(&fcmp)> myset_2(fcmp);
		// we need to send the address of the function to constructor as a parameter.
		// Those 2 lines acts same.
	
		rfill(myset, 20, Irand{ -100, 100 });
		for (const auto& s : myset)
			cout << s << " ";
		// output -> 9 27 -39 -45 -56 63 67 -69 -73 -75 -81 82 83 92 93 94 95 97 99 100
	}
*/

/*
	#include <set>
	#include <cmath>
	#include "nutility.h"
	
	int main()
	{
		using namespace std;
	
		auto f = [](int x, int y)
		{
			return std::abs(x) < std::abs(y);
		};
	
		set<int, decltype(f)> myset;		// before C++20 ERROR
		set<int, decltype(f)> myset_2(f);	// before C++20 OK
		// when myset's(set<int, decltype(f)>) constructor called,
		// it needs to default construct a compiler generated lambda class.
		// But before C++20 compiler generated lambda classes does not have a default ctor.
	
		rfill(myset, 20, Irand{ -100, 100 });
		for (const auto& s : myset)
			cout << s << " ";
		// output -> 9 27 -39 -45 -56 63 67 -69 -73 -75 -81 82 83 92 93 94 95 97 99 100
	}
*/

/*
	#include <set>
	#include <string>
	#include "nutility.h"
	
	int main()
	{
		using namespace std;
	
		auto fcmp = spred();
	
		set<string, decltype(fcmp)> myset(fcmp);
	
		for (int i = 0; i < 15; ++i) {
			myset.insert(rname() + ' ' + rfname());
		}
		print(myset, "\n");
		// output ->
		//	demir yosun
		//	soner beyaz
		//	taci cuhadar
		//	kasim belgeli
		//	sadri muglali
		//	dilek orhancan
		//	galip tufancan
		//	halime corbaci
		//	irmak dokuzcan
		//	kayahan bilgic
		//	kerem tekkilic
		//	hulki yanardoner
		//	nasrullah kalpten
		//	yurdagul engereke
		//	nasrullah baturalp
	}
*/

/*
	-> COMPARATOR needs to be
	1. anti-simetric 
		if (x op y) == true,  (y op x) == false
	2. irreflexive
		x < x == false
	3. transitive
		if (a < b == true) and if (b < c == true),  (a < c also needs to be true.
	4. transitivity equivalance
		if !(a < b) && !(b < a) == true, b needs to be equal to a 
		if !(b < c) && !(c < b) == true, b needs to be equal to c
		!(a < c) && !(c < a) also needs to be true and a is equal to c
*/

/*
	Q. Why do we need to have multiple same key in a container(multiset, multimap)?
	-------------
	A. Think about a game that stores people and we are using names of people
	as a key. We can store lots of people with same name(key) in container.
*/

/*
	#include <string>
	#include <set>
	
	int main()
	{
		using namespace std;
	
		set<string> myset{ "hello", "we", "are", "hello", "live", "hello" };
		multiset<string> mymultiset{ "hello", "we", "are", "hello", "live", "hello" };
	
		std::cout << "myset.size() = " << myset.size() << '\n';
		// output -> myset.size() = 4
	
		for (const auto& s : myset)
			cout << s << ' ';
		cout << '\n';
		// output -> are hello live we
	
		std::cout << "mymultiset.size() = " << mymultiset.size() << '\n';
		// output -> mymultiset.size() = 6
	}
*/

/*
	differences between global find() function and set containers find() function
	1. Complexity difference -> 
		global find function			O(n)
		set container find function		O(log(n))
	2. Global find's equality and set containers equivalance result does not need to be same. 
		-> global find will understand the value that has been search like (*iter == value)
		-> set's find function using comparator to understand it is the value it has been searched
		(-15) can be equal to (15) with using a comparator.
*/

/*
	#include <set>
	#include <algorithm>	// std::find
	#include <iterator>		// std::distance
	#include "nutility.h"
	
	int main()
	{
		using namespace std;
	
		set<string> myset;
	
		rfill(myset, 30, rname);
		print(myset," ", cout);
		// output ->
		//	alev atil baran beril cansu cem cemil ciler emrecan engin ferhat fikret furkan hande jade kazim
		//	leyla mahir malik mehmet mukerrem muslum necati olcay osman sade sami temel tijen zarife
	
		string key;
		std::cout << "write a name: ";
		std::cin >> key;
	
		if (auto iter = myset.find(key); iter != myset.end())
		{
			cout << "found " << *iter << '\n';
			cout << "index = " << distance(myset.begin(), iter) << '\n';
		}
		else
			cout << "is not found\n";
		// output ->
		//	write a name : cansu
		//	found cansu
		//	index = 4
	}
*/

/*
	#include <set>
	#include "nutility.h"
	
	int main()
	{
		using namespace std;
	
		set<string> myset;
	
		rfill(myset, 10, rname);
		print(myset, " ", cout);
		// output ->
		//	adem afacan aycan azize bilgin devlet necmettin nihat pakize yalcin
	
		string key;
		std::cout << "write a name: ";
		std::cin >> key;
	
		// before C++20 [count()]
		if (myset.count(key))
			cout << "count -> found : " << key << '\n';
		else
			cout << "not found" << '\n';
	
		// after C++20 [contains()]
		if (myset.contains(key))
			cout << "contains -> found : " << key << '\n';
		else
			cout << "not found" << '\n';
	
		// output ->
		//	write a name : necmettin
		//	count->found : necmettin
		//	contains->found : necmettin
	}
*/

/*
	#include <set>
	#include <iterator>		// std::next
	#include "nutility.h"
	
	int main()
	{
		using namespace std;
	
		set<string> myset;
		rfill(myset, 10, rname);
	
		auto iter = next(myset.begin(), 5);
		*iter = "hello";	// syntax error
		// *iter returns const string& (const T&)
	
		const_cast<string&>(*iter) = "world";
		// legal but Undefined Behaviour because data corruption can occur.
	
		// set holds its members as binary search tree.
		// 1 2 3 4 5 * 6 7 8 9
		// We are trying to add 28 to * -> Undefined Behaviour, binary search tree has been corrupted.
	}
*/

/*
	#include <set>
	#include <utility>
	#include <iterator>
	#include "nutility.h"
	
	int main()
	{
		using namespace std;
		set<int> myset{ 11, 22, 33, 44, 55, 66, 77, 88, 99 };
	
	
		pair<set<int>::iterator,bool> retval = myset.insert(23);
		if (retval.second)
		{
			cout << "retval add\n";
			cout << "value has been added: " << *retval.first << '\n';
			cout << "index of added value: " << distance(myset.begin(), retval.first) << '\n';
		}
		else
			cout << "retval not add\n";
	
		print(myset);
		// output ->
		//	retval add
		//	value has been added : 23
		//	index of added value : 3
		//  11 22 23 33 44 55 66 77 88 99
	
		auto retval_2 = myset.insert(44);
		if (retval_2.second)
			cout << "retval_2 add\n";
		else
		{
			cout << "retval_2 can not be added\n";
			cout << "value already exist: " << *retval_2.first << "\n";
			cout << "index of the value that already exists: " << distance(myset.begin(), retval_2.first) << '\n';
		}
		print(myset);
		// output ->
		//	retval_2 can not be added
		//	value already exist : 44
		//	index of the value that already exists : 4
		//	11 22 23 33 44 55 66 77 88 99
	
	
		if (myset.insert(87).second)
			cout << "value added\n";
		// controlling if the insertion is done.
		print(myset);
		// output ->
		//	value added
		//	11 22 23 33 44 55 66 77 87 88 99
	
	
		auto [iter, is_inserted] = myset.insert(12);	// structured binding
	
		if (is_inserted) {
			cout << "value added\n";
			cout << "inserted values index : " << distance(myset.begin(), iter) << '\n';
		}
		print(myset);
		// output ->
		//	value added
		//	inserted values index : 1
		//	11 12 22 23 33 44 55 66 77 87 88 99
	}
*/

/*
	#include <string>
	
	struct Person {
		std::string m_name{ "hello" };
		std::string m_surname{ "world" };
		int m_no = 346283;
	};
	
	Person foo()
	{
		Person per_1;
		per_1.m_name += "lalala";
		return per_1;
	}
	
	int main()
	{
		auto [name, surname, no] = foo();
	
		// auto compiler_gen_object = foo();
		// std::string name = compiler_gen_object.m_name;
		// std::string surname = compiler_gen_object.m_surname;
		// int no = compiler_gen_object.m_no;
	
		std::cout << "name = " << name << '\n';
		std::cout << "surname = " << surname << '\n';
		std::cout << "no = " << no << '\n';
	}
*/

/*
	multiset's insert() function returns an iterator.
	Because every object that multiset holds to can be inserted. 
	multiset container does not have unique keys.
*/

/*
	#include <set>
	#include "nutility.h"
	
	int main()
	{
		using namespace std;
	
		set<pair<int, double>> myset;
	
		myset.insert(make_pair(3, 5.2));
		myset.emplace(5, 4.2);	// sending (5, 4.2) directly to pair's constructor.
	
		print(myset);	// output -> [3, 5.2] [5, 4.2]
	}
*/

/*
	#include <set>
	
	int main()
	{
		using namespace std;
	
		set<int> myset{ 3, 6, 9, 12, 78, 90, 234 };
	
		myset.insert(myset.begin(), 5);			// hint insert overload function
		myset.emplace_hint(myset.begin(), 7);	// hint emplace overload.
	
		// if the value that we want to insert; is near, to the place that the value is actually will be inserted.
		// hint insert overload will decrease the cost.
	}
*/

/*
	#include <set>
	#include "nutility.h"
	
	int main()
	{
		using namespace std;
	
		set<int> myset{ 3, 6, 9, 12, 78, 90, 234 };
		print(myset);	// output -> 3 6 9 12 78 90 234
	
		myset.erase(myset.begin());
		print(myset);	// output -> 6 9 12 78 90 234
	
		myset.erase(next(myset.begin(),3));
		print(myset);	// output -> 6 9 12 90 234
	}
*/

/*
	#include <set>
	#include "nutility.h"
	
	int main()
	{
		using namespace std;
	
		set<int> myset{ 3, 6, 9, 12, 78, 90, 234 };
		print(myset);	// output -> 3 6 9 12 78 90 234
	
		auto beg = myset.find(9);
		auto end = myset.find(90);
	
		myset.erase(beg, end);	//	[9, 90) range-erase
		print(myset);	// output -> 3 6 90 234
	}
*/

/*
	#include <set>
	#include <string>
	#include "nutility.h"
	
	int main()
	{
		using namespace std;
	
		set<string> myset{ "hello", "world", "we", "are", "live", "from", "izmir"};
		print(myset);
		// output -> are from hello izmir live we world
	
		auto n = myset.erase("live");	// n's type is bool
		print(myset);
		// output -> are from hello izmir we world
		std::cout << n << '\n';	// output -> 1
	
		multiset<int> my_multiset{ 1, 1, 5, 4, 7, 8, 5, 23, 6, 7, 5, 4 };
		print(my_multiset);
		// output -> 1 1 4 4 5 5 5 6 7 7 8 23
	
		auto k = my_multiset.erase(5);
		print(my_multiset);
		// output -> 1 1 4 4 6 7 7 8 23
		std::cout << k << '\n';	// output -> 3
	}
*/

/*
	#include <set>
	#include <functional>	// std::greater
	
	template <typename Key>
	using gset = std::set<Key, std::greater<Key>>
	
	// using Alias template for not writing std::greater every time
	// that we create a set using std::greater<>
	
	// gset<int> -> set<int,std::greater<int>>
*/

/*
	lower bound(key)	-> First equal or first bigger value than the Key's location
	-----------------
	2 4 4 4 5 8 9 
	  *	lower bound(4)

	2 4 4 4 5 8 9 
			  * lower bound(7)
	 
	upper bound(key) -> first location that is bigger than the Key value.
	-----------------
	2 4 4 4 5 8 9
	        * upper bound(4)
	
	2 4 4 4 5 8 9 
			  * upper bound(7)
	
	<------------------------------------------------->

	2 4 4 4 5 8 9 -> Key = 4
	  L     U		

	difference between distance(lowerbound, upperbound) 
	will give us how many Key values that we have in container.

	equal range(key)	-> [lower_bound, upper_bound]
*/

/*
	#include <set>
	#include <algorithm>	// std::lower_bound, std::upper_bound, std::equal_range
	
	int main()
	{
		using namespace std;
		multiset<int> my_multiset{ 2, 5, 7, 7, 7, 7, 9, 9, 9, 13, 13, 45, 89 };
	
		// -------------> FOR KEY = 7
		auto iter_lower = my_multiset.lower_bound(7);
		cout << "index of lower bound = " << distance(my_multiset.begin(), iter_lower) << '\n';
		// output -> index of lower bound = 2
	
		auto iter_upper = my_multiset.upper_bound(7);
		cout << "index of upper bound = " << distance(my_multiset.begin(), iter_upper) << '\n';
		// output -> index of upper bound = 6
	
		cout << "distance for equal range = " << distance(iter_lower, iter_upper) << '\n';
		// output -> distance for equal range = 4
		// There are 4 Key values(Key = 7) in multiset.
	
		// -------------> FOR KEY = 6
		auto iter_lower_2 = my_multiset.lower_bound(6);
		cout << "index of lower bound = " << distance(my_multiset.begin(), iter_lower_2) << '\n';
		// output -> index of lower bound = 2
	
		auto iter_upper_2 = my_multiset.upper_bound(6);
		cout << "index of upper bound = " << distance(my_multiset.begin(), iter_upper_2) << '\n';
		// output -> index of upper bound = 2
	
		cout << "distance for equal range = " << distance(iter_lower_2, iter_upper_2) << '\n';
		// output -> distance for equal range = 0
		// There are 0 Key values(Key = 6) in multiset.
	}
*/

/*
	#include <vector>
	#include <algorithm>	// std::lower_bound , std::upper_bound
	#include <functional>
	
	int main()
	{
		using namespace std;
	
		std::vector ivec{ 3, 7, 8, 11, 34, 56, 78, 90 };
	
		cout << lower_bound(ivec.begin(), ivec.end(), 11) - ivec.begin() << '\n';	// output -> 3
		cout << upper_bound(ivec.begin(), ivec.end(), 11) - ivec.begin() << '\n';	// output -> 4
	
		// because of vectors iterator is random_access_iterator we can do substraction with iterators.
	}
*/

/*
	// How to add values to vector when the values order will still be sorted?

	#include <vector>
	#include <string>
	#include <algorithm>
	#include "nutility.h"
	
	int main()
	{
		using namespace std;
	
		vector<string> svec;
	
		for (int i = 0; i < 5; ++i)
		{
			auto name = get_random_name();
			auto iter_lower = lower_bound(svec.begin(), svec.end(), name);
			svec.insert(iter_lower, name);
			print(svec, "\n");
		}
	
		// output ->
		//	rupen alemdar
		//	---------------------------------------------------------------------------- -
		//	melih uluocak
		//	rupen alemdar
		//	---------------------------------------------------------------------------- -
		//	melih uluocak
		//	rupen alemdar
		//	tuncer yosun
		//	---------------------------------------------------------------------------- -
		//	bekir malkaciran
		//	melih uluocak
		//	rupen alemdar
		//	tuncer yosun
		//	---------------------------------------------------------------------------- -
		//	bekir malkaciran
		//	lale akyildiz
		//	melih uluocak
		//	rupen alemdar
		//	tuncer yosun
	}
*/

/*
	#include <vector>
	#include <string>
	#include <algorithm>
	#include <utility>
	#include "nutility.h"
	
	int main()
	{
		using namespace std;
	
		vector<string> svec;
		rfill(svec, 1000, rtown);
		sort(svec.begin(), svec.end());
		// print(svec);
	
		string town = "ankara";
	
		// pair<vector<string>::iterator, vector<string>::iterator> ip = equal_range(svec.begin(), svec.end(), town);
		// auto ip = equal_range(svec.begin(), svec.end(), town);
		auto [iter_lower, iter_upper] = equal_range(svec.begin(), svec.end(), town);
	
		std::cout << "how many " << town << " = " << distance(iter_lower, iter_upper) << '\n';
	
		std::cout << "first index : " << distance(svec.begin(), iter_lower)
			<< " last index: " << distance(svec.begin(), iter_upper) << '\n';
	}
*/

/*
	#include <vector>
	#include <string>
	#include <algorithm>
	#include "nutility.h"
	
	int main()
	{
		using namespace std;
	
		vector<string> svec;
	
		auto fcomp = spred();
	
		for (int i = 0; i < 10; ++i)
		{
			auto name = get_random_name();
			auto iter_lower = lower_bound(svec.begin(), svec.end(), name, fcomp);
			svec.insert(iter_lower, name);
		}
		print(svec, "\n");
		// output ->
		//	mert derin
		//	suphi yavas
		//	dilek ordulu
		//	poyraz zalim
		//	zekai akarsu
		//	tansel gurkas
		//	figen karabatur
		//	kerim yasayavas
		//	poyraz altindag
		//	ceylan altinisik
	}
*/

/*
	#include <set>
	#include <string>
	#include "nutility.h"
	
	int main()
	{
		using namespace std;
	
		set<string> myset{ "hello", "world", "we", "are", "live", "from", "izmir" };
	
		print(myset);
		// output -> are from hello izmir live we world
	
		string old_key{ "world" };
		string new_key{ "galaxy" };
	
		// in this approach.
		// when we use erase() function we are calling destructor of the object itself and deleting the node.
		// than in insert() function we create a new node and construct another string object.
		if (auto iter = myset.find(old_key); iter != myset.end()) {
			myset.erase(iter);
			myset.insert(new_key);
		}
		print(myset);
		// output -> are from galaxy hello izmir live we
	
		string old_key_2{ "hello" };
		string new_key_2{ "bye" };
	
		// better approach is
		// extracting the node and change the string object in that node(do not call its destructor)
		// also do not construct another string object and another node.
		// when we extract the node set's size will decrease by 1.
		if (auto iter = myset.find(old_key_2); iter != myset.end()) {
			auto handle = myset.extract(iter);
			handle.value() = new_key_2;
			myset.insert(std::move(handle));
		}
	
		print(myset);
		// output -> are bye from galaxy izmir live we
	}
*/

/*
	---------------------------
	| std::map, std::multimap |
	---------------------------
*/

/*
	template <typename Key, typename T, typename Comparator = std::less<Key>, 
					std::allocator<std::pair<const Key, T>>
	class Map{

	};
*/

/*
	#include <map>
	#include <string>
	
	int main()
	{
		using namespace std;
	
		map<string, int> m{
			{"hello", 1},
			{"world", 2},
			{"we", 3},
			{"are", 4},
			{"live", 5},
			{"from", 6},
			{"izmir", 7},
		};
	
		for (const auto& p : m) {
			cout << p.first << " " << p.second << '\n';
		}
		// output ->
		//	are 4
		//	from 6
		//	hello 1
		//	izmir 7
		//	live 5
		//	we 3
		//	world 2
	
		// O(log n) reaching an element
	}
*/

/*
	#include <map>
	#include <string>
	
	int main()
	{
		using namespace std;
	
		map<string, int> m{
			{"hello", 1},
			{"world", 1},
			{"we", 1},
			{"are", 1},
			{"live", 1},
			{"from", 1},
			{"izmir", 1},
		};
	
		for (const auto& p : m) {
			cout << p.first << " " << p.second << '\n';
		}
		// output ->
		//	are 1
		//	from 1
		//	hello 1
		//	izmir 1
		//	live 1
		//	we 1
		//	world 1
	
		// values of different Keys can be same. (are -> 1, from -> 1)
	}
*/

/*
	#include <map>
	#include <string>
	#include <functional>
	
	int main()
	{
		using namespace std;
	
		map<string, int, greater<string>> m{
			{"hello", 1},
			{"world", 2},
			{"we", 3},
			{"are", 4},
			{"live", 5},
			{"from", 6},
			{"izmir", 7},
		};
	
		// using greater<string>
	
		for (const auto& p : m) {
			cout << p.first << " " << p.second << '\n';
		}
		// output ->
		//	world 2
		//	we 3
		//	live 5
		//	izmir 7
		//	hello 1
		//	from 6
		//	are 4
	}
*/

/*
	#include <map>
	#include <string>
	#include <functional>
	
	int main()
	{
		using namespace std;
	
		map<string, int, greater<string>> m{
			{"hello", 1},
			{"world", 2},
			{"we", 3},
			{"are", 4},
			{"live", 5},
			{"from", 6},
			{"izmir", 7},
		};
	
		// using structured binding
		for (const auto&[name, number] : m) {
			cout << name << " " << number << '\n';
		}
		// output ->
		//	world 2
		//	we 3
		//	live 5
		//	izmir 7
		//	hello 1
		//	from 6
		//	are 4
	}
*/

/*
	#include <map>
	#include <string>
	#include <functional>
	
	int main()
	{
		using namespace std;
	
		map<string, int> m{
			{"hello", 1},
			{"world", 2},
			{"we", 3},
			{"are", 4},
			{"live", 5},
			{"from", 6},
			{"izmir", 7},
		};
	
		m.insert(pair<string, int>{"yes", 8});
		// using temp object to insert a pair to map.
	
		m.insert(pair{ "no",9 });
		// CTAD for pair class template
	
		m.insert(make_pair("space",10));
		// using make_pair() function to insert a pair to map
	
		m.emplace("galaxy", 11);
		// using emplace() function to call pair's constructor directly.
	
	
		for (const auto& [name, number] : m) {
			cout << name << " " << number << '\n';
		}
		// output ->
		//	are 4
		//	from 6
		//	galaxy 11
		//	hello 1
		//	izmir 7
		//	live 5
		//	no 9
		//	space 10
		//	we 3
		//	world 2
		//	yes 8
	}
*/

/*
	#include <map>
	#include <string>
	#include "nutility.h"
	
	int main()
	{
		using namespace std;
	
		map<string, int> mymap;
	
		for (size_t i = 0; i < 1000; ++i){
			mymap.emplace(rname(), Irand{ 1000,9000}());
		}
		std::cout << "mymap.size() = " << mymap.size() << '\n';
		// output -> mymap.size() = 318
		// same key can not be added to map container because it only stores unique keys.
	
		multimap<string, int> my_multimap;
	
		for (size_t i = 0; i < 1000; ++i) {
			my_multimap.emplace(rname(), Irand{ 1000,9000 }());
		}
		std::cout << "my_multimap.size() = " << my_multimap.size() << '\n';
		// output -> my_multimap.size() = 1000
		// same key can be added to multimap container. Keys does not have to be unique.
	}
*/

/*
	#include <map>
	#include <string>
	#include "nutility.h"

	int main()
	{
		using namespace std;

		map<string, int> mymap;

		for (size_t i = 0; i < 10; ++i) {
			mymap.emplace(rname(), Irand{ 1000,9000 }());
		}

		string key_1 = "galaxy";
		string key_2 = "izmir";
		int number = 15;

		if (auto [iter, inserted] = mymap.insert({ key_1, number }); inserted)
			cout << "item added " << iter->first << '\n';
		// output -> item added galaxy

		if (auto [iter, inserted] = mymap.insert({ key_2, number }); inserted)
			cout << "item added " << iter->first << '\n';
		// output -> item added galaxy

		// ------> trying to add key_2 again
		if (auto [iter, inserted] = mymap.insert({ key_2, number }); inserted)
			cout << "item added " << iter->first << '\n';
		else
			cout << "item has already in map and its number is " << iter->second << '\n';
		// output -> item has already in map and its number is 15

		for (const auto& p : mymap) {
			cout << p << '\n';
		}
		// output ->
		//	[atalay, 5679]
		//	[billur, 2340]
		//	[busra, 7340]
		//	[ciler, 8921]
		//	[galaxy, 15]
		//	[izmir, 15]
		//	[nagehan, 3891]
		//	[nuri, 1398]
		//	[sade, 8151]
		//	[sadiye, 7547]
		//	[tarik, 2871]
		//	[zubeyde, 3496]
	}
*/

/*
	#include <map>
	#include <string>
	#include "nutility.h"

	int main()
	{
		using namespace std;

		map<string, int> mymap{
			{"hello", 1},
			{"izmir", 2},
			{"world",3},
		};

		mymap.operator[]("izmir") = 111;
		mymap["world"] = 555;
		// These 2 are same lines
		// we are changing the value of the pair inside map container has a key "izmir" and "world"

		print(mymap, "\n");
		// output ->
		//	[hello, 1]
		//	[izmir, 111]
		//	[world, 555]


		mymap["galaxy"] = 666;
		// if the key that we use in operator[key]() function is not stored in map container
		
		// STEP_1 -> m.insert(pair{"galaxy", int{}})
		// STEP_2 -> add the value to pair.second = 666
		print(mymap, "\n");
		// output ->
		//	[galaxy, 666]
		//	[hello, 1]
		//	[izmir, 111]
		//	[world, 555]


		mymap["Pyramid"];
		print(mymap, "\n");
		// output ->
		//	[Pyramid, 0]
		//	[galaxy, 666]
		//	[hello, 1]
		//	[izmir, 111]
		//	[world, 555]


		mymap["forest"] += 99;
		// because of value initialize in STEP_1, value = 0
		// then it will add 99 to 0.
		// It will not be an Undefined Behaviour (NO UB)
		print(mymap, "\n");
		// output ->
		//	[forest, 99]
		//	[galaxy, 666]
		//	[hello, 1]
		//	[izmir, 111]
		//	[world, 555]
	}
*/

/*
	#include <vector>
	#include <map>
	#include "nutility.h"
	
	int main()
	{
		using namespace std;
	
		vector<int> ivec;
		rfill(ivec, 10000, Irand{ 1,20 });
	
		map<int, int> count_map;
	
		for (const auto& key : ivec) {
			++count_map[key];
			// if there is no a key in map(first the map is empty), it will create pair{key, int{}}
			// value initialize the value and increase 1(prefix increment).
			// if the same key will come again it will increase its values count.
		}
	
		print(count_map, "\n");
		// output ->
		//	[1, 494]
		//	[2, 503]
		//	[3, 454]
		//	[4, 509]
		//	[5, 492]
		//	[6, 515]
		//	[7, 531]
		//	[8, 511]
		//	[9, 536]
		//	[10, 529]
		//	[11, 517]
		//	[12, 506]
		//	[13, 496]
		//	[14, 507]
		//	[15, 506]
		//	[16, 470]
		//	[17, 476]
		//	[18, 460]
		//	[19, 479]
		//	[20, 509]
	}
*/

/*
	#include <vector>
	#include <map>
	#include <algorithm>
	#include "nutility.h"
	
	int main()
	{
		using namespace std;
	
		vector<int> ivec;
		rfill(ivec, 10000, Irand{ 1, 10 });
	
		map<int, int> count_map;
	
		for (const auto& item : ivec) {
			++count_map[item];
		}
	
		// we want an order where the values are decreasing not the order of .
		vector<pair<int, int>> sort_vec{ count_map.begin(), count_map.end() };
		sort(sort_vec.begin(), sort_vec.end(), [](const auto& p1, const auto& p2) {
			return p1.second > p2.second;
			});

		print(sort_vec, "\n");
		// output ->
		//	[1, 1068]
		//	[6, 1027]
		//	[3, 1023]
		//	[8, 998]
		//	[9, 996]
		//	[4, 995]
		//	[2, 985]
		//	[5, 977]
		//	[7, 973]
		//	[10, 958]
	}
*/

/*
	operator[]() function is only available for map container.
	The purpose of this function is; 
	if there is no key create it, if there was change its value.
	But in multimap because of keys are not unique 
	it would act like insert() function that is why
	for multimap container there is no operator[]()
*/

/*
	#include <map>
	#include <string>
	#include <exception>
	#include "nutility.h"
	
	int main()
	{
		using namespace std;
	
		map<int, string> mymap;
	
		for (size_t i = 0; i < 10; ++i) {
			mymap.emplace(Irand{ 1, 20 }(), rtown());
		}
		print(mymap, "\n");
		// output ->
		//	[4, sivas]
		//	[6, burdur]
		//	[7, aksaray]
		//	[8, bursa]
		//	[9, erzurum]
		//	[11, mardin]
		//	[19, corum]
	
	
		// RUN SEVERAL TIMES TO SEE BOTH RESULTS..
		try
		{
			mymap.at(17) = "istanbul";
			cout << "value at key 17 has been changed\n";
			// if there is a key it will change its value.
			// if there is not a key in container it will throw exception.
		}
		catch (const std::out_of_range& ex)
		{
			cout << "there is no key(17)\n";
			cout << "exception caught: " << ex.what() << '\n';
		}
		// output ->
		//	there is no key(17)
		//	exception thrown : invalid map<K, T> key
	
		print(mymap, "\n");
		// output ->
		//	[4, sivas]
		//	[6, burdur]
		//	[7, aksaray]
		//	[8, bursa]
		//	[9, erzurum]
		//	[11, mardin]
		//	[19, corum]
	}
*/

/*
	#include <map>
	#include <string>
	#include "nutility.h"
	
	int main()
	{
		using namespace std;
	
		map<string, string> mymap{
			{"hello", "world"},
			{"we", "are"},
			{"live", "from"},
			{"izmir", "istanbul"}
		};
	
		string old_key = "hello";
		string new_key = "hi";
	
		// |------------------------OLD WAY-------------------------|
		if (auto iter = mymap.find(old_key); iter != mymap.end()) {
			auto value = iter->second;
			mymap.erase(iter);
			mymap.emplace(new_key, value);
			print(mymap, "\n");
		}
		else {
			cout << "key has not been found\n";
		}
		// output ->
		//	[hi, world]
		//	[izmir, istanbul]
		//	[live, from]
		//	[we, are]
	
		// |------------------------NEW WAY-------------------------|
		if (auto iter = mymap.find(new_key); iter != mymap.end())
		{
			auto handle = mymap.extract(iter);
			handle.key() = old_key;
			handle.mapped() += "lalala";	// mapped() for value
			mymap.insert(move(handle));
		}
		print(mymap, "\n");
		// output ->
		//	[hello, worldlalala]
		//	[izmir, istanbul]
		//	[live, from]
		//	[we, are]
	}
*/

/*
	#include <map>
	#include <string>
	#include "nutility.h"
	
	int main()
	{
		using namespace std;
	
		multimap<string, string> my_multimap;
	
		for (size_t i = 0; i < 1000; ++i){
			my_multimap.emplace(rtown(), rname());
		}
	
		string str_town = "istanbul";
	
		auto [iter_lower, iter_upper] = my_multimap.equal_range(str_town);
		print(iter_lower, iter_upper, "\n");
		// output ->
		//	[istanbul, mahir]
		//	[istanbul, hakan]
		//	[istanbul, teslime]
		//	[istanbul, yilmaz]
		//	[istanbul, recep]
		//	[istanbul, naciye]
		//	[istanbul, yesim]
		//	[istanbul, aylin]
		//	[istanbul, nefes]
	}
*/

/*
	--------------------------
	| ostream iterator class |
	--------------------------
*/

/*
	#include <vector>
	#include <string>
	#include <fstream>
	#include <iterator>
	#include <algorithm>
	
	template <typename InIter, typename OutIter>
	OutIter Copy(InIter beg, InIter end, OutIter destbeg)
	{
		while (beg != end)
			*destbeg++ = *beg++;
	
		return destbeg;
	}
	
	template <typename T>
	class OstreamIterator {
	public:
		OstreamIterator(std::ostream& os, const char* psep = "") : m_os(os), mp_sep(psep) {}
		OstreamIterator& operator++() { return *this; }
		OstreamIterator& operator++(int) { return *this; }
		OstreamIterator& operator*() { return *this; }
		OstreamIterator& operator=(const T& val)
		{
			m_os << val << mp_sep;
			return *this;
		}
	
		// postfix operator++ needs to be neutral
		// prefix operator++ needs to be neutral
		// operator* needs to be needs to be neutral
	
	private:
		const char* mp_sep;
		std::ostream& m_os;
	};
	
	int main()
	{
		using namespace std;
	
		vector<string> svec{ "hello", "world", "we", "are", "live", "from", "izmir" };
	
		Copy(svec.begin(), svec.end(), OstreamIterator<string>{cout, " "});
		// output -> hello world we are live from izmir
	
			
			//	std::ofstream ofs{ "out.txt" };
			//	if (!ofs) {
			//		std::cerr << "can not create out.txt file\n";
			//		exit(EXIT_FAILURE);
			//	}
			//	Copy(svec.begin(), svec.end(), OstreamIterator<string>{ofs, "\n"});	
	}
*/

/*
	#include <vector>
	#include <iterator>
	#include <algorithm>
	
	int main()
	{
		using namespace std;
	
		vector<int> ivec{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };
		copy(ivec.begin(), ivec.end(), ostream_iterator<int>{cout, " "});
		// output -> 1 2 3 4 5 6 7 8 9
		std::cout << '\n';
	
		// only values that mod3 equals 0.
		const int mod_val = 3;
		copy_if(ivec.begin(), ivec.end(), ostream_iterator<int>{cout, " "}, [mod_val](const int& value) {
			return value % mod_val == 0;
			});
		// output -> 3 6 9
	}
*/

/*
	#include <string>
	#include <iterator>
	#include <algorithm>
	
	int main()
	{
		using namespace std;
	
		string str{ "Kenobi" };
	
		copy(str.begin(), str.end(), ostream_iterator<char>{cout, "\n"});
		// output ->
		//	K
		//	e
		//	n
		//	o
		//	b
		//	i
	}
*/

/*
	-------------------------
	| unordered_ containers |
	-------------------------
*/

/*
	In unordered containers
	
	Think about keys as
		-> phone numbers 
		-> dates
		-> addresses 
		...

	We will hash these keys to an index. 
	e.g 
		(532-381-92-92) ---> index 0
		(533-290-12-23) ---> index 1
		...
	When we create the index from keys, we can think like,
	checking an index from vector and reaching its value.

	Hashing : converting keys to index
	Hasher / hash function : the function that convert key to index

	when hasher function gets better, collisions will decrease between the indexes.
	in STL if there is collision between indexes it wil transfer that index to list container.
*/

/*
	#include <utility>
	#include <string>
	
	int main()
	{
		// std::hash is a class template (function object class)
		using namespace std;
	
		cout << hash<string>{}("hello world") << '\n';	// output -> 8618312879776256743
		cout << hash<string>{}("hello works") << '\n';	// output -> 8619145210078623245
		// return type of the hash{}.operator() function is is size_t.
	}
*/

/*
	#include <utility>
	#include <string>
	#include "nutility.h"
	#include <algorithm>
	
	int main()
	{
		using namespace std;
	
		for (size_t i = 0; i < 10; ++i)
		{
			auto town = rtown();
			cout << town << "--" << hash<string>{}(town) << '\n';
		}
		// output ->
		//	van--7567212965004407202
		//	erzurum--5838188580277136765
		//	konya--10572069968141414621
		//	rize--12840692861783398749
		//	istanbul--2879597496717178791		-->	Same keys will hashed to same index
		//	kilis--8937725022190127603
		//	gaziantep--16308901194605905576
		//	istanbul--2879597496717178791		--> Same keys will hashed to same index
		//	bingol--13541606597357020272
		//	adiyaman--9893890511214172247
	}
*/

/*
	#include <utility>
	
	template <typename Key, typename Hash = std::hash<Key>,
		typename Eq = std::equal_to<Key>, typename A = std::allocator<Key>>
	class UnorderedSet {
	
	};
*/

/*
	#include <utility>
	#include <unordered_set>
	#include <string>
	
	#include <vector>
	#include <list>
	
	int main()
	{
		using namespace std;
	
		vector<list<string>> bucket_vec;
		// every list<string> is called bucket.
		// kind of how unordered containers store.
	
		unordered_set<string> myset(512);	// bucket count
	}
*/

/*
	#include <string>
	#include <unordered_set>
	#include "nutility.h"
	
	int main()
	{
		using namespace std;
	
		unordered_set<string> myset;
	
		for (int i = 0; i < 10; ++i){
			myset.insert(rtown());
		}
		print(myset);
		// output -> bayburt denizli eskisehir rize erzurum sivas erzincan ordu canakkale agri
		// ordering is random(unordered) "rize" is before "erzurum"
	
		string searched_town = "izmir";
		// ---------OLD WAY------------
		myset.count(searched_town);
		// for set containers the return type is int
		// and value is 0 or 1, because keys are unique
	
		// ---------NEW WAY------------
		myset.contains(searched_town);
		// return type is bool
	
	
		myset.insert(searched_town);
		// return type is pair<iterator, bool>
	}
*/

/*
	Complexity of searching with key is O(1).
*/

/*
	#include <string>
	#include <unordered_set>
	#include <utility>
	
	class Myclass {
	public:
		int m_a;
		std::string m_b;
		double m_c;
	};
	
	// explicit(full) specialization for User Defined Type
	template <>
	struct std::hash<Myclass> {
		std::size_t operator()(const Myclass& m) const
		{
			// minimal operation is hashing each data member and add them.
			return std::hash<int>{}(m.m_a) +
				std::hash<std::string>{}(m.m_b) +
				std::hash<double>{}(m.m_c);
		}
	};
	
	int main()
	{
		using namespace std;
	
		unordered_set<Myclass> myset;
		unordered_set<Myclass, hash<Myclass>> myset_2;
		// Those 2 lines are same
	}
*/

/*
	#include <string>
	#include <unordered_set>
	#include <utility>
	
	class Myclass {
	public:
		int m_a;
		std::string m_b;
		double m_c;
	};
	
	// using Functor class as a Hasher function
	struct MyclassHasher
	{
		std::size_t operator()(const Myclass& m) const
		{
			// minimal operation is hashing each data member and add them.
			return std::hash<int>{}(m.m_a) +
				std::hash<std::string>{}(m.m_b) +
				std::hash<double>{}(m.m_c);
		}
	};
	
	int main()
	{
		using namespace std;
	
		unordered_set<Myclass, MyclassHasher> myset;
	}
*/

/*
	#include <string>
	#include <unordered_set>
	#include <utility>
	
	class Myclass {
	public:
		int m_a;
		std::string m_b;
		double m_c;
	};
	
	// using free function as a Hasher
	
	std::size_t hash_myclass(const Myclass& m)
	{
		// minimal operation is hashing each data member and add them.
		return std::hash<int>{}(m.m_a) +
			std::hash<std::string>{}(m.m_b) +
			std::hash<double>{}(m.m_c);
	}
	
	int main()
	{
		using namespace std;
	
		unordered_set<Myclass, decltype(&hash_myclass)> myset;
		// unordered_set<Myclass, size_t(*)(const Myclass&)> myset2(hash_myclass);
	}
*/

/*
	#include <string>
	#include <unordered_set>
	#include <utility>
	
	class Myclass {
	public:
		int m_a{};
		std::string m_b{};
		double m_c{};
	};
	
	int main()
	{
		using namespace std;
	
		// using lambda object as a hasher
		auto f = [](const Myclass& m)
		{
			return std::hash<int>{}(m.m_a) +
				std::hash<std::string>{}(m.m_b) +
				std::hash<double>{}(m.m_c);
		};
	
		unordered_set<Myclass, decltype(f)> myset;			// after C++20
		unordered_set<Myclass, decltype(f)> myset_2(f);		// before C++20
	}
*/

/*
	#include "nutility.h"
	#include <unordered_set>
	
	class Point {
	public:
		Point() = default;
		Point (int x, int y, int z) : mx(x), my(y), mz(z) {}
		friend std::ostream& operator<<(std::ostream& os, const Point& p)
		{
			return os << "(" << p.mx << ", " << p.my << ", " << p.mz << ")";
		}
	
		int getx()const
		{
			return mx;
		}
		int gety()const
		{
			return my;
		}
		int getz()const
		{
			return mz;
		}
	
		bool operator==(const Point& other)const
		{
			return mx == other.mx && my == other.my && mz == other.mz;
		}
	
		static Point random_point()
		{
			Irand rand{ 0, 9 };
			return Point{ rand(), rand(), rand() };
		}
	private:
		int mx{}, my{}, mz{};
	};
	
	struct PointHasher {
	public:
		std::size_t operator()(const Point& p) const
		{
			return
				std::hash<int>{}(p.getx()) +
				std::hash<int>{}(p.gety()) +
				std::hash<int>{}(p.getz());
		}
	};
	
	int main()
	{
		using namespace std;
	
		unordered_set<Point, PointHasher, std::equal_to<Point>> myset;
		for (int i = 0; i < 10; ++i) {
			myset.insert(Point::random_point());
		}
	
		// 2 problems in this situation
		// 1.	There is no Hasher for Hashing class Point -> (struct PointHasher)
		// 2.	We can not do comparison with == operator. -> (operator==() overload)
	
		for (const auto& p : myset) {
			std::cout << p << '\n';
		}
	}
*/

/*
	For holding custom types objects in these containers(unordered_set, unordered_map)
		-> custom type can be able to hash.
			-> creating an explicit specialization of std::hash for custom type
			-> create an Hasher function for custom type
		-> member function or free function for operator==()
		-> create another function(functor class, lambda function.. ) 
			and use this function in 3rd template parameter (like hasher function)
*/

/*
	#include "nutility.h"
	#include <unordered_set>
	
	class Point {
	public:
		Point() = default;
		Point(int x, int y, int z) : mx(x), my(y), mz(z) {}
		friend std::ostream& operator<<(std::ostream& os, const Point& p)
		{
			return os << "(" << p.mx << ", " << p.my << ", " << p.mz << ")";
		}
	
		int getx()const
		{
			return mx;
		}
		int gety()const
		{
			return my;
		}
		int getz()const
		{
			return mz;
		}
	
		bool operator==(const Point& other)const
		{
			return mx == other.mx && my == other.my && mz == other.mz;
		}
	
		static Point random_point()
		{
			Irand rand{ 0, 20 };
			return Point{ rand(), rand(), rand() };
		}
	private:
		int mx{}, my{}, mz{};
	};
	
	struct PointHasher {
	public:
		std::size_t operator()(const Point& p) const
		{
			return
				std::hash<int>{}(p.getx()) +
				std::hash<int>{}(p.gety()) +
				std::hash<int>{}(p.getz());
		}
	};
	
	int main()
	{
		using namespace std;
	
		unordered_set<Point, PointHasher, std::equal_to<Point>> myset;
	
		for (int i = 0; i < 1000; ++i) {
			myset.insert(Point::random_point());
		}
		cout << "myset.size() = " << myset.size() << '\n';
		// output -> myset.size() = 950 -> 50 collisions happened.
	
		cout << "myset.bucket_count() = " << myset.bucket_count() << '\n';
		// output -> myset.bucket_count() = 1024
		// bucket_count is power of 2. (2^10)
	
		// We can send bucket_count as an argument of constructor.
		unordered_set<Point, PointHasher, std::equal_to<Point>> myset_2(500);
		// unordered_set(size_t Buckets) overload
		cout << "myset_2.bucket_count() = " << myset_2.bucket_count() << '\n';
		// myset_2.bucket_count() = 512 -> making value to nearest power of 2 -> (2^9)
	
		//--------------------------------------------------------------------------
	
		cout << "myset.load_factor() = " << myset.load_factor() << '\n';
		// output -> myset.load_factor() = 0.925781
		// [myset.size() / myset.bucket_count() = myset.load_factor]
		cout << "myset.load_factor() = " <<
			static_cast<double>(myset.size()) / static_cast<double>(myset.bucket_count()) << '\n';
		// output -> myset.load_factor() = 0.925781
	
		//--------------------------------------------------------------------------
	
		cout << "myset.max_load_factor() = " << myset.max_load_factor() << '\n';
		// output -> myset.max_load_factor() = 1
	
	
		// when max_load_factor == 1 and the size of the unordered_set and the bucket count becomes equal
		// bucket_count will be increased by power of 2 (512 -> 1024)
		// and rehashing will be applied to the container.
		// Because of rehashing operation is expensive,
		// generally prefered max_load_factor is between 0.7 and 0.8
		// we can customize the efficiency by changing the bucket_count and max_load_factor.
	}
*/

/*
	#include <unordered_set>
	#include "nutility.h"
	#include <string>
	
	int main()
	{
		using namespace std;
	
		unordered_set<string> myset;
	
		while (myset.size() != 100)
			myset.insert(rname());
	
		std::cout << "myset.size() = " << myset.size() << '\n';
		std::cout << "myset.bucket_count() = " << myset.bucket_count() << '\n';
		std::cout << "load_factor = " << (float)myset.size() / myset.bucket_count() << '\n';
		std::cout << "myset.load_factor() = " << myset.load_factor() << '\n';
		std::cout << "myset.max_load_factor() = " << myset.max_load_factor() << '\n';
		// output ->
		//	myset.size() = 100
		//	myset.bucket_count() = 512
		//	load_factor = 0.195312
		//	myset.load_factor() = 0.195312
		//  myset.max_load_factor() = 1		-> default 1
	
		myset.max_load_factor(0.8f);
		std::cout << "myset.max_load_factor() = " << myset.max_load_factor() << '\n';
		// output -> myset.max_load_factor() = 0.8
	}
*/

/*
	#include <string>
	#include <iomanip>
	#include <unordered_set>
	#include "nutility.h"
	
	int main()
	{
		using namespace std;
	
		unordered_set<string> myset(16);
	
		while (myset.size() != 10)
			myset.insert(rname());
	
		std::cout << "myset.size() = " << myset.size() << '\n';
		std::cout << "myset.bucket_count() = " << myset.bucket_count() << '\n';
		std::cout << "myset.load_factor() = " << myset.load_factor() << '\n';
		std::cout << "myset.max_load_factor() = " << myset.max_load_factor() << "\n\n";
	
		cout << left;
	
		for (size_t i{}; i < myset.bucket_count(); ++i) {
			cout << setw(4) << i << " [" << myset.bucket_size(i) << "] ";
	
			if (myset.bucket_size(i) != 0)
			{
				for (auto iter = myset.begin(i); iter != myset.end(i); ++iter)
				{
					cout << *iter << ' ';
				}
			}
			cout << '\n';
		}
	
		// output ->
		//	myset.size() = 10
		//	myset.bucket_count() = 16
		//	myset.load_factor() = 0.625
		//	myset.max_load_factor() = 1
		//	0[2] hakan fikret		--> collision
		//	1[1] cahide
		//	2[0]
		//	3[0]
		//	4[0]
		//	5[0]
		//	6[0]
		//	7[0]
		//	8[0]
		//	9[0]
		//	10[2] sadi metin		--> collision
		//	11[2] necmi pakize		--> collision
		//	12[0]
		//	13[0]
		//	14[1] cihat
		//	15[2] atalay nagehan	--> collision

		// if we are looking for "atalay" ->
		// it is in index 15 but there is a collision(2 elements in list container)
		// finding "atalay" will be O(1) because it is first element on the list
		// inside that bucket so we can not find it directly 
	
		// if we are looking for "nagehan" ->
		// it is in index 15 and there is a collision(2 elements in list container)
		// finding "nagehan" will be amortized constant time not O(1) 
		// because we can not find it directly in the list inside index 15 bucket
		// we will first find "atalay" than will move to next node "nagehan"
	
		// if we are looking for "cihat" -> we will find it in index 14 -> O(1)
	
		// if we are looking for "izmir" -> it might be in index 9
		// but because of there is no element called "izmir",
		// it won't be hashed so we couldn't found it in any index.
	}
*/

/*
	2 scenerios that unordered(hashmap) containers rehashed.
		1. we can use container.rehash() function 
		2. when load_factor became equal to max_load_factor
*/

/*
	------------------------
	| std::array container |
	------------------------
*/

/*
	Creating a wrapper class for C style array with Zero Cost Abstraction.

	Q. Why we use std::array instead of C style array?
	A1. std::array objects does know its member type like C style array 
		but also its member count.
	A2. there is no array to pointer(array decay) conversion happens in std::array
	A3. no exception in C-style arrays when we reach out of bounds of it.
		but std::array throw exception when we use at() member function
	A4. no type conversion from different size std::array
		array<int,10> cannot implicitly convert to array<int,11>
*/

/*
	struct Array {
		int a[10];
	};
	
	int main()
	{
		Array ar = { 3, 6, 7, 9 };
		// no initializer_list constructor will be called.
		// it is aggregate initialization.
	}
*/

/*
	template <typename T, std::size_t size>
	struct Array {
		T ar[size];
	};
	
	int main()
	{
		Array<int, 5> a{ 45, 2, 6, 5, 4 };
	}
*/

/*
	#include <array>
	
	void new_line()
	{
		std::cout << "\n";
	}
	
	int main()
	{
		using namespace std;
	
		array<int, 5> ar;
		// because of aggregate initialization
		// default initialize makes elements undetermined(garbage) value
	
		for (auto i : ar)
			cout << i << '\n'; // Undefined Behaviour.
		new_line();
	
		array<int, 6> ar_2{};
		// value initializing array makes elements to be value initialize
		// so elements of ar_2 will be 0.
	
		for (auto i : ar_2)
			cout << i << ' ';
		// output -> 0 0 0 0 0 0
		new_line();
	
		array<int, 7> ar_3{0};
		// aggregate initialize all elements.
	
		for (auto i : ar_3)
			cout << i << ' ';
		// output -> 0 0 0 0 0 0 0
		new_line();
	
		array<int, 7> ar_4{ 11, 22, 33 };
		// aggregate initialize all elements.
	
		for (auto i : ar_4)
			cout << i << ' ';
		// output -> 11 22 33 0 0 0 0
	}
*/

/*
	#include <array>
	
	int main()
	{
		using namespace std;
	
		array ar{ 10, 20, 30, 40, 50 };
		array<int, 5> ar_2{ 10, 20, 30, 40, 50 };
		// Those 2 lines are same, after C++17 CTAD will be applied
	
		array<int>  ar_3{ 34,23,12 };	// syntax error
		array<> ar_4{ 34,23,12 };		// syntax error
	}
*/

/*
	#include <array>
	
	int main()
	{
		using namespace std;
	
		array ar{ 11, 22, 33, 44, 55 };
		constexpr auto arsize = ar.size();
	
		int* p = ar;	// syntax error
		// no array decay will be applied.
	
		auto p1 = ar.data();	// p's type is int*
		auto p2 = &ar[0];
		auto p3 = &*ar.begin();
		// Those 3 lines are same
	}
*/

/*
	#include <array>
	
	int main()
	{
		using namespace std;
	
		array<int, 0> ar;
	
		cout << "ar.size() = " << ar.size() << '\n';	// output -> ar.size() = 0
	
		constexpr auto b = ar.data() == nullptr;
		cout << boolalpha << b << '\n';					// output -> true
	}
*/

/*
	#include <ostream>
	#include <array>
	#include <string>
	#include "nutility.h"
	
	template <typename T, std::size_t size>
	std::ostream& operator<<(std::ostream& os, const std::array<T, size>& ar)
	{
		os << '[';
		for (size_t i{}; i < size - 1; ++i) {
			os << ar[i] << ", ";
		}
		return os << ar.back() << ']';
	}
	
	int main()
	{
		using namespace std;
	
		array ar1{ 5, 6, 7, 1, 9, 3, 2 };
		array ar2{ 3.5, 2.6, 6.7, 5.1, 1.9, 8.3, 7.2 };
	
		cout << ar1 << '\n' << ar2 << '\n';
		// output ->
		//	[5, 6, 7, 1, 9, 3, 2]
		//	[3.5, 2.6, 6.7, 5.1, 1.9, 8.3, 7.2]
	
		array<string, 5> ar3{};
		for (auto& s : ar3)
			s = rtown();
	
		cout << ar3 << '\n';
		// [afyonkarahisar, bolu, trabzon, nigde, karabuk]
	}
*/

/*
	#include <array>
	
	int main()
	{
		using namespace std;
		array<int, 5> ar{2, 4, 6, 8, 10};
		// random_access_iterator.
	
		for (auto iter = ar.crbegin(); iter != ar.crend(); ++iter)
			cout << *iter << '\n';
		// output ->
		//	10
		//	8
		//	6
		//	4
		//	2
	}
*/

/*
	#include <array>
	
	int main()
	{
		using namespace std;
		array<int, 5> ar{ 2, 4, 6, 8, 10 };
	
		// operator[]() function
		for (size_t i{}; i < ar.size(); ++i)
			cout << ar[i] << ' ';
		// output -> 2 4 6 8 10
	
		try {
			auto val = ar[5];
			// no exception thrown -> Undefined Behaviour
	
			auto val_2 = ar.at(5);
			// will throw an out_of_range exception.
		}
		catch (const std::exception& ex)
		{
			cout << "exception caught: " << ex.what() << '\n';
		}
	}
*/

/*
	#include <array>
	#include <iterator>
	#include <algorithm>
	
	int main()
	{
		using namespace std;
		array<int, 5> ar;
	
		ar.fill(12);
		copy(ar.begin(), ar.end(), ostream_iterator<int>(cout, " "));
		// output -> 12 12 12 12 12
	}
*/

/*
	#include <array>
	#include "nutility.h"
	
	std::array<int, 3> foo(int x, int y, int z)
	{
		return { 2 * x, 3 * y, 4 * z };
	}
	
	int main()
	{
		using namespace std;
	
		auto ar = foo(11, 12, 13);
	
		print(ar);					// output -> 22 36 52
		print(foo(11, 12, 13));		// output -> 22 36 52
		// Those 2 lines are same
	}
*/

/*
	#include <array>
	
	template <typename T, std::size_t size>
	std::ostream& operator<<(std::ostream& os, const std::array<T, size>& ar)
	{
		os << '[';
		for (size_t i{}; i < size - 1; ++i) {
			os << ar[i] << ", ";
		}
		return os << ar.back() << ']';
	}
	
	int main()
	{
		using namespace std;
	
		array<array<int, 3>, 4> arr{ {{1, 2, 3}, { 4, 5, 6}, {7, 8, 9}, {3, 3, 3 }} };
		cout << arr << '\n';
		// output -> [[1, 2, 3], [4, 5, 6], [7, 8, 9], [3, 3, 3]]

		arr[2][2] = 11;
		cout << arr << '\n';
		// output -> [[1, 2, 3], [4, 5, 6], [7, 8, 11], [3, 3, 3]]
	}
*/

/*
	// using std::array in C API's
	#include <array>
	#include <cstdlib>


	void print_array(const int* p, size_t size)
	{
		while (size--)
			printf("%d ", *p++);
	}

	void set_array_random(int* p, size_t size)
	{
		while (size--)
			*p++ = rand() % 1000;
	}

	int main()
	{
		using namespace std;

		array ar{ 3, 6, 7, 8, 9 };
		print_array(ar.data(), ar.size());	// output -> 3 6 7 8 9

		cout << '\n';

		set_array_random(ar.data(), ar.size());
		print_array(ar.data(), ar.size());	// output -> 41 467 334 500 169
	}
*/

/*
	#include <array>
	
	int main()
	{
		using namespace std;
	
		array ar{ 3, 5, 7, 2, 4, 3, 6 };
	
		cout << get<0>(ar) << '\n';	// output -> 3
	
		cout << get<7>(ar) << '\n';	// syntax error in compile time.
		//C2338	static_assert failed: 'array index out of bounds'
	}
*/

/*
	#include <array>
	#include "nutility.h"
	
	int main()
	{
		using namespace std;
	
		array ar{ 3, 5, 7 };
	
		auto& [x, y, z] = ar;
		++x;
		++y;
		++z;
		print(ar); // output -> 4 6 8
	
		auto [ar1, ar2, ar3] = ar;
		++ar1;
		++ar2;
		++ar3;
		print(ar); // output -> 4 6 8
		// when we don't use reference declerator.
		// elements in structured binding are created by copying.
	}
*/

/*
	#include <array>
	
	int main()
	{
		using namespace std;
	
		array ar1{ 3, 5, 7, 9 };
	
		auto [x, y, z] = ar1;	// syntax error
		// C3449	the number of identifiers must match the value of
		// 'std::tuple_size<std::array<_First,4>>::value' in a structured binding of tuple - like type
	}
*/

/*
	#include <array>

	int main()
	{
		using namespace std;

		array ar1{ 3, 5, 7, 9 };
		array ar2{ 11, 22, 33 };

		auto [x, y, z, _] = ar1;
		auto [a, b, _] = ar2;
		// syntax error
		// C2374	'_': redefinition; multiple initialization
		// C2386	'_': a symbol with this name already exists in the current scope

		// using '_' is a conventin
	}
*/

/*
	#include <array>
	
	struct Mystruct {
		int x, y, z;
	};	// aggregate type
	
	Mystruct foo()
	{
		return { 9, 8, 7 };
	}
	
	int main()
	{
		auto [x, y, z] = foo();
	
		std::cout << x << '\n';	// output -> 9
	}
*/

/*
	#include <array>
	
	class Myclass {
	public:
		Myclass() = default;
	
		Myclass(const Myclass&)
		{
			std::cout << "copy ctor\n";
		}
	
		Myclass(Myclass&&)
		{
			std::cout << "move ctor\n";
		}
	};
	
	int main()
	{
		std::array<Myclass, 3> arx;
	
		auto ary = arx;
		// output ->
		//	copy ctor
		//	copy ctor
		//	copy ctor
	
		auto arz = std::move(arx);
		// output ->
		//	move ctor
		//	move ctor
		//	move ctor
	}
*/

/*
	#include <array>
	#include <vector>
	
	int main()
	{
		using namespace std;
	
		vector<int> ivec{ 4, 6, 8, 9, 1, 2, 3 };
	
		array ar{ ivec.begin(), ivec.end() };
		//	array<vector<int>::iterator, 2> iterarr;
		// ar is holding vector<int> iterators, not the elements of the vector
	}
*/

/*
	-----------------------------------
	| std::stack -> container adaptor |
	-----------------------------------
	class template
*/

/*
	stack is class template and have 2 template argument
		1. type of the object that will hold in std::stack 
		2. type of the container that std::stack will use 
			(default template argument -> std::deque) 

	C++ standarts are saying you can use a container with push_back() member function.
*/

/*
#include <deque>

template <typename T, typename C = std::deque<T>>
class Stack {
public:
	Stack() = default;
	Stack(const C& x) : c(x) {}
	Stack(C&& x) : c(std::move(x)) {}

	void push(const T& t)
	{
		c.push_back(t);
	}

	void pop()
	{
		if (c.empty()) {
			throw std::runtime_error{ "pop from empty stack" };
		}
		c.pop_back();
	}

	std::size_t size() const
	{
		return c.size();
	}

	std::size_t empty() const
	{
		return c.empty();
	}

	template <typename ...Args>
	void emplace(Args&& ...args)
	{
		std::emplace_back(std::forward<Args>(args)...);
	}
protected:
	C c;
};
*/

/*
	#include <stack>
	#include <vector>
	#include <list>
	
	template <typename T>
	using vstack = std::stack<T, std::vector<T>>;
	
	template <typename T>
	using lstack = std::stack<T, std::list<T>>;
	
	
	int main()
	{
		using namespace std;
	
		vstack<int> my_vstack;
		my_vstack.push(1);
	
		lstack<int> my_lstack;
		my_lstack.push(2);
	}
*/

/*
	#include <stack>
	#include <deque>
	#include <vector>
	
	int main()
	{
		using namespace std;
	
		stack<int> mystack;										// has a default ctor
		stack<int> mystack_2{ 3, 5, 6, 7, 8 };					// no initializer list ctor
	
		int ar[] = { 3, 5, 6, 7, 8, 1, 2 };
		stack<int> mystack_3{ begin(ar), end(ar) };				// has a range ctor
		cout << "mystack.size() = " << mystack_3.size() << '\n';
		// output -> mystack.size() = 7
	
		deque<int> mydeque{ 1, 2, 3, 4, 5 };
		vector<int> myvec{ 6, 7, 8, 9 };
	
		stack<int> mystack_4{ mydeque };									// valid
		stack<int> mystack_5{ myvec };										// syntax error
		stack<int, vector<int>> mystack_6{ myvec };				// valid
	}
*/

/*
	#include <stack>
	
	class MyStack : public std::stack<int> {
	public:
		void multiply(int val)
		{
			for (auto& i : c) {
				i *= val;
			}
		}
		// c is a data member of the base class.
		// c is in the protected section of the base class so derived class can reach.
	};
	
	int main()
	{
		MyStack mystack;
	
		for (int i = 0; i < 10; ++i)
			mystack.push(i);
	
		mystack.multiply(10);
	
		while (!mystack.empty())
		{
			std::cout << mystack.top() << " ";
			mystack.pop();
		}
		// output -> 90 80 70 60 50 40 30 20 10 0
	
		// std::stack classes pop() member functions return type is void.
	}
*/

/*
	#include <stack>
	#include <string>
	#include "nutility.h"
	
	int main()
	{
		using namespace std;
	
		stack<string> mystack;
	
		for (int i = 0; i < 3; i++){
			auto x = rname();
			cout << x << '\n';
			mystack.push(x);
		}
	
		std::cout << "<-------- stack is being emptied -------->\n";
	
		while (!mystack.empty()) {
			std::cout << mystack.top() << " is gone\n";
			mystack.pop();
		}
		// output ->
		//	metin
		//	sadri
		//	cesim
		//	<--------stack is being emptied-------->
		//	cesim is gone
		//	sadri is gone
		//	metin is gone
	}
*/

/*
	#include <vector>
	
	template <typename T>
	class Stack {
	public:
		void push(const T& x)
		{
			c.push_back(x);
		}
		void push(T&& x)
		{
			c.push_back(std::move(x));
		}

		template <typename ...Args>
		void emplace(Args&& ...args)
		{
			c.emplace_back(std::forward<Args>(args)...);
		}

	protected:
		std::vector<T> c;
	};
*/

/*
	#include <stack>
	
	int main()
	{
		using namespace std;
	
		stack<int> mystack;
	
		mystack.push(11);
		mystack.push(22);
		mystack.push(33);
		mystack.push(44);
	
		mystack.top() = 99;	// return type is T&
	
		while (!mystack.empty())
		{
			cout << mystack.top() << ' ';
			mystack.pop();
		}
		// output -> 99 33 22 11
	}
*/

/*
	// QUESTION

	#include <stack>
	#include <array>
	#include <string>
	#include <algorithm>

	//	{}
	//	[]
	//	()
	//	<>

	static const std::array<char, 4> open_arr{ '{', '[', '(', '<' };
	static const std::array<char, 4> close_arr{ '}', ']', ')', '>' };

	bool is_match(const std::string& str)
	{
		std::stack<char> mystack;

		for (auto i : str)
		{
			auto iter_open  = std::find(open_arr.begin(), open_arr.end(), i);
			auto iter_close = std::find(close_arr.begin(), close_arr.end(), i);

			if (iter_open != open_arr.end())		// if open_brace found
				mystack.push(i);

			if (iter_close != close_arr.end())		// if close_brace found
			{
				if (!mystack.empty())
				{
					auto index = std::distance(close_arr.begin(), iter_close);

					if (mystack.top() == open_arr[index])
						mystack.pop();
					else
						return false;
				}
				else
					return false;
			}
		}

		if (mystack.empty())
			return true;
		else
			return false;
	}

	int main()
	{
		using namespace std;

		string str{ "((<hello[10]>)) {[x](y)}" };
		cout << boolalpha << is_match(str) << '\n';
	}
*/

/*
	--------------
	| std::queue |
	--------------
	default container template argument is std::deque
	First in First Out(FIFO)
*/
	
/*
	#include <queue>
	#include <vector>
	
	int main()
	{
		using namespace std;
	
		queue<int, vector<int>> x;
		x.push(12);
	
		x.pop();	// syntax error
		//  error C2039: 'pop_front': is not a member of 
		// 'std::vector<int,std::allocator<int>>'
	
		// we can not use vector container class
		// we can use list container class
		// we can use deque container class(default argument)
	}
*/

/*
	#include <queue>
	#include <string>
	
	int main()
	{
		using namespace std;
	
		queue<string> x;
	
		x.push("hello");
		x.push("world");
		x.push("live");
		x.push("from");
		x.push("izmir");
	
		cout << "x.size() = " << x.size() << '\n';
		cout << boolalpha << "is queue empty : " << x.empty() << '\n';
		cout << "queue beginning : " << x.front() << '\n';
		cout << "queue end : " << x.back() << '\n';
	
		while (!x.empty()) {
			cout << x.front() << " is leaving the queue\n";
			x.pop();
		}
		// output ->
		//	x.size() = 5
		//	is queue empty : false
		//	queue beginning : hello
		//	queue end : izmir
		//	hello is leaving the queue
		//	world is leaving the queue
		//	live is leaving the queue
		//	from is leaving the queue
		//	izmir is leaving the queue
	}
*/

/*
	-----------------------
	| std::priority_queue |
	-----------------------
*/

/*
	1. we can not use list as a container class type.
		random_access_iterator need.
	2. we can use vector container class type.
*/

/*
	#include <queue>
	#include <string>
	#include "nutility.h"
	
	int main()
	{
		using namespace std;
	
		priority_queue<string> x;
	
		for (int i = 0; i < 10; ++i)
		{
			string str = rtown();
			cout << str << " added.\n";
			x.push(str);
		}
	
		// less<string> comparator has been use as a default argument(3rd parameter).
		// lexicographical compare will be applied for the value that will leave the container.
	
		cout << '\n';
		while (!x.empty()) {
			cout << x.top() << " out\n";
			x.pop();
		}
	
		// output ->
		//	tekirdag added.
		//	sivas added.
		//	bursa added.
		//	mersin added.
		//	izmir added.
		//	diyarbakir added.
		//	agri added.
		//	kirsehir added.
		//	aksaray added.
		//	zonguldak added.
		//
		//	zonguldak out
		//	tekirdag out
		//	sivas out
		//	mersin out
		//	kirsehir out
		//	izmir out
		//	diyarbakir out
		//	bursa out
		//	aksaray out
		//	agri out
	}
*/

/*
	#include <queue>
	#include <string>
	#include <vector>
	#include <functional>
	#include "nutility.h"
	
	int main()
	{
		using namespace std;
	
		priority_queue<string, vector<string>, greater<>> x;
	
		for (int i = 0; i < 10; ++i)
		{
			string str = rtown();
			cout << str << " added.\n";
			x.push(str);
		}
	
		cout << '\n';
		while (!x.empty()) {
			cout << x.top() << " out\n";
			x.pop();
		}
	
		// output ->
		//	trabzon added.
		//	samsun added.
		//	kars added.
		//	bayburt added.
		//	ankara added.
		//	giresun added.
		//	nevsehir added.
		//	sakarya added.
		//	adiyaman added.
		//	denizli added.
		//
		//	adiyaman out
		//	ankara out
		//	bayburt out
		//	denizli out
		//	giresun out
		//	kars out
		//	nevsehir out
		//	sakarya out
		//	samsun out
		//	trabzon out
	}
*/

/*
	#include <queue>
	#include <vector>
	#include <cmath>
	#include "nutility.h"
	
	int main()
	{
		using namespace std;
	
		const auto f = [](int x, int y) {
			return abs(x) < abs(y);
		};
	
		priority_queue<int, vector<int>, decltype(f)> x;
	
		for (int i = 0; i < 10; ++i){
			x.push(Irand{ -100, 100 }());
		}
	
		while (!x.empty()) {
			cout << x.top() << '\n';
			x.pop();
		}
		// output ->
		//	- 88
		//	- 85
		//	- 69
		//	54
		//	- 41
		//	41
		//	- 35
		//	- 30
		//	- 24
		//	16
	}
*/

/*
	---------------------
	| reference wrapper |
	---------------------
*/

/*
	template <typename T>
	class ReferenceWrapper {
	public:
		ReferenceWrapper(T& t) : mp{&t} {}
		operator T& ()
		{
			return *mp;
		}
		T& get()
		{
			return *mp;
		}
	
		ReferenceWrapper operator=(T& t)
		{
			mp = &t;
		}
	private:
		T* mp;
	};
	
	int main()
	{
		int x{};
		ReferenceWrapper<int> r{ x };
	
		int ival = r;
		int ival = r.operator int &();
		// These 2 lines are same
	
		int y = 10;
		r = y;
		r.operator=(y);
		// These 2 lines are same.
	}
*/

/*
	#include <functional>
	
	template <typename T>
	std::reference_wrapper<T> Ref(T& t)
	{
		return std::reference_wrapper<T>{t};
	}
	
	int main()
	{
		using namespace std;
	
		int x = 10;
	
		reference_wrapper<int> r{ x };
		cout << r << '\n';					// output -> 10
		cout << r.operator int& () << '\n';	// output -> 10
	
		r.get() = 45;
		cout << "x = " << x << '\n';		// output -> x = 45
	
		int ival = 55;
		r = ival;
		cout << "r = " << r << '\n';		// output -> r = 55
	
		auto y = Ref(x);
		// y's type is std::reference_wrapper<int>
		// original is ref(x);
	
		auto r1 = ref(x);
		// r1's type is std::reference_wrapper<int>
		auto r2 = cref(x);
		// r2's type is std::reference_wrapper<const int>
	
		x = 10;
		++r1;
		cout << "x = " << x << '\n';	// output -> x = 11
		r1.get() = 15;
	
		++r2;			// syntax error.
		r2.get() = 15;	// syntax error
	}
*/

/*
	#include <functional>
	
	template <typename T>
	void func(T x)
	{
		std::cout << typeid(x).name() << '\n';
	}
	
	class Myclass {
		unsigned char mbuf[4096]{};
	};
	
	int main()
	{
		Myclass m;
		std::cout << "sizeof(Myclass) = " << sizeof(Myclass) << '\n';
		// output -> 4096
	
		func(m);
		// output -> class Myclass
		// copy ctor will be called for func(m) call
	
		func(std::ref(m));
		// output -> class std::reference_wrapper<class Myclass>
	
		func<Myclass&>(m);
		// can also be used instead of std:ref()
	}
*/

/*
	#include <functional>
	
	int main()
	{
		using namespace std;
	
		int x = 10, y = 20, z = 30;
		vector<int&> rvec { x, y, z }; // syntax error
		// containers can not hold references.
	
		int a = 10, b = 20, c = 30;
		vector<reference_wrapper<int>> myvec{ a, b, c };
	
		++myvec[0];
		++myvec[1];
		++myvec[2];
	
		cout << "a = " << a << '\n';	// output -> a = 11
		cout << "b = " << b << '\n';	// output -> b = 21
		cout << "c = " << c << '\n';	// output -> c = 31
	}
*/

/*
	#include <functional>
	#include <list>
	#include <vector>
	#include <algorithm>
	
	int main()
	{
		using namespace std;
	
		list<int> mylist{ 43, 21, 6, 92, 54 };
		vector<reference_wrapper<int>> myvec{ mylist.begin(), mylist.end() };
	
		sort(myvec.begin(), myvec.end());
	
		for (auto i : mylist)
			cout << i << ' ';
		// output -> 43 21 6 92 54
	
		cout << '\n';
	
		for (auto i : myvec)
			cout << i << ' ';
		// output -> 6 21 43 54 92
	
*/

/*
	#include <random>
	#include <functional>
	#include <algorithm>
	#include <vector>
	
	template <typename T>
	void func(T);
	
	template <typename ForIt, typename F>
	void Generate(ForIt beg, ForIt end, F fn)
	
	{
		while (beg != end) {
			*beg++ = fn();
		}
	}
	
	int main()
	{
		using namespace std;
	
		mt19937 eng;
		std::cout << "sizeof(eng) = " << sizeof(eng) << '\n';
		// output -> sizeof(eng) = 5000
		func(ref(eng));
	
		vector<unsigned int> ivec(1000);
		Generate(ivec.begin(), ivec.end(), eng);		// copy will be applied
		Generate(ivec.begin(), ivec.end(), ref(eng));	// no copy - reference semantics
	}
*/

/*
	#include <utility>
	#include <functional>
	
	int main()
	{
		using namespace std;
	
		int x = 10, y = 34;
	
		pair<int, int> p1{ x, y };
		p1.first = 590;
		p1.second = 887;
		cout << "x = " << x << '\n';	// output -> x = 10
		cout << "y = " << y << '\n';	// output -> y = 34
		// because of x and y has been copied to pair(p1) their values did not change.
	
		pair<int&, int&> p2{ x, y };
		p2.first = 590;
		p2.second = 887;
		cout << "x = " << x << '\n';	// output -> x = 590
		cout << "y = " << y << '\n';	// output -> y = 887
	
		auto p3 = make_pair(x, y);	// pair<int,int>
		p3.first++;
		p3.second++;
		cout << "x = " << x << '\n';	// output -> x = 590
		cout << "y = " << y << '\n';	// output -> y = 887
		// because of make_pai(x, y)'s type deduce to pair<int,int>, x ad y is copied and their values did not change.
	
		auto p4 = make_pair(ref(x), ref(y));	// pair<int&, int&>
		p4.first++;
		p4.second++;
		cout << "x = " << x << '\n';	// output -> x = 591
		cout << "y = " << y << '\n';	// output -> y = 888
	}
*/

/*
	// std::bind function adaptor (function template)

	#include <functional>
	#include <vector>
	#include <algorithm>
	
	bool is_ok(int x)
	{
		return x > 25;
	}
	
	void foo(int x, int y, int z)
	{
		std::cout << "x = " << x << '\n';
		std::cout << "y = " << y << '\n';
		std::cout << "z = " << z << '\n';
	
		std::cout << "----------------------------------------------\n";
	}
	
	int main()
	{
		using namespace std;
	
		vector<int> ivec{ 4, 12, 5, 23, 9, 45, 8, 82 };
	
	
		find_if(ivec.begin(), ivec.end(), is_ok);
	
		int ival = 14;
		find_if(ivec.begin(), ivec.end(), [ival](int x) {return x > ival; });
	
	
		// std::bind wants a callable and returns also a callable
		auto fn = bind(foo, 10, 20, 30);
		fn();
		// output ->
		//	x = 10
		//	y = 20
		//	z = 30
	
	
		// std::placeholders is a nested namespace.
		using namespace std::placeholders;
	
		auto f1 = bind(foo, 10, 20, _1);
		f1(333);
		// output ->
		//	x = 10
		//	y = 20
		//	z = 333
	
		auto f2 = bind(foo, _1, 10, 20);
		f2(333);
		// output ->
		//	x = 333
		//	y = 10
		//	z = 20
	
		auto f3 = bind(foo, _1, _2, 20);
		f3(999, 777);
		// output ->
		//	x = 999
		//	y = 777
		//	z = 20
	
		auto f4 = bind(foo, _1, 333, _2);
		f4(999, 777);
		// output ->
		//	x = 999
		//	y = 333
		//	z = 777
	
		auto f5 = bind(foo, _1, _1, _1);
		f5(3);
		// output ->
		//	x = 3
		//	y = 3
		//	z = 3
	
		auto f6 = bind(foo, _3, _1, _2);
		f6(10, 20, 30);
		// output ->
		//	x = 30
		//	y = 10
		//	z = 20
	}
*/

/*
	#include <vector>
	#include <random>
	#include <algorithm>
	#include <functional>
	
	int main()
	{
		using namespace std;
	
		vector<int> ivec(50);
	
		mt19937 eng;
		uniform_int_distribution dist{ 0, 100 };
	
		generate(ivec.begin(), ivec.end(), [&]() {return dist(eng); });
	
		for (auto i : ivec)
			cout << i << ' ';
		cout << "\n-----------------------------------\n";
		// output -> 82 13 91 84 12 97 92 22 63 31 9 55 28 19 55 100 96
		// 100 97 97 15 73 98 99 96 11 49 80 80 29 14 0 42 11 92 64 80 88 96
		// 50 66 80 3 36 85 21 94 68 68 40
	
		const int greater_than_var = 70;
	
		vector<int> destvec;
		auto fn = bind(greater<int>{}, placeholders::_1, greater_than_var);
	
		copy_if(ivec.begin(), ivec.end(), back_inserter(destvec), fn);
		// fn(*iter) called like this inside copy_if algor
	
		for (auto i : destvec)
			cout << i << ' ';
		cout << '\n';
		// output -> 82 91 84 97 92 100 96 100 97 97 73 98 99 96 80 80 92 80 88 96 80 85 94
	
	
		// also can be done by lambda expression
		vector<int> destvec2;
		copy_if(ivec.begin(), ivec.end(), back_inserter(destvec2),
			[greater_than_var](int i) {return i > greater_than_var; });
	
		for (auto i : destvec)
			cout << i << ' ';
		cout << '\n';
		// output -> 82 91 84 97 92 100 96 100 97 97 73 98 99 96 80 80 92 80 88 96 80 85 94
	}
*/

/*
	#include <functional>
	
	void foo(int x, int y, int z)
	{
		std::cout << "x = " << x << '\n';
		std::cout << "y = " << y << '\n';
		std::cout << "z = " << z << '\n';
	}
	
	int main()
	{
		using namespace std;
		using namespace placeholders;
	
		int a = 77, b = 33;
	
		// bind can be called similar like instantly invoke lambda expressions
		bind(foo, 99, _2, _1)(90, 60);
		// output ->
		//	x = 99
		//	y = 60
		//	z = 90
	}
*/

/*
	#include <functional>
	
	class Functor {
	public:
		int operator()(int x, int y)const
		{
			return x * x + y * y;
		}
	};
	
	class Myclass {
	public:
		void foo(int x) const
		{
			std::cout << "x = " << x << '\n';
		}
	};
	
	int main()
	{
		using namespace std;
		using namespace placeholders;
	
	
		auto fn = bind(Functor{}, _1, 100);
		auto val = fn(90);
		cout << "val = " << val << '\n';	// output -> val = 18100
		// callable can be a Functor class
	
		auto f1 = bind([](int a, int b) {return a * b; }, _1, 100);
		val = f1(90);
		cout << "val = " << val << '\n';	// output -> val = 9000
		// callable can be a lambda expression
	
	
		Myclass m;
		auto f2 = bind(&Myclass::foo, m, 30);
		f2();	// output -> x = 30
	
		auto f3 = bind(&Myclass::foo, _1, 40);
		f3(m);	// output -> x = 40
	
		Myclass* p{ &m };
		auto f4 = bind(&Myclass::foo, p, 50);
		f4();	// output -> x = 50
	}
*/

/*
	#include <functional>
	
	void foo(int& r)
	{
		++r;
	}
	
	void bar(std::ostream& os, int x)
	{
		os << ++x << '\n';
	}
	
	int main()
	{
		using namespace std;
	
		int x{ 30 };
		cout << "x = " << x << '\n';	// output -> x = 30
	
		auto fn = bind(foo, x);
		fn();
		cout << "x = " << x << '\n';	// output -> x = 30
		// when we send a variable in std::bind, it will copy the variable itself
		// as its data member, so x's value did not change.
	
		auto f1 = bind(foo, ref(x));
		f1();
		cout << "x = " << x << '\n';	// output -> x = 31
	
	
		auto f = bind(bar, cout, placeholders::_1);			// syntax error
		// ostream class is closed for copy operations.
	
		auto f = bind(bar, ref(cout), placeholders::_1);	// legal
		f(x);	// output -> 32
	}
*/

/*
	// std::function is a class template

	#include <functional>

	int sum(int x, int y)
	{
		return x + y;
	}
	
	int foo(int a, int b, int c)
	{
		return a * b * c;
	}
	
	class Functor {
	public:
		int operator()(int a, int b)const
		{
			return a * b;
		}
	};
	
	int main()
	{
		using namespace std;
		using namespace placeholders;
	
		auto f1 = [](int x, int y) {return x * x + y * y; };
		auto f2 = std::bind(foo, _1, _2, 400);
	
		std::function<int(int, int)> fn1{ sum };
		cout << fn1(34, 56) << '\n';	// output -> 90
		// sum function has been called.
	
		std::function<int(int, int)> fn2{ Functor{} };
		cout << fn2(34, 56) << '\n';			// output -> 1904
		// Functor classes operator() call function has been called.
	
		std::function<int(int, int)> fn3{ f1 };
		cout << fn3(34, 56) << '\n';			// output -> 4292
		// f1 lambda expression has been called.
	
		std::function<int(int, int)> fn4{ f2 };
		cout << fn4(34, 56) << '\n';			// output -> 761600
		// f2 callable(foo()) returns from std::bind has been called
	
		std::function<int(int, int)> fn5{ [](int a, int b) {return a - b; } };
		cout << fn5(34, 56) << '\n';			// output -> -22
	}
*/

/*
	#include <functional>
	#include <vector>
	
	void func(std::function<int(int, int)> fn)
	{
		fn(10, 20);
	}
	// generic callback structure.
	
	int sum(int x, int y)
	{
		return x + y;
	}
	
	class Functor {
	public:
		int operator()(int a, int b)const
		{
			return a * b;
		}
	};
	
	int foo(int a, int b, int c)
	{
		return a * b * c;
	}
	
	using myfunc = std::function<int(int, int)>;
	
	int main()
	{
		using namespace std;
		using namespace placeholders;
	
		vector<std::function<int(int, int)>> myvec;
		// vector<myfunc> myvec;
		// These 2 lines are same
	
		myvec.push_back(sum);
		myvec.push_back(Functor{});
		myvec.push_back([](int a, int b) {return a * b - 1; });
		myvec.push_back(std::bind(foo, 10, _1, _2));
	
		for (auto& f : myvec) {
			f(10, 20);
		}
		// in every turn we will call a function.
	}
*/

/*
	#include <functional>
	
	int foo(int, int)
	{
		std::cout << "foo called\n";
		return 1;
	}
	
	int bar(int, int)
	{
		std::cout << "bar called\n";
		return 2;
	}
	
	struct Functor {
		int operator()(int, int)
		{
			std::cout << "Functor\n";
			return 3;
		}
	
	};
	
	int main()
	{
		using namespace std;
	
		function f{ foo };	// C++17 Class Template Argument Deduction (CTAD)
		f(1, 2);	// output -> foo called
	
		f = bar;
		f(1, 2);	// output -> bar called
	
		f = Functor{};
		f(1, 2);	// output -> Functort
	
		f = [](int a, int b) {
			std::cout << "lambda expression\n";
			return 4;};
		f(1, 2);	// output -> lambda exprssion
	}
*/

/*
	#include <functional>
	
	int main()
	{
		using namespace std;
	
		function<int(int, int)> fn;	// using default ctor
	
		// fn is not wrapping any function when default constructed.
		// calling fn() will cause an exception.
	
		try
		{
			fn(12, 56);	// run-time error
		}
		catch (const std::bad_function_call& ex)
		{
			std::cout << "exception caught: " << ex.what() << '\n';
			// output -> exception caught: bad function call
		}
	}
*/

/*
	#include <functional>
	
	int bar(int, int)
	{
		std::cout << "bar called\n";
		return 2;
	}
	
	int main()
	{
		using namespace std;
	
		// function<int(int, int)> fn;
		// output ->
		//	there is no wrapped callable.
	
		function fn = bar;
		// output ->
		//	there is a callable can be invoked.
		//	bar called
	
		if (fn) {
			std::cout << "there is a callable can be invoked.\n";
			fn(10, 20);
		}
		else {
			std::cout << "there is no wrapped callable.\n";
		}
	}
*/

/*
	#include <functional>
	
	int bar(int);
	
	std::function<int(int)> foo()
	{
		//	return bar;
		return [](int x) {return x * 5; };
	}
	
	int main()
	{
		std::cout << foo()(25) << '\n';	// output -> 125
	}
*/

/*
	#include <vector>
	#include <functional>
	
	void foo(int (*fptr)(int, int));
	int bar(int, int);
	
	using ftype = int(*)(int);
	int f1(int);
	int f2(int);
	int f3(int);
	
	using ftype_generalized = std::function<int(int)>;
	
	int main()
	{
		foo(bar);
		foo(&bar);
		// both are same because function to function pointer conversion will be happen.
		// but for classes member functions it is not same different syntax is applied.
	
		std::vector<ftype> myvec{ f1, f2, f3 };
		std::vector<ftype> myvec{ &f1, &f2, &f3 };
		// These 2 lines are same
	
		std::vector myvec{ f1, f2, f3 };	// CTAD C++17
	
		std::vector<ftype_generalized> func_vec{ f1, f2, f3 };
	}
*/

/*
	----------------------------
	| member function pointers |
	----------------------------
*/

/*
	class Myclass {
	public:
		static int foo(int);
		int baz(int);
	};
	
	int bar(int);
	
	int main()
	{
		auto f = [](int a) {return a * 5; };
	
		int(*fp)(int);
	
		fp = &bar;
		fp = &Myclass::foo;	// static member function
		fp = f;				// stateless lambda
	
		fp = &Myclass::baz;	// syntax error.
		// non-static member functions does have this pointer(hidden parameter)
	
		auto fp1 = &Myclass::baz;
		int(Myclass::* fp1)(int) = &Myclass::baz;
		// These 2 lines are same
	}
*/

/*
	int foo(int);
	
	using ftype = int (*)(int);
	
	int main()
	{
		auto fp1 = &foo;
		auto fp2 = foo;
		int (*fp3)(int) = &foo;
		ftype fp4 = &foo;
		// Those 4 lines are same.
	}
*/

/*
	int f1(int);
	int f2(int);
	int f3(int);
	int f4(int);
	int f5(int);
	
	using fptype = int (*)(int);
	
	int main()
	{
		fptype fp_arr[] = { f1, f2, f3, f4, f5 };
	}
*/

/*
	int f1(int);
	int f2(int);
	int f3(int);
	int f4(int);
	int f5(int);
	
	using fptype = int (*)(int);
	
	int main()
	{
		auto f = f1;
		// type deduction for auto is int(*)(int) which is a function pointer
	
		auto& r = f1;
		// type deduction for auto is int(int) which is a function itself.
		int(&r2)(int) = f1;	// same line as [auto& r = f1]
	}
*/

/*
	// there is no type difference between global foo() and static member bar() functions.
	// static member functions did not have this pointer.
	
	#include <type_traits>
	
	int foo(int);
	
	class Myclass {
	public:
		static int bar(int);
	};
	
	int main()
	{
		auto f1 = foo;
		auto f2 = Myclass::bar;
	
		std::is_same_v<decltype(f1), decltype(f2)>;	// true[compile time]
	}
*/

/*
	int foo(int);
	
	class Myclass {
	public:
		int bar(int);
		double baz(int, int);
	};
	
	int main()
	{
		auto f1 = foo;
	
		int(*f2)(int) = Myclass::bar;	// syntax error
		// non-static member functions are not implicitly convert 
		// from function to function pointer.
	
		int(Myclass::* f2)(int) = &Myclass::bar;
		double (Myclass::* f3)(int, int) = &Myclass::baz;
	}
*/

/*
	class Myclass {
	public:
		int foo(int);
		int bar(int);
		int baz(int);
	};
	
	using mftype = int (Myclass::*)(int);
	
	int main()
	{
		int(Myclass:: * mf_arr2[3])(int) = {
			&Myclass::bar,
			&Myclass::foo,
			&Myclass::baz,
		};
	
		mftype mf_arr2[] = {
			&Myclass::bar,
			&Myclass::foo,
			&Myclass::baz, };
	}
*/

/*
	class Myclass {
	public:
		int foo(int x)
		{
			std::puts("int Myclass::foo(int x)");
			std::printf("x = %d\n", x);
			std::cout << "this = " << this << '\n';
			return x;
		}
	};
	
	int main()
	{
		Myclass m;
	
		std::cout << "&m = " << &m << '\n';
		m.foo(45);
	
		// output ->
		//	&m = 00BCF9E7
		//	int Myclass::foo(int x)
		//	x = 45
		//	this = 00BCF9E7
	
		auto fp = &Myclass::foo;
		// int (Myclass:: * fp)(int) = &Myclass::foo;
	
		// [.*] -> member function pointer selection operator
		(m.*fp)(34);
		// output ->
		//	int Myclass::foo(int x)
		//	x = 34
		//	this = 00BCF9E7
	}
*/

/*
	class Myclass {
	public:
		int foo(int x)
		{
			std::puts("int Myclass::foo(int x)");
			std::printf("x = %d\n", x);
			std::cout << "this = " << this << '\n';
			return x;
		}
	};
	
	int main()
	{
		Myclass m;
		Myclass* p{ &m };
	
		auto fp = &Myclass::foo;
	
		((*p).*fp)(34);	// verbose
		// can be used to call a member function if we have a pointer to an object.
		// output ->
		//	int Myclass::foo(int x)
		//	x = 34
		//	this = 007AFD57
	
		(p->*fp)(44);
		// output ->
		//	int Myclass::foo(int x)
		//	x = 44
		//	this = 007AFD57
	}
*/

/*
	#include <functional>
	
	int sum(int x, int y, int z)
	{
		std::cout << "sum(int, int, int)\n";
		return x + y + z;
	}
	
	int main()
	{
		auto result = std::invoke(sum, 10, 20, 30);
		// output -> sum(int, int, int)
	
		std::cout << "std::invoke(sum, 10, 20, 30) = " << result << '\n';
		// output -> std::invoke(sum, 10, 20, 30) = 60
	}
*/

/*
	class Myclass {
	public:
		int foo(int x)
		{
			std::puts("int Myclass::foo(int x)");
			std::printf("x = %d\n", x);
			std::cout << "this = " << this << '\n';
			return x;
		}
	};
	
	int main()
	{
		using namespace std;
	
		Myclass m;
		cout << "&m = " << &m << '\n';
		// output -> &m = 004FFB93
	
		invoke(&Myclass::foo, m, 12);
		// output ->
		//	int Myclass::foo(int x)
		//	x = 12
		//	this = 004FFB93
	
		auto fptr = &Myclass::foo;
		invoke(fptr, m, 13);
		// output ->
		//	int Myclass::foo(int x)
		//	x = 13
		//	this = 004FFB93
	
		Myclass* ptr{ &m };
		invoke(fptr, ptr, 14);
		// output ->
		//	int Myclass::foo(int x)
		//	x = 14
		//	this = 004FFB93
	}
*/

/*
	class Myclass {
	public:
		int foo(int x);
		int bar(int x);
		int baz(int x);
	};
	
	void g(Myclass m, int val, int (Myclass::*fp)(int))
	{
		(m.*fp)(val);
	}
	
	int main()
	{
		Myclass mx;
	
		g(mx, 20, &Myclass::baz);
		g(mx, 20, &Myclass::bar);
		g(mx, 20, &Myclass::foo);
		// client can declare which member function will be called.
	}
*/

/*
	#include <functional>
	
	class Myclass {
	public:
		int foo(int x)
		{
			std::cout << "Myclass::foo(int)\n";
			return 1;
		}
		int bar(int x)
		{
			std::cout << "Myclass::bar(int)\n";
			return 2;
		}
		int baz(int x)
		{
			std::cout << "Myclass::baz(int)\n";
			return 3;
		}
	};
	

	int main()
	{
		Myclass mx;
	
		using ftype = int(Myclass::*)(int);
	
		ftype arr[] = {
			&Myclass::foo,
			&Myclass::bar,
			&Myclass::baz,
		};
	
		for (auto fp : arr)
		{
			(mx.*fp)(12);
			std::invoke(fp, mx, 13);
			// Those 2 lines acts same
		}
		// output ->
		//	Myclass::foo(int)
		//	Myclass::bar(int)
		//	Myclass::baz(int)
	}
*/

/*
	class Myclass {
	public:
		int foo(int x)
		{
			std::cout << "Myclass::foo(int)\n";
			return 1;
		}
		int bar(int x)
		{
			std::cout << "Myclass::bar(int)\n";
			return 2;
		}
	
		void func()
		{
			((*this).*mfp)(10);
		}
	
		void set_mfp(int (Myclass::* f)(int))
		{
			mfp = f;
		}
	private:
		int (Myclass::* mfp)(int) {&Myclass::foo};
	};
	
	
	int main()
	{
		Myclass mx;
		mx.func();	// output -> Myclass::foo(int)
	
		mx.set_mfp(&Myclass::bar);
		mx.func();	// output -> Myclass::bar(int)
	}
*/

/*
	------------------------
	| data member pointers |
	------------------------
*/

/*
	#include <functional>
	
	struct Point {
		int mx, my, mz;
	};
	
	int main()
	{
		Point p = { 35, 56, 90 };
		auto x = &p.my;
		// x's type is int* (pointer to int)
	
		auto dmptr = &Point::mx;			// data member pointer
		//int Point::* dmptr = &Point::mx;
		// Those 2 lines are same.
	
		std::cout << p.*dmptr << '\n';	// output -> 35
	
		p.*dmptr = 90;	// [p.*dmptr] is an L value expression
		std::cout << "p.mx = " << p.mx << '\n';	// output -> p.mx = 90
	
		std::invoke(dmptr, p) = 888;
		std::cout << "p.mx = " << p.mx << '\n';	// output -> p.mx = 888
	}
*/

/*
	#include <functional>
	
	struct Point {
		int mx, my, mz;
	};
	
	void func(Point& p, int Point::*mp)
	{
		p.*mp = 555;
	}
	
	int main()
	{
		Point mypoint = { 44, 77, 99 };
	
		func(mypoint, &Point::mx);
		func(mypoint, &Point::my);
		func(mypoint, &Point::mz);
		// client can declare which data member will be used.
	}
*/

/*
	#include <functional>
	
	int main()
	{
		using namespace std;
	
		function<double(double)> f;
	
		cout << (f ? "not empty" : "empty") << '\n';	// output -> empty
	
		f = [](double dval) {return dval * dval; };
		cout << (f ? "not empty" : "empty") << '\n';	// output -> not empty
	}
*/

/*
	#include <functional>
	
	class Myclass {
	public:
		void foo(int x)
		{
			std::cout << "void Myclass::foo(int x) x = " << x << '\n';
			std::cout << "this = " << this << '\n';
		}
	};
	
	int main()
	{
		using namespace std;
	
		function<void(Myclass&, int)> f1 = &Myclass::foo;
		function<void(Myclass*, int)> f2 = &Myclass::foo;
	
		Myclass m;
		cout << "&m = " << &m << '\n';	// output -> &m = 00AFF687
	
		f1(m, 10);
		f2(&m, 22);
		// output ->
		//	void Myclass::foo(int x) x = 10
		//	this = 00AFF687
		//	void Myclass::foo(int x) x = 22
		//	this = 00AFF687
	}
*/

/*
	#include <functional>
	
	class Myclass {
	public:
		void foo(int x)
		{
			std::cout << "Myclass::foo(int x) x = " << x << '\n';
			std::cout << "this = " << this << '\n';
		}
	};
	
	int main()
	{
		using namespace std;
	
		auto fn = mem_fn(&Myclass::foo);
	
		Myclass m;
		cout << "&m = " << &m << '\n';	// output -> &m = 00F3FA3B
	
		fn(m, 12);
		// output ->
		//	Myclass::foo(int x) x = 12
		//	this = 00F3FA3B
	}
*/

/*
	#include <vector>
	#include <string>
	#include <algorithm>
	#include <functional>
	
	int main()
	{
		using namespace std;
	
		vector<string> svec{ "hello", "world", "we", "are", "live", "from", "izmir" };
		vector<size_t> len_vec(7);
		vector<size_t> len_vec2(7);
	
		transform(svec.begin(), svec.end(), len_vec.begin(), mem_fn(&string::size));
		// every string object in svec will call its size() member function
	
		transform(svec.begin(), svec.end(), len_vec2.begin(), 
								[](const string& str) {return str.size(); });
		// can be done by a lamda expression too..
	
		for (auto len : len_vec)
			cout << len << ' ';
		cout << '\n';
		// output -> 5 5 2 3 4 4 5
	
		for (auto len : len_vec2)
			cout << len << ' ';
		cout << '\n';
		// output -> 5 5 2 3 4 4 5
	}
*/

/*
	#include <functional>
	
	bool is_even(int x)
	{
		return x % 2 == 0;
	}
	
	int main()
	{
		using namespace std;
	
		int ival{ 34546 };
		cout << boolalpha;
	
		cout << is_even(ival) << '\n' << is_even(ival + 1) << '\n';
		// output ->
		//	true
		//	false
	
		auto fn = not_fn(is_even);
		cout << fn(ival) << '\n' << fn(ival + 1) << '\n';
		// output ->
		//	false
		//	true
	
		// not_fn adaptor gets a callable as a parameter and returns a callable.
		// the callable that not_fn() returns, will have a logical not of the result that it normally returns.
		// is_even(1) normally returns false but not_fn(is_even)(1) returns true
	}
*/

/*
	#include <algorithm>
	#include <functional>
	#include <random>
	#include <vector>
	
	bool is_even(int x)
	{
		return x % 2 == 0;
	}
	
	int main()
	{
		using namespace std;
	
		mt19937 eng;
		uniform_int_distribution dist{ 0, 10000 };
	
		vector<int> ivec(5000);
		generate(ivec.begin(), ivec.end(), [&] {return dist(eng); });
	
		cout << "count of odd : " <<
			count_if(ivec.begin(), ivec.end(), [](int x) { return !is_even(x); }) << '\n';
		// output -> count of odd : 2475
	
		cout << "count of odd : " <<
			count_if(ivec.begin(), ivec.end(), not_fn(is_even)) << '\n';
		// output -> count of odd : 2475
	}
*/

/*
	------------------------------
	| std::move_iterator adaptor |
	------------------------------
*/

/*
	#include <string>
	#include <vector>
	#include <iterator>
	
	class Myclass {
	public:
		Myclass() = default;
		Myclass(const Myclass&) 
		{
			std::cout << "copy ctor\n";
		}
		Myclass(Myclass&&)
		{
			std::cout << "move ctor\n";
		}
		Myclass& operator=(const Myclass&)
		{
			std::cout << "copy assignment\n";
			return *this;
		}
		Myclass& operator=(Myclass&&)
		{
			std::cout << "move assignment\n";
			return *this;
		}
	};
	
	template <typename Iter>
	std::move_iterator<Iter> MakeMoveIterator(Iter it)
	{
		return std::move_iterator<Iter>{it};
	}
	
	int main()
	{
		using namespace std;
	
		vector<string> svec{ "hello_world", "we_are_live", "from_Izmir" };
	
		auto iter = svec.begin();
		auto s = *iter;	// copy ctor
		cout << "length = " << svec[0].length() << '\n'; // output -> length = 11
		// did not moved, it is copied.
	
		auto s2 = std::move(*iter);
		cout << "length = " << svec[0].length() << '\n'; // output -> length = 0
		// it is moved
	
		*iter = "hello world";
		for (auto str : svec)
			cout << str << ' ';
		cout << '\n';
		// output -> hello world we_are_live from_Izmir
	
		move_iterator<vector<string>::iterator> move_iter{ svec.begin() };
		auto s3 = *move_iter;
		cout << "length = " << svec[0].length() << '\n'; // output -> length = 0
		// element is moved.
	
	
		vector<Myclass> my_vec(100);
		move_iterator <vector<Myclass>::iterator> vec_iter{ my_vec.begin() };
		Myclass x = *vec_iter;	// output -> move ctor
	
		auto iter_end = MakeMoveIterator(my_vec.end());
		// iter_end's type is std::move_iterator<std::vector<Myclass>::iterator>
	
		auto s4 = *make_move_iterator(my_vec.begin());	// output -> move ctor
		// STL make_move_iterator function template
	}
*/

/*
	#include <vector>
	#include <iterator>
	#include <algorithm>
	
	class Myclass {
	public:
		Myclass() = default;
	
		Myclass(const Myclass&)
		{
			std::cout << "copy ctor\n";
		}
		Myclass(Myclass&&)
		{
			std::cout << "move ctor\n";
		}
		Myclass& operator=(const Myclass&)
		{
			std::cout << "copy assignment\n";
			return *this;
		}
		Myclass& operator=(Myclass&&)
		{
			std::cout << "move assignment\n";
			return *this;
		}
	};
	
	int main()
	{
		using namespace std;
	
		vector<Myclass> x(10);
		vector<Myclass> y(10);
	
		copy(x.begin(), x.end(), y.begin());
		// copy assignment will be called for 10 times
	
		copy(make_move_iterator(x.begin()), make_move_iterator(x.end()), y.begin());
		// move assignment will be called for 10 times
	
		std::move(x.begin(), x.end(), y.begin());
		// move assignment will be called for 10 times
		// std::move() is an STL algorithm in <algorithm> header
	}
*/

/*
	--------------
	| std::tuple |
	--------------
*/

/*
	#include <tuple>
	#include <string>
	
	enum {age, wage, name};
	
	int main()
	{
		using namespace std;
	
		tuple<int, double, string> tx{ 12, 4.5, "hello"};
		tuple{ 12, 4.5, "hello" };	// CTAD(C++17)
	
		get<0>(tx) = 16;
		// returns a reference to 0'th index element in tx tuple
	
		cout << get<0>(tx) << '\n';	// output -> 16
	
		get<2>(tx) += " world";
		cout << get<2>(tx) << '\n';	// output -> hello world
	
		get<3>(tx);					// syntax error
		// will be a compile time error not run-time error.
	
		int index = 2;
		get<index>(tx);				// syntax error
		// compile time error nttp has to be constant expression
	
		const int c_index = 1;
		get<c_index>(tx);			// legal
	
		get<double>(tx) = 10.2;
		cout << get<1>(tx) << '\n';	// output -> 10.2
	
	
		tuple tx2{ 12, 4.5, 44 };
		get<int>(tx2) = 17;			// ambiguity error
		// there are 2 int in tx2 tuple.
	
	
		get<wage>(tx) = 99.9;
		cout << get<1>(tx) << '\n';	// output -> 99.9
	}
*/

/*
	#include <tuple>
	
	template <typename ...Args>
	auto MakeTuple(Args&& ...args)
	{
		return std::tuple(std::forward<Args>(args)...) {};
	}
	
	int main()
	{
		using namespace std;
		auto tp = make_tuple(12, 6.76, "Hello world"s);
		// tp's type is std::tuple<int, double, std::string>
	
		auto tp2 = MakeTuple(12, 6.76, 9L);
		// tp2's type is std::tuple<int, double, long>
	}
*/

/*
	#include <tuple>
	#include <string>
	
	using namespace std;
	
	auto foo()
	{
		return tuple{ 82, 5.3, string{"live izmir"} };
	}
	
	int main()
	{
		tuple tx{ 12, 8.2, string{"hello world"} };
	
		auto& [age, height, name] = tx;
		// structured binding
	
		age = 28;
		cout << get<0>(tx) << '\n';	// output -> 28
	
		auto [x, y, z] = foo();
	
		std::cout << z << '\n';		// output -> live izmir
	}
*/

/*
	#include <tuple>
	#include <string>
	#include <vector>
	
	using Person = std::tuple<int, double, std::string>;
	
	int main()
	{
		using namespace std;
		vector<Person> pvec{ {10, 2.3, "hello"}, {99,6.3, "world"} };
	
		pvec.emplace_back(18, 8.5, "izmir");
	
		for (auto item : pvec)
		{
			cout << get<0>(item) << ' ';
			cout << get<1>(item) << ' ';
			cout << get<2>(item) << '\n';
		}
		// output ->
		//	10 2.3 hello
		//	99 6.3 world
		//	18 8.5 izmir
	
		// using structured binding
		for (const auto& [x, y, z] : pvec)
		{
			cout << x << ' ';
			cout << y << ' ';
			cout << z << '\n';
		}
		// output ->
		//	10 2.3 hello
		//	99 6.3 world
		//	18 8.5 izmir
	}
*/

/*
	// comparison in tuple
	
	#include <tuple>
	#include <random>
	#include <algorithm>
	#include <vector>
	
	using My_tuple = std::tuple<int, int, int>;
	
	int main()
	{
		using namespace std;
	
		vector<My_tuple> tvec;
	
		mt19937 eng;
		uniform_int_distribution dist1{ 0, 10 };
		uniform_int_distribution dist2{ 0, 20 };
		uniform_int_distribution dist3{ 0, 30 };
	
		for (int i = 0; i < 1000; ++i)
		{
			tvec.emplace_back(dist1(eng), dist2(eng), dist3(eng));
		}
	
		sort(tvec.begin(), tvec.end());
	
		for (const auto& [x, y, z] : tvec)
		{
			cout << x << ' ';
			cout << y << ' ';
			cout << z << '\n';
		}
	
		// output ->
		//	0 0 4
		//	0 0 9
		//	0 0 12
		//	0 0 18
		//	0 0 18
		//	0 0 30
		//	0 1 2
		//	0 1 7
		//	0 1 21
		//	0 1 27
		//	0 2 0
		//	0 2 1
		//	0 2 12
		//	0 2 24
	}
*/

/*
	#include <tuple>
	
	std::tuple<int, std::string, double> foo()
	{
		return { 99, "yes", 15.3 };
	}
	
	int main()
	{
		using namespace std;
	
		int x{};
		string str{};
		double d{};
	
		auto tp = tie(x, str, d);
		// tp's type is std::tuple<int&, std::string&, double&>
	
		tie(x, str, d) = foo();
		// tp = foo();
	
		cout << x << '\n';		// output -> 99
		cout << str << '\n';	// output -> yes
		cout << d << '\n';		// output -> 15.3
	}
*/

/*
	#include <tuple>
	#include <utility>
	
	int main()
	{
		int x = 10;
		int y = 34;
	
		std::tie(y, x) = std::pair{ x,y };
	
		std::cout << "x = " << x << '\n';	// output -> x = 34
		std::cout << "y = " << y << '\n';	// output -> y = 10
	}
*/

/*
	#include <tuple>
	#include <string>
	
	std::tuple<int, double, std::string> foo();
	
	int main()
	{
		using namespace std;
	
		int ival{};
		double dval{};
		string str{};
	
		tie(std::ignore, dval, str) = foo();
		// we can use std::ignore if we do not want to use that variable.
	
		auto [_, dval, str] = foo();
		// we do need to crate a variable even if
		// we are not going to use it in structured binding.
	
		auto [_, k, l] = foo();	// syntax error
		// we already used a variable called '_'
	
		auto [__, x, y] = foo();
	}
*/

/*
	#include <tuple>
	
	int main()
	{
		using namespace std;
	
		int x = 1, y = 2, z = 3;
	
		//	int temp = x;
		//	x = y;
		//	y = z;
		//	z = temp;
		// instead of this code we can use std::tie
	
		tie(x, y, z) = tuple{ y, z, x };
		cout << x << y << z << '\n';	// output -> 231
	}
*/

/*
	#include <tuple>
	
	class Date {
	public:
		Date(int y, int m, int d) : m_year{ y }, m_mon{ m }, m_day{ d } {}
	
		friend bool operator<(const Date& d1, const Date& d2)
		{
			return std::tuple(d1.m_year, d1.m_mon, d1.m_day) < std::tuple(d2.m_year, d2.m_mon, d2.m_day);
			// In tuple, comparison starts from first elem, 
			// if same then second, still same then third ...
		}
	private:
		int m_year;
		int m_mon;
		int m_day;
	};
*/

/*
	--------------
	| std::apply |
	--------------
*/

/*
	#include <tuple>
	
	void print(int x, int y, int z)
	{
		std::cout << x << ' ' << y << ' ' << z << '\n';
	}
	
	void double_it(int& x, int& y, int& z)
	{
		x *= 2;
		y *= 2;
		z *= 2;
	}
	
	int main()
	{
		using namespace std;
	
		tuple tx{ 4,6,9 };
	
		apply(print, tx);							// output -> 4 6 9
		print(get<0>(tx), get<1>(tx), get<2>(tx));	// output -> 4 6 9
		// Those 2 lines acts like same.
	
		apply(double_it, tx);
		apply(print, tx);							// output -> 8 12 18
	}
*/

/*
	#include <tuple>
	
	template <typename ...Ts>
	std::ostream& operator<<(std::ostream& os, const std::tuple<Ts...>& tx)
	{
		std::apply
		(
			[&os](const Ts& ...tupleArgs)
			{
				os << '[';
				std::size_t n{ 0 };
				((os << tupleArgs << (++n != sizeof...(Ts) ? ", " : "")), ...);	// binary fold expression
				os << ']';
			}, tx
		);
		return os;
	}
	
	int main()
	{
		std::cout << std::tuple{ 43, 5.6, "hello", 'A' } << '\n';
	}
*/

/*
	// tuple_size and tuple_element are meta functions in tuple interface
	
	#include <tuple>
	#include <array>
	
	using tp_type = std::tuple<int, double, long>;
	using arr_type = std::array<double, 5>;
	
	int main()
	{
		using namespace std;
	
		constexpr auto val = tuple_size<tp_type>::value;
		constexpr auto val2 = tuple_size_v<tp_type>;		// variable template
		// Those 2 lines are same
		// vals value is equal to element count in tuple
	
		constexpr auto val3 = tuple_size_v<arr_type>;
		// val3 equals to 5
	
		// tuple_size can be used for std::pair, std::array and std::tuple.(tuple interface)
	
		tuple_element<1, tp_type>::type x{};	// x's type is double
		tuple_element_t<0, tp_type> y{};		// y's type is int
		// alias template
	}
*/

/*
	----------------------------
	| sorted ranged algorithms |
	----------------------------
*/

/*
	#include <vector>
	#include <string>
	#include "nutility.h"
	
	int main()
	{
		using namespace std;
	
		vector<string> svec;
	
		for (int i = 0; i < 5; ++i) {
			auto town = rtown();
			auto iter = lower_bound(svec.begin(), svec.end(), town);
	
			svec.insert(iter, std::move(town));
			print(svec);
		}
		// output ->
		//	sivas
		//	sivas tunceli
		//	kirikkale sivas tunceli
		//	elazig kirikkale sivas tunceli
		//	denizli elazig kirikkale sivas tunceli
	}
*/

/*
	#include <vector>
	#include <string>
	#include "nutility.h"
	
	int main()
	{
		using namespace std;
	
		vector<string> svec{"aaa", "bbb", "ccc", "ddd", "ddd", "ddd", "eee"};
	
		auto [iter_lower, iter_upper] = equal_range(svec.begin(), svec.end(), "ddd");
	
		cout << "index lower_bound = " << distance(svec.begin(), iter_lower) << '\n';
		cout << "index upper_bound = " << distance(svec.begin(), iter_upper) << '\n';
		// output ->
		//	index lower_bound = 3
		//	index upper_bound = 6
	}
*/

/*
	#include <vector>
	#include <list>
	#include "nutility.h"
	
	int main()
	{
		using namespace std;
	
		vector<int> ivec;
		list<int> ilist;
	
		rfill(ivec, 20, Irand{ 0, 100 });
		rfill(ilist, 20, Irand{ 0, 100 });
	
		sort(ivec.begin(), ivec.end());
		ilist.sort();
	
		print(ivec);
		// output -> 4 11 11 13 16 20 26 27 32 34 37 37 68 69 78 82 84 94 97 99
		print(ilist);
		// output -> 6 9 11 15 28 29 32 37 45 49 56 62 65 68 70 72 75 93 94 96
	
		// vector and list both have
		set_intersection(ivec.begin(), ivec.end(), ilist.begin(), ilist.end(), ostream_iterator<int>{cout, " "});
		// output -> 11 32 37 68 94
		std::cout << '\n';
	
		// all of the vector and list have
		set_union(ivec.begin(), ivec.end(), ilist.begin(), ilist.end(), ostream_iterator<int>{cout, " "});
		// output -> 4 6 9 11 11 13 15 16 20 26 27 28 29 32 34 37
		//				37 45 49 56 62 65 68 69 70 72 75 78 82 84 93 94 96 97 99
		std::cout << '\n';
	
		// vector have but list does not have
		set_difference(ivec.begin(), ivec.end(), ilist.begin(), ilist.end(), ostream_iterator<int>{cout, " "});
		// output -> 4 11 13 16 20 26 27 34 37 69 78 82 84 97 99
		std::cout << '\n';
	
		// (all of the vector and list have) - (vector and list both have)
		set_symmetric_difference(ivec.begin(), ivec.end(), ilist.begin(), ilist.end(), ostream_iterator<int>{cout, " "});
		// output -> 4 6 9 11 13 15 16 20 26 27 28 29 34 37
		//				45 49 56 62 65 69 70 72 75 78 82 84 93 96 97 99
	}
*/

/*
	#include <vector>
	#include <algorithm>
	
	int main()
	{
		using namespace std;
	
		vector<int> ivec{ 2, 5, 7, 9, 13, 45, 89, 90, 123, 567 };
		vector<int> ivec_2{ -2, 5, -7, 9, -13, -45, -89, 90, -123, 567 };
	
		int ival{45};
		if (binary_search(ivec.begin(), ivec.end(), ival))
			cout << "the value : " << ival << " is exists in vector\n";
		else
			cout << "the value : " << ival << " is not exists in vector\n";
		// output -> the value : 45 is exists in vector
	
		if (binary_search(ivec.begin(), ivec.end(), ival, [](int x, int y) {
			return abs(x) < abs(y);
			}))
			cout << "the value : " << ival << " is exists in vector\n";
		else
			cout << "the value : " << ival << " is not exists in vector\n";
		// the value : 45 is exists in vector
		// (-45) exists in the vector not 45.
	}
*/

/*
	------------------------------
	| structured binding / C++17 |
	------------------------------
	generally used for tuple-like classes
*/

/*
	int main()
	{
		using namespace std;
	
		int ar[] = { 3, 6, 9 };
		auto [x, y, z] = ar;
		cout << x << y << z << '\n';	// output -> 369
	
		x += 2;	// x is not a reference to ar[0]
		cout << ar[0] << '\n';			// output -> 3
	
		auto& [k, l, m] = ar;
		++k;	// k is a reference to ar[0] because of auto&
		cout << ar[0] << '\n';			// output -> 4
	
		ar[0] = ar[1] = ar[2] = 0;
		cout << x << y << z << '\n';	// output -> 569
		cout << k << l << m << '\n';	// output -> 000
	}
*/

/*
	int main()
	{
		using namespace std;
	
		int ar[] = { 3, 6, 9 };
		int ar2[] = { 1, 2, 3 };
	
		auto [x, y, _] = ar;
		auto [a, b, _] = ar2;
		// error C2374: '_': redefinition; multiple initialization
		// error C2386: '_': a symbol with this name already exists in the current scope
	}
*/

/*
	#include <string>
	
	struct Mystruct {
		int a, b;
		std::string str;
	};
	
	Mystruct foo()
	{
		return { 4, 6, "hello world" };
	}
	
	int main()
	{
		using namespace std;
	
		auto [a, b, name] = foo();
	
		cout << name << " " << a << " " << b << '\n';
		// output -> hello world 4 6
	}
*/

/*
	#include <string>
	
	class Myclass {
	public:
		Myclass(int x, int y, std::string s) : a(x), b(y), str(s) {}
	private:
		friend void func();
		int a, b;
		std::string str;
	};
	
	Myclass foo()
	{
		return { 4, 6, "hello world" };
	}
	
	void func()
	{
		auto [a, b, str] = foo();	// valid after C++17
	}
	
	int main()
	{
		using namespace std;
	
		auto [a, b, name] = foo();	// syntax error
		// because of data members of class is in private section.
		// Error E2845	cannot bind to non - public member "Myclass::a"
	}
*/

/*
	#include <string>
	
	struct Mystruct {
		int a, b;
		std::string str;
	};
	
	Mystruct foo()
	{
		return { 4, 6, "hello world" };
	}
	
	int main()
	{
		using namespace std;
	
		auto [a, b, str] = foo();
	
		auto fn = [=]() { return a + b; };
		// capturing structure binding object in lambda expressions
		// is not valid before C++20.
	}
*/

/*
	#include <array>
	#include <tuple>
	
	int main()
	{
		using namespace std;
	
		array<int, 3> ar{ 1, 5, 9 };
		auto [x, y, z] = ar;
		// array is applicable to tuple-like api
		//	1. tuple_element
		//	2. tuple_size
		//	3. get() function template
	
		tuple_element<1, decltype(ar)>::type;	// type int
		tuple_element_t<1, decltype(ar)>;		// type int
	
		using tp = tuple<int, double, long, long long>;
		tuple_element_t<2, tp>;					// type long
	
		using mypair = pair<int, double>;
	
		tuple_size<decltype(ar)>::value;	// size_t 3 unsigned int
		tuple_size<tp>::value;				// size_t 4 unsigned int
		tuple_size_v<mypair>;				// size_t 2 unsigned int
	
		tp x{0,2.3,10L, 11LL};
	
		get<0>(ar);
	}
*/

/*
	#include <string>
	
	class Person {
	public:
		Person(std::string name, std::string surname) :
			m_name{std::move(name)}, m_surname{std::move(surname)} {}
	
		std::string get_name() const { return m_name; }
		std::string get_surname() const { return m_surname; }
	
		std::string m_name;
		std::string m_surname;
	};
	
	template <>
	struct std::tuple_element<0, Person> {
		using type = std::string;
	};
	
	template <>
	struct std::tuple_element<1, Person> {
		using type = std::string;
	};
	
	template <>
	struct std::tuple_size<Person> {
		constexpr static std::size_t value = 2;
	};
	
	template <std::size_t n>
	auto get(const Person& p)
	{
		if constexpr (n == 0)
			return p.get_name();
		else if constexpr (n == 1)
			return p.get_surname();
	}
	
	int main()
	{
		using namespace std;
	
		Person per{ "Hello", "World" };
		auto [x, y] = per;
	
		std::cout << x << ' ' << y << '\n';
	}
*/

/*
	#include <type_traits>
	
	struct Mystruct {
		int a[5]{};
		double b[10]{};
	};
	
	int main()
	{
		Mystruct ms;
	
		auto [p1, p2] {ms};
	
		std::cout << sizeof(p1) << ' ' << sizeof(p2) << '\n';
		// output -> 20 80
	
		constexpr auto b = std::is_same_v<decltype(p1), int[5]>;
		// b is true
	
		// arrays are not decaying to pointers.
	}
*/

/*
	struct Mystruct {
		Mystruct() = default;
		Mystruct(const Mystruct&) {
			std::cout << "Mystruct copy ctor\n";
		}
	
		~Mystruct()
		{
			std::cout << "D";
		}
		int a{}, b{}, c{};
	};
	
	int main()
	{
		Mystruct ms;
	
		auto [x, y, z] = ms;
		// output -> Mystruct copy ctor
		// compiler will copy Mystruct class object then use its data members
		// in structured binding as structure binding objects.
	
		// output -> DD
		// because of Mystruct object has been copied, at the end of the main scope
		// they both will be destroyed.
	}
*/

/*
	struct Mystruct {
		int a[5]{};
		double b[10]{};
	};
	
	int main()
	{
		Mystruct ms;
	
		auto [p1, p2] {ms};
		// because of Mystruct will be copied.
		// p1 and p2 are the data members of copied Mystruct.
		// which are int[5] and double[10]
	}
*/

/*
	struct Mystruct {
		int a{}, b{};
	};
	
	int main()
	{
		Mystruct ms;
	
		// both are universal references and reference collapsion rule applied.
		auto&& [x, y] = ms;				// & - && -> &
		auto&& [a, b] = Mystruct{};		// && - && -> &&
	}
*/

/*
	struct Mystruct {
		char str[20]{ "hello" };
		int a{};
	};
	
	int main()
	{
		Mystruct ms;
	
		auto [a, s] = ms;
		// s's type is char[20]
		auto b = s;
		// b's type is char* because of array decays to pointer
	}
*/

/*
	------------------
	| decltype(auto) |
	------------------
*/

/*
	template <typename T>
	decltype(auto) foo(T& x)
	{
		return x;
		// x's type is int&
		// decltype(auto)'s type is same as decltype(x)'s type which is int&
	}
	
	decltype(auto) bar(int x)
	{
		return (x);		// Undefined Behaviour
		// x's type is int
		// decltype(x)'s type is int
		// decltype((x))'s type is int&
		// decltype(auto)'s type(return type) will be int&
	
		// after scope ends x will be destroyed,
		// and the reference to x will become dangling.
	}
	
	int main()
	{
		int y = 10;
		double l = 2.3;
	
		decltype(y);
		decltype(auto) x = y;
		decltype(auto) z = (y);
		decltype(auto) t = std::move(y);
	
		// when we apply decltype() to y, (y), std::move(y)
		// which type we get will be the type of decltype(auto)
		// decltype(y) -> int					-> decltype(auto) -- x -> int
		// decltype((y)) -> int&				-> decltype(auto) -- z -> int&
		// decltype(std::move(y)) -> int&&		-> decltype(auto) -- t -> int&&
	}
*/

/*
	------------------------------
	| std::bitset class template |
	------------------------------
	// generally used in embedded system and system programming 
*/

/*
	template <std::size_t n>	// NTTP(Non Type Template Parameter)
	class Bitset {
	
	};
	// zero cost abstraction will be applied.
*/

/*
	#include <bitset>
	
	int main()
	{
		using namespace std;
	
		bitset<8> bs;
		cout << bs << '\n';	// output -> 00000000
		// inserter function
	
		bitset<32> bs2(872345u);
		cout << bs2 << '\n';	// output -> 00000000000011010100111110011001
	
		bitset<8> bs3("11111111");
		cout << bs3 << '\n';	// output -> 11111111
	}
*/

/*
	#include <bitset>
	
	int main()
	{
		using namespace std;
	
		bitset<8> bs("11111111");
		cout << bs << '\n';	// output -> 11111111
	
		bs[7] = 0;
		cout << bs << '\n';	// output -> 01111111
	
		bs.operator[](4) = 0;
		// returns a proxy class which have
		// flip(), operator bool(), operator=() and operator~() member functions.
		cout << bs << '\n';	// output -> 01101111
	
		bs[6] = false;
		cout << bs << '\n';	// output -> 00101111
	
		bs[5] = bs[6];
		cout << bs << '\n';	// output -> 00001111
	
		bs[3] = bs.operator[](3).operator~();
		cout << bs << '\n';	// output -> 00000111
	
		// operator bool() function
		cout << bs[4] << '\n';								// output -> 0
		cout << bs.operator[](4).operator bool() << '\n';	// output -> 0
		// Those 2 lines are same
	}
*/

/*
	#include <bitset>
	
	int main()
	{
		using namespace std;
	
		bitset<16> bs("010101101010011");
	
		auto x = bs[5];
		// x's type is not bool -> its type is a proxy class type.
	
		auto y = bs[5].operator bool();
		// y's type is bool.
	}
*/

/*
	#include <bitset>
	
	int main()
	{
		using namespace std;
	
		constexpr bitset<8> bs1("00101000");
		constexpr bitset<8> bs2("00000000");
		constexpr bitset<8> bs3;
		constexpr bitset<8> bs4("11111111");
	
		// any() member function returns true if any bit is set.
		// returns false if all bits are not set.
		constexpr bool a = bs1.any();	// a -> true
		constexpr bool b = bs2.any();	// b -> false
		constexpr bool c = bs3.any();	// c -> false
	
		// none() member function returns false if any bit is set.
		// returns true if all bits are not set.
		constexpr bool d = bs1.none();	// d -> false
		constexpr bool e = bs2.none();	// e -> true
		constexpr bool f = bs3.none();	// f -> true
	
		// all() member function returns if all bits are set.
		constexpr bool g = bs4.all();	// g -> true
		constexpr bool h = bs1.all();	// h -> false
	
		// count() member function returns(size_t) how many bits are set.
		constexpr size_t set_bit_count1 = bs1.count();	// 2
		constexpr size_t set_bit_count2 = bs4.count();	// 8
		constexpr size_t set_bit_count3 = bs3.count();	// 0
	
		// set() member function returns *this
		// if no argument sets all bits.
		bitset<8> bs5;
		bitset<8> bs6("00001111");
		bs5.set();
		bs6.set();
		cout << bs5 << '\n';	// output -> 11111111
		cout << bs6 << '\n';	// output -> 11111111
	
		// set(size_t, bool = true)
		bitset<8> bs7("00001111");
		bs7.set(7, 1);
		bs7.set(6);
		bs7.set(0, 0);
		cout << bs7 << '\n';	// output -> 11001110
	
	
		bitset<8> bs8;	// defalt initialize all bits are not set.
		bs8 = ~bs8;
		//	bs8 = bs8.operator~();
		// Those 2 lines are same.
		cout << bs8 << '\n';	// output -> 11111111
	
		// reset() member function
		bs8.reset(3);
		cout << bs8 << '\n';	// output -> 11110111
		bs8.reset();
		cout << bs8 << '\n';	// output -> 00000000
	
		// flip() member function
		bitset<8> bs9;
		bs9.flip();
		cout << bs9 << '\n';	// output -> 11111111
		bs9.flip(3);
		cout << bs9 << '\n';	// output -> 11110111
	}
*/

/*
	#include <bitset>
	
	int main()
	{
		using namespace std;
	
		bitset<32> bx{ 87345u };
		bitset<32> by{ 803459344u };
	
		cout << bx << '\n';
		cout << by << '\n';
		cout << (bx & by) << '\n';
		// output ->
		//	00000000000000010101010100110001
		//	00101111111000111101000100010000
		//	00000000000000010101000100010000
	
		cout << bx << '\n';
		cout << by << '\n';
		cout << (bx | by) << '\n';
	
		// output ->
		//	00000000000000010101010100110001
		//	00101111111000111101000100010000
		//	00101111111000111101010100110001
	
		cout << bx << '\n';
		cout << by << '\n';
		cout << (bx ^ by) << '\n';
	
		// output ->
		//	00000000000000010101010100110001
		//	00101111111000111101000100010000
		//	00101111111000101000010000100001
	}
*/

/*
	#include <bitset>
	
	int main()
	{
		using namespace std;
	
		bitset<8> bx{ "00001111"};
	
		cout << bx << '\n';	// output -> 00001111
		bx <<= 3;
		cout << bx << '\n';	// output -> 01111000
	
		bx.set();
		cout << bx << 5 << '\n';	// output -> 111111115
	
		cout << (bx << 5) << '\n';	// output -> 11100000
		// operator<<(cout, bx.operator<<(5))
		// Those 2 lines are same.
	}
*/

/*
	#include <bitset>
	
	int main()
	{
		try
		{
			std::bitset<16> bs{ "1010001020100101" };
		}
		catch (const std::exception& ex)
		{
			std::cout << "exception caught : " << ex.what() << '\n';
			// output -> exception caught : invalid bitset char
		}
	}
*/

/*
	#include <bitset>
	#include <algorithm>
	
	int main()
	{
		using namespace std;
	
		bitset<16> bs{ 2362369 };
	
		auto str = bs.to_string();
	
		copy(str.begin(), str.end(), ostream_iterator<char>{cout, " "});
		// output -> 0 0 0 0 1 1 0 0 0 0 0 0 0 0 0 1
	}
*/

/*
	#include <bitset>
	#include <algorithm>
	
	int main()
	{
		using namespace std;
	
		bitset<16> bs{ "110100101001011" };
	
		auto ux = bs.to_ulong();
	
		cout << ux << '\n';	// output -> 26955
	}
*/

/*
	#include <bitset>
	#include <set>

	int main()
	{
		using namespace std;

		bitset<32> bs1{ "110100101001" };
		bitset<32> bs2{ "111100101001" };

		auto bs3 = bs1 == bs2;
		// operator==() and operator!=() are overloaded functions
		auto bs4 = bs1 < bs2;	// syntax error
		// operator<(), operator>(), operator<=()...
		// comparison functions are not overloaded.

		set<bitset<16>> myset;
		myset.insert(8712);	// syntax error
		// C2678 binary '<': no operator found which takes a left - hand operand of type 'const _Ty'
		// (or there is no acceptable conversion)

		// set containers 2nd template parameter is Comparator parameter
		// default comparator argument = less<bitset<16>>
	}
*/

/*
	#include <bitset>
	#include <set>

	int main()
	{
		using namespace std;

		auto fcmp = [](bitset<16> x, bitset<16> y) {
			return x.to_ulong() < y.to_ulong();
		};

		set<bitset<16>, decltype(fcmp)> myset;
		myset.insert(8172);
		myset.insert(3456);
		myset.insert(121);
		myset.insert(254);
		myset.insert(29054);

		for (auto bs : myset){
			cout << bs << ' ' << bs.to_ulong() <<  '\n';
		}
		// output ->
		//	0000000001111001 121
		//	0000000011111110 254
		//	0000110110000000 3456
		//	0001111111101100 8172
		//	0111000101111110 29054
	}
*/

/*
	---------------------------
	| dynamic storage objects |
	--------------------------- 
*/

/*
	// C code
	#include <cstdlib>
	
	struct Window {
		int a, b, c;
	};
	
	int main()
	{
		//	struct Window* pd = malloc(sizeof(struct Window));
		// legal in C -> implicit conversion from void* to Window*,  not legal in C++
	
		struct Window* pd = (Window*)malloc(sizeof(struct Window));
	
		if (!pd)	// controlling if we allocate a memory. If not returns a null pointer.
		{
			// we allocate the memory but now every data member of Window object
			// have indeterminate(garbage) values in it.
		}
	
		pd->a = 10;
		pd->b = 11;
		pd->c = 12;
	
		free(pd);
		// when our job is finished we use free() function
	}
*/

/*
	#include <string>
	
	int main()
	{
		using namespace std;
	
		string* p1 = new string;
		auto p2 = new string;
		// Those 2 lines are same
		// dynamic storage objects have been default initialized.
	
		new string{};	// value initialized
	
		auto p3 = new string(12, 'a');
		// 2 memory allocation happens in heap.
		// 1. storage of string object (memory allocation) [sizeof(string)]
		// 2. storage that string object holds ("aaaaaaaaaaaaa") (resource allocation)
	}
*/

/*
	class Myclass {
	public:
		Myclass()
		{
			std::cout << "default ctor\n";
		}
		Myclass(int)
		{
			std::cout << "Myclass(int)\n";
		}
		Myclass(int, int)
		{
			std::cout << "Myclass(int, int)\n";
		}
		~Myclass()
		{
			std::cout << "destructor\n";
		}
	private:
		unsigned char buf[1024]{};
	};
	
	void* operator new(size_t);	// operator new function
	// same signature as malloc() function
	// if succeeds returns a void*, if not throw a bad_alloc exception
	// we are NOT overloading new operator, we are overloading operator new() function.
	
	int main()
	{
		std::cout << "sizeof(Myclass) = " << sizeof(Myclass) << '\n';
		// output -> sizeof(Myclass) = 1024
	
		Myclass* p1 = new Myclass;
		// output -> default ctor	-> default initialization
		Myclass* p2 = new Myclass();
		// output -> default ctor	-> value initialization
		Myclass* p3 = new Myclass{};
		// output -> default ctor	-> value initialization
		Myclass* p4 = new Myclass{ 12 };
		// output -> Myclass(int)
		Myclass* p4 = new Myclass{ 12, 56 };
		// output -> Myclass(int, int)
	
		// No destructor have been called for p1, p2, p3, p4, p5
	
		// PSEUDO CODE
		// operator new function have been called for new Myclass; statement
		//		void* vp = operator new(sizeof(Myclass));	
				// operator new() function have been called.
		//		try {
		//			new (vp)Myclass;	-> ctor has been called.
		//		}
		//		catch (...) {
		//			operator delete(vp);
		//		}
	}
*/

/*
	#include <vector>
	
	class Myclass {
	public:
		Myclass()
		{
			std::cout << "default ctor\n";
		}
		~Myclass()
		{
			std::cout << "destructor\n";
		}
	private:
		unsigned char buf[1024 * 1024]{};
	};
	
	int main()
	{
		using namespace std;
	
		vector<void*> vec;
	
		int i;
	
		try
		{
			for (i = 0; i < 10000; ++i)
			{
				vec.push_back(operator new(sizeof(Myclass)));
			}
		}
		catch (const std::exception& ex)
		{
			std::cout << "exception caught : " << ex.what() << '\n';
			cout << "i = " << i << '\n';
		}
		// output ->
		//	exception caught : bad allocation
		//	i = 1864
		// operator new() function throw an exception
	}
*/

/*
	class Myclass {
	public:
		Myclass()
		{
			std::cout << "default ctor\n";
		}
		~Myclass()
		{
			std::cout << "destructor\n";
		}
	private:
		unsigned char buf[1024 * 1024]{};
	};
	
	int main()
	{
		using namespace std;
	
		auto p = new Myclass;
	
		delete p;
		// PSEUDO CODE for delete expression
		//		p->~Myclass();
		//		operator delete(p);
		// gave back the memory which have allocated with operator new()
	}
*/

/*
	#include <cstdlib>
	
	class Myclass {
	public:
		Myclass()
		{
			std::cout << "default ctor, this = " << this << '\n';
		}
		~Myclass()
		{
			std::cout << "destructor gave back resources. this = " << this << '\n';
		}
	private:
		unsigned char buf[1024]{};
	};
	
	void* operator new(std::size_t sz)
	{
		std::cout << "operator new function called for the size of : " << sz << '\n';
	
		void* vp = std::malloc(sz);
	
		if (!vp) {
			throw std::bad_alloc{};
		}
	
		std::cout << "the address of allocated block is : " << vp << '\n';
		return vp;
	}
	
	void operator delete(void* vp) noexcept
	{
		if (!vp) return;
		std::cout << "operator delete function called for the address of : " << vp << '\n';
		std::free(vp);
	}
	
	int main()
	{
		auto p = new Myclass;
		// output ->
		//	operator new function called for the size of : 1024
		//	the address of allocated block is : 00000296B1191AC0
		//	default ctor, this = 00000296B1191AC0
	
		std::cout << "object will be destroyed\n";
	
		delete p;
		// output ->
		//	destructor gave back resources. this = 00000296B1191AC0
		//	operator delete function called for the address of : 00000296B1191AC0
	
		std::cout << "main continiues..\n";
	}
*/

/*
	class Myclass {
	public:
		Myclass()
		{
			std::cout << "default ctor... this = " << this << '\n';
		}
		~Myclass()
		{
			std::cout << "destructor... this = " << this << '\n';
		}
	private:
		unsigned char buf[256]{};
	};
	
	int main()
	{
		using namespace std;
	
		Myclass* p = new Myclass[5];	// array new
		// output ->
		//	default ctor... this = 0167A814
		//	default ctor... this = 0167A914
		//	default ctor... this = 0167AA14
		//	default ctor... this = 0167AB14
		//	default ctor... this = 0167AC14
	
		delete[] p;						// array delete
		// output ->
		//	destructor... this = 0167AC14
		//	destructor... this = 0167AB14
		//	destructor... this = 0167AA14
		//	destructor... this = 0167A914
		//	destructor... this = 0167A814
	}
*/

/*
	class Myclass {
	public:
		Myclass()
		{
			std::cout << "default ctor... this = " << this << '\n';
		}
		~Myclass()
		{
			std::cout << "destructor... this = " << this << '\n';
		}
	private:
		unsigned char buf[256]{};
	};
	
	int main()
	{
		using namespace std;
	
		const Myclass* p1 = new const Myclass;
		auto p2 = new const Myclass;
		// Those 2 lines are same.
	}
*/

/*
	class Myclass {
	public:
		Myclass()
		{
			std::cout << "default ctor... this = " << this << '\n';
		}
		~Myclass()
		{
			std::cout << "destructor... this = " << this << '\n';
		}
	private:
		unsigned char buf[256]{};
	};
	
	int main()
	{
		using namespace std;
	
		Myclass* p = new Myclass;
	
		delete p;
		// p is dangling pointer now.
	
		delete p;	// double deletion
	
		Myclass m1;
		p = &m1;
	}
*/

/*
	// Mental model for how memory allocation throw a bad_alloc exception

	#include <cstdlib>

	using new_handler = void(*)();
	
	new_handler gfp = nullptr;
	
	new_handler get_new_handler()
	{
		return gfp;
	}
	new_handler set_new_handler(new_handler f)
	{
		auto temp_new_handler = gfp;
		gfp = f;
		return temp_new_handler;
	}
	
	void* operator new(size_t sz)
	{
		for (;;)
		{
			void* vp = malloc(sz);
			if (vp) {
				return vp;
			}
	
			auto fp = get_new_handler();
	
			// controlling if fp is nullptr or is there any other handler assigned to it.
			if (!fp) {
				throw std::bad_alloc{};
			}
			else
				fp();
			// if operator new has been failed and we already assigned another handler
			// our handler function will be called.
		}
	}
*/

/*
	#include <new>
	#include <vector>
	
	void first_handler()
	{
		static int cnt{};
		std::cout << "first_handler has been called for " << ++cnt << " times.\n";
	}
	
	struct Myclass {
		unsigned char buff[2048 * 2048]{};
	};
	
	int main()
	{
		//	std::set_new_handler(&first_handler);
	
		std::vector<Myclass*> myvec;
	
		try
		{
			for (int i = 0; i < 10000; ++i) {
				if (i % 100 == 0)
				{
					std::cout << i << '\n';
				}
				myvec.push_back(new Myclass);
			}
		}
		catch (const std::exception& ex)
		{
			std::cout << "exception caught: " << ex.what() << '\n';
		}
		// output ->
		//	0
		//	100
		//	200
		//	300
		//	400
		//	exception caught : bad allocation
	}
*/

/*
	a function saved to set_new_handler can do these.

	1) can run a code that makes possible to allocate a memory.
	2) can run some code then throw bad_alloc or 
		another exception that inherited from bad_alloc.
	3) can set nullptr -> set_new_handler(nullptr) -> 
		cause function to throw bad_alloc exception
	4) can set another handler -> set_new_handler(another_handler)
*/

/*
	// 2) can run some code then throw bad_alloc or 
	//	another exception that inherited from bad_alloc.

	#include <new>
	#include <vector>
	
	void first_handler()
	{
		static int cnt{};
		std::cout << "first_handler has been called for " << ++cnt << " times.\n";
		if (cnt == 5)
			throw std::bad_alloc{};
	}
	
	struct Myclass {
		unsigned char buff[2048 * 2048]{};
	};
	
	int main()
	{
		std::set_new_handler(&first_handler);
	
		std::vector<Myclass*> myvec;
	
		for (int i = 0; i < 10000; ++i) {
			if (i % 100 == 0)
			{
				std::cout << i << '\n';
			}
			myvec.push_back(new Myclass);
		}
		// output ->
		//	0
		//	100
		//	200
		//	300
		//	400
		//	first_handler has been called for 1 times.
		//	first_handler has been called for 2 times.
		//	first_handler has been called for 3 times.
		//	first_handler has been called for 4 times.
		//	first_handler has been called for 5 times.
		//	exception caught : bad allocation
	}
*/

/*
	// 3) can set nullptr -> set_new_handler(nullptr) -> 
	// cause function to throw bad_alloc exception

	#include <new>
	#include <vector>
	
	void first_handler()
	{
		static int cnt{};
		std::cout << "first_handler has been called for " << ++cnt << " times.\n";
		if (cnt == 3)
			std::set_new_handler(nullptr);
	}
	
	struct Myclass {
		unsigned char buff[2048 * 2048]{};
	};
	
	int main()
	{
		std::set_new_handler(&first_handler);
	
		std::vector<Myclass*> myvec;
	
		try
		{
			for (int i = 0; i < 10000; ++i) {
				if (i % 100 == 0)
				{
					std::cout << i << '\n';
				}
				myvec.push_back(new Myclass);
			}
		}
		catch (const std::exception& ex)
		{
			std::cout << "exception caught: " << ex.what() << '\n';
		}
		// output ->
		//	0
		//	100
		//	200
		//	300
		//	400
		//	first_handler has been called for 1 times.
		//	first_handler has been called for 2 times.
		//	first_handler has been called for 3 times.
		//	exception caught : bad allocation
	}
*/

/*
	//	4) can set another handler->set_new_handler(another_handler)
	
	#include <new>
	#include <vector>
	
	void second_handler()
	{
		static int cnt{};
		std::cout << "second_handler has been called for " << ++cnt << " times.\n";
		if (cnt == 3)
			std::set_new_handler(nullptr);
	}
	
	void first_handler()
	{
		static int cnt{};
		std::cout << "first_handler has been called for " << ++cnt << " times.\n";
		if (cnt == 3)
			std::set_new_handler(&second_handler);
	}
	
	struct Myclass {
		unsigned char buff[2048 * 2048]{};
	};
	
	int main()
	{
		std::set_new_handler(&first_handler);
	
		std::vector<Myclass*> myvec;
	
		try
		{
			for (int i = 0; i < 10000; ++i) {
				if (i % 100 == 0)
				{
					std::cout << i << '\n';
				}
				myvec.push_back(new Myclass);
			}
		}
		catch (const std::exception& ex)
		{
			std::cout << "exception caught: " << ex.what() << '\n';
		}
		// output ->
		//	0
		//	100
		//	200
		//	300
		//	400
		//	first_handler has been called for 1 times.
		//	first_handler has been called for 2 times.
		//	first_handler has been called for 3 times.
		//	second_handler has been called for 1 times.
		//	second_handler has been called for 2 times.
		//	second_handler has been called for 3 times.
		//	exception caught : bad allocation
	}
*/

/*
	-----------------------------
	| placement new expressions |
	-----------------------------
*/

/*
	#include <cstdlib>
	
	class Myclass {
	private:
		unsigned char buf[1024]{};
	};
	
	void* operator new(std::size_t, int x, int y)
	{
		std::cout << "x = " << x << " y = " << y << '\n';
		return malloc(1000);
	}
	
	int main()
	{
		auto p = new(111, 555)Myclass;
		// output -> x = 111 y = 555
		// we can send more information to operator new function overload.
	}
*/

/*
	// CAN NOT BE OVERLOADED
	//	void* operator new(std::size_t, void* vp)
	//	{
	//		return vp;
	//	}
	
	class Myclass {
	public:
		Myclass()
		{
			std::cout << "Myclass default ctor this = " << this << '\n';
		}
		~Myclass()
		{
	
		}
	private:
		unsigned char buf[1024]{};
	};
	
	int main()
	{
		unsigned char buffer[1024];
	
		std::cout << "address of buffer array = " <<  static_cast<void*>(buffer) << '\n';
	
		Myclass* p = new(buffer)Myclass;
		// in this statement we are sending &buffer as void* to operator new function.
		// void* operator new(std::size_t, void* vp) -> second param vp -> will be &buffer
	
		// because of operator new function returns vp(&buffer),
		// Myclass object will be constructed in the address that we want(in stack in this case).
	
		// output ->
		//	address of buffer array = 00000021FC2FF530
		//	Myclass default ctor this = 00000021FC2FF530
	
		delete p;	// Undefined behaviour
		// because of Myclass is constructed in stack[did not memory allocate with malloc]
		// because buffer arrays address is in stack.
		// calling operator delete() function will be undefined behaviour.
		// in this case we need to call ~Myclass() destructor by its name.
	
		p->~Myclass();
	}
*/

/*
	class Myclass {
		char mbuff[1024 * 1024];
	};
	
	int main()
	{
		using namespace std;
	
		new(nothrow) Myclass;
		// if it fails it is not throwing an exception, it retuns a nullptr
	
		Myclass* p = new(nothrow) Myclass;
	
		if (!p) {
			//...
		}
	}
*/

/*
	-----------------------------------------------------------------------------------
	| overloading operator new() and operator delete() functions as a member function |
	-----------------------------------------------------------------------------------
*/

/*
	class Myclass {
	public:
		void* operator new(std::size_t n)
		{
			this;
			// using this keyword is a syntax error -> static member function
		}
	private:
		char buf[1024]{};
	};
	
	int main()
	{
		auto p = new Myclass;
		// if operator new() function was not a static member function
		// it would need a Myclass object to call that non-static member function.
		// but we need to allocate memory before creating Myclass object.
		// that is why operator new() function is by default a static member function.
	}
*/

/*
	class Myclass {
	public:
		static void* operator new(std::size_t n)
		{
			return nullptr;
		}
		// we can also use static keyword in the function decleration of definition.
	private:
		char buf[1024]{};
	};
	
	int main()
	{
		auto p = new Myclass;
	}
*/

/*
	#include <cstdlib>
	
	class Myclass {
	public:
		Myclass()
		{
			std::cout << "default ctor this = " << this << '\n';
		}
	
		~Myclass()
		{
			std::cout << "destructor this = " << this << '\n';
		}
	
		static void* operator new(std::size_t n)
		{
			std::cout << "Myclass::operator new\n";
			std::cout << "n = " << n << '\n';
			void* vp = std::malloc(n);
	
			if (!vp) {
				throw std::bad_alloc{};
			}
	
			std::cout << "address : " << vp << '\n';
			return vp;
		}
	
		static void operator delete(void* vp)
		{
			std::cout << "Myclass::operator delete vp = " << vp << '\n';
			std::free(vp);
		}
	
	private:
		char buf[1024]{};
	};
	
	int main()
	{
		Myclass* p = new Myclass;
		delete p;
		//	Myclass::operator new
		//	n = 1024
		//	address : 01034B08
		//	default ctor this = 01034B08
		//	destructor this = 01034B08
		//	Myclass::operator delete vp = 01034B08
	}
*/

/*
	#include <cstdlib>
	
	class Myclass {
	public:
		static void* operator new(std::size_t n)
		{
			std::cout << "Myclass::operator new\n";
			void* vp = std::malloc(n);
	
			if (!vp) {
				throw std::bad_alloc{};
			}
			return vp;
		}
		static void operator delete(void* vp)
		{
			std::cout << "Myclass::operator delete\n";
			std::free(vp);
		}
	
	private:
		char buf[1024]{};
	};
	
	int main()
	{
		// even if our class has an operator new() or operator delete() static member functions
		// we can call standart libraries functions by using ::(unary scope resolution operator).
		Myclass* p = ::new Myclass;
		::delete p;
		// output -> empty
	}
*/