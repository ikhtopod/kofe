#include "camera.h"

#include "everywhere.h"


const float Camera::DEFAULT_FOV { 45.0f };

const float Camera::DEFAULT_MOVEMENT_SPEED { 2.25f };

const float Camera::DEFAULT_PITCH { 0.0f };
const float Camera::MAX_PITCH { 89.0f };
const float Camera::MIN_PITCH { -89.0f };

const float Camera::DEFAULT_YAW { 0.0f };
const float Camera::MIN_YAW { 0.0f };
const float Camera::MAX_YAW { 360.0f };

const float Camera::DEFAULT_ROLL { 0.0f };

const float Camera::DEFAULT_MOUSE_SENSITIVITY_X { 0.08f };
const float Camera::DEFAULT_MOUSE_SENSITIVITY_Y { 0.07f };

Camera::Camera() :
    m_fov { DEFAULT_FOV },
    m_axis {},
    m_lastMousePosition {}
{
    Everywhere::Instance().Get<Input>().Attach(this);
    m_lastMousePosition = Everywhere::Instance().Get<Input>().GetMousePosition();

    UpdateCameraVectors();
}

Camera::~Camera() {
    Everywhere::Instance().Get<Input>().Detach(this);
}

void Camera::UpdateCameraVectors() {
    glm::vec3 front {};

    glm::vec3 rotation = glm::radians(GetTransform().GetRotation());

    front.x = std::cos(rotation.x) * std::cos(rotation.y);
    front.y = std::sin(rotation.x);
    front.z = std::sin(rotation.x) * std::cos(rotation.y);

    m_axis.SetFront(glm::normalize(front));
    m_axis.SetRight(glm::normalize(glm::cross(m_axis.GetFront(), Axis::UP)));
    m_axis.SetUp(glm::normalize(glm::cross(m_axis.GetRight(), m_axis.GetFront())));
}

float Camera::GetFoV() const {
    return m_fov;
}

glm::mat4 Camera::ToMatrix() const {
    return glm::lookAt(GetTransform().GetPosition(),
                       GetTransform().GetPosition() + m_axis.GetFront(),
                       m_axis.GetUp());
}
