#ifndef PARENTTRANSFORMATION_H
#define PARENTTRANSFORMATION_H

#include "transform.h"


class ParentTransformation {
protected:
    Transform m_parentTransform;

public:
    virtual ~ParentTransformation() = default;
    ParentTransformation();

    virtual Transform& GetParentTransform();
    virtual const Transform& GetParentTransform() const;
    virtual void SetParentTransform(const Transform& parentTransform);
};

#endif // PARENTTRANSFORMATION_H
