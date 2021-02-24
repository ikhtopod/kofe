#include "projection/orthographic.h"

#include "everywhere.h"

#include <utility>


namespace {

static constexpr float BOTTOM { -0.5f };
static constexpr float TOP { 0.5f };

} // namespace


Orthographic::Orthographic() :
    Projection {},
    m_scale {} {}

Orthographic::Orthographic(const glm::vec3& scale) :
    Projection {},
    m_scale { scale } {}

Orthographic::Orthographic(glm::vec3&& scale) noexcept :
    Projection {},
    m_scale { std::move(scale) } {}

Orthographic::Orthographic(float distance) :
    Projection {},
    m_scale {} {
    SetScaleByDistance(distance);
}

Orthographic::Orthographic(const Orthographic& other) :
    Projection { other },
    m_scale { other.m_scale } {}

Orthographic& Orthographic::operator=(const Orthographic& other) {
    if (this != &other) {
        Projection::operator=(other);
        m_scale = other.m_scale;
    }

    return *this;
}

glm::vec3 Orthographic::GetScale() const {
    return m_scale;
}

void Orthographic::SetScale(const glm::vec3& scale) {
    m_scale = scale;
}

void Orthographic::SetScale(glm::vec3&& scale) noexcept {
    m_scale = std::move(scale);
}

void Orthographic::SetScaleByDistance(float distance) {
    SetScale(glm::vec3 { 1.0f } / distance);
}

glm::mat4 Orthographic::ToMatrix() const {
    float width = Everywhere::Instance().Get<Window>().GetScreen().GetWidth();
    float height = Everywhere::Instance().Get<Window>().GetScreen().GetHeight();

    float left = -width / height * 0.5f;
    float right = width / height * 0.5f;

    glm::mat4 matrix = glm::ortho(left, right, BOTTOM, TOP, m_depthNear, m_depthFar);
    matrix = glm::scale(matrix, m_scale);

    return matrix;
}
