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

    for (auto& child : m_children.Get()) {
        std::shared_ptr<Mesh> meshChild { std::dynamic_pointer_cast<Mesh>(child) };

        if (meshChild) {
            std::shared_ptr<Material>& childMaterial =
                    Everywhere::Instance().Get<MaterialStorage>().GetMaterials().At(
                            meshChild->GetMaterialId());
            childMaterial->SetColor(color);
        }
    }
}