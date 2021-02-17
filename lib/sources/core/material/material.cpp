#include "material/material.h"


Material::Material() :
    Material { std::shared_ptr<Shader> { new Shader {} } } {}


Material::Material(const std::shared_ptr<Shader>& shader) :
    GlobalTransformation {},
    m_shader { shader } {}

std::shared_ptr<Shader> Material::GetShader() {
    return m_shader;
}

const std::shared_ptr<Shader> Material::GetShader() const {
    return m_shader;
}

void Material::SetShader(const std::shared_ptr<Shader>& shader) {
    m_shader = shader;
}

void Material::Processing() {
    if (m_shader->UniformProcessingFunctions().size() == 0) {
        DoInitShader();
    }

    m_shader->SetGlobalTransform(this->GetGlobalTransform());
    m_shader->Processing();
}
