#include "freecamera.h"

#include "everywhere.h"
#include "axis.h"

#include <glm/glm.hpp>


FreeCamera::FreeCamera() {}

glm::mat4 FreeCamera::ToMatrix() const {
    return glm::lookAt(GetTransform().GetPosition(),
                       GetTransform().GetPosition() + Axis::BACKWARD,
                       Axis::UP);
}

void FreeCamera::UpdateInput() {
    Input& input = Everywhere::Instance().Get<Input>();
    DeltaTime& delta = Everywhere::Instance().Get<DeltaTime>();

    const float VELOCITY = MOVEMENT_SPEED * delta.GetDelta();

    // Keyboard
    if (input.KeyIsPressed(GLFW_KEY_W))
        GetTransform().AddPosition(VELOCITY * Axis::BACKWARD);
    if (input.KeyIsPressed(GLFW_KEY_S))
        GetTransform().AddPosition(VELOCITY * Axis::FORWARD);

    if (input.KeyIsPressed(GLFW_KEY_A))
        GetTransform().AddPosition(VELOCITY * Axis::LEFT);
    if (input.KeyIsPressed(GLFW_KEY_D))
        GetTransform().AddPosition(VELOCITY * Axis::RIGHT);
    if (input.KeyIsPressed(GLFW_KEY_Q))
        GetTransform().AddPosition(VELOCITY * Axis::DOWN);
    if (input.KeyIsPressed(GLFW_KEY_E))
        GetTransform().AddPosition(VELOCITY * Axis::UP);

    // Mouse
    if (!input.WasChangedMousePosition()) return;

    glm::vec2 mousePosition = input.GetMousePosition();
}
