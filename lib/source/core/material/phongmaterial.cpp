#include "material/phongmaterial.h"

#include "everywhere.h"


namespace {

static const std::filesystem::path PHONG_VERTEX_PATH {
    R"vert(./resources/shaders/phong-shader.vert)vert"
};

static const std::filesystem::path PHONG_FRAGMENT_PATH {
    R"frag(./resources/shaders/phong-shader.frag)frag"
};

static const Color DEFAULT_AMBIENT { Color::BLACK };
static const Color DEFAULT_DEFFUSE { Color::BLACK };
static const Color DEFAULT_SPECULAR { glm::vec3 { 0.5f } };
static const float DEFAULT_SHININESS { 32.0f };

} // namespace


void PhongMaterial::DoInitShader() {
    auto UniformMaterialFunc = [this](Shader* shader) {
        if (this == nullptr) return;

        shader->SetVec3("material.ambient", static_cast<glm::vec3>(GetAmbient()));
        shader->SetVec3("material.diffuse", static_cast<glm::vec3>(GetDiffuse()));
        shader->SetVec3("material.specular", static_cast<glm::vec3>(GetSpecular()));
        shader->SetFloat("material.shininess", GetShininess());
    };

    auto UniformDirectionalLightFunc = [this](Shader* shader) {
        if (this == nullptr) return;

        auto& directionalLights =
                Everywhere::Instance().Get<LightStorage>().GetDirectionalLights();

        const size_t MAX_LIGHTS = std::min<size_t>(LightStorage::MAX_DIRECTIONAL_LIGHTS,
                                                   directionalLights.size());

        shader->SetUInt("directionalLightArraySize", MAX_LIGHTS);

        for (size_t i = 0; i < MAX_LIGHTS; ++i) {
            const std::string directionalLightsName { "directionalLights[" + std::to_string(i) + "]." };

            const std::string directionName { directionalLightsName + "direction" };
            const std::string ambientName { directionalLightsName + "ambient" };
            const std::string diffusetName { directionalLightsName + "diffuse" };
            const std::string specularName { directionalLightsName + "specular" };

            shader->SetVec3(directionName,
                            directionalLights[i]->GetGlobalTransform().GetAxis().GetFront());
            shader->SetVec3(ambientName,
                            static_cast<glm::vec3>(directionalLights[i]->GetAmbientColor()));
            shader->SetVec3(diffusetName,
                            static_cast<glm::vec3>(directionalLights[i]->GetDiffuseColor()));
            shader->SetVec3(specularName,
                            static_cast<glm::vec3>(directionalLights[i]->GetSpecularColor()));
        }
    };

    auto UniformPointLightFunc = [this](Shader* shader) {
        if (this == nullptr) return;

        auto& pointLights =
                Everywhere::Instance().Get<LightStorage>().GetPointLights();

        const size_t MAX_LIGHTS = std::min<size_t>(LightStorage::MAX_POINT_LIGHTS,
                                                   pointLights.size());

        shader->SetUInt("pointLightArraySize", MAX_LIGHTS);

        for (size_t i = 0; i < MAX_LIGHTS; ++i) {
            const std::string pointLightsName { "pointLights[" + std::to_string(i) + "]." };

            const std::string positionName { pointLightsName + "position" };
            const std::string ambientName { pointLightsName + "ambient" };
            const std::string diffusetName { pointLightsName + "diffuse" };
            const std::string specularName { pointLightsName + "specular" };
            const std::string constantName { pointLightsName + "constant" };
            const std::string linearName { pointLightsName + "linear" };
            const std::string quadraticName { pointLightsName + "quadratic" };

            shader->SetVec3(positionName,
                            static_cast<glm::vec3>(pointLights[i]->GetGlobalTransform().GetPosition()));
            shader->SetVec3(ambientName,
                            static_cast<glm::vec3>(pointLights[i]->GetAmbientColor()));
            shader->SetVec3(diffusetName,
                            static_cast<glm::vec3>(pointLights[i]->GetDiffuseColor()));
            shader->SetVec3(specularName,
                            static_cast<glm::vec3>(pointLights[i]->GetSpecularColor()));
            shader->SetFloat(constantName, pointLights[i]->GetConstant());
            shader->SetFloat(linearName, pointLights[i]->GetLinear());
            shader->SetFloat(quadraticName, pointLights[i]->GetQuadratic());
        }
    };

    auto UniformSpotLightFunc = [this](Shader* shader) {
        if (this == nullptr) return;

        auto& spotLights =
                Everywhere::Instance().Get<LightStorage>().GetSpotLights();

        const size_t MAX_LIGHTS = std::min<size_t>(LightStorage::MAX_POINT_LIGHTS,
                                                   spotLights.size());

        shader->SetUInt("spotLightArraySize", MAX_LIGHTS);

        for (size_t i = 0; i < MAX_LIGHTS; ++i) {
            const std::string spotLightsName { "spotLights[" + std::to_string(i) + "]." };

            const std::string positionName { spotLightsName + "position" };
            const std::string directionName { spotLightsName + "direction" };
            const std::string cutoffName { spotLightsName + "cutoff" };
            const std::string ambientName { spotLightsName + "ambient" };
            const std::string diffusetName { spotLightsName + "diffuse" };
            const std::string specularName { spotLightsName + "specular" };
            const std::string constantName { spotLightsName + "constant" };
            const std::string linearName { spotLightsName + "linear" };
            const std::string quadraticName { spotLightsName + "quadratic" };

            shader->SetVec3(positionName,
                            static_cast<glm::vec3>(spotLights[i]->GetGlobalTransform().GetPosition()));
            shader->SetVec3(directionName,
                            spotLights[i]->GetGlobalTransform().GetAxis().GetFront());
            shader->SetFloat(cutoffName, glm::cos(spotLights[i]->GetCutoffRadians()));
            shader->SetVec3(ambientName,
                            static_cast<glm::vec3>(spotLights[i]->GetAmbientColor()));
            shader->SetVec3(diffusetName,
                            static_cast<glm::vec3>(spotLights[i]->GetDiffuseColor()));
            shader->SetVec3(specularName,
                            static_cast<glm::vec3>(spotLights[i]->GetSpecularColor()));
            shader->SetFloat(constantName, spotLights[i]->GetConstant());
            shader->SetFloat(linearName, spotLights[i]->GetLinear());
            shader->SetFloat(quadraticName, spotLights[i]->GetQuadratic());
        }
    };

    auto UniformCameraFunc = [this](Shader* shader) {
        if (this == nullptr) return;

        glm::vec3 cameraPosition =
                Everywhere::Instance().Get<Camera>().GetTransform().GetPosition();

        shader->SetVec3("cameraPosition", cameraPosition);
    };

    m_shader->UniformProcessingFunctions().push_back(UniformMaterialFunc);
    m_shader->UniformProcessingFunctions().push_back(UniformDirectionalLightFunc);
    m_shader->UniformProcessingFunctions().push_back(UniformPointLightFunc);
    m_shader->UniformProcessingFunctions().push_back(UniformSpotLightFunc);
    m_shader->UniformProcessingFunctions().push_back(UniformCameraFunc);
}

