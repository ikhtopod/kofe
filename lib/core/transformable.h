#ifndef TRANSFORMABLE_H
#define TRANSFORMABLE_H

#include "transform.h"


class Transformable {
protected:
    Transform m_transform;
    Transform m_globalTransform;

public:
    Transformable();
    virtual ~Transformable() = default;

public:
    virtual Transform& GetTransform();
    virtual const Transform& GetTransform() const;
    virtual void SetTransform(const Transform& transform);

    virtual Transform& GetGlobalTransform();
    virtual const Transform& GetGlobalTransform() const;
    virtual void SetGlobalTransform(const Transform& globalTransform);
};

#endif // TRANSFORMABLE_H
