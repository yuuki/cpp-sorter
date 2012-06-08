#ifndef PARALLEL_SORTER_HPP
#define PARALLEL_SORTER_HPP

#include <algorithm>
#include <vector>
#include <functional>
#include <tbb/partitioner.h>
#include <tbb/blocked_range.h>
#include <tbb/parallel_for.h>
#include <tbb/task_scheduler_init.h>

#include "common_sorter.hpp"
#include "sequential_sorter.hpp"

namespace mysorter {

    /////////// Concurrent Shell Sort with TBB ///////////

    template <typename RandomAccessIterator, typename Predicate> inline static
    void shell_sort_tbb(RandomAccessIterator first, RandomAccessIterator last, const Predicate pred)
    {
        tbb::task_scheduler_init init;
        auto const N = std::distance(first, last);
        auto h = 1;

        while (h < N) h = 3*h + 1;
        h /= 3;
        while (h != 0) {
            auto const task = [&, h](const tbb::blocked_range<size_t> &r) {
                for (auto k = r.begin(); k < r.end(); ++k) {
                    for (auto i = k + h; i < N; i += h) {
                        auto val = first[i];
                        auto j = i - h;
                        for (; pred(val, first[j]) and j >= h; j -= h) {
                            first[j + h] = first[j];
                        }
                        first[j + h] = val;
                    }
                }
            };
            tbb::parallel_for(tbb::blocked_range<size_t>(0, h), task, tbb::auto_partitioner());
            h /= 3;
        }
        insertion_sort(first, last, pred);

        init.terminate();
    }

    template <typename RandomAccessIterator, typename Predicate> inline static
    void shell_sort_openmp(RandomAccessIterator first, RandomAccessIterator last, const Predicate pred)
    {
        auto const N = std::distance(first, last);
        auto h = 1;

        while (h < N) h = 3*h + 1;
        h /= 3;
        #pragma omp parallel firstparivate(h)
        {
        while (h != 0) {
            #pragma omp for
            for (auto k = 0; k < h; ++k) {
                for (auto i = k + h; i < N; i += h) {
                    auto val = first[i];
                    auto j = i - h;
                    for (; pred(val, first[j]) and j >= h; j -= h) {
                        first[j + h] = first[j];
                    }
                    first[j + h] = val;
                }
            }
            h /= 3;
        }
        }
        insertion_sort(first, last, pred);
    }


}

#endif // PARALLEL_SORTER_HPP
