#ifndef OBJECT_H
#define OBJECT_H

#include "iprocess.h"
#include "transformable.h"
#include "collectionof.h"
#include "mesh.h"


class Object :
        public IProcess,
        public Transformable
{
private:
    CollectionOf<Mesh> m_meshes;

public:
    Object();
    ~Object();

public:
    CollectionOf<Mesh>& GetMeshes();
    const CollectionOf<Mesh>& GetMeshes() const;

public: /* IProcess */
    void Processing() override;
};

#endif // OBJECT_H
