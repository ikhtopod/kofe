#include "freecamera.h"

#include "everywhere.h"
#include "axis.h"
#include "util.h"

#include <glm/glm.hpp>
#include <algorithm>


FreeCamera::FreeCamera() : Camera {} {}

void FreeCamera::UpdateInput() {
    Input& input = Everywhere::Instance().Get<Input>();
    DeltaTime& delta = Everywhere::Instance().Get<DeltaTime>();

    const float VELOCITY = DEFAULT_MOVEMENT_SPEED * delta.GetDelta();

    // Keyboard
    if (input.KeyIsPressed(GLFW_KEY_W))
        GetTransform().AddPosition(VELOCITY * m_axis.GetFront());
    if (input.KeyIsPressed(GLFW_KEY_S))
        GetTransform().AddPosition(-VELOCITY * m_axis.GetFront());
    if (input.KeyIsPressed(GLFW_KEY_A))
        GetTransform().AddPosition(-VELOCITY * m_axis.GetRight());
    if (input.KeyIsPressed(GLFW_KEY_D))
        GetTransform().AddPosition(VELOCITY * m_axis.GetRight());
    if (input.KeyIsPressed(GLFW_KEY_Q))
        GetTransform().AddPosition(-VELOCITY * m_axis.GetUp());
    if (input.KeyIsPressed(GLFW_KEY_E))
        GetTransform().AddPosition(VELOCITY * m_axis.GetUp());

    // Mouse
    if (!input.WasChangedMousePosition()) return;

    [[maybe_unused]] glm::vec2 mousePosition = input.GetMousePosition();


    glm::vec3 rotation = GetTransform().GetRotation();

    rotation.x += (m_lastMousePosition.y - mousePosition.y) * DEFAULT_MOUSE_SENSITIVITY_X;
    rotation.y += (mousePosition.x - m_lastMousePosition.x) * DEFAULT_MOUSE_SENSITIVITY_Y;

    rotation.x = std::clamp<float>(rotation.x, MIN_PITCH, MAX_PITCH);
    rotation.y = util::Repeat(rotation.y, MIN_YAW, MAX_YAW);

    GetTransform().SetRotation(rotation);


    UpdateCameraVectors();

    m_lastMousePosition = mousePosition;
}
