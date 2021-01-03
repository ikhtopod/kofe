#include "application.h"

#include "app_exceptions.h"
#include "everywhere.h"

#include <GLFW/glfw3.h>


Application::Application() : Application { ":notitle:" } {}

Application::Application(const std::string& title) {
    try {
        Window* window = new Window { ScreenSize { 960, 540 }, title };
        Everywhere::Get().InitWindow(window);
    } catch (...) {
        Application::~Application();
        throw;
    }
}

Application::Application(const char* title) :
    Application { std::string { title } } {}

Application::~Application() {
    Everywhere::Get().FreeWindow();
    glfwTerminate();
}


void Application::MainLoop() {
    GLFWwindow* context = Everywhere::Get().GetWindow().GetContext();

    while (glfwWindowShouldClose(context) == GLFW_FALSE) {
        glfwPollEvents();
        glfwSwapBuffers(context);
    }
}

void Application::Run() {
    MainLoop();
}