PhongMaterial::PhongMaterial() :
    PhongMaterial { DEFAULT_AMBIENT, DEFAULT_DEFFUSE,
                    DEFAULT_SPECULAR, DEFAULT_SHININESS } {}


PhongMaterial::PhongMaterial(const Color& ambient, const Color& diffuse,
                             const Color& specular, float shininess) :
    Material { std::shared_ptr<Shader> {
            new Shader { PHONG_VERTEX_PATH, PHONG_FRAGMENT_PATH } } },
    m_ambient { ambient }, m_diffuse { diffuse },
    m_specular { specular }, m_shininess { shininess } {}

Color PhongMaterial::GetAmbient() const {
    return m_ambient;
}

Color PhongMaterial::GetDiffuse() const {
    return m_diffuse;
}

Color PhongMaterial::GetSpecular() const {
    return m_specular;
}

float PhongMaterial::GetShininess() const {
    return m_shininess;
}

void PhongMaterial::SetAmbient(const Color& ambient) {
    m_ambient = ambient;
}

void PhongMaterial::SetDiffuse(const Color& diffuse) {
    m_diffuse = diffuse;
}

void PhongMaterial::SetSpecular(const Color& specular) {
    m_specular = specular;
}

void PhongMaterial::SetShininess(float shininess) {
    m_shininess = shininess;
}

void PhongMaterial::SetAmbientAndDiffuse(const Color& value) {
    SetAmbient(value);
    SetDiffuse(value);
}

void PhongMaterial::SetAllParameters(const Color& ambient, const Color& diffuse,
                                     const Color& specular, float shininess) {
    SetAmbient(ambient);
    SetDiffuse(diffuse);
    SetSpecular(specular);
    SetShininess(shininess);
}