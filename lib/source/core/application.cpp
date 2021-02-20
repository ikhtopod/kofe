#include "application.h"

#include "everywhere.h"
#include "mesh/mesh.h"
#include "light/directionallight.h"
#include "light/pointlight.h"
#include "light/spotlight.h"
#include "material/texturematerial.h"
#include "material/phongmaterial.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <cmath>
#include <iostream>


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
        Everywhere::Instance().Get<Camera>().GetTransform().AddPosition({ 0.0f, 0.0f, 3.0f });
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

        //DemoMainLoop();

        Everywhere::Instance().Get<Space>().Processing();

        Everywhere::Instance().Get<Window>().Processing();
    }
}

void Application::Run() {
    MainLoop();
}


/* Temp Methods */

Space* Application::CreateDemoSpace() {
    std::shared_ptr<Texture> tempDiffuseTexture {
        new Texture {
            std::filesystem::path {
                R"png(./resources/textures/texture_box_01.png)png" } }
    };

    std::shared_ptr<Texture> tempSpecularTexture {
        new Texture { std::filesystem::path {
                          R"png(./resources/textures/texture_box_01_specular.png)png" },
                      tempDiffuseTexture->NextTextureUnit() }
    };

    std::shared_ptr<Texture> tempEmissionTexture {
        new Texture { std::filesystem::path {
                          R"png(./resources/textures/texture_box_01_emission.png)png" },
                      tempSpecularTexture->NextTextureUnit() }
    };

    std::shared_ptr<TextureMaterial> tempTextureMaterial {
        new TextureMaterial { tempDiffuseTexture,
                              tempSpecularTexture,
                              tempEmissionTexture }
    };

    auto tempPhongMaterial = std::make_shared<PhongMaterial>();
    tempPhongMaterial->SetAmbientAndDiffuse(Color::GREEN);

    Everywhere::Instance().Get<MaterialStorage>().GetMaterials().Add(tempTextureMaterial);
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

    std::shared_ptr<Mesh> tempMeshObject_01 { new Mesh { vertices, indices } };
    tempMeshObject_01->SetMaterialId(materialId);
    tempMeshObject_01->GetTransform().AddPosition({ 0.0f, 0.0f, -1.0f });

    std::shared_ptr<Scene> tempScene { new Scene {} };
    tempScene->GetObjects().Add(tempMeshObject_01);

    //auto tempDirectionalLight_01 = std::make_shared<DirectionalLight>();
    //tempDirectionalLight_01->GetTransform().SetRotation({ 45.0f, 0.0f, 0.0f });
    //tempScene->GetObjects().Add(tempDirectionalLight_01);

    auto tempSpotLight_01 = std::make_shared<SpotLight>(2.0f, 25.0f);
    tempSpotLight_01->GetTransform().AddRotationY(180.0f);
    tempScene->GetObjects().Add(tempSpotLight_01);

    Space* tempSpace = new Space {};
    tempSpace->GetScenes().Add(tempScene);

    return tempSpace;
}

void Application::DemoMainLoop() {
    static const float anglePerSec = 180.0f;
    auto& light = Everywhere::Instance().Get<Space>().GetScenes().Front()->GetObjects().Back();
    const float angleRotation = anglePerSec * Everywhere::Instance().Get<DeltaTime>().GetDelta();
    light->GetTransform().AddRotationY(angleRotation);
}
