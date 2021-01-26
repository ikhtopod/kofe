#include "perspective.h"

#include "everywhere.h"


const float Perspective::DEPTH_NEAR { 0.1f };
const float Perspective::DEPTH_FAR { 2000.0f };


glm::mat4 Perspective::ToMatrix() const {
    float width = Everywhere::Instance().Get<Window>().GetScreen().GetWidth();
    float height = Everywhere::Instance().Get<Window>().GetScreen().GetHeight();

    float fov = glm::radians(85.0f);
    float aspect = width / height;

    return glm::perspective(fov, aspect, DEPTH_NEAR, DEPTH_FAR);
}
