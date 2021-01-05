#ifndef SCENE_H
#define SCENE_H

#include "iprocess.h"
#include "object.h"

#include <cstddef>
#include <vector>
#include <memory>


class Scene : public IProcess {
    using ObjectSPtr = std::shared_ptr<Object>;

private:
    std::vector<ObjectSPtr> m_objects;

public:
    Scene();
    ~Scene();

public: /* Object operations */
    void AddObject(const ObjectSPtr& object);
    void DeleteObjects(size_t index);
    void ClearObjects();

public: /* IProcess */
    void Processing() override;
};

#endif // SCENE_H
