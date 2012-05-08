#ifndef __SELECTION_SORT_HPP__
#define __SELECTION_SORT_HPP__

#include "sorter.hpp"

class SelectionSorter : public Sorter {
public:
    virtual void sort() override;
    // virtual ~SelectionSorter() = default;
private:
    static void insert(std::vector<int>&, const int&);
};

void SelectionSorter::sort() {
    std::vector<int>& v = this->values;
    int size = v.size();
    for (int i = 1; i < size; ++i) {
        SelectionSorter::insert(v, i);
    }
    return;
}

void SelectionSorter::insert(std::vector<int>& v, const int& pos) { // 値渡しより参照渡し
    const int val = v[pos];
    int i = pos - 1;
    while (i >= 0 and v[i] > val) {
        v[i + 1] = v[i];
        --i;
    }
    v[i + 1] = val;
    return;
}

#endif
