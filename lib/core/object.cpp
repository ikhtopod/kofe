#include "object.h"


Object::Object() :
    m_meshes {},
    m_materials {} {}

Object::~Object() {
    m_meshes.Clear();
    m_materials.Clear();
}

CollectionOf<Mesh>& Object::GetMeshes() { return m_meshes; }
const CollectionOf<Mesh>& Object::GetMeshes() const { return m_meshes; }

CollectionOf<Material>& Object::GetMaterials() { return m_materials; }
const CollectionOf<Material>& Object::GetMaterials() const { return m_materials; }

void Object::Processing() {
    for (auto& material : m_materials.Get()) {
        material->Processing();
    }

    for (auto& mesh : m_meshes.Get()) {
        mesh->Processing();
    }
}
