#ifndef TRANSFORMABLE_H
#define TRANSFORMABLE_H

#include "localtransformation.h"
#include "globaltransformation.h"


class Transformable :
        public LocalTransformation,
        public GlobalTransformation
{
public:
    Transformable();
    virtual ~Transformable() = default;
};

#endif // TRANSFORMABLE_H
