#ifndef __SORTER_HPP__
#define __SORTER_HPP__

#include <algorithm>
#include <vector>
#include <functional>

namespace mysorter {

    template<class T, class Predicate>
    void selection_sort(std::vector<T>& values, const Predicate pred)
    {
        for (auto ri = values.begin() + 1; ri != values.end(); ++ri) {
            auto const val = *ri;
            auto const pos = std::find_if(values.begin(), ri, bind1st(pred, val));
            for (auto it = ri - 1; it >= pos; --it) {
                *(it + 1) = *it;
            }
            *pos = val;
        }

    };

    template<class T>
    void selection_sort(std::vector<T>& values)
    {
        selection_sort(values, std::less<T>());
    };

}

#endif
