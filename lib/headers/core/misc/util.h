#ifndef UTIL_H
#define UTIL_H

#include <glm/glm.hpp>

#include <cmath>
#include <limits>


namespace util {

template<typename T = float, typename U = T>
T Repeat(T value, U min, U max) {
    T result { value };

    if (value < min) {
        result = max + std::fmod(value, max);
    } else if (value > max) {
        result = min - std::fmod(value, max);
    }

    return result;
}

template<typename T = float>
bool IsEqual(T x, T y) {
    return std::abs(x - y) < std::numeric_limits<float>::epsilon();
}

} // namespace util

#endif // UTIL_H
