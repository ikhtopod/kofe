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

const std::vector<DirectionalLight*>
        LightStorage::GetNearestDirectionalLights(const glm::vec3& position) const {
    return GetNearestLightSources<DirectionalLight>(
            m_directionalLights,
            position,
            MAX_DIRECTIONAL_LIGHTS);
}

const std::vector<PointLight*>
        LightStorage::GetNearestPointLight(const glm::vec3& position) const {
    return GetNearestLightSources<PointLight>(
            m_pointLights,
            position,
            MAX_POINT_LIGHTS);
}

const std::vector<SpotLight*>
        LightStorage::GetNearestSpotLight(const glm::vec3& position) const {
    return GetNearestLightSources<SpotLight>(
            m_spotLights,
            position,
            MAX_SPOT_LIGHTS);
}
