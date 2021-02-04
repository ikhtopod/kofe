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

    const float velocity = DEFAULT_MOVEMENT_SPEED * delta.GetDelta();

    // Keyboard
    if (input.KeyIsPressed(GLFW_KEY_W))
        Position += m_axis.GetFront() * velocity;
    if (input.KeyIsPressed(GLFW_KEY_S))
        Position -= m_axis.GetFront() * velocity;
    if (input.KeyIsPressed(GLFW_KEY_A))
        Position -= m_axis.GetRight() * velocity;
    if (input.KeyIsPressed(GLFW_KEY_D))
        Position += m_axis.GetRight() * velocity;
    if (input.KeyIsPressed(GLFW_KEY_Q))
        Position -= m_axis.GetUp() * velocity;
    if (input.KeyIsPressed(GLFW_KEY_E))
        Position += m_axis.GetUp() * velocity;

    // Mouse
    if (!input.WasChangedMousePosition()) return;

    glm::vec2 mousePosition = input.GetMousePosition();

    RightAngle += (mousePosition.x - m_lastMousePosition.x) * DEFAULT_MOUSE_SENSITIVITY_X;
    UpAngle += (m_lastMousePosition.y - mousePosition.y) * DEFAULT_MOUSE_SENSITIVITY_Y;

    RightAngle = util::Repeat(RightAngle, MIN_YAW, MAX_YAW);
    UpAngle = std::clamp<float>(UpAngle, MIN_PITCH, MAX_PITCH);

    glm::quat Yaw = glm::angleAxis(glm::radians(-RightAngle), glm::vec3(0, 1, 0));
    glm::quat Pitch = glm::angleAxis(glm::radians(UpAngle), glm::vec3(1, 0, 0));

    Orientation = Yaw * Pitch;

    UpdateCameraVectors();

    m_lastMousePosition = mousePosition;
}
