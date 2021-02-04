#include "input.h"

#include "everywhere.h"
#include "util.h"

#include <cmath>
#include <thread>


Input* Input::GetThisInput() {
    GLFWwindow* context = Everywhere::Instance().Get<Window>().GetContext();
    return static_cast<Input*>(glfwGetWindowUserPointer(context));
}

void Input::FramebufferSizeCallback(GLFWwindow*, int width, int height) {
    Everywhere::Instance().Get<Window>().GetScreen().Update(width, height);
    Everywhere::Instance().Get<OpenGL>().UpdateViewportSize();
}

void Input::ScrollCallback(GLFWwindow*, double x, double y) {
    Input* thisInput = Input::GetThisInput();

    if (thisInput == nullptr) return;

    thisInput->SetScrollValue( { static_cast<float>(x), static_cast<float>(y) } );
}

void Input::MousePositionCallback(GLFWwindow*, double x, double y) {
    Input* thisInput = Input::GetThisInput();

    if (thisInput == nullptr) return;

    thisInput->SetMousePosition( { static_cast<float>(x), static_cast<float>(y) } );

    thisInput->SetWasChangedMousePosition(true);
}

void Input::AssignCallbacks() {
    glfwSetWindowUserPointer(context, this);

    glfwSetFramebufferSizeCallback(context, Input::FramebufferSizeCallback);
    glfwSetScrollCallback(context, Input::ScrollCallback);
    glfwSetCursorPosCallback(context, Input::MousePositionCallback);
}

void Input::FirstMousePosition() {
    double x {}, y {};
    glfwGetCursorPos(context, &x, &y);
    SetMousePosition({ static_cast<float>(x), static_cast<float>(y) });
}

void Input::Init() {
    UpdateContext();

    Input::AssignCallbacks();

    glfwSetCursorPos(context, 1, 1);
    glfwSetInputMode(context, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
    glfwSetCursorPos(context, 0, 0);
    glfwSetInputMode(context, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    FirstMousePosition();
}

Input::Input() :
    ObservableInput {},
    context {},
    m_mousePosition {},
    m_scrollValue {},
    m_wasChangedMousePosition { false }
{
    Init();
}

glm::vec2 Input::GetMousePosition() const {
    return m_mousePosition;
}

void Input::SetMousePosition(const glm::vec2& mousePosition) {
    m_mousePosition = mousePosition;
}

void Input::SetMousePosition(glm::vec2&& mousePosition) noexcept {
    m_mousePosition.x = std::move(mousePosition.x);
    m_mousePosition.y = std::move(mousePosition.y);
}

glm::vec2 Input::GetScrollValue() const {
    return m_scrollValue;
}

void Input::SetScrollValue(const glm::vec2& scrollValue) {
    m_scrollValue = scrollValue;
}

void Input::SetScrollValue(glm::vec2&& scrollValue) noexcept {
    m_scrollValue.x = std::move(scrollValue.x);
    m_scrollValue.y = std::move(scrollValue.y);
}

void Input::SetWasChangedMousePosition(bool wasChanged) {
    m_wasChangedMousePosition = wasChanged;
}

bool Input::MouseButtonIsReleased(int key) const {
    return glfwGetMouseButton(context, key) == GLFW_RELEASE;
}

bool Input::MouseButtonIsPressed(int key) const {
    return glfwGetMouseButton(context, key) == GLFW_PRESS;
}

bool Input::WasChangedMousePosition() const {
    return m_wasChangedMousePosition;
}

bool Input::KeyIsReleased(int key) const {
    return glfwGetKey(context, key) == GLFW_RELEASE;
}

bool Input::KeyIsPressed(int key) const {
    return glfwGetKey(context, key) == GLFW_PRESS;
}

void Input::KeyEvents() {
    if (glfwGetKey(context, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(context, GLFW_TRUE);
    }
}

void Input::UpdateContext() {
    context = Everywhere::Instance().Get<Window>().GetContext();
}

void Input::Processing() {
    UpdateContext();
    KeyEvents();

    SetWasChangedMousePosition(false); // need before glfwPollEvents()
    glfwPollEvents();
    Notify();
}
