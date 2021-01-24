#ifndef GLOBALTRANSFORMATION_H
#define GLOBALTRANSFORMATION_H

#include "transform.h"


class GlobalTransformation {
protected:
    Transform m_globalTransform;

public:
    virtual ~GlobalTransformation() = default;
    GlobalTransformation();

    virtual Transform& GetGlobalTransform();
    virtual const Transform& GetGlobalTransform() const;
    virtual void SetGlobalTransform(const Transform& globalTransform);
};

#endif // GLOBALTRANSFORMATION_H
