#include "transform/localtransformation.h"


LocalTransformation::LocalTransformation() :
    m_transform {} {}

Transform& LocalTransformation::GetTransform() {
    return m_transform;
}

const Transform& LocalTransformation::GetTransform() const {
    return m_transform;
}

void LocalTransformation::SetTransform(const Transform& transform) {
    m_transform = transform;
}
