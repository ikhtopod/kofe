#include "transform/localtransformation.h"

#include <utility>


void swap(LocalTransformation& lhs, LocalTransformation& rhs) {
    if (&lhs == &rhs) return;

    using std::swap;

    swap(lhs.m_localTransform, rhs.m_localTransform);
}


LocalTransformation::LocalTransformation() :
    m_localTransform {} {}

LocalTransformation::LocalTransformation(const LocalTransformation& other) :
    m_localTransform { other.m_localTransform } {}

LocalTransformation::LocalTransformation(LocalTransformation&& other) noexcept :
    m_localTransform { std::move(other.m_localTransform) } {}

LocalTransformation& LocalTransformation::operator=(const LocalTransformation& other) {
    if (this != &other) {
        m_localTransform = other.m_localTransform;
    }

    return *this;
}

LocalTransformation& LocalTransformation::operator=(LocalTransformation&& other) noexcept {
    if (this != &other) {
        m_localTransform = std::move(other.m_localTransform);
    }

    return *this;
}

LocalTransformation::LocalTransformation(const Transform& transform) :
    m_localTransform { transform } {}

LocalTransformation::LocalTransformation(Transform&& transform) noexcept :
    m_localTransform { std::move(transform) } {}

Transform& LocalTransformation::GetTransform() {
    return m_localTransform;
}

const Transform& LocalTransformation::GetTransform() const {
    return m_localTransform;
}

void LocalTransformation::SetTransform(const Transform& transform) {
    m_localTransform = transform;
}
