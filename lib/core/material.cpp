#include "material.h"

#include "app_exceptions.h"
#include "everywhere.h"
#include <algorithm>


namespace {
namespace uniform_name {

static const std::string OBJECT_COLOR { "material.color" };

}; // namespace uniform_name
}; // namespace


Material::Material() :
    GlobalTransformation {},
    Colorable { Color::WHITE },
    m_shaders {},
    m_textures {} {}

Material::~Material() {
    m_shaders.Clear();
    m_textures.Clear();
}

CollectionOf<Shader>& Material::GetShaders() {
    return m_shaders;
}
const CollectionOf<Shader>& Material::GetShaders() const {
    return m_shaders;
}

CollectionOf<Texture>& Material::GetTextures() {
    return m_textures;
}
const CollectionOf<Texture>& Material::GetTextures() const {
    return m_textures;
}

void Material::UniformMaterialData() const {
    for (auto& shader : m_shaders.Get()) {
        shader->SetVec4(::uniform_name::OBJECT_COLOR, static_cast<glm::vec4>(m_color));
    }
}

void Material::UniformLightData() const {
    auto& pointLights = Everywhere::Instance().Get<LightStorage>().GetPointLights();

    size_t end = std::min<size_t>(LightStorage::MAX_POINT_LIGHTS, pointLights.size());

    for (auto& shader : m_shaders.Get()) {
        for (size_t i = 0; i < end; ++i) {
            std::string posName { "pointLights[" + std::to_string(i) + "].position" };
            shader->SetVec3(posName,
                            static_cast<glm::vec3>(pointLights[i]->GetGlobalTransform().GetPosition()),
                            true);

            std::string colorName { "pointLights[" + std::to_string(i) + "].color" };
            shader->SetVec4(colorName,
                            static_cast<glm::vec4>(pointLights[i]->GetColor()),
                            true);
        }
    }
}

void Material::Processing() {
    for (auto& shader : m_shaders.Get()) {
        shader->Use();
        shader->SetGlobalTransform(this->GetGlobalTransform());
        UniformMaterialData();
        UniformLightData();
        shader->Processing();
    }

    for (auto& texture : m_textures.Get()) {
        texture->Processing();
    }
}
