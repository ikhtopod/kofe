#ifndef LOCALTRANSFORMATION_H
#define LOCALTRANSFORMATION_H

#include "transform.h"


class LocalTransformation {
protected:
    Transform m_transform;

public:
    virtual ~LocalTransformation() = default;
    LocalTransformation();

    virtual Transform& GetTransform();
    virtual const Transform& GetTransform() const;
    virtual void SetTransform(const Transform& transform);
};

#endif // LOCALTRANSFORMATION_H
