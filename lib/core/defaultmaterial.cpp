#include "defaultmaterial.h"

#include "everywhere.h"


void DefaultMaterial::DoInitShader() {
    auto UniformMaterialFunc = [this](Shader* shader) {
        if (this == nullptr) return;

        shader->SetVec3("material.ambient", static_cast<glm::vec3>(m_color));
        shader->SetVec3("material.diffuse", static_cast<glm::vec3>(m_color));
        shader->SetVec3("material.specular", glm::vec3 { 0.5f });
        shader->SetFloat("material.shininess", 32.0f);
    };

    auto UniformLightFunc = [this](Shader* shader) {
        if (this == nullptr) return;

        auto& pointLights = Everywhere::Instance().Get<LightStorage>().GetPointLights();

        size_t end = std::min<size_t>(LightStorage::MAX_POINT_LIGHTS, pointLights.size());

        for (size_t i = 0; i < end; ++i) {
            const std::string pointLightsName { "pointLights[" + std::to_string(i) + "]." };

            const std::string positionName { pointLightsName + "position" };
            const std::string ambientName { pointLightsName + "ambient" };
            const std::string diffusetName { pointLightsName + "diffuse" };
            const std::string specularName { pointLightsName + "specular" };

            shader->SetVec3(positionName,
                            static_cast<glm::vec3>(pointLights[i]->GetGlobalTransform().GetPosition()));
            shader->SetVec3(ambientName,
                            static_cast<glm::vec3>(pointLights[i]->GetColor()) * glm::vec3 { .2f });
            shader->SetVec3(diffusetName,
                            static_cast<glm::vec3>(pointLights[i]->GetColor()) * glm::vec3 { .5f });
            shader->SetVec3(specularName, glm::vec3 { 1.0f });
        }
    };

    auto UniformCameraFunc = [this](Shader* shader) {
        if (this == nullptr) return;

        glm::vec3 cameraPosition =
                Everywhere::Instance().Get<Camera>().GetTransform().GetPosition();

        shader->SetVec3("cameraPosition", cameraPosition);
    };

    m_shader->UniformProcessingFunctions().push_back(UniformMaterialFunc);
    m_shader->UniformProcessingFunctions().push_back(UniformLightFunc);
    m_shader->UniformProcessingFunctions().push_back(UniformCameraFunc);
}

DefaultMaterial::DefaultMaterial() :
    Material {},
    m_color { Color::WHITE } {}

Color DefaultMaterial::GetColor() const {
    return m_color;
}

void DefaultMaterial::SetColor(const Color& color) {
    m_color = color;
}
