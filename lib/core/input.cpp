#include "input.h"

#include "everywhere.h"


void Input::AssignCallbacks() {
    GLFWwindow* context = Everywhere::Get().GetWindow().GetContext();
    glfwSetFramebufferSizeCallback(context, Input::FramebufferSizeCallback);
}

void Input::FramebufferSizeCallback(GLFWwindow*, int width, int height) {
    Everywhere::Get().GetWindow().GetScreen().Update(width, height);
    Everywhere::Get().GetOpenGL().UpdateViewportSize();
}

void Input::Init() {
    GLFWwindow* context = Everywhere::Get().GetWindow().GetContext();
    Input::AssignCallbacks();
    glfwSetInputMode(context, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

Input::Input() {
    Init();
}

void Input::KeyEvents() {
    GLFWwindow* context = Everywhere::Get().GetWindow().GetContext();

    if (glfwGetKey(context, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(context, GLFW_TRUE);
    }
}

void Input::Processing() {
    KeyEvents();
    glfwPollEvents();
}
