#include "transform/localtransformation.h"


LocalTransformation::LocalTransformation() :
    m_localTransform {} {}

Transform& LocalTransformation::GetTransform() {
    return m_localTransform;
}

const Transform& LocalTransformation::GetTransform() const {
    return m_localTransform;
}

void LocalTransformation::SetTransform(const Transform& transform) {
    m_localTransform = transform;
}
