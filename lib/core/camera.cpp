#include "camera.h"

#include "everywhere.h"


const float Camera::DEFAULT_FOV { 85.0f };

Camera::Camera() :
    m_fov { DEFAULT_FOV }
{
    Everywhere::Instance().Get<Input>().Attach(this);
}

Camera::~Camera() {
    Everywhere::Instance().Get<Input>().Detach(this);
}

float Camera::GetFoV() const {
    return m_fov;
}
