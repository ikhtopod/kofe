#include "scene.h"

#include "app_exceptions.h"
#include <iterator>


Scene::Scene() :
    m_objects {} {}

Scene::~Scene() {
    ClearObjects();
}

void Scene::AddObject(const Scene::ObjectSPtr& object) {
    m_objects.push_back(object);
}

void Scene::DeleteObjects(size_t index) {
    if (index >= m_objects.size()) return;

    m_objects[index].reset();
    m_objects.erase(std::next(m_objects.begin(), index));
}

void Scene::ClearObjects() {
    for (auto& object : m_objects) {
        object.reset();
    }

    m_objects.clear();
}

void Scene::Processing() {
    for (auto& object : m_objects) {
        if (object)
            object->Processing();
    }
}
