#include "material.h"

#include "app_exceptions.h"


Material::Material() :
    m_shaders {} {}

Material::~Material() {
    m_shaders.Clear();
}

CollectionOf<Shader>& Material::GetShaders() { return m_shaders; }
const CollectionOf<Shader>& Material::GetShaders() const { return m_shaders; }

void Material::Processing() {
    for (auto& shader : m_shaders.Get()) {
        shader->Processing();
    }
}
