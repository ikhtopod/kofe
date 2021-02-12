#include "material.h"

#include "app_exceptions.h"


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

void Material::Processing() {
    for (auto& shader : m_shaders.Get()) {
        shader->SetGlobalTransform(this->GetGlobalTransform());
        UniformMaterialData();
        shader->Processing();
    }

    for (auto& texture : m_textures.Get()) {
        texture->Processing();
    }
}
