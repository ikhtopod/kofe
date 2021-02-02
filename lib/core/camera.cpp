#include "camera.h"

#include "everywhere.h"


const float Camera::DEFAULT_FOV { 45.0f };

const float Camera::MOVEMENT_SPEED { 2.25f };


Camera::Camera() :
    m_fov { DEFAULT_FOV },
    m_axis {}
{
    Everywhere::Instance().Get<Input>().Attach(this);
}

Camera::~Camera() {
    Everywhere::Instance().Get<Input>().Detach(this);
}

float Camera::GetFoV() const {
    return m_fov;
}
