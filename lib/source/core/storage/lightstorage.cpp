#include "storage/lightstorage.h"


const size_t LightStorage::MAX_DIRECTIONAL_LIGHTS { 4 };
const size_t LightStorage::MAX_POINT_LIGHTS { 12 };
const size_t LightStorage::MAX_SPOT_LIGHTS { 6 };

LightStorage::LightStorage() :
    m_directionalLights {},
    m_pointLights {},
    m_spotLights {} {}

LightStorage::~LightStorage() {
    m_directionalLights.clear();
    m_pointLights.clear();
    m_spotLights.clear();
}

std::vector<DirectionalLight*>& LightStorage::GetDirectionalLights() {
    return m_directionalLights;
}

const std::vector<DirectionalLight*>& LightStorage::GetDirectionalLights() const {
    return m_directionalLights;
}

std::vector<PointLight*>& LightStorage::GetPointLights() {
    return m_pointLights;
}

const std::vector<PointLight*>& LightStorage::GetPointLights() const {
    return m_pointLights;
}

std::vector<SpotLight*>& LightStorage::GetSpotLights() {
    return m_spotLights;
}

const std::vector<SpotLight*>& LightStorage::GetSpotLights() const {
    return m_spotLights;
}
