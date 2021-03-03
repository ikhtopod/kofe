#include "application.h"

#include "everywhere.h"
#include "texture/texturedata.h"
#include "object/model.h"
#include "light/directionallight.h"
#include "light/pointlight.h"
#include "light/spotlight.h"
#include "material/texturematerial.h"
#include "material/phongmaterial.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <cmath>

#ifdef DEBUG
    #include <iostream>
#endif


namespace {

/* Temp Methods */

Space* CreateDemoSpace() {
    std::shared_ptr<Scene> tempScene { new Scene {} };
    Everywhere::Instance().Get<Projection>().SetDepthFar(20.0f);

    const size_t SIZE_END = 3;
    for (size_t i = 0; i < SIZE_END; i++) {
        for (size_t j = 0; j < SIZE_END; ++j) {
            for (size_t k = 0; k < SIZE_END; ++k) {
                auto tempModel = std::make_shared<Model>(
                    R"obj(./resources/models/human/human.obj)obj");
                tempModel->GetTransform().AddPosition({ i * 2, j * 2, k * 2 });
                tempScene->GetObjects().Add(tempModel);
            }
        }
    }

    //auto tempModelLOD = std::make_shared<Model>(
    //    R"obj(./resources/models/human/human.obj)obj");
    //tempScene->GetObjects().Add(tempModelLOD);

    auto tempDirectionalLight_01 = std::make_shared<DirectionalLight>();
    tempDirectionalLight_01->GetTransform().AddRotationYX({ -45.0f, -145.0f, 0.0f });

    //auto tempDirectionalLight_02 = std::make_shared<DirectionalLight>();
    //tempDirectionalLight_02->GetTransform().AddRotationYX({ 0.0f, 180.0f, -45.0f });

    tempScene->GetObjects().Add(tempDirectionalLight_01);
    //tempScene->GetObjects().Add(tempDirectionalLight_02);

    //auto tempSpotLight_01 = std::make_shared<SpotLight>(2.0f, 15.0f);
    //tempSpotLight_01->GetTransform().AddRotationXY(-45.0f, 45.0f);
    //tempScene->GetObjects().Add(tempSpotLight_01);

    Space* tempSpace = new Space {};
    tempSpace->GetScenes().Add(tempScene);

    return tempSpace;
}

void DemoMainLoop() {
    std::string newTitle =
        "kofe | FPS: " +
        std::to_string(Everywhere::Instance().Get<DeltaTime>().GetFPS());
    Everywhere::Instance().Get<Window>().SetTitle(newTitle);

    /*static const float anglePerSec = 180.0f;
    auto light = Everywhere::Instance().Get<Space>().GetScenes().Front()->GetObjects().Back();
    const float angleRotation = anglePerSec * Everywhere::Instance().Get<DeltaTime>().GetDelta();
    light->GetTransform().AddRotationY(angleRotation);*/
}


} // namespace


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
        Everywhere::Instance().Init<TextureStorage>(new TextureStorage {});
        Everywhere::Instance().Init<Input>(new Input {});
        Everywhere::Instance().Init<Camera>(new FreeCamera {});
        Everywhere::Instance().Init<Space>(CreateDemoSpace());

        // Additional settings
        Everywhere::Instance().Get<Camera>().GetTransform().AddPosition({ 0.0f, 0.0f, 2.0f });
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
    Everywhere::Instance().Free<TextureStorage>();
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
