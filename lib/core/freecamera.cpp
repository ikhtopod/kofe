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

    glm::quat quatFront = Orientation * glm::quat(0, 0, 0, -1) * glm::conjugate(Orientation);
    glm::vec3 Front = { quatFront.x, quatFront.y, quatFront.z };
    glm::vec3 Right = glm::normalize(glm::cross(Front, glm::vec3(0, 1, 0)));
    glm::vec3 Up = glm::normalize(glm::cross(Right, Front));

    // Keyboard
    if (input.KeyIsPressed(GLFW_KEY_W))
        Position += Front * velocity;
    if (input.KeyIsPressed(GLFW_KEY_S))
        Position -= Front * velocity;
    if (input.KeyIsPressed(GLFW_KEY_A))
        Position -= Right * velocity;
    if (input.KeyIsPressed(GLFW_KEY_D))
        Position += Right * velocity;
    if (input.KeyIsPressed(GLFW_KEY_Q))
        Position -= Up * velocity;
    if (input.KeyIsPressed(GLFW_KEY_E))
        Position += Up * velocity;

    // Mouse
    if (!input.WasChangedMousePosition()) return;

    glm::vec2 mousePosition = input.GetMousePosition();

    RightAngle += (mousePosition.x - m_lastMousePosition.x) * DEFAULT_MOUSE_SENSITIVITY_X;
    UpAngle += (m_lastMousePosition.y - mousePosition.y) * DEFAULT_MOUSE_SENSITIVITY_Y;

    RightAngle = util::Repeat(RightAngle, MIN_YAW, MAX_YAW);
    UpAngle = std::clamp<float>(UpAngle, MIN_PITCH, MAX_PITCH);

    UpdateCameraVectors();

    m_lastMousePosition = mousePosition;
}
