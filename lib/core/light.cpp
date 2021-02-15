#include "light.h"

#include "everywhere.h"
#include "mesh.h"


Light::Light() :
    Object {},
    Colorable {} {}

void Light::Processing() {
    Object::Processing();
}

void Light::SetColor(const Color& color) {
    Colorable::SetColor(color);

    std::shared_ptr<Mesh> meshChild { std::dynamic_pointer_cast<Mesh>(m_children.Front()) };
    if (meshChild) {
        const size_t ID = meshChild->GetMaterialId();
        std::shared_ptr<Material>& childMaterial =
                Everywhere::Instance().Get<MaterialStorage>().GetMaterials().At(ID);
        childMaterial->SetColor(color);
    }
}