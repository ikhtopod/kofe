#include "transform/parenttransformation.h"


ParentTransformation::ParentTransformation() :
    m_parentTransform {} {}

Transform& ParentTransformation::GetParentTransform() {
    return m_parentTransform;
}

const Transform& ParentTransformation::GetParentTransform() const {
    return m_parentTransform;
}

void ParentTransformation::SetParentTransform(const Transform& parentTransform) {
    m_parentTransform = parentTransform;
}
