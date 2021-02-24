#ifndef PROJECTION_H
#define PROJECTION_H

#include "interface/icanbeeverywhere.h"
#include "interface/icanbematrix.h"

#include <glm/glm.hpp>
#include <glm/matrix.hpp>


class Projection :
    public ICanBeEverywhere,
    public ICanBeMatrix {
protected:
    float m_depthNear;
    float m_depthFar;

public:
    Projection(Projection&& other) noexcept = delete;
    Projection& operator=(Projection&& other) noexcept = delete;

public:
    Projection();
    Projection(const Projection& other);
    Projection& operator=(const Projection& other);
    virtual ~Projection() = default;

public:
    float GetDepthNear() const;
    void SetDepthNear(float depthNear);

    float GetDepthFar() const;
    void SetDepthFar(float depthFar);
};

#endif // PROJECTION_H
