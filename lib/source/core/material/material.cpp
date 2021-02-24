#include "material/material.h"


Material::Material() :
    Material { std::shared_ptr<Shader> { new Shader {} } } {}


Material::Material(const std::shared_ptr<Shader>& shader) :
    ParentTransformation {},
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
    if (m_shader->UniformProcessingFunctions().empty()) {
        DoInitShader();
    }

    m_shader->SetParentTransform(this->GetParentTransform());
    m_shader->Processing();
}
