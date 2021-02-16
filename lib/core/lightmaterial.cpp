#include "lightmaterial.h"


void LightMaterial::DoInitShader() {
    auto UniformCameraFunc = [this](Shader* shader) {
        if (this == nullptr) return;

        shader->SetVec4("color", static_cast<glm::vec4>(GetColor()));
    };

    m_shader->UniformProcessingFunctions().push_back(UniformCameraFunc);
}

Color LightMaterial::GetColor() const {
    return m_color;
}

void LightMaterial::SetColor(const Color& color) {
    m_color = color;
}
