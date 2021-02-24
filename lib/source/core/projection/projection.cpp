#include "projection/projection.h"


namespace {

static constexpr float DEFAULT_DEPTH_NEAR { 0.1f };
static constexpr float DEFAULT_DEPTH_FAR { 2000.0f };

} // namespace


Projection::Projection() :
    m_depthNear { DEFAULT_DEPTH_NEAR },
    m_depthFar { DEFAULT_DEPTH_FAR } {}

Projection::Projection(const Projection& other) :
    m_depthNear { other.m_depthNear },
    m_depthFar { other.m_depthFar } {}

Projection& Projection::operator=(const Projection& other) {
    if (this != &other) {
        m_depthNear = other.m_depthNear;
        m_depthFar = other.m_depthFar;
    }

    return *this;
}


float Projection::GetDepthNear() const {
    return m_depthNear;
}

void Projection::SetDepthNear(float depthNear) {
    m_depthNear = depthNear;
}

float Projection::GetDepthFar() const {
    return m_depthFar;
}

void Projection::SetDepthFar(float depthFar) {
    m_depthFar = depthFar;
}
