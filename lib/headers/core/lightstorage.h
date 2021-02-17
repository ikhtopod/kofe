#ifndef LIGHTSTORAGE_H
#define LIGHTSTORAGE_H

#include "icanbeeverywhere.h"
#include "pointlight.h"

#include <vector>


class LightStorage final :
    public ICanBeEverywhere {
public:
    static const size_t MAX_POINT_LIGHTS;

private:
    std::vector<PointLight*> m_pointLights;

public:
    LightStorage();
    virtual ~LightStorage();

public:
    LightStorage(const LightStorage&) = delete;
    LightStorage(LightStorage&&) noexcept = delete;
    LightStorage& operator=(const LightStorage&) = delete;
    LightStorage& operator=(LightStorage&&) noexcept = delete;

public:
    std::vector<PointLight*>& GetPointLights();
    const std::vector<PointLight*>& GetPointLights() const;
};

#endif // LIGHTSTORAGE_H
