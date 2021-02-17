#include "transform/parenttransformation.h"

#include <utility>


void swap(ParentTransformation& lhs, ParentTransformation& rhs) {
    if (&lhs == &rhs) return;

    using std::swap;

    swap(lhs.m_parentTransform, rhs.m_parentTransform);
}


ParentTransformation::ParentTransformation() :
    m_parentTransform {} {}

ParentTransformation::ParentTransformation(const ParentTransformation& other) :
    m_parentTransform { other.m_parentTransform } {}

ParentTransformation::ParentTransformation(ParentTransformation&& other) noexcept :
    m_parentTransform { std::move(other.m_parentTransform) } {}

ParentTransformation& ParentTransformation::operator=(const ParentTransformation& other) {
    if (this != &other) {
        m_parentTransform = other.m_parentTransform;
    }

    return *this;
}

ParentTransformation& ParentTransformation::operator=(ParentTransformation&& other) noexcept {
    if (this != &other) {
        m_parentTransform = std::move(other.m_parentTransform);
    }

    return *this;
}

Transform& ParentTransformation::GetParentTransform() {
    return m_parentTransform;
}

const Transform& ParentTransformation::GetParentTransform() const {
    return m_parentTransform;
}

void ParentTransformation::SetParentTransform(const Transform& parentTransform) {
    m_parentTransform = parentTransform;
}
