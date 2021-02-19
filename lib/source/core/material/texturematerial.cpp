#include "material/texturematerial.h"

#include "everywhere.h"

#include <filesystem>


namespace {

static const std::filesystem::path TEXTURE_VERTEX_PATH {
    R"vert(./resources/shaders/texture-shader.vert)vert"
};

static const std::filesystem::path TEXTURE_FRAGMENT_PATH {
    R"frag(./resources/shaders/texture-shader.frag)frag"
};

static const std::filesystem::path DEFAULT_TETURE_PATH {
    R"png(./resources/textures/default_texture.png)png"
};

static constexpr float DEFAULT_SHININESS { 32.0f };

} // namespace


void TextureMaterial::DoInitShader() {
    auto UniformMaterialFunc = [this]([[maybe_unused]] Shader* shader) {
        if (this == nullptr) return;
        shader->SetInt("material.diffuse", GetDiffuse()->GetTextureUnit() - GL_TEXTURE0);
        shader->SetInt("material.specular", GetSpecular()->GetTextureUnit() - GL_TEXTURE0);
        shader->SetInt("material.emission", GetEmission()->GetTextureUnit() - GL_TEXTURE0);
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
                            static_cast<glm::vec3>(directionalLights[i]->GetGlobalTransform().GetRotation()));
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


TextureMaterial::TextureMaterial() :
    TextureMaterial {
        std::shared_ptr<Texture> { new Texture { ::DEFAULT_TETURE_PATH, GL_TEXTURE0 } },
        std::shared_ptr<Texture> { new Texture { ::DEFAULT_TETURE_PATH, GL_TEXTURE1 } },
        std::shared_ptr<Texture> { new Texture { ::DEFAULT_TETURE_PATH, GL_TEXTURE2 } },
        ::DEFAULT_SHININESS
    } {}


TextureMaterial::TextureMaterial(const std::shared_ptr<Texture>& diffuse,
                                 const std::shared_ptr<Texture>& specular,
                                 const std::shared_ptr<Texture>& emission) :
    TextureMaterial { diffuse, specular, emission, ::DEFAULT_SHININESS } {}

TextureMaterial::TextureMaterial(const std::shared_ptr<Texture>& diffuse,
                                 const std::shared_ptr<Texture>& specular,
                                 const std::shared_ptr<Texture>& emission,
                                 float shininess) :
    Material { std::shared_ptr<Shader> {
            new Shader { TEXTURE_VERTEX_PATH, TEXTURE_FRAGMENT_PATH } } },
    m_diffuse { diffuse },
    m_specular { specular },
    m_emission { emission },
    m_shininess { shininess } {}


void TextureMaterial::Processing() {
    Material::Processing();

    m_diffuse->Processing();
    m_specular->Processing();
    m_emission->Processing();
}


std::shared_ptr<Texture> TextureMaterial::GetDiffuse() const {
    return m_diffuse;
}

std::shared_ptr<Texture> TextureMaterial::GetSpecular() const {
    return m_specular;
}

std::shared_ptr<Texture> TextureMaterial::GetEmission() const {
    return m_emission;
}

float TextureMaterial::GetShininess() const {
    return m_shininess;
}

void TextureMaterial::SetDiffuse(const std::shared_ptr<Texture>& diffuse) {
    m_diffuse = diffuse;
}

void TextureMaterial::SetSpecular(const std::shared_ptr<Texture>& specular) {
    m_specular = specular;
}

void TextureMaterial::SetEmission(const std::shared_ptr<Texture>& emission) {
    m_emission = emission;
}

void TextureMaterial::SetShininess(float shininess) {
    m_shininess = shininess;
}
