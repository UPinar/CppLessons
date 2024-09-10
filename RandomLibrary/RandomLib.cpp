#include <iostream>
#include <random>

/*
    ------------------
    | random library |
    ------------------
*/

/*
    int main()
    {
        using namespace std;
    
        std::cout << typeid(mt19937).name() << '\n';
        // output -> class std::mersenne_twister_engine<unsigned int,32,624,
        //           397,31,2567483615,11,4294967295,7,2636928640,15,4022730752,18,1812433253>
    
        // mt19937 is a template specialization created with those template arguments above.
        // if 1 of those NTTP is changed we will have a different template specialization.
    }
*/

/*
    int main()
    {
        using namespace std;
    
        mt19937 eng;
        // functor class (have an operator call function)
    
        for (int i = 0; i < 5; ++i){
            cout << eng() << '\n';
        }
        // output ->
        //  3499211612
        //  581869302
        //  3890346734
        //  3586334585
        //  545404204
    }
*/

/*
    // https://en.cppreference.com/w/cpp/numeric/random/mersenne_twister_engine
    
    // The Nth consecutive invocation of a default-constructed engine 
    // is required to produce the following value:
    // 10000 	std::mt19937 	    4123659995
    // 10000 	std::mt19937_64 	9981545732273789042
    
    int main()
    {
        using namespace std;
    
        mt19937 eng;
    
        for (int i = 0; i < 10000 - 1; ++i) {
            eng();
        }
    
        cout << eng() << '\n';
        // output -> 4123659995
    
        mt19937_64 eng2;
    
        for (int i = 0; i < 10000 - 1; ++i) {
            eng2();
        }
    
        cout << eng2() << '\n';
        // output -> 9981545732273789042
    }
*/

/*
    int main()
    {
        using namespace std;
    
        mt19937 eng;
        cout << sizeof(eng) << '\n';    // output -> 5000 byte
        // its size is too big. Better not copy!
    }
*/

/*
    #include <bitset>
    
    int main()
    {
        using namespace std;
    
        mt19937 eng;
    
        for (int i = 0; i < 5; ++i) {
            cout << bitset<32>(eng()) << '\n';
        }
        // output ->
        //  11010000100100011011101101011100
        //  00100010101011101001111011110110
        //  11100111111000011111101011101110
        //  11010101110000110001111101111001
        //  00100000100000100011010100101100
    
        // what random engine does is creating bits.
        // creating distribution using those bits is different classes job.
    }
*/

/*
    int main()
    {
        using namespace std;
    
        mt19937 eng;
        mt19937 eng2{ 5489 };
        // Those 2 objects are same
    
        eng.default_seed; // static data member of the class -> 5489U
    }
*/

/*
    int main()
    {
        using namespace std;
    
        mt19937 eng;
        mt19937 eng2{ 5489 };
        // Those 2 objects are same
    
        eng.default_seed; // static data member of the class -> 5489U
    
        mt19937 eng3{ 87345345u };
        // we can use our seed value.
    
        eng3.seed(34985u);
        // we can change seed value after we construct the object
        // with seed() member function
    }
*/

/*
    int main()
    {
        using namespace std;
    
        mt19937 eng;
        // every member in mt19937 template specialization chain
        // is known before it has been created.
    
        eng.discard(9999);
        // discard() member function is used for discarding first n elements in chain
    
        std::cout << eng() << '\n'; // output -> 4123659995
        // because of 10000th element in chain is guaranteed to be 4123659995
        // when we discard first 9999 element we start with 10000th element.
    }
*/

/*
    int main()
    {
        using namespace std;
    
        // static member functions min() and max()
        std::cout << mt19937::min() << '\n';
        // output -> 0
        std::cout << mt19937::max() << '\n';
        // output -> 4294967295 (4 byte int max)
        std::cout << mt19937_64::max() << '\n';
        // output -> 18446744073709551615 (8 byte int max)
    }
*/

/*
    void checkStates(std::mt19937& first, std::mt19937& second)
    {
        if (first == second) {
            std::cout << "same states\n";
        }
        else {
            std::cout << "different states\n";
        }
    }
    
    int main()
    {
        using namespace std;
    
        // all random number generator engines have their own state
        mt19937 eng1;
        mt19937 eng2;
        checkStates(eng1, eng2);    // output -> same states
    
        auto x = eng1();
        checkStates(eng1, eng2);    // output -> different states
    
        x = eng2();
        checkStates(eng1, eng2);    // output -> same states
    }
*/

