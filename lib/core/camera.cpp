#include "camera.h"

#include "everywhere.h"

#include <glm/gtx/quaternion.hpp>


const float Camera::DEFAULT_FOV { 45.0f };

const float Camera::DEFAULT_MOVEMENT_SPEED { 2.25f };

const float Camera::DEFAULT_PITCH { 0.0f };
const float Camera::MIN_PITCH { -89.0f };
const float Camera::MAX_PITCH { 89.0f };

const float Camera::DEFAULT_YAW { 0.0f };
const float Camera::MIN_YAW { -360.0f };
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

    Position = glm::vec3 { 0, 0, 0 };
    Orientation = glm::quat();
    RightAngle = 0.f;
    UpAngle = 0.f;

    UpdateCameraVectors();
}

Camera::~Camera() {
    Everywhere::Instance().Get<Input>().Detach(this);
}

void Camera::UpdateCameraVectors() {
    glm::quat quatFront = Orientation * glm::quat(0, 0, 0, -1) * glm::conjugate(Orientation);

    m_axis.SetFront({ quatFront.x, quatFront.y, quatFront.z });
    m_axis.SetRight(glm::normalize(glm::cross(m_axis.GetFront(), Axis::UP)));
    m_axis.SetUp(glm::normalize(glm::cross(m_axis.GetRight(), m_axis.GetFront())));
}

float Camera::GetFoV() const {
    return m_fov;
}

glm::mat4 Camera::ToMatrix() const {
    glm::quat reverseOrient = glm::conjugate(Orientation);
    glm::mat4 rot = glm::mat4_cast(reverseOrient);
    glm::mat4 translation = glm::translate(glm::mat4(1.0), -Position);

    return rot * translation;
}
