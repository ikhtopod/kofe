#ifndef PARENTTRANSFORMATION_H
#define PARENTTRANSFORMATION_H

#include "transform.h"


class ParentTransformation {
protected:
    Transform m_parentTransform;

public:
    ParentTransformation();
    ParentTransformation(const ParentTransformation& other);
    ParentTransformation(ParentTransformation&& other) noexcept;
    ParentTransformation& operator=(const ParentTransformation& other);
    ParentTransformation& operator=(ParentTransformation&& other) noexcept;
    virtual ~ParentTransformation() = default;

public:
    virtual Transform& GetParentTransform();
    virtual const Transform& GetParentTransform() const;
    virtual void SetParentTransform(const Transform& parentTransform);

public:
    friend void swap(ParentTransformation&, ParentTransformation&);
};


void swap(ParentTransformation& lhs, ParentTransformation& rhs);

#endif // PARENTTRANSFORMATION_H
