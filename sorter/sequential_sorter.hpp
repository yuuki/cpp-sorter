#ifndef SEQUENCIAL_SORTER_HPP
#define SEQUENCIAL_SORTER_HPP

#include <algorithm>
#include <vector>
#include <functional>

#include "common_sorter.hpp"

namespace mysorter {

    //////////// Insertion Sort //////////////

    template <typename RandomAccessIterator, typename Predicate = LessPred<RandomAccessIterator> > inline static
    void insertion_sort(RandomAccessIterator first, RandomAccessIterator last,
            const Predicate pred = LessPred<RandomAccessIterator>())
    {
        for (auto ri = first + 1; ri < last; ++ri) {
            auto const val = *ri;
            auto const pos = std::find_if(first, ri, std::bind(pred, val, std::placeholders::_1));
            for (auto it = ri - 1; it >= pos; --it) {
                *(it + 1) = *it;
            }
            *pos = val;
        }
    };


    /////////// Shell Sort ///////////

    template <typename RandomAccessIterator, typename Predicate = LessPred<RandomAccessIterator> > inline static
    void shell_sort(RandomAccessIterator first, RandomAccessIterator last, const Predicate pred = LessPred<RandomAccessIterator>())
    {
        auto h = 1;
        while (h < std::distance(first, last)) h = 3*h + 1;
        h /= 3;
        while (h != 0) {
            for (auto it = first + h; it < last; ++it) {
                auto val = *it;
                auto jt = it - h;
                for (; pred(val, *jt) and jt >= first + h; jt -= h) {
                   *(jt + h) = *jt;
                }
                *(jt + h) = val;
            }
            h /= 3;
        }
        insertion_sort(first, last, pred);
    }

    //////////// Quick Sort //////////////

    namespace _impl_qsort {

        template < typename RandomAccessIterator, typename Predicate > inline static
        RandomAccessIterator partition(RandomAccessIterator left, RandomAccessIterator right,
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

        template < typename RandomAccessIterator, typename Predicate > inline static
        void qsort(RandomAccessIterator left, RandomAccessIterator right, const Predicate pred)
        {
            if (left >= right) return;

            auto pivot = left + std::distance(left, right) / 2;
            auto store = partition(left, right, pivot, pred);

            qsort(left, store - 1, pred);
            qsort(store + 1, right, pred);
        }

        template < typename RandomAccessIterator, typename Predicate > inline static
        void qsort2(RandomAccessIterator left, RandomAccessIterator right, const int min_size, const Predicate pred)
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

    template <typename RandomAccessIterator, typename Predicate = LessPred<RandomAccessIterator> > inline static
    void quick_sort(RandomAccessIterator first, RandomAccessIterator last,
            const Predicate pred = LessPred<RandomAccessIterator>())
    {
        _impl_qsort::qsort<RandomAccessIterator, Predicate>(first, last - 1, pred);
    }


    //////////// Quick Sort using Insertion Sort towards parts of array. //////////////
    template <typename RandomAccessIterator, typename Predicate = LessPred<RandomAccessIterator> > inline static
    void quick_sort2(RandomAccessIterator first, RandomAccessIterator last,
            const Predicate pred = LessPred<RandomAccessIterator>())
    {
        const int min_size = 20;
        _impl_qsort::qsort2<RandomAccessIterator, Predicate>(first, last - 1, min_size, pred);
    }


    /////////// Heap Sort ///////////
    namespace _impl_hsort {

        template <typename RandomAccessIterator, typename Predicate = LessPred<RandomAccessIterator> > inline static
        void heapify(RandomAccessIterator first, RandomAccessIterator last, const RandomAccessIterator idx, const Predicate pred)
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

        template <typename RandomAccessIterator, typename Predicate = LessPred<RandomAccessIterator> > inline static
        void build_heap(RandomAccessIterator first, RandomAccessIterator last, const Predicate pred)
        {
            const size_t n = std::distance(first, last);
            for (auto it = std::next(first, n/2 - 1); it >= first; --it) {
                heapify(first, last, it, pred);
            }
        }

    }

    template <typename RandomAccessIterator, typename Predicate = LessPred<RandomAccessIterator> > inline static
    void heap_sort(RandomAccessIterator first, RandomAccessIterator last,
            const Predicate pred = LessPred<RandomAccessIterator>())
    {
        _impl_hsort::build_heap<RandomAccessIterator, Predicate>(first, last, pred);
        for (auto it = last - 1; it > first; --it) {
            std::iter_swap(first, it); // move largest value to a part of sorted array
            _impl_hsort::heapify<RandomAccessIterator, Predicate>(first, it, first, pred); // first becomes largest
        }
    }



}

#endif // SEQUENCIAL_SORTER_HPP
