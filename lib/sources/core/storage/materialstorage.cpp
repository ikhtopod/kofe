#include "storage/materialstorage.h"


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
