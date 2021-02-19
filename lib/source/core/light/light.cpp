#include "light/light.h"

#include "everywhere.h"
#include "material/lightmaterial.h"


Light::Light() :
    Light { Color::WHITE } {}

Light::Light(const Color& color) :
    Object {},
    m_color { color },
    m_childMesh {} {}


void Light::Processing() {
    Object::Processing();

    if (m_childMesh) {
        m_childMesh->SetParentTransform(GetParentTransform() + GetTransform());
        m_childMesh->Processing();
    }
}

Color Light::GetColor() const {
    return m_color;
}

void Light::SetColor(const Color& color) {
    m_color = color;

    if (m_childMesh) {
        const size_t ID = m_childMesh->GetMaterialId();
        std::shared_ptr<LightMaterial> childLightMaterial =
                std::dynamic_pointer_cast<LightMaterial>(
                        Everywhere::Instance().Get<MaterialStorage>().GetMaterials().At(ID));

        if (childLightMaterial) {
            childLightMaterial->SetColor(color);
        }
    }
}
