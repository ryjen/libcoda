#ifndef ARG3_MATH_UTIL_H_
#define ARG3_MATH_UTIL_H_

#include <limits>
#include <type_traits>
#include <cmath>

namespace arg3
{
    template<class T>
    typename std::enable_if<!std::numeric_limits<T>::is_integer, bool>::type
    almost_equal(T x, T y, int ulp)
    {
        // the machine epsilon has to be scaled to the magnitude of the larger value
        // and multiplied by the desired precision in ULPs (units in the last place)
        return std::abs(x-y) <=   std::numeric_limits<T>::epsilon()
               * std::max(std::abs(x), std::abs(y))
               * ulp;
    }

}

#endif
