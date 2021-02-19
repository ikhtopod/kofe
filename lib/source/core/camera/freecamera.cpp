#include "camera/freecamera.h"

#include "everywhere.h"
#include "misc/axis.h"
#include "misc/util.h"

#include <glm/glm.hpp>
#include <algorithm>


FreeCamera::FreeCamera() :
    Camera {} {}

void FreeCamera::UpdateInput() {
    Input& input = Everywhere::Instance().Get<Input>();
    DeltaTime& delta = Everywhere::Instance().Get<DeltaTime>();

    // Keyboard
    const float VELOCITY = DEFAULT_MOVEMENT_SPEED * delta.GetDelta();
    Axis axis = GetTransform().GetAxis();

    if (input.KeyIsPressed(GLFW_KEY_W))
        GetTransform().AddPosition(VELOCITY * axis.GetFront());
    if (input.KeyIsPressed(GLFW_KEY_S))
        GetTransform().AddPosition(-VELOCITY * axis.GetFront());
    if (input.KeyIsPressed(GLFW_KEY_A))
        GetTransform().AddPosition(-VELOCITY * axis.GetRight());
    if (input.KeyIsPressed(GLFW_KEY_D))
        GetTransform().AddPosition(VELOCITY * axis.GetRight());
    if (input.KeyIsPressed(GLFW_KEY_Q))
        GetTransform().AddPosition(-VELOCITY * axis.GetUp());
    if (input.KeyIsPressed(GLFW_KEY_E))
        GetTransform().AddPosition(VELOCITY * axis.GetUp());

    // Mouse
    if (!input.WasChangedMousePosition()) return;

    glm::vec2 mousePosition = input.GetMousePosition();

    m_yaw += (mousePosition.x - m_lastMousePosition.x) *
             DEFAULT_MOUSE_SENSITIVITY_YAW * delta.GetDelta();
    m_pitch += (m_lastMousePosition.y - mousePosition.y) *
               DEFAULT_MOUSE_SENSITIVITY_PITCH * delta.GetDelta();

    m_yaw = util::Repeat(m_yaw, MIN_YAW, MAX_YAW);
    m_pitch = std::clamp<float>(m_pitch, MIN_PITCH, MAX_PITCH);

    glm::quat qYaw = glm::angleAxis(glm::radians(-m_yaw), Axis::UP);
    glm::quat qPitch = glm::angleAxis(glm::radians(m_pitch), Axis::RIGHT);

    GetTransform().SetOrientation(qYaw * qPitch);

    m_lastMousePosition = mousePosition;
}
