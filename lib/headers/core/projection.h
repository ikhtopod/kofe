#ifndef PROJECTION_H
#define PROJECTION_H

#include "icanbeeverywhere.h"
#include "icanbematrix.h"

#include <glm/glm.hpp>
#include <glm/matrix.hpp>


class Projection :
        public ICanBeEverywhere,
        public ICanBeMatrix
{
public:
    virtual ~Projection() = default;
};

#endif // PROJECTION_H
