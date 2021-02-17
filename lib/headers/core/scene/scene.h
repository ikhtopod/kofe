#ifndef SCENE_H
#define SCENE_H

#include "interface/iprocess.h"
#include "transform/transformable.h"
#include "misc/collectionof.h"
#include "object.h"


class Scene :
    public IProcess,
    public Transformable {
private:
    CollectionOf<Object> m_objects;

public:
    Scene();
    virtual ~Scene();

public:
    CollectionOf<Object>& GetObjects();
    const CollectionOf<Object>& GetObjects() const;

public: /* IProcess */
    void Processing() override;
};

#endif // SCENE_H
