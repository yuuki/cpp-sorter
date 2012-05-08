#include <vector>
#include <iostream>

#include "selection_sort.hpp"

int main() {
    std::vector<int> v = {32, 71, 12, 45, 26, 80, 53, 33}; //C++11から配列的な初期化構文が使えるようになった

    SelectionSorter sorter;
    sorter.set_values(v);
    sorter.sort();
    v = sorter.get_values();

    std::cout << "myvector contains:";
    for (auto const i : v) { // Range-based for: C++11からfor each的なことができるようになった
        std::cout << " " << i;
    }
    std::cout << "\n";

    return 0;
}
