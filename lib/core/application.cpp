#include "application.h"

#include "app_exceptions.h"
#include "everywhere.h"

#include <GLFW/glfw3.h>


Application::Application() : Application { ":notitle:" } {}

Application::Application(const char* title) :
    Application { std::string { title } } {}


Application::Application(const std::string& title) {
    try {
        Everywhere::Get().InitWindow(new Window { ScreenSize { 960, 540 }, title });
        Everywhere::Get().InitOpenGL(new OpenGL {});
        Everywhere::Get().InitInput(new Input {});

        /* Temp Space */
        std::shared_ptr<Object> tempObject { new Object {} };
        std::shared_ptr<Scene> tempScene { new Scene {} };
        tempScene->AddObject(tempObject);
        Space* tempSpace = new Space {};
        tempSpace->AddScene(tempScene);

        Everywhere::Get().InitSpace(tempSpace);
        /* ********** */
    } catch (...) {
        Application::~Application();
        throw;
    }
}

Application::~Application() {
    Everywhere::Get().FreeSpace();
    Everywhere::Get().FreeInput();
    Everywhere::Get().FreeOpenGL();
    Everywhere::Get().FreeWindow();

    glfwTerminate();
}


void Application::MainLoop() {
    while (Everywhere::Get().GetWindow().CanProcess()) {
        Everywhere::Get().GetOpenGL().Processing();
        Everywhere::Get().GetInput().Processing();

        Everywhere::Get().GetSpace().Processing();

        Everywhere::Get().GetWindow().SwapBuffers();
    }
}

void Application::Run() {
    MainLoop();
}
