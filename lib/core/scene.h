#ifndef SCENE_H
#define SCENE_H

#include "iprocess.h"
#include "collectionof.h"
#include "object.h"


class Scene : public IProcess {
private:
    CollectionOf<Object> m_objects;

public:
    Scene();
    ~Scene();

public:
    CollectionOf<Object>& GetObjects();
    const CollectionOf<Object>& GetObjects() const;

public: /* IProcess */
    void Processing() override;
};

#endif // SCENE_H
