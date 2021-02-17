#ifndef TRANSFORMABLE_H
#define TRANSFORMABLE_H

#include "localtransformation.h"
#include "parenttransformation.h"


class Transformable :
    public LocalTransformation,
    public ParentTransformation {
public:
    Transformable();
    virtual ~Transformable() = default;
};

#endif // TRANSFORMABLE_H
