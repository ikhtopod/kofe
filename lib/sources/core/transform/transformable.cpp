#include "transform/transformable.h"


Transformable::Transformable() :
    LocalTransformation {},
    ParentTransformation {} {}

Transform Transformable::GetGlobalTransform() {
    return GetParentTransform() + GetTransform();
}

const Transform Transformable::GetGlobalTransform() const {
    return GetParentTransform() + GetTransform();
}