/*
    #include <sstream>
    
    // serialization & deserialization
    int main()
    {
        using namespace std;
    
        mt19937 eng;
    
        //cout << eng << '\n';
        // outputs engines state
    
        stringstream ss;
        ss << eng;
        // holding random number generators state in stringstream object
    
        for (int i = 0; i < 5; ++i) {
            cout << eng() << '\n';
        }
        // output ->
        //  3499211612
        //  581869302
        //  3890346734
        //  3586334585
        //  545404204
    
        cout << "------------------------\n";
    
        ss >> eng;
        // transfering the holded state back
    
        for (int i = 0; i < 5; ++i) {
            cout << eng() << '\n';
        }
        // output ->
        //  3499211612
        //  581869302
        //  3890346734
        //  3586334585
        //  545404204
    }
*/

/*
    int main()
    {
        using namespace std;
    
        random_device rd;
        // if the compiler is supporting generated numbers
        // will be non deterministic (every time they will be different numbers)
    
        for (int i = 0; i < 5; ++i) {
            cout << rd() << '\n';
        }
        // output 1 ->
        //  1438040552
        //  2695426187
        //  4255321613
        //  1139278288
        //  3156343251
    
        // output 2 ->
        //  4280776851
        //  2054476128
        //  283726298
        //  4112478565
        //  1362087684

        cout << rd.entropy() << '\n';   // output -> 32
        // if class generates deterministic numbers
        // entropy() member function will return 0
        // else class generates non-deterministic numbers
    }
*/

/*
    int main()
    {
        using namespace std;
    
        mt19937 eng{ random_device{}() };
        // everytime we start our program
        // random number generator will be seeded with a non-deterministic value
        // created by random_device{} objects operator call function
    
        for (int i = 0; i < 5; ++i) {
            cout << eng() << '\n';
        }
        // output 1 ->
        //  2398702563
        //  672145557
        //  1745659077
        //  2317362023
        //  2318765360
    
        // output 2 ->
        //  1654029671
        //  175998404
        //  1613595889
        //  3568356961
        //  1466122656
    }
*/

/*
    #include <chrono>
    
    int main()
    {
        using namespace std;
        using namespace std::chrono;
    
        cout << system_clock::now().time_since_epoch().count() << '\n';
        // returns non-deterministic value depends on the time change
    
        mt19937 eng(system_clock::now().time_since_epoch().count());
    
        for (int i = 0; i < 5; ++i) {
            cout << eng() << '\n';
        }
        // output 1 ->
        //  17000718590397243
        //  3788172805
        //  1539693512
        //  1856865784
        //  2980141487
        //  4241980549
    
        // output 2 ->
        //  17000718995830373
        //  1425865738
        //  900343488
        //  1862265618
        //  4175564836
        //  3258735091
    }
*/

/*
    int main()
    {
        using namespace std;
    
        // we want to create backgammon dices
    
        mt19937 eng;
        minstd_rand mrand;
    
        uniform_int_distribution<int> dist{ 1,6 };
        // uniform_int_distribution<> dist{ 1,6 }; -> default argument int
        // uniform_int_distribution dist{ 1,6 };    // CTAD(class template argument deduction)
        // Those 3 lines are same
    
        dist(eng);
        dist(mrand);
    
        for (int i = 0; i < 100; ++i) {
            dist(eng);
        }
    }
*/

/*
    #include <map>
    
    int main()
    {
        using namespace std;
    
        mt19937 eng;
        map<int, int> cmap;
    
        uniform_int_distribution<int> dist{ 1, 6 };
    
        for (int i = 0; i < 10'000'000; ++i) {
            ++cmap[dist(eng)];
        }
    
        // if the count of the keys in map are close to each other
        // it is declaring the quality of the distribution
    
        for (const auto& [dice, count] : cmap) {
            cout << dice << " - " << count << '\n';
        }
        // output ->
        //  1 - 1666708
        //  2 - 1666465
        //  3 - 1667497
        //  4 - 1664921
        //  5 - 1667321
        //  6 - 1667088
    }
*/

/*
    #include <iomanip>
    
    int main()
    {
        // temperature values as uniform distribution
        using namespace std;
    
        mt19937 eng;
        uniform_real_distribution<double> dist{ 10.0, 45.0 };
    
        cout << fixed << setprecision(2) << '\n';
        for (int i = 0; i < 10; ++i) {
            cout << dist(eng) << '\n';
        }
        // output ->
        //  14.74
        //  39.23
        //  43.91
        //  17.74
        //  20.79
        //  29.15
        //  16.59
        //  44.75
        //  44.88
        //  43.87
    }
*/

