#include "storage/lightstorage.h"


const size_t LightStorage::MAX_DIRECTIONAL_LIGHTS { 4 };
const size_t LightStorage::MAX_POINT_LIGHTS { 12 };
const size_t LightStorage::MAX_SPOT_LIGHTS { 6 };

LightStorage::LightStorage() :
    m_directionalLights {},
    m_pointLights {},
    m_spotLights {} {}

LightStorage::~LightStorage() {
    m_directionalLights.Clear();
    m_pointLights.Clear();
    m_spotLights.Clear();
}

CollectionOfPtr<DirectionalLight>& LightStorage::GetDirectionalLights() {
    return m_directionalLights;
}

const CollectionOfPtr<DirectionalLight>& LightStorage::GetDirectionalLights() const {
    return m_directionalLights;
}

CollectionOfPtr<PointLight>& LightStorage::GetPointLights() {
    return m_pointLights;
}

const CollectionOfPtr<PointLight>& LightStorage::GetPointLights() const {
    return m_pointLights;
}

CollectionOfPtr<SpotLight>& LightStorage::GetSpotLights() {
    return m_spotLights;
}

const CollectionOfPtr<SpotLight>& LightStorage::GetSpotLights() const {
    return m_spotLights;
}
