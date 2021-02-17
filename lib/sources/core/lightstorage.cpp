#include "lightstorage.h"


const size_t LightStorage::MAX_POINT_LIGHTS { 6 };

LightStorage::LightStorage() :
    m_pointLights {} {}

LightStorage::~LightStorage() {
    m_pointLights.clear();
}

std::vector<PointLight*>& LightStorage::GetPointLights() {
    return m_pointLights;
}

const std::vector<PointLight*>& LightStorage::GetPointLights() const {
    return m_pointLights;
}