/*
    // check histogram.png
    #include <map>
    #include <fstream>
    #include <iomanip>
    #include <string>
    
    int main()
    {
        using namespace std;
    
        mt19937 eng;
        normal_distribution<> dist{ 50., 5. };
    
        map<int, int> cmap;
    
        std::ofstream ofs{ "out.txt" };
    
        if (!ofs) {
            std::cerr << "couldn't create out.txt\n";
            exit(EXIT_FAILURE);
        }
    
        constexpr int n = 1'000'000;
    
        ofs << fixed << setprecision(4);
        for (int i = 0; i < n; ++i){
            ++cmap[static_cast<int>(round(dist(eng)))];
        }
    
        ofs << setfill('0');
        for (const auto& [key, count] : cmap) {
            ofs << setw(2) << key << " " << string(count / 1000, '*') << '\n';
        }
    }
*/

/*
    int main()
    {
        using namespace std;
        normal_distribution<> dist{ 70., 10. };
    
        normal_distribution<> dist2(dist.param());
        // using param() member function to send other
        // normal_distribution objects constructor.
    
        dist.mean();    // arithmetic mean
        // first parameter of the normal_distribution objects constructor.
        dist.sigma();   // standard deviation
        // second parameter of the normal_distribution objects constructor.
    
    
        uniform_int_distribution<> dist3{ 20,70 };
    
        dist3.min();
        // first parameter of the uniform_int_distribution objects constructor.
        dist3.max();
        // second parameter of the uniform_int_distribution objects constructor.
    }
*/

/*
    #include <map>
    
    int main()
    {
        using namespace std;
    
        mt19937 eng;
        discrete_distribution<int> dist{ 10, 10, 10, 10, 10, 13 };
    
        map<int, int> cmap;
    
        for (int i = 0; i < 1'000'000; ++i) {
            ++cmap[dist(eng)];
        }
    
        for (const auto& [val, count] : cmap) {
            cout << val << " " << count << '\n';
        }
        // output ->
        //  0 158650
        //  1 158611
        //  2 159020
        //  3 158890
        //  4 158573
        //  5 206256
    }
*/

/*
    #include <map>
    
    int main()
    {
        // tricked dice
        using namespace std;
    
        mt19937 eng;
        discrete_distribution<int> dist{ 0, 10, 10, 10, 10, 10, 11 };
    
        map<int, int> cmap;
    
        for (int i = 0; i < 1'000'000; ++i) {
            ++cmap[dist(eng)];
        }
    
        for (const auto& [val, count] : cmap) {
            cout << val << " " << count << '\n';
        }
        // output ->
        //  1 163789
        //  2 163732
        //  3 164235
        //  4 164140
        //  5 163863
        //  6 180241
    }
*/

/*
    #include <map>
    #include <iomanip>
    
    int main()
    {
        using namespace std;
    
        mt19937 eng;
    
        double a[12] = { 10, 10, 11, 10, 10, 11, 10, 10, 11, 10, 10, 11 };
        // months
    
        discrete_distribution<> dist{ begin(a), end(a) };
    
        map<int, int> cmap;
    
        for (int i = 0; i < 10'000'000; ++i) {
            ++cmap[dist(eng)];
        }
    
        cout << setfill('0');
        for (const auto& [val, count] : cmap) {
            cout << setw(2) << val + 1 << " " << count << '\n';
        }
        // output ->
        //  01 805604
        //  02 807578
        //  03 887043
        //  04 807440
        //  05 807375
        //  06 888123
        //  07 803674
        //  08 806384
        //  09 886595
        //  10 807402
        //  11 806618
        //  12 886164
    }
*/

/*
    void func(auto& distObj)
    {
        std::mt19937 eng;
        int count{};
        for (int i = 0; i < 10'000'000; ++i) {
            count += distObj(eng) ? 1 : 0;
        }
        std::cout << count << '\n';
    }
    
    int main()
    {
        using namespace std;
    
        bernoulli_distribution dist{ 0.5 };
        // 0.5 is uniform distribution
        func(dist); // output -> 499956
    
        bernoulli_distribution dist2{ 0.8 };
        func(dist2); // output -> 800001
    }
*/

