#include "transform/transformable.h"

#include <utility>


void swap(Transformable& lhs, Transformable& rhs) {
    if (&lhs == &rhs) return;

    using std::swap;

    swap(static_cast<ParentTransformation>(lhs), static_cast<ParentTransformation>(rhs));
    swap(static_cast<LocalTransformation>(lhs), static_cast<LocalTransformation>(rhs));
}

Transformable::Transformable() :
    ParentTransformation {},
    LocalTransformation {} {}


Transformable::Transformable(const Transformable& other) :
    ParentTransformation { other.m_parentTransform },
    LocalTransformation { other.m_localTransform } {}

Transformable::Transformable(Transformable&& other) noexcept :
    ParentTransformation { std::move(other.m_parentTransform) },
    LocalTransformation { std::move(other.m_localTransform) } {}

Transformable& Transformable::operator=(const Transformable& other) {
    if (this != &other) {
        m_parentTransform = std::move(other.m_parentTransform);
        m_localTransform = std::move(other.m_localTransform);
    }

    return *this;
}

Transformable& Transformable::operator=(Transformable&& other) noexcept {
    if (this != &other) {
        m_parentTransform = other.m_parentTransform;
        m_localTransform = other.m_localTransform;
    }

    return *this;
}

Transformable::Transformable(const Transform& parent, const Transform& local) :
    ParentTransformation { parent },
    LocalTransformation { local } {}

Transformable::Transformable(const ParentTransformation& parent, const LocalTransformation& local) :
    ParentTransformation { parent },
    LocalTransformation { local } {}

Transform Transformable::GetGlobalTransform() {
    return GetParentTransform() + GetTransform();
}

const Transform Transformable::GetGlobalTransform() const {
    return GetParentTransform() + GetTransform();
}
