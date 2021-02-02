#ifndef UTIL_H
#define UTIL_H

#include <glm/glm.hpp>

#include <cmath>


namespace util {

template <typename T = float, typename U = T>
T Repeat(T value, U min, U max) {
    T result { value };

    if (value < min) {
        result = max + std::fmod(value, max);
    } else if (value > max) {
        result = min - std::fmod(value, max);
    }

    return result;
}

} // namespace util

#endif // UTIL_H
