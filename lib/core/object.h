#ifndef OBJECT_H
#define OBJECT_H

#include "iprocess.h"
#include "collectionof.h"
#include "mesh.h"
#include "material.h"


class Object : public IProcess {
private:
    CollectionOf<Mesh> m_meshes;
    CollectionOf<Material> m_materials;

public:
    Object();
    ~Object();

public:
    CollectionOf<Mesh>& GetMeshes();
    const CollectionOf<Mesh>& GetMeshes() const;

    CollectionOf<Material>& GetMaterials();
    const CollectionOf<Material>& GetMaterials() const;

public: /* IProcess */
    void Processing() override;
};

#endif // OBJECT_H
