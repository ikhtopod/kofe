#include "projection/orthographic.h"

#include "everywhere.h"

#include <utility>


const float Orthographic::BOTTOM { -0.5f };
const float Orthographic::TOP { 0.5f };
const float Orthographic::DEPTH_NEAR { -10.0f };
const float Orthographic::DEPTH_FAR { 100.0f };


Orthographic::Orthographic() :
    m_scale {} {}

Orthographic::Orthographic(const glm::vec3& scale) :
    m_scale { scale } {}

Orthographic::Orthographic(glm::vec3&& scale) noexcept :
    m_scale { std::move(scale) } {}

Orthographic::Orthographic(float distance) :
    m_scale {} {
    SetScaleByDistance(distance);
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

    glm::mat4 matrix = glm::ortho(left, right, BOTTOM, TOP, DEPTH_NEAR, DEPTH_FAR);
    matrix = glm::scale(matrix, m_scale);

    return matrix;
}
