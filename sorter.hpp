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

    // Template Alias (C++11)
    template <typename T>
    using value_t = typename std::iterator_traits<T>::value_type;

    template <typename T>
    using LessPred = std::less< value_t<T> >;


    //////////// Insertion Sort //////////////

    template <typename RandomAccessIterator, typename Predicate = LessPred<RandomAccessIterator> >
    void insertion_sort(RandomAccessIterator first, RandomAccessIterator last,
            Predicate pred = LessPred<RandomAccessIterator>())
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


    //////////// Quick Sort //////////////

    namespace _impl_qsort {

        template < typename RandomAccessIterator, typename Predicate >
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

        template < typename RandomAccessIterator, typename Predicate >
        static void qsort(RandomAccessIterator left, RandomAccessIterator right, const Predicate pred)
        {
            if (left >= right) return;

            auto pivot = left + std::distance(left, right) / 2;
            auto store = partition(left, right, pivot, pred);

            qsort(left, store - 1, pred);
            qsort(store + 1, right, pred);
        }

        template < typename RandomAccessIterator, typename Predicate >
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

    template <typename RandomAccessIterator, typename Predicate = LessPred<RandomAccessIterator> >
    static void quick_sort(RandomAccessIterator first, RandomAccessIterator last,
            Predicate pred = LessPred<RandomAccessIterator>())
    {
        _impl_qsort::qsort<RandomAccessIterator, Predicate>(first, last - 1, pred);
    }


    //////////// Quick Sort using Insertion Sort towards parts of array. //////////////
    template <typename RandomAccessIterator, typename Predicate = LessPred<RandomAccessIterator> >
    static void quick_sort2(RandomAccessIterator first, RandomAccessIterator last,
            Predicate pred = LessPred<RandomAccessIterator>())
    {
        const int min_size = 20;
        _impl_qsort::qsort2<RandomAccessIterator, Predicate>(first, last - 1, min_size, pred);
    }


    /////////// Heap Sort ///////////
    namespace _impl_hsort {

        template <typename RandomAccessIterator, typename Predicate = LessPred<RandomAccessIterator> >
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

        template <typename RandomAccessIterator, typename Predicate = LessPred<RandomAccessIterator> >
        static void build_heap(RandomAccessIterator first, RandomAccessIterator last, const Predicate pred)
        {
            const size_t n = std::distance(first, last);
            for (auto it = std::next(first, n/2 - 1); it >= first; --it) {
                heapify(first, last, it, pred);
            }
        }

    }

    template <typename RandomAccessIterator, typename Predicate = LessPred<RandomAccessIterator> >
    static void heap_sort(RandomAccessIterator first, RandomAccessIterator last,
            Predicate pred = LessPred<RandomAccessIterator>())
    {
        _impl_hsort::build_heap<RandomAccessIterator, Predicate>(first, last, pred);
        for (auto it = last - 1; it > first; --it) {
            std::iter_swap(first, it); // move largest value to a part of sorted array
            _impl_hsort::heapify<RandomAccessIterator, Predicate>(first, it, first, pred); // first becomes largest
        }
    }


    //////
    ////// Tag Dispacher for each sort algorithm
    //////

    struct insertion_tag{};
    struct quick_tag{};
    struct quick2_tag{};
    struct heap_tag{};
    struct insertion{ using sort_tag = insertion_tag; }; // using alias
    struct quick{ using sort_tag = quick_tag; };
    struct quick2{ using sort_tag = quick2_tag; };
    struct heap{ using sort_tag = heap_tag; };

    template<typename T> struct sort_traits { using sort_tag = T; };
    template<> struct sort_traits<insertion> { using sort_tag = insertion::sort_tag; };
    template<> struct sort_traits<quick> { using sort_tag = quick::sort_tag; };
    template<> struct sort_traits<quick2> { using sort_tag = quick2::sort_tag; };
    template<> struct sort_traits<heap> { using sort_tag = heap::sort_tag; };

    namespace detail {
        template <typename RandomAccessIterator, typename Predicate>
        void sort_(insertion_tag, RandomAccessIterator first, RandomAccessIterator last, Predicate pred) {
            insertion_sort(first, last, pred);
        };

        template <typename RandomAccessIterator, typename Predicate>
        void sort_(quick_tag, RandomAccessIterator first, RandomAccessIterator last, Predicate pred) {
            quick_sort(first, last, pred);
        };

        template <typename RandomAccessIterator, typename Predicate>
        void sort_(quick2_tag, RandomAccessIterator first, RandomAccessIterator last, Predicate pred) {
            quick_sort2(first, last, pred);
        };

        template <typename RandomAccessIterator, typename Predicate>
        void sort_(heap_tag, RandomAccessIterator first, RandomAccessIterator last, Predicate pred) {
            heap_sort(first, last, pred);
        };
        template <typename T, typename RandomAccessIterator, typename Predicate>
        void sort_(T, RandomAccessIterator first, RandomAccessIterator last, Predicate pred) {
            quick_sort2(first, last, pred);
        };
    }

    template <typename Tag, typename RandomAccessIterator, typename Predicate = LessPred<RandomAccessIterator>>
    void sort(Tag, RandomAccessIterator first, RandomAccessIterator last, Predicate pred = LessPred<RandomAccessIterator>()) {
        using sort_tag = typename sort_traits<Tag>::sort_tag;
        detail::sort_(sort_tag(), first, last, pred);
    }

}

#endif
