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

static const std::filesystem::path DEFAULT_TEXTURE_PATH {
    R"png(./resources/textures/default_texture.png)png"
};

static constexpr float DEFAULT_SHININESS { 32.0f };

} // namespace


void TextureMaterial::DoInitShader() {
    auto UniformMaterialFunc = [this]([[maybe_unused]] Shader* shader) {
        if (this == nullptr) return;
        shader->SetInt("material.diffuse", GetDiffuse()->GetTextureUnit());
        shader->SetInt("material.specular", GetSpecular()->GetTextureUnit());
        shader->SetInt("material.emission", GetEmission()->GetTextureUnit());
        shader->SetFloat("material.shininess", GetShininess());
    };

    auto UniformDirectionalLightFunc = [this](Shader* shader) {
        if (this == nullptr) return;

        auto& directionalLights =
            Everywhere::Instance().Get<LightStorage>().GetDirectionalLights();

        const size_t MAX_LIGHTS = std::min<size_t>(LightStorage::MAX_DIRECTIONAL_LIGHTS,
                                                   directionalLights.Size());

        shader->SetUInt("directionalLightArraySize", MAX_LIGHTS);

        for (size_t i = 0; i < MAX_LIGHTS; ++i) {
            if (!directionalLights[i]) continue;

            DirectionalLight* directionalLight = directionalLights[i];

            const std::string directionalLightsName { "directionalLights[" + std::to_string(i) + "]." };
            const std::string directionName { directionalLightsName + "direction" };
            const std::string ambientName { directionalLightsName + "ambient" };
            const std::string diffusetName { directionalLightsName + "diffuse" };
            const std::string specularName { directionalLightsName + "specular" };

            shader->SetVec3(directionName,
                            directionalLight->GetGlobalTransform().GetAxis().GetFront());
            shader->SetVec3(ambientName,
                            static_cast<glm::vec3>(directionalLight->GetAmbientColor()));
            shader->SetVec3(diffusetName,
                            static_cast<glm::vec3>(directionalLight->GetDiffuseColor()));
            shader->SetVec3(specularName,
                            static_cast<glm::vec3>(directionalLight->GetSpecularColor()));
        }
    };

    auto UniformPointLightFunc = [this](Shader* shader) {
        if (this == nullptr) return;

        auto& pointLights =
            Everywhere::Instance().Get<LightStorage>().GetPointLights();

        const size_t MAX_LIGHTS = std::min<size_t>(LightStorage::MAX_POINT_LIGHTS,
                                                   pointLights.Size());

        shader->SetUInt("pointLightArraySize", MAX_LIGHTS);

        for (size_t i = 0; i < MAX_LIGHTS; ++i) {
            if (!pointLights[i]) continue;

            PointLight* pointLight = pointLights[i];

            const std::string pointLightsName { "pointLights[" + std::to_string(i) + "]." };
            const std::string positionName { pointLightsName + "position" };
            const std::string ambientName { pointLightsName + "ambient" };
            const std::string diffusetName { pointLightsName + "diffuse" };
            const std::string specularName { pointLightsName + "specular" };
            const std::string constantName { pointLightsName + "constant" };
            const std::string linearName { pointLightsName + "linear" };
            const std::string quadraticName { pointLightsName + "quadratic" };

            shader->SetVec3(positionName,
                            static_cast<glm::vec3>(pointLight->GetGlobalTransform().GetPosition()));
            shader->SetVec3(ambientName,
                            static_cast<glm::vec3>(pointLight->GetAmbientColor()));
            shader->SetVec3(diffusetName,
                            static_cast<glm::vec3>(pointLight->GetDiffuseColor()));
            shader->SetVec3(specularName,
                            static_cast<glm::vec3>(pointLight->GetSpecularColor()));
            shader->SetFloat(constantName, pointLight->GetConstant());
            shader->SetFloat(linearName, pointLight->GetLinear());
            shader->SetFloat(quadraticName, pointLight->GetQuadratic());
        }
    };

    auto UniformSpotLightFunc = [this](Shader* shader) {
        if (this == nullptr) return;

        auto& spotLights =
            Everywhere::Instance().Get<LightStorage>().GetSpotLights();

        const size_t MAX_LIGHTS = std::min<size_t>(LightStorage::MAX_POINT_LIGHTS,
                                                   spotLights.Size());

        shader->SetUInt("spotLightArraySize", MAX_LIGHTS);

        for (size_t i = 0; i < MAX_LIGHTS; ++i) {
            if (!spotLights[i]) continue;

            SpotLight* spotLight = spotLights[i];

            const std::string spotLightsName { "spotLights[" + std::to_string(i) + "]." };
            const std::string positionName { spotLightsName + "position" };
            const std::string directionName { spotLightsName + "direction" };
            const std::string cutoffName { spotLightsName + "cutoff" };
            const std::string outerCutoffName { spotLightsName + "outercutoff" };
            const std::string ambientName { spotLightsName + "ambient" };
            const std::string diffusetName { spotLightsName + "diffuse" };
            const std::string specularName { spotLightsName + "specular" };
            const std::string constantName { spotLightsName + "constant" };
            const std::string linearName { spotLightsName + "linear" };
            const std::string quadraticName { spotLightsName + "quadratic" };

            shader->SetVec3(positionName,
                            static_cast<glm::vec3>(spotLight->GetGlobalTransform().GetPosition()));
            shader->SetVec3(directionName,
                            spotLight->GetGlobalTransform().GetAxis().GetFront());
            shader->SetFloat(cutoffName, glm::cos(spotLight->GetCutoffRadians()));
            shader->SetFloat(outerCutoffName, glm::cos(spotLight->GetOuterCutoffRadians()));
            shader->SetVec3(ambientName,
                            static_cast<glm::vec3>(spotLight->GetAmbientColor()));
            shader->SetVec3(diffusetName,
                            static_cast<glm::vec3>(spotLight->GetDiffuseColor()));
            shader->SetVec3(specularName,
                            static_cast<glm::vec3>(spotLight->GetSpecularColor()));
            shader->SetFloat(constantName, spotLight->GetConstant());
            shader->SetFloat(linearName, spotLight->GetLinear());
            shader->SetFloat(quadraticName, spotLight->GetQuadratic());
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
        TextureData { ::DEFAULT_TEXTURE_PATH, GL_TEXTURE0 },
        TextureData { ::DEFAULT_TEXTURE_PATH, GL_TEXTURE1 },
        TextureData { ::DEFAULT_TEXTURE_PATH, GL_TEXTURE2 },
        ::DEFAULT_SHININESS
    } {}


TextureMaterial::TextureMaterial(const TextureData& diffuse,
                                 const TextureData& specular,
                                 const TextureData& emission) :
    TextureMaterial { diffuse, specular, emission, ::DEFAULT_SHININESS } {}

TextureMaterial::TextureMaterial(const TextureData& diffuse,
                                 const TextureData& specular,
                                 const TextureData& emission,
                                 float shininess) :
    Material { std::shared_ptr<Shader> {
        new Shader { TEXTURE_VERTEX_PATH, TEXTURE_FRAGMENT_PATH } } },
    m_diffuse { diffuse },
    m_specular { specular },
    m_emission { emission },
    m_shininess { shininess } {}


void TextureMaterial::Processing() {
    Material::Processing();

    GetDiffuse()->Processing();
    GetSpecular()->Processing();
    GetEmission()->Processing();
}


std::shared_ptr<Texture> TextureMaterial::GetDiffuse() const {
    return Everywhere::Instance().Get<TextureStorage>().Get(m_diffuse);
}

std::shared_ptr<Texture> TextureMaterial::GetSpecular() const {
    return Everywhere::Instance().Get<TextureStorage>().Get(m_specular);
}

std::shared_ptr<Texture> TextureMaterial::GetEmission() const {
    return Everywhere::Instance().Get<TextureStorage>().Get(m_emission);
}

TextureData TextureMaterial::GetDiffuseTextureData() const {
    return m_diffuse;
}

TextureData TextureMaterial::GetSpecularTextureData() const {
    return m_specular;
}

TextureData TextureMaterial::GetEmissionTextureData() const {
    return m_emission;
}

void TextureMaterial::SetDiffuseTextureData(const TextureData& diffuse) {
    m_diffuse = diffuse;
}

void TextureMaterial::SetSpecularTextureData(const TextureData& specular) {
    m_specular = specular;
}

void TextureMaterial::SetEmissionTextureData(const TextureData& emission) {
    m_emission = emission;
}

float TextureMaterial::GetShininess() const {
    return m_shininess;
}

void TextureMaterial::SetShininess(float shininess) {
    m_shininess = shininess;
}
