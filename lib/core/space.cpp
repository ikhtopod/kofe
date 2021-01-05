#include "space.h"

#include "app_exceptions.h"
#include <iterator>


const glm::mat4 Space::MODEL { 1.0f };


Space::Space() :
    m_scenes {} {}

Space::~Space() {
    ClearScenes();
}

void Space::AddScene(const Space::SceneSPtr& scene) {
    m_scenes.push_back(scene);
}

void Space::DeleteScene(size_t index) {
    if (index >= m_scenes.size()) return;

    m_scenes[index].reset();
    m_scenes.erase(std::next(m_scenes.begin(), index));
}

void Space::ClearScenes() {
    for (auto& scene : m_scenes) {
        scene.reset();
    }

    m_scenes.clear();
}

void Space::Processing() {
    for (auto& scene : m_scenes) {
        if (scene)
            scene->Processing();
    }
}
