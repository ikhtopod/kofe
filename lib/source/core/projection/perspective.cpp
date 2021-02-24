#include "projection/perspective.h"

#include "everywhere.h"


glm::mat4 Perspective::ToMatrix() const {
    float width = Everywhere::Instance().Get<Window>().GetScreen().GetWidth();
    float height = Everywhere::Instance().Get<Window>().GetScreen().GetHeight();

    float fov = Everywhere::Instance().Get<Camera>().GetFoV();
    float aspect = width / height;

    return glm::perspective(glm::radians(fov), aspect, m_depthNear, m_depthFar);
}
