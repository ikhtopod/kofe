#include "freecamera.h"

#include "everywhere.h"

#include <glm/glm.hpp>


FreeCamera::FreeCamera() {}

glm::mat4 FreeCamera::ToMatrix() const {
    return {};
}

void FreeCamera::UpdateInput() {
    Input& input = Everywhere::Instance().Get<Input>();
    glm::vec2 mousePosition = input.GetMousePosition();
}
