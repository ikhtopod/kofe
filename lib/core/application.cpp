#include "application.h"

#include "app_exceptions.h"
#include "everywhere.h"
#include "mesh.h"
#include "pointlight.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <cmath>


Application::Application() :
    Application { ":notitle:" } {}

Application::Application(const char* title) :
    Application { std::string { title } } {}


Application::Application(const std::string& title) {
    try {
        // Objects are created in strict order
        Everywhere::Instance().Init<DeltaTime>(new DeltaTime {});
        Everywhere::Instance().Init<MaterialStorage>(new MaterialStorage {});
        Everywhere::Instance().Init<Projection>(new Perspective {});
        Everywhere::Instance().Init<Window>(new Window { ScreenSize { 960, 540 }, title });
        Everywhere::Instance().Init<Graphics>(new OpenGL {});
        Everywhere::Instance().Init<Input>(new Input {});
        Everywhere::Instance().Init<Camera>(new FreeCamera {});
        Everywhere::Instance().Init<Space>(CreateDemoSpace());

        // Additional settings
        Everywhere::Instance().Get<Camera>().GetTransform().AddPosition({ 0.0f, 0.0f, 6.0f });
    } catch (...) {
        Application::~Application();
        throw;
    }
}

Application::~Application() {
    // Objects are destroyed in reverse order
    Everywhere::Instance().Free<Space>();
    Everywhere::Instance().Free<Camera>();
    Everywhere::Instance().Free<Input>();
    Everywhere::Instance().Free<Graphics>();
    Everywhere::Instance().Free<Window>();
    Everywhere::Instance().Free<Projection>();
    Everywhere::Instance().Free<MaterialStorage>();
    Everywhere::Instance().Free<DeltaTime>();

    glfwTerminate();
}


void Application::MainLoop() {
    while (Everywhere::Instance().Get<Window>().CanProcess()) {
        Everywhere::Instance().Get<DeltaTime>().Update();
        Everywhere::Instance().Get<Graphics>().Processing();
        Everywhere::Instance().Get<Input>().Processing();

        DemoMainLoop();

        Everywhere::Instance().Get<Space>().Processing();

        Everywhere::Instance().Get<Window>().Processing();
    }
}

void Application::Run() {
    MainLoop();
}


/* Temp Methods */

Space* Application::CreateDemoSpace() {
    std::shared_ptr<Shader> tempShader { new Shader {} };

    tempShader->SetUniformProcessingFunc([](Shader*) {});

    std::shared_ptr<Texture> tempTexture {
        new Texture {
                std::filesystem::path { R"png(./resources/textures/texture_01.png)png" },
        }
    };

    std::shared_ptr<Material> tempMaterial { new Material {} };
    tempMaterial->GetShaders().Add(tempShader);
    tempMaterial->GetTextures().Add(tempTexture);

    Everywhere::Instance().Get<MaterialStorage>().GetMaterials().Add(tempMaterial);
    size_t materialId = Everywhere::Instance().Get<MaterialStorage>().GetMaterials().Size() - 1;

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
        { { -0.5f, 0.5f, 0.5f }, { 0.0f, 0.0f } }
    };

    std::vector<GLuint> indices {
        0, 1, 2, 2, 3, 0,
        4, 5, 6, 6, 7, 4,
        8, 9, 10, 10, 4, 8,
        11, 2, 12, 12, 13, 11,
        10, 14, 5, 5, 4, 10,
        3, 2, 11, 11, 15, 3
    };

    std::shared_ptr<Mesh> tempMeshObject { new Mesh { vertices, indices } };
    tempMeshObject->SetMaterialId(materialId);
    tempMeshObject->GetTransform().AddPosition({ -1.0f, -1.0f, 0.0f });

    std::shared_ptr<Mesh> tempMeshChildren { new Mesh { vertices, indices } };
    tempMeshObject->SetMaterialId(tempMeshObject->GetMaterialId());
    tempMeshChildren->GetTransform().SetScale({ .5f, .5f, .5f });
    tempMeshChildren->GetTransform().AddPosition({ 2.0f, 2.0f, 0.0f });

    tempMeshObject->Children().Add(tempMeshChildren);

    std::shared_ptr<Scene> tempScene { new Scene {} };
    tempScene->GetObjects().Add(tempMeshObject);

    std::shared_ptr<PointLight> tempPointLight { new PointLight {} };
    tempPointLight->SetColor({ 0.8f, 0.307634f, 0.016358f });
    tempScene->GetObjects().Add(tempPointLight);

    Space* tempSpace = new Space {};
    tempSpace->GetScenes().Add(tempScene);

    return tempSpace;
}

void Application::DemoMainLoop() {
    auto object = Everywhere::Instance().Get<Space>().GetScenes().Front()->GetObjects().Front();
    float angleRotation = 100.0f * Everywhere::Instance().Get<DeltaTime>().GetDelta();
    object->GetTransform().AddRotation({ angleRotation / 2.0f, angleRotation, -angleRotation });
    auto child = object->Children().Front();
    child->GetTransform().AddRotation({ angleRotation, -angleRotation, angleRotation * 2.0f });
}
