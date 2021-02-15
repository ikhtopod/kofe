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
        Everywhere::Instance().Init<LightStorage>(new LightStorage {});
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
    Everywhere::Instance().Free<LightStorage>();
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
        { { -0.500000, 0.500000, 0.500000 }, { -1.0000, 0.0000, 0.0000 }, { 1.000000, 0.000000 } },
        { { -0.500000, -0.500000, -0.500000 }, { -1.0000, 0.0000, 0.0000 }, { 0.000000, 1.000000 } },
        { { -0.500000, -0.500000, 0.500000 }, { -1.0000, 0.0000, 0.0000 }, { 0.000000, 0.000000 } },
        { { -0.500000, 0.500000, -0.500000 }, { 0.0000, 0.0000, -1.0000 }, { 1.000000, 0.000000 } },
        { { 0.500000, -0.500000, -0.500000 }, { 0.0000, 0.0000, -1.0000 }, { 0.000000, 1.000000 } },
        { { -0.500000, -0.500000, -0.500000 }, { 0.0000, 0.0000, -1.0000 }, { 0.000000, 0.000000 } },
        { { 0.500000, 0.500000, -0.500000 }, { 1.0000, 0.0000, 0.0000 }, { 1.000000, 0.000000 } },
        { { 0.500000, -0.500000, 0.500000 }, { 1.0000, 0.0000, 0.0000 }, { 0.000000, 1.000000 } },
        { { 0.500000, -0.500000, -0.500000 }, { 1.0000, 0.0000, 0.0000 }, { 0.000000, 0.000000 } },
        { { 0.500000, 0.500000, 0.500000 }, { 0.0000, 0.0000, 1.0000 }, { 1.000000, 0.000000 } },
        { { -0.500000, -0.500000, 0.500000 }, { 0.0000, 0.0000, 1.0000 }, { 0.000000, 1.000000 } },
        { { 0.500000, -0.500000, 0.500000 }, { 0.0000, 0.0000, 1.0000 }, { 0.000000, 0.000000 } },
        { { 0.500000, -0.500000, -0.500000 }, { 0.0000, -1.0000, 0.0000 }, { 1.000000, 0.000000 } },
        { { -0.500000, -0.500000, 0.500000 }, { 0.0000, -1.0000, 0.0000 }, { 0.000000, 1.000000 } },
        { { -0.500000, -0.500000, -0.500000 }, { 0.0000, -1.0000, 0.0000 }, { 0.000000, 0.000000 } },
        { { -0.500000, 0.500000, -0.500000 }, { 0.0000, 1.0000, 0.0000 }, { 1.000000, 0.000000 } },
        { { 0.500000, 0.500000, 0.500000 }, { 0.0000, 1.0000, 0.0000 }, { 0.000000, 1.000000 } },
        { { 0.500000, 0.500000, -0.500000 }, { 0.0000, 1.0000, 0.0000 }, { 0.000000, 0.000000 } },
        { { -0.500000, 0.500000, 0.500000 }, { -1.0000, 0.0000, 0.0000 }, { 1.000000, 0.000000 } },
        { { -0.500000, 0.500000, -0.500000 }, { -1.0000, 0.0000, 0.0000 }, { 1.000000, 1.000000 } },
        { { -0.500000, -0.500000, -0.500000 }, { -1.0000, 0.0000, 0.0000 }, { 0.000000, 1.000000 } },
        { { -0.500000, 0.500000, -0.500000 }, { 0.0000, 0.0000, -1.0000 }, { 1.000000, 0.000000 } },
        { { 0.500000, 0.500000, -0.500000 }, { 0.0000, 0.0000, -1.0000 }, { 1.000000, 1.000000 } },
        { { 0.500000, -0.500000, -0.500000 }, { 0.0000, 0.0000, -1.0000 }, { 0.000000, 1.000000 } },
        { { 0.500000, 0.500000, -0.500000 }, { 1.0000, 0.0000, 0.0000 }, { 1.000000, 0.000000 } },
        { { 0.500000, 0.500000, 0.500000 }, { 1.0000, 0.0000, 0.0000 }, { 1.000000, 1.000000 } },
        { { 0.500000, -0.500000, 0.500000 }, { 1.0000, 0.0000, 0.0000 }, { 0.000000, 1.000000 } },
        { { 0.500000, 0.500000, 0.500000 }, { 0.0000, 0.0000, 1.0000 }, { 1.000000, 0.000000 } },
        { { -0.500000, 0.500000, 0.500000 }, { 0.0000, 0.0000, 1.0000 }, { 1.000000, 1.000000 } },
        { { -0.500000, -0.500000, 0.500000 }, { 0.0000, 0.0000, 1.0000 }, { 0.000000, 1.000000 } },
        { { 0.500000, -0.500000, -0.500000 }, { 0.0000, -1.0000, 0.0000 }, { 1.000000, 0.000000 } },
        { { 0.500000, -0.500000, 0.500000 }, { 0.0000, -1.0000, 0.0000 }, { 1.000000, 1.000000 } },
        { { -0.500000, -0.500000, 0.500000 }, { 0.0000, -1.0000, 0.0000 }, { 0.000000, 1.000000 } },
        { { -0.500000, 0.500000, -0.500000 }, { 0.0000, 1.0000, 0.0000 }, { 1.000000, 0.000000 } },
        { { -0.500000, 0.500000, 0.500000 }, { 0.0000, 1.0000, 0.0000 }, { 1.000000, 1.000000 } },
        { { 0.500000, 0.500000, 0.500000 }, { 0.0000, 1.0000, 0.0000 }, { 0.000000, 1.000000 } }
    };

    std::vector<GLuint> indices {
        0, 1, 2, 3, 4, 5,
        6, 7, 8, 9, 10, 11,
        12, 13, 14, 15, 16, 17,
        18, 19, 20, 21, 22, 23,
        24, 25, 26, 27, 28, 29,
        30, 31, 32, 33, 34, 35
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

    std::shared_ptr<PointLight> tempPointLight_01 { new PointLight {} };
    tempPointLight_01->SetColor({ 0.8f, 0.307634f, 0.016358f });
    tempScene->GetObjects().Add(tempPointLight_01);

    std::shared_ptr<PointLight> tempPointLight_02 { new PointLight {} };
    tempPointLight_02->SetColor({ 0.600858f, 0.8f, 0.70773f });
    //tempPointLight_02->GetTransform().SetPosition({ 2.0f, 0.5f, -0.1f });
    tempPointLight_01->Children().Add(tempPointLight_02);

    Space* tempSpace = new Space {};
    tempSpace->GetScenes().Add(tempScene);

    return tempSpace;
}

void Application::DemoMainLoop() {
    auto& object = Everywhere::Instance().Get<Space>().GetScenes().Front()->GetObjects().Front();
    float angleRotation = 100.0f * Everywhere::Instance().Get<DeltaTime>().GetDelta();
    object->GetTransform().AddRotation({ angleRotation / 2.0f, angleRotation, -angleRotation });
    auto& child = object->Children().Front();
    child->GetTransform().AddRotation({ angleRotation, -angleRotation, angleRotation * 2.0f });

    auto& light = Everywhere::Instance().Get<Space>().GetScenes().Front()->GetObjects().At(1);
    light->GetTransform().AddRotation({ angleRotation, angleRotation, angleRotation });
    auto& lightChild = light->Children().At(1);
    float addPos = static_cast<float>(std::sin(glfwGetTime()));
    light->GetTransform().SetPosition({ -addPos, -addPos, -addPos });
    lightChild->GetTransform().SetPosition({ addPos, addPos, addPos });
}
