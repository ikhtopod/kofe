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
        std::shared_ptr<Mesh> tempMesh { new Mesh {} };
        std::shared_ptr<Material> tempMaterial { new Material {} };
        std::shared_ptr<Object> tempObject { new Object {} };
        tempObject->GetMeshes().Add(tempMesh);
        tempObject->GetMaterials().Add(tempMaterial);
        std::shared_ptr<Scene> tempScene { new Scene {} };
        tempScene->GetObjects().Add(tempObject);
        Space* tempSpace = new Space {};
        tempSpace->GetScenes().Add(tempScene);
        /* ********** */
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
