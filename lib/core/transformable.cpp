#include "transformable.h"


Transformable::Transformable() :
    m_transform {},
    m_globalTransform {} {}

Transform& Transformable::GetTransform() {
    return m_transform;
}

const Transform& Transformable::GetTransform() const {
    return m_transform;
}

void Transformable::SetTransform(const Transform& transform) {
    m_transform = transform;
}

Transform& Transformable::GetGlobalTransform() {
    return m_globalTransform;
}

const Transform& Transformable::GetGlobalTransform() const {
    return m_globalTransform;
}

void Transformable::SetGlobalTransform(const Transform& globalTransform) {
    m_globalTransform = globalTransform;
}
