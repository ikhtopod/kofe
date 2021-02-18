#include "scene/object.h"


Object::Object() :
    Transformable {},
    m_children {} {}

Object::~Object() {
    m_children.Clear();
}

CollectionOf<Object>& Object::Children() {
    return m_children;
}

const CollectionOf<Object>& Object::Children() const {
    return m_children;
}

void Object::Processing() {
    for (auto& child : m_children.Get()) {
        if (child) {
            child->SetParentTransform(GetParentTransform() + GetTransform());
            child->Processing();
        }
    }
}
