#ifndef COMMON_SORTER_HPP
#define COMMON_SORTER_HPP

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


}

#endif // COMMON_SORTER_HPP
