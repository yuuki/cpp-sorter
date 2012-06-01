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
    std::vector<int> v = {32, 71, 12, 45, 26, 80, 53, 33}; //C++11から配列的な初期化構文が使えるようになった
    std::cout << "original:\n";
    print(v);

    std::cout << "insertion_sort:\n";
    mysorter::insertion_sort(v.begin(), v.end());
    print(v);

    std::cout << "insertion_sort: greater\n";
    mysorter::insertion_sort(v.begin(), v.end(), std::greater<int>());
    print(v);

    std::cout << "quick_sort:\n";
    mysorter::quick_sort(v.begin(), v.end());
    print(v);

    std::cout << "quick_sort: greater\n";
    mysorter::quick_sort(v.begin(), v.end(), std::greater<int>());
    print(v);

    std::cout << "quick_sort2:\n";
    mysorter::quick_sort2(v.begin(), v.end());
    print(v);

    return 0;
}
