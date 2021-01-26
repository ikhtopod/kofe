#ifndef PROJECTION_H
#define PROJECTION_H

#include "icanbeeverywhere.h"

#include <glm/glm.hpp>
#include <glm/matrix.hpp>


class Projection : public ICanBeEverywhere {
public:
    Projection() = default;
    virtual ~Projection() = default;

public:
    virtual glm::mat4 ToMatrix() const = 0;
};

#endif // PROJECTION_H
