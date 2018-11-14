#ifndef CODA_MATH_UTIL_H_
#define CODA_MATH_UTIL_H_

#include <cmath>
#include <limits>
#include <type_traits>

namespace coda {
  template <class T>
  typename std::enable_if<!std::numeric_limits<T>::is_integer, bool>::type
  almost_equal(T x, T y, T tolerance = std::numeric_limits<T>::epsilon()) {
    T diff = std::fabs(x - y);
    if (diff <= tolerance) {
      return true;
    }

    return diff < std::fmax(std::fabs(x), std::fabs(y)) * tolerance;
  }
} // namespace coda

#endif
