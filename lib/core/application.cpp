#include "application.h"

#include "app_exceptions.h"
#include "everywhere.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <cmath>


Application::Application() : Application { ":notitle:" } {}

Application::Application(const char* title) :
    Application { std::string { title } } {}


Application::Application(const std::string& title) {
    try {
        Everywhere::Instance().window().Init(new Window { ScreenSize { 960, 540 }, title });
        Everywhere::Instance().openGL().Init(new OpenGL {});
        Everywhere::Instance().input().Init(new Input {});
        Everywhere::Instance().space().Init(CreateDemoSpace());
    } catch (...) {
        Application::~Application();
        throw;
    }
}

Application::~Application() {
    Everywhere::Instance().space().Free();
    Everywhere::Instance().input().Free();
    Everywhere::Instance().openGL().Free();
    Everywhere::Instance().window().Free();

    glfwTerminate();
}


void Application::MainLoop() {
    while (Everywhere::Instance().window().Get().CanProcess()) {
        Everywhere::Instance().openGL().Get().Processing();
        Everywhere::Instance().input().Get().Processing();

        Everywhere::Instance().space().Get().Processing();

        Everywhere::Instance().window().Get().SwapBuffers();
    }
}

void Application::Run() {
    MainLoop();
}


/* Temp Methods */

Space* Application::CreateDemoSpace() {
    std::vector<Vertex> vertices {
        { { -0.5f, -0.5f, -0.5f }, { 0.0f, 0.0f } },
        { { 0.5f, -0.5f, -0.5f }, { 1.0f, 0.0f } },
        { { 0.5f, 0.5f, -0.5f }, { 1.0f, 1.0f } },
        { { -0.5f, 0.5f, -0.5f }, { 0.0f, 1.0f } },
        { { -0.5f, -0.5f, 0.5f }, { 0.0f, 0.0f } },
        { { 0.5f, -0.5f, 0.5f }, { 1.0f, 0.0f } },
        { { 0.5f, 0.5f, 0.5f }, { 1.0f, 1.0f } },
        { { -0.5f, 0.5f, 0.5f }, { 0.0f, 1.0f } },
        { { -0.5f, 0.5f, 0.5f }, { 1.0f, 0.0f } },
        { { -0.5f, 0.5f, -0.5f }, { 1.0f, 1.0f } },
        { { -0.5f, -0.5f, -0.5f }, { 0.0f, 1.0f } },
        { { 0.5f, 0.5f, 0.5f }, { 1.0f, 0.0f } },
        { { 0.5f, -0.5f, -0.5f }, { 0.0f, 1.0f } },
        { { 0.5f, -0.5f, 0.5f }, { 0.0f, 0.0f } },
        { { 0.5f, -0.5f, -0.5f }, { 1.0f, 1.0f } },
        { { -0.5f, 0.5f, 0.5f }, { 0.0f, 0.0f } },
    };

    std::vector<GLuint> indices {
        0, 1, 2, 2, 3, 0,
        4, 5, 6, 6, 7, 4,
        8, 9, 10, 10, 4, 8,
        11, 2, 12, 12, 13, 11,
        10, 14, 5, 5, 4, 10,
        3, 2, 11, 11, 15, 3,
    };

    std::shared_ptr<Mesh> tempMesh { new Mesh { vertices, indices } };
    std::shared_ptr<Shader> tempShader {
        new Shader {
            std::filesystem::path { R"vert(./resources/shaders/default.vert)vert" },
            std::filesystem::path { R"frag(./resources/shaders/default.frag)frag" },
        }
    };

    tempShader->SetUniformProcessingFunc([](Shader* that) {
        static const glm::mat4 IDENTITY_MATRIX { 1.0f };
        static const ScreenSize& screen = Everywhere::Instance().window().Get().GetScreen();

        glm::mat4 transform = IDENTITY_MATRIX;
        GLdouble angleAccel { 40.0 };
        GLfloat rotationAngleRad = glm::radians(static_cast<GLfloat>(std::fmod(glfwGetTime() * angleAccel, 360.0)));
        transform = glm::rotate(transform, rotationAngleRad, glm::vec3(1.f, .0f, 1.0f));
        transform = glm::scale(transform, glm::vec3(1.0f));

        that->SetMat4("model", transform);
        that->SetMat4("view", glm::translate(IDENTITY_MATRIX, glm::vec3(.0f, .0f, -2.f)));
        that->SetMat4("projection",
                      glm::perspective(glm::radians(85.0f),
                                       static_cast<GLfloat>(screen.GetWidth()) /
                                       static_cast<GLfloat>(screen.GetHeight()),
                                       .1f, 2000.f));
    });

    std::shared_ptr<Texture> tempTexture {
        new Texture {
            std::filesystem::path { R"png(./resources/textures/texture_01.png)png" },
        }
    };
    std::shared_ptr<Material> tempMaterial { new Material {} };
    tempMaterial->GetShaders().Add(tempShader);
    tempMaterial->GetTextures().Add(tempTexture);
    std::shared_ptr<Object> tempObject { new Object {} };
    tempObject->GetMeshes().Add(tempMesh);
    tempObject->GetMaterials().Add(tempMaterial);
    std::shared_ptr<Scene> tempScene { new Scene {} };
    tempScene->GetObjects().Add(tempObject);
    Space* tempSpace = new Space {};
    tempSpace->GetScenes().Add(tempScene);

    return tempSpace;
}
