#ifndef MATERIALSTORAGE_H
#define MATERIALSTORAGE_H

#include "interface/icanbeeverywhere.h"
#include "misc/collectionof.h"
#include "material/material.h"

#include <cstddef>


class MaterialStorage final : public ICanBeEverywhere {
private:
    CollectionOf<Material> m_materials;

public:
    MaterialStorage();
    ~MaterialStorage();

public:
    MaterialStorage(const MaterialStorage&) = delete;
    MaterialStorage(MaterialStorage&&) noexcept = delete;
    MaterialStorage& operator=(const MaterialStorage&) = delete;
    MaterialStorage& operator=(MaterialStorage&&) noexcept = delete;

public:
    CollectionOf<Material>& GetMaterials();
    const CollectionOf<Material>& GetMaterials() const;

    size_t GetLastMaterialID() const;
};

#endif // MATERIALSTORAGE_H
