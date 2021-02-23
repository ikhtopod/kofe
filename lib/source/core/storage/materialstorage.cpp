#include "storage/materialstorage.h"

#include "app_exceptions.h"


MaterialStorage::MaterialStorage() :
    m_materials {} {}

MaterialStorage::~MaterialStorage() {
    m_materials.Clear();
}

CollectionOf<Material>& MaterialStorage::GetMaterials() {
    return m_materials;
}

const CollectionOf<Material>& MaterialStorage::GetMaterials() const {
    return m_materials;
}

size_t MaterialStorage::GetLastMaterialID() const {
    if (m_materials.IsEmpty()) {
        throw MaterialStorageException {
            "MaterialStorage has no last material id (MaterialStorage is empty)"
        };
    }

    return m_materials.Size() - 1;
}
