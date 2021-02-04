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

    UpdateCameraVectors();
}

Camera::~Camera() {
    Everywhere::Instance().Get<Input>().Detach(this);
}

void Camera::UpdateCameraVectors() {
    const glm::quat INVERSE_ORIENTATION = glm::inverse(GetTransform().GetOrientation());

    m_axis.SetFront(glm::rotate(INVERSE_ORIENTATION, Axis::FRONT));
    m_axis.SetRight(glm::rotate(INVERSE_ORIENTATION, -Axis::RIGHT));
    m_axis.SetUp(glm::rotate(INVERSE_ORIENTATION, -Axis::UP));
}

float Camera::GetFoV() const {
    return m_fov;
}

glm::mat4 Camera::ToMatrix() const {
    return GetTransform().GetOrientationMatrix() *
            GetTransform().GetPositionMatrix();
}
