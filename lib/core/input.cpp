#include "input.h"

#include "everywhere.h"


void Input::AssignCallbacks() {
    GLFWwindow* context = Everywhere::Instance().Get<Window>().GetContext();
    glfwSetFramebufferSizeCallback(context, Input::FramebufferSizeCallback);
}

void Input::FramebufferSizeCallback(GLFWwindow*, int width, int height) {
    Everywhere::Instance().Get<Window>().GetScreen().Update(width, height);
    Everywhere::Instance().Get<OpenGL>().UpdateViewportSize();
}

void Input::Init() {
    GLFWwindow* context = Everywhere::Instance().Get<Window>().GetContext();
    Input::AssignCallbacks();
    glfwSetInputMode(context, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

Input::Input() {
    Init();
}

void Input::KeyEvents() {
    GLFWwindow* context = Everywhere::Instance().Get<Window>().GetContext();

    if (glfwGetKey(context, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(context, GLFW_TRUE);
    }
}

void Input::Processing() {
    KeyEvents();
    glfwPollEvents();
}
