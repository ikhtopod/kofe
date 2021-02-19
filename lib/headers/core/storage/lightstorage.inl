#ifndef LIGHTSTORAGE_INL
#define LIGHTSTORAGE_INL

#include "light/light.h"

#include <glm/glm.hpp>

#include <vector>
#include <type_traits>
#include <algorithm>


/**
 * @brief Get the Nearest Light Sources object.
 * Naive non-optimized algorithms.
 * @tparam T Light Source type.
 * @tparam typename Checking that the given type is derived from the Light class.
 * @param lights All Light Sources.
 * @param position The position of the target.
 * @param max_lights Maximum number of light sources.
 * @return A new list with the closest light sources relative to the given position.
 */
template<typename T,
         typename = std::enable_if_t<std::is_base_of_v<Light, T>>>
const std::vector<T*> GetNearestLightSources(
        const std::vector<T*> lights,
        const glm::vec3& position,
        const size_t max_lights) {
    std::vector<T*> nearest {
        lights.begin(), lights.end()
    };

    if (lights.size() <= max_lights) {
        return nearest;
    }

    std::sort(nearest.begin(), nearest.end(),
              [&position](T* a, T* b) {
                  if (!a) return false;
                  if (!b) return true;

                  return glm::distance(a->GetTransform().GetPosition(), position) <
                         glm::distance(b->GetTransform().GetPosition(), position);
              });

    return { nearest.begin(), std::next(nearest.begin(), max_lights) };
}

#endif // LIGHTSTORAGE_INL
