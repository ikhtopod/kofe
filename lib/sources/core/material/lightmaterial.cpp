#include "material/lightmaterial.h"


namespace {

static const std::filesystem::path LIGHT_VERTEX_PATH {
    R"vert(./resources/shaders/light-shader.vert)vert"
};

static const std::filesystem::path LIGHT_FRAGMENT_PATH {
    R"frag(./resources/shaders/light-shader.frag)frag"
};

} // namespace


void LightMaterial::DoInitShader() {
    auto UniformCameraFunc = [this](Shader* shader) {
        if (this == nullptr) return;

        shader->SetVec4("color", static_cast<glm::vec4>(GetColor()));
    };

    m_shader->UniformProcessingFunctions().push_back(UniformCameraFunc);
}

LightMaterial::LightMaterial() :
    LightMaterial { Color::BLACK } {}


LightMaterial::LightMaterial(const Color& color) :
    Material { std::shared_ptr<Shader> {
            new Shader { LIGHT_VERTEX_PATH, LIGHT_FRAGMENT_PATH } } },
    m_color { color } {}

Color LightMaterial::GetColor() const {
    return m_color;
}

void LightMaterial::SetColor(const Color& color) {
    m_color = color;
}
