#include "pointlightmaterial.h"


void PointLightMaterial::InitShader() {
    auto UniformCameraFunc = [this](Shader* shader) {
        if (this == nullptr) return;

        shader->SetVec4("color", static_cast<glm::vec4>(GetColor()));
    };

    m_shader->UniformProcessingFunctions().push_back(UniformCameraFunc);
}
