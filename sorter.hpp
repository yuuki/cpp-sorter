#ifndef __SORTER_HPP__
#define __SORTER_HPP__

#include <algorithm>
#include <vector>
#include <functional>

namespace mysorter {

    // Selection Sort
    template <
        class RandomAccessIterator,
        class Predicate = std::less< typename std::iterator_traits<RandomAccessIterator>::value_type >
    >
    void selection_sort(RandomAccessIterator first, RandomAccessIterator last, 
            Predicate pred = std::less< typename std::iterator_traits<RandomAccessIterator>::value_type>())
    {
        for (auto ri = first + 1; ri != last; ++ri) {
            auto const val = *ri;
            auto const pos = std::find_if(first, ri, bind1st(pred, val));
            for (auto it = ri - 1; it >= pos; --it) {
                *(it + 1) = *it;
            }
            *pos = val;
        }

    };

    // 
    namespace _impl_quick_sort {

        template < class RandomAccessIterator, class Predicate >
        static void qsort(RandomAccessIterator left, RandomAccessIterator right, Predicate pred)
        {
            if (left < right) {
                auto pivot = left + std::distance(left, right) / 2;
                std::iter_swap(pivot, right);
                auto store = left;
                for (auto it = left; it < right; ++it) {
                    if (pred(*it, *right)) {
                        std::iter_swap(store, it);
                        ++store;
                    }
                }
                std::iter_swap(store, right);
                qsort(left, store - 1, pred);
                qsort(store + 1, right, pred);
            }
        }
    }

    template <
        class RandomAccessIterator,
        class Predicate = std::less< typename std::iterator_traits<RandomAccessIterator>::value_type >
    >
    static void quick_sort(RandomAccessIterator first, RandomAccessIterator last,
            Predicate pred = std::less< typename std::iterator_traits<RandomAccessIterator>::value_type>())
    {
        _impl_quick_sort::qsort<RandomAccessIterator, Predicate>(first, last - 1, pred);
    }

}

#endif
