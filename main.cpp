#include <vector>
#include <iostream>
#include <functional>

#include "sorter.hpp"

template<typename T>
void print(std::vector<T> v) {
    for (auto const i : v) {
        std::cout << " " << i;
    }
    std::cout << "\n";
}

int main() {
    using namespace mysorter;

    std::vector<int> a = {30, 40, 10, 70, 20, 90, 50, 60, 80};
    std::cout << "original:\n";
    print(a);

    std::cout << "default sort:\n";
    auto z(a);
    sort(z.begin(), z.end());
    print(z);

    std::cout << "insertion_sort:\n";
    auto b(a);
    sort(insertion(), b.begin(), b.end());
    print(b);

    std::cout << "insertion_sort: greater\n";
    auto c(a);
    sort(insertion(), c.begin(), c.end(), std::greater<int>());
    print(c);

    std::cout << "quick_sort:\n";
    auto d(a);
    sort(quick(), d.begin(), d.end());
    print(d);

    std::cout << "quick_sort: greater\n";
    auto e(a);
    sort(quick(), e.begin(), e.end(), std::greater<int>());
    print(e);

    std::cout << "quick_sort2:\n";
    auto f(a);
    sort(quick2(), f.begin(), f.end());
    print(f);

    std::cout << "heap_sort:\n";
    auto g(a);
    sort(heap(), g.begin(), g.end());
    print(g);

    std::cout << "shell_sort:\n";
    auto h(a);
    sort(shell(), h.begin(), h.end());
    print(h);

    std::cout << "shell_sort_with_tbb:\n";
    auto i(a);
    sort(shell_tbb(), i.begin(), i.end());
    print(i);

    return 0;
}