/*
    ----------------------------------------------------
    | algorithms related with random number generators |
    ----------------------------------------------------
*/

/*
    --------------
    | generate() |
    --------------
*/

/*
    #include <algorithm>
    #include <vector>
    
    int main()
    {
        using namespace std;
    
        vector<int> ivec(15);
    
        mt19937 eng;
        uniform_int_distribution dist{ 1940, 2000 };
        generate(ivec.begin(), ivec.end(), [&] {return dist(eng); });
    
    
        generate(ivec.begin(), ivec.end(), [=] {return dist(eng); });   // syntax error
        // Error -> expression having type 'const std::uniform_int_distribution<int>' would lose some const -
        // volatile qualifiers in order to call 'int std::uniform_int<_Ty>::operator ()<const std::mt19937>(_Engine &)'
    
        generate(ivec.begin(), ivec.end(), [=]()mutable {return dist(eng); });
        // solved the error about but it is not good thing to copy eng object which is 5000bytes
    
        for (auto val : ivec)
            cout << val << ' ';
        // output -> 2000 1998 2000 1998 1999 1949 1984 1999 1999 1998 1946 1969 1988 1988 1958
    }
*/

/*
    #include <algorithm>
    #include <list>
    #include "nutility.h"
    
    template <typename ForIter, typename Func>
    ForIter Generate(ForIter beg, ForIter end, Func f)
    {
        while (beg != end) {
            *beg++ = f();
        }
        return end;
    }
    
    int main()
    {
        using namespace std;
    
        list<string> slist(10);
    
        generate(slist.begin(), slist.end(), &rtown);
    
        for (const auto& town : slist)
            cout << town << '\n';
        // output ->
        //  aydin
        //  mus
        //  kirklareli
        //  van
        //  kilis
        //  diyarbakir
        //  kahramanmaras
        //  tunceli
        //  sakarya
        //  karaman
    }
*/

/*
    ----------------
    | generate_n() |
    ----------------
*/

/*
    #include <algorithm>
    #include <vector>
    
    int main()
    {
        using namespace std;
    
        mt19937 eng;
        uniform_real_distribution dist{ 10.0, 20.0 };
        vector<double> dvec;
    
        generate_n(back_inserter(dvec), 100, [&] {return dist(eng); });
    }
*/

/*
    -------------
    | shuffle() |
    -------------
*/

/*
    #include <algorithm>
    #include <vector>
    #include "nutility.h"
    
    int main()
    {
        using namespace std;
    
        vector<int> ivec{ 1, 3, 4, 2, 5, 6 };
        print(ivec);    // output -> 1 3 4 2 5 6
    
        mt19937 eng;
        shuffle(ivec.begin(), ivec.end(), eng);
        // no copying eng in here because 3rd parameter is universal reference
        // sending lvalue parameter will become &
        // sending rvalue parameter will become &&
        print(ivec);    // output -> 5 1 2 3 6 4
    }
*/

/*
    #include <algorithm>
    #include <string>
    
    int main()
    {
        using namespace std;
    
        string str{ "hello world" };
        mt19937 eng{ random_device{}()};
    
        for (int i = 0; i < 5; ++i) {
            cout << "|" << str << "|\n";
            shuffle(str.begin(), str.end(), eng);
        }
        // output ->
        //  |hello world|
        //  |ldwrl leoho|
        //  |lhe olldowr|
        //  |hw rodllleo|
        //  |olwedl rhol|
    }
*/

/*
    ------------------
    | sample() C++17 |
    ------------------
*/

/*
    #include <algorithm>
    #include <iterator>
    #include <string>
    
    int main()
    {
        std::string in{ "ABCDEFGHIJK" }, out;
    
        std::sample(in.begin(), in.end(), std::back_inserter(out), 4,
            std::mt19937{ std::random_device{}() });
    
        std::cout << "Four random letters out of " << in << " : " << out << '\n';
        // output -> Four random letters out of ABCDEFGHIJK : BGHI
    }
*/

/*
    #include <algorithm>
    #include <string>
    #include <vector>
    #include <iterator>
    
    int main()
    {
        using namespace std;
        const vector<string> months = { "January", "February", "March", "April", "May", "June",
            "July", "August", "September", "October", "November", "December" };
    
        int n = 5;
    
        std::sample(months.begin(), months.end(), ostream_iterator<string>{cout, " "}, n, mt19937{ random_device{}() });
        // output -> February August September October December
    }
*/