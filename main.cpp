#include <vector>
#include <iostream>
#include <functional>

#include "sorter.hpp"

template<class T>
void print(std::vector<T> v) {
    for (auto const i : v) {
        std::cout << " " << i;
    }
    std::cout << "\n";
}

int main() {
    std::vector<int> a = {30, 40, 10, 70, 20, 90, 50, 60, 80}; //C++11から配列的な初期化構文が使えるようになった
    std::cout << "original:\n";
    print(a);

    std::cout << "insertion_sort:\n";
    auto b(a);
    mysorter::insertion_sort(b.begin(), b.end());
    print(b);

    std::cout << "insertion_sort: greater\n";
    auto c(a);
    mysorter::insertion_sort(c.begin(), c.end(), std::greater<int>());
    print(c);

    std::cout << "quick_sort:\n";
    auto d(a);
    mysorter::quick_sort(d.begin(), d.end());
    print(d);

    std::cout << "quick_sort: greater\n";
    auto e(a);
    mysorter::quick_sort(e.begin(), e.end(), std::greater<int>());
    print(e);

    std::cout << "quick_sort2:\n";
    auto f(a);
    mysorter::quick_sort2(f.begin(), f.end());
    print(f);

    std::cout << "heap_sort:\n";
    auto g(a);
    mysorter::heap_sort(g.begin(), g.end());
    print(g);

    return 0;
}
