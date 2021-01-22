#include "object.h"


Object::Object() :
    Transformable {},
    m_meshes {} {}

Object::~Object() {
    m_meshes.Clear();
}

CollectionOf<Mesh>& Object::GetMeshes() { return m_meshes; }
const CollectionOf<Mesh>& Object::GetMeshes() const { return m_meshes; }

void Object::Processing() {
    for (auto& mesh : m_meshes.Get()) {
        mesh->Processing();
    }
}
