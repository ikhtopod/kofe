#ifndef PROJECTION_H
#define PROJECTION_H

#include "interface/icanbeeverywhere.h"
#include "interface/icanbematrix.h"

#include <glm/glm.hpp>
#include <glm/matrix.hpp>


class Projection :
    public ICanBeEverywhere,
    public ICanBeMatrix {
public:
    virtual ~Projection() = default;
};

#endif // PROJECTION_H
