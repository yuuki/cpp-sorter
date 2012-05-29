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

    template<class RandomAccessIterator, class Predicate>
    class QuickSort {
        typedef typename std::iterator_traits<RandomAccessIterator>::value_type value_t;

        QuickSort(RandomAccessIterator const low, RandomAccessIterator const high, Predicate c) {
            assert( low <= high );
        }

        public:
        static void sort(RandomAccessIterator first, RandomAccessIterator last, Predicate pred)
        {
            qsort(first, last - 1, pred);
        }

        private:
        static void qsort(typename std::vector<value_t>::iterator left, typename std::vector<value_t>::iterator right, Predicate pred)
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

        template<class IterT, class PredT>
        friend void quick_sort(IterT first, IterT last, PredT c);

    };


    template<class RandomAccessIterator, class Predicate>
    static inline void quick_sort(RandomAccessIterator first, RandomAccessIterator last, Predicate pred)
    {
        typedef typename std::iterator_traits<RandomAccessIterator>::value_type value_t;
        QuickSort<RandomAccessIterator,Predicate>::sort(first, last, pred);
    }

    template<class RandomAccessIterator>
    static inline void quick_sort(RandomAccessIterator first, RandomAccessIterator last)
    {
        typedef typename std::iterator_traits<RandomAccessIterator>::value_type value_t;
        QuickSort< RandomAccessIterator, std::less<value_t> >::sort(first, last, std::less<value_t>());
    }

}

#endif
