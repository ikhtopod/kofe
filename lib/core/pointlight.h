#ifndef POINTLIGHT_H
#define POINTLIGHT_H

#include "light.h"


class PointLight : public Light {
public:
    PointLight();
    virtual ~PointLight() = default;
};

#endif // POINTLIGHT_H
