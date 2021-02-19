#include "camera/camera.h"

#include "everywhere.h"

#include <glm/gtx/transform.hpp>


const float Camera::DEFAULT_FOV { 45.0f };

const float Camera::DEFAULT_MOVEMENT_SPEED { 2.25f };

const float Camera::DEFAULT_PITCH { 0.0f };
const float Camera::MIN_PITCH { -89.0f };
const float Camera::MAX_PITCH { 89.0f };

const float Camera::DEFAULT_YAW { 0.0f };
const float Camera::MIN_YAW { -360.0f };
const float Camera::MAX_YAW { 360.0f };

const float Camera::DEFAULT_ROLL { 0.0f };

const float Camera::DEFAULT_MOUSE_SENSITIVITY_YAW { 4.0f };
const float Camera::DEFAULT_MOUSE_SENSITIVITY_PITCH { 4.5f };

const glm::quat Camera::DEFAULT_CAMERA_ORIENTATION { 0.0f, 0.0f, 0.0f, -1.0f };

Camera::Camera() :
    m_fov { DEFAULT_FOV },
    m_lastMousePosition {},
    m_yaw { DEFAULT_YAW },
    m_pitch { DEFAULT_PITCH } {
    Everywhere::Instance().Get<Input>().Attach(this);

    m_lastMousePosition = Everywhere::Instance().Get<Input>().GetMousePosition();
    GetTransform().SetAxisOrientation(DEFAULT_CAMERA_ORIENTATION);
    GetTransform().SetOrientation(DEFAULT_CAMERA_ORIENTATION);
}

Camera::~Camera() {
    Everywhere::Instance().Get<Input>().Detach(this);
}

float Camera::GetFoV() const {
    return m_fov;
}

glm::mat4 Camera::ToMatrix() const {
    const glm::mat4 ORIENTATION = glm::mat4_cast(glm::conjugate(GetTransform().GetOrientation()));
    const glm::mat4 POSITION = glm::translate(-GetTransform().GetPosition());

    return ORIENTATION * POSITION;
}
