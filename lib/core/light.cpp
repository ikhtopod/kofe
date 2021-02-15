#include "light.h"

#include "everywhere.h"


Light::Light() :
    Object {},
    Colorable {},
    m_childMesh {} {}

void Light::Processing() {
    Object::Processing();

    m_childMesh->SetGlobalTransform(GetGlobalTransform() + GetTransform());
    m_childMesh->Processing();
}

void Light::SetColor(const Color& color) {
    Colorable::SetColor(color);

    if (m_childMesh) {
        const size_t ID = m_childMesh->GetMaterialId();
        std::shared_ptr<Material>& childMaterial =
                Everywhere::Instance().Get<MaterialStorage>().GetMaterials().At(ID);
        childMaterial->SetColor(color);
    }
}
