#ifndef __SORTER_HPP__
#define __SORTER_HPP__

#include <algorithm>
#include <vector>
#include <functional>

namespace mysorter {

    //////////// Insertion Sort //////////////

    template <
        class RandomAccessIterator,
        class Predicate = std::less< typename std::iterator_traits<RandomAccessIterator>::value_type >
    >
    void insertion_sort(RandomAccessIterator first, RandomAccessIterator last, 
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


    //////////// Quick Sort //////////////

    namespace _impl_quick_sort {

        template < class RandomAccessIterator, class Predicate >
        static RandomAccessIterator partition(RandomAccessIterator left, RandomAccessIterator right, const RandomAccessIterator pivot, const Predicate pred)
        {
            std::iter_swap(pivot, right);
            auto store = left;
            for (auto it = left; it < right; ++it) {
                if (pred(*it, *right)) {
                    std::iter_swap(store, it);
                    ++store;
                }
            }
            std::iter_swap(store, right);
            return store;
        }

        template < class RandomAccessIterator, class Predicate >
        static void qsort(RandomAccessIterator left, RandomAccessIterator right, Predicate pred)
        {
            if (left >= right) return;

            auto pivot = left + std::distance(left, right) / 2;
            auto store = partition(left, right, pivot, pred);

            qsort(left, store - 1, pred);
            qsort(store + 1, right, pred);
        }

        template < class RandomAccessIterator, class Predicate >
        static void qsort2(RandomAccessIterator left, RandomAccessIterator right, const int min_size, Predicate pred)
        {
            if (left >= right) return;

            auto pivot = left + std::distance(left, right) / 2;
            auto store = partition(left, right, pivot, pred);

            if (std::distance(left, store - 1) <= min_size) {
                insertion_sort(left, store, pred);
            } else {
                qsort2(left, store - 1, min_size, pred);
            }
            if (std::distance(store + 1, right) <= min_size) {
                insertion_sort(store + 1, right + 1, pred);
            } else {
                qsort2(store + 1, right, min_size, pred);
            }
        }

    }

    template <
        class RandomAccessIterator,
        class Predicate = std::less< typename std::iterator_traits<RandomAccessIterator>::value_type >
    >
    static void quick_sort(RandomAccessIterator first, RandomAccessIterator last,
            Predicate pred = std::less< typename std::iterator_traits<RandomAccessIterator>::value_type >())
    {
        _impl_quick_sort::qsort<RandomAccessIterator, Predicate>(first, last - 1, pred);
    }


    //////////// Quick Sort using Insertion Sort towards parts of array. //////////////
    template <
        class RandomAccessIterator,
        class Predicate = std::less< typename std::iterator_traits<RandomAccessIterator>::value_type >
    >
    static void quick_sort2(RandomAccessIterator first, RandomAccessIterator last,
            Predicate pred = std::less< typename std::iterator_traits<RandomAccessIterator>::value_type >())
    {
        const int min_size = 5;
        _impl_quick_sort::qsort2<RandomAccessIterator, Predicate>(first, last - 1, min_size, pred);
    }


    /////////// Heap Sort ///////////

}

#endif
