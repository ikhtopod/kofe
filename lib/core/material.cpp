#include "material.h"


Material::Material() :
    GlobalTransformation {},
    m_shader { new Shader {} },
    m_textures {} {}

Material::~Material() {
    m_textures.Clear();
}

std::shared_ptr<Shader> Material::GetShader() {
    return m_shader;
}
const std::shared_ptr<Shader> Material::GetShader() const {
    return m_shader;
}

void Material::SetShader(const std::shared_ptr<Shader>& shader) {
    m_shader = shader;
}

CollectionOf<Texture>& Material::GetTextures() {
    return m_textures;
}
const CollectionOf<Texture>& Material::GetTextures() const {
    return m_textures;
}

void Material::Processing() {
    if (m_shader->UniformProcessingFunctions().size() == 0) {
        DoInitShader();
    }

    m_shader->SetGlobalTransform(this->GetGlobalTransform());
    m_shader->Processing();

    for (auto& texture : m_textures.Get()) {
        texture->Processing();
    }
}
