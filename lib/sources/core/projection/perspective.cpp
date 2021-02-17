#include "projection/perspective.h"

#include "everywhere.h"


const float Perspective::DEPTH_NEAR { 0.1f };
const float Perspective::DEPTH_FAR { 2000.0f };


glm::mat4 Perspective::ToMatrix() const {
    float width = Everywhere::Instance().Get<Window>().GetScreen().GetWidth();
    float height = Everywhere::Instance().Get<Window>().GetScreen().GetHeight();

    float fov = Everywhere::Instance().Get<Camera>().GetFoV();
    float aspect = width / height;

    return glm::perspective(glm::radians(fov), aspect, DEPTH_NEAR, DEPTH_FAR);
}
