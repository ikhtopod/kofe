#include "globaltransformation.h"


GlobalTransformation::GlobalTransformation() : m_globalTransform {} {}

Transform& GlobalTransformation::GetGlobalTransform() {
    return m_globalTransform;
}

const Transform& GlobalTransformation::GetGlobalTransform() const {
    return m_globalTransform;
}

void GlobalTransformation::SetGlobalTransform(const Transform& globalTransform) {
    m_globalTransform = globalTransform;
}
