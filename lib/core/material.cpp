#include "material.h"

#include "app_exceptions.h"


Material::Material() :
    m_shaders {},
    m_textures {} {}

Material::~Material() {
    m_shaders.Clear();
    m_textures.Clear();
}

CollectionOf<Shader>& Material::GetShaders() { return m_shaders; }
const CollectionOf<Shader>& Material::GetShaders() const { return m_shaders; }

CollectionOf<Texture>& Material::GetTextures() { return m_textures; }
const CollectionOf<Texture>& Material::GetTextures() const { return m_textures; }

void Material::Processing() {
    for (auto& shader : m_shaders.Get()) {
        shader->Processing();
    }

    for (auto& texture : m_textures.Get()) {
        texture->Processing();
    }
}
