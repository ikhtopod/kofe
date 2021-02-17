#ifndef LIGHTSTORAGE_H
#define LIGHTSTORAGE_H

#include "interface/icanbeeverywhere.h"
#include "light/pointlight.h"
#include "light/directionallight.h"

#include <vector>


class LightStorage final :
    public ICanBeEverywhere {
public:
    static const size_t MAX_DIRECTIONAL_LIGHTS;
    static const size_t MAX_POINT_LIGHTS;
    static const size_t MAX_SPOT_LIGHTS;

private:
    std::vector<DirectionalLight*> m_directionalLights;
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
    std::vector<DirectionalLight*>& GetDirectionalLights();
    const std::vector<DirectionalLight*>& GetDirectionalLights() const;

    std::vector<PointLight*>& GetPointLights();
    const std::vector<PointLight*>& GetPointLights() const;
};

#endif // LIGHTSTORAGE_H
