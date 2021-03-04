#include "object/object.h"


void swap(Object& lhs, Object& rhs) {
    if (&lhs == &rhs) return;

    using std::swap;

    swap(static_cast<Transformable>(lhs), static_cast<Transformable>(rhs));
    swap(lhs.m_children, rhs.m_children);
}


Object::Object() :
    Transformable {},
    m_children {} {}

Object::Object(const Object& other) :
    Transformable { other },
    m_children { other.m_children } {}

Object::Object(Object&& other) noexcept :
    Transformable { std::move(other) },
    m_children { std::move(other.m_children) } {}

Object& Object::operator=(const Object& other) {
    if (this != &other) {
        Transformable::operator=(other);
        m_children = other.m_children;
    }

    return *this;
}

Object& Object::operator=(Object&& other) noexcept {
    if (this != &other) {
        Transformable::operator=(std::move(other));
        m_children = std::move(other.m_children);
    }

    return *this;
}

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
            child->SetParentTransform(GetGlobalTransform());
            child->Processing();
        }
    }
}
