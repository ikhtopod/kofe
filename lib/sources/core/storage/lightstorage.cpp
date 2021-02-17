#include "storage/lightstorage.h"


const size_t LightStorage::MAX_DIRECTIONAL_LIGHTS { 4 };
const size_t LightStorage::MAX_POINT_LIGHTS { 12 };
const size_t LightStorage::MAX_SPOT_LIGHTS { 6 };

LightStorage::LightStorage() :
    m_pointLights {} {}

LightStorage::~LightStorage() {
    m_pointLights.clear();
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
