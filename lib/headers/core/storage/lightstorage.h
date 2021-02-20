#ifndef LIGHTSTORAGE_H
#define LIGHTSTORAGE_H

#include "interface/icanbeeverywhere.h"
#include "misc/collectionof.h"
#include "light/directionallight.h"
#include "light/pointlight.h"
#include "light/spotlight.h"


class LightStorage final :
    public ICanBeEverywhere {
public:
    static const size_t MAX_DIRECTIONAL_LIGHTS;
    static const size_t MAX_POINT_LIGHTS;
    static const size_t MAX_SPOT_LIGHTS;

private:
    CollectionOfPtr<DirectionalLight> m_directionalLights;
    CollectionOfPtr<PointLight> m_pointLights;
    CollectionOfPtr<SpotLight> m_spotLights;

public:
    LightStorage();
    virtual ~LightStorage();

public:
    LightStorage(const LightStorage&) = delete;
    LightStorage(LightStorage&&) noexcept = delete;
    LightStorage& operator=(const LightStorage&) = delete;
    LightStorage& operator=(LightStorage&&) noexcept = delete;

public:
    CollectionOfPtr<DirectionalLight>& GetDirectionalLights();
    const CollectionOfPtr<DirectionalLight>& GetDirectionalLights() const;

    CollectionOfPtr<PointLight>& GetPointLights();
    const CollectionOfPtr<PointLight>& GetPointLights() const;

    CollectionOfPtr<SpotLight>& GetSpotLights();
    const CollectionOfPtr<SpotLight>& GetSpotLights() const;
};

#endif // LIGHTSTORAGE_H
