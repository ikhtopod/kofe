#include "space.h"

#include "app_exceptions.h"
#include <iterator>


const glm::mat4 Space::MODEL { 1.0f };


Space::Space() :
    m_scenes {} {}

Space::~Space() {
    m_scenes.Clear();
}

CollectionOf<Scene>& Space::GetScenes() { return m_scenes; }

const CollectionOf<Scene>& Space::GetScenes() const { return m_scenes; }

void Space::Processing() {
    for (auto& scene : m_scenes.Get()) {
        if (scene) {
            scene->Processing();
        }
    }
}
