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

    std::cout << "selection_sort:\n";
    mysorter::selection_sort(v);
    print(v);

    std::cout << "selection_sort: greater\n";
    mysorter::selection_sort(v, std::greater<int>());
    print(v);

    return 0;
}
