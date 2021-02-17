#ifndef LOCALTRANSFORMATION_H
#define LOCALTRANSFORMATION_H

#include "transform.h"


class LocalTransformation {
protected:
    Transform m_localTransform;

public:
    LocalTransformation();
    LocalTransformation(const LocalTransformation& other);
    LocalTransformation(LocalTransformation&& other) noexcept;
    LocalTransformation& operator=(const LocalTransformation& other);
    LocalTransformation& operator=(LocalTransformation&& other) noexcept;
    virtual ~LocalTransformation() = default;

public:
    virtual Transform& GetTransform();
    virtual const Transform& GetTransform() const;
    virtual void SetTransform(const Transform& transform);

public:
    friend void swap(LocalTransformation&, LocalTransformation&);
};


void swap(LocalTransformation& lhs, LocalTransformation& rhs);

#endif // LOCALTRANSFORMATION_H
