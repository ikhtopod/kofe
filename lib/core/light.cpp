#include "light.h"

#include "everywhere.h"


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
        std::shared_ptr<Material>& childMaterial =
                Everywhere::Instance().Get<MaterialStorage>().GetMaterials().At(ID);
        childMaterial->SetColor(color);
    }
}
