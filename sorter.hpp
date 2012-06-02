#ifndef __SORTER_HPP__
#define __SORTER_HPP__

#include <algorithm>
#include <vector>
#include <functional>

#ifdef ENABLE_SORTER_LOG
#include <iostream>
#define LOG(expr) (std::clog << "# " << __func__ << ": " << expr << std::endl)
#define LOG_FOR(I,A,B) (for (auto I = A; I < B; ++I) {std::cout << *I << " ";} std::cout << std::endl;)
#else
#define LOG(expr) ((void)0)
#define LOG_FOR(I,A,B) ((void)0)
#endif

namespace mysorter {

    // struct insertion_sort_tag{};
    // struct quick_sort_tag{};
    // struct quick_sort2_tag{};
    // struct heap_sort_tag{};

    // template <class RandomAccessIterator, class tag>
    // static void sort<RandomAccessIterator, tag>

    // Template Alias (C++11)
    template <class T>
    using value_t = typename std::iterator_traits<T>::value_type;

    //////////// Insertion Sort //////////////

    template <class RandomAccessIterator, class Predicate = std::less< value_t<RandomAccessIterator> >>
    void insertion_sort(RandomAccessIterator first, RandomAccessIterator last,
            Predicate pred = std::less< value_t<RandomAccessIterator> >())
    {
        for (auto ri = first + 1; ri < last; ++ri) {
            auto const val = *ri;
            auto const pos = std::find_if(first, ri, bind1st(pred, val));
            for (auto it = ri - 1; it >= pos; --it) {
                *(it + 1) = *it;
            }
            *pos = val;
        }
    };


    //////////// Quick Sort //////////////

    namespace _impl_qsort {

        template < class RandomAccessIterator, class Predicate >
        static RandomAccessIterator partition(RandomAccessIterator left, RandomAccessIterator right,
            const RandomAccessIterator pivot, const Predicate pred)
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
        static void qsort(RandomAccessIterator left, RandomAccessIterator right, const Predicate pred)
        {
            if (left >= right) return;

            auto pivot = left + std::distance(left, right) / 2;
            auto store = partition(left, right, pivot, pred);

            qsort(left, store - 1, pred);
            qsort(store + 1, right, pred);
        }

        template < class RandomAccessIterator, class Predicate >
        static void qsort2(RandomAccessIterator left, RandomAccessIterator right, const int min_size, const Predicate pred)
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

    template <class RandomAccessIterator, class Predicate = std::less< value_t<RandomAccessIterator> >>
    static void quick_sort(RandomAccessIterator first, RandomAccessIterator last,
            const Predicate pred = std::less< typename std::iterator_traits<RandomAccessIterator>::value_type >())
    {
        _impl_qsort::qsort<RandomAccessIterator, Predicate>(first, last - 1, pred);
    }


    //////////// Quick Sort using Insertion Sort towards parts of array. //////////////
    template <class RandomAccessIterator, class Predicate = std::less< value_t<RandomAccessIterator> >>
    static void quick_sort2(RandomAccessIterator first, RandomAccessIterator last,
            const Predicate pred = std::less< typename std::iterator_traits<RandomAccessIterator>::value_type >())
    {
        const int min_size = 4;
        _impl_qsort::qsort2<RandomAccessIterator, Predicate>(first, last - 1, min_size, pred);
    }


    /////////// Heap Sort ///////////
    namespace _impl_hsort {

        template <class RandomAccessIterator, class Predicate = std::less< value_t<RandomAccessIterator> >>
        static void heapify(RandomAccessIterator first, RandomAccessIterator last, const RandomAccessIterator idx, const Predicate pred)
        {
            auto const left = first + 2 * std::distance(first, idx) + 1;
            auto const right = first + 2 * std::distance(first, idx) + 2;
            auto largest = idx; // largest or smallest

            if (left < last and pred(*idx, *left)) {
                largest = left;
            }

            if (right < last and pred(*largest, *right)) {
                largest = right;
            }

            if (largest != idx) {
                std::iter_swap(idx, largest);
                heapify(first, last, largest, pred);
            }
        }

        template <class RandomAccessIterator, class Predicate = std::less< value_t<RandomAccessIterator> >>
        static void build_heap(RandomAccessIterator first, RandomAccessIterator last, const Predicate pred)
        {
            const size_t n = std::distance(first, last);
            for (auto it = std::next(first, n/2 - 1); it >= first; --it) {
                heapify(first, last, it, pred);
            }
        }

    }

    template <class RandomAccessIterator, class Predicate = std::less< value_t<RandomAccessIterator> >>
    static void heap_sort(RandomAccessIterator first, RandomAccessIterator last,
            const Predicate pred = std::less< typename std::iterator_traits<RandomAccessIterator>::value_type >())
    {
        _impl_hsort::build_heap<RandomAccessIterator, Predicate>(first, last, pred);
        for (auto it = last - 1; it > first; --it) {
            std::iter_swap(first, it); // move largest value to a part of sorted array
            _impl_hsort::heapify<RandomAccessIterator, Predicate>(first, it, first, pred); // first becomes largest
        }
    }

}

#endif
