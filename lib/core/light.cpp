#include "light.h"

#include "everywhere.h"
#include "lightmaterial.h"


Light::Light() :
    Object {},
    m_color {},
    m_childMesh {} {}

void Light::Processing() {
    Object::Processing();

    m_childMesh->SetGlobalTransform(GetGlobalTransform() + GetTransform());
    m_childMesh->Processing();
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
