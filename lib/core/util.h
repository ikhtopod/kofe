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

template <>
glm::vec2 Repeat<glm::vec2>(glm::vec2 value, glm::vec2::value_type min, glm::vec2::value_type max) {
    value.x = Repeat(value.x, min, max);
    value.y = Repeat(value.y, min, max);

    return value;
}

template <>
glm::vec3 Repeat<glm::vec3>(glm::vec3 value, glm::vec3::value_type min, glm::vec3::value_type max) {
    value.x = Repeat(value.x, min, max);
    value.y = Repeat(value.y, min, max);
    value.z = Repeat(value.z, min, max);

    return value;
}

} // namespace util

#endif // UTIL_H
