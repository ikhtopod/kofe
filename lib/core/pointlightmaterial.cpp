#include "pointlightmaterial.h"


void PointLightMaterial::InitShaders() {
    auto UniformCameraFunc = [this](Shader* shader) {
        if (this == nullptr) return;

        shader->SetVec4("color", static_cast<glm::vec4>(GetColor()));
    };

    for (auto& shader : m_shaders.Get()) {
        shader->UniformProcessingFunctions().push_back(UniformCameraFunc);
    }
}
